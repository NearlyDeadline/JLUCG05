
// JLUCG05View.cpp: CJLUCG05View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "JLUCG05.h"
#endif

#include "JLUCG05Doc.h"
#include "JLUCG05View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CJLUCG05View

IMPLEMENT_DYNCREATE(CJLUCG05View, CView)

BEGIN_MESSAGE_MAP(CJLUCG05View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_Hermite, &CJLUCG05View::OnHermite)
	ON_COMMAND(ID_Bezier, &CJLUCG05View::OnBezier)
	ON_COMMAND(ID_BSpline, &CJLUCG05View::OnBspline)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_ClearScreen, &CJLUCG05View::OnClearscreen)
END_MESSAGE_MAP()

// CJLUCG05View 构造/析构

CJLUCG05View::CJLUCG05View() noexcept
{
	PolygonPen.lopnStyle = PS_SOLID;
	PolygonPen.lopnWidth.x = 1;
	PolygonPen.lopnColor = RGB(0, 0, 0);
	HermitePen.lopnStyle = PS_SOLID;
	HermitePen.lopnWidth.x = 4;
	HermitePen.lopnColor = RGB(255, 0, 0);
	BezierPen.lopnStyle = PS_SOLID;
	BezierPen.lopnWidth.x = 4;
	BezierPen.lopnColor = RGB(0, 255, 0);
	BSplinePen.lopnStyle = PS_SOLID;
	BSplinePen.lopnWidth.x = 4;
	BSplinePen.lopnColor = RGB(0, 0, 255);
}

CJLUCG05View::~CJLUCG05View()
{
	
}

BOOL CJLUCG05View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CJLUCG05View 绘图

void CJLUCG05View::OnDraw(CDC* pDC)
{
	CJLUCG05Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

}


// CJLUCG05View 打印

BOOL CJLUCG05View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CJLUCG05View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CJLUCG05View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CJLUCG05View 诊断

#ifdef _DEBUG
void CJLUCG05View::AssertValid() const
{
	CView::AssertValid();
}

void CJLUCG05View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CJLUCG05Doc* CJLUCG05View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJLUCG05Doc)));
	return (CJLUCG05Doc*)m_pDocument;
}
#endif //_DEBUG


// CJLUCG05View 消息处理程序


void CJLUCG05View::OnHermite()
{
	if (pointsFilled) {
		CDC* pDC = this->GetDC();
		//m_pen.CreatePenIndirect(&PolygonPen);
		//CPen* pen = pDC->SelectObject(&m_pen);
		pDC->MoveTo(points[0]);
		pDC->LineTo(points[1]);
		pDC->SetPixel(points[1], PolygonPen.lopnColor);
		pDC->MoveTo(points[2]);
		pDC->LineTo(points[3]);
		pDC->SetPixel(points[3], PolygonPen.lopnColor);
		Hermite(pDC);
		//pDC->SelectObject(pen);
		ReleaseDC(pDC);
	}
}


void CJLUCG05View::OnBezier()
{
	if (pointsFilled) {
		CPoint* bezier = new CPoint[CJLUCG05View::DENSITY + 1];
		GetBezierPoints(bezier);
		CDC* pDC = this->GetDC();
		pDC->MoveTo(points[0]);
		pDC->LineTo(points[1]);
		pDC->LineTo(points[2]);
		pDC->LineTo(points[3]);
		pDC->LineTo(points[0]);
		for (int i = 0; i <= CJLUCG05View::DENSITY + 1; i++) {
			pDC->SetPixel(bezier[i], BezierPen.lopnColor);
		}
		ReleaseDC(pDC);
		delete bezier;
	}
}


void CJLUCG05View::OnBspline()
{
	if (pointsFilled) {
		CDC* pDC = this->GetDC();
		pDC->MoveTo(points[0]);
		pDC->LineTo(points[1]);
		pDC->LineTo(points[2]);
		pDC->LineTo(points[3]);
		pDC->LineTo(points[0]);
		BSpine(pDC);
		ReleaseDC(pDC);
	}
}


void CJLUCG05View::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (pointsFilled) {
		for (int i = 0; i < CJLUCG05View::POINTS_SIZE - 1; i++) {
			points[i] = points[i + 1];
		}
		points[CJLUCG05View::POINTS_SIZE - 1] = point;
	}
	else {
		points[pointsCount++] = point;
		if (pointsCount == 4)
			pointsFilled = true;
	}
	CDC* pDC = this->GetDC();
	pDC->SetPixel(point, PolygonPen.lopnColor);
	ReleaseDC(pDC);
	CView::OnLButtonDown(nFlags, point);
}


void CJLUCG05View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonUp(nFlags, point);
}


// Hermite曲线作图函数，pDC为设备指针，points为型值点数组，density为曲线上点的取值数
void CJLUCG05View::Hermite(CDC* pDC, int density)
{
	CPoint PiD;//对应Pi'
	PiD.x = points[1].x - points[0].x;
	PiD.y = points[1].y - points[0].y;
	CPoint PjD;//对应Pi+1'
	PjD.x = points[3].x - points[2].x;
	PjD.y = points[3].y - points[2].y;
	int x[4]; //x[0] * u ^ 3 + x[1] * u ^ 2 + x[2] * u + x[3]
	x[0] = 2 * points[0].x - 2 * points[2].x + 1 * PiD.x + 1 * PjD.x;
	x[1] = -3 * points[0].x + 3 * points[2].x - 2 * PiD.x - 1 * PjD.x;
	x[2] = PiD.x;
	x[3] = points[0].x;
	int y[4];
	y[0] = 2 * points[0].y - 2 * points[2].y + 1 * PiD.y + 1 * PjD.y;
	y[1] = -3 * points[0].y + 3 * points[2].y - 2 * PiD.y - 1 * PjD.y;
	y[2] = PiD.y;
	y[3] = points[0].y;
	double i = 0.0;
	double delta = 1.0 / density;
	for (int j = 0; j <= density; j++) {
		pDC->SetPixel(
			(int)(pow(i, 3) * x[0] + pow(i, 2) * x[1] + i * x[2] + x[3]),
			(int)(pow(i, 3) * y[0] + pow(i, 2) * y[1] + i * y[2] + y[3]),
			HermitePen.lopnColor
		);
		i += delta;
	}
}


void CJLUCG05View::OnClearscreen()
{
	ShowWindow(FALSE);
	ShowWindow(TRUE);
	pointsCount = 0;
	pointsFilled = false;
	drawType = 0;
}

// 使用控制点坐标数组，生成Bezier曲线，存入result数组中。注意result数组的大小应为density+1
void CJLUCG05View::GetBezierPoints(CPoint* result, int density)
{
	double t = 0.0;
	double delt = 1.0 / (double)density;
	for (int i = 0; i <= density; i++) {
		result[i] = Decas(t);
		t += delt;
	}
}

// 输入参数值t，返回曲线的x,y值
CPoint CJLUCG05View::Decas(double t)
{
	int n = CJLUCG05View::POINTS_SIZE - 1;
	CPoint* R = new CPoint[n+1];
	CPoint* Q = new CPoint[n+1];
	CPoint P0;
	for (int i = 0; i <= n; i++)
		R[i] = points[i];
	for (int m = n; m > 0; m--) {
		for (int i = 0; i <= m - 1; i++) {
			Q[i].x = R[i].x + t * (R[i + 1].x - R[i].x);
			Q[i].y = R[i].y + t * (R[i + 1].y - R[i].y);
		}
		for (int i = 0; i <= m - 1; i++) {
			R[i] = Q[i];
		}
	}
	P0 = R[0];
	delete R;
	delete Q;
	return P0;
}


// B样条曲线作图函数
void CJLUCG05View::BSpine(CDC* pDC, int density)
{
	int x[4]; //x[0] * u ^ 3 + x[1] * u ^ 2 + x[2] * u + x[3]
	x[0] = -1 * points[0].x + 3 * points[1].x - 3 * points[2].x + 1 * points[3].x;
	x[1] = 3 * points[0].x - 6 * points[1].x + 3 * points[2].x;
	x[2] = -3 * points[0].x + 3 * points[2].x;
	x[3] = points[0].x + 4 * points[1].x + points[2].x;
	int y[4];
	y[0] = -1 * points[0].y + 3 * points[1].y - 3 * points[2].y + 1 * points[3].y;
	y[1] = 3 * points[0].y - 6 * points[1].y + 3 * points[2].y;
	y[2] = -3 * points[0].y + 3 * points[2].y;
	y[3] = points[0].y + 4 * points[1].y + points[2].y;
	double i = 0.0;
	double delta = 1.0 / density;
	for (int j = 0; j <= density; j++) {
		pDC->SetPixel(
			(int)((pow(i, 3) * x[0] + pow(i, 2) * x[1] + i * x[2] + x[3]) * 0.16667),
			(int)((pow(i, 3) * y[0] + pow(i, 2) * y[1] + i * y[2] + y[3]) * 0.16667),
			BSplinePen.lopnColor
		);
		i += delta;
	}
}
