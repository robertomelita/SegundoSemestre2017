use northwind;

select * from orders where OrderDate>'1996-07-01' and OrderDate<'1996-07-31' and ShipCountry like "f_____";