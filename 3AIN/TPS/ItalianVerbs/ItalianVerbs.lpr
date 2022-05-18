program ItalianVerbs;

{$mode objfpc}{$H+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes
  { you can add units after this };
var
  verb : string;
  c : char;
  transitive, active : boolean;
begin
  write('inserire il verbo: ');
  readln(verb);
  write('e'' transitivo?(Y/n) ');
  readln(c);
  if upcase(c) <> 'N' then
     transitive := true
  else
     transitive := false;
  write('coniugare all''attivo?(Y/n) ');
  readln(c);
  if upcase(c) <> 'N' then
     active := true
  else
     active := false;
  coniugate(verb, transitive, active);
  readln();
end.

