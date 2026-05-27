//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
    g.agregarCiudad(0, "Comodoro Rivadavia", 520, 420);
    g.agregarCiudad(1, "Trelew",             390, 260);
	g.agregarCiudad(2, "Rawson",             420, 240);
    g.agregarCiudad(3, "Puerto Madryn",      370, 210);
	g.agregarCiudad(4, "Esquel",             120, 220);

    g.agregarRuta(0, 1, 376,  "RN 3");
    g.agregarRuta(1, 2, 22,   "RP 7");
	g.agregarRuta(1, 3, 64.8, "RN 3");
    g.agregarRuta(3, 4, 665,  "RN 3 + RN 25 + RN 40");
	g.agregarRuta(2, 4, 623,  "RN 25 + RN 40");
    g.agregarRuta(1, 4, 602,  "RN 25 + RN 40");
    g.agregarRuta(0, 2, 384,  "RN 3 + RP 7");
    g.agregarRuta(0, 3, 439,  "RN 3");
	g.agregarRuta(0, 4, 576,  "RN 3 + RN 25 + RN 40");

	cboOrigen->Items->Add("Comodoro Rivadavia");
    cboOrigen->Items->Add("Trelew");
    cboOrigen->Items->Add("Rawson");
    cboOrigen->Items->Add("Puerto Madryn");
	cboOrigen->Items->Add("Esquel");

	cboDestino->Items->Add("Comodoro Rivadavia");
    cboDestino->Items->Add("Trelew");
    cboDestino->Items->Add("Rawson");
    cboDestino->Items->Add("Puerto Madryn");
	cboDestino->Items->Add("Esquel");

	cboOrigen->ItemIndex  = 0;
	cboDestino->ItemIndex = 1;
	dibujarMapa();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnCalcularClick(TObject *Sender)
{
	int origen  = cboOrigen->ItemIndex;
    int destino = cboDestino->ItemIndex;

    if (origen == destino) {
		memoResultados->Lines->Add("Error: origen y destino son iguales.");
        return;
	}

    memoResultados->Lines->Add("=== CALCULANDO RUTA OPTIMA ===");
    string resultado = g.calcularRutaOptimaStr(origen, destino);

    string linea = "";
	for (int i = 0; i <= resultado.size(); i++) {
        if (i == resultado.size() || resultado[i] == '\n') {
            memoResultados->Lines->Add(linea.c_str());
            linea = "";
		} else {
            linea += resultado[i];
		}
    }
	memoResultados->Lines->Add("---");
	dibujarMapa();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnCortarClick(TObject *Sender)
{
    int origen  = cboOrigen->ItemIndex;
    int destino = cboDestino->ItemIndex;

	if (origen == destino) {
        memoResultados->Lines->Add("Error: origen y destino son iguales.");
		return;
    }

    g.cortarRuta(origen, destino);
	memoResultados->Lines->Add("=== RUTA CORTADA ===");
    memoResultados->Lines->Add(("De " + to_string(origen) + " a " + to_string(destino)).c_str());
	memoResultados->Lines->Add("---");
	 dibujarMapa();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnHabilitarClick(TObject *Sender)
{
    int origen  = cboOrigen->ItemIndex;
	int destino = cboDestino->ItemIndex;

    g.habilitarRuta(origen, destino);
    memoResultados->Lines->Add("=== RUTA HABILITADA ===");
	memoResultados->Lines->Add(("De " + to_string(origen) + " a " + to_string(destino)).c_str());
	memoResultados->Lines->Add("---");
	 dibujarMapa();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnMatrizClick(TObject *Sender)
{

    memoResultados->Font->Name = "Courier New";
	memoResultados->Font->Size = 9;

    string ciudades[5] = {"Comodoro", "Trelew", "Rawson", "P.Madryn", "Esquel"};
    char buf[512];

    // Encabezado
	sprintf(buf, "%-10s %9s %9s %9s %9s %9s", "", "Comodoro", "Trelew", "Rawson", "P.Madryn", "Esquel");
    memoResultados->Lines->Add(buf);

    // Filas
    for (int i = 0; i < 5; i++) {
        string fila = "";
		sprintf(buf, "%-10s", ciudades[i].c_str());
        fila += buf;

        for (int j = 0; j < 5; j++) {
            float val = (i == j) ? 0 : g.getMatriz(i, j);
            if (val == 999999)
				sprintf(buf, " %9s", "INF");
            else
                sprintf(buf, " %9.0f", val);
            fila += buf;
        }
        memoResultados->Lines->Add(fila.c_str());
	}
}

//---------------------------------------------------------------------------
void __fastcall TForm1::btnGuardarClick(TObject *Sender)
{
	g.guardarDatos("chubut.dat");
    memoResultados->Lines->Add("=== DATOS GUARDADOS ===");
    memoResultados->Lines->Add("---");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnCargarClick(TObject *Sender)
{
    g.resetear();
    g.cargarDatos("chubut.dat");
    cboOrigen->Items->Clear();
	cboDestino->Items->Clear();
    cboOrigen->Items->Add("Comodoro Rivadavia");
	cboOrigen->Items->Add("Trelew");
    cboOrigen->Items->Add("Rawson");
    cboOrigen->Items->Add("Puerto Madryn");
	cboOrigen->Items->Add("Esquel");
	cboDestino->Items->Add("Comodoro Rivadavia");
	cboDestino->Items->Add("Trelew");
	cboDestino->Items->Add("Rawson");
	cboDestino->Items->Add("Puerto Madryn");
	cboDestino->Items->Add("Esquel");
	cboOrigen->ItemIndex  = 0;
	cboDestino->ItemIndex = 1;
	memoResultados->Lines->Add("=== DATOS CARGADOS ===");
	memoResultados->Lines->Add("---");
	 dibujarMapa();
}
//---------------------------------------------------------------------------

void TForm1::dibujarMapa()
{
    TPngImage* png = new TPngImage();
    png->LoadFromFile("chubut.png");
    imgMapa->Picture->Assign(png);
	delete png;
}

//---------------------------------------------------------------------------

