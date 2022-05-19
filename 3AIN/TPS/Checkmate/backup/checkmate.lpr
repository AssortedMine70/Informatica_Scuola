program checkmate;

{$mode objfpc}{$H+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes
  { you can add units after this };

type
  bmp = file of byte;

// variabili dichiarate qui saranno GLOBALI

// procedure nome(parametri);               ->  void
// function  nome(parametri):tipodiritorno; ->  tipodiritorno
// (parametro, parametro2, .. parametroN: tipoparametro; ...)
// (var parametro: tipoparametro) -> parametro passato per indirizzo

procedure checkmate1(var fp:bmp);
var // variabili LOCALI della funzione
  fw : bmp;
  b, g, r : byte;
  offset, buffer : byte;
  i, j : integer;
begin
  assign(fw, 'scacchiera_1.bmp');
  rewrite(fw);
  seek(fp, 10);
  read(fp, offset);
  reset(fp);
  for i:=0 to offset-1 do
  begin
    read(fp, buffer);
    write(fw, buffer);
  end;
  for i:=0 to 199 do
      for j:=0 to 199 do
          if (((i div 5) mod 2) = 0) xor ((j div 5) mod 2 = 0) then        // div -> divisione INTERA - / -> divisione REALE
            begin
            read(fp, b, g, r);
            write(fw, b, g, r);
            end
          else
            begin
            read(fp, b, g, r);
            write(fw, 0, 0, 0);
            end;
  close(fw);
end;

procedure checkmate2(var fp:bmp);
var // variabili LOCALI della funzione
  fw : bmp;
  b, g, r : byte;
  offset, buffer : byte;
  i, j : integer;
begin
  assign(fw, 'scacchiera_2.bmp');
  rewrite(fw);
  seek(fp, 10);
  read(fp, offset);
  reset(fp);
  for i:=0 to offset-1 do
  begin
    read(fp, buffer);
    write(fw, buffer);
  end;
  for i:=0 to 199 do
      for j:=0 to 199 do
          if (((i div 5) mod 2) = 0) xor ((j div 5) mod 2 = 0) then        // div -> divisione INTERA - / -> divisione REALE
            begin
            read(fp, b, g, r);                                  
            write(fw, 0, 0, 0);
            end
          else
            begin
            read(fp, b, g, r);                                  
            write(fw, b, g, r);
            end;
  close(fw);
end;

var // variabili del main -> visibili solo nel main
  fp : bmp;

begin
  assign(fp, 'image.bmp');
  // rewrite(fp) -> RICREA il file / reset(fp) -> APRE il file
  reset(fp);
  checkmate1(fp);
  checkmate2(fp);
  close(fp);
end.


