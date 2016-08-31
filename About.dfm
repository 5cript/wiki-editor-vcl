object AboutForm: TAboutForm
  Left = 0
  Top = 0
  Caption = 'About'
  ClientHeight = 542
  ClientWidth = 506
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object RichEdit1: TRichEdit
    Left = 8
    Top = 247
    Width = 489
    Height = 289
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Lines.Strings = (
      'The MIT License (MIT)'
      ''
      'Copyright (c) 2015 5cript'
      ''
      
        'Permission is hereby granted, free of charge, to any person obta' +
        'ining a copy'
      
        'of this software and associated documentation files (the "Softwa' +
        're"), to deal'
      
        'in the Software without restriction, including without limitatio' +
        'n the rights'
      
        'to use, copy, modify, merge, publish, distribute, sublicense, an' +
        'd/or sell'
      
        'copies of the Software, and to permit persons to whom the Softwa' +
        're is'
      'furnished to do so, subject to the following conditions:'
      ''
      
        'The above copyright notice and this permission notice shall be i' +
        'ncluded in all'
      'copies or substantial portions of the Software.'
      ''
      
        'THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, ' +
        'EXPRESS OR'
      
        'IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANT' +
        'ABILITY,'
      
        'FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVEN' +
        'T SHALL THE'
      
        'AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR' +
        ' OTHER'
      
        'LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ' +
        'ARISING FROM,'
      
        'OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DE' +
        'ALINGS IN THE'
      'SOFTWARE.')
    ParentFont = False
    ReadOnly = True
    TabOrder = 0
    Zoom = 100
  end
  object RichEdit2: TRichEdit
    Left = 8
    Top = 8
    Width = 489
    Height = 233
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Lines.Strings = (
      'This Project uses several libraries on github created by'
      
        'Tim Ebbeke which are provided under the MIT License, which is pr' +
        'ovided below.'
      ''
      'The following git repositories (all MIT) are used:'
      ''
      'wretched-css'
      'mplex'
      'SimpleJSON'
      'SimpleUtil'
      'twisted-spirit'
      'wiki-client'
      'wiki-editor'
      'wiki-markup'
      'wiki-meta'
      'wiki-editor-vcl'
      'dll'
      'wiki-vcl-css')
    ParentFont = False
    ReadOnly = True
    TabOrder = 1
    Zoom = 100
  end
end
