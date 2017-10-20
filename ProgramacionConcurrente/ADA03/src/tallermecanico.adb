with Ada.Text_IO;
with Ada.Integer_Text_IO;
use Ada.Text_IO;
use Ada.Integer_Text_IO;

procedure Tallermecanico is

   task type buzon is
      entry citaMecanico;
      entry entregaUsuario(patente: in integer);
   end buzon;

   type pbuzon is access buzon;

   task type usuario is
   end usuario;

   task type mecanico is
      entry citaUsuario(x: out pbuzon);
   end mecanico;




   task body usuario is
      x:pbuzon;
      patente:integer;
   begin
      patente:=1010101;
      mecanico.citaUsuario(x);
      Put("Estoy trabajando, ");
      Put_Line(x);
      x.entregaUsuario(patente);
   end usuario;

   task body mecanico is
      y: pbuzon;
      patente:integer;
   begin
      loop
         accept citaUsuario(x: out pbuzon) do
            x:= new buzon;
            y:= x;
         end citaUsuario;
         Put("Soy el mecanico: Estoy arreglando el auto ");
         y.citaMecanico(patente);
      end loop;
   end mecanico;

   task body buzon is
   begin
      accept citaMecanico (x : out pbuzon) do
         Put_Line("Recibiendo auto");
      end citaMecanico;
      accept entregaUsuario  do
         Put_Line("Entregando a usuario");
      end entregaUsuario;

   end buzon;

   mec:mecanico;

begin
   null;
end Tallermecanico;
