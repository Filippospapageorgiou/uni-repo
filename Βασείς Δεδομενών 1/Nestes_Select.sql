SELECT *
FROM EMP;

-- Περίπτωση 1: Εμφάνιση υπαλλήλων (ENAME) που κάνουν την ίδια δουλειά
-- (JOB) με τον CODD ή τον ELMASRI και έχουν μισθό (SAL) μεγαλύτερο των 1250

SELECT ENAME
FROM EMP
WHERE JOB IN (
SELECT JOB
FROM EMP
WHERE ENAME='CODD' OR ENAME='ELMASRI')
AND SAL > 1250;

-- Περίπτωση 2: Εμφάνιση υπαλλήλων (ENAME, JOB) με μισθό (SAL) μεγαλύτερο
 -- από τον μισθό όσων εργάζονται ως πωλητές

SELECT ENAME "ΟΝΟΜΑ", JOB "ΘΕΣΗ", SAL "ΜΙΣΘΟΣ"
FROM EMP
WHERE SAL > (
SELECT MAX(SAL)
FROM EMP
WHERE JOB = 'SALESMAN');

-- Περίπτωση 3: Εμφάνιση υπαλλήλων (ENAME, SAL) που ανήκουν στο ίδιο τμήμα
-- (DEPTNO) και έχουν την ίδια θέση (JOB) με τον CODD

SELECT ENAME, SAL
FROM EMP
WHERE (DEPTNO, JOB) IN (
SELECT DEPTNO, JOB
FROM EMP
WHERE ENAME = 'CODD');

-- Περίπτωση 4: Εμφάνιση υπαλλήλων (ENAME) που εργάζονται (JOB) ως αναλυτές
-- και ανήκουν σε τμήμα (DEPTNO) που έχει και προγραμματιστή

SELECT ENAME,DEPTNO
FROM EMP
WHERE JOB = 'ANALYST'
AND DEPTNO IN (
SELECT DEPTNO
FROM EMP
WHERE JOB = 'PROGRAMMER');


-- ΝΟΤ ΙΝ
-- Περίπτωση 5: Εμφάνιση υπαλλήλων (ENAME) που εργάζονται (JOB) ως αναλυτές
-- και ανήκουν σε τμήμα (DEPTNO) που δεν έχει πωλητή
SELECT ENAME,DEPTNO
FROM EMP
WHERE JOB = 'ANALYST'
AND DEPTNO NOT IN (
SELECT DEPTNO
FROM EMP
WHERE JOB = 'SALESMAN');

-- Περίπτωση 6: Εμφάνιση υπαλλήλων (ENAME,JOB,SAL) που έχουν την ίδια θέση
-- (JOB) και ανήκουν στο ίδιο τμήμα (DEPTNO) με τον CODD ή τον ELMASRI
SELECT ENAME,JOB,SAL
FROM EMP
WHERE (JOB,DEPTNO) = (
SELECT JOB,DEPTNO
FROM EMP
WHERE ENAME IN ('CODD', 'ELMASRI'));

-- Ανεξάρτητες ενφωλιασμένες select
-- Περίπτωση 7: Εμφάνιση υπαλλήλων (ENAME,JOB,DEPTNO,SAL) που έχουν την
-- ίδια θέση (JOB) με τον CODD ή μισθό (SAL) μεγαλύτερο ή ίσο του DATE. Το
-- αποτέλεσμα να είναι ταξινομημένο κατά θέση (JOB) και μισθό (SAL).

SELECT ENAME,JOB,DEPTNO,SAL
FROM EMP
WHERE JOB IN
(SELECT JOB FROM EMP WHERE ENAME = 'CODD')
OR SAL >=
(SELECT SAL FROM EMP WHERE ENAME = 'DATE')
ORDER BY JOB,SAL;

-- Πολλαπλά ενφωλιασμένη select
-- Περίπτωση 8: Εμφάνιση υπαλλήλων (ENAME,JOB,DEPTNO) που έχουν θέση
-- (JOB) που συναντάται και στα τμήματα SALES και ACCOUNTING (DNAME)

SELECT ENAME,JOB,DEPTNO
FROM EMP
WHERE JOB IN (
SELECT JOB 
FROM EMP
WHERE DEPTNO IN (
SELECT DEPTNO FROM DEPT
WHERE DNAME IN('SALES','ACCOUNTING')));



