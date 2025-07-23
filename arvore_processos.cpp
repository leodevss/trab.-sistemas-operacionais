#include <iostream>
#include <vector>
using namespace std;

struct Processo {
    int pid;
    int ppid; // processo pai
    string nome;
};

// Função recursiva para imprimir árvore
void mostrar_arvore(const vector<Processo>& processos, int ppid, int nivel) {
    for (const auto& p : processos) {
        if (p.ppid == ppid) {
            for (int i = 0; i < nivel; ++i) cout << "  ";
            cout << "└── PID " << p.pid << ": " << p.nome << endl;
            mostrar_arvore(processos, p.pid, nivel + 1);
        }
    }
}

int main() {
    vector<Processo> processos = {
        {1, 0, "Init"},
        {2, 1, "Terminal"},
        {3, 1, "Editor"},
        {4, 2, "Shell"},
        {5, 2, "Python"},
        {6, 4, "Script.py"},
        {7, 3, "AutoSave"}
    };

    cout << "\n--- ÁRVORE DE PROCESSOS ---\n" << endl;
    mostrar_arvore(processos, 0, 0);

    return 0;
}

