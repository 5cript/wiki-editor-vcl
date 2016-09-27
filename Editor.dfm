object MainEditor: TMainEditor
  Left = 0
  Top = 0
  Caption = 'Media Wiki Editor 0.1'
  ClientHeight = 617
  ClientWidth = 1014
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = Menu
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 632
    Top = 414
    Width = 75
    Height = 25
    Caption = 'Button1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = Button1Click
  end
  object PageContainer: TScrollBox
    Left = 8
    Top = 8
    Width = 729
    Height = 400
    DoubleBuffered = True
    Color = clWhite
    ParentColor = False
    ParentDoubleBuffered = False
    TabOrder = 1
  end
  object Edit1: TEdit
    Left = 488
    Top = 414
    Width = 121
    Height = 21
    TabOrder = 2
    Text = 'Edit1'
  end
  object RichEdit1: TRichEdit
    Left = 240
    Top = 424
    Width = 185
    Height = 89
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Lines.Strings = (
      'RichEdit1')
    ParentFont = False
    TabOrder = 3
    Zoom = 100
  end
  object Panel1: TPanel
    Left = 8
    Top = 414
    Width = 185
    Height = 22
    BevelOuter = bvNone
    Caption = 'Panel1'
    Color = clNavy
    ParentBackground = False
    TabOrder = 4
  end
  object DrawGrid1: TDrawGrid
    Left = 760
    Top = 414
    Width = 345
    Height = 129
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
    TabOrder = 5
    OnDrawCell = DrawGrid1DrawCell
    OnGetEditMask = DrawGrid1GetEditMask
    OnGetEditText = DrawGrid1GetEditText
  end
  object StringGrid1: TStringGrid
    Left = 743
    Top = 216
    Width = 320
    Height = 120
    Color = clHighlight
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goEditing]
    TabOrder = 6
  end
  object Menu: TMainMenu
    Left = 912
    Top = 8
    object File1: TMenuItem
      Caption = '$File'
      object OpenArticle1: TMenuItem
        Caption = '$OpenArticle'
        ShortCut = 16463
      end
      object SaveArticleAs1: TMenuItem
        Caption = '$SaveArticleAs'
      end
      object SaveArticle1: TMenuItem
        Caption = '$SaveArticle'
        ShortCut = 16467
      end
      object Autosave1: TMenuItem
        Caption = '$Autosave'
        Checked = True
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = '$Exit'
        OnClick = Exit1Click
      end
    end
    object Help1: TMenuItem
      Caption = '$Help'
      object About1: TMenuItem
        Caption = '$About'
        OnClick = About1Click
      end
    end
  end
end
