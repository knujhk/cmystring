#include <iostream>
#include "CMyStringEx.h"

using namespace std;

int main(){

    CMyString* pStrData= new CMyStringEx;
    pStrData->setData("코드몽키");

    cout << pStrData->getData() << endl;
    delete pStrData;

    return 0;
}