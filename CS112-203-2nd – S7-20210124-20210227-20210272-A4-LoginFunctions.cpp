// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: CS112-203-2nd – S7-20210124-20210227-20210272-A4-LoginFunctions.cpp
// Last Modification Date: 12/5/2022
// Author1 and ID and Group: Hossam Ahmed Fouad 20210124
// Author2 and ID and Group: Abdelrahman Atef   20210227
// Author3 and ID and Group: Omar Mohamed       20210272
// Teaching Assistant: Eng. Abdelrahman
// Purpose:Creating A Full Functioning Data Base System

#include <iostream>
#include <regex>
#include <fstream>
#include <conio.h>
#include <cstdlib>

using namespace std;

bool ValidateUsername(string& username);
bool ValidatePassword(string& password);
bool ValidateEmail(string& email);
bool ValidateID(string& id);
bool ValidateMobile(string& mobile);
bool UniquePassword(string& pass, const vector<string>&data);
pair<int,bool> ValidateLogin(string& id, string& pass);
void LoadDataBase();
void TakePassword(string& holder);
vector<string>WordReader(string& line);
vector<string>DataBaseReader(string& line);
void Register();
int Login();
void ChangePassword();
string RailFenceEncryption(string& text);
struct User{

    string username{},email{},password{},id{},mobile{};
    vector<string>oldPasswords{};

};

vector<User>users{};
vector<vector<string>>dataBaseText{};

ostream& operator<<(ostream& out , vector<string>&data){
    out<<"[";
    for (string& word : data) {
        out<<word<<", ";
    }
    out<<"]";
    return out;
}

ostream& operator<<(ostream& out, vector<User>&data){
    for(User& user : data){
        out<<user.username<<" " << user.password << " " << user.id<<endl;
    }
    return out;
}

string RailFenceEncryption(string& text){
    string result{};
    int key = 4;
    bool skip_one_turn;
    bool skip_two_turn;
    if(key > text.length()){
        result = text;
        return result;
    } else {
        int factor{0};
        factor = key > 2 ? 2 * key - 3 : 1;
        int skip1{0}, skip2{0}, start{0};
        for (int row = 1; row <= key; row++) {
            skip_one_turn = true;
            skip_two_turn = false;
            skip1 =key > 2 ?  factor - 2 * (row < key ? row - 1 : 0) : 1;
            skip2 = ((key > 2) && (skip1 < factor)) ? (factor - 1 - skip1) : 0;
            result += text[row - 1];
            start = row - 1;
            while (start < text.length()){
                if ((start + skip1+1) < text.length() && skip_one_turn){
                    start += skip1+1;
                    result += text[start];
                    if(skip2!=0){
                        skip_one_turn = !skip_one_turn;
                    }
                    skip_two_turn = !skip_two_turn;
                }
                else if((start + skip2+1) < text.length() && skip2 != 0 && skip_two_turn){
                    start += skip2+1;
                    result += text[start];
                    skip_one_turn = !skip_one_turn;
                    skip_two_turn = !skip_two_turn;
                }else{
                    break;
                }
            }
        }
        return result;
    }
}
/**
 * Load Data Base Users
 */
void LoadDataBase() {
    string result;
    fstream file;
    file.open("dataBase.txt", ios::in);
    string currentLine{};
    vector<string> words{};
    vector<string>data{};
    while (getline(file, currentLine)) {
        words = WordReader(currentLine);
        if (words.size() > 0) {
            if (words[0] == "USER") {
                User newUser;
                users.push_back(newUser);
            }else{
                words = WordReader(currentLine);
                if (words[0] == "Username") {
                    for (int i = 2; i < words.size(); ++i) {
                        result += words[i];
                    }
                    users[users.size()-1].username = result;
                    result.clear();
                } else if (words[0] == "Password") {
                    for (int i = 2; i < words.size(); ++i) {
                        result += words[i];
                    }
                    users[users.size()-1].password = result;
                    result.clear();
                }else if(words[0]=="ID"){

                    for (int i = 2; i < words.size(); ++i) {
                        result += words[i];
                    }
                    users[users.size()-1].id = result;
                    result.clear();

                }else if (words[0] == "Email") {
                    for (int i = 2; i < words.size(); ++i) {
                        result += words[i];
                    }
                    users[users.size()-1].email = result;
                    result.clear();
                } else if (words[0] == "Mobile") {
                    for (int i = 2; i < words.size(); ++i) {
                        result += words[i];
                    }
                    users[users.size()-1].mobile = result;
                    result.clear();
                } else if (words[0] == "Old") {
                    for (int i = 2; i < words.size(); ++i) {
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

bool ValidateUsername(string& username){
    //Default State
    regex validUsername("[a-zA-z\\-]+");

    return regex_match(username,validUsername);
}

bool ValidatePassword(string& password){
    //Default State
    bool lower{false},upper{false},digit{false},special{false},length{false};
    length = password.size() >= 8;
    regex spec("\\W+");
    special = regex_search(password,spec);
    for (int i = 0; i <password.size() ; ++i) {
        //cout<<"char: "<<password[i]<<endl;
        if(isspace(password[i])){
            cout<<"\nInvalid password format, can't have spaces"<<endl;
            return false;
        }else if(isdigit(password[i])){
            digit= true;
        } else if(isupper(password[i])){
            upper = true;
        } else if(islower(password[i])){
            lower = true;
        }
    }
    if(lower&&upper&&digit&&special&&length){
        return true;
    } else{
        cout<<"\nPassword is weak, must contain a lower case,upper case, a digit , a special character and at least 8 characters"<<endl;
        return false;
    }
}

bool ValidateEmail(string& email){
    //Default State

    regex validEmail("[^\\.]+[\\.]?[0-9A-Za-z.]*@[0-9A-Za-z]*[A-Za-z]+[0-9]*([A-Za-z0-9]+[\\-][A-Za-z0-9]+)?\\.[a-z]+");

    return regex_match(email,validEmail);

}

bool ValidateID(string& id){
    //Default State
    regex validID("[^\\s]+");

    if(regex_match(id,validID)){
        for(User& user : users){
            if(user.id == id){
                cout<<"\nID already taken, please choose another one"<<endl;
                return false;
            }
        }
        return true;

    } else{
        cout<<"Invalid ID format, please try again"<<endl;
        return false;
    }
}

bool ValidateMobile(string& mobile){
    //Default State
    regex validMobile("(01)([0]{1}([12690]))?([0]{2})?([1]{1}([142]))?([2]{1}[0278])?([0-9]{7})");

    return regex_match(mobile,validMobile);
}

vector<string>DataBaseReader(string& line){
    vector<string>data{};
    string word{};
    int i=0;
    while (i<line.size()){
        if (!isdigit(line[i]) && !isalpha(line[i])&& !isspace(line[i])){
            word.push_back(line[i]);
            data.push_back(word);
            word.clear();
            i++;
        } else if(isspace(line[i])){
            while (isspace(line[i])){
                word.push_back(line[i]);
                i++;
            }
            data.push_back(word);
            word.clear();
        }else if(isalpha(line[i])){
            while (isalpha(line[i])) {
                word.push_back(line[i]);
                i++;
            }
            data.push_back(word);
            word.clear();
        }else if(isdigit(line[i])){
            while (isdigit(line[i])){
                word.push_back(line[i]);
                i++;
            }
            data.push_back(word);
            word.clear();
        }else{

        }
    }
    return data;
}

vector<string> WordReader(string& line){
    vector<string>words{};
    string result{};
    int i = 0;
    while (i<line.size()){
        while (!isspace(line[i]) && i<line.size()){
            result.push_back(line[i]);
            i++;
        }
        if(result.size()>0){
            words.push_back(result);
        }
        result.clear();
        i++;
    }
    return words;
}

void TakePassword(string& holder){
    holder.clear();
    char container[100];
    int i=0;
    for ( ;;++i) {
        container[i]=getch();
        if (container[i]=='\b'){
            i-=2;
            printf("\b \b");
        }else if(container[i]=='\r'){
            break;
        } else{
            cout<<"*";
        }
    }
    for (int j = 0; j < i+1 ; ++j) {
        holder.push_back(container[j]);
    }
    cout<<endl;
    holder.pop_back();
}

//Main Registration Function
void Register() {

    User newUser;
    cout << "Enter Username: ";
    getline(cin, newUser.username);


    while(!ValidateUsername(newUser.username)){

        cout << "\nInvalid Username Format, please try again" << endl;

        cout << "Enter Username: ";
        getline(cin, newUser.username);

    }
    cout<<endl;
    cout<<"Enter password: ";
    TakePassword(newUser.password);
    string passCheck{};
    cout<<"Re-enter password: ";
    TakePassword(passCheck);
    while (passCheck!=newUser.password){
        cout<<"\nRe-entered password is not identical to first password please try again"<<endl;
        cout<<"Enter password: ";
        TakePassword(newUser.password);
        cout<<"Re-enter password: ";
        TakePassword(passCheck);
    }
    while (!ValidatePassword(newUser.password)){
        cout<<"Enter password: ";
        TakePassword(newUser.password);
        cout<<"Re-enter password: ";
        TakePassword(passCheck);
        while (passCheck!=newUser.password){
            cout<<"\nRe-entered password is not identical to first password please try again"<<endl;
            cout<<"Password1: "<<newUser.password<<endl;
            cout<<"Password2: "<<passCheck<<endl;
            cout<<"Enter password: ";
            TakePassword(newUser.password);
            cout<<"Re-enter password: ";
            TakePassword(passCheck);
        }
    }

    cout << endl;
    cout << "Enter ID: ";
    getline(cin, newUser.id);

    while (!ValidateID(newUser.id)){

    cout << "Enter ID: ";

    getline(cin, newUser.id);

    }

    cout << endl;
    cout << "Enter Email: ";
    getline(cin, newUser.email);

    while (!ValidateEmail(newUser.email)){

        cout << "\nInvalid Email Format, please try again" << endl;

        cout << "Enter Email: ";
        getline(cin, newUser.email);

    }

    cout << endl;
    cout << "Enter Mobile: ";
    getline(cin, newUser.mobile);

    while (!ValidateMobile(newUser.mobile)){

        cout << "\nInvalid mobile format, please try again" << endl;
        cout << "Enter Mobile: ";
        getline(cin, newUser.mobile);

    }
    cout<<endl;
    cout<<"Registration is complete, welcome "<<newUser.username<<"!"<<endl;

    //Opening Data Base File
    fstream file;
    file.open("dataBase.txt", ios::app);

    //Registering user to data base
    newUser.password = RailFenceEncryption(newUser.password);
    users.push_back(newUser);
    cout<<endl;

    if (file.is_open()) {
        file << "USER " << users.size() << "\n";
        file << "    Username     : " << newUser.username << "\n";
        file << "    Password     : " << newUser.password << "\n";
        file << "    ID           : " << newUser.id << "\n";
        file << "    Email        : " << newUser.email << "\n";
        file << "    Mobile       : " << newUser.mobile << "\n";
        file << "    Old Passwords:";
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
pair<int,bool>ValidateLogin(string& id, string& pass) {
    bool foundID{false}, correctPass{false};
    pair<int, bool> result;
    int counter = -1;
    result.first = counter;
    for (User &user: users) {
        counter++;
        if (user.id == id) {
            foundID = true;
            cout<<user.password<<endl;
            cout<<pass<<endl;
            cout<<RailFenceEncryption(pass)<<endl;
            if (user.password == RailFenceEncryption(pass)) {
                correctPass = true;
                result.first = counter;
                result.second = foundID && correctPass;
            }
            break;
        }
    }
    return result;
}

bool UniquePassword(string& pass, const vector<string>&data){
    for(const string& d : data){
        if(d == RailFenceEncryption(pass)){
            cout<<"Already used password, choose a new one"<<endl;
            return false;
        }
    }
    return true;
}

int Login(){
    User newUser;
    int counter{0};
    cout<<"Enter ID: ";
    getline(cin,newUser.id);
    cout<<endl;
    cout<<"Enter Password: ";
    TakePassword(newUser.password);
    pair<int,bool>res = ValidateLogin(newUser.id,newUser.password);
    while (!res.second && counter<2){
        counter++;
        cout<<"\nInvalid ID or password, please try again"<<endl;
        cout<<"Enter ID: ";
        getline(cin,newUser.id);
        cout<<"Enter Password: ";
        TakePassword(newUser.password);
        res = ValidateLogin(newUser.id,newUser.password);
    }
    if (counter==2){
        cout<<"Too many trials, ACCESS DENIED"<<endl;
    }else{
        cout<<"Success! Welcome " << users[res.first].username <<endl;
    }

    return res.first;

}
/**
* Change Password
*/
void ChangePassword(){
    string passCheck{};
    int indexUser = Login();
    if(indexUser>-1) {
        users[indexUser].oldPasswords.push_back(users[indexUser].password);
        cout << "Enter new password: ";
        TakePassword(users[indexUser].password);
        while (!UniquePassword(users[indexUser].password, users[indexUser].oldPasswords)) {
            cout << "\nPassword already used, please choose a new one" << endl;
            cout << "Enter new password: ";
            TakePassword(users[indexUser].password);
        }
        cout << "Re-enter password: ";
        TakePassword(passCheck);
        cout << endl;
        while (passCheck != users[indexUser].password) {
            cout << "\nRe-entered password is not identical to first password please try again" << endl;
            cout << "Enter password: ";
            TakePassword(users[indexUser].password);
            while (!UniquePassword(users[indexUser].password, users[indexUser].oldPasswords)) {
                cout << "\nPassword already used, please choose a new one" << endl;
                cout << "Enter new password: ";
                TakePassword(users[indexUser].password);
            }
            cout << "Re-enter password: ";
            TakePassword(passCheck);
        }
        while (!ValidatePassword(users[indexUser].password)) {
            cout << "Enter new password: ";
            TakePassword(users[indexUser].password);
            cout << "Re-enter password: ";
            TakePassword(passCheck);
            while (passCheck != users[indexUser].password) {
                cout << "\nRe-entered password is not identical to first password please try again" << endl;
                cout << "Enter password: ";
                TakePassword(users[indexUser].password);
                while (!UniquePassword(users[indexUser].password, users[indexUser].oldPasswords)) {
                    cout << "\nPassword already used, please choose a new one" << endl;
                    cout << "Enter new password: ";
                    TakePassword(users[indexUser].password);
                }
                cout << "Re-enter password: ";
                TakePassword(passCheck);
            }
        }
        users[indexUser].password = RailFenceEncryption(users[indexUser].password);
        fstream file;
        file.open("dataBase.txt",ios::in);
        if(file.is_open()){
            string line{};
            vector<string>data{};
            dataBaseText.clear();
            while (getline(file,line)){
                data = DataBaseReader(line);
                dataBaseText.push_back(data);
            }
            file.close();
        }
        file.open("dataBase.txt", ios::out);
        string line{};
        vector<string> words{};
        if (file.is_open()) {
            for (int i = 0; i < dataBaseText.size(); ++i) {
                for (int j = 0; j < dataBaseText[i].size(); ++j) {
                    if (dataBaseText[i][j] == "USER") {
                        if (stoi(dataBaseText[i][j + 2]) == indexUser + 1) {
                            i += 2;
                            j += 5;
                            cout<<dataBaseText[i]<<endl;
                            cout<<dataBaseText[i][j]<<endl;
                            //string out{};
                            int remove = dataBaseText[i].size();
                            for (int x = j; x <remove; x++) {
                               cout<<dataBaseText[i]<<endl;
                               dataBaseText[i].pop_back();
                               cout<<dataBaseText[i]<<endl;
                            }
                            dataBaseText[i].push_back(users[indexUser].password);
                            i += 4;
                            dataBaseText[i].push_back(" ");
                            dataBaseText[i].push_back(users[indexUser].oldPasswords[users[indexUser].oldPasswords.size() - 1]);
                            break;
                        }
                    }
                }
            }
            for (int i = 0; i < dataBaseText.size(); ++i) {
                for (int j = 0; j < dataBaseText[i].size(); ++j) {
                    file << dataBaseText[i][j];
                }
                file << endl;
            }

            file.close();
        }

        cout << "\nPassword has successfully changed!" << endl;
    }
}


