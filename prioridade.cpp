#include <iostream>
#include <vector>
#include <algorithm>
#include <unistd.h> // sleep
using namespace std;

struct Processo {
    int pid;
    string nome;
    int tempo_restante;
    int prioridade;

    Processo(int p, string n, int t, int pri) {
        pid = p;
        nome = n;
        tempo_restante = t;
        prioridade = pri;
    }
};

// Função para ordenar por prioridade (menor número = maior prioridade)
bool compararPrioridade(Processo a, Processo b) {
    return a.prioridade < b.prioridade;
}

int main() {
    vector<Processo> processos;

    // Criando processos com prioridades diferentes
    processos.push_back(Processo(1, "Editor", 5, 3));
    processos.push_back(Processo(2, "Navegador", 4, 1));
    processos.push_back(Processo(3, "Terminal", 3, 2));

    cout << "\n--- SIMULADOR POR PRIORIDADE ---\n" << endl;

    // Ordena os processos por prioridade
    sort(processos.begin(), processos.end(), compararPrioridade);

    for (auto& p : processos) {
        cout << "Executando: " << p.nome << " (PID: " << p.pid << ") - Prioridade: " << p.prioridade << endl;
        sleep(p.tempo_restante); // executa até terminar
        p.tempo_restante = 0;
        cout << "✅ Processo " << p.nome << " finalizado.\n" << endl;
        sleep(1);
    }

    cout << "✅ Todos os processos foram concluídos!" << endl;
    return 0;
}

