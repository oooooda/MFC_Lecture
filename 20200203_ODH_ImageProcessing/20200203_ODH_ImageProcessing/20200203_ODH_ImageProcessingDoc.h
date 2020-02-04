
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
};
