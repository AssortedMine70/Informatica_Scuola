// Federico Santucci, 3AIN
program TrasmissioneBinaria2;

{$mode objfpc}{$H+}

uses
  strutils,
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes
  { you can add units after this };

type
  Byte = string[8];
  Message = array[1..256] of Byte;

function cecktransmission(msg:Byte):Boolean;
var
  i, countone : integer;
begin
  countone := 0;
  cecktransmission := true;
  for i:= 1 to length(msg) do
      if msg[i] = '1' then
         countone := countone+1;
  if (countone mod 2) <> 0 then
     cecktransmission := false;
end;

function code(chr:char):Byte;
var
  i, countone : integer;
begin
  countone := 0;
  code := IntToBin(ord(chr), 8);
  for i:=2 to length(code) do
      if code[i] = '1' then
         countone := countone+1;
  if (countone mod 2) <> 0 then
     code[1] := '1';
end;

function decode(coded:Byte):char;
var
  i, binVal, bin : integer;
begin
  bin := 0;
  binVal := 64;
  for i:=2 to length(coded) do
     begin
     if coded[i] = '1' then
        bin := bin + binVal;
     binVal := binVal div 2;
     end;
  decode := chr(bin);
end;

procedure transmit(channelname, str:string);
var
  i, j, countOne : integer;
  transmitchannel : text;
  msg : Message;
  tempByte, parityByte : Byte;
begin
  setlength(tempByte, 8);
  setlength(parityByte, 8);
  assign(transmitchannel, channelname);
  rewrite(transmitchannel);
  for i:=1 to length(str) do
     begin
     msg[i] := code(str[i]);
     writeln(transmitchannel, code(str[i]));
     end;
  for i:=1 to 8 do
     begin
     countone := 0;
     for j:=1 to length(str) do
        if tempByte[j] = '1' then
           countone := countone+1;
     if (countone mod 2) <> 0 then
        parityByte[i] := '1'
     else
        parityByte[i] := '0';
  end;
  writeln(transmitchannel, tempByte);
  close(transmitchannel);
end;

function receive(channelname:string):string;
var
  receivechannel : text;
  tempByte : Byte;
  i : integer;
  tempstr : string;
begin
  assign(receivechannel, channelname);
  reset(receivechannel);
  i := 1;
  repeat
    setlength(tempstr, i+1);
    readln(receivechannel, tempByte);
    if cecktransmission(tempByte) then
       tempstr[i] := decode(tempByte)
    else
       tempstr[i] := '#';
    i := i+1;
  until eof(receivechannel);
  receive := tempstr;
  close(receivechannel);
end;

var
  str : string;

begin
  writeln('Inserire Messaggio da Inviare: ');
  readln(str);
  transmit('channel.txt', str);
  writeln('Messaggio Trasmesso. Premere Invio per Ricevere.');
  readln();
  writeln(receive('channel.txt'));
  readln();
end.

