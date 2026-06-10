//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <ctime>
#include <cmath>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

struct CiudadExtra { int id; string nombre; int x, y; };
static CiudadExtra ciudadesExtra[5] = {
	{ 5, "Rio Mayo",    390, 350 },
	{ 6, "Sarmiento",  630, 210 },
	{ 7, "Gaiman",     580,  30 },
	{ 8, "Camarones",  740, 250 },
	{ 9, "Lago Puelo",  55,  50 }
};

struct RutaExtra { int origen, destino; float distancia; string descripcion; };
static RutaExtra rutasRioMayo[2]   = { {5,0,278,"RN 26"}, {5,4,260,"RN 40"} };
static RutaExtra rutasSarmiento[2] = { {6,0,148,"RN 26"}, {6,1,290,"RN 25"} };
static RutaExtra rutasGaiman[2]    = { {7,1,17,"RP 7"},   {7,2,28,"RP 7"}   };
static RutaExtra rutasCamarones[2] = { {8,2,165,"RP 1"},  {8,0,270,"RP 1"}  };
static RutaExtra rutasLagoPuelo[1] = { {9,4,70,"RN 40"}                      };

//---------------------------------------------------------------------------
void TForm1::escribirHistorial(string operacion) {
	FILE* f = fopen("historial.txt", "a");
	if (f == NULL) return;
	time_t ahora = time(NULL);
	struct tm* t = localtime(&ahora);
	char ts[32];
	sprintf(ts, "[%04d-%02d-%02d %02d:%02d:%02d]",
		t->tm_year+1900, t->tm_mon+1, t->tm_mday,
		t->tm_hour, t->tm_min, t->tm_sec);
	fprintf(f, "%s %s\n", ts, operacion.c_str());
	fclose(f);
}

//---------------------------------------------------------------------------
bool TForm1::esArístaCamino(int a, int b) {
	if (!mostrarCamino) return false;
	for (int i = 0; i < longitudCamino - 1; i++) {
		if ((caminoOptimo[i] == a && caminoOptimo[i+1] == b) ||
			(caminoOptimo[i] == b && caminoOptimo[i+1] == a))
			return true;
	}
	return false;
}

//---------------------------------------------------------------------------
void TForm1::dibujarMapa() {
	int W = imgMapa->Width;
	int H = imgMapa->Height;
	if (W <= 0 || H <= 0) return;

	TBitmap* bmp = new TBitmap();
	bmp->Width  = W;
	bmp->Height = H;
	TCanvas* c  = bmp->Canvas;

	c->Brush->Color = clBlack;
	c->FillRect(TRect(0, 0, W, H));

	float sx = (float)W / 760.0f;
	float sy = (float)H / 420.0f;

	TPoint pts[] = {
		TPoint((int)(150*sx),(int)(10*sy)),  TPoint((int)(560*sx),(int)(8*sy)),
		TPoint((int)(590*sx),(int)(25*sy)),  TPoint((int)(620*sx),(int)(20*sy)),
		TPoint((int)(650*sx),(int)(38*sy)),  TPoint((int)(670*sx),(int)(60*sy)),
		TPoint((int)(685*sx),(int)(92*sy)),  TPoint((int)(695*sx),(int)(125*sy)),
		TPoint((int)(688*sx),(int)(152*sy)), TPoint((int)(698*sx),(int)(175*sy)),
		TPoint((int)(710*sx),(int)(200*sy)), TPoint((int)(715*sx),(int)(228*sy)),
		TPoint((int)(712*sx),(int)(255*sy)), TPoint((int)(718*sx),(int)(282*sy)),
		TPoint((int)(722*sx),(int)(310*sy)), TPoint((int)(720*sx),(int)(338*sy)),
		TPoint((int)(724*sx),(int)(362*sy)), TPoint((int)(728*sx),(int)(388*sy)),
		TPoint((int)(720*sx),(int)(408*sy)), TPoint((int)(690*sx),(int)(418*sy)),
		TPoint((int)(645*sx),(int)(420*sy)), TPoint((int)(595*sx),(int)(416*sy)),
		TPoint((int)(545*sx),(int)(411*sy)), TPoint((int)(495*sx),(int)(406*sy)),
		TPoint((int)(445*sx),(int)(400*sy)), TPoint((int)(395*sx),(int)(393*sy)),
		TPoint((int)(345*sx),(int)(382*sy)), TPoint((int)(300*sx),(int)(368*sy)),
		TPoint((int)(262*sx),(int)(350*sy)), TPoint((int)(232*sx),(int)(328*sy)),
		TPoint((int)(210*sx),(int)(302*sy)), TPoint((int)(192*sx),(int)(272*sy)),
		TPoint((int)(178*sx),(int)(240*sy)), TPoint((int)(166*sx),(int)(207*sy)),
		TPoint((int)(155*sx),(int)(172*sy)), TPoint((int)(145*sx),(int)(137*sy)),
		TPoint((int)(138*sx),(int)(102*sy)), TPoint((int)(136*sx),(int)(70*sy)),
		TPoint((int)(140*sx),(int)(42*sy)),  TPoint((int)(145*sx),(int)(22*sy))
	};
	c->Brush->Color = (TColor)0x1E3A14;
	c->Pen->Color   = (TColor)0x4A9A3A;
	c->Pen->Width   = 2;
	c->Polygon(pts, 40);

	int cant = g.getCantCiudades();

	if (mostrarCamino) {
		// MODO CAMINO: gris tenue todas + verde el camino optimo
		for (int i = 0; i < g.getCantRutas(); i++) {
			ruta* r = g.getRuta(i);
			if (r == NULL) continue;
			ciudad* co = g.getCiudad(r->get_Origen());
			ciudad* cd = g.getCiudad(r->get_Destino());
			if (co == NULL || cd == NULL) continue;
			c->Pen->Color = (TColor)0x334433;
			c->Pen->Width = 1;
			c->MoveTo((int)(co->get_X()*sx), (int)(co->get_Y()*sy));
			c->LineTo((int)(cd->get_X()*sx), (int)(cd->get_Y()*sy));
		}
		// Resaltar camino optimo en verde
		for (int i = 0; i < g.getCantRutas(); i++) {
			ruta* r = g.getRuta(i);
			if (r == NULL) continue;
			if (!esArístaCamino(r->get_Origen(), r->get_Destino())) continue;
			ciudad* co = g.getCiudad(r->get_Origen());
			ciudad* cd = g.getCiudad(r->get_Destino());
			if (co == NULL || cd == NULL) continue;
			int x1 = (int)(co->get_X()*sx), y1 = (int)(co->get_Y()*sy);
			int x2 = (int)(cd->get_X()*sx), y2 = (int)(cd->get_Y()*sy);
			c->Pen->Color = (TColor)0x00FF44;
			c->Pen->Width = 3;
			c->MoveTo(x1, y1); c->LineTo(x2, y2);

			int porcentaje = 50, offset = 14;
			if (i == 0) { porcentaje = 40; offset =  16; }
			if (i == 1) { porcentaje = 50; offset = -14; }
			if (i == 2) { porcentaje = 35; offset =  16; }
			if (i == 3) { porcentaje = 40; offset = -16; }
			if (i == 4) { porcentaje = 45; offset =  16; }
			if (i == 5) { porcentaje = 55; offset = -16; }
			if (i == 6) { porcentaje = 60; offset =  16; }
			if (i == 7) { porcentaje = 50; offset = -16; }
			if (i == 8) { porcentaje = 45; offset =  14; }

			int mx = x1+(x2-x1)*porcentaje/100, my = y1+(y2-y1)*porcentaje/100;
			double dx=x2-x1, dy=y2-y1, len=sqrt(dx*dx+dy*dy);
			if (len<1) len=1;
			int ex = mx+(int)((-dy/len)*offset), ey = my+(int)((dx/len)*offset);
			string dist = to_string((int)r->get_Distancia()) + " km";
			c->Font->Size=8; c->Font->Style=TFontStyles()<<fsBold;
			int tw=c->TextWidth(dist.c_str()), th=c->TextHeight(dist.c_str());
			c->Brush->Style=bsSolid; c->Brush->Color=clWhite;
			c->Pen->Color=(TColor)0x00BB33; c->Pen->Width=1;
			c->RoundRect(ex-tw/2-4,ey-th/2-3,ex+tw/2+4,ey+th/2+3,5,5);
			c->Font->Color=clBlack; c->Brush->Style=bsClear;
			c->TextOut(ex-tw/2,ey-th/2,dist.c_str());
		}
	} else {
		// MODO NORMAL: todas las rutas con su color segun estado
		for (int i = 0; i < g.getCantRutas(); i++) {
			ruta* r = g.getRuta(i);
			if (r == NULL) continue;
			ciudad* co = g.getCiudad(r->get_Origen());
			ciudad* cd = g.getCiudad(r->get_Destino());
			if (co == NULL || cd == NULL) continue;
			int x1=(int)(co->get_X()*sx), y1=(int)(co->get_Y()*sy);
			int x2=(int)(cd->get_X()*sx), y2=(int)(cd->get_Y()*sy);

			if (r->is_Activa()) {
				c->Pen->Color = (TColor)0x00CCFF; // celeste = activa
				c->Pen->Width = 2;
			} else {
				c->Pen->Color = (TColor)0x0000CC; // rojo = cortada
				c->Pen->Width = 2;
			}
			c->MoveTo(x1, y1); c->LineTo(x2, y2);

			// Etiqueta solo para rutas activas
			if (!r->is_Activa()) continue;

			int porcentaje = 50, offset = 14;
			if (i == 0) { porcentaje = 40; offset =  16; }
			if (i == 1) { porcentaje = 50; offset = -14; }
			if (i == 2) { porcentaje = 35; offset =  16; }
			if (i == 3) { porcentaje = 40; offset = -16; }
			if (i == 4) { porcentaje = 45; offset =  16; }
			if (i == 5) { porcentaje = 55; offset = -16; }
			if (i == 6) { porcentaje = 60; offset =  16; }
			if (i == 7) { porcentaje = 50; offset = -16; }
			if (i == 8) { porcentaje = 45; offset =  14; }

			int mx=x1+(x2-x1)*porcentaje/100, my=y1+(y2-y1)*porcentaje/100;
			double dx=x2-x1, dy=y2-y1, len=sqrt(dx*dx+dy*dy);
			if (len<1) len=1;
			int ex=mx+(int)((-dy/len)*offset), ey=my+(int)((dx/len)*offset);
			string dist=to_string((int)r->get_Distancia())+" km";
			c->Font->Size=8; c->Font->Style=TFontStyles()<<fsBold;
			int tw=c->TextWidth(dist.c_str()), th=c->TextHeight(dist.c_str());
			c->Brush->Style=bsSolid; c->Brush->Color=clWhite;
			c->Pen->Color=(TColor)0x00AACC; c->Pen->Width=1;
			c->RoundRect(ex-tw/2-4,ey-th/2-3,ex+tw/2+4,ey+th/2+3,5,5);
			c->Font->Color=clBlack; c->Brush->Style=bsClear;
			c->TextOut(ex-tw/2,ey-th/2,dist.c_str());
		}
	}

	// Dibujar ciudades
	for (int i = 0; i < cant; i++) {
		ciudad* ci = g.getCiudad(i);
		if (ci == NULL) continue;
		int cx=(int)(ci->get_X()*sx), cy=(int)(ci->get_Y()*sy);
		int id=ci->get_id();

		bool esCamino = false;
		if (mostrarCamino)
			for (int k=0; k<longitudCamino; k++)
				if (caminoOptimo[k]==i) { esCamino=true; break; }

		if (esCamino)
			c->Brush->Color = (TColor)0x00CC44;
		else if (id < 5)
			c->Brush->Color = (TColor)0xDD4422;
		else
			c->Brush->Color = (TColor)0x22AA44;

		c->Pen->Color = esCamino ? clWhite : (TColor)0x888888;
		c->Pen->Width = esCamino ? 3 : 2;
		int rad = esCamino ? 18 : 14;
		c->Ellipse(cx-rad,cy-rad,cx+rad,cy+rad);

		c->Font->Size=esCamino?10:9; c->Font->Color=clWhite;
		c->Font->Style=TFontStyles()<<fsBold; c->Brush->Style=bsClear;
		string idStr=to_string(id);
		int tw=c->TextWidth(idStr.c_str()), th=c->TextHeight(idStr.c_str());
		c->TextOut(cx-tw/2,cy-th/2,idStr.c_str());

		string nombre=ci->get_Nombre();
		c->Font->Size=8;
		tw=c->TextWidth(nombre.c_str()); th=c->TextHeight(nombre.c_str());
		c->Brush->Style=bsSolid; c->Brush->Color=(TColor)0x222222;
		c->Pen->Color=(TColor)0x444444; c->Pen->Width=1;
		c->RoundRect(cx-tw/2-2,cy+rad+2,cx+tw/2+2,cy+rad+th+4,3,3);
		c->Font->Color=clWhite; c->Brush->Style=bsClear;
		c->TextOut(cx-tw/2,cy+rad+3,nombre.c_str());
	}

	// Leyenda
	c->Brush->Style=bsSolid; c->Brush->Color=(TColor)0x111111;
	c->Pen->Color=clGray; c->Pen->Width=1;
	c->Rectangle(5,H-88,185,H-5);
	c->Font->Size=7; c->Font->Style=TFontStyles();
	c->Brush->Style=bsSolid; c->Brush->Color=(TColor)0xDD4422;
	c->Ellipse(12,H-81,22,H-71);
	c->Font->Color=clWhite; c->Brush->Style=bsClear;
	c->TextOut(26,H-81,"Ciudad inicial");
	c->Brush->Style=bsSolid; c->Brush->Color=(TColor)0x22AA44;
	c->Ellipse(12,H-63,22,H-53);
	c->Font->Color=clWhite; c->Brush->Style=bsClear;
	c->TextOut(26,H-63,"Ciudad extra");
	c->Brush->Style=bsSolid; c->Brush->Color=(TColor)0x00CC44;
	c->Ellipse(12,H-45,22,H-35);
	c->Font->Color=clWhite; c->Brush->Style=bsClear;
	c->TextOut(26,H-45,"En ruta optima");
	c->Pen->Color=(TColor)0x00CCFF; c->Pen->Width=2;
	c->MoveTo(12,H-27); c->LineTo(35,H-27);
	c->Font->Color=clWhite; c->TextOut(40,H-32,"Ruta activa");
	c->Pen->Color=(TColor)0x0000CC; c->Pen->Width=2;
	c->MoveTo(12,H-12); c->LineTo(35,H-12);
	c->Font->Color=clWhite; c->TextOut(40,H-17,"Ruta cortada");

	imgMapa->Picture->Assign(bmp);
	delete bmp;
}

//---------------------------------------------------------------------------
void TForm1::actualizarGrids() {
	int cantC=g.getCantCiudades();
	gridCiudades->Cells[0][0]="ID"; gridCiudades->Cells[1][0]="Nombre";
	gridCiudades->Cells[2][0]="X";  gridCiudades->Cells[3][0]="Y";
	gridCiudades->RowCount=cantC+1;
	for (int i=0;i<cantC;i++) {
		ciudad* ci=g.getCiudad(i); if (ci==NULL) continue;
		gridCiudades->Cells[0][i+1]=IntToStr(ci->get_id());
		gridCiudades->Cells[1][i+1]=ci->get_Nombre().c_str();
		gridCiudades->Cells[2][i+1]=IntToStr(ci->get_X());
		gridCiudades->Cells[3][i+1]=IntToStr(ci->get_Y());
	}
	gridRutas->Cells[0][0]="Origen";   gridRutas->Cells[1][0]="Destino";
	gridRutas->Cells[2][0]="Distancia"; gridRutas->Cells[3][0]="Ruta";
	gridRutas->Cells[4][0]="Estado";
	int cantR=g.getCantRutas();
	gridRutas->RowCount=(cantR>0)?cantR+1:2;
	for (int i=0;i<cantR;i++) {
		ruta* r=g.getRuta(i); if (r==NULL) continue;
		string nomO="",nomD="";
		ciudad* co=g.getCiudad(r->get_Origen());
		ciudad* cd=g.getCiudad(r->get_Destino());
		if (co) nomO=co->get_Nombre();
		if (cd) nomD=cd->get_Nombre();
		gridRutas->Cells[0][i+1]=nomO.c_str();
		gridRutas->Cells[1][i+1]=nomD.c_str();
		gridRutas->Cells[2][i+1]=(FloatToStr(r->get_Distancia())+" km");
		gridRutas->Cells[3][i+1]=r->get_Descripcion().c_str();
		gridRutas->Cells[4][i+1]=r->is_Activa()?"ACTIVA":"CORTADA";
	}
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
	mostrarCamino=false; longitudCamino=0;
	for (int i=0;i<15;i++) caminoOptimo[i]=-1;

	g.agregarCiudad(0,"Comodoro Rivadavia",700,390);
	g.agregarCiudad(1,"Trelew",            380,200);
	g.agregarCiudad(2,"Rawson",            660,110);
	g.agregarCiudad(3,"Puerto Madryn",     370, 45);
	g.agregarCiudad(4,"Esquel",             90,140);

	g.agregarRuta(0,1,376,  "RN 3");
	g.agregarRuta(1,2,22,   "RP 7");
	g.agregarRuta(1,3,64.8, "RN 3");
	g.agregarRuta(3,4,665,  "RN 3 + RN 25 + RN 40");
	g.agregarRuta(2,4,623,  "RN 25 + RN 40");
	g.agregarRuta(1,4,602,  "RN 25 + RN 40");
	g.agregarRuta(0,2,384,  "RN 3 + RP 7");
	g.agregarRuta(0,3,439,  "RN 3");
	g.agregarRuta(0,4,576,  "RN 3 + RN 25 + RN 40");

	actualizarCombos(); actualizarComboDisponibles();
	actualizarComboBaja(); actualizarGrids();
	cboOrigen->ItemIndex=0; cboDestino->ItemIndex=1;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender) { dibujarMapa(); }

//---------------------------------------------------------------------------
void __fastcall TForm1::cboOrigenChange(TObject *Sender) {
	mostrarCamino=false; dibujarMapa();
}

//---------------------------------------------------------------------------
void TForm1::actualizarCombos() {
	int idxO=cboOrigen->ItemIndex, idxD=cboDestino->ItemIndex;
	cboOrigen->Items->Clear(); cboDestino->Items->Clear();
	for (int i=0;i<g.getCantCiudades();i++) {
		ciudad* ci=g.getCiudad(i);
		if (ci!=NULL) {
			cboOrigen->Items->Add(ci->get_Nombre().c_str());
			cboDestino->Items->Add(ci->get_Nombre().c_str());
		}
	}
	if (idxO<cboOrigen->Items->Count) cboOrigen->ItemIndex=idxO;
	else cboOrigen->ItemIndex=0;
	if (idxD<cboDestino->Items->Count) cboDestino->ItemIndex=idxD;
	else cboDestino->ItemIndex=(cboDestino->Items->Count>1)?1:0;
}

//---------------------------------------------------------------------------
void TForm1::actualizarComboDisponibles() {
	cboAgregar->Items->Clear();
	for (int i=0;i<5;i++)
		if (!g.existeCiudad(ciudadesExtra[i].id))
			cboAgregar->Items->Add(ciudadesExtra[i].nombre.c_str());
	if (cboAgregar->Items->Count>0) cboAgregar->ItemIndex=0;
}

//---------------------------------------------------------------------------
void TForm1::actualizarComboBaja() {
	cboBaja->Items->Clear();
	for (int i=0;i<g.getCantCiudades();i++) {
		ciudad* ci=g.getCiudad(i);
		if (ci!=NULL) cboBaja->Items->Add(ci->get_Nombre().c_str());
	}
	if (cboBaja->Items->Count>0) cboBaja->ItemIndex=0;
}

//---------------------------------------------------------------------------
void TForm1::cargarRutasExtra(int idCiudadExtra) {
	int idxNueva=-1;
	for (int i=0;i<g.getCantCiudades();i++)
		if (g.getCiudad(i)->get_id()==idCiudadExtra) { idxNueva=i; break; }
	if (idxNueva==-1) return;

	if (idCiudadExtra==5) {
		for (int r=0;r<2;r++) {
			int idxDest=-1;
			for (int i=0;i<g.getCantCiudades();i++)
				if (g.getCiudad(i)->get_id()==rutasRioMayo[r].destino) { idxDest=i; break; }
			if (idxDest!=-1) g.agregarRuta(idxNueva,idxDest,rutasRioMayo[r].distancia,rutasRioMayo[r].descripcion);
		}
	} else if (idCiudadExtra==6) {
		for (int r=0;r<2;r++) {
			int idxDest=-1;
			for (int i=0;i<g.getCantCiudades();i++)
				if (g.getCiudad(i)->get_id()==rutasSarmiento[r].destino) { idxDest=i; break; }
			if (idxDest!=-1) g.agregarRuta(idxNueva,idxDest,rutasSarmiento[r].distancia,rutasSarmiento[r].descripcion);
		}
	} else if (idCiudadExtra==7) {
		for (int r=0;r<2;r++) {
			int idxDest=-1;
			for (int i=0;i<g.getCantCiudades();i++)
				if (g.getCiudad(i)->get_id()==rutasGaiman[r].destino) { idxDest=i; break; }
			if (idxDest!=-1) g.agregarRuta(idxNueva,idxDest,rutasGaiman[r].distancia,rutasGaiman[r].descripcion);
		}
	} else if (idCiudadExtra==8) {
		for (int r=0;r<2;r++) {
			int idxDest=-1;
			for (int i=0;i<g.getCantCiudades();i++)
				if (g.getCiudad(i)->get_id()==rutasCamarones[r].destino) { idxDest=i; break; }
			if (idxDest!=-1) g.agregarRuta(idxNueva,idxDest,rutasCamarones[r].distancia,rutasCamarones[r].descripcion);
		}
	} else if (idCiudadExtra==9) {
		int idxDest=-1;
		for (int i=0;i<g.getCantCiudades();i++)
			if (g.getCiudad(i)->get_id()==rutasLagoPuelo[0].destino) { idxDest=i; break; }
		if (idxDest!=-1) g.agregarRuta(idxNueva,idxDest,rutasLagoPuelo[0].distancia,rutasLagoPuelo[0].descripcion);
	}
}

//---------------------------------------------------------------------------
void __fastcall TForm1::btnCalcularClick(TObject *Sender) {
	int origen=cboOrigen->ItemIndex, destino=cboDestino->ItemIndex;
	if (origen==destino) { memoResultados->Lines->Add("Error: origen y destino son iguales."); return; }
	memoResultados->Lines->Add("=== CALCULANDO RUTA OPTIMA ===");
	string resultado=g.calcularRutaOptimaStr(origen,destino);
	longitudCamino=g.getCaminoIndices(origen,destino,caminoOptimo,15);
	mostrarCamino=(longitudCamino>1);
	string linea="";
	for (int i=0;i<=(int)resultado.size();i++) {
		if (i==(int)resultado.size()||resultado[i]=='\n') { memoResultados->Lines->Add(linea.c_str()); linea=""; }
		else linea+=resultado[i];
	}
	memoResultados->Lines->Add("---");
	string logLinea=resultado;
	for (int i=0;i<(int)logLinea.size();i++) if (logLinea[i]=='\n') logLinea[i]=' ';
	escribirHistorial("RUTA OPTIMA: "+logLinea);
	actualizarGrids(); dibujarMapa();
}

//---------------------------------------------------------------------------
void __fastcall TForm1::btnCortarClick(TObject *Sender) {
    int origen  = cboOrigen->ItemIndex;
    int destino = cboDestino->ItemIndex;
    if (origen == destino) {
        memoResultados->Lines->Add("Error: origen y destino son iguales.");
        return;
    }

    // Verificar si existe ruta directa buscando en el array de rutas
    bool existeRuta = false;
    for (int i = 0; i < g.getCantRutas(); i++) {
        ruta* r = g.getRuta(i);
        if (r == NULL) continue;
        if ((r->get_Origen() == origen && r->get_Destino() == destino) ||
            (r->get_Origen() == destino && r->get_Destino() == origen)) {
            if (r->is_Activa()) { existeRuta = true; break; }
        }
    }

    if (!existeRuta) {
        memoResultados->Lines->Add("=== ERROR ===");
        memoResultados->Lines->Add("No existe conexion directa activa entre esas ciudades.");
        memoResultados->Lines->Add("---");
        return;
    }

	mostrarCamino = false;
	g.cortarRuta(origen, destino);
	string nomO = g.getCiudad(origen)  ? g.getCiudad(origen)->get_Nombre()  : to_string(origen);
	string nomD = g.getCiudad(destino) ? g.getCiudad(destino)->get_Nombre() : to_string(destino);
	memoResultados->Lines->Add("=== RUTA CORTADA ===");
	memoResultados->Lines->Add(("De " + nomO + " a " + nomD).c_str());
	memoResultados->Lines->Add("---");
	escribirHistorial("RUTA CORTADA: " + nomO + " -> " + nomD);
	actualizarGrids();
	dibujarMapa();
}

//---------------------------------------------------------------------------


void __fastcall TForm1::btnHabilitarClick(TObject *Sender) {
	int origen=cboOrigen->ItemIndex, destino=cboDestino->ItemIndex;
	mostrarCamino=false;
	g.habilitarRuta(origen,destino);
	string nomO=g.getCiudad(origen)  ? g.getCiudad(origen)->get_Nombre()  : to_string(origen);
	string nomD=g.getCiudad(destino) ? g.getCiudad(destino)->get_Nombre() : to_string(destino);
	memoResultados->Lines->Add("=== RUTA HABILITADA ===");
	memoResultados->Lines->Add(("De "+nomO+" a "+nomD).c_str());
	memoResultados->Lines->Add("---");
	escribirHistorial("RUTA HABILITADA: "+nomO+" -> "+nomD);
	actualizarGrids(); dibujarMapa();
}




//---------------------------------------------------------------------------
void __fastcall TForm1::btnMatrizClick(TObject *Sender) {
	memoResultados->Font->Name="Courier New"; memoResultados->Font->Size=9;
	int cant=g.getCantCiudades(); char buf[64]; string enc="";
	sprintf(buf,"%-12s",""); enc+=buf;
	for (int j=0;j<cant;j++) {
		string n=g.getCiudad(j)->get_Nombre();
		if (n.size()>9) n=n.substr(0,9);
		sprintf(buf," %9s",n.c_str()); enc+=buf;
	}
	memoResultados->Lines->Add(enc.c_str());
	for (int i=0;i<cant;i++) {
		string fila="",nf=g.getCiudad(i)->get_Nombre();
		if (nf.size()>11) nf=nf.substr(0,11);
		sprintf(buf,"%-12s",nf.c_str()); fila+=buf;
		for (int j=0;j<cant;j++) {
			float val=(i==j)?0:g.getMatriz(i,j);
			if (val>=999999) sprintf(buf," %9s","INF");
			else sprintf(buf," %9.0f",val);
			fila+=buf;
		}
		memoResultados->Lines->Add(fila.c_str());
	}
	memoResultados->Lines->Add("---");
}

//---------------------------------------------------------------------------
void __fastcall TForm1::btnGuardarClick(TObject *Sender) {
	g.guardarDatos("chubut.dat");
	memoResultados->Lines->Add("=== DATOS GUARDADOS ===");
	memoResultados->Lines->Add("---");
}

//---------------------------------------------------------------------------
void __fastcall TForm1::btnCargarClick(TObject *Sender) {
	mostrarCamino=false;
	g.resetear(); g.cargarDatos("chubut.dat");
	actualizarCombos(); actualizarComboDisponibles();
	actualizarComboBaja(); actualizarGrids();
	memoResultados->Lines->Add("=== DATOS CARGADOS ===");
	memoResultados->Lines->Add("---");
	dibujarMapa();
}

//---------------------------------------------------------------------------
void __fastcall TForm1::btnAgregarCiudadClick(TObject *Sender) {
	if (cboAgregar->Items->Count==0) { memoResultados->Lines->Add("No hay mas ciudades disponibles."); return; }
	int idxSel=cboAgregar->ItemIndex; if (idxSel<0) return;
	int cnt=0,idExtra=-1;
	for (int i=0;i<5;i++) {
		if (!g.existeCiudad(ciudadesExtra[i].id)) {
			if (cnt==idxSel) { idExtra=i; break; } cnt++;
		}
	}
	if (idExtra==-1) { memoResultados->Lines->Add("Error: ciudad no encontrada."); return; }
	CiudadExtra& ce=ciudadesExtra[idExtra];
	g.agregarCiudad(ce.id,ce.nombre,ce.x,ce.y);
	cargarRutasExtra(ce.id);
	mostrarCamino=false;
	memoResultados->Lines->Add(("=== CIUDAD AGREGADA: "+ce.nombre+" ===").c_str());
	memoResultados->Lines->Add("Rutas predefinidas cargadas automaticamente.");
	memoResultados->Lines->Add("---");
	escribirHistorial("CIUDAD AGREGADA: "+ce.nombre);
	actualizarCombos(); actualizarComboDisponibles();
	actualizarComboBaja(); actualizarGrids(); dibujarMapa();
}

//---------------------------------------------------------------------------
void __fastcall TForm1::btnBajaCiudadClick(TObject *Sender) {
	int indice=cboBaja->ItemIndex;
	if (indice<0||indice>=g.getCantCiudades()) { memoResultados->Lines->Add("Error: seleccione una ciudad valida."); return; }
	ciudad* ci=g.getCiudad(indice); if (ci==NULL) return;
	string nombreCiudad=ci->get_Nombre(); int idCiudad=ci->get_id();
	AnsiString msg="Dar de baja: "+AnsiString(nombreCiudad.c_str())+
				   "\nEsto eliminara la ciudad y todas sus rutas asociadas.\n\nConfirmar?";
	if (MessageBox(Handle,UnicodeString(msg).c_str(),L"Confirmar baja",MB_YESNO|MB_ICONWARNING)!=IDYES) return;
	mostrarCamino=false;
	g.eliminarCiudad(idCiudad);
	memoResultados->Lines->Add(("=== CIUDAD DADA DE BAJA: "+nombreCiudad+" ===").c_str());
	memoResultados->Lines->Add("Todas sus rutas asociadas fueron eliminadas.");
	memoResultados->Lines->Add("---");
	escribirHistorial("CIUDAD DADA DE BAJA: "+nombreCiudad);
	actualizarCombos(); actualizarComboDisponibles();
	actualizarComboBaja(); actualizarGrids(); dibujarMapa();
}
//---------------------------------------------------------------------------

