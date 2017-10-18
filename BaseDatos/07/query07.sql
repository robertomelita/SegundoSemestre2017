USE northwind;

select CompanyName,count(products.SupplierID) as nbProducts
from suppliers 
join products 
on products.SupplierID = suppliers.SupplierID
group by CompanyName
order by nbProducts desc;