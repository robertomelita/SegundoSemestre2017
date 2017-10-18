use northwind;

select CompanyName,(count( orders.CustomerID )) as nbOrders from customers
join orders
on orders.CustomerID=customers.CustomerID
group by CompanyName
having nbOrders > 20;