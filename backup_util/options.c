#include <stdio.h>

#define OPTIONS_FILE_NAME "backup_options.txt"

int main() {
    FILE* options_file = fopen(OPTIONS_FILE_NAME, "w");
    int show_backup_console = 0;

    printf("========== BACKUP OPTIONS ==========");
    printf("Show backup console?(1/0): ");
    if (scanf("%d", &show_backup_console) == 1 && (show_backup_console == 0 || show_backup_console == 1)) {
        printf("Set option \'show backup console\' to %d\n", show_backup_console);
    }
    else {
        printf("Wrong input, please, enter 1(yes) or 0(no)");
    }

    fwrite(&show_backup_console, sizeof(int), 1, options_file);
    fwrite('\n', sizeof(char), 1, options_file);



    return 0;
}