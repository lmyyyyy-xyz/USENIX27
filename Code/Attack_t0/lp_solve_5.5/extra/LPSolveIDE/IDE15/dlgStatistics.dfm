object StatisticsForm: TStatisticsForm
  Left = 311
  Top = 171
  BorderIcons = [biSystemMenu]
  Caption = 'Statistics'
  ClientHeight = 322
  ClientWidth = 657
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCreate = FormCreate
  DesignSize = (
    657
    322)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 158
    Width = 35
    Height = 13
    Caption = 'Scaling'
  end
  object Label2: TLabel
    Left = 8
    Top = 0
    Width = 37
    Height = 13
    Caption = 'General'
  end
  object Button1: TButton
    Left = 574
    Top = 289
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = '&OK'
    ModalResult = 1
    TabOrder = 0
  end
  object Stats: TListView
    Left = 8
    Top = 16
    Width = 336
    Height = 136
    Columns = <
      item
        AutoSize = True
      end
      item
        AutoSize = True
        Caption = 'Value'
      end>
    ReadOnly = True
    TabOrder = 1
    ViewStyle = vsReport
  end
  object Stats2: TListView
    Left = 8
    Top = 177
    Width = 641
    Height = 96
    Anchors = [akLeft, akTop, akRight]
    Columns = <
      item
        AutoSize = True
      end
      item
        AutoSize = True
        Caption = 'Name'
      end
      item
        AutoSize = True
        Caption = 'Min'
      end
      item
        AutoSize = True
        Caption = 'Name'
      end
      item
        AutoSize = True
        Caption = 'Max'
      end
      item
        Width = 3
      end>
    ReadOnly = True
    TabOrder = 2
    ViewStyle = vsReport
  end
end
