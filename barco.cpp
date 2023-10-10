#include "barco.hpp"

barco::barco(int x,int y,orientacion z,tipo tamanio){
    pos_x=x;
    pos_y=y;
    orient=z;
    type=tamanio;
}
void barco::setPos_x(int x) {
    if(x<10){
     pos_x=x;
    } 
}

void barco::setPos_y(int y) { 
    if(y<10){
    pos_y=y;
    }
}