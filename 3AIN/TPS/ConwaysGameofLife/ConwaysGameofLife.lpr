// Federico Santucci, 3AIN
program ConwaysGameofLife;

{$mode objfpc}{$H+}

uses
  crt,
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes
  { you can add units after this };

{$R *.res}

type
  matrix = array[0..50, 0..50] of integer;
var
  mat : matrix;
  i, j, N, input : integer;

{ inizializza la matrice quadrata di dimensioni N x N settandone tutti i valori a 0 }
function init(n : integer): matrix;
begin
  for i:= 0 to n do
      for j:= 0 to n do
          Result[i,j]:= 0;
  gotoxy(1, 1);
end;

{ imposta il valore di ogni cella al numero dei suoi vicini }
function countNeighbours(n: integer) : matrix;
begin
  for i:= 0 to n do
      for j:= 0 to n do
          begin
          Result[i, j] := 0;
          if (mat[i-1, j] <> 0) and (i-1 >= 0) then
               Result[i,j] := Result[i,j] + 1;
          if (mat[i, j-1] <> 0) and (j-1 >= 0) then
               Result[i,j] := Result[i,j] + 1;
          if (mat[i+1, j] <> 0) and (i+1 <= n) then
               Result[i,j] := Result[i,j] + 1;
          if (mat[i, j+1] <> 0) and (j+1 <= n) then
               Result[i,j] := Result[i,j] + 1;
          if (mat[i-1, j-1] <> 0) and ((i-1 >= 0) and (j-1 >= 0)) then
               Result[i,j] := Result[i,j] + 1;
          if (mat[i-1, j+1] <> 0) and ((i-1 >= 0) and (j+1<= n)) then
               Result[i,j] := Result[i,j] + 1;
          if (mat[i+1, j-1] <> 0) and ((i+1 <= n) and (j-1 >= 0)) then
               Result[i,j] := Result[i,j] + 1;
          if (mat[i+1, j+1] <> 0) and ((i+1 <= n) and (j+1 <= n)) then
               Result[i,j] := Result[i,j] + 1;
          end;
end;

{ procedura che permette il setup della matrice navigandola con i tasti frecce }
function setup(n: integer) : matrix;
var
  x, y : integer;
begin
  x:=1; y:=1;
  gotoxy(x, y);
  repeat
        input := ord(ReadKey);
        case (input) of
             72 : if y-1 > 0 then begin y:=y-1; gotoxy(x,y); end;
             80 : if y+1 < N then begin y:=y+1; gotoxy(x,y); end;
             75 : if x-1 > 0 then begin x:=x-1; gotoxy(x,y); end;
             77 : if x+1 < N then begin x:=x+1; gotoxy(x,y); end;
             13 : if Result[y-1, x-1] > 0 then begin Result[y-1, x-1] := 0; write(' '); end else begin Result[y-1, x-1] := 1; write('X'); end;
        end;
        gotoxy(x, y);
  until input=32;
end;

{ stampa una matrice quadrata di dimensioni N x N }
procedure print(mat: matrix; n: integer);
begin
  gotoxy(1, 1);
  for i:= 0 to n do
      begin
      for j:= 0 to n do
          if mat[i, j] <> 0 then
             write('X')
          else
             write(' ');
      writeln();
      end;
end;

{ aggiorna la matrice secondo le regole del gioco della vita }
function update(n: integer): matrix;
var
  neighbours : matrix;
begin
  neighbours := countNeighbours(n);
  for i:= 0 to n do
      for j:= 0 to n do
          begin
          Result[i, j] := mat[i, j];
          if mat[i, j] <> 0 then
             begin
              if (neighbours[i, j] < 2) or (neighbours[i, j] > 3) then
                 Result[i, j] := 0;
             end
          else
              if neighbours[i, j] = 3 then
                 Result[i, j] := 1;
          end;

end;

begin
  writeln('Simulatore de "Il Gioco della vita di Conway" di Federico Santucci.');
  writeln('Nella prossima schermata sarà possibile impostare la situazione di partenza della matrice, muovendosi tra le');
  writeln('celle con le freccette e cambiando il loro stato premendo invio. Partita la simulazione, premere qualsiasi per');
  writeln('interromperla. Premere un tasto qualsiasi per continuare.');
  Readkey;
  ClrScr;
  n := 20;
  mat := init(N);
  mat := setup(N);
  cursoroff;
  print(mat, N);
  repeat
        mat := update(N);
        print(mat, N);
        Delay(200);
  until KeyPressed;
end.

