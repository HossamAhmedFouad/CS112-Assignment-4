// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: xxxxxx.cpp
// Last Modification Date: xx/xx/xxxx
// Author1 and ID and Group: xxxxx xxxxx
// Author2 and ID and Group: xxxxx xxxxx
// Author3 and ID and Group: xxxxx xxxxx
// Teaching Assistant: xxxxx xxxxx
// Purpose:..........

#include <bits/stdc++.h>
#include <iostream>
#include <regex>
using namespace std;

bool ValidateUsername(string username);
bool ValidatePassword(string password);
bool ValidateEmail(string email);
bool ValidateID(string id);
bool ValidateMobile(string mobile);
void LoadDataBase();
vector<string>WordReader(string& line);
void Register();
/**
*STRUCTURE
*/
struct User{

    string username{},email{},password{},id{},mobile{};
    vector<string>oldPasswords{};

};
vector<User>users{};
/**
* DEBUG
*/
ostream& operator<<(ostream& out , vector<string>&data){
    out<<"[";
    for (string& word : data) {
        out<<word<<", ";
    }
    out<<"]";
    return out;
}

ostream& operator<<(ostream& out, vector<User>&data){
    for(User user : data){
        out<<user.username<<" " << user.password << " " << user.id<<endl;
    }
    return out;
}

int main(){

    //Test Your Code Here
 
    return 0;
}
/**
 * Load Data Base Users
 */
void LoadDataBase() {
    string result;
    bool read;
    fstream file;
    file.open("dataBase.txt", ios::in);
    string currentLine{};
    vector<string> words{};
    while (getline(file, currentLine)) {
        words = WordReader(currentLine);
        cout<<words<<endl;
        if (words.size() > 0) {
            if (words[0] == "USER") {
                User newUser;
                users.push_back(newUser);
            }else{
                words = WordReader(currentLine);
                if (words[0] == "Username") {
                    for (int i = 1; i < words.size(); ++i) {
                        result += words[i];
                    }
                    users[users.size()-1].username = result;
                    result.clear();
                } else if (words[0] == "Password") {
                    for (int i = 1; i < words.size(); ++i) {
                        result += words[i];
                    }
                    users[users.size()-1].password = result;
                    result.clear();
                } else if (words[0] == "Email") {
                    for (int i = 1; i < words.size(); ++i) {
                        result += words[i];
                    }
                    users[users.size()-1].email = result;
                    result.clear();
                } else if (words[0] == "Mobile") {
                    for (int i = 1; i < words.size(); ++i) {
                        result += words[i];
                    }
                    users[users.size()-1].mobile = result;
                    result.clear();
                } else if (words[0] == "Old") {
                    for (int i = 1; i < words.size(); ++i) {
                        users[users.size()-1].oldPasswords.push_back(words[i]);
                    }
                }

            }
        }
    }
    file.close();
}

/**
* User Registeration
*/

//Validation Functions

bool ValidateUsername(string username){
    //Default State
    bool correct = false;
    
 
 
 
    return correct;
}

bool ValidatePassword(string password){
    //Default State
    bool correct = false;
    
 
 
 
    return correct;
}

bool ValidateEmail(string email){
    //Default State
    bool correct = false;
    
 
 
 
    return correct;
}

bool ValidateID(string id){
    //Default State
    bool correct = false;
    
 
 
    return correct;
}

bool ValidateMobile(string mobile){
    //Default State
    bool correct = false;
    
 
 
    return correct;
}

/**
*Read From Data Base File Word By Word
*/
vector<string> WordReader(string& line){
    vector<string>words{};
    string result{};
    int i = 0;
    while (i<line.size()){
        while (!isspace(line[i]) && i<line.size()){
            result.push_back(line[i]);
            i++;
        }
        if(result.size()>1){
            words.push_back(result);
        }
        result.clear();
        i++;
    }
    return words;
}

//Main Registration Function

void Register() {

    User newUser;
    cout << "Enter Username: ";
    getline(cin, newUser.username);


//    while(!ValidateUsername(newUser.name)){

    cout << "Error Message <--Modify It" << endl;

    cout << "Enter Username: ";
    getline(cin, newUser.username);

//    }

    cout << endl;
    cout << "Enter Password: ";
    getline(cin, newUser.password);

//    while (!ValidatePassword(newUser.password)){

    cout << "Error Message <-- Modify It" << endl;

    cout << "Enter Password: ";
    getline(cin, newUser.password);

//    }

    cout << endl;
    cout << "Enter ID: ";
    getline(cin, newUser.id);

//    while (!ValidateID(newUser.id)){

    cout << "Error Message <-- Modify It" << endl;

    cout << "Enter ID: ";

    getline(cin, newUser.id);

//    }

    cout << endl;
    cout << "Enter Email: ";
    getline(cin, newUser.email);

//    while (!ValidateEmail(newUser.email)){

    cout << "Error Message <-- Modify It" << endl;

    cout << "Enter Email: ";
    getline(cin, newUser.email);

    //   }

    cout << endl;
    cout << "Enter Mobile: ";
    getline(cin, newUser.mobile);

//    while (!ValidateMobile(newUser.mobile)){

    cout << "Error Message <-- Modify It" << endl;

    cout << "Enter Mobile: ";
    getline(cin, newUser.mobile);

//    }

    //Opening Data Base File
    fstream file;
    file.open("dataBase.txt", ios::app);

    //Registering user to data base
    users.push_back(newUser);
    cout<<endl;
    cout<<users.size()<<endl;
    if (file.is_open()) {
        file << "USER " << users.size() << ":" << "\n";
        file << "    Username     : " << newUser.username << "\n";
        file << "    Password     : " << newUser.password << "\n";
        file << "    ID           : " << newUser.id << "\n";
        file << "    Email        : " << newUser.email << "\n";
        file << "    Mobile       : " << newUser.mobile << "\n";
        file << "    Old Passwords: ";
        for (int i = 0; i <newUser.oldPasswords.size(); ++i) {
            //ADD ENCRYPTION HERE
            file<<newUser.oldPasswords[i]<<" ";
        }
        file<<endl;
        file<<endl;
        file.close();
    }
}

/**
* User Login
*/


/**
* Change Password
*/



