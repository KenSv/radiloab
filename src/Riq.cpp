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
    case DBI_THRR_OFFSETS:
        cout << " - смещения порога записи" << endl;
        break;
    case DBI_SPLITTERS:
        cout << " - разделители окна" << endl;
        break;
    case DBI_CHAN_STATES:
        cout << " - состояния каналов" << endl;
        break;
// пользователи
    case DBI_USER_LOGIN:
        cout << " - логин пользователя" << endl;
        break;
    case DBI_USER_NAME:
        cout << " - полное имя пользователя" << endl;
        break;
    case DBI_USER_AVATAR:
        cout << " - аватар пользователя" << endl;
        break;
    case DBI_USER_PASSWD:
        cout << " - хеш пароля пользователя" << endl;
        break;

// проекты
    case DBI_PROJ_NAME:
        cout << " - имя проекта" << endl;
        break;
    case DBI_PROJ_PASSWD:
        cout << " - хеш пароля проекта" << endl;
        break;
    case DBI_PROJ_DATA_DIR:
        cout << " - папка для сохранения файлов" << endl;
        break;
    case DBI_PROJ_OPTIONS:
        cout << " - опции проекта" << endl;
        break;

// приёмники
    case DBI_RCV_NAME:
        cout << " - имя приёмника" << endl;
        break;
    case DBI_RCV_CHN_NAME:
        cout << " - имя канала приёмника" << endl;
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
    case DBI_STYPE:
        value = *((unsigned char *) *buf);
        *buf += sizeof(char);
        cout << hex << value << " - тип сигнала" << endl;
        break;
    case DBI_MTYPE:
        value = *((unsigned char *) *buf);
        *buf += sizeof(char);
        cout << hex << value << " - тип модуляции" << endl;
        break;
     case DBI_ACOUNT:
        value = *((short *) *buf);
        *buf += sizeof(short);
        cout << hex << value << " - счётчик активности" << endl;
        break;
     case DBI_TCOUNT:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - счётчик общего числа обнаружений" << endl;
        break;
     case DBI_NRCV:
        value = *((int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - количество приёмников, на которых сигнал был найден" << endl;
        break;
     case DBI_CHANNEL:
        value = *((unsigned short *) *buf);
        *buf += sizeof(short);
        cout << hex << value << " - номер канала по стандарту" << endl;
        break;

     case DBI_CLVL:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - текущий уровень" << endl;
        break;
     case DBI_MLVL:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - максимальный уровень" << endl;
        break;
     case DBI_RLVL:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - опорный уровень" << endl;
        break;
     case DBI_NLVL:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - уровень шума" << endl;
        break;

     case DBI_AZIMUTH:
        value = *((short *) *buf);
        *buf += sizeof(short);
        cout << hex << value << " - азимут" << endl;
        break;
     case DBI_ELEVATION:
        value = *((short *) *buf);
        *buf += sizeof(short);
        cout << hex << value << " - угол места" << endl;
        break;
     case DBI_DTIME:
        value = *((long *) *buf);
        *buf += sizeof(long);
        cout << hex << value << " - время обнаружения" << endl;
        break;
     case DBI_FTIME:
        value = *((long *) *buf);
        *buf += sizeof(long);
        cout << hex << value << " - время первого появления" << endl;
        break;
     case DBI_LTIME:
        value = *((long *) *buf);
        *buf += sizeof(long);
        cout << hex << value << " - время последнего появления" << endl;
        break;
     case DBI_MTIME:
        value = *((long *) *buf);
        *buf += sizeof(long);
        cout << hex << value << " - время максимального уровня" << endl;
        break;

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
     case DBI_DBW:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - ширина полосы демодуляции" << endl;
        break;
     case DBI_VBW:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - разрешение по частоте" << endl;
        break;
     case DBI_BW:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - ширина полосы" << endl;
        break;
     case DBI_THRW:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - порог водопада" << endl;
        break;
     case DBI_THRR:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - порог записи" << endl;
        break;
     case DBI_THRS:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - порог обнаружения относительно уровня шума" << endl;
        break;
     case DBI_THR_TYPE:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - тип порога записи" << endl;
        break;
     case DBI_THR_APASS:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - число превышений для активности" << endl;
        break;
     case DBI_THR_IAPASS:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - число проходов без превышения для неактивности" << endl;
        break;
     case DBI_SCALE:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - масштаб по оси частот" << endl;
        break;
     case DBI_SOD_SCALE:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - режим выбора границ спектра осциллографа детектора" << endl;
        break;
     case DBI_DMD_TYPE:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - тип демодулятора" << endl;
        break;
     case DBI_DBANDWIDTH:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - полоса демодулятора" << endl;
        break;
     case DBI_YFMIN:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - Нижняя граница спектра" << endl;
        break;
     case DBI_YFMAX:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - Верхняя граница спектра" << endl;
        break;
     case DBI_TGRAM_MIN:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - Нижняя граница топограмы" << endl;
        break;
     case DBI_TGRAM_MAX:
        value = *((double *) *buf);
        *buf += sizeof(double);
        cout << hex << value << " - Верхняя граница топограмы" << endl;
        break;
     case DBI_TRACES:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - флаги трасс" << endl;
        break;
// каналы
     case DBI_CHAN_ASTATES:
        value = *((int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - количество состояний каналов" << endl;
        break;
     case DBI_CHAN_NPARTS:
        value = *((int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - количество частей столбца" << endl;
        break;
/*
// пользователи
#define DBI_USER_ID			(0x00000110|DBIT_U32)	// ID пользователя
     case DBI_TRACES:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - флаги трасс" << endl;
        break;

// проекты
#define DBI_PROJ_FLAGS		(0x00000120|DBIT_U32)	// флаги проекта
     case DBI_TRACES:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - флаги трасс" << endl;
        break;
#define DBI_PROJ_CREATED	(0x00000120|DBIT_S64)	// когда создан
#define DBI_PROJ_CREATED_BY	(0x00000121|DBIT_U32)	// кем создан
     case DBI_TRACES:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - флаги трасс" << endl;
        break;
#define DBI_PROJ_OPENED		(0x00000121|DBIT_S64)	// когда открыт последний раз
#define DBI_PROJ_OPENED_BY	(0x00000122|DBIT_U32)	// кем открыт последний раз
     case DBI_TRACES:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - флаги трасс" << endl;
        break;
#define DBI_PROJ_DEF_RCV	(0x00000120|DBIT_S32)	// приёмник по умолчанию (панорама)
#define DBI_PROJ_DEF_ARCV	(0x00000121|DBIT_S32)	// приёмник по умолчанию (панорама)

// приёмники
#define DBI_RCV_FLAGS		(0x00000130|DBIT_U32)	// флаги приёмника
     case DBI_TRACES:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - флаги трасс" << endl;
        break;
#define DBI_RCV_COLOR		(0x00000131|DBIT_U32)	// цвет приёмника
     case DBI_TRACES:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - флаги трасс" << endl;
        break;
#define DBI_RCV_CHN_CVR_UIN	(0x00000132|DBIT_U64)	// ID конвертера канала приёмника
#define DBI_RCV_CHN_FLAGS	(0x00000132|DBIT_U32)	// флаги канала приёмника
     case DBI_TRACES:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - флаги трасс" << endl;
        break;

// правила
#define DBI_RULE_FREQ_USE	(0x00000140|DBIT_U32)	// использование границ частоты
     case DBI_TRACES:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - флаги трасс" << endl;
        break;
#define DBI_RULE_BAND_USE	(0x00000141|DBIT_U32)	// использование границ полосы
     case DBI_TRACES:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - флаги трасс" << endl;
        break;
#define DBI_RULE_REFD_USE	(0x00000140|DBIT_S32)	// использование опорного уровня
#define DBI_RULE_STAT_USE	(0x00000141|DBIT_S32)	// использование стационарности
#define DBI_RULE_LAST_USE	(0x00000142|DBIT_U32)	// использование последнего времени
     case DBI_TRACES:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - флаги трасс" << endl;
        break;
#define DBI_RULE_DESC_USE	(0x00000143|DBIT_U32)	// использование нового описания
     case DBI_TRACES:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - флаги трасс" << endl;
        break;

// сигналы/связи
#define DBI_SGN_COUNT		(0x00000150|DBIT_U32)	// количество сигналов
     case DBI_TRACES:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - флаги трасс" << endl;
        break;
#define DBI_LNK_COUNT		(0x00000151|DBIT_U32)	// количество связей
     case DBI_TRACES:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - флаги трасс" << endl;
        break;
#define DBI_NET_COUNT		(0x00000152|DBIT_U32)	// количество связей
     case DBI_TRACES:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - флаги трасс" << endl;
        break;
#define DBI_TYPE			(0x00000153|DBIT_U32)	// логический тип устройства / тип сигнала
     case DBI_TRACES:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - флаги трасс" << endl;
        break;
#define DBI_STATE			(0x00000154|DBIT_U32)	// дополнительные данные о состоянии
     case DBI_TRACES:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - флаги трасс" << endl;
        break;
#define DBI_DEV_CHANEL		(0x00000155|DBIT_U32)	// дополнительные данные о состоянии
     case DBI_TRACES:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - флаги трасс" << endl;
        break;
#define DBI_BT_FEAT			(0x00000156|DBIT_U32)	// особенности Bluetooth
     case DBI_TRACES:
        value = *((unsigned int *) *buf);
        *buf += sizeof(int);
        cout << hex << value << " - флаги трасс" << endl;
        break;

#define DBI_ID				(0x00000150|DBIT_U64)	// идентификатор
#define DBI_ID2				(0x00000151|DBIT_U64)	// идентификатор 2
#define DBI_ID3				(0x00000152|DBIT_U64)	// идентификатор 3
#define DBI_ID4				(0x00000153|DBIT_U64)	// идентификатор 4
#define DBI_DATA_TX			(0x00000154|DBIT_U64)	// передано
#define DBI_DATA_RX			(0x00000155|DBIT_U64)	// принято
#define DBI_BTS_IMEI		(0x00000157|DBIT_U64)	// IMEI

#define DBI_DEV_TYPE		(0x00000150|DBIT_S32)	// тип устройства
#define DBI_LINKS			(0x00000151|DBIT_S32)	// количество связей

#define DBI_WF_STD			(0x00000150|DBIT_U16)	// стандарт WiFi
#define DBI_WF_SEC			(0x00000151|DBIT_U16)	// безопасность WiFi
#define DBI_ZB_PAN			(0x00000152|DBIT_U16)	// ID сети ZigBee
#define DBI_CELL_LAC		(0x00000154|DBIT_U16)	// LAC
#define DBI_CELL_BSIC		(0x00000155|DBIT_U16)	// BSIC
#define DBI_BTS_MCC			(0x00000156|DBIT_U16)	// MCC
#define DBI_BTS_MNC			(0x00000157|DBIT_U16)	// MNC
*/

    default:
        unsigned int nb = (varType >> 24) & 0x0F;
        *buf += nb;
        break;
    }

    return true;
}
