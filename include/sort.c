#include "types.h"
#include <sys/types.h>

// Sorts birthdays, starting with the ones closest to the current_date and ending with the ones farthest.
void sort_birthdays(birthday_t *birthdays_array, size_t array_size, date_t current_date) {
    // Get ordinal of current_date.
    int current_ordinal = (current_date.month-1 * 30) + current_date.day;
    int ordinals[array_size];

    // Calculate ordinals
    for (int i = 0; i < array_size; i++) {
        ordinals[i] = (birthdays_array[i].month-1 * 30) + birthdays_array[i].day;
    }

    // Sort birthdays

}
