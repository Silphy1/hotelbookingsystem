//Header Files
#include<iostream>
#include<conio.h>
#include<fstream>
#include<cstdio>
#include<dos.h>
#include<cstdlib>
#include<filesystem>
#include<Windows.h>
#include<string>
#include<stdio.h>

//namespaces
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ofstream;
using std::ifstream;
using std::fstream;
using std::ios_base;
using std::ios;

//Global functions
int main(); //main funciton
void login(); // include the admin login as well a the normal user login
void registeruser(); // register to hotel for a normal user

//2. Build the main menu admin & user main menu(that has 1. Book a room 2. Customer Records 3.Rooms Alloted 4.Edit Record & 5. Exit with a your choice button
//3.Be able to enter cutomer details and get informaitonm includeing, Room No., Name, Adress, Phone Num, No of days till checkout, and a check to see if room is booked

//class hotel
class hotel
{
private:
	//Hotel Inforamtion Variables
	int room_num;
	char name[30];
	char address[50];
	char phone[15];
	int days;
	float totalprice;
public:
	void main_menu();		//to display the main menu
	void main_menuadmin(); //to display admin menu
	void add();				//to book a room
	void display(); 		//to display the customer record
	void rooms();			//to display allotted rooms
	void edit();			//to edit the customer record
	int check(int);	     	//to check room status
	void modify(int);		//to modify the record
	void delete_rec(int);   //to delete the record

};

void hotel::main_menu()
{
	//declaring variables
	int numresp;
	//Getting user responce to the main menu
	cout << "                   Welcome to the Ardin Moore Hotel!\n";
	cout << "                             1 : Book A Room        \n";
	cout << "                             2 : Check Out          \n\n";
	cout << "                      Enter Your Responce Here : ";
	cin >> numresp;
	//linking function to userinput
	if (numresp == 1)
	{
		cout << "Great! You want to book a room! Lets go!";
		Sleep(200);
		add();
	}
	else if (numresp == 2)
	{
		cout << "Great you want to check out! Lets go!" << endl;
		Sleep(200);
		delete_rec(int());
	}
	else
		cout << "No Valid Reponce Detected, Try Again\n";
}

void hotel::main_menuadmin()
{
	//declaring variables
	int numresp;
	//Front Admin Display
	cout << "                  Welcome Admin!\n                   Lets Get you Started!" << endl;
	cout << "                        1 : Book A Room For Customer    " << endl;
	cout << "                        2 : Display Customer Record     " << endl;
	cout << "                        3 : See All Allotted Rooms      " << endl;
	cout << "                        4 : Edit A Cutomer Record		 " << endl;
	cout << "                        5 : Check Room Status           " << endl;
	cout << "                        6 : Modify A Record             " << endl;
	cout << "                        7 : Delete A Cutsomer Record\n\n    " << endl;
	//taking userinput
	cout << "                        Enter Responce Here: ";
	cin >> numresp;
	//linking userinput to the functions in the application
	switch (numresp)
	{
	case 1:
		add();
		break;
	case 2:
		display();
		break;
	case 3:
		rooms();
		break;
	case 4:
		edit();
		break;
	case 5:
		check(int());
		break;
	case 6:
		modify(int());
		break;
	case 7:
		delete_rec(int());
		break;
		default:
			{
			cout << "No Valid Reponce Detected, Try Again\n";
			}
	}
}

void hotel::add()
{
	//declaring varibales
	int r, flag;
	//writing to the file 
	ofstream file("Record.dat", ios::app);
	
	// Checking for room 
	cout << "Enter the customer room number: " << endl;
	cout << "********************************" << endl;
	cout << "Enter the room number: ";
	cin >> r;
	//condition to check if the room is filled 0 & 1 if 1 then it is true and if 0 it is false
	flag = check(r);
	//if statement to react to room being filled or empty
	if(flag)
		cout << "Room is Occupied\n";
	else
	{
		//room_num == r meaninf that the roomnumber in the class would equal r to assign the customer details to that certiain room
		room_num = r;
		// Getting the customer details
		cout << "\n";
		cout << "Enter the Your Name : ";
		cin >> name;
		cout << "Enter Address : ";
		cin >> address;
		cout << "Phone NO. : ";
		cin >> phone;

		//char* = the variable value is the location in memory where the actual assigned value is saved. 
		// Hence, the * means that the variable points to a location in memory where the value can be found.
		
		// this sets the current variables of dat.types in the class function and set it == to the varibale in the origional class like this ->x = x
		// where this->x is the x in the class funtion and the =x is the origional x in the referecned class
		
		//sizeof dtermines the size in bytes of a varibale(x) or data type(int)
		file.write((char*)this, sizeof(hotel));
		cout << "\n Your Room is booked\n";
	}
	cout << "Press any key to continue!" << endl;
	//gets any single character and returns an interger, basically takes in something and does nothing for this specific line in this programm
	_getch();
	//closing the file
	file.close();
}

void hotel::display()
{
	//open the Record File
	ifstream file("Record.dat", ios::in);
	//decalring varibales
	int r, flag;
	//Getting Hotel Room Info
	cout << "Enter the room number: ";
	cin >> r;
	//creating a loop that runs through all the data in the file and gather the inforation from the pointed adress in the reference of the room number
	while (!file.eof())
	{
		//reading the .dat file by getting the pinter adress in the code and traslating it back to a strig value
		file.read((char*)this, sizeof(hotel));
		//Pulls data from the file and outputs the information
			if (room_num == r)
			{
				//outpuuting room information
				cout << "Room No. : " << room_num << "\n";
				cout << "Name : " << name << "\n";
				cout << "Adress : " << address << "\n";
				cout << "Phone NO. : " << phone << "\n";
				//setting flag to = 1 to set up other if statement to put out the room being vacant or not
				flag = 1;
				//braking the statement
				break;
			}
	}
	//flag = 1 so if it does ==0 then the room should be vacan since theres no information on that room  
	if (flag == 0)
	
		cout << "Nobody is in this room, or it is vacant please try again!\n";
		cout << "Please try again later or now up to you!\n";

	//just takes a value
	_getch();
	file.close();
}

void hotel::rooms()
{
	//opening the file to beable to read it ::in opens the file for reading 
	ifstream file("Record.dat", ios::in);
	//Outputting What Its going to do.
	cout << "List of room filled in the hotel\n";
	cout << "**********************************\n";
	cout << "\nRoom No.\nName\nAdress\nPhone\n";
	//declaring variables
	while(!file.eof())
	{
		//while the file has information its going to display every room in the hotel
		file.read((char*)this, sizeof(hotel));
		//also itd going to output the information
		cout << "Room No. : " << room_num << "\n";
		cout << "Name : " << name << "\n";
		cout << "Adress : " << address << "\n";
		cout << "Phone NO. : " << phone << "\n";
	}
	
	_getch();
	//closoing the file
	file.close();
}

void hotel::edit()
{
	//declaring the varibles
	int choice, r;
	//giving the option to the admin
	cout << "\n\n 1.Modify Customer Record";
	cout << "\n 2.Delete Customer Record";
	//getting the user input
	cout << "\n Enter your choice: ";
	cin >> choice;

	//getting the room number to modify for the user
	cout << "\n Enter room no: ";
	cin >> r;

	switch (choice)
	{
	case 1: modify(r);
		break;
	case 2: delete_rec(r);
		break;
	default: cout << "\n Wrong Choice!!";
	}

	cout << "\n Press any key to continue!!!";
	_getch();
}


int hotel::check(int r)
{
	//declaring varibles
	int flag = 0;
	//opening the file to read
	ifstream file("Record.dat", ios::in);
	//setting up a while loop to chek if the room is full 
	while (!file.eof())
	{
		//reading from the file
		file.read((char*)this, sizeof(hotel));
		if (room_num == r)
		{
			//setting flag to 1 if the room is filled then breaking the while loop
			flag = 1;
			break;
		}
	}
	file.close();
	return(flag);
}

void hotel::modify(int r)
{
	//declaring varibales
	long pos, flag=0;
	//opening the file for writing
	fstream file("Record.dat", ios::out|ios::in|ios::binary);
	//while the file is open from the beginning
	while (!file.eof())
	{
		//sets the position of the file to tell where the adress of the variables are
		pos = file.tellg();
		//read from the file everything 
		file.read((char*)this, sizeof(hotel));
		//check to see if the room num is the right number
		if (room_num == r)
		{
			//takes in the new values
			cout << "\n Enter New Details";
			cout << "\n *****************";
			cout << "\n Name: ";
			cin >> name;
			cout << " Address: ";
			cin >> address;
			cout << " Phone no: ";
			cin >> phone;
			//seeks the position of the old values and replaces them with the tellg funciton
			file.seekg(pos);
			//writes to the file replacing old info with the new info 
			file.write((char*)this, sizeof(hotel));
			//tells teh user that the record is updated
			cout << "Record is Updated\n";
			//sets flag to equal 1(true)
			flag = 1;
			//breaks the while loop
			break;
		}
	}
	//if flag is equal to zero then the file could not be found and the room is vacant
	if (flag == 0)
	{
		cout << "Room not found or is vacant\n";
	}
	//closes the file
	file.close();
}

void hotel::delete_rec(int r)
{
	//declaring varibales
	int flag = 0;
	char ch;
	//opening a temp file to rname later and othe roigional file to delete some things
	ifstream file("Record.dat", ios::in);
	ofstream file2("temp.dat", ios::out);
	//reading info from the file
	while (file.eof())
	{
		//reading the data from the file
		file.read((char*)this, sizeof(hotel));
		//gettig the room number and displaying the information
		if (room_num == r)
		{
			cout << "\n Name: " << name;
			cout << "\n Address: " << address;
			cout << "\n Pone No: " << phone;
			cout << "\n\n Do you want to delete this record(y/n): ";
			cin >> ch;
			//taking in userinput
			if (ch == 'n')
			{
				file2.write((char*)this, sizeof(hotel));

				flag = 1;
			}
		}	else
			file2.write((char*)this, sizeof(hotel));

	}
	file.close();
	file2.close();
	if (flag == 0)
	{
		cout << "No room found or vacant\n";
	}
	else
	{
		//deleteing the old file and renam,ing hte temp file by copying the new data in the file
		remove("Record.dat");
		rename("temp.dat", "Record.dat");
	}

}

int main()
{
	//declaring variables
	int numresp;
	//Entrance page
	cout << "                                  Welcome to the Ardin Moore Hotel!      \n";
	cout << "                         Were going to send you to the Login/Registery Page.....";
	Sleep(600);
	cout << "\n" << "\n" << "\n" << "1 : Login\n2 : Register" << endl;
	cout << "Enter Your Responce Here : ";
	cin >> numresp;
	//linking funtions to user responce
	if (numresp == 1)
	{
		login();
	}
	else if (numresp == 2)
	{
		registeruser();
	}
	else
		cout << "No Valid Responce Accepted, Try Again..." << endl;
}

void login()
{
	//calling classes
	hotel main1;
	//declaring variables
	string username, password, admin, adminpassword, un, pass;
	int numresp;
	//taking in the username and password
	cout << "Enter your Username : ";
	cin >> username;
	cout << "Enter  your Password : ";
	cin >> password;
	//opening the file and checking for the admin or username&password
	ifstream read;
	read.open(username + ".txt");
	getline(read, un);
	getline(read, pass);
	read.close();
	//Admin Login
	if (username == un && username == "admin1")
	{
		if (password == pass)
		{
			cout << "Welcome Admin!\n Sending you to the admin menu now....\n";
			Sleep(800);
			main1.main_menuadmin();
		}
	}
	//Normal User Login
	else if (username == un)
	{
		if (password == pass)
		{
			cout << "Welcome " << username << " sending you to the main menu now!\n";
			Sleep(500);
			main1.main_menu();

		}
	}
}

void registeruser()
{
	//decalring varibales
	string username, password;
	int numresp;
	//getting user input
	cout << "Enter your preffered username : ";
	cin >> username;
	cout << "Enter your preffered password : ";
	cin >> password;
	//creating a file of the user input
	fstream file;
	file.open(username + ".txt", ios_base::app);
	//sending the userinput into the file
	file << username << endl;
	file << password << endl;
	//closing the file
	file.close();
	//Getting userresponce to if they want to login to the hotel registry system
	cout << "Your Account is created! Would you like to login now?";
	cout << "Enter your resonce here (1 : Yes & 2 : No) : ";
	cin >> numresp;
	if (numresp == 1)
	{
		cout << "Sending you to the login page now....";
		Sleep(1000);
		login();
	}
	else if (numresp == 2)
	{
		cout << "Exiting the application now....";
		Sleep(1000);
		exit(1);
	}
	else
		cout << "No valid reponce recived. Try Again!" << endl;
}
