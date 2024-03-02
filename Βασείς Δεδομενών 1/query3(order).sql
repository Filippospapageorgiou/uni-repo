 -- exmaple4.1
 SELECT *
 FROM country 
 WHERE Region='Caribbean'
 ORDER BY name;
 
 -- example 4.2
 
 SELECT code
 FROM country
 WHERE Region='Caribbean'
 ORDER by name DESC;
 
 -- example 4.4
 
 SELECT CONCAT(HeadOfState,'of',Name) AS ruler,
               Population as subjects
FROM country
ORDER BY 2 DESC; 

-- exercise 
SELECT name,continent,indepYear
FROM country
WHERE GovernmentForm = 'Republic'
ORDER BY Continent,IndepYear DESC;

-- exmaple 5.2
SELECT *
FROM city
ORDER BY ID
LIMIT 100;

SELECT *
FROM city
WHERE CountryCode ='GRC'
ORDER BY Population DESC
LIMIT 5;

SELECT *  
FROM countrylanguage
WHERE Language='Greek'
ORDER BY Percentage DESC
LIMIT 2;

SELECT *  
FROM countrylanguage
WHERE Language='Greek'
ORDER BY Percentage DESC
LIMIT 3,2;





