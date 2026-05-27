#include "grafo.h"
#include <iostream>
using namespace std;

grafo::grafo() {
    cantCiudades = 0;
    cantRutas    = 0;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            if (i == j) matriz[i][j] = 0;
            else        matriz[i][j] = INF;
        }
    }
    for (int i = 0; i < MAX; i++) {
        ciudades[i] = NULL;
        rutas[i]    = NULL;
    }
}

grafo::~grafo() {
    for (int i = 0; i < cantCiudades; i++) delete ciudades[i];
    for (int i = 0; i < cantRutas; i++)    delete rutas[i];
}

void grafo::agregarCiudad(int id, string nombre, int x, int y) {
    ciudades[cantCiudades] = new ciudad(id, nombre, x, y);
    cantCiudades++;
}

void grafo::agregarRuta(int origen, int destino, float distancia, string descripcion) {
    rutas[cantRutas] = new ruta(origen, destino, distancia, descripcion);
    cantRutas++;
    matriz[origen][destino] = distancia;
    matriz[destino][origen] = distancia;
}

void grafo::cortarRuta(int origen, int destino) {
    for (int i = 0; i < cantRutas; i++) {
        if (rutas[i]->get_Origen() == origen &&
            rutas[i]->get_Destino() == destino) {
            rutas[i]->set_Activa(false);
        }
    }
    matriz[origen][destino] = INF;
    matriz[destino][origen] = INF;
}

void grafo::habilitarRuta(int origen, int destino) {
    for (int i = 0; i < cantRutas; i++) {
        if (rutas[i]->get_Origen() == origen &&
            rutas[i]->get_Destino() == destino) {
            rutas[i]->set_Activa(true);
            matriz[origen][destino] = rutas[i]->get_Distancia();
            matriz[destino][origen] = rutas[i]->get_Distancia();
        }
    }
}

void grafo::imprimirCiudades() {
    cout << "=== CIUDADES ===" << endl;
    for (int i = 0; i < cantCiudades; i++) {
        ciudades[i]->info();
    }
}

void grafo::imprimirRutas() {
    cout << "=== RUTAS ===" << endl;
    for (int i = 0; i < cantRutas; i++) {
        cout << rutas[i]->info() << endl;
    }
}

void grafo::imprimirMatriz() {
    cout << "=== MATRIZ DE ADYACENCIA ===" << endl;
    for (int i = 0; i < cantCiudades; i++) {
        for (int j = 0; j < cantCiudades; j++) {
            if (matriz[i][j] == INF) cout << "INF\t";
            else                     cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
}

void grafo::calcularRutaOptima(int origen, int destino) {
    float distancias[MAX];
    bool  visitado[MAX];
    int   anterior[MAX];

    for (int i = 0; i < MAX; i++) {
        distancias[i] = INF;
        visitado[i]   = false;
        anterior[i]   = -1;
    }

    distancias[origen] = 0;

    for (int paso = 0; paso < cantCiudades; paso++) {
        int actual = -1;
        for (int i = 0; i < cantCiudades; i++) {
            if (!visitado[i]) {
                if (actual == -1 || distancias[i] < distancias[actual])
                    actual = i;
            }
        }
        if (actual == -1 || distancias[actual] == INF) break;
        visitado[actual] = true;

        for (int vecino = 0; vecino < cantCiudades; vecino++) {
            if (matriz[actual][vecino] != INF && !visitado[vecino]) {
                float nuevaDist = distancias[actual] + matriz[actual][vecino];
                if (nuevaDist < distancias[vecino]) {
                    distancias[vecino] = nuevaDist;
                    anterior[vecino]   = actual;
                }
            }
        }
    }

    cout << "De " << ciudades[origen]->get_Nombre()
         << " a " << ciudades[destino]->get_Nombre() << endl;

    if (distancias[destino] == INF) {
        cout << "No hay camino disponible." << endl;
        return;
    }

    int camino[MAX];
    int longitud = 0;
    int actual   = destino;

    while (actual != -1) {
        camino[longitud] = actual;
        longitud++;
        actual = anterior[actual];
    }

    for (int i = longitud - 1; i >= 0; i--) {
        cout << ciudades[camino[i]]->get_Nombre();
        if (i > 0) cout << " -> ";
    }
    cout << endl;
    cout << "Distancia total: " << distancias[destino] << " km" << endl;
}

string grafo::calcularRutaOptimaStr(int origen, int destino) {
    float distancias[MAX];
    bool  visitado[MAX];
    int   anterior[MAX];

    for (int i = 0; i < MAX; i++) {
        distancias[i] = INF;
        visitado[i]   = false;
        anterior[i]   = -1;
    }

    distancias[origen] = 0;

    for (int paso = 0; paso < cantCiudades; paso++) {
        int actual = -1;
        for (int i = 0; i < cantCiudades; i++) {
            if (!visitado[i]) {
                if (actual == -1 || distancias[i] < distancias[actual])
                    actual = i;
            }
        }
        if (actual == -1 || distancias[actual] == INF) break;
        visitado[actual] = true;

        for (int vecino = 0; vecino < cantCiudades; vecino++) {
            if (matriz[actual][vecino] != INF && !visitado[vecino]) {
                float nuevaDist = distancias[actual] + matriz[actual][vecino];
                if (nuevaDist < distancias[vecino]) {
                    distancias[vecino] = nuevaDist;
                    anterior[vecino]   = actual;
                }
            }
        }
    }

    string resultado = "";
    resultado += "De " + ciudades[origen]->get_Nombre() +
                 " a " + ciudades[destino]->get_Nombre() + "\n";

    if (distancias[destino] == INF) {
        resultado += "No hay camino disponible.";
        return resultado;
    }

    int camino[MAX];
    int longitud = 0;
    int actual   = destino;

    while (actual != -1) {
        camino[longitud] = actual;
        longitud++;
        actual = anterior[actual];
    }

    for (int i = longitud - 1; i >= 0; i--) {
        resultado += ciudades[camino[i]]->get_Nombre();
        if (i > 0) resultado += " -> ";
    }

    resultado += "\nDistancia total: " +
                 to_string((int)distancias[destino]) + " km";

    return resultado;
}

void grafo::guardarDatos(string nombreArchivo) {
    ofstream archivo(nombreArchivo.c_str());

    if (!archivo.is_open()) {
        return;
    }

    archivo << cantCiudades << endl;

    for (int i = 0; i < cantCiudades; i++) {
        if (ciudades[i] == NULL) continue;
        string nombreGuardar = ciudades[i]->get_Nombre();
        for (int k = 0; k < nombreGuardar.size(); k++) {
            if (nombreGuardar[k] == ' ') nombreGuardar[k] = '_';
        }
        archivo << ciudades[i]->get_id() << " "
                << nombreGuardar         << " "
                << ciudades[i]->get_X()  << " "
                << ciudades[i]->get_Y()  << endl;
    }

    archivo << cantRutas << endl;

    for (int i = 0; i < cantRutas; i++) {
        if (rutas[i] == NULL) continue;
        string descGuardar = rutas[i]->get_Descripcion();
        for (int k = 0; k < descGuardar.size(); k++) {
            if (descGuardar[k] == ' ') descGuardar[k] = '_';
        }
        archivo << rutas[i]->get_Origen()    << " "
                << rutas[i]->get_Destino()   << " "
                << rutas[i]->get_Distancia() << " "
                << descGuardar               << " "
                << rutas[i]->is_Activa()     << endl;
    }

    archivo.close();
}

void grafo::cargarDatos(string nombreArchivo) {
    ifstream archivo(nombreArchivo.c_str());
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para cargar." << endl;
        return;
    }
    int cant;
    archivo >> cant;
    for (int i = 0; i < cant; i++) {
        int    id, x, y;
        string nombre;
        archivo >> id >> nombre >> x >> y;
        for (int k = 0; k < nombre.size(); k++) {
            if (nombre[k] == '_') nombre[k] = ' ';
        }
        agregarCiudad(id, nombre, x, y);
    }
    archivo >> cant;
    for (int i = 0; i < cant; i++) {
        int    origen, destino;
        float  distancia;
        string descripcion;
        bool   activa;
        archivo >> origen >> destino >> distancia >> descripcion >> activa;
        for (int k = 0; k < descripcion.size(); k++) {
            if (descripcion[k] == '_') descripcion[k] = ' ';
        }
        agregarRuta(origen, destino, distancia, descripcion);
        if (!activa) cortarRuta(origen, destino);
    }
    archivo.close();
	cout << "Datos cargados correctamente." << endl;
}

float grafo::getMatriz(int i, int j) const {
	return matriz[i][j];
}

void grafo::resetear() {
    for (int i = 0; i < cantCiudades; i++) delete ciudades[i];
    for (int i = 0; i < cantRutas; i++)    delete rutas[i];
    cantCiudades = 0;
    cantRutas    = 0;
    for (int i = 0; i < MAX; i++) {
        ciudades[i] = NULL;
        rutas[i]    = NULL;
        for (int j = 0; j < MAX; j++) {
            if (i == j) matriz[i][j] = 0;
            else        matriz[i][j] = INF;
        }
    }
}

