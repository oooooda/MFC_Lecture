#pragma once


// CZoomRate 대화 상자

class CZoomRate : public CDialog
{
	DECLARE_DYNAMIC(CZoomRate)

public:
	CZoomRate(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CZoomRate();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// int m_ZoomRate;// int m_ZoomRate;
	double m_ZoomRate;
};
