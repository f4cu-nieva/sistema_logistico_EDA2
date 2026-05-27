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

        int get_Origen()const;
        int get_Destino()const;
        float  get_Distancia()const;   // qué tipo devuelve?
        string get_Descripcion()const;
        bool is_Activa()const;   // qué tipo devuelve?

        void set_Activa(bool b);   // qué tipo recibe?
        string info()const;
};

#endif
