object HeaderOptionsFrame: THeaderOptionsFrame
  Left = 0
  Top = 0
  Width = 249
  Height = 422
  TabOrder = 0
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 65
    Height = 13
    Caption = '$HeaderType'
  end
  object HeaderLayer: TComboBox
    Left = 3
    Top = 27
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
end
