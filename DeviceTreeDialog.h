// DeviceTreeDialog.h : header file
//

#if !defined(AFX_DEVICETREEDIALOG_H__69D8A1BC_906E_4294_B543_E4B599FE6ACE__INCLUDED_)
#define AFX_DEVICETREEDIALOG_H__69D8A1BC_906E_4294_B543_E4B599FE6ACE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DeviceTree.h"
/////////////////////////////////////////////////////////////////////////////
// CDeviceTreeDlg dialog

class CDeviceTreeDlg : public CDialog
{
// Construction
public:
	CDeviceTreeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDeviceTreeDlg)
	enum { IDD = IDD_DEVICETREEDLG_DIALOG };
	CDeviceTree	m_DeviceTree;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeviceTreeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDeviceTreeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVICETREEDIALOG_H__69D8A1BC_906E_4294_B543_E4B599FE6ACE__INCLUDED_)
