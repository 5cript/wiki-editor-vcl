object TableOptionsFrame: TTableOptionsFrame
  Left = 0
  Top = 0
  Width = 249
  Height = 422
  TabOrder = 0
  object AttributeLbl: TLabel
    Left = 3
    Top = 3
    Width = 80
    Height = 13
    Caption = '$TableAttributes'
  end
  object TableAttributes: TValueListEditor
    Left = 3
    Top = 22
    Width = 243
    Height = 182
    KeyOptions = [keyEdit, keyAdd, keyDelete, keyUnique]
    TabOrder = 0
    TitleCaptions.Strings = (
      '$Key'
      '$Value')
    OnValidate = TableAttributesValidate
    ColWidths = (
      71
      166)
  end
  object HeaderCellChecker: TCheckBox
    Left = 3
    Top = 210
    Width = 166
    Height = 17
    Caption = '$SelectedCellIsHeaderCell'
    TabOrder = 1
  end
end
