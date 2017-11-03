with Ada.Text_IO; use Ada.Text_IO;
with Ada.Numerics.Float_Random;


procedure Trenes is

   Num_Estaciones : constant := 5;
   Num_Trenes : constant := 3;

   type Num_Estación is range 1 .. Num_Estaciones;
   type Num_Tren is range 1 .. Num_Trenes;

   package Num_Estación_IO is new Ada.Text_IO.Integer_IO (Num_Estación);
   use Num_Estación_IO;
   package Num_Tren_IO is new Ada.Text_IO.Integer_IO (Num_Tren);
   use Num_Tren_IO;

   task type TSemaforo is
      entry Wait;
      entry Signal;
   end Tsemaforo;
   task body TSemaforo is
    S: integer := 1;  -- Es el contador del semáforo.
   begin
    loop
      select
        when S > 0 =>
          accept Wait;
          S := S - 1;
      or
        accept Signal;
        S := S + 1;
      or
        terminate;
      end select;
    end loop;
  end TSemaforo;

   Semaforos_Estacion : array (Num_Estación) of TSemaforo;

   task type Tren is
           entry Comenzar (Tu_Num : in Num_Tren);
   end Tren;

   Lista_Trenes : array (Num_Tren) of Tren;

   task body Tren is

      Mi_Num: Num_tren;

      procedure Pon_Nombre is
      begin
         Put ("Tren nº"); Put (Mi_Num); Put (": ");
      end Pon_Nombre;

      Espera_En_Estación: constant Duration := 5.0;
      Duración_Mínima: constant Duration := 2.0;
      Factor_Duración: constant Duration := 10.0;
      Azar_Gen: Ada.Numerics.Float_Random.Generator;

      Actual, Siguiente: Num_Estación;
   begin

      Ada.Numerics.Float_Random.Reset (Azar_Gen);

      accept Comenzar (Tu_Num : in Num_Tren) do
         Mi_Num := Tu_Num;
      end Comenzar;

      Pon_Nombre;
      Put_Line ("Comienzo el trayecto");
      Actual := 1;

      loop

         Pon_Nombre; Put ("En estación "); Put (Actual); New_Line;

         delay Espera_En_Estación;

         if Actual = Num_Estaciones then
            Siguiente := 1;
         else
            Siguiente := Actual + 1;
         end if;

          Semaforos_Estacion(siguiente).Wait;

         Pon_Nombre;
         Put ("Trayecto hacia estación ");
         Put (Siguiente);
         New_Line;

         Semaforos_Estacion(Actual).Signal;
         delay Duration (Ada.Numerics.Float_Random.Random (Azar_Gen))
           * Factor_Duración + Duración_Mínima;

         Actual := Siguiente;

      end loop;
   end Tren;


begin

   for I in Lista_Trenes'Range loop
      Lista_Trenes (I).Comenzar (Tu_Num => I);
   end loop;

end Trenes;
