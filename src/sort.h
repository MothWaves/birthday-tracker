#ifndef SORT_H_
#define SORT_H_

void sort_birthdays(birthday_t *birthdays_array, size_t array_size, date_t current_date);
int calculate_ordinal(int day, int month, int year);
int isLeap(int year);
int calculateOrdinalDifference(date_t date, date_t other_date);



#endif // SORT_H_
