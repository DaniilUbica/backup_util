#include <iostream>

#include "Backupper.h"
#include "Config.h"

void gui_controll(Backupper& backupper) {
    bool is_working = true;
    std::cout << "====== BACKUPPER APP ======\n";
    while (is_working) {
        int choose = 0;
        std::cout << "1. Add new backup\n";
        std::cout << "2. Start backup\n";
        std::cout << "3. Show created backups\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter yor choose: ";

        std::cin >> choose;

        if (choose == 1) {
            std::string source, target, time;
            std::cout << "\nEnter source: ";
            std::cin >> source;
            std::cout << "\nEnter target: ";
            std::cin >> target;
            std::cout << "\nEnter time: ";
            std::cin >> time;
            backupper.add_backup(source, target, time);
            backupper.save_backups();
        }
        else if (choose == 2) {
            backupper.run_backup();
        }
        else if (choose == 3) {
            int counter = 1;
            std::vector<backup_info*> backups = backupper.get_backups();
            for (backup_info* backup : backups) {
                std::cout << counter << ". " << backup->source << " - " << backup->target << " - " << backup->datetime << "\n";
                counter++;
            }
        }
        else if (choose == 4) {
            break;
        }
        else {
            std::cout << "Wrong input! Please, try again\n";
            choose = 0;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    Backupper backupper;
    auto options = backupper.read_options_file();
    if (std::get<1>(options) == 1) {
        gui_controll(backupper);
    }
    show_window(std::get<0>(options));
    set_autorun();
    backupper.update();

    return 0;
}