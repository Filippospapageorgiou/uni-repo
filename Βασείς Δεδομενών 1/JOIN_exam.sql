SELECT *
FROM EMP,DEPT
WHERE EMP.DEPTNO=DEPT.DEPTNO;

-- Σύνδεση πινάκων
-- Περίπτωση 1: Εμφάνιση ονόματος (ENAME), μισθού (SAL) και έδρας (LOC)
-- πωλητών

SELECT ENAME,JOB,SAL,LOC
FROM EMP,DEPT
WHERE EMP.DEPTNO=DEPT.DEPTNO
AND JOB='SALESMAN';

-- Σύνδεση πινάκων
-- Περίπτωση 2: Εμφάνιση υπαλλήλων (ΕΝΑΜΕ) που απασχολούνται στο project
-- PERSONNEL
SELECT ENAME
FROM EMP,ASSIGN,PROJ
WHERE PROJ.PROJ_CODE=ASSIGN.PROJ_CODE
      AND ASSIGN.EMPNO=EMP.EMPNO
	  AND PROJ.DESCRIPTION="PERSONNEL";
      
-- Περίπτωση 3a: Εμφάνιση υπαλλήλων (ΕΝΑΜΕ) όσων εργάζονται στην πόλη
-- CHICAGO

SELECT EMP.ENAME
FROM EMP, DEPT
WHERE EMP.DEPTNO = DEPT.DEPTNO
AND DEPT.LOC='CHICAGO';