
// JmPos.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CJmPosApp:
// �� Ŭ������ ������ ���ؼ��� JmPos.cpp�� �����Ͻʽÿ�.
//

class CJmPosApp : public CWinApp
{
public:
	CJmPosApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CJmPosApp theApp;