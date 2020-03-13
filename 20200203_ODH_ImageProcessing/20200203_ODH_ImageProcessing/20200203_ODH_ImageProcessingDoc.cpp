
// 20200203_ODH_ImageProcessingDoc.cpp: CMy20200203ODHImageProcessingDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "20200203_ODH_ImageProcessing.h"
#endif

#include "20200203_ODH_ImageProcessingDoc.h"
#include "CDownSampleDlg1.h"
#include "CUpSampleDlg.h"
#include "CQuantizationDlg.h"
#include "CConstantDlg.h"
#include "CStressTransformDlg.h"
#include "CZoomRate.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMy20200203ODHImageProcessingDoc

IMPLEMENT_DYNCREATE(CMy20200203ODHImageProcessingDoc, CDocument)

BEGIN_MESSAGE_MAP(CMy20200203ODHImageProcessingDoc, CDocument)
END_MESSAGE_MAP()


// CMy20200203ODHImageProcessingDoc 생성/소멸

CMy20200203ODHImageProcessingDoc::CMy20200203ODHImageProcessingDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMy20200203ODHImageProcessingDoc::~CMy20200203ODHImageProcessingDoc()
{
}

BOOL CMy20200203ODHImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMy20200203ODHImageProcessingDoc serialization

void CMy20200203ODHImageProcessingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMy20200203ODHImageProcessingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMy20200203ODHImageProcessingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMy20200203ODHImageProcessingDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMy20200203ODHImageProcessingDoc 진단

#ifdef _DEBUG
void CMy20200203ODHImageProcessingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy20200203ODHImageProcessingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy20200203ODHImageProcessingDoc 명령


BOOL CMy20200203ODHImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CFile File;
	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);

	if (File.GetLength() == 256 * 256) {
		m_width = 256;
		m_height = 256;
	}
	else if (File.GetLength() == 512 * 512) {
		m_width = 512;
		m_height = 512;
	}
	else if (File.GetLength() == 640 * 480) {
		m_width = 640;
		m_height = 480;
	}
	else {
		AfxMessageBox(_T("Not Support Image Size"));
	}
	
	m_size = m_width * m_height;

	m_InputImage = new unsigned char[m_size];

	for (int i = 0; i < m_size; i++) {
		m_InputImage[i] = 255;
	}

	File.Read(m_InputImage, m_size);
	File.Close();
	
	return TRUE;
}


BOOL CMy20200203ODHImageProcessingDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CFile File; //파일 객체 선언
	CFileDialog SaveDlg(FALSE, "raw", NULL, OFN_HIDEREADONLY);
	//raw 파일을 다른 이름으로 저장하기를 위한 대화 상자 객체 선언
	
	if (SaveDlg.DoModal() == IDOK) {
		//  DoModal 멤버 함수에 저장하기 수행
		File.Open(SaveDlg.GetPathName(), CFile::modeCreate |
			CFile::modeWrite);
		//파일 열기
		File.Write(m_OutputImage, m_size);  //파일 쓰기
		File.Close();//파일 닫기
	}

	return TRUE;
	//return CDocument::OnSaveDocument(lpszPathName);
}


void CMy20200203ODHImageProcessingDoc::DeleteContents()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CDocument::DeleteContents();
}


void CMy20200203ODHImageProcessingDoc::OnDownSampling()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	CDownSampleDlg1 dlg;
	if (dlg.DoModal() == IDOK) // 대화상자의 활성화 여부
	{
		m_Re_height = m_height / dlg.m_DownSampleRate;
		// 축소 영상의 세로 길이를 계산
		m_Re_width = m_width / dlg.m_DownSampleRate;
		// 축소 영상의 가로 길이를 계산
		m_Re_size = m_Re_height * m_Re_width;
		// 축소 영상의 크기를 계산

		m_OutputImage = new unsigned char[m_Re_size];
		// 축소 영상을 위한 메모리 할당
		for (i = 0; i < m_Re_size; i++)
		{
			m_OutputImage[i] = 255;
		}

		for (i = 0; i < m_Re_height; i++)
		{
			for (j = 0; j < m_Re_width; j++) 
			{
				m_OutputImage[i*m_Re_width + j]= m_InputImage[(i*dlg.m_DownSampleRate*m_width) + dlg.m_DownSampleRate*j];
				// 축소 영상을 생성
			}
		}
	}

}


void CMy20200203ODHImageProcessingDoc::OnUpSampling()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	CUpSampleDlg dlg;
	if (dlg.DoModal() == IDOK) { // DoModal 대화상자의 활성화 여부
		m_Re_height = m_height * dlg.m_UpSampleRate;
		// 확대 영상의 세로 길이 계산
		m_Re_width = m_width * dlg.m_UpSampleRate;
		// 확대 영상의 가로 길이 계산
		m_Re_size = m_Re_height * m_Re_width;
		// 확대 영상의 크기 계산
		m_OutputImage = new unsigned char[m_Re_size];
		// 확대 영상을 위한 메모리 할당

		for (i = 0; i < m_Re_size; i++)
			m_OutputImage[i] = 255; // 초기화

		for (i = 0; i < m_height; i++) {
			for (j = 0; j < m_width; j++) {
				m_OutputImage[i*dlg.m_UpSampleRate*m_Re_width + dlg.m_UpSampleRate*j] = m_InputImage[i*m_width + j];
			} // 재배치하여 영상 확대
		}
	}

}


void CMy20200203ODHImageProcessingDoc::OnQuantization()
{
	// TODO: 여기에 구현 코드 추가.
	CQuantizationDlg dlg;

	if (dlg.DoModal() == IDOK)
		//양자화 비트 수를 결정하는 대화상자의 활성화 여부
	{
		int i, j, value, LEVEL;
		double HIGH, *TEMP;

		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;

		m_OutputImage = new unsigned char[m_Re_size];
		//양자화 처리된 영상을 출력하기 위한 메모리 할당

		TEMP = new double[m_size];
		//입력 영상 크기(m_size)와 동일한 메모리 할당

		LEVEL = 256; //입력 영상의 양자와 단계(2^8=256)
		HIGH = 256;

		value = (int)pow(2, dlg.m_QuantBit);
		//양자화 단계 결정(예 : 2^4=16)

		for (i = 0; i < m_size; i++) {
			for (j = 0; j < value; j++) {
				if (m_InputImage[i] >= (LEVEL / value)*j &&
					m_InputImage[i] < (LEVEL / value)*(j + 1)) {
					TEMP[i] = (double)(HIGH / value) *j; //양자화 수행
					//TEMP[i] += 0.5;
				}
			}
		}

		for (i = 0; i < m_size; i++)
		{
			m_OutputImage[i] = (unsigned char)TEMP[i];
			//결과 영상 생성
		}
	}
}


void CMy20200203ODHImageProcessingDoc::OnSumConstant()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK)
	{
		for (i = 0; i < m_size; i++)
		{
			if (m_InputImage[i] + dlg.m_Constant >= 255)
			{
				m_OutputImage[i] = 255;
				//출력값이 255보다 크면 255출력
			}
			else
			{
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] + dlg.m_Constant);
				//상수 값과 화소 값과의 덧셈
			}
		}
	}



}


void CMy20200203ODHImageProcessingDoc::OnSubConstant()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK)
	{
		for (i = 0; i < m_size; i++)
		{
			
			if (m_InputImage[i] - dlg.m_Constant < 0)
			{
				m_OutputImage[i] = 0;
				//0보다 작으면 0 출력
			}
			else
			{
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] - dlg.m_Constant);
				//상수 값과 화소 값과의 뺄셈
			}
		}
	}
}


void CMy20200203ODHImageProcessingDoc::OnMulConstant()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK)
	{
		for (i = 0; i < m_size; i++)
		{

			if (m_InputImage[i] * dlg.m_Constant >= 255)
			{
				m_OutputImage[i] = 255;
				//255보다 크면 255 출력
			}
			else if (m_InputImage[i] * dlg.m_Constant < 0)
			{
				m_OutputImage[i] = 0;
				//0보다 작으면 0 출력
			}
			else
			{
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] * dlg.m_Constant);
				//상수 값과 화소 값과의 곱셈
			}
		}
	}
}


void CMy20200203ODHImageProcessingDoc::OnDivConstant()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK)
	{
		for (i = 0; i < m_size; i++)
		{

			if (m_InputImage[i] / dlg.m_Constant >= 255)
			{
				m_OutputImage[i] = 255;
				//255보다 크면 255 출력
			}
			else if (m_InputImage[i] / dlg.m_Constant < 0)
			{
				m_OutputImage[i] = 0;
				//0보다 작으면 0 출력
			}
			else
			{
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] / dlg.m_Constant);
				//상수 값과 화소 값과의 곱셈
			}
		}
	}
}


void CMy20200203ODHImageProcessingDoc::OnAndOperate()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK)
	{
		for (i = 0; i <= m_Re_size; i++)
		{
			if ((m_InputImage[i] & (unsigned char)dlg.m_Constant) >= 255)
			{
				m_OutputImage[i] = 255;
			}
			else if ((m_InputImage[i] & (unsigned char)dlg.m_Constant) <0)
			{
				m_OutputImage[i] = 0;
			}
			else
			{
				m_OutputImage[i] = m_InputImage[i] & (unsigned char)dlg.m_Constant;
			}
		}
	}


}


void CMy20200203ODHImageProcessingDoc::OnOrOperate()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	int i;
	
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_width * m_Re_height;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK)
	{
		for (i = 0; i < m_Re_size; i++)
		{
			if ((m_InputImage[i] | (unsigned char)dlg.m_Constant) >= 255)
			{
				m_OutputImage[i] = 255;
			}
			else if ((m_InputImage[i] | (unsigned char)dlg.m_Constant) < 0)
			{
				m_OutputImage[i] = 0;
			}
			else
			{
				m_OutputImage[i] = m_InputImage[i] | (unsigned char)dlg.m_Constant;
			}

		}
	}
}


void CMy20200203ODHImageProcessingDoc::OnXorOperate()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_width * m_Re_height;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK)
	{
		for (i = 0; i < m_Re_size; i++)
		{
			if ((m_InputImage[i] ^ (unsigned char)dlg.m_Constant) >= 255)
			{
				m_OutputImage[i] = 255;
			}
			else if ((m_InputImage[i] ^ (unsigned char)dlg.m_Constant) < 0)
			{
				m_OutputImage[i] = 0;
			}
			else
			{
				m_OutputImage[i] = m_InputImage[i] ^ (unsigned char)dlg.m_Constant;
			}

		}
	}
}


void CMy20200203ODHImageProcessingDoc::OnNegaTransform()
{
	// TODO: 여기에 구현 코드 추가.
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_width * m_Re_height;

	m_OutputImage = new unsigned char[m_Re_size];

	for (i = 0; i < m_size; i++)
	{
		m_OutputImage[i] = 255 - m_InputImage[i];
	}
}


void CMy20200203ODHImageProcessingDoc::OnGammaCorrection()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	int i;
	double temp;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_width * m_Re_height;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK)
	{
		for(i =0 ; i<m_size ; i++)
		{
			temp = pow(m_InputImage[i], 1 / dlg.m_Constant);
			 
			if (temp < 0)
			{
				m_OutputImage[i] = 0;
			}
			else if (temp > 255)
			{
				m_OutputImage[i] = 255;
			}
			else
			{
				m_OutputImage[i] = (unsigned char)temp;
			}
		}
	}

}


void CMy20200203ODHImageProcessingDoc::OnBinarzation()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	int i;


	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_width * m_Re_height;

	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK)
	{
		for (i = 0; i < m_size; i++)
		{
			if (m_InputImage[i] >= dlg.m_Constant)
			{
				m_OutputImage[i] = 255;
			}
			else
			{
				m_OutputImage[i] = 0;
			}
		}
	}
}


void CMy20200203ODHImageProcessingDoc::OnStressTransform()
{
	// TODO: 여기에 구현 코드 추가.
	CStressTransformDlg dlg;
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_width * m_Re_height;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK)
	{
		for (i = 0; i < m_size; i++)
		{
			if (m_InputImage[i] >= dlg.m_StrartPoint && 
				m_InputImage[i] <= dlg.m_EndPoint)
			{
				m_OutputImage[i] = 255;
			}
			else
			{
				m_OutputImage[i] = m_InputImage[i];
			}
		}
	}

	

}


void CMy20200203ODHImageProcessingDoc::OnHistoStretch()
{
	// TODO: 여기에 구현 코드 추가.
	int i;
	unsigned char LOW, HIGH, MAX, MIN;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_width * m_Re_height;

	LOW = 0;
	HIGH = 255;

	MIN = m_InputImage[0]; //최소값을 찾기 위한 초기값
	MAX = m_InputImage[0]; //최대갓을 찾기 위한 초기값

	//입력 영상의 최소값 찾기
	for (i = 0; i < m_size; i++)
	{
		if (m_InputImage[i] < MIN)
		{
			MIN = m_InputImage[i];
		}
	}
	//입력 영상의 최대값 찾기
	for (i = 0; i < m_size; i++)
	{
		if (m_InputImage[i] > MAX)
		{
			MAX = m_InputImage[i];
		}
	}

	m_OutputImage = new unsigned char[m_Re_size];

	//히스토 그램 stretch
	for (i = 0; i < m_size; i++)
	{
		m_OutputImage[i] = (unsigned char)((m_InputImage[i] - MIN) *  HIGH / (MAX - MIN));
	}


}


void CMy20200203ODHImageProcessingDoc::OnHistogram()
{
	// TODO: 여기에 구현 코드 추가.
	// 히스토그램의 값은 0~255
   // 히스토그램의 크기 값을 MAX=255로 정규화하여 출력
   // 히스트그램의 크기 : 256*256 지정

	int i, j, value;
	unsigned char LOW, HIGH;
	double MAX, MIN, DIF;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_width * m_Re_height;

	LOW = 0;
	HIGH = 255;


	// 초기화
	for (i = 0; i < 256; i++)
		m_HIST[i] = LOW;

	// 빈도 수 조사
	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}

	// 정규화
	MAX = m_HIST[0];
	MIN = m_HIST[0];

	for (i = 0; i < 256; i++) {
		if (m_HIST[i] > MAX)
			MAX = m_HIST[i];
	}

	for (i = 0; i < 256; i++) {
		if (m_HIST[i] < MIN)
			MIN = m_HIST[i];
	}
	DIF = MAX - MIN;

	// 정규화된 히스토그램
	for (i = 0; i < 256; i++)
		m_Scale_HIST[i] = (unsigned char)((m_HIST[i] - MIN) * HIGH / DIF);

	// 정규화된 히스토그램 출력
	m_OutputImage = new unsigned char[m_Re_size + (256 * 20)];

	for (i = 0; i < m_Re_size; i++)
		m_OutputImage[i] = 255;

	// 정규화된 히스토그램의 값은 출력 배열에 검은 점(0)으로 표현
	for (i = 0; i < 256; i++) 
	{
		for (j = 0; j < m_Scale_HIST[i]; j++)
		{
			m_OutputImage[m_Re_width*(m_Re_height - j - 1) + i] = 0;
		}
	}

	// 히스토그램을 출력하고 그 아래 부분에 히스토그램의 색을 표시
	for (i = m_Re_height; i < m_Re_height + 5; i++) 
	{
		for (j = 0; j < 256; j++)
		{
			m_OutputImage[m_Re_height * i + j] = 255;
		}
	}

	for (i = m_Re_height + 5; i < m_Re_height + 20; i++) {

		for (j = 0; j < 256; j++) 
		{
			m_OutputImage[m_Re_height * i + j] = j;
		}
	}

	m_Re_height = m_Re_height + 20;
	m_Re_size = m_Re_height * m_Re_width;




}


void CMy20200203ODHImageProcessingDoc::OnEndInSearch()
{
	// TODO: 여기에 구현 코드 추가.
	int i;
	unsigned char LOW, HIGH, MAX, MIN;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	LOW = 0;
	HIGH = 255;

	MIN = m_InputImage[0];
	MAX = m_InputImage[0];

	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] < MIN)
			MIN = m_InputImage[i];
	}

	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] > MAX)
			MAX = m_InputImage[i];
	}

	m_OutputImage = new unsigned char[m_Re_size];
	for (i = 0; i < m_size; i++) {
		// 원본 영상의 최소값보다 작은 값은 0
		if (m_InputImage[i] <= MIN) {
			m_OutputImage[i] = 0;
		}

		// 원본 영상의 최대값보다 큰 값은 255
		else if (m_InputImage[i] >= MAX) {
			m_OutputImage[i] = 255;
		}
		else
			m_OutputImage[i] = (unsigned char)((m_InputImage[i] -
				MIN)*HIGH / (MAX - MIN));
	}


}


void CMy20200203ODHImageProcessingDoc::OnHistoEqual()
{
	// TODO: 여기에 구현 코드 추가.

	int i, value;
	unsigned char LOW, HIGH, Temp;
	double SUM = 0.0;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	LOW = 0;
	HIGH = 255;

	// 초기화
	for (i = 0; i < 256; i++)
		m_HIST[i] = LOW;

	// 빈도 수 조사
	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}

	// 누적 히스토그램 생성
	for (i = 0; i < 256; i++) {
		SUM += m_HIST[i];
		m_Sum_Of_HIST[i] = SUM;
	}

	m_OutputImage = new unsigned char[m_Re_size];

	// 입력 영상을 평활화된 영상으로 출력
	for (i = 0; i < m_size; i++) {
		Temp = m_InputImage[i];
		m_OutputImage[i] = (unsigned char)(m_Sum_Of_HIST[Temp] * HIGH / m_size);
	}

}


void CMy20200203ODHImageProcessingDoc::OnHistoSpec()
{
	// TODO: 여기에 구현 코드 추가.
	int i, value, Dvalue, top, bottom, DADD;
	unsigned char *m_DTEMP, m_Sum_Of_ScHIST[256], m_TABLE[256];
	unsigned char LOW, HIGH, Temp, *m_Org_Temp;
	double m_DHIST[256], m_Sum_Of_DHIST[256], SUM = 0.0, DSUM = 0.0;
	double DMAX, DMIN;

	top = 255;
	bottom = top - 1;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;


	m_OutputImage = new unsigned char[m_Re_size];
	m_Org_Temp = new unsigned char[m_size];

	CFile File;
	CFileDialog OpenDlg(TRUE);
	m_DTEMP = new unsigned char[m_size];

	
	//원하는 히스토그램이 있는 영상을 입력 받음
	if (OpenDlg.DoModal() == IDOK)
	{
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);

		if (File.GetLength() == (unsigned)m_size) 
		{
			m_DTEMP = new unsigned char[m_size];
			File.Read(m_DTEMP, m_size);
			File.Close();
		}

		else
		{
			AfxMessageBox("Image size not matched");
			//같은 크기의 영상을 대상으로함
			return ;
		}
	}

	LOW = 0;
	HIGH = 255;

	//초기화
	for (i = 0; i < 256; i++)
	{
		m_HIST[i] = LOW;
		m_DHIST[i] = LOW;
		m_TABLE[i] = LOW;
	}

	//빈도 수 조사
	for (i = 0; i < m_size; i++)
	{
		value = (int)m_InputImage[i];
		m_HIST[value]++;
		Dvalue = (int)m_DTEMP[i];
		m_DHIST[Dvalue]++;
	}

	//누적 히스토그램 조사
	for (i = 0; i < 256; i++)
	{
		SUM += m_HIST[i];
		m_Sum_Of_HIST[i] = SUM;
		DSUM += m_DHIST[i];
		m_Sum_Of_DHIST[i] = DSUM;
	}

	//원본 영상의 평활화
	for (i = 0; i < m_size; i++)
	{
		Temp = m_InputImage[i];
		m_Org_Temp[i] = (unsigned char)(m_Sum_Of_HIST[Temp]*HIGH/m_size);
	}

	//누적 히스토그램에서 최소값과 최대값 지정
	DMIN = m_Sum_Of_DHIST[0];
	DMAX = m_Sum_Of_DHIST[255];

	//원하는 영상을 평활화
	for (i = 0; i < 256; i++)
	{
		m_Sum_Of_ScHIST[i] = (unsigned char)((m_Sum_Of_DHIST[i] - DMIN) * HIGH / (DMAX - DMIN));
	}

	// 룩업테이블을 이용한 명세화
	for ( ; ; )
	{
		for (i = m_Sum_Of_ScHIST[bottom]; i <= m_Sum_Of_ScHIST[top]; i++)
		{
			m_TABLE[i] = top;
		}
		top = bottom;
		bottom = bottom - 1;

		if (bottom < -1)
		{
			break;
		}

		for (i = 0; i < m_size; i++)
		{
			DADD = (int)m_Org_Temp[i];
			m_OutputImage[i] = m_TABLE[DADD];
		}
	}
	
}


void CMy20200203ODHImageProcessingDoc::OnEmbossing()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	double EmboMask[3][3] = { {-1., 0., 0.}, {0., 0., 0. }, {0., 0., 1. } };
	//마스크 선택
	//double EmboMask[3][3] = { {0., 0., 0.}, {0., 1., 0. }, {0., 0., 0. } };
	//double EmboMask[3][3] = { {1., 1., 1.}, {1., -8., 1. }, {1., 1., 1. } };

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, EmboMask);
	//OnMaskProcess함수를 호출하여 회선 처리를 한다

	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}//회선 처리 결과가 0~255 사이 값이 되도록한다.
	
	//m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);
	//정규화 함수를 사용할 때

	//회선 처리 결과나 정규화 처리 결과는 2차원 배열 값이 되므로
	//2차원 배열을 1차원 배열로 바꾸어 출력 하도록 한다.

	for (i = 0; i< m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			m_OutputImage[i*m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}

}

double** CMy20200203ODHImageProcessingDoc::OnMaskProcess(unsigned char *Target, double Mask[3][3])
{
	// TODO: 여기에 구현 코드 추가.
	//회선 처리가 일어나는 함수
	int i, j, n, m;
	double **tempInputImage, **tempOutputImage, S = 0.0;

	tempInputImage = Image2DMem(m_height + 2, m_width + 2);
	// 입력값을 위한 메모리 할당
	tempOutputImage = Image2DMem(m_height, m_width);
	//출력 값을 위한 메모리 할당

	//1차원 입력 영상의 값을 2차원 배열에 할다아한다.
	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			tempInputImage[i + 1][j + 1] = (double)Target[i * m_width + j];
			//tempInputImage 의 (1,1)부터 적용 zeop패딩?
		}
	}

	//회선 연산
	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			for (n = 0; n < 3; n++)
			{
				for (m = 0; m < 3; m++)
				{
					S += Mask[n][m] * tempInputImage[i + n][j+ m];
				}
			}//회선 마스크의 크기 만큼 이동하면서 값을 누적
			tempOutputImage[i][j] = S;	//누적된 값을 출력 메모리에 저장
			S = 0.0;	//다음 블록으로 이동하면 누적 값을 초기화
		}
	}
	return tempOutputImage;
}




double ** CMy20200203ODHImageProcessingDoc::OnScale(double **Target, int height, int width)
{	//정규화를 위한 함수
	int i, j;
	double min, max;
	
	min = max = Target[0][0];

	for (i = 0; i < height ; i++)
	{
		for (j = 0; j < width ; j++)
		{
			if (Target[i][j] <= min)
			{
				min = Target[i][j];
			}
		}
	}

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (Target[i][j] >= max)
			{
				max = Target[i][j];
			}
		}
	}

	max = max - min;

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			Target[i][j] = (Target[i][j] - min) * (255. / max);
		}
	}

	return Target;
}

double ** CMy20200203ODHImageProcessingDoc::Image2DMem(int height, int width)
{	//2차원 메모리 할당을 위한 함수
	
	double** temp;
	
	int i, j;
	temp = new double *[height];
	for (i = 0; i < height; i++)
	{
		temp[i] = new double[width];
	}

	for (i = 0; i < height; i++) 
	{
		for (j = 0; j < width ; j++)
		{
			temp[i][j] = 0.0;
		}
	}	//할당된 2차원 메모리를 최기화

	return temp;
}




void CMy20200203ODHImageProcessingDoc::OnBlurr()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	double BlurrMask[3][3] = { {1. / 9., 1. / 9., 1. / 9.},
	   {1. / 9., 1. / 9., 1. / 9.}, {1. / 9., 1. / 9., 1. / 9.} };

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	m_tempImage = OnMaskProcess(m_InputImage, BlurrMask);
	//블러링 처리
	//m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);

	//정규화
	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			m_OutputImage[i*m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}
}


void CMy20200203ODHImageProcessingDoc::OnGaussianFilter()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	double GaussianMask[3][3] = { {1. / 16., 1. / 8., 1. / 16.},{1. / 8., 1. / 4., 1. / 8.}, {1. / 16., 1. / 8., 1. / 16.} };
	//double GaussianMask[3][3] = { {1, 2, 1}, { 2,4,2 }, { 1,2,1 } };

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	m_tempImage = OnMaskProcess(m_InputImage, GaussianMask);
	//m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);

	//정규화
	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			m_OutputImage[i*m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}
}


void CMy20200203ODHImageProcessingDoc::OnSharpening()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	//double SharpeningMask[3][3] = { {-1., -1., -1. },{-1., 9., -1. }, {-1., -1., -1. } };
	double SharpeningMask[3][3] = { {0., -1., 0. },{-1., 5., -1. }, {0., -1., 0. } };

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	m_tempImage = OnMaskProcess(m_InputImage, SharpeningMask);
	//m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);

	//정규화
	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			m_OutputImage[i*m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}
}


void CMy20200203ODHImageProcessingDoc::OnHpfSharp()
{
	// TODO: 여기에 구현 코드 추가.

	int i, j;
	double HpfSharpeningMask[3][3] = { {-1./9., -1./9., -1./9. },
	{-1./9., 8./9., -1./9. }, {-1./9., -1./9., -1./9. } };

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];


	m_tempImage = OnMaskProcess(m_InputImage, HpfSharpeningMask);
	//m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);


	//정규화
	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			m_OutputImage[i*m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}
}


void CMy20200203ODHImageProcessingDoc::OnLpfSharp()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;

	int i, j, alpha;
	double LpfSharpeningMask[3][3] = { {1. / 9., 1. / 9., 1. / 9. },{1. / 9., 1. / 9., 1. / 9. }, {1. / 9., 1. / 9., 1. / 9. } };
	//double LpfSharpeningMask[3][3] = { {1. / 12., 1. / 12., 1. / 12. },
	//{1. / 12., 4., 1. / 12. }, {1. / 12., 1. / 12., 1. /12. } };

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK)
	{
		alpha = (int)dlg.m_Constant;
		// 대화상자를 이용하여 상수를 입력 받는다
	}

	m_tempImage = OnMaskProcess(m_InputImage, LpfSharpeningMask);

	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			m_tempImage[i][j] = (alpha * m_InputImage[i*m_width + j]) - (unsigned char)m_tempImage[i][j];
		}
	}

	//m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);


	//정규화
	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			m_OutputImage[i*m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}
}


void CMy20200203ODHImageProcessingDoc::On5x5Buurr()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	double X5BlurrMask[5][5] = { {1. / 25., 1. / 25., 1. / 25., 1. / 25., 1. / 25. },
	   {1. / 25., 1. / 25., 1. / 25., 1. / 25., 1. / 25. }, {1. / 25., 1. / 25., 1. / 25., 1. / 25., 1. / 25. },
	   {1. / 25., 1. / 25., 1. / 25., 1. / 25., 1. / 25. } , {1. / 25., 1. / 25., 1. / 25., 1. / 25., 1. / 25. } };

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	m_tempImage = On5X5MaskProcess(m_InputImage, X5BlurrMask);
	//블러링 처리
	//m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);

	//정규화
	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			m_OutputImage[i*m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}
}

double ** CMy20200203ODHImageProcessingDoc::On5X5MaskProcess(unsigned char * Target, double Mask[5][5])
{
	int i, j, n, m;
	double **tempInputImage, **tempOutputImage, S = 0.0;

	tempInputImage = Image2DMem(m_height + 4, m_width + 4);
	// 입력값을 위한 메모리 할당
	tempOutputImage = Image2DMem(m_height, m_width);
	//출력 값을 위한 메모리 할당

	//1차원 입력 영상의 값을 2차원 배열에 할다아한다.
	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			tempInputImage[i + 2][j + 2] = (double)Target[i * m_width + j];
			//tempInputImage 의 (3,3)부터 
		}
	}

	//회선 연산
	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			for (n = 0; n < 5; n++)
			{
				for (m = 0; m < 5; m++)
				{
					S += Mask[n][m] * tempInputImage[i + n][j + m];
				}
			}//회선 마스크의 크기 만큼 이동하면서 값을 누적
			tempOutputImage[i][j] = S;	//누적된 값을 출력 메모리에 저장
			S = 0.0;	//다음 블록으로 이동하면 누적 값을 초기화
		}
	}
	return tempOutputImage;
	return nullptr;
}

void CMy20200203ODHImageProcessingDoc::OnDiffOperatorHor()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	double DiffHorMask[3][3]
		= { {0.,-1.,0.},{0.,1.,0.},{0.,0.,0.} };
	//수평 필터 선택
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	m_tempImage = OnMaskProcess(m_InputImage, DiffHorMask);

	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}

	for(i=0 ; i<m_height ;i++)
	{
		for (j = 0; j < m_width; j++)
		{
			m_OutputImage[i*m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
		}
	}
}


void CMy20200203ODHImageProcessingDoc::OnDiffOperatorVer()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	double DiffHorMask[3][3]
		= { {0.,0.,0.},{-1.,1.,0.},{0.,0.,0.} };
	//수직 필터 선택
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	m_tempImage = OnMaskProcess(m_InputImage, DiffHorMask);

	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}

	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			m_OutputImage[i*m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
		}
	}
}


void CMy20200203ODHImageProcessingDoc::OnHomogenOperator()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, n, m;
	double max, **tempOutputImage;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	m_tempImage = Image2DMem(m_height + 2, m_width + 2);
	tempOutputImage = Image2DMem(m_Re_height, m_Re_width);

	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			m_tempImage[i + 1][j + 1] = (double)m_InputImage[i * m_width + j];
		}
	}
	
	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			max = 0.0; //블럭이 이동할 때마다 최대값 초기화
			for (n = 0 ; n < 3 ; n++)
			{
				for (m = 0; m < 3; m++)
				{
					if (DoubleABS(m_tempImage[i + 1][j + 1] - m_tempImage[i + n][j + m]) >= max)
					{//블록의 가운데 값 - 블록의 주변 픽셀 값의 절대 값 중 최대값을 찾는다.
						
						max = DoubleABS(m_tempImage[i + 1][j + 1] -
							m_tempImage[i + n][j + m]);
					}
				}
			}
			tempOutputImage[i][j] = max;//찾은 최대값을 출력 값으로 지정
		}
	}

	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			if (tempOutputImage[i][j] > 255.)
				tempOutputImage[i][j] = 255.;
			if (tempOutputImage[i][j] < 0.)
				tempOutputImage[i][j] = 0.;
		}
	}

	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			m_OutputImage[i*m_Re_width + j] = (unsigned char)tempOutputImage[i][j];
		}
	}
}

double CMy20200203ODHImageProcessingDoc::DoubleABS(double X)
{	//실수의 절대 값 연산 함수
	if (X >= 0)
		return X;
	else
		return -X;
}


void CMy20200203ODHImageProcessingDoc::OnDifferenceOperator()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, n, m;
	double max, **tempOutputImage;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	m_tempImage = Image2DMem(m_height + 2, m_width + 2);
	tempOutputImage = Image2DMem(m_Re_height, m_Re_width);

	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			m_tempImage[i + 1][j + 1] = (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			max = 0.0; //블럭이 이동할 때마다 최대값 초기화
			
			n = 0;
			for (m = 0; m < 3; m++)
			{
				if (DoubleABS(m_tempImage[i][j] - m_tempImage[i + 2 - n][j + 2 - m]) >= max)
				{//블록의 가운데 값 - 블록의 주변 픽셀 값의 절대 값 중 최대값을 찾는다.

					max = DoubleABS(m_tempImage[i][j] -
						m_tempImage[i + 2 - n][j + 2 - m]);
				}
			}
			
			if (DoubleABS(m_tempImage[i + 1][j + 2] - m_tempImage[i + 1][j] >= max))
			{
				max = DoubleABS(m_tempImage[i + 1][j + 2] - 
					m_tempImage[i + 1][j]);
			}
			
			tempOutputImage[i][j] = max;//찾은 최대값을 출력 값으로 지정
		}
	}

	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			if (tempOutputImage[i][j] > 255.)
				tempOutputImage[i][j] = 255.;
			if (tempOutputImage[i][j] < 0.)
				tempOutputImage[i][j] = 0.;
		}
	}

	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			m_OutputImage[i*m_Re_width + j] = (unsigned char)tempOutputImage[i][j];
		}
	}
}


void CMy20200203ODHImageProcessingDoc::OnRobertsRow()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	double DiffHorMask[3][3]
		= { {-1.,0.,0.},{0.,1.,0.},{0.,0.,0.} };
	//로버츠 행 검출 필터 선택
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	m_tempImage = OnMaskProcess(m_InputImage, DiffHorMask);

	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}

	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			m_OutputImage[i*m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
		}
	}
}


void CMy20200203ODHImageProcessingDoc::OnRpbertsColumn()
{
	// TODO: 여기에 구현 코드 추가.
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	double DiffCoMask[3][3]
		= { {0.,0.,-1.},{0.,1.,0.},{0.,0.,0.} };
	//로버츠 열 검출 필터 선택
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	m_tempImage = OnMaskProcess(m_InputImage, DiffCoMask);

	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}

	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			m_OutputImage[i*m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
		}
	}
}


void CMy20200203ODHImageProcessingDoc::OnRobertsSynthesis()
{
	// TODO: 여기에 구현 코드 추가.
	// TODO: 여기에 구현 코드 추가.
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	double DiffCoMask[3][3]
		= { {0.,0.,-1.},{0.,1.,0.},{0.,0.,0.} };
	//로버츠 열 검출 필터 선택
	double DiffRoMask[3][3]
		= { {0.,0.,-1.},{0.,1.,0.},{0.,0.,0.} };
	//로버츠 행 검출 필터 선택
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	m_tempImage = OnMaskProcess(m_InputImage, DiffCoMask);
	m_tempImage1 = OnMaskProcess(m_InputImage, DiffRoMask);



	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			m_tempImage[i][j] = sqrt(pow(m_tempImage[i][j], 2) + pow(m_tempImage1[i][j], 2));

			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}

	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			m_OutputImage[i*m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
		}
	}
}


void CMy20200203ODHImageProcessingDoc::OnSobelRow()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	double DiffHorMask[3][3]
		= { {-1.,-2.,-1.},{0.,0.,0.},{1.,2.,1.} };
	//소벨 행 검출 필터 선택
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	m_tempImage = OnMaskProcess(m_InputImage, DiffHorMask);

	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}

	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			m_OutputImage[i*m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
		}
	}
}


void CMy20200203ODHImageProcessingDoc::OnSobelColumn()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	double DiffHorMask[3][3]
		= { {1.,0.,-1.},{2.,0.,-2.},{1.,0.,-1.} };
	//소벨 열 검출 검출 필터 선택
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	m_tempImage = OnMaskProcess(m_InputImage, DiffHorMask);

	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}

	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			m_OutputImage[i*m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
		}
	}
}


void CMy20200203ODHImageProcessingDoc::OnSobelSynthesis()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	double DiffCoMask[3][3]
		= { {1.,0.,-1.},{2.,0.,-2.},{1.,0.,-1.} };
	//로버츠 열 검출 필터 선택
	double DiffRoMask[3][3]
		= { {-1.,-2.,-1.},{0.,0.,0.},{1.,2.,1.} };
	//로버츠 행 검출 필터 선택
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	m_tempImage = OnMaskProcess(m_InputImage, DiffCoMask);
	m_tempImage1 = OnMaskProcess(m_InputImage, DiffRoMask);



	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			m_tempImage[i][j] = sqrt(pow(m_tempImage[i][j], 2) + pow(m_tempImage1[i][j], 2));

			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}

	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			m_OutputImage[i*m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
		}
	}
}


void CMy20200203ODHImageProcessingDoc::OnPrewittRow()
{
	// TODO: 여기에 구현 코드 추가.
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	double DiffHorMask[3][3]
		= { {-1.,-1.,-1.},{0.,0.,0.},{1.,1.,1.} };
	//프리윗 행 검출 필터 선택
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	m_tempImage = OnMaskProcess(m_InputImage, DiffHorMask);

	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}

	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			m_OutputImage[i*m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
		}
	}
}


void CMy20200203ODHImageProcessingDoc::OnPrewittColumn()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	double DiffHorMask[3][3]
		= { {1.,0.,-1.},{1.,0.,-1.},{1.,0.,-1.} };
	//프리윗 열 검출 검출 필터 선택
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	m_tempImage = OnMaskProcess(m_InputImage, DiffHorMask);

	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}

	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			m_OutputImage[i*m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
		}
	}
}


void CMy20200203ODHImageProcessingDoc::OnPrewittSynthesis()
{
	// TODO: 여기에 구현 코드 추가.
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	double DiffCoMask[3][3]
		= { {1.,0.,-1.},{1.,0.,-1.},{1.,0.,-1.} };
	//프리윗 열 검출 필터 선택
	double DiffRoMask[3][3]
		= { {-1.,-1.,-1.},{0.,0.,0.},{1.,1.,1.} };
	//프리윗 행 검출 필터 선택
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	m_tempImage = OnMaskProcess(m_InputImage, DiffCoMask);
	m_tempImage1 = OnMaskProcess(m_InputImage, DiffRoMask);



	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			m_tempImage[i][j] = sqrt(pow(m_tempImage[i][j], 2) + pow(m_tempImage1[i][j], 2));

			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}

	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			m_OutputImage[i*m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
		}
	}
}


void CMy20200203ODHImageProcessingDoc::OnLaplacian()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	double DiffHorMask[3][3]
		= { {0.,1.,0.},{1.,-4.,1.},{0.,1.,0.} };
	//라플라시안 회선 마스크
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	m_tempImage = OnMaskProcess(m_InputImage, DiffHorMask);

	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}

	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			m_OutputImage[i*m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
		}
	}
}


void CMy20200203ODHImageProcessingDoc::OnLaplacianOfGaussian()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	//double GaussianMask[3][3] = { {1. / 16., 1. / 8., 1. / 16.},{1. / 8., 1. / 4., 1. / 8.}, {1. / 16., 1. / 8., 1. / 16.} };
	double GaussianMask[3][3] = { {1,2,1},{2,4,2},{1,2,1} };
	double DiffHorMask[3][3]
		= { {-1.,-1.,-1.},{-1.,8.,-1.},{-1.,-1.,-1.} };
	double X5Mask[5][5] = { {0.,0.,-1.,0.,0.},{0.,-1.,-2.,-1.,0.},{-1.,-2.,16.,-2.,-1.,},
	{0.,-1.,-2.,-1.,0.} ,{0.,0.,-1.,0.,0.} };

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	m_tempImage = OnMaskProcess01(m_InputImage, GaussianMask, DiffHorMask);
	//m_tempImage = On5X5MaskProcess(m_InputImage, X5Mask);


	//정규화
	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			m_OutputImage[i*m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}
}

double ** CMy20200203ODHImageProcessingDoc::OnMaskProcess01(unsigned char * Target, double Mask01[3][3], double Mask02[3][3])
{
	//회선 처리가 일어나는 함수
	//회선 처리가 일어나는 함수
	int i, j, n, m;
	double **tempInputImage01,**tempInputImage02, **tempOutputImage, S = 0.0;

	tempInputImage01 = Image2DMem(m_height + 2, m_width + 2);
	tempInputImage02 = Image2DMem(m_height + 2, m_width + 2);

	// 입력값을 위한 메모리 할당
	tempOutputImage = Image2DMem(m_height, m_width);
	//출력 값을 위한 메모리 할당

	//1차원 입력 영상의 값을 2차원 배열에 할다아한다.
	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			tempInputImage01[i + 1][j + 1] = (double)Target[i * m_width + j];
			//tempInputImage 의 (1,1)부터 적용 zeop패딩?
		}
	}

	//회선 연산
	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			for (n = 0; n < 3; n++)
			{
				for (m = 0; m < 3; m++)
				{
					S += Mask01[n][m] * tempInputImage01[i + n][j + m];
				}
			}//회선 마스크의 크기 만큼 이동하면서 값을 누적
			tempInputImage02[i+1][j+1] = S;	//누적된 값을 출력 메모리에 저장
			S = 0.0;	//다음 블록으로 이동하면 누적 값을 초기화
		}
	}
	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			for (n = 0; n < 3; n++)
			{
				for (m = 0; m < 3; m++)
				{
					S += Mask02[n][m] * tempInputImage02[i + n][j + m];
				}
			}//회선 마스크의 크기 만큼 이동하면서 값을 누적
			tempOutputImage[i][j] = S;	//누적된 값을 출력 메모리에 저장
			S = 0.0;	//다음 블록으로 이동하면 누적 값을 초기화
		}
	}
	
	
	return tempOutputImage;

}

void CMy20200203ODHImageProcessingDoc::OnNearest()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	int ZoomRate = 2; //영상 확대 배율
	double **tempArray;

	m_Re_height = int(ZoomRate*m_height); //확대된 영상의 높이
	m_Re_width = int(ZoomRate*m_width); //확대된 영상의 너비
	m_Re_size = m_Re_width * m_Re_height;

	m_tempImage = Image2DMem(m_height, m_width);
	tempArray = Image2DMem(m_Re_height, m_Re_width);

	m_OutputImage = new unsigned char[m_Re_size];

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i*m_width + j];
		}
	}

	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			tempArray[i][j] = m_tempImage[i / ZoomRate][j / ZoomRate];
			//이웃한 화소를 이용한 보간
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i*m_Re_width + j] = (unsigned char)tempArray[i][j];
		}
	}

}


void CMy20200203ODHImageProcessingDoc::OnBilinear()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, point, i_H, i_W;
	unsigned char newValue;
	double ZoomRate = 2.0, r_H, r_W, s_H, s_W;
	double C1, C2, C3, C4;

	m_Re_height = int(ZoomRate*m_height); //확대된 영상의 높이
	m_Re_width = int(ZoomRate*m_width); //확대된 영상의 너비
	m_Re_size = m_Re_width * m_Re_height;

	m_tempImage = Image2DMem(m_height, m_width);
	m_OutputImage = new unsigned char[m_Re_size];
	
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i*m_width + j];
		}
	}

	for (i = 0; i < m_Re_height; i++) {

		for (j = 0; j < m_Re_width; j++) {
			r_H = i / ZoomRate;
			r_W = j / ZoomRate;
			
			i_H = (int)floor(r_H);
			i_W = (int)floor(r_W);

			s_H = r_H - i_H;
			s_W = r_W - i_W;

			if (i_H < 0 || i_H >= (m_height - 1) ||
				i_W < 0 || i_W >= (m_height - 1)) {

				point = i * m_Re_width + j;
				m_OutputImage[point] = 255;
			}
			
			else {
				C1 = (double)m_tempImage[i_H][i_W];
				C2 = (double)m_tempImage[i_H][i_W+1];
				C3 = (double)m_tempImage[i_H+1][i_W+1];
				C4 = (double)m_tempImage[i_H+1][i_W];

				newValue = (unsigned char)(C1*(1-s_H)*(1-s_W)
					+ C2 * s_W*(1 - s_H) + C3 * s_W*s_H + C4 * (1 - s_W)*s_H);
				point = i * m_Re_width + j;
				m_OutputImage[point] = newValue;

			}

		}
	}
}
