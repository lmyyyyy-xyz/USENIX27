unit dlgGotoLine;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, XPMenu;

type
  TGotoLineForm = class(TForm)
    Button1: TButton;
    Button2: TButton;
    LineNumer: TEdit;
    Label1: TLabel;
    procedure Button1Click(Sender: TObject);
    procedure LineNumerKeyPress(Sender: TObject; var Key: Char);
    procedure CheckLine;
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  GotoLineForm: TGotoLineForm;

implementation
uses main;
{$R *.dfm}

procedure TGotoLineForm.Button1Click(Sender: TObject);
begin
  CheckLine;
end;

procedure TGotoLineForm.CheckLine;
var i: integer;
begin
  if TryStrToInt(LineNumer.Text, i) and
    (i <= MainForm.Editor.Lines.Count) and
    (i > 0)  then
  ModalResult := mrOK else
  MessageDlg('Invalid line number.', mtError, [mbOK], 0);
end;

procedure TGotoLineForm.LineNumerKeyPress(Sender: TObject; var Key: Char);
begin
  if Key = #13 then
  begin
    CheckLine;
    abort;
  end;
end;

procedure TGotoLineForm.FormCreate(Sender: TObject);
begin
  TXPMenu.Create(self).Active := true;
end;

end.
