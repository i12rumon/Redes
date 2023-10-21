#include "tablero.hpp"
#include <cstdlib>
#include <ctime>

Tablero::Tablero() {
    this->generar_tablero();
}

void Tablero::generar_tablero() {
    srand(time(NULL));
    tipo tipos_barco[5] = {tipo(1), tipo(1), tipo(2), tipo(2), tipo(3)};

    for (int i = 0; i < 5; i++) {
        orientacion side = orientacion(rand() % 2);
        int pos_x = rand() % 10;
        int pos_y = rand() % 10;
        barco barco_nuevo = barco(pos_x, pos_y, side, tipos_barco[i]);
        barcos_tablero.push_back(barco_nuevo);
    }
}

void Tablero::generar_matriz() {
    char matriz[10][10];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            matriz[i][j] = '.';
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 5; k++) {
                if (barcos_tablero[k].esta(i, j)) {
                    matriz[i][j] = '#';
                }
            }
            std::cout << matriz[i][j];
        }
        std::cout << std::endl;
    }
}