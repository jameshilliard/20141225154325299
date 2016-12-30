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

//��ȡSD������·��
int GetSDCardPath(char aryPath[])
{
	return 0;
}

//��ȡ������
int sccGetSysInfo( int pIPCInst, int pStreamType,int nType,int *nValue )
{
		*nValue = 0;
    return 0;
}

//���ø�����
int sccSetSysInfo( int pIPCInst, int pStreamType,int nType,int nValue )
{
    return 0;
}

//----------------------------video-------------------------
//��ʼ����ȡ��Ƶ
int sccStreamStart(int pIPCInst,int pStreamType)
{
    return 1;
}

//�ر�ȡ��Ƶ
int sccStreamStop(int pIPCInst,int pStreamInst,int pStreamType)
{
    return 0;
}

//��ȡ��Ƶ ��ȡ����0ģʽ����ô˽ӿڻ�ȡ��Ƶ����
int sccStreamRecv(int pIPCInst, int pStreamInst,char **poDataBuf,int *poDataLen,int *iPofType,int *iResType, int *iStreamType )
{
    return 0;
}

//��ȡ��Ƶ ��ȡ����1ģʽ����ô˽ӿڻ�ȡ��Ƶ����
static int pushSCCVideoData(char *buf, int len ) 
{
		sccPushStream(3451, 0, buf, len, 1, 9, 4 );	//push����
}

int sccStreamRelease(int pIPCInst,int pStreamInst,char *pDataBuf)
{
    return 0;
}

//--------------------audio-------------------
//������Ƶ��ȡ
int sccOpenAudioOut( int pIPCInst, int iAudioType )
{
    return 0;
}

static int g_len=0;
static int g_audio=0;
static char g_audioBuf[1024*4]={0};
static int GetAudioData()	//��ȡ������Ƶ����
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

//P2P�̹߳�����ȡ��Ƶ����
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

//P2P�ر���Ƶ��ȡ
int sccCloseAudioOut( int pStreamInst )
{
		//�˳�������Ƶ��ȡ����
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

//���нӿھ���˵�����Կ�ͷ�ļ�
int main()
{
	//�������� ���������豸�������һ��.
	setVideoEncodeType( H264 );
	//��¼������
	sccModuInit(111,"puser","psw","www.scc21.com",8080, 1 );
	
	//��������..
	sccOnAlarm( 111, 1, 0 );
	
	//��ȡ������ʽ
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
//�ָ���������..
int sccRestorationParam()
{
	return 0;
}


//����FTP��Ϣ
int sccSetFtpInfo( HK_FTP_INFO *st_ftpinfo )
{
	return 0;
}

//��ȡFTP��Ϣ
int sccGetFtpInfo( HK_FTP_INFO *gt_ftpinfo )
{
	return 0;
}

//����PPOE�ʺ�
int sccSetPPPOEInfo( char *ppoeID, char *ppoePswd )
{
	return 0;
}

//��ȡPPOE�ʺ�
int sccGetPPPOEInfo( char ppoeID[128], char ppoePswd[128] )
{
	return 0;
}

//�豸�ʺ�����
//�ж��Ƿ�Ϊ�գ����Ϊ�վͲ�д�������ļ�
int sccSetCamId(char *pCamID, char *pPasswd, char *pMac1, char *pMac2, char *pHost, int irOpen, int rt900)
{
	return 0;
}

//�޸����ӵ�ַ��mac
int sccUpdateHostOrMac(char *pHost, char *mac1, char *mac2)
{
	return 0;
}

//�޸��豸ID��mac
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