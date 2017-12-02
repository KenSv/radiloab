#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include "db.h"
#include "include/Riq.h"

using namespace std;

int main(int argc, char* argv[])
{
    char dirName[1000];
    long int length;
    FILE *fRiq, *fIn, *fOut;
    char* pRiq;
    char *fname = new char [30];

    printf("Current path: %s\n", getcwd(dirName, sizeof(dirName)));
    if (argc > 1) {
        fname = argv[1];
    } else {
        strcpy(fname, "2017_09_13_12_54_32_333.riq");
    }
    printf("File name: %s\n", fname);
    try
    {
        fIn = fopen(fname, "rb");
    }
    catch (int e)
    {
        printf("Error opening file. Error %i", e);
        fclose(fIn);
        exit(1);
    }
    fOut = fopen("origin.riq", "wb");
    fseek(fIn, 0L, SEEK_END);
    length = ftell(fIn);

    printf("File length: %li\n", length);
    printf("===========================================\n");
    printf("  Адрес |\tЗначение\tОписание\n");
    printf("===========================================\n");

    char *buf = new char [length];
    try {
        rewind(fIn);
        fread((char *) buf, sizeof(char), length, fIn);
        pRiq = (char*) malloc(sizeof(char)*length);
        char* readPtr = buf;
        char* writePtr = pRiq;

        fRiq = fopen("filtered.riq", "w");
        while(readPtr < &buf[length]) {
            printf("%8x ", (unsigned int) (readPtr -buf));
            if(!parseVar(&readPtr, &writePtr))
                parseArray(&readPtr, &writePtr);
        }
        fwrite(buf, sizeof(char), length, fOut);
        fwrite(pRiq, sizeof(char), length, fRiq);

        delete [] buf;
        fclose(fIn);
        fclose(fOut);
        fclose(fRiq);
        free(pRiq);
    } catch (int e) {
        printf("An exception %i occurred\n", e);
        exit(1);
    }
   exit(0);
}


//void getType(char** buf) {
//    unsigned int varType = *((int *) *buf);
//    string typeName = "";
//    if(varType & (DBIT_ARRAY|DBIT_ARRAY2|DBIT_ARRAY3))
//    {
//        typeName = "A";
//        switch (varType & 0x30000000)
//        {
//        case DBIT_ARRAY2:
//            typeName += "2D";
//            break;
//        case DBIT_ARRAY3:
//            typeName += "3D";
//            break;
//        default:
//            typeName += "1D";
//            break;
//        }
//    } else {
//        typeName = "  N";
//    }
//
//    typeName += ((varType & 0xC0000000)? "U": "S");
//    unsigned int nb = (varType >> 24) & 0x0F;
//    typeName +=  (nb == 1? "0": "\0") + to_string(nb << 3);
//
//    *buf += 4;  // указатель на значение переменной
//    long value;
//    int arItems;
//    if (typeName[0] == 'A')
//    {
//        arItems = *((int *) *buf);
//        *buf += sizeof(int) + arItems * nb;  // длина массива следует за типом значения - 4 байта?
//        value = arItems;
//    }
//    else
//    {
//        switch (nb)
//        {
//        case 1:
//            value = *((char *) *buf);
//            break;
//        case 2:
//            value = *((short *) *buf);
//            break;
//        case 4:
//            value = *((int *) *buf);
//            break;
//        case 8:
//            value = *((long *) *buf);
//            break;
//        default:
//            break;
//        }
//        *buf += nb;
//    }
//    printf("Тип: %s\t Код типа: %#08x\t Значение: %li\n", &typeName[0], varType, value);
//}
