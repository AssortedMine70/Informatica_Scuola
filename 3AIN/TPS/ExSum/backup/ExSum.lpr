program ExSum;

{$mode objfpc}{$H+}

uses
  {$IFDEF UNIX} {$IFDEF UseCThreads}
  cthreads, {$ENDIF} {$ENDIF}
  Classes { you can add units after this };

function convert(str : char) : integer;
begin
   if (Ord(str) >= ord('A')) and (ord(str) <= ord('F')) then
      Convert := ord(str) - ord('A') + 10
   else
      Convert := ord(str) - ord('0');
end;

function reconvert(n : integer) : char;
begin
   if n <= 9 then
      Reconvert := chr(ord('0')+n)
   else
      Reconvert := chr(ord('A')+(n-10));
end;

procedure shift(var str : string);
var
  i : integer;
begin
   for i := length(str) downto 1 do
     str[i] := str[i-1];
   str[1] := ' ';
   setlength(str, length(str)+1);
end;

procedure readEx(var ex: string);
var
  control: boolean;
  i: integer;
begin
  control := False;
  repeat
    readln(ex);
    for i := 1 to length(ex) do
      if ((Ord(ex[i]) >= Ord('0')) and (Ord(ex[i]) <= Ord('9'))) or ((Ord(ex[i]) >= Ord('A')) and (Ord(ex[i]) <= Ord('F'))) then
        control := true;
    if control = false then
      writeln('L''input non e'' un numero Esadecimale.');
  until control;
end;

function addEx(ex1, ex2 : string) : string;
var
  i, carry : integer;
  temp : char;
begin
  addEx := '';
  carry := 0;
  if (convert(ex1[i])+convert(ex2[i])) > 15 then
    i := 2
  else
    i := 1;
  repeat
    if (convert(ex1[i])+convert(ex2[i])+carry) > 15 then
      begin
      carry := reconvert(convert(ex1[i])+convert(ex2[i])+carry-15);
      addEx[i]:= 'F';
      end
    else
      addEx[i]:= reconvert(convert(ex1[i])+convert(ex2[i])+carry);
  until (i>length(ex1)) or (i>length(ex2));
end;

var
  ex1, ex2 : string;

begin
  ex1 := '';
  ex2 := '';
  readEx(ex1);
  readEx(ex2);
  shift(ex1);
  writeln(ex1);
  addEx(ex1, ex2);
  readln();
end.
