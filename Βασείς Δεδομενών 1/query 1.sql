SELECT contactFirstName,contactLastName
FROM customers;

-- exercise 2
SELECT CONCAT(contactFirstName,'-',contactLastName) AS contact_person
FROM customers;

-- exercise 3
SELECT DISTINCT country
FROM customers;

SELECT AVG(creditLimit),MIN(creditLimit),MAX(creditLimit)
FROM customers;
