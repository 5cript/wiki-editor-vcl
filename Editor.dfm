object MainEditor: TMainEditor
  Left = 0
  Top = 0
  Caption = 'Media Wiki Editor 0.1'
  ClientHeight = 466
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
  object Button1: TButton
    Left = 632
    Top = 414
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 0
    OnClick = Button1Click
  end
  object PageContainer: TScrollBox
    Left = 8
    Top = 8
    Width = 729
    Height = 400
    Color = clWhite
    ParentColor = False
    TabOrder = 1
    object TestHeader: TRichEdit
      Left = 11
      Top = 17
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
      TabOrder = 0
      Zoom = 100
      OnEnter = TestHeaderEnter
    end
    object Line: TPanel
      Left = 11
      Top = 43
      Width = 609
      Height = 1
      BevelEdges = []
      BevelOuter = bvNone
      Color = clGray
      ParentBackground = False
      TabOrder = 1
    end
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
