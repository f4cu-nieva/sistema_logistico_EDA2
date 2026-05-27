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
        int get_id();//ingresar el id de ciudad
        string get_Nombre(); //ingresar el nombre
        int get_X();//ingresar el eje X
        int get_Y();//ingresar el eje Y
        void set_Nombre(string s);//Mostrar el nombre de la ciudad(nodo)
        void info();

};
#endif
/*
.h — la "ficha técnica" — dice qué existe (atributos y funciones declaradas)
.cpp — el "manual de instrucciones" — dice cómo funciona cada cosa
*/
