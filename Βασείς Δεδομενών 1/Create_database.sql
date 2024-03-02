-- 1.)Δημιουργία Βασή Δεδομενών
CREATE DATABASE personel;
-- 2.)Χρησιμοποίω Βασή
USE personel;
-- 3.)Δημιουργό τους Πινακές
CREATE TABLE DEPT(DEPTNO INT(2) NOT NULL, 
                     DNAME VARCHAR(14), LOC VARCHAR(14),
                     PRIMARY KEY(DEPTNO));
CREATE TABLE EMP(EMPNO INT(4) NOT NULL, 
                    ENAME VARCHAR(10), JOB VARCHAR(9), 
                    MGR INT(4), HIREDATE DATE,  
                    SAL FLOAT(7,2), COMM FLOAT(7,2),
                    DEPTNO INT(2), 
         PRIMARY KEY(EMPNO),
         FOREIGN KEY(DEPTNO) REFERENCES DEPT(DEPTNO));
DESCRIBE DEPT;
DESCRIBE EMP;
SHOW TABLES;
-- 4.)Εισάγω στοιχεία
INSERT INTO DEPT(DEPTNO, DNAME, LOC) 
            VALUES (10, 'ACCOUNTING', 'NEW YORK'); 
INSERT INTO DEPT VALUES (20, 'RESEARCH', 'DALLAS');                                                                     
INSERT INTO DEPT(DNAME, DEPTNO, LOC)
            VALUES ('SALES', 30, 'CHICAGO');                                                                    
INSERT INTO DEPT(DEPTNO, LOC, DNAME)
            VALUES (40, 'BOSTON', 'OPERATIONS');                                                                     
INSERT INTO EMP
     (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
         VALUES (7369, 'SMITH', 'CLERK', 7902, '1980/12/17', 800, NULL, 20);
INSERT INTO EMP
     (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
          VALUES (7499, 'ALLEN', 'SALESMAN', 7698, '1981/02/20', 1600, 300, 30);                    
INSERT INTO EMP
     (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
          VALUES (7521, 'WARD', 'SALESMAN', 7698, '2002/02/01', 1250, 500, 30);                    
INSERT INTO EMP
     (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
          VALUES (7566, 'JONES', 'MANAGER', 7839, '1981/12/24', 2975, NULL, 20);                    
INSERT INTO EMP
      (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
       VALUES (7654, 'MARTIN', 'SALESMAN', 7698, '1981/10/28', 1250, 1400, 30);                    
INSERT INTO EMP
       (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
        VALUES (7698, 'BLAKE', 'MANAGER', 7839, '2001/05/02', 2850, NULL, 30);                    
INSERT INTO EMP
        (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
       VALUES (7782, 'CLARK', 'MANAGER', 7839, '1981/11/27', 2450, NULL, 10);                    
INSERT INTO EMP
     (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
         VALUES (7788, 'TT', 'ANALYST', 7566, '1987/04/29', 3000, NULL, 20);                    
INSERT INTO EMP
       (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
        VALUES (7839, 'KING', 'PRESIDENT', NULL, '1987/11/12', 5000, NULL, 10);                    
INSERT INTO EMP
       (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
            VALUES (7844, 'TURNER', 'SALESMAN', 7698, '2007/10/19', 1500, 0, 30);     
INSERT INTO EMP
         (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
            VALUES (7876, 'ADAMS', 'CLERK', 7788, '2003/05/07', 1100, NULL, 20);                    
INSERT INTO EMP
          (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
            VALUES (7900, 'JAMES', 'CLERK', 7698, '2003/12/12', 950, NULL, 30);                    
INSERT INTO EMP
           (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
            VALUES (7902, 'FORD', 'ANALYST', 7566, '2003/12/19', 3000, NULL, 20);                    
INSERT INTO EMP
          (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
            VALUES (7934, 'MILLER', 'CLERK', 7782, '2003/01/19', 1300, NULL, 10);    
INSERT INTO EMP
          (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO)
    VALUES (7999, 'BATES', 'ANALYST', 7566, '2004/01/04', 1300, NULL, NULL);            
-- --------------------------------------------------------------------------
-- 5.) Πως βλέπω περιεχόμενα πινακών
SELECT *FROM EMP;
SELECT *FROM DEPT;
-- 6)Πάραδειγματα πάνω στην βάση
SELECT empno,ename,sal+comm
FROM EMP;

SELECT empno, ename, sal+IFNULL(comm,0)
FROM EMP;

-- 7.) Δείξτε στοιχεία για αναλυτές, προγραμματιστές ταξινομημένες κατά θέση και κατά όνομα
SELECT empno "code", ename "name", job "θέση", sal "αμοιβή", 
               sal+IFNULL(comm, 0) "σύνολο"
FROM EMP
WHERE job IN ('ANALYST', 'PROGRAMMER')
ORDER BY job, ename;

-- 8.) Υπολογιστε μέσο ορο,μιν,μαχ,σαμ μισθου
SELECT AVG(sal),MIN(sal),MAX(sal),SUM(sal),COUNT(sal),count(comm),
COUNT(*)
FROM EMP;

SELECT AVG(sal), MIN(sal), MAX(sal), SUM(sal), COUNT(sal), 
               SUM(sal), COUNT(sal), COUNT(*) 
FROM EMP
WHERE job='ANALYST';

-- 9.)Δειξτέ θέσεις υπαλλήλων
SELECT DISTINCT job
FROM EMP
ORDER BY job;

-- 10.)Δείξτε θέσεις σε κάθε τμήμα
SELECT DISTINCT deptno, job
FROM EMP
ORDER BY deptno ASC, job ASC;

-- 11.)Δείξτε αναλύτες,προγραμμιστές με μισθό μεταξύ 1000 και 7000
SELECT ename,job,sal 
FROM EMP
WHERE job IN('ANALYST','PROGRAMMER')
AND sal>=1000 AND sal <=7000;

-- ----------------------------------
SELECT ename, job, sal 
FROM EMP
WHERE (job IN ('ANALYST', 'PROGRAMMER'))
AND (sal>= 1300 OR sal+IFNULL(comm,0)>= 1500)
ORDER BY job, ename, sal;


-- 12.)Δήλωση update
UPDATE EMP
SET Job='ANALYST'
WHERE ename='ADAMS';

UPDATE EMP
SET sal=1.1*sal
WHERE job='CLERK'; 




