SELECT productName,pl.textDescription AS productLine,p.quantityInStock
FROM products p JOIN productlines pl
     ON p.productLine=pl.productLine; 

-- ASK JOIN
SELECT customers.customerName as customer,
       customers.city as city,sum(payments.amount) as total_amount,
       customers.creditLimit as credit_limit
FROM payments JOIN customers 
      ON payments.customerNumber=customers.customerNumber
WHERE customers.country IN ('Frnace','USA')
GROUP BY payments.customerNumber
ORDER BY total_amount DESC;

-- EXAM 3 Tables join

USE world;

SELECT ct.name AS city,
       ct.population as population,
       COUNT(*) AS languages_spoken
FROM city ct
    JOIN country cn ON ct.countrycode=cn.code
    JOIN countrylanguage cl ON cn.code=cl.countrycode
WHERE cn.name='Greece'
GROUP BY ct.name
ORDER BY population DESC
LIMIT 2;
    
USE sakila;

-- ASK JOIN

SELECT l.name,COUNT(*) AS total_movies
FROM film f JOIN language l
     ON f.language_id=l.language_id
GROUP BY f.language_id;

-- ASK

SELECT CONCAT(a.first_name,' ',a.last_name) AS actor_name,
       COUNT(*) AS total_movies
FROM film_actor fa
     JOIN actor a ON fa.actor_id=a.actor_id
     JOIN film f ON fa.film_id=f.film_id
 GROUP BY a.actor_id
 ORDER BY 2 DESC;
 
 
 SELECT f.title 
 FROM film_category fc 
     JOIN film f ON fc.film_id=f.film_id
     JOIN category c ON fc.category_id=c.category_id
WHERE NOT f.rating  IN('R','NC-17')
      AND f.length BETWEEN 60 AND 90
      AND f.description REGEXP 'boring|love|documentary'
      AND f.replacement_cost <=14
	  AND c.name IN ('Travel','family','comedy','Claccis');


