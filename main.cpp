#include<iostream>
#include<conio.h>
#include<fstream>
#include<stdlib.h>
#include<cstring>
#include<ctime>
using namespace std;
class hotel
{
	int roomNo;
	string name,address,phone;
	bool isempty()
	{  //checking if the file is empty
		ifstream fin("Record.txt",ios::in);  //opening the file in the reading mode
		if(fin.is_open())
		{
			fin.seekg(0,ios::end);
			size_t size=fin.tellg();
			if(size==0)
				return true;
			else
				return false;
		}
	}
	void modifyCheckin(int rNo,string cn,string ca,string cp)
	{
		 //to get the 
		long pos; //to store position
		int no;  //to store room number
		string n,a,p,s1,s2,s3,s4,s5;  //to store the name,address,phone number date and time fields
		fstream file("Checkin.txt",ios::in|ios::out);
		
		while(!file.eof())  //reading till end of file
		{
			pos=file.tellg(); //to get the current record position
			file>>no>>n>>a>>p>>s1>>s2>>s3>>s4>>s5;  //reading record of size class hotel
			if(no==rNo && n==cn && a==ca && p==cp) {
				file.seekg(pos);  //to go to the current position in the file where we need to edit the details
				file<<" "<<roomNo<<" "<<name<<" "<<address<<" "<<phone<<" "<<s1<<" "<<s2<<" "<<s3<<" "<<s4<<" "<<s5; 
				break;
			}
		}
		file.close();
	}
	void checkin()
	{
		ofstream fout("Checkin.txt",ios::app); //opening file in appending mode
		time_t now =time(0);
		char* dt= ctime(&now);  //getting details of time and date from the system
		fout<<" "<<roomNo<<" "<<name<<" "<<address<<" "<<phone<<" "<<dt;  //storing check-in date and time information
		fout.close();
	}
	void checkout()
	{
		ofstream fout("Checkout.txt",ios::app);  //opening file in appending mode
		time_t now =time(0);
		char* dt= ctime(&now); //getting date and time from the system
		fout<<" "<<roomNo<<" "<<name<<" "<<address<<" "<<phone<<" "<<dt;  //storing check-out date and time information
		fout.close();
	}
	public:
		void mainMenu();   //to display the menu
		void bookRoom();  //to book a room
		void display();  //to display customer record
		void rooms();  //to display the rooms which are occupied
		void edit();  // to edit the customer record
		int check(int rNo);  //to check the status of the room
		void modify(int rNo); //to modify the record or status of room
		void deleteRecord(int rNo); //to delete a record
};
void hotel::mainMenu()
{
	int choice;
	
	while(choice!=5)
	{
		//displaying the menu
		system("cls"); //to clear the screen	
		cout<<"\n\t\t\t\t*************";
		cout<<"\n\t\t\t\t* MAIN MENU *";
		cout<<"\n\t\t\t\t*************";
		cout<<"\n\n\n\t\t\t1.Book A Room";
		cout<<"\n\t\t\t2.Customer Record";
		cout<<"\n\t\t\t3.Rooms Allotted";
		cout<<"\n\t\t\t4.Edit Record";
		cout<<"\n\t\t\t5.Exit";
		cout<<"\n\n\t\t\tEnter Your Choice: ";
		cin>>choice;
		system("cls");
		switch(choice)
		{
			case 1: this->bookRoom();
					break;
			case 2: this->display();
					break;
			case 3: this->rooms();
					break;
			case 4: this->edit();
					break;
			case 5: break;
			default:
					{
						cout<<"\n\n\t\t\tWrong choice!!!";
						cout<<"\n\t\t\tPress any key to continue!!";
						getch();
					}
		}
	}
}
void hotel::bookRoom()
{
	system("cls"); //to clear the screen
	int r,flag;
	ofstream fout("Record.txt",ios::app); //opening file in appenidng mode
	cout<<"\n Enter Customer Detalis";
	cout<<"\n **********************";
	cout<<"\n\n Room no: ";
	cin>>r;
	flag=check(r);  //checing is the room is occupied or available
	if(flag)  //displaying message if the room is already occupied
		cout<<"\n Sorry..!!!Room is already booked";
	else //booking the room if it is vacant
	{
		this->roomNo=r;
		cout<<" Name: ";
		cin>>name;
		cout<<" Address: ";
		cin>>address;
		cout<<" Phone No: ";
		cin>>phone;
		fout<<" "<<roomNo<<" "<<name<<" "<<address<<" "<<phone; //entering the customer details into the file
		this->checkin();
		cout<<"\n Room is booked!!!";
	}
	cout<<"\n Press any key to continue!!";
	getch();
	fout.close();  //closing the file
}
void hotel::display()
{
	system("cls"); //to clear the screen
	ifstream fin("Record.txt",ios::in); //opening the file in reading mode
	int r,flag=0; //setting flag initially to zero 
	cout<<"\n Enter room no: ";
	cin>>r;
	while(!fin.eof())  //reading the file till end of file
	{
		fin>>roomNo>>name>>address>>phone;  //taking each record of size class hotel
		if(roomNo==r) //compating each record with the enterted room number
		{   
			//displaying details if the record is found
			cout<<"\n Customer Details";
			cout<<"\n ****************";
			cout<<"\n\n Room no: "<<roomNo;
			cout<<"\n Name: "<<name;
			cout<<"\n Address: "<<address;
			cout<<"\n Phone no: "<<phone;
			flag=1; //setting flag value to 1 since the record is found in the file
			break;
		}
	}
	if(flag==0)  //displaying message if the record is not found
		cout<<"\n Sorry!! The Room number is not found or vacant!!";
	cout<<"\n\n Press any key to continue!!";
	getch();
	fin.close();  //closing the file
}
void hotel::rooms()
{
	system("cls"); //clearing the screen
	ifstream fin("Record.txt",ios::in);  //opening the file in reading mode to read the data from the file to display
	if(isempty())
	{
		cout<<"All rooms are empty";
		cout<<"\n\n\n\t\t\tPress any key to continue!!";
		getch();
		fin.close(); //closing the file
		return;
	}
	cout<<"\n\t\t\tList Of Rooms Allotted";  
	cout<<"\n\t\t\t*********************";
	cout<<"\n\n Room No.\tName\t\tAddress\t\tPhone No.\n";
	while(!fin.eof()) //reading from file till end of file
	{
		fin>>roomNo>>name>>address>>phone; //reading each record of size class hotel from the file
		cout<<"\n\n "<<roomNo<<"\t\t"<<name; //displaying the the details read from the file
		cout<<"\t\t"<<address<<"\t\t"<<phone;
	}
	cout<<"\n\n\n\t\t\tPress any key to continue!!";
	getch();
	fin.close(); //closing the file
}
void hotel::edit()
{
	system("cls"); //to clear the screen
	int choice,r;  
	//displaying the editing options available
	cout<<"\n EDIT MENU";
	cout<<"\n *********";
	cout<<"\n\n 1.Modify Customer Record";
	cout<<"\n 2.Delete Customer Record(if customer is vacating)";
	cout<<"\n Enter your choice: ";
	cin>>choice;  //reading the choice from the customer
	cout<<"\n Enter room no: ";
	cin>>r; //reading the room number
	switch(choice)
	{
		case 1: this->modify(r);  //calling modify function to change the records
				break;
		case 2: this->deleteRecord(r);  //calling the deleteRecord function to delete the particular record
				break;
		default: cout<<"\n Wrong Choice!!";
	}
	cout<<"\n Press any key to continue!!!";
	getch();
}
int hotel::check(int rNo) //to check the status of the room
{
	int flag=0;  //initially setting flag value to 0
	ifstream fin("Record.txt",ios::in);  //opening the file in the reading mode
	if(isempty())
	{
		return 0;
	}
	while(!fin.eof())  //reading till the file till end of file
	{
		fin>>roomNo>>name>>address>>phone;  //reading each record of size class hotel
		if(roomNo==rNo)  //checking if the room number is equal to the record  
		{
			flag=1;  //setting flag=1 if the the room number is found in the file name
			break;
		}
	} 
	fin.close();
	return flag; //returning 1 if room number is found , 0 otherwise
}
void hotel::modify(int rNo)
{
	long pos,flag=0;  //initially setting flag=0
	string n,a,p;
	fstream file("Record.txt",ios::in|ios::out);  //opening the file in reading & writing in binary format
	while(!file.eof())  //reading till end of file
	{
		pos=file.tellg(); //to get the current record position
		file>>roomNo>>name>>address>>phone;  //reading record of size class hotel
		if(roomNo==rNo)  //checking if the room number is equal to the input room number
		{
			n=name;
			a=address;
			p=phone;
			//editing the details of the room number
			cout<<"\n Enter New Details";
			cout<<"\n *****************";
			cout<<"\n Name: ";
			cin>>name;
			cout<<"\n Address: ";
			cin>>address;
			cout<<"\n Phone no: ";
			cin>>phone;
			file.seekg(pos);  //to go to the current position in the file where we need to edit the details
			file<<" "<<roomNo<<" "<<name<<" "<<address<<" "<<phone;  //writing the new details into the file
			cout<<"\n Record is modified!!"; 
			this->modifyCheckin(rNo,n,a,p);
			flag=1; //setting flag to 1 since the record is found
			break;
		}
	}
	if(flag==0)  //checking if flag value is 0 and printing the message
		cout<<"\n Sorry!! The room number is not found or vacant!!";
	file.close();  //closing the file
}
void hotel::deleteRecord(int rNo)  //to delete a record of the room number rNo
{
	int flag=0; //setting the flag to 0
	char ch;
	ifstream fin("Record.txt",ios::in);  //opening the file in reading mode 
	ofstream fout("temp.txt",ios::out);  //creating a temporary file in writing mode
	while(!fin.eof())  //reading file till end of file
	{
		fin>>roomNo>>name>>address>>phone;   //reading a record os size class hotel
		if(roomNo==rNo) //comparing if the room numbers are equal 
		{
			//displaying the details if the record is found
			cout<<"\n Name: "<<name;
			cout<<"\n Address: "<<address;
			cout<<"\n Phone No: "<<phone;
			cout<<"\n\n Do you want to delete this record(y/n): ";
			cin>>ch;
			if(ch=='n')
				fout<<" "<<roomNo<<" "<<name<<" "<<address<<" "<<phone;  //writing the record into the temporary file if the user does not want to delete the record
			else
			{
				this->checkout();
			}
			flag=1;  //setting flag to 1 since the record id found
		}
		else
			fout<<" "<<roomNo<<" "<<name<<" "<<address<<" "<<phone;  //writing the record to the temporary file
	}
	fin.close(); //closing the files
	fout.close(); 
	if(flag==0) //checking if the flag==0 that is record not found
		cout<<"\n Sorry!! The room number is not found or vacant!!";
	else
	{
		remove("Record.txt"); //removing the original file
		rename("temp.txt","Record.txt"); //renaming the temporary file to original file
	}	
}
int main()
{
	hotel h;
	cout<<"\n\t\t\t****************************";
	cout<<"\n\t\t\t* HOTEL MANAGEMENT PROJECT *";
	cout<<"\n\t\t\t****************************";
	
	cout<<"\n\n\n\n\t\tMade By:";
	cout<<" RAMYA SRI MANTRIPRAGADA";
	cout<<"\n\n\n\n\n\t\t\t\tPress any key to continue!!";
	getch();
	h.mainMenu();
	cout<<"\nSUCCESSFULLY EXITED!!";
	return 0;	
}
