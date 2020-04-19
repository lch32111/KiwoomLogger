#include "KiwoomLoggerDlg.hpp"

#include "KiwoomLogger.hpp"
#include "resource.h"
#include "KL/KLVersion.h"

#include <iostream>
#include <io.h>
#include <fcntl.h>

#include "KL/KLSystem.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define KWAPI theApp.m_kwOpenAPI

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_KHOPENAPICTRL1, KWAPI);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(KiwoomLoggerDlg, CDialogEx)
	ON_EVENT(KiwoomLoggerDlg, IDC_KHOPENAPICTRL1, 1, OnReceiveTrDataKhopenapictrl, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(KiwoomLoggerDlg, IDC_KHOPENAPICTRL1, 2, OnReceiveRealDataKhopenapictrl, VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(KiwoomLoggerDlg, IDC_KHOPENAPICTRL1, 3, OnReceiveMsgKhopenapictrl, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(KiwoomLoggerDlg, IDC_KHOPENAPICTRL1, 4, OnReceiveChejanData, VTS_BSTR VTS_I4 VTS_BSTR)
	ON_EVENT(KiwoomLoggerDlg, IDC_KHOPENAPICTRL1, 5, OnEventConnect, VTS_I4)
	ON_EVENT(KiwoomLoggerDlg, IDC_KHOPENAPICTRL1, 7, OnReceiveRealCondition, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(KiwoomLoggerDlg, IDC_KHOPENAPICTRL1, 8, OnReceiveTrCondition, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I2 VTS_I2)
	ON_EVENT(KiwoomLoggerDlg, IDC_KHOPENAPICTRL1, 9, OnReceiveConditionVer, VTS_I4 VTS_BSTR)
END_EVENTSINK_MAP()


KiwoomLoggerDlg::KiwoomLoggerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KIWOOMLOGGER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void KiwoomLoggerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_KHOPENAPICTRL1, KWAPI);
}

BEGIN_MESSAGE_MAP(KiwoomLoggerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()

BOOL KiwoomLoggerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Printinf Korean Characters to console
	std::wcout.imbue(std::locale("kor"));
	std::wcin.imbue(std::locale("kor"));

	// Add "About..." menu item to system menu.
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CString	strTitle;
	strTitle.Format(_T("Kiwoom Logger %d.%d.%d"), KL_VERSION_MAJOR, KL_VERSION_MINOR, KL_VERSION_PATCH);
	SetWindowText(strTitle);

	KWAPI.CommConnect();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void KiwoomLoggerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void KiwoomLoggerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR KiwoomLoggerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void KiwoomLoggerDlg::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	if (!KWAPI.GetSafeHwnd()) return;
}

void KiwoomLoggerDlg::OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg)
{
	if (!KWAPI.GetSafeHwnd()) return;
}

void KiwoomLoggerDlg::OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
	if (!KWAPI.GetSafeHwnd()) return;
}

void KiwoomLoggerDlg::OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList)
{
	if (!KWAPI.GetSafeHwnd()) return;
}

void KiwoomLoggerDlg::OnReceiveRealCondition(LPCTSTR strCode, LPCTSTR strType, LPCTSTR strConditionName, LPCTSTR strConditionIndex)
{
	if (!KWAPI.GetSafeHwnd()) return;
}

void KiwoomLoggerDlg::OnReceiveTrCondition(LPCTSTR sScrNo, LPCTSTR strCodeList, LPCTSTR strConditionName, int nIndex, int nNext)
{
	if (!KWAPI.GetSafeHwnd()) return;
}

void KiwoomLoggerDlg::OnReceiveConditionVer(long lRet, LPCTSTR sMsg)
{
	if (!KWAPI.GetSafeHwnd()) return;
}

void KiwoomLoggerDlg::OnEventConnect(LONG nItemCnt)
{
	if (nItemCnt == 0)
	{
		KiwoomLogger::EnterKLSystem(this, &KWAPI);
	}
	else
	{
		// 立加 厚沥惑 贸府
		EndDialog(IDCANCEL);
	}
}
