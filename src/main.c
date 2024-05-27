#include "time.h"
#include <stdio.h>
#include <jansson.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Default paths to config directory and database file, relative to the user's HOME directory.
#define CONFIG_PATH  ".config/birthday-tracker"
#define DATABASE_PATH ".local/share/birthday-tracker/birthdays.json"

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

// Function Prototypes
int handle_config();
void create_config();
json_t read_birthdays(char* path);
void print_usage();
void get_command(int argc, char *argv[]);
void set_defaults();
char *get_path_to_config_file();
void list_birthdays(birthday_t *birthdays_array, size_t array_size, date_t current_date);
birthday_t *decode_birthday_array(json_t *array, size_t *array_size);
void sort_birthdays(birthday_t *birthdays_array, size_t array_size, date_t date);
char *literal_month(int month);
date_t get_current_date();

// Initiate global config file.
config_t config;
// Program command mode
enum command program_command;

// Default config path and database path, respectively.
const char *default_config_path;
const char *default_database_path;

int main(int argc, char *argv[]) {
    // Set default global variables.
    set_defaults();
    // Read config file.
    int error = handle_config();

    // Create config file if config is missing.
    if (error == -1) {
        create_config();
        error = handle_config();
        if (error == -1) {
            printf("Could not read created config file. Exiting...\n");
            exit(-3);
        }
    }

    // Read birthday json file.
    json_t *json_root = json_load_file(config.path_to_birthdays, JSON_REJECT_DUPLICATES, NULL);
    if (!json_root) {
        json_root = json_array();
        if (json_dump_file(json_root, config.path_to_birthdays, 0) == -1) {
            printf("Couldn't create birthday json file. Exiting...");
            exit(-1);
        }
    }
    size_t birthdays_bufsize;
    birthday_t *birthdays = decode_birthday_array(json_root, &birthdays_bufsize);
    date_t current_date;
    get_command(argc, argv);
    switch (program_command) {
        case LIST:
            current_date = get_current_date();
            sort_birthdays(birthdays, birthdays_bufsize, current_date);
            list_birthdays(birthdays, birthdays_bufsize, current_date);
            break;
        case ADD:
            printf("Not implemented yet!\n");
            exit(0);
            break;
        case EDIT:
            printf("Not implemented yet!\n");
            exit(0);
            break;
        case REMOVE:
            printf("Not implemented yet!\n");
            exit(0);
            break;
        default:
            printf("This should be impossible! Uh oh!\n");
            exit(-4);
            break;
    }

    free(birthdays);
    return 0;
}

date_t get_current_date() {
    date_t current_date;

    time_t t = time(NULL);
    struct tm *date = localtime(&t);

    current_date.day = date->tm_mday;
    current_date.month = date->tm_mon;
    current_date.year = 1900 + date->tm_year;

    return current_date;
}

void sort_birthdays(birthday_t *birthdays_array, size_t array_size, date_t date) {

}

// This should either be handle_arguments or get_command
void get_command(int argc, char *argv[]) {
    if (argc < 2) {
        program_command = LIST;
    }
    else {
        char *argument = argv[1];
        if (strcmp(argument, "list") == 0) {
            program_command = LIST;
        }
        else if (strcmp(argument, "add") == 0) {
            program_command = ADD;
        }
        else if (strcmp(argument, "edit") == 0) {
            program_command = EDIT;
        }
        else if (strcmp(argument, "remove") == 0) {
            program_command = REMOVE;
        }
        else {
            // See if there's a way to not count the flags.
            // If there is and the user gives a non-existent command, they should get a usage warning.
            program_command = LIST;
        }
    }
}

// Opens config json file and sets the value of `config`.
// Returns -1 if it there is no config file.
int handle_config() {
    char *config_file = get_path_to_config_file();
    FILE *fptr = fopen(config_file, "r");

    // Config file not found.
    if (!fptr) {
        return -1;
    }
    // Set database path value.
    json_t *config_json = json_loadf(fptr, 0, NULL);
    const char *database_path = NULL;
    json_unpack(config_json, "{s?:s}", "database_path", &database_path);
    if (!database_path) {
        config.path_to_birthdays = default_database_path;
    }
    else {
        config.path_to_birthdays = database_path;
    }

    // Config complete.
    fclose(fptr);
    return 0;
}

// Creates a new empty config json file.
void create_config() {
    char * config_file = get_path_to_config_file();
    FILE *fptr = fopen(config_file, "w");

    if (!fptr) {
        printf("Failed to create config file. Exiting...\n");
        exit(-2);
    }
    else {
        fclose(fptr);
    }
}

char *get_path_to_config_file() {
    // Get config directory.
    const char *config_dir = getenv("BIRTHDAY_TRACKER_CONFIG");
    if (!config_dir) {
        // Default config path.
        config_dir = default_config_path;
    }

    // Get config.json file from config directory and open it.
    int n = strlen(config_dir) + strlen("/config.json");
    char *config_file = (char*) malloc((n+1));
    strcpy(config_file, config_dir);
    strcat(config_file, "/config.json");
    return config_file;
}

// Set default global variables.
void set_defaults() {
    char *home = getenv("HOME");
    int n = strlen(home);
    // no idea why I need to add 2 instead of 1 but it'll truncate the last character if I don't.
    // Missing some extra character being snuck in somewhere?
    //
    // Ok, so I figured it out, I guess snprintf needs the extra 1 for writing purposes, i don't know.
    // I've added that to the callings of snprintf and left the rest with the +1 so the strings are
    // just the right size.
    // I'm leaving these comments here for...historical purposes I guess.
    //
    // It actually needs +3 or there's issues. I don't know man.
    int bufsize_cf = n + strlen(CONFIG_PATH) + 3;
    int bufsize_db = n + strlen(DATABASE_PATH) + 3;
    char * config_path = (char*) malloc(bufsize_cf);
    char * database_path = (char*) malloc(bufsize_db);
    // Format default config path.
    snprintf(config_path, bufsize_cf-1, "%s/%s", home, CONFIG_PATH);
    // Format default database path.
    snprintf(database_path, bufsize_db-1, "%s/%s", home, DATABASE_PATH);

    default_config_path = config_path;
    default_database_path = database_path;
}

void list_birthdays(birthday_t *birthdays_array, size_t array_size, date_t current_date) {
    for (int i = 0; i < array_size; i++) {
        char *prefix;
        birthday_t bd = birthdays_array[i];
        switch (bd.day % 10) {
            case 1:
                prefix = "st";
                break;
            case 2:
                prefix = "nd";
                break;
            case 3:
                prefix = "rd";
                break;
            default:
                prefix = "th";
                break;
        }
        if (bd.day == 11 || bd.day == 12 || bd.day == 13) {
            prefix = "th";
        }
        printf("%s: %s %d%s", bd.person_name, literal_month(bd.month), bd.day, prefix);
        if (bd.year_of_birth != 0){
            printf("\t(Turns %d)\n", current_date.year - bd.year_of_birth);
        }
        else {
            printf("\n");
        }
    }
    if (array_size == 0) {
        printf("No birthdays!\n");
    }

}

char *literal_month(int month) {
    char *month_name;
    switch (month) {
        case 1:
            month_name = "January";
            break;
        case 2:
            month_name = "February";
            break;
        case 3:
            month_name = "March";
            break;
        case 4:
            month_name = "April";
            break;
        case 5:
            month_name = "May";
            break;
        case 6:
            month_name = "June";
            break;
        case 7:
            month_name = "July";
            break;
        case 8:
            month_name = "August";
            break;
        case 9:
            month_name = "September";
            break;
        case 10:
            month_name = "October";
            break;
        case 11:
            month_name = "November";
            break;
        case 12:
            month_name = "December";
            break;
        default:
            month_name = "Not a real month :)";
            break;
    }

    return month_name;
}

// Returns a dynamic array from the values from array and sets sizeptr to the number of entries in the array.
birthday_t *decode_birthday_array(json_t *array, size_t *sizeptr) {
    size_t array_size = json_array_size(array);
    // Set sizeptr.
    *sizeptr = array_size;
    birthday_t *birthdays = (birthday_t*) malloc(array_size * sizeof(birthday_t));
    if (!birthdays) {
        printf("Couldn't allocate memory.\n");
        exit(-6);
    }

    size_t i;
    json_t *value;
    json_t *name, *month, *day, *year;
    json_array_foreach(array, i, value) {
        int error = 0;

        // Check that elements are correct value, if not: exit.
        name = json_object_get(value, "name");
        if (!json_is_string(name)) {
            error = 1;
        }
        day = json_object_get(value, "day");
        if (!json_is_integer(day)){
            error = 1;
        }
        month = json_object_get(value, "month");
        if (!json_is_integer(month)) {
            error = 1;
        }
        year = json_object_get(value, "year");
        if (error == 1) {
            printf("Birthdays database is corrupted! Exiting...\n");
            free(birthdays);
            exit(-5);
        }

        // Set values
        birthdays[i].person_name = json_string_value(name);
        birthdays[i].day = json_integer_value(day);
        birthdays[i].month = json_integer_value(month);
        birthdays[i].year_of_birth = json_integer_value(year);

    }

    return birthdays;
}
