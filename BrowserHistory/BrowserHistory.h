
// BrowserHistory.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBrowserHistoryApp: 
// �йش����ʵ�֣������ BrowserHistory.cpp
//

class CBrowserHistoryApp : public CWinApp
{
public:
	CBrowserHistoryApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBrowserHistoryApp theApp;
