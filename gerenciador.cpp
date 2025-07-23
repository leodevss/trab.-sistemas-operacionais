#include <iostream>
#include <dirent.h>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <unistd.h> 

using namespace std;

void listar_processos() {
    DIR* dir = opendir("/proc");
    struct dirent* entry;

    if (dir == nullptr) {
        cerr << "Não foi possível abrir /proc" << endl;
        return;
    }

    cout << "PID\tNome do Processo" << endl;

    while ((entry = readdir(dir)) != nullptr) {
        if (isdigit(entry->d_name[0])) {
            string pid = entry->d_name;
            ifstream status("/proc/" + pid + "/status");
            string linha;
            string nome;

            while (getline(status, linha)) {
                if (linha.find("Name:") == 0) {
                    nome = linha.substr(6);
                    break;
                }
            }

            cout << pid << "\t" << nome << endl;
        }
    }

    closedir(dir);
}

float calcular_uso_cpu() {
    ifstream file("/proc/stat");
    string linha;
    getline(file, linha);
    file.close();

    unsigned long long int user, nice, system, idle, iowait, irq, softirq;
    istringstream ss(linha);
    string cpu_label;
    ss >> cpu_label >> user >> nice >> system >> idle >> iowait >> irq >> softirq;

    unsigned long long int idle_time = idle + iowait;
    unsigned long long int non_idle = user + nice + system + irq + softirq;
    unsigned long long int total = idle_time + non_idle;

    usleep(100000); // Espera 100 milissegundos

    file.open("/proc/stat");
    getline(file, linha);
    file.close();

    istringstream ss2(linha);
    ss2 >> cpu_label >> user >> nice >> system >> idle >> iowait >> irq >> softirq;

    unsigned long long int idle2 = idle + iowait;
    unsigned long long int non_idle2 = user + nice + system + irq + softirq;
    unsigned long long int total2 = idle2 + non_idle2;

    float total_diff = total2 - total;
    float idle_diff = idle2 - idle_time;

    return 100.0 * (1.0 - (idle_diff / total_diff));
}

void mostrar_uso_memoria() {
    ifstream file("/proc/meminfo");
    string linha;
    unsigned long mem_total = 0, mem_available = 0;

    while (getline(file, linha)) {
        if (linha.find("MemTotal:") == 0) {
            istringstream ss(linha);
            string label;
            ss >> label >> mem_total;
        }
        if (linha.find("MemAvailable:") == 0) {
            istringstream ss(linha);
            string label;
            ss >> label >> mem_available;
        }
    }
    file.close();

    unsigned long mem_usada = mem_total - mem_available;
    float uso_percent = (mem_usada * 100.0) / mem_total;

    cout << "Uso de Memória: " << mem_usada / 1024 << " MB / "
         << mem_total / 1024 << " MB (" << uso_percent << "%)" << endl;
}

int main() {
    listar_processos();

    cout << endl;
    float uso_cpu = calcular_uso_cpu();
    cout << "Uso da CPU: " << uso_cpu << "%" << endl;

    mostrar_uso_memoria();

    return 0;
}

