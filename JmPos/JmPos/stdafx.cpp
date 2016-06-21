
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// JmPos.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"
CppSQLite3DB g_SqlMgr;

CString GetModuleFilePath(void)
{
	TCHAR szFilePath[1024]={0};
	CString strFilePath;
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	strFilePath.Format(_T("%s"), szFilePath);
	strFilePath = strFilePath.Left(strFilePath.ReverseFind('\\'));
	return strFilePath;
}

vector<stOrder> ParsingOrderString(CString strOrder)
{
	vector<stOrder> vecOrder;
	CString strTemp;
	int nCount = 0;
	stOrder stOrderTemp;

	while (TRUE)
	{
		strTemp = _T("");
		AfxExtractSubString(strTemp, strOrder, nCount, '|');
		if (nCount % 3 == 0)
		{
			stOrderTemp.strMenu = strTemp;
		}
		if (nCount % 3 == 1)
		{
			stOrderTemp.strCount = strTemp;
		}
		if (nCount % 3 == 2)
		{
			stOrderTemp.strPrice = strTemp;
			vecOrder.push_back(stOrderTemp);
		}
		nCount++;

		if (strTemp == _T(""))
		{
			break;
		}		
	}
	return vecOrder;
}

CString GetDateString()
{
	CTime cTime = CTime::GetCurrentTime();
	CString strDate;
	strDate.Format(_T("%02d-%02d-%02d")
		, cTime.GetYear(), cTime.GetMonth(), cTime.GetDay());
	return strDate;
}