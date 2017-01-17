// COMM.cpp : implementation file
//

#include "stdafx.h"
#include "HelloDialog.h"
#include "COMM.h"
#include <memory.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCOMM

///////////////////////////////////////////////////////////////////////////////
//CComm 
//extern CGlobalVar GlobalVar;
CComm::CComm()
{
	m_com_adr = "GCM1";
	m_baud = 115200;
	m_hComDev = NULL;
	m_bPortOpened = FALSE;
}

CComm::~CComm()
{
	
}

BOOL CComm::OpenPort()
{
	CString strComm = m_com_adr;
	if(!m_bPortOpened)
	{
		m_hComDev = CreateFile(strComm,
			GENERIC_READ | GENERIC_WRITE,
			0,                    // exclusive access
			NULL,                 // no security attrs
			OPEN_EXISTING,
			0, // 不支持 overlapped I/O
			NULL ); 
		if(m_hComDev == INVALID_HANDLE_VALUE )
		{
			m_bPortOpened = FALSE;
		}
		else
		{
			SetCommMask (m_hComDev, EV_RXCHAR|EV_TXEMPTY);
			
			//分配设备缓冲区　　
			SetupComm(m_hComDev,512,512);
			
			//初始化缓冲区中的信息
			PurgeComm(m_hComDev,PURGE_TXCLEAR|PURGE_RXCLEAR|PURGE_RXABORT|PURGE_TXABORT);
			
			if (!InitDCB())
			{
				m_bPortOpened = FALSE;
			}
			
			if(!InitCommTimeout())
				m_bPortOpened = FALSE;
			
			EscapeCommFunction(m_hComDev,SETDTR);
			EscapeCommFunction(m_hComDev,SETRTS);  
		}
		
	}
    return m_bPortOpened;
}

BOOL CComm::ClosePort()
{
	if(m_bPortOpened && m_hComDev != NULL && m_hComDev != INVALID_HANDLE_VALUE)
	{
		PurgeComm(m_hComDev, PURGE_TXABORT | PURGE_RXABORT |
			PURGE_TXCLEAR | PURGE_RXCLEAR ) ;
		CloseHandle(m_hComDev) ;
		m_hComDev = NULL;
	}
	m_bPortOpened = FALSE;
	return TRUE;
}

BOOL CComm::Write(BYTE *pBuf,int nLen)
{
	BOOL        bWriteStat ;
    DWORD       dwBytesWritten ;
    COMSTAT     ComStat;
	DWORD       dwCommError;
	
	ClearCommError(m_hComDev,&dwCommError,&ComStat);
	
    bWriteStat = WriteFile(m_hComDev, pBuf, sizeof(TCHAR)*nLen,&dwBytesWritten,NULL) ;
	if(bWriteStat <= 0)
	{
		return FALSE;
	}
    return TRUE;
}

int CComm::Read(BYTE *pBuf,int nLen,BOOL bFlag)
{
	COMSTAT    ComStat ;
    DWORD      dwErrorFlags;
    DWORD      dwLength;
    BOOL       bReadStat ;
	
    ClearCommError(m_hComDev, &dwErrorFlags, &ComStat ) ;
	dwLength=ComStat.cbInQue;
	bReadStat = ReadFile(m_hComDev,pBuf,dwLength,&dwLength,NULL);
//    GlobalVar.BugPrintf(pBuf,dwLength);
	if(!bReadStat)
	{
		dwLength = 0;
	}
    return dwLength;
}

BOOL CComm::InitCommTimeout()
{
	memset(&m_CommTimeOuts,0,sizeof(COMMTIMEOUTS));
	GetCommTimeouts(m_hComDev,&m_CommTimeOuts);
	
	m_CommTimeOuts.ReadIntervalTimeout = MAXDWORD;    
	m_CommTimeOuts.ReadTotalTimeoutMultiplier = 1;       
	m_CommTimeOuts.ReadTotalTimeoutConstant = 100;  
	
	if(!SetCommTimeouts(m_hComDev,&m_CommTimeOuts))
	{
		CString strError;
		strError.Format(_T("SetCommTimeouts failed . %d"),GetLastError());
		return FALSE;
	}
	return true;
}

BOOL CComm::InitDCB()
{
	DCB dcb;
	dcb.DCBlength = sizeof(DCB);
	GetCommState(m_hComDev,&dcb);
	
	dcb.BaudRate = m_baud; 
	
	dcb.fBinary = TRUE; 
	dcb.fParity = TRUE; 
	
	dcb.fOutxCtsFlow = TRUE; 
	
	dcb.fOutxDsrFlow = FALSE; 
	
	dcb.fDtrControl = DTR_CONTROL_ENABLE; 
	
	dcb.fDsrSensitivity = FALSE;  
	m_bPortOpened = TRUE;
	if(!SetCommState(m_hComDev,&dcb))
	{
		CString strError;
		strError.Format(_T("SetCommState failed . %d"),GetLastError());
		m_bPortOpened = FALSE;
	}
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCOMM message handlers
