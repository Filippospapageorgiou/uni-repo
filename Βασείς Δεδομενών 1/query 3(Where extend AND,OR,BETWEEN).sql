SELECT *
FROM employees
WHERE NOT jobTitle='Sales Rep';

SELECT productName,productLine,quantityInStock
FROM products
WHERE productLine='Classic Cars'
      OR productLine='Motorcycles'
ORDER BY productLine,quantityInStock DESC;      

-- Ask1
SELECT checkNumber,paymentDate,amount
FROM payments
WHERE customerNumber = 389
AND (paymentDate >= '2004-01-01' AND paymentDate <='2004-12-31');

-- ASK2
SELECT *
FROM payments
WHERE (amount >= 5000 AND amount <= 15000)
AND (paymentDate >= '2004-01-01' AND paymentDate <='2004-12-31');

-- ASK3
SELECT *
FROM offices
WHERE city= 'London'
      OR city='Paris'
      OR city='Tokyo';

SELECT *
FROM employees
WHERE firstName BETWEEN 'D' AND 'G';      

-- ASK4
SELECT customerName,country,creditLimit
FROM customers
WHERE (country='USA' OR country='Spain' OR country='Italy')
      AND creditLimit BETWEEN 100000 AND 120000
      ORDER BY country,creditLimit DESC;  
      
SELECT *
FROM offices
WHERE city NOT IN('Boston','NYC');
      
      