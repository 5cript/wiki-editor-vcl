object HeaderOptionsFrame: THeaderOptionsFrame
  Left = 0
  Top = 0
  Width = 249
  Height = 422
  TabOrder = 0
  object Label1: TLabel
    Left = 3
    Top = 58
    Width = 65
    Height = 13
    Caption = '$HeaderType'
  end
  object Label2: TLabel
    Left = 0
    Top = 3
    Width = 249
    Height = 16
    Alignment = taCenter
    AutoSize = False
    Caption = '$Header'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold, fsUnderline]
    ParentFont = False
  end
  object HeaderLayer: TComboBox
    Left = 3
    Top = 75
    Width = 243
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 0
    Text = '$HeaderLayer2'
    OnChange = HeaderLayerChange
    Items.Strings = (
      '$HeaderLayer2'
      '$HeaderLayer3'
      '$HeaderLayer4'
      '$HeaderLayer5'
      '$HeaderLayer6')
  end
  object Button1: TButton
    Left = 3
    Top = 25
    Width = 243
    Height = 25
    Caption = '$RemoveElement'
    TabOrder = 1
    OnClick = Button1Click
  end
end
