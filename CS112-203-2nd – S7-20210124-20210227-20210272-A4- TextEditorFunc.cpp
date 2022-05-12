// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: CS112-203-2nd – S7 -20210124-20210227-20210272-A4- TextEditorFunc.cpp
// Last Modification Date: 12/5/2022
// Author1 and ID and Group: Hossam Ahmed Fouad 20210124
// Author2 and ID and Group: Abdelrahman Atef   20210227
// Author3 and ID and Group: Omar Mohamed 	    20210272
// Teaching Assistant: Eng. Abdelrahman
// Purpose:Perform Text Edit On txt files
#include <bits/stdc++.h>
using namespace std;
void AddText(string fileName);
void DisplayContent(string fileName);
void EmptyTheFile(string fileName);
void EncryptFile(string fileName);
void DecryptFile(string fileName);
string RailFenceEncryption(string& text);
string RailFenceDecryption(string& text);
vector<string>DataReader(string& line);

void merge(string &file);
void numbersOfWords(string &file);
void numberOfChar(string &file);
void numberOfLines(string &file);
void searchForWord(string &file);
void menu();

int main(){

    bool exit= false;
    string file;
    int num;
    cout<<"Enter name of file:";
    cin>>file;
    cout<<endl;
    file+=".txt";
    fstream myfile;
    myfile.open(file);
    if(myfile){
        cout<<"This File Already Exist"<<endl;
        myfile.open(file,ios::in|ios::out);
    } else{
        ofstream myfile(file);
    }
    while (!exit){
        menu();
        cin>>num;
        if(num==1){
            AddText(file);
        }else if(num==2){
            DisplayContent(file);
        }else if(num==3){
            EmptyTheFile(file);
        }else if(num==4){
            EncryptFile(file);
        }else if(num==5){
            DecryptFile(file);
        }else if(num==6){
            merge(file);
        }
        else if(num==7){
            numbersOfWords(file);
        }
        else if(num==8){
            numberOfChar(file);
        }
        else if(num==9){
            numberOfLines(file);
        }
        else if(num==10){
            searchForWord(file);
        }
        else if(num==16){
            exit= true;
        }
    }
    return 0;
}
/*
word reader
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
        if(result.size()>0){
            words.push_back(result);
        }
        result.clear();
        i++;
    }
    return words;
}
/*
Data Reader
*/
vector<string>DataReader(string& line){
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

/*
functions
*/
void AddText(string fileName) {
    fstream file;
    file.open(fileName, ios::app);
    string text{};
    while (getline(cin,text,'\r')){
        text.erase(0,1);
        if(text[text.size()-1]=='\n'){
            text.pop_back();
        }
        file<<text;
        if (!getline(cin, text)) {
            cin.clear();
            break;
        }
    }
    file.close();

}
void DisplayContent(string fileName){
    fstream file;
    file.open(fileName,ios::in);
    string line{};
    while (getline(file,line)){
        cout<<line<<endl;
    }
    file.close();
}

void EmptyTheFile(string fileName){
    fstream file;
    file.open(fileName,ios::out);
    file<<"";
    file.close();
}
string RailFenceEncryption(string& text){
    string result{};
    int key = 3;
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
string RailFenceDecryption(string& text) {
    int key = 3;
    vector<vector<char>>matrix(key,vector<char>(text.size(),0));
    vector<vector<char>>v_rows;
    vector<char>v_row;
    string result = "";
    bool skip_one_turn;
    bool skip_two_turn;
    if(key > text.length()){
        result = text;
        return result;
    } else {
        int factor{0};
        factor = key > 2 ? 2 * key - 3 : 1;
        int skip1{0}, skip2{0}, start{0}, fixed_start{0}, counter{0};
        for (int row = 1; row <= key; row++) {
            v_row.clear();
            skip_one_turn = true;
            skip_two_turn = false;
            skip1 = key > 2 ? factor - 2 * (row < key ? row - 1 : 0) : 1;
            skip2 = ((key > 2) && (skip1 < factor)) ? (factor - 1 - skip1) : 0;
            fixed_start = row - 1;
            v_row.push_back(text[start]);
            matrix[row-1][fixed_start] = text[start];
            counter = 0;
            while (fixed_start < text.length()) {
                if ((fixed_start + skip1 + 1) < text.length() && skip_one_turn) {
                    counter++;
                    fixed_start += skip1 + 1;
                    matrix[row-1][fixed_start] = text[start+counter];
                    if (skip2 != 0) {
                        skip_one_turn = !skip_one_turn;
                    }
                    skip_two_turn = !skip_two_turn;
                } else if ((fixed_start + skip2 + 1) < text.length() && skip2 != 0 && skip_two_turn) {
                    counter++;
                    fixed_start += skip2 + 1;
                    matrix[row-1][fixed_start]= text[start+counter];
                    skip_one_turn = !skip_one_turn;
                    skip_two_turn = !skip_two_turn;
                } else {
                    for(int i =start+1;i<=start+counter;i++){
                        v_row.push_back(text[i]);
                    }
                    v_rows.push_back(v_row);
                    start += counter + 1;
                    break;
                }
            }
        }
        int x_begin = 0;
        int y_begin = 0;
        int x_speed = 1;
        int y_speed = 1;
        while (x_begin<matrix[y_begin].size()){
            result += matrix[y_begin][x_begin];
            if(y_begin + y_speed > matrix.size()-1){
                y_speed *= -1;
            }
            if(y_begin + y_speed < 0){
                y_speed *=-1;
            }
            y_begin+=y_speed;
            x_begin+=x_speed;
        }

        return result;
    }

}

void EncryptFile(string fileName){
    fstream file;
    file.open(fileName,ios::in);
    string line{};
    vector<vector<string>>data{};
    while (getline(file,line)){
        data.push_back(DataReader(line));
    }
    file.close();
    file.open(fileName, ios::out);
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j <data[i].size() ; ++j) {
            file<<RailFenceEncryption(data[i][j]);
        }
        file<<endl;
    }
    file.close();
}

void DecryptFile(string fileName){
    fstream file;
    file.open(fileName,ios::in);
    string line{};
    vector<vector<string>>data{};
    while (getline(file,line)){
        data.push_back(DataReader(line));
    }
    file.close();
    file.open(fileName, ios::out);
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j <data[i].size() ; ++j) {
            file<<RailFenceDecryption(data[i][j]);
        }
        file<<endl;
    }
    file.close();
}

void merge(string &file){
    string anotherFile;
    string currentLine{};
    vector<string> words{};
    cout<<"name of another file:";
    cin>>anotherFile;
    anotherFile+=".txt";
    fstream myfile2,myfile;
    myfile2.open(anotherFile,ios::in);
    myfile.open(file, ios::app);
    if(myfile2){
        while(getline(myfile2,currentLine)){
            words=WordReader(currentLine);
            myfile<<" ";
            for (int i=0;i<words.size();i++) {
                myfile<<words[i];
                myfile<<" ";
            }
        }
    } else{
        cout<<"invalid file name"<<endl;
    }
}

void numbersOfWords(string &file){
    int wordSize{0};
    string currentLine{};
    vector<string> words{};
    fstream myfile;
    myfile.open(file,ios::in);
    while (getline(myfile,currentLine)){
        words= WordReader(currentLine);
        wordSize+=words.size();
    }
    cout<<wordSize<<endl;
}

void numberOfChar(string &file){
    int charSize{0};
    string currentLine{};
    vector<string> words{};
    fstream myfile;
    myfile.open(file,ios::in);
    while (getline(myfile,currentLine)){
        words= WordReader(currentLine);
        if(words.size()>0){
            charSize+=currentLine.size();
        }
    }
    cout<<charSize<<endl;
}

void numberOfLines(string &file){
    int lineSize{0};
    string currentLine{};
    vector<string> words{};
    fstream myfile;
    myfile.open(file,ios::in);
    while (getline(myfile,currentLine)){
        words= WordReader(currentLine);
        if(words.size()>0){
            lineSize+=1;
        }

    }
    cout<<lineSize<<endl;
}

void searchForWord(string &file){
    bool found= false;
    string word;
    cout<<"enter a word:";
    cin>>word;
    transform(word.begin(),word.end(),word.begin(),::tolower);
    string currentLine{};
    vector<string> words{};
    fstream myfile;
    myfile.open(file,ios::in);
    while (getline(myfile,currentLine)) {
        words = WordReader(currentLine);
        for(int i=0;i<words.size();i++){
            transform(words[i].begin(),words[i].end(),words[i].begin(),::tolower);
            if(words[i]==word){
                found= true;
            }
        }
    }
    if(found){
        cout<<"Word was found in the file"<<endl;
    } else{
        cout<<"Word was not found in the file"<<endl;
    }

}
void menu(){
    cout<<"1.Add new text to the end of the file"<<endl;
    cout<<"2.Display the content of the file"<<endl;
    cout<<"3.Empty the file"<<endl;
    cout<<"4.Encrypt the file content"<<endl;
    cout<<"5.Decrypt the file content"<<endl;
    cout<<"6.Merge another file"<<endl;
    cout<<"7.Count the number of words in the file"<<endl;
    cout<<"8.Count the number of characters in the file"<<endl;
    cout<<"9.Count the number of lines in the file"<<endl;
    cout<<"10.Search for a word in the file"<<endl;
    cout<<"11.Count the number of times a word exists in the file"<<endl;
    cout<<"12.Turn the file content to upper case"<<endl;
    cout<<"13.Turn the file content to lower case"<<endl;
    cout<<"14.Turn file content to 1st caps (1st char of each word is capital)"<<endl;
    cout<<"15.Save"<<endl;
    cout<<"16.Exit"<<endl;
}
