object MainEditor: TMainEditor
  Left = 0
  Top = 0
  Caption = 'Media Wiki Editor 0.1'
  ClientHeight = 651
  ClientWidth = 764
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = Menu
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object PageContainer: TPanel
    Left = 8
    Top = 8
    Width = 745
    Height = 377
    Color = clWhite
    ParentBackground = False
    TabOrder = 0
  end
  object TestHeader: TRichEdit
    Left = 88
    Top = 436
    Width = 185
    Height = 27
    BevelEdges = []
    BorderStyle = bsNone
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    Lines.Strings = (
      'TestEdit')
    ParentFont = False
    TabOrder = 1
    Zoom = 100
    OnEnter = TestHeaderEnter
  end
  object Button1: TButton
    Left = 352
    Top = 438
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Line: TPanel
    Left = 24
    Top = 48
    Width = 609
    Height = 2
    BevelEdges = []
    BevelOuter = bvNone
    Color = clGray
    ParentBackground = False
    TabOrder = 3
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
  end
end
