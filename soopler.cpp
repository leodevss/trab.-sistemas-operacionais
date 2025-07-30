#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <chrono>

std::queue<std::string> filaImpressao;

void adicionarDocumento(const std::string& doc) {
    filaImpressao.push(doc);
    std::cout << "Documento adicionado: " << doc << "\n";
}

void processarImpressao() {
    while (!filaImpressao.empty()) {
        std::string doc = filaImpressao.front();
        filaImpressao.pop();
        std::cout << "Imprimindo: " << doc << "...\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Impressão concluída: " << doc << "\n";
    }
}

int main() {
    int opcao;
    std::string nomeDoc;

    do {
        std::cout << "\n[1] Adicionar documento\n[2] Iniciar impressão\n[0] Sair\n> ";
        std::cin >> opcao;
        std::cin.ignore();

        if (opcao == 1) {
            std::cout << "Nome do documento: ";
            std::getline(std::cin, nomeDoc);
            adicionarDocumento(nomeDoc);
        } else if (opcao == 2) {
            processarImpressao();
        }

    } while (opcao != 0);

    return 0;
}
