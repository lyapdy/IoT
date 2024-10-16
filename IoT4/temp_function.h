#ifndef TEMP_FUNCTION_H
#define TEMP_FUNCTION_H

/**
 * Maximum number of data rows that can be stored.
 */
#define MAX_DATA_ROWS 10000

/**
 * Maximum temperature value that can be recorded.
 */
#define MAX_TEMP_VALUE 99

/**
 * Minimum temperature value that can be recorded.
 */
#define MIN_TEMP_VALUE -99

/**
 * Maximum number of months in a year.
 */
#define MAX_MONTHS 12

/**
 * Maximum number of records that can be stored per month.
 */
#define MAX_RECORDS_PER_MONTH 44640

/**
 * Represents a single temperature data point.
 */
struct TemperatureData
{
    /**
     * The year of the data point.
     */
    int year;

    /**
     * The month of the data point.
     */
    int month;

    /**
     * The day of the data point.
     */
    int day;

    /**
     * The hour of the data point.
     */
    int hour;

    /**
     * The minute of the data point.
     */
    int minute;

    /**
     * The temperature value of the data point.
     */
    int temperature;
};

/**
 * Represents the monthly statistics for a given year and month.
 */
struct MonthlyStatistics
{
    /**
     * The year of the statistics.
     */
    int year;

    /**
     * The month of the statistics.
     */
    int month;

    /**
     * The average temperature for the month.
     */
    float averageTemperature;

    /**
     * The minimum temperature recorded for the month.
     */
    int minTemperature;

    /**
     * The maximum temperature recorded for the month.
     */
    int maxTemperature;

    /**
     * The number of data points used to calculate the statistics.
     */
    int count;
};

/**
 * Represents the yearly statistics for a given year.
 */
struct YearlyStatistics
{
    /**
     * The average temperature for the year.
     */
    float averageTemperature;

    /**
     * The minimum temperature recorded for the year.
     */
    int minTemperature;

    /**
     * The maximum temperature recorded for the year.
     */
    int maxTemperature;
};

/**
 * Parses a CSV file and stores the data in the provided array.
 *
 * @param filename the name of the CSV file to parse
 * @param data the array to store the parsed data in
 * @return the number of data points parsed
 */
int parseCSVFile(const char *filename, struct TemperatureData *data);

/**
 * Calculates the monthly and yearly statistics from the provided data.
 *
 * @param data the array of temperature data points
 * @param numEntries the number of data points in the array
 * @param statistics the array to store the monthly statistics in
 * @param yearlyStatistics the structure to store the yearly statistics in
 */
void calculateStatistics(struct TemperatureData *data, int numEntries, struct MonthlyStatistics *statistics, struct YearlyStatistics *yearlyStatistics);

/**
 * Prints the yearly statistics to the provided stream.
 *
 * @param stream the stream to print to
 * @param statistics the yearly statistics to print
 */
void showYearlyStatistics(FILE *const stream, struct YearlyStatistics *statistics);

/**
 * Prints the monthly statistics to the provided stream.
 *
 * @param stream the stream to print to
 * @param statistics the monthly statistics to print
 */
void showMonthlyStatistics(FILE *const stream, struct MonthlyStatistics *statistics);

/**
 * Prints the monthly statistics for a specific month to the provided stream.
 *
 * @param stream the stream to print to
 * @param statistics the monthly statistics to print
 * @param month the month to print statistics for
 */
void showMonthStatistics(FILE *const stream, struct MonthlyStatistics *statistics, int month);

#endif /* TEMP_FUNCTION_H */
