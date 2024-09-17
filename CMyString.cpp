#include <iostream>
#include <string.h>
#include "CMyString.h"

using namespace std;

CMyString::CMyString(){ 
    cout << "CMyString() 디폴트 생성자 호출" << endl;
}
CMyString::CMyString(char const* pParam) {
    cout << "CMyString() 변환 생성자 호출" << endl;
    this->setData(pParam);
}
CMyString::CMyString(const CMyString& rhs){
    cout << "CMyString() 복사 생성자 호출" << endl;
    this->setData(rhs.getData());     
}
CMyString::CMyString(CMyString&& rhs) noexcept{
    cout << "CMyString() 이동 생성자 호출" << endl;
    this->m_pszData = rhs.m_pszData;
    this->length = rhs.length;
    rhs.m_pszData = nullptr;
    //rhs가 갖고있던 문자열 길이 정보도 옮겨와야 함.
}
CMyString& CMyString::operator=(const CMyString& rhs){
    cout << "CMyString() 복사 대입 연산" << endl;
    this->setData(rhs.getData());

    return *this;
}
CMyString& CMyString::operator=(const char* pParam){
    cout << "CMyString() 복사 대입 연산" << endl;
    this->setData(pParam);
    
    return *this;
}
CMyString& CMyString::operator=(CMyString&& rhs) noexcept{
    cout << "CMyString() 이동 대입 연산" << endl;
    delete[] this->m_pszData;

    this->m_pszData = rhs.m_pszData;
    this->length = rhs.length;

    rhs.m_pszData = nullptr;

    return *this;
}
size_t CMyString::append(const char* pParam){
    
    //고려사항1: 매개변수로 넘어온 게 널이면?
    if(pParam == nullptr){
        return 0;
    }
    //고려사항2: 호출자가 갖고있는 포인터가 널이면?
    if(this->m_pszData == nullptr){
        this->setData(pParam);
        return this->length;
    }
    
    size_t lenAppend = strlen(pParam);

    char* newString = new char[this->length + lenAppend + 1];
    strcpy(newString,this->m_pszData);
    strcat(newString + (this->length), pParam);

    delete[] this->m_pszData;
    this->m_pszData = newString;
    this->length += lenAppend;

    return this->length;   //반환값이 0이냐 아니냐로 함수 성공여부 따짐
}  
// CMyString CMyString::operator+(const CMyString& rhs) {
//     cout << "CMyString() 덧셈 연산자 오버로딩" << endl;
//     CMyString ret;
//     size_t length(this->getLength() + rhs.getLength());
//     ret.m_pszData = new char[length+1];
//     char* to = ret.m_pszData;
//     char* from = this->m_pszData;
//     while(*to = *from){
//         to++;
//         from++;
//     }
//     from = rhs.m_pszData;
//     while(*to = *from){
//         to++;
//         from++;
//     }
//     return ret;
// } append 메서드가 있다면 위 코드를 사용하지 않아도 됨
char& CMyString::operator[](int index){
    // if((index < 0) || (index >= this->length))
    //     return 0;//인덱싱을 잘못 한 경우 아무일도 일어나지 않게 하려고함
    //             //예외 처리를 해야하나?
    //             
    return (this->m_pszData)[index];
}
char CMyString::operator[](int index) const{
    if((index < 0) || (index >= this->length))
        return 0;
    if(this->m_pszData != nullptr)
        return (this->m_pszData)[index];;
    
    return 0;
}
CMyString CMyString::operator+(const CMyString& rhs){
    CMyString result(this->getData());
    result.append(rhs.m_pszData);

    return result;
}
CMyString CMyString::operator+(char const* pParam){
    CMyString result(this->getData());
    result.append(pParam);

    return result;
}
CMyString& CMyString::operator+=(char const* pParm){
    cout << "+= 연산자 함수 호출" << endl;
    this->append(pParm);
    return *this;
}
CMyString::~CMyString() { 
    cout << "~CMyString() 소멸자 호출" << endl;
    delete[] m_pszData;
}
CMyString::operator const char*() const{
    //const char* 타입과의 호환성을 위한 형변환 연산자 오버로딩
    cout << "CMyString() const char* 로 형변환" << endl;
    return m_pszData;
}
const char* CMyString::getData() const{
    return m_pszData;
} 
size_t CMyString::getLength() const {
    return this->length;
}
void CMyString::onSetData(const char*& pParam){
}
void CMyString::setData(const char* pParam){  

    //pParam이라는 포인터가 지역변수에 저장
    onSetData(pParam);

    if(m_pszData != nullptr)
        delete[] m_pszData; 

    size_t length = strlen(pParam);
    this->length = length;
    //또는 length = strlen(pParam); 한 줄로도 가능

    m_pszData = new char[length+1];
    strcpy(m_pszData,pParam);
}

//전역함수
CMyString operator+(const char* pLeft, const CMyString& rhs){
    CMyString result(pLeft);
    result.append(rhs.m_pszData); //이 함수가 CMyString 클래스의 friend로
                                    //선언되었기 때문에 private 멤버 접근가능
    return result;
}