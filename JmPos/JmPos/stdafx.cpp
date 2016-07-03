
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// JmPos.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

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

void ConvertMoneyString(CString parm_data, CString &parm_string)
{
    // ������� ��Ȯ�ϰ� �����ϱ� ���ؼ� ',' ó������� ����� ���ڿ� ������ �ʱ�ȭ�Ѵ�.
    if(parm_string.GetLength()) parm_string.Format("");
    // ���ڿ��� ���̸� ���Ѵ�.
    int count = parm_data.GetLength();
 
    for(int i = 0; i < count; i++)
	{
        // 3�� ����� �� "," �� ���ڿ��� �߰��Ѵ�.
        if(i && !(i % 3)) parm_string = "," + parm_string;
        // parm_data ���� parm_string���� �����Ѱ��� ���������� �����Ѵ�.
        parm_string = CString(parm_data[count - 1 - i]) + parm_string;
    }
}