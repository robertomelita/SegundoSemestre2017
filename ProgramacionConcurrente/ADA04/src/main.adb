with Ada.Integer_Text_IO;
use Ada.Integer_Text_IO;
with ada.text_io;
use Ada.Text_IO;
with Ada.Numerics.Discrete_Random;

procedure Main is
   task type semD is
      entry wait;
      entry signal;
   end semD;
   task type semI is
      entry wait;
      entry signal;
   end semI;
   task type tren;

   task body semD is
   begin
      loop
         accept wait;
         accept signal;
      end loop;
   end semD;

   task body semI is
   begin
      loop
         accept wait;
         accept signal;
      end loop;
   end semI;

   task body tren is
      i:integer;
   begin
      loop
         if(i<n) then
            sem(i).wait;
            put("avanza");
            sem(i).signal;
         else
            sem(i).wait;
            put("avanza");
            sem(i+1).wait;
            sem(i).signal;
         end if;
      end loop;
   end tren;
end Main;
