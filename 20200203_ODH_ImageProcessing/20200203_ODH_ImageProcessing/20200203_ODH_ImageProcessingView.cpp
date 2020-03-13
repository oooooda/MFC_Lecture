
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
ON_COMMAND(ID_HISTO_STRETCH, &CMy20200203ODHImageProcessingView::OnHistoStretch)
ON_COMMAND(ID_HISTOGRAM, &CMy20200203ODHImageProcessingView::OnHistogram)
ON_COMMAND(ID_END_IN_SEARCH, &CMy20200203ODHImageProcessingView::OnEndInSearch)
ON_COMMAND(ID_HISTO_EQUAL, &CMy20200203ODHImageProcessingView::OnHistoEqual)
ON_COMMAND(ID_HISTO_SPEC, &CMy20200203ODHImageProcessingView::OnHistoSpec)
ON_COMMAND(ID_EMBOSSING, &CMy20200203ODHImageProcessingView::OnEmbossing)
ON_COMMAND(ID_BLURR, &CMy20200203ODHImageProcessingView::OnBlurr)
ON_COMMAND(ID_GAUSSIAN_FILTER, &CMy20200203ODHImageProcessingView::OnGaussianFilter)
ON_COMMAND(ID_SHARPENING, &CMy20200203ODHImageProcessingView::OnSharpening)
ON_COMMAND(ID_HPF_SHARP, &CMy20200203ODHImageProcessingView::OnHpfSharp)
ON_COMMAND(ID_LPF_SHARP, &CMy20200203ODHImageProcessingView::OnLpfSharp)
ON_COMMAND(ID_5X5_BUURR, &CMy20200203ODHImageProcessingView::On5x5Buurr)
ON_COMMAND(ID_DIFF_OPERATOR_HOR, &CMy20200203ODHImageProcessingView::OnDiffOperatorHor)
ON_COMMAND(ID_DIFF_OPERATOR_VER, &CMy20200203ODHImageProcessingView::OnDiffOperatorVer)
ON_COMMAND(ID_HOMOGEN_OPERATOR, &CMy20200203ODHImageProcessingView::OnHomogenOperator)
ON_COMMAND(ID_DIFFERENCE_OPERATOR, &CMy20200203ODHImageProcessingView::OnDifferenceOperator)
ON_COMMAND(ID_ROBERTS_ROW, &CMy20200203ODHImageProcessingView::OnRobertsRow)
ON_COMMAND(ID_RPBERTS_COLUMN, &CMy20200203ODHImageProcessingView::OnRpbertsColumn)
ON_COMMAND(ID_ROBERTS_SYNTHESIS, &CMy20200203ODHImageProcessingView::OnRobertsSynthesis)
ON_COMMAND(ID_SOBEL_ROW, &CMy20200203ODHImageProcessingView::OnSobelRow)
ON_COMMAND(ID_SOBEL_COLUMN, &CMy20200203ODHImageProcessingView::OnSobelColumn)
ON_COMMAND(ID_SOBEL_SYNTHESIS, &CMy20200203ODHImageProcessingView::OnSobelSynthesis)
ON_COMMAND(ID_PREWITT_ROW, &CMy20200203ODHImageProcessingView::OnPrewittRow)
ON_COMMAND(ID_PREWITT_COLUMN, &CMy20200203ODHImageProcessingView::OnPrewittColumn)
ON_COMMAND(ID_PREWITT_SYNTHESIS, &CMy20200203ODHImageProcessingView::OnPrewittSynthesis)
ON_COMMAND(ID_LAPLACIAN, &CMy20200203ODHImageProcessingView::OnLaplacian)
ON_COMMAND(ID_LAPLACIAN_OF_GAUSSIAN, &CMy20200203ODHImageProcessingView::OnLaplacianOfGaussian)
ON_COMMAND(ID_NEAREST, &CMy20200203ODHImageProcessingView::OnNearest)
ON_COMMAND(ID_BILINEAR, &CMy20200203ODHImageProcessingView::OnBilinear)
END_MESSAGE_MAP()
 


// CMy20200203ODHImageProcessingView 생성/소멸

CMy20200203ODHImageProcessingView::CMy20200203ODHImageProcessingView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy20200203ODHImageProcessingView::~CMy20200203ODHImageProcessingView()
{
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument(); //Doc클래스 참조
	ASSERT_VALID(pDoc);

	delete[] pDoc->m_tempImage;
	delete[] pDoc->m_OutputImage;
	delete[] pDoc->m_InputImage;
	//delete[] pDoc->m_tempImage1;


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


void CMy20200203ODHImageProcessingView::OnHistoStretch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnHistoStretch();
	Invalidate(TRUE);

}


void CMy20200203ODHImageProcessingView::OnHistogram()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnHistogram();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnEndInSearch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnEndInSearch();
	Invalidate(TRUE);
	int a = 0;
}


void CMy20200203ODHImageProcessingView::OnHistoEqual()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnHistoEqual();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnHistoSpec()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnHistoSpec();
	Invalidate(TRUE);
	//delete[] pDoc->m_OutputImage;

}


void CMy20200203ODHImageProcessingView::OnEmbossing()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnEmbossing();
	Invalidate(TRUE);
	//delete[] pDoc->m_OutputImage;
}


void CMy20200203ODHImageProcessingView::OnBlurr()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnBlurr();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnGaussianFilter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnGaussianFilter();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnSharpening()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnSharpening();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnHpfSharp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnHpfSharp();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnLpfSharp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnLpfSharp();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::On5x5Buurr()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->On5x5Buurr();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnDiffOperatorHor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnDiffOperatorHor();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnDiffOperatorVer()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnDiffOperatorVer();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnHomogenOperator()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnHomogenOperator();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnDifferenceOperator()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnDifferenceOperator();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnRobertsRow()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnRobertsRow();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnRpbertsColumn()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnRpbertsColumn();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnRobertsSynthesis()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnRobertsSynthesis();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnSobelRow()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnSobelRow();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnSobelColumn()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnSobelColumn();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnSobelSynthesis()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnSobelSynthesis();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnPrewittRow()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnPrewittRow();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnPrewittColumn()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnPrewittColumn();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnPrewittSynthesis()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnPrewittSynthesis();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnLaplacian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnLaplacian();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnLaplacianOfGaussian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnLaplacianOfGaussian();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnNearest()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnNearest();
	Invalidate(TRUE);
}


void CMy20200203ODHImageProcessingView::OnBilinear()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200203ODHImageProcessingDoc *pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnBilinear();
	Invalidate(TRUE);
}
