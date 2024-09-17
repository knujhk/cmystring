#pragma once
#include "CMyString.h"


class CMyStringEx : public CMyString
{
public:
    CMyStringEx();
    ~CMyStringEx();
    void onSetData(const char*&);
    CMyStringEx& operator=(const char*);
};