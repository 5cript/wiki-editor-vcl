object HeaderOptionsFrame: THeaderOptionsFrame
  Left = 0
  Top = 0
  Width = 249
  Height = 422
  TabOrder = 0
  object Label1: TLabel
    Left = 16
    Top = 34
    Width = 65
    Height = 13
    Caption = '$HeaderType'
  end
  object HeaderLayer: TComboBox
    Left = 11
    Top = 53
    Width = 225
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
    Top = 3
    Width = 243
    Height = 25
    Caption = '$RemoveElement'
    TabOrder = 1
    OnClick = Button1Click
  end
end
