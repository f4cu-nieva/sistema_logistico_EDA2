#include "ruta.h"

ruta::ruta(int id_origen, int id_destino, float distancia, string descripcion) {
	this->id_origen   = id_origen;
	this->id_destino  = id_destino;
	this->distancia   = distancia;
	this->descripcion = descripcion;
	this->activa      = true; // toda ruta arranca activa
}

ruta::~ruta() {
}

int ruta::get_Origen() const {
	return id_origen;
}

int ruta::get_Destino() const {
	return id_destino;
}

float ruta::get_Distancia() const {
	return distancia;
}

string ruta::get_Descripcion() const {
	return descripcion;
}

bool ruta::is_Activa() const {
	return activa;
}

void ruta::set_Origen(int o) {
	id_origen = o;
}

void ruta::set_Destino(int d) {
	id_destino = d;
}

void ruta::set_Activa(bool b) {
	activa = b;
}

string ruta::info() const {
	string estado = activa ? "ACTIVA" : "CORTADA";
	return "[" + to_string(id_origen) + " -> " + to_string(id_destino) + "] " +
		   descripcion + " | " + to_string((int)distancia) + " km | " + estado;
}
