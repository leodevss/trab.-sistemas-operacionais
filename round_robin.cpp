#include <iostream>
#include <queue>
#include <unistd.h> // Para usar sleep no Linux
using namespace std;

// Estrutura que representa um processo
struct Processo {
    int pid;
    string nome;
    int tempo_restante;

    Processo(int p, string n, int t) {
        pid = p;
        nome = n;
        tempo_restante = t;
    }
};

int main() {
    queue<Processo> fila;

    // Criando processos simulados
    fila.push(Processo(1, "Editor de Texto", 5));
    fila.push(Processo(2, "Navegador Web", 7));
    fila.push(Processo(3, "Terminal", 4));

    int quantum = 2; // Tempo máximo que cada processo pode executar por vez

    cout << "\n--- SIMULADOR ROUND ROBIN ---\n" << endl;

    while (!fila.empty()) {
        Processo atual = fila.front();
        fila.pop();

        cout << "Executando: " << atual.nome << " (PID: " << atual.pid << ")" << endl;

        // Simula execução por quantum
        int tempo_exec = min(quantum, atual.tempo_restante);
        sleep(tempo_exec); // pausa para simular execução
        atual.tempo_restante -= tempo_exec;

        cout << "Tempo restante: " << atual.tempo_restante << " segundos\n" << endl;

        if (atual.tempo_restante > 0) {
            fila.push(atual); // volta para a fila se ainda tem tempo
        } else {
            cout << "✅ Processo " << atual.nome << " finalizado.\n" << endl;
        }

        sleep(1); // pequena pausa entre ciclos
    }

    cout << "✅ Todos os processos foram concluídos com sucesso!\n" << endl;

    return 0;
}

