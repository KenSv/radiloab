#ifndef RIQ_H
#define RIQ_H
typedef char            _u8;
typedef signed char     _s8;
typedef short           _s16;
typedef unsigned short  _u16;
typedef unsigned int    _u32;
typedef int             _s32;
typedef long            _s64;
typedef unsigned long   _u64;
typedef double          _f64;



bool parseVar(char** buf, char** pRiq);
bool parseArray(char** buf, char** pRiq);
void dumpArray(char** buf, unsigned int bytes, unsigned int items, unsigned short itemsOnLine);
void dumpTimeStamp(char** buf, const char* msg);
void fiterBlackman(char** buf, const double in[], double out[], int sizeIn);
void fiterKalman(_u8* pIn, _f64* pOut, int block_size);
void filterSimple(_u8* pIn, _f64* pOut, int block_size);

#endif // RIQ_H
