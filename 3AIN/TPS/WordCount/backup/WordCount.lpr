// Federico Santucci, 3AIN
program WordCount;

{$mode objfpc}{$H+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes
  { you can add units after this };

var
  sentence : string;
  i, count : integer;
begin
  writeln('Scrivere una frase: ');
  readln(sentence);
  count := 1;
  for i := 0 to length(sentence) do
      if sentence[i] = ' ' then
        count := count+1;
  writeln('Numero di parole: ', count);
  for i := 0 to length(sentence) do
      if sentence[i] = ' ' then
        writeln()
      else
        write(sentence[i]);
  readln();
end.
