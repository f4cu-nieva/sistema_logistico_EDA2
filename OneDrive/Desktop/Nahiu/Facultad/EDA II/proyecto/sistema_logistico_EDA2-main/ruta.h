#ifndef RUTA_H
#define RUTA_H

#include <string>
using namespace std;

class ruta {
	private:
		int id_origen;
		int id_destino;
		float distancia;
		string descripcion;
		bool  activa;

	public:
        ruta(int id_origen, int id_destino, float distancia, string descripcion);//constructor
		~ruta();//destructor

		int get_Origen();
		int get_Destino();
		float  get_Distancia();
		string get_Descripcion();
		bool is_Activa();

		void set_Origen(int o);
		void set_Destino(int d);

		void set_Activa(bool b);
		string info();//devuelve info de la ruta
};

#endif
