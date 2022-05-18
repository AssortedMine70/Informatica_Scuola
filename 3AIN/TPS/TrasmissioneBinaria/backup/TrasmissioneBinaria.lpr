// Federico Santucci, 3AIN
program TrasmissioneBinaria;

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
     code[1] := 1;
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
  i : integer;
  transmitchannel : text;
begin
  assign(transmitchannel, channelname);
  rewrite(transmitchannel);
  for i:=1 to length(str) do
     writeln(transmitchannel, code(str[i]));
  close(transmitchannel);
end;

function receive(channelname:string):Byte;
var
  receivechannel : text;
begin
  assign(receivechannel, channelname);
  reset(receivechannel);

  close(receivechannel);
end;


begin
  transmit('channel.txt', 'Hello World');
  //writeln(receive('channel.txt'));
  readln();
end.

