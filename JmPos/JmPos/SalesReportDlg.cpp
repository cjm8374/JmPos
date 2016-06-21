// SalesReportDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "JmPos.h"
#include "SalesReportDlg.h"
#include "afxdialogex.h"
#include <map>

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
	ON_BN_CLICKED(IDC_BTN_SALESREPORT_SEARCH, &CSalesReportDlg::OnBnClickedBtnSalesreportSearch)
	ON_BN_CLICKED(IDC_BTN_SALESREPORT_VIEW_MENUS, &CSalesReportDlg::OnBnClickedBtnSalesreportViewMenus)
END_MESSAGE_MAP()


// CSalesReportDlg 메시지 처리기입니다.


void CSalesReportDlg::OnBnClickedBtnSalesreportSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strYear, strMonth, strDay;
	GetDlgItem(IDC_EDIT_SALESREPORT_YEAR)->GetWindowTextA(strYear);
	GetDlgItem(IDC_EDIT_SALESREPORT_MONTH)->GetWindowTextA(strMonth);
	GetDlgItem(IDC_EDIT_SALESREPORT_DAY)->GetWindowTextA(strDay);

	strYear.Trim();
	strMonth.Trim();
	strDay.Trim();

	CString strDateSearch;
	strDateSearch += _T("'%%%");
	if (strYear != _T(""))
	{
		strDateSearch += (strYear + _T("-"));
	}
	else
	{
		return;
	}
	if (strMonth != _T(""))
	{
		strDateSearch += (strMonth + _T("-"));
	}
	if (strDay != _T(""))
	{
		strDateSearch += strDay;
	}
	strDateSearch += _T("%%%'");

	char szQuery[1024] = { 0 };
	sprintf_s(szQuery, "select count(sale_table) as count_table, sum(sale_total_price) as sum_price from tblSales where sale_date like %s", strDateSearch);

	CppSQLite3Query data = g_SqlMgr.execQuery(szQuery);
	if(!data.eof())
	{
		GetDlgItem(IDC_EDIT_SALESREPORT_TABLECOUNT)->SetWindowTextA(data.fieldValue(0));
		GetDlgItem(IDC_EDIT_SALESREPORT_TOTALPRICE)->SetWindowTextA(data.fieldValue(1));
	}
}

void CSalesReportDlg::OnBnClickedBtnSalesreportViewMenus()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strYear, strMonth, strDay;
	GetDlgItem(IDC_EDIT_SALESREPORT_YEAR)->GetWindowTextA(strYear);
	GetDlgItem(IDC_EDIT_SALESREPORT_MONTH)->GetWindowTextA(strMonth);
	GetDlgItem(IDC_EDIT_SALESREPORT_DAY)->GetWindowTextA(strDay);

	strYear.Trim();
	strMonth.Trim();
	strDay.Trim();

	CString strDateSearch;
	strDateSearch += _T("'%%");
	if (strYear != _T(""))
	{
		strDateSearch += (strYear + _T("-"));
	}
	else
	{
		return;
	}
	if (strMonth != _T(""))
	{
		strDateSearch += (strMonth + _T("-"));
	}
	if (strDay != _T(""))
	{
		strDateSearch += strDay;
	}
	strDateSearch += _T("%%'");

	char szQuery[1024] = { 0 };
	sprintf_s(szQuery, "select sale_menu from tblSales where sale_date like %s;", strDateSearch);
	
	map<CString, int> mapOrderList;
	CppSQLite3Query data = g_SqlMgr.execQuery(szQuery);
	
	if (!data.eof())
	{
		CString strOrder(data.fieldValue(0));
		vector<stOrder> vecOrder = ParsingOrderString(strOrder);
		for (vector<stOrder>::size_type i = 0; i < vecOrder.size(); i++)
		{
			map<CString, int>::iterator iter = mapOrderList.find(vecOrder[i].strMenu);
			if (iter == mapOrderList.end())
			{
				mapOrderList[vecOrder[i].strMenu] = _ttoi(vecOrder[i].strCount);
			}
			else
			{
				mapOrderList[vecOrder[i].strMenu] += _ttoi(vecOrder[i].strCount);
			}
		}
		data.nextRow();
	}

	CListCtrl* pOrderList = (CListCtrl*)GetDlgItem(IDC_LIST_SALESREPORT_MENUS);
	pOrderList->DeleteAllItems();
	
	for (map<CString, int>::iterator iter = mapOrderList.begin();iter != mapOrderList.end(); iter++)
	{
		int nIndex = pOrderList->GetItemCount();
		pOrderList->InsertItem(nIndex, iter->first);

		CString strTemp;
		strTemp.Format(_T("%d"), iter->second);
		pOrderList->SetItemText(nIndex, 1, strTemp);
	}

	/*vector<stOrder> vecOrder = ParsingOrderString(strOrder);

	if (vecOrder.empty() == false)
	{
		pOrderList->DeleteAllItems();
		for (vector<stOrder>::size_type i = 0; i < vecOrder.size(); i++)
		{
			int nIndex = pOrderList->GetItemCount();
			pOrderList->InsertItem(nIndex, vecOrder[i].strMenu);
			pOrderList->SetItemText(nIndex, 1, vecOrder[i].strCount);
		}
		UpdateData(FALSE);
	}*/
}

BOOL CSalesReportDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CListCtrl* OrderList = (CListCtrl*)GetDlgItem(IDC_LIST_SALESREPORT_MENUS);
	OrderList->InsertColumn(0, _T("메뉴"), LVCFMT_LEFT, 120);
	OrderList->InsertColumn(1, _T("수량"), LVCFMT_CENTER, 40);
	//OrderList->InsertColumn(2, _T("가격"), LVCFMT_LEFT, 80);
	OrderList->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
