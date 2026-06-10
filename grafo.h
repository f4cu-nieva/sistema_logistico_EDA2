#ifndef GRAFO_H
#define GRAFO_H

#include "ciudad.h"
#include "ruta.h"
#include <fstream>

#define INF 999999
#define MAX 15

class grafo {
private:
	ciudad* ciudades[MAX];
	ruta*   rutas[MAX * MAX]; // mas espacio para rutas con mas ciudades
	float   matriz[MAX][MAX];
	int     cantCiudades;
	int     cantRutas;

public:
	grafo();
	~grafo();

	void agregarCiudad(int id, string nombre, int x, int y);
	void eliminarCiudad(int id); // NUEVO: da de baja una ciudad y sus rutas
	void agregarRuta(int origen, int destino, float distancia, string descripcion);
	void cortarRuta(int origen, int destino);
	void habilitarRuta(int origen, int destino);
	void imprimirCiudades();
	void imprimirRutas();
	void imprimirMatriz();

	void   calcularRutaOptima(int origen, int destino);
	string calcularRutaOptimaStr(int origen, int destino);

	void guardarDatos(string nombreArchivo);
	void cargarDatos(string nombreArchivo);

	float  getMatriz(int i, int j);
	int    getCantCiudades();         // NUEVO: retorna cantidad actual
	ciudad* getCiudad(int indice);    // NUEVO: retorna puntero a ciudad[indice]
	bool   existeCiudad(int id);      // NUEVO: verifica si el id ya esta en el grafo

	void resetear();
	void registrarHistorial(string operacion);

	int getCaminoIndices(int origen, int destino, int* camino, int maxLen);

	int    getCantRutas();
	ruta*  getRuta(int indice);
};

#endif

