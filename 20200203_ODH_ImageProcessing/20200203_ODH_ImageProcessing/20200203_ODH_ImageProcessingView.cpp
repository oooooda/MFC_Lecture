
// 20200203_ODH_ImageProcessingView.cpp: CMy20200203ODHImageProcessingView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "20200203_ODH_ImageProcessing.h"
#endif

#include "20200203_ODH_ImageProcessingDoc.h"
#include "20200203_ODH_ImageProcessingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy20200203ODHImageProcessingView

IMPLEMENT_DYNCREATE(CMy20200203ODHImageProcessingView, CView)

BEGIN_MESSAGE_MAP(CMy20200203ODHImageProcessingView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_COMMAND(ID_DOWN_SAMPLING, &CMy20200203ODHImageProcessingView::OnDownSampling)
ON_COMMAND(ID_DOWN_SAMPLING, &CMy20200203ODHImageProcessingView::OnDownSampling)
ON_COMMAND(ID_UP_SAMPLE, &CMy20200203ODHImageProcessingView::OnUpSample)
ON_COMMAND(ID_QUANTIZATION, &CMy20200203ODHImageProcessingView::OnQuantization)
ON_COMMAND(ID_SUM_CONSTANT, &CMy20200203ODHImageProcessingView::OnSumConstant)
ON_COMMAND(ID_SUB_CONSTANT, &CMy20200203ODHImageProcessingView::OnSubConstant)
ON_COMMAND(ID_MUL_CONSTANT, &CMy20200203ODHImageProcessingView::OnMulConstant)
ON_COMMAND(ID_DIV_CONSTANT, &CMy20200203ODHImageProcessingView::OnDivConstant)
ON_COMMAND(ID_AND_OPERATE, &CMy20200203ODHImageProcessingView::OnAndOperate)
ON_COMMAND(ID_OR_OPERATE, &CMy20200203ODHImageProcessingView::OnOrOperate)
ON_COMMAND(ID_XOR_OPERATE, &CMy20200203ODHImageProcessingView::OnXorOperate)
ON_COMMAND(ID_NEGA_TRANSFORM, &CMy20200203ODHImageProcessingView::OnNegaTransform)
ON_COMMAND(ID_GAMMA_CORRECTION, &CMy20200203ODHImageProcessingView::OnGammaCorrection)
ON_COMMAND(ID_BINARZATION, &CMy20200203ODHImageProcessingView::OnBinarzation)
ON_COMMAND(ID_STRESS_TRANSFORM, &CMy20200203ODHImageProcessingView::OnStressTransform)
END_MESSAGE_MAP()

// CMy20200203ODHImageProcessingView 생성/소멸

CMy20200203ODHImageProcessingView::CMy20200203ODHImageProcessingView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy20200203ODHImageProcessingView::~CMy20200203ODHImageProcessingView()
{
}

BOOL CMy20200203ODHImageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy20200203ODHImageProcessingView 그리기

void CMy20200203ODHImageProcessingView::OnDraw(CDC* pDC)
{
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	int i, j;
	unsigned char R, G, B;

	for (i = 0; i < pDoc->m_height; i++) {
		for (j = 0; j < pDoc->m_width; j++) {
			R = pDoc->m_InputImage[i*pDoc->m_width + j];
			G = B =R;
			pDC->SetPixel(j + 5, i + 5, RGB(R, G, B));
		}
	}
	
	// 축소된 영상 출력
	for (i = 0; i < pDoc->m_Re_height; i++) {
		for(j = 0; j < pDoc->m_Re_width; j++) {
			R = pDoc->m_OutputImage[i*pDoc->m_Re_width + j];
			G = B = R;
			pDC->SetPixel(j + pDoc->m_width + 10, i + 5, RGB(R, G, B));
		}
	}
}


// CMy20200203ODHImageProcessingView 인쇄

BOOL CMy20200203ODHImageProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy20200203ODHImageProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy20200203ODHImageProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy20200203ODHImageProcessingView 진단

#ifdef _DEBUG
void CMy20200203ODHImageProcessingView::AssertValid() const
{
	CView::AssertValid();
}

void CMy20200203ODHImageProcessingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy20200203ODHImageProcessingDoc* CMy20200203ODHImageProcessingView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy20200203ODHImageProcessingDoc)));
	return (CMy20200203ODHImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG




void CMy20200203ODHImageProcessingView::OnDownSampling()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument(); //Doc클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnDownSampling(); //Doc 클래스에  OnDownSampling 함수 호출

	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnUpSample()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument(); //Doc클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnUpSampling(); //Doc 클래스에  OnUpSampling 함수 호출

	Invalidate(TRUE);
}



void CMy20200203ODHImageProcessingView::OnQuantization()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument(); //Doc클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnQuantization(); //Doc 클래스에  OnUpSampling 함수 호출

	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnSumConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();
	pDoc->OnSumConstant();
	Invalidate(TRUE);

}


void CMy20200203ODHImageProcessingView::OnSubConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();
	pDoc->OnSubConstant();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnMulConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();
	pDoc->OnMulConstant();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnDivConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();
	pDoc->OnDivConstant();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnAndOperate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument(); //Doc클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnAndOperate(); //Doc 클래스에  OnUpSampling 함수 호출

	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnOrOperate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnOrOperate();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnXorOperate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnXorOperate();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnNegaTransform()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnNegaTransform();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnGammaCorrection()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnGammaCorrection();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnBinarzation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnBinarzation();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnStressTransform()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnStressTransform();
	Invalidate(TRUE);
}
