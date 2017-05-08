; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDeviceTreeDlg
LastTemplate=CTreeCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DeviceTreeDlg.h"

ClassCount=3
Class1=CDeviceTreeDlgApp
Class2=CDeviceTreeDlg

ResourceCount=3
Resource2=IDD_DEVICETREEDLG_DIALOG
Resource1=IDR_MAINFRAME
Class3=CDeviceTree
Resource3=IDD_DEVICETREEDLG_DIALOG (English (U.S.))

[CLS:CDeviceTreeDlgApp]
Type=0
HeaderFile=DeviceTreeDlg.h
ImplementationFile=DeviceTreeDlg.cpp
Filter=N

[CLS:CDeviceTreeDlg]
Type=0
HeaderFile=DeviceTreeDialog.h
ImplementationFile=DeviceTreeDialog.cpp
Filter=D
LastObject=IDC_TREE1
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_DEVICETREEDLG_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CDeviceTreeDlg

[DLG:IDD_DEVICETREEDLG_DIALOG (English (U.S.))]
Type=1
Class=CDeviceTreeDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_DEVICE_TREE,SysTreeView32,1342242823

[CLS:CDeviceTree]
Type=0
HeaderFile=DeviceTree.h
ImplementationFile=DeviceTree.cpp
BaseClass=CTreeCtrl
Filter=W

