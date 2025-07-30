#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

fs::path current_path = fs::current_path();
fs::path backup_dir = current_path / "backup";

void ls() {
    for (const auto& entry : fs::directory_iterator(current_path)) {
        std::cout << entry.path().filename() << "\n";
    }
}

void cd(const std::string& dir) {
    fs::path new_path = current_path / dir;
    if (fs::exists(new_path) && fs::is_directory(new_path)) {
        current_path = fs::canonical(new_path);
        std::cout << "Diretório atual: " << current_path << "\n";
    } else {
        std::cout << "Diretório não encontrado.\n";
    }
}

void cat(const std::string& filename) {
    fs::path file_path = current_path / filename;
    if (fs::exists(file_path)) {
        std::ifstream file(file_path);
        std::string line;
        while (getline(file, line)) {
            std::cout << line << "\n";
        }
        file.close();
    } else {
        std::cout << "Arquivo não encontrado.\n";
    }
}

void backup(const std::string& filename) {
    if (!fs::exists(backup_dir)) {
        fs::create_directory(backup_dir);
    }

    fs::path source = current_path / filename;
    fs::path destination = backup_dir / filename;

    if (fs::exists(source)) {
        fs::copy_file(source, destination, fs::copy_options::overwrite_existing);
        std::cout << "Arquivo copiado para backup.\n";
    } else {
        std::cout << "Arquivo não encontrado.\n";
    }
}

void restore(const std::string& filename) {
    fs::path source = backup_dir / filename;
    fs::path destination = current_path / filename;

    if (fs::exists(source)) {
        fs::copy_file(source, destination, fs::copy_options::overwrite_existing);
        std::cout << "Arquivo restaurado.\n";
    } else {
        std::cout << "Arquivo não encontrado no backup.\n";
    }
}

int main() {
    std::string command;

    std::cout << "Mini Shell Iniciado. Digite 'sair' para encerrar.\n";

    while (true) {
        std::cout << current_path << " > ";
        std::getline(std::cin, command);

        if (command == "sair") break;
        else if (command == "ls") ls();
        else if (command.rfind("cd ", 0) == 0) cd(command.substr(3));
        else if (command.rfind("cat ", 0) == 0) cat(command.substr(4));
        else if (command.rfind("backup ", 0) == 0) backup(command.substr(7));
        else if (command.rfind("restore ", 0) == 0) restore(command.substr(8));
        else std::cout << "Comando inválido.\n";
    }

    return 0;
}
