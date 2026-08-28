object AboutForm: TAboutForm
  Left = 373
  Top = 175
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'About'
  ClientHeight = 337
  ClientWidth = 330
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label10: TLabel
    Left = 51
    Top = 16
    Width = 194
    Height = 24
    Caption = 'LPSolve IDE v5.5.2.14'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Button1: TButton
    Left = 128
    Top = 300
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 0
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 205
    Width = 297
    Height = 82
    Caption = 'Third party components'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    object Label7: TLabel
      Left = 16
      Top = 24
      Width = 36
      Height = 13
      Caption = 'SynEdit'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label8: TLabel
      Left = 16
      Top = 40
      Width = 74
      Height = 13
      Caption = 'VirtualTreeView'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label9: TLabel
      Left = 16
      Top = 56
      Width = 41
      Height = 13
      Caption = 'XPMenu'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label6: TLabel
      Left = 120
      Top = 24
      Width = 141
      Height = 13
      Cursor = crHandPoint
      Caption = 'http://synedit.sourceforge.net'
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsUnderline]
      ParentColor = False
      ParentFont = False
      OnClick = URLClick
    end
    object Label13: TLabel
      Left = 120
      Top = 40
      Width = 137
      Height = 13
      Cursor = crHandPoint
      Caption = 'http://www.delphi-gems.com'
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsUnderline]
      ParentColor = False
      ParentFont = False
      OnClick = URLClick
    end
    object Label14: TLabel
      Left = 120
      Top = 56
      Width = 127
      Height = 13
      Cursor = crHandPoint
      Caption = 'http://www.shagrouni.com'
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsUnderline]
      ParentColor = False
      ParentFont = False
      OnClick = URLClick
    end
  end
  object GroupBox2: TGroupBox
    Left = 16
    Top = 109
    Width = 297
    Height = 93
    Caption = 'lp_solve'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    object Label2: TLabel
      Left = 16
      Top = 51
      Width = 79
      Height = 13
      Caption = 'Michel Berkelaar'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 16
      Top = 66
      Width = 59
      Height = 13
      Caption = 'Jeroen Dirks'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel
      Left = 120
      Top = 51
      Width = 57
      Height = 13
      Caption = 'Kjell Eikland'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label5: TLabel
      Left = 120
      Top = 66
      Width = 75
      Height = 13
      Caption = 'Peter Notebaert'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label16: TLabel
      Left = 15
      Top = 34
      Width = 251
      Height = 13
      Cursor = crHandPoint
      Caption = 'https://github.com/lp-solve/lp_solve'
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsUnderline]
      ParentColor = False
      ParentFont = False
      OnClick = URLClick
    end
    object Label12: TLabel
      Left = 15
      Top = 17
      Width = 194
      Height = 13
      Cursor = crHandPoint
      Caption = 'https://groups.google.com/g/lp_solve'
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsUnderline]
      ParentColor = False
      ParentFont = False
      OnClick = URLClick
    end
  end
  object GroupBox3: TGroupBox
    Left = 16
    Top = 48
    Width = 297
    Height = 57
    Caption = 'Authors'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    object Label11: TLabel
      Left = 12
      Top = 21
      Width = 228
      Height = 13
      Caption = 'Henri Gourvest, William Pattton, Peter Notebaert'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label17: TLabel
      Left = 48
      Top = 32
      Width = 3
      Height = 13
      Cursor = crHandPoint
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsUnderline]
      ParentColor = False
      ParentFont = False
      OnClick = URLClick
    end
    object Label18: TLabel
      Left = 8
      Top = 32
      Width = 5
      Height = 13
    end
  end
end
