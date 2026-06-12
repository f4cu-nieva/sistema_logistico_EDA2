#include "grafo.h"
#include <iostream>
#include <cstdio>   // sscanf
using namespace std;

//  Constructor / destructor
grafo::grafo() {
	cantCiudades = 0;
	cantRutas    = 0;

	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			matriz[i][j] = (i == j) ? 0 : INF;
		}
	}
	for (int i = 0; i < MAX; i++) {
		ciudades[i] = nullptr;
	}
	for (int i = 0; i < MAX * MAX; i++) {
		rutas[i] = nullptr;
	}
}

grafo::~grafo() {
	for (int i = 0; i < cantCiudades; i++) {
		delete ciudades[i];
	}
	for (int i = 0; i < cantRutas; i++) {
		delete rutas[i];
	}
}

//  Alta / baja de ciudades y rutas
void grafo::agregarCiudad(int id, string nombre, int x, int y) {
	if (cantCiudades >= MAX) {
		cout << "Error: no se pueden agregar mas ciudades." << endl;
		return;
	}
	ciudades[cantCiudades] = new ciudad(id, nombre, x, y);
	cantCiudades++;
}

void grafo::eliminarCiudad(int id) {
	// 1. Buscar el indice de la ciudad
	int indice = -1;
	for (int i = 0; i < cantCiudades; i++) {
		if (ciudades[i] != nullptr && ciudades[i]->get_id() == id) {
			indice = i;
			break;
		}
	}
	if (indice == -1) {
		cout << "Error: no se encontro la ciudad con id " << id << endl;
		return;
	}

	// 2. Eliminar todas las rutas que tocan a esa ciudad y compactar el array
	int cantNueva = 0;
	for (int i = 0; i < cantRutas; i++) {
		bool tocaCiudad = rutas[i]->get_Origen()  == indice ||
						  rutas[i]->get_Destino() == indice;
		if (tocaCiudad) {
			delete rutas[i];
		} else {
			rutas[cantNueva] = rutas[i];
			cantNueva++;
		}
	}
	for (int i = cantNueva; i < cantRutas; i++) {
		rutas[i] = nullptr;
	}
	cantRutas = cantNueva;

	// 3. Eliminar la ciudad y compactar su array
	delete ciudades[indice];
	for (int i = indice; i < cantCiudades - 1; i++) {
		ciudades[i] = ciudades[i + 1];
	}
	ciudades[cantCiudades - 1] = nullptr;
	cantCiudades--;

	// 4. Reindexar las rutas: los indices mayores al borrado bajan 1
	for (int i = 0; i < cantRutas; i++) {
		int o = rutas[i]->get_Origen();
		int d = rutas[i]->get_Destino();
		if (o > indice) rutas[i]->set_Origen(o - 1);
		if (d > indice) rutas[i]->set_Destino(d - 1);
	}

	// 5. Reconstruir la matriz desde cero con los indices ya corregidos
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			matriz[i][j] = (i == j) ? 0 : INF;
		}
	}
	for (int i = 0; i < cantRutas; i++) {
		if (rutas[i]->is_Activa()) {
			int   o    = rutas[i]->get_Origen();
			int   d    = rutas[i]->get_Destino();
			float dist = rutas[i]->get_Distancia();
			matriz[o][d] = dist;
			matriz[d][o] = dist;
		}
	}
}

void grafo::agregarRuta(int origen, int destino, float distancia, string descripcion) {
	if (cantRutas >= MAX * MAX) {
		cout << "Error: no se pueden agregar mas rutas." << endl;
		return;
	}
	rutas[cantRutas] = new ruta(origen, destino, distancia, descripcion);
	cantRutas++;
	matriz[origen][destino] = distancia;
	matriz[destino][origen] = distancia;
}

void grafo::cortarRuta(int origen, int destino) {
	for (int i = 0; i < cantRutas; i++) {
		if (rutas[i]->get_Origen() == origen && rutas[i]->get_Destino() == destino) {
			rutas[i]->set_Activa(false);
		}
	}
	matriz[origen][destino] = INF;
	matriz[destino][origen] = INF;
}

void grafo::habilitarRuta(int origen, int destino) {
	bool encontrado = false;
	for (int i = 0; i < cantRutas; i++) {
		if (rutas[i]->get_Origen() == origen && rutas[i]->get_Destino() == destino) {
			rutas[i]->set_Activa(true);
			matriz[origen][destino] = rutas[i]->get_Distancia();
			matriz[destino][origen] = rutas[i]->get_Distancia();
			encontrado = true;
		}
	}

	if (encontrado) {
		cout << "Ruta habilitada correctamente." << endl;
	} else {
		cout << "Error: no se encontro la ruta indicada." << endl;
	}
}

// ===============================================================
//  Salida por consola (depuracion)
// ===============================================================
void grafo::imprimirCiudades() const {
	cout << "=== CIUDADES ===" << endl;
	for (int i = 0; i < cantCiudades; i++) {
		cout << ciudades[i]->info() << endl;
	}
}

void grafo::imprimirRutas() const {
	cout << "=== RUTAS ===" << endl;
	for (int i = 0; i < cantRutas; i++) {
		cout << rutas[i]->info() << endl;
	}
}

void grafo::imprimirMatriz() const {
	cout << "=== MATRIZ DE ADYACENCIA ===" << endl;
	for (int i = 0; i < cantCiudades; i++) {
		for (int j = 0; j < cantCiudades; j++) {
			if (matriz[i][j] == INF) {
				cout << "INF\t";
			} else {
				cout << matriz[i][j] << "\t";
			}
		}
		cout << endl;
	}
}

//  Dijkstra
void grafo::dijkstra(int origen, float distancias[], int anterior[]) const {
	bool visitado[MAX];
	for (int i = 0; i < MAX; i++) {
		distancias[i] = INF;
		anterior[i]   = -1;
		visitado[i]   = false;
	}
	distancias[origen] = 0;

	for (int paso = 0; paso < cantCiudades; paso++) {
		// Elegir el nodo no visitado mas cercano
		int actual = -1;
		for (int i = 0; i < cantCiudades; i++) {
			if (!visitado[i] && (actual == -1 || distancias[i] < distancias[actual])) {
				actual = i;
			}
		}
		if (actual == -1 || distancias[actual] == INF) break;
		visitado[actual] = true;

		// Relajar las aristas hacia sus vecinos
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
}

int grafo::reconstruirCamino(int destino, const int anterior[],
							  int camino[], int maxLen) const {
	int temp[MAX];
	int longitud = 0;
	int actual   = destino;

	// Recorrer hacia atras desde el destino usando 'anterior'
	while (actual != -1 && longitud < MAX) {
		temp[longitud] = actual;
		longitud++;
		actual = anterior[actual];
	}

	// Invertir para que quede en orden origen -> destino
	for (int i = 0; i < longitud && i < maxLen; i++) {
		camino[i] = temp[longitud - 1 - i];
	}
	return longitud;
}

void grafo::calcularRutaOptima(int origen, int destino) const {
	float distancias[MAX];
	int   anterior[MAX];
	dijkstra(origen, distancias, anterior);

	cout << "De " << ciudades[origen]->get_Nombre()
		 << " a " << ciudades[destino]->get_Nombre() << endl;

	if (distancias[destino] == INF) {
		cout << "No hay camino disponible." << endl;
		return;
	}

	int camino[MAX];
	int longitud = reconstruirCamino(destino, anterior, camino, MAX);
	for (int i = 0; i < longitud; i++) {
		cout << ciudades[camino[i]]->get_Nombre();
		if (i < longitud - 1) cout << " -> ";
	}
	cout << endl;
	cout << "Distancia total: " << distancias[destino] << " km" << endl;
}

string grafo::calcularRutaOptimaStr(int origen, int destino) const {
	float distancias[MAX];
	int   anterior[MAX];
	dijkstra(origen, distancias, anterior);

	string resultado = "De " + ciudades[origen]->get_Nombre() +
					   " a " + ciudades[destino]->get_Nombre() + "\n";

	if (distancias[destino] == INF) {
		return resultado + "No hay camino disponible.";
	}

	int camino[MAX];
	int longitud = reconstruirCamino(destino, anterior, camino, MAX);
	for (int i = 0; i < longitud; i++) {
		resultado += ciudades[camino[i]]->get_Nombre();
		if (i < longitud - 1) resultado += " -> ";
	}
	resultado += "\nDistancia total: " + to_string((int)distancias[destino]) + " km";
	return resultado;
}

int grafo::getCaminoIndices(int origen, int destino, int* camino, int maxLen) const {
	float distancias[MAX];
	int   anterior[MAX];
	dijkstra(origen, distancias, anterior);

	if (distancias[destino] == INF) return 0;
	return reconstruirCamino(destino, anterior, camino, maxLen);
}

//  Persistencia en archivo
void grafo::guardarDatos(string nombreArchivo) {
	ofstream archivo(nombreArchivo.c_str());
	if (!archivo.is_open()) return;

	// --- Ciudades ---
	archivo << "=== CIUDADES (" << cantCiudades << ") ===" << endl;
	for (int i = 0; i < cantCiudades; i++) {
		if (ciudades[i] == nullptr) continue;
		// Reemplazamos espacios por '_' para no romper el parseo con sscanf
		string nombreGuardar = ciudades[i]->get_Nombre();
		for (int k = 0; k < (int)nombreGuardar.size(); k++) {
			if (nombreGuardar[k] == ' ') nombreGuardar[k] = '_';
		}
		archivo << "ID:"     << ciudades[i]->get_id() << " "
				<< "Nombre:" << nombreGuardar          << " "
				<< "X:"      << ciudades[i]->get_X()   << " "
				<< "Y:"      << ciudades[i]->get_Y()   << endl;
	}

	// --- Rutas ---
	archivo << "=== RUTAS (" << cantRutas << ") ===" << endl;
	for (int i = 0; i < cantRutas; i++) {
		if (rutas[i] == nullptr) continue;
		string descGuardar = rutas[i]->get_Descripcion();
		for (int k = 0; k < (int)descGuardar.size(); k++) {
			if (descGuardar[k] == ' ') descGuardar[k] = '_';
		}
		string estado = rutas[i]->is_Activa() ? "ACTIVA" : "CORTADA";
		archivo << "["  << rutas[i]->get_Origen()
				<< "->" << rutas[i]->get_Destino()      << "] "
				<< "Ruta:"   << descGuardar              << " "
				<< "Dist:"   << rutas[i]->get_Distancia() << "km "
				<< "Estado:" << estado                   << endl;
	}

	archivo.close();
}

void grafo::cargarDatos(string nombreArchivo) {
	ifstream archivo(nombreArchivo.c_str());
	if (!archivo.is_open()) {
		cout << "Error al abrir el archivo para cargar." << endl;
		return;
	}

	string linea;

	// --- Ciudades ---
	getline(archivo, linea); // "=== CIUDADES (N) ==="
	int cantC = 0;
	sscanf(linea.c_str(), "=== CIUDADES (%d) ===", &cantC);

	for (int i = 0; i < cantC; i++) {
		getline(archivo, linea);
		int  id, x, y;
		char nombre[256];
		sscanf(linea.c_str(), "ID:%d Nombre:%s X:%d Y:%d", &id, nombre, &x, &y);
		string nombreStr = nombre;
		for (int k = 0; k < (int)nombreStr.size(); k++) {
			if (nombreStr[k] == '_') nombreStr[k] = ' ';
		}
		agregarCiudad(id, nombreStr, x, y);
	}

	// --- Rutas ---
	getline(archivo, linea); // "=== RUTAS (N) ==="
	int cantR = 0;
	sscanf(linea.c_str(), "=== RUTAS (%d) ===", &cantR);

	for (int i = 0; i < cantR; i++) {
		getline(archivo, linea);
		int   origen, destino;
		float distancia;
		char  desc[256];
		char  estado[16];
		sscanf(linea.c_str(), "[%d->%d] Ruta:%s Dist:%fkm Estado:%s",
			   &origen, &destino, desc, &distancia, estado);
		string descStr = desc;
		for (int k = 0; k < (int)descStr.size(); k++) {
			if (descStr[k] == '_') descStr[k] = ' ';
		}
		agregarRuta(origen, destino, distancia, descStr);
		if (string(estado) == "CORTADA") cortarRuta(origen, destino);
	}

	archivo.close();
	cout << "Datos cargados correctamente." << endl;
}

//  Consultas
float grafo::getMatriz(int i, int j) const {
	return matriz[i][j];
}

int grafo::getCantCiudades() const {
	return cantCiudades;
}

int grafo::getCantRutas() const {
	return cantRutas;
}

ciudad* grafo::getCiudad(int indice) const {
	if (indice < 0 || indice >= cantCiudades) return nullptr;
	return ciudades[indice];
}

ruta* grafo::getRuta(int indice) const {
	if (indice < 0 || indice >= cantRutas) return nullptr;
	return rutas[indice];
}

bool grafo::existeCiudad(int id) const {
	for (int i = 0; i < cantCiudades; i++) {
		if (ciudades[i] != nullptr && ciudades[i]->get_id() == id) {
			return true;
		}
	}
	return false;
}

void grafo::resetear() {
	for (int i = 0; i < cantCiudades; i++) {
		delete ciudades[i];
		ciudades[i] = nullptr;
	}
	for (int i = 0; i < cantRutas; i++) {
		delete rutas[i];
		rutas[i] = nullptr;
	}
	cantCiudades = 0;
	cantRutas    = 0;

	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			matriz[i][j] = (i == j) ? 0 : INF;
		}
	}
}
