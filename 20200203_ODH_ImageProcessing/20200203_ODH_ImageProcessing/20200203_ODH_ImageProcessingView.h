
// 20200203_ODH_ImageProcessingView.h: CMy20200203ODHImageProcessingView 클래스의 인터페이스
//

#pragma once


class CMy20200203ODHImageProcessingView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy20200203ODHImageProcessingView() noexcept;
	DECLARE_DYNCREATE(CMy20200203ODHImageProcessingView)

// 특성입니다.
public:
	CMy20200203ODHImageProcessingDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMy20200203ODHImageProcessingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnDownSampling();
	afx_msg void OnDownSampling();
	afx_msg void OnUpSample();
	afx_msg void OnQuantization();
	afx_msg void OnSumConstant();
	afx_msg void OnSubConstant();
	afx_msg void OnMulConstant();
	afx_msg void OnDivConstant();
	afx_msg void OnAndOperate();
	afx_msg void OnOrOperate();
	afx_msg void OnXorOperate();
	afx_msg void OnNegaTransform();
	afx_msg void OnGammaCorrection();
	afx_msg void OnBinarzation();
	afx_msg void OnStressTransform();
	afx_msg void OnHistoStretch();
	afx_msg void OnHistogram();
	afx_msg void OnEndInSearch();
	afx_msg void OnHistoEqual();
	afx_msg void OnHistoSpec();
	afx_msg void OnEmbossing();
	afx_msg void OnBlurr();
	afx_msg void OnGaussianFilter();
	afx_msg void OnSharpening();
	afx_msg void OnHpfSharp();
	afx_msg void OnLpfSharp();
	afx_msg void On5x5Buurr();
	afx_msg void OnDiffOperatorHor();
	afx_msg void OnDiffOperatorVer();
	afx_msg void OnHomogenOperator();
	afx_msg void OnDifferenceOperator();
	afx_msg void OnRobertsRow();
	afx_msg void OnRpbertsColumn();
	afx_msg void OnRobertsSynthesis();
	afx_msg void OnSobelRow();
	afx_msg void OnSobelColumn();
	afx_msg void OnSobelSynthesis();
	afx_msg void OnPrewittRow();
	afx_msg void OnPrewittColumn();
	afx_msg void OnPrewittSynthesis();
	afx_msg void OnLaplacian();
	afx_msg void OnLaplacianOfGaussian();
	afx_msg void OnNearest();
	afx_msg void OnBilinear();
};

#ifndef _DEBUG  // 20200203_ODH_ImageProcessingView.cpp의 디버그 버전
inline CMy20200203ODHImageProcessingDoc* CMy20200203ODHImageProcessingView::GetDocument() const
   { return reinterpret_cast<CMy20200203ODHImageProcessingDoc*>(m_pDocument); }
#endif

