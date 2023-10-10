#include "barco.hpp"


barco::barco(int x,int y,orientacion z,tipo tamanio){
    pos_x=x;
    pos_y=y;
    orient=z;
    type=tamanio;

    if (orient == orientacion::HORIZONTAL) {
        end_x = x + (int) tamanio;
        end_y = y;
    } else {
        end_y = y + (int) tamanio;
        end_x = x;
    }
    
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

bool barco::esta(int x, int y) {
    if (x >= pos_x && x <= end_x && y >= pos_y && y <= end_y) {
        return true;
    }

    return false;
}

bool barco::generado_correctamente(int posX,int posY,int posendX,int posendY,tipo tamanio,orientacion a){
    if(a==0){
        if(((posX+tamanio)==posendX)){
            return true;
        }
        return false;
    }
    else{
       if((posY+tamanio)==posendY){
            return true;
        }
        return false;
    }
}