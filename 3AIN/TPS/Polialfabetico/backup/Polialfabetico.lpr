program Polialfabetico;

{$mode objfpc}{$H+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes
  { you can add units after this };

type
  alphabet = array[97..122] of char;
  message = array[0..1023] of char;
var
  First, Second : alphabet;
  firstKey, secondKey, input : char;
  msg, codified : message;
  i, logicsize : integer;
begin
  writeln('Inserire di seguito il messaggio, lettera per lettera.');
  writeln('Terminare la frase con un trattino (-).');
  logicsize := 0;
  repeat
    repeat
      readln(input);
    until ((input >= 'a') and (input <= 'z')) or (input = '-') or (input = ' ');
    if input <> '-' then
      begin
        msg[logicsize] := input;
        logicsize := logicsize + 1;
      end;
  until input = '-';
  writeln(logicsize);
  logicsize:=logicsize-1;
  for i:=0 to logicsize do
      write(msg[i]);
  writeln('');
  writeln('Inserire la prima chiave di codifica: ');
  repeat
      readln(firstKey);
  until (firstKey >= 'a') and (firstKey <= 'z');
  for i:=97 to 122 do
      if 122-(i-97-(ord(firstKey)-96)) <= 122 then
        First[i] := char(122-(i-97-(ord(firstKey)-96)))
      else
        First[i] := char(122-(i-97-(ord(firstKey)-96))-26);
  writeln('Alfabeto codificato in ', firstKey, ':');
  for i:=97 to 122 do
      write(First[i]);
  writeln('');
  writeln('Inserire la seconda chiave di codifica: ');
  repeat
      readln(secondKey);
  until (secondKey >= 'a') and (secondKey <= 'z');
  for i:=97 to 122 do
      if 122-(i-97-(ord(secondKey)-96)) <= 122 then
        Second[i] := char(122-(i-97-(ord(secondKey)-96)))
      else
        Second[i] := char(122-(i-97-(ord(secondKey)-96))-26);
  writeln('Alfabeto codificato in ', secondKey, ':');
  for i:=97 to 122 do
      write(Second[i]);

  writeln('Inserire di seguito con quale chiave si vuole codificare ogni lettera: ');
  for i:=0 to logicsize do
      begin
         repeat
           write(msg[i], ' = ');
           readln(input);
         until (input = firstKey) or (input = secondKey);
         if input=firstKey then
           codified[i] := First[ord(msg[i])]
         else
           codified[i] := Second[ord(msg[i])];
      end;
  writeln('');
  writeln('frase codificata: ');
  for i:=0 to logicsize do
      write(codified[i]);
  readln();
end.

// char() e ord()

