#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <map>

using namespace std;

class Subject{
private:
    char returnedOrNot;
    int budget;
    map <string, int> content;
public:
    Subject();
    ~Subject();
};

int scanNonReturned(){
    ifstream fp("입출금내역.txt");
    /*string sub, yesOrNot, str, num;
    int left, budget, total = 0, returned = 0;
    vector <string> content;
    vector <int> price;
    getline(fp, sub, ' ');   //항목 저장
    getline(fp, num, ' ');
    left = stoi(num);   //잔액 저장
    getline(fp, num, ' ');
    budget = stoi(num);   //예산 저장
    do{
        getline(fp, str, ' ');
        if(str == "Y" || str == "N")
            break;
        content.push_back(str);
        getline(fp, num, ' ');
        price.push_back(stoi(num));
        total += stoi(num);
    }while(true);
    yesOrNot = str;*/
    string sub, str;
    char returnedOrNot;
    int budget;
    getline(fp, sub, ' ');
    getline(fp, str, ' ');
    returnedOrNot = str[0];
    if(returnedOrNot == 'N'){
        getline(fp, str, ' ');
        budget = stoi(str);
        do{
            getline(fp, str, ' ');
            cout << str;
            if(str == "\\")
                break;
        }while(true);
    }


    fp.close();
    /*cout << "항목: " << sub << " 잔액: " << left << " 예산: " << budget << endl;
    for(int i = 0; i < content.size(); i++)
        cout << "내용: " << content[i] << " 가격: " <<  price[i];
    cout << endl;
    cout << "환입여부: " << yesOrNot << " 합계: " << total << " 환입금: " << returned << endl;*/
    return 0;
}

int scanReturned(){
    cout << "scanReturned 함수" << endl;
    return 0;
}

int scanAll(){
    cout << "scanAll 함수" << endl;
    return 0;
}

int scan(){
    string sub;
    cout << "조회할 항목을 입력하세요" << endl;
    cout << "미환입 환입 전체" << endl;
    try{
        getline(cin, sub);
        cout << endl;
        if(sub == "미환입")
            scanNonReturned();
        else if(sub == "환입")
            scanReturned();
        else if(sub == "전체")
            scanAll();
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
        if(act == "조회")
            scan();
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
    cout << endl;
    return 0;
}

int main() {
    while(true){
        if(home())
            break;
    }
    return 0;
}
