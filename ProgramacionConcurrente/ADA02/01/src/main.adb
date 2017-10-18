with Ada.Text_IO;
use Ada.Text_IO;
with Ada.numerics.Discrete_Random;
use Ada.Numerics.Discrete_Random;
procedure Main is

   task type Cliente;
   task Cajero is
      entry atencion(x:in out integer);
   end Cajero;
   type S is access Cliente;
   A:S;


   --clientes : array(1..100) of Cliente;


   task body Cliente is
      x:integer;
   begin
      Reset(G);
      x:=Random(G);
      Put(x);
      Put_Line("Esperando atencion");
      Cajero.atencion(x);
      Put_Line("Me atendieron!!!!!");
   end Cliente;

   task body Cajero is
   begin
      loop
         accept atencion (x : in out integer) do
            Put_Line("Atendiendo Cliente");
         end atencion;
      end loop;
   end Cajero;

begin
   for i in 1..100
   loop
      A:= new Cliente;
   end loop;
end Main;
