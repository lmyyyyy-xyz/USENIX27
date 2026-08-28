inherited TextReplaceDialog: TTextReplaceDialog
  Caption = 'Replace text'
  ClientHeight = 323
  OldCreateOrder = True
  PixelsPerInch = 144
  TextHeight = 20
  object Label2: TLabel [1]
    Left = 12
    Top = 63
    Width = 100
    Height = 20
    Caption = '&Replace with:'
  end
  inherited gbSearchOptions: TGroupBox
    Top = 108
    TabOrder = 2
    ExplicitTop = 108
  end
  inherited rgSearchDirection: TRadioGroup
    Top = 108
    TabOrder = 3
    ExplicitTop = 108
  end
  inherited btnOK: TButton
    Top = 275
    TabOrder = 4
    ExplicitTop = 275
  end
  inherited btnCancel: TButton
    Top = 275
    TabOrder = 5
    ExplicitTop = 275
  end
  object cbReplaceText: TComboBox
    Left = 148
    Top = 57
    Width = 350
    Height = 28
    ItemHeight = 20
    TabOrder = 1
  end
end
