#ifndef CIUDAD_H //archivo.h
#define CIUDAD_H      // evita que se incluya dos veces
#include <string>
using namespace std;

class ciudad{
    private:

        int id_ciudad;
        string nombre;
        int x;
        int y;

    public:

        ciudad(int id_ciudad, string nombre, int x, int y); //constructor
        ~ciudad();//destructor
		int get_id();//mostrar(retornar) el id de ciudad
		string get_Nombre(); //mostrar el nombre
		int get_X();//mostrar el valor del eje X
		int get_Y();//mostrar el valor del eje y
		void set_Nombre(string s);//escribir el nombre de la ciudad(nodo)
        void info();

};
#endif
/*
.h — atributos y funciones declaradas
.cpp — Desarrollo de funciones ya declaradas en la clase
*/
