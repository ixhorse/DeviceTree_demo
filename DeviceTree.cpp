// DeviceTree.cpp : implementation file
//

#include "stdafx.h"
#include "DeviceTreeDlg.h"
#include "DeviceTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma message("CDeviceTree - A tree control for showing installed devices - By A. Riazi (a.riazi@misbah3com.com)")
/////////////////////////////////////////////////////////////////////////////
// CDeviceTree

CDeviceTree::CDeviceTree()
{
}

CDeviceTree::~CDeviceTree()
{
}


BEGIN_MESSAGE_MAP(CDeviceTree, CTreeCtrl)
	//{{AFX_MSG_MAP(CDeviceTree)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeviceTree message handlers

int CDeviceTree::EnumDeviceClasses(int index, 
								   TCHAR* DeviceClassName, 
								   TCHAR* DeviceClassDesc, 
								   BOOL* DevicePresent,
								   int* ClassImage)
{
	GUID ClassGuid;
	ZeroMemory(&ClassGuid, sizeof(GUID));

	HDEVINFO NewDeviceInfoSet;
   
	int result;
	TCHAR* name=new TCHAR[MAX_DEV_LEN];
	BOOL resNam=FALSE;
	ULONG RequiredSize=MAX_DEV_LEN;

	result = CM_Enumerate_Classes(index, &ClassGuid, 0);

	*DevicePresent=FALSE;
   
	//incorrect device class:
	if (result == CR_INVALID_DATA)
		return -2;
	  
	//device class is absent
	if(result == CR_NO_SUCH_VALUE)
		return -1;
	
	//bad param. - fatal error
	if(result != CR_SUCCESS)
		return -3;

	resNam=SetupDiClassNameFromGuid(&ClassGuid, name, RequiredSize, &RequiredSize);
	if(RequiredSize > 0)
	{
		delete [] name;
		name=new TCHAR[RequiredSize];
		resNam=SetupDiClassNameFromGuid(&ClassGuid, name, RequiredSize, &RequiredSize);
    }

	SetupDiGetClassImageIndex(&m_ImageListData, &ClassGuid, ClassImage);
	NewDeviceInfoSet=SetupDiGetClassDevs(&ClassGuid, 0, NULL, DIGCF_PRESENT);

	if (NewDeviceInfoSet == INVALID_HANDLE_VALUE)
    {  
		*DevicePresent=FALSE;
		_tcscpy(DeviceClassName, name);

		delete [] name;
		name=NULL;
		return 0;
	}

   HKEY KeyClass=SetupDiOpenClassRegKeyEx(&ClassGuid, 
							MAXIMUM_ALLOWED, 
							DIOCR_INSTALLER,
							NULL, 
							0);

	if (KeyClass == INVALID_HANDLE_VALUE)
	{  
		*DevicePresent=FALSE;
		_tcscpy(DeviceClassName, name);

		delete [] name;
		name=NULL;
		return 0;
	}
	else
	{
		long dwSize=MAX_DEV_LEN;
		int res=RegQueryValue(KeyClass, NULL, DeviceClassDesc, &dwSize);

		if (res != ERROR_SUCCESS)
		_tcscpy(DeviceClassDesc, _T(""));
	}
   
	SetupDiDestroyDeviceInfoList(NewDeviceInfoSet);

    _tcscpy(DeviceClassName, name);
    *DevicePresent=TRUE;

	RegCloseKey(KeyClass);
	
	delete [] name;
	name=NULL;
	return 0;
}

int CDeviceTree::EnumDevices(int index, 
							 TCHAR* DeviceClassName, 
							 TCHAR* DeviceName)
{
	ULONG RequiredSize = 0;
	GUID guid;
	ZeroMemory(&guid, sizeof(GUID));
	GUID* guids = new GUID[1];
         
	HDEVINFO NewDeviceInfoSet;
	SP_DEVINFO_DATA DeviceInfoData;

	BOOL res=SetupDiClassGuidsFromName(DeviceClassName, &guids[0], 
							RequiredSize, &RequiredSize);

	if (RequiredSize==0)
	{
		//incorrect class name:
		_tcscpy(DeviceName, _T(""));
		return -2;
	}

	if (!res)
	{
		delete [] guids;
		guids=new GUID[RequiredSize];
		res=SetupDiClassGuidsFromName(DeviceClassName, &guids[0], 
							RequiredSize, &RequiredSize);

		if (!res || RequiredSize==0)
		{
			//incorrect class name:
			_tcscpy(DeviceName, _T(""));
			return -2;
		}
	}

	//get device info set for our device class
	NewDeviceInfoSet=SetupDiGetClassDevs(&guids[0], 0, NULL, DIGCF_PRESENT);
	
	if(NewDeviceInfoSet == INVALID_HANDLE_VALUE)
		if(!res)
		{
			//device information is unavailable:
			_tcscpy(DeviceName, _T(""));
			return -3;
		}

	DeviceInfoData.cbSize = 28;
	//is devices exist for class
	DeviceInfoData.DevInst=0;
	ZeroMemory(&DeviceInfoData.ClassGuid, sizeof(GUID));
	DeviceInfoData.Reserved=0;

	res=SetupDiEnumDeviceInfo(NewDeviceInfoSet, index, &DeviceInfoData);

	if (!res) 
	{
		//no such device:
		SetupDiDestroyDeviceInfoList(NewDeviceInfoSet);
		_tcscpy(DeviceName, _T(""));
		return -1;
	}


	if (!SetupDiGetDeviceRegistryProperty(NewDeviceInfoSet, &DeviceInfoData,
							SPDRP_FRIENDLYNAME, 0, (BYTE*) DeviceName, 
							MAX_DEV_LEN, NULL))
	{
		res = SetupDiGetDeviceRegistryProperty(NewDeviceInfoSet, &DeviceInfoData,
							SPDRP_DEVICEDESC, 0, (BYTE*) DeviceName,
							MAX_DEV_LEN, NULL);
		if (!res)
		{
			//incorrect device name:
			SetupDiDestroyDeviceInfoList(NewDeviceInfoSet);
			_tcscpy(DeviceName, _T(""));
			return -4;
		}
	}
    
	return 0;
}

void CDeviceTree::EnumDevices()
{
	DeleteAllItems();
	
	//Set Image List 
	m_ImageListData.cbSize = sizeof(m_ImageListData);
	SetupDiGetClassImageList(&m_ImageListData);

	m_ImageList.Attach(m_ImageListData.ImageList);
	CBitmap myComputer;
	myComputer.LoadBitmap(IDB_MYCOMPUTER);
	COLORREF colormask=RGB(255, 0, 255);
	m_ImageList.Add(&myComputer, colormask);
	
	SetImageList(&m_ImageList, TVSIL_NORMAL);
	HTREEITEM hRoot, hDeviceClasses;
	
	TCHAR ComputerName[MAX_PATH];
    DWORD dwSize = MAX_PATH;
    
	GetComputerName(ComputerName, &dwSize);

	int ComputerImage=m_ImageList.GetImageCount() - 1;
	hRoot=InsertItem(ComputerName, ComputerImage, ComputerImage);
	
	TCHAR classes[MAX_DEV_LEN];
	TCHAR classesDesc[MAX_DEV_LEN];

	BOOL DevExist=FALSE;
	int index=0;
	int DeviceImage;
	int res=EnumDeviceClasses(index , classes, classesDesc, &DevExist, &DeviceImage);
   
	while (res!=-1)
	{
		if (res >= -1 && DevExist) 
		{	
			//Add New Device Entry to Tree
			if (_tcsicmp(classesDesc, _T(""))==0)
				hDeviceClasses=InsertItem((LPCTSTR) classes, 
					DeviceImage, DeviceImage, hRoot);
			else
				hDeviceClasses=InsertItem((LPCTSTR) classesDesc, 
					DeviceImage, DeviceImage, hRoot);
			
			//loop for enumerating devices of specefic class!
			int result, DevIndex=0;
			TCHAR DeviceName[MAX_DEV_LEN]=_T("");
			
			result=EnumDevices(DevIndex, classes, DeviceName);
			
			while (result!=-1)
			{
				if (result == 0)
					InsertItem(DeviceName, DeviceImage, DeviceImage, hDeviceClasses);
					
				DevIndex++;
				result=EnumDevices(DevIndex, classes, DeviceName);
			}

			if (GetChildItem(hDeviceClasses)==NULL)
				DeleteItem(hDeviceClasses);
			else
				SortChildren(hDeviceClasses);

		}

		index++;
		res=EnumDeviceClasses(index, classes, classesDesc, &DevExist, &DeviceImage);
	}

	Expand(hRoot, TVE_EXPAND);
	SortChildren(hRoot);
}
