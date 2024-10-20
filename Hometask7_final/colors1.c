#include <stdio.h>

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define WHITE   "\033[1;37m"

int main() {
    printf("%s00%s",    YELLOW, RESET);
    printf("%s===3%s ", RED,    RESET);
    printf("%s-.%s\n",  WHITE,  RESET);
}