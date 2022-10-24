
// MFCApplication3Dlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CMFCApplication3Dlg
class CMFCApplication3Dlg : public CDialogEx
{
// Создание
public:
	CMFCApplication3Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton();
	afx_msg void OnBnClickedBild();
//	afx_msg void OnBnClickedDetectio();
	afx_msg void OnBnClickedButton1();
	//afx_msg void OnEnChangeEdit14();
//	double p_d1;
	double D1;
	double D2;
	double D3;
//	double D4;
	double H1;
	double H2;
	afx_msg void OnEnChangeh3();
	double H3;
	//double D4;
	double H5;
	double H4;
	double H6;
	double S1;
//	double N1;
	double D4;
//	double l1;
//	double h7;
//	double R;
//	double r12;
	double L1;
	double H7;
	double R12;
	double RR;


	bool CheckData();
};
