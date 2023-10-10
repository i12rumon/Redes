#include <iostream>
#include <string>

class usuario{
    private:
    std::string user;
    std::string pass;
    public:
    usuario(std::string user_,std::string pass_);
    inline std::string getUser()const{return user;};
    inline std::string getPass()const{return pass;};
    inline void setUser(std::string newUser) { user = newUser; }
    inline void setPass(std::string newPass) { pass = newPass; }
    
};