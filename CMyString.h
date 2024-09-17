#pragma once
//#include <iostream> 헤더파일에서 다른 헤더파일을 인클루드하는게 좋지않다.

class CMyString
{
    friend CMyString operator+(const char* pLeft, const CMyString& rhs);

public:
    //생성자
    CMyString();
    explicit CMyString(const char*);
    CMyString(const CMyString& rhs); 
    CMyString(CMyString&& rhs) noexcept;

    //복사,이동 대입 연산자 재정의
    CMyString& operator=(const CMyString& rhs);
    CMyString& operator=(const char*);
    CMyString& operator=(CMyString&& rhs) noexcept;

    //배열 연산자
    char& operator[](int);
    char operator[](int) const;

    //문자열 덧셈 기능
    size_t append(const char*);
    CMyString operator+(const CMyString& rhs);
    CMyString operator+(const char*);
    CMyString& operator+=(char const*);

    //소멸자
    virtual ~CMyString();

    //CMyString -> char const* 로 묵시적 형 변환 지원
    operator const char*() const;

    //게터 세터
    virtual void onSetData(const char*&);
    const char* getData() const;
    size_t getLength() const;                              
    void setData(const char*); 

private:
    char* m_pszData = nullptr;  
    size_t length = 0;
};


//덧셈 연산에서 왼쪽 피연산자가 문자열 상수인 경우
CMyString operator+(const char* pLeft, const CMyString& rhs);
