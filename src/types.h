#ifndef TYPES_H_
#define TYPES_H_
#include <stdbool.h>

// config struct
typedef struct {
    const char* path_to_birthdays;
} config_t;

// birthday struct
typedef struct {
    const char* person_name;
    int day;
    int month;
    int year_of_birth;
    bool hidden;
    bool important;
} birthday_t;

enum command {
    LIST,
    ADD,
    EDIT,
    REMOVE
};

typedef struct date {
    int day;
    int month;
    int year;
} date_t;


#endif // TYPES_H_
