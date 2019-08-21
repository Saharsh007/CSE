use 17co121

DROP TABLE student_d;
DROP TABLE faculty_d;
DROP TABLE student_issue;
DROP TABLE faculty_issue;
DROP TABLE faculty_return;
DROP TABLE student_return;

CREATE TABLE student_d (
    sid varchar(10) NOT NULL UNIQUE,
    name varchar(255),
    age int,
    address varchar(255),
    state varchar(255),
    email varchar(30),
    PRIMARY KEY(sid)
);

CREATE TABLE faculty_d (
    fid varchar(10) UNIQUE NOT NULL,
    name varchar(255) NOT NULL,
    address varchar(255),
    email varchar(30),
    PRIMARY KEY(fid)
 );

CREATE TABLE student_issue (
    sid varchar(10) UNIQUE NOT NULL,
    bookno varchar(10),
    issue_date DATE,
    return_date DATE,
    ADD CONSTRAINT id
    FOREIGN KEY(sid) REFERENCES student_d(sid) ON DELETE CASCADE
);


CREATE TABLE faculty_issue (
    fid varchar(10) UNIQUE NOT NULL,
    bookno varchar(10),
    issue_date DATE,
    return_date DATE,
    ADD CONSTRAINT id
    FOREIGN KEY(fid) REFERENCES faculty_d(fid) ON DELETE CASCADE
);

CREATE TABLE faculty_return (
    fid varchar(10) UNIQUE NOT NULL,
    bookno varchar(10)
);

CREATE TABLE student_return (
    sid varchar(10) UNIQUE NOT NULL,
    bookno varchar(10)
);


INSERT INTO student_d VALUES('s100' , 'name1' , 19 , 'address1' , 'state1' , 'email1@gmail.com');  
INSERT INTO student_d VALUES('s101' , 'name2' , 20 , 'address2' , 'state2' , 'email2@gmail.com'); 
INSERT INTO student_d VALUES('s102' , 'name3' , 18 , 'address3' , 'state3' , 'email3@gmail.com'); 
INSERT INTO student_d VALUES('s103' , 'name4' , 21 , 'address4' , 'state4' , 'email4@gmail.com'); 
INSERT INTO student_d VALUES('s104' , 'name5' , 19 , 'address5' , 'state5' , 'email5@gmail.com'); 
INSERT INTO student_d VALUES('s105' , 'name6' , 19 , 'address5' , 'state6' , 'email5@gmail.com'); 
INSERT INTO student_d VALUES('s106' , 'name7' , 19 , 'address5' , 'state7' , 'email5@gmail.com'); 
INSERT INTO student_d VALUES('s107' , 'name8' , 19 , 'address5' , 'state8' , 'email5@gmail.com'); 
INSERT INTO student_d VALUES('s108' , 'name9' , 19 , 'address5' , 'state5' , 'email5@gmail.com'); 
INSERT INTO student_d VALUES('s109' , 'name10' , 19 , 'address5' , 'state5' , 'email5@gmail.com'); 
INSERT INTO student_d VALUES('s1010' , 'name11' , 19 , 'address5' , 'state10' , 'email5@gmail.com'); 
INSERT INTO student_d VALUES('s1011' , 'name12' , 19 , 'address5' , 'state10' , 'email5@gmail.com'); 
INSERT INTO student_d VALUES('s1012' , 'name13' , 19 , 'address5' , 'state10' , 'email5@gmail.com'); 
INSERT INTO student_d VALUES('s1013' , 'name14' , 19 , 'address5' , 'state11' , 'email5@gmail.com'); 
INSERT INTO student_d VALUES('s1014' , 'name15' , 19 , 'address5' , 'state11' , 'email5@gmail.com'); 



INSERT INTO faculty_d VALUES('f100' , 'name1', 'address1' , 'email1@gmail.com');  
INSERT INTO faculty_d VALUES('f101' , 'name2', 'address2' , 'email2@gmail.com');  
INSERT INTO faculty_d VALUES('f102' , 'name3', 'address3' , 'email3@gmail.com');  
INSERT INTO faculty_d VALUES('f103' , 'name4', 'address4' , 'email4@gmail.com');  
INSERT INTO faculty_d VALUES('f104' , 'name5', 'address5' , 'email5@gmail.com');  
INSERT INTO faculty_d VALUES('f105' , 'name6', 'address6' , 'email6@gmail.com');  
INSERT INTO faculty_d VALUES('f106' , 'name7', 'address7' , 'email7@gmail.com');  
INSERT INTO faculty_d VALUES('f107' , 'name8', 'address8' , 'email8@gmail.com');  
INSERT INTO faculty_d VALUES('f108' , 'name9', 'address9' , 'email9@gmail.com');  
INSERT INTO faculty_d VALUES('f109' , 'name10', 'address10' , 'email10@gmail.com');  
INSERT INTO faculty_d VALUES('f110' , 'name11', 'address11' , 'email11@gmail.com');  
INSERT INTO faculty_d VALUES('f111' , 'name12', 'address12' , 'email12@gmail.com');  
INSERT INTO faculty_d VALUES('f112' , 'name13', 'address13' , 'email13@gmail.com');  
INSERT INTO faculty_d VALUES('f113' , 'name14', 'address14' , 'email14@gmail.com');  
INSERT INTO faculty_d VALUES('f114' , 'name15', 'address15' , 'email15@gmail.com');  



INSERT INTO student_issue VALUES('s101','b102','2019-07-13','2019-07-23');
INSERT INTO student_issue VALUES('s103','b100','2019-07-11','2019-07-22');
INSERT INTO student_issue VALUES('s101','b103','2019-07-13','2019-07-23');
INSERT INTO student_issue VALUES('s110','b204','2019-07-01','2019-07-02');
INSERT INTO student_issue VALUES('s111','b901','2019-07-14','2019-07-30');
INSERT INTO student_issue VALUES('s105','b107','2019-07-12','2019-07-15');


SELECT * FROM student_issue;



INSERT INTO faculty_issue VALUES('f101','b104','2019-07-13','2019-07-23');
INSERT INTO faculty_issue VALUES('f103','b101','2019-07-11','2019-07-22');
INSERT INTO faculty_issue VALUES('f101','b201','2019-07-13','2019-07-23');
INSERT INTO faculty_issue VALUES('f110','b204','2019-07-01','2019-07-02');
INSERT INTO faculty_issue VALUES('f111','b912','2019-07-14','2019-07-30');
INSERT INTO faculty_issue VALUES('f105','b990','2019-07-12','2019-07-15');


INSERT INTO student_return VALUES('s101','b102');
INSERT INTO student_return VALUES('s103','b100');
INSERT INTO student_return VALUES('s101','b103');
INSERT INTO student_return VALUES('s110','b204');
INSERT INTO student_return VALUES('s111','b901');
INSERT INTO student_return VALUES('s105','b107');


INSERT INTO faculty_return VALUES('f101','b104');
INSERT INTO faculty_return VALUES('f103','b101');
INSERT INTO faculty_return VALUES('f101','b201');
INSERT INTO faculty_return VALUES('f110','b204');
INSERT INTO faculty_return VALUES('f111','b912');
INSERT INTO faculty_return VALUES('f105','b990');

#1
INSERT INTO student_issue VALUES('s1120','b110','2019-07-29','2019-08-15');

SELECT * FROM student_issue;

#2
DELETE FROM student_d WHERE name = 'name2'
SELECT * FROM student_d;
SELECT * FROM student_issue;

#3
ALTER TABLE student_issue
ADD COLUMN age INT ;

#4
ALTER TABLE student_return
ADD CONSTRAINT id 
FOREIGN KEY (sid) REFERENCES student_issue(sid)
ON DELETE CASCADE;

ALTER TABLE student_return
ADD CONSTRAINT book
FOREIGN KEY (bookno) REFERENCES student_issue(bookno)
ON DELETE CASCADE;

ALTER TABLE faculty_return
ADD CONSTRAINT id 
FOREIGN KEY (sid) REFERENCES faculty_issue(sid)
ON DELETE CASCADE;

ALTER TABLE faculty_return
ADD CONSTRAINT id  
FOREIGN KEY (bookno) REFERENCES faculty_issue(bookno)
ON DELETE CASCADE;

#5
ALTER TABLE student_d
MODIFY name varchar(20) NOT NULL;

#6
ALTER TABLE faculty_return
DROP CONSTRAINT id


#7
ALTER TABLE student_d
ADD COLUMN phone_no int UNIQUE
PRIMARY KEY(phone_no);

#8
ALTER TABLE student_d
ADD COLUMN pincode int;

#9
ALTER TABLE student_issue
ADD COLUMN phone_no
ADD CONSTRAINT phone_no_student_issue
FOREIGN KEY(phone_no) REFERENCES student_d(phone_no)
ON DELETE CASCADE;

#10
ALTER TABLE student_d
DROP address;

#11
SELECT DISTINCT state from student_d;

#12
SELECT count( DISTINCT(state) ) FROM student_d;

#13
SELECT sid, COUNT(*) AS freq FROM student_d GROUP BY sid 
HAVING COUNT(*) >3;

#14
SELECT sid, COUNT(*) AS freq FROM student_d GROUP BY sid 
HAVING COUNT(*) = 0;

#15
SELECT sid, COUNT(*) AS freq FROM student_d GROUP BY sid 
HAVING COUNT(*) > 0 ;