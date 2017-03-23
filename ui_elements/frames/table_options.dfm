object TableOptionsFrame: TTableOptionsFrame
  Left = 0
  Top = 0
  Width = 249
  Height = 422
  TabOrder = 0
  object AttributeLbl: TLabel
    Left = 3
    Top = 27
    Width = 80
    Height = 13
    Caption = '$TableAttributes'
  end
  object Label2: TLabel
    Left = 0
    Top = 3
    Width = 249
    Height = 16
    Alignment = taCenter
    AutoSize = False
    Caption = '$Table'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold, fsUnderline]
    ParentFont = False
  end
  object TableAttributes: TValueListEditor
    Left = 3
    Top = 46
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
    Top = 234
    Width = 166
    Height = 17
    Caption = '$SelectedCellIsHeaderCell'
    TabOrder = 1
  end
end
