#include <iostream>
#include "../db.h"
#include "../include/Riq.h"

using namespace std;

Riq::Riq()
{
    //ctor
}

Riq::~Riq()
{
    //dtor
}

bool Riq::parseArray(char** buf)
{
    unsigned int varType = *((int *) *buf);
    unsigned int nb = (varType >> 24) & 0x0F;
    *buf += 4;
    int arItems = *((int *) *buf);
    *buf += sizeof(int) + arItems * nb;  // длина массива следует за типом значения - 4 байта?
//    value = arItems;
    cout << arItems << " Массив" << endl;
    return true;
}

bool Riq::parseVar(char** buf)
{
    unsigned int varType = *((int *) *buf);
    if(varType & (DBIT_ARRAY|DBIT_ARRAY2|DBIT_ARRAY3)) return false;
    *buf += 4;
    long value;
    switch (varType)
    {
    case DBI_VERSION:
        value = *((int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - версия DB API" << endl;
        break;
    case DBI_SFLAGS:
        value = *((int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - системные флаги" << endl;
        break;
    case DBI_UFLAGS:
        value = *((int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - пользовательские флаги" << endl;
        break;
    case DBI_UIN:
        value = *((long *) *buf);
        *buf += sizeof(long);
        cout << hex << value << " - Уникальный номер" << endl;
        break;
    case DBI_UID:
        value = *((long *) *buf);
        *buf += sizeof(long);
        cout << hex << value << " - Уникальный идентификатор" << endl;
        break;
    case DBI_PROJECTID:
        value = *((long *) *buf);
        *buf += sizeof(long);
        cout << hex << value << " - Уникальный идентификатор проекта" << endl;
        break;
    case DBI_SCANID:
        value = *((int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - Идентификатор сканирования" << endl;
        break;
    case DBI_FMIN:
        value = *((long *) *buf);
        *buf += sizeof(long);
        cout << hex << value << " - Начальная частота (МГц)" << endl;
        break;
    case DBI_FMAX:
        value = *((long *) *buf);
        *buf += sizeof(long);
        cout << hex << value << " - Конечная частота (МГц)" << endl;
        break;





     case DBI_IQDATA_GAIN:
        value = *((long *) *buf);
        *buf += sizeof(long);
        cout << hex << value << " - множитель для перевода IQ в _f64" << endl;
        break;



     case DBI_X:
        value = *((int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - положение по горизонтали" << endl;
        break;



    default:
        break;
    }

    return true;
}
