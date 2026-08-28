object ParamForm: TParamForm
  Left = 397
  Top = 450
  BorderStyle = bsDialog
  Caption = 'LP parameters'
  ClientHeight = 198
  ClientWidth = 675
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -17
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCreate = FormCreate
  PixelsPerInch = 144
  TextHeight = 20
  object Label1: TLabel
    Left = 12
    Top = 12
    Width = 77
    Height = 20
    Caption = 'File name:'
  end
  object Label2: TLabel
    Left = 12
    Top = 74
    Width = 98
    Height = 20
    Caption = 'Profile name:'
  end
  object FileName: TEdit
    Left = 12
    Top = 37
    Width = 593
    Height = 28
    TabOrder = 0
  end
  object Button1: TButton
    Left = 603
    Top = 37
    Width = 39
    Height = 32
    Caption = '...'
    TabOrder = 1
    OnClick = Button1Click
  end
  object ProfilName: TComboBox
    Left = 12
    Top = 98
    Width = 223
    Height = 28
    ItemHeight = 20
    TabOrder = 2
    OnDropDown = ProfilNameDropDown
  end
  object Button2: TButton
    Left = 12
    Top = 148
    Width = 116
    Height = 38
    Hint = 'Read solver options from file'
    Caption = '&Read'
    ModalResult = 1
    TabOrder = 3
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 140
    Top = 148
    Width = 116
    Height = 38
    Hint = 'Write current solver options to file'
    Caption = '&Write'
    ModalResult = 1
    TabOrder = 4
    OnClick = Button3Click
  end
  object Button5: TButton
    Left = 542
    Top = 148
    Width = 115
    Height = 38
    Caption = '&Cancel'
    ModalResult = 2
    TabOrder = 5
  end
  object OpenDialog: TOpenDialog
    Filter = 'Params file (*.lpi)|*.lpi'
    Left = 568
    Top = 72
  end
end
