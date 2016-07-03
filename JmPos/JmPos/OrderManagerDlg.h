#pragma once


// COrderManagerDlg 대화 상자입니다.

class COrderManagerDlg : public CDialog
{
	DECLARE_DYNAMIC(COrderManagerDlg)

public:
	COrderManagerDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	COrderManagerDlg(CWnd* pParent, int nMode, int  TableIndex);
	virtual ~COrderManagerDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_ORDER_MANAGER };

private:
	int			m_nMode;
	vector<int>	m_vecOtherTable;
	int			m_nTableIndex;
	int			m_nTotalPrice;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void UpdateMenuList();
	void InsertOrder(CString strMenu, CString strPrice);
	void InsertOrder(CString strMenu, CString strCount, CString strPrice);
	void DeleteOrder(CString strMenu);
	void UpdateTotalPrice();
	void InitOrderList();
	afx_msg void OnNMDblclkListOrdermgrMenus(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListOrdermgrOrders(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnOrdermgrOk();
	afx_msg void OnBnClickedButtonOrdermgrCancel();
};
