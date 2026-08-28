program LpSolveIDE;
{$APPTYPE CONSOLE}
// this keeps a console window for lp_solve stderr and stdout.
// can run without but a cmd window pops up on each write
// The cmd window close box bypasses the close query method  that the widow uses.
// also if the window errors with exception, it will DRWatson from its close box
// but closing the cmd window exits both without DRWason SEND request.



uses
  Forms,
  SysUtils,
  Windows,
  main in 'main.pas' {MainForm},
  LPHighlighter in 'LPHighlighter.pas',
  dlgSearchText in 'dlgSearchText.pas' {TextSearchDialog},
  dlgReplaceText in 'dlgReplaceText.pas' {TextReplaceDialog},
  dlgConfirmReplace in 'dlgConfirmReplace.pas' {ConfirmReplaceDialog},
  dlgGotoLine in 'dlgGotoLine.pas' {GotoLineForm},
  dlgAbout in 'dlgAbout.pas' {AboutForm},
  ResultArray in 'ResultArray.pas',
  Params in 'Params.pas' {ParamForm},
  XPMenu in 'XPMenu.pas',
  SynHighlighterXML in 'SynHighlighterXML.pas',
  lpobject in 'lpobject.pas',
  dlgStatistics in 'dlgStatistics.pas' {StatisticsForm};

{$R *.res}

begin
//  madExcept.DetectConsole := false;
  Application.Initialize;
  Application.HelpFile := '';
  Application.CreateForm(TMainForm, MainForm);
  if (ParamCount > 0) then
    if FileExists(ParamStr(1)) then
      MainForm.OpenFile(ParamStr(1));
  Application.Run;
end.

