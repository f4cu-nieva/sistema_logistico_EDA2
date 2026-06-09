#include "grafo.h"
#include <iostream>
#include <ctime>
using namespace std;

grafo::grafo() {
	cantCiudades = 0;
	cantRutas    = 0;
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			if (i == j) {
				matriz[i][j] = 0;
			} else {
				matriz[i][j] = INF;
			}
		}
	}
	for (int i = 0; i < MAX; i++) {
		ciudades[i] = NULL;
	}
	for (int i = 0; i < MAX * MAX; i++) {
		rutas[i] = NULL;
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

void grafo::agregarCiudad(int id, string nombre, int x, int y) {
	int salida = 0;
	ciudad* nueva = NULL;

	if (cantCiudades >= MAX) {
		cout << "Error: no se pueden agregar mas ciudades." << endl;
		salida = 1;
	}

	if (salida == 0) {
		nueva = new ciudad(id, nombre, x, y);
		if (nueva == NULL) {
			cout << "Error: no se pudo reservar memoria." << endl;
			salida = 1;
		}
	}

	if (salida == 0) {
		ciudades[cantCiudades] = nueva;
		cantCiudades++;
	}
}

// ---------------------------------------------------------------
// NUEVO: eliminarCiudad
// Elimina la ciudad con el id dado, limpia sus rutas y la matriz
// ---------------------------------------------------------------
void grafo::eliminarCiudad(int id) {
	// 1. Buscar el indice de la ciudad en el array
	int indice = -1;
	for (int i = 0; i < cantCiudades; i++) {
		if (ciudades[i] != NULL && ciudades[i]->get_id() == id) {
			indice = i;
			break;
		}
	}

	if (indice == -1) {
		cout << "Error: no se encontro la ciudad con id " << id << endl;
		return;
	}

	// 2. Eliminar todas las rutas que involucran esta ciudad
	int nuevaCantRutas = 0;
	ruta* nuevasRutas[MAX * MAX];
	for (int i = 0; i < MAX * MAX; i++) {
		nuevasRutas[i] = NULL;
	}

	for (int i = 0; i < cantRutas; i++) {
		if (rutas[i] != NULL &&
			rutas[i]->get_Origen()  != indice &&
			rutas[i]->get_Destino() != indice) {
			nuevasRutas[nuevaCantRutas] = rutas[i];
			nuevaCantRutas++;
		} else {
			delete rutas[i];
			rutas[i] = NULL;
		}
	}

	for (int i = 0; i < MAX * MAX; i++) {
		rutas[i] = nuevasRutas[i];
	}
	cantRutas = nuevaCantRutas;

	// 3. Eliminar el objeto ciudad y compactar el array
	delete ciudades[indice];
	ciudades[indice] = NULL;

	for (int i = indice; i < cantCiudades - 1; i++) {
		ciudades[i] = ciudades[i + 1];
	}
	ciudades[cantCiudades - 1] = NULL;
	cantCiudades--;

	// 4. Actualizar indices de rutas (bajamos 1 los que eran > indice)
	for (int i = 0; i < cantRutas; i++) {
		if (rutas[i] != NULL) {
			int o = rutas[i]->get_Origen();
			int d = rutas[i]->get_Destino();
			if (o > indice) rutas[i]->set_Origen(o - 1);
			if (d > indice) rutas[i]->set_Destino(d - 1);
		}
	}

	// 5. Reconstruir la matriz desde cero con los indices ya corregidos
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			matriz[i][j] = (i == j) ? 0 : INF;
		}
	}

	for (int i = 0; i < cantRutas; i++) {
		if (rutas[i] != NULL && rutas[i]->is_Activa()) {
			int o    = rutas[i]->get_Origen();
			int d    = rutas[i]->get_Destino();
			float dist = rutas[i]->get_Distancia();
			matriz[o][d] = dist;
			matriz[d][o] = dist;
		}
	}
}

void grafo::agregarRuta(int origen, int destino, float distancia, string descripcion) {
	int salida = 0;
	ruta* nueva = NULL;

	if (cantRutas >= MAX * MAX) {
		cout << "Error: no se pueden agregar mas rutas." << endl;
		salida = 1;
	}

	if (salida == 0) {
		nueva = new ruta(origen, destino, distancia, descripcion);
		if (nueva == NULL) {
			cout << "Error: no se pudo reservar memoria." << endl;
			salida = 1;
		}
	}

	if (salida == 0) {
		rutas[cantRutas] = nueva;
		cantRutas++;
		matriz[origen][destino] = distancia;
		matriz[destino][origen] = distancia;
	}
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
	int encontrado = 0;

	for (int i = 0; i < cantRutas; i++) {
		if (rutas[i]->get_Origen() == origen && rutas[i]->get_Destino() == destino) {
			rutas[i]->set_Activa(true);
			matriz[origen][destino] = rutas[i]->get_Distancia();
			matriz[destino][origen] = rutas[i]->get_Distancia();
			encontrado = 1;
		}
	}

	if (encontrado == 1) {
		cout << "Ruta habilitada correctamente." << endl;
	} else {
		cout << "Error: no se encontro la ruta indicada." << endl;
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
			if (matriz[i][j] == INF) {
				cout << "INF\t";
			} else {
				cout << matriz[i][j] << "\t";
			}
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
	string resultado = "";

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
	if (!archivo.is_open()) return;

	// --- Encabezado ciudades ---
	archivo << "=== CIUDADES (" << cantCiudades << ") ===" << endl;
	for (int i = 0; i < cantCiudades; i++) {
		if (ciudades[i] == NULL) continue;
		string nombreGuardar = ciudades[i]->get_Nombre();
		for (int k = 0; k < (int)nombreGuardar.size(); k++) {
			if (nombreGuardar[k] == ' ') nombreGuardar[k] = '_';
		}
		archivo << "ID:"     << ciudades[i]->get_id() << " "
				<< "Nombre:" << nombreGuardar          << " "
				<< "X:"      << ciudades[i]->get_X()   << " "
				<< "Y:"      << ciudades[i]->get_Y()   << endl;
	}

	// --- Encabezado rutas ---
	archivo << "=== RUTAS (" << cantRutas << ") ===" << endl;
	for (int i = 0; i < cantRutas; i++) {
		if (rutas[i] == NULL) continue;
		string descGuardar = rutas[i]->get_Descripcion();
		for (int k = 0; k < (int)descGuardar.size(); k++) {
			if (descGuardar[k] == ' ') descGuardar[k] = '_';
		}
		string estado = rutas[i]->is_Activa() ? "ACTIVA" : "CORTADA";
		archivo << "["  << rutas[i]->get_Origen()
				<< "->" << rutas[i]->get_Destino()  << "] "
				<< "Ruta:" << descGuardar            << " "
				<< "Dist:" << rutas[i]->get_Distancia() << "km "
				<< "Estado:" << estado               << endl;
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

	// --- Leer ciudades ---
	getline(archivo, linea); // "=== CIUDADES (N) ==="
	int cantC = 0;
	sscanf(linea.c_str(), "=== CIUDADES (%d) ===", &cantC);

	for (int i = 0; i < cantC; i++) {
		getline(archivo, linea);
		int    id, x, y;
		char   nombre[256];
		sscanf(linea.c_str(), "ID:%d Nombre:%s X:%d Y:%d", &id, nombre, &x, &y);
		string nombreStr = nombre;
		for (int k = 0; k < (int)nombreStr.size(); k++) {
			if (nombreStr[k] == '_') nombreStr[k] = ' ';
		}
		agregarCiudad(id, nombreStr, x, y);
	}

	// --- Leer rutas ---
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

float grafo::getMatriz(int i, int j) {
	return matriz[i][j];
}

int grafo::getCantCiudades() {
	return cantCiudades;
}

ciudad* grafo::getCiudad(int indice) {
	if (indice < 0 || indice >= cantCiudades) return NULL;
	return ciudades[indice];
}

bool grafo::existeCiudad(int id) {
	for (int i = 0; i < cantCiudades; i++) {
		if (ciudades[i] != NULL && ciudades[i]->get_id() == id) {
			return true;
		}
	}
	return false;
}

void grafo::resetear() {
	for (int i = 0; i < cantCiudades; i++) {
		delete ciudades[i];
		ciudades[i] = NULL;
	}
	for (int i = 0; i < cantRutas; i++) {
		delete rutas[i];
		rutas[i] = NULL;
	}

	cantCiudades = 0;
	cantRutas    = 0;

	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			if (i == j) {
				matriz[i][j] = 0;
			} else {
				matriz[i][j] = INF;
			}
		}
	}
}

void grafo::registrarHistorial(string operacion) {
	ofstream archivo("historial.txt", ios::app); // append: no sobreescribe
	if (!archivo.is_open()) return;

	// Obtener fecha y hora actual
	time_t ahora = time(NULL);
	struct tm* t = localtime(&ahora);
	char timestamp[32];
	sprintf(timestamp, "[%04d-%02d-%02d %02d:%02d:%02d]",
		t->tm_year + 1900,
		t->tm_mon  + 1,
		t->tm_mday,
		t->tm_hour,
		t->tm_min,
		t->tm_sec);

	archivo << timestamp << " " << operacion << endl;
	archivo.close();
}

int grafo::getCantRutas() {
    return cantRutas;
}

ruta* grafo::getRuta(int indice) {
    if (indice < 0 || indice >= cantRutas) return NULL;
    return rutas[indice];
}

int grafo::getCaminoIndices(int origen, int destino, int* camino, int maxLen) {
    float distancias[MAX];
    bool  visitado[MAX];
    int   anterior[MAX];
    for (int i = 0; i < MAX; i++) {
        distancias[i] = INF; visitado[i] = false; anterior[i] = -1;
    }
    distancias[origen] = 0;
    for (int paso = 0; paso < cantCiudades; paso++) {
        int actual = -1;
        for (int i = 0; i < cantCiudades; i++)
            if (!visitado[i] && (actual == -1 || distancias[i] < distancias[actual]))
                actual = i;
        if (actual == -1 || distancias[actual] == INF) break;
        visitado[actual] = true;
        for (int v = 0; v < cantCiudades; v++) {
            if (matriz[actual][v] != INF && !visitado[v]) {
                float nd = distancias[actual] + matriz[actual][v];
                if (nd < distancias[v]) { distancias[v] = nd; anterior[v] = actual; }
            }
        }
    }
    if (distancias[destino] == INF) return 0;
    int tmp[MAX], lon = 0, act = destino;
    while (act != -1 && lon < MAX) { tmp[lon++] = act; act = anterior[act]; }
    for (int i = 0; i < lon && i < maxLen; i++) camino[i] = tmp[lon-1-i];
    return lon;
}
