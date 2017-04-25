object TableOptionsFrame: TTableOptionsFrame
  Left = 0
  Top = 0
  Width = 249
  Height = 547
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
  object Label1: TLabel
    Left = 1
    Top = 227
    Width = 97
    Height = 13
    Caption = '$TableCellAttributes'
  end
  object Label3: TLabel
    Left = 3
    Top = 127
    Width = 101
    Height = 13
    Caption = '$TableRowAttributes'
  end
  object TableAttributes: TValueListEditor
    Left = 3
    Top = 46
    Width = 243
    Height = 75
    KeyOptions = [keyEdit, keyAdd, keyDelete, keyUnique]
    PopupMenu = ChangeStyleMenu
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
    Top = 327
    Width = 243
    Height = 17
    Caption = '$SelectedCellIsHeaderCell'
    TabOrder = 1
    OnClick = HeaderCellCheckerClick
  end
  object CellAttributes: TValueListEditor
    Left = 3
    Top = 246
    Width = 243
    Height = 75
    KeyOptions = [keyEdit, keyAdd, keyDelete, keyUnique]
    PopupMenu = ChangeStyleMenu
    TabOrder = 2
    TitleCaptions.Strings = (
      '$Key'
      '$Value')
    OnValidate = CellAttributesValidate
    ColWidths = (
      71
      166)
  end
  object RowAttributes: TValueListEditor
    Left = 1
    Top = 146
    Width = 243
    Height = 75
    KeyOptions = [keyEdit, keyAdd, keyDelete, keyUnique]
    PopupMenu = ChangeStyleMenu
    TabOrder = 3
    TitleCaptions.Strings = (
      '$Key'
      '$Value')
    OnValidate = CellAttributesValidate
    ColWidths = (
      71
      166)
  end
  object Button1: TButton
    Left = 3
    Top = 350
    Width = 243
    Height = 25
    Caption = '$ChangeTableSize'
    TabOrder = 4
    OnClick = Button1Click
  end
  object ChangeStyleMenu: TPopupMenu
    Left = 192
    Top = 384
    object Change1: TMenuItem
      Caption = '$ChangeTableStyle'
      OnClick = Change1Click
    end
    object ChangeClass1: TMenuItem
      Caption = '$ChangeTableClass'
      OnClick = ChangeClass1Click
    end
  end
end
