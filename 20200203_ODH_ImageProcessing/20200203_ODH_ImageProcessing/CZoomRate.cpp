// CZoomRate.cpp: 구현 파일
//

#include "pch.h"
#include "20200203_ODH_ImageProcessing.h"
#include "CZoomRate.h"
#include "afxdialogex.h"


// CZoomRate 대화 상자

IMPLEMENT_DYNAMIC(CZoomRate, CDialog)

CZoomRate::CZoomRate(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG6, pParent)
	, m_ZoomRate(0)

{

}

CZoomRate::~CZoomRate()
{
}

void CZoomRate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT1, m_ZoomRate);
	//  DDV_MinMaxInt(pDX, m_ZoomRate, 0, INT_MAX);
	DDX_Text(pDX, IDC_EDIT1, m_ZoomRate);
}


BEGIN_MESSAGE_MAP(CZoomRate, CDialog)
END_MESSAGE_MAP()


// CZoomRate 메시지 처리기
