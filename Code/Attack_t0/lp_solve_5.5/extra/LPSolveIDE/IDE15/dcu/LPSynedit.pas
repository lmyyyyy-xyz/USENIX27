unit LPSynedit;

interface

uses
  Windows, Messages, SysUtils, Classes, Controls, SynEdit, Graphics;

type
  TLPSynedit = class(TSynedit)
  private
    FEnableMPS: boolean;
    procedure SetEnableMPS(Value: boolean);
  protected
    procedure PaintTextLines(AClip: TRect; const aFirstRow, aLastRow,
      FirstCol, LastCol: integer); override;
  public
    constructor Create(AOwner: TComponent); override;
  published
    property EnableMPS: boolean read FEnableMPS write SetEnableMPS;
    { Published declarations }
  end;

procedure Register;

implementation

procedure Register;
begin
  RegisterComponents('LP Solver', [TLPSynedit]);
end;

{ TLPSynedit }

constructor TLPSynedit.Create(AOwner: TComponent);
begin
  inherited;
  FEnableMPS := false;
end;

procedure TLPSynedit.PaintTextLines(AClip: TRect; const aFirstRow,
  aLastRow, FirstCol, LastCol: integer);
var
  nRightEdge, fTextOffSet: integer;
const
  cols: array[0..11] of integer = (1,3,4,12,14,22,24,36,39,47,49,61);
var
  i: integer;
begin
  inherited;
  if FEnableMPS then
  begin
    fTextOffset := fGutterWidth + 2 - (LeftChar - 1) * CharWidth;
    for i := low(cols) to high(cols) do
    begin
      nRightEdge := fTextOffset + (cols[i]) * CharWidth; // pixel value
      if (nRightEdge >= AClip.Left) and (nRightEdge <= AClip.Right) then
      begin
        Canvas.Pen.Color := $00E0E0E0;
        Canvas.Pen.Width := 1;
        Canvas.MoveTo(nRightEdge, AClip.Top);
        Canvas.LineTo(nRightEdge, AClip.Bottom + 1);
      end;
    end;
  end;
end;

procedure TLPSynedit.SetEnableMPS(Value: boolean);
begin
  if FEnableMPS <> Value then
  begin
    FEnableMPS := Value;
    Invalidate;
  end;
end;

end.
