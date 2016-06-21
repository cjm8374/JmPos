// MenuManagerDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "JmPos.h"
#include "MenuManagerDlg.h"
#include "afxdialogex.h"


// CMenuManagerDlg ��ȭ �����Դϴ�.

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


// CMenuManagerDlg �޽��� ó�����Դϴ�.


BOOL CMenuManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CListCtrl* MenuList = (CListCtrl*)this->GetDlgItem(IDC_LIST_MENUMGR_MENU);
	MenuList->InsertColumn(0, _T("�޴�"), LVCFMT_LEFT, 120);
	MenuList->InsertColumn(1, _T("����"), LVCFMT_LEFT, 100);
	MenuList->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	UpdateMenuList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CMenuManagerDlg::OnBnClickedBtnMenumgrInsert()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	
	CString strMenuName, strMenuPrice;
	this->GetDlgItem(IDC_EDIT_MENUMGR_NAME)->GetWindowText(strMenuName);
	this->GetDlgItem(IDC_EDIT_MENUMGR_PRICE)->GetWindowText(strMenuPrice);

	strMenuName.Trim();
	strMenuPrice.Trim();
	if (strMenuName == _T("") || strMenuPrice == _T(""))
	{
		AfxMessageBox(_T("�޴�, ������ ����� �Է��� �ֽʽÿ�"));
		return;
	}
	
	char szQuery[1024] = { 0 };
	sprintf_s(szQuery, "insert into tblMenu (menu_name,menu_price) values ('%s',%d);"
		,strMenuName, ::_ttoi(strMenuPrice));

	int result = g_SqlMgr.execDML(szQuery);
	if (result <= 0)
	{
		AfxMessageBox(_T("DB �޴� ��� ����"));
	}

	UpdateMenuList();
}


void CMenuManagerDlg::OnBnClickedBtnMenumgrUpdate()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CMenuManagerDlg::OnBnClickedBtnMenumgrDelete()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CString strMenuName;
	this->GetDlgItem(IDC_EDIT_MENUMGR_NAME)->GetWindowText(strMenuName);

	char szQuery[1024] = { 0 };
	sprintf_s(szQuery, "delete from tblMenu where menu_name='%s';", strMenuName);

	int result = g_SqlMgr.execDML(szQuery);
	if (result <= 0)
	{
		AfxMessageBox(_T("DB �޴� ���� ����"));
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
	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.	
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
