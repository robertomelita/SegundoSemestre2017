use northwind;

SELECT  Country, City,count(City) as nbEmployees from employees
group by Country,City
order by nbEmployees DESC;

create view vista1 as SELECT employees.EmployeeID, sum(UnitPrice*Quantity) as volumen from employees
JOIN orders ON employees.EmployeeID = orders.EmployeeID
JOIN order_details ON orders.OrderID = order_details.OrderID
group by employees.EmployeeID
order by volumen desc;


select *,(select avg(volumen) from vista1) as promedio from vista1
group by EmployeeID
having volumen>promedio
order by volumen desc;



select CompanyName,count(suppliers.SupplierID) as nbProducts  from suppliers
join products On suppliers.SupplierID= products.SupplierID
group by CompanyName
having nbProducts >= 4;


CREATE USER 'user4'@'localhost';
GRANT select on northwind.vista1 to 'user4'@'localhost';




select od.ProductID, od.quantity 
from orders o
join order_details od
ON o.OrderID = od.OrderID
where o.OrderID=10248;

BEGIN;
UPDATE order_details set order_details.Quantity = 15 where OrderID=10248 AND ProductID=11;
update products set products.UnitsInStock = (products.UnitsInStock - 3) where ProductID = 11;
update products set products.UnitsOnOrder = (products.UnitsOnOrder + 3) where ProductID = 11;
commit;

select od.ProductID, od.quantity 
from orders o
join order_details od
ON o.OrderID = od.OrderID
where o.OrderID=10248 ;
select UnitsInStock from products where ProductID=11;
select UnitsOnOrder from products where ProductID=11;