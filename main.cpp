#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <map>
#include <iterator>

using namespace std;

class Subject{
private:
    string name;
    char returnedOrNot;
    int budget;
    map <string, int> content;
public:
    Subject();
    Subject(string name, char returnedOrNot, int budget){
        this->name = name;
        this->returnedOrNot = returnedOrNot;
        this->budget = budget;
    }
    //~Subject();
    void add(string con, int pri){
        content[con] = pri;
    }
    int total(){
        int total = 0;
        for(map <string, int>::iterator it = content.begin(); it != content.end(); it++)
            total += it->second;
        return total;
    }
    int left(){   //잔액
        return this->budget - this->total();
    }
    void print(){
        cout << name << " " << returnedOrNot << " " << budget << " ";
        for(map <string, int>::iterator it = content.begin(); it != content.end(); it++)
            cout << it->first << " " << it->second << " ";
        cout << this->total() << " " << this->left() << endl;
    }
};

int scanNonReturned(){
    ifstream fp("입출금내역.txt");
    string name, str, str_;
    char returnedOrNot;
    int budget, num;

    while(!fp.eof()){
        getline(fp, name, ' ');
        getline(fp, str, ' ');
        returnedOrNot = str[0];
        if(returnedOrNot == 'N'){
            getline(fp, str, ' ');
            budget = stoi(str);
            Subject sub(name, returnedOrNot, budget);
            do{
                getline(fp, str, ' ');
                if(str == "\\")
                    break;
                getline(fp, str_, ' ');
                sub.add(str, stoi(str_));
            }while(true);
            sub.print();
        }
    }
    fp.close();
    return 0;
}

int scanReturned(){
    ifstream fp("입출금내역.txt");
    string name, str, str_;
    char returnedOrNot;
    int budget, num;

    while(!fp.eof()){
        getline(fp, name, ' ');
        getline(fp, str, ' ');
        returnedOrNot = str[0];
        if(returnedOrNot == 'Y'){
            getline(fp, str, ' ');
            budget = stoi(str);
            Subject sub(name, returnedOrNot, budget);
            do{
                getline(fp, str, ' ');
                if(str == "\\")
                    break;
                getline(fp, str_, ' ');
                sub.add(str, stoi(str_));
            }while(true);
            sub.print();
        }
    }
    fp.close();
    return 0;
}

int scanAll(){
    ifstream fp("입출금내역.txt");
    string name, str, str_;
    char returnedOrNot;
    int budget, num;

    while(!fp.eof()){
        getline(fp, name, ' ');
        getline(fp, str, ' ');
        returnedOrNot = str[0];
        getline(fp, str, ' ');
        budget = stoi(str);
        Subject sub(name, returnedOrNot, budget);
        do{
            getline(fp, str, ' ');
            if(str == "\\")
                break;
            getline(fp, str_, ' ');
            sub.add(str, stoi(str_));
        }while(true);
        sub.print();
    }
    fp.close();
    return 0;
}

int scan(){
    string sub;
    cout << "조회할 항목을 입력하세요" << endl;
    cout << "미환입 환입 전체 돌아가기" << endl;
    try{
        getline(cin, sub);
        cout << endl;
        if(sub == "미환입")
            scanNonReturned();
        else if(sub == "환입")
            scanReturned();
        else if(sub == "전체")
            scanAll();
        else if(sub == "돌아가기")
            return 1;
        else
            throw sub;
    }catch(string sub){
        //잘못된 입력
    }
    return 0;
}

int addSubject(){
    cout << "addSubject 함수" << endl;
    return 0;
}

int addContent(){
    cout << "addContent 함수" << endl;
    return 0;
}

int add(){
    string whatToAdd;
    cout << "무엇을 추가하시겠습니까?" << endl;
    cout << "항목 내용" << endl;
    try{
        getline(cin, whatToAdd);
        cout << endl;
        if(whatToAdd == "항목")
            addSubject();
        else if(whatToAdd == "내용")
            addContent();
        else
            throw whatToAdd;
    }catch(string whatToAdd){
        //잘못된 입력
    }
    return 0;
}

int del(){
    cout << "del 함수" << endl;
    return 0;
}

int ret(){
    cout << "ret 함수" << endl;
    return 0;
}

int invalid(){
    cout << "invalid 함수" << endl;
    return 0;
}

int home(){
    string act;
    cout << "원하는 기능을 입력하세요" << endl;
    cout << "조회 추가 삭제 환입 끄기" << endl;
    try{
        getline(cin, act);
        cout << endl;
        if(act == "조회"){
            while(true)
                if(!scan())
                    break;
        }
        else if(act == "추가")
            add();
        else if(act == "삭제")
            del();
        else if(act == "환입")
            ret();
        else if(act == "끄기")
            return 1;
        else
            throw act;
    }catch(string act){
        //잘못된 입력
    }
    return 0;
}

int main() {
    while(true){
        if(home())
            break;
    }
    return 0;
}
