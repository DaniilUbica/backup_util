#include <stdio.h>

#define OPTIONS_FILE_NAME "backup_options.txt"

int enter_option_yes_no(char* option_name, int* option);

int main() {
    FILE* options_file = fopen(OPTIONS_FILE_NAME, "w");
    int show_backup_console = 0;
    int show_backup_gui = 0;

    printf("========== BACKUP OPTIONS ==========\n");
    enter_option_yes_no("backup console", &show_backup_console);

    fprintf(options_file, "%d\r", show_backup_console);
    enter_option_yes_no("backup gui", &show_backup_gui);

    fprintf(options_file, "%d\r", show_backup_gui);

    return 0;
}

int enter_option_yes_no(char* option_name, int* option) {
    while (1) {
        printf("Show %s?(1/0): ", option_name);
        if (scanf("%d", option) == 1 && (*option == 0 || *option == 1)) {
            printf("Set option \'show %s\' to %d\n", option_name, *option);
            break;
        }
        else {
            printf("Wrong input, please, enter 1(yes) or 0(no).\n");
            fflush(stdin);
        }
    }
}