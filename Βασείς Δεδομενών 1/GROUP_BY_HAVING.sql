-- example 2.1
SELECT *
FROM country
GROUP BY Continent;

-- example 2.2
SELECT Continent,Region,COUNT(*) AS Countries
FROM country
GROUP BY Continent,Region;

-- example 2.4
SELECT Continent,Region,COUNT(*) AS Countries
FROM country
WHERE Continent IN ('ASIA','EUROPE','AFRICA')
GROUP BY Continent,Region
ORDER BY Continent,Region DESC
LIMIT 10;

SELECT *
FROM country;

SELECT CountryCode,COUNT(Name),SUM(Population),avg(Population)
FROM city
GROUP BY CountryCode WITH ROLLUP;

SELECT Language,COUNT(CountryCode) AS countries
FROM countrylanguage
GROUP BY Language
ORDER BY countries DESC
limit 1;

SELECT name,GovernmentForm,COUNT(*),MAX(GNP),AVG(LifeExpectancy),SUM(SurfaceArea)
FROM country
WHERE Continent IN ('Europe')
GROUP BY GovernmentForm
ORDER BY 3 DESC;

SELECT Continent,COUNT(*) AS countries
FROM country
GROUP BY Continent
HAVING Countries>50;

SELECT Continent,COUNT(*) AS Countries,AVG(Population),SurfaceArea
FROM country
WHERE IndepYear is NOT NULL
GROUP BY Continent
HAVING Countries>10 AND MIN(SurfaceArea)>10
ORDER BY Countries DESC;
















