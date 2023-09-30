#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <thread>
#include <ctime> 
#include <tuple>

#pragma warning(disable : 4996)
#define BACKUPS_FILE_PATH "backups.txt"
#define OPTIONS_FILE_NAME "./gui/backup_options.txt"

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
	void read_backups_from_file();
	void copy_directory(std::string source, std::string target);
	void copy_file(std::string source, std::string target);
	void run_backup();
	void update();
	std::tuple<int, int> read_options_file();

	std::vector<backup_info*> get_backups();
private:
	std::vector<backup_info*> _backups;
};