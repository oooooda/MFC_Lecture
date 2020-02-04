
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
};

#ifndef _DEBUG  // 20200203_ODH_ImageProcessingView.cpp의 디버그 버전
inline CMy20200203ODHImageProcessingDoc* CMy20200203ODHImageProcessingView::GetDocument() const
   { return reinterpret_cast<CMy20200203ODHImageProcessingDoc*>(m_pDocument); }
#endif

