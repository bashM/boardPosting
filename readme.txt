BasheeR,
Final project,
the Poster database!

In this project I have create a pretty simple program that takes users’ input and provide they some information based
on what they have entered in the program.
However, at the begging I thought the project was pretty hard to implant.
So what the program does? I took the idea form the our midterm,
and you did suggested me to take the idea and do an actual hard coded program that has 5 main functions
and 5 main selections. Each selection presented a particular job that users can use to view data from the database.
Those functions are:

1)  V: selection were users can see and view all the messages in the database.
This function takes the key “tid” that is given by the users where they can see a result of the messages
and look at its ID, the poster name, and the date of the posted message.
However, I had such a hard time to do the SQL query as using “tid=:1” as how we usually get the user input,
and pass that input to the query. Then the SQL query can generate the result so they can provide the result as
how it is shown in the database.
After taking so much time to figure how I can let the SQL provide the data.
BasheeR,
At first it was quite odd using such a statement in the query, but it worked!
This is the query I used ( select * form messages where itd=’” +itd + “’; ). It looks weird but it works!

2) S: selection this where users can in only one word that of any give threads.
So the program can generate the every singe message that is under threads.
Then users can see the Id, and the topic of the message,
so users can the id later on to view and post messages.
The SQL query that I used is ( select tid, topic form threads where topic like:1).
In which users can see the threads ID, and the topic.

3) B: selection were users can view the boards, titles, and the number of threads in here
the program will generate everything things in the data base under  bid, number of threads, and titles.
The query I used is ("select bid, title, (select count(*) from threads where bid = bid) from boards";)
which count how many threads there were in the given table.

4) P: selection where users can post messages and those messages can be inserted in the database right a way.
At first I was having a hard time get the messages stored in the database,
but then I found out that the messages has to be committed in the database
so I had to use this extra line (conn->commit();) where the messages can be stored in the database right away.
And the query I used is an insertion action,
which is provided as ("insert into messages (messageBody,postTime,poster,tid) values (:1,current_timestamp,:2,:3)";)

5) Q: selection where users can Terminate the program and exit out!
Finally, on last lecture we did learn how to use a sequence and use trigger.  
I actually used this method in add and give any new message that posted by the user a unique “mId” so each new message s
tored in the database the trigger table will take care of it. 
Also you can view the base.sql file so you view all the tables and triggers table that is used on this project.

At the end I hope this project met all the requirements and satisfied you.
Thank you!


