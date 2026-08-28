object GotoLineForm: TGotoLineForm
  Left = 628
  Top = 163
  ActiveControl = LineNumer
  BorderStyle = bsDialog
  Caption = 'Goto line number'
  ClientHeight = 145
  ClientWidth = 506
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -17
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  OnCreate = FormCreate
  PixelsPerInch = 144
  TextHeight = 20
  object Label1: TLabel
    Left = 37
    Top = 37
    Width = 164
    Height = 20
    Caption = 'Enter new line number'
  end
  object Button1: TButton
    Left = 37
    Top = 98
    Width = 115
    Height = 39
    Caption = 'OK'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 357
    Top = 98
    Width = 115
    Height = 39
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object LineNumer: TEdit
    Left = 283
    Top = 37
    Width = 186
    Height = 28
    TabOrder = 2
    Text = '0'
    OnKeyPress = LineNumerKeyPress
  end
end
