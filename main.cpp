#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

void read_type(&cur_ptr) {

}


int main(int argc, char* argv[])
{
   char dirName[1000];
//   char ch; // для варианта с побайтовой обработкой
   long int length, i;
   ifstream in;
   ofstream out;
   char *fname = new char [28];
   cout << "Current path: " << getcwd(dirName, sizeof(dirName)) << endl;
    if (argc > 1) {
        fname = argv[1];
    } else {
        fname = "2017_09_13_12_54_32_333.riq";
    }
   cout << "File name: " << fname << endl;
   in.open(fname, ios::in | ios::binary);
   out.open("out.riq", ios::out | ios::binary);

   if (!in) {
       length = in.tellg();
       cout << "Error opening file ";
       exit(1);
   }

// вариант с побайтовым чтением
/*
    while(in){
        in.get(ch);
        out.put(ch);
    }
*/

    cout << "Byte order" << endl;
    in.seekg(0);
    char *buf1 = new char[4];
    in.read((char *) buf1, 4);
//   int v = 0xc4000001;
//   int *ptr = v;
    for (i = 0; i < 4 ; i++) {
        cout << i << ": " << (int) buf1[i] << endl;
        out.write(&buf1[i], 1);
    }

//   out.write(buf1, 1);
   delete [] buf1;
   in.close();
   out.close();
   exit(0);


// вариант с чтением/записью посредством буфера
    in.seekg(0, in.end);
    length = in.tellg();
    cout << "File length: " << length << endl;
    char *buf = new char [length];
    try {
        in.seekg(0);
        in.read((char *) buf, length);
//        in.read((char *) & str, sizeof(str_type));     // вариант с чтением структуры str_type
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
