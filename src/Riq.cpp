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
    unsigned int arItems = *((int *) *buf);
    *buf += sizeof(int); // длина массива следует за типом значения - 4 байта?
//    value = arItems;


    cout << arItems << " Массив" << endl;
    switch (varType)
    {
    case DBI_IQDATA_S16:
        cout << " - Q-канал (_s16)" << endl;
        break;
    case DBI_IQDATA_F64:
        cout << " - IQ-данные (_f64)" << endl;
        break;
    case DBI_ODATA_S16:
        cout << " - осциллограф (_s16)" << endl;
        break;
    case DBI_ODATA_F64:
        cout << " - осциллограф (_f64)" << endl;
        break;
    case DBI_FFT_F64:
        cout << " - спектр (_f64)" << endl;
        break;
    case DBI_FFT_U16:
        cout << " - спектр (_s16)" << endl;
        break;
    case DBI_FFT_U8:
        cout << " - спектр (_u8)" << endl;
        break;
    case DBI_FFT_F64_2D:
        cout << " - 2D спектр (_f64)" << endl;
        break;
    case DBI_TGRAM_F64:
        cout << " - 2D топограма (_f64)" << endl;
        break;
    case DBI_BYTEARRAY:
        cout << " - массив данных" << endl;
        break;
    case DBI_DESC_S8:
        cout << " - описание" << endl;
        break;
    case DBI_DESC_U16:
        cout << " - описание" << endl;
        break;
    case DBI_FRAMES:
        cout << " - типы представления фреймов в каждом окне" << endl;
//        cout << hex << buf << *buf << nb << arItems << endl;
        printf(/*"buf: %x *buf: %x*/ "nb: %i items: %i \n", nb, arItems);
        break;
    case DBI_MD_NAME:
        cout << " - имя мультимедиа файла" << endl;
        break;
    case DBI_CHAN_FFT:
        cout << " - канальный спектр" << endl;
        break;
    case DBI_SIGN_MASK:
        cout << " - маска сигнатуры" << endl;
        break;
    case DBI_NAME_S8:
        cout << " - имя" << endl;
        break;
    case DBI_NAME_U16:
        cout << " - " << endl;
        break;
    case DBI_GROUPNAME:
        cout << " - название под-группы эталона" << endl;
        break;
    case DBI_SUBGROUPNAME:
        cout << " - название под-группы эталона" << endl;
        break;
/*    case :
        cout << " - " << endl;
        break;
    case :
        cout << " - " << endl;
        break;
    case :
        cout << " - " << endl;
        break;
    case :
        cout << " - " << endl;
        break;
    case :
        cout << " - " << endl;
        break;
    case :
        cout << " - " << endl;
        break;
*/
    default:
        break;
    }

/*    for (unsigned int i=0; i < arItems; i++)
    {
        for (unsigned int j=0; j < nb; j++) {
            cout << i+1 << hex << *((char *) *buf + (i*nb)+j) << " ";
        }
        cout << endl;
    }
*/
    *buf += arItems * nb;
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
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - системные флаги" << endl;
        break;
    case DBI_UFLAGS:
        value = *((unsigned int *) *buf);
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
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - Идентификатор сканирования" << endl;
        break;
    case DBI_FMIN:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - Начальная частота (МГц)" << endl;
        break;
    case DBI_FMAX:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << itoa(value) << " - Конечная частота (МГц)" << endl;
        break;
    case DBI_FCUR:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - Центральная частота (МГц)" << endl;
        break;
    case DBI_BAND:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - полоса (МГц)" << endl;
        break;
    case DBI_GFMIN:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - общая начальная частота (МГц)" << endl;
        break;
    case DBI_GFMAX:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - общая конечная частота (МГц)" << endl;
        break;
    case DBI_FDIFF:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - отклонение частоты (МГц)" << endl;
        break;

    case DBI_COUNT:
        value = *((int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - число выборок в данном сканировании" << endl;
        break;
    case DBI_SAMPLES:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - число отсчётов в каждой выборке" << endl;
        break;
    case DBI_TOTAL_SAMPLES:
        value = *((long *) *buf);
        *buf += sizeof(long);
        cout << hex << value << " - общее число отсчётов" << endl;
        break;
    case DBI_RBW_KHZ:
        value = *((unsigned short *) *buf);
        *buf += sizeof(short);
        cout << hex << value << " - rbw в кГц" << endl;
        break;

    case DBI_NPACK:
        value = *((int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - номер выборки в пачке" << endl;
        break;
    case DBI_NPACKS:
        value = *((int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - всего выборок в пачке" << endl;
        break;
    case DBI_PEAK_MAX:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - максимум пик-детектора" << endl;
        break;
    case DBI_PEAK_MEAN:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - среднее пик-детектора" << endl;
        break;

    case DBI_STIME:
        value = *((long *) *buf);
        *buf += sizeof(long);
        cout << hex << value << " - время начала сканирования" << endl;
        break;
    case DBI_ETIME:
        value = *((long *) *buf);
        *buf += sizeof(long);
        cout << hex << value << " - время конца сканирования" << endl;
        break;
    case DBI_CTIME:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - время получения выборки" << endl;
        break;

    case DBI_INDEX:
        value = *((int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - номер выборки" << endl;
        break;
    case DBI_OFFSET:
        value = *((long *) *buf);
        *buf += sizeof(long);
        cout << hex << value << " - смещение выборки в файле" << endl;
        break;
    case DBI_SIZE:
        value = *((int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - размер выборки в файле" << endl;
        break;

     case DBI_DATA_GAIN:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - множитель для перевода FFT в _f64" << endl;
        break;
     case DBI_DATA_OFFSET:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - смещение для перевода FFT в _f64" << endl;
        break;
     case DBI_IQDATA_GAIN:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - множитель для перевода IQ в _f64" << endl;
        break;
     case DBI_IQDATA_OFFSET:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - смещение для перевода IQ в _f64" << endl;
        break;
     case DBI_ODATA_GAIN:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - множитель для перевода LF в _f64" << endl;
        break;
     case DBI_ODATA_OFFSET:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - смещение для перевода LF в _f64" << endl;
        break;

     case DBI_X:
        value = *((int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - положение по горизонтали" << endl;
        break;
     case DBI_Y:
        value = *((int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - положение по вертикали" << endl;
        break;
     case DBI_CX:
        value = *((int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - размер по горизонтали" << endl;
        break;
     case DBI_CY:
        value = *((int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - размер по вертикали" << endl;
        break;
/*
#define DBI_STYPE			(0x00000040|DBIT_U8)	// тип сигнала
#define DBI_MTYPE			(0x00000041|DBIT_U8)	// тип модуляции
#define DBI_ACOUNT			(0x00000042|DBIT_S16)	// счётчик активности
#define DBI_TCOUNT			(0x00000043|DBIT_U32)	// счётчик общего числа обнаружений
#define DBI_NRCV			(0x00000044|DBIT_S32)	// количество приёмников, на которых сигнал был найден
*/

/*
#define DBI_CHANNEL			(0x00000049|DBIT_U16)	// номер канала по стандарту

#define DBI_CLVL			(0x00000050|DBIT_F64)	// текущий уровень
#define DBI_MLVL			(0x00000051|DBIT_F64)	// максимальный уровень
#define DBI_RLVL			(0x00000052|DBIT_F64)	// опорный уровень
#define DBI_NLVL			(0x00000053|DBIT_F64)	// уровень шума

#define DBI_AZIMUTH			(0x00000052|DBIT_S16)	// азимут
#define DBI_ELEVATION		(0x00000053|DBIT_S16)	// угол места

#define DBI_DTIME			(0x00000055|DBIT_S64)	// время обнаружения
#define DBI_FTIME			(0x00000056|DBIT_S64)	// время первого появления
#define DBI_LTIME			(0x00000057|DBIT_S64)	// время последнего появления
#define DBI_MTIME			(0x00000058|DBIT_S64)	// время максимального уровня
*/

/*
#define DBI_VFILTER			(0x00000062|DBIT_U16)	// видеофильтр
#define DBI_RANGE_NUM		(0x00000063|DBIT_U16)	// номер диапазона
#define DBI_RBW				(0x00000064|DBIT_F64)	// разрешение Гц/отсчет
#define DBI_NOISE_S32		(0x00000065|DBIT_S32)	// уровень шума дБм
#define DBI_NOISE_F64		(0x00000065|DBIT_F64)	// уровень шума дБм
#define DBI_BANDWIDTH		(0x00000066|DBIT_F64)	// полоса сигнала Гц
*/

/*
#define DBI_FLAGS			(0x0000006A|DBIT_U32)	// флаги
#define DBI_GROUP1			(0x0000006A|DBIT_S32)	// ID группы 1
#define DBI_MASK			(0x0000006B|DBIT_U32)	// маска
#define DBI_GROUP2			(0x0000006B|DBIT_S32)	// ID группы 2
*/

// Opt структура
     case DBI_AMPL:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - Амплитуда" << endl;
        break;
     case DBI_ATTEN:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - аттенюатор" << endl;
        break;
     case DBI_REF_LEVEL:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - опорный уровень" << endl;
        break;
     case DBI_NSAMPLES:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - количество отсчетов" << endl;
        break;
     case DBI_BSAMPLES:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - количество отсчетов в полосе" << endl;
        break;
     case DBI_VFMIN:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - минимальная видимая граница частот" << endl;
        break;
     case DBI_VFMAX:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - максимальная видимая граница частот" << endl;
        break;
     case DBI_AVGNUM:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - число усреднений" << endl;
        break;
     case DBI_AVGTYPE:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - тип усреднения" << endl;
        break;
     case DBI_FFTWIN:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - тип окна БПФ" << endl;
        break;
/*#define DBI_DBW 			(0x0000007C|DBIT_F64)	// ширина полосы демодуляции
#define DBI_VBW 			(0x0000007D|DBIT_F64)	// разрешение по частоте
#define DBI_BW 				(0x0000007F|DBIT_F64)	// ширина полосы
#define DBI_THRW			(0x00000080|DBIT_F64)	// порог водопада
#define DBI_THRR			(0x00000081|DBIT_F64)	// порог записи
#define DBI_THRR_OFFSETS	(0x00000081|DBIT_AF64)	// смещения порога записи
#define DBI_THRS			(0x00000082|DBIT_F64)	// порог обнаружения относительно уровня шума
#define DBI_THR_TYPE		(0x00000083|DBIT_U32)	// тип порога записи
#define DBI_THR_APASS		(0x00000085|DBIT_U32)	// число превышений для активности
#define DBI_THR_IAPASS		(0x00000086|DBIT_U32)	// число проходов без превышения для неактивности
#define DBI_SCALE			(0x00000087|DBIT_F64)	// масштаб по оси частот
#define DBI_SOD_SCALE		(0x00000088|DBIT_U32)	// режим выбора границ спектра осциллографа детектора
#define DBI_DMD_TYPE		(0x00000089|DBIT_U32)	// тип демодулятора
#define DBI_DBANDWIDTH		(0x0000008A|DBIT_F64)	// полоса демодулятора
#define DBI_YFMIN 			(0x0000008B|DBIT_F64)	// Нижняя граница спектра
#define DBI_YFMAX 			(0x0000008C|DBIT_F64)	// Верхняя граница спектра
#define DBI_SPLITTERS		(0x0000008D|DBIT_AF32)	// разделители окна
#define DBI_TGRAM_MIN 		(0x0000008E|DBIT_F64)	// Нижняя граница топограмы
#define DBI_TGRAM_MAX 		(0x0000008F|DBIT_F64)	// Верхняя граница топограмы
#define DBI_TRACES			(0x00000090|DBIT_U32)	// флаги трасс
*/

    default:
        unsigned int nb = (varType >> 24) & 0x0F;
        *buf += nb;
        break;
    }

    return true;
}
