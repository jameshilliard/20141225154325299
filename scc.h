/*******************
 *	�Ͽ����ܼ���P2Pƽ̨IPC�Խ�ʹ�ýӿ�˵����
 *   ����֧��QQ��198509138
 *    ���䣺		 sun@uipcam.hk
********************/

enum enumVGAMode
{
ENUM_NONE = 0,  
ENUM_QQ720P=1,      /*320*180*/
ENUM_CIF=2,         /*352x288*/
ENUM_QVGA=3,        /*320x240*/
ENUM_Q720P=4,	 			/*640*360*/
ENUM_VGA=5,         /*640x480*/
ENUM_D_ONE=6,       /*704x480*/
ENUM_PAL_D1=7,      /*704x576*/
ENUM_XVGA=8,        /*1024x768*/
ENUM_720P = 9,      /*1280*720*/	
ENUM_SXGA=10,       /*1280x960*/
ENUM_HD200=11,      /*1600*1200*/
ENUM_RESOLUTION_ALL,  
};

typedef enum{
	VIDEO_FORMAT_P = 0,
	VIDEO_FORMAT_I = 1,
	VIDEO_FORMAT_SPS = 3,	//120 121
	VIDEO_FORMAT_PPS =4,	//8 9
}VIDEO_FORMAT_E;

typedef enum{
	AUDIO_FORMAT_G726 = 1,
	AUDIO_FORMAT_PCMA = 2,
	AUDIO_FORMAT_PCMU = 3,
	AUDIO_FORMAT_BUTT
}AUDIO_FORMAT_E;

//================*A��ӿ���P2Pƽ̨��ʵ��,IPC��ֱ��ʹ�ô˽ӿ�*========

#define MPEG4           1
#define M_JPEG          2
#define H264            4
//��ǰ�豸֧�ֵ�����


#ifdef __cplusplus
extern "C"
{
#endif

//�豸֧�ֵ�������(1 MPEG4, 2 M_JPEG, 4 H264)
void setVideoEncodeType( int ntype);

//����P2Pƽ̨
    //pIPCInst: ģ���� > 0
    //puser 		ƽ̨�ʺ�
    //psw   		ƽ̨����
    //host  		ƽ̨��ַ
    //port  		ƽ̨�˿�
    //nLang  		����  ����Ϊ1,��������Ϊ0
    //����ֵ��>=0���� <0����
int sccModuInit(int pIPCInst,char * puser, char *psw, char *host,unsigned short nport,int nLang);

//��ǰ�豸����ģʽ
//1 ����IPCΪAPģʽ
//0 ����IPCΪ����ģʽ
int sccEnableAPMode( int enable );

//����IPC¼��ΪAVI��ʽ,��֧�������ѯ
//1 AVI¼��
//0 ˽�и�ʽ¼��
int sccEnableAviMode( int enable );

//��ǰ�豸��Ƶ�Ķ�ȡ����ģʽ
//1 Push ģʽ,�豸����Ƶ��������push�����ǵĻ������С�
//0 Get ģʽ���豸����Ƶ�����ǵĳ���  	// Ĭ���� 0
int sccVideoMode( int enable );

//�˳�P2Pƽ̨
int sccModuExit();


//�������� 
//nAlarmType ָ�������ͣ��ƶ���� 1; ��ͨIO���� 2;  ��������(�ߵ�����) 4;
int sccOnAlarm( int pIPCInst,int nAlarmType,int  nReserved );


//������չ�ӿ�
//nAlarmType 	ָ�������ͣ��ƶ���� 1; ��ͨIO���� 2;  ��ʱ��Ϣ���� 4;
//char *cData Ҫ���͵�����
int sccOnAlarm_EX( int pIPCInst,int nAlarmType,int nReserved, char *cData );

//��ǰ�û�������
int sccConnectionUser( int *iCount );    
    

//========================*B��ӿ�IPC����ʵ�֣�P2Pƽ̨����,�ӿ��ڲ���������*==========

//����͸���ӿ�pc->dev B���ͽӿ���Ҫʵ��
//int ulParam Ԥ��
int sccRecvAPPData( char *cData, int ulParam );

//��ȡ͸�����ݣ����ݲ��ܴ���4096.�˽ӿڲ�������. B���ͽӿ���Ҫʵ��
//int ulParam Ԥ��
int sccReceiveData( char cData[4096], int *ulParam );

//����ϵͳ
int sccResystem();

//��������ѹ����
//pIPCInst: ģ����
//pStreamType: �����ͣ�0�������� 1��������
//����ֵ������ֵ��ʾ��ͨ���������ݵľ��  >0����; ==0����
int sccStreamStart(int pIPCInst,int pStreamType);
    

//ֹͣ����ѹ����
//pIPCInst: ģ����
//pStreamInst: ����sccStreamStart���صĽ������ݵľ��
//pStreamType: �����ͣ�0�������� 1�������� ����sccStreamStart�в�����ͬ��
//����ֵ��>0����; ==0����
int sccStreamStop(int pIPCInst,int pStreamInst,int pStreamType);
    

//sccVideoMode (0)===============>Start
//0 Get ģʽ���豸����Ƶ�����ǵĳ���  // Ĭ���� 0
//����ѹ��������
//pIPCInst: ģ����
//pStreamInst: ����sccStreamStart���صĽ������ݵľ��
//poDataBuf: ������ݻ�����ָ��ĵ�ַ
//poDataLen��������ݳ��ȵĵ�ַ
//iPofType:  1����I֡��0����P֡��
//iResType:  �ֱ���  enumVGAMode �������ȷ�����ߴ���ʵ�ʷֱ���
//iStreamType;	 H264����Ϊ 4��M_JPEG����Ϊ 2
//����ֵ��>0����(������Ƶ����) <=0����
/**ע��:��Ƶ����,��P֡Ҫȫ����ʾΪI֡;�ֱ���һ��Ҫ��**/
int sccStreamRecv(int pIPCInst,int pStreamInst,char **poDataBuf,int *poDataLen,int *iPofType,int *iResType, int *iStreamType );

//�ͷŸ�����
//pIPCInst: ģ����
//pStreamInst: ����sccStreamStart���صĽ������ݵľ��
//pDataBuf: ���ݻ�����ָ�룬�Ǻ���sccStreamRecv����������������
//����ֵ��>0���� <0����
int sccStreamRelease(int pIPCInst,int pStreamInst,char *pDataBuf);
//sccVideoMode (0)===============>End

//sccVideoMode (1)===============>Start  A��ӿ�
//1 Push ģʽ,�豸����Ƶ�������� push�����ǵĻ������С�
//����ѹ�������� ���ӿ�Ϊ������ģʽ�ӿ�
//pIPCInst: ģ����
//pStreamInst: ������ 0; ������ 1��
//poDataBuf: ������ݻ�����ָ��ĵ�ַ
//poDataLen��������ݳ��ȵĵ�ַ
//iPofType:  1����I֡��0����P֡ ���з�P֡�����ʾΪI֡ �����ֻ��п��ܿ�����
//iResType:  �ֱ��� enumVGAMode �������ȷ�����ߴ���ʵ�ʷֱ���
//iStreamType;	 H264����Ϊ 4��M_JPEG����Ϊ 2
//����ֵ��>0����(������Ƶ����) <=0����
/**ע��:��Ƶ����,��P֡Ҫȫ����ʾΪI֡;�ֱ���һ��Ҫ��**/  
int sccPushStream(int pIPCInst,int pStreamInst,char *poDataBuf,int poDataLen,int iPofType,int iResType, int iStreamType );
//sccVideoMode (1)===============>End

    
//���á���ȡϵͳ���� 
//pStreamInst: �������� (0�������� 1��������)
int sccSetSysInfo( int pIPCInst, int pStreamType,int nType,int nValue );
int sccGetSysInfo( int pIPCInst, int pStreamType,int nType,int *nValue );
/*
 pStreamType  	 nType	nValue	����
   0            	1(W)					��̨��
   0             	2(W)					��̨��
   0             	3(W)					��̨��
   0             	4(W)					��̨��
   0             	5(W)	    0		�䱶 ��
   0             	6(W)			0		�䱶 Զ
   0            	7(W)					ֹͣ FU  ��̨
   0							8(W)			0		��Ȧ+
   0							9(W)			0   ��Ȧ-
   0              10(W)					�۽�+
   0              11(W)					�۽�-
   0             	60(W)   	1:��̨��ʼ�Զ�ˮƽѲ�� 2:��̨��ʼ�Զ���ֱѲ�� 3:��̨��ʼȫ��λѲ��
                	50(R/W)				����
                	51(R/W)				ɫ��
                	52(R/W)				�Աȶ�
                	53(R/W)				���Ͷ�
                	54(R/W)    		����(����)��16-2048��
                	55(R/W)    		�������� 1:�� 2:�� 3:��
                	56(R/W)    		�޸ķֱ���
                	57(R/W)    		�޸�֡��
                  59(R/W)				�������ж�
   0              61(W)					���·�ת 
   0              62(W)					���ҷ�ת
   0              63(R)         ��ȡԤ��λ [1-8](�ƶ���Ԥ��λ)
   0              64(W)         ����Ԥ��λ [1-8](����Ԥ��λ)
   0              65(R/W)       ���ò���(��̨�ٶ�) 1(��)-10(��)
                  66(R/W) 			�����
                  67(R/W) 			���
                  70(R/W)				50(PAL) 60(NTSC)Ƶ��
   0              100(R/W)      5000 ���þ����������˿ںš�
   0              101(R/W)      0:�������������� 1 ���رջ���������
   0              102(R/W)      �����źŵ�(ָʾ��)
   0              103(R/W)      1:��IR  0 �ر�IR
   0              104(R/W)			IO �����ƽ 0:�͵�ƽ 1:�ߵ�ƽ
                  106(R/W)      cbr 0 vbr 1
   0              105(R/W)			I0 ���� 0:NO 1:NC
                  107(W)				�ָ�Ĭ�ϲ���
   0              108(R)        ��ȡ�豸�Ƿ�֧����̨
   0							109(W)				�ָ���������..
   
   0						200(W)					�ܾ�����	(200����Ӳ�����ƹ���)
   0						201(W)					������Ƶ���߶Խ��ܾ�����
   0						202(W)					������Ƶ���߶Խ�����
   0						203(R/W) [1 99]	���û�ȡ��ʱ ʱ�䡣��1 99�� 1����һֱ����99����һֱ����
   0            204(R/W) [1 2]	 1.��������; 2�رյ���
   0            205(R/W) [1 2]   1.�����ƶ��������; 2.�ر��ƶ��������

   
   0  301(R/W)  �ֻ��ۿ�����ͼ��ȼ�
   0  302(R/W)  SD���Ƿ��ƶ���ⱨ��¼�� 	0��֧�� 1֧��
   0  303(R/W)  �ⲿ���뱨��¼�� 					0��֧�� 1֧��
   0  304(R/W)  �����Զ�¼��     					0��֧�� 1֧��
   0  305(R/W)  ¼���Զ��滻     					0��֧�� 1֧��
   0  306(R/W)  �Ƿ�����¼��     					0��֧�� 1֧��
   0  307(R/W)  ¼���ļ���С     					10MB-200MB
   0  308(R/W)  SD��¼��������     				0��������1������
*/

//----------------------------------------------------------------------------------------  
//G711A  8000 ������hz  16 bit
//������ �����豸��� ipc->pc
//pIPCInst: ģ����
//int iAudioType ��Ƶ���ͣ������豸֧������������û�õ���
int sccOpenAudioOut( int pIPCInst, int iAudioType );

//�������
//pIPCInst: ģ����
//pStreamInst: ����sccOpenAudioOut���صĽ������ݵľ��
//poDataBuf: ������ݻ�����ָ��ĵ�ַ
//poDataLen��������ݳ��ȵĵ�ַ
//����ֵ��>=0���� <0����
int sccAudioOutRecv(int pIPCInst,int pStreamInst,char **poDataBuf,int *poDataLen );

//�ͷŶ���������������
//pIPCInst: ģ����
//pStreamInst: ����sccOpenAudioOut���صĽ������ݵľ��
int sccAudioOutRelease( int pIPCInst, int pStreamInst, char *cAudioData );

//�ر����� 
//pStreamInst: ����sccOpenAudioOut���صĽ������ݵľ��
int sccCloseAudioOut( int pStreamInst );


//----------------------------------------------------------------------------------
//������ �����豸����  pc->ipc
//pIPCInst: ģ����
//int iAudioType ��Ƶ���ͣ������豸֧����������
int sccOpenAudioIn( int pIPCInst, int iAudioType );

//��������
//pIPCInst: ģ����
//pStreamInst: ����sccOpenAudioIn���صĽ������ݵľ��
//char *poDataBuf ��Ƶ����
//int poDataLen ���ݳ���
int sccAudioInWrite(int pIPCInst,int pStreamInst,char *poDataBuf,int poDataLen );


//ֹͣ��������
//pStreamInst: ����sccOpenAudioIn���صĽ������ݵľ��
int sccCloseAudioIn(int pStreamInst );
//-----------------------------------------------------------------------


//wifi����
#define HK_WIFI_FIND_LEN 25                 
#define SSID_LEN      37
#define WIFIPASS_LEN  50
#define TF_PATH  255

typedef enum{
	WIFI_NETTYPE_INFRA = 0,
	WIFI_NETTYPE_ADHOC = 1,
	WIFI_NETTYPE_BUTT
}WIFI_NETTYPE_E;

typedef enum{
	WIFI_ENCTYPE_NONE = 0,
	WIFI_ENCTYPE_TKIP = 2,
	WIFI_ENCTYPE_AES  = 3,
	WIFI_ENCTYPE_BUTT
}WIFI_ENCTYPE_E;

typedef enum{
	WIFI_AUTHMODE_NONE = 0,
	WIFI_AUTHMODE_WEP  = 1,
	WIFI_AUTHMODE_WPA  = 2,
	WIFI_AUTHMODE_WPA2 = 3,
	WIFI_AUTHMODE_AUTO = 4,
	WIFI_AUTHMODE_BUTT
}WIFI_AUTHMODE_E;     
     
//IP��ַ��Ϣ
typedef struct _SCCNetInfo
{
	int  nNetMode;    // 1 DHCP, 0 �̶�IP
	char aryIP[64];   // ip
	char aryMsk[64];  // ��������
  char aryGW[64];   // ����
  char aryDNS0[64]; // DNS
  char aryDNS1[64]; // ����DNS
	char aryMac[64];  // mac
}SCCNetInfo;

//��ȡ����������Ϣ״̬
//�ɹ����� >= 0
// nInter 0 �����ߣ�1������ ���ɹ����� >= 0
int ReadNetInfo( short nInter, SCCNetInfo *pnetcfg ); 

//������������
//�ɹ����� >= 0
// nInter 0 �����ߣ�1������ ���ɹ����� >= 0
int WriteNetInfo( short nInter, SCCNetInfo *pnetcfg  );

 //wifi info
 typedef struct hk_remote_wffi_info
 {
     char nettype;		//Ԥ��
     char enctype;		//0����none,2-TKIP,3-AES
     char authmode;		//0����none,1-wep,2-wpa,3-wpa2
     char ssid[SSID_LEN];
     int  iSignal;		//�ź�ǿ�� [0 100] //0608�����Ӳ���
 }REMOTE_INFO;       
 
typedef struct hk_remote_wifi_find          
{                                           
    int count;                              
    REMOTE_INFO wifi_info[HK_WIFI_FIND_LEN];
                                            
}REMOTE_WIFI_FIND;              
         
//wifi ���ýṹ
 typedef struct _REMOTE_WIFICFG
 {
 		 char  enable;		//1������0�ر�
     char  netstat;		//1	Ԥ��
     char  nettype;   //4��������APģʽ 0������ͨģʽ	//20130709
     char  enctype;		//0����none,2-TKIP,3-AES
     char  authmode;	//0����none,1-wep,2-wpa,3-wpa2,4-auto
     char  defkeyid;	//1	Ԥ��
     char  ssid[SSID_LEN];
     char  pass[WIFIPASS_LEN];
 }REMOTE_WIFICFG;


//����WIFI ��Ϣ
//����ֵ >= 0�ɹ�
int InitWifi( REMOTE_WIFICFG* );
//��ȡWIFI ��ǰ����
//����ֵ >= 0�ɹ�����ǰ��ʹ�õ�WIFI���Ӳ��д���Ϣ
int GetWifiInfo( REMOTE_WIFICFG* );  
// ɨ��WIFI���ӵ�
REMOTE_WIFI_FIND *ScanWifiInfo();   

//�豸ʱ��
//int iZone; ʱ��,���Ϊ0��������ļ���ȡֵ.   �����й���28800
//unsigned int ulTime; ʱ���뼶
//int SummerTime �Ƿ�ʹ������ʱ��1ʹ��(��ԭ��ʱ���ϼ�һ��Сʱ),0��ʹ��.�����0��������ļ���ȡֵ.
int SetSystemTime( int iZone, unsigned int ulTime, int SummerTime );

//��ȡSDCard·��������< 0 ʧ�ܡ�
int GetSDCardPath(char aryPath[]);

//��ʽ��TF��
int FormatSDCard(); 

typedef struct _MD_PARAM
{
   char nChannel; 			//[1 3]��������
   char bEnable; 				//��1, ��0
   char nSensitivity;		//[0 10]���ж�
   char nRes;     			//Ԥ��
   short  x1;     			//��������ֵ
   short  y1;
   short  x2;
   short  y2;  
}S_MD_PARAM;

//���򱨾��������ȡ
int SetMDParam( S_MD_PARAM smdParam[], int iCount );
int GetMDParam( S_MD_PARAM smdParam[], int *iCount );

typedef struct hk_emailinfo
{
    int iPort;		//���Ͷ˿�
    int isOpen;		//Ԥ��
    int ioin;			//IO�����Ƿ����ʼ���1��  0�أ�
    int iCount; 	//����ͼƬ������0 3��
    int move; 		//�ƶ������Ƿ����ʼ���1 0��0��open ��1��close��
    int sderror;	//sd�������Ƿ����ʼ�[1 0]
    int nDataEnc;	//���ݼ��ܷ�ʽ 0-NO;1-SSL;2-TLS;
    int isTest;		//�Ƿ��Ͳ��ԣ�1 ����һ�ݲ����ʼ���0�����͡�
    char sedEmail[128];		//������
    char recEmail[128]; 	//������
    char smtpServer[128];	//SMTP������
    char smtpUser[128];  	//�����û�
    char smtpPswd[128];	 	//��������
    char emailinfo[256]; 	//�ʼ�����
}HK_EMAIL_INFO;

//�����ʼ�������Ϣ
int sccSetEmailInfo(HK_EMAIL_INFO *st_emailinfo);

//��ȡ�ʼ�������Ϣ
int sccGetEmailInfo(HK_EMAIL_INFO *st_emailinfo );

typedef struct hk_ftpinfo
{
		int isOpen;					//����
		int iPort; 					//�˿�
		char ftpServer[128];//FTP�������ӵ�ַ
		char ftpUser[128];	//FTP�û���
		char ftpPswd[128];	//FTP����
		char ftpType[128];  //FTP����
}HK_FTP_INFO;

//����FTP��Ϣ
int sccSetFtpInfo( HK_FTP_INFO *st_ftpinfo );

//��ȡFTP��Ϣ
int sccGetFtpInfo( HK_FTP_INFO *gt_ftpinfo );

//����PPOE�ʺ�
int sccSetPPPOEInfo( char *ppoeID, char *ppoePswd );

//��ȡPPOE�ʺ�
int sccGetPPPOEInfo( char ppoeID[128], char ppoePswd[128] );

//�ж��Ƿ�Ϊ�գ����Ϊ�վͲ�д�������ļ�
int sccSetCamId(char *pCamID, char *pPasswd, char *pMac1, char *pMac2, char *pHost, int irOpen, int rt900);

//�޸����ӵ�ַ��mac
int sccUpdateHostOrMac(char *pHost, char *mac1, char *mac2);

//�޸��豸ID��mac
int sccUpdateCamIDOrMac(char *devid, char *pwd, char *mac1, char *mac2);

//�ָ���������..
int sccRestorationParam();

#ifdef __cplusplus
}
#endif
