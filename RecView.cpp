// RecView.cpp : implementation of the RecView class
//
#include "stdafx.h"
#include "v10.h"
#include "Set.h"
#include "Doc.h"
#include "RecView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// RecView
IMPLEMENT_DYNCREATE(RecView, CRecordView)
BEGIN_MESSAGE_MAP(RecView, CRecordView)
	//{{AFX_MSG_MAP(RecView)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRecordView::OnFilePrintPreview)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// RecView construction/destruction
RecView::RecView()
	: CRecordView(RecView::IDD)
{
}
RecView::~RecView()
{
}
void RecView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RecView)
	//}}AFX_DATA_MAP
}
BOOL RecView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CRecordView::PreCreateWindow(cs);
}
void RecView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_set;
	CRecordView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
}
/////////////////////////////////////////////////////////////////////////////
// RecView printing
BOOL RecView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}
void RecView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void RecView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
/////////////////////////////////////////////////////////////////////////////
// RecView diagnostics
#ifdef _DEBUG
void RecView::AssertValid() const
{
	CRecordView::AssertValid();
}
void RecView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}
Doc* RecView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Doc)));
	return (Doc*)m_pDocument;
}
#endif //_DEBUG
/////////////////////////////////////////////////////////////////////////////
// RecView database support
CRecordset* RecView::OnGetRecordset()
{
	return m_pSet;
}
/////////////////////////////////////////////////////////////////////////////
// RecView message handlers

void RecView::OnPrint(CDC* pDC, CPrintInfo* pInfo) {
    const int page_height = pDC->GetDeviceCaps(VERTRES);
    const int page_width = pDC->GetDeviceCaps(HORZRES);
    int line_height = pDC->GetTextExtent("V").cy;

    int column_y = page_height / 17;
    int column_x = page_width / 12;

    pDC->TextOut(column_x, column_y, "ID");
    pDC->TextOut(column_x * 4, column_y, "Name");
    pDC->TextOut(column_x * 7, column_y, "Manager");

    pDC->MoveTo(column_x, column_y + line_height);
    pDC->LineTo(column_x * 10, column_y + line_height);

    line_height += line_height;

    Set record_set;
    record_set.Open();

    while (!record_set.IsEOF()) {
        column_y += static_cast<int>(line_height / 1.7);

        CString id_text;
        id_text.Format("%d", record_set.m_id);
        pDC->TextOut(column_x, column_y, id_text);
        pDC->TextOut(column_x * 4, column_y, record_set.m_name);
        if (record_set.m_manager) {
            pDC->TextOut(column_x * 7, column_y, "X");
        }

        record_set.MoveNext();
    }
}