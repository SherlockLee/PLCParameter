// PLCParameter.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPLCParameterApp:
// �йش����ʵ�֣������ PLCParameter.cpp
//

class CPLCParameterApp : public CWinApp
{
public:
	CPLCParameterApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPLCParameterApp theApp;