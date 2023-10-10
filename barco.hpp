#include <iostream>
#include <string>
enum orientacion{
    HORIZONTAL = 0,
    VERTICAL = 1
    };
enum tipo{
    PEQUENIO = 1,
    MEDIANO = 2,
    GRANDE = 3
    };
class barco{
    private:
    int pos_x;
    int pos_y;
    int end_x;
    int end_y;
    orientacion orient;
    tipo type;
    public:
    barco(int x,int y,orientacion z,tipo tamanio);
    barco();
    inline int getPos_x()const{return pos_x;};
    inline int getPos_y()const{return pos_y;};
    void setPos_x(int x);
    void setPos_y(int y);
    inline orientacion getOrientacion() const {return orient;};
    inline tipo getTipo() const {return type;};
    inline void setOrientacion(orientacion direccion){orient=direccion;};
    inline void setTipo(tipo tamanio){type=tamanio;};
    bool esta(int x, int y);
    
    
};