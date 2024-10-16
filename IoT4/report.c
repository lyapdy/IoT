#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "temp_function.h"
#include "temp_interact_mode.h"
#include "time.h"
#include "MQTTClient.h"

// Определяем константы
#define CLIENTID "ExampleClientPub" // Идентификатор клиента для подключения к MQTT
#define TOPIC "/node-red/temp"      // Топик для публикации данных температуры
#define PAYLOAD "32"                // Payload для публикации (по умолчанию "Hello World!")
#define QOS 1                       // Качество обслуживания для публикации
#define TIMEOUT 10000L              // Таймаут для публикации

#define SET_BIT(REG, BIT) ((REG) = (REG) | (BIT)) // Битовая операция установки
#define READ_BIT(REG, BIT) ((REG) & (BIT))        // Битовая операция чтения
#define USERNAME_OFFSET 0                         // Смещение для имени пользователя в флагах разрешения
#define PASSWWORD_OFFSET 1                        // Смещение для пароля в флагах разрешения
#define ADDRESS_OFFSET 2                          // Смещение для адреса в флагах разрешения
#define SEND_PERMISSION 0b111                     // Флаги разрешения для отправки сообщений MQTT

int sendMqttPermission = 0; // Флаги разрешения для отправки сообщений MQTT
double DELAY = 5;           // Задержка между отправкой сообщений MQTT

// Определяем структуры для данных температуры и статистики
struct TemperatureData records[MAX_RECORDS_PER_MONTH * MAX_MONTHS];
struct MonthlyStatistics monthlyStatistics[MAX_RECORDS_PER_MONTH * MAX_MONTHS];
struct YearlyStatistics yearlyStatistics;

int main(int argc, char *argv[])
{
    // Инициализируем клиент MQTT и опции подключения
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;

    // Обрабатываем параметры командной строки
    const char *PASS_FILE_EXTENSION = ".csv";
    char PORT[] = ":1883";
    char *filename = NULL;
    char *extension = NULL;
    char *saveFilename = NULL;
    int month = 0;
    int opt = 0;
    int numEntries;
    char ADDRESS[30] = "";

    // обрабатываем аргументы командной строки
    while ((opt = getopt(argc, argv, "hf:m:s:iu:p:c:")) != -1)
    {

        switch (opt)
        {
        // Печатаем сообщение помощи
        case 'h':
            printf("This program calculates the statistics of temperature data in a CSV file.\n");
            printf("-f filename.csv: the input file to process (required)\n");
            printf("-m month: the month for statistics output is 1-12 (optional)\n");
            printf("-s filename: save output in file (optional)\n");
            printf("-i enter to interactive mode (optional)\n");
            printf("To send the average temperature values per message, you must specify the user name, password and connection address.\n");
            printf("-u username: the username to connect to the MQTT broker\n");
            printf("-p password: the password to connect to the MQTT broker\n");
            printf("-c address: the address to connect to the MQTT broker\n");

            return 0;
        // Обрабатываем параметр имени файла
        case 'f':
            filename = optarg;
            break;
        // Обрабатываем параметр месяца
        case 'm':
            month = atoi(optarg);
            break;
        // Обрабатываем параметр сохранения файла
        case 's':
            saveFilename = optarg;
            break;
        // Переходим в интерактивный режим
        case 'i':
            printf("Welcome to interactive mode\n");
            showInteractMenu();

            return 0;
        // Обрабатываем параметр имени пользователя для MQTT брокера
        case 'u':
            printf("username: %s \n", optarg);
            conn_opts.username = optarg;
            SET_BIT(sendMqttPermission, (1 << USERNAME_OFFSET));
            break;
        // Обрабатываем параметр пароля для MQTT брокера
        case 'p':
            printf("password: %s \n", optarg);
            conn_opts.password = optarg;
            SET_BIT(sendMqttPermission, (1 << PASSWWORD_OFFSET));
            break;
        // Обрабатываем параметр адреса для MQTT брокера
        case 'c':
            printf("ADDRESS: %s \n", optarg);
            strcpy(ADDRESS, optarg);
            SET_BIT(sendMqttPermission, (1 << ADDRESS_OFFSET));
            break;
        default:
            printf("This program calculates the statistics of temperature data in a CSV file.\n");
            printf("Usage: [-h for help] \n");

            return 1;
        }
    }

    // Проверяем, указан ли входной файл
    if (filename == NULL)
    {
        printf("This program calculates the statistics of temperature data in a CSV file.\n");
        fprintf(stderr, "Input file is required. Use -f option.\n");
        printf("Usage: [-h for help] \n");
        return 1;
    }

    extension = strrchr(filename, '.');
    if (extension == NULL || strcmp(extension, PASS_FILE_EXTENSION) != 0)
    {
        fprintf(stderr, "Wrong file extension. Please try again.\n");
        return 1;
    }

    // Проверяем, является ли месяц корректным
    if (month < 0 || month > 12)
    {
        fprintf(stderr, "Wrong input month. Please try again.\n");
        return 1;
    }

    // Парсим файл CSV и рассчитываем статистику
    numEntries = parseCSVFile(filename, records);
    calculateStatistics(records, numEntries, monthlyStatistics, &yearlyStatistics);

    // Выводим статистику в зависимости от указанного месяца или вывод полной
    if (month == 0)
    {
        showMonthlyStatistics(stdout, monthlyStatistics);
        showYearlyStatistics(stdout, &yearlyStatistics);
    }
    else
    {
        showMonthStatistics(stdout, monthlyStatistics, month);
    }

    // сохраняем статистику в файл, если указан
    if (saveFilename != NULL)
    {
        FILE *fo = fopen(saveFilename, "w");

        if (month == 0)
        {
            showMonthlyStatistics(fo, monthlyStatistics);
            showYearlyStatistics(fo, &yearlyStatistics);
        }
        else
        {
            showMonthStatistics(fo, monthlyStatistics, month);
        }

        fclose(fo);
    }

    // Проверяем, указаны ли все необходимые параметры для отправки сообщений MQTT
    if (!READ_BIT(sendMqttPermission, (1 << USERNAME_OFFSET)))
    {
        printf("Username no entered\n");
    }

    if (!READ_BIT(sendMqttPermission, (1 << PASSWWORD_OFFSET)))
    {
        printf("Password no entered\n");
    }

    if (!READ_BIT(sendMqttPermission, (1 << ADDRESS_OFFSET)))
    {
        printf("Addres no entered\n");
    }

    // Отправляем сообщения MQTT, если указаны все необходимые параметры
    if (sendMqttPermission == SEND_PERMISSION)
    {
        strcat(ADDRESS, PORT);
        printf("Connection: %s \n", ADDRESS);

        MQTTClient_create(&client, ADDRESS, CLIENTID,
                          MQTTCLIENT_PERSISTENCE_NONE, NULL);
        conn_opts.keepAliveInterval = 20;
        conn_opts.cleansession = 1;
        // conn_opts.username =  "IoT";
        // conn_opts.password = "student1";

        if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
        {
            printf("Failed to connect, return code %d\n", rc);
            exit(-1);
        }

        int i = 0;
        while (1)
        {

            clock_t begin = clock();

            char str[255];
            sprintf(str, "%.2f", monthlyStatistics[i].averageTemperature);
            printf("%d. Send mqtt monthly average temperature: %s\n", i + 1, str);
            i++;

            pubmsg.payload = str;
            pubmsg.payloadlen = strlen(str);
            pubmsg.qos = QOS;
            pubmsg.retained = 0;
            MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
            // printf("Waiting for up to %d seconds for publication of %s\n"
            //         "on topic %s for client with ClientID: %s\n",
            //         (int)(TIMEOUT/1000), PAYLOAD, TOPIC, CLIENTID);
            rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
            // printf("Message with delivery token %d delivered\n", token);

            if (i >= 12)
                break;

            while ((double)(clock() - begin) / CLOCKS_PER_SEC < DELAY)
            {
            }
        }
        printf("Send completed\n");
        MQTTClient_disconnect(client, 10000);
        MQTTClient_destroy(&client);
    }
    else
    {
        printf("Send mqtt blocked\n");
    }

    return 0;
}
