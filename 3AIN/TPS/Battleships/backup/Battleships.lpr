program Battleships;

{$mode objfpc}{$H+}{$M+}

uses
  crt,
  SysUtils,
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes
  { you can add units after this };

type
  Board = array[1..10, 1..10] of integer;

{Board}  procedure    BoardInit(var b : Board);
var i, j : integer;
begin
  for i := 1 to 10 do
      for j := 1 to 10 do
          b[i,j] := 0;
end;

{Board}  function     BoardCanTarget(b : Board; x, y : integer):boolean;
begin
  BoardCanTarget := false;
  if b[y, x] < 2 then
     BoardCanTarget := true
end;

{Board}  function     BoardHit(var b : Board; x, y : integer):boolean;
begin
  BoardHit := false;
  if b[y, x] = 1 then
     BoardHit := true;
  b[y,x] := b[y,x]+2;
end;

{Board}  function     BoardPlace(var b : Board; x, y, size, rotation : integer):boolean;
var
  i : integer;
begin
  BoardPlace := false;
  case rotation of
       0: begin
          if y-size >= 0 then
             begin
             BoardPlace := true;
             for i := 0 to size-1 do
                 if b[y-i, x] <> 0 then
                      BoardPlace := false;
             if BoardPlace then
                begin
                for i:= 0 to size-1 do
                    b[y-i, x] := 1;
                end;
             end;
          end;
       1: begin
          if x+size <= 10 then
             begin
             BoardPlace := true;
             for i := 0 to size-1 do
                 if b[y, x+i] <> 0 then
                      BoardPlace := false;
             if BoardPlace then
                begin
                for i:= 0 to size-1 do
                    b[y, x+i] := 1;
                end;
             end;
          end;
       2: begin
          if y+size <= 10 then
             begin
             BoardPlace := true;
             for i := 0 to size-1 do
                 if b[y+i, x] <> 0 then
                      BoardPlace := false;
             if BoardPlace then
                begin
                for i:= 0 to size-1 do
                    b[y+i, x] := 1;
                end;
             end;
          end;
       3: begin
          if x-size >= 0 then
             begin
             BoardPlace := true;
             for i := 0 to size-1 do
                 if b[y, x-i] <> 0 then
                      BoardPlace := false;
             if BoardPlace then
                begin
                for i:= 0 to size-1 do
                    b[y, x-i] := 1;
                end;
             end;
          end;
  end;
end;

{Board}  function     BoardCheckPlaceability(var b : Board; x, y, size, rotation : integer):boolean;
var
  i : integer;
begin
  BoardCheckPlaceability := false;
  case rotation of
       0: begin
          if y-size >= 0 then
             begin
             BoardCheckPlaceability := true;
             for i := 0 to size-1 do
                 if b[y-i, x] <> 0 then
                      BoardCheckPlaceability := false;
             end;
          end;
       1: begin
          if x+size <= 10 then
             begin
             BoardCheckPlaceability := true;
             for i := 0 to size-1 do
                 if b[y, x+i] <> 0 then
                      BoardCheckPlaceability := false;
             end;
          end;
       2: begin
          if y+size <= 10 then
             begin
             BoardCheckPlaceability := true;
             for i := 0 to size-1 do
                 if b[y+i, x] <> 0 then
                      BoardCheckPlaceability := false;
             end;
          end;
       3: begin
          if x-size >= 0 then
             begin
             BoardCheckPlaceability := true;
             for i := 0 to size-1 do
                 if b[y, x-i] <> 0 then
                      BoardCheckPlaceability := false;
             end;
          end;
  end;
end;

{Board}  procedure    BoardPrint(b : Board);
var x, y : integer;
begin
  writeln('/-1-2-3-4-5-6-7-8-9-10\');
  for y := 1 to 10 do
      begin
        write(chr(64+y),' ');
        for x := 1 to 10 do
            begin
            case b[y, x] of
                 0: write(' ');
                 1: write('O');
                 2: write('X');
                 3: write('V');
                 end;
            write(' ');
            end;
      writeln('|');
      end;
  writeln('\---------------------/');
end;

{Board}  procedure    BoardCovered(b : Board);
var x, y : integer;
begin
  gotoxy(45, 5);
  writeln('/-1-2-3-4-5-6-7-8-9-10\');
  for y := 1 to 10 do
      begin
      gotoxy(45, 5+y);
        write(chr(64+y),' ');
        for x := 1 to 10 do
            begin
            case b[y, x] of
                 0: write('/');
                 1: write('/');
                 2: write('X');
                 3: write('V');
                 end;
            write(' ');
            end;
      writeln('|');
      end;
  gotoxy(45, 16);
  writeln('\---------------------/');
end;

{Player} procedure    PlayerInitBoard(var b: Board; i : integer);
var
  x, y, r, input, count : integer;
begin
  BoardInit(b);
  count := 3;
  repeat
     clrscr;
     writeln('Giocatore ', i, ': Fase di Piazzamento.');
     writeln;
     x:=3; y:=6; r:=0;
     writeln('Cacciatorpediniere - 2 Caselle - x', count, ' - Premere Invio per Confermare la posizione, R per ruotare la nave.');
     writeln;
     BoardPrint(b);
     gotoxy(28,10);
     writeln('(Rotazione Corrente: 0)');
     gotoxy(28,11);
     writeln('(0 = su, 1 = destra, 2 = sotto, 3 = sinistra.)');
     gotoxy(x, y);
     repeat
       input := ord(ReadKey);
         case (input) of
             72  : if y-1 >= 6  then begin y:=y-1; gotoxy(x,y); end;
             80  : if y+1 <= 15 then begin y:=y+1; gotoxy(x,y); end;
             75  : if x-2 >= 3  then begin x:=x-2; gotoxy(x,y); end;
             77  : if x+2 <= 20 then begin x:=x+2; gotoxy(x,y); end;
             114 : begin r:=(r+1) mod 4; gotoxy(49,10); write(r); gotoxy(x,y); end;
         end;
     until (input=13) and BoardCheckPlaceability(b, ((x-3) div 2)+1, (y-6)+1, 2, r);
     BoardPlace(b,((x-3) div 2)+1,(y-6)+1, 2, r);
     count := count-1;
  until count = 0;
  count := 2;
  repeat
     clrscr;
     writeln('Giocatore ', i, ': Fase di Piazzamento.');
     writeln;
     x:=3; y:=6; r:=0;
     writeln('Incrociatori       - 3 Caselle - x', count, ' - Premere Invio per Confermare la posizione, R per ruotare la nave.');
     writeln;
     BoardPrint(b);
     gotoxy(28,10);
     writeln('(Rotazione Corrente: 0)');
     gotoxy(28,11);
     writeln('(0 = su, 1 = destra, 2 = sotto, 3 = sinistra.)');
     gotoxy(x, y);
     repeat
       input := ord(ReadKey);
         case (input) of
             72  : if y-1 >= 6  then begin y:=y-1; gotoxy(x,y); end;
             80  : if y+1 <= 15 then begin y:=y+1; gotoxy(x,y); end;
             75  : if x-1 >= 3  then begin x:=x-2; gotoxy(x,y); end;
             77  : if x+1 <= 20 then begin x:=x+2; gotoxy(x,y); end;
             114 : begin r:=(r+1) mod 4; gotoxy(49,10); write(r); gotoxy(x,y); end;
         end;
     until (input=13) and BoardCheckPlaceability(b, ((x-3) div 2)+1, (y-6)+1, 3, r);
     BoardPlace(b,((x-3) div 2)+1,(y-6)+1, 3, r);
     count := count-1;
  until count = 0;
  count := 1;
  repeat
    clrscr;
     writeln('Giocatore ', i, ': Fase di Piazzamento.');
     writeln;
     x:=3; y:=6; r:=0;
     writeln('Corazzata          - 4 Caselle - x', count, ' - Premere Invio per Confermare la posizione, R per ruotare la nave.');
     writeln;
     BoardPrint(b);
     gotoxy(28,10);
     writeln('(Rotazione Corrente: 0)');
     gotoxy(28,11);
     writeln('(0 = su, 1 = destra, 2 = sotto, 3 = sinistra.)');
     gotoxy(x, y);
     repeat
       input := ord(ReadKey);
         case (input) of
             72  : if y-1 >= 6  then begin y:=y-1; gotoxy(x,y); end;
             80  : if y+1 <= 15 then begin y:=y+1; gotoxy(x,y); end;
             75  : if x-1 >= 3  then begin x:=x-2; gotoxy(x,y); end;
             77  : if x+1 <= 20 then begin x:=x+2; gotoxy(x,y); end;
             114 : begin r:=(r+1) mod 4; gotoxy(49,10); write(r); gotoxy(x,y); end;
         end;
     until (input=13) and BoardCheckPlaceability(b, ((x-3) div 2)+1, (y-6)+1, 4, r);
     BoardPlace(b,((x-3) div 2)+1,(y-6)+1, 4, r);
     count := count-1;
  until count = 0;
  clrscr;
  writeln('Giocatore ', i, ': Fase di Piazzamento.');
  writeln;
  writeln;
  writeln;
     BoardPrint(b);
  Sleep(1500);
end;

{Game}   procedure    GameTitleScreen();
begin
  writeln('Battaglia Navale - Federico Santucci');
  writeln('Inserire lo schermo intero prima di continuare. Premere Invio quando impostato.');
  repeat until ord(ReadKey)=13;
  clrscr;
end;

{Game}   procedure    GameTransition();
begin
  clrscr;
  writeln('Cambio di Giocatore. Premere Invio per continuare.');
  repeat until ord(ReadKey)=13;
  clrscr;
end;

{Game}   procedure    GameTurn(var b1, b2 : Board; i : integer);
var
  x, y, input : integer;
begin
  clrscr;
  writeln('Giocatore ', i, ': Fase di Attacco.');
  writeln;
  writeln('/ = nebbia di guerra, 0 = nave, V = nave affondata, X = buco nell''acqua.');
  writeln;
  BoardPrint(b1);
  BoardCovered(b2);
  x := 47; y := 6;
  repeat
       input := ord(ReadKey);
         case (input) of
             72  : if y-1 >= 6  then begin y:=y-1; gotoxy(x,y); end;
             80  : if y+1 <= 15 then begin y:=y+1; gotoxy(x,y); end;
             75  : if x-2 >= 47  then begin x:=x-2; gotoxy(x,y); end;
             77  : if x+2 <= 65 then begin x:=x+2; gotoxy(x,y); end;
         end;
     until (input=13) and BoardCanTarget(b2, (x-45) div 2, y-5);
     gotoxy(10, 18);
     write('ATTACCO A ',char(65+y-6), (x-45) div 2, '-> ' );
     if BoardHit(b2, (x-45) div 2, y-5) then
        write('COLPITO')
     else
        write('ACQUA');
  Sleep(1500);
end;

{Game}   function    GameEndCondition(b1, b2 : Board):boolean;
var
  i, j : integer;
begin
  GameEndCondition := true;
  for i := 1 to 10 do
      for j := 1 to 10 do
          if (b1[i,j] = 1) or (b2[i,j] = 1) then
             GameEndCondition := false;
end;

var
  Board1, Board2 : Board;
begin
  GameTitleScreen;
  PlayerInitBoard(Board1, 1);
  GameTransition;
  PlayerInitBoard(Board2, 2);
  repeat
    GameTransition;
    GameTurn(Board1, Board2, 1);
    GameTransition;
    GameTurn(Board2, Board1, 2);
  until GameEndCondition(Board1, Board2);
  readln();
end.

