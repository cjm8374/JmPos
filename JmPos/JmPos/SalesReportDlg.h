#pragma once


// CSalesReportDlg ��ȭ �����Դϴ�.

class CSalesReportDlg : public CDialog
{
	DECLARE_DYNAMIC(CSalesReportDlg)

public:
	CSalesReportDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSalesReportDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_SALESREPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSalesreportSearch();
	afx_msg void OnBnClickedBtnSalesreportViewMenus();
	virtual BOOL OnInitDialog();
};
