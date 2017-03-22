object BackupSettingsDialog: TBackupSettingsDialog
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = '$BackupSettings'
  ClientHeight = 175
  ClientWidth = 470
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 16
    Width = 78
    Height = 13
    Caption = '$BackupInterval'
  end
  object Label2: TLabel
    Left = 16
    Top = 67
    Width = 65
    Height = 13
    Caption = '$MaxBackups'
  end
  object OldestBackup: TLabel
    Left = 16
    Top = 112
    Width = 71
    Height = 13
    Caption = '$OldestBackup'
  end
  object IntervalLabel: TLabel
    Left = 445
    Top = 16
    Width = 12
    Height = 13
    Caption = '15'
  end
  object Interval: TTrackBar
    Left = 200
    Top = 12
    Width = 239
    Height = 35
    Max = 120
    Min = 5
    Frequency = 5
    Position = 15
    TabOrder = 0
    OnChange = MaxBackupsChange
  end
  object MaxBackups: TEdit
    Left = 200
    Top = 64
    Width = 239
    Height = 21
    NumbersOnly = True
    TabOrder = 1
    Text = '100'
    OnChange = MaxBackupsChange
  end
  object Button1: TButton
    Left = 256
    Top = 144
    Width = 101
    Height = 25
    Caption = '$Ok'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 363
    Top = 144
    Width = 99
    Height = 25
    Caption = '$Cancel'
    TabOrder = 3
    OnClick = Button2Click
  end
end
