#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <windows.h>
#include <sstream>
using namespace std;

const char* HOST = "localhost";
const char* USER = "root";
const char* PW = "Spal@1325";
const char* DB = "mydb";


class Student{
private:
	string Id;
public:
	Student(): Id(""){}

	void setId(string Id){
		this->Id=Id;
	}
	string getId(){
		return Id;
	} 
	
};

class Library{
private:
	string Name;
	int Quantity;
public:	
	Library() : Name(""), Quantity(0){}
	
	void setName(string Name){
		this->Name = Name;
	} 
	string getName(){
		return Name;
	} 
	void setQuantity(int Quantity){
		this->Quantity = Quantity;
	} 
	int getQuantity(){
		return Quantity;
	} 
	
};

void admin(MYSQL* connection, Library l, Student s){
	bool closed = false;
	while(!closed){
		int choice;
		cout<<"1. Add Book"<<endl;
		cout<<"2. Add Student"<<endl;
		cout<<"0. Exit"<<endl;
		cout<<"Enter Choice:";
		cin>>choice;
		
		if(choice==1){
			system("cls");     // clears screen
			string name;
			int q;
			
			cout<<"Book Name: ";
			cin>>name;
			l.setName(name);
			
			cout<<"Enter quantity: ";
			cin>>q;
			l.setQuantity(q);
			
			stringstream ss;
			ss<<l.getQuantity();
			string sq = ss.str();
			
			string book = "INSERT INTO lib (Name, Quantity) VALUES('"+l.getName()+"', '"+sq+"') ";
			
			if(!mysql_query(connection, book.c_str())){
				cout<<"Book Inserted"<<endl;
			} 
			else{
				cout<<"Error: "<<mysql_error(connection)<<endl;
			} 
		}
		
		else if(choice == 2){
			system("cls");     // clears screen
			string id;
			cout<<"Enter Student ID: ";
			cin>>id;
			s.setId(id);
			
			string student = "INSERT INTO student (Id) VALUES('"+s.getId()+"')";
			
			if(!mysql_query(connection, student.c_str())){
				cout<<"Book Inserted"<<endl;
			} 
			else{
				cout<<"Error: "<<mysql_error(connection)<<endl;
			} 
		}
		else if(!choice){
			cout<<"Getting Back to Log In Page...."<<endl;
			closed = true;
		}
	}
	Sleep(3000);    // in milisec
}

void display(MYSQL* connection){
	system("cls");
	cout<<"AVAILABLE BOOKS"<<endl;
	cout<<"---------------"<<endl;
	string disp = "SELECT * FROM lib";	// * means select all
	if(mysql_query(connection, disp.c_str())){
		cout<<"Error: "<<mysql_error(connection)<<endl;
	}
	else{
		MYSQL_RES* res;
		res = mysql_store_result(connection);
		if(res){
			int n = mysql_num_fields(res);
			MYSQL_ROW row;
			while(row = mysql_fetch_row(res)){
				for(int i=0; i<n; i++){
					cout<<" "<<row[i];
				}
				cout<<endl;
			}
			mysql_free_result(res);
		}
	}
}

int book(MYSQL* connection, string name){
	string exist = "SELECT Name, Quantity FROM lib WHERE Name = '"+name+"' ";
	if(mysql_query(connection, exist.c_str())){
		cout<<"Error: "<<mysql_error(connection)<<endl;
	}
	else{
		MYSQL_RES* res;
		res = mysql_store_result(connection);
		if(res){
			int n = mysql_num_fields(res);
			MYSQL_ROW row;
			while(row = mysql_fetch_row(res)){
				for(int i=0; i<n; i++){
					if(name == row[i]){
						return atoi(row[i+1]); // atoi->ascii to int, i+1 cuz i+1 is the quantity row
					}
					else{
						cout<<"Book Not Found"<<endl;
					}
				}
			}
		}
		mysql_free_result(res);
	}
	return 0;
	Sleep(5000);
}

void user(MYSQL* connection, Library l, Student s){
	system("cls");
	display(connection);
	string stid;
	cout<<"Enter your ID: ";
	cin>>stid;
	string comp = "SELECT * FROM student WHERE Id = '"+stid+"'";
	
	if(mysql_query(connection, comp.c_str())){
		cout<<"Error: "<<mysql_error(connection)<<endl;
	}
	else{
		MYSQL_RES* res;
		res = mysql_store_result(connection);
		if(res){
			int n = mysql_num_rows(res);
			if(n==1){
				cout<<"Student ID Found."<<endl;
				string bname;
				cout<<"Enter your Book Name: ";
				cin>>bname;
				if(book(connection, bname)>0){
					stringstream ss;
					ss<<book(connection,bname)-1;
					string Sq = ss.str();
					string update = "UPDATE lib SET Quantity ='"+Sq+"' WHERE Name ='"+bname+"' ";
					if(!mysql_query(connection,update.c_str())){
						cout<<"Book is Available. Borrowing Book...."<<endl;
					}
					else{
						cout<<"Error: "<<mysql_error(connection);
					}
				}
				
				else{
					cout<<"Book is not Available."<<endl;
				}
			}
			else if(!n){
				cout<<"This Student does not EXIST."<<endl;
			}
		}
	}
}

int main() {
	Student s;
	Library l;
	
	MYSQL* connection;
	connection = mysql_init(NULL);
	
	if(mysql_real_connect(connection, HOST, USER, PW, DB, 3306, NULL, 0)){
		cout<<"LOGGED IN"<<endl;
	} 
	else{
		cout<<"ERROR: "<<mysql_error(connection)<<endl;
	} 
	Sleep(3000);   // in milisec
	
	bool exit = false;
	while(!exit){
		system("cls");      // clears screen
		int val;
		cout<<"WELCOME TO LIBRARY MANAGEMENT SYSTEM" <<endl;
		cout<<"------------------------------------" <<endl;
		cout<<"1. Administration"<<endl;
		cout<<"2. User"<<endl;
		cout<<"0. Exit"<<endl;
		cout<<"Enter Choice: ";
		cin>>val;
		
		if(val==1){
			system("cls");
			admin(connection,l,s);
		}
		else if(val==2){
			user(connection,l,s);
			Sleep(5000);
		}
		else if(!val){
			exit = true;
			cout<<"Program ends..."<<endl;
			Sleep(3000);
		}
		
	}
	
	mysql_close(connection);
}








