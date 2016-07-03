#pragma once


// COrderManagerDlg ��ȭ �����Դϴ�.

class COrderManagerDlg : public CDialog
{
	DECLARE_DYNAMIC(COrderManagerDlg)

public:
	COrderManagerDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	COrderManagerDlg(CWnd* pParent, int nMode, int  TableIndex);
	virtual ~COrderManagerDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_ORDER_MANAGER };

private:
	int			m_nMode;
	vector<int>	m_vecOtherTable;
	int			m_nTableIndex;
	int			m_nTotalPrice;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
