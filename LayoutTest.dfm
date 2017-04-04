object TestForm: TTestForm
  Left = 0
  Top = 0
  Caption = 'TestForm'
  ClientHeight = 516
  ClientWidth = 688
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object GridPanel1: TGridPanel
    Left = 384
    Top = 32
    Width = 209
    Height = 177
    Caption = 'GridPanel1'
    ColumnCollection = <
      item
        Value = 50.000000000000000000
      end
      item
        Value = 50.000000000000000000
      end>
    ControlCollection = <
      item
        Column = 0
        Control = RichEdit1
        Row = 0
      end
      item
        Column = 1
        Control = RichEdit2
        Row = 0
      end>
    RowCollection = <
      item
        Value = 50.000000000000000000
      end
      item
        Value = 50.000000000000000000
      end>
    TabOrder = 0
    DesignSize = (
      209
      177)
    object RichEdit1: TRichEdit
      Left = 1
      Top = 1
      Width = 103
      Height = 87
      Anchors = []
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      Lines.Strings = (
        'RichEdit1')
      ParentFont = False
      TabOrder = 0
      Zoom = 100
    end
    object RichEdit2: TRichEdit
      Left = 104
      Top = 1
      Width = 104
      Height = 87
      Align = alClient
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      Lines.Strings = (
        'RichEdit2')
      ParentFont = False
      TabOrder = 1
      Zoom = 100
    end
  end
  object GridPanel2: TGridPanel
    Left = 8
    Top = 8
    Width = 201
    Height = 121
    Caption = 'GridPanel2'
    ColumnCollection = <
      item
        Value = 100.000000000000000000
      end>
    ControlCollection = <
      item
        Column = 0
        Control = Edit1
        Row = 0
      end
      item
        Column = 0
        Control = Edit2
        Row = 1
      end
      item
        Column = 0
        Control = Edit3
        Row = 2
      end>
    RowCollection = <
      item
        Value = 50.000000000000000000
      end
      item
        Value = 50.000000000000000000
      end
      item
        SizeStyle = ssAuto
      end>
    TabOrder = 1
    object Edit1: TEdit
      AlignWithMargins = True
      Left = 4
      Top = 4
      Width = 193
      Height = 21
      Align = alTop
      Constraints.MinHeight = 12
      TabOrder = 0
      Text = 'Edit1'
    end
    object Edit2: TEdit
      AlignWithMargins = True
      Left = 4
      Top = 50
      Width = 193
      Height = 21
      Align = alTop
      Constraints.MinHeight = 21
      TabOrder = 1
      Text = 'Edit2'
    end
    object Edit3: TEdit
      AlignWithMargins = True
      Left = 4
      Top = 96
      Width = 193
      Height = 21
      Align = alTop
      Constraints.MinHeight = 12
      TabOrder = 2
      Text = 'Edit1'
    end
  end
  object GridPanel3: TGridPanel
    Left = 215
    Top = 21
    Width = 185
    Height = 186
    Caption = 'GridPanel3'
    ColumnCollection = <
      item
        Value = 100.000000000000000000
      end>
    ControlCollection = <
      item
        Column = 0
        Control = Edit4
        Row = 0
      end
      item
        Column = 0
        Control = Edit5
        Row = 1
      end
      item
        Column = 0
        Control = Edit6
        Row = 2
      end
      item
        Column = 0
        Control = Edit7
        Row = 3
      end>
    RowCollection = <
      item
        SizeStyle = ssAuto
      end
      item
        SizeStyle = ssAuto
      end
      item
        SizeStyle = ssAuto
      end
      item
        SizeStyle = ssAuto
      end>
    TabOrder = 2
    DesignSize = (
      185
      186)
    object Edit4: TEdit
      Left = 32
      Top = 1
      Width = 121
      Height = 21
      Anchors = []
      TabOrder = 0
      Text = 'Edit4'
    end
    object Edit5: TEdit
      Left = 32
      Top = 22
      Width = 121
      Height = 21
      Anchors = []
      TabOrder = 1
      Text = 'Edit5'
    end
    object Edit6: TEdit
      Left = 32
      Top = 43
      Width = 121
      Height = 21
      Anchors = []
      TabOrder = 2
      Text = 'Edit6'
    end
    object Edit7: TEdit
      Left = 32
      Top = 64
      Width = 121
      Height = 21
      Anchors = []
      TabOrder = 3
      Text = 'Edit7'
    end
  end
  object RichEdit3: TRichEdit
    Left = 20
    Top = 137
    Width = 185
    Height = 89
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Lines.Strings = (
      'RichEdit3'
      '3646')
    ParentFont = False
    TabOrder = 3
    WantTabs = True
    Zoom = 100
  end
  object StringGrid1: TStringGrid
    Left = 152
    Top = 296
    Width = 425
    Height = 169
    TabOrder = 4
  end
end
