//---------------------------------------------------------------------------
#include "grafo.h"
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
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
	TLabel *Label1;
	TLabel *Label2;
	TComboBox *cboOrigen;
	TLabel *Label3;
	TComboBox *cboDestino;
	TMemo *memoResultados;
	TButton *btnCalcular;
	TButton *btnCortar;
	TButton *btnHabilitar;
	TButton *btnMatriz;
	TButton *btnGuardar;
	TButton *btnCargar;
	TImage *imgMapa;
	void __fastcall btnCalcularClick(TObject *Sender);
	void __fastcall btnCortarClick(TObject *Sender);
	void __fastcall btnHabilitarClick(TObject *Sender);
	void __fastcall btnMatrizClick(TObject *Sender);
	void __fastcall btnGuardarClick(TObject *Sender);
	void __fastcall btnCargarClick(TObject *Sender);


private:	// User declarations
	grafo g;
	void dibujarMapa();
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
