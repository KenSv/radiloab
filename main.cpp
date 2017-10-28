#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include "db.h"
#include "include/Riq.h"

using namespace std;

void getType(char** buf) {
    unsigned int varType = *((int *) *buf);
    string typeName = "";
    if(varType & (DBIT_ARRAY|DBIT_ARRAY2|DBIT_ARRAY3))
    {
        typeName = "A";
        switch (varType & 0x30000000)
        {
        case DBIT_ARRAY2:
            typeName += "2D";
            break;
        case DBIT_ARRAY3:
            typeName += "3D";
            break;
        default:
            typeName += "1D";
            break;
        }
    } else {
        typeName = "  N";
    }

    typeName += ((varType & 0xC0000000)? "U": "S");
    unsigned int nb = (varType >> 24) & 0x0F;
//    unsigned int id = varType & 0x000000FF;
//    cout << "Id: " << id << " bytes: " << hex << nb <<endl;

    typeName +=  (nb == 1? "0": "\0") + to_string(nb << 3);

    *buf += 4;  // указатель на значение переменной
    long value;
    int arItems;
    if (typeName[0] == 'A')
    {
        arItems = *((int *) *buf);
//        cout << "array bytes: " << nb << endl;
        *buf += sizeof(int) + arItems * nb;  // длина массива следует за типом значения - 4 байта?
        value = arItems;
    }
    else
    {
        switch (nb)
        {
        case 1:
            value = *((char *) *buf);
            break;
        case 2:
            value = *((short *) *buf);
            break;
        case 4:
            value = *((int *) *buf);
            break;
        case 8:
            value = *((long *) *buf);
            break;
        default:
            break;
        }
        *buf += nb;
    }
    // << hex << (long) (*buf)
    cout << "Тип: " << typeName << " Код типа: 0x" << hex << varType << " Значение: " << value << endl;
}

int main(int argc, char* argv[])
{
    char dirName[1000];
//   char ch; // для варианта с побайтовой обработкой
    long int length;
    ifstream in;
    ofstream out;
    char *fname = new char [28];
    cout << "Current path: " << getcwd(dirName, sizeof(dirName)) << endl;
    if (argc > 1) {
        fname = argv[1];
    } else {
        strcpy(fname, "2017_09_13_12_54_32_333.riq");
    }
    cout << "File name: " << fname << endl;
    in.open(fname, ios::in | ios::binary);
    out.open("out.riq", ios::out | ios::binary);

    if (!in) {
        length = in.tellg();
        cout << "Error opening file ";
        exit(1);
    }

// вариант с чтением/записью посредством буфера
    in.seekg(0, in.end);
    length = in.tellg();
    cout << "File length: " << length << endl;
    cout << "========================================" << endl << endl;

    char *buf = new char [length];
    try {
        in.seekg(0);
        in.read((char *) buf, length);
//        in.read((char *) & str, sizeof(str_type));     // вариант с чтением структуры str_type
    char* readPtr = buf;
//	int ptr = 0;
    Riq riq;
	while(readPtr < &buf[length]) {
//        getType(&readPtr);

        cout << (unsigned int) (readPtr -buf) << " ";
        if(!riq.parseVar(&readPtr))
            riq.parseArray(&readPtr);
	}

        out.write(buf, length);
// жаль нет finally. Остаток кода нужно бы поместить туда :)
// Если через класс, то уничтожать переменные/буферы в деструкторе ?
        delete [] buf;
        in.close();
        out.close();
    } catch (int e) {
        cout << "An exception " << e <<" occurred\n";
        exit(2); // указать правильный код ошибки
    }

   exit(0);
}
