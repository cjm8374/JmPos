#pragma once


// CMenuManagerDlg ��ȭ �����Դϴ�.

class CMenuManagerDlg : public CDialog
{
	DECLARE_DYNAMIC(CMenuManagerDlg)

public:
	CMenuManagerDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMenuManagerDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_MENU_MANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnMenumgrInsert();
	afx_msg void OnBnClickedBtnMenumgrUpdate();
	afx_msg void OnBnClickedBtnMenumgrDelete();
	void UpdateMenuList();
	afx_msg void OnNMClickListMenumgrMenu(NMHDR *pNMHDR, LRESULT *pResult);
};