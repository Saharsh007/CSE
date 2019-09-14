DROP TABLE student;

CREATE TABLE student (
    id int,
    name varchar(255),
    ip varchar(255)
);


INSERT INTO student VALUES('100' , 'name1 ' , '127.0.0.1' );  
INSERT INTO student VALUES('101' , 'namaaae2' , '127.0.0.1'); 
INSERT INTO student VALUES('102' , 'nabe3' , '127.0.0.1'); 
INSERT INTO student VALUES('103' , 'name4' , '127.0.0.1'); 
INSERT INTO student VALUES('104' , 'name5' , '127.0.0.1'); 
INSERT INTO student VALUES('105' , 'naaaame6', '127.0.0.1'); 
INSERT INTO student VALUES('106' , 'name7ab   ', '127.0.0.1'); 
INSERT INTO student VALUES('107' , '  abname8  ' , '127.0.0.1'); 
INSERT INTO student VALUES('108' , '  name9                 ', '127.0.0.1'); 


#selecting substring of length 3 from beginning from 103
SELECT SUBSTRING( name, 1, 3) AS ExtractString
FROM student;

#aaa substring
SELECT name FROM student 
WHERE locate('aaa',name)>0;


#reverse name
SELECT name,REVERSE(name) FROM student WHERE id = 107;

#remove tailing spaces
SELECT LENGTH(name) as len FROM student;
SELECT TRIM(name) as trimmed  , name as untrimmed from student;

UPDATE student
SET  name = TRIM(TRAILING FROM name);

#length of name
SELECT LENGTH(name) as len FROM student;

#set uppercase
UPDATE student
SET name = UPPER(name);

#print first octant of IP
SELECT LEFT(ip,LOCATE('.',ip) - 1) from student;

#change substring AB TO XY
UPDATE student
SET name  = REPLACE(name,'AB','XY');

#multiply 3 to the name of 107
UPDATE student
SET name = REPEAT(name,3)
WHERE id = 107;

#hex value of student with id 109
SELECT name as acutalname , HEX(name) as hexval FROM student 
WHERE id = 105;