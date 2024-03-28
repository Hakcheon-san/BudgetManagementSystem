//to do:빈페이지를 읽었을 때 error가 나지않게 하기

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <map>
#include <iterator>
#include <list>

using namespace std;

typedef map <string, int> con;

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
    string _name(){
        return name;
    }
    char _returnedOrNot(){
        return returnedOrNot;
    }
    int _budget(){
        return budget;
    }
    con _content(){
        return content;
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
        cout << endl;
    }
};

typedef Subject sub;
typedef list <sub> subs;

subs readSubjects(){
    subs subjects;
    ifstream fp("입출금내역.txt");
    string name, str, str_;
    char returnedOrNot;
    int budget;

    while(!fp.eof()){
        getline(fp, name, ' ');
        getline(fp, str, ' ');
        returnedOrNot = str[0];
        getline(fp, str, ' ');
        budget = stoi(str);
        Subject subject(name, returnedOrNot, budget);
        do{
            getline(fp, str, ' ');
            if(str == "\\")
                break;
            getline(fp, str_, ' ');
            subject.add(str, stoi(str_));
        }while(true);
        //subject.print();
        subjects.push_back(subject);
    }
    fp.close();
    return subjects;
}

int writeSubjects(subs subjects){
    ofstream ofp("입출금내역.txt");
    list <sub>::iterator it = subjects.begin();
    do{
        ofp << it->_name() << " " << it->_returnedOrNot() << " " << it->_budget() << " ";
        con content = it->_content();
        for(map <string, int>::iterator it_ = content.begin(); it_ != content.end(); it_++)
            ofp << it_->first << " " << it_->second << " ";
        ofp << "\\";
        if(++it == subjects.end())
            continue;
        ofp << " ";
    }while(it != subjects.end());
    ofp.close();
    return 0;
}

int scanNonReturned(){
    subs subjects = readSubjects();
    for(list <sub>::iterator it = subjects.begin(); it != subjects.end(); it++)
        if(it->_returnedOrNot() == 'N')
            it->print();
    return 0;
}

int scanReturned(){
    subs subjects = readSubjects();
    for(list <sub>::iterator it = subjects.begin(); it != subjects.end(); it++)
        if(it->_returnedOrNot() == 'Y')
            it->print();
    return 0;
}

int scanAll(){
    subs subjects = readSubjects();
    for(list <sub>::iterator it = subjects.begin(); it != subjects.end(); it++)
        it->print();
    return 0;
}

int scan(){
    string subject;
    cout << "조회할 항목을 입력하세요" << endl;
    cout << "미환입 환입 전체 돌아가기" << endl;
    try{
        getline(cin, subject);
        cout << endl;
        if(subject == "미환입")
            scanNonReturned();
        else if(subject == "환입")
            scanReturned();
        else if(subject == "전체")
            scanAll();
        else if(subject == "돌아가기")
            return 1;
        else
            throw subject;
    }catch(string subject){
        //잘못된 입력
    }
    return 0;
}

int addSubject(){
    subs subjects = readSubjects();
    string name, str;
    int budget;

    cout << "항목 이름: ";
    getline(cin, name);   //to do:항목명 입력시 뛰어쓰기 못하게 하기
    cout << endl;
    cout << "예산: ";
    getline(cin, str);   //to do:예산 입력시 숫자외 못하게 하기
    cout << endl;
    budget = stoi(str);
    Subject subject(name, 'N', budget);
    subjects.push_back(subject);
    writeSubjects(subjects);
    return 0;
}

int addContent(){
    list <sub> subjects = readSubjects();
    string name, content, str;
    int price;

    for(list <sub>::iterator it = subjects.begin(); it != subjects.end(); it++)
        cout << it->_name() << endl;
    do{
        cout << "항목: ";
        getline(cin, name);
        list <sub>::iterator it = subjects.begin();
        do{
            if(name == it->_name()){
                cout << "내용: ";
                getline(cin, content);   //to do:내용 입력시 뛰어쓰기 못하게 하기
                cout << endl;
                cout << "금액: ";
                getline(cin, str);   //to do:예산 입력시 숫자외 못하게 하기
                cout << endl;
                price = stoi(str);
                it->add(content, price);
                break;
            }
            it++;
        }while(it != subjects.end());
        if(it != subjects.end())
            break;
    }while(true);
    writeSubjects(subjects);
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
                if(scan())
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
