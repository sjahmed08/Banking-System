/**************************************************************

Author: Syed Ahmed
Date: 12/04/2014
Description: Program implements a full banking system 
where customers can look up their account information and make
withdrawls and deposits. 


***************************************************************/

#include<iostream>
#include<fstream>
#include<ctype.h>
#include<iomanip>

using namespace std;

class Bank_Account //create bank_account class
{
public:
	int Acct_number;			//account number
	char name[50];				//name of account holder
	char type;					// declare account type
	int deposit;				// initial deposit
	void create_acct();			//function to create acount
	void modify();				//function to modify account information
	void show_account() const;	//function to show account data
	void dep(int);				//function to deposit money into account
	void withdraw(int);			// function to withdraw money from account
	int retacno() const;		//function to return account number
	int retdeposit() const;		// function to return balance amount
	char rettype() const;		// function to return type of account 
};

void Bank_Account::create_acct()
{
	cout<< "\nEnter account number";
	cin >> Acct_number;
	cout<< "\nEnter the name of the account holder: ";
	cin.ignore();
	cin.getline(name,50); //stores name as a string in char[50]
	cout << "\nEnter Type of the account (C/S): ";
	cin >> type;
	cout<<"\nEnter the initial amount (>= 500 for saving and >=100 for current): ";
	cin >> deposit;
	cout<< "\n\n\nAccount Created...";
}

void Bank_Account::show_account() const
{
	cout<<"\nAccount No. : " << Acct_number;
	cout<<"\nAccount holder name: ";
	cout<< name;
	cout<<"\nType of Account : " <<type;
	cout<<"\nBalance account : " <<deposit;
}

void Bank_Account::modify()
{
	cout<<"\nAccount No. : " <<Acct_number;
	cout<< "\nModify Account Holder Name: ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nModify Type of Account : ";
	cin>>type;
	cout<<"\nModify initial depost: ";
	cin>>deposit;
}

void Bank_Account::dep(int x)
{
	deposit +=x;
}

void Bank_Account::withdraw(int x)
{
	deposit -=x;
}

int Bank_Account::retacno() const
{
	return Acct_number;
}

int Bank_Account::retdeposit() const
{
	return deposit;
}

char Bank_Account::rettype() const
{
	return type;
}

/*****************************************************************
Function declaration
*****************************************************************/

void write_account();		//function to write record in binary file
void display_sp(int);		//function to display account details
void modify_account(int);	//function to modify record of file 
void delete_account(int);	//function to delete record of account
void display_all();			//function to display all accounts
void deposit_withdraw(int, int);	//function to deposit/withdraw from account
void intro();				//introductory screen function

/***************************************************************
THE MAIN FUNCTION
***************************************************************/

int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");    //clears function
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t08. EXIT";
		cout<<"\n\n\tSelect from (1-8) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : "; 
			cin >> num;
			deposit_withdraw(num,1);
			break;
		case '3':
			cout<<"\n\n\tEnter The account No. : "; 
			cin >> num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			cout<<"\n\n\tEnter The account No. : ";
			cin >> num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout <<"\n\n\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		case '7':
			cout << "\n\n\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		case '8': 
			cout <<  "\n\n\tThanks for using bank management system";
			break;
		default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch != '8');
	return 0;
}

void write_account()
{
	Bank_Account ac;
	ofstream outFile;
	outFile.open("account.dat", ios::binary|ios::app);
	ac.create_acct();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
	outFile.close();
}


void display_sp(int n)
{
	Bank_Account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open press any key";
		return;
	}
	cout<<"\nBalance Details\n";

	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
inFile.close();
if(flag==false){
	cout<<"\n\nAccount number does not exist";
}
	
/****************************************************************************
function to modify record of file
*****************************************************************************/

void modify_account(int n);
{

	bool found=false;
	Bank_Account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be opened";
		return;
	}
	while(!File.eof() && found ==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The new details of account "<<endl;
			ac.modify();
			int pos = (-1)*static_cast<int>(sizeof(Bank_Account));
		//	File.seekp(pos.ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
			cout<<"\n\n\t Record Updated";
			found=true;
		}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found";
	}
}
/*****************************************************************************
function to delete record of file
*****************************************************************************/

void delete_account(int n);
{
	Bank_Account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open";
		return;
	}
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted...";
}
/********************************************************************************
Function to display all accounts deposit list
********************************************************************************/

void display_all();
{
	Bank_Account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open";
			return;
	}
	cout<<"\n\n\t\tAccount holder list\n\n";
	cout<<"===================================================";
	cout<<"A/c no.		NAME			TYPE BALANCE\n";
	cout<<"==================================================";
		while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account)))
		{
		//	ac.report();
		}
		inFile.close();
}

/****************************************************************************
Function to deposit and withdraw amounts
****************************************************************************/

void deposit_withdraw(int n, int option);
{
	int amt;
	bool found=false;
	Bank_Account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
		if(ac.retacno() ==n)
		{
			ac.show_account();
		//	if(option == 1)
			{
				cout<<"\n\n\tTO DEPOSIT AMOUNT";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}
			/*if(option==2)
			{
				cout<<"\n\n\tTo Withdraw Amount";
				cout<<"\n\nEnter The amount to be withdrawn";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype() == 'S') || (bal<1000 && ac.rettype()== 'C'))
					cout<<"Insufficience balance";
				else
				ac.withdraw(amt);
			}
			*/
			int post=(-1)*static_cast<int>(sizeof(ac));
	//		File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
			cout<<"\n\n\t Record Updated";
			found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found";
}
/******************************************************************
introduction function
******************************************************************/
void intro();
{
	cout<<"\n\n\n\t BANK";
	cout<<"\n\n\tManagement";
	cout<<"\n\n\t SYSTEM";
	cout<<"\n\n\n\nMADE BY: ";
	cout<<"\n\nSCHOOL: you school name";
	cin.get();
}
}


}






