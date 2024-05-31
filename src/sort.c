#include "types.h"
#include <stdio.h>
#include <sys/types.h>
#include <math.h>

void heapify(birthday_t *array, int ordinals[], size_t count, int i);
void birthdaySwap(birthday_t *a, birthday_t *b);
void intSwap(int *a, int *b);
int calculate_ordinal(int day, int month, int year);
int isLeap(int year);

// Sorts birthdays, starting with the ones closest to the current_date and ending with the ones farthest.
void sort_birthdays(birthday_t *birthdays_array, size_t array_size, date_t current_date) {
    // Get ordinal of current_date.
    int current_ordinal = calculate_ordinal(current_date.day, current_date.month, current_date.year);
    int ordinals[array_size];

    // Calculate ordinals
    for (int i = 0; i < array_size; i++) {
        int year = current_date.year;
        // Boolean flag that the birthday will happen next year.
        int next_year = 0;

        // Get year in which birthday will occur.
        if ((birthdays_array[i].month == current_date.month && birthdays_array[i].day < current_date.day) ||
        birthdays_array[i].month < current_date.month) {
            year += 1;
            next_year = 1;
        }
        // Calculate ordinal from the current_date.
        int birthday_ordinal = calculate_ordinal(birthdays_array[i].day, birthdays_array[i].month, year);
        birthday_ordinal -= current_ordinal; // This might cause an issue with leap years. I should fix that.
        if (next_year) {
            birthday_ordinal += 360;
        }
        ordinals[i] = birthday_ordinal;
    }

    // Sort birthdays (Uses heapsort)
    for (int i = array_size / 2 - 1; i >= 0; i--) {
        heapify(birthdays_array, ordinals, array_size, i);
    }

    for (int i = array_size - 1; i >= 0; i--) {
        birthdaySwap(&birthdays_array[0], &birthdays_array[i]);
        intSwap(&ordinals[0], &ordinals[i]);
        heapify(birthdays_array, ordinals, i, 0);
    }
}

int isLeap(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

int calculate_ordinal(int day, int month, int year) {
    int m, d, y;
    m = month;
    if (m <= 2) {
        m = month + 12;
    }
    d = day;
    y = year;

    int ordinal_march = (int) floor((153 * (m - 3) + 2) / (float) 5) + d;
    int ordinal;
    if (m <= 12) {
        ordinal = ordinal_march + 59 + isLeap(y);
    }
    else {
        ordinal = ordinal_march - 306;
    }
    return ordinal;
}

void heapify(birthday_t *array, int ordinals[], size_t count, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < count && ordinals[left] > ordinals[largest]) {
        largest = left;
    }
    if (right < count && ordinals[right] > ordinals[largest]) {
        largest = right;
    }

    if (largest != i) {
        birthdaySwap(&array[i], &array[largest]);
        intSwap(&ordinals[i], &ordinals[largest]);
        heapify(array, ordinals, count, largest);
    }
}

void birthdaySwap(birthday_t *a, birthday_t *b) {
    birthday_t aux = *a;
    *a = *b;
    *b = aux;
}

void intSwap(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}
