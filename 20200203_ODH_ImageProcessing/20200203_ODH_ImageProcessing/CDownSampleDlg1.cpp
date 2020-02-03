// CDownSampleDlg1.cpp: 구현 파일
//

#include "pch.h"
#include "20200203_ODH_ImageProcessing.h"
#include "CDownSampleDlg1.h"
#include "afxdialogex.h"


// CDownSampleDlg1 대화 상자

IMPLEMENT_DYNAMIC(CDownSampleDlg1, CDialog)

CDownSampleDlg1::CDownSampleDlg1(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG11, pParent)
	, m_DownSampleRate(0)
{

}

CDownSampleDlg1::~CDownSampleDlg1()
{
}

void CDownSampleDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_DownSampleRate);
	DDV_MinMaxInt(pDX, m_DownSampleRate, 1, 32);
}


BEGIN_MESSAGE_MAP(CDownSampleDlg1, CDialog)
END_MESSAGE_MAP()


// CDownSampleDlg1 메시지 처리기
