#ifndef GRAFO_H
#define GRAFO_H

#include "ciudad.h"
#include "ruta.h"
#include <fstream>

#define INF 999999
#define MAX 15

// Grafo no dirigido y ponderado que modela la red de rutas de Chubut.
// Las ciudades son los nodos y las rutas las aristas. La matriz de
// adyacencia guarda la distancia entre indices de ciudades (INF = sin
// conexion directa). Los caminos optimos se calculan con Dijkstra.
class grafo {
private:
	ciudad* ciudades[MAX];
	ruta*   rutas[MAX * MAX]; // mas espacio para rutas con mas ciudades
	float   matriz[MAX][MAX];
	int     cantCiudades;
	int     cantRutas;

	// --- Helpers internos de pathfinding (Dijkstra) ---
	// Calcula la distancia minima desde 'origen' a todas las ciudades.
	// Deja en 'distancias' el costo y en 'anterior' el nodo previo de
	// cada uno (para poder reconstruir el camino).
	void dijkstra(int origen, float distancias[], int anterior[]) const;

	// A partir del vector 'anterior' arma el camino desde su raiz hasta
	// 'destino', en orden, dentro de 'camino'. Devuelve su longitud.
	int  reconstruirCamino(int destino, const int anterior[],
						    int camino[], int maxLen) const;

public:
	grafo();
	~grafo();

	// --- Alta / baja de ciudades y rutas ---
	void agregarCiudad(int id, string nombre, int x, int y);
	void eliminarCiudad(int id); // da de baja una ciudad y sus rutas
	void agregarRuta(int origen, int destino, float distancia, string descripcion);
	void cortarRuta(int origen, int destino);
	void habilitarRuta(int origen, int destino);

	// --- Salida por consola (depuracion) ---
	void imprimirCiudades() const;
	void imprimirRutas() const;
	void imprimirMatriz() const;

	// --- Camino optimo ---
	void   calcularRutaOptima(int origen, int destino) const;     // imprime por consola
	string calcularRutaOptimaStr(int origen, int destino) const;  // devuelve texto (GUI)
	int    getCaminoIndices(int origen, int destino, int* camino, int maxLen) const;

	// --- Persistencia ---
	void guardarDatos(string nombreArchivo);
	void cargarDatos(string nombreArchivo);

	// --- Consultas ---
	float   getMatriz(int i, int j) const;
	int     getCantCiudades() const;
	int     getCantRutas() const;
	ciudad* getCiudad(int indice) const;
	ruta*   getRuta(int indice) const;
	bool    existeCiudad(int id) const;

	void resetear();
};

#endif
