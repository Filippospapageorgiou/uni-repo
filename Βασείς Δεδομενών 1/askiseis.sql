-- ASK10
SELECT SUM(quantityOrdered*priceEach) AS totalPrice
FROM orderdetails
WHERE orderNumber BETWEEN 10100 AND 10199;

-- ASK11
SELECT productName
FROM products
WHERE productLine IN ('Vintage Cars','Planes')
     AND productScale IN ('1:18','1:32','1:50') 
ORDER BY  buyPrice DESC
LIMIT 5;

-- ASK12
SELECT city,phone,postalCode
FROM offices
WHERE state IS NULL;