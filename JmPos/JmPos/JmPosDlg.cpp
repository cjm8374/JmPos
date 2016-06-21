
// JmPosDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "JmPos.h"
#include "JmPosDlg.h"
#include "afxdialogex.h"
#include "MenuManagerDlg.h"
#include "OrderManagerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CJmPosDlg 대화 상자



CJmPosDlg::CJmPosDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJmPosDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJmPosDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CJmPosDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_MENU, &CJmPosDlg::OnBnClickedBtnMenu)
	ON_BN_CLICKED(IDC_BTN_ORDER1, &CJmPosDlg::OnBnClickedBtnOrder1)
	ON_BN_CLICKED(IDC_BTN_PAY1, &CJmPosDlg::OnBnClickedBtnPay1)
	ON_BN_CLICKED(IDC_BTN_ORDER2, &CJmPosDlg::OnBnClickedBtnOrder2)
	ON_BN_CLICKED(IDC_BTN_PAY2, &CJmPosDlg::OnBnClickedBtnPay2)
	ON_BN_CLICKED(IDC_BTN_ORDER3, &CJmPosDlg::OnBnClickedBtnOrder3)
	ON_BN_CLICKED(IDC_BTN_PAY3, &CJmPosDlg::OnBnClickedBtnPay3)
	ON_BN_CLICKED(IDC_BTN_ORDER4, &CJmPosDlg::OnBnClickedBtnOrder4)
	ON_BN_CLICKED(IDC_BTN_PAY4, &CJmPosDlg::OnBnClickedBtnPay4)
	ON_BN_CLICKED(IDC_BTN_ORDER5, &CJmPosDlg::OnBnClickedBtnOrder5)
	ON_BN_CLICKED(IDC_BTN_PAY5, &CJmPosDlg::OnBnClickedBtnPay5)
	ON_BN_CLICKED(IDC_BTN_ORDER6, &CJmPosDlg::OnBnClickedBtnOrder6)
	ON_BN_CLICKED(IDC_BTN_PAY6, &CJmPosDlg::OnBnClickedBtnPay6)
	ON_BN_CLICKED(IDC_BTN_ORDER7, &CJmPosDlg::OnBnClickedBtnOrder7)
	ON_BN_CLICKED(IDC_BTN_PAY7, &CJmPosDlg::OnBnClickedBtnPay7)
	ON_BN_CLICKED(IDC_BTN_ORDER8, &CJmPosDlg::OnBnClickedBtnOrder8)
	ON_BN_CLICKED(IDC_BTN_PAY8, &CJmPosDlg::OnBnClickedBtnPay8)
	ON_BN_CLICKED(IDC_BTN_ORDER9, &CJmPosDlg::OnBnClickedBtnOrder9)
	ON_BN_CLICKED(IDC_BTN_PAY9, &CJmPosDlg::OnBnClickedBtnPay9)
	ON_BN_CLICKED(IDC_BTN_ORDER10, &CJmPosDlg::OnBnClickedBtnOrder10)
	ON_BN_CLICKED(IDC_BTN_PAY10, &CJmPosDlg::OnBnClickedBtnPay10)
	ON_BN_CLICKED(IDC_BTN_REPORT, &CJmPosDlg::OnBnClickedBtnReport)
END_MESSAGE_MAP()


// CJmPosDlg 메시지 처리기

BOOL CJmPosDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SetTableListColumn();
	
	CString strDBFilePath = GetModuleFilePath() + _T("\\JmPosDB.db");
	g_SqlMgr.open(strDBFilePath);
	g_SqlMgr.execDML("create table if not exists tblMenu (menu_name varchar(100), menu_price integer);");
	g_SqlMgr.execDML("create table if not exists tblSales (sale_date datetime, sale_table integer, sale_menu varchar(200), sale_total_price integer);");

	UpdateOrderList(1, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE1));
	UpdateOrderList(2, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE2));
	UpdateOrderList(3, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE3));
	UpdateOrderList(4, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE4));
	UpdateOrderList(5, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE5));
	UpdateOrderList(6, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE6));
	UpdateOrderList(7, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE7));
	UpdateOrderList(8, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE8));
	UpdateOrderList(9, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE9));
	UpdateOrderList(10, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE10));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CJmPosDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CJmPosDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CJmPosDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CJmPosDlg::SetTableListColumn(void)
{
	SetTableListColumn((CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE1));
	SetTableListColumn((CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE2));
	SetTableListColumn((CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE3));
	SetTableListColumn((CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE4));
	SetTableListColumn((CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE5));
	SetTableListColumn((CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE6));
	SetTableListColumn((CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE7));
	SetTableListColumn((CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE8));
	SetTableListColumn((CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE9));
	SetTableListColumn((CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE10));
}

void CJmPosDlg::SetTableListColumn(CListCtrl* pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("메뉴"), LVCFMT_LEFT, 120);
	pListCtrl->InsertColumn(1, _T("수량"), LVCFMT_LEFT, 40);	
	pListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}

void CJmPosDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	g_SqlMgr.close();
}

void CJmPosDlg::OnBnClickedBtnMenu()
{
	CMenuManagerDlg dlg;
	dlg.DoModal();
}


void CJmPosDlg::OnBnClickedBtnOrder1()
{
	COrderManagerDlg dlg(NULL, ORDER_MODE, 1);
	if (dlg.DoModal() == IDOK)
	{
		UpdateOrderList(1, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE1));
	}
}


void CJmPosDlg::OnBnClickedBtnPay1()
{
	COrderManagerDlg dlg(NULL, PAY_MODE, 1);
	if (dlg.DoModal() == IDOK)
	{
		UpdateOrderList(1, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE1));
	}
}


void CJmPosDlg::OnBnClickedBtnOrder2()
{
	COrderManagerDlg dlg(NULL, ORDER_MODE, 2);
	if (dlg.DoModal() == IDOK)
	{
		UpdateOrderList(2, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE2));
	}
}


void CJmPosDlg::OnBnClickedBtnPay2()
{
	COrderManagerDlg dlg(NULL, PAY_MODE, 2);
	if (dlg.DoModal() == IDOK)
	{
		UpdateOrderList(2, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE2));
	}
}


void CJmPosDlg::OnBnClickedBtnOrder3()
{
	COrderManagerDlg dlg(NULL, ORDER_MODE, 3);
	if (dlg.DoModal() == IDOK)
	{
		UpdateOrderList(3, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE3));
	}
}


void CJmPosDlg::OnBnClickedBtnPay3()
{
	COrderManagerDlg dlg(NULL, PAY_MODE, 3);
	if (dlg.DoModal() == IDOK)
	{
		UpdateOrderList(3, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE3));
	}
}


void CJmPosDlg::OnBnClickedBtnOrder4()
{
	COrderManagerDlg dlg(NULL, ORDER_MODE, 4);
	if (dlg.DoModal() == IDOK)
	{
		UpdateOrderList(4, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE4));
	}
}


void CJmPosDlg::OnBnClickedBtnPay4()
{
	COrderManagerDlg dlg(NULL, PAY_MODE, 4);
	if (dlg.DoModal() == IDOK)
	{
		UpdateOrderList(4, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE4));
	}
}


void CJmPosDlg::OnBnClickedBtnOrder5()
{
	COrderManagerDlg dlg(NULL, ORDER_MODE, 5);
	if (dlg.DoModal() == IDOK)
	{
		UpdateOrderList(5, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE5));
	}
}


void CJmPosDlg::OnBnClickedBtnPay5()
{
	COrderManagerDlg dlg(NULL, PAY_MODE, 5);
	if (dlg.DoModal() == IDOK)
	{
		UpdateOrderList(5, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE5));
	}
}


void CJmPosDlg::OnBnClickedBtnOrder6()
{
	COrderManagerDlg dlg(NULL, ORDER_MODE, 6);
	if (dlg.DoModal() == IDOK)
	{
		UpdateOrderList(6, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE6));
	}
}


void CJmPosDlg::OnBnClickedBtnPay6()
{
	COrderManagerDlg dlg(NULL, PAY_MODE, 6);
	if (dlg.DoModal() == IDOK)
	{
		UpdateOrderList(6, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE6));
	}
}


void CJmPosDlg::OnBnClickedBtnOrder7()
{
	COrderManagerDlg dlg(NULL, ORDER_MODE, 7);
	if (dlg.DoModal() == IDOK)
	{
		UpdateOrderList(7, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE7));
	}
}


void CJmPosDlg::OnBnClickedBtnPay7()
{
	COrderManagerDlg dlg(NULL, PAY_MODE, 7);
	if (dlg.DoModal() == IDOK)
	{
		UpdateOrderList(7, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE7));
	}
}


void CJmPosDlg::OnBnClickedBtnOrder8()
{
	COrderManagerDlg dlg(NULL, ORDER_MODE, 8);
	if (dlg.DoModal() == IDOK)
	{
		UpdateOrderList(8, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE8));
	}
}


void CJmPosDlg::OnBnClickedBtnPay8()
{
	COrderManagerDlg dlg(NULL, PAY_MODE, 8);
	if (dlg.DoModal() == IDOK)
	{
		UpdateOrderList(8, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE8));
	}
}


void CJmPosDlg::OnBnClickedBtnOrder9()
{
	COrderManagerDlg dlg(NULL, ORDER_MODE, 9);
	if (dlg.DoModal() == IDOK)
	{
		UpdateOrderList(9, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE9));
	}
}


void CJmPosDlg::OnBnClickedBtnPay9()
{
	COrderManagerDlg dlg(NULL, PAY_MODE, 9);
	if (dlg.DoModal() == IDOK)
	{
		UpdateOrderList(9, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE9));
	}
}


void CJmPosDlg::OnBnClickedBtnOrder10()
{
	COrderManagerDlg dlg(NULL, ORDER_MODE, 10);
	if (dlg.DoModal() == IDOK)
	{
		UpdateOrderList(10, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE10));
	}
}


void CJmPosDlg::OnBnClickedBtnPay10()
{
	COrderManagerDlg dlg(NULL, PAY_MODE, 10);
	if (dlg.DoModal() == IDOK)
	{
		UpdateOrderList(10, (CListCtrl*)this->GetDlgItem(IDC_LIST_TABLE10));
	}
}


void CJmPosDlg::OnBnClickedBtnReport()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CJmPosDlg::UpdateOrderList(int nTableIndex, CListCtrl* pOrderList)
{
	CString strTableIndex;
	strTableIndex.Format(_T("TABLE%d"), nTableIndex);
	
	pOrderList->DeleteAllItems();

	CString strOrder = theApp.GetProfileStringA(strTableIndex, _T("Order"), NULL);
	vector<stOrder> vecOrder = ParsingOrderString(strOrder);

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
	}
}

void CJmPosDlg::GetBundlePayCheck(int* array)
{
	UpdateData(TRUE);
	array[0] = IsDlgButtonChecked(IDC_CHECK_BUNDLE1);
	array[1] = IsDlgButtonChecked(IDC_CHECK_BUNDLE2);
	array[2] = IsDlgButtonChecked(IDC_CHECK_BUNDLE3);
	array[3] = IsDlgButtonChecked(IDC_CHECK_BUNDLE4);
	array[4] = IsDlgButtonChecked(IDC_CHECK_BUNDLE5);
	array[5] = IsDlgButtonChecked(IDC_CHECK_BUNDLE6);
	array[6] = IsDlgButtonChecked(IDC_CHECK_BUNDLE7);
	array[7] = IsDlgButtonChecked(IDC_CHECK_BUNDLE8);
	array[8] = IsDlgButtonChecked(IDC_CHECK_BUNDLE9);
	array[9] = IsDlgButtonChecked(IDC_CHECK_BUNDLE10);
}

void CJmPosDlg::InitBundlePayCheck()
{
	CheckDlgButton(IDC_CHECK_BUNDLE1, FALSE);
	CheckDlgButton(IDC_CHECK_BUNDLE2, FALSE);
	CheckDlgButton(IDC_CHECK_BUNDLE3, FALSE);
	CheckDlgButton(IDC_CHECK_BUNDLE4, FALSE);
	CheckDlgButton(IDC_CHECK_BUNDLE5, FALSE);
	CheckDlgButton(IDC_CHECK_BUNDLE6, FALSE);
	CheckDlgButton(IDC_CHECK_BUNDLE7, FALSE);
	CheckDlgButton(IDC_CHECK_BUNDLE8, FALSE);
	CheckDlgButton(IDC_CHECK_BUNDLE9, FALSE);
	CheckDlgButton(IDC_CHECK_BUNDLE10, FALSE);
	UpdateData(FALSE);
}