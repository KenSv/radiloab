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

void Riq::dumpArray(char** buf, unsigned int bytes, unsigned int items, unsigned short itemsOnLine)
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
        if ((i+1)%itemsOnLine == 0) cout << endl;
    }
}

void Riq::dumpTimeStamp(char** buf, const char* msg)
{
//    time_t tm = (time_t *) *buf;
//    printf("%s: %s", msg, ctime(tm));
    printf("%s: %s", msg, ctime((time_t *) *buf));
    *buf += 8;
}

bool Riq::parseArray(char** buf)
{
    unsigned int varType = *((int *) *buf);
    unsigned int nb = (varType >> 24) & 0x0F;
    *buf += 4;
    unsigned int arItems = *((int *) *buf);
    *buf += 4; // длина массива следует за типом значения - 4 байта?
//    value = arItems;

//    cout << arItems << " Массив ";
    printf(" Массив %u записей: ", arItems);
    switch (varType)
    {
    case DBI_IQDATA_S16:
        cout << " Q-канал (_s16)" << endl;
        break;
    case DBI_IQDATA_F64:
        cout << " IQ-данные (_f64)" << endl;
        break;
    case DBI_ODATA_S16:
        cout << " осциллограф (_s16)" << endl;
        break;
    case DBI_ODATA_F64:
        cout << " осциллограф (_f64)" << endl;
        break;
    case DBI_FFT_F64:
        cout << " спектр (_f64)" << endl;
        break;
    case DBI_FFT_U16:
        cout << " спектр (_s16)" << endl;
        break;
    case DBI_FFT_U8:
        cout << " спектр (_u8)" << endl;
        break;
    case DBI_FFT_F64_2D:
        cout << " 2D спектр (_f64)" << endl;
        break;
    case DBI_TGRAM_F64:
        cout << " 2D топограма (_f64)" << endl;
        break;
    case DBI_BYTEARRAY:
        cout << " массив данных" << endl;
        break;
    case DBI_DESC_S8:
        cout << " описание" << endl;
        break;
    case DBI_DESC_U16:
        cout << " описание" << endl;
        break;
    case DBI_FRAMES:
        cout << " типы представления фреймов в каждом окне" << endl;
//        cout << hex << buf << *buf << nb << arItems << endl;
        printf(/*"buf: %x *buf: %x*/ "nb: %i items: %i \n", nb, arItems);
        break;
    case DBI_MD_NAME:
        cout << " имя мультимедиа файла" << endl;
        break;
    case DBI_CHAN_FFT:
        cout << " канальный спектр" << endl;
        break;
    case DBI_SIGN_MASK:
        cout << " маска сигнатуры" << endl;
        break;
    case DBI_NAME_S8:
        cout << " имя" << endl;
        break;
    case DBI_NAME_U16:
        cout << " " << endl;
        break;
    case DBI_GROUPNAME:
        cout << " название под-группы эталона" << endl;
        break;
    case DBI_SUBGROUPNAME:
        cout << " название под-группы эталона" << endl;
        break;
    case DBI_THRR_OFFSETS:
        cout << " смещения порога записи" << endl;
        break;
    case DBI_SPLITTERS:
        cout << " разделители окна" << endl;
        break;
    case DBI_CHAN_STATES:
        cout << " состояния каналов" << endl;
        break;
// пользователи
    case DBI_USER_LOGIN:
        cout << " логин пользователя" << endl;
        break;
    case DBI_USER_NAME:
        cout << " полное имя пользователя" << endl;
        break;
    case DBI_USER_AVATAR:
        cout << " аватар пользователя" << endl;
        break;
    case DBI_USER_PASSWD:
        cout << " хеш пароля пользователя" << endl;
        break;

// проекты
    case DBI_PROJ_NAME:
        cout << " имя проекта" << endl;
        break;
    case DBI_PROJ_PASSWD:
        cout << " хеш пароля проекта" << endl;
        break;
    case DBI_PROJ_DATA_DIR:
        cout << " папка для сохранения файлов" << endl;
        break;
    case DBI_PROJ_OPTIONS:
        cout << " опции проекта" << endl;
        break;

// приёмники
    case DBI_RCV_NAME:
        cout << " имя приёмника" << endl;
        break;
    case DBI_RCV_CHN_NAME:
        cout << " имя канала приёмника" << endl;
        break;
    default:
        break;
    }

    dumpArray(buf, nb, arItems, 32);
    cout << "<<< Конец массива" << endl;
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
        *buf += 4;
        cout << hex << value << " - версия DB API" << endl;
        break;
    case DBI_SFLAGS:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - системные флаги" << endl;
        break;
    case DBI_UFLAGS:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - пользовательские флаги" << endl;
        break;
    case DBI_UIN:
        value = *((long *) *buf);
        *buf += 8;
        cout << hex << value << " - Уникальный номер" << endl;
        break;
    case DBI_UID:
        value = *((long *) *buf);
        *buf += 8;
        cout << hex << value << " - Уникальный идентификатор" << endl;
        break;
    case DBI_PROJECTID:
        value = *((long *) *buf);
        *buf += 8;
        cout << hex << value << " - Уникальный идентификатор проекта" << endl;
        break;
    case DBI_SCANID:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - Идентификатор сканирования" << endl;
        break;
    case DBI_FMIN:
//        value = *((double *) *buf);
        printf("%lf - Начальная частота (МГц)\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - Начальная частота (МГц)" << endl;
        break;
    case DBI_FMAX:
//        value = *((double *) *buf);
        printf("%lf - Конечная частота (МГц)\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - Конечная частота (МГц)" << endl;
        break;
    case DBI_FCUR:
        value = *((double *) *buf);
        *buf += 8;
        cout << hex << value << " - Центральная частота (МГц)" << endl;
        break;
    case DBI_BAND:
        value = *((double *) *buf);
        *buf += 8;
        cout << hex << value << " - полоса (МГц)" << endl;
        break;
    case DBI_GFMIN:
 //       value = *((double *) *buf);
        printf("%lf - общая начальная частота (МГц)\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - общая начальная частота (МГц)" << endl;
        break;
    case DBI_GFMAX:
//        value = *((double *) *buf);
        printf("%lf - общая конечная частота (МГц)\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - общая конечная частота (МГц)" << endl;
        break;
    case DBI_FDIFF:
        value = *((double *) *buf);
        *buf += 8;
        cout << hex << value << " - отклонение частоты (МГц)" << endl;
        break;

    case DBI_COUNT:
        value = *((int *) *buf);
        *buf += 4;
        cout << hex << value << " - число выборок в данном сканировании" << endl;
        break;
    case DBI_SAMPLES:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - число отсчётов в каждой выборке" << endl;
        break;
    case DBI_TOTAL_SAMPLES:
        value = *((long *) *buf);
        *buf += 8;
        cout << hex << value << " - общее число отсчётов" << endl;
        break;
    case DBI_RBW_KHZ:
//        value = *((unsigned short *) *buf);
        printf("%6u - rbw в кГц\n", *((unsigned short *) *buf));
        *buf += 2;
//        cout << hex << value << " - rbw в кГц" << endl;
        break;

    case DBI_NPACK:
        value = *((int *) *buf);
        *buf += 4;
        cout << hex << value << " - номер выборки в пачке" << endl;
        break;
    case DBI_NPACKS:
        value = *((int *) *buf);
        *buf += 4;
        cout << hex << value << " - всего выборок в пачке" << endl;
        break;
    case DBI_PEAK_MAX:
        value = *((double *) *buf);
        *buf += 8;
        cout << hex << value << " - максимум пик-детектора" << endl;
        break;
    case DBI_PEAK_MEAN:
        value = *((double *) *buf);
        *buf += 8;
        cout << hex << value << " - среднее пик-детектора" << endl;
        break;

    case DBI_STIME:
//        value = *((long *) *buf);
//        printf("Время начала сканирования: %s", ctime((time_t *) *buf));
        dumpTimeStamp(buf, "Время начала сканирования");
//        *buf += 8;
//        cout << hex << value << " - время начала сканирования" << endl;
        break;
    case DBI_ETIME:
//        value = *((long *) *buf);
        dumpTimeStamp(buf, "Время конца сканирования");
//        printf("Время конца сканирования: %s", ctime((time_t *) *buf));
//        *buf += 8;
//        cout << hex << value << " - время конца сканирования" << endl;
        break;
    case DBI_CTIME:
//        value = *((unsigned int *) *buf);
        printf("%ui - время получения выборки\n", *((unsigned int *) *buf));
        *buf += 4;
//        cout << hex << value << " - время получения выборки" << endl;
        break;

    case DBI_INDEX:
//        value = *((int *) *buf);
        printf("%i - номер выборки\n", *((int *) *buf));
        *buf += 4;
//        cout << hex << value << " - номер выборки" << endl;
        break;
    case DBI_OFFSET:
//        value = *((long *) *buf);
        printf("%li - смещение выборки в файле\n", *((long *) *buf));
        *buf += 8;
//        cout << hex << value << " - смещение выборки в файле" << endl;
        break;
    case DBI_SIZE:
        value = *((int *) *buf);
        *buf += 4;
        cout << hex << value << " - размер выборки в файле" << endl;
        break;

     case DBI_DATA_GAIN:
        value = *((double *) *buf);
        *buf += 8;
        cout << hex << value << " - множитель для перевода FFT в _f64" << endl;
        break;
     case DBI_DATA_OFFSET:
//        value = *((double *) *buf);
        printf("%lf - смещение для перевода FFT в _f64\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - смещение для перевода FFT в _f64" << endl;
        break;
     case DBI_IQDATA_GAIN:
//        value = *((double *) *buf);
        printf("%lf - множитель для перевода IQ в _f64\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - множитель для перевода IQ в _f64" << endl;
        break;
     case DBI_IQDATA_OFFSET:
//        value = *((double *) *buf);
        printf("%lf - смещение для перевода IQ в _f64\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - смещение для перевода IQ в _f64" << endl;
        break;
     case DBI_ODATA_GAIN:
//        value = *((double *) *buf);
        printf("%lf - множитель для перевода LF в _f64\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - множитель для перевода LF в _f64" << endl;
        break;
     case DBI_ODATA_OFFSET:
//        value = *((double *) *buf);
        printf("%lf - смещение для перевода LF в _f64\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - смещение для перевода LF в _f64" << endl;
        break;

     case DBI_X:
        value = *((int *) *buf);
        *buf += 4;
        cout << hex << value << " - положение по горизонтали" << endl;
        break;
     case DBI_Y:
        value = *((int *) *buf);
        *buf += 4;
        cout << hex << value << " - положение по вертикали" << endl;
        break;
     case DBI_CX:
        value = *((int *) *buf);
        *buf += 4;
        cout << hex << value << " - размер по горизонтали" << endl;
        break;
     case DBI_CY:
        value = *((int *) *buf);
        *buf += 4;
        cout << hex << value << " - размер по вертикали" << endl;
        break;
    case DBI_STYPE:
        value = *((unsigned char *) *buf);
        *buf += 1;
        cout << hex << value << " - тип сигнала" << endl;
        break;
    case DBI_MTYPE:
        value = *((unsigned char *) *buf);
        *buf += 1;
        cout << hex << value << " - тип модуляции" << endl;
        break;
     case DBI_ACOUNT:
        value = *((short *) *buf);
        *buf += 2;
        cout << hex << value << " - счётчик активности" << endl;
        break;
     case DBI_TCOUNT:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - счётчик общего числа обнаружений" << endl;
        break;
     case DBI_NRCV:
        value = *((int *) *buf);
        *buf += 4;
        cout << hex << value << " - количество приёмников, на которых сигнал был найден" << endl;
        break;
     case DBI_CHANNEL:
        value = *((unsigned short *) *buf);
        *buf += 2;
        cout << hex << value << " - номер канала по стандарту" << endl;
        break;

     case DBI_CLVL:
        value = *((double *) *buf);
        *buf += 8;
        cout << hex << value << " - текущий уровень" << endl;
        break;
     case DBI_MLVL:
        value = *((double *) *buf);
        *buf += 8;
        cout << hex << value << " - максимальный уровень" << endl;
        break;
     case DBI_RLVL:
        value = *((double *) *buf);
        *buf += 8;
        cout << hex << value << " - опорный уровень" << endl;
        break;
     case DBI_NLVL:
        value = *((double *) *buf);
        *buf += 8;
        cout << hex << value << " - уровень шума" << endl;
        break;

     case DBI_AZIMUTH:
        value = *((short *) *buf);
        *buf += 2;
        cout << hex << value << " - азимут" << endl;
        break;
     case DBI_ELEVATION:
        value = *((short *) *buf);
        *buf += 2;
        cout << hex << value << " - угол места" << endl;
        break;
     case DBI_DTIME:
//        value = *((long *) *buf);
        dumpTimeStamp(buf, "Время обнаружения");
//        printf("Время обнаружения: %s", ctime((time_t *) *buf));
//        *buf += 8;
//        cout << hex << value << " - время обнаружения" << endl;
        break;
     case DBI_FTIME:
//        value = *((long *) *buf);
        dumpTimeStamp(buf, "Время первого появления");
//        printf("%li - время первого появления\n", *((long *) *buf));
//        *buf += 8;
//        cout << hex << value << " - время первого появления" << endl;
        break;
     case DBI_LTIME:
//        value = *((long *) *buf);
        dumpTimeStamp(buf, "Время последнего появления");
//        printf("%li - время последнего появления\n", *((long *) *buf));
//        *buf += 8;
//        cout << hex << value << " - время последнего появления" << endl;
        break;
     case DBI_MTIME:
//        value = *((long *) *buf);
        dumpTimeStamp(buf, "Время максимального уровня");
//        printf("%li - время максимального уровня\n", *((long *) *buf));
//        *buf += 8;
//        cout << hex << value << " - время максимального уровня" << endl;
        break;

     case DBI_VFILTER:
        value = *((unsigned short *) *buf);
        *buf += 2;
        cout << hex << value << " - видеофильтр" << endl;
        break;
     case DBI_RANGE_NUM:
//        value = *((unsigned short *) *buf);
        printf("%i - номер диапазона\n", *((unsigned short  *) *buf));
        *buf += 2;
//        cout << hex << value << " - номер диапазона" << endl;
        break;
     case DBI_RBW:
//        value = *((double *) *buf);
        printf("%f - разрешение Гц/отсчет\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - разрешение Гц/отсчет" << endl;
        break;
     case DBI_NOISE_S32:
//        value = *((int *) *buf);
        printf("%i - уровень шума дБм (32)\n", *((int *) *buf));
        *buf += 4;
//        cout << hex << value << " - уровень шума дБм" << endl;
        break;
     case DBI_NOISE_F64:
//        value = *((double *) *buf);
        printf("%f - уровень шума дБм (64)\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - уровень шума дБм" << endl;
        break;
     case DBI_BANDWIDTH:
        value = *((double *) *buf);
        *buf += 8;
        cout << hex << value << " - полоса сигнала Гц" << endl;
        break;

     case DBI_FLAGS:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - флаги" << endl;
        break;
     case DBI_GROUP1:
        value = *((int *) *buf);
        *buf += 4;
        cout << hex << value << " - ID группы 1" << endl;
        break;
     case DBI_MASK:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - маска" << endl;
        break;
     case DBI_GROUP2:
        value = *((int *) *buf);
        *buf += 4;
        cout << hex << value << " - ID группы 2" << endl;
        break;

// Opt структура
     case DBI_AMPL:
        value = *((double *) *buf);
        *buf += 8;
        cout << hex << value << " - Амплитуда" << endl;
        break;
     case DBI_ATTEN:
        value = *((double *) *buf);
        *buf += 8;
        cout << hex << value << " - аттенюатор" << endl;
        break;
     case DBI_REF_LEVEL:
        value = *((double *) *buf);
        *buf += 8;
        cout << hex << value << " - опорный уровень" << endl;
        break;
     case DBI_NSAMPLES:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - количество отсчетов" << endl;
        break;
     case DBI_BSAMPLES:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - количество отсчетов в полосе" << endl;
        break;
     case DBI_VFMIN:
        value = *((double *) *buf);
        *buf += 8;
        cout << hex << value << " - минимальная видимая граница частот" << endl;
        break;
     case DBI_VFMAX:
        value = *((double *) *buf);
        *buf += 8;
        cout << hex << value << " - максимальная видимая граница частот" << endl;
        break;
     case DBI_AVGNUM:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - число усреднений" << endl;
        break;
     case DBI_AVGTYPE:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - тип усреднения" << endl;
        break;
     case DBI_FFTWIN:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - тип окна БПФ" << endl;
        break;
     case DBI_DBW:
        value = *((double *) *buf);
        *buf += 8;
        cout << hex << value << " - ширина полосы демодуляции" << endl;
        break;
     case DBI_VBW:
        value = *((double *) *buf);
        *buf += 8;
        cout << hex << value << " - разрешение по частоте" << endl;
        break;
     case DBI_BW:
        value = *((double *) *buf);
        *buf += 8;
        cout << hex << value << " - ширина полосы" << endl;
        break;
     case DBI_THRW:
//        value = *((double *) *buf);
        printf("%lf - порог водопада\n", *((double *) *buf));
        *buf += 8;
//        cout << value << " - порог водопада" << endl;
        break;
     case DBI_THRR:
//        value = *((double *) *buf);
        printf("%lf - порог записи\n", *((double *) *buf));
        *buf += 8;
        break;
     case DBI_THRS:
//        value = *((double *) *buf);
        printf("%lf - порог обнаружения относительно уровня шума\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - порог обнаружения относительно уровня шума" << endl;
        break;
     case DBI_THR_TYPE:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - тип порога записи" << endl;
        break;
     case DBI_THR_APASS:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - число превышений для активности" << endl;
        break;
     case DBI_THR_IAPASS:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - число проходов без превышения для неактивности" << endl;
        break;
     case DBI_SCALE:
        value = *((double *) *buf);
        *buf += 8;
        cout << hex << value << " - масштаб по оси частот" << endl;
        break;
     case DBI_SOD_SCALE:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - режим выбора границ спектра осциллографа детектора" << endl;
        break;
     case DBI_DMD_TYPE:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - тип демодулятора" << endl;
        break;
     case DBI_DBANDWIDTH:
        value = *((double *) *buf);
        *buf += 8;
        cout << hex << value << " - полоса демодулятора" << endl;
        break;
     case DBI_YFMIN:
        value = *((double *) *buf);
        *buf += 8;
        cout << hex << value << " - Нижняя граница спектра" << endl;
        break;
     case DBI_YFMAX:
        value = *((double *) *buf);
        *buf += 8;
        cout << hex << value << " - Верхняя граница спектра" << endl;
        break;
     case DBI_TGRAM_MIN:
        value = *((double *) *buf);
        *buf += 8;
        cout << hex << value << " - Нижняя граница топограмы" << endl;
        break;
     case DBI_TGRAM_MAX:
        value = *((double *) *buf);
        *buf += 8;
        cout << hex << value << " - Верхняя граница топограмы" << endl;
        break;
     case DBI_TRACES:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - флаги трасс" << endl;
        break;
// каналы
     case DBI_CHAN_ASTATES:
        value = *((int *) *buf);
        *buf += 4;
        cout << hex << value << " - количество состояний каналов" << endl;
        break;
     case DBI_CHAN_NPARTS:
        value = *((int *) *buf);
        *buf += 4;
        cout << hex << value << " - количество частей столбца" << endl;
        break;
// пользователи
     case DBI_USER_ID:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - ID пользователя" << endl;
        break;
// проекты
     case DBI_PROJ_FLAGS:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - флаги проекта" << endl;
        break;
     case DBI_PROJ_CREATED:
        value = *((long *) *buf);
        *buf += 8;
        cout << hex << value << " - когда создан" << endl;
        break;
     case DBI_PROJ_CREATED_BY:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - кем создан" << endl;
        break;
     case DBI_PROJ_OPENED:
        value = *((long *) *buf);
        *buf += 8;
        cout << hex << value << " - когда открыт последний раз" << endl;
        break;
     case DBI_PROJ_OPENED_BY:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - кем открыт последний раз" << endl;
        break;
     case DBI_PROJ_DEF_RCV:
        value = *((int *) *buf);
        *buf += 4;
        cout << hex << value << " - приёмник по умолчанию (панорама)" << endl;
        break;
     case DBI_PROJ_DEF_ARCV:
        value = *((int *) *buf);
        *buf += 4;
        cout << hex << value << " - приёмник по умолчанию (панорама)" << endl;
        break;
// приёмники
     case DBI_RCV_FLAGS:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - флаги приёмника" << endl;
        break;
     case DBI_RCV_COLOR:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - цвет приёмника" << endl;
        break;
     case DBI_RCV_CHN_CVR_UIN:
        value = *((unsigned long *) *buf);
        *buf += 8;
        cout << hex << value << " - ID конвертера канала приёмника" << endl;
        break;
     case DBI_RCV_CHN_FLAGS:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - флаги канала приёмника" << endl;
        break;
// правила
     case DBI_RULE_FREQ_USE:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - использование границ частоты" << endl;
        break;
     case DBI_RULE_BAND_USE:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - использование границ полосы" << endl;
        break;
     case DBI_RULE_REFD_USE:
        value = *((int *) *buf);
        *buf += 4;
        cout << hex << value << " - использование опорного уровня" << endl;
        break;
     case DBI_RULE_STAT_USE:
        value = *((int *) *buf);
        *buf += 4;
        cout << hex << value << " - использование стационарности" << endl;
        break;
     case DBI_RULE_LAST_USE:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - использование последнего времени" << endl;
        break;
#define DBI_RULE_DESC_USE	(0x00000143|DBIT_U32)	// использование нового описания
     case DBI_RULE_DESC_USE:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - использование нового описания" << endl;
        break;
// сигналы/связи
     case DBI_SGN_COUNT:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - количество сигналов" << endl;
        break;
     case DBI_LNK_COUNT:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - количество связей" << endl;
        break;
     case DBI_NET_COUNT:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - количество связей" << endl;
        break;
     case DBI_TYPE:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - логический тип устройства / тип сигнала" << endl;
        break;
     case DBI_STATE:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - дополнительные данные о состоянии" << endl;
        break;
     case DBI_DEV_CHANEL:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - дополнительные данные о состоянии" << endl;
        break;
     case DBI_BT_FEAT:
        value = *((unsigned int *) *buf);
        *buf += 4;
        cout << hex << value << " - особенности Bluetooth" << endl;
        break;
     case DBI_ID:
        value = *((unsigned long *) *buf);
        *buf += 8;
        cout << hex << value << " - идентификатор" << endl;
        break;
     case DBI_ID2:
        value = *((unsigned long *) *buf);
        *buf += 8;
        cout << hex << value << " - идентификатор 2" << endl;
        break;
     case DBI_ID3:
        value = *((unsigned long *) *buf);
        *buf += 8;
        cout << hex << value << " - идентификатор 3" << endl;
        break;
     case DBI_ID4:
        value = *((unsigned long *) *buf);
        *buf += 8;
        cout << hex << value << " - идентификатор 4" << endl;
        break;
     case DBI_DATA_TX:
        value = *((unsigned long *) *buf);
        *buf += 8;
        cout << hex << value << " - передано" << endl;
        break;
     case DBI_DATA_RX:
        value = *((unsigned long *) *buf);
        *buf += 8;
        cout << hex << value << " - принято" << endl;
        break;
     case DBI_BTS_IMEI:
        value = *((unsigned long *) *buf);
        *buf += 8;
        cout << hex << value << " - IMEI" << endl;
        break;

     case DBI_DEV_TYPE:
        value = *((int *) *buf);
        *buf += 4;
        cout << hex << value << " - тип устройства" << endl;
        break;
     case DBI_LINKS:
        value = *((int *) *buf);
        *buf += 4;
        cout << hex << value << " - количество связей" << endl;
        break;

     case DBI_WF_STD:
        value = *((unsigned short *) *buf);
        *buf += 2;
        cout << hex << value << " - стандарт WiFi" << endl;
        break;
     case DBI_WF_SEC:
        value = *((unsigned short *) *buf);
        *buf += 2;
        cout << hex << value << " - безопасность WiFi" << endl;
        break;
     case DBI_ZB_PAN:
        value = *((unsigned short *) *buf);
        *buf += 2;
        cout << hex << value << " - ID сети ZigBee" << endl;
        break;
     case DBI_CELL_LAC:
        value = *((unsigned short *) *buf);
        *buf += 2;
        cout << hex << value << " - LAC" << endl;
        break;
     case DBI_CELL_BSIC:
        value = *((unsigned short *) *buf);
        *buf += 2;
        cout << hex << value << " - BSIC" << endl;
        break;
     case DBI_BTS_MCC:
        value = *((unsigned short *) *buf);
        *buf += 2;
        cout << hex << value << " - MCC" << endl;
        break;
     case DBI_BTS_MNC:
        value = *((unsigned short *) *buf);
        *buf += 2;
        cout << hex << value << " - MNC" << endl;
        break;
     case DBI_EOF:
        value = *((unsigned char *) *buf);
        *buf += 1;
        cout << hex << value << " - конец файла" << endl;
        break;
    default:
        unsigned int nb = (varType >> 24) & 0x0F;
        *buf += nb;
        cout << " - ????? " << hex << varType<< endl;
        break;
    }

    return true;
}
