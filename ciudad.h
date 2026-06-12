#ifndef CIUDAD_H
#define CIUDAD_H

#include <string>
using namespace std;

// Representa un nodo del grafo: una ciudad con su id, nombre y
// posicion (x, y) que se usa para dibujarla en el mapa.
class ciudad {
private:
	int    id_ciudad;
	string nombre;
	int    x;
	int    y;

public:
	ciudad(int id_ciudad, string nombre, int x, int y);
	~ciudad();

	// Getters (no modifican el objeto -> const)
	int    get_id()     const;
	string get_Nombre() const;
	int    get_X()      const;
	int    get_Y()      const;

	void set_Nombre(string s);

	// Devuelve los datos de la ciudad en texto: "[id] ciudad: nombre"
	string info() const;
};

#endif
/*
.h — la "ficha técnica" — dice qué existe (atributos y funciones declaradas)
.cpp — el "manual de instrucciones" — dice cómo funciona cada cosa
*/
