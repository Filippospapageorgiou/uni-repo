-- example 2.1
SELECT *
FROM country
GROUP BY Continent;

-- example 2.2
SELECT Continent,COUNT(*) AS Countries
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