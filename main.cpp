//to do:빈페이지를 읽었을 때 error가 나지않게 하기 - done
//to do:추가할 때 취소 기능 만들기 - done
//to do:찾는 항목명이 없을 때 재입력 시키기 - done
//to do:예산 초과했을 경우 환입 처리

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <map>
#include <iterator>
#include <list>

using namespace std;

bool ERROR_UNOCCURED = true;
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
    ~Subject() {};
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
    bool exist(string con){
        for(map <string, int>::iterator it = content.begin(); it != content.end(); it++)
            if(con == it->first)
                return true;
        return false;
    }
    int exceed(int price){
        if(this->total() + price > budget)
            return this->total() + price - budget;
        else
            return 0;
    }
    void add(string con, int pri){
        content[con] = pri;
    }
    int del(string str){
        try{
            for(map <string, int>::iterator it = content.begin(); it != content.end(); it++)
                if(str == it->first){
                    content.erase(it);
                    return 0;
                }
            throw str;
        }catch(string str){
            return 1;   //일치하는 내용 없음
        }
    }
    int total(){
        int total = 0;
        for(map <string, int>::iterator it = content.begin(); it != content.end(); it++)
            total += it->second;
        return total;
    }
    int left(){   //잔액
        return budget - this->total();
    }
    void ret(){   //환입
        returnedOrNot = 'Y';
        content["환입"] = this->left();
    }
    void print(){
        cout << name << endl;
        cout << "환입: "<< returnedOrNot << " 예산: " << budget << " " << endl;
        cout << "내역: ";
        for(map <string, int>::iterator it = content.begin(); it != content.end(); it++)
            cout << it->first << " " << it->second << " ";
        cout << endl;
        cout << "합계: " << this->total() << " 잔액: ";
        if(this->exceed(0))
            cout << "+" << this->exceed(0) << "(초과)" << endl;
        else
            cout << this->left() << endl;
        cout << endl;
    }
};

typedef Subject sub;
typedef list <sub> subs;

void errorOccured(){
    ERROR_UNOCCURED = false;
}

void printErrorMessage(int errorCode){
    cout << "오류가 발생했습니다. 오류코드: " << errorCode << endl;
    switch(errorCode){
    case 1:
        //cout << "(주의)추가/삭제/환입을 하면 데이터가 삭제될 수 있습니다" << endl;
        break;
    default:
        break;
    }
    cout << endl;
    cout << "--- AS: +(82)10-4305-0252 연중무휴 ---" << endl;
    cout << endl;
    return;
}

subs readSubjects(){
    subs subjects;
    ifstream fp("db.txt");
    string name, str, str_;
    char returnedOrNot;
    int budget;

    while(!fp.eof()){
        getline(fp, name, ' ');
        if(name.length() == 0)
            break;
        getline(fp, str, ' ');
        returnedOrNot = str[0];
        getline(fp, str, ' ');
        try {
            budget = stoi(str);
        }catch(exception E){
            errorOccured();
            printErrorMessage(1);
            fp.close();
            subs emptySubjects;
            return emptySubjects;
        }
        Subject subject(name, returnedOrNot, budget);
        do{
            getline(fp, str, ' ');
            if(str == "\\")
                break;
            getline(fp, str_, ' ');
            try{
                subject.add(str, stoi(str_));
            }catch(exception E){
                errorOccured();
                printErrorMessage(1);
                fp.close();
                subs emptySubjects;
                return emptySubjects;
            }
        }while(true);
        //subject.print();
        subjects.push_back(subject);
    }
    fp.close();
    return subjects;
}

int writeSubjects(subs subjects){
    ofstream ofp("db.txt");

    list <sub>::iterator it = subjects.begin();
    while(it != subjects.end()){
        ofp << it->_name() << " " << it->_returnedOrNot() << " " << it->_budget() << " ";
        con content = it->_content();
        for(map <string, int>::iterator it_ = content.begin(); it_ != content.end(); it_++)
            ofp << it_->first << " " << it_->second << " ";
        ofp << "\\";
        if(++it == subjects.end())
            continue;
        ofp << " ";
    }
    ofp.close();
    return 0;
}

int backup(subs subjects){
    ofstream ofp("backup.txt");

    list <sub>::iterator it = subjects.begin();
    while(it != subjects.end()){
        ofp << it->_name() << " " << it->_returnedOrNot() << " " << it->_budget() << " ";
        con content = it->_content();
        for(map <string, int>::iterator it_ = content.begin(); it_ != content.end(); it_++)
            ofp << it_->first << " " << it_->second << " ";
        ofp << "\\";
        if(++it == subjects.end())
            continue;
        ofp << " ";
    }
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

bool exist(string name){
    subs subjects = readSubjects();
    for(list <sub>::iterator it = subjects.begin(); it != subjects.end(); it++)
        if(it->_name() == name)
            return true;
    return false;
}

int addSubject(){   //항목X -> 예산
    subs subjects = readSubjects();
    string name, str;
    int budget;

    if(!ERROR_UNOCCURED)
        return -1;
    do{
        cout << "예산/취소: ";
        getline(cin, name);   //to do:항목명 입력시 뛰어쓰기 못하게 하기 - done
        cout << endl;
        if(name.find(' ') != string::npos){
            cout << "뛰어쓰기 없이 입력하세요" << endl;
            cout << endl;
            continue;
        }
        if(name == "취소")
            break;
        if(exist(name)){
            cout << name << " 이(가) 이미 있습니다. 다른 이름을 입력하세요" << endl;
            cout << endl;
            continue;
        }
        do{
            cout << "금액/취소: ";
            getline(cin, str);   //to do:예산 입력시 숫자외 못하게 하기 - done
            cout << endl;
            if(str.find(' ') != string::npos){
                cout << "뛰어쓰기 없이 입력하세요" << endl;
                cout << endl;
                continue;
            }
            if(str == "취소")
                break;
            try{
                budget = stoi(str);
            }catch(exception E){
                cout << "숫자 혹은 취소를 입력하세요" << endl;
                cout << endl;
                continue;
            }
            Subject subject(name, 'N', budget);
            subjects.push_back(subject);
            writeSubjects(subjects);
            if(ERROR_UNOCCURED)
                backup(subjects);
            break;
        }while(true);
        break;
    }while(true);
    return 0;
}

int addContent(){   //내용X -> 지출
    list <sub> subjects = readSubjects();
    string name, content, str;
    int price;

    if(!ERROR_UNOCCURED)
        return -1;
    do{
        for(list <sub>::iterator it = subjects.begin(); it != subjects.end(); it++)
            cout << it->_name() << endl;
        cout << "취소" << endl;
        cout << endl;
        cout << "예산: ";
        getline(cin, name);
        cout << endl;
        if(name == "취소")
            break;
        list <sub>::iterator it = subjects.begin();
        do{
            if(name == it->_name()){
                cout << "지출/취소: ";
                getline(cin, content);   //to do:내용 입력시 뛰어쓰기 못하게 하기 - done
                cout << endl;
                if(content.find(' ') != string::npos){
                    cout << "뛰어쓰기 없이 입력하세요" << endl;
                    cout << endl;
                    continue;
                }
                if(content == "취소")
                    break;
                if(it->exist(content)){
                    cout << content << " 이(가) 이미 있습니다. 다른 이름을 입력하세요" << endl;
                    cout << endl;
                    continue;
                }
                do{
                    cout << "금액/취소: ";
                    getline(cin, str);   //to do:예산 입력시 숫자외 못하게 하기 - done
                    cout << endl;
                    if(str == "취소")
                        break;
                    try{
                        price = stoi(str);
                    }catch(exception E){
                        cout << "숫자 혹은 취소를 입력하세요" << endl;
                        cout << endl;
                        continue;
                    }
                    if(it->exceed(price)){
                        do{
                            cout << "예산을 " << it->exceed(price) << "원 초과합니다. 추가하시겠습니까?" << endl;
                            cout << "예 아니오" << endl;
                            getline(cin, str);
                            cout << endl;
                            if(str == "예"){
                                it->add(content, price);
                                break;
                            }else if(str == "아니오")
                                break;
                        }while(true);
                    }else
                        it->add(content, price);
                    writeSubjects(subjects);
                    if(ERROR_UNOCCURED)
                        backup(subjects);
                    break;
                }while(true);
                break;
            }
            it++;
        }while(it != subjects.end());
        if(it != subjects.end())
            break;
    }while(true);
    return 0;
}

int add(){
    string whatToAdd;

    do{
        cout << "무엇을 추가하시겠습니까?" << endl;
        cout << "예산 지출 취소" << endl;
        try{
            getline(cin, whatToAdd);
            cout << endl;
            if(whatToAdd == "예산"){
                addSubject();
                break;
            }
            else if(whatToAdd == "지출"){
                addContent();
                break;
            }else if(whatToAdd == "취소")
                break;
            else
                throw whatToAdd;
        }catch(string whatToAdd){
            //잘못된 입력
        }
    }while(true);
    return 0;
}

int delSubject(){   //항목X -> 예산
    subs subjects = readSubjects();
    string name;

    if(!ERROR_UNOCCURED)
        return -1;
    do{
        for(list <sub>::iterator it = subjects.begin(); it != subjects.end(); it++)
            cout << it->_name() << endl;
        cout << "취소" << endl;
        cout << endl;
        cout << "예산: ";
        getline(cin, name);
        cout << endl;
        if(name == "취소")
            break;
        list <sub>::iterator it = subjects.begin();
        do{
            if(name == it->_name()){
                subjects.erase(it);

                writeSubjects(subjects);
                if(ERROR_UNOCCURED)
                    backup(subjects);
                break;
            }
            it++;
        }while(it != subjects.end());
        if(it != subjects.end())
            break;
    }while(true);
    return 0;
}

int delContent(){   //내용X -> 지출
    subs subjects = readSubjects();
    string str;
    int num, num_;

    if(!ERROR_UNOCCURED)
        return -1;
    do{
        num_ = 1;
        for(list <sub>::iterator it = subjects.begin(); it != subjects.end(); it++){
            con content = it->_content();
            for(map <string, int>::iterator it_ = content.begin(); it_!= content.end(); it_++){
            //for(map <string, int>::iterator it_ = it->_content().begin(); it_ != it->_content().end(); it_++){
                cout << num_++ << " " << it->_name() << " " << it_->first << " " << it_->second << "원" << endl;
            }
        }
        cout << endl;
        cout << "번호/취소: ";
        getline(cin, str);   //to do:번호 입력시 숫자외 못하게 하기 - done
        cout << endl;
        if(str == "취소")
            break;
        try{
            num = stoi(str);
        }catch(exception E){
            cout << "숫자 혹은 취소를 입력하세요" << endl;
            cout << endl;
            continue;
        }
        num_ = 1;
        list <sub>::iterator it = subjects.begin();
        do{
            con content = it->_content();
            map <string, int>::iterator it_ = content.begin();
            do{
                if(num == num_){
                    do{
                        cout << it->_name() << " " << it_->first << " " << it_->second << "원을 삭제하시겠습니까?" << endl;
                        cout << "예 아니오" << endl;
                        getline(cin, str);
                        cout << endl;
                        if(str == "예"){
                            it->del(it_->first);
                            writeSubjects(subjects);
                            if(ERROR_UNOCCURED)
                                backup(subjects);
                            break;
                        }else if(str == "아니오")
                            break;
                    }while(true);
                    break;
                }
                num_++;
                it_++;
            }while(it_ != content.end());
            if(it_ != content.end())
                break;
            it++;
        }while(it != subjects.end());
        if(it != subjects.end())
            break;
    }while(true);
}

int del(){
    string whatToDel;

    do{
        cout << "무엇을 삭제하시겠습니까?" << endl;
        cout << "예산 지출 취소" << endl;
        try{
            getline(cin, whatToDel);
            cout << endl;
            if(whatToDel == "예산"){
                delSubject();
                break;
            }
            else if(whatToDel == "지출"){
                delContent();
                break;
            }else if(whatToDel == "취소")
                break;
            else
                throw whatToDel;
        }catch(string whatToDel){
            //잘못된 입력
        }
    }while(true);
    return 0;
}

int ret(){
    subs subjects = readSubjects();
    string name, str, _str;

    if(!ERROR_UNOCCURED)
        return -1;
    do{
        for(list <sub>::iterator it = subjects.begin(); it != subjects.end(); it++)
            if(it->_returnedOrNot() == 'N')
                cout << it->_name() << " " << it->left() << "원" << endl;
        cout << "취소" << endl;
        cout << endl;
        cout << "예산: ";
        getline(cin, name);
        cout << endl;
        if(name == "취소")
            break;
        list <sub>::iterator it = subjects.begin();
            do{
                if(name == it->_name()){
                    if(it->_returnedOrNot() == 'Y'){
                        it = subjects.end();
                        break;
                    }
                    cout << name << " " << it->left() << "원을 환입하시겠습니까?" << endl;
                    cout << "예 아니오" << endl;
                    getline(cin, str);
                    cout << endl;
                    if(str == "예"){
                        it->ret();
                        writeSubjects(subjects);
                        if(ERROR_UNOCCURED)
                            backup(subjects);
                        break;
                    }else if(str == "아니오")
                        break;
                    else
                        continue;
                }
                it++;
            }while(it != subjects.end());
        if(it != subjects.end())
            break;
    }while(true);
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
