#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "temp_function.h"

#define MAX_LEN_FILENAME 100

extern struct TemperatureData records[MAX_RECORDS_PER_MONTH * MAX_MONTHS];
extern struct MonthlyStatistics monthlyStatistics[MAX_RECORDS_PER_MONTH * MAX_MONTHS];
extern struct YearlyStatistics yearlyStatistics;

void showInteractMenu()
{
    // Определение констант для расширения файла и максимальной длины имени файла
    const char *PASS_FILE_EXTENSION = ".csv";
    char *extension = NULL;
    char filename[MAX_LEN_FILENAME];
    char saveFilename[MAX_LEN_FILENAME];

    // Инициализация переменных для ввода и статистики
    int numEntries = 0;
    int choice = 0;

    do
    {
        // Отображение интерактивного меню пользователю
        printf("\nMenu:\n");
        printf("1. Open file\n");
        printf("2. Show statistics for all months\n");
        printf("3. Show statistics for one month\n");
        printf("4. Show statistics for the year\n");
        printf("5. Save statistics to a file\n");
        printf("0. Exit\n");
        printf("Select an action: ");
        scanf("%d", &choice);

        putchar('\n');
        switch (choice)
        {
        case 1:
            // Открытие файла
            printf("Enter file name: ");
            scanf("%s", filename);

            // Проверка расширения файла
            extension = strrchr(filename, '.');
            if (extension == NULL || strcmp(extension, PASS_FILE_EXTENSION) != 0)
            {
                fprintf(stderr, "Wrong file extension. Please try again.\n");
                continue;
            }

            // Парсинг файла и расчет статистики
            numEntries = parseCSVFile(filename, records);
            if (numEntries != -1)
            {
                calculateStatistics(records, numEntries, monthlyStatistics, &yearlyStatistics);
                fprintf(stderr, "%s file was opened successfully.", filename);
            }

            break;
        case 2:
        case 3:
        case 4:
        case 5:
            // Проверка, был ли открыт файл
            if (numEntries == 0)
            {
                fprintf(stderr, "Input file is required. Please open file.\n");
                continue;
            }

            // Обработка выбора пользователя
            switch (choice)
            {
            case 2:
                // Показать статистику для всех месяцев
                showMonthlyStatistics(stdout, monthlyStatistics);
                break;
            case 3:
                // Показать статистику для одного месяца
                printf("Select month: ");
                int month = 0;
                scanf("%d", &month);

                if (month < 0 || month > 12)
                {
                    fprintf(stderr, "Wrong input month. Please try again.\n");
                    continue;
                }
                showMonthStatistics(stdout, monthlyStatistics, month);
                break;
            case 4:
                // Показать статистику для года
                showYearlyStatistics(stdout, &yearlyStatistics);
                break;
            case 5:
                // Сохранить статистику в файл
                printf("Enter file name: ");
                scanf("%s", saveFilename);

                FILE *fo = fopen(saveFilename, "w");

                showMonthlyStatistics(fo, monthlyStatistics);
                showYearlyStatistics(fo, &yearlyStatistics);

                fclose(fo);
                break;
            }

            break;
        case 0:
            // Выход из программы
            printf("The program is completed.\n");
            break;
        default:
            // Неправильный ввод
            printf("Invalid selection. Try again.\n");
        }
    } while (choice != 0);
}