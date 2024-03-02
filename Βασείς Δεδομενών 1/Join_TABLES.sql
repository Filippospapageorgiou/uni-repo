CREATE DATABASE EXAM;
USE EXAM;

CREATE TABLE Student(ST_id INT,ST_name VARCHAR(14),ST_surname VARCHAR(14),PRIMARY KEY(ST_id));
CREATE TABLE Course(C_id INT,C_name VARCHAR(14),PRIMARY KEY(C_id));

SHOW TABLES;

INSERT INTO Student(ST_id,ST_name,ST_surname)
            VALUES('1','Filippos','PAPAGEORGIOU');
INSERT INTO Student(ST_id,ST_name,ST_surname)
            VALUES('2','Stelios','PAPAGEROGIOU');
INSERT INTO Course(C_id,C_name)
       VALUES('1','C++');
INSERT INTO Course(C_id,C_name)
       VALUES('2','JAVA');
 


CREATE TABLE ASSINMENT(ST_id INT,C_id INT, 
           PRIMARY KEY(ST_id,C_id),
           FOREIGN KEY(ST_id) REFERENCES Student(ST_id),
           FOREIGN KEY(C_id) REFERENCES Course(C_id));

DROP TABLE ASSINMENT;           
           
CREATE TABLE ASSINMENT(ST_id INT,ST_name VARCHAR(14),C_id INT,C_name VARCHAR(14), 
           PRIMARY KEY(ST_id,C_id),
           FOREIGN KEY(ST_id) REFERENCES Student(ST_id),
           FOREIGN KEY(C_id) REFERENCES Course(C_id)); 
           
INSERT  INTO ASSINMENT(ST_id,C_id)
       VALUES("1","1");
INSERT  INTO ASSINMENT(ST_id,C_id)
       VALUES("1","2");
INSERT  INTO ASSINMENT(ST_id,C_id)
       VALUES("2","2");
INSERT  INTO ASSINMENT(ST_id,C_id)
       VALUES("2","1");
       
 SELECT * FROM ASSINMENT;      
 
 SELECT Student.ST_name,Course.C_name
 FROM Student,ASSINMENT,Course
 WHERE Student.ST_id=ASSINMENT.ST_id AND Course.C_id=ASSINMENT.C_id;
 
       
