#include <stdio.h>
#include <stdlib.h>
#include "temp_function.h"

int parseCSVFile(const char *filename, struct TemperatureData *data)
{
    // Открываем файл для чтения
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error: Unable to open file %s\n", filename);
        return -1;
    }

    // Инициализируем счетчики
    int numEntries = 0;
    int countErrors = 0;
    char buffer[100];

    // Читаем файл построчно
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        // Пробуем распарсить строку
        if (sscanf(buffer, "%d;%d;%d;%d;%d;%d", &data[numEntries].year, &data[numEntries].month, &data[numEntries].day, &data[numEntries].hour, &data[numEntries].minute, &data[numEntries].temperature) == 6)
        {
            // Увеличиваем счетчик
            numEntries++;
        }
        else
        {
            fprintf(stderr, "Error: Invalid format in CSV file at line %d\n", numEntries + 2);
            countErrors++; // Увеличиваем счетчик ошибок
        }
    }

    // Если были ошибки, выводим сообщение
    if (countErrors > 0)
    {
        fprintf(stderr, "The number of errors detected in CSV file: %d.\n\n", countErrors);
    }

    fclose(file);
    return numEntries;
}

void calculateStatistics(struct TemperatureData *data, int numEntries, struct MonthlyStatistics *statistics, struct YearlyStatistics *yearlyStatistics)
{
    // Инициализируем статистику по году
    yearlyStatistics->averageTemperature = 0.0;
    yearlyStatistics->minTemperature = MAX_TEMP_VALUE;
    yearlyStatistics->maxTemperature = MIN_TEMP_VALUE;

    // Инициализируем статистику по месяцам
    for (int i = 0; i < 12; i++)
    {
        statistics[i].month = i + 1;
        statistics[i].averageTemperature = 0.0;
        statistics[i].minTemperature = MAX_TEMP_VALUE;
        statistics[i].maxTemperature = MIN_TEMP_VALUE;
    }

    int count = 0;
    // Обходим все записи в массиве
    for (int i = 0; i < numEntries; i++)
    {
        // Вычисляем статистику по году
        yearlyStatistics->averageTemperature += data[i].temperature;
        if (data[i].temperature < yearlyStatistics->minTemperature)
        {
            yearlyStatistics->minTemperature = data[i].temperature;
        }
        if (data[i].temperature > yearlyStatistics->maxTemperature)
        {
            yearlyStatistics->maxTemperature = data[i].temperature;
        }

        count++;

        // Вычисляем статистику по месяцу
        int index = data[i].month - 1;
        statistics[index].year = data[i].year;
        statistics[index].averageTemperature += data[i].temperature;
        if (data[i].temperature < statistics[index].minTemperature)
        {
            statistics[index].minTemperature = data[i].temperature;
        }
        if (data[i].temperature > statistics[index].maxTemperature)
        {
            statistics[index].maxTemperature = data[i].temperature;
        }
        statistics[index].count++;
    }

    // Вычисляем среднюю температуру по году и месяцам
    for (int i = 0; i < 12; i++)
    {
        if (statistics[i].count > 0)
        {
            statistics[i].averageTemperature /= statistics[i].count;
        }
    }

    if (count > 0)
    {
        yearlyStatistics->averageTemperature /= count;
    }
}

void showYearlyStatistics(FILE *const stream, struct YearlyStatistics *statistics)
{
    // выводим статистику за год
    fprintf(stream, "Year statistic: avr: %.1f; min: %d; max: %d;\n", statistics->averageTemperature, statistics->minTemperature, statistics->maxTemperature);
}

void showMonthlyStatistics(FILE *const stream, struct MonthlyStatistics *statistics)
{
    // выводим статистику по всем месяцам
    int countLine = 0;
    fprintf(stream, "ID# Year Month NuValue MonthAvg MonthMin MonthMax\n");
    for (int i = 0; i < 12; i++)
    {
        if (statistics[i].count > 0)
        {
            fprintf(stream, "%3d %4d %5d %7d %8.1f %8d %8d\n", ++countLine, statistics[i].year, statistics[i].month, statistics[i].count, statistics[i].averageTemperature, statistics[i].minTemperature, statistics[i].maxTemperature);
        }
    }
}

void showMonthStatistics(FILE *const stream, struct MonthlyStatistics *statistics, int month)
{
    // выводим статистику за определенный месяц
    int countLine = 0;
    fprintf(stream, "ID# Year Month NuValue MonthAvg MonthMin MonthMax\n");
    if (statistics[month].count > 0)
    {
        fprintf(stream, "%3d %4d %5d %7d %8.1f %8d %8d\n", ++countLine, statistics[month].year, statistics[month].month, statistics[month].count, statistics[month].averageTemperature, statistics[month].minTemperature, statistics[month].maxTemperature);
    }
}