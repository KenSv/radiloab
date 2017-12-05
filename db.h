#pragma once
//---------------------------------------------------------------------
//#if !defined(_WIN32) && !defined(_LINUX)
#if !defined(_WIN32) && !defined(__linux)
#error "OS not specified!"
#endif
//---------------------------------------------------------------------
// ������� ���� - ���
#define DBIT_ARRAY			0x10000000	// ������
#define DBIT_ARRAY2			0x20000000	// 2D ������
#define DBIT_ARRAY3			0x30000000	// 3D ������
#define DBIT_INT			0x40000000	// �������������
#define DBIT_UNSIGNED		0x80000000	// �����������

#define DBIT_S8				(0x01000000|DBIT_INT)
#define DBIT_U8				(DBIT_S8|DBIT_UNSIGNED)
#define DBIT_AS8			(DBIT_S8|DBIT_ARRAY)
#define DBIT_AU8			(DBIT_S8|DBIT_UNSIGNED|DBIT_ARRAY)

#define DBIT_S16			(0x02000000|DBIT_INT)
#define DBIT_U16			(DBIT_S16|DBIT_UNSIGNED)
#define DBIT_AS16			(DBIT_S16|DBIT_ARRAY)
#define DBIT_AU16			(DBIT_S16|DBIT_UNSIGNED|DBIT_ARRAY)

#define DBIT_S32			(0x04000000|DBIT_INT)
#define DBIT_U32			(DBIT_S32|DBIT_UNSIGNED)
#define DBIT_AS32			(DBIT_S32|DBIT_ARRAY)
#define DBIT_AU32			(DBIT_S32|DBIT_UNSIGNED|DBIT_ARRAY)

#define DBIT_S64			(0x08000000|DBIT_INT)
#define DBIT_U64			(DBIT_S64|DBIT_UNSIGNED)
#define DBIT_AS64			(DBIT_S64|DBIT_ARRAY)
#define DBIT_AU64			(DBIT_S64|DBIT_UNSIGNED|DBIT_ARRAY)

#define DBIT_F32			0x04000000
#define DBIT_AF32			(DBIT_F32|DBIT_ARRAY)

#define DBIT_F64			0x08000000
#define DBIT_AF64			(DBIT_F64|DBIT_ARRAY)
#define DBIT_A2F64			(DBIT_F64|DBIT_ARRAY2)
//---------------------------------------------------------------------
#define DBI_EOF				0						// ����� �����
#define DBI_NULL			(0x00000000|DBIT_AU8)	// ������ ������
#define DBI_VERSION			(0x00000001|DBIT_U32)	// ������ DB API
#define DBI_SFLAGS			(0x00000002|DBIT_U32)	// ��������� �����
#define DBI_UFLAGS			(0x00000003|DBIT_U32)	// ���������������� �����

#define DBI_UIN				(0x00000008|DBIT_U64)	// ���������� �����
#define DBI_UID				(0x00000009|DBIT_U64)	// ���������� �������������
#define DBI_PROJECTID		(0x0000000A|DBIT_U64)	// ���������� ������������� �������
#define DBI_SCANID			(0x0000000B|DBIT_U32)	// ������������� ������������

#define DBI_FMIN			(0x00000010|DBIT_F64)	// ��������� ������� (���)
#define DBI_FMAX			(0x00000011|DBIT_F64)	// �������� ������� (���)
#define DBI_FCUR			(0x00000012|DBIT_F64)	// ����������� ������� (���)
#define DBI_BAND			(0x00000013|DBIT_F64)	// ������ (���)
#define DBI_GFMIN			(0x00000014|DBIT_F64)	// ����� ��������� ������� (���)
#define DBI_GFMAX			(0x00000015|DBIT_F64)	// ����� �������� ������� (���)
#define DBI_FDIFF			(0x00000016|DBIT_F64)	// ���������� ������� (���)

#define DBI_COUNT			(0x00000018|DBIT_S32)	// ����� ������� � ������ ������������ ??? skn ����� ������� �� ������ ???
#define DBI_SAMPLES			(0x00000019|DBIT_U32)	// ����� �������� � ������ �������
#define DBI_TOTAL_SAMPLES	(0x00000019|DBIT_U64)	// ����� ����� ��������
#define DBI_RBW_KHZ			(0x00000020|DBIT_U16)	// rbw � ���

#define DBI_IQDATA			0x00000020
#define DBI_FFT				0x00000022
#define DBI_TGRAM			0x00000023
#define DBI_ODATA			0x00000024

#define DBI_IQDATA_S16		(DBI_IQDATA|DBIT_AS16)	// Q-����� (_s16)
#define DBI_IQDATA_F64		(DBI_IQDATA|DBIT_AF64)	// IQ-������ (_f64)
#define DBI_ODATA_S16		(DBI_ODATA|DBIT_AS16)	// ����������� (_s16)
#define DBI_ODATA_F64		(DBI_ODATA|DBIT_AF64)	// ����������� (_f64)

#define DBI_FFT_F64			(DBI_FFT|DBIT_AF64)		// ������ (_f64)
#define DBI_FFT_U16			(DBI_FFT|DBIT_AU16)		// ������ (_s16)
#define DBI_FFT_U8			(DBI_FFT|DBIT_AU8)		// ������ (_u8)
#define DBI_FFT_F64_2D		(DBI_FFT|DBIT_A2F64)	// 2D ������ (_f64)

#define DBI_TGRAM_F64		(DBI_TGRAM|DBIT_A2F64)	// 2D ��������� (_f64)

#define DBI_NPACK			(0x00000023|DBIT_S32)	// ����� ������� � �����
#define DBI_NPACKS			(0x00000024|DBIT_S32)	// ����� ������� � �����

#define DBI_PEAK_MAX		(0x00000025|DBIT_F64)	// �������� ���-���������
#define DBI_PEAK_MEAN		(0x00000026|DBIT_F64)	// ������� ���-���������

#define DBI_STIME			(0x00000028|DBIT_S64)	// ����� ������ ������������
#define DBI_ETIME			(0x00000029|DBIT_S64)	// ����� ����� ������������
#define DBI_CTIME			(0x0000002A|DBIT_U32)	// ����� ��������� �������

#define DBI_INDEX			(0x00000030|DBIT_S32)	// ����� �������
#define DBI_OFFSET			(0x00000031|DBIT_S64)	// �������� ������� � �����
#define DBI_SIZE			(0x00000032|DBIT_U32)	// ������ ������� � �����

#define DBI_DATA_GAIN		(0x00000034|DBIT_F64)	// ��������� ��� �������� FFT � _f64
#define DBI_DATA_OFFSET		(0x00000035|DBIT_F64)	// �������� ��� �������� FFT � _f64
#define DBI_IQDATA_GAIN		(0x00000036|DBIT_F64)	// ��������� ��� �������� IQ � _f64
#define DBI_IQDATA_OFFSET	(0x00000037|DBIT_F64)	// �������� ��� �������� IQ � _f64
#define DBI_ODATA_GAIN		(0x00000038|DBIT_F64)	// ��������� ��� �������� LF � _f64
#define DBI_ODATA_OFFSET	(0x00000039|DBIT_F64)	// �������� ��� �������� LF � _f64

#define DBI_X				(0x0000003A|DBIT_S32)	// ��������� �� �����������
#define DBI_Y				(0x0000003B|DBIT_S32)	// ��������� �� ���������
#define DBI_CX				(0x0000003C|DBIT_S32)	// ������ �� �����������
#define DBI_CY				(0x0000003D|DBIT_S32)	// ������ �� ���������
#define DBI_BYTEARRAY		(0x0000003E|DBIT_AU8)	// ������ ������

#define DBI_STYPE			(0x00000040|DBIT_U8)	// ��� �������
#define DBI_MTYPE			(0x00000041|DBIT_U8)	// ��� ���������
#define DBI_ACOUNT			(0x00000042|DBIT_S16)	// ������� ����������
#define DBI_TCOUNT			(0x00000043|DBIT_U32)	// ������� ������ ����� �����������
#define DBI_NRCV			(0x00000044|DBIT_S32)	// ���������� ���������, �� ������� ������ ��� ������
#define DBI_DESC_S8			(0x00000045|DBIT_AS8)	// ��������
#define DBI_DESC_U16		(0x00000045|DBIT_AU16)	// ��������
#define DBI_FRAMES			(0x00000046|DBIT_AU32)	// ���� ������������� ������� � ������ ����
#define DBI_MD_NAME			(0x00000047|DBIT_AS8)	// ��� ����������� �����
#define DBI_CHANNEL			(0x00000049|DBIT_U16)	// ����� ������ �� ���������

#define DBI_CLVL			(0x00000050|DBIT_F64)	// ������� �������
#define DBI_MLVL			(0x00000051|DBIT_F64)	// ������������ �������
#define DBI_RLVL			(0x00000052|DBIT_F64)	// ������� �������
#define DBI_NLVL			(0x00000053|DBIT_F64)	// ������� ����

#define DBI_AZIMUTH			(0x00000052|DBIT_S16)	// ������
#define DBI_ELEVATION		(0x00000053|DBIT_S16)	// ���� �����

#define DBI_DTIME			(0x00000055|DBIT_S64)	// ����� �����������
#define DBI_FTIME			(0x00000056|DBIT_S64)	// ����� ������� ���������
#define DBI_LTIME			(0x00000057|DBIT_S64)	// ����� ���������� ���������
#define DBI_MTIME			(0x00000058|DBIT_S64)	// ����� ������������� ������

#define DBI_CHAN_FFT		(0x00000002|DBIT_A2F64)	// ��������� ������
#define DBI_SIGN_MASK 		(0x00000003|DBIT_AF64)	// ����� ���������
#define DBI_NAME_S8			(0x00000060|DBIT_AS8)	// ���
#define DBI_NAME_U16		(0x00000060|DBIT_AU16)	//
#define DBI_GROUPNAME		(0x00000061|DBIT_AU16)	// �������� ������ �������
#define DBI_VFILTER			(0x00000062|DBIT_U16)	// �����������
#define DBI_RANGE_NUM		(0x00000063|DBIT_U16)	// ����� ���������
#define DBI_RBW				(0x00000064|DBIT_F64)	// ���������� ��/������
#define DBI_NOISE_S32		(0x00000065|DBIT_S32)	// ������� ���� ���
#define DBI_NOISE_F64		(0x00000065|DBIT_F64)	// ������� ���� ���
#define DBI_BANDWIDTH		(0x00000066|DBIT_F64)	// ������ ������� ��
#define DBI_SUBGROUPNAME	(0x00000067|DBIT_AU16)	// �������� ���-������ �������

#define DBI_FLAGS			(0x0000006A|DBIT_U32)	// �����
#define DBI_GROUP1			(0x0000006A|DBIT_S32)	// ID ������ 1
#define DBI_MASK			(0x0000006B|DBIT_U32)	// �����
#define DBI_GROUP2			(0x0000006B|DBIT_S32)	// ID ������ 2

// Opt ���������
#define DBI_AMPL 			(0x00000070|DBIT_F64)	// ���������
#define DBI_ATTEN 			(0x00000071|DBIT_F64)	// ����������
#define DBI_REF_LEVEL 		(0x00000072|DBIT_F64)	// ������� �������
#define DBI_NSAMPLES		(0x00000075|DBIT_U32)	// ���������� ��������
#define DBI_BSAMPLES		(0x00000076|DBIT_U32)	// ���������� �������� � ������
#define DBI_VFMIN 			(0x00000077|DBIT_F64)	// ����������� ������� ������� ������
#define DBI_VFMAX 			(0x00000078|DBIT_F64)	// ������������ ������� ������� ������
#define DBI_AVGNUM			(0x00000079|DBIT_U32)	// ����� ����������
#define DBI_AVGTYPE			(0x0000007A|DBIT_U32)	// ��� ����������
#define DBI_FFTWIN			(0x0000007B|DBIT_U32)	// ��� ���� ���
#define DBI_DBW 			(0x0000007C|DBIT_F64)	// ������ ������ �����������
#define DBI_VBW 			(0x0000007D|DBIT_F64)	// ���������� �� �������
#define DBI_BW 				(0x0000007F|DBIT_F64)	// ������ ������
#define DBI_THRW			(0x00000080|DBIT_F64)	// ����� ��������
#define DBI_THRR			(0x00000081|DBIT_F64)	// ����� ������
#define DBI_THRR_OFFSETS	(0x00000081|DBIT_AF64)	// �������� ������ ������
#define DBI_THRS			(0x00000082|DBIT_F64)	// ����� ����������� ������������ ������ ����
#define DBI_THR_TYPE		(0x00000083|DBIT_U32)	// ��� ������ ������
#define DBI_THR_APASS		(0x00000085|DBIT_U32)	// ����� ���������� ��� ����������
#define DBI_THR_IAPASS		(0x00000086|DBIT_U32)	// ����� �������� ��� ���������� ��� ������������
#define DBI_SCALE			(0x00000087|DBIT_F64)	// ������� �� ��� ������
#define DBI_SOD_SCALE		(0x00000088|DBIT_U32)	// ����� ������ ������ ������� ������������ ���������
#define DBI_DMD_TYPE		(0x00000089|DBIT_U32)	// ��� ������������
#define DBI_DBANDWIDTH		(0x0000008A|DBIT_F64)	// ������ ������������
#define DBI_YFMIN 			(0x0000008B|DBIT_F64)	// ������ ������� �������
#define DBI_YFMAX 			(0x0000008C|DBIT_F64)	// ������� ������� �������
#define DBI_SPLITTERS		(0x0000008D|DBIT_AF32)	// ����������� ����
#define DBI_TGRAM_MIN 		(0x0000008E|DBIT_F64)	// ������ ������� ���������
#define DBI_TGRAM_MAX 		(0x0000008F|DBIT_F64)	// ������� ������� ���������
#define DBI_TRACES			(0x00000090|DBIT_U32)	// ����� �����

// ������
#define DBI_CHAN_STATES		(0x00000100|DBIT_AU64)	// ��������� �������
#define DBI_CHAN_ASTATES	(0x00000101|DBIT_S32)	// ���������� ��������� �������
#define DBI_CHAN_NPARTS		(0x00000105|DBIT_S32)	// ���������� ������ �������

// ������������
#define DBI_USER_ID			(0x00000110|DBIT_U32)	// ID ������������
#define DBI_USER_LOGIN		(0x00000110|DBIT_AS8)	// ����� ������������
#define DBI_USER_NAME		(0x00000111|DBIT_AS8)	// ������ ��� ������������
#define DBI_USER_AVATAR		(0x00000110|DBIT_AU32)	// ������ ������������
#define DBI_USER_PASSWD		(0x00000110|DBIT_AU8)	// ��� ������ ������������

// �������
#define DBI_PROJ_NAME		(0x00000120|DBIT_AS8)	// ��� �������
#define DBI_PROJ_PASSWD		(0x00000120|DBIT_AU8)	// ��� ������ �������
#define DBI_PROJ_FLAGS		(0x00000120|DBIT_U32)	// ����� �������
#define DBI_PROJ_CREATED	(0x00000120|DBIT_S64)	// ����� ������
#define DBI_PROJ_CREATED_BY	(0x00000121|DBIT_U32)	// ��� ������
#define DBI_PROJ_OPENED		(0x00000121|DBIT_S64)	// ����� ������ ��������� ���
#define DBI_PROJ_OPENED_BY	(0x00000122|DBIT_U32)	// ��� ������ ��������� ���
#define DBI_PROJ_DATA_DIR	(0x00000121|DBIT_AS8)	// ����� ��� ���������� ������
#define DBI_PROJ_DEF_RCV	(0x00000120|DBIT_S32)	// ������� �� ��������� (��������)
#define DBI_PROJ_DEF_ARCV	(0x00000121|DBIT_S32)	// ������� �� ��������� (��������)
#define DBI_PROJ_OPTIONS	(0x00000122|DBIT_AU8)	// ����� �������

// ��������
#define DBI_RCV_FLAGS		(0x00000130|DBIT_U32)	// ����� ��������
#define DBI_RCV_NAME		(0x00000130|DBIT_AS8)	// ��� ��������
#define DBI_RCV_COLOR		(0x00000131|DBIT_U32)	// ���� ��������
#define DBI_RCV_CHN_NAME	(0x00000132|DBIT_AS8)	// ��� ������ ��������
#define DBI_RCV_CHN_CVR_UIN	(0x00000132|DBIT_U64)	// ID ���������� ������ ��������
#define DBI_RCV_CHN_FLAGS	(0x00000132|DBIT_U32)	// ����� ������ ��������

// �������
#define DBI_RULE_FREQ_USE	(0x00000140|DBIT_U32)	// ������������� ������ �������
#define DBI_RULE_BAND_USE	(0x00000141|DBIT_U32)	// ������������� ������ ������
#define DBI_RULE_REFD_USE	(0x00000140|DBIT_S32)	// ������������� �������� ������
#define DBI_RULE_STAT_USE	(0x00000141|DBIT_S32)	// ������������� ��������������
#define DBI_RULE_LAST_USE	(0x00000142|DBIT_U32)	// ������������� ���������� �������
#define DBI_RULE_DESC_USE	(0x00000143|DBIT_U32)	// ������������� ������ ��������

// �������/�����
#define DBI_SGN_COUNT		(0x00000150|DBIT_U32)	// ���������� ��������
#define DBI_LNK_COUNT		(0x00000151|DBIT_U32)	// ���������� ������
#define DBI_NET_COUNT		(0x00000152|DBIT_U32)	// ���������� ������
#define DBI_TYPE			(0x00000153|DBIT_U32)	// ���������� ��� ���������� / ��� �������
#define DBI_STATE			(0x00000154|DBIT_U32)	// �������������� ������ � ���������
#define DBI_DEV_CHANEL		(0x00000155|DBIT_U32)	// �������������� ������ � ���������
#define DBI_BT_FEAT			(0x00000156|DBIT_U32)	// ����������� Bluetooth

#define DBI_ID				(0x00000150|DBIT_U64)	// �������������
#define DBI_ID2				(0x00000151|DBIT_U64)	// ������������� 2
#define DBI_ID3				(0x00000152|DBIT_U64)	// ������������� 3
#define DBI_ID4				(0x00000153|DBIT_U64)	// ������������� 4
#define DBI_DATA_TX			(0x00000154|DBIT_U64)	// ��������
#define DBI_DATA_RX			(0x00000155|DBIT_U64)	// �������
#define DBI_BTS_IMEI		(0x00000157|DBIT_U64)	// IMEI

#define DBI_DEV_TYPE		(0x00000150|DBIT_S32)	// ��� ����������
#define DBI_LINKS			(0x00000151|DBIT_S32)	// ���������� ������

#define DBI_WF_STD			(0x00000150|DBIT_U16)	// �������� WiFi
#define DBI_WF_SEC			(0x00000151|DBIT_U16)	// ������������ WiFi
#define DBI_ZB_PAN			(0x00000152|DBIT_U16)	// ID ���� ZigBee
#define DBI_CELL_LAC		(0x00000154|DBIT_U16)	// LAC
#define DBI_CELL_BSIC		(0x00000155|DBIT_U16)	// BSIC
#define DBI_BTS_MCC			(0x00000156|DBIT_U16)	// MCC
#define DBI_BTS_MNC			(0x00000157|DBIT_U16)	// MNC

#define DBI_GLOBAL_ID		0x00001000
#define DBI_MAX_ID			0x00FFFFFF
#define MKDBI_GLOBAL_ID(cnt,type)		(min(DBI_GLOBAL_ID + (cnt), DBI_MAX_ID) | (type))
//---------------------------------------------------------------------
#define DB_GETITEMID(v)		(v & DBI_MAX_ID)
#define DB_GETITEMTYPE(v)	(v & 0xFF000000)
#define DB_GETITEMSIZE(v)	((v & 0x0F000000) >> 24)
#define DB_GETARRAYDIM(v)	((v & 0x30000000) >> 28)
//---------------------------------------------------------------------
#define DBF_IQ				0x00000001		// I ������
#define DBF_FFT 			0x00000004		// ������
#define DBF_MULTIRANGE		0x00000010		// ��������� �����
#define DBF_FIRST_PART		0x00001000		// ������ �����
#define DBF_LAST_PART		0x00002000		// ������ �����
#define DBF_TEMPORARY		0x00001000		// ��������� (��������� ��� ��������)
//---------------------------------------------------------------------
#define DB_API_VERSION		1
//---------------------------------------------------------------------
