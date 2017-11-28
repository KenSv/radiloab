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
    typeName +=  (nb == 1? "0": "\0") + to_string(nb << 3);

    *buf += 4;  // указатель на значение переменной
    long value;
    int arItems;
    if (typeName[0] == 'A')
    {
        arItems = *((int *) *buf);
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
    printf("Тип: %s\t Код типа: %#08x\t Значение: %li\n", &typeName[0], varType, value);
}

int main(int argc, char* argv[])
{
    char dirName[1000];
//   char ch; // для варианта с побайтовой обработкой
    long int length;
    ifstream in;
    ofstream out;
    FILE *fRiq;
    char* pRiq;
    char *fname = new char [28];
    printf("Current path: %s\n", getcwd(dirName, sizeof(dirName)));
    if (argc > 1) {
        fname = argv[1];
    } else {
        strcpy(fname, "2017_09_13_12_54_32_333.riq");
    }
    printf("File name: %s\n", fname);
    in.open(fname, ios::in | ios::binary);
    out.open("out.riq", ios::out | ios::binary);

    if (!in) {
        length = in.tellg();
        printf("Error opening file");
        exit(1);
    }

// вариант с чтением/записью посредством буфера
    in.seekg(0, in.end);
    length = in.tellg();

    printf("File length: %li\n", length);
    printf("===========================================\n");
    printf("  Адрес |\tЗначение\tОписание\n");
    printf("===========================================\n");

    char *buf = new char [length];
    try {
        in.seekg(0);
        in.read((char *) buf, length);
        pRiq = (char*) malloc(sizeof(char)*length);
//        in.read((char *) & str, sizeof(str_type));     // вариант с чтением структуры str_type
        char* readPtr = buf;
        char* writePtr = pRiq;
//	int ptr = 0;
//        Riq riq;
        fRiq = fopen("out_riq.riq", "w");
        while(readPtr < &buf[length]) {
//        getType(&readPtr);
            printf("%8x ", (unsigned int) (readPtr -buf));
            if(!parseVar(&readPtr, &writePtr))
                parseArray(&readPtr, &writePtr);
        }

        out.write(buf, length);
//        memcpy(pRiq, buf, length);
        fwrite(pRiq, sizeof(char), length, fRiq);
// жаль нет finally. Остаток кода нужно бы поместить туда :)
// Если через класс, то уничтожать переменные/буферы в деструкторе ?
        delete [] buf;
        in.close();
        out.close();
        fclose(fRiq);
        free(pRiq);
    } catch (int e) {
        printf("An exception %i occurred\n", e);
        exit(2); // указать правильный код ошибки
    }

   exit(0);
}
