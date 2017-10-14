with ada.text_io;
use Ada.Text_IO;

procedure Example is
    task A;
    task B;

    task body A is
    begin
    put_Line("Soy la task A");
    end A;

    task body B is
    begin
    Put_Line("Soy la task B");
    end B;
begin
    null;
end Example;