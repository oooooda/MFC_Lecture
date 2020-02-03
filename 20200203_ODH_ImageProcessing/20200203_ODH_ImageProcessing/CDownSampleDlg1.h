#pragma once


// CDownSampleDlg1 대화 상자

class CDownSampleDlg1 : public CDialog
{
	DECLARE_DYNAMIC(CDownSampleDlg1)

public:
	CDownSampleDlg1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDownSampleDlg1();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG11 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_DownSampleRate;
};
