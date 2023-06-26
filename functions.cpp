#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>
#include <stdlib.h>



using namespace std;

string Ncode="";
string Pass="";
string Gender="";
string Fname="";
string Lname="";
string Pnum="";
string Dob="";
string Eadd="";
bool checkpass;
bool checkpass2 ;



/////////////////////////////_INT_TO_STRING_/////////////////////////////////
string numberToString(int num )  
{   ostringstream os;  
    os << num;      
    return os.str(); 
}


/////////////////////_HASHING_THE_PASSWORD_////////////////////
unsigned int Hash(string & data)
{
    unsigned int result(0);

    for(unsigned int ch: data)
        result = ch + (result<<4) + (result<<10) - result;

    return result ;
}


//////////////////////_LOG_IN_///////////////////////
Login(string ncode,string pass ,string filename)
{
    checkpass = false;

    unsigned int hash_pass= Hash(pass);
    string Hashpass = numberToString(hash_pass)+',';
    string line;
    string national_code, hashpass;

	ifstream infile(filename);


    while(getline(infile,line))
    {
        stringstream ss(line);
        

        getline(ss,national_code,',');
        national_code += ',';
        getline(ss,hashpass,',');
        hashpass += ',';

        if(national_code == ncode && hashpass == Hashpass){
            checkpass = true;
            break;
        }

    }
    
    infile.close();

    return checkpass;
}
