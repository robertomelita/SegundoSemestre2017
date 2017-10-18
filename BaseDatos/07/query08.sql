USE northwind;

select ProductName,sum(order_details.UnitPrice*Quantity) as VolumenNegocio
from order_details
join products 
on order_details.ProductID = products.ProductID
group by ProductName
order by VolumenNegocio desc;