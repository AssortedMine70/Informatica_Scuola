// Federico Santucci, 3AIN
program project1;

{$mode objfpc}{$H+}

uses
  crt,
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes
  { you can add units after this };

type
  matrix = array[1..5,1..5] of char;

function convert(str : string) : string;
var
  i : integer;
begin
  convert := str;
  for i := 1 to length(str) do
      if (UpCase(str[i])='A') or (UpCase(str[i])='E') or (UpCase(str[i])='I') or (UpCase(str[i])='O') or (UpCase(str[i])='U') then
         convert[i] := '+'
      else if str[i] <> ' ' then
         convert[i] := '-';
end;

function update(word : string; var coded: string; c : char; var errors : integer) : boolean;
var
  i : integer;
begin
  update := false;
  for i := 0 to length(word) do
      if upcase(word[i]) = upcase(c) then
         begin
         coded[i] := c;
         update := true;
         end;
      if update = false then
         errors := errors+1;
end;

procedure init(var m : matrix);
var
  i : integer;
begin
  for i := 1 to 5 do
      m[i] := '';
end;

procedure hangman(var m : matrix; errors : integer);
var
  i : integer;
begin
  case errors of
       1:
         begin
           for i := 1 to 5 do
               m[i][1] := '|';
         end;
       2:
         begin
           for i := 1 to 5 do
               m[i][5] := '|';
         end;
       3:
         begin
           for i := 2 to 4 do
               m[1][i] := '-';
         end;
       4: m[2][3] := '!';
       5: m[3][3] := 'O';
       6: m[4][3] := '!';
       7: m[5][2] := '\';
       8: m[5][4] := '/';
       9: m[4][4] := '\';
       10: m[4][2] := '/';
  end;
end;

procedure print(m : matrix);
var
  i : integer;
begin
  for i := 1 to 5 do
      writeln(m[i]);
end;

var
  word, coded : string;
  t : char;
  errors : integer;
  board : matrix;
begin
  write('Scrivere la Stringa che va indovinata: ');                      // |---|
  readln(word);                                                          // | | |
  ClrScr;                                                                // | O |
  coded := convert(word);                                                // |/|\|
  errors := 0;                                                           // |/ \|
  init(board);
  repeat
    ClrScr;
    writeln(coded);
    print(board);
    write('Lettera: ');
    readln(t);
    update(word, coded, t, errors);
    hangman(board, errors);
  until (errors>10) or (word=coded);
  if word=coded then
     writeln('HAI VINTO!')
  else
     writeln('HAI PERSO!');
  readln();
end.

