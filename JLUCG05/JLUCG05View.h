
// JLUCG05View.h: CJLUCG05View 类的接口
//

#pragma once


class CJLUCG05View : public CView
{
protected: // 仅从序列化创建
	CJLUCG05View() noexcept;
	DECLARE_DYNCREATE(CJLUCG05View)

// 特性
public:
	CJLUCG05Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CJLUCG05View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHermite();
	afx_msg void OnBezier();
	afx_msg void OnBspline();
private:
	static const int POINTS_SIZE = 4;
	static const int DENSITY = 1000;
	CPoint points[POINTS_SIZE];
	int pointsCount = 0;
	bool pointsFilled = false;
	int drawType = 0; //0代表不画图，1代表Hermite曲线，2代表Bezier曲线，3代表B样条曲线
	//CPen m_pen;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
private:
	tagLOGPEN PolygonPen;//控制多边形和控制向量画笔
	tagLOGPEN HermitePen;//Hermite曲线画笔
	tagLOGPEN BezierPen;//Bezier曲线画笔
	tagLOGPEN BSplinePen;//B样条曲线画笔
						 // Hermite曲线作图函数，pDC为设备指针，points为型值点数组，density为曲线上点的取值数
	void Hermite(CDC* pDC, int density = CJLUCG05View::DENSITY);
public:
	afx_msg void OnClearscreen();
private:
	// 使用控制点坐标数组，生成Bezier曲线，存入result数组中。注意result数组的大小应为density+1
	void GetBezierPoints(CPoint* result, int density = CJLUCG05View::DENSITY);
	// 输入参数值t，返回曲线的x,y值
	CPoint Decas(double t);
	// B样条曲线作图函数
	void BSpine(CDC* pDC, int density = CJLUCG05View::DENSITY);
};

#ifndef _DEBUG  // JLUCG05View.cpp 中的调试版本
inline CJLUCG05Doc* CJLUCG05View::GetDocument() const
   { return reinterpret_cast<CJLUCG05Doc*>(m_pDocument); }
#endif

