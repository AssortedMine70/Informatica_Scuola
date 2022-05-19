// Federico Santucci, 3AIN
program hamming;

{$mode objfpc}{$H+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes
  { you can add units after this };

type                                     
   hammingCode = array[1..12] of ShortInt;
   hammingFile = file of hammingCode;
   str8 = string[8];

function hammingWrite(filename:string; letter:integer):hammingCode;
var
  fp : hammingFile;
  asciiCode : str8;
  i : integer;
  code : hammingCode;
begin
   assign(fp, filename);
   rewrite(fp);
   asciiCode := BinStr(letter, 8);
   for i := 1 to 12 do
         code[i] := 0;
   // fills with the Ascii Code
   if asciiCode[1] = '1' then
      code[3 ] := 1;
   if asciiCode[2] = '1' then
      code[5 ] := 1;
   if asciiCode[3] = '1' then
      code[6 ] := 1;
   if asciiCode[4] = '1' then
      code[7 ] := 1;
   if asciiCode[5] = '1' then
      code[9 ] := 1;
   if asciiCode[6] = '1' then
      code[10] := 1;
   if asciiCode[7] = '1' then
      code[11] := 1;
   if asciiCode[8] = '1' then
      code[12] := 1;
   // fills the Control Bits
   code[1] := (code[3] + code[5] + code[7] + code[9] + code[11]) mod 2;
   code[2] := (code[3] + code[6] + code[7] + code[10] + code[11]) mod 2;
   code[4] := (code[5] + code[6] + code[7] + code[12]) mod 2;
   code[8] := (code[9] + code[10] + code[11] + code[12]) mod 2;
   // writes file
   hammingWrite := code;
   write(fp, code);
   close(fp);
end;

function hammingRead(filename:string):integer;
var
  fp : hammingFile;
  wrongBit : integer;
  code : hammingCode;
begin
   assign(fp, filename);
   reset(fp);
   // reads file
   read(fp, code);
   // wrong Bit individuation
   if code[1] <> (code[3] + code[5] + code[7] + code[9] + code[11]) mod 2 then
      wrongBit := 1;
   if code[2] <> (code[3] + code[6] + code[7] + code[10] + code[11]) mod 2 then
      wrongBit := wrongBit + 2;
   if code[4] <> (code[5] + code[6] + code[7] + code[12]) mod 2 then
      wrongBit := wrongBit + 4;
   if code[8] <> (code[9] + code[10] + code[11] + code[12]) mod 2 then
      wrongBit := wrongBit + 8;
   // eventual Bit Correction
   if wrongBit <> 0 then
      code[wrongBit] := (code[wrongBit] + 1) mod 2;
   // calculates the Ascii Code
   if code[3 ] = 1 then
      hammingRead := 128;
   if code[5 ] = 1 then
      hammingRead := hammingRead + 64;
   if code[6 ] = 1 then
      hammingRead := hammingRead + 32;
   if code[7 ] = 1 then
      hammingRead := hammingRead + 16;
   if code[9 ] = 1 then
      hammingRead := hammingRead + 8;
   if code[10] = 1 then
      hammingRead := hammingRead + 4;
   if code[11] = 1 then
      hammingRead := hammingRead + 2;
   if code[12] = 1 then
      hammingRead := hammingRead + 1;
   close(fp);
end;

var
   written : hammingCode;
   i : integer;
begin
   written := hammingWrite('msg.hamming', ord('-'));
   writeln('written:');
   for i := 1 to 12 do
         write(written[i]);
   writeln;
   writeln('Press a key to read.');
   readln;
   writeln('read:', chr(hammingRead('msg.hamming')));
   readln();
end.

