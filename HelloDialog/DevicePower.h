#if !defined(AFX_DEVICEPOWER_H__4B7BBD2C_826E_403A_BE93_D3D0B59C3EC9__INCLUDED_)
#define AFX_DEVICEPOWER_H__4B7BBD2C_826E_403A_BE93_D3D0B59C3EC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DevicePower.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DevicePower window
#define WT(str) (_T("str"))

class DevicePower : public CWnd
{
// Construction
public:
	DevicePower();
private:
	int Port;
	HINSTANCE hinst1;
	HINSTANCE hinst2;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DevicePower)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL initDevice();
	void PowerOff();
	int PowerStatus();
	void PowerOn();
	BOOL OpenSerialPort();

	virtual ~DevicePower();

	// Generated message map functions
protected:
	//{{AFX_MSG(DevicePower)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVICEPOWER_H__4B7BBD2C_826E_403A_BE93_D3D0B59C3EC9__INCLUDED_)
