// testhlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testhl.h"
#include "testhlDlg.h"
#include "htmlayout.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTesthlDlg dialog

CTesthlDlg::CTesthlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTesthlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTesthlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTesthlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTesthlDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTesthlDlg, CDialog)
	//{{AFX_MSG_MAP(CTesthlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTesthlDlg message handlers

void Wchar_tToString(string& szDst, const wchar_t *wchar)
{
	wchar_t * wText = (wchar_t *) wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP,NULL,wText,-1,NULL,0,NULL,FALSE);// WideCharToMultiByte的运用
	char *psText;  // psText为char*的临时数组，作为赋值给std::string的中间变量
	psText = new char[dwNum];
	WideCharToMultiByte (CP_OEMCP,NULL,wText,-1,psText,dwNum,NULL,FALSE);// WideCharToMultiByte的再次运用
	szDst = psText;// std::string赋值
	delete []psText;// psText的清除
}

bool set_string(string& poor_std_string, const wchar_t* str )
{
	if(!str) return false;
	Wchar_tToString(poor_std_string, str);
	return true;
}

void onTableRowClick(HELEMENT he, UINT idx)
{
	htmlayout::dom::element hl = he;
	htmlayout::dom::element elTarget = htmlayout::dom::element(hl.root()).get_element_by_id("btn_mod");

	string a;
	if(set_string(a, elTarget.get_attribute("disabled")) ) 
	{
		elTarget.remove_attribute("disabled");
		HTMLayoutUpdateElementEx(elTarget, REDRAW_NOW);
	}
}

void OnButtonClick(HELEMENT he)
{
	htmlayout::dom::element hl = he;
	htmlayout::dom::element hr = hl.root();
	string id;
	if(set_string(id, hl.get_attribute("id")) ) 
	{
		if ("btn_add" == id)
		{
		}
	}
}

struct DOMEventsHandlerType: htmlayout::event_handler
{
	DOMEventsHandlerType(): event_handler(0xFFFFFFFF) {}
	virtual BOOL handle_event (HELEMENT he, BEHAVIOR_EVENT_PARAMS& params ) 
	{ 
        switch( params.cmd )
        {
        case BUTTON_CLICK:              OnButtonClick(params.heTarget); break;// click on button
        case BUTTON_PRESS:              break;// mouse down or key down in button
        case BUTTON_STATE_CHANGED:      break;
        case EDIT_VALUE_CHANGING:       break;// before text change
        case EDIT_VALUE_CHANGED:        break;//after text change
        case SELECT_SELECTION_CHANGED:  break;// selection in <select> changed
        case SELECT_STATE_CHANGED:      break;// node in select expanded/collapsed, heTarget is the node
        case POPUP_REQUEST: 
			break;// request to show popup just received, 
			//     here DOM of popup element can be modifed.
        case POPUP_READY:               break;// popup element has been measured and ready to be shown on screen,
			//     here you can use functions like ScrollToView.
        case POPUP_DISMISSED:           break;// popup element is closed,
			//     here DOM of popup element can be modifed again - e.g. some items can be removed
			//     to free memory.
        case MENU_ITEM_ACTIVE:                // menu item activated by mouse hover or by keyboard
			break;
        case MENU_ITEM_CLICK:                 // menu item click 
			break;
			
			
            // "grey" event codes  - notfications from behaviors from this SDK 
        case HYPERLINK_CLICK:           break;// hyperlink click
        case TABLE_HEADER_CLICK:        break;// click on some cell in table header, 
			//     target = the cell, 
			//     reason = index of the cell (column number, 0..n)
        case TABLE_ROW_CLICK:           onTableRowClick(params.heTarget, params.reason); break;// click on data row in the table, target is the row
			//     target = the row, 
			//     reason = index of the row (fixed_rows..n)
        case TABLE_ROW_DBL_CLICK:       break;// mouse dbl click on data row in the table, target is the row
			//     target = the row, 
			//     reason = index of the row (fixed_rows..n)
			
        case ELEMENT_COLLAPSED:         break;// element was collapsed, so far only behavior:tabs is sending these two to the panels
        case ELEMENT_EXPANDED:          break;// element was expanded,
			
        }
        return FALSE; 
	}
	
} DOMEventsHandler;


LRESULT OnAttachBehavior(LPNMHL_ATTACH_BEHAVIOR lpab )
{
    // attach custom behaviors
    htmlayout::behavior::handle(lpab);
	
    // behavior implementations are located om /include/behaviors/ folder
    // to connect them into the chain of available 
    // behaviors - just include them into the project.
    return 0;
}

// HTMLayout specific notification handler.
LRESULT CALLBACK HTMLayoutNotifyHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LPVOID vParam)
{
	// all HTMLayout notification are comming here.
	NMHDR*  phdr = (NMHDR*)lParam;
	
	switch(phdr->code)
	{
	case HLN_CREATE_CONTROL:    break; //return OnCreateControl((LPNMHL_CREATE_CONTROL) lParam);
	case HLN_CONTROL_CREATED:   break; //return OnControlCreated((LPNMHL_CREATE_CONTROL) lParam);
	case HLN_DESTROY_CONTROL:   break; //return OnDestroyControl((LPNMHL_DESTROY_CONTROL) lParam);
	case HLN_LOAD_DATA:         break; //return OnLoadData((LPNMHL_LOAD_DATA) lParam);
	case HLN_DATA_LOADED:       break; //return OnDataLoaded((LPNMHL_DATA_LOADED)lParam);
	case HLN_DOCUMENT_COMPLETE: break; //return OnDocumentComplete();
	case HLN_ATTACH_BEHAVIOR:   return OnAttachBehavior((LPNMHL_ATTACH_BEHAVIOR)lParam );
	}
	return 0;
}

BOOL CTesthlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTesthlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTesthlDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTesthlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

LRESULT CTesthlDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	// Sciter过滤窗口消息，如果是Sciter引擎处理过的就直接返回
    LRESULT lRet;
    BOOL bHandled = FALSE;
    lRet = HTMLayoutProcND(m_hWnd,message,wParam,lParam,&bHandled);
    if ( bHandled )
    {
        return lRet;
    }
	
    //当窗口创建时，加载HTML文件
	switch (message) 
	{
	case WM_ERASEBKGND:
		return TRUE; // as HTMLayout will draw client area in full
		
		// HTMLayout +
    case WM_CREATE:
		{
			HTMLayoutSetCallback(m_hWnd,&HTMLayoutNotifyHandler,0);
			
			// attach DOM events handler so we will be able to receive DOM events like BUTTON_CLICK, HYPERLINK_CLICK, etc.
			//HTMLayoutWindowAttachEventHandler( hWnd, 
			//    DOMEventsHandler.element_proc, 
			//   &DOMEventsHandler, 
			//    DOMEventsHandler.subscribed_to);
			htmlayout::attach_event_handler(m_hWnd, &DOMEventsHandler);
			
			
			HTMLayoutLoadFile(m_hWnd,L"test.htm");
			break;
		}
	default:
		return CDialog::WindowProc(message, wParam, lParam);
    }
	
	return 0;
}
