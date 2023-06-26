#ifndef employee_h
#define employee_h
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>
#include <ctime>
#include <iomanip>
#include "functions.hpp"



using namespace std;


class Employee
{
	protected:
		string national_code, gender, first_name, last_name, phone_num, date_of_birth, email_address ;
		string password;

		string personal_code;
		long long salary;

	public:

        void Signin();

		void View_customer_accounts();
		void Transaction(string sender_account, string reciver_accout, int ccv2, string expire_date, long amount);
		void View_request();



};


void Employee::Signin()
{
    ofstream  Employee("new_employee.csv",ios::app);

	cout << "NATIONAL CODE : " ;
	getline(cin,national_code) ;
	national_code += ',';

	cout << "PASSWORD : " ;
	getline(cin,password) ;
	unsigned int hash_pass= Hash(password);
    string hashpass = numberToString(hash_pass) + ',';

	cout << "GENDER : " ;
	getline(cin,gender) ;
	gender +=',';

	cout << "FIRST NAME : " ;
	getline(cin,first_name) ;
	first_name += ',';

	cout << "LAST NAME : " ;
	getline(cin,last_name) ;
	last_name += ',';

	cout << "PHONE NUMBER : " ;
	getline(cin,phone_num) ;
	phone_num += ',';

	cout << "DATE OF BIRTH (1402/3/17) : " ;
	cin  >> date_of_birth ;
	date_of_birth += ',';

	cout << "EMAIL ADDRESS: " ;
	getline(cin,email_address) ;
	email_address += ',';

	srand(time(NULL));
    personal_code=rand();

	salary = 0;

    Employee << personal_code << national_code << salary << hashpass << gender << first_name << last_name 
			 << phone_num << date_of_birth << email_address << "\n";
    

    Employee.close();

}


void Employee::View_customer_accounts()
{
	string  card_number, account_type, expire_year, expire_month, cvv2, pin, balance;

	ifstream Accountfile("accounts.csv");
	ofstream Customer_accounts("customer_accounts.csv");

	string line;
	string  national_number;

	cout << "NATIONAL CODE : " ;
	getline(cin,national_number) ;
	national_number += ',';

	//Separating national code from list and comparing it with the national code entered by the user
	while (getline(Accountfile, line))
	{
		stringstream ss(line);

        getline(ss,national_code,',');
        national_code += ',';

		if (national_code == national_number)
		{
			Customer_accounts << line << "\n";
		}
	}
	Accountfile.close();
	Customer_accounts.close();

	system("CLS");

	ifstream customer_accounts("customer_accounts.csv");
	
	int name1 = national_number.find(',');
	national_number = national_number.substr(0, name1);

	cout << "ACCOUNTS OF USER WITH " << national_number << " NATIONAL NUMBER :" << "\n";
	cout << "=========================================================================\n";
	cout << "CARDNUMBER        ACCOUNT TUPE   EXPIRE DATE    CVV2  PIN   BALANCE\n";
	cout << "=========================================================================\n";
		
	while (getline(customer_accounts, line))
	{
		stringstream ss(line);

		getline(ss,national_code,',');
		getline(ss,card_number,',');
		getline(ss,account_type,',');
		getline(ss,expire_year,',');
		getline(ss,expire_month,',');
		getline(ss,cvv2,',');
		getline(ss,pin,',');
		getline(ss,balance,',');

		cout << left << setw(18) << card_number << left << setw(15) << account_type << left << setw(2) << expire_year << "/" << left << setw(12) << expire_month << left << setw(6)
			 << cvv2 << left << setw(6) << pin  << balance << endl;
	}

}


void Employee::Transaction(string sender_account, string reciver_accout, int ccv2, string expire_date, long amount)
{
	
}


void Employee::View_request()
{
	string amount, return_amount, loan_code , date , state ;

	ifstream Requestfilein("request_loans.csv");
	ofstream Loanfileout("loans.csv", ios::app);

	string line;

	cout << "REQUEST LOAN LIST:" << "\n";
	cout << "=======================================================================\n";
	cout << "NATIONAL CODE    LOAN CODE      AMOUNT        RETURN AMOUNT     DATE   \n";
	cout << "========================================================================\n";
	

	while (getline(Requestfilein, line))
	{
		stringstream ss(line);

		getline(ss,national_code,',');
		getline(ss,loan_code,',');
		getline(ss,amount,',');
		getline(ss,return_amount,',');
		getline(ss,date,',');

		cout << left << setw(17) << national_code << left << setw(15) << loan_code << left << setw(14) << amount << left << setw(16) 
			 << return_amount << left << setw(10) << date << endl;
	
	}

	Requestfilein.close();

	ifstream RequestfileIn("request_loans.csv");
	ofstream RequestfileOut("temp.csv" );

	string loan_number;
	cout << "\n" << "choose a loan : ";
	getline(cin,loan_number) ;

	while (getline(RequestfileIn, line))
	{
		stringstream ss(line);

		getline(ss,national_code,',');
		getline(ss,loan_code,',');
		getline(ss,amount,',');
		getline(ss,return_amount,',');
		getline(ss,date,',');

		if( loan_code == loan_number )
		{
			Loanfileout << line;
			cout << "\n\nThe loan with " << loan_code << " loan code accepted succesfuly\n";

			break;
		}
		else
		{
			RequestfileOut << line << "\n";
		}
	}

	Loanfileout.close();
	RequestfileIn.close();
	RequestfileOut.close();
	remove("request_loans.csv");
	rename("temp.csv","request_loans.csv");
}


class EmployeeList : public Employee
{
	public:
		void View_customer_list();
		void View_account_list();
		void Search_customer_list();
		void Search_account_list();
};


void EmployeeList::View_customer_list()
{
	ifstream customerfile("customers.csv", ios::app);
	string line;

	cout << "customer LIST:" << "\n";
	cout << "==================================================================================================================\n";
	cout << "NATIONAL CODE    PASSWORD      FIRT NAME      LAST NAME     PHONE NUMBER    DATE OF BIRTH  EMAIL ADDRESS   \n";
	cout << "==================================================================================================================\n";
		
	while (getline(customerfile, line))
	{
		stringstream ss(line);

		getline(ss,national_code,',');
		getline(ss,password,',');
		getline(ss,first_name,',');
		getline(ss,last_name,',');
		getline(ss,phone_num,',');
		getline(ss,date_of_birth,',');
		getline(ss,email_address,',');

		cout << left << setw(17) << national_code << left << setw(14) << password << left << setw(15) << first_name << left << setw(14) 
			 << last_name << left << setw(16) << phone_num << left << setw(15) << date_of_birth << left << setw(18) << email_address << endl;
	}

	customerfile.close();
}


void EmployeeList::View_account_list()
{
	string  card_number, account_type, expire_year, expire_month, cvv2, pin, balance;

	ifstream accountfile("accounts.csv", ios::app);
	string line;

	cout << "ACCOUNT LIST:" << "\n";
	cout << "========================================================================================\n";
	cout << "NATIONAL CODE    CARDNUMBER        ACCOUNT TUPE   EXPIRE DATE    CVV2  PIN   BALANCE\n";
	cout << "========================================================================================\n";
		
	while (getline(accountfile, line))
	{
		stringstream ss(line);

		getline(ss,national_code,',');
		getline(ss,card_number,',');
		getline(ss,account_type,',');
		getline(ss,expire_year,',');
		getline(ss,expire_month,',');
		getline(ss,cvv2,',');
		getline(ss,pin,',');
		getline(ss,balance,',');

		cout << left << setw(17) << national_code << left << setw(18) << card_number << left << setw(15) << account_type << left << setw(2) << expire_year << "/" << left << setw(12) << expire_month << left << setw(6)
			 << cvv2 << left << setw(6) << pin  << balance << endl;
	}

	accountfile.close();
}


void EmployeeList::Search_customer_list()
{
	ifstream Customerfile("customers.csv");

	string line;
	string  national_number;

	cout << "NATIONAL CODE : " ;
	getline(cin,national_number) ;

	system("CLS");

	while (getline(Customerfile, line))
	{
		stringstream ss(line);

        getline(ss,national_code,',');

		if (national_code == national_number)
		{
			cout<< "NATIONAL NUMBER : " << national_number << "\n";

			getline(ss,password,',');
			getline(ss,first_name,',');
			getline(ss,last_name,',');
			getline(ss,phone_num,',');
			getline(ss,date_of_birth,',');
			getline(ss,email_address,',');

			cout<< "PASSWORD : " << password << "\nFIRST NAME :" << first_name << "\nLAST NAME : " << last_name 
				<< "\nPHONE NUMBER :" << phone_num << "\nDATE OF BIRTH :" << date_of_birth << "\nEMAIL ADDRESS :" << email_address << "\n";

			break;
		}
	}
	Customerfile.close();
}


void EmployeeList::Search_account_list()
{
	string  card_number, account_type, expire_year, expire_month, cvv2, pin, balance;

	ifstream Accountfile("accounts.csv");

	string line;
	string  national_number;

	cout << "NATIONAL CODE : " ;
	getline(cin,national_number) ;

	system("CLS");

	while (getline(Accountfile, line))
	{
		stringstream ss(line);

        getline(ss,national_code,',');

		if (national_code == national_number)
		{
			cout<< "NATIONAL NUMBER : " << national_number << "\n";

			getline(ss,card_number,',') ;
			getline(ss,account_type,',');
			getline(ss,expire_year,',');
			getline(ss,expire_month,',');
			getline(ss,cvv2,',');
			getline(ss,pin,',');
			getline(ss,balance,',');

			cout<< "CARD NUMBER : " << card_number  << "\nACCOUNT TYPE : " << account_type << "\nEXPIRE DATE :" << expire_year << "/" <<  expire_month
				<< "\nCVV2 : " << cvv2 << "\nPIN :" << pin << "\nBALANCE :" << balance << "\n";

			break;
		}
	}
	Accountfile.close();

}

#endif