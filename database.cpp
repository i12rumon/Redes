#include "database.hpp"
#include <iostream>
#include <cstring>
bool checkUserValidity(std::string username, std::string password) {
    std::ifstream readFile;
    readFile.open("registered_users.txt");
    std::string userLine, passwdLine;
    while (std::getline(readFile, userLine)) {
        std::getline(readFile, passwdLine);
        if (username == userLine && password == passwdLine) {
            std::cout << "[DATABASE] Contraseña para " << username << " correcta" << std::endl;
            return true;
        }
    }
    
    return false;
}

/*
#include <iostream>
#include <iomanip>  // Para std::setw

void printHex(const std::string& str) {
    for (char c : str) {
        std::cout << std::setw(2) << std::hex << static_cast<int>(c) << ' ';
    }
    std::cout << std::endl;
}

// ...
*/

bool checkUserName(char* username) {
    std::ifstream readFile;
    readFile.open("registered_users.txt");
    std::string userLine, passwdLine;
    while (std::getline(readFile, userLine)) {
        std::getline(readFile, passwdLine);
        if (strcmp(username, userLine.c_str()) == 0) {
            std::cout << "[DATABASE] Usuario " << username << " existe" << std::endl;
            return true;
        }
    }

    std::cout << "[DATABASE] Usuario " << username << " no existe" << std::endl;
    return false;
}


bool registerUser(std::string username, std::string password) {
    if (! checkUserValidity(username, password)) {
        std::ofstream writeFile("registered_users.txt", std::ios_base::app);
        writeFile << username << std::endl << password << std::endl;
        return true;
    }

    return false;
}