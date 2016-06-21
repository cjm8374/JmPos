
// JmPosDlg.h : 헤더 파일
//

#pragma once

// CJmPosDlg 대화 상자
class CJmPosDlg : public CDialogEx
{
// 생성입니다.
public:
	CJmPosDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_JMPOS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

public:
	void SetTableListColumn(void);
	void SetTableListColumn(CListCtrl* pListCtrl);
	void UpdateOrderList(int nTableIndex, CListCtrl* pOrderList);
	void GetBundlePayCheck(int* array);
	void InitBundlePayCheck();
// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnMenu();
	afx_msg void OnBnClickedBtnOrder1();
	afx_msg void OnBnClickedBtnPay1();
	afx_msg void OnBnClickedBtnOrder2();
	afx_msg void OnBnClickedBtnPay2();
	afx_msg void OnBnClickedBtnOrder3();
	afx_msg void OnBnClickedBtnPay3();
	afx_msg void OnBnClickedBtnOrder4();
	afx_msg void OnBnClickedBtnPay4();
	afx_msg void OnBnClickedBtnOrder5();
	afx_msg void OnBnClickedBtnPay5();
	afx_msg void OnBnClickedBtnOrder6();
	afx_msg void OnBnClickedBtnPay6();
	afx_msg void OnBnClickedBtnOrder7();
	afx_msg void OnBnClickedBtnPay7();
	afx_msg void OnBnClickedBtnOrder8();
	afx_msg void OnBnClickedBtnPay8();
	afx_msg void OnBnClickedBtnOrder9();
	afx_msg void OnBnClickedBtnPay9();
	afx_msg void OnBnClickedBtnOrder10();
	afx_msg void OnBnClickedBtnPay10();
	afx_msg void OnBnClickedBtnReport();
};