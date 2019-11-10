DROP TABLE student;


CREATE TABLE student (
   id int,
   name varchar(50),
   subname varchar(50),
   marks int,
   PRIMARY KEY(id)
);


INSERT INTO student VALUES(100,'name0','sub0','00');
INSERT INTO student VALUES(101,'name1','sub1','10');
INSERT INTO student VALUES(102,'name2','sub2','20');
INSERT INTO student VALUES(103,'name3','sub3','30');
INSERT INTO student VALUES(104,'name4','sub4','40');


#1 get names of all students with procedure

DELIMITER $$

CREATE PROCEDURE getnames()
BEGIN
    SELECT 
        name
    FROM 
        student
END$$

DELIMITER;

CALL getnames();



#2 PASS ID AND RECIEVE STUDENT NAME

DELIMITER $$

CREATE PROCEDURE getstudentname(
    IN checkid int
)
BEGIN
    SELECT
        name
    FROM
        student
    WHERE
        id = checkid;
END$$

DELIMITER ;


CALL getstudentname(101);

#3 PASS TWO PARAMETERS AND GET STUDENT NAME

DELIMITER $$

CREATE PROCEDURE getnameusingtwovariables(
    IN checkid int,
    IN checksubname varchar(50)
)
BEGIN
    SELECT
        name
    FROM
        student
    WHERE
        id = checkid
    AND
        subname = checksubname;
END $$

DELIMITER ;


#4 ADD GENDER COULMN AND A PROCEDURE TO FIND COUNT OF A SPECIFIC GENDER
ALTER TABLE student  
ADD gender varchar(10);

UPDATE student  SET gender = 'male'  WHERE id = 100;
UPDATE student  SET gender = 'female'  WHERE id = 101;
UPDATE student  SET gender = 'male'  WHERE id = 102;
UPDATE student  SET gender = 'female'  WHERE id = 103;
UPDATE student  SET gender = 'male'  WHERE id = 104;


DELIMITER $$

CREATE PROCEDURE gendercount(
    IN requiredgender varchar(10)
)
BEGIN
    SELECT
        count(*)
    FROM
        student
    WHERE
        gender = requiredgender;
END $$

DELIMITER ;


#5 CREATE A STORED PROCEDURE AND STORE THE ANSWER

DELIMITER $$

CREATE PROCEDURE getnameandstore(
    IN requiredid int;
)
BEGIN
    SELECT
        name
    FROM
        student
    WHERE
        id = requiredid;
END $$

DELIMITER ;

CALL getnameandstore(100,@ansname);
SELECT @ansname;

