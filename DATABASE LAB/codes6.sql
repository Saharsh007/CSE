DROP TABLE sales;
DROP TABLE book;

CREATE TABLE book (
    id int,
    name varchar(255),
    price int,
    pages int,
    publisher varchar(255),

    PRIMARY KEY(id)
);


CREATE TABLE sales (
    id int,
    quantitysold int,
    FOREIGN KEY(id) REFERENCES book(id)
);

INSERT INTO book VALUES(100 , 'name1' , 1000 , 300 , 'publisher1'  );  
INSERT INTO book VALUES(101 , 'name2' , 1001 , 301 , 'publisher2'  );  
INSERT INTO book VALUES(102 , 'Oame3' , 1002 , 302 , 'publisher3'  );  
INSERT INTO book VALUES(103 , 'name4' , 1003 , 303 , 'publisher4'  );  
INSERT INTO book VALUES(104 , 'name5' , 1004 , 304 , 'publisher5'  );  
INSERT INTO book VALUES(105 , 'name6' , 1005 , 305 , 'publisher6'  );  
INSERT INTO book VALUES(106 , 'name7' , 1006 , 306 , 'publisher7'  );  
INSERT INTO book VALUES(107 , 'name8' , 1007 , 307 , 'publisher8'  );  
INSERT INTO book VALUES(108 , 'name9' , 1008 , 308 , 'publisher9'  );  
INSERT INTO book VALUES(109 , 'name10' , 1009 , 309 , 'publisher10'  );  
 
INSERT INTO sales VALUES(100,5000);
INSERT INTO sales VALUES(100,9000);
INSERT INTO sales VALUES(101,5001);
INSERT INTO sales VALUES(102,5002);
INSERT INTO sales VALUES(103,5003);
INSERT INTO sales VALUES(104,1);
INSERT INTO sales VALUES(105,5005);
INSERT INTO sales VALUES(107,5007);
INSERT INTO sales VALUES(109,5009);	
INSERT INTO sales VALUES(109,2000);

#books not sold at all
SELECT b.id
FROM book b
    LEFT JOIN sales s ON b.id = s.id
WHERE s.quantitysold IS NULL;

#book name with quantity

SELECT b.name , SUM(s.quantitysold)
FROM book b
	JOIN sales s ON b.id = s.id
WHERE s.quantitysold > 0
GROUP BY b.id;

#4th costliest
SELECT b.name AS BOOK_NAME , b.price AS PRICE 
FROM book b 
ORDER BY b.price DESC LIMIT 3,1;

-- SELECT b.name , SUM(s.quantitysold)
-- FROM book b 
--  	JOIN sales s ON b.id = s.id
-- GROUP BY b.id
-- ORDER BY s.quantitysold DESC LIMIT 3,1;

#sales > sales of at least one other
SELECT book_name
FROM (SELECT book.name as book_name , SUM(sales.quantitysold) as sum FROM sales NATURAL JOIN book GROUP BY book.id ) as new_table
WHERE sum > any ( SELECT SUM(quantitysold) FROM sales GROUP BY id );


#pages > at least one book and starts with 'O'
SELECT book_name , pages 
FROM (SELECT book.name as book_name , SUM(book.pages) as pages FROM sales NATURAL JOIN book GROUP BY book.id ) as new_table
WHERE pages > any ( SELECT SUM(pages) FROM book GROUP BY id ) 
AND book_name LIKE "O%";

#price > at least one book 
SELECT book_name , prices 
FROM (SELECT book.name as book_name , book.price as prices FROM sales NATURAL JOIN book GROUP BY book.id ) as new_table
WHERE prices > any ( SELECT price FROM book GROUP BY id );



#display rank and book number
SET @position := 0;
SELECT 	 (@position := @position + 1) AS rank , name
FROM book
ORDER BY price DESC;