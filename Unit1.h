//---------------------------------------------------------------------------
#include "grafo.h"
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ComCtrls.hpp>
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabel    *Label1;
	TComboBox *cboOrigen;
	TComboBox *cboDestino;
	TMemo     *memoResultados;
	TButton   *btnCalcular;
	TButton   *btnCortar;
	TButton   *btnHabilitar;
	TButton   *btnMatriz;
	TButton   *btnGuardar;
	TButton   *btnCargar;
	TImage    *imgMapa;
	TComboBox *cboAgregar;
	TButton *btnAgregarCiudad;
	TButton *btnBajaCiudad;
	TLabel *Label4;
	TComboBox *cboBaja;
	TStringGrid *gridCiudades;
	TStringGrid *gridRutas;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label2;
	TLabel *Label3;    // da de baja la ciudad seleccionada en cboOrigen

	void __fastcall btnCalcularClick(TObject *Sender);
	void __fastcall btnCortarClick(TObject *Sender);
	void __fastcall btnHabilitarClick(TObject *Sender);
	void __fastcall btnMatrizClick(TObject *Sender);
	void __fastcall btnGuardarClick(TObject *Sender);
	void __fastcall btnCargarClick(TObject *Sender);
	void __fastcall btnAgregarCiudadClick(TObject *Sender);
	void __fastcall btnBajaCiudadClick(TObject *Sender);
	void __fastcall cboOrigenChange(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);



			  /*

	void __fastcall Label5Click(TObject *Sender);
	void __fastcall Label5ContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled);
			  // NUEVO
			  */

private:
	grafo g;
	void dibujarMapa();


	void actualizarCombos();           // NUEVO: reconstruye cboOrigen y cboDestino
	void actualizarComboDisponibles(); // NUEVO: reconstruye cboAgregar
	void cargarRutasExtra(int idCiudadExtra); // NUEVO: carga rutas de la ciudad extra
	void actualizarComboBaja();

	void escribirHistorial(string operacion);
	void actualizarGrids();

	int caminoOptimo[15];   // indices de ciudades del camino
	int longitudCamino;     // cantidad de ciudades en el camino
	bool mostrarCamino;
    bool esAr staCamino(int a, int b);
public:
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
