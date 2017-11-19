#ifndef RIQ_H
#define RIQ_H


class Riq
{
    public:
        Riq();
        virtual ~Riq();
        bool parseVar(char** buf);
        bool parseArray(char** buf);
        void dumpArray(char** buf, unsigned int bytes, unsigned int items, unsigned short itemsOnLine);
        void dumpTimeStamp(char** buf, const char* msg);
//        void* getNextSpectr(char** buf);
        void* applyFilter(char* ptrIn, char* ptrOut, int size, long double gain, long double offset);
        void fiterBlackman(char** buf, const double in[], double out[], int sizeIn);
        void fiterKalman(char** buf);
    protected:
    private:
};

#endif // RIQ_H
