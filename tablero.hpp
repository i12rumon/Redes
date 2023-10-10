#include "barco.hpp"
#include <vector>

class Tablero {
    private:
        std::vector<barco> barcos_tablero;
        void generar_tablero();
    
    public:
        Tablero();
        void generar_matriz();
};