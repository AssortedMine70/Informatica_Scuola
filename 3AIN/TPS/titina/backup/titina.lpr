program titina;

{$mode objfpc}{$H+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes
  { you can add units after this };

type
  alphaType = array['a'..'z'] of integer;
var
  tit : text;
  i, chr, lastchr, max, min : char;
  j, k, len, vocs, cons, doubles, glutamyCount, soleucyCount : integer;
  charOccursion : alphaType;
  glutamy: string = 'glutamy';
  soleucy: string = 'soleucy';

begin
  assign(tit, 'titina.txt');
  reset(tit);
  len := 0; vocs := 0; cons := 0; doubles := 0; glutamyCount := 0; soleucyCount := 0; j := 1; k:= 1; max := 'a'; min := 'a'; lastchr := char(0);
  for i:='a' to 'z' do
      charOccursion[i] := 0;
  while not eof(tit) do
  begin
    read(tit, chr);
    if (chr >= 'a') and (chr <= 'z') then
    begin
      len := len+1;
      charOccursion[chr] := charOccursion[chr]+1;
        if chr in ['a', 'e', 'i', 'o', 'u'] then
           vocs := vocs+1
        else
           cons := cons+1;
      if lastchr = chr then
         doubles := doubles+1;
      if glutamy[j] = chr then
         if j = length(glutamy) then
            begin
                 glutamyCount := glutamyCount+1;
                 j := 0;
            end
         else
            j := j+1
      else
         j := 1;
      if soleucy[k] = chr then
         if k = length(soleucy) then
            begin
                 soleucyCount := soleucyCount+1;
                 k := 0;
            end
         else
            k := k+1
      else
         k := 1;
      lastchr := chr;
    end;
  end;
  writeln('Lunghezza Proteina: ', len);
  writeln('Numero Vocali     : ', vocs);
  writeln('Numero Consonanti : ', cons);
  writeln('Numero Doppie     : ', doubles);
  writeln('Occorrenza Lettere:');
  for i:='a' to 'z' do
      begin
      if charOccursion[i] > charOccursion[max] then
         max := i;
      if (charOccursion[i] < charOccursion[min]) and (charOccursion[i] <> 0) then
         min := i;
      if charOccursion[i] <> 0 then
         writeln(char(i), ': ', charOccursion[i]);
      end;
  writeln('Lettera dalla maggior occorrenza: ', max);
  writeln('Lettera dalla minor   occorrenza: ', min);
  writeln('Presenza della parola ''glutamy'': ', glutamyCount, 'volte.');
  writeln('Presenza della parola ''soleucy'': ', soleucyCount, 'volte');
  readln();
end.

