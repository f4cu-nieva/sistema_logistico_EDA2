#include "ciudad.h" //archivo.cpp

 #include <iostream>

 using namespace std;

ciudad::ciudad(int id_ciudad, string nombre, int x, int y) { //funcion del constructor
    this->id_ciudad = id_ciudad;
    this->nombre    = nombre;
    this->x         = x;
    this->y         = y;
}//se ingresan los datos de la ciudad


ciudad::~ciudad() {
}

int ciudad::get_id(){
	return id_ciudad;
}

string ciudad::get_Nombre(){
 	return nombre;
 }

int ciudad::get_X()
{
	return x;
}

int ciudad::get_Y(){
    return y;
}

void   ciudad::set_Nombre(string s) {
nombre = s;
}

void ciudad::info(){

    cout<<"[ "<<id_ciudad << "] " << " ciudad: "<< nombre << endl;

    //return "[" + to_string(id_ciudad) + "] " + nombre;
}

