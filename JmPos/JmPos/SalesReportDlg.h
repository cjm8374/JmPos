#pragma once


// CSalesReportDlg 대화 상자입니다.

class CSalesReportDlg : public CDialog
{
	DECLARE_DYNAMIC(CSalesReportDlg)

public:
	CSalesReportDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSalesReportDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_SALESREPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSalesreportSearch();
	afx_msg void OnBnClickedBtnSalesreportViewMenus();
	virtual BOOL OnInitDialog();
};
