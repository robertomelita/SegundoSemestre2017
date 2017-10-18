use northwind;

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