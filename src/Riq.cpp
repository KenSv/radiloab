#include <iostream>
#include <math.h>
#include <string.h>
#include "../db.h"
#include "../include/Riq.h"

using namespace std;

//#ifdef KALMAN
//// реализация фильтра Калмана
//#elifdef BLACKMAN
//// реализация фильтра Блэкмана
//#elif
//// альтернативная реализация
//#endif


//static void from_log(_f64* ones, _s32 size)
//{
//    for (_s32 i = 0; i < size; i++)
//        ones[i] = pow(10., ones[i] / 10.);
//}
//
//static void to_log(_f64* ones, _s32 size)
//{
//    for (_s32 i = 0; i < size; i++)
//        ones[i] = 10.*log10(ones[i]);
//}

void filterSimple(_u8* pIn, _f64* pOut, int block_size)
{
    double dmax = 0;
    double delta = 0;
    double gain = 1;
    double offset = 0;
    int i;
    _f64* pKoef;

    pKoef   = (_f64*) malloc(block_size * sizeof(_f64));

    for (i=0; i < block_size; i++)
        pOut[i] = pow(10, (pIn[i] * gain + offset)/10);

    for (i=0; i < block_size; i++)
    {
        delta = pOut[i+1] - pOut[i];
        if (abs(delta) > dmax) dmax = delta;
        pKoef[i+1] = delta;
    }

    for (i=1; i < block_size; i++)
        pOut[i] = pOut[i] * pOut[i] / dmax;

    for (i=0; i < block_size; i++)
        pOut[i] = 10.*log10(pOut[i]);

    free(pKoef);
}

void fiterKalman(_u8* pIn, _f64* pOut, int block_size)
{
    double gain = 1;
    double offset = 0;
//    _f64* pOut;
//    _u8* pIn;
//    pIn = (_u8*) *buf;
//    pOut = (_f64*) malloc(block_size * sizeof(_f64));

    double ps;              // predicted state
    double pc;              // predicted covariance

    double factor_r = 1;    // factor of real value to previous real value
    double noise_m = 0.2;   // measurement noise
    double factor_m = 1;    // factor of measured value to real value
    double noise_env = 0.8; // environment noise

    double state;
    double covariance;
    double K;
    int i;

    // Задаем начальные значение state и covariance
    state = pOut[0];
    covariance = 0.1;
    // оставил в отдельном цикле, на случай применения рекурсивной обработки
    for (i=0; i < block_size; i++)
        pOut[i] = pow(10, (pIn[i] * gain + offset)/10);

    for (i=0; i< block_size; i++)
    {
        //time update - prediction
        ps = factor_r*state;
        pc = factor_r*covariance*factor_r + noise_m;
        //measurement update - correction
        K = factor_m*pc/(factor_m*pc*factor_m + noise_env);
        state = ps + K*(pOut[i] - factor_m*ps);
        covariance = (1 - K*factor_m)*pc;
        pOut[i] = state;
    }
    for (i=0; i < block_size; i++)
        pOut[i] = 10.*log10(pOut[i]);
}

void fiterBlackman(char** buf, const double in[], double out[], int sizeIn)
{
//    void Filter (const double in[], double out[], int sizeIn)
    const int N = 20;           //Длина фильтра
    double Fd   = 2000;      //Частота дискретизации входных данных
    double Fs   = 20;        //Частота полосы пропускания
    double Fx   = 50;        //Частота полосы затухания

    double H[N]     = {0};    //Импульсная характеристика фильтра
    double H_id[N]  = {0}; //Идеальная импульсная характеристика
    double W[N]     = {0};    //Весовая функция

    //Расчет импульсной характеристики фильтра
    double Fc = (Fs + Fx) / (2 * Fd);

    for (int i=0;i<N;i++)
    {
        if (i==0) H_id[i] = 2*M_PI*Fc;
        else H_id[i] = sinl(2*M_PI*Fc*i )/(M_PI*i);
        // весовая функция Блекмена
        W [i] = 0.42 - 0.5 * cosl((2*M_PI*i) /( N-1)) + 0.08 * cosl((4*M_PI*i) /( N-1));
        H [i] = H_id[i] * W[i];
    }

    //Нормировка импульсной характеристики
    double SUM=0;
    for (int i=0; i<N; i++) SUM +=H[i];
    for (int i=0; i<N; i++) H[i]/=SUM; //сумма коэффициентов равна 1

    //Фильтрация входных данных
    for (int i=0; i<sizeIn; i++)
    {
        out[i]=0.;
        for (int j=0; j<N-1; j++)// та самая формула фильтра
        {
            if(i-j>=0)
            out[i]+= H[j]*in[i-j];
        }
    }
}

void dumpArray(char** buf, unsigned int bytes, unsigned int items, unsigned short itemsOnLine)
{
    for (unsigned int i=0; i < items; i++)
    {
        switch (bytes)
        {
            case 1:
                printf("%4d ", *((char *) *buf + i*bytes));
                break;
            case 2:
                printf("%6d ", *((short *) *buf + i*bytes));
                break;
            case 4:
                printf("%10d ", *((int *) *buf + i*bytes));
                break;
            case 8:
                printf("%f ", *((double *) *buf + i*bytes));
                break;
            default:
                break;
        }
        if ((i+1)%itemsOnLine == 0) printf("\n");
    }
}

void dumpTimeStamp(char** buf, const char* msg)
{
    printf("%s: (%li) %s", msg, *((long *) *buf), ctime((time_t *) *buf));
    *buf += 8;
}

void dump_u8(char** buf, const char* msg)
{
    printf("%16ui\t- %s\n", *((_u8 *) *buf), msg);
    (*buf) ++;
}

void dump_s16(char** buf, const char* msg)
{
    printf("%16ui\t- %s\n", *((_s16 *) *buf), msg);
    *buf += 2;
}

void dump_u16(char** buf, const char* msg)
{
    printf("%16ui\t- %s\n", *((_u16 *) *buf), msg);
    *buf += 2;
}

void dump_s32(char** buf, const char* msg)
{
    printf("%16i\t- %s\n", *((_s32 *) *buf), msg);
    *buf += 4;
}

void dump_u32(char** buf, const char* msg)
{
    printf("%16i\t- %s\n", *((_u32 *) *buf), msg);
    *buf += 4;
}

void dump_u64(char** buf, const char* msg)
{
    printf("%16li\t- %s\n", *((_u64 *) *buf), msg);
    *buf += 8;
}

void dump_s64(char** buf, const char* msg)
{
    printf("%16li\t- %s\n", *((_s64 *) *buf), msg);
    *buf += 8;
}

void dump_f64(char** buf, const char* msg)
{
    printf("%16lf\t- %s\n", *((_f64 *) *buf), msg);
    *buf += 8;
}

void dumpHex64(char** buf, const char* msg)
{
    printf("%16lx\t- %s\n", *((_u64 *) *buf), msg);
    *buf += 8;
}

void dumpHex32(char** buf, const char* msg)
{
    printf("%16x\t- %s\n", *((_u32 *) *buf), msg);
    *buf += 4;
}

void dumpHex8(char** buf, const char* msg)
{
    printf("%16x\t- %s\n", *((_u8 *) *buf), msg);
    (*buf)++;
}

bool parseArray(char** buf, char** pRiq)
{
    unsigned int varType = *((int *) *buf);
    unsigned int nb = (varType >> 24) & 0x0F;
    *buf += 4;
    unsigned int arItems = *((int *) *buf);
    *buf += 4; // длина массива следует за типом значения - 4 байта?

    memcpy(*pRiq, (*buf) - 8, arItems * nb + 8);

    printf(" Массив %u записей: ", arItems);
    _f64* ptrOut = (_f64*)malloc(arItems * sizeof(_f64));

    switch (varType)
    {
    case DBI_IQDATA_S16:
        printf(" IQ-канал (_s16)\n");
        break;
    case DBI_IQDATA_F64:
        printf(" IQ-данные (_f64)\n");
        break;
    case DBI_ODATA_S16:
        printf(" осциллограф (_s16)\n");
        break;
    case DBI_ODATA_F64:
        printf(" осциллограф (_f64)\n");
        break;
    case DBI_FFT_F64:
        printf(" спектр (_f64)\n");
        break;
    case DBI_FFT_U16:
        printf(" спектр (_s16)\n");
        break;
    case DBI_FFT_U8:
        filterSimple(*buf, ptrOut, arItems);
        for (unsigned int i=0; i < arItems; i++)
        {
           (*pRiq)[i] = (_u8)((unsigned int) ptrOut[i]);
        }
        printf(" спектр (_u8)\n");
        break;
    case DBI_FFT_F64_2D:
        printf(" 2D спектр (_f64)\n");
        break;
    case DBI_TGRAM_F64:
        printf(" 2D топограма (_f64)\n");
        break;
    case DBI_BYTEARRAY:
        printf(" массив данных\n");
        break;
    case DBI_DESC_S8:
        printf(" описание\n");
        break;
    case DBI_DESC_U16:
        printf(" описание\n");
        break;
    case DBI_FRAMES:
        printf(" типы представления фреймов в каждом окне\n");
//        cout << hex << buf << *buf << nb << arItems << endl;
        printf(/*"buf: %x *buf: %x*/ "nb: %i items: %i \n", nb, arItems);
        break;
    case DBI_MD_NAME:
        printf(" имя мультимедиа файла\n");
        break;
    case DBI_CHAN_FFT:
        printf(" канальный спектр\n");
        break;
    case DBI_SIGN_MASK:
        printf(" маска сигнатуры\n");
        break;
    case DBI_NAME_S8:
        printf(" имя\n");
        break;
    case DBI_NAME_U16:
        printf(" \n");
        break;
    case DBI_GROUPNAME:
        printf(" название под-группы эталона\n");
        break;
    case DBI_SUBGROUPNAME:
        printf(" название под-группы эталона\n");
        break;
    case DBI_THRR_OFFSETS:
        printf(" смещения порога записи\n");
        break;
    case DBI_SPLITTERS:
        printf(" разделители окна\n");
        break;
    case DBI_CHAN_STATES:
        printf(" состояния каналов\n");
        break;
// пользователи
    case DBI_USER_LOGIN:
        printf(" логин пользователя\n");
        break;
    case DBI_USER_NAME:
        printf(" полное имя пользователя\n");
        break;
    case DBI_USER_AVATAR:
        printf(" аватар пользователя\n");
        break;
    case DBI_USER_PASSWD:
        printf(" хеш пароля пользователя\n");
        break;

// проекты
    case DBI_PROJ_NAME:
        printf(" имя проекта\n");
        break;
    case DBI_PROJ_PASSWD:
        printf(" хеш пароля проекта\n");
        break;
    case DBI_PROJ_DATA_DIR:
        printf(" папка для сохранения файлов\n");
        break;
    case DBI_PROJ_OPTIONS:
        printf(" опции проекта\n");
        break;

// приёмники
    case DBI_RCV_NAME:
        printf(" имя приёмника\n");
        break;
    case DBI_RCV_CHN_NAME:
        printf(" имя канала приёмника\n");
        break;
    default:
        break;
    }
        free(ptrOut);

    dumpArray(buf, nb, arItems, 32);
    printf("<<< Конец массива\n");
    *pRiq += (arItems * nb  + 8);
    *buf += arItems * nb;
    return true;
}

bool parseVar(char** buf, char** pRiq)
{
    unsigned int varType = *((int *) *buf);
    if(varType & (DBIT_ARRAY|DBIT_ARRAY2|DBIT_ARRAY3)) return false;
    unsigned int nb = (varType >> 24) & 0x0F;
    memcpy(*pRiq, *buf, nb + 4);
    *pRiq += (nb + 4);
    *buf += 4;
    long value;
    switch (varType)
    {
    case DBI_VERSION:
//        dumpHex32(buf, "версия DB API");
        dump_u32(buf, "версия DB API");
//        value = *((int *) *buf);
//        *buf += 4;
////        cout << hex << value << " - версия DB API" << endl;
//        printf("%8lx - версия DB API\n", value);
        break;
    case DBI_SFLAGS:
        dump_u32(buf, "системные флаги");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        printf("%8lx - системные флаги\n", value);
////        cout << hex << value << " - системные флаги" << endl;
        break;
    case DBI_UFLAGS:
        dumpHex32(buf, "пользовательские флаги");
//        dump_u32(buf, "пользовательские флаги");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
////        cout << hex << value << " - пользовательские флаги" << endl;
//        printf("%8lx - пользовательские флаги\n", value);
        break;
    case DBI_UIN:
        dump_u64(buf, "Уникальный номер");
//        value = *((long *) *buf);
//        *buf += 8;
////        cout << hex << value << " - Уникальный номер" << endl;
//        printf("%16lx - Уникальный номер\n", value);
        break;
    case DBI_UID:
        dump_u64(buf, "Уникальный идентификатор");
//        value = *((long *) *buf);
//        *buf += 8;
////        cout << hex << value << " - Уникальный идентификатор" << endl;
//        printf("%16lx - Уникальный идентификатор\n", value);
        break;
    case DBI_PROJECTID:
        dump_u64(buf, "Уникальный идентификатор проекта");
//        value = *((long *) *buf);
//        *buf += 8;
////        cout << hex << value << " - Уникальный идентификатор проекта" << endl;
//        printf("%16lx - Уникальный идентификатор проекта\n", value);
        break;
    case DBI_SCANID:
        dump_u32(buf, "Идентификатор сканирования");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
////        cout << hex << value << " - Идентификатор сканирования" << endl;
//        printf("%8lx - Идентификатор сканирования\n", value);
        break;
    case DBI_FMIN:
        dump_f64(buf, "Начальная частота (МГц)");
//        printf("%lf - Начальная частота (МГц)\n", *((double *) *buf));
//        *buf += 8;
        break;
    case DBI_FMAX:
        dump_f64(buf, "Конечная частота (МГц)");
//        printf("%lf - Конечная частота (МГц)\n", *((double *) *buf));
//        *buf += 8;
        break;
    case DBI_FCUR:
        dump_f64(buf, "Центральная частота (МГц)");
//        printf("%lf - Центральная частота (МГц)\n", *((double *) *buf));
//        *buf += 8;
        break;
    case DBI_BAND:
        dump_f64(buf, "полоса (МГц)");
//        printf("%lf - полоса (МГц)\n", *((double *) *buf));
//       *buf += 8;
        break;
    case DBI_GFMIN:
        dump_f64(buf, "общая начальная частота (МГц)");
//        printf("%lf - общая начальная частота (МГц)\n", *((double *) *buf));
//        *buf += 8;
        break;
    case DBI_GFMAX:
        dump_f64(buf, "общая конечная частота (МГц)");
//        printf("%lf - общая конечная частота (МГц)\n", *((double *) *buf));
//        *buf += 8;
        break;
    case DBI_FDIFF:
        dump_f64(buf, "отклонение частоты (МГц)");
//        printf("%lf - отклонение частоты (МГц)\n", *((double *) *buf));
//        *buf += 8;
        break;

    case DBI_COUNT:
        dump_s32(buf, "число выборок в данном сканировании");
//        value = *((int *) *buf);
//        *buf += 4;
////        cout << hex << value << " - число выборок в данном сканировании" << endl;
//        printf("%8lx - число выборок в данном сканировании\n", value);
        break;
    case DBI_SAMPLES:
        dump_u32(buf, "число отсчётов в каждой выборке");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
////        cout << hex << value << " - число отсчётов в каждой выборке" << endl;
//        printf("%8lx - число отсчётов в каждой выборке\n", value);
        break;
    case DBI_TOTAL_SAMPLES:
        dump_u64(buf, "общее число отсчётов");
//        value = *((long *) *buf);
//        *buf += 8;
////        cout << hex << value << " - общее число отсчётов" << endl;
//        printf("%16lx - общее число отсчётов\n", value);
        break;
    case DBI_RBW_KHZ:
        dump_u16(buf, "rbw в кГц");
//        printf("%6u - rbw в кГц\n", *((unsigned short *) *buf));
//        *buf += 2;
        break;

    case DBI_NPACK:
        dump_s32(buf, "номер выборки в пачке");
//        value = *((int *) *buf);
//        *buf += 4;
////        cout << hex << value << " - номер выборки в пачке" << endl;
//        printf("%8lx - номер выборки в пачке\n", value);
        break;
    case DBI_NPACKS:
        dump_s32(buf, "всего выборок в пачке");
//        value = *((int *) *buf);
//        *buf += 4;
////        cout << hex << value << " - всего выборок в пачке" << endl;
//        printf("%8lx - всего выборок в пачке\n", value);
        break;
    case DBI_PEAK_MAX:
        dump_f64(buf, "максимум пик-детектора");
//        printf("%lf - максимум пик-детектора\n", *((double *) *buf));
//        *buf += 8;
        break;
    case DBI_PEAK_MEAN:
        dump_f64(buf, "среднее пик-детектора");
//        printf("%lf - среднее пик-детектора\n", *((double *) *buf));
//        *buf += 8;
        break;

    case DBI_STIME:
        dumpTimeStamp(buf, "Время начала сканирования");
        break;
    case DBI_ETIME:
        dumpTimeStamp(buf, "Время конца сканирования");
        break;
    case DBI_CTIME:
        dump_u32(buf, "время получения выборки");
//        printf("%ui - время получения выборки\n", *((_u32 *) *buf));
//        *buf += 4;
        break;

    case DBI_INDEX:
        dump_s32(buf, "номер выборки");
//        printf("%i - номер выборки\n", *((int *) *buf));
//        *buf += 4;
        break;
    case DBI_OFFSET:
        dump_s64(buf, "смещение выборки в файле");
//        printf("%li - смещение выборки в файле\n", *((_s64 *) *buf));
//        *buf += 8;
        break;
    case DBI_SIZE:
        dump_u32(buf, "размер выборки в файле");
//        printf("%i - размер выборки в файле\n", *((_u32 *) *buf));
//        *buf += 4;
        break;

     case DBI_DATA_GAIN:
        dump_f64(buf, "множитель для перевода FFT в _f64");
//        printf("%lf - множитель для перевода FFT в _f64\n", *((double *) *buf));
//        *buf += 8;
        break;
     case DBI_DATA_OFFSET:
        dump_f64(buf, "смещение для перевода FFT в _f64");
//        printf("%lf - смещение для перевода FFT в _f64\n", *((double *) *buf));
//        *buf += 8;
        break;
     case DBI_IQDATA_GAIN:
        dump_f64(buf, "множитель для перевода IQ в _f64");
//        printf("%lf - множитель для перевода IQ в _f64\n", *((double *) *buf));
//        *buf += 8;
        break;
     case DBI_IQDATA_OFFSET:
        dump_f64(buf, "смещение для перевода IQ в _f64");
//        printf("%lf - смещение для перевода IQ в _f64\n", *((double *) *buf));
//        *buf += 8;
        break;
     case DBI_ODATA_GAIN:
        dump_f64(buf, "множитель для перевода LF в _f64");
//        printf("%lf - множитель для перевода LF в _f64\n", *((double *) *buf));
//        *buf += 8;
        break;
     case DBI_ODATA_OFFSET:
        dump_f64(buf, "смещение для перевода LF в _f64");
//        printf("%lf - смещение для перевода LF в _f64\n", *((double *) *buf));
//        *buf += 8;
        break;

     case DBI_X:
        dump_s32(buf, "положение по горизонтали");
//        value = *((int *) *buf);
//        *buf += 4;
////        cout << hex << value << " - положение по горизонтали" << endl;
//        printf("%8lx - положение по горизонтали\n", value);
        break;
     case DBI_Y:
        dump_s32(buf, "положение по вертикали");
//        value = *((int *) *buf);
//        *buf += 4;
////        cout << hex << value << " - положение по вертикали" << endl;
//        printf("%8lx - положение по вертикали\n", value);
        break;
     case DBI_CX:
        dump_s32(buf, "размер по горизонтали");
//        value = *((int *) *buf);
//        *buf += 4;
////        cout << hex << value << " - размер по горизонтали" << endl;
//        printf("%8lx - размер по горизонтали\n", value);
        break;
     case DBI_CY:
        dump_s32(buf, "размер по вертикали");
//        value = *((int *) *buf);
//        *buf += 4;
////        cout << hex << value << " - размер по вертикали" << endl;
//        printf("%8lx - размер по вертикали\n", value);
        break;
    case DBI_STYPE:
        dump_u8(buf, "тип сигнала");
//        value = *((unsigned char *) *buf);
//        *buf += 1;
////        cout << hex << value << " - тип сигнала" << endl;
//        printf("%8lx - тип сигнала\n", value);
        break;
    case DBI_MTYPE:
        dump_u8(buf, "тип модуляции");
//        value = *((unsigned char *) *buf);
//        *buf += 1;
////        cout << hex << value << " - тип модуляции" << endl;
//        printf("%2lx - тип модуляции\n", value);
        break;
     case DBI_ACOUNT:
        dump_s16(buf, "счётчик активности");
//        value = *((short *) *buf);
//        *buf += 2;
////        cout << hex << value << " - счётчик активности" << endl;
//        printf("%4lx - счётчик активности\n", value);
        break;
     case DBI_TCOUNT:
        dump_u32(buf, "счётчик общего числа обнаружений");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
////        cout << hex << value << " - счётчик общего числа обнаружений" << endl;
//        printf("%8lx - счётчик общего числа обнаружений\n", value);
        break;
     case DBI_NRCV:
        dump_s32(buf, "количество приёмников, на которых сигнал был найден");
//        value = *((int *) *buf);
//        *buf += 4;
////        cout << hex << value << " - количество приёмников, на которых сигнал был найден" << endl;
//        printf("%8lx - количество приёмников, на которых сигнал был найден\n", value);
        break;
     case DBI_CHANNEL:
        dump_u16(buf, "номер канала по стандарту");
//        value = *((unsigned short *) *buf);
//        *buf += 2;
//        cout << hex << value << " - номер канала по стандарту" << endl;
        break;

     case DBI_CLVL:
        dump_f64(buf, "текущий уровень");
////        value = *((double *) *buf);
//        printf("%lf - текущий уровень\n", *((double *) *buf));
//        *buf += 8;
////        cout << hex << value << " - текущий уровень" << endl;
        break;
     case DBI_MLVL:
        dump_f64(buf, "максимальный уровень");
////        value = *((double *) *buf);
//        printf("%lf - максимальный уровень\n", *((double *) *buf));
//        *buf += 8;
////        cout << hex << value << " - максимальный уровень" << endl;
        break;
     case DBI_RLVL:
        dump_f64(buf, "опорный уровень");
////        value = *((double *) *buf);
//        printf("%lf - опорный уровень\n", *((double *) *buf));
//        *buf += 8;
////        cout << hex << value << " - опорный уровень" << endl;
        break;
     case DBI_NLVL:
        dump_f64(buf, "уровень шума");
////        value = *((double *) *buf);
//        printf("%lf - уровень шума\n", *((double *) *buf));
//        *buf += 8;
////        cout << hex << value << " - уровень шума" << endl;
        break;

     case DBI_AZIMUTH:
        dump_s16(buf, "азимут");
//        value = *((short *) *buf);
//        *buf += 2;
//        cout << hex << value << " - азимут" << endl;
        break;
     case DBI_ELEVATION:
        dump_s16(buf, "угол места");
//        value = *((short *) *buf);
//        *buf += 2;
//        cout << hex << value << " - угол места" << endl;
        break;
     case DBI_DTIME:
        dumpTimeStamp(buf, "Время обнаружения");
        break;
     case DBI_FTIME:
        dumpTimeStamp(buf, "Время первого появления");
        break;
     case DBI_LTIME:
        dumpTimeStamp(buf, "Время последнего появления");
        break;
     case DBI_MTIME:
        dumpTimeStamp(buf, "Время максимального уровня");
        break;

     case DBI_VFILTER:
        dump_u16(buf, "видеофильтр");
//        value = *((unsigned short *) *buf);
//        *buf += 2;
//        cout << hex << value << " - видеофильтр" << endl;
        break;
     case DBI_RANGE_NUM:
        dump_u16(buf, "номер диапазона");
////        value = *((unsigned short *) *buf);
//        printf("%i - номер диапазона\n", *((unsigned short  *) *buf));
//        *buf += 2;
////        cout << hex << value << " - номер диапазона" << endl;
        break;
     case DBI_RBW:
        dump_f64(buf, "разрешение Гц/отсчет");
////        value = *((double *) *buf);
//        printf("%f - разрешение Гц/отсчет\n", *((double *) *buf));
//        *buf += 8;
////        cout << hex << value << " - разрешение Гц/отсчет" << endl;
        break;
     case DBI_NOISE_S32:
        dump_s32(buf, "уровень шума дБм (32)");
////        value = *((int *) *buf);
//        printf("%i - уровень шума дБм (32)\n", *((int *) *buf));
//        *buf += 4;
////        cout << hex << value << " - уровень шума дБм" << endl;
        break;
     case DBI_NOISE_F64:
        dump_f64(buf, "уровень шума дБм (64)");
////        value = *((double *) *buf);
//        printf("%f - уровень шума дБм (64)\n", *((double *) *buf));
//        *buf += 8;
////        cout << hex << value << " - уровень шума дБм" << endl;
        break;
     case DBI_BANDWIDTH:
        dump_f64(buf, "полоса сигнала Гц");
////        value = *((double *) *buf);
//        printf("%lf - полоса сигнала Гц\n", *((double *) *buf));
//        *buf += 8;
////        cout << hex << value << " - полоса сигнала Гц" << endl;
        break;

     case DBI_FLAGS:
        dump_u32(buf, "флаги");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - флаги" << endl;
        break;
     case DBI_GROUP1:
        dump_s32(buf, "ID группы 1");
//        value = *((int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - ID группы 1" << endl;
        break;
     case DBI_MASK:
        dump_u32(buf, "маска");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - маска" << endl;
        break;
     case DBI_GROUP2:
        dump_s32(buf, "ID группы 2");
//        value = *((int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - ID группы 2" << endl;
        break;

// Opt структура
     case DBI_AMPL:
        dump_f64(buf, "Амплитуда");
////        value = *((double *) *buf);
//        printf("%lf - Амплитуда\n", *((double *) *buf));
//        *buf += 8;
////        cout << hex << value << " - Амплитуда" << endl;
        break;
     case DBI_ATTEN:
        dump_f64(buf, "аттенюатор");
////        value = *((double *) *buf);
//        printf("%lf - аттенюатор\n", *((double *) *buf));
//        *buf += 8;
////        cout << hex << value << " - аттенюатор" << endl;
        break;
     case DBI_REF_LEVEL:
        dump_f64(buf, "опорный уровень");
////        value = *((double *) *buf);
//        printf("%lf - опорный уровень\n", *((double *) *buf));
//        *buf += 8;
////        cout << hex << value << " - опорный уровень" << endl;
        break;
     case DBI_NSAMPLES:
        dump_u32(buf, "количество отсчетов");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - количество отсчетов" << endl;
        break;
     case DBI_BSAMPLES:
        dump_u32(buf, "количество отсчетов в полосе");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - количество отсчетов в полосе" << endl;
        break;
     case DBI_VFMIN:
        dump_f64(buf, "");
////        value = *((double *) *buf);
//        printf("%lf - минимальная видимая граница частот\n", *((double *) *buf));
//        *buf += 8;
////        cout << hex << value << " - минимальная видимая граница частот" << endl;
        break;
     case DBI_VFMAX:
        dump_f64(buf, "");
////        value = *((double *) *buf);
//        printf("%lf - максимальная видимая граница частот\n", *((double *) *buf));
//        *buf += 8;
////        cout << hex << value << " - максимальная видимая граница частот" << endl;
        break;
     case DBI_AVGNUM:
        dump_u32(buf, "число усреднений");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - число усреднений" << endl;
        break;
     case DBI_AVGTYPE:
        dump_u32(buf, "тип усреднения");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - тип усреднения" << endl;
        break;
     case DBI_FFTWIN:
        dump_u32(buf, "тип окна БПФ");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - тип окна БПФ" << endl;
        break;
     case DBI_DBW:
        dump_f64(buf, "ширина полосы демодуляции");
////        value = *((double *) *buf);
//        printf("%lf - ширина полосы демодуляции\n", *((double *) *buf));
//        *buf += 8;
////        cout << hex << value << " - ширина полосы демодуляции" << endl;
        break;
     case DBI_VBW:
        dump_f64(buf, "разрешение по частоте");
////        value = *((double *) *buf);
//        printf("%lf - разрешение по частоте\n", *((double *) *buf));
//        *buf += 8;
////        cout << hex << value << " - разрешение по частоте" << endl;
        break;
     case DBI_BW:
        dump_f64(buf, "ширина полосы");
////        value = *((double *) *buf);
//        printf("%lf - ширина полосы\n", *((double *) *buf));
//        *buf += 8;
////        cout << hex << value << " - ширина полосы" << endl;
        break;
     case DBI_THRW:
        dump_f64(buf, "порог водопада");
////        value = *((double *) *buf);
//        printf("%lf - порог водопада\n", *((double *) *buf));
//        *buf += 8;
////        cout << value << " - порог водопада" << endl;
        break;
     case DBI_THRR:
        dump_f64(buf, "порог записи");
////        value = *((double *) *buf);
//        printf("%lf - порог записи\n", *((double *) *buf));
//        *buf += 8;
        break;
     case DBI_THRS:
        dump_f64(buf, "порог обнаружения относительно уровня шума");
////        value = *((double *) *buf);
//        printf("%lf - порог обнаружения относительно уровня шума\n", *((double *) *buf));
//        *buf += 8;
////        cout << hex << value << " - порог обнаружения относительно уровня шума" << endl;
        break;
     case DBI_THR_TYPE:
        dump_u32(buf, "тип порога записи");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - тип порога записи" << endl;
        break;
     case DBI_THR_APASS:
        dump_u32(buf, "число превышений для активности");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - число превышений для активности" << endl;
        break;
     case DBI_THR_IAPASS:
        dump_u32(buf, "число проходов без превышения для неактивности");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - число проходов без превышения для неактивности" << endl;
        break;
     case DBI_SCALE:
        dump_f64(buf, "масштаб по оси частот");
////        value = *((double *) *buf);
//        printf("%lf - масштаб по оси частот\n", *((double *) *buf));
//        *buf += 8;
////        cout << hex << value << " - масштаб по оси частот" << endl;
        break;
     case DBI_SOD_SCALE:
        dump_u32(buf, "режим выбора границ спектра осциллографа детектора");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - режим выбора границ спектра осциллографа детектора" << endl;
        break;
     case DBI_DMD_TYPE:
        dump_u32(buf, "тип демодулятора");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - тип демодулятора" << endl;
        break;
     case DBI_DBANDWIDTH:
        dump_f64(buf, "полоса демодулятора");
////        value = *((double *) *buf);
//        printf("%lf - полоса демодулятора\n", *((double *) *buf));
//        *buf += 8;
////        cout << hex << value << " - полоса демодулятора" << endl;
        break;
     case DBI_YFMIN:
        dump_f64(buf, "Нижняя граница спектра");
////        value = *((double *) *buf);
//        printf("%lf - Нижняя граница спектра\n", *((double *) *buf));
//        *buf += 8;
////        cout << hex << value << " - Нижняя граница спектра" << endl;
        break;
     case DBI_YFMAX:
        dump_f64(buf, "Верхняя граница спектра");
////        value = *((double *) *buf);
//        printf("%lf - Верхняя граница спектра\n", *((double *) *buf));
//        *buf += 8;
////        cout << hex << value << " - Верхняя граница спектра" << endl;
        break;
     case DBI_TGRAM_MIN:
        dump_f64(buf, "Нижняя граница топограмы");
////        value = *((double *) *buf);
//        printf("%lf - Нижняя граница топограмы\n", *((double *) *buf));
//        *buf += 8;
////        cout << hex << value << " - Нижняя граница топограмы" << endl;
        break;
     case DBI_TGRAM_MAX:
        dump_f64(buf, "Верхняя граница топограмы");
////        value = *((double *) *buf);
//        printf("%lf - Верхняя граница топограмы\n", *((double *) *buf));
//        *buf += 8;
////        cout << hex << value << " - Верхняя граница топограмы" << endl;
        break;
     case DBI_TRACES:
        dump_u32(buf, "флаги трасс");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - флаги трасс" << endl;
        break;
// каналы
     case DBI_CHAN_ASTATES:
        dump_s32(buf, "количество состояний каналов");
//        value = *((int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - количество состояний каналов" << endl;
        break;
     case DBI_CHAN_NPARTS:
        dump_s32(buf, "количество частей столбца");
//        value = *((int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - количество частей столбца" << endl;
        break;
// пользователи
     case DBI_USER_ID:
        dump_u32(buf, "ID пользователя");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - ID пользователя" << endl;
        break;
// проекты
     case DBI_PROJ_FLAGS:
        dump_u32(buf, "флаги проекта");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - флаги проекта" << endl;
        break;
     case DBI_PROJ_CREATED:
        dump_s64(buf, "когда создан");
//        value = *((long *) *buf);
//        *buf += 8;
//        cout << hex << value << " - когда создан" << endl;
        break;
     case DBI_PROJ_CREATED_BY:
        dump_u32(buf, "кем создан");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - кем создан" << endl;
        break;
     case DBI_PROJ_OPENED:
        dump_s64(buf, "когда открыт последний раз");
//        value = *((long *) *buf);
//        *buf += 8;
//        cout << hex << value << " - когда открыт последний раз" << endl;
        break;
     case DBI_PROJ_OPENED_BY:
        dump_u32(buf, "кем открыт последний раз");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - кем открыт последний раз" << endl;
        break;
     case DBI_PROJ_DEF_RCV:
        dump_s32(buf, "приёмник по умолчанию (панорама)");
//        value = *((int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - приёмник по умолчанию (панорама)" << endl;
        break;
     case DBI_PROJ_DEF_ARCV:
        dump_s32(buf, "приёмник по умолчанию (панорама)");
//        value = *((int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - приёмник по умолчанию (панорама)" << endl;
        break;
// приёмники
     case DBI_RCV_FLAGS:
        dump_u32(buf, "флаги приёмника");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - флаги приёмника" << endl;
        break;
     case DBI_RCV_COLOR:
        dump_u32(buf, "цвет приёмника");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - цвет приёмника" << endl;
        break;
     case DBI_RCV_CHN_CVR_UIN:
        dump_u64(buf, "ID конвертера канала приёмника");
//        value = *((unsigned long *) *buf);
//        *buf += 8;
//        cout << hex << value << " - ID конвертера канала приёмника" << endl;
        break;
     case DBI_RCV_CHN_FLAGS:
        dump_u32(buf, "флаги канала приёмника");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - флаги канала приёмника" << endl;
        break;
// правила
     case DBI_RULE_FREQ_USE:
        dump_u32(buf, "");
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - использование границ частоты" << endl;
        break;
     case DBI_RULE_BAND_USE:
        dump_u32(buf, "использование границ полосы");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - использование границ полосы" << endl;
        break;
     case DBI_RULE_REFD_USE:
        dump_s32(buf, "использование опорного уровня");
//        value = *((int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - использование опорного уровня" << endl;
        break;
     case DBI_RULE_STAT_USE:
        dump_s32(buf, "использование стационарности");
//        value = *((int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - использование стационарности" << endl;
        break;
     case DBI_RULE_LAST_USE:
        dump_u32(buf, "использование последнего времени");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - использование последнего времени" << endl;
        break;
     case DBI_RULE_DESC_USE:
        dump_u32(buf, "использование нового описания");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - использование нового описания" << endl;
        break;
// сигналы/связи
     case DBI_SGN_COUNT:
        dump_u32(buf, "количество сигналов");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - количество сигналов" << endl;
        break;
     case DBI_LNK_COUNT:
        dump_u32(buf, "количество связей");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - количество связей" << endl;
        break;
     case DBI_NET_COUNT:
        dump_u32(buf, "количество связей");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - количество связей" << endl;
        break;
     case DBI_TYPE:
        dump_u32(buf, "логический тип устройства / тип сигнала");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - логический тип устройства / тип сигнала" << endl;
        break;
     case DBI_STATE:
        dump_u32(buf, "дополнительные данные о состоянии");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - дополнительные данные о состоянии" << endl;
        break;
     case DBI_DEV_CHANEL:
        dump_u32(buf, "дополнительные данные о состоянии");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - дополнительные данные о состоянии" << endl;
        break;
     case DBI_BT_FEAT:
        dump_u32(buf, "особенности Bluetooth");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - особенности Bluetooth" << endl;
        break;
     case DBI_ID:
        dump_u64(buf, "идентификатор");
//        value = *((unsigned long *) *buf);
//        *buf += 8;
//        cout << hex << value << " - идентификатор" << endl;
        break;
     case DBI_ID2:
        dump_u64(buf, "идентификатор 2");
//        value = *((unsigned long *) *buf);
//        *buf += 8;
//        cout << hex << value << " - идентификатор 2" << endl;
        break;
     case DBI_ID3:
        dump_u64(buf, "идентификатор 3");
//        value = *((unsigned long *) *buf);
//        *buf += 8;
//        cout << hex << value << " - идентификатор 3" << endl;
        break;
     case DBI_ID4:
        dump_u64(buf, "идентификатор 4");
//        value = *((unsigned long *) *buf);
//        *buf += 8;
//        cout << hex << value << " - идентификатор 4" << endl;
        break;
     case DBI_DATA_TX:
        dump_u64(buf, "передано");
//        value = *((unsigned long *) *buf);
//        *buf += 8;
//        cout << hex << value << " - передано" << endl;
        break;
     case DBI_DATA_RX:
        dump_u64(buf, "принято");
//        value = *((unsigned long *) *buf);
//        *buf += 8;
//        cout << hex << value << " - принято" << endl;
        break;
     case DBI_BTS_IMEI:
        dump_u64(buf, "IMEI");
//        value = *((unsigned long *) *buf);
//        *buf += 8;
//        cout << hex << value << " - IMEI" << endl;
        break;

     case DBI_DEV_TYPE:
        dump_s32(buf, "тип устройства");
//        value = *((int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - тип устройства" << endl;
        break;
     case DBI_LINKS:
        dump_s32(buf, "количество связей");
//        value = *((int *) *buf);
//        *buf += 4;
//        cout << hex << value << " - количество связей" << endl;
        break;

     case DBI_WF_STD:
        dump_u16(buf, "стандарт WiFi");
//        value = *((unsigned short *) *buf);
//        *buf += 2;
//        cout << hex << value << " - стандарт WiFi" << endl;
        break;
     case DBI_WF_SEC:
        dump_u16(buf, "безопасность WiFi");
//        value = *((unsigned short *) *buf);
//        *buf += 2;
//        cout << hex << value << " - безопасность WiFi" << endl;
        break;
     case DBI_ZB_PAN:
        dump_u16(buf, "ID сети ZigBee");
//        value = *((unsigned short *) *buf);
//        *buf += 2;
//        cout << hex << value << " - ID сети ZigBee" << endl;
        break;
     case DBI_CELL_LAC:
        dump_u16(buf, "LAC");
//        value = *((unsigned short *) *buf);
//        *buf += 2;
//        cout << hex << value << " - LAC" << endl;
        break;
     case DBI_CELL_BSIC:
        dump_u16(buf, "BSIC");
//        value = *((unsigned short *) *buf);
//        *buf += 2;
//        cout << hex << value << " - BSIC" << endl;
        break;
     case DBI_BTS_MCC:
        dump_u16(buf, "MCC");
//        value = *((unsigned short *) *buf);
//        *buf += 2;
//        cout << hex << value << " - MCC" << endl;
        break;
     case DBI_BTS_MNC:
        dump_u16(buf, "MNC");
//        value = *((unsigned short *) *buf);
//        *buf += 2;
//        cout << hex << value << " - MNC" << endl;
        break;
     case DBI_EOF:
        dump_u8(buf, "конец файла");
//        value = *((unsigned char *) *buf);
//        *buf += 1;
//        cout << hex << value << " - конец файла" << endl;
        break;
    default:
        unsigned int nb = (varType >> 24) & 0x0F;
        *buf += nb;
        printf("%16x\t - ?????\n", varType);
        break;
    }

    return true;
}
