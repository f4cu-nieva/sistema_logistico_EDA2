object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 814
  ClientWidth = 1120
  Color = clInactiveCaptionText
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnShow = cboOrigenChange
  TextHeight = 15
  object Label1: TLabel
    Left = 366
    Top = 16
    Width = 333
    Height = 25
    Caption = 'Sistema de Gestion de Rutas - Chubut'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -19
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
  end
  object imgMapa: TImage
    Left = 8
    Top = 134
    Width = 601
    Height = 378
    Center = True
    Proportional = True
    Stretch = True
  end
  object lblCiudadAgregar: TLabel
    Left = 520
    Top = 66
    Width = 106
    Height = 17
    Caption = 'Ciudad a agregar:'
    Color = clCadetblue
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clSeagreen
    Font.Height = -13
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentColor = False
    ParentFont = False
  end
  object Label4: TLabel
    Left = 520
    Top = 108
    Width = 114
    Height = 15
    Caption = 'Ciuadad a dar de baja'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clSeagreen
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 270
    Top = 549
    Width = 80
    Height = 28
    Caption = 'Ciudades'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clSeagreen
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object Label6: TLabel
    Left = 825
    Top = 549
    Width = 48
    Height = 28
    Caption = 'Rutas'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clSeagreen
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 136
    Top = 64
    Width = 55
    Height = 20
    Caption = 'Origen: '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -15
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 133
    Top = 104
    Width = 58
    Height = 20
    Caption = 'Destino:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -15
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object cboOrigen: TComboBox
    Left = 197
    Top = 65
    Width = 289
    Height = 23
    Color = clWhitesmoke
    TabOrder = 0
    Text = 'cboOrigen'
    OnChange = cboOrigenChange
  end
  object cboDestino: TComboBox
    Left = 197
    Top = 105
    Width = 289
    Height = 23
    TabOrder = 1
    Text = 'cboDestino'
  end
  object memoResultados: TMemo
    Left = 615
    Top = 134
    Width = 484
    Height = 378
    Color = clDarkgreen
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWhite
    Font.Height = -15
    Font.Name = 'Segoe UI'
    Font.Style = []
    Lines.Strings = (
      'memoResultados')
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 2
  end
  object btnCalcular: TButton
    Left = 165
    Top = 518
    Width = 75
    Height = 25
    Caption = 'Calcular Ruta'
    TabOrder = 3
    OnClick = btnCalcularClick
  end
  object btnCortar: TButton
    Left = 275
    Top = 518
    Width = 75
    Height = 25
    Caption = 'Cortar Ruta'
    TabOrder = 4
    OnClick = btnCortarClick
  end
  object btnHabilitar: TButton
    Left = 387
    Top = 518
    Width = 75
    Height = 25
    Caption = 'Habilitar Ruta'
    TabOrder = 5
    OnClick = btnHabilitarClick
  end
  object btnMatriz: TButton
    Left = 734
    Top = 518
    Width = 75
    Height = 25
    Caption = 'Ver Matriz'
    TabOrder = 6
    OnClick = btnMatrizClick
  end
  object btnGuardar: TButton
    Left = 854
    Top = 518
    Width = 75
    Height = 25
    Caption = 'Guardar'
    TabOrder = 7
    OnClick = btnGuardarClick
  end
  object btnCargar: TButton
    Left = 974
    Top = 518
    Width = 75
    Height = 25
    Caption = 'Cargar'
    TabOrder = 8
    OnClick = btnCargarClick
  end
  object cboAgregar: TComboBox
    Left = 640
    Top = 65
    Width = 289
    Height = 23
    Style = csDropDownList
    TabOrder = 9
  end
  object btnAgregarCiudad: TButton
    Left = 944
    Top = 64
    Width = 105
    Height = 25
    Caption = 'Agregar Ciudad'
    TabOrder = 10
    OnClick = btnAgregarCiudadClick
  end
  object btnBajaCiudad: TButton
    Left = 944
    Top = 104
    Width = 75
    Height = 25
    Caption = 'Dar de Baja'
    TabOrder = 11
    OnClick = btnBajaCiudadClick
  end
  object cboBaja: TComboBox
    Left = 640
    Top = 105
    Width = 289
    Height = 23
    TabOrder = 12
    Text = 'cboBaja'
  end
  object gridCiudades: TStringGrid
    Left = 173
    Top = 583
    Width = 265
    Height = 211
    ColCount = 4
    FixedCols = 0
    RowCount = 2
    TabOrder = 13
  end
  object gridRutas: TStringGrid
    Left = 696
    Top = 583
    Width = 294
    Height = 211
    ColCount = 4
    FixedCols = 0
    RowCount = 2
    TabOrder = 14
  end
end
