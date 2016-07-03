// OrderManagerDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "JmPos.h"
#include "OrderManagerDlg.h"
#include "afxdialogex.h"


// COrderManagerDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(COrderManagerDlg, CDialog)

COrderManagerDlg::COrderManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COrderManagerDlg::IDD, pParent)
	, m_nTotalPrice(0)
{

}

COrderManagerDlg::COrderManagerDlg(CWnd* pParent, int nMode, int  TableIndex)
	: CDialog(COrderManagerDlg::IDD, pParent)
	, m_nTableIndex(TableIndex)
	, m_nTotalPrice(0)
{
	m_nMode = nMode;
}

COrderManagerDlg::~COrderManagerDlg()
{
}

void COrderManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COrderManagerDlg, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ORDERMGR_MENUS, &COrderManagerDlg::OnNMDblclkListOrdermgrMenus)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ORDERMGR_ORDERS, &COrderManagerDlg::OnNMDblclkListOrdermgrOrders)
	ON_BN_CLICKED(IDC_BTN_ORDERMGR_OK, &COrderManagerDlg::OnBnClickedBtnOrdermgrOk)
	ON_BN_CLICKED(IDC_BUTTON_ORDERMGR_CANCEL, &COrderManagerDlg::OnBnClickedButtonOrdermgrCancel)
END_MESSAGE_MAP()


// COrderManagerDlg 메시지 처리기입니다.


BOOL COrderManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CListCtrl* MenuList = (CListCtrl*)GetDlgItem(IDC_LIST_ORDERMGR_MENUS);
	MenuList->InsertColumn(0, _T("메뉴"), LVCFMT_LEFT, 120);
	MenuList->InsertColumn(1, _T("가격"), LVCFMT_LEFT, 80);
	MenuList->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CListCtrl* OrderList = (CListCtrl*)GetDlgItem(IDC_LIST_ORDERMGR_ORDERS);
	OrderList->InsertColumn(0, _T("메뉴"), LVCFMT_LEFT, 120);
	OrderList->InsertColumn(1, _T("수량"), LVCFMT_LEFT, 40);
	OrderList->InsertColumn(2, _T("가격"), LVCFMT_LEFT, 80);
	OrderList->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
	UpdateMenuList();

	InitOrderList();

	if (m_nMode == ORDER_MODE)
	{
		this->SetWindowTextA(_T("주문"));
		this->GetDlgItem(IDC_BTN_ORDERMGR_OK)->SetWindowTextA(_T("주문"));
	}
	else
	{
		this->SetWindowTextA(_T("계산"));
		this->GetDlgItem(IDC_BTN_ORDERMGR_OK)->SetWindowTextA(_T("계산"));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void COrderManagerDlg::UpdateMenuList()
{
	CListCtrl* MenuList = (CListCtrl*)this->GetDlgItem(IDC_LIST_ORDERMGR_MENUS);
	char szQuery[1024] = { 0 };
	int index = 0;

	MenuList->DeleteAllItems();
	sprintf_s(szQuery, "select menu_name,menu_price from tblMenu order by menu_name");
	CppSQLite3Query data = g_SqlMgr.execQuery(szQuery);

	while (!data.eof())
	{
		index = MenuList->GetItemCount();
		MenuList->InsertItem(index, data.fieldValue(0));
		MenuList->SetItemText(index, 1, data.fieldValue(1));
		data.nextRow();
	}

	UpdateData(FALSE);
}

void COrderManagerDlg::OnNMDblclkListOrdermgrMenus(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CListCtrl* MenuList = (CListCtrl*)this->GetDlgItem(IDC_LIST_ORDERMGR_MENUS);
	int index = pNMItemActivate->iItem;
	if (index != -1)
	{
		InsertOrder(MenuList->GetItemText(index, 0), MenuList->GetItemText(index, 1));
	}
	*pResult = 0;
}


void COrderManagerDlg::OnNMDblclkListOrdermgrOrders(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CListCtrl* OrderList = (CListCtrl*)this->GetDlgItem(IDC_LIST_ORDERMGR_ORDERS);
	int index = pNMItemActivate->iItem;
	if (index != -1)
	{
		DeleteOrder(OrderList->GetItemText(index, 0));
	}
	*pResult = 0;
}

void COrderManagerDlg::InsertOrder(CString strMenu, CString strPrice)
{
	CListCtrl* OrderList = (CListCtrl*)this->GetDlgItem(IDC_LIST_ORDERMGR_ORDERS);
	
	for (int i = 0; i < OrderList->GetItemCount(); i++)
	{
		if (strMenu == OrderList->GetItemText(i, 0))
		{
			int nMenuCount = ::_ttoi(OrderList->GetItemText(i, 1));
			nMenuCount++;
			CString strMenuCount;
			strMenuCount.Format(_T("%d"), nMenuCount);
			OrderList->SetItemText(i, 1, strMenuCount);
			UpdateTotalPrice();
			UpdateData(FALSE);
			return;
		}
	}

	int nInsertIndex = OrderList->GetItemCount();
	OrderList->InsertItem(nInsertIndex, strMenu);
	OrderList->SetItemText(nInsertIndex, 1, _T("1"));
	OrderList->SetItemText(nInsertIndex, 2, strPrice);
	UpdateTotalPrice();
	UpdateData(FALSE);
}

void COrderManagerDlg::DeleteOrder(CString strMenu)
{
	CListCtrl* OrderList = (CListCtrl*)this->GetDlgItem(IDC_LIST_ORDERMGR_ORDERS);
	
	for (int i = 0; i < OrderList->GetItemCount(); i++)
	{
		if (strMenu == OrderList->GetItemText(i, 0))
		{
			int nMenuCount = ::_ttoi(OrderList->GetItemText(i, 1));
			nMenuCount--;
			if (nMenuCount == 0)
			{
				OrderList->DeleteItem(i);
				UpdateTotalPrice();
				UpdateData(FALSE);
				break;
			}

			CString strMenuCount;
			strMenuCount.Format(_T("%d"), nMenuCount);
			OrderList->SetItemText(i, 1, strMenuCount);
			UpdateTotalPrice();
			UpdateData(FALSE);
			return;
		}
	}
}

void COrderManagerDlg::UpdateTotalPrice()
{
	UpdateData(TRUE);

	CListCtrl* OrderList = (CListCtrl*)this->GetDlgItem(IDC_LIST_ORDERMGR_ORDERS);
	
	int nPrice = 0;
	int nCount = 0;
	int nTotalPrice = 0;

	for (int i = 0; i < OrderList->GetItemCount(); i++)
	{
		nCount = _ttoi(OrderList->GetItemText(i, 1));
		nPrice = _ttoi(OrderList->GetItemText(i, 2));
		nTotalPrice += (nCount * nPrice);
	}

	m_nTotalPrice = nTotalPrice;

	CString strTotalPrice;
	strTotalPrice.Format(_T("%d"), nTotalPrice);

	CString strMoney;
	ConvertMoneyString(strTotalPrice, strMoney);
	this->GetDlgItem(IDC_EDIT_ORDERMGR_PRICE)->SetWindowTextA(strMoney);
}

void COrderManagerDlg::OnBnClickedBtnOrdermgrOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (m_nMode == PAY_MODE)
	{
		int nResult = AfxMessageBox(_T("계산을 완료 하시겠습니까?"), MB_OKCANCEL);
		if (nResult == IDOK)
		{
			CListCtrl* OrderList = (CListCtrl*)this->GetDlgItem(IDC_LIST_ORDERMGR_ORDERS);
			CString strOrder;
			for (int i = 0; i < OrderList->GetItemCount(); i++)
			{
				strOrder += OrderList->GetItemText(i, 0);
				strOrder += _T('|');
				strOrder += OrderList->GetItemText(i, 1);
				strOrder += _T('|');
				strOrder += OrderList->GetItemText(i, 2);
				strOrder += _T('|');
			}
			
			char szQuery[1024];
			sprintf_s(szQuery, "insert into tblSales (sale_date,sale_table,sale_menu,sale_total_price) values ('%s',%d,'%s',%d);"
				, GetDateString(), m_nTableIndex, strOrder, m_nTotalPrice);
			g_SqlMgr.execDML(szQuery);

			CString strTableIndex;
			strTableIndex.Format(_T("TABLE%d"), m_nTableIndex);
			theApp.WriteProfileStringA(strTableIndex, _T("Order"), _T(""));
		}
		else
		{
			return;
		}
	}
	else
	{
		CListCtrl* OrderList = (CListCtrl*)this->GetDlgItem(IDC_LIST_ORDERMGR_ORDERS);
		CString strOrder;
		for (int i = 0; i < OrderList->GetItemCount(); i++)
		{
			strOrder += OrderList->GetItemText(i, 0);
			strOrder += _T('|');
			strOrder += OrderList->GetItemText(i, 1);
			strOrder += _T('|');
			strOrder += OrderList->GetItemText(i, 2);
			strOrder += _T('|');
		}

		CString strTableIndex;
		strTableIndex.Format(_T("TABLE%d"), m_nTableIndex);
		theApp.WriteProfileStringA(strTableIndex, _T("Order"), strOrder);
	}

	OnOK();
}


void COrderManagerDlg::OnBnClickedButtonOrdermgrCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}

void COrderManagerDlg::InitOrderList()
{
	CListCtrl* OrderList = (CListCtrl*)this->GetDlgItem(IDC_LIST_ORDERMGR_ORDERS);

	CString strTableIndex;
	strTableIndex.Format(_T("TABLE%d"), m_nTableIndex);

	CString strOrder = theApp.GetProfileStringA(strTableIndex, _T("Order"), NULL);
	vector<stOrder> vecOrder = ParsingOrderString(strOrder);

	if (vecOrder.empty() == false)
	{
		OrderList->DeleteAllItems();
		for (vector<stOrder>::size_type i = 0; i < vecOrder.size(); i++)
		{
			int nIndex = OrderList->GetItemCount();
			OrderList->InsertItem(nIndex, vecOrder[i].strMenu);
			OrderList->SetItemText(nIndex, 1, vecOrder[i].strCount);
			OrderList->SetItemText(nIndex, 2, vecOrder[i].strPrice);
		}
		UpdateData(FALSE);
	}

	UpdateTotalPrice();	
}