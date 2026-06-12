#include "ciudad.h"

ciudad::ciudad(int id_ciudad, string nombre, int x, int y) {
	this->id_ciudad = id_ciudad;
	this->nombre    = nombre;
	this->x         = x;
	this->y         = y;
}

ciudad::~ciudad() {
}

int ciudad::get_id() const {
	return id_ciudad;
}

string ciudad::get_Nombre() const {
	return nombre;
}

int ciudad::get_X() const {
	return x;
}

int ciudad::get_Y() const {
	return y;
}

void ciudad::set_Nombre(string s) {
	nombre = s;
}

string ciudad::info() const {
	return "[" + to_string(id_ciudad) + "] ciudad: " + nombre;
}
