#include <iostream>
#include <string>

class usuario{
    private:
        std::string user;
        std::string pass;
        int socket_;
        int opponent_socket_;
        bool valid_;
        bool ready_;
    public:
        usuario(std::string user_,std::string pass_);
        usuario(int socket);
        inline std::string getUser()const{return user;};
        inline bool checkUser(std::string username) { if (username == user) { return true; } else { return false; } };
        inline std::string getPass()const{return pass;};
        inline void setUser(std::string newUser) { user = newUser; }
        inline void setPass(std::string newPass) { pass = newPass; }
        inline int getSocket() { return socket_; };
        inline bool getValidity() { return valid_; };
        inline void setValidity(bool validity) { valid_ = validity; };
        inline int getOpponentSocket() { return opponent_socket_; };
        inline void setOpponent(int opponent) { opponent_socket_ = opponent; };
        inline bool readyToFight() { return ready_; };
        inline void ready(bool ready) { ready_ = ready; }; 
};