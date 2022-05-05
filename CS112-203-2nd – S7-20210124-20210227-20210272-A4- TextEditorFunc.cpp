// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: CS112-203-2nd – SectionNumber -YourID-YourID-YourID-A4- TextEditorFunc.cpp
// Last Modification Date: 5/5/2022
// Author1 and ID and Group: Hossam Ahmed Fouad 20210124
// Author2 and ID and Group: Abdelrahman Atef   20210227
// Author3 and ID and Group: Omar Mohamed 	    20210272
// Teaching Assistant: xxxxx xxxxx
// Purpose:Perform Text Edit On txt files
#include <bits/stdc++.h>
using namespace std;
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
    cout<<"enter name of file:";
    cin>>file;
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
        if(num==6){
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
functions
*/
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
