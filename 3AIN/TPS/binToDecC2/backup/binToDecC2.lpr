// Federico Santucci, 3AIN - 01/03/22
program binToDecC2;

{$mode objfpc}{$H+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes
  { you can add units after this };

type
    st8=string[8];

function binToDecC2(nbin:st8):integer;
var i, j, flag, pow : integer;
begin
  binToDecC2 := 0;
  pow := 1;
  if nbin[1] = '1' then
    begin
    flag := 0;
    i := 8;
    repeat
       if (nbin[i] = '1') and (i-1>=1) then
          begin
             flag := 1;
             for j := i-1 downto 1 do
                 if nbin[j] = '1' then
                    nbin[j] := '0'
                 else
                    nbin[j] := '1';
          end;
       i := i-1;
    until (flag = 1) or (i = 1);
    for i := 8 downto 1 do
        begin
        if nbin[i] = '1' then
          binToDecC2 := binToDecC2 - pow;
        pow := pow*2;
        end;
    end
  else
    for i := 8 downto 1 do
        begin
        if nbin[i] = '1' then
          binToDecC2 := binToDecC2 + pow;
        pow := pow*2;
        end;
end;

var
  str : st8;

begin
  writeln('Inserire il numero binario in C2:');
  readln(str);
  writeln('Valore decimale: ', binToDecC2(str));
  writeln();
  writeln('Premere Invio per chiudere il programma.');
  readln();
end.

