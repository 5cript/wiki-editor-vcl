object ListOptionsFrame: TListOptionsFrame
  Left = 0
  Top = 0
  Width = 249
  Height = 422
  TabOrder = 0
  object Label1: TLabel
    Left = 0
    Top = 3
    Width = 249
    Height = 16
    Alignment = taCenter
    AutoSize = False
    Caption = '$List'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold, fsUnderline]
    ParentFont = False
  end
  object RemoveList: TButton
    Left = 3
    Top = 25
    Width = 243
    Height = 25
    Caption = '$RemoveElement'
    TabOrder = 0
    OnClick = RemoveListClick
  end
end
