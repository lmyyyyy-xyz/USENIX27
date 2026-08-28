unit ResultArray;

interface
uses classes, lpsolve;

type
  TResultArray = class
  private
    FList: TList;
    function GetValue(const row, col: integer): double;
    procedure SetValue(const row, col: integer; const Value: double);
    function GetColCount: integer;
  public
    function Add(size: integer): PFloatArray;
    procedure GetStats(item, len: integer; var min, max: integer);
    procedure Clear;
    constructor Create;
    property Value[const row, col: integer]: double read GetValue write SetValue; default;
    property ColCount: integer read GetColCount;
    destructor Destroy; override;
  end;

implementation

{ TResultArray }

function TResultArray.Add(size: integer): PFloatArray;
begin
  getmem(result, size * sizeof(double));
  FList.Add(result);
  FillChar(result^, size * sizeof(double), 0);
  inc(integer(result), sizeof(double));
end;

procedure TResultArray.Clear;
var i: integer;
begin
  for i := 0 to FList.Count - 1 do
    freemem(FList.Items[i]);
  FList.Clear;
end;

  constructor TResultArray.Create;
  begin
    FList := TList.Create;
  end;

  destructor TResultArray.Destroy;
  begin
    Clear;
    FList.Free;
    inherited;
  end;

  function TResultArray.GetColCount: integer;
  begin
    result := FList.Count;
  end;

  procedure TResultArray.GetStats(item, len: integer; var min, max: integer);
  var
    i: integer;
  begin
    min := 0; max := 0;
    for i := 1 to len do
    begin
      if min = 0 then min := 1 else
      if abs(PFloatArray(FList.Items[item])[i]) < abs(PFloatArray(FList.Items[item])[min]) then
      min := i;

      if max = 0 then max := 1 else
      if abs(PFloatArray(FList.Items[item])[i]) > abs(PFloatArray(FList.Items[item])[max]) then
      max := i;
    end;
  end;

  function TResultArray.GetValue(const row, col: integer): double;
  begin
    result := PFloatArray(FList.Items[row])[col];
  end;

  procedure TResultArray.SetValue(const row, col: integer;
    const Value: double);
  begin
    PFloatArray(FList.Items[row])[col] := Value;
  end;

end.


