#include <stdio.h>
#include <jansson.h>
#include <string.h>

#define DEFAULT_CONFIG_PATH  "~/.config/birthday-tracker/config.json"
#define DEFAULT_DATABASE_PATH "~/.local/share/birthday-tracker/birthdays.json"

int handle_config();
void create_config();
json_t read_birthdays(char* path);
void print_usage();
void get_command(int argc, char *argv[]);

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
        json_root = json_pack("[]");
        if (json_dump_file(json_root, config.path_to_birthdays, 0) == -1) {
            printf("Couldn't create birthday json file. Exiting...");
            exit(-1);
        }
    }

    free(config.path_to_birthdays);
    get_command(argc, argv);
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
            program_command = LIST;
        }
    }
}

// Opens config json file and sets the value of `config`.
// Returns -1 if it there is no config file.
int handle_config() {
    char *config_path = getenv("BIRTHDAY_TRACKER_CONFIG");
    if (!config_path) {
        // Default config path.
        config_path = DEFAULT_CONFIG_PATH;
    }
    FILE *fptr = fopen(config_path, "r");

    // Config file not found.
    if (!fptr) {
        return -1;
    }

    // Set database path value.
    json_t *config_json = json_loadf(fptr, 0, NULL);
    const char *database_path;
    json_unpack(config_json, "{s:s}", "database_path", &database_path);
    if (!database_path) {
        config.path_to_birthdays = DEFAULT_DATABASE_PATH;
    }
    else {
        config.path_to_birthdays = realloc(config.path_to_birthdays, strlen(database_path)+1);
        strcpy(config.path_to_birthdays, database_path);
    }

    // Config complete.
    fclose(fptr);
    return 0;
}
