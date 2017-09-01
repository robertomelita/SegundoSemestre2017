program Multm;
(*Declaraciones*)

type matriz = array[1..3,1..3] of integer;
type vector = array[1..3] of integer;

var a:matriz;
var b:vector;
var r:vector;

var k:integer;

procedure llenarM();
var i:integer;
var j:integer;
begin
    for i := 1 to 3 do
    begin
        for j := 1 to 3 do
        begin
            a[i,j] := 1;
        end;
    end;
end;

procedure llenarV();
begin
    b[1] := 2;
    b[2] := -1;
    b[3] := 1;
    r[1] := 0;
    r[2] := 0;
    r[2] := 0;
end;


begin
    llenarM;
    llenarV;
    cobegin
        Proceso1();
        Proceso2();
        Proceso3();
    coend;
end.

process type Proceso1();
begin
    for k := 1 to 3 do
    begin
        r[1] := r[1]+b[i]*a[1,i];
    end;
end;

process type Proceso2();
begin
    for k := 1 to 3 do
    begin
        r[2] := r[2]+b[i]*a[2,i];
    end;
end;

process type Proceso3();
begin
    for k := 1 to 3 do
    begin
        r[3] := r[3]+b[i]*a[3,i];
    end;
end;