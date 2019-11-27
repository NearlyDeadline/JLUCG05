
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
END_MESSAGE_MAP()

// CJLUCG05View 构造/析构

CJLUCG05View::CJLUCG05View() noexcept
{
	// TODO: 在此处添加构造代码

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

void CJLUCG05View::OnDraw(CDC* /*pDC*/)
{
	CJLUCG05Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
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
