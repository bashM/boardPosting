#include <iostream>
#include <occi.h>
#include <termios.h>
#include <unistd.h>
using namespace std;
using namespace oracle::occi;

string readPassword()
{
    struct termios settings;
    tcgetattr( STDIN_FILENO, &settings );
    settings.c_lflag =  (settings.c_lflag & ~(ECHO));
    tcsetattr( STDIN_FILENO, TCSANOW, &settings );

    string password = "";
    getline(cin, password);

    settings.c_lflag = (settings.c_lflag |   ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &settings );
    return password;
}

void show_help_menu()
{
	cout << "################     Welcome To The Posters     ###################" << endl << endl;
	cout << "Please select what would you like to do?  " << endl<< endl;
	cout << ">>>  V  >>> To View All messages  " << endl;
	cout << ">>>  S  >>> To Search by a given key word of the title" << endl;
	cout << ">>>  B  >>> to view Borads, titles and number of threads  " << endl;
    	cout << ">>>  P  >>> To Post a new messages" << endl;
	cout << ">>>  Q  >>> To Terminating The Programme" << endl << endl;
	cout << "##################################################################"<< endl<<endl;
}
void v_messages(Connection *conn, string tId)
{
	string queryStr = "select * from  messages where tid='" + tId + "'";
      cout << "SQL: " << queryStr<< endl;
    	Statement *stmt = conn->createStatement();
    	stmt->setSQL(queryStr);

	ResultSet *rs = stmt->executeQuery();

	 while (rs->next()) {
		string mId = rs->getString(1);
		string poster = rs->getString(4); 
		string body = rs->getString(2); 
		Timestamp ts = rs->getTimestamp(3); 

		cout << "ID:" << mId << "\t" << "poster:"<< poster <<"\t"<< "date:" << ts.toText("yyyy-mm-dd hh:mi", 0) <<endl;
		cout << body << endl << endl; 		

	}
	stmt->closeResultSet(rs);
    	conn->terminateStatement(stmt);
}

void s_searching(Connection *conn, string keyW){
	string queryStr = "select tid,topic from threads where topic like :1";
    	Statement *stmt = conn->createStatement(); 
    	stmt->setSQL(queryStr);
	stmt->setString(1, "%" + keyW + "%");
	ResultSet *rs = stmt->executeQuery();

	cout <<"Threads ID \t Topic" <<endl; 
	 while (rs->next()) {
        	string tId = rs->getString(1);
		string topic = rs->getString(2);

		cout << tId << "\t" << topic <<endl;
	}
	cout << endl;
	stmt->closeResultSet(rs);
    	conn->terminateStatement(stmt);
}

void v_boards(Connection *conn){

	string queryStr = "select bid, title, (select count(*) from threads where bid = bid) from boards";
	Statement *stmt = conn->createStatement(); 
        stmt->setSQL(queryStr);
        ResultSet *rs = stmt->executeQuery();

        cout <<"Board ID \t number of threads \t title " <<endl; 
         while (rs->next()) {
                string bid = rs->getString(1);
                string title = rs->getString(2);
		int count = rs->getInt(3);

                cout << bid << "\t\t" << count << "\t" <<title <<endl;
        }
        cout << endl;
	stmt->closeResultSet(rs);
	conn->terminateStatement(stmt);


}

void post_message(Connection *conn, string body, string poster, string tid){
	string queryStr = "insert into messages (messageBody,postTime,poster,tid) values (:1,current_timestamp,:2,:3)";
        Statement *stmt = conn->createStatement();

        stmt->setSQL(queryStr);
	stmt->setString(1, body);
        stmt->setString(2, poster);
	stmt->setString(3, tid);

	try {
  	int n = stmt->executeUpdate();
	conn->commit();
	if (n == 0 ){
		cout << "sorry the message can not be posted"<< endl;
		return;
	}
	cout << "the message was posted!"<<endl << endl;
	}catch (SQLException ex){
		cout << "sorry the message can not be posted!" << endl;
		cout << ex.getMessage() << endl << endl;
	}

		conn->terminateStatement(stmt);

}
//view menu
int main()
{

    	string userName;
    	string password;
    	const string connectString = "sunfire.csci.viu.ca";

    	cout << "Your user name: ";
    	getline(cin, userName);

    	cout << "Your password: ";
    	password = readPassword();
    	cout << endl;

    	
    	Environment *env = Environment::createEnvironment();
    	Connection *conn = env->createConnection(userName, password, connectString);

	show_help_menu();
    	char option;
	int rfr_num=0;
	bool loop = true;
	int processed = 6;		//index of processed queue
	int index = -1;
	while(loop){
        //taking input of performing action
		string s;
		cout<<"Enter your selection please >>>>  ";
		cin>>option;
		getline(cin,s);

		switch(option){

			case 'b':{
				v_boards(conn);
  			    		//pushing the
				break;
                	case 'q': {
                    		return 0;
                		}
			}
            		case 'p' :{
                		cout << " enter a user name:";
				string poster;
				cin >> poster; 

				cout << "enter the thread ID:";
				string tid;
				cin >> tid;
				cout << "enter your message: "<<endl;
				string body; 
				cin >> body;
				post_message(conn, body, poster, tid);
                		break;
            		}
         
            		case 'v' :{
				cout << " please enter the thread  ID:"; 
				string tId;
				cin >> tId; 
				v_messages(conn, tId);                
                		break; 
            		}
         
            		case 's':{
				cout << "please enter the word to search for:" ;
				string keyW;
				cin >> keyW;
				s_searching(conn, keyW);               
                		break;
            		}
            		case 'Q' :{
                		loop = false;
                		break;
            		}
    
    			return 0;
    		}
  	}
}
