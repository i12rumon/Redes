#include <cstring>
#include <vector>
#include <cstdio>
#include "database.hpp"
#include "funciones_srv.hpp"

void commandHandler(char* string, int socket, std::vector<usuario> &usuarios) {
    char* token = strtok(string, " "); // Ya tenemos el primer token, ahora con este, tenemos que averiguar que nos ha llegado
    char* usuario_str = NULL;
    char* password_str = NULL;

    if (usuarios.empty()) {
        usuarios.push_back(usuario(socket));
    }

    usuario* user = NULL;

    for (auto it = usuarios.begin(); it != usuarios.end(); it++) {
        if (it->getSocket() == socket) {
            user = std::__to_address(it);
            break;
        } else {
            usuarios.push_back(usuario(socket));
            user = std::__to_address(usuarios.end());
            std::cout << "[FUNCIONES_SRV] Usuario nuevo añadido." << std::endl;
        }
    }

    if (strcmp(token, "USUARIO") == 0) {
        // Ahora podemos decir que nos está pidiendo el usuario
        usuario_str = strtok(NULL, " "); // Obtener el usuario

        if (checkUserName(usuario_str)) {
            user->setUser(usuario_str);
            std::cout << "[FUNCIONES_SRV] Usuario " << user->getUser() << " nombre de usuario valido." << std::endl;
            strcpy(string, "+Ok. Usuario correcto");
        } else {
            std::cout << "[FUNCIONES_SRV] Usuario " << user->getUser() << " nombre de usuario inválido." << std::endl;
            strcpy(string, "-Err. Usuario incorrecto");
        }

        return;

    } else if (strcmp(token, "PASSWORD") == 0) {
        // Ahora estamos sacando la contraseña
        password_str = strtok(NULL, " ");
        user->setPass(password_str);

        if (user->getUser() != "empty" && user->getPass() != "empty") {
            user->setValidity(checkUserValidity(user->getUser(), user->getPass()));
            if (user->getValidity()) {
                std::cout << "[FUNCIONES_SRV] Usuario " << user->getUser() << " valido." << std::endl;
                strcpy(string, "+Ok. Usuario validado");
            } else {
                std::cout << "[FUNCIONES_SRV] Usuario " << user->getUser() << " invalido." << std::endl;
                strcpy(string, "-Err. Error en la validación");
            }
        }

    } else if (strcmp(token, "REGISTER") == 0) {
        // Ahora hemos recibido el comando de registrar, tendriamos que tener una clase para comprobar
        // los datos de registro del usuario
        char* opt = strtok(NULL, " ");
        while (opt != NULL) {
            if (strcmp(opt, "-u") == 0) {
                usuario_str = strtok(NULL, " ");
            } else if (strcmp(opt, "-p") == 0) {
                password_str = strtok(NULL, " ");
            }
            opt = strtok(NULL, " ");
        }

        printf("%s %s", usuario_str, password_str);
        if (registerUser(usuario_str, password_str)) {
            // Registramos al usuario y comprobamos si se ha registrado correctamente
            user->setPass(password_str);
            user->setUser(usuario_str);
            user->setValidity(true);
            std::cout << "[FUNCIONES_SRV] Usuario " << user->getUser() << " registrado." << std::endl;
        }

    } else if (strcmp(token, "INICIAR-PARTIDA") == 0) {
        // Aqui van las cosas de iniciar la partida y eso, hay que emparejar al jugador con
        // alguien que no este emparejado
        if (pairUsers(socket, usuarios)) {
            strcpy(string, "+Ok. Empieza la partida");
            send(user->getOpponentSocket(), string, sizeof(string), 0); // Le enviamos al oponente que vamos a empezar la partida
        } else {
            // Si no se han encontrado usuarios listos para hacer partida, pues simplemente esperamos a jugadores hasta
            // que haya uno listo que encuentre a este jugador y empareje la partida
            strcpy(string, "+Ok. Esperando jugadores");
        }

    } else if (strcmp(token, "DISPARO") == 0) {
        // Piu piu
        char* letra = strtok(NULL, ",");
        char* numero = strtok(NULL, ",");
        printf("%s %s", letra, numero);
    }
}

bool pairUsers(int socket, std::vector<usuario> &usuarios) {
    /*
    Esta funcion supuestamente sirve para emparejar a dos usuarios. Primero lo que hacemos es usando
    el socket de la persona que se ha iniciado la partida, buscamos a otro usuario conectado que:ç
    - No tenga un oponente asignado
    - Haya sido verificado con el inicio de sesion
    - Y que su socket no sea el socket de la persona que ha iniciado la conexion
    En el caso de que se cumplan las 3 cosas, se asigna el socket de la persona que ha invocado el comando
    INICIAR-PARTIDA, se establece el opponent socket usando setOpponent al primer usuario en el vector
    que cumpla las 3 condiciones. Luego si se ha encontrado a una persona que satisfaga las 3 opciones,
    el usuario se le colocará el socket del oponente como su socket de oponente.

    Esto tiene unas ventajas. En el caso de que un usuario lance un comando de ataque, el servidor lo recibira
    buscara el usuario que ha iniciado ese comando por medio de su socket, y dentro de ese mismo usuario
    encontrará el oponente y asi se puede entablar una conexion mas o menos diecta sin tener que aumentar
    la complejidad del código para obtener el socket del oponente.

    Devuelve true si se ha realizado el emparejamiento, false en el caso contrario.
    */
    
    int opponentSocket = 0;
    bool opponentFound = false;
    for (usuario oponente : usuarios) {
        opponentSocket = oponente.getOpponentSocket();
        if (opponentSocket == -1 && oponente.getValidity() == true && oponente.getSocket() != socket) {
            oponente.setOpponent(socket);
            break;
        }
    }

    if (opponentFound) {
        for (usuario user : usuarios) {
            if (user.getSocket() == socket) {
                user.setOpponent(opponentSocket);
                return true;
            }
        }
    }

    return false;
}