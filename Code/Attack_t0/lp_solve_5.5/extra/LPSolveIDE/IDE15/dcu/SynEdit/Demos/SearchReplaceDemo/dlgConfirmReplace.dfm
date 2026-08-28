object ConfirmReplaceDialog: TConfirmReplaceDialog
  Left = 176
  Top = 158
  BorderStyle = bsDialog
  Caption = 'Confirm replace'
  ClientHeight = 151
  ClientWidth = 505
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -17
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 144
  TextHeight = 20
  object lblConfirmation: TLabel
    Left = 92
    Top = 18
    Width = 402
    Height = 68
    AutoSize = False
    WordWrap = True
  end
  object Image1: TImage
    Left = 25
    Top = 25
    Width = 49
    Height = 49
  end
  object btnReplace: TButton
    Left = 12
    Top = 103
    Width = 116
    Height = 35
    Caption = '&Yes'
    Default = True
    ModalResult = 6
    TabOrder = 0
  end
  object btnSkip: TButton
    Left = 134
    Top = 103
    Width = 115
    Height = 35
    Caption = '&No'
    ModalResult = 7
    TabOrder = 1
  end
  object btnCancel: TButton
    Left = 255
    Top = 103
    Width = 116
    Height = 35
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
  object btnReplaceAll: TButton
    Left = 377
    Top = 103
    Width = 115
    Height = 35
    Caption = 'Yes to &all'
    ModalResult = 10
    TabOrder = 3
  end
end
