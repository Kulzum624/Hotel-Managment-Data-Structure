#include<iostream>
#include<stdlib.h>
#include<string>
#include<stack>
#include<queue>
#include<fstream>
#include<conio.h>

using namespace std;
//Prototypes of the Functions Out Side the Class
void for_Admin();
void main_function();
void for_User();
void leave_Room();
void display();
void deleteRoom(int);
void inserting_RoomDetails();


//First Class For the Rooms in Hotel to store the details of the Room
class Room {
public:
	int room_no;
	string room_size;
	bool air_conditioner;
	bool attached_bath;
	bool room_status;
	bool check;
	Room* next;
public:
	//Default Constructor
	Room() {
		room_no = 0;
		room_size = "NULL";
		air_conditioner = attached_bath = room_status = check = false;
	}

	//Parameterised Constructer
	Room(int room_no, string room_size, bool air_conditioner, bool attached_bath, bool room_status, bool check) {
		this->room_no			= room_no;
		this->room_size			= room_size;
		this->air_conditioner	= air_conditioner;
		this->attached_bath		= attached_bath;
		this->room_status		= room_status;
		this->check				= check;
	}
};

//here is the initialisation of the queue
queue <Room> q_Room;

//here is the prototype for the saving all informations of the Room in A file
void saving_Roomdetails(queue <Room> );

//here is the function prototype beacuse of the Room class object
void insertRoom(Room**, int, string, bool, bool, bool, bool);

// The Admin class is for having private password also for having main functions of the hotel for services
class Admin {
	int day, month, year;//customer date of check in or out
	int time;			//customer time of check in or out
	int mobile_no;		//mobile number of the customer
	int order_Room_no;	//This is for Room Number which will be reserved my customers
	string name;		//this is for name of the customer
	string address;		//address of the customer
	string pass;		//password for admin login
	string rev;			//reviews of the customer after leaving the hotel
	Room* h_Room;		//object the above class " ROOM "
public:
	//default constructor
	Admin() {
		day=month=year = 0;
		time = 0;
		name = "NULL";
		mobile_no = 0;
		address = "NULL";
		order_Room_no = 0;
	}
	//function for checking the password after accessing it from the file
	void password() {
		ifstream fin;
		string passo;
		
		fin.open("password.txt");
		getline(fin, passo);
		cout << "ENter the PAssword: ";
		cin >> pass;
		if (pass==passo) {
			system("cls");
			cout << "login"<<endl;
			for_Admin();
		}
		else
			cout << "Invalid Password" << endl;
	}
	//function for creating the file for booking the details of Customer
	void createfile() {
		ofstream fout;
		fout.open("Bookingdetails.txt",ios::app);
		fout << "date\ttime\tRoom NO\tName\tMObile Number\tAddress\n";
	}
	
	//function for taking the details of the customer while booking the room and keeping data in a file
	void book_Room() {
		ofstream fout;
		fout.open("Bookingdetails.txt", ios::app);
		cout << "ENter the details of the Customer: " << endl;
		cout << "Name : ";
		cin.ignore();
		cin >> name;
		cout << endl << "Mobile : ";
		cin.ignore();
		cin >> mobile_no;
		fflush(stdin);
		cout << endl << "Address : ";
		fflush(stdin);
		cin >> address;
		cout << endl << "Time in Hours : ";
		fflush(stdin);
		cin >> time;
		cout << endl << "Day/Month/Year : ";
		fflush(stdin);
		cin >> day;
		fflush(stdin);
		cin >> month;
		fflush(stdin);
		cin >> year;
		cin.ignore();
		cout << endl << "Room # ";
		fflush(stdin);
		cin >> order_Room_no;

		cout << endl << "Room # " << order_Room_no << " succesfully booked" << endl;

		fout << day << "/" << month << "/" << year << "\t\t" << time << "\t\t" << order_Room_no << "\t\t" << name << "\t\t" << mobile_no << "\t\t" << address << endl;
		fout.close();
	}

	//function for accessing the information of the room
	void view_roomInformation() {
		display();
	}

	//function for taking reviews of customer at the time of checking out
	void reviews() {
		ofstream reve;
		cout << "Sir Kindly Write About Our Hotel Service" << endl;
		cin >> rev;
		reve.open("Reviews.txt", ios::app);
		reve << rev;
	}

	//function for acceessing the all booking details from the file
	void display_all_data() {
		ifstream fin;
		string line;
		fin.open("Bookingdetails.txt");
		while (fin) {
			getline(fin, line);
			cout << line << endl;
		}
		fin.close();
	}

};


//function for the inserting the details of the room in queue
void insertRoom(Room** head, int r_no, string r_size, bool ac, bool ab, bool a_status, bool c) {
	Room* new_Room = new Room();
	new_Room->room_no = r_no;
	new_Room->room_size = r_size;
	new_Room->air_conditioner = ac;
	new_Room->attached_bath = ab;
	new_Room->room_status = a_status;
	new_Room->check = c;
	new_Room->next = (*head);
	q_Room.push(*new_Room);
	saving_Roomdetails(q_Room);
}

//this function is for taking the details of Room and then passing it to the insertRoom function to go to queue
void inserting_RoomDetails() {
	Room* head; int r_no; string r_size; bool ac; bool ab; bool a_status; bool c;
	cout << "Enter the Room No ";
	cin >> r_no;
	cout << "Enter the Size of the Room ";
	cin >> r_size;
	cout << "Enter the Air conditioner Status ";
	cin >> ac;
	cout << "Enter the Attach Bath Status ";
	cin >> ab;
	cout << "Enter the Room Status ";
	cin >> a_status;
	cout << "Enter the Room is Empty or Not ";
	cin >> c;
	insertRoom(&head, r_no, r_size, ac, ab, a_status, c);
	cout << "The Details of the Rooms Are Inserted" << endl;
	cout << "Thank You!" << endl;
}

void saving_Roomdetails(queue <Room> tempque) {
	queue <Room> temp;
	temp = tempque;
	ofstream fout;
	fout.open("Roomdetails.txt",ios::app);
	//fout << "Room No:\t\tRoom Size\t\tAir Conditioner\t\tAttach Bath\t\tRoom Status\t\tEmpty/Full" << endl;
	while (!temp.empty()) {
		if (temp.front().air_conditioner == 1 && temp.front().attached_bath == 1 && temp.front().room_status == 1 && temp.front().check == 1) {
			fout << "\t" << temp.front().room_no << "\t\t" << temp.front().room_size << "\t\tYES\t\t\t\tYES\t\t\tOPEN\t\t\tFULL" << endl;
		}
		else if (temp.front().air_conditioner == 1 && temp.front().attached_bath == 1 && temp.front().room_status == 1 && temp.front().check == 0) {
			fout << "\t" << temp.front().room_no << "\t\t" << temp.front().room_size << "\t\tYES\t\t\t\tYES\t\t\tOPEN\t\t\tEMPTY" << endl;
		}
		else if (temp.front().air_conditioner == 1 && temp.front().attached_bath == 1 && temp.front().room_status == 0 && temp.front().check == 1) {
			fout << "\t" << temp.front().room_no << "\t\t" << temp.front().room_size << "\t\tYES\t\t\t\tYES\t\t\tCLOSED\t\t\tFULL" << endl;
		}
		else if (temp.front().air_conditioner == 1 && temp.front().attached_bath == 0 && temp.front().room_status == 1 && temp.front().check == 1) {
			fout << "\t" << temp.front().room_no << "\t\t" << temp.front().room_size << "\t\tYES\t\tNO\t\t\tOPEN\t\t\tFULL" << endl;
		}
		else if (temp.front().air_conditioner == 0 && temp.front().attached_bath == 1 && temp.front().room_status == 1 && temp.front().check == 1) {
			fout << "\t" << temp.front().room_no << "\t\t" << temp.front().room_size << "\t\tNO\t\tYES\t\t\tOPEN\t\t\tFULL" << endl;
		}
		else if (temp.front().air_conditioner == 1 && temp.front().attached_bath == 1 && temp.front().room_status == 0 && temp.front().check == 0) {
			fout << "\t" << temp.front().room_no << "\t\t" << temp.front().room_size << "\t\tYES\t\tYES\t\t\tCLOSED\t\t\tEMPTY" << endl;
		}
		else if (temp.front().air_conditioner == 1 && temp.front().attached_bath == 0 && temp.front().room_status == 0 && temp.front().check == 1) {
			fout << "\t" << temp.front().room_no << "\t\t" << temp.front().room_size << "\t\tYES\t\tNO\t\t\tCLOSED\t\t\tFULL" << endl;
		}
		else if (temp.front().air_conditioner == 0 && temp.front().attached_bath == 0 && temp.front().room_status == 1 && temp.front().check == 1) {
			fout << "\t" << temp.front().room_no << "\t\t" << temp.front().room_size << "\t\tNO\t\tNO\t\t\tOPEN\t\t\tFULL" << endl;
		}
		else if (temp.front().air_conditioner == 0 && temp.front().attached_bath == 1 && temp.front().room_status == 0 && temp.front().check == 1) {
			fout << "\t" << temp.front().room_no << "\t\t" << temp.front().room_size << "\t\tNO\t\tYES\t\t\tCLOSED\t\t\tFULL" << endl;
		}
		else if (temp.front().air_conditioner == 0 && temp.front().attached_bath == 1 && temp.front().room_status == 1 && temp.front().check == 0) {
			fout << "\t" << temp.front().room_no << "\t\t" << temp.front().room_size << "\t\tNO\t\tYES\t\t\tOPEN\t\t\tEMPTY" << endl;
		}
		else if (temp.front().air_conditioner == 1 && temp.front().attached_bath == 0 && temp.front().room_status == 1 && temp.front().check == 0) {
			fout << "\t" << temp.front().room_no << "\t\t" << temp.front().room_size << "\t\tYES\t\tNO\t\t\tOPEN\t\t\tEMPTY" << endl;
		}
		else if (temp.front().air_conditioner == 0 && temp.front().attached_bath == 0 && temp.front().room_status == 1 && temp.front().check == 0) {
			fout << "\t" << temp.front().room_no << "\t\t" << temp.front().room_size << "\t\tNO\t\tNO\t\t\tOPEN\t\t\tEMPTY" << endl;
		}
		else if (temp.front().air_conditioner == 0 && temp.front().attached_bath == 0 && temp.front().room_status == 0 && temp.front().check == 1) {
			fout << "\t" << temp.front().room_no << "\t\t" << temp.front().room_size << "\t\tNO\t\tNO\t\t\tCLOSED\t\t\tFULL" << endl;
		}
		else if (temp.front().air_conditioner == 0 && temp.front().attached_bath == 1 && temp.front().room_status == 0 && temp.front().check == 0) {
			fout << "\t" << temp.front().room_no << "\t\t" << temp.front().room_size << "\t\tNO\t\tYES\t\t\tCLOSED\t\t\tEMPTY" << endl;
		}
		else if (temp.front().air_conditioner == 1 && temp.front().attached_bath == 0 && temp.front().room_status == 0 && temp.front().check == 0) {
			fout << "\t" << temp.front().room_no << "\t\t" << temp.front().room_size << "\t\tYES\t\tNO\t\t\tCLOSED\t\t\tEMPTY" << endl;
		}
		else {
			fout << "\t" << temp.front().room_no << "\t\t" << temp.front().room_size << "\t\tNO\t\tNO\t\t\tCLOSED\t\t\tEMPTY" << endl;
		}
		temp.pop();
	}
	fout.close();
}

//function for the removing any room from the hotel
void deleteRoom(int rno) {
	stack <Room> s_Room;
	stack <Room> s_Room_s;
	stack <Room> s_Roomtwo;
	stack <Room> s_Roomtwo_s;
	Room* temp1 = new Room();
	Room* temp11 = new Room();
	Room* temp2 = new Room();
	Room* temp22 = new Room();
	Room* temp3 = new Room();
	Room* temp33 = new Room();
	if (q_Room.empty()) {
		return;
	}
	if (q_Room.front().room_no == rno) {
		q_Room.pop();
	}
	while (rno != q_Room.front().room_no) {
		temp1->air_conditioner = q_Room.front().air_conditioner;
		temp1->attached_bath = q_Room.front().attached_bath;
		temp1->check = q_Room.front().check;
		temp1->room_no = q_Room.front().room_no;
		temp1->room_size = q_Room.front().room_size;
		temp1->room_status = q_Room.front().room_status;
		s_Room.push(*temp1);
		q_Room.pop();
	}
	q_Room.pop();
	while (!q_Room.empty()) {
		temp11->air_conditioner = q_Room.front().air_conditioner;
		temp11->attached_bath = q_Room.front().attached_bath;
		temp11->check = q_Room.front().check;
		temp11->room_no = q_Room.front().room_no;
		temp11->room_size = q_Room.front().room_size;
		temp11->room_status = q_Room.front().room_status;
		s_Room_s.push(*temp11);
		q_Room.pop();
	}while (!s_Room_s.empty()) {
		temp22->air_conditioner = s_Room_s.top().air_conditioner;
		temp22->attached_bath = s_Room_s.top().attached_bath;
		temp22->check = s_Room_s.top().check;
		temp22->room_no = s_Room_s.top().room_no;
		temp22->room_size = s_Room_s.top().room_size;
		temp22->room_status = s_Room_s.top().room_status;
		s_Roomtwo_s.push(*temp22);
		s_Room_s.pop();
	}
	while (!s_Room.empty()) {
		temp2->air_conditioner = s_Room.top().air_conditioner;
		temp2->attached_bath = s_Room.top().attached_bath;
		temp2->check = s_Room.top().check;
		temp2->room_no = s_Room.top().room_no;
		temp2->room_size = s_Room.top().room_size;
		temp2->room_status = s_Room.top().room_status;
		s_Roomtwo.push(*temp2);
		s_Room.pop();
	}
	while (!s_Roomtwo.empty()) {
		temp3->air_conditioner = s_Roomtwo.top().air_conditioner;
		temp3->attached_bath = s_Roomtwo.top().attached_bath;
		temp3->check = s_Roomtwo.top().check;
		temp3->room_no = s_Roomtwo.top().room_no;
		temp3->room_size = s_Roomtwo.top().room_size;
		temp3->room_status = s_Roomtwo.top().room_status;
		q_Room.push(*temp3);
		s_Roomtwo.pop();
	}
	while (!s_Roomtwo_s.empty()) {
		temp33->air_conditioner = s_Roomtwo_s.top().air_conditioner;
		temp33->attached_bath = s_Roomtwo_s.top().attached_bath;
		temp33->check = s_Roomtwo_s.top().check;
		temp33->room_no = s_Roomtwo_s.top().room_no;
		temp33->room_size = s_Roomtwo_s.top().room_size;
		temp33->room_status = s_Roomtwo_s.top().room_status;
		q_Room.push(*temp33);
		s_Roomtwo_s.pop();
	}
}

//function for the checking out of the hotel for customers
void leave_Room() {
	int rnoo;
	cout << "Enter Your Room Number: " << endl;
	cin >> rnoo;
	stack <Room> s_Room;
	stack <Room> s_Room_s;
	stack <Room> s_Roomtwo;
	stack <Room> s_Roomtwo_s;
	Room* temp1 = new Room();
	Room* temp11 = new Room();
	Room* temp2 = new Room();
	Room* temp22 = new Room();
	Room* temp3 = new Room();
	Room* temp33 = new Room();
	if (q_Room.empty()) {
		return;
	}
	if (q_Room.front().room_no == rnoo) {
		q_Room.pop();
	}
	while (rnoo != q_Room.front().room_no) {
		temp1->air_conditioner = q_Room.front().air_conditioner;
		temp1->attached_bath = q_Room.front().attached_bath;
		temp1->check = q_Room.front().check;
		temp1->room_no = q_Room.front().room_no;
		temp1->room_size = q_Room.front().room_size;
		temp1->room_status = q_Room.front().room_status;
		s_Room.push(*temp1);
		q_Room.pop();
	}
	q_Room.front().check = 0;
	while (!q_Room.empty()) {
		temp11->air_conditioner = q_Room.front().air_conditioner;
		temp11->attached_bath = q_Room.front().attached_bath;
		temp11->check = q_Room.front().check;
		temp11->room_no = q_Room.front().room_no;
		temp11->room_size = q_Room.front().room_size;
		temp11->room_status = q_Room.front().room_status;
		s_Room_s.push(*temp11);
		q_Room.pop();
	}while (!s_Room_s.empty()) {
		temp22->air_conditioner = s_Room_s.top().air_conditioner;
		temp22->attached_bath = s_Room_s.top().attached_bath;
		temp22->check = s_Room_s.top().check;
		temp22->room_no = s_Room_s.top().room_no;
		temp22->room_size = s_Room_s.top().room_size;
		temp22->room_status = s_Room_s.top().room_status;
		s_Roomtwo_s.push(*temp22);
		s_Room_s.pop();
	}
	while (!s_Room.empty()) {
		temp2->air_conditioner = s_Room.top().air_conditioner;
		temp2->attached_bath = s_Room.top().attached_bath;
		temp2->check = s_Room.top().check;
		temp2->room_no = s_Room.top().room_no;
		temp2->room_size = s_Room.top().room_size;
		temp2->room_status = s_Room.top().room_status;
		s_Roomtwo.push(*temp2);
		s_Room.pop();
	}
	while (!s_Roomtwo.empty()) {
		temp3->air_conditioner = s_Roomtwo.top().air_conditioner;
		temp3->attached_bath = s_Roomtwo.top().attached_bath;
		temp3->check = s_Roomtwo.top().check;
		temp3->room_no = s_Roomtwo.top().room_no;
		temp3->room_size = s_Roomtwo.top().room_size;
		temp3->room_status = s_Roomtwo.top().room_status;
		q_Room.push(*temp3);
		s_Roomtwo.pop();
	}
	while (!s_Roomtwo_s.empty()) {
		temp33->air_conditioner = s_Roomtwo_s.top().air_conditioner;
		temp33->attached_bath = s_Roomtwo_s.top().attached_bath;
		temp33->check = s_Roomtwo_s.top().check;
		temp33->room_no = s_Roomtwo_s.top().room_no;
		temp33->room_size = s_Roomtwo_s.top().room_size;
		temp33->room_status = s_Roomtwo_s.top().room_status;
		q_Room.push(*temp33);
		s_Roomtwo_s.pop();
	}
}

//function for the displaying all Room details from the FILE
void display() {
	ifstream fin;
	string line;
	fin.open("Roomdetails.txt");
	while (fin) {
		getline(fin, line);
		cout << line << endl;
	}
	fin.close();
}

//function for the admin user
void for_Admin() {
	Room room;
	Admin admin;
	int x;
	int y;
	cout << "\n\t\tWELCOME TO HOTEL MANAGEMENT PROJECT\n ";
	cout << "\t\t_______________________________________ ";
	cout << "\n\t\t1.Press 1 to book a room              ";
	cout << "\n\t\t2.Press 2 to view room information    ";
	cout << "\n\t\t3.Press 3 to view customer information";
	cout << "\n\t\t4.Press 4 to leave the room           ";
	cout << "\n\t\t5.Press 5 to Insert the room details  ";
	cout << "\n\t\t6.Press 6 to Delete any room details  ";
	cout << "\n\t\t7.Enter 0 to exit                     ";
	cout << "\n\t\t______________________________________";
	cout << "\nSelect your choice                    ";
	cin >> x;
	switch (x) {
	case 1: {
		system("cls");
		admin.book_Room();
		system("pause");
		system("cls");
		for_Admin();
		break;
	}
	case 2: {
		system("cls");
		admin.view_roomInformation();
		system("pause");
		system("cls");
		for_Admin();
		break;
	}
	case 3: {
		system("cls");
		admin.display_all_data();
		system("pause");
		system("cls");
		for_Admin();
		break;
	}
	case 4: {
		system("cls");
		leave_Room();
		admin.reviews();
		cout << "Hope You Enjoyed " << endl << "Have A Safe Journey" << endl;
		system("pause");
		system("cls");
		for_Admin();
		break;
	}
	case 5: {
		system("cls");
		inserting_RoomDetails();
		system("pause");
		system("cls");
		for_Admin();
		break;
	}
	case 6: {
		system("cls");
		cout << "ENter the Number of Room which You want to Delete: ";
		cin >> y;
		deleteRoom(y);
		cout << "The Room # " << y << "has been removed from Our Hotel. " << endl;
		cout << "Thank You!" << endl;
		system("pause");
		system("cls");
		for_Admin();
	}
	case 0: {
		cout << "BYE! BYE!" << endl;
		system("pause");
	}
	}
}

//function for the customer user
void for_User() {
	Room room;
	Admin user;
	int x;
	cout << "\n\t\tWELCOME TO HOTEL MANAGEMENT PROJECT\n ";
	cout << "\t\t_______________________________________ ";
	cout << "\n\t\t1.Press 1 to book a room              ";
	cout << "\n\t\t2.Press 2 to view room information    ";
	cout << "\n\t\t3.Press 3 to leave the room           ";
	cout << "\n\t\t4.Enter 0 to exit                    ";
	cout << "\n\t\t______________________________________";
	cout << "\nSelect your choice                    ";
	cin >> x;
	switch (x) {
	case 1: {
		system("cls");
		user.book_Room();
		break;
	}
	case 2: {
		system("cls");
		user.view_roomInformation();
		system("pause");
		system("cls");
		for_User();
		break;
	}
	case 3: {
		system("cls");
		leave_Room();
		user.reviews();
		cout << "Hope You Enjoyed " << endl << "Have A Safe Journey" << endl;
		break;
	}
	case 0: {
		cout << "Have a Nice Day Sir!" << endl;
		break;
	}
	}
}

//this is main function// or the front or 1st view of our project
void main_function() {
	Admin admin;
	int x;
	cout << "\n\t\tWELCOME TO HOTEL MANAGEMENT PROJECT\n ";
	cout << "\t\t_______________________________________ ";
	cout << "\n\t\t1.Press 1 to Admin   ";
	cout << "\n\t\t2.Press 2 to User    ";
	cout << "\n\t\t3.Enter 0 to exit    ";
	cout << "\n\t\t______________________________________";
	cout << "\nSelect your choice                    ";
	cin >> x;
	switch (x) {
	case 1: {
		admin.password();
		break;
	}
	case 2: {
		for_User();
		break;
	}
	case 3: {
		cout << "Have a Nice Day Sir!" << endl;
		exit(1);
		break;
	}
	}
}

int main() {
	main_function(); //calling the main function to start the program
}