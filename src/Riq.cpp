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

void fft_videofilter(_f64* S_in, _f64* S_out, int block_size, int blocks_num, int video_filter)
{
//	int i;
	_f64* vf_coeff;
//	_f64 wnd_mean;

	if (video_filter > 1) {
		// coefficients generation
		video_filter |= 1; // must be odd
//		vf_coeff = (_f64*)cp_mzalloc(video_filter*sizeof(_f64));
		vf_coeff = (_f64*)malloc(video_filter*sizeof(_f64));

		// fill coefficients
//		wnd_mean = 0;
//		for (i = 0; i < (_s32)video_filter; i++){
//			vf_coeff[i] = exp(-0.5*pow((i-(video_filter>>1))/0.3/(video_filter>>1),2));
//			wnd_mean += vf_coeff[i];
//		}
//		for (i = 0; i < video_filter; i++) vf_coeff[i] /= wnd_mean;
//
//		while (blocks_num--) {
//			vfilter_f64(S_in, block_size, vf_coeff, video_filter, S_out);
//
//			// increment pointers
//			S_in += block_size;
//			S_out += block_size;
//		}
//
//		// free memory
		if (vf_coeff) free(vf_coeff);

	} else {
//		cp_memcpy(S_out,S_in,block_size*blocks_num*sizeof(_f64));
//		wmemcpy(S_out,S_in,block_size*blocks_num*sizeof(_f64));
	}
}

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

void dump_s32(char** buf, const char* msg)
{
    printf("%i\t- %s\n", *((_s32 *) *buf), msg);
    *buf += 4;
}

void dump_f64(char** buf, const char* msg)
{
    printf("%lf\t- %s\n", *((_f64 *) *buf), msg);
    *buf += 8;
}

void dumpHex64(char** buf, const char* msg)
{
    printf("%16lx\t- %s\n", *((_u64 *) *buf), msg);
    *buf += 8;
}

void dumpHex32(char** buf, const char* msg)
{
    printf("%8x\t- %s\n", *((_u32 *) *buf), msg);
    *buf += 4;
}

void dumpHex8(char** buf, const char* msg)
{
    printf("%2x\t- %s\n", *((_u8 *) *buf), msg);
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
        dumpHex32(buf, "версия DB API");
//        value = *((int *) *buf);
//        *buf += 4;
////        cout << hex << value << " - версия DB API" << endl;
//        printf("%8lx - версия DB API\n", value);
        break;
    case DBI_SFLAGS:
        dumpHex32(buf, "системные флаги");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
//        printf("%8lx - системные флаги\n", value);
////        cout << hex << value << " - системные флаги" << endl;
        break;
    case DBI_UFLAGS:
        dumpHex32(buf, "пользовательские флаги");
//        value = *((unsigned int *) *buf);
//        *buf += 4;
////        cout << hex << value << " - пользовательские флаги" << endl;
//        printf("%8lx - пользовательские флаги\n", value);
        break;
    case DBI_UIN:
        dumpHex64(buf, "Уникальный номер");
//        value = *((long *) *buf);
//        *buf += 8;
////        cout << hex << value << " - Уникальный номер" << endl;
//        printf("%16lx - Уникальный номер\n", value);
        break;
    case DBI_UID:
        dumpHex64(buf, "Уникальный идентификатор");
//        value = *((long *) *buf);
//        *buf += 8;
////        cout << hex << value << " - Уникальный идентификатор" << endl;
//        printf("%16lx - Уникальный идентификатор\n", value);
        break;
    case DBI_PROJECTID:
        dumpHex64(buf, "Уникальный идентификатор проекта");
//        value = *((long *) *buf);
//        *buf += 8;
////        cout << hex << value << " - Уникальный идентификатор проекта" << endl;
//        printf("%16lx - Уникальный идентификатор проекта\n", value);
        break;
    case DBI_SCANID:
        dumpHex32(buf, "Идентификатор сканирования");
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
        value = *((int *) *buf);
        *buf += 4;
//        cout << hex << value << " - число выборок в данном сканировании" << endl;
        printf("%8lx - число выборок в данном сканировании\n", value);
        break;
    case DBI_SAMPLES:
        value = *((unsigned int *) *buf);
        *buf += 4;
//        cout << hex << value << " - число отсчётов в каждой выборке" << endl;
        printf("%8lx - число отсчётов в каждой выборке\n", value);
        break;
    case DBI_TOTAL_SAMPLES:
        value = *((long *) *buf);
        *buf += 8;
//        cout << hex << value << " - общее число отсчётов" << endl;
        printf("%16lx - общее число отсчётов\n", value);
        break;
    case DBI_RBW_KHZ:
        printf("%6u - rbw в кГц\n", *((unsigned short *) *buf));
        *buf += 2;
        break;

    case DBI_NPACK:
        value = *((int *) *buf);
        *buf += 4;
//        cout << hex << value << " - номер выборки в пачке" << endl;
        printf("%8lx - номер выборки в пачке\n", value);
        break;
    case DBI_NPACKS:
        value = *((int *) *buf);
        *buf += 4;
//        cout << hex << value << " - всего выборок в пачке" << endl;
        printf("%8lx - всего выборок в пачке\n", value);
        break;
    case DBI_PEAK_MAX:
        printf("%lf - максимум пик-детектора\n", *((double *) *buf));
        *buf += 8;
        break;
    case DBI_PEAK_MEAN:
        printf("%lf - среднее пик-детектора\n", *((double *) *buf));
        *buf += 8;
        break;

    case DBI_STIME:
        dumpTimeStamp(buf, "Время начала сканирования");
        break;
    case DBI_ETIME:
        dumpTimeStamp(buf, "Время конца сканирования");
        break;
    case DBI_CTIME:
        printf("%ui - время получения выборки\n", *((unsigned int *) *buf));
        *buf += 4;
        break;

    case DBI_INDEX:
        printf("%i - номер выборки\n", *((int *) *buf));
        *buf += 4;
        break;
    case DBI_OFFSET:
        printf("%li - смещение выборки в файле\n", *((_s64 *) *buf));
        *buf += 8;
        break;
    case DBI_SIZE:
        printf("%i - размер выборки в файле\n", *((_u32 *) *buf));
        *buf += 4;
        break;

     case DBI_DATA_GAIN:
        printf("%lf - множитель для перевода FFT в _f64\n", *((double *) *buf));
        *buf += 8;
        break;
     case DBI_DATA_OFFSET:
        printf("%lf - смещение для перевода FFT в _f64\n", *((double *) *buf));
        *buf += 8;
        break;
     case DBI_IQDATA_GAIN:
        printf("%lf - множитель для перевода IQ в _f64\n", *((double *) *buf));
        *buf += 8;
        break;
     case DBI_IQDATA_OFFSET:
        printf("%lf - смещение для перевода IQ в _f64\n", *((double *) *buf));
        *buf += 8;
        break;
     case DBI_ODATA_GAIN:
        printf("%lf - множитель для перевода LF в _f64\n", *((double *) *buf));
        *buf += 8;
        break;
     case DBI_ODATA_OFFSET:
        printf("%lf - смещение для перевода LF в _f64\n", *((double *) *buf));
        *buf += 8;
        break;

     case DBI_X:
        value = *((int *) *buf);
        *buf += 4;
//        cout << hex << value << " - положение по горизонтали" << endl;
        printf("%8lx - положение по горизонтали\n", value);
        break;
     case DBI_Y:
        value = *((int *) *buf);
        *buf += 4;
//        cout << hex << value << " - положение по вертикали" << endl;
        printf("%8lx - положение по вертикали\n", value);
        break;
     case DBI_CX:
        value = *((int *) *buf);
        *buf += 4;
//        cout << hex << value << " - размер по горизонтали" << endl;
        printf("%8lx - размер по горизонтали\n", value);
        break;
     case DBI_CY:
        value = *((int *) *buf);
        *buf += 4;
//        cout << hex << value << " - размер по вертикали" << endl;
        printf("%8lx - размер по вертикали\n", value);
        break;
    case DBI_STYPE:
        value = *((unsigned char *) *buf);
        *buf += 1;
//        cout << hex << value << " - тип сигнала" << endl;
        printf("%8lx - тип сигнала\n", value);
        break;
    case DBI_MTYPE:
        value = *((unsigned char *) *buf);
        *buf += 1;
//        cout << hex << value << " - тип модуляции" << endl;
        printf("%2lx - тип модуляции\n", value);
        break;
     case DBI_ACOUNT:
        value = *((short *) *buf);
        *buf += 2;
//        cout << hex << value << " - счётчик активности" << endl;
        printf("%4lx - счётчик активности\n", value);
        break;
     case DBI_TCOUNT:
        value = *((unsigned int *) *buf);
        *buf += 4;
//        cout << hex << value << " - счётчик общего числа обнаружений" << endl;
        printf("%8lx - счётчик общего числа обнаружений\n", value);
        break;
     case DBI_NRCV:
        value = *((int *) *buf);
        *buf += 4;
//        cout << hex << value << " - количество приёмников, на которых сигнал был найден" << endl;
        printf("%8lx - количество приёмников, на которых сигнал был найден\n", value);
        break;
     case DBI_CHANNEL:
        value = *((unsigned short *) *buf);
        *buf += 2;
        cout << hex << value << " - номер канала по стандарту" << endl;
        break;

     case DBI_CLVL:
//        value = *((double *) *buf);
        printf("%lf - текущий уровень\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - текущий уровень" << endl;
        break;
     case DBI_MLVL:
//        value = *((double *) *buf);
        printf("%lf - максимальный уровень\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - максимальный уровень" << endl;
        break;
     case DBI_RLVL:
//        value = *((double *) *buf);
        printf("%lf - опорный уровень\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - опорный уровень" << endl;
        break;
     case DBI_NLVL:
//        value = *((double *) *buf);
        printf("%lf - уровень шума\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - уровень шума" << endl;
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
//        value = *((double *) *buf);
        printf("%lf - полоса сигнала Гц\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - полоса сигнала Гц" << endl;
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
//        value = *((double *) *buf);
        printf("%lf - Амплитуда\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - Амплитуда" << endl;
        break;
     case DBI_ATTEN:
//        value = *((double *) *buf);
        printf("%lf - аттенюатор\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - аттенюатор" << endl;
        break;
     case DBI_REF_LEVEL:
//        value = *((double *) *buf);
        printf("%lf - опорный уровень\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - опорный уровень" << endl;
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
//        value = *((double *) *buf);
        printf("%lf - минимальная видимая граница частот\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - минимальная видимая граница частот" << endl;
        break;
     case DBI_VFMAX:
//        value = *((double *) *buf);
        printf("%lf - максимальная видимая граница частот\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - максимальная видимая граница частот" << endl;
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
//        value = *((double *) *buf);
        printf("%lf - ширина полосы демодуляции\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - ширина полосы демодуляции" << endl;
        break;
     case DBI_VBW:
//        value = *((double *) *buf);
        printf("%lf - разрешение по частоте\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - разрешение по частоте" << endl;
        break;
     case DBI_BW:
//        value = *((double *) *buf);
        printf("%lf - ширина полосы\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - ширина полосы" << endl;
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
//        value = *((double *) *buf);
        printf("%lf - масштаб по оси частот\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - масштаб по оси частот" << endl;
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
//        value = *((double *) *buf);
        printf("%lf - полоса демодулятора\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - полоса демодулятора" << endl;
        break;
     case DBI_YFMIN:
//        value = *((double *) *buf);
        printf("%lf - Нижняя граница спектра\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - Нижняя граница спектра" << endl;
        break;
     case DBI_YFMAX:
//        value = *((double *) *buf);
        printf("%lf - Верхняя граница спектра\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - Верхняя граница спектра" << endl;
        break;
     case DBI_TGRAM_MIN:
//        value = *((double *) *buf);
        printf("%lf - Нижняя граница топограмы\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - Нижняя граница топограмы" << endl;
        break;
     case DBI_TGRAM_MAX:
//        value = *((double *) *buf);
        printf("%lf - Верхняя граница топограмы\n", *((double *) *buf));
        *buf += 8;
//        cout << hex << value << " - Верхняя граница топограмы" << endl;
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
