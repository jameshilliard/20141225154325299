/*******************
 *	合凯智能技术P2P平台IPC对接使用接口说明：
 *   技术支持QQ：198509138
 *    邮箱：		 sun@uipcam.hk
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

//================*A类接口由P2P平台库实现,IPC端直接使用此接口*========

#define MPEG4           1
#define M_JPEG          2
#define H264            4
//当前设备支持的码流


#ifdef __cplusplus
extern "C"
{
#endif

//设备支持的码流是(1 MPEG4, 2 M_JPEG, 4 H264)
void setVideoEncodeType( int ntype);

//启动P2P平台
    //pIPCInst: 模块句柄 > 0
    //puser 		平台帐号
    //psw   		平台密码
    //host  		平台地址
    //port  		平台端口
    //nLang  		语言  中文为1,其他语言为0
    //返回值：>=0正常 <0错误
int sccModuInit(int pIPCInst,char * puser, char *psw, char *host,unsigned short nport,int nLang);

//当前设备工作模式
//1 设置IPC为AP模式
//0 设置IPC为网络模式
int sccEnableAPMode( int enable );

//设置IPC录像为AVI格式,不支持软件查询
//1 AVI录像
//0 私有格式录像
int sccEnableAviMode( int enable );

//当前设备视频的读取工作模式
//1 Push 模式,设备的视频数据主动push到我们的缓冲区中。
//0 Get 模式，设备的视频由我们的程序  	// 默认是 0
int sccVideoMode( int enable );

//退出P2P平台
int sccModuExit();


//发生报警 
//nAlarmType 指报警类型，移动侦测 1; 普通IO报警 2;  开锁呼叫(走的推送) 4;
int sccOnAlarm( int pIPCInst,int nAlarmType,int  nReserved );


//报警扩展接口
//nAlarmType 	指报警类型，移动侦测 1; 普通IO报警 2;  及时信息发送 4;
//char *cData 要发送的数据
int sccOnAlarm_EX( int pIPCInst,int nAlarmType,int nReserved, char *cData );

//当前用户连接数
int sccConnectionUser( int *iCount );    
    

//========================*B类接口IPC程序实现，P2P平台调用,接口内部不能阻塞*==========

//数据透传接口pc->dev B类型接口需要实现
//int ulParam 预留
int sccRecvAPPData( char *cData, int ulParam );

//获取透传数据，数据不能大于4096.此接口不能阻塞. B类型接口需要实现
//int ulParam 预留
int sccReceiveData( char cData[4096], int *ulParam );

//重启系统
int sccResystem();

//启动接收压缩流
//pIPCInst: 模块句柄
//pStreamType: 流类型，0：主码流 1：从码流
//返回值：返回值表示该通道接收数据的句柄  >0正常; ==0错误
int sccStreamStart(int pIPCInst,int pStreamType);
    

//停止接收压缩流
//pIPCInst: 模块句柄
//pStreamInst: 函数sccStreamStart返回的接收数据的句柄
//pStreamType: 流类型，0：主码流 1：从码流 （和sccStreamStart中参数相同）
//返回值：>0正常; ==0错误
int sccStreamStop(int pIPCInst,int pStreamInst,int pStreamType);
    

//sccVideoMode (0)===============>Start
//0 Get 模式，设备的视频由我们的程序  // 默认是 0
//接收压缩流数据
//pIPCInst: 模块句柄
//pStreamInst: 函数sccStreamStart返回的接收数据的句柄
//poDataBuf: 存放数据缓冲区指针的地址
//poDataLen：存放数据长度的地址
//iPofType:  1代表I帧，0代表P帧，
//iResType:  分辨率  enumVGAMode 请务必正确，或者大于实际分辨率
//iStreamType;	 H264码流为 4，M_JPEG码流为 2
//返回值：>0正常(返回视频长度) <=0错误
/**注意:视频数据,非P帧要全部标示为I帧;分辨率一定要有**/
int sccStreamRecv(int pIPCInst,int pStreamInst,char **poDataBuf,int *poDataLen,int *iPofType,int *iResType, int *iStreamType );

//释放该数据
//pIPCInst: 模块句柄
//pStreamInst: 函数sccStreamStart返回的接收数据的句柄
//pDataBuf: 数据缓冲区指针，是函数sccStreamRecv第三个参数的内容
//返回值：>0正常 <0错误
int sccStreamRelease(int pIPCInst,int pStreamInst,char *pDataBuf);
//sccVideoMode (0)===============>End

//sccVideoMode (1)===============>Start  A类接口
//1 Push 模式,设备的视频数据主动 push到我们的缓冲区中。
//接收压缩流数据 本接口为非阻塞模式接口
//pIPCInst: 模块句柄
//pStreamInst: 主码流 0; 子码流 1。
//poDataBuf: 存放数据缓冲区指针的地址
//poDataLen：存放数据长度的地址
//iPofType:  1代表I帧，0代表P帧 所有非P帧，请标示为I帧 否则手机有可能看不了
//iResType:  分辨率 enumVGAMode 请务必正确，或者大于实际分辨率
//iStreamType;	 H264码流为 4，M_JPEG码流为 2
//返回值：>0正常(返回视频长度) <=0错误
/**注意:视频数据,非P帧要全部标示为I帧;分辨率一定要有**/  
int sccPushStream(int pIPCInst,int pStreamInst,char *poDataBuf,int poDataLen,int iPofType,int iResType, int iStreamType );
//sccVideoMode (1)===============>End

    
//设置、获取系统参数 
//pStreamInst: 主次码流 (0：主码流 1：从码流)
int sccSetSysInfo( int pIPCInst, int pStreamType,int nType,int nValue );
int sccGetSysInfo( int pIPCInst, int pStreamType,int nType,int *nValue );
/*
 pStreamType  	 nType	nValue	描述
   0            	1(W)					云台上
   0             	2(W)					云台下
   0             	3(W)					云台左
   0             	4(W)					云台右
   0             	5(W)	    0		变倍 近
   0             	6(W)			0		变倍 远
   0            	7(W)					停止 FU  云台
   0							8(W)			0		光圈+
   0							9(W)			0   光圈-
   0              10(W)					聚焦+
   0              11(W)					聚焦-
   0             	60(W)   	1:云台开始自动水平巡航 2:云台开始自动垂直巡航 3:云台开始全方位巡航
                	50(R/W)				亮度
                	51(R/W)				色彩
                	52(R/W)				对比度
                	53(R/W)				饱和度
                	54(R/W)    		码流(速率)［16-2048］
                	55(R/W)    		设置质量 1:好 2:中 3:差
                	56(R/W)    		修改分辨率
                	57(R/W)    		修改帧率
                  59(R/W)				报警敏感度
   0              61(W)					上下翻转 
   0              62(W)					左右翻转
   0              63(R)         获取预置位 [1-8](移动到预置位)
   0              64(W)         设置预置位 [1-8](设置预置位)
   0              65(R/W)       设置步长(云台速度) 1(慢)-10(快)
                  66(R/W) 			爆光度
                  67(R/W) 			锐度
                  70(R/W)				50(PAL) 60(NTSC)频率
   0              100(R/W)      5000 设置局域网监听端口号。
   0              101(R/W)      0:启动互联网功能 1 ：关闭互联网功能
   0              102(R/W)      开关信号灯(指示灯)
   0              103(R/W)      1:打开IR  0 关闭IR
   0              104(R/W)			IO 输出电平 0:低电平 1:高电平
                  106(R/W)      cbr 0 vbr 1
   0              105(R/W)			I0 输入 0:NO 1:NC
                  107(W)				恢复默认参数
   0              108(R)        获取设备是否支持云台
   0							109(W)				恢复出厂设置..
   
   0						200(W)					拒绝开锁	(200特殊硬件定制功能)
   0						201(W)					开启视频或者对讲拒绝开锁
   0						202(W)					开启视频或者对讲开锁
   0						203(R/W) [1 99]	设置获取延时 时间。［1 99］ 1代表一直锁，99代表一直开锁
   0            204(R/W) [1 2]	 1.开启灯泡; 2关闭灯泡
   0            205(R/W) [1 2]   1.开启移动侦测亮灯; 2.关闭移动侦测亮灯

   
   0  301(R/W)  手机观看设置图像等级
   0  302(R/W)  SD卡是否移动侦测报警录像 	0不支持 1支持
   0  303(R/W)  外部输入报警录像 					0不支持 1支持
   0  304(R/W)  开机自动录像     					0不支持 1支持
   0  305(R/W)  录像自动替换     					0不支持 1支持
   0  306(R/W)  是否语音录制     					0不支持 1支持
   0  307(R/W)  录像文件大小     					10MB-200MB
   0  308(R/W)  SD卡录主子码流     				0子码流，1主码流
*/

//----------------------------------------------------------------------------------------  
//G711A  8000 采样率hz  16 bit
//打开语音 对于设备输出 ipc->pc
//pIPCInst: 模块句柄
//int iAudioType 音频类型，根据设备支持类型来。（没用到）
int sccOpenAudioOut( int pIPCInst, int iAudioType );

//语音输出
//pIPCInst: 模块句柄
//pStreamInst: 函数sccOpenAudioOut返回的接收数据的句柄
//poDataBuf: 存放数据缓冲区指针的地址
//poDataLen：存放数据长度的地址
//返回值：>=0正常 <0错误
int sccAudioOutRecv(int pIPCInst,int pStreamInst,char **poDataBuf,int *poDataLen );

//释放读出来的语音数据
//pIPCInst: 模块句柄
//pStreamInst: 函数sccOpenAudioOut返回的接收数据的句柄
int sccAudioOutRelease( int pIPCInst, int pStreamInst, char *cAudioData );

//关闭语音 
//pStreamInst: 函数sccOpenAudioOut返回的接收数据的句柄
int sccCloseAudioOut( int pStreamInst );


//----------------------------------------------------------------------------------
//打开语音 对于设备输入  pc->ipc
//pIPCInst: 模块句柄
//int iAudioType 音频类型，根据设备支持类型来。
int sccOpenAudioIn( int pIPCInst, int iAudioType );

//语音输入
//pIPCInst: 模块句柄
//pStreamInst: 函数sccOpenAudioIn返回的接收数据的句柄
//char *poDataBuf 音频数据
//int poDataLen 数据长度
int sccAudioInWrite(int pIPCInst,int pStreamInst,char *poDataBuf,int poDataLen );


//停止语音输入
//pStreamInst: 函数sccOpenAudioIn返回的接收数据的句柄
int sccCloseAudioIn(int pStreamInst );
//-----------------------------------------------------------------------


//wifi配置
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
     
//IP地址信息
typedef struct _SCCNetInfo
{
	int  nNetMode;    // 1 DHCP, 0 固定IP
	char aryIP[64];   // ip
	char aryMsk[64];  // 子网掩码
  char aryGW[64];   // 网关
  char aryDNS0[64]; // DNS
  char aryDNS1[64]; // 备用DNS
	char aryMac[64];  // mac
}SCCNetInfo;

//获取有线网络信息状态
//成功返回 >= 0
// nInter 0 是有线，1是无线 ，成功返回 >= 0
int ReadNetInfo( short nInter, SCCNetInfo *pnetcfg ); 

//配置有线网络
//成功返回 >= 0
// nInter 0 是有线，1是无线 ，成功返回 >= 0
int WriteNetInfo( short nInter, SCCNetInfo *pnetcfg  );

 //wifi info
 typedef struct hk_remote_wffi_info
 {
     char nettype;		//预留
     char enctype;		//0代表none,2-TKIP,3-AES
     char authmode;		//0代表none,1-wep,2-wpa,3-wpa2
     char ssid[SSID_LEN];
     int  iSignal;		//信号强度 [0 100] //0608新增加参数
 }REMOTE_INFO;       
 
typedef struct hk_remote_wifi_find          
{                                           
    int count;                              
    REMOTE_INFO wifi_info[HK_WIFI_FIND_LEN];
                                            
}REMOTE_WIFI_FIND;              
         
//wifi 配置结构
 typedef struct _REMOTE_WIFICFG
 {
 		 char  enable;		//1开启，0关闭
     char  netstat;		//1	预留
     char  nettype;   //4代表工作在AP模式 0代表普通模式	//20130709
     char  enctype;		//0代表none,2-TKIP,3-AES
     char  authmode;	//0代表none,1-wep,2-wpa,3-wpa2,4-auto
     char  defkeyid;	//1	预留
     char  ssid[SSID_LEN];
     char  pass[WIFIPASS_LEN];
 }REMOTE_WIFICFG;


//设置WIFI 信息
//返回值 >= 0成功
int InitWifi( REMOTE_WIFICFG* );
//获取WIFI 当前配置
//返回值 >= 0成功，当前是使用的WIFI连接才有此信息
int GetWifiInfo( REMOTE_WIFICFG* );  
// 扫描WIFI连接点
REMOTE_WIFI_FIND *ScanWifiInfo();   

//设备时间
//int iZone; 时区,如果为0请从配置文件读取值.   比如中国：28800
//unsigned int ulTime; 时间秒级
//int SummerTime 是否使用夏令时。1使用(在原来时间上加一个小时),0不使用.如果是0请从配置文件读取值.
int SetSystemTime( int iZone, unsigned int ulTime, int SummerTime );

//获取SDCard路径，返回< 0 失败。
int GetSDCardPath(char aryPath[]);

//格式化TF卡
int FormatSDCard(); 

typedef struct _MD_PARAM
{
   char nChannel; 			//[1 3]三个区域
   char bEnable; 				//开1, 关0
   char nSensitivity;		//[0 10]敏感度
   char nRes;     			//预留
   short  x1;     			//两点坐标值
   short  y1;
   short  x2;
   short  y2;  
}S_MD_PARAM;

//区域报警设置与获取
int SetMDParam( S_MD_PARAM smdParam[], int iCount );
int GetMDParam( S_MD_PARAM smdParam[], int *iCount );

typedef struct hk_emailinfo
{
    int iPort;		//发送端口
    int isOpen;		//预留
    int ioin;			//IO报警是否发送邮件［1发  0关］
    int iCount; 	//发送图片张数［0 3］
    int move; 		//移动报警是否发送邮件［1 0］0：open ，1：close。
    int sderror;	//sd卡错误是否发送邮件[1 0]
    int nDataEnc;	//数据加密方式 0-NO;1-SSL;2-TLS;
    int isTest;		//是否发送测试，1 发送一份测试邮件，0不发送。
    char sedEmail[128];		//发送者
    char recEmail[128]; 	//接收者
    char smtpServer[128];	//SMTP服务器
    char smtpUser[128];  	//邮箱用户
    char smtpPswd[128];	 	//邮箱密码
    char emailinfo[256]; 	//邮件内容
}HK_EMAIL_INFO;

//设置邮件发送信息
int sccSetEmailInfo(HK_EMAIL_INFO *st_emailinfo);

//获取邮件发送信息
int sccGetEmailInfo(HK_EMAIL_INFO *st_emailinfo );

typedef struct hk_ftpinfo
{
		int isOpen;					//开启
		int iPort; 					//端口
		char ftpServer[128];//FTP服务连接地址
		char ftpUser[128];	//FTP用户名
		char ftpPswd[128];	//FTP密码
		char ftpType[128];  //FTP类型
}HK_FTP_INFO;

//设置FTP信息
int sccSetFtpInfo( HK_FTP_INFO *st_ftpinfo );

//获取FTP信息
int sccGetFtpInfo( HK_FTP_INFO *gt_ftpinfo );

//设置PPOE帐号
int sccSetPPPOEInfo( char *ppoeID, char *ppoePswd );

//获取PPOE帐号
int sccGetPPPOEInfo( char ppoeID[128], char ppoePswd[128] );

//判断是否为空，如果为空就不写入配置文件
int sccSetCamId(char *pCamID, char *pPasswd, char *pMac1, char *pMac2, char *pHost, int irOpen, int rt900);

//修改连接地址与mac
int sccUpdateHostOrMac(char *pHost, char *mac1, char *mac2);

//修改设备ID与mac
int sccUpdateCamIDOrMac(char *devid, char *pwd, char *mac1, char *mac2);

//恢复出厂设置..
int sccRestorationParam();

#ifdef __cplusplus
}
#endif
