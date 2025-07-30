//so funciona no windowns e faz parte do spooler

#include <iostream>
#include <fstream>
#include <conio.h>  // Só funciona no Windows. No Linux seria via ncurses ou leitura direta.

int main() {
    std::ofstream arquivo("teclas_log.txt", std::ios::app);
    char tecla;

    std::cout << "Pressione ESC para sair.\n";

    while (true) {
        tecla = _getch();  // Captura a tecla sem precisar dar ENTER

        if (tecla == 27) break; // Tecla ESC
        arquivo << tecla;
        std::cout << tecla;
    }

    arquivo.close();
    return 0;
}
