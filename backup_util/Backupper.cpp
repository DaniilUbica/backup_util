#include "Backupper.h"

inline std::vector<std::string> split(std::string const& str, const char delim) {
    std::vector<std::string> out;
    std::stringstream ss(str);

    std::string s;
    while (std::getline(ss, s, delim)) {
        out.push_back(s);
    }
    return out;
}

Backupper::Backupper() {
    std::string source;
    std::string target;
    std::string datetime;

    std::fstream file(BACKUPS_FILE_PATH);
    while (!file.eof()) {
        std::string info;
        std::getline(file, info, '\n');
        std::vector<std::string> data = split(info, '=');
        if (data.size() > 2) {
            source = data[0];
            target = data[1];
            datetime = data[2];
        }
        add_backup(source, target, datetime);
    }
}

Backupper::~Backupper() {
	for (backup_info* backup : _backups) {
		delete backup;
	}
}

void Backupper::add_backup(std::string source, std::string target, std::string datetime) {
	_backups.push_back(new backup_info{ source, target, datetime });
}

void Backupper::save_backups() {
	std::fstream file(BACKUPS_FILE_PATH);
	for (const auto backup : _backups) {
		file << backup->source << "=" << backup->target << "=" << backup->datetime << "\n";
	}
	file.close();
}

void Backupper::copy_directory(std::string source, std::string target) {
    try {
        std::vector<std::future<void>> futures;

        if (!fs::exists(source) || !fs::is_directory(source)) {
            std::cout << "Can't find source directory or it is not a directory!\n";
            return;
        }
        if (!fs::exists(target)) {
            if (!fs::create_directory(target)) {
                std::cout << "Can't create target folder!\n";
                return;
            }
            else {
                std::cout << "Created new directory: " << target << "\n";
            }
        }
        for (const fs::directory_entry& entry : fs::directory_iterator(source)) {
            const fs::path path = entry.path();
            const fs::path filename = path.filename();
            const fs::path target_path = target / filename;

            if (fs::is_directory(path)) {
                copy_directory(path.string(), target_path.string());
            }
            else {
                fs::copy_file(path, target_path, fs::copy_options::overwrite_existing);
            }
        }
        std::cout << "Directory has been copied succesfully!\n";
    }
    catch (const fs::filesystem_error& e) {
        std::cout << "Error while copying directory: " << e.what() << "\n";
    }
}

void Backupper::copy_file(std::string source, std::string target) {
    try {
        const fs::path path = source;
        fs::copy_file(source, target / path.filename(), fs::copy_options::overwrite_existing);
    }
    catch (const fs::filesystem_error& e) {
        std::cout << "Error while copying file: " << e.what() << "\n";
    }
}

void Backupper::run_backup() {
    std::vector<std::thread> threads;
    for (int i = 0; i < _backups.size(); i++) {
        threads.emplace_back(&Backupper::copy_directory, this, _backups[i]->source, _backups[i]->target);
    }
    for (int i = 0; i < _backups.size(); i++) {
        threads[i].join();
    }
}

std::vector<backup_info*> Backupper::get_backups() {
    return _backups;
}
