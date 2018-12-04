/*
--=================================================
-- Filename:      base.sql
-- Author:        basheer
-- Date:          2016-03-22
-- Institution:   VIU
-- Class:         CSCI 370
-- Project:       project
-- Purpose:       create the tables necessary for testing of project
--
--=================================================

-- == describe all tables (uncomment if needed
--desc Forumusers;
--desc admins;
--desc boards;
--desc threads;
--desc messages;


-- == ensure these tables can be used
-- (drops are called in reverse order of creation)
*/
drop trigger msg_id;
drop sequence msg_seq;
drop table messages;
drop table threads;
drop table boards;
drop table admins;

drop table Forumusers;
CREATE TABLE Forumusers (
	userName CHAR(10) PRIMARY KEY,
	firstName VARCHAR(20) NOT NULL,
	lastName VArCHAR(20) NOT NULL,
	email VARCHAR(80)
	);

CREATE TABLE admins (
	userName CHAR(10) REFERENCES Forumusers,
   PRIMARY KEY (userName)
	);

CREATE TABLE boards (
	bid CHAR(5) PRIMARY KEY,
	title VARCHAR(20) NOT NULL,
	creator VARCHAR (10)NOT NULL,
	createTime TIMESTAMP NOT NULL,
	manager CHAR (10)
	);

CREATE TABLE threads (
 	tid CHAR (10) PRIMARY KEY,
	topic VARCHAR (20) NOT NULL,
	creator VARCHAR (10) NOT NULL,
	createTime TIMESTAMP NOT NULL,
	bid CHAR (5) REFERENCES boards
	);

CREATE TABLE messages (
	mid NUMBER (10) PRIMARY KEY,
	messageBody VARCHAR (50) NOT NULL,
	postTime TIMESTAMP NOT NULL,
	poster VARCHAR (20) NOT NULL,
	tid CHAR (10) REFERENCES threads
	);
CREATE Sequence msg_seq;
create trigger msg_id
before insert on messages
for each row
begin
	select msg_seq.NEXTVAL
	into :new.mid
	from dual;
END;
/

--Forumusers data:

insert into Forumusers
values ('JD', 'Jone', 'Doe', 'jone@live.ca');

insert into Forumusers
values ('lolipop','Mary', 'lele', 'lele@gmail.com');

insert into Forumusers
values ('bad boy','bash','bash', 'bash@live.ca');

insert into Forumusers
values ('boxing', 'mohamd','Ali','ali@hotmail.com');

insert into Forumusers
values ('cool girl', 'kate', 'cool', 'cool@live.ca');

insert into Forumusers
values ('the Man', ' dave', 'james', 'james@gmail.com');

insert into Forumusers
values ('MVP', 'Amer', ' Jhonson', 'amer@raptors.ca');

insert into Forumusers
values ('the best', 'Melo', ' Anthony', 'melo@nyc.com');

insert into Forumusers
values ('AA', 'Will', 'Smith', 'will@hotmail.com');

--admen


--boards

insert into boards
values ('00001', 'data base','AA', to_timestamp('1-1-2015 11:00:00','dd-mm-yyyy HH24:Mi:SS'), 'AA');
insert into boards
values ('7777', 'c++', 'bash', to_timestamp('1-1-2015 12:00:00','dd-mm-yyyy HH24:Mi:SS'), 'bash');

insert into threads
values ('00001', 'math' , 'the best', current_timestamp, '00001');
insert into threads
values ('7777', 'array and lists', 'kate', current_timestamp, '7777');

insert into boards
values ('007', 'life','Melo', to_timestamp('4-4-2015 06:40:00','dd-mm-yyyy HH24:Mi:SS'), 'Melo');
insert into boards
values ('006', 'new', 'dave', to_timestamp('4-5-2015 12:00:00','dd-mm-yyyy HH24:Mi:SS'), 'dave');

insert into threads
values ('007', 'food' , 'Melo', current_timestamp, '007');
insert into threads
values ('006', 'new', 'dave', current_timestamp, '006');
