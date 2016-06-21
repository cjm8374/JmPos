#pragma once


// CMenuManagerDlg 대화 상자입니다.

class CMenuManagerDlg : public CDialog
{
	DECLARE_DYNAMIC(CMenuManagerDlg)

public:
	CMenuManagerDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMenuManagerDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_MENU_MANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnMenumgrInsert();
	afx_msg void OnBnClickedBtnMenumgrUpdate();
	afx_msg void OnBnClickedBtnMenumgrDelete();
	void UpdateMenuList();
	afx_msg void OnNMClickListMenumgrMenu(NMHDR *pNMHDR, LRESULT *pResult);
};