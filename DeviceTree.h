////////////////////////////////////////////////////////////////////////////
//	Copyright : A. Riazi 2004
//
//	email: a.riazi@misbah3com.com
//
//	This code may be used in compiled form in any way you desire. This
//	file may be redistributed unmodified by any means PROVIDING it is 
//	not sold for profit without the authors written consent, and 
//	providing that this notice and the authors name is included.
//
//	This file is provided 'as is' with no expressed or implied warranty.
//	The author accepts no liability if it causes any damage to your computer.
//
//	Please let me know of any bugs/mods/improvements.
//	and I will try to fix/incorporate them into this file.
//	Enjoy!
//
//	Description : This class represent a tree control that show all of 
//				  installed devices. For more information, see my article:
//				  Enumerating Installed Devices 
//				  (http://www.codeproject.com/system/enumdevices.asp)
//
//				  For C# version, I suggest to see Vladimir Afanasyev articles 
//				  at CodeProject:
//				  http://www.codeproject.com/csharp/DivingSysProg1.asp     &
//				  http://www.codeproject.com/csharp/DivingSysProg2.asp
//
//				  Part of the code was taken from Vladimir articles.
////////////////////////////////////////////////////////////////////////////

#ifndef _DEVICE_TREE_H_
#define _DEVICE_TREE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DeviceTree.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDeviceTree window

#include "SetupAPI.h"
#include "cfgmgr32.h"

#pragma comment(lib, "SetupAPI.lib")
#pragma comment(lib, "rpcrt4.lib")

#define MAX_DEV_LEN 1000

class CDeviceTree : public CTreeCtrl
{
// Construction
public:
	CDeviceTree();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeviceTree)
	//}}AFX_VIRTUAL

// Implementation
public:
	void EnumDevices();
	virtual ~CDeviceTree();

private:
	int EnumDevices(int index, TCHAR* DeviceClassName, TCHAR* DeviceName);
	int EnumDeviceClasses(int index, TCHAR* DeviceClassName, 
					TCHAR* DeviceClassDesc, BOOL* DevicePresent, int* ClassImage);
	
	SP_CLASSIMAGELIST_DATA m_ImageListData;
	CImageList m_ImageList;
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CDeviceTree)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // _DEVICE_TREE_H_
