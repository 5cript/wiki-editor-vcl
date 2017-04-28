object ResizeDialog: TResizeDialog
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = 'Resize Dialog'
  ClientHeight = 97
  ClientWidth = 274
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 11
    Width = 60
    Height = 13
    Caption = '$TableWidth'
  end
  object Label2: TLabel
    Left = 8
    Top = 39
    Width = 63
    Height = 13
    Caption = '$TableHeight'
  end
  object TableWidth: TSpinEdit
    Left = 137
    Top = 8
    Width = 129
    Height = 22
    MaxValue = 500
    MinValue = 1
    TabOrder = 0
    Value = 0
  end
  object TableHeight: TSpinEdit
    Left = 137
    Top = 36
    Width = 129
    Height = 22
    MaxValue = 500
    MinValue = 1
    TabOrder = 1
    Value = 0
  end
  object Button1: TButton
    Left = 19
    Top = 64
    Width = 120
    Height = 25
    Caption = '$Ok'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 145
    Top = 64
    Width = 120
    Height = 25
    Caption = '$Cancel'
    TabOrder = 3
    OnClick = Button2Click
  end
end
