object MainForm: TMainForm
  Left = 231
  Top = 251
  ActiveControl = Editor
  BorderIcons = [biSystemMenu, biMinimize, biMaximize, biHelp]
  Caption = 'LPSolve 5 IDE'
  ClientHeight = 1030
  ClientWidth = 1200
  Color = clBtnFace
  TransparentColorValue = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -17
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 144
  TextHeight = 20
  object Splitter1: TSplitter
    Left = 0
    Top = 517
    Width = 1025
    Height = 5
    Cursor = crVSplit
    Align = alBottom
    ExplicitTop = 333
    ExplicitWidth = 828
  end
  object PageControl: TPageControl
    Left = 0
    Top = 29
    Width = 1025
    Height = 488
    ActivePage = TabSheetEditor
    Align = alClient
    Images = ImageList
    TabOrder = 0
    object TabSheetEditor: TTabSheet
      Caption = 'Source'
      ImageIndex = 26
      object Editor: TLPSynedit
        Left = 0
        Top = 0
        Width = 1017
        Height = 453
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -22
        Font.Name = 'Courier New'
        Font.Style = []
        PopupMenu = PopupMenu
        TabOrder = 0
        Gutter.DigitCount = 2
        Gutter.Font.Charset = DEFAULT_CHARSET
        Gutter.Font.Color = clWindowText
        Gutter.Font.Height = -11
        Gutter.Font.Name = 'Courier New'
        Gutter.Font.Style = []
        Gutter.LeftOffset = 6
        Gutter.RightOffset = 5
        Gutter.ShowLineNumbers = True
        MaxScrollWidth = 1
        Options = [eoAutoIndent, eoAutoSizeMaxScrollWidth, eoDragDropEditing, eoDropFiles, eoGroupUndo, eoHideShowScrollbars, eoRightMouseMovesCursor, eoScrollPastEol, eoShowScrollHint, eoSmartTabDelete, eoSmartTabs, eoTabsToSpaces, eoTrimTrailingSpaces]
        RightEdge = 255
        WantTabs = True
        OnDropFiles = EditorDropFiles
        OnReplaceText = EditorReplaceText
        OnStatusChange = EditorStatusChange
        EnableMPS = False
      end
    end
    object Matrix: TTabSheet
      Caption = 'Matrix'
      ImageIndex = 27
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object MatrixTable: TVirtualStringTree
        Left = 0
        Top = 0
        Width = 1017
        Height = 333
        Align = alClient
        Header.AutoSizeIndex = -1
        Header.Font.Charset = DEFAULT_CHARSET
        Header.Font.Color = clWindowText
        Header.Font.Height = -11
        Header.Font.Name = 'MS Sans Serif'
        Header.Font.Style = []
        Header.MainColumn = -1
        Header.Options = [hoColumnResize, hoDblClickResize, hoDrag, hoHotTrack, hoShowHint, hoShowSortGlyphs, hoVisible]
        Header.SortDirection = sdDescending
        Header.Style = hsPlates
        NodeDataSize = 4
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        TreeOptions.AnimationOptions = [toAnimatedToggle]
        TreeOptions.AutoOptions = [toAutoDropExpand, toAutoScroll, toAutoScrollOnExpand, toAutoTristateTracking]
        TreeOptions.MiscOptions = [toAcceptOLEDrop, toCheckSupport, toGridExtensions, toInitOnSave, toReportMode, toToggleOnDblClick, toWheelPanning]
        TreeOptions.PaintOptions = [toShowButtons, toShowDropmark, toShowHorzGridLines, toShowRoot, toShowVertGridLines, toThemeAware, toUseBlendedSelection]
        TreeOptions.SelectionOptions = [toExtendedFocus]
        OnBeforeCellPaint = MatrixTableBeforeCellPaint
        OnCompareNodes = MatrixTableCompareNodes
        OnGetText = MatrixTableGetText
        OnHeaderClick = MatrixTableHeaderClick
        OnInitNode = MatrixTableInitNode
        Columns = <>
      end
    end
    object TabSheetOptions: TTabSheet
      Caption = 'Options'
      ImageIndex = 25
      object pcOptions: TPageControl
        Left = 0
        Top = 0
        Width = 1017
        Height = 453
        ActivePage = tsOptions
        Align = alClient
        TabOrder = 0
        object tsOptions: TTabSheet
          Caption = 'Options'
          ImageIndex = 1
          object BBRuleModeOptions: TGroupBox
            Left = 578
            Top = 12
            Width = 445
            Height = 470
            Caption = 'Branch Bound'
            TabOrder = 0
            object Label1: TLabel
              Left = 222
              Top = 123
              Width = 113
              Height = 20
              Caption = 'BB Rule Select'
            end
            object Label2: TLabel
              Left = 12
              Top = 25
              Width = 104
              Height = 20
              Caption = 'BB Floor First'
            end
            object Label4: TLabel
              Left = 222
              Top = 197
              Width = 86
              Height = 20
              Caption = 'Depth Limit'
            end
            object Label15: TLabel
              Left = 222
              Top = 271
              Width = 78
              Height = 20
              Caption = 'Obj Bound'
            end
            object CheckBox9: TCheckBox
              Left = 37
              Top = 123
              Width = 149
              Height = 26
              Caption = 'Weight Reverse'
              TabOrder = 0
              OnClick = OptionCheckBoxClick
            end
            object CheckBox10: TCheckBox
              Tag = 1
              Left = 37
              Top = 148
              Width = 149
              Height = 26
              Caption = 'Branch Reverse'
              TabOrder = 1
              OnClick = OptionCheckBoxClick
            end
            object CheckBox11: TCheckBox
              Tag = 2
              Left = 37
              Top = 172
              Width = 149
              Height = 26
              Caption = 'Greedy'
              TabOrder = 2
              OnClick = OptionCheckBoxClick
            end
            object CheckBox12: TCheckBox
              Tag = 3
              Left = 37
              Top = 197
              Width = 149
              Height = 26
              Caption = 'Pseudo Cost'
              TabOrder = 3
              OnClick = OptionCheckBoxClick
            end
            object CheckBox13: TCheckBox
              Tag = 4
              Left = 37
              Top = 222
              Width = 149
              Height = 26
              Caption = 'Depth First'
              TabOrder = 4
              OnClick = OptionCheckBoxClick
            end
            object CheckBox14: TCheckBox
              Tag = 5
              Left = 37
              Top = 246
              Width = 149
              Height = 26
              Caption = 'Randomize'
              TabOrder = 5
              OnClick = OptionCheckBoxClick
            end
            object CheckBox15: TCheckBox
              Tag = 6
              Left = 37
              Top = 271
              Width = 149
              Height = 26
              Caption = 'Gub'
              TabOrder = 6
              OnClick = OptionCheckBoxClick
            end
            object CheckBox16: TCheckBox
              Tag = 7
              Left = 37
              Top = 295
              Width = 149
              Height = 27
              Caption = 'Dynamic'
              TabOrder = 7
              OnClick = OptionCheckBoxClick
            end
            object CheckBox17: TCheckBox
              Tag = 8
              Left = 37
              Top = 320
              Width = 149
              Height = 26
              Caption = 'Restart'
              TabOrder = 8
              OnClick = OptionCheckBoxClick
            end
            object CheckBox58: TCheckBox
              Tag = 9
              Left = 37
              Top = 345
              Width = 149
              Height = 26
              Caption = 'Breadth First'
              TabOrder = 9
              OnClick = OptionCheckBoxClick
            end
            object CheckBox60: TCheckBox
              Tag = 10
              Left = 37
              Top = 369
              Width = 149
              Height = 26
              Caption = 'AutoOrder'
              TabOrder = 10
              OnClick = OptionCheckBoxClick
            end
            object CheckBox68: TCheckBox
              Tag = 11
              Left = 37
              Top = 394
              Width = 149
              Height = 26
              Caption = 'RCostFixing'
              TabOrder = 11
              OnClick = OptionCheckBoxClick
            end
            object CheckBox69: TCheckBox
              Tag = 12
              Left = 37
              Top = 418
              Width = 149
              Height = 27
              Caption = 'StrongInit'
              TabOrder = 12
              OnClick = OptionCheckBoxClick
            end
            object BBRuleSelectOption: TComboBox
              Left = 246
              Top = 148
              Width = 186
              Height = 28
              Hint = 'Select lowest indexed non-integer column'
              Style = csDropDownList
              ItemHeight = 20
              ItemIndex = 0
              ParentShowHint = False
              ShowHint = True
              TabOrder = 13
              Text = 'First'
              OnChange = BBRuleSelectOptionChange
              OnClick = OptionCheckBoxClick
              Items.Strings = (
                'First'
                'Gap'
                'Range'
                'Fraction'
                'Pseudo Cost'
                'Pseudo Non Int'
                'Pseudo Ratio'
                'User')
            end
            object BBFloorFirstOption: TComboBox
              Left = 37
              Top = 49
              Width = 186
              Height = 28
              Hint = 'Take floor branch first'
              Style = csDropDownList
              ItemHeight = 20
              ItemIndex = 1
              ParentShowHint = False
              ShowHint = True
              TabOrder = 14
              Text = 'Floor'
              OnChange = BBFloorFirstOptionChange
              OnClick = OptionCheckBoxClick
              Items.Strings = (
                'Ceiling'
                'Floor'
                'Automatic'
                'Default')
            end
            object DepthLimitOption: TEdit
              Left = 246
              Top = 222
              Width = 186
              Height = 28
              Hint = 'Sets the maximum branch-and-bound depth.'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 15
              Text = '-50'
              OnExit = OptionCheckBoxClick
              OnKeyPress = EditOptionChange
            end
            object ObjBoundOption: TEdit
              Left = 246
              Top = 295
              Width = 186
              Height = 28
              Hint = 'Set initial "at least better than" guess for objective function.'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 16
              OnExit = OptionCheckBoxClick
              OnKeyPress = EditOptionChange
            end
          end
          object ScaleOptions: TGroupBox
            Left = 12
            Top = 12
            Width = 248
            Height = 470
            Caption = 'Scale'
            TabOrder = 1
            object Label9: TLabel
              Left = 12
              Top = 31
              Width = 82
              Height = 20
              Caption = 'Scale Type'
            end
            object Label5: TLabel
              Left = 12
              Top = 111
              Width = 87
              Height = 20
              Caption = 'Scale Mode'
            end
            object Label22: TLabel
              Left = 9
              Top = 345
              Width = 83
              Height = 20
              Caption = 'Scale Limit'
            end
            object CheckBox51: TCheckBox
              Tag = 4
              Left = 37
              Top = 234
              Width = 112
              Height = 26
              Hint = 'also scaling integer variables'
              HelpContext = 3
              Caption = 'Integers'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 4
              OnClick = OptionCheckBoxClick
            end
            object CheckBox50: TCheckBox
              Tag = 3
              Left = 37
              Top = 209
              Width = 112
              Height = 26
              Hint = 'Make sure that no scaled number is above 1'
              HelpContext = 3
              Caption = 'Equilibrate'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 3
              OnClick = OptionCheckBoxClick
            end
            object CheckBox49: TCheckBox
              Tag = 2
              Left = 37
              Top = 185
              Width = 112
              Height = 26
              Hint = 'also do Power scaling'
              HelpContext = 3
              Caption = 'Power2'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 2
              OnClick = OptionCheckBoxClick
            end
            object CheckBox48: TCheckBox
              Tag = 1
              Left = 37
              Top = 160
              Width = 112
              Height = 26
              Hint = 'Scale to convergence using logarithmic mean of all values'
              HelpContext = 3
              Caption = 'Logarithmic'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 1
              OnClick = OptionCheckBoxClick
            end
            object CheckBox47: TCheckBox
              Left = 37
              Top = 135
              Width = 112
              Height = 27
              HelpContext = 3
              Caption = 'Quadratic'
              TabOrder = 0
              OnClick = OptionCheckBoxClick
            end
            object ScaleTypeOption: TComboBox
              Left = 37
              Top = 57
              Width = 133
              Height = 28
              Hint = 'Linear scaling'
              HelpContext = 3
              Style = csDropDownList
              ItemHeight = 20
              ItemIndex = 0
              ParentShowHint = False
              ShowHint = True
              TabOrder = 8
              Text = 'None (Linear)'
              OnChange = ScaleTypeOptionChange
              OnClick = OptionCheckBoxClick
              Items.Strings = (
                'None (Linear)'
                'Extreme'
                'Range'
                'Mean'
                'Geometric'
                'Future1'
                'Future2'
                'CurtisreId')
            end
            object CheckBox59: TCheckBox
              Tag = 5
              Left = 37
              Top = 258
              Width = 112
              Height = 27
              Hint = 'also scaling integer variables'
              HelpContext = 3
              Caption = 'DynUpdate'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 5
              OnClick = OptionCheckBoxClick
            end
            object CheckBox70: TCheckBox
              Tag = 6
              Left = 37
              Top = 283
              Width = 112
              Height = 26
              HelpContext = 3
              Caption = 'RowsOnly'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 6
              OnClick = OptionCheckBoxClick
            end
            object CheckBox71: TCheckBox
              Tag = 7
              Left = 37
              Top = 308
              Width = 112
              Height = 26
              HelpContext = 3
              Caption = 'ColsOnly'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 7
              OnClick = OptionCheckBoxClick
            end
            object ScaleLimitOption: TEdit
              Left = 37
              Top = 369
              Width = 186
              Height = 28
              Hint =
                'Sets the relative scaling convergence criterion for the active s' +
                'caling mode; the integer part specifies the maximum number of it' +
                'erations.'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 9
              OnExit = OptionCheckBoxClick
              OnKeyPress = EditOptionChange
            end
          end
          object PivotModeOption: TGroupBox
            Left = 271
            Top = 12
            Width = 297
            Height = 470
            Caption = 'Pivot'
            TabOrder = 2
            object Label6: TLabel
              Left = 15
              Top = 406
              Width = 72
              Height = 20
              Caption = 'Max Pivot'
            end
            object Label7: TLabel
              Left = 12
              Top = 25
              Width = 75
              Height = 20
              Caption = 'Pivot Rule'
            end
            object CheckBox32: TCheckBox
              Left = 37
              Top = 98
              Width = 149
              Height = 27
              Hint = 'In case of Steepest Edge, fall back to DEVEX in primal'
              Caption = 'Primal Fall Back'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 0
              OnClick = OptionCheckBoxClick
            end
            object CheckBox33: TCheckBox
              Tag = 1
              Left = 37
              Top = 123
              Width = 149
              Height = 26
              Hint = 'Enable multiple pricing'
              Caption = 'Multiple'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 1
              OnClick = OptionCheckBoxClick
            end
            object CheckBox34: TCheckBox
              Tag = 2
              Left = 37
              Top = 148
              Width = 149
              Height = 26
              Hint = 'Enable partial pricing'
              Caption = 'Partial'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 2
              OnClick = OptionCheckBoxClick
            end
            object CheckBox35: TCheckBox
              Tag = 3
              Left = 37
              Top = 172
              Width = 149
              Height = 26
              Hint = 'Temporarily use First Index if cycling is detected '
              Caption = 'Adaptive'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 3
              OnClick = OptionCheckBoxClick
            end
            object CheckBox36: TCheckBox
              Tag = 4
              Left = 37
              Top = 197
              Width = 149
              Height = 26
              Caption = 'Hybrid'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 4
              OnClick = OptionCheckBoxClick
            end
            object CheckBox37: TCheckBox
              Tag = 5
              Left = 37
              Top = 222
              Width = 149
              Height = 26
              Hint = 'Adds a small randomization effect to the selected pricer'
              Caption = 'Randomize'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 5
              OnClick = OptionCheckBoxClick
            end
            object CheckBox52: TCheckBox
              Tag = 6
              Left = 37
              Top = 246
              Width = 149
              Height = 26
              Hint = 'Detect and use data on the block structure of the model'
              Caption = 'AutoPartialCols'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 6
              OnClick = OptionCheckBoxClick
            end
            object CheckBox53: TCheckBox
              Tag = 7
              Left = 37
              Top = 271
              Width = 149
              Height = 26
              Hint = 'Detect and use data on the block structure of the model'
              Caption = 'AutoPartialRows'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 7
              OnClick = OptionCheckBoxClick
            end
            object CheckBox54: TCheckBox
              Tag = 8
              Left = 37
              Top = 295
              Width = 149
              Height = 27
              Hint = 'Scan entering/leaving columns left rather than right'
              Caption = 'LoopLeft'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 8
              OnClick = OptionCheckBoxClick
            end
            object CheckBox55: TCheckBox
              Tag = 9
              Left = 37
              Top = 320
              Width = 149
              Height = 26
              Hint = 'Scan entering/leaving columns alternatingly left/right'
              Caption = 'LoopAlternate'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 9
              OnClick = OptionCheckBoxClick
            end
            object CheckBox56: TCheckBox
              Tag = 10
              Left = 37
              Top = 345
              Width = 149
              Height = 26
              Caption = 'HarrisTwoPass'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 10
              OnClick = OptionCheckBoxClick
            end
            object MaxPivotOption: TEdit
              Left = 37
              Top = 431
              Width = 186
              Height = 28
              Hint =
                'Sets the maximum number of pivots between a re-inversion of the ' +
                'matrix'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 11
              Text = '42'
              OnExit = OptionCheckBoxClick
              OnKeyPress = EditOptionChange
            end
            object PivotRuleOption: TComboBox
              Left = 37
              Top = 49
              Width = 223
              Height = 28
              Hint = 'Devex pricing from Paula Harris'
              Style = csDropDownList
              ItemHeight = 20
              ItemIndex = 2
              ParentShowHint = False
              ShowHint = True
              TabOrder = 12
              Text = 'Devex'
              OnChange = PivotRuleOptionChange
              OnClick = OptionCheckBoxClick
              Items.Strings = (
                'First Index'
                'Dantzig'
                'Devex'
                'Steepest Edge')
            end
            object CheckBox83: TCheckBox
              Tag = 12
              Left = 37
              Top = 369
              Width = 149
              Height = 26
              Caption = 'True Norm Init'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 13
              OnClick = OptionCheckBoxClick
            end
          end
        end
        object tsGeneral: TTabSheet
          Caption = 'Advanced'
          object Label3: TLabel
            Left = 209
            Top = 345
            Width = 92
            Height = 20
            Caption = 'Basis Crash'
          end
          object Label10: TLabel
            Left = 209
            Top = 382
            Width = 99
            Height = 20
            Caption = 'Simplex Type'
          end
          object Label11: TLabel
            Left = 542
            Top = 25
            Width = 101
            Height = 20
            Caption = 'Solution Limit'
          end
          object Label13: TLabel
            Left = 542
            Top = 62
            Width = 60
            Height = 20
            Caption = 'Timeout'
          end
          object Label16: TLabel
            Left = 542
            Top = 98
            Width = 49
            Height = 20
            Caption = 'Infinite'
          end
          object Label17: TLabel
            Left = 542
            Top = 135
            Width = 45
            Height = 20
            Caption = 'EPSB'
          end
          object Label18: TLabel
            Left = 542
            Top = 172
            Width = 46
            Height = 20
            Caption = 'EPSD'
          end
          object Label19: TLabel
            Left = 542
            Top = 209
            Width = 54
            Height = 20
            Caption = 'EPSEL'
          end
          object Label20: TLabel
            Left = 542
            Top = 283
            Width = 92
            Height = 20
            Caption = 'EPS Perturb'
          end
          object Label21: TLabel
            Left = 542
            Top = 320
            Width = 74
            Height = 20
            Caption = 'EPS Pivot'
          end
          object Label23: TLabel
            Left = 898
            Top = 195
            Width = 108
            Height = 20
            Caption = 'Break at Value'
          end
          object Label24: TLabel
            Left = 542
            Top = 394
            Width = 82
            Height = 20
            Caption = 'Neg Range'
          end
          object Label12: TLabel
            Left = 542
            Top = 246
            Width = 55
            Height = 20
            Caption = 'EPS Int'
          end
          object AntiDegenOptions: TGroupBox
            Left = 345
            Top = 12
            Width = 173
            Height = 310
            Caption = 'Anti Degen'
            TabOrder = 1
            object CheckBox1: TCheckBox
              Left = 12
              Top = 25
              Width = 137
              Height = 26
              Hint =
                'Check if there are equality slacks in the basis and try to drive' +
                ' them out in order to reduce chance of degeneracy in Phase 1'
              HelpContext = 1
              Caption = 'Fixed vars'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 0
              OnClick = OptionCheckBoxClick
            end
            object CheckBox2: TCheckBox
              Tag = 1
              Left = 12
              Top = 49
              Width = 137
              Height = 26
              HelpContext = 1
              Caption = 'Column Check'
              TabOrder = 1
              OnClick = OptionCheckBoxClick
            end
            object CheckBox3: TCheckBox
              Tag = 2
              Left = 12
              Top = 74
              Width = 137
              Height = 26
              HelpContext = 1
              Caption = 'Stalling'
              TabOrder = 2
              OnClick = OptionCheckBoxClick
            end
            object CheckBox4: TCheckBox
              Tag = 3
              Left = 12
              Top = 98
              Width = 137
              Height = 27
              HelpContext = 1
              Caption = 'Num Failure'
              TabOrder = 3
              OnClick = OptionCheckBoxClick
            end
            object CheckBox5: TCheckBox
              Tag = 4
              Left = 12
              Top = 123
              Width = 137
              Height = 26
              HelpContext = 1
              Caption = 'Lost Feas'
              TabOrder = 4
              OnClick = OptionCheckBoxClick
            end
            object CheckBox6: TCheckBox
              Tag = 5
              Left = 12
              Top = 148
              Width = 137
              Height = 26
              HelpContext = 1
              Caption = 'Infeasible'
              TabOrder = 5
              OnClick = OptionCheckBoxClick
            end
            object CheckBox7: TCheckBox
              Tag = 6
              Left = 12
              Top = 172
              Width = 137
              Height = 26
              HelpContext = 1
              Caption = 'Dynamic'
              TabOrder = 6
              OnClick = OptionCheckBoxClick
            end
            object CheckBox8: TCheckBox
              Tag = 7
              Left = 12
              Top = 197
              Width = 137
              Height = 26
              HelpContext = 1
              Caption = 'DuringBB'
              TabOrder = 7
              OnClick = OptionCheckBoxClick
            end
            object CheckBox57: TCheckBox
              Tag = 8
              Left = 12
              Top = 222
              Width = 137
              Height = 26
              HelpContext = 1
              Caption = 'RhsPerturb'
              TabOrder = 8
              OnClick = OptionCheckBoxClick
            end
            object CheckBox61: TCheckBox
              Tag = 9
              Left = 12
              Top = 246
              Width = 137
              Height = 26
              HelpContext = 1
              Caption = 'BoundFlip'
              TabOrder = 9
              OnClick = OptionCheckBoxClick
            end
          end
          object PresolveOptions: TGroupBox
            Left = 0
            Top = 12
            Width = 334
            Height = 310
            Caption = 'Presolve'
            TabOrder = 0
            object CheckBox38: TCheckBox
              Left = 12
              Top = 25
              Width = 125
              Height = 26
              Hint = 'Presolve rows'
              HelpContext = 2
              Caption = 'Rows'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 0
              OnClick = OptionCheckBoxClick
            end
            object CheckBox39: TCheckBox
              Tag = 1
              Left = 12
              Top = 49
              Width = 125
              Height = 26
              Hint = 'Presolve columns'
              HelpContext = 2
              Caption = 'Cols'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 1
              OnClick = OptionCheckBoxClick
            end
            object CheckBox40: TCheckBox
              Tag = 2
              Left = 12
              Top = 74
              Width = 125
              Height = 26
              Hint = 'Eliminate linearly dependent rows'
              HelpContext = 2
              Caption = 'Lindep'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 2
              OnClick = OptionCheckBoxClick
            end
            object CheckBox41: TCheckBox
              Tag = 3
              Left = 12
              Top = 98
              Width = 125
              Height = 27
              HelpContext = 2
              Caption = 'Aggregate'
              TabOrder = 3
              OnClick = OptionCheckBoxClick
            end
            object CheckBox42: TCheckBox
              Tag = 4
              Left = 12
              Top = 123
              Width = 125
              Height = 26
              HelpContext = 2
              Caption = 'Sparser'
              TabOrder = 4
              OnClick = OptionCheckBoxClick
            end
            object CheckBox43: TCheckBox
              Tag = 5
              Left = 12
              Top = 148
              Width = 125
              Height = 26
              Hint = 'Convert constraints to SOSes (only SOS1 handled)'
              HelpContext = 2
              Caption = 'SOS'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 5
              OnClick = OptionCheckBoxClick
            end
            object CheckBox44: TCheckBox
              Tag = 6
              Left = 12
              Top = 172
              Width = 125
              Height = 26
              Hint =
                'If the phase 1 solution process finds that a constraint is redun' +
                'dant then this constraint is deleted'
              HelpContext = 2
              Caption = 'Reduce MIP'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 6
              OnClick = OptionCheckBoxClick
            end
            object CheckBox45: TCheckBox
              Tag = 19
              Left = 185
              Top = 222
              Width = 124
              Height = 26
              HelpContext = 2
              Caption = 'Duals'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 19
              OnClick = OptionCheckBoxClick
            end
            object CheckBox46: TCheckBox
              Tag = 20
              Left = 185
              Top = 246
              Width = 124
              Height = 26
              HelpContext = 2
              Caption = 'Sens Duals'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 20
              OnClick = OptionCheckBoxClick
            end
            object CheckBox62: TCheckBox
              Tag = 7
              Left = 12
              Top = 197
              Width = 125
              Height = 26
              HelpContext = 2
              Caption = 'KnapSack'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 7
              OnClick = OptionCheckBoxClick
            end
            object CheckBox63: TCheckBox
              Tag = 8
              Left = 12
              Top = 222
              Width = 125
              Height = 26
              HelpContext = 2
              Caption = 'Elimeq2'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 8
              OnClick = OptionCheckBoxClick
            end
            object CheckBox64: TCheckBox
              Tag = 9
              Left = 12
              Top = 246
              Width = 125
              Height = 26
              HelpContext = 2
              Caption = 'ImpliedFree'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 9
              OnClick = OptionCheckBoxClick
            end
            object CheckBox65: TCheckBox
              Tag = 10
              Left = 12
              Top = 271
              Width = 125
              Height = 26
              HelpContext = 2
              Caption = 'Reduce GCD'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 10
              OnClick = OptionCheckBoxClick
            end
            object CheckBox66: TCheckBox
              Tag = 11
              Left = 185
              Top = 25
              Width = 124
              Height = 26
              HelpContext = 2
              Caption = 'ProbeFix'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 11
              OnClick = OptionCheckBoxClick
            end
            object CheckBox67: TCheckBox
              Tag = 12
              Left = 185
              Top = 49
              Width = 137
              Height = 26
              HelpContext = 2
              Caption = 'ProbeReduce'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 12
              OnClick = OptionCheckBoxClick
            end
            object CheckBox72: TCheckBox
              Tag = 13
              Left = 185
              Top = 74
              Width = 137
              Height = 26
              HelpContext = 2
              Caption = 'RowDominate'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 13
              OnClick = OptionCheckBoxClick
            end
            object CheckBox73: TCheckBox
              Tag = 14
              Left = 185
              Top = 98
              Width = 137
              Height = 27
              HelpContext = 2
              Caption = 'ColDominate'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 14
              OnClick = OptionCheckBoxClick
            end
            object CheckBox74: TCheckBox
              Tag = 15
              Left = 185
              Top = 123
              Width = 137
              Height = 26
              Caption = 'MergeRows'
              TabOrder = 15
            end
            object CheckBox79: TCheckBox
              Tag = 16
              Left = 185
              Top = 148
              Width = 137
              Height = 26
              Caption = 'Implied SLK'
              TabOrder = 16
            end
            object CheckBox80: TCheckBox
              Tag = 17
              Left = 185
              Top = 172
              Width = 137
              Height = 26
              Caption = 'ColFixDual'
              TabOrder = 17
            end
            object CheckBox81: TCheckBox
              Tag = 18
              Left = 185
              Top = 197
              Width = 137
              Height = 26
              Caption = 'Bounds'
              TabOrder = 18
            end
          end
          object BasisCrashOption: TComboBox
            Left = 320
            Top = 345
            Width = 186
            Height = 28
            Style = csDropDownList
            ItemHeight = 20
            ItemIndex = 0
            TabOrder = 2
            Text = 'Nothing'
            OnClick = OptionCheckBoxClick
            Items.Strings = (
              'Nothing'
              'Non Basic Bounds'
              'Most Feasible'
              'Least Degenerate')
          end
          object IgnoreIntegerOption: TCheckBox
            Left = 898
            Top = 122
            Width = 250
            Height = 26
            Hint =
              'Specifies if Integer restrictions must be ignored.'
            Caption = 'Ignore Integer restrictions'
            ParentShowHint = False
            ShowHint = True
            TabOrder = 14
            OnClick = OptionCheckBoxClick
          end
          object BoundsTighterOption: TCheckBox
            Left = 898
            Top = 146
            Width = 150
            Height = 26
            Hint =
              'Specifies if set bounds may only be tighter or also less restric' +
              'tive.'
            Caption = 'Bounds Tighter'
            ParentShowHint = False
            ShowHint = True
            TabOrder = 15
            OnClick = OptionCheckBoxClick
          end
          object BreackAtFirstOption: TCheckBox
            Left = 898
            Top = 170
            Width = 150
            Height = 27
            Hint =
              'Specifies if the branch-and-bound algorithm stops at first found' +
              ' solution'
            Caption = 'Break at first'
            ParentShowHint = False
            ShowHint = True
            TabOrder = 16
            OnClick = OptionCheckBoxClick
          end
          object SimplexTypeOption: TComboBox
            Left = 320
            Top = 382
            Width = 186
            Height = 28
            Hint = 'Phase1 Primal, Phase2 Primal'
            Style = csDropDownList
            ItemHeight = 20
            ItemIndex = 1
            ParentShowHint = False
            ShowHint = True
            TabOrder = 3
            Text = 'Dual Primal'
            OnChange = SimplexTypeOptionChange
            OnClick = OptionCheckBoxClick
            Items.Strings = (
              'Primal Primal'
              'Dual Primal'
              'Primal Dual'
              'Dual Dual')
          end
          object SolutionLimitOption: TEdit
            Left = 652
            Top = 25
            Width = 186
            Height = 28
            Hint = 'The solution number that must be returned.'
            ParentShowHint = False
            ShowHint = True
            TabOrder = 4
            Text = '1'
            OnExit = OptionCheckBoxClick
            OnKeyPress = EditOptionChange
          end
          object TimeoutOption: TEdit
            Left = 652
            Top = 62
            Width = 186
            Height = 28
            Hint = 'The number of seconds after which a timeout occurs'
            ParentShowHint = False
            ShowHint = True
            TabOrder = 5
            Text = '0'
            OnExit = OptionCheckBoxClick
            OnKeyPress = EditOptionChange
          end
          object InfiniteOption: TEdit
            Left = 652
            Top = 98
            Width = 186
            Height = 28
            Hint = 'Specifies the practical value for "infinite".'
            ParentShowHint = False
            ShowHint = True
            TabOrder = 6
            OnExit = OptionCheckBoxClick
            OnKeyPress = EditOptionChange
          end
          object EpsbOption: TEdit
            Left = 652
            Top = 135
            Width = 186
            Height = 28
            Hint =
              'Specifies the value that is used as a tolerance for the Right Ha' +
              'nd Side (RHS) to determine whether a value should be considered ' +
              'as 0.'
            ParentShowHint = False
            ShowHint = True
            TabOrder = 7
            OnExit = OptionCheckBoxClick
            OnKeyPress = EditOptionChange
          end
          object EpsdOption: TEdit
            Left = 652
            Top = 172
            Width = 186
            Height = 28
            Hint =
              'Specifies the value that is used as a tolerance for reduced cost' +
              's to determine whether a value should be considered as 0.'
            ParentShowHint = False
            ShowHint = True
            TabOrder = 8
            OnExit = OptionCheckBoxClick
            OnKeyPress = EditOptionChange
          end
          object EpselOption: TEdit
            Left = 652
            Top = 209
            Width = 186
            Height = 28
            Hint =
              'Specifies the value that is used as a tolerance for rounding val' +
              'ues to zero.'
            ParentShowHint = False
            ShowHint = True
            TabOrder = 9
            OnExit = OptionCheckBoxClick
            OnKeyPress = EditOptionChange
          end
          object EpsPerturbOption: TEdit
            Left = 652
            Top = 283
            Width = 186
            Height = 28
            Hint =
              'Specifies the value that is used as perturbation scalar for dege' +
              'nerative problems.'
            ParentShowHint = False
            ShowHint = True
            TabOrder = 11
            OnExit = OptionCheckBoxClick
            OnKeyPress = EditOptionChange
          end
          object EpsPivotOption: TEdit
            Left = 652
            Top = 320
            Width = 186
            Height = 28
            Hint =
              'Specifies the value that is used as a tolerance pivot element to' +
              ' determine whether a value should be considered as 0.'
            ParentShowHint = False
            ShowHint = True
            TabOrder = 12
            OnExit = OptionCheckBoxClick
            OnKeyPress = EditOptionChange
          end
          object BreakAtValueOption: TEdit
            Left = 898
            Top = 220
            Width = 187
            Height = 28
            Hint =
              'Specifies if the branch-and-bound algorithm stops when the objec' +
              't value is better than a given value.'
            ParentShowHint = False
            ShowHint = True
            TabOrder = 17
            OnExit = OptionCheckBoxClick
            OnKeyPress = EditOptionChange
          end
          object NegRangeOption: TEdit
            Left = 652
            Top = 394
            Width = 186
            Height = 28
            Hint =
              'Set negative value below which variables are split into a negati' +
              've and a positive part.'
            ParentShowHint = False
            ShowHint = True
            TabOrder = 13
            OnExit = OptionCheckBoxClick
            OnKeyPress = EditOptionChange
          end
          object MPSOptions: TGroupBox
            Left = 886
            Top = 12
            Width = 266
            Height = 100
            Caption = 'MPS'
            TabOrder = 14
            object freeMPSOption: TCheckBox
              Left = 12
              Top = 25
              Width = 150
              Height = 26
              Hint =
                'Read/write in Free MPS format.'
              ParentShowHint = False
              ShowHint = True
              Caption = 'Free MPS format'
              TabOrder = 14
              OnClick = OptionCheckBoxClick
            end
            object IBMMPSOption: TCheckBox
              Left = 12
              Top = 49
              Width = 250
              Height = 26
              Hint =
                'Interprete integer variables without bounds as binary variables. ' +
                'That is the original IBM standard.'
              ParentShowHint = False
              ShowHint = True
              Caption = 'IBM Integer interpretation'
              TabOrder = 14
              OnClick = OptionCheckBoxClick
            end
            object NegateObjConstMPSOption: TCheckBox
              Left = 12
              Top = 73
              Width = 250
              Height = 26
              Hint =
                'Interprete the objective constant with an oposite sign.'
              ParentShowHint = False
              ShowHint = True
              Caption = 'Negate objective constant'
              TabOrder = 14
              OnClick = OptionCheckBoxClick
            end
          end
          object EpsIntOption: TEdit
            Left = 652
            Top = 246
            Width = 186
            Height = 28
            Hint =
              'tolerance that is used to determine whether a floating-point num' +
              'ber is in fact an integer.'
            ParentShowHint = False
            ShowHint = True
            TabOrder = 10
            OnExit = OptionCheckBoxClick
            OnKeyPress = EditOptionChange
          end
          object ImproveOptions: TGroupBox
            Left = 0
            Top = 332
            Width = 174
            Height = 137
            Caption = 'Improve'
            TabOrder = 18
            object CheckBox75: TCheckBox
              Left = 12
              Top = 25
              Width = 150
              Height = 26
              Caption = 'Solution'
              TabOrder = 0
              OnClick = OptionCheckBoxClick
            end
            object CheckBox76: TCheckBox
              Tag = 1
              Left = 12
              Top = 49
              Width = 150
              Height = 26
              Caption = 'DualFeas'
              TabOrder = 1
              OnClick = OptionCheckBoxClick
            end
            object CheckBox77: TCheckBox
              Tag = 2
              Left = 12
              Top = 74
              Width = 150
              Height = 26
              Caption = 'ThetaGap'
              TabOrder = 2
              OnClick = OptionCheckBoxClick
            end
            object CheckBox78: TCheckBox
              Tag = 3
              Left = 12
              Top = 98
              Width = 150
              Height = 27
              Caption = 'BBSimplex'
              TabOrder = 3
              OnClick = OptionCheckBoxClick
            end
          end
        end
        object tsMessages: TTabSheet
          Caption = 'Messages'
          ImageIndex = 3
          object Label8: TLabel
            Left = 197
            Top = 12
            Width = 63
            Height = 20
            Caption = 'Print Sol'
          end
          object Label14: TLabel
            Left = 197
            Top = 49
            Width = 62
            Height = 20
            Caption = 'Verbose'
          end
          object DebugOption: TCheckBox
            Left = 283
            Top = 86
            Width = 149
            Height = 26
            Caption = 'Debug'
            TabOrder = 3
            OnClick = OptionCheckBoxClick
          end
          object LagTraceOption: TCheckBox
            Left = 283
            Top = 111
            Width = 149
            Height = 26
            Caption = 'Lag Trace'
            TabOrder = 4
            OnClick = OptionCheckBoxClick
          end
          object PrintSolOption: TComboBox
            Left = 283
            Top = 12
            Width = 223
            Height = 28
            Hint = 'Prints the solution (variables) of the lp.'
            Style = csDropDownList
            ItemHeight = 20
            ItemIndex = 0
            ParentShowHint = False
            ShowHint = True
            TabOrder = 1
            Text = 'False'
            OnClick = OptionCheckBoxClick
            Items.Strings = (
              'False'
              'True'
              'Automatic')
          end
          object TraceOption: TCheckBox
            Left = 283
            Top = 135
            Width = 149
            Height = 27
            Caption = 'Trace'
            TabOrder = 5
            OnClick = OptionCheckBoxClick
          end
          object VerboseOption: TComboBox
            Left = 283
            Top = 49
            Width = 223
            Height = 28
            Hint = 'Normal messages are reported. This is the default.'
            Style = csDropDownList
            ItemHeight = 20
            ItemIndex = 4
            ParentShowHint = False
            ShowHint = True
            TabOrder = 2
            Text = 'Normal'
            OnChange = VerboseOptionChange
            OnClick = OptionCheckBoxClick
            Items.Strings = (
              'Neutral'
              'Critical'
              'Severe'
              'Important'
              'Normal'
              'Detailed'
              'Full')
          end
          object MessagesOptions: TGroupBox
            Left = 12
            Top = 12
            Width = 174
            Height = 383
            Caption = 'Messages'
            TabOrder = 0
            object CheckBox18: TCheckBox
              Left = 12
              Top = 25
              Width = 150
              Height = 26
              Caption = 'Presolve'
              Enabled = False
              TabOrder = 0
              OnClick = OptionCheckBoxClick
            end
            object CheckBox19: TCheckBox
              Tag = 1
              Left = 12
              Top = 49
              Width = 150
              Height = 26
              Caption = 'Iteration'
              TabOrder = 1
              OnClick = OptionCheckBoxClick
            end
            object CheckBox20: TCheckBox
              Tag = 2
              Left = 12
              Top = 74
              Width = 150
              Height = 26
              Caption = 'Invert'
              TabOrder = 2
              OnClick = OptionCheckBoxClick
            end
            object CheckBox21: TCheckBox
              Tag = 3
              Left = 12
              Top = 98
              Width = 150
              Height = 27
              Caption = 'Lp Feasible'
              TabOrder = 3
              OnClick = OptionCheckBoxClick
            end
            object CheckBox22: TCheckBox
              Tag = 4
              Left = 12
              Top = 123
              Width = 150
              Height = 26
              Caption = 'Lp Optimal'
              TabOrder = 4
              OnClick = OptionCheckBoxClick
            end
            object CheckBox23: TCheckBox
              Tag = 5
              Left = 12
              Top = 148
              Width = 150
              Height = 26
              Caption = 'Lp Equal'
              TabOrder = 5
              OnClick = OptionCheckBoxClick
            end
            object CheckBox24: TCheckBox
              Tag = 6
              Left = 12
              Top = 172
              Width = 150
              Height = 26
              Caption = 'Lp Better'
              TabOrder = 6
              OnClick = OptionCheckBoxClick
            end
            object CheckBox25: TCheckBox
              Tag = 7
              Left = 12
              Top = 197
              Width = 150
              Height = 26
              Caption = 'Mipl Feasible'
              TabOrder = 7
              OnClick = OptionCheckBoxClick
            end
            object CheckBox26: TCheckBox
              Tag = 8
              Left = 12
              Top = 222
              Width = 150
              Height = 26
              Caption = 'Mipl Equal'
              TabOrder = 8
              OnClick = OptionCheckBoxClick
            end
            object CheckBox27: TCheckBox
              Tag = 9
              Left = 12
              Top = 246
              Width = 150
              Height = 26
              Caption = 'Mipl Better'
              TabOrder = 9
              OnClick = OptionCheckBoxClick
            end
            object CheckBox28: TCheckBox
              Tag = 10
              Left = 12
              Top = 271
              Width = 150
              Height = 26
              Caption = 'Mipl Strategy'
              TabOrder = 10
              OnClick = OptionCheckBoxClick
            end
            object CheckBox29: TCheckBox
              Tag = 11
              Left = 12
              Top = 295
              Width = 150
              Height = 27
              Caption = 'Mipl Optimal'
              TabOrder = 11
              OnClick = OptionCheckBoxClick
            end
            object CheckBox30: TCheckBox
              Tag = 12
              Left = 12
              Top = 320
              Width = 150
              Height = 26
              Caption = 'Performance'
              TabOrder = 12
              OnClick = OptionCheckBoxClick
            end
            object CheckBox31: TCheckBox
              Tag = 13
              Left = 12
              Top = 345
              Width = 150
              Height = 26
              Caption = 'Init Pseudo Cost'
              TabOrder = 13
              OnClick = OptionCheckBoxClick
            end
          end
        end
        object tsPlugin: TTabSheet
          Caption = 'Plugins'
          ImageIndex = 4
          object Label25: TLabel
            Left = 12
            Top = 12
            Width = 33
            Height = 20
            Caption = 'BFP'
          end
          object Label26: TLabel
            Left = 12
            Top = 74
            Width = 110
            Height = 20
            Caption = 'XLI Data name'
          end
          object Label27: TLabel
            Left = 12
            Top = 111
            Width = 87
            Height = 20
            Caption = 'XLI Options'
          end
          object BFPOption: TComboBox
            Left = 62
            Top = 12
            Width = 223
            Height = 28
            ItemHeight = 20
            TabOrder = 0
            OnExit = OptionCheckBoxClick
            OnKeyPress = EditOptionChange
            Items.Strings = (
              'bfp_etaPFI'
              'bfp_LUSOL'
              'bfp_GLPK')
          end
          object XLIDataNameOption: TEdit
            Left = 135
            Top = 74
            Width = 482
            Height = 28
            TabOrder = 1
            OnExit = OptionCheckBoxClick
            OnKeyPress = EditOptionChange
          end
          object XLIOption: TEdit
            Left = 135
            Top = 111
            Width = 482
            Height = 28
            TabOrder = 2
            OnExit = OptionCheckBoxClick
            OnKeyPress = EditOptionChange
          end
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Result'
      ImageIndex = 28
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object PageControl1: TPageControl
        Left = 0
        Top = 0
        Width = 1017
        Height = 453
        ActivePage = TabSheet3
        Align = alClient
        TabOrder = 0
        ExplicitHeight = 333
        object TabSheet3: TTabSheet
          Caption = 'Objective'
          ExplicitLeft = 0
          ExplicitTop = 0
          ExplicitWidth = 0
          ExplicitHeight = 0
          object ObjectiveTable: TVirtualStringTree
            Left = 0
            Top = 0
            Width = 1009
            Height = 298
            Align = alClient
            Header.AutoSizeIndex = 0
            Header.Font.Charset = DEFAULT_CHARSET
            Header.Font.Color = clWindowText
            Header.Font.Height = -11
            Header.Font.Name = 'MS Sans Serif'
            Header.Font.Style = []
            Header.Options = [hoColumnResize, hoDblClickResize, hoDrag, hoHotTrack, hoShowHint, hoShowSortGlyphs, hoVisible]
            Header.SortDirection = sdDescending
            Header.Style = hsPlates
            NodeDataSize = 4
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            TreeOptions.AnimationOptions = [toAnimatedToggle]
            TreeOptions.AutoOptions = [toAutoDropExpand, toAutoScroll, toAutoScrollOnExpand, toAutoTristateTracking]
            TreeOptions.MiscOptions = [toAcceptOLEDrop, toCheckSupport, toGridExtensions, toInitOnSave, toReportMode, toToggleOnDblClick, toWheelPanning]
            TreeOptions.PaintOptions = [toShowButtons, toShowDropmark, toShowHorzGridLines, toShowRoot, toShowVertGridLines, toThemeAware, toUseBlendedSelection]
            TreeOptions.SelectionOptions = [toExtendedFocus]
            OnBeforeCellPaint = ObjectiveTableBeforeCellPaint
            OnCompareNodes = ObjectiveTableCompareNodes
            OnGetText = ObjectiveTableGetText
            OnHeaderClick = ObjectiveTableHeaderClick
            OnInitNode = ObjectiveTableInitNode
            Columns = <
              item
                Options = [coAllowClick, coDraggable, coEnabled, coParentBidiMode, coResizable, coShowDropMark, coVisible]
                Position = 0
                Width = 100
                WideText = 'Variables'
              end>
          end
        end
        object TabSheet4: TTabSheet
          Caption = 'Constraints'
          ImageIndex = 1
          ExplicitLeft = 0
          ExplicitTop = 0
          ExplicitWidth = 0
          ExplicitHeight = 0
          object ConstraintTable: TVirtualStringTree
            Left = 0
            Top = 0
            Width = 1258
            Height = 494
            Align = alClient
            Header.AutoSizeIndex = 0
            Header.Font.Charset = DEFAULT_CHARSET
            Header.Font.Color = clWindowText
            Header.Font.Height = -11
            Header.Font.Name = 'MS Sans Serif'
            Header.Font.Style = []
            Header.Options = [hoColumnResize, hoDblClickResize, hoDrag, hoHotTrack, hoShowHint, hoShowSortGlyphs, hoVisible]
            Header.SortDirection = sdDescending
            Header.Style = hsPlates
            NodeDataSize = 4
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            TreeOptions.AnimationOptions = [toAnimatedToggle]
            TreeOptions.AutoOptions = [toAutoDropExpand, toAutoScroll, toAutoScrollOnExpand, toAutoTristateTracking]
            TreeOptions.MiscOptions = [toAcceptOLEDrop, toCheckSupport, toGridExtensions, toInitOnSave, toReportMode, toToggleOnDblClick, toWheelPanning]
            TreeOptions.PaintOptions = [toShowButtons, toShowDropmark, toShowHorzGridLines, toShowRoot, toShowVertGridLines, toThemeAware, toUseBlendedSelection]
            TreeOptions.SelectionOptions = [toExtendedFocus]
            OnBeforeCellPaint = ConstraintTableBeforeCellPaint
            OnCompareNodes = ConstraintTableCompareNodes
            OnGetText = ConstraintTableGetText
            OnHeaderClick = ConstraintTableHeaderClick
            OnInitNode = ConstraintTableInitNode
            Columns = <
              item
                Options = [coAllowClick, coDraggable, coEnabled, coParentBidiMode, coResizable, coShowDropMark, coVisible]
                Position = 0
                Width = 100
                WideText = 'Constraints'
              end>
          end
        end
        object TabSheet1: TTabSheet
          Caption = 'Sensitivity'
          ImageIndex = 2
          ExplicitLeft = 0
          ExplicitTop = 0
          ExplicitWidth = 0
          ExplicitHeight = 0
          object PageControl3: TPageControl
            Left = 0
            Top = 0
            Width = 1009
            Height = 418
            ActivePage = TabSheet7
            Align = alClient
            TabOrder = 0
            ExplicitWidth = 1252
            ExplicitHeight = 463
            object TabSheet7: TTabSheet
              Caption = 'Objective'
              ExplicitLeft = 0
              ExplicitTop = 0
              ExplicitWidth = 0
              ExplicitHeight = 0
              object ObjectiveSensTable: TVirtualStringTree
                Left = 0
                Top = 0
                Width = 1001
                Height = 263
                Align = alClient
                Header.AutoSizeIndex = 0
                Header.Font.Charset = DEFAULT_CHARSET
                Header.Font.Color = clWindowText
                Header.Font.Height = -11
                Header.Font.Name = 'MS Sans Serif'
                Header.Font.Style = []
                Header.Options = [hoColumnResize, hoDblClickResize, hoDrag, hoHotTrack, hoShowHint, hoShowSortGlyphs, hoVisible]
                Header.SortDirection = sdDescending
                Header.Style = hsPlates
                NodeDataSize = 4
                ParentShowHint = False
                ShowHint = True
                TabOrder = 0
                TreeOptions.AnimationOptions = [toAnimatedToggle]
                TreeOptions.AutoOptions = [toAutoDropExpand, toAutoScroll, toAutoScrollOnExpand, toAutoTristateTracking]
                TreeOptions.MiscOptions = [toAcceptOLEDrop, toCheckSupport, toGridExtensions, toInitOnSave, toReportMode, toToggleOnDblClick, toWheelPanning]
                TreeOptions.PaintOptions = [toShowButtons, toShowDropmark, toShowHorzGridLines, toShowRoot, toShowVertGridLines, toThemeAware, toUseBlendedSelection]
                TreeOptions.SelectionOptions = [toExtendedFocus]
                OnBeforeCellPaint = ObjectiveSensTableBeforeCellPaint
                OnCompareNodes = ObjectiveSensTableCompareNodes
                OnGetText = ObjectiveSensTableGetText
                OnHeaderClick = ObjectiveSensTableHeaderClick
                OnInitNode = ObjectiveSensTableInitNode
                Columns = <
                  item
                    Options = [coAllowClick, coDraggable, coEnabled, coParentBidiMode, coResizable, coShowDropMark, coVisible]
                    Position = 0
                    Width = 100
                    WideText = 'Variables'
                  end>
              end
            end
            object TabSheet8: TTabSheet
              Caption = 'Duals'
              ImageIndex = 1
              ExplicitLeft = 0
              ExplicitTop = 0
              ExplicitWidth = 0
              ExplicitHeight = 0
              object RHSSensTable: TVirtualStringTree
                Left = 0
                Top = 0
                Width = 1001
                Height = 263
                Align = alClient
                Header.AutoSizeIndex = 0
                Header.Font.Charset = DEFAULT_CHARSET
                Header.Font.Color = clWindowText
                Header.Font.Height = -11
                Header.Font.Name = 'MS Sans Serif'
                Header.Font.Style = []
                Header.Options = [hoColumnResize, hoDblClickResize, hoDrag, hoHotTrack, hoShowHint, hoShowSortGlyphs, hoVisible]
                Header.SortDirection = sdDescending
                Header.Style = hsPlates
                NodeDataSize = 4
                ParentShowHint = False
                ShowHint = True
                TabOrder = 0
                TreeOptions.AnimationOptions = [toAnimatedToggle]
                TreeOptions.AutoOptions = [toAutoDropExpand, toAutoScroll, toAutoScrollOnExpand, toAutoTristateTracking]
                TreeOptions.MiscOptions = [toAcceptOLEDrop, toCheckSupport, toGridExtensions, toInitOnSave, toReportMode, toToggleOnDblClick, toWheelPanning]
                TreeOptions.PaintOptions = [toShowButtons, toShowDropmark, toShowHorzGridLines, toShowRoot, toShowVertGridLines, toThemeAware, toUseBlendedSelection]
                TreeOptions.SelectionOptions = [toExtendedFocus]
                OnBeforeCellPaint = RHSSensTableBeforeCellPaint
                OnCompareNodes = RHSSensTableCompareNodes
                OnGetText = RHSSensTableGetText
                OnHeaderClick = RHSSensTableHeaderClick
                OnInitNode = RHSSensTableInitNode
                Columns = <
                  item
                    Options = [coAllowClick, coDraggable, coEnabled, coParentBidiMode, coResizable, coShowDropMark, coVisible]
                    Position = 0
                    Width = 100
                    WideText = 'Variables'
                  end>
              end
            end
          end
        end
      end
    end
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 880
    Width = 1025
    Height = 19
    Panels = <
      item
        Width = 100
      end
      item
        Width = 100
      end
      item
        Width = 100
      end
      item
        Width = 100
      end
      item
        Width = 100
      end
      item
        Width = 220
      end>
  end
  object PageControl2: TPageControl
    Left = 0
    Top = 522
    Width = 1025
    Height = 358
    ActivePage = TabSheet5
    Align = alBottom
    TabOrder = 1
    object TabSheet5: TTabSheet
      Caption = 'Log'
      object MemoLog: TSynMemo
        Left = 0
        Top = 0
        Width = 1017
        Height = 323
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -22
        Font.Name = 'Courier New'
        Font.Style = []
        TabOrder = 0
        Gutter.Font.Charset = DEFAULT_CHARSET
        Gutter.Font.Color = clWindowText
        Gutter.Font.Height = -11
        Gutter.Font.Name = 'Courier New'
        Gutter.Font.Style = []
        Gutter.Visible = False
        ReadOnly = True
        RightEdge = 0
      end
    end
    object TabSheet6: TTabSheet
      Caption = 'Messages'
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object MemoMessages: TSynMemo
        Left = 0
        Top = 0
        Width = 1017
        Height = 323
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -22
        Font.Name = 'Courier New'
        Font.Style = []
        TabOrder = 0
        Gutter.Font.Charset = DEFAULT_CHARSET
        Gutter.Font.Color = clWindowText
        Gutter.Font.Height = -11
        Gutter.Font.Name = 'Courier New'
        Gutter.Font.Style = []
        Gutter.Visible = False
        ReadOnly = True
        RightEdge = 0
      end
    end
  end
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 1025
    Height = 29
    Caption = 'ToolBar1'
    Color = clBtnFace
    Images = ImageList
    ParentColor = False
    TabOrder = 3
    object ToolButton11: TToolButton
      Left = 0
      Top = 0
      Hint = 'New'
      Caption = 'New'
      ImageIndex = 6
      MenuItem = NewFile
      ParentShowHint = False
      ShowHint = True
      Style = tbsDropDown
      OnClick = acNewExecute
    end
    object ToolButton1: TToolButton
      Left = 44
      Top = 0
      Action = acOpen
      ParentShowHint = False
      ShowHint = True
    end
    object ToolButton2: TToolButton
      Left = 67
      Top = 0
      Action = acSave
      ParentShowHint = False
      ShowHint = True
    end
    object ToolButton3: TToolButton
      Left = 90
      Top = 0
      Action = acSolve
      ParentShowHint = False
      ShowHint = True
    end
    object ToolButton14: TToolButton
      Left = 113
      Top = 0
      Action = acSolveBasis
      ParentShowHint = False
      ShowHint = True
    end
    object ToolButton13: TToolButton
      Left = 136
      Top = 0
      Action = acStop
      ParentShowHint = False
      ShowHint = True
    end
    object ToolButton4: TToolButton
      Left = 159
      Top = 0
      Width = 8
      Caption = 'ToolButton4'
      ImageIndex = 17
      Style = tbsDivider
    end
    object ToolButton9: TToolButton
      Left = 167
      Top = 0
      Action = acUndo
      ParentShowHint = False
      ShowHint = True
    end
    object ToolButton10: TToolButton
      Left = 190
      Top = 0
      Action = acRedo
      ParentShowHint = False
      ShowHint = True
    end
    object ToolButton12: TToolButton
      Left = 213
      Top = 0
      Width = 8
      Caption = 'ToolButton12'
      ImageIndex = 22
      Style = tbsDivider
    end
    object ToolButton5: TToolButton
      Left = 221
      Top = 0
      Action = acFind
      ParentShowHint = False
      ShowHint = True
    end
    object ToolButton6: TToolButton
      Left = 244
      Top = 0
      Action = acFindPrev
      ParentShowHint = False
      ShowHint = True
    end
    object ToolButton7: TToolButton
      Left = 267
      Top = 0
      Action = acFindNext
      ParentShowHint = False
      ShowHint = True
    end
    object ToolButton8: TToolButton
      Left = 290
      Top = 0
      Action = acReplace
      ParentShowHint = False
      ShowHint = True
    end
    object ToolButton15: TToolButton
      Left = 313
      Top = 0
      Width = 8
      Caption = 'ToolButton15'
      ImageIndex = 21
      Style = tbsSeparator
    end
    object Priority: TTrackBar
      Left = 321
      Top = 0
      Width = 150
      Height = 22
      Hint = 'Thread priority'
      Ctl3D = True
      Max = 2
      Min = -3
      ParentCtl3D = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      ThumbLength = 15
      OnChange = PriorityChange
    end
  end
  object LPSolver: TLPSolver
    LagTrace = False
    IgnoreInteger = False
    BoundsTighter = False
    SimplexType = stDualPrimal
    BasisCrash = cNothing
    OnAbort = LPSolverAbort
    OnLog = LPSolverLog
    Messages = [mPresolve, mIteration, mInvert, mLpFeasible, mLpBetter, mMiLpFeasible, mMiLpEqual, mMiLpBetter, mMiLpOptimal]
    OnMessage = LPSolverMessage
    Verbose = vNormal
    TimeOut = 0
    PrintSol = mbFalse
    Debug = False
    Trace = False
    AntiDegen = [adFixedVars, adStalling, adInfeasible]
    Presolve = []
    MaxPivot = 250
    BBRuleSelect = bbPseudoNonIntSelect
    BBRuleMode = [bbGreedyMode, bbDynamicMode, bbRCostFixing]
    ScaleType = sGeometric
    ScaleMode = [sEquilibrate, sIntegers]
    Improve = []
    PivotRule = pDevex
    PivotMode = [pAdaptive]
    BreakAtFirst = False
    BBFloorFirst = bAutomatic
    BBDepthLimit = -50
    SolutionLimit = 1
    ObjBound = 1E30
    Infinite = 1E30
    Epsb = 0.000000000100000000
    Epsd = 0.000000001000000000
    Epsel = 0.000000000001000000
    EpsPerturb = 0.000010000000000000
    EpsPivot = 0.000000200000000000
    EpsInt = 0.000000100000000000
    ScaleLimit = 5.000000000000000000
    BreakAtValue = -1E30
    NegRange = -1000000.000000000000000000
    FreeMPS = False
    IBMMPS = False
    NegateObjConstMPS = False
    OnLoad = LPSolverLoad
    Left = 256
    Top = 480
  end
  object MainMenu: TMainMenu
    Images = ImageList
    Left = 92
    Top = 480
    object mFile: TMenuItem
      Caption = '&File'
      object NewFile: TMenuItem
        Caption = 'New'
        Hint = 'New'
        ImageIndex = 6
        object NewLPscript1: TMenuItem
          Action = acNewLP
        end
        object NewMPSscript1: TMenuItem
          Action = acNewMPS
        end
      end
      object Open1: TMenuItem
        Action = acOpen
      end
      object Save2: TMenuItem
        Action = acSave
      end
      object Save1: TMenuItem
        Action = acSaveAs
      end
      object Export1: TMenuItem
        Caption = 'Export Source'
        object ExporttoHtml1: TMenuItem
          Action = acExportHTML
        end
        object ExporttoRtf1: TMenuItem
          Action = acExportRtf
        end
        object ExporttoTex1: TMenuItem
          Action = acExportTex
        end
      end
      object ExportMatrice1: TMenuItem
        Caption = 'Export Matrix'
        object acMatExpCsv1: TMenuItem
          Action = acMatExpCsv
        end
        object acMatExpHtml1: TMenuItem
          Action = acMatExpHtml
        end
        object acMatExpRtf1: TMenuItem
          Action = acMatExpRtf
        end
      end
      object Result1: TMenuItem
        Caption = 'Export Result'
        object ExporttoCSV1: TMenuItem
          Action = acObjExpCSV
        end
        object ExporttoHTML2: TMenuItem
          Action = acObjExpHTML
        end
        object ExporttoRTF2: TMenuItem
          Action = acObjExpRTF
        end
        object N7: TMenuItem
          Caption = '-'
        end
        object ExporttoCSV2: TMenuItem
          Action = acConExpCSV
        end
        object ExporttoHTML3: TMenuItem
          Action = acConExpHTML
        end
        object ExporttoRTF3: TMenuItem
          Action = acConExpRTF
        end
      end
      object Sensitivity1: TMenuItem
        Caption = 'Export Sensitivity'
        object ObjectivetoCSV1: TMenuItem
          Action = acSensObjExpCsv
        end
        object ObjectivetoHTML1: TMenuItem
          Action = acSensObjExpHtml
        end
        object ObjectivetoRTF1: TMenuItem
          Action = acSensObjExpRtf
        end
        object N6: TMenuItem
          Caption = '-'
        end
        object ObjectivetoCSV2: TMenuItem
          Action = acSensDualExpCsv
        end
        object ObjectivetoHTML2: TMenuItem
          Action = acSensDualExpHtml
        end
        object ObjectivetoRTF2: TMenuItem
          Action = acSensDualExpRtf
        end
      end
      object Quit1: TMenuItem
        Action = acQuit
      end
    end
    object Edit1: TMenuItem
      Caption = '&Edit'
      object Cut2: TMenuItem
        Action = acCut
      end
      object Copy2: TMenuItem
        Action = acCopy
      end
      object Paste2: TMenuItem
        Action = acPaste
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Undo1: TMenuItem
        Action = acUndo
      end
      object Redo1: TMenuItem
        Action = acRedo
      end
    end
    object Search1: TMenuItem
      Caption = '&Search'
      object Search2: TMenuItem
        Action = acFind
      end
      object Searchagain1: TMenuItem
        Action = acFindNext
      end
      object Findprevious1: TMenuItem
        Action = acFindPrev
      end
      object Replace1: TMenuItem
        Action = acReplace
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object Gotolinenumber1: TMenuItem
        Action = acGotoLine
      end
    end
    object Problem1: TMenuItem
      Caption = '&Action'
      object Solve1: TMenuItem
        Action = acSolve
      end
      object Statistics1: TMenuItem
        Action = acStatistics
        ShortCut = 119
      end
      object Stop1: TMenuItem
        Action = acStop
      end
      object LoadBasis1: TMenuItem
        Action = acSolveBasis
      end
      object Savebasis1: TMenuItem
        Action = acSaveBasis
      end
      object SyntaxCheck1: TMenuItem
        Action = acSyntaxCheck
      end
      object Loadscript1: TMenuItem
        Action = acLoadScript
      end
    end
    object View: TMenuItem
      Caption = '&View'
      object LP1: TMenuItem
        Tag = 1
        Action = acViewAsLP
        RadioItem = True
      end
      object MPS1: TMenuItem
        Action = acViewAsMPS
        RadioItem = True
      end
    end
    object Options1: TMenuItem
      Caption = 'Options'
      object Saveasdefault1: TMenuItem
        Action = acSaveDefaultOptions
      end
      object Saveoptions1: TMenuItem
        Action = acSaveOptions
        Caption = 'Save IDE options ...'
      end
      object Loadoptions1: TMenuItem
        Action = acLoadOptions
        Caption = 'Load IDE options ...'
      end
      object TMenuItem
        Action = acResetOptions
      end
      object N5: TMenuItem
        Caption = '-'
      end
      object SolParams1: TMenuItem
        Caption = 'Solver params ...'
        OnClick = SolParams1Click
      end
    end
    object Help1: TMenuItem
      Caption = 'Help'
      object About1: TMenuItem
        Action = acAbout
      end
      object Help3: TMenuItem
        Action = acHelpOnline
      end
      object Help2: TMenuItem
        Action = acHelp
      end
    end
  end
  object OpenDialogScript: TOpenDialog
    Filter =
      'All know files (*.lp; *.lpt; *.mps)|*.lp; *.lpt; *.mps|LP files ' +
      '(*.lp)|*.lp|CPLEX files (*.lpt)|*.lpt|MPS files (*.mps)|*.mps'
    Left = 164
    Top = 480
  end
  object OpenDialogOptions: TOpenDialog
    Filter = 'Options files (*.lpo)|*.lpo'
    Left = 164
    Top = 512
  end
  object SaveDialogOptions: TSaveDialog
    DefaultExt = 'lpo'
    Filter = 'Option file (*.lpo)|*.lpo'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 128
    Top = 512
  end
  object SaveDialogScript: TSaveDialog
    DefaultExt = 'lp'
    Filter =
      'LP files (*.lp)|*.lp|CPLEX files (*.lpt)|*.lpt|MPS files (*.mps)' +
      '|*.mps'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 128
    Top = 480
  end
  object ActionList: TActionList
    Images = ImageList
    Left = 12
    Top = 480
    object acSolve: TAction
      Caption = '&Solve'
      Hint = 'Solve'
      ImageIndex = 22
      ShortCut = 120
      OnExecute = acSolveExecute
      OnUpdate = acIsNotSolving
    end
    object acStop: TAction
      Caption = 'Stop'
      Enabled = False
      Hint = 'Stop'
      ImageIndex = 21
      ShortCut = 121
      OnExecute = acStopExecute
      OnUpdate = acIsSolving
    end
    object acOpen: TAction
      Caption = '&Open ...'
      Hint = 'Open file'
      ImageIndex = 7
      ShortCut = 16463
      OnExecute = acOpenExecute
    end
    object acSaveAs: TAction
      Caption = '&Save as ...'
      Hint = 'Save file as ...'
      ImageIndex = 8
      OnExecute = acSaveAsExecute
    end
    object acSave: TAction
      Caption = '&Save'
      Hint = 'Save file'
      ImageIndex = 8
      ShortCut = 16467
      OnExecute = acSaveExecute
    end
    object acCut: TAction
      Caption = 'C&ut'
      Hint = 'Cut'
      ImageIndex = 0
      ShortCut = 16472
      OnExecute = acCutExecute
    end
    object acCopy: TAction
      Caption = '&Copy'
      Hint = 'Copy'
      ImageIndex = 1
      ShortCut = 16451
      OnExecute = acCopyExecute
    end
    object acPaste: TAction
      Caption = '&Paste'
      Hint = 'Paste'
      ImageIndex = 2
      ShortCut = 16470
      OnExecute = acPasteExecute
    end
    object acUndo: TAction
      Caption = '&Undo'
      Hint = 'Undo'
      ImageIndex = 3
      ShortCut = 16474
      OnExecute = acUndoExecute
    end
    object acRedo: TAction
      Caption = '&Redo'
      Hint = 'Redo'
      ImageIndex = 4
      ShortCut = 24666
      OnExecute = acRedoExecute
    end
    object acNew: TAction
      Caption = 'New'
      Hint = 'New'
      ImageIndex = 6
      OnExecute = acNewExecute
    end
    object acSyntaxCheck: TAction
      Caption = 'Syntax Check'
      Hint = 'Syntax Check'
      ImageIndex = 23
      OnExecute = acSyntaxCheckExecute
    end
    object acFind: TAction
      Caption = 'Find ...'
      Hint = 'Find'
      ImageIndex = 17
      ShortCut = 16454
      OnExecute = acFindExecute
    end
    object acReplace: TAction
      Caption = 'Replace ...'
      Hint = 'Replace'
      ImageIndex = 20
      ShortCut = 16466
      OnExecute = acReplaceExecute
    end
    object acFindNext: TAction
      Caption = 'Find next'
      Hint = 'Find next'
      ImageIndex = 18
      ShortCut = 114
      OnExecute = acFindNextExecute
    end
    object acFindPrev: TAction
      Caption = 'Find previous'
      Hint = 'Find previous'
      ImageIndex = 19
      ShortCut = 8306
      OnExecute = acFindPrevExecute
    end
    object acNewLP: TAction
      Caption = 'New LP script'
      Hint = 'New LP script'
      ImageIndex = 6
      OnExecute = acNewLPExecute
    end
    object acNewMPS: TAction
      Caption = 'New MPS script'
      Hint = 'New MPS script'
      ImageIndex = 6
      OnExecute = acNewMPSExecute
    end
    object acViewAsLP: TAction
      Caption = 'LP format'
      Checked = True
      OnExecute = acViewAsLPExecute
      OnUpdate = acIsNotSolving
    end
    object acViewAsMPS: TAction
      Caption = 'MPS format'
      OnExecute = acViewAsMPSExecute
      OnUpdate = acIsNotSolving
    end
    object acSaveDefaultOptions: TAction
      Caption = 'Save as default'
      OnExecute = acSaveDefaultOptionsExecute
    end
    object acSaveOptions: TAction
      Caption = 'Save options ...'
      ImageIndex = 8
      OnExecute = acSaveOptionsExecute
    end
    object acLoadOptions: TAction
      Caption = 'Load options ...'
      ImageIndex = 7
      OnExecute = acLoadOptionsExecute
    end
    object acGotoLine: TAction
      Caption = 'Goto line number ...'
      ImageIndex = 24
      ShortCut = 32839
      OnExecute = acGotoLineExecute
    end
    object acStatistics: TAction
      Caption = 'Statistics ...'
      ImageIndex = 29
      OnExecute = acStatisticsExecute
    end
    object acExportHTML: TAction
      Caption = 'to Html ...'
      OnExecute = acExportHTMLExecute
    end
    object acExportRtf: TAction
      Caption = 'to Rtf ...'
      OnExecute = acExportRtfExecute
    end
    object acExportTex: TAction
      Caption = 'to LaTeX ...'
      OnExecute = acExportTexExecute
    end
    object acConExpHTML: TAction
      Caption = 'Constraints to HTML ...'
      OnExecute = acConExpHTMLExecute
    end
    object acConExpRTF: TAction
      Caption = 'Constraints to RTF ...'
      OnExecute = acConExpRTFExecute
    end
    object acConExpCSV: TAction
      Caption = 'Constraints to CSV ...'
      OnExecute = acConExpCSVExecute
    end
    object acObjExpHTML: TAction
      Caption = 'Objective to HTML ...'
      OnExecute = acObjExpHTMLExecute
    end
    object acObjExpRTF: TAction
      Caption = 'Objective to RTF ...'
      OnExecute = acObjExpRTFExecute
    end
    object acObjExpCSV: TAction
      Caption = 'Objective to CSV ...'
      OnExecute = acObjExpCSVExecute
    end
    object acObjCopHTML: TAction
      Caption = 'Copy as HTML'
      OnExecute = acObjCopHTMLExecute
    end
    object acObjCopRTF: TAction
      Caption = 'Copy as RTF'
    end
    object acObjCopCSV: TAction
      Caption = 'Copy as CSV'
    end
    object acLoadScript: TAction
      Caption = 'Load script'
      OnExecute = acLoadScriptExecute
    end
    object acAbout: TAction
      Caption = 'About ...'
      OnExecute = acAboutExecute
    end
    object acQuit: TAction
      Caption = 'Quit'
      OnExecute = acQuitExecute
    end
    object acMatExpHtml: TAction
      Caption = 'to HTML ...'
      OnExecute = acMatExpHtmlExecute
    end
    object acMatExpRtf: TAction
      Caption = 'to RTF ...'
      OnExecute = acMatExpRtfExecute
    end
    object acMatExpCsv: TAction
      Caption = 'to CSV ...'
      OnExecute = acMatExpCsvExecute
    end
    object acSensObjExpHtml: TAction
      Caption = 'Objective to HTML ...'
      OnExecute = acSensObjExpHtmlExecute
    end
    object acSensObjExpRtf: TAction
      Caption = 'Objective to RTF ...'
      OnExecute = acSensObjExpRtfExecute
    end
    object acSensObjExpCsv: TAction
      Caption = 'Objective to CSV ...'
      OnExecute = acSensObjExpCsvExecute
    end
    object acSensDualExpHtml: TAction
      Caption = 'Dual to HTML ...'
      OnExecute = acSensDualExpHtmlExecute
    end
    object acSensDualExpRtf: TAction
      Caption = 'Dual to RTF ...'
      OnExecute = acSensDualExpRtfExecute
    end
    object acSensDualExpCsv: TAction
      Caption = 'Dual to CSV ...'
      OnExecute = acSensDualExpCsvExecute
    end
    object acSaveBasis: TAction
      Caption = 'Save basis ...'
      OnExecute = acSaveBasisExecute
    end
    object acSolveBasis: TAction
      Caption = 'Solve basis ...'
      Hint = 'Solve basis'
      ImageIndex = 31
      OnExecute = acSolveBasisExecute
      OnUpdate = acIsNotSolving
    end
    object acHelpOnline: TAction
      Caption = 'Help https://lp-solve.github.io/'
      Hint = 'Help'
      ImageIndex = 30
      ShortCut = 112
      OnExecute = acHelpOnlineExecute
    end
    object acHelp: TAction
      Caption = 'Help local lp_solve55.chm'
      Hint = 'Help'
      ImageIndex = 30
      ShortCut = 113
      OnExecute = acHelpExecute
    end
    object acLoadParams: TAction
      Caption = 'Load Params ...'
      ImageIndex = 7
      OnExecute = acLoadParamsExecute
    end
    object acSaveParams: TAction
      Caption = 'Save Params ...'
      ImageIndex = 8
      OnExecute = acSaveParamsExecute
    end
    object acResetOptions: TAction
      Caption = 'Reset to solver defaults'
      OnExecute = acResetOptionsExecute
    end
  end
  object ImageList: TImageList
    Left = 40
    Top = 480
    Bitmap = {
      494C010121002200040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000009000000001002000000000000090
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008484000084
      8400008484000084840000848400008484000084840000848400008484000000
      0000000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000FFFF00000000000084
      8400008484000084840000848400008484000084840000848400008484000084
      840000000000000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF0000FFFF000000
      0000008484000084840000848400008484000084840000848400008484000084
      84000084840000000000000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000FFFF00FFFFFF0000FF
      FF00000000000084840000848400008484000084840000848400008484000084
      8400008484000084840000000000000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF0000FFFF00FFFF
      FF0000FFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000FFFF00FFFFFF0000FF
      FF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF0000FFFF00000000000000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF0000FFFF00FFFF
      FF0000FFFF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF00000000000000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000FFFF00FFFFFF0000FF
      FF00000000000000000000000000000000000000000000000000000000000000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF00000000000000000000
      0000000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000000000000000000000000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF0000000000000000000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF00000000000000FF000000FF0000
      00FF00000000000000FF00000000000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF00000000000000000000
      0000000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000A5A5A5007B7B7B00636363004A4A4A005A5A5A007B7B8400A5A5
      A500000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000B5B5B500636363004A4A4A004242420042424200424242004A4A4A007373
      73000000000000000000000000000000000000000000000000007F5B00000000
      00007F5B00007F5B0000000000007F5B00007F5B0000000000007F5B00007F5B
      0000000000007F5B00007F5B00007F5B0000000000000000000000000000B5B5
      B5007B7B7B0084635200A57B5200C6946300D69C6300C68C6300A56B52008442
      310084847B0000000000000000000000000000000000634A2900634A2900634A
      2900634A2900634A2900634A2900634A2900634A2900634A2900634A2900634A
      2900634A2900634A2900634A290000000000000000000000000000000000ADA5
      A500E7CEC600F7E7D600F7E7DE00F7E7DE00F7E7DE00F7E7D600CEBDAD005252
      52006B6B6B00A5A5A500000000000000000000000000000000007F5B00000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000007F5B0000000000007F5B00000000000000000000B5BDBD008473
      6300A58C7300E7BD9400E7BD9400E7BD9400F7C69400F7C69400F7BD9400E79C
      8400A55A420084312100000000000000000000000000634A2900C6B5A500F7F7
      F700F7F7F700F7F7F700F7F7F700FFFFF700FFF7F700F7F7E700F7EFE700F7E7
      D600F7DED600E7CEC600D6BDB500634A29000000000000000000CEBDB500F7E7
      DE00F7F7F700E7E7E700CEB5A500D6AD9400DEC6BD00EFF7F700F7F7F700F7E7
      D600847B7B0063636300ADADAD00000000000000000000000000000000000000
      00000000000000000000007F0000000000000000000000000000000000000000
      0000000000007F5B00007F5B00007F5B0000000000000000000084848400B59C
      8400F7CEB500F7CEA500F7CEA500F7CEA500F7D6A500F7D6A500F7D6B500F7C6
      A500F7A59400B55A420084847B000000000000000000634A2900F7F7F7008431
      08005231180052311800D6C6C600106384000039520021314200B5A5A5001029
      8400001863000018630000186300D6BDB50000000000DECEC600F7EFE700F7F7
      F700CE9C8400B54A1000BD633900DEAD9C00C65A2100BD522100D6AD9C00F7F7
      F700F7E7DE00736B6B006B6B6B000000000000000000000000007F5B00000000
      00000000000000000000007F0000007F00000000000000000000000000000000
      00000000000000000000000000000000000000000000ADB5B500948C8400EFD6
      C600635A5A00B59C9400F7DEC600F7D6B500F7D6B500F7DEB500F7DEB500F7DE
      B500F7CEA500E79C8400844A3100A5ADAD0000000000634A2900F7F7F7008431
      0800E77B4200B55A290052311800106B840000C6F70000A5C600313129001031
      84001042D6000031B5000031B5000018630000000000F7E7D600F7F7F700C67B
      5A00BD420800C64A1000C6A59400F7F7F700DE946B00C64A0800BD420800CE9C
      8400F7F7F700F7E7D600525252009494940000000000000000007F5B00000000
      00000000000000000000007F000010C21000007F000000000000000000000000
      000000000000848484007F5B0000848484000000000094949400C6B5B500FFE7
      D600C6BDAD0031313100B5ADA500F7DEC600F7D6C60031313100C6B594003129
      2100F7D6B500F7B59400B56B520084848C0000000000634A2900F7F7F7009439
      0800F78C5200E7845200C6632900216B840000C6F70000C6F70000A5C6002139
      8400214AE7001042D6001031B5000018630000000000F7F7F700DEAD9400BD4A
      0800CE632900CE632900CE6B3900DE8C6B00CE5A2900CE632900CE5A2900BD42
      1000E7CEBD00F7EFEF00A59494005A5A5A0000000000000000007F5B00000000
      00000000000000000000007F0000007F000010C21000007F0000000000000000
      0000000000007F5B00007F5B00007F5B0000000000007B737B00E7DED600FFEF
      E700F7EFE700736B630031393100E7D6C600F7DED600E7CEC60021292100B5A5
      8400F7D6A500F7BD9400D68C73006B6B6B0000000000634A2900F7F7F7009442
      1800F7A57300F79C6300C67B52002173840021CEF70010C6F70000A5C6002139
      8400315AE7002152E7001039B50000186300F7E7D600F7F7F700C6633100CE5A
      2100CE633100CE5A2100CE8C6B00F7E7DE00D66B3900CE5A2100CE633100C652
      1800C67B5200F7F7F700E7CEC6004A4A4A000000000000000000000000000000
      00000000000000000000007F0000007F0000007F0000007F0000007F00000000
      000000000000000000007F5B0000000000000000000073737300FFF7F700FFF7
      E700FFFFF700FFFFF70021181000D6CEC600F7EFE70063636300D6C6B500524A
      4200F7CEA500F7C69400E7A584005252520000000000634A2900FFFFF700A552
      1800FFB58400F7AD8400C68C63003173840031D6F70021CEF70010A5C6003142
      8400426BE7004263E700314AC60000186300F7E7DE00F7DED600C6521800CE63
      3100CE633100CE5A2100C6846B00F7F7F700EFAD9400C64A0800CE632900CE5A
      2900C65A2900F7F7F700F7E7D6004A4A4A0000000000000000007F5B00000000
      00000000000000000000007F0000007F0000007F0000007F0000007F00000000
      000000000000000000007F5B000000000000000000008C848C00E7E7E700FFF7
      E700FFFFF700737373003131310042393100736B6300F7E7D600F7DED600F7D6
      C600F7D6B500F7C6A500D69C73006B636B0000000000634A2900FFF7F700A552
      2900B56B4200C6846300D6947300317B840052DEF70042D6F70031ADC600314A
      8400637BF7005273F700425AC60000186300F7E7DE00F7DECE00CE5A2100CE63
      3100CE632900CE632900C6521800CEB5AD0000000000E79C7B00C6521800CE63
      2900C65A2900F7F7F700F7DED6004A4A4A0000000000000000007F5B00000000
      00000000000000000000007F0000007F000000DF0000007F0000000000000000
      00000000000000000000000000000000000000000000A5A5AD00D6CEC600FFFF
      F700FFFFF700F7FFF7007373730063636300F7EFE700E7D6D600F7E7D600F7E7
      D600F7D6B500F7C6A500B58463008484840000000000634A2900F7F7E700B563
      4200F7F7F700FFEFE700FFDEC6004284840073E7F70063DEF70042B5C6004252
      9400738CF7007384F700526BC60000186300F7E7D600FFEFE700DE6B3100D66B
      3100CE5A2900CE5A2100CE521800C64A1000E7D6C600F7F7F700D6733900CE5A
      2100CE6B3900F7F7F700EFDED60063636300000000007F5B00007F5B00007F5B
      00000000000000000000007F000000FF0000007F000000000000000000000000
      000000000000000000007F5B00000000000000000000C6C6C600A5A5A500FFFF
      F7000000000000000000A5ADA500636B6300D6D6D60031313100F7EFE700FFEF
      D600F7D6B500E7C6A500846B5200ADADB50000000000634A2900F7EFE700E7CE
      B500E79C7300E7947300E78C63004284840094EFF70084E7F70063BDD600425A
      9400849CFF008494F7006373D6000018630000000000F7F7F700F79C6B00E763
      2900CE8C6B00F7EFE700D67B5200BD310000D69C7B00F7F7F700DE8C6300D652
      1000E79C7300F7F7F700DECEBD00A5A5A50000000000848484007F5B00008484
      84000000000000000000007F0000007F00000000000000000000000000000000
      000000000000000000007F5B0000000000000000000000000000A5A5A500C6C6
      C600000000000000000000000000C6BDB500736B7300C6B5B500FFF7E700F7E7
      D600F7D6B500A58C7300737373000000000000000000634A2900F7E7D600F7E7
      E700634A29000000000000000000528C8400B5F7FF00A5EFFF0084C6D6005263
      9400637BB500738CD6007384D6000018630000000000F7F7EF00FFEFDE00FF8C
      4A00DE845A00F7F7F700F7F7F700E7BDA500F7F7F700F7F7F700E7733900E773
      3100FFF7EF00F7E7E700A59C9400000000000000000000000000000000000000
      00000000000000000000007F0000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000CED6D600ADA5
      AD00C6C6C6000000000000000000FFFFF700FFF7E700FFF7E700F7EFD600F7DE
      C600B59C9400736B6B00BDBDC6000000000000000000634A2900F7DED600F7E7
      D600634A29000000000000000000528C8400D6F7FF00C6F7FF0094C6D6005284
      84007384B500E7E7FF00B5C6FF001021630000000000F7DED600F7F7F700FFEF
      CE00FFB57300EFAD8400EFE7DE00EFF7F700F7E7E700F7A57B00FF8C4A00FFDE
      CE00F7F7F700F7DED600BDBDBD0000000000000000007F5B00007F5B00007F5B
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000007F5B000000000000000000000000000000000000D6D6
      D600A5A5A500A5A5A500D6CEC600E7E7E700FFF7E700E7DED600C6B5B500948C
      84008484840000000000000000000000000000000000634A2900D6CEC600E7DE
      D600634A29000000000000000000528C9400739CA50084B5B500B5CED6005284
      8400C6CEDE006373A5006373A500526394000000000000000000F7DED600F7F7
      F700F7F7F700FFF7C600FFDEAD00FFCE9C00FFCE9400FFD6AD00F7F7F700F7F7
      F700F7DED600BDBDBD000000000000000000000000007F5B0000000000007F5B
      0000000000007F5B00007F5B0000000000007F5B00007F5B0000000000007F5B
      00007F5B0000000000007F5B0000000000000000000000000000000000000000
      000000000000C6C6C600ADA5AD008C848C00737373007B7B7B00949C9400B5BD
      BD000000000000000000000000000000000000000000D6CEBD00B5A58400D6CE
      C600634A29000000000000000000528C9400F7F7F700F7F7F700D6FFFF005284
      840000000000000000000000000000000000000000000000000000000000F7DE
      D600F7EFE700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7E7E700F7DE
      D600D6CECE00000000000000000000000000000000007F5B00007F5B00007F5B
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000D6C6B500B5A5
      8C00634A29000000000000000000B5CECE00528C9400528C9400528C9400528C
      9400000000000000000000000000000000000000000000000000000000000000
      0000F7E7DE00F7DED600EFDED600EFDED600EFDED600F7DED600E7DED6000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000848484000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008484
      8400000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000084848400F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7
      F700F7F7F70000000000000000000000000000000000C6C6C600848484008484
      8400848484008484840084848400848484008484840084848400848484008484
      8400848484008484840084848400000000000000000084848400C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C6000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000084848400F7F7
      F700848484008484840084848400848484008484840084848400848484008484
      8400F7F7F70000000000000000000000000000000000C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C60084848400000000000000000084848400F7F7F700C6C6
      C60000000000C6C6C60000000000C6C6C60000000000C6C6C60000000000C6C6
      C600C6C6C6000000000000000000000000000000000000000000CED6D6000000
      0000F7F7F700F7F7F700F7F7F700F7F7F700CED6D600F7F7F700F7F7F700F7F7
      F700F7F7F700F7F7F7000000000000000000000000000000000084848400F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7
      F700F7F7F70000000000000000000000000000000000C6C6C600F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7
      F700F7F7F700C6C6C60084848400000000000000000084848400F7F7F700F7F7
      F700848400008484000084840000848400008484000084840000848400000000
      0000C6C6C6000000000000000000000000000000000000000000000000000000
      0000840000008400000084000000F7F7F700CED6D600F7F7F700840000008400
      000084000000F7F7F7000000000000000000000000000000000084848400F7F7
      F700848484008484840084848400848484008484840084848400848484008484
      8400F7F7F70000000000000000000000000000000000C6C6C600F7F7F7000000
      0000F7F7F7008484840084848400848484008484840084848400848484008484
      8400F7F7F700C6C6C60084848400000000000000000084848400F7F7F700C6C6
      C60000000000C6C6C600F7F7F700C6C6C600F7F7F700C6C6C60000000000C6C6
      C600C6C6C6000000000000000000000000000000000000000000CED6D6000000
      0000F7F7F700F7F7F700F7F7F700F7F7F700CED6D600F7F7F700F7F7F700F7F7
      F700F7F7F700F7F7F700000000000000000000000000000000008484840000FF
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000000000000000000000000000000000C6C6C600000000000000
      000000000000F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7
      F700F7F7F700C6C6C60084848400000000000000000084848400F7F7F700F7F7
      F700848400008484000084840000848400008484000084840000848400000000
      0000C6C6C6000000000000000000000000000000000000000000000000000000
      0000840000008400000084000000F7F7F700CED6D600F7F7F700840000008400
      000084000000F7F7F700000000000000000000000000000000008484840000FF
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000000000000000000000000000000000C6C6C600000000000000
      0000000000000000000084848400848484008484840084848400848484008484
      8400F7F7F700C6C6C60084848400000000000000000084848400F7F7F700C6C6
      C60000000000C6C6C600F7F7F700C6C6C600F7F7F700C6C6C60000000000C6C6
      C600C6C6C6000000000000000000000000000000000000000000CED6D6000000
      0000F7F7F700F7F7F700F7F7F700F7F7F700CED6D600F7F7F700F7F7F700F7F7
      F700F7F7F700F7F7F700000000000000000000000000000000008484840000FF
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000000000000000000000000000000000C6C6C600000000000000
      0000000000000000000000000000F7F7F700F7F7F700F7F7F700F7F7F700F7F7
      F700F7F7F700C6C6C60084848400000000000000000084848400F7F7F700F7F7
      F700848400008484000084840000848400008484000084840000848400000000
      0000C6C6C6000000000000000000000000000000000000000000000000000000
      0000840000008400000084000000F7F7F700CED6D600F7F7F700840000008400
      000084000000F7F7F7000000000000000000000000000000000084848400F7F7
      F700848484008484840084848400848484008484840084848400848484008484
      8400F7F7F70000000000000000000000000000000000C6C6C600000000000000
      0000000000008484840084848400848484008484840084848400848484008484
      8400F7F7F700C6C6C60084848400000000000000000084848400F7F7F700C6C6
      C60000000000C6C6C60000000000C6C6C600F7F7F700C6C6C60000000000C6C6
      C600C6C6C6000000000000000000000000000000000000000000CED6D6000000
      0000F7F7F700F7F7F700F7F7F700F7F7F700CED6D600F7F7F700F7F7F700F7F7
      F700F7F7F700F7F7F7000000000000000000000000000000000084848400F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7
      F700F7F7F70000000000000000000000000000000000C6C6C600000000000000
      000000000000F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7
      F700F7F7F700C6C6C60084848400000000000000000084848400F7F7F700F7F7
      F700848400008484000084840000848400008484000084840000848400000000
      0000C6C6C6000000000000000000000000000000000000000000000000000000
      0000840000008400000084000000F7F7F700CED6D600F7F7F700840000008400
      000084000000F7F7F7000000000000000000000000000000000084848400F7F7
      F70084848400848484008484840084848400F7F7F700F7F7F700F7F7F700F7F7
      F700F7F7F70000000000000000000000000000000000C6C6C60000000000F7F7
      F700000000000000000084848400848484008484840084848400848484008484
      8400F7F7F700C6C6C60084848400000000000000000084848400F7F7F700C6C6
      C60000000000C6C6C600F7F7F700C6C6C600F7F7F700C6C6C60000000000C6C6
      C600C6C6C6000000000000000000000000000000000000000000CED6D6000000
      0000F7F7F700F7F7F700F7F7F700F7F7F700CED6D600F7F7F700F7F7F700F7F7
      F700F7F7F700F7F7F7000000000000000000000000000000000084848400F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700000000000000
      00000000000000000000000000000000000000000000C6C6C600F7F7F700F7F7
      F700F7F7F7000000000000000000F7F7F700F7F7F700F7F7F700F7F7F700F7F7
      F700F7F7F700C6C6C60084848400000000000000000084848400F7F7F700F7F7
      F700848400008484000084840000848400008484000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000084848400F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700000000000000
      00000000000000000000000000000000000000000000C6C6C600F7F7F700F7F7
      F700F7F7F7008484840084848400848484008484840084848400F7F7F7008484
      8400848484008484840084848400000000000000000084848400F7F7F700C6C6
      C600F7F7F700C6C6C600F7F7F700C6C6C600F7F7F700C6C6C600C6C6C6000000
      0000848484000000000000000000000000000000000000000000CED6D6000000
      0000CED6D600CED6D600CED6D600CED6D600CED6D600F7F7F700CED6D600CED6
      D600CED6D600CED6D6000000000000000000000000000000000084848400F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700000000000000
      00000000000000000000000000000000000000000000C6C6C600F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700C6C6
      C600000000008484840000000000000000000000000084848400F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700C6C6C6008484
      8400000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000848484008484
      8400848484008484840084848400848484008484840084848400000000000000
      00000000000000000000000000000000000000000000C6C6C600F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700C6C6
      C600848484000000000000000000000000000000000084848400848484008484
      8400848484008484840084848400848484008484840084848400848484000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000001073100000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000848484008484840084848400000000000000000000000000000000000808
      C6000808C6000808C6000808C6000808C6000808C6000808C6000808C6000808
      C6000808C6000808C60000000000000000000000000000000000000000000000
      0000107310004294420010731000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000084848400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00008484840000000000000000008484840000000000000000000808C6005A52
      DE005A5ADE006363E7006363E7006B6BE7006B6BE7006B6BE7006363E7006363
      E7005A5ADE005A52DE000808C600000000000000000000000000000000000000
      0000107310004294420042944200107310000000000000000000000000000000
      0000000000000000000000000000000000000000000084848400F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7
      F700000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00008484840000000000000000008484840000000000000000000808C6005252
      DE005A5ADE005A5AE7006363E7006363E7006363E7006363E7006363E7005A5A
      E7005A5ADE005252DE000808C600000000000000000000000000000000000000
      0000107310004294420042944200429442001073100000000000000000000000
      0000000000000000000000000000000000000000000084848400F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7
      F700000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00008484840084848400848484000000000000000000000000000808C6004A4A
      DE005252DE005252E7005A52E7005A5AE7005A5AE7005A5AE7005A52E7005252
      E7005252DE004A4ADE000808C600000000000000000000000000000000000000
      000010731000429442004294420042944200398C390010731000000000000000
      0000000000000000000000000000000000000000000084848400F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700C6C6C6000000000000000000F7F7F700F7F7
      F700000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00008484840000000000000000008484840000000000000000000808C6004242
      DE004A42DE004A4ADE004A4AE7004A4AE700524AE7004A4AE7004A4AE7004A4A
      DE004A42DE004242DE000808C600000000000000000000000000000000000000
      000010731000399439003994390039943900398C390031843100107310000000
      0000000000000000000000000000000000000000000084848400F7F7F700F7F7
      F700F7F7F700F7F7F70084848400000000000000000000000000F7F7F700F7F7
      F700000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00008484840000000000000000008484840000000000000000000808C6003931
      D6003939DE003939DE004242DE004242DE004242DE004242DE004242DE003939
      DE003939DE003931D6000808C600000000000000000000000000000000000000
      000010731000318C3100318C3100318C3100318C310029842900217B21001073
      1000000000000000000000000000000000000000000084848400F7F7F700F7F7
      F700F7F7F700848484000000000000000000000000000000000000000000F7F7
      F700000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00008484840084848400848484000000000000000000000000000808C6002929
      D6002929D6003131DE003131DE003131DE003131DE003131DE003131DE003131
      DE002929D6002929D6000808C600000000000000000000000000000000000000
      000010731000218C2100298C29002184210021842100217B2100187B18001873
      1800107310000000000000000000000000000000000084848400F7F7F700F7F7
      F700F7F7F700000000000000000000000000F7F7F7000000000000000000F7F7
      F700848484000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000808C6002121
      D6002121D6002121D6002121D6002121DE002121DE002121DE002121D6002121
      D6002121D6002121D6000808C600000000000000000000000000000000000000
      0000107310001884180018841800187B1800187B1800107B1000107310001073
      1000000000000000000000000000000000000000000084848400F7F7F700F7F7
      F700F7F7F7000000000000000000F7F7F700F7F7F700F7F7F700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000808C6001010
      CE001818D6004A4ADE004A4ADE004A4ADE004A4ADE004A4ADE004A4ADE004A4A
      DE001818D6001010CE000808C600000000000000000000000000000000000000
      000010731000298C2900318C3100218421000873080008730800086B08000000
      0000000000000000000000000000000000000000000084848400F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000808C6000808
      CE001008CE007B7BE7007B7BE7007B7BE7007B7BE7007B7BE7007B7BE7007B7B
      E7001008CE000808CE000808C600000000000000000000000000000000000000
      0000107310004A9C4A004A9C4A004A9C4A004A9C4A0031843100000000000000
      0000000000000000000000000000000000000000000084848400F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F7000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000808C6000808
      C6000808CE00ADADEF00ADADEF00ADADEF00ADADEF00ADADEF00ADADEF00ADAD
      EF000808CE000808CE000808C600000000000000000000000000000000000000
      00001073100073AD730073AD730073AD730073AD730000000000000000000000
      0000000000000000000000000000000000000000000084848400F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F7008484840084848400C6C6
      C600000000000000000000000000000000008484840000000000000000000000
      0000848484000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000808C6000000
      C6000000C6006B6BDE00F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700BDBD
      F7000000C6000000C6000808C600000000000000000000000000000000000000
      0000006B000094C6940094C6940094C694000000000000000000000000000000
      0000000000000000000000000000000000000000000084848400F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F70084848400000000008484
      8400000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      C6000000C6000000C6000000C6000000C6000000CE000000CE000000C6000000
      C6000000C6000000C60000000000000000000000000000000000000000000000
      0000006B0000BDD6BD00BDD6BD00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000084848400F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F70084848400848484000000
      0000000000000000000000000000000000000000000084848400000000008484
      8400000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000398C390000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000084848400848484008484
      8400848484008484840084848400848484008484840084848400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000636363006363
      6300636363006363630063636300636363006363630063636300636363006363
      6300636363006363630063636300000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F700000000000000000000000000000000000000000000000000F7F7F7000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000F7F7F700000000000000000000000000000000000000000000000000F7F7
      F700000000000000000000000000000000000000000000639C0000639C000063
      9C0000639C0000639C0000639C0000639C0000639C0000639C0000639C000063
      9C0000639C0000639C00000000006363630000000000F7F7F700000000000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F70000000000000000000000000000000000000000000000000000000000F7F7
      F700000000000000000000000000000000000000000000000000F7F7F7000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000F7F7F700000000000000000000000000000000000000000000000000F7F7
      F7000000000000000000000000000000000000639C0063CEFF0000639C009CFF
      FF006BD6FF006BD6FF006BD6FF006BD6FF006BD6FF006BD6FF006BD6FF006BD6
      FF0039A5D6009CFFFF0000639C006363630000000000F7F7F700000000000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F700000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000639C0063CEFF0000639C009CFF
      FF007BE7FF007BE7FF007BE7FF007BE7FF007BE7FF007BE7FF007BE7FF007BE7
      FF0042ADDE009CFFFF0000639C00636363000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F7000000000000000000000000008484840000000000F7F7F700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000F7F7F7000000000000000000000000008484840000000000F7F7F7000000
      00000000000000000000000000000000000000639C0063CEFF0000639C009CFF
      FF0084EFFF0084EFFF0084EFFF0084EFFF0084EFFF0084EFFF0084EFFF0084EF
      FF004AB5E7009CFFFF00006B9C00636363000000000000000000F7F7F7000000
      00000000000000000000000000000000000000000000F7F7F700000000000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F7000000000000000000000000000000000000000000F7F7F700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000F7F7F7000000000000000000000000000000000000000000F7F7F7000000
      00000000000000000000000000000000000000639C0063CEFF0000639C009CFF
      FF0094F7FF0094F7FF0094F7FF0094F7FF0094F7FF0094F7FF0094F7FF0094F7
      FF0052BDEF009CFFFF00006B9C00636363000000000000000000F7F7F7000000
      00000000000000000000C6C6C6000000000000000000F7F7F700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000084848400000000008484840000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000848484000000000084848400000000000000
      00000000000000000000000000000000000000639C006BD6FF0000639C009CFF
      FF009CFFFF009CFFFF009CFFFF009CFFFF009CFFFF009CFFFF009CFFFF009CFF
      FF005AC6FF009CFFFF00006BA500636363000000000000000000F7F7F7000000
      00000000000000000000C6C6C6000000000000000000F7F7F700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000639C007BE7FF0000639C00F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7
      F70084E7FF00F7F7F7000873A500636363000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000639C0084EFFF0084E7FF000063
      9C0000639C0000639C0000639C0000639C0000639C0000639C0000639C000063
      9C0000639C0000639C0000639C0000000000000000000000000000000000F7F7
      F7000000000000000000000000000000000000000000F7F7F700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000084848400840000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008400000084848400000000000000
      00000000000000000000000000000000000000639C0094F7FF008CF7FF008CF7
      FF008CF7FF008CF7FF008CF7FF00F7F7F700F7F7F700F7F7F700F7F7F700F7F7
      F70000639C006363630000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000008484840084000000000000000000000000000000000000008400
      0000840000008400000084000000000000000000000084000000840000008400
      0000840000000000000000000000000000000000000084000000848484000000
      00000000000000000000000000000000000000639C00F7F7F7009CFFFF009CFF
      FF009CFFFF009CFFFF00F7F7F70000639C0000639C0000639C0000639C000063
      9C0000639C000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000008400000000000000000000000000000000000000000000000000
      0000840000008400000084000000000000000000000084000000840000008400
      0000000000000000000000000000000000000000000000000000840000000000
      0000000000000000000000000000000000000000000000639C00F7F7F700F7F7
      F700F7F7F700F7F7F70000639C00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000F7F7F7000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000008400000000000000000000000000000000000000000000000000
      0000840000008400000084000000000000000000000084000000840000008400
      0000000000000000000000000000000000000000000000000000840000000000
      000000000000000000000000000000000000000000000000000000639C000063
      9C0000639C0000639C0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000008484840084000000000000000000000000000000848484008400
      0000000000000000000084000000000000000000000084000000000000000000
      0000840000008484840000000000000000000000000084000000848484000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000084848400840000008400000084000000840000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000008400000084000000840000008400000084848400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000840000008400000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008400
      0000C6C6C6008400000084000000000000000000000000000000000000000000
      0000000000000000000000000000000000008400000084000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000084000000C6C6
      C600840000008400000084000000000000000000000000000000000000000000
      0000000000000000000000000000840000008400000084000000000000000000
      0000000000000000000000000000000000000000000000000000C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000000
      0000C6C6C6000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000084000000C6C6C6008400
      0000840000008400000000000000000000000000000000000000000000000000
      0000000000000000000084000000840000008400000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000C6C6C60000000000000000000000000084848400848484008484
      8400848484008484840084848400848484008484840084848400848484008484
      8400848484008484840000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084000000C6C6C600840000008400
      000084000000000000000000000000000000000000000000000084848400C6C6
      C600000000008484840000000000840000000000000000000000000000000000
      00000000840000000000000000000000000000000000C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C60000FFFF0000FFFF0000FFFF00C6C6C600C6C6
      C60000000000000000000000000000000000000000008484840000FFFF00FF00
      FF0000FFFF00FF00FF0000FFFF00FF00FF0000FFFF00FF00FF0000FFFF00FF00
      FF0000FFFF008484840000000000000000000000000000000000000000000000
      0000C6C6C600C6C6C600C6C6C600000000008484840084000000840000008400
      0000000000000000000000000000000000000000000084848400C6C6C600C6C6
      C600C6C6C6000000000084848400000000000000000000000000000000000000
      84000000840000000000000000000000000000000000C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600848484008484840084848400C6C6C600C6C6
      C60000000000C6C6C600000000000000000000000000848484000000000000FF
      FF00FF00FF0000FFFF00FF00FF0000FFFF00FF00FF0000FFFF00FF00FF0000FF
      FF0000000000848484000000000000000000000000000000000084848400C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C6000000000084848400000000000000
      00000000000000000000000000000000000000000000C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C60000000000000000000000000000000000000084000000
      8400000084000000840000008400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000C6C6C600C6C6C60000000000000000008484840000FFFF000000
      000000FFFF00FF00FF0000FFFF000000000000FFFF00FF00FF0000FFFF000000
      000000FFFF008484840000000000000000000000000000000000C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C60000000000000000000000
      00000000000000000000000000000000000000000000C6C6C60000000000FFFF
      0000C6C6C600C6C6C600C6C6C600000000000000000000000000000000000000
      84000000840000000000000000000000840000000000C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000000
      0000C6C6C60000000000C6C6C6000000000000000000848484000000000000FF
      FF000000000000FFFF000000000000FFFF000000000000FFFF000000000000FF
      FF00FF00FF0084848400000000000000000000000000C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000000
      0000000000000000000000000000000000000000000084848400000000000000
      0000C6C6C600C6C6C60084848400000000000000000000000000000000000000
      0000000084000000000000000000000084000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000C6C6
      C60000000000C6C6C6000000000000000000000000008484840000FFFF00FF00
      FF0000FFFF000000000000FFFF00FF00FF0000FFFF000000000000FFFF00FF00
      FF0000FFFF0084848400000000000000000000000000C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000000
      000000000000000000000000000000000000000000000000000084848400C6C6
      C600C6C6C6008484840000000000000000000000000000000000000000000000
      0000000000000000000000000000000084000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000C6C6C60000000000C6C6C6000000000000000000848484000000000000FF
      FF000000000000FFFF00FF00FF0000FFFF00FF00FF0000FFFF000000000000FF
      FF00FF00FF0084848400000000000000000000000000C6C6C60000000000FFFF
      0000C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000008400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000008484840000FFFF000000
      000000FFFF00FF00FF0000FFFF00FF00FF0000FFFF00FF00FF0000FFFF000000
      000000FFFF0084848400000000000000000000000000C6C6C60000000000FFFF
      0000C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000008400000000000000
      0000000084000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000848484000000000000FF
      FF000000000000FFFF000000000000FFFF000000000000FFFF000000000000FF
      FF00000000008484840000000000000000000000000000000000000000000000
      0000FFFF0000FFFF0000C6C6C600C6C6C600C6C6C600C6C6C600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000008400000000000000
      0000000084000000840000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000084848400848484008484
      8400848484008484840084848400848484008484840084848400848484008484
      8400848484008484840000000000000000000000000000000000848484000000
      00000000000000000000C6C6C600C6C6C600C6C6C60084848400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000084000000
      8400000084000000840000008400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000C6C6C600C6C6C600C6C6C600C6C6C6000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000084000000840000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000084000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000084A5B500000829008494AD00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000BD5A5A00AD4A
      4200943942009439420094394200843142008431310084313100732931007321
      3100732131005A2131005A2121000000000000000000A5948400392918003929
      1800392918003929180039291800392918003929180039291800392918002929
      2900003152001063BD000029520094A5AD000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CE5A6B00F78C8C00E773
      7B00AD31100021181000BDB5B500BDB5B500CEC6C600CECEC600313942009429
      210094292100942121005A2131000000000000000000A5948400F7F7F700A594
      8400A5948400A5948400A5948400A5948400A5948400A59484007B7373000031
      6300006BD600108CE70029A5F700294A630000000000F7F7F700F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F7000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CE636B00FF949C00F784
      7B00E7737B005A4A420021292100846B6B00F7E7E700F7EFE70084736B009429
      21009429310094292100732131000000000000000000A5948400F7F7F700F7F7
      F700F7F7F700F7F7F700CED6D6007B8C8400524A5200394A520029395200105A
      84001094E70039C6FF00527B9C00ADBDCE0000000000F7F7F700000000000000
      0000F7F7F7000000000000000000000000000000000000000000F7F7F7000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000840000008400
      00008400000000000000000000000000000000000000CE6B6B00FF9C9C00F78C
      8C00F7847B005A4A42000000000021292100F7DED600F7E7D600736B5A00AD31
      3100AD31310094293100732931000000000000000000A5948400F7F7F700F7F7
      F700F7F7F700E7DEE7007B7B8400A59C9C00CEBDAD00CEA59C00636363002939
      3900397BAD00528CAD0094ADB5000000000000000000F7F7F700F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F7000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000840000008400
      00008400000000000000000000000000000000000000CE6B7B00FFA5B500FF9C
      9C00F78C8C005A4A42005A4A42005A4A42005A4A42005A524200735A5A00BD4A
      4200AD394200AD313100732931000000000000000000A5948400F7F7F700F7F7
      F700F7F7F700A5A5AD00BDADAD00FFF7E700FFE7E700F7D6BD00F7CEAD006363
      63007B84940094ADB500000000000000000000000000F7F7F700000000000000
      0000F7F7F7000000000000000000000000000000000000000000F7F7F7000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000E7737B00FFADB500FFAD
      B500FF9C9C00F78C8C00F7847B00E7737B00E76B7B00CE636B00CE5A6B00BD52
      5A00BD4A4200AD394200843131000000000000000000BD9C8400F7F7F700F7F7
      F700F7F7F700948C8400F7E7E700FFFFF700FFF7F700FFE7E700F7D6D600CEA5
      9C00394A520000000000000000000000000000000000F7F7F700F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F7000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000840000008400
      00008400000000000000000000000000000000000000E7848C00FFB5C600FFB5
      B500CE525A00BD524200BD4A4200BD393100AD392100AD312100942910009421
      0000BD525A00BD4A4200843131000000000000000000BD9C9C00F7F7F700F7F7
      F700F7F7F70094948400F7E7E70000000000FFFFF700FFF7F700FFE7E700E7BD
      AD004A5A630000000000000000000000000000000000F7F7F700F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F70000000000F7F7F700F7F7F7000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000840000008400
      00008400000000000000000000000000000000000000E78C8C00FFC6C600CE5A
      5A00F7F7F700F7F7F700FFFFF700F7F7F700F7EFE700F7DED600E7D6C600E7CE
      C60094210000BD525A00843142000000000000000000BDA59C00F7F7F700F7F7
      F700F7F7F700BDC6BD00BDBDBD000000000000000000FFFFF700FFF7E700A594
      840094949C0000000000000000000000000000000000F7F7F700000000000000
      0000F7F7F700F7F7F700F7F7F70000000000C6C6C60000000000F7F7F7000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008400
      00008400000084000000000000000000000000000000E7949C00FFC6C600CE63
      6B00F7F7F700F7F7F700F7F7F700FFFFF700F7F7F700F7EFE700F7DED600E7D6
      C60094291000CE5A5A00943942000000000000000000CEA59C00F7F7F700F7F7
      F700F7F7F700F7FFFF00BDADAD00BDBDBD00F7E7E700F7E7E700A5A59C00525A
      52000000000000000000000000000000000000000000F7F7F70000000000C6C6
      C60000000000F7F7F70000000000C6C6C60000000000C6C6C600000000000000
      0000000000000000000084000000840000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00008400000084000000840000000000000000000000F79C9C00FFC6C600E76B
      6B00F7F7F700F7F7F700F7F7F700F7F7F700FFFFF700F7F7F700F7EFE700F7DE
      D600AD312100CE636B00943942000000000000000000CEAD9C00F7F7F700F7F7
      F700F7F7F700F7F7F700F7FFFF00BDC6BD00949484007B7B73007B7B84003931
      29000000000000000000000000000000000000000000F7F7F700F7F7F7000000
      0000C6C6C60000000000C6C6C60000000000C6C6C60000000000C6C6C600C6C6
      C600C6C6C6000000000084000000840000000000000000000000000000000000
      0000000000000000000000000000840000008400000084000000000000000000
      00000000000084000000840000008400000000000000F7A59C00FFC6C600E773
      7B00F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700FFFFF700F7F7F700F7EF
      E700AD392100E76B7B00943942000000000000000000CEADAD00F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700A594840039291800392918003929
      1800000000000000000000000000000000000000000000000000000000000000
      000000000000C6C6C60000000000C6C6C60000000000C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C60084000000840000000000000000000000000000000000
      0000000000000000000000000000840000008400000084000000000000000000
      00000000000084000000840000008400000000000000F7ADB500FFC6C600F784
      8C00F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700FFFFF700F7F7
      F700BD3931004A182100AD4A42000000000000000000CEBDAD00F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700BD9C8400CEC6BD0039291800D6C6
      BD00000000000000000000000000000000000000000000000000000000000000
      00000000000000000000C6C6C60000000000C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C60084000000840000000000000000000000000000000000
      0000000000000000000000000000840000008400000084000000000000000000
      00000000000084000000840000008400000000000000F7ADB500FFC6C600FF8C
      8C00F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700FFFF
      F700BD4A4200AD4A5A00AD4A5A000000000000000000E7BDAD00F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700BD9C9C0039291800D6C6BD000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C6000000000084000000840000000000000000000000000000000000
      0000000000000000000000000000000000008400000084000000840000008400
      00008400000084000000840000000000000000000000F7B5B500F7B5B500F7AD
      B500F7ADB500F7A5B500F79C9C00E7949C00E78C8C00E78C8C00E7848C00E773
      7B00CE6B7B00CE6B6B00CE636B000000000000000000E7BDAD00E7BDAD00E7BD
      AD00E7BDAD00E7BDAD00CEBDAD00CEADAD00CEA59C00D6C6BD00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000084000000840000000000000000000000000000000000
      0000000000000000000000000000000000000000000084000000840000008400
      0000840000008400000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000847B
      7B00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000004A5A63004A5A63004A5A63004A5A
      6300525A63004252520042424200313131002121180021101800080808000800
      0000080008000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000847B
      7B00F7F7F700847B7B00847B7B00847B7B00847B7B00847B7B00847B7B00847B
      7B00847B7B000000000000000000000000004A5A63004A5A630073B5D600008C
      D600008CD600008CD600008CC6000884C600087BAD00087BAD0021739C00216B
      8C00214252000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000847B
      7B00F7F7F700F7F7F700F7F7F700F7F7F700F7E7E700F7DECE00DEC6CE00DEBD
      B500847B7B000000000000000000000000004A5A630084C6D6000073BD0084E7
      FF0063D6FF0052CEFF0052CEFF0042C6F70031B5F70031ADF70021A5E700088C
      D60021637B005A5A520000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000847B
      7B00F7F7F700F7F7F700F7F7F700FFFFF700F7F7F700F7DEE700F7CECE00DEC6
      B500847B7B00000000000000000000000000637B840084D6F7000073BD0094C6
      D60073DEFF0063D6FF0063D6FF0052CEFF0052C6FF0042BDF70031B5F70031AD
      F7000884D6002142520000000000000000000000000000000000000000008400
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000847B
      7B00F7F7F700F7F7F700F7F7F700F7F7F700FFF7F700F7E7E700F7DEE700DECE
      CE00847B7B00000000000000000000000000637B840084DEF70084CEE7000073
      BD0084E7FF0073D6FF0063DEFF0063D6FF0063D6FF0052CEFF0042C6F70042BD
      F70031B5F70021637B006B849400000000000000000000000000000000008400
      0000000000000000000000000000000000000000000084000000840000008400
      0000840000008400000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000A58C
      7B00F7F7F700F7F7F700F7F7F700F7F7F700FFFFF700F7F7F700F7E7E700F7CE
      CE00847B7B00000000000000000000000000637B840094E7F70094E7FF000073
      BD0094BDC60073DEFF0063DEFF0063DEFF0063DEFF0063D6FF0052D6FF0052CE
      FF0042BDF70031A5E7004A5A6300000000000000000000000000840000000000
      0000000000000000000000000000000000000000000000000000840000008400
      0000840000008400000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000A58C
      8C00F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700FFFFF700F7E7E700F7DE
      E700847B7B00000000000000000000000000637B840094E7F700A5EFFF0084CE
      E7000073BD0084E7FF0084E7FF0084E7FF0084E7FF0084E7FF0084E7FF0084E7
      FF0073DEFF0073DEFF0052ADD6004A5A63000000000000000000840000000000
      0000000000000000000000000000000000000000000000000000000000008400
      0000840000008400000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000A594
      8C00F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7E7
      E700847B7B00000000000000000000000000637B8400A5EFF700A5EFFF00A5EF
      FF0000639C000073BD000073BD000073BD000073BD000073BD000073BD000073
      BD000073BD000073BD000073BD000073BD000000000000000000840000000000
      0000000000000000000000000000000000000000000000000000840000000000
      0000840000008400000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000BD94
      8C00F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700FFFFF700F7F7
      F700847B7B00000000000000000000000000637B8400A5EFF700A5F7FF00A5EF
      FF00A5EFFF0084DEFF0063DEFF0063DEFF0063DEFF0063DEFF0063DEFF0063DE
      FF00637B84000000000000000000000000000000000000000000000000008400
      0000000000000000000000000000000000008400000084000000000000000000
      0000000000008400000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000BDA5
      8C00F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700847B
      7B00847B7B00000000000000000000000000637B8400A5F7F700B5F7F700A5F7
      FF00A5EFFF00A5EFFF0073DEFF00637B8400637B8400637B8400637B8400637B
      8400637B84000000000000000000000000000000000000000000000000000000
      0000840000008400000084000000840000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000BDA5
      A500F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700847B7B000000
      000000000000000000000000000000000000637B8400A5D6E700B5F7F700B5F7
      F700A5F7FF00A5EFFF00637B8400B5CECE000000000000000000000000000000
      0000000000009463420094634200946342000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000BDAD
      A500F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700A58C7B00BDBD
      B50000000000CEBDB500000000000000000000000000637B8400637B8400637B
      8400637B8400637B8400637B8400000000000000000000000000000000000000
      000000000000DEC6C60094634200946342000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000DEAD
      A500F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700A58C8C000000
      0000CEBDB5000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000094735200CEBDAD000000
      000000000000A58C7B00DECEC600947352000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000DEAD
      A500DEADA500DEADA500DEADA500DEADA500BDADA500BDA5A500BD948C00CEBD
      B500000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000A58C7B00A584
      7B00B5947B00C6BDAD0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000BDA594007B42100021080800948484000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000845A3100212121002121210021212100212121002121
      2100212121002121210021212100212121000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000D6734A00A5391000732100002118000000000000CEA59400210808002108
      0000A58C84000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000A54221008C2110008C211000731800007318
      00005A1000005A1000005A0800004208000000000000637B840052525A004242
      4A003131310021212100946B4A00F7E7CE00B59C8400B59C8400B59C8400B59C
      8400B59C8400B59C8400B59C8400212121000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000F763290000000000CEA594005A21000000000000BD734A00A53910002108
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000A5523900FFFFF700C69C9C00C69C9C00C69C
      9C00A59C9C00A5949C00A59484005A080000737B840021B5F700008CCE00008C
      CE00008CCE00008CCE0094734A00F7EFE700F7DECE00E7D6BD00E7CEBD00D6C6
      AD00D6B5AD00D6B5AD00B59C8400212121000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000F773290000000000000000007321000000000000D65A290000000000AD94
      8C00390800000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000C6634A00F7F7F700DE734A00C65A3900C65A
      3900C65A3900C65A3900A5949C005A1000007384840073CEF70010B5F70010AD
      F70000A5E7000094CE00A57B5A00F7F7F700C6AD9400C6AD9400C6A59400B59C
      8400D6C6AD00B59C8400B59C8400212121000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000E7946300F7732900A542100073210000945A4A00D65A290000000000CEAD
      940073210000000000000000000000000000000000008C848400081010000810
      1000081010000810100008101000C6735A00F7F7F700F7F7F700FFEFF700F7DE
      D600F7C6BD00F7B5AD00A59C9C005A1000008484840073D6F70031C6F70010B5
      F70000A5F700009CE700A5847300F7F7F700F7F7F700F7EFE700F7DECE00E7D6
      BD00734A31006342210052392100423121000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000840000000000000000000000000000000000000000000000000000000000
      000000000000FF844A00F76B31008C3918007B391000BD521800D65A2900BD42
      1000AD847300000000000000000000000000000000008C848400FFEFF700F7DE
      D600DED6D600DEC6BD00DEBDBD00DE847300F7F7F700F7947300DE7B5A00DE73
      4A00C65A3900C65A3900C69C9C0073100000848C940084DEF70042CEF70031C6
      F70010B5F700009CE700B58C7300F7F7F700C6AD9400C6AD9400C6A59400F7E7
      CE0084523100D6CEBD0063422100000000000000000000000000840000008400
      0000840000008400000084000000000000000000000000000000000000000000
      0000840000000000000000000000000000000000000000000000000000000000
      00000000000000000000FF947300F7632900D6846300D65A2900D65A3100D694
      7300E7BDAD00000000000000000000000000000000008C848400FFFFF700DE9C
      7300DE845A00DE845A00C67B5A00DE948400F7F7F700F7F7F700F7F7F700FFFF
      F700F7E7E700F7C6BD00C69C9C00731800008494940094E7F70063DEF70052CE
      F70031C6F70010ADF700B5948400F7F7F700F7F7F700F7F7F700F7F7F700F7EF
      E700845A31008452310000000000000000000000000000000000840000008400
      0000840000008400000000000000000000000000000000000000000000000000
      0000000000008400000000000000000000000000000000000000000000000000
      00000000000000000000000000005A524A00393929005A422900ADADAD000000
      00000000000000000000000000000000000000000000A5948400F7F7F700FFFF
      F700F7EFF700F7E7E700F7DED600DEA59C00F7F7F700FF9C8400FF9C8400F7D6
      D600DE734A008C2110008C2110007318000084949400A5EFF70084E7F70073DE
      F70052D6F70010ADF700B59C8400B5948400B58C7300A5847300A57B5A009473
      4A00946B4A000000000000000000000000000000000000000000840000008400
      0000840000000000000000000000000000000000000000000000000000000000
      0000000000008400000000000000000000000000000000000000000000000000
      0000000000000000000000000000736352005A4A4200393929004A5A52000000
      00000000000000000000000000000000000000000000A5949C00F7F7F700FFBD
      9C00F7A58400DE9C7300DE845A00F7B59C00F7F7F700F7F7F700F7F7F700F7F7
      F700F77B5A00F7BDAD008C211000C6B5B500949C9400B5F7FF00A5EFFF0094E7
      F70073D6F700109CCE00109CCE00109CCE001094CE00008CCE00008CCE00008C
      CE00312921000000000000000000000000000000000000000000840000008400
      0000000000008400000000000000000000000000000000000000000000000000
      0000000000008400000000000000000000000000000000000000000000000000
      00000000000000000000000000008C848400A5A5940073635200212931000000
      00000000000000000000000000000000000000000000A59C9C00F7F7F700F7F7
      F700F7F7F700FFEFF700F7E7E700F7BDAD00F7F7F700F7F7F700F7F7F700F7F7
      F700F7947300A5391000CEBDB50000000000949CAD00B5F7FF00A5F7FF00637B
      8400636B7300526B7300525A5A00525A5A0052525A00424A5A00216B8400008C
      CE0042394A000000000000000000000000000000000000000000840000000000
      0000000000000000000084000000840000000000000000000000000000000000
      0000840000000000000000000000000000000000000000000000000000000000
      00000000000000000000BDA5AD008C7B84000000000000000000393929000000
      00000000000000000000000000000000000000000000C6A5AD00F7F7F700FFD6
      BD00FFC6AD00F7DED6008C848400F7BDAD00F7B5AD00F7B5AD00F7A59C00F79C
      8400F79C8400DECEC600000000000000000094A5AD00B5F7FF00B5F7FF006384
      840094CECE0094EFF70084DEE70063CEE7005294AD00424A4A00217B9400008C
      CE00524A5A000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008400000084000000840000008400
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000A5848400BDBDAD0000000000000000005A4A42000000
      00000000000000000000000000000000000000000000C6B5AD00F7F7F700F7F7
      F700F7F7F700F7F7F700A5948400C6BDBD005A424A00B5C6C600000000000000
      00000000000000000000000000000000000094A5AD00B5F7F700B5F7FF00A5F7
      F70073949400A5F7F7006B7B730084CECE00526B73003152730063C6F70021B5
      F70052525A000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000008C848400000000000000000000000000BDA5AD00BDBD
      B5000000000000000000000000000000000000000000DEB5AD00F7F7F700F7F7
      F700F7F7F700F7F7F700A59C9C00735A4A00C6C6C60000000000000000000000
      0000000000000000000000000000000000000000000094A5AD0094A5AD0094A5
      AD00638C9400A5EFF700A5EFF70094DEE700425A5A0073848400848484007384
      8400000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000A5A5A500000000000000000000000000000000009494
      94000000000000000000000000000000000000000000DEB5AD00DEB5AD00C6B5
      AD00C6B5AD00C6A5AD00C69C9C00CEC6D6000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000084ADBD0084ADBD00849CAD000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000900000000100010000000000800400000000000000000000
      000000000000000000000000FFFFFF00FFFF000000000000FFFF000000000000
      001F000000000000000F00000000000000070000000000000003000000000000
      00010000000000000000000000000000001F000000000000001F000000000000
      001F0000000000008FF1000000000000FFF9000000000000FF75000000000000
      FF8F000000000000FFFF000000000000F80FFFFFF00FD248E0078001E003DFFA
      C0038000C001FDF8C00180008001DCFF800080008000DC78800080008000DC38
      800080000000FC1D800080000000DC1D800080000080DC3F8000800000008C7D
      8C00800080008CFDCE0186008001FDFFC601860080018FFDE0078600C003A925
      F80F860FE0078FFFFFFFC60FF01FFFFFC003E0018003FFFFC003800180038001
      C00380018AA38001C00380018013A001C003800188238001C00380018013A001
      C003900188238001C003B8018013A001C003A8018A238001C00380018013A001
      C003800188238001C003800180438001C017800180178001C00F800B800F8001
      C01F8007801FFFFFFFFF800FFFFFFFFFFFFFFFFFFBFFFFFFFF71E003F1FF8007
      FF36C001F0FF8007F516C001F07F8007DF31C001F03F8007FF76C001F01F8007
      BFF6C001F00F8007FFD1C001F0078007DFFFC001F00F800FFFBFC001F01F800F
      77FFC001F03F800777BFC001F07F800307FFC001F0FF8029AFD7E003F1FF801F
      8FE7FFFFFBFF803FDFC7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC387E1C3
      C00107C1C387E1C3800007C1C387E1C3000007C1C007E00300000101C007E003
      00000001C007E00300000001E10FF08700000001F39FF9CF00008003F39FF9CF
      0001C107FCFFFF3F0003C107F9E1879F0007E38FFBF18FDF81FFE3AFFBF18FDF
      C3FFE38FF9CDB39FFFFFFFFFFC1FF83FFFF3FFFFFFFFFFFFFFE1FF3FC007FFFF
      FFC1FE3F8003C001FF83C07F00018001F00788F700018001C10F04E700018001
      809F02C100008001805F20E60000A001000F30F680008001000F81FEDFE0A001
      200FC3BFE8218001200FFFB7EFF78AA1B01FFFB3F41780039C1FFFC1F7FBFFFF
      C03FFFF3F803FFFFF0FFFFF7FFFFFFFFFFFFFFF1FFFFFFFFC0018000000FF9FF
      80018000000FF9FF80018000000FF3C780018001000F73C780018003000F27FF
      80018007000F07C780018107000F00C780018187000F01E38001800F000403F1
      8001800F000006388001800F00000E388001800FF8001E388001801FFC003F01
      8001803FFE047F83FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE0030007
      FFFFEFFDE0030007FFFFC7FFE0030003FFFFC3FBE0030003EFFFE3F7E0030001
      EF83F1E7E0030001DFC3F8CFE0030000DFE3FC1FE0030000DFD3FE3FE0030007
      EF3BFC1FE0030007F0FFF8CFE00300F8FFFFE1E7E00381F8FFFFC3F3E007FF98
      FFFFC7FDE00FFFC3FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0FFFFFFFC00FFFF
      F087FE008000FFFFF487FE000000FFFFF6A7FE000000FFFFF02780000000FFF7
      F80780000001C1F7FC0780000003C3FBFE1F80000007C7FBFE1F80000007CBFB
      FE1F80010007DCF7FCDF80030007FF0FFCDF803F0007FFFFFDCF807F800FFFFF
      FDEF80FFF8FFFFFFFFFFFFFFFFFFFFFF00000000000000000000000000000000
      000000000000}
  end
  object PopupMenu: TPopupMenu
    Images = ImageList
    Left = 92
    Top = 509
    object Cut1: TMenuItem
      Action = acCut
    end
    object Copy1: TMenuItem
      Action = acCopy
    end
    object Paste1: TMenuItem
      Action = acPaste
    end
    object N2: TMenuItem
      Caption = '-'
    end
    object Undo2: TMenuItem
      Action = acUndo
    end
    object Redo2: TMenuItem
      Action = acRedo
    end
    object N3: TMenuItem
      Caption = '-'
    end
    object LPformat1: TMenuItem
      Action = acViewAsLP
      RadioItem = True
    end
    object NewLPscript2: TMenuItem
      Action = acViewAsMPS
      RadioItem = True
    end
  end
  object SynEditSearch: TSynEditSearch
    Left = 192
    Top = 480
  end
  object SynEditRegexSearch: TSynEditRegexSearch
    Left = 192
    Top = 512
  end
  object XLIViewActionList: TActionList
    Left = 11
    Top = 512
  end
  object XLINewActionList: TActionList
    Left = 40
    Top = 512
  end
  object SynXMLSyn: TSynXMLSyn
    ElementAttri.Style = []
    AttributeAttri.Foreground = clRed
    AttributeValueAttri.Foreground = clBlack
    AttributeValueAttri.Style = []
    NamespaceAttributeValueAttri.Style = []
    TextAttri.Style = []
    EntityRefAttri.Style = []
    ProcessingInstructionAttri.Foreground = clTeal
    CommentAttri.Background = clNone
    CommentAttri.Style = [fsItalic]
    WantBracesParsed = False
    Left = 664
    Top = 480
  end
  object ExportDialog: TSaveDialog
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 224
    Top = 480
  end
  object SynMacroRecorder: TSynMacroRecorder
    Editor = Editor
    RecordShortCut = 24658
    PlaybackShortCut = 24656
    Left = 224
    Top = 512
  end
  object OpenDialogBasis: TOpenDialog
    Filter = 'Basis file (*.bas)|*.bas'
    Left = 316
    Top = 483
  end
  object SaveDialogBasis: TSaveDialog
    Filter = 'Basis file (*.bas)|*.bas'
    Left = 316
    Top = 515
  end
end
