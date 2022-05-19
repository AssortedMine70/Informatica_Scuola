program trovaValore;

{$mode objfpc}{$H+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes
  { you can add units after this };

type
    st25=string[25];
    tmiamat=array[1..10,1..10]of st25;

procedure trovaValore(mati:tmiamat;incognita:st25;var cx,cy:integer);
var i, j, flag : integer;
begin
  flag := 0;
  i := 1;
  repeat
    j := 1;
    repeat
      if incognita = mati[i, j]  then
      begin
        flag := 1;
        cy := i;
        cx := j;
      end;
      j := j+1;
    until j > 10;
    i := i+1;
  until i > 10;
  if flag = 0 then
  begin
    cy := 0;
    cx := 0;
  end;
end;

var
  str : st25;
  mat : tmiamat;
  x, y, i, j : integer;

begin
  writeln('Inizializzazione Matrice:');
  i := 1;
  repeat
    j := 1;
    repeat
      write('(', j, ', ', i, '): ');
      readln(mat[i, j]);
      j := j+1;
    until j > 10;
    i := i+1;
  until i > 10;
  writeln('Inserire la stringa da cercare: ');
  readln(str);
  trovaValore(mat, str, x, y);
  writeln();
  if x = 0 then
     writeln('Non e'' stata trovata l''incognita all''interno della matrice. (', x, ', ', y, ')')
  else
     writeln('L''incognita si trova in ', x, ', ', y, '.');
  writeln();
  writeln('Premere Invio per chiudere il programma.');
  readln();
end.

