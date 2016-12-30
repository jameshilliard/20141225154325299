#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/socket.h>

#include "scc.h"

REMOTE_WIFI_FIND* ScanWifiInfo()
{
    return NULL;
}

int InitWifi( REMOTE_WIFICFG *wffiinfo )
{
    return 0;
}

int GetWifiInfo(REMOTE_WIFICFG *hkWifiInfo)
{
    return 0;
}

int ReadNetInfo( short nInter, SCCNetInfo *hkPnetcfg)
{
    return 0;
}

//获取SD卡绝对路径
int GetSDCardPath(char aryPath[])
{
	return 0;
}

//获取各参数
int sccGetSysInfo( int pIPCInst, int pStreamType,int nType,int *nValue )
{
		*nValue = 0;
    return 0;
}

//配置各参数
int sccSetSysInfo( int pIPCInst, int pStreamType,int nType,int nValue )
{
    return 0;
}

//----------------------------video-------------------------
//开始来读取视频
int sccStreamStart(int pIPCInst,int pStreamType)
{
    return 1;
}

//关闭取视频
int sccStreamStop(int pIPCInst,int pStreamInst,int pStreamType)
{
    return 0;
}

//读取视频 获取采用0模式会调用此接口获取视频数据
int sccStreamRecv(int pIPCInst, int pStreamInst,char **poDataBuf,int *poDataLen,int *iPofType,int *iResType, int *iStreamType )
{
    return 0;
}

//读取视频 获取采用1模式会调用此接口获取视频数据
static int pushSCCVideoData(char *buf, int len ) 
{
		sccPushStream(3451, 0, buf, len, 1, 9, 4 );	//push数据
}

int sccStreamRelease(int pIPCInst,int pStreamInst,char *pDataBuf)
{
    return 0;
}

//--------------------audio-------------------
//开启音频读取
int sccOpenAudioOut( int pIPCInst, int iAudioType )
{
    return 0;
}

static int g_len=0;
static int g_audio=0;
static char g_audioBuf[1024*4]={0};
static int GetAudioData()	//读取机器音频数据
{
	while(1)
	{
		 if(g_audio==0)
		 	{
		 			g_audio = 1;
		 		//g_len = audioLen;
		 		 //strcpy( g_audioBuf, audioData);
		 	}
	}
}

//P2P线程过来读取音频数据
int sccAudioOutRecv(int pIPCInst,int pStreamInst,char **poDataBuf,int *poDataLen )
{
		*poDataLen = 0;
		if( g_audio == 1)
		{
			 *poDataBuf = g_audioBuf;
			 *poDataLen = g_len;
		}
		else
			return 0;
		
   return 0;
}

//P2P关闭音频读取
int sccCloseAudioOut( int pStreamInst )
{
		//退出机器音频读取数据
    return 0;
}

int sccAudioOutRelease( int pIPCInst, int pStreamInst, char *cAudioData )
{
    return 0;
}

//------
int sccOpenAudioIn( int pIPCInst, int iAudioType )
{
    return 0;
}

int sccAudioInWrite(int pIPCInst,int pStreamInst,char *poDataBuf,int poDataLen )
{
    return 0;
}
int sccCloseAudioIn(int pStreamInst )
{
    return 0;
}

//所有接口具体说明可以看头文件
int main()
{
	//设置类型 必须与你设备输出类型一至.
	setVideoEncodeType( H264 );
	//登录服务器
	sccModuInit(111,"puser","psw","www.scc21.com",8080, 1 );
	
	//报警推送..
	sccOnAlarm( 111, 1, 0 );
	
	//获取码流形式
	sccVideoMode( 1 );
	
	while(1)
	{
    	sleep(3);        
   }
   return 0;
}





int  sccSetLanPwd( int pIPCInst,char *pBuf )
{
	return 0;
}

int  sccGetLanPwd( int pIPCInst,char *pBuf )
{
	return 0;
}
	
int sccSetEmailInfo(HK_EMAIL_INFO *hk_emailinfo)
{
	return 0;
}

int sccGetEmailInfo(HK_EMAIL_INFO *hk_emailinfo)
{
	return 0;
}


int SetSystemTime( int iZone, unsigned int ulTime, int SummerTime )
{
	return 0;
}

int WriteNetInfo( short nInter, SCCNetInfo *pnetcfg  )
{
    return 0;
}
//-----------------------------------------------------
//恢复出厂设置..
int sccRestorationParam()
{
	return 0;
}


//设置FTP信息
int sccSetFtpInfo( HK_FTP_INFO *st_ftpinfo )
{
	return 0;
}

//获取FTP信息
int sccGetFtpInfo( HK_FTP_INFO *gt_ftpinfo )
{
	return 0;
}

//设置PPOE帐号
int sccSetPPPOEInfo( char *ppoeID, char *ppoePswd )
{
	return 0;
}

//获取PPOE帐号
int sccGetPPPOEInfo( char ppoeID[128], char ppoePswd[128] )
{
	return 0;
}

//设备帐号配置
//判断是否为空，如果为空就不写入配置文件
int sccSetCamId(char *pCamID, char *pPasswd, char *pMac1, char *pMac2, char *pHost, int irOpen, int rt900)
{
	return 0;
}

//修改连接地址与mac
int sccUpdateHostOrMac(char *pHost, char *mac1, char *mac2)
{
	return 0;
}

//修改设备ID与mac
int sccUpdateCamIDOrMac(char *devid, char *pwd, char *mac1, char *mac2)
{
	return 0;
}

int sccResystem()
{
	return 0;
}

int FormatSDCard()
{
	return 0;
}