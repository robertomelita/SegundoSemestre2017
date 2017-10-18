use northwind;

select 	ProductName, 
		UnitPrice,
		(select avg(UnitPrice)from products) as Promedio
from products
having UnitPrice>Promedio
order by UnitPrice desc;