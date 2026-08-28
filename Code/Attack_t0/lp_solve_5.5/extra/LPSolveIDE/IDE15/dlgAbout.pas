unit dlgAbout;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TAboutForm = class(TForm)
    Label10: TLabel;
    Button1: TButton;
    GroupBox1: TGroupBox;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label6: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    GroupBox2: TGroupBox;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label16: TLabel;
    GroupBox3: TGroupBox;
    Label11: TLabel;
    Label17: TLabel;
    Label18: TLabel;
    Label12: TLabel;
    procedure FormCreate(Sender: TObject);
    procedure URLClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  AboutForm: TAboutForm;

implementation
uses ShellApi, XPMenu;

{$R *.dfm}

procedure TAboutForm.FormCreate(Sender: TObject);
begin
  TXPMenu.Create(self).Active := true;
end;



procedure TAboutForm.URLClick(Sender: TObject);
begin
  shellexecute(Application.Handle, 'open', PChar(TLabel(Sender).Caption), nil, nil, SW_SHOW);
end;

end.
