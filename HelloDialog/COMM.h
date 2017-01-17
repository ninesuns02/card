#if !defined(AFX_COMM_H__C37B67D6_2050_4251_A3F9_111E79C25E09__INCLUDED_)
#define AFX_COMM_H__C37B67D6_2050_4251_A3F9_111E79C25E09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// COMM.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCOMM window

/// Comm.h

#ifndef CCOMM_H_H
#define CCOMM_H_H 
class CComm
{
public:
	BOOL InitDCB();
	BOOL InitCommTimeout();
	long m_lTickCounts;
	HANDLE m_hComDev;
	CComm();
	~CComm();
	BOOL OpenPort();
	BOOL ClosePort();
	int  Read(BYTE *pBuf,int nLen, BOOL bFlag = TRUE);
	BOOL Write(BYTE *pBuf,int nLen);
	BOOL m_bPortOpened;
protected:
	CString m_com_adr;
	int  m_baud;
	CString m_parity;
	BYTE m_data_bit;
	BYTE m_stop_bit;
	int  m_time_out;
	
	OVERLAPPED  m_osWrite, m_osRead ;
	COMMTIMEOUTS  m_CommTimeOuts;
private:
};
#endif // !defined(AFX_COMM_H__C37B67D6_2050_4251_A3F9_111E79C25E09__INCLUDED_)
#endif