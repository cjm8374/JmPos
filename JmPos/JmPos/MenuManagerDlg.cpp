// MenuManagerDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "JmPos.h"
#include "MenuManagerDlg.h"
#include "afxdialogex.h"


// CMenuManagerDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMenuManagerDlg, CDialog)

CMenuManagerDlg::CMenuManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMenuManagerDlg::IDD, pParent)
{

}

CMenuManagerDlg::~CMenuManagerDlg()
{
}

void CMenuManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMenuManagerDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_MENUMGR_INSERT, &CMenuManagerDlg::OnBnClickedBtnMenumgrInsert)
	ON_BN_CLICKED(IDC_BTN_MENUMGR_UPDATE, &CMenuManagerDlg::OnBnClickedBtnMenumgrUpdate)
	ON_BN_CLICKED(IDC_BTN_MENUMGR_DELETE, &CMenuManagerDlg::OnBnClickedBtnMenumgrDelete)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MENUMGR_MENU, &CMenuManagerDlg::OnNMClickListMenumgrMenu)
END_MESSAGE_MAP()


// CMenuManagerDlg 메시지 처리기입니다.


BOOL CMenuManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CListCtrl* MenuList = (CListCtrl*)this->GetDlgItem(IDC_LIST_MENUMGR_MENU);
	MenuList->InsertColumn(0, _T("메뉴"), LVCFMT_LEFT, 120);
	MenuList->InsertColumn(1, _T("가격"), LVCFMT_LEFT, 100);
	MenuList->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	UpdateMenuList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMenuManagerDlg::OnBnClickedBtnMenumgrInsert()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	
	CString strMenuName, strMenuPrice;
	this->GetDlgItem(IDC_EDIT_MENUMGR_NAME)->GetWindowText(strMenuName);
	this->GetDlgItem(IDC_EDIT_MENUMGR_PRICE)->GetWindowText(strMenuPrice);

	strMenuName.Trim();
	strMenuPrice.Trim();
	if (strMenuName == _T("") || strMenuPrice == _T(""))
	{
		AfxMessageBox(_T("메뉴, 가격을 제대로 입력해 주십시오"));
		return;
	}
	
	char szQuery[1024] = { 0 };
	sprintf_s(szQuery, "insert into tblMenu (menu_name,menu_price) values ('%s',%d);"
		,strMenuName, ::_ttoi(strMenuPrice));

	int result = g_SqlMgr.execDML(szQuery);
	if (result <= 0)
	{
		AfxMessageBox(_T("DB 메뉴 등록 실패"));
	}

	UpdateMenuList();
}


void CMenuManagerDlg::OnBnClickedBtnMenumgrUpdate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMenuManagerDlg::OnBnClickedBtnMenumgrDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString strMenuName;
	this->GetDlgItem(IDC_EDIT_MENUMGR_NAME)->GetWindowText(strMenuName);

	char szQuery[1024] = { 0 };
	sprintf_s(szQuery, "delete from tblMenu where menu_name='%s';", strMenuName);

	int result = g_SqlMgr.execDML(szQuery);
	if (result <= 0)
	{
		AfxMessageBox(_T("DB 메뉴 삭제 실패"));
	}
	
	UpdateMenuList();
}


void CMenuManagerDlg::UpdateMenuList()
{
	CListCtrl* MenuList = (CListCtrl*)this->GetDlgItem(IDC_LIST_MENUMGR_MENU);
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


void CMenuManagerDlg::OnNMClickListMenumgrMenu(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.	
	CListCtrl* MenuList = (CListCtrl*)this->GetDlgItem(IDC_LIST_MENUMGR_MENU);
	int index = pNMItemActivate->iItem;
	if(index >= 0 && index < MenuList->GetItemCount())
    {
		this->GetDlgItem(IDC_EDIT_MENUMGR_NAME)->SetWindowTextA(MenuList->GetItemText(index, 0));
		this->GetDlgItem(IDC_EDIT_MENUMGR_PRICE)->SetWindowTextA(MenuList->GetItemText(index, 1));		
    }
	else
	{
		this->GetDlgItem(IDC_EDIT_MENUMGR_NAME)->SetWindowTextA("");
		this->GetDlgItem(IDC_EDIT_MENUMGR_PRICE)->SetWindowTextA("");
	}
	UpdateData(FALSE);

	*pResult = 0;
}
