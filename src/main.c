#include <stdio.h>
#include <jansson.h>
#include <stdlib.h>
#include <string.h>

// Default paths to config directory and database file, relative to the user's HOME directory.
#define CONFIG_PATH  ".config/birthday-tracker"
#define DATABASE_PATH ".local/share/birthday-tracker/birthdays.json"

int handle_config();
void create_config();
json_t read_birthdays(char* path);
void print_usage();
void get_command(int argc, char *argv[]);
void set_defaults();
char *get_path_to_config_file();

// config struct
typedef struct {
    const char* path_to_birthdays;
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

    printf("Value: %s\n", config.path_to_birthdays);
    printf("Value: %s\n", default_database_path);
    printf("Value: %s\n", default_config_path);
    exit(0);
    // Read birthday json file.
    json_t *json_root = json_load_file(config.path_to_birthdays, JSON_REJECT_DUPLICATES, NULL);
    if (!json_root) {
        // TODO :: Create json and reassign pointer.
        json_root = json_array();
        if (json_dump_file(json_root, config.path_to_birthdays, 0) == -1) {
            printf("Couldn't create birthday json file. Exiting...");
            exit(-1);
        }
    }

    printf("SUCCESS!\n");
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
