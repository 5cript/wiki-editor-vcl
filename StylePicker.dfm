object FrameStylePicker: TFrameStylePicker
  Left = 0
  Top = 0
  Caption = 'FrameStylePicker'
  ClientHeight = 215
  ClientWidth = 445
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 13
    Width = 53
    Height = 13
    Caption = '$FontColor'
  end
  object Label2: TLabel
    Left = 8
    Top = 42
    Width = 47
    Height = 13
    Caption = '$FontSize'
  end
  object Label3: TLabel
    Left = 8
    Top = 72
    Width = 87
    Height = 13
    Caption = '$BackgroundColor'
  end
  object ChangeFontColor: TButton
    Left = 127
    Top = 8
    Width = 121
    Height = 25
    Caption = '$Change'
    TabOrder = 0
    OnClick = FontColorExampleClick
  end
  object FontSize: TSpinEdit
    Left = 127
    Top = 39
    Width = 121
    Height = 22
    MaxValue = 9001
    MinValue = 1
    TabOrder = 1
    Value = 1
    OnChange = FontSizeChange
  end
  object ExampleFrame: TPanel
    Left = 254
    Top = 8
    Width = 185
    Height = 169
    Caption = '$Example'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentBackground = False
    ParentFont = False
    TabOrder = 2
  end
  object ChangeBackgroundColor: TButton
    Left = 127
    Top = 67
    Width = 121
    Height = 25
    Caption = '$Change'
    TabOrder = 3
    OnClick = ChangeBackgroundColorClick
  end
  object BoldState: TCheckBox
    Left = 8
    Top = 104
    Width = 97
    Height = 17
    Caption = '$BoldFont'
    TabOrder = 4
    OnClick = BoldStateClick
  end
  object ItalicState: TCheckBox
    Left = 8
    Top = 127
    Width = 97
    Height = 17
    Caption = '$ItalicFont'
    TabOrder = 5
    OnClick = ItalicStateClick
  end
  object Button1: TButton
    Left = 304
    Top = 183
    Width = 133
    Height = 25
    Caption = '$Cancel'
    TabOrder = 6
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 165
    Top = 183
    Width = 133
    Height = 25
    Caption = '$Ok'
    TabOrder = 7
    OnClick = Button2Click
  end
  object Alignment: TComboBox
    Left = 8
    Top = 150
    Width = 145
    Height = 21
    TabOrder = 8
    Text = '$AlignLeft'
    OnChange = AlignmentChange
    Items.Strings = (
      '$AlignLeft'
      '$AlignCenter'
      '$AlignRight')
  end
  object ColorDialog: TColorDialog
    Color = 14717791
    CustomColors.Strings = (
      'ColorA=FFFFFFFF'
      'ColorB=FFFFFFFF'
      'ColorC=FFFFFFFF'
      'ColorD=FFFFFFFF'
      'ColorE=FFFFFFFF'
      'ColorF=FFFFFFFF'
      'ColorG=FFFFFFFF'
      'ColorH=FFFFFFFF'
      'ColorI=FFFFFFFF'
      'ColorJ=FFFFFFFF'
      'ColorK=FFFFFFFF'
      'ColorL=FFFFFFFF'
      'ColorM=FFFFFFFF'
      'ColorN=FFFFFFFF'
      'ColorO=FFFFFFFF'
      'ColorP=FFFFFFFF')
    Options = [cdFullOpen]
    Left = 552
    Top = 144
  end
end
