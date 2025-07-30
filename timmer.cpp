#include <iostream>
#include <chrono>
#include <thread>

void tarefaPesada() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

int main() {
    auto inicio = std::chrono::high_resolution_clock::now();

    tarefaPesada();

    auto fim = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracao = fim - inicio;

    std::cout << "Tempo de execução: " << duracao.count() << " segundos\n";

    return 0;
}
