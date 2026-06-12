#ifndef RUTA_H
#define RUTA_H

#include <string>
using namespace std;

// Representa una arista del grafo: una ruta entre dos ciudades
// (por indice de origen/destino), con su distancia, descripcion
// y un estado activa/cortada.
class ruta {
private:
	int    id_origen;
	int    id_destino;
	float  distancia;
	string descripcion;
	bool   activa;

public:
	ruta(int id_origen, int id_destino, float distancia, string descripcion);
	~ruta();

	// Getters (no modifican el objeto -> const)
	int    get_Origen()      const;
	int    get_Destino()     const;
	float  get_Distancia()   const;
	string get_Descripcion() const;
	bool   is_Activa()       const;

	// Setters
	void set_Origen(int o);
	void set_Destino(int d);
	void set_Activa(bool b);

	// Devuelve la info de la ruta en texto, incluyendo su estado.
	string info() const;
};

#endif
