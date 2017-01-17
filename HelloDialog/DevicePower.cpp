// DevicePower.cpp : implementation file
//

#include "stdafx.h"
#include "DevicePower.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DevicePower
typedef int (*InitCom)(int);
typedef int (*InitCommExt)();
typedef int (*CloseCom)();
typedef (*ClosePow)();
typedef (*OpenPow)();
typedef (*ClosePow)();
typedef (*PowerSta)();
DevicePower::DevicePower()
{
	
}


DevicePower::~DevicePower()
{
	if (hinst1)
		FreeLibrary(hinst1);
	if (hinst2)
		FreeLibrary(hinst2);

	CloseCom m_pDll = (CloseCom)GetProcAddress(hinst1,_T("CloseComm"));
	if (m_pDll) {
		m_pDll();
	}
}


BEGIN_MESSAGE_MAP(DevicePower, CWnd)
	//{{AFX_MSG_MAP(DevicePower)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// DevicePower message handlers


BOOL DevicePower::OpenSerialPort()
{
	BOOL readstatus;
	CloseCom m_pDll_close = (CloseCom)GetProcAddress(hinst1,_T("CloseComm"));
	if (m_pDll_close) {
		m_pDll_close();
		Sleep(500);
	}

	InitCom m_pDll = (InitCom)GetProcAddress(hinst1,_T("InitComm"));
	int result = m_pDll(Port);
	if (result != 1)
	{
		readstatus = FALSE;
	}
	else
	{
		readstatus = TRUE;
	}
	return readstatus;
}




void DevicePower::PowerOn()
{
	OpenPow m_pDll = (OpenPow)GetProcAddress(hinst2, _T("OpenPower"));
	int status = PowerStatus();
	if (status == 0)
	{
		m_pDll();
	}
}

int DevicePower::PowerStatus()
{
	PowerSta m_pDll = (PowerSta)GetProcAddress(hinst2,_T("PowerStatus"));
	int status = m_pDll();
	return status;
}

void DevicePower::PowerOff()
{
	ClosePow m_pDll = (OpenPow)GetProcAddress(hinst2,_T("ClosePower"));
	int status=PowerStatus();
	if (status != 0)
	{
		m_pDll();
	}
}

BOOL DevicePower::initDevice()
{
	Port = 4;
	hinst1 = LoadLibrary(L"termb.dll");
	hinst2 = LoadLibrary(L"RFIDPower.dll");
	if (!hinst1 || !hinst2) {
		return FALSE;
	}
	
	return TRUE;
}

