#include <cstdio>
#include <vector>
#include "funciones_srv.hpp"

int main() {
    std::vector<usuario> usuarios;  
    char usuario_str[] = "USUARIO nacabaro";
    char password_str[] = "PASSWORD 123456789";
    char delim[] = " ";
    commandHandler(usuario_str, 2, usuarios);
    commandHandler(password_str, 2, usuarios);
}