object TableOptionsFrame: TTableOptionsFrame
  Left = 0
  Top = 0
  Width = 249
  Height = 547
  TabOrder = 0
  OnResize = FrameResize
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
  object ScrollBox: TScrollBox
    Left = 0
    Top = 25
    Width = 249
    Height = 432
    BevelOuter = bvNone
    BorderStyle = bsNone
    TabOrder = 0
    object RowAttrLabel: TLabel
      Left = 3
      Top = 189
      Width = 101
      Height = 13
      Caption = '$TableRowAttributes'
    end
    object CellAttrLabel: TLabel
      Left = 3
      Top = 289
      Width = 97
      Height = 13
      Caption = '$TableCellAttributes'
    end
    object AttributeLbl: TLabel
      Left = 3
      Top = 89
      Width = 80
      Height = 13
      Caption = '$TableAttributes'
    end
    object RowAttributes: TValueListEditor
      Left = 3
      Top = 208
      Width = 220
      Height = 75
      KeyOptions = [keyEdit, keyAdd, keyDelete, keyUnique]
      PopupMenu = ChangeStyleMenu
      TabOrder = 0
      TitleCaptions.Strings = (
        '$Key'
        '$Value')
      OnMouseDown = RowAttributesMouseDown
      OnValidate = RowAttributesValidate
      ColWidths = (
        71
        143)
    end
    object CellAttributes: TValueListEditor
      Left = 3
      Top = 308
      Width = 226
      Height = 75
      KeyOptions = [keyEdit, keyAdd, keyDelete, keyUnique]
      PopupMenu = ChangeStyleMenu
      TabOrder = 1
      TitleCaptions.Strings = (
        '$Key'
        '$Value')
      OnMouseDown = CellAttributesMouseDown
      OnValidate = CellAttributesValidate
      ColWidths = (
        71
        149)
    end
    object TableAttributes: TValueListEditor
      Left = 3
      Top = 108
      Width = 220
      Height = 75
      KeyOptions = [keyEdit, keyAdd, keyDelete, keyUnique]
      PopupMenu = ChangeStyleMenu
      TabOrder = 2
      TitleCaptions.Strings = (
        '$Key'
        '$Value')
      OnMouseDown = TableAttributesMouseDown
      OnValidate = TableAttributesValidate
      ColWidths = (
        71
        143)
    end
    object Button1: TButton
      Left = 3
      Top = 26
      Width = 220
      Height = 25
      Caption = '$ChangeTableSize'
      TabOrder = 3
      OnClick = Button1Click
    end
    object HeaderCellChecker: TCheckBox
      Left = 3
      Top = 3
      Width = 243
      Height = 17
      Caption = '$SelectedCellIsHeaderCell'
      TabOrder = 4
      OnClick = HeaderCellCheckerClick
    end
    object Button2: TButton
      Left = 3
      Top = 57
      Width = 220
      Height = 25
      Caption = '$RemoveElement'
      TabOrder = 5
      OnClick = Button2Click
    end
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
