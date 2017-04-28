object LogWindow: TLogWindow
  Left = 0
  Top = 0
  Caption = 'Log'
  ClientHeight = 289
  ClientWidth = 619
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = LogWindowMenu
  OldCreateOrder = False
  OnCreate = FormCreate
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object Log: TRichEdit
    Left = 0
    Top = 0
    Width = 619
    Height = 289
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    PlainText = True
    ScrollBars = ssVertical
    TabOrder = 0
    Zoom = 100
  end
  object LogWindowMenu: TMainMenu
    Left = 384
    Top = 128
    object File1: TMenuItem
      Caption = '$File'
      object SaveLog1: TMenuItem
        Caption = '$SaveLog'
        OnClick = SaveLog1Click
      end
      object ClearLog1: TMenuItem
        Caption = '$ClearLog'
        OnClick = ClearLog1Click
      end
    end
  end
end
