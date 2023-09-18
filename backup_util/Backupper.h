#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <thread>

#define BACKUPS_FILE_PATH "backups.txt"

namespace fs = std::filesystem;

struct backup_info {
	std::string source;
	std::string target;
	std::string datetime;
};

class Backupper {
public:
	Backupper();
	~Backupper();

	void add_backup(std::string source, std::string target, std::string datetime);
	void save_backups();
	void copy_directory(std::string source, std::string target);
	void copy_file(std::string source, std::string target);
	void run_backup();

	std::vector<backup_info*> get_backups();
private:
	std::vector<backup_info*> _backups;
};

