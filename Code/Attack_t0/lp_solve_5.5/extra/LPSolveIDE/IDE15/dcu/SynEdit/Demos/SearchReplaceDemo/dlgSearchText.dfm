object TextSearchDialog: TTextSearchDialog
  Left = 132
  Top = 168
  BorderStyle = bsDialog
  Caption = 'Search Text'
  ClientHeight = 277
  ClientWidth = 511
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -17
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCloseQuery = FormCloseQuery
  PixelsPerInch = 144
  TextHeight = 20
  object Label1: TLabel
    Left = 12
    Top = 18
    Width = 82
    Height = 20
    Caption = '&Search for:'
  end
  object cbSearchText: TComboBox
    Left = 148
    Top = 12
    Width = 350
    Height = 28
    ItemHeight = 20
    TabOrder = 0
  end
  object gbSearchOptions: TGroupBox
    Left = 12
    Top = 62
    Width = 237
    Height = 195
    Caption = 'Options'
    TabOrder = 1
    object cbSearchCaseSensitive: TCheckBox
      Left = 12
      Top = 26
      Width = 216
      Height = 26
      Caption = 'C&ase sensitivity'
      TabOrder = 0
    end
    object cbSearchWholeWords: TCheckBox
      Left = 12
      Top = 60
      Width = 216
      Height = 26
      Caption = '&Whole words only'
      TabOrder = 1
    end
    object cbSearchFromCursor: TCheckBox
      Left = 12
      Top = 94
      Width = 216
      Height = 26
      Caption = 'Search from &caret'
      TabOrder = 2
    end
    object cbSearchSelectedOnly: TCheckBox
      Left = 12
      Top = 128
      Width = 216
      Height = 26
      Caption = '&Selected text only'
      TabOrder = 3
    end
    object cbRegularExpression: TCheckBox
      Left = 12
      Top = 160
      Width = 216
      Height = 26
      Caption = '&Regular expression'
      TabOrder = 4
    end
  end
  object rgSearchDirection: TRadioGroup
    Left = 262
    Top = 62
    Width = 236
    Height = 100
    Caption = 'Direction'
    ItemIndex = 0
    Items.Strings = (
      '&Forward'
      '&Backward')
    TabOrder = 2
  end
  object btnOK: TButton
    Left = 262
    Top = 229
    Width = 115
    Height = 36
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 3
  end
  object btnCancel: TButton
    Left = 383
    Top = 229
    Width = 115
    Height = 36
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 4
  end
end
