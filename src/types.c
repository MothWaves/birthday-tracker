#include "types.h"


date_t dateFromBirthday(birthday_t birthday) {
  date_t date = { birthday.day, birthday.month, birthday.year_of_birth };
  return date;
}
