#include <iostream>
#include <fstream>
#include <cctype>
#include<iomanip>
using namespace std;

class Account{
    //Declaring variables
    int accnumber;
    char name[60];
    int deposit;
    char type;
//access identifier
public:
//Declaring and defining functions
//function 1 - to create an account
void Create_account(){
    cout<< "\n \n Enter Account number : ";
    cin>> accnumber;

    cout<< " \n Enter the Name of Account holder : ";
    cin.ignore();//to clear characters from input buffer.
    cin.getline(name,60);

    cout<< "\n Enter Type of Account in form C for Current/S for Saving : ";
    cin>> type;
    type=toupper(type);//to convert it into UPPERCASE.


    cout<<" \n Enter the initial amount(>=1500 for current and >= 1000 for savings ) : ";
    cin>> deposit;
    
    cout<< "\n \n Congratulations, Your Account is Created in our Bank.\n ";
    
    
}

//function 2 - to show the details of the account

void Display_account(){
    cout<<"\n The details of your account are as follows : "<<endl;
    cout<<"\n \n \t \t Account number      = "<< accnumber << endl;
    cout<<"\t \t Account holder name = "<< name <<endl;
    cout<<"\t \t Account Type        = " <<type << endl;
    cout<<"\t \t Balance amount      = "<<deposit <<endl;       
}


//function 3 - to modify details of the account

void Modify_account(){
    cout<<"For account number "<< accnumber<<endl;
    cout<<"Modify Account Holder Name : ";
    cin.ignore();
    cin.getline(name,60);

    cout<<"\n Modify Type of Account(C/S) : ";
    cin>> type;
    type=toupper(type);

    cout<<"\n Modify Amount of money : ";
    cin>> deposit;
   
   Display_account();
}

//Function 4 - to add on the amount deposited
void deposited(int x){
    deposit += x;
}

//Function 5 - to withdraw amount

void withdraw(int y){
    deposit -= y; 
}
 //function 6 - to report data
void reportdata() const
{
	cout<<accnumber<<"    "<<name<<"     "<<type<<"      "<<deposit<<endl;
}

	
int returnaccnumber() const
{
	return accnumber;
}

int returndeposit() const
{
	return deposit;
}

char returntype() const
{
	return type;
}



};

void write_account();	//function to write record in binary file
void display_sp(int);	//function to display account details given by user
void modify_account(int);	//function to modify record of file
void delete_account(int);	//function to delete record of file
void display_all();		//function to display all account details
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
void intro();	//introductory screen function
int main()
{
	char option;
	int num;
	intro();
	do
	{
		
		cout<<"\n\t ::MAIN MENU::";
		cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t08. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) ";
		cin>>option;
	
		switch(option)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4': 
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\tThanks for using the bank managemnt system";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(option!='8');
	return 0;
};


void write_account(){
	Account acc;
	ofstream outFile;
	outFile.open("Account.dat",ios::binary|ios::app);
	acc.Create_account();
	outFile.write(reinterpret_cast<char *> (&acc), sizeof(Account));
	outFile.close();
};


void display_sp(int n)
{
	Account acc;
	bool flag=false;
	ifstream inFile;
	inFile.open("Account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&acc), sizeof(Account)))
	{
		if(acc.returnaccnumber()==n)
		{
			acc.Display_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nThis Account number does not exist";
};

void modify_account(int n)
{
	bool found=false;
	Account acc;
	fstream File;
	File.open("Account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&acc), sizeof(Account));
		if(acc.returnaccnumber()==n)
		{
			acc.Display_account();
			cout<<"\n\nEnter The New Details of the Account"<<endl;
			acc.Modify_account();
			int pos=(-1)*static_cast<int>(sizeof(Account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&acc), sizeof(Account));
			cout<<"\n\n\t The account is updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
};


void delete_account(int n)
{
	Account acc;
	ifstream inFile;
	ofstream outFile;
	inFile.open("Account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&acc), sizeof(Account)))
	{
		if(acc.returnaccnumber()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&acc), sizeof(Account));
		}
	}
	inFile.close();
	outFile.close();
	remove("Account.dat");
	rename("Temp.dat","Account.dat");
	cout<<"\n\n\tThe account is deleted.";
}

void display_all()
{
	Account acc;
	ifstream inFile;
	inFile.open("Account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&acc), sizeof(Account)))
	{
		acc.reportdata();
	}
	inFile.close();
};

void deposit_withdraw(int n, int opt)
{
	int amt;
	bool found=false;
	Account acc;
	fstream File;
	File.open("Account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&acc), sizeof(Account));
		if(acc.returnaccnumber()==n)
		{
			acc.Display_account();
			if(opt==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited : ";
				cin>>amt;
				acc.deposited(amt);
			}
			if(opt==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdrawn : ";
				cin>>amt;
				int bal=acc.returndeposit()-amt;
				if((bal<500 && acc.returntype()=='S') || (bal<1000 && acc.returntype()=='C'))
					cout<<"The balance is insufficient.";
				else
					acc.withdraw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(acc));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&acc), sizeof(Account));
			cout<<"\n\n\tThe account is updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
};


void intro()
{
	cout<<"==========================================================="<<endl;
	cout<<"\t  BANK  MANAGEMENT  SYSTEM  \n";
	cout<<"==========================================================="<<endl;

	
	cin.get();
}; 