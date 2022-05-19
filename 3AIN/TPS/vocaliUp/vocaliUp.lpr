// Federico Santucci, 3AIN - 01/03/22

program vocaliUp;

{$mode objfpc}{$H+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes
  { you can add units after this };

type
    st50=string[50];

procedure vocaliUp(var frase:st50);
var i : integer;
begin
  for i := 1 to length(frase) do
      if (frase[i] = 'a') or (frase[i] = 'e') or (frase[i] = 'i') or (frase[i] = 'o') or (frase[i] = 'u') then
         frase[i] := upcase(frase[i]);
end;

var
  str : st50;

begin
  writeln('Inserire la frase:');
  readln(str);
  vocaliUp(str);
  writeln('Frase con le vocali maiuscole:');
  writeln(str);
  writeln();
  writeln('Premere Invio per chiudere il programma.');
  readln();
end.

