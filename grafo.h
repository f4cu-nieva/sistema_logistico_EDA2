#ifndef GRAFO_H
#define GRAFO_H

#include "ciudad.h"
#include "ruta.h"
#include <fstream>

#define INF 999999
#define MAX 10

class grafo {
private:
    ciudad* ciudades[MAX];
    ruta* rutas[MAX];
    float   matriz[MAX][MAX];
    int     cantCiudades;
    int     cantRutas;

public:
    grafo();
    ~grafo();

    void agregarCiudad(int id, string nombre, int x, int y);
    void agregarRuta(int origen, int destino, float distancia, string descripcion);
    void cortarRuta(int origen, int destino);
    void habilitarRuta(int origen, int destino);
    void imprimirCiudades();
    void imprimirRutas();
    void imprimirMatriz();

    void calcularRutaOptima(int origen, int destino);

    string calcularRutaOptimaStr(int origen, int destino);

    void guardarDatos(string nombreArchivo);
	void cargarDatos(string nombreArchivo);

	float getMatriz(int i, int j) const;

    void resetear();
};

#endif
