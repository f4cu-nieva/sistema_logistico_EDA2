object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 814
  ClientWidth = 670
  Color = clInactiveCaptionText
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Label1: TLabel
    Left = 158
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
  object Label2: TLabel
    Left = 32
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
    Left = 32
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
  object imgMapa: TImage
    Left = 33
    Top = 397
    Width = 560
    Height = 276
    Center = True
    Proportional = True
    Stretch = True
  end
  object cboOrigen: TComboBox
    Left = 93
    Top = 65
    Width = 500
    Height = 23
    Color = clWhitesmoke
    TabOrder = 0
    Text = 'cboOrigen'
  end
  object cboDestino: TComboBox
    Left = 96
    Top = 105
    Width = 497
    Height = 23
    TabOrder = 1
    Text = 'cboDestino'
  end
  object memoResultados: TMemo
    Left = 32
    Top = 150
    Width = 561
    Height = 241
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
    Left = 15
    Top = 704
    Width = 75
    Height = 25
    Caption = 'Calcular Ruta'
    TabOrder = 3
    OnClick = btnCalcularClick
  end
  object btnCortar: TButton
    Left = 136
    Top = 704
    Width = 75
    Height = 25
    Caption = 'Cortar Ruta'
    TabOrder = 4
    OnClick = btnCortarClick
  end
  object btnHabilitar: TButton
    Left = 248
    Top = 704
    Width = 75
    Height = 25
    Caption = 'Habilitar Ruta'
    TabOrder = 5
    OnClick = btnHabilitarClick
  end
  object btnMatriz: TButton
    Left = 352
    Top = 704
    Width = 75
    Height = 25
    Caption = 'Ver Matriz'
    TabOrder = 6
    OnClick = btnMatrizClick
  end
  object btnGuardar: TButton
    Left = 456
    Top = 704
    Width = 75
    Height = 25
    Caption = 'Guardar'
    TabOrder = 7
    OnClick = btnGuardarClick
  end
  object btnCargar: TButton
    Left = 560
    Top = 704
    Width = 75
    Height = 25
    Caption = 'Cargar'
    TabOrder = 8
    OnClick = btnCargarClick
  end
end
