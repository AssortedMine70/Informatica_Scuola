// Federico Santucci, 3AIN
program project1;

{$mode objfpc}{$H+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes
  { you can add units after this };
type
  alphabet = array[97..122] of integer;
var
  v : string;
  ispalindrome : boolean;
  i : integer;
  count : alphabet;
begin
  writeln('Inserire la frase:');
  readln(v);
  for i:=1 to (length(v) div 2) do
      if v[i]<>v[length(v)-i] then
         ispalindrome:=false;
  writeln('la frase è palindroma? ', ispalindrome);
  for i:=97 to 122 do
      count[i]:=0;
  for i:=1 to length(v) do
      count[ord(v[i])]:=count[ord(v[i])]+1;
  for i:=97 to 122 do
      if(count[i]<>0) then
         writeln(char(i), ': ', count[i]);
  readln();
end.
