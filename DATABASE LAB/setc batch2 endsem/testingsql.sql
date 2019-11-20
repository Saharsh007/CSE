
create table items (
	itemid varchar(10),
	itemname varchar(255),
	itemprice int,
	itemqty int,
	primary key(itemid)
);

create table customer(
	cid varchar(10),
	cname varchar(255),
	primary key (cid)
);


create table store(
	storeid varchar(10), 
	itemid varchar(10),
	storelocation varchar(255),
	primary key (storeid,itemid),
	foreign key (itemid) references items(itemid)
);

create table purchase(
	storeid varchar(10),
	cid varchar(10),
	pdate date,
	totalamount int,
	primary key (storeid,cid),
	foreign key (storeid) references store(storeid),
	foreign key (cid) references customer(cid)
);

create table enroll(
	cid varchar(10),	
	storeid varchar(10),
	primary key (cid,storeid),
	foreign key (cid) references customer(cid),
	foreign key (storeid) references store(storeid)
);

insert into items values('i100','name0',100,10);
insert into items values('i101','name1',101,11);
insert into items values('i102','name2',102,12);
insert into items values('i103','name3',103,13);
insert into items values('i104','name4',104,14);
insert into items values('i105','name5',105,15);

insert into customer values('c100','cname0');
insert into customer values('c101','cname1');
insert into customer values('c102','cname2');
insert into customer values('c103','cname3');
insert into customer values('c104','cname4');

insert into store values('s100','i100','location0');
insert into store values('s100','i101','location0');
insert into store values('s101','i102','location1');
insert into store values('s102','i103','location2');
insert into store values('s103','i104','location3');
insert into store values('s103','i105','location3');


insert into purchase values('s100','c100','2019-08-19',10);
insert into purchase values('s101','c100','2019-08-19',12);
insert into purchase values('s100','c101','2019-08-19',11);
insert into purchase values('s101','c102','2019-08-19',12);
insert into purchase values('s102','c103','2019-08-19',14);
insert into purchase values('s103','c104','2019-08-19',15);

insert into enroll values('c100','s100');
insert into enroll values('c101','s100');
insert into enroll values('c102','s103');
insert into enroll values('c102','s101');
insert into enroll values('c103','s103');
insert into enroll values('c103','s102');
insert into enroll values('c104','s103');
insert into enroll values('c104','s102');


-- select c.cid from purcahse p left join enroll e on p.storeid = e.storeid and p.cid = e.cid;  
# wrong thing
select actualval  from (select e.cid as actualval,p.cid as checkval from enroll e left join purchase p on
 p.storeid = e.storeid and p.cid = e.cid where e.cid = 'c103') as new_table
where checkval =c null;


# q2
create view  questiontwo as
select c.cid,c.cname,sum(p.totalamount) from customer c left join purchase p on p.cid = c.cid group by c.cid;

select * from questiontwo;

#q3
delimiter $$
create procedure questionthree(IN passedcid varchar(10))
begin 
select storeid,totalamount from purchase where cid = passedcid;
end $$
delimiter ;

call  questionthree('c100');


#q4
delimiter $$
create procedure questionfour()
begin
create view questionfourview as
select storeid,sum(totalamount) from purchase group by storeid;
end $$
delimiter ;

call questionfour();
select * from questionfourview;


#q5
create table questionfivechangetable(
	storeid varchar(10),
	cid varchar(10),
	pdate date,
	totalamount int,
	changedate date
);

delimiter $$
create trigger questionfive before update on purchase
for each row
begin
 IF NEW.totalamount = 3*OLD.totalamount then
 insert into questionfivechangetable values(old.storeid,old.cid,old.pdate,new.totalamount,CURDATE()) ;
 end if ;
end $$
delimiter ;


update purchase 
set totalamount = 3*totalamount where cid='c100';

select * from questionfivechangetable;


#q6 (not working)
select cid from enroll group by storeid where sum(count(storeid))>
 all(select sum(count(storeid)) from enroll group by storeid);



#using cursor
delimiter $$
create procedure list_name(INOUT name varchar(1000))
begin
declare isdone int default 0;
declare tempstring varchar(255) default "";
declare test_cursor cursor for select cid from items;
declare CONTINUE HANDLER FOR NOT FOUND SET isdone = 1;
open test_cursor;
getlist : LOOP
FETCH test_cursor into tempstring;
if isdone = 1 then 
leave getlist;
end if;
set name = CONCAT(tempstring,";",name);
end LOOP getlist;
close test_cursor;
end $$
delimiter ;


delimiter $$
create procedure testagain(INOUT namelist varchar(1000))
begin
declare isdone int default 0;
declare sometext varchar(100) default "";
create cursor somecursor for select name from items;
declare continue handler for not found set isdone = 1;
open somecursor;
getlist : LOOP
FETCH somecursor into sometext;
if isdone=1 then
leave getlist;
end if;
set namelist = concat(sometext ,";", namelist);
end LOOP getlist;
close somecursor;
delimiter ;





# trigger practice
delimiter $$
create trigger on after insert on purchase
for each row
begin
if new.totalamount = 300 then
insert into questionfivechangetable("somevalues");
end if;
end$$
delimiter ;







#cursor practice
delimiter $$
create procedure practice1(OUT someval varchar(100))
begin
declare ifend int default 0;
declare someval varchar(100);
declare cursor test_cursor on select cid from purchase;
declare continue handler for not found  set ifend = 1;
open test_cursor;
getlist LOOP:
fetch test_cursor into someval;
if ifend = 1 then
leave getlist;
end if;
someval = concat(someval,":",someval)
end LOOP getlist;
close test_cursor;
delimiter ;


# trigger practice again
delimiter $$
create trigger tiggnew on
