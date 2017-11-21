#ifndef RIQ_H
#define RIQ_H
typedef char _u8;
typedef int32_t _s32;
typedef double _f64;


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
        void applyFilter(char* ptrIn, char* ptrOut, int size, long double gain, long double offset);
        void fiterBlackman(char** buf, const double in[], double out[], int sizeIn);
        void fiterKalman(_u8* pIn, _f64* pOut, int block_size);
        void filterSimple(_u8* pIn, _f64* pOut, int block_size);
    protected:
    private:
        _f64 gain;
        _f64 offset;
};

#endif // RIQ_H
