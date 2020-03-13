
// 20200203_ODH_ImageProcessingDoc.h: CMy20200203ODHImageProcessingDoc 클래스의 인터페이스
//


#pragma once


class CMy20200203ODHImageProcessingDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMy20200203ODHImageProcessingDoc() noexcept;
	DECLARE_DYNCREATE(CMy20200203ODHImageProcessingDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CMy20200203ODHImageProcessingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	unsigned char*m_InputImage;
	int m_width;
	int m_height;
	int m_size;
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	void OnDownSampling();
	// 입력 영상을 위한 포인터
	unsigned char*m_OutputImage;
	//입력 영상의 가로축 크기
	int m_Re_width;
	//입력 영상의 세로축 크기
	int m_Re_height;
	//입력 영상의 전체 크기
	int m_Re_size;
	void OnUpSampling();
	void OnQuantization();
	void OnSumConstant();
	void OnSubConstant();
	void OnMulConstant();
	void OnDivConstant();
	void OnAndOperate();
	void OnOrOperate();
	void OnXorOperate();
	void OnNegaTransform();
	void OnGammaCorrection();
	void OnBinarzation();
	void OnStressTransform();
	void OnHistoStretch();
	void OnHistogram();
	//히스토 그램
	double m_HIST[256];
	double m_Sum_Of_HIST[256];
	unsigned char m_Scale_HIST[256];
	void OnEndInSearch();
	void OnHistoEqual();
	void OnHistoSpec();
	void OnEmbossing();
	//화소 영역을 처리하는 함수
	double ** OnMaskProcess(unsigned char * Target, double Mask[3][3]);
	double ** OnMaskProcess01(unsigned char * Target, double Mask01[3][3], double Mask02[3][3]);
	double ** On5X5MaskProcess(unsigned char * Target, double Mask[5][5]);
	//영상의 화소 값을 정규화시키는 함수
	double** OnScale(double **Target, int height, int width);
	//화소 영역 처리 프로그램을 간단히 하겨고 1차월 배열을 2차원 배열로 할당하는 함수
	double ** Image2DMem(int height, int width);
	double** m_tempImage;
	double** m_tempImage1;
	
	void OnBlurr();
	void OnGaussianFilter();
	void OnSharpening();
	void OnHpfSharp();
	void OnLpfSharp();
	void On5x5Buurr();
	void OnDiffOperatorHor();
	void OnDiffOperatorVer();
	void OnHomogenOperator();
	double DoubleABS(double X);
	void OnDifferenceOperator();
	void OnRobertsRow();
	void OnRpbertsColumn();
	void OnRobertsSynthesis();
	void OnSobelRow();
	void OnSobelColumn();
	void OnSobelSynthesis();
	void OnPrewittRow();
	void OnPrewittColumn();
	void OnPrewittSynthesis();
	void OnLaplacian();
	void OnLaplacianOfGaussian();
	void OnNearest();
	void OnBilinear();
};
