#include <iostream>
#include "tablero.hpp"
#include "funciones_srv.hpp"

int main() {
    //std::vector<usuario> usuariosConectados;
    std::vector<usuario> usuarios = std::vector<usuario>();

    int new_sd;
	sockaddr_in from;
	socklen_t from_len;
	char buffer[MSG_SIZE];
    fd_set readfds, auxfds;

    // Abrimos el socket
    int sd;
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1) {
        perror("Error abriendo el socket.\n");
        exit(-1);
    }

    // Esto es una cosa que nos permite que otros sockets puedan reutilizar cualquier puerto al que nos enlacemos
    int on = 1, ret;
    ret = setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    struct sockaddr_in sockname;
    sockname.sin_family = AF_INET;
    sockname.sin_port = htons(2000);
    sockname.sin_addr.s_addr = INADDR_ANY;

    // Vamos a hacer binding del socket ahora.
    if (bind(sd, (struct sockaddr *) &sockname, sizeof(sockname)) == -1) {
        perror("Error binding.\n");
        exit(-1);
    }

    if (listen(sd, 1) == -1) {
        perror("Error listening en el socket.\n");
        exit(-1);
    }

    printf("Esperando conexiones, todo ok.\n");

    // Inicializamos los consjusntos fd_set
    FD_ZERO(&readfds);
    FD_ZERO(&auxfds);
    FD_SET(sd, &readfds);
    FD_SET(0, &readfds);

    while(1) {
        // Aqui vamos a aceptar peticiones
        auxfds = readfds;
        int salida;
        salida = select(FD_SETSIZE, &auxfds, NULL, NULL, NULL);
        // Signfica que ha llegado algo
        if (salida > 0) {
            // Ahora toca buscar de que socket ha salido.
            for (int i = 0; i < FD_SETSIZE; i++) {
                if (FD_ISSET(i, &auxfds)){
                    if (i == sd) {
                        if ((new_sd = accept(sd, (struct sockaddr *) &from, &from_len)) < 0) {
                            // Comprobamos si hemos podido aceptar la peticionm
                            perror("Error aceptando peticiones.\n");
                        } else {
                            // Se acaba de conectar un usuario, sorpresaa
                            if (usuarios.size() < MAX_CLIENTS) {
                                usuarios.push_back(usuario(new_sd));
                                FD_SET(new_sd, &readfds);
                                bzero(buffer, sizeof(buffer));
                                sprintf(buffer, "+0k. Usuario conectado");
                                printf("[MAIN] Nuevo cliente conectado.\n");
                                std::cout << "[MAIN] Hay " << usuarios.size() << " usuarios conectados ahora mismo." << std::endl;
                                send(new_sd, buffer, sizeof(buffer), 0);
                            } else {
                                bzero(buffer, sizeof(buffer));
                                sprintf(buffer, "[MAIN] Hay demasiados clientes.\n");
                                send(new_sd, buffer, sizeof(buffer), 0);
                                close(new_sd); // Mandar al cliente a tomar por qlo
                            }
                        }
                    } else if (i == 0) {
                        // Esto seria un mensaje de consola aqui se podría interpretar como quisieramos
                    } else {
                        // Ahora esto es de un socket externo.
                        bzero(buffer, sizeof(buffer));
                        int recibido = recv(i, buffer, sizeof(buffer), 0);
                        
                        // Limpiamos la cadena, sino da errores
                        if (buffer[recibido - 1] == '\n') {
                            buffer[recibido - 1] = '\0';
                        }

                        if (recibido > 0) {
                            // Hemos recibido un mensaje del socket i-esimo, vamos a ver que es lo que ha dicho
                            printf("[COMMAND] %i -> %s\n", i, buffer);
                            commandHandler(buffer, i, usuarios);
                            send(i, buffer, sizeof(buffer), 0);
                        }
                        
                        if (recibido == 0) {
                            // Aqui se esta enviando un control - c, es decir, echar al cliente del server
                            removeUser(i, usuarios, buffer);
                            std::cout << "[MAIN] Usuario borrado correctamente." << std::endl;
                            std::cout << "[MAIN] Ahora mismo hay " << usuarios.size() << " usuarios conectados." << std::endl;
                            close(i);
                            FD_CLR(i, &readfds);
                        }
                    }
                }
            }
        }
    }
    
    close(sd);
    return 0;
}

