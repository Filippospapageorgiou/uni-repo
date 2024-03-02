SELECT productName,quantityInStock
FROM products
WHERE quantityInStock >= 9000;

SELECT *
FROM products
WHERE productVendor = 'WELLY DIECAST PRODUCTIONS';

-- example 3.3
SELECT orderNumber , requiredDate,status
FROM orders
WHERE orderDate>'2005-05-16';

-- exercise 05
SELECT  *
FROM customers
WHERE contactFirstName='Elizabeth';

-- exrcise06
SELECT customerName
FROM customers
WHERE creditLimit > 100000;

-- exercise07
SELECT CONCAT(firstName,' ',lastName) AS full_name
FROM employees
Where jobTitle<>'sales rep'

