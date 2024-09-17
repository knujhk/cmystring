#include <iostream>
#include <string.h>
#include "CMyStringEx.h"

using namespace std;

CMyStringEx::CMyStringEx()
{
    cout << "CMyStringEx 디폴트 생성자 호출" << endl;
}
CMyStringEx::~CMyStringEx()
{
    cout << "CMyStringEx 디폴트 소멸자 호출" << endl;
}
void CMyStringEx::onSetData(const char*& pParam){
    cout << "CMyStringEx::onSetData()" << endl;
    if(pParam != nullptr){
        if(strcmp(pParam,"코드몽키") == 0){
            pParam = "프로그래머";
            //어떻게 이게 되는거지? 
            //현재 함수에 대한 호출자인 setData가 문자열 리터럴을 가리키는 포인터를
            //매개변수로 받아 지역변수에 저장했고
            //현재 함수 내부에서 pParam은 그것에 대한 참조자
            //따라서 지역변수인 포인터 값을 다른 문자열리터럴에 대한 포인터 값으로
            //변경 가능
        }
    }
}
CMyStringEx& CMyStringEx::operator=(const char* pParam){
    cout << "CMyStringEx() 복사 대입 연산" << endl;
    this->setData(pParam);
    
    return *this;
}