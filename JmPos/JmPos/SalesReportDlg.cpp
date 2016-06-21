// SalesReportDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "JmPos.h"
#include "SalesReportDlg.h"
#include "afxdialogex.h"


// CSalesReportDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSalesReportDlg, CDialog)

CSalesReportDlg::CSalesReportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSalesReportDlg::IDD, pParent)
{

}

CSalesReportDlg::~CSalesReportDlg()
{
}

void CSalesReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSalesReportDlg, CDialog)
END_MESSAGE_MAP()


// CSalesReportDlg 메시지 처리기입니다.
