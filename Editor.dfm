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
    Top = 264
    Width = 745
    Height = 377
    Color = clWhite
    ParentBackground = False
    TabOrder = 0
  end
  object Button1: TButton
    Left = 8
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Menu: TMainMenu
    Left = 912
    Top = 8
    object File1: TMenuItem
      Caption = '$File'
      object OpenArticle1: TMenuItem
        Caption = '$OpenArticle'
      end
      object SaveArticle1: TMenuItem
        Caption = '$SaveArticle'
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
