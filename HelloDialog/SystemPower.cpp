// SystemPower.cpp : implementation file
//

#include "stdafx.h"
#include "HelloDialog.h"
#include "SystemPower.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SystemPower

IMPLEMENT_DYNCREATE(SystemPower, CWinThread)

SystemPower::SystemPower()
{
}

SystemPower::~SystemPower()
{
}

BOOL SystemPower::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int SystemPower::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(SystemPower, CWinThread)
	//{{AFX_MSG_MAP(SystemPower)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SystemPower message handlers
