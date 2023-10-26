#include "usuario.hpp"

usuario::usuario(std::string user_,std::string pass_){
    user=user_;
    pass=pass_;
    opponent_socket_ = -1;
    ready_ = false;
}

usuario::usuario(int socket) {
    socket_ = socket;
    user = "empty";
    pass = "empty";
    opponent_socket_ = -1;
    ready_ = false;
}