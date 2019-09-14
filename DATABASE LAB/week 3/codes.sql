DROP TABLE student;
DROP TABLE registration;
DROP TABLE courses;
CREATE TABLE student (
    roll varchar(10) NOT NULL UNIQUE,
    name varchar(255),
    gender varchar(10),
    address varchar(255),
    PRIMARY KEY(roll)
);


CREATE TABLE courses (
    cid varchar(10) NOT NULL UNIQUE,
    name varchar(255)
);


CREATE TABLE registration(
    roll varchar(10), 
    cid varchar(255),
    PRIMARY KEY(roll,cid)
);


INSERT INTO student VALUES('s100' , 'name1' , 'male' , 'address1');  
INSERT INTO student VALUES('s101' , 'name2' , 'female', 'address2'); 
INSERT INTO student VALUES('s102' , 'name3' , 'male', 'address3'); 
INSERT INTO student VALUES('s103' , 'name4' , 'male' , 'address4'); 
INSERT INTO student VALUES('s104' , 'name5' , 'female', 'address5'); 



INSERT INTO courses VALUES('c103','OS');
INSERT INTO courses VALUES('c101','DDS');
INSERT INTO courses VALUES('c203','DSA');
INSERT INTO courses VALUES('c403','DATABASE');
INSERT INTO courses VALUES('c102','NETWORKS');

INSERT INTO registration VALUES('s100','c103');
INSERT INTO registration VALUES('s100','c403');
INSERT INTO registration VALUES('s100','c102');
INSERT INTO registration VALUES('s102','c203');
INSERT INTO registration VALUES('s102','c103');
INSERT INTO registration VALUES('s102','c101');
INSERT INTO registration VALUES('s103','c403');
INSERT INTO registration VALUES('s103','c203');
INSERT INTO registration VALUES('s104','c103');
INSERT INTO registration VALUES('s104','c101');


# selecting students who have chosen OS
SELECT student.name FROM 
registration LEFT JOIN courses ON registration.cid = courses.cid
LEFT JOIN student On student.roll = registration.roll
WHERE courses.name = "OS";

#something random
SELECT student FROM (registration LEFT JOIN courses) LEFT JOIN student
ON student.roll = registration.roll AND registration.cid = courses.cid AND courses.name = "OS"
WHERE student.name IS NOT NULL;


#all student name with courses
SELECT student.name,courses.name FROM 
registration LEFT JOIN courses ON registration.cid = courses.cid
LEFT JOIN student On student.roll = registration.roll;


#count of total , male and female students...
SELECT COUNT(*) ,
	COUNT(IF(gender="male",1,null)),
	COUNT(IF(gender="female",1,null))
FROM student;

SELECT gender , COUNT(*) FROM student GROUP BY gender

#no course registered student names
SELECT student.name FROM (student LEFT JOIN registration ON student.roll = registration.roll) where registration.roll IS NULL;


#distinct count of all subject registrations
SELECT cid,COUNT(*) as count FROM registration GROUP BY cid ORDER BY count DESC;


#find all courses registered by s103

SELECT courses.name FROM (registration LEFT JOIN courses ON registration.cid = courses.cid) WHERE registration.roll = "s103";