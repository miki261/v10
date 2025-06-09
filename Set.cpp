// Set.cpp : implementation of the Set class
//
#include "stdafx.h"
#include "v10.h"
#include "Set.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// Set implementation
IMPLEMENT_DYNAMIC(Set, CRecordset)
Set::Set(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(Set)
	m_id = 0;
	m_name = _T("");
	m_manager = FALSE;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString Set::GetDefaultConnect()
{
	return _T("ODBC;DSN=v10");
}

CString Set::GetDefaultSQL()
{
	return _T("[User]");
}
void Set::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(Set)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[id]"), m_id);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Bool(pFX, _T("[manager]"), m_manager);
	//}}AFX_FIELD_MAP
}
/////////////////////////////////////////////////////////////////////////////
// Set diagnostics
#ifdef _DEBUG
void Set::AssertValid() const
{
	CRecordset::AssertValid();
}
void Set::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG