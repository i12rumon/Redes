#include <vector>
#include "usuario.hpp"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <vector>

#define MSG_SIZE 256
#define MAX_CLIENTS 15

void commandHandler(char* string, int socket, std::vector<usuario> &usuarios);
bool pairUsers(int socket, std::vector<usuario> &usuarios);
bool removeUser(int socket, std::vector<usuario> &usuarios, char* buffer);