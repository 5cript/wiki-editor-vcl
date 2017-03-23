object MainEditor: TMainEditor
  Left = 0
  Top = 0
  Caption = 'Media Wiki Editor 0.1'
  ClientHeight = 685
  ClientWidth = 1057
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = Menu
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object WikiElementCategoryGroup: TCategoryPanelGroup
    Left = 0
    Top = 0
    Height = 666
    VertScrollBar.Tracking = True
    HeaderFont.Charset = DEFAULT_CHARSET
    HeaderFont.Color = clWindowText
    HeaderFont.Height = -11
    HeaderFont.Name = 'Tahoma'
    HeaderFont.Style = []
    TabOrder = 0
    OnMouseUp = WikiElementCategoryGroupMouseUp
    object CategoryPanel2: TCategoryPanel
      Top = 158
      Height = 92
      Caption = '$StructureElements'
      TabOrder = 0
      ExplicitTop = 161
      object Panel4: TPanel
        Left = 3
        Top = 3
        Width = 190
        Height = 60
        Color = 13548930
        ParentBackground = False
        TabOrder = 0
        OnEndDrag = TextEndDrag
        OnStartDrag = GenericStartDrag
        object Image2: TImage
          Left = 8
          Top = 5
          Width = 50
          Height = 50
          DragMode = dmAutomatic
          Picture.Data = {
            0954506E67496D61676589504E470D0A1A0A0000000D49484452000000320000
            003208060000001E3F88B10000000467414D410000B18F0BFC61050000000970
            48597300000EC200000EC20115284A80000001074944415478DAED97C10D8240
            1045677B014F56801508774A80A394824728813B588154E049E845C7801702EA
            1A93FD92FF12B2CB8490FFB2B36C3037455680A10818144183226850040D8AA0
            41113428820645D09817E98F22DEC175B67916B2CD8AEC8C9133E8422D659B15
            31FA306AC72D657B21D2E86CEF3AF78493660BED44121D8B2ED77E8CC6AAE728
            7C3F0EB5A47E26A54EAD441E047AC5C150DB6CDD685C2FC358B522ED58B31641
            8522687C21A21B24885DE71E682B79EE124B9144F2AE90E8C71FAB4F5FD74FEE
            6B2D647EAAB3D24EA4D132DE292212DA1F88AB39D9572092EA1A16687DF526DB
            CAFF47FE108AA041113428820645D0A0081A144183226850048D3BB2EE207AFA
            97B6E50000000049454E44AE426082}
          Stretch = True
          OnEndDrag = Image2EndDrag
          OnStartDrag = GenericStartDrag
        end
        object Label4: TLabel
          Left = 68
          Top = 21
          Width = 82
          Height = 14
          Caption = '$HorizontalLine'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          OnEndDrag = TextEndDrag
          OnStartDrag = GenericStartDrag
        end
      end
    end
    object CategoryPanel1: TCategoryPanel
      Top = 0
      Height = 158
      Caption = '$UiTextElements'
      TabOrder = 1
      object Panel2: TPanel
        Left = 3
        Top = 3
        Width = 190
        Height = 60
        Color = 13548930
        ParentBackground = False
        TabOrder = 0
        OnEndDrag = HeaderEndDrag
        OnStartDrag = GenericStartDrag
        object HeaderImage: TImage
          Left = 8
          Top = 5
          Width = 50
          Height = 50
          DragMode = dmAutomatic
          Picture.Data = {
            0954506E67496D61676589504E470D0A1A0A0000000D49484452000000320000
            00320802000000915D1FE6000000017352474200AECE1CE90000000467414D41
            0000B18F0BFC6105000000097048597300000EC300000EC301C76FA864000000
            B04944415478DAEDD8C1118230108561D28B362115682170D452E488856805D8
            04F6128F0E90615E7632E332FCEFFE763E924B961063ACFC25C08205CB416015
            607DBAFA787B0BFDD37D1CAE074BB36A9EB13FE7B17E79B5E1F2C81AB9DE5C7C
            878D9598AF98D247A79944D6CCA5ABE62E59A5B1A6C3ED2CBD090B162C58B060
            C98F95F5EC91E5F41261C182050B9691556A4F74C39A36CBAEAF1E97FDF4EB41
            996F6F6EF747D27F020B162C0F8195932F7E6F01BB1CAF4EBD0000000049454E
            44AE426082}
          Stretch = True
          OnEndDrag = HeaderEndDrag
          OnStartDrag = GenericStartDrag
        end
        object Label1: TLabel
          Left = 68
          Top = 21
          Width = 46
          Height = 14
          Caption = '$Header'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          OnEndDrag = HeaderEndDrag
          OnStartDrag = GenericStartDrag
        end
      end
      object Panel3: TPanel
        Left = 3
        Top = 69
        Width = 190
        Height = 60
        Color = 13548930
        ParentBackground = False
        TabOrder = 1
        OnEndDrag = TextEndDrag
        OnStartDrag = GenericStartDrag
        object TextImge: TImage
          Left = 8
          Top = 5
          Width = 50
          Height = 50
          DragMode = dmAutomatic
          Picture.Data = {
            0954506E67496D61676589504E470D0A1A0A0000000D49484452000000320000
            00320802000000915D1FE60000000467414D410000B18F0BFC61050000000970
            48597300000EC300000EC301C76FA864000000CB4944415478DAEDD8BD0DC230
            1086E17817A0404C0013C0127450C20094E968A0842E4B8409C204880676313F
            4A11A2D89CE12219F17EF5E9FCF8E4C667ACB5497C31B060C18A20B0945987B9
            99ECD50E9CE57637FE0B5673CB17F6707329169D7AC9753BEA2E8F6DB0DCED04
            AC0ACD5D10C67AB61B78EE286495952745D679E599BC9CF5284DFB6AAC75AFF0
            BC8700D6BDD734C954586F13C01207162C58B060C182050B162C58ADB32A5F53
            58612A2DD797ACC6B5896CCDA0CFAA4FC8998F81BFBB7683050B16ACA872030B
            336AAC873724110000000049454E44AE426082}
          Stretch = True
          OnEndDrag = TextEndDrag
          OnStartDrag = GenericStartDrag
        end
        object Label2: TLabel
          Left = 68
          Top = 21
          Width = 53
          Height = 14
          Caption = '$TextBox'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          OnEndDrag = TextEndDrag
          OnStartDrag = GenericStartDrag
        end
      end
    end
  end
  object Panel1: TPanel
    Left = 200
    Top = 0
    Width = 857
    Height = 666
    Align = alClient
    Caption = 'Panel1'
    TabOrder = 1
    object Splitter1: TSplitter
      Left = 560
      Top = 1
      Width = 6
      Height = 664
      Align = alRight
      Color = clSilver
      ParentColor = False
      ExplicitLeft = 491
      ExplicitHeight = 655
    end
    object PageContainer: TScrollBox
      Left = 1
      Top = 1
      Width = 559
      Height = 664
      Align = alClient
      DoubleBuffered = True
      DragMode = dmAutomatic
      Color = clWhite
      ParentColor = False
      ParentDoubleBuffered = False
      TabOrder = 0
      OnDragOver = ViewportDragOver
      OnResize = PageContainerResize
      object Viewport: TGridPanel
        Left = 0
        Top = 0
        Width = 300
        Height = 529
        BevelOuter = bvNone
        ColumnCollection = <
          item
            Value = 100.000000000000000000
          end>
        ControlCollection = <>
        RowCollection = <
          item
            SizeStyle = ssAuto
            Value = 100.000000000000000000
          end>
        TabOrder = 0
        VerticalAlignment = taAlignTop
        OnDragOver = ViewportDragOver
      end
    end
    object PropertyControlPane: TPanel
      Left = 566
      Top = 1
      Width = 290
      Height = 664
      Align = alRight
      TabOrder = 1
      OnResize = PropertyControlPaneResize
      object Log: TRichEdit
        Left = 8
        Top = 446
        Width = 305
        Height = 179
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Lines.Strings = (
          'Log')
        ParentFont = False
        ScrollBars = ssVertical
        TabOrder = 0
        Zoom = 100
      end
      object StartComponentSelect: TBitBtn
        Left = 6
        Top = 8
        Width = 307
        Height = 45
        BiDiMode = bdLeftToRight
        Caption = '$Select'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -21
        Font.Name = 'Tahoma'
        Font.Style = []
        Glyph.Data = {
          360C0000424D360C000000000000360000002800000020000000200000000100
          180000000000000C0000120B0000120B00000000000000000000FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFCFCFCF000000000000636363FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFC3C3C30000000000003C3C3CFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFC3C3C30000000000003C3C3CFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFC3C3C30000000000003C3C3CFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD3D3D39898
          984D4D4D2D2D2D0000000000000D0D0D4C4C4C9A9A9AD4D4D4FFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD1D1D16868680D0D0D0000
          000000000000000000000000000000000000000000000E0E0E6A6A6AD3D3D3FF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA5A5A51919190000000000000606
          062222223232320000000000001111112A2A2A0C0C0C0000000000001A1A1AA5
          A5A5FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF8989890101010000000303033636368383
          83C4C4C4ACACAC000000000000353535CECECE9797974A4A4A0B0B0B00000003
          03038E8E8EFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFF9D9D9D0101010000000F0F0F656565CCCCCCF9F9
          F9FFFFFFC3C3C30000000000003C3C3CFFFFFFFCFCFCDCDCDC8383831F1F1F00
          00000101019E9E9EFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFD3D3D31717170000000E0E0E727272E7E7E7FFFFFFFFFF
          FFFFFFFFC3C3C30000000000003C3C3CFFFFFFFFFFFFFFFFFFF5F5F59797971E
          1E1E000000181818D4D4D4FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFCFCFC696969000000030303585858E2E2E2FFFFFFFFFFFFFFFF
          FFFFFFFFC3C3C30000000000003C3C3CFFFFFFFFFFFFFFFFFFFFFFFFF4F4F480
          80800B0B0B000000696969FCFCFCFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFD3D3D3101010000000272727B7B7B7FFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFC3C3C30000000000003C3C3CFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD8
          D8D8464646000000111111D3D3D3FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFF8D8D8D000000020202626262EEEEEEFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFC3C3C30000000000003C3C3CFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA
          FAFA9090900B0B0B0000008D8D8DFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFF4D4D4D000000111111999999FFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFC3C3C30000000000003C3C3CFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFC5C5C52727270000004D4D4DFFFFFFFFFFFFFFFFFFFFFFFF1C1C1C1C1C1C
          1C1C1C1C1C1C0404040000000404041414141C1C1C1C1C1C1C1C1C1C1C1C1C1C
          1C1C1C1C1515150000000000000707071C1C1C1C1C1C1C1C1C1C1C1C1C1C1C1C
          1C1C1818180707070000000404041C1C1C1C1C1C1C1C1C1C1C1C000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          00000000000000000000000000000000000000000000000000001C1C1C1C1C1C
          1C1C1C1C1C1C0202020000000505051515151C1C1C1C1C1C1C1C1C1C1C1C1C1C
          1C1C1C1C1515150000000000000707071C1C1C1C1C1C1C1C1C1C1C1C1C1C1C1C
          1C1C1919190808080000000101011C1C1C1C1C1C1C1C1C1C1C1CFFFFFFFFFFFF
          FFFFFFFFFFFF2424240000001C1C1CAFAFAFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFC3C3C30000000000003C3C3CFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFD5D5D5383838000000242424FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFF4F4F4F0000000A0A0A878787FDFDFDFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFC3C3C30000000000003C3C3CFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFB6B6B61B1B1B0000004F4F4FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFF8D8D8D0000000000004A4A4ADFDFDFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFC3C3C30000000000003C3C3CFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4
          F4F47575750404040000008D8D8DFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFD3D3D3111111000000161616969696FDFDFDFFFFFFFFFFFFFFFF
          FFFFFFFFC3C3C30000000000003C3C3CFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBD
          BDBD2C2C2C000000111111D3D3D3FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFCFCFC696969000000000000353535BFBFBFFFFFFFFFFFFFFFFF
          FFFFFFFFC3C3C30000000000003C3C3CFFFFFFFFFFFFFFFFFFFFFFFFDCDCDC56
          56560101010000006B6B6BFCFCFCFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFD4D4D41B1B1B000000030303434343BEBEBEFEFEFEFFFF
          FFFFFFFFC3C3C30000000000003C3C3CFFFFFFFFFFFFFFFFFFD7D7D76161610A
          0A0A0000001C1C1CD6D6D6FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFAAAAAA040404000000030303323232929292DDDD
          DDFFFFFFC3C3C30000000000003C3C3CFFFFFFE7E7E7A9A9A949494909090900
          0000060606ABABABFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF9191910202020000000000001212124545
          457F7F7F8080800000000000002929298B8B8B5454541D1D1D00000000000002
          0202929292FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA6A6A61C1C1C0000000000000000
          000808081212120000000000000606060B0B0B0000000000000000001C1C1CA8
          A8A8FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD5D5D56C6C6C0E0E0E0000
          000000000000000000000000000000000000000000000E0E0E6D6D6DD5D5D5FF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD4D4D49A9A
          9A5252522020200000000000000C0C0C5151519A9A9AD4D4D4FFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFC3C3C30000000000003C3C3CFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFC3C3C30000000000003C3C3CFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFC3C3C30000000000003C3C3CFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFCFCFCF000000000000636363FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
        ParentBiDiMode = False
        ParentFont = False
        Spacing = 10
        TabOrder = 1
        OnClick = StartComponentSelectClick
      end
      object PropertyTabs: TTabControl
        Left = 6
        Top = 59
        Width = 307
        Height = 381
        TabOrder = 2
        Tabs.Strings = (
          '$PTabsSpecific'
          '$PTabsStyleOpts')
        TabIndex = 0
        OnChanging = PropertyTabsChanging
        object ElementSpecificOptions: TPanel
          Left = 4
          Top = 24
          Width = 299
          Height = 353
          Align = alClient
          TabOrder = 0
        end
        object StyleOptions: TPanel
          Left = 4
          Top = 24
          Width = 299
          Height = 353
          Align = alClient
          TabOrder = 1
          Visible = False
        end
      end
    end
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 666
    Width = 1057
    Height = 19
    Panels = <>
  end
  object Menu: TMainMenu
    Left = 1000
    Top = 24
    object File1: TMenuItem
      Caption = '$File'
      object NewArticle1: TMenuItem
        Caption = '$NewArticle'
        OnClick = NewArticle1Click
      end
      object OpenArticle1: TMenuItem
        Caption = '$OpenArticle'
        ShortCut = 16463
        OnClick = OpenArticle1Click
      end
      object SaveArticleAs1: TMenuItem
        Caption = '$SaveArticleAs'
        ShortCut = 24659
        OnClick = SaveArticleAs1Click
      end
      object SaveArticle1: TMenuItem
        Caption = '$SaveArticle'
        ShortCut = 16467
        OnClick = SaveArticle1Click
      end
      object Autosave1: TMenuItem
        Caption = '$Autosave'
        Checked = True
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = '$Exit'
        ShortCut = 24644
        OnClick = Exit1Click
      end
    end
    object Help1: TMenuItem
      Caption = '$Help'
      object About1: TMenuItem
        Caption = '$Licensing'
        OnClick = About1Click
      end
    end
    object AllSettings1: TMenuItem
      Caption = '$AllSettings'
      object AllSettings2: TMenuItem
        Caption = '$AllSettings'
        OnClick = AllSettings2Click
      end
      object CaptionSettings1: TMenuItem
        Caption = '$BackupSettings'
        OnClick = CaptionSettings1Click
      end
    end
    object Debug1: TMenuItem
      Caption = '$Debug'
      Visible = False
      object AddTestElements1: TMenuItem
        Caption = '$controller->test'
        OnClick = AddTestElements1Click
      end
      object estFormShowModal1: TMenuItem
        Caption = '$TestForm->ShowModal'
        OnClick = estFormShowModal1Click
      end
      object loadCursor1: TMenuItem
        Caption = '$loadCursor'
      end
      object initLocals1: TMenuItem
        Caption = '$initLocals'
        OnClick = initLocals1Click
      end
    end
  end
  object AppEvents: TApplicationEvents
    OnMessage = AppEventsMessage
    Left = 952
    Top = 664
  end
end
