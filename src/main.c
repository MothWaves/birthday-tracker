#include <stdio.h>
#include <jansson.h>
#include <string.h>

int handle_config();
void create_config();
json_t read_birthdays(char* path);
void print_usage();
void handle_arguments(int argc, char *argv[]);

// config struct
typedef struct {
    char* path_to_birthdays;
} config_t;

// birthday struct
typedef struct {
    char* person_name;
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

// Initiate global config file.
config_t config;
// Program command mode
enum command program_command;

int main(int argc, char *argv[]) {
    // Read config file.
    int error = handle_config();

    // Create config file if config is missing.
    if (error == -1) {
        create_config();
    }
    // Read birthday json file.
    json_t *json_root = json_load_file(config.path_to_birthdays, JSON_REJECT_DUPLICATES, NULL);
    if (!json_root) {
        // TODO :: Create json and reassign pointer.
    }

    handle_arguments(argc, argv);
}

// This should either be handle_arguments or get_command
void handle_arguments(int argc, char *argv[]) {
    if (argc < 2) {
        program_command = LIST;
    }
    else {
        char *argument = argv[1];
        if (strcmp(argument, "list") == 0) {
            program_command = LIST;
        }
        else if (strcmp(argument, "add") == 0) {
            program_command = LIST;
        }
        else if (strcmp(argument, "edit") == 0) {
            program_command = LIST;
        }
        else if (strcmp(argument, "remove") == 0) {
            program_command = LIST;
        }
        else {
            // Handle flags given to no command
        }
    }
}
