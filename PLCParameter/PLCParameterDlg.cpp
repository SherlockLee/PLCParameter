// PLCParameterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PLCParameter.h"
#include "PLCParameterDlg.h"
#include <malloc.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning(disable:4996)
//////////////////////////////////////////////////////////////////////////
// 控件用到的全局变量
//////////////////////////////////////////////////////////////////////////
enum STATIC_ID
{
	ID_STATIC_1 = 10000,
	ID_STATIC_2,
	ID_STATIC_3,
	ID_STATIC_4,
	ID_STATIC_5,
	ID_STATIC_6,
	ID_STATIC_7,
	ID_STATIC_8,
	ID_STATIC_9,
	ID_STATIC_10,
	ID_STATIC_11,
	ID_STATIC_12,
	ID_STATIC_13,
	ID_STATIC_14,
	ID_STATIC_15,
	ID_STATIC_16,
	ID_STATIC_17,
	ID_STATIC_18,
	ID_STATIC_19,
	ID_STATIC_20,
	ID_STATIC_21,
	ID_STATIC_22,
	ID_STATIC_23,
	ID_STATIC_24,
	ID_STATIC_25,
	ID_STATIC_26,
	ID_STATIC_27,
	ID_STATIC_28,
	ID_STATIC_29
};

enum EDIT_ID
{
	ID_EDIT_1 = 20000,
	ID_EDIT_2,
	ID_EDIT_3,
	ID_EDIT_4,
	ID_EDIT_5,
	ID_EDIT_6,
	ID_EDIT_7,
	ID_EDIT_8,
	ID_EDIT_9,
	ID_EDIT_10,
	ID_EDIT_11,
	ID_EDIT_12,
	ID_EDIT_13,
	ID_EDIT_14,
	ID_EDIT_15,
	ID_EDIT_16,
	ID_EDIT_17,
	ID_EDIT_18,
	ID_EDIT_19,
	ID_EDIT_20,
	ID_EDIT_21,
	ID_EDIT_22,
	ID_EDIT_23,
	ID_EDIT_24,
	ID_EDIT_25,
	ID_EDIT_26,
	ID_EDIT_27,
	ID_EDIT_28,
	ID_EDIT_29,
};

TCHAR * StaticAxisNameArray[27] = {"Kv速度增益", "Kf速度前馈", "Impulse脉冲计数", "Road角度", "SwLimitNeg负向限位开关", 
								"SwLimitPos负向限位开关", "MaxVelocity最大速度", "MaxAcceleration最大加速度", "MaxDecelercation最大减速度", "MaxJerk最大加加速", 
								"MaxTorque最大力矩", "MaxTorqueRamp", "TorqueTechUnitsDenom", "TorqueTechUnitsNum", "VelocityTechUnitsDenom", 
								"VelocityTechUnitsNum", "TnCyc", "T2", "TestMode", "ReglerMode", 
								"AxisType", "ExtEncoder", "CyclicDataInputs", "CyclicDataOutputs", "ProfileCurveChoose", 
								"AxisModMax", "AxisModMin"};
TCHAR * StaticSystemNameArray[27] = {"TnCyc插补周期", "Multi分频系数"};

CStatic *pStaticAxis[27];
CStatic *pStaticSystem[2];
CEdit *pEditAxis[27];
CEdit *pEditSystem[2];

//////////////////////////////////////////////////////////////////////////

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CPLCParameterDlg 对话框




CPLCParameterDlg::CPLCParameterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPLCParameterDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPLCParameterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPLCParameterDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CPLCParameterDlg 消息处理程序

BOOL CPLCParameterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//////////////////////////////////////////////////////////////////////////
	// 静态控件/编辑框控件部分
	//////////////////////////////////////////////////////////////////////////
	CRect rect(10, 10, 230, 30), rectSystem(10, 630, 230, 650), 
		rectEdit(245, 10, 465, 30), rectSystemEdit(245, 630, 465, 650);
	TCHAR LabelName [256] = {0};
	TCHAR cNum[5] = {0};
	for (int Num = 0; Num < 27; Num++)
	{		
		SecureZeroMemory(LabelName, sizeof(LabelName));
		SecureZeroMemory(cNum, sizeof(cNum));

		sprintf(cNum, "%d. ", (Num + 1));
		strcat(LabelName, cNum);
		if (Num < 2)
		{
			strcat(LabelName, StaticSystemNameArray[Num]);
			pStaticAxis[Num] = NewStatic(ID_STATIC_28 + Num, LabelName, rectSystem, SS_CENTER|SS_SIMPLE|SS_SUNKEN);
			rectSystem.top += 22;
			rectSystem.bottom += 22;

			pEditAxis[Num] = NewEdit(ID_EDIT_28 + Num, rectSystemEdit, ES_CENTER);
			rectSystemEdit.top += 22;
			rectSystemEdit.bottom += 22;
		}
		SecureZeroMemory(LabelName, sizeof(LabelName));
		strcat(LabelName, cNum);
		strcat(LabelName, StaticAxisNameArray[Num]);
		pStaticAxis[Num] = NewStatic(ID_STATIC_1 + Num, LabelName, rect, SS_CENTER|SS_SIMPLE|SS_SUNKEN);
		rect.top += 22;
		rect.bottom += 22;

		pEditAxis[Num] = NewEdit(ID_EDIT_1 + Num, rectEdit, ES_CENTER);
		rectEdit.top += 22;
		rectEdit.bottom += 22;
	}
	//////////////////////////////////////////////////////////////////////////


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPLCParameterDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPLCParameterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPLCParameterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


CStatic * CPLCParameterDlg::NewStatic(int nID, char * cName, CRect rect, int nStyle)
{
	CStatic *pStatic = new CStatic();
	ASSERT_VALID(pStatic);

	pStatic->Create(cName, WS_VISIBLE|WS_CHILD|nStyle, rect, this, nID);
	return pStatic;
}

CEdit * CPLCParameterDlg::NewEdit(int nID, CRect rect, int nStyle)
{
	CEdit *pEdit = new CEdit();
	ASSERT_VALID(pEdit);

	pEdit->Create(WS_VISIBLE|WS_CHILD|nStyle, rect, this, nID);
	
	return pEdit;
}

void CPLCParameterDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	for (int Num = 0; Num < 27; Num++)
	{
		if (pStaticAxis[Num])
		{
			delete pStaticAxis[Num];
		}

		if (pEditAxis[Num])
		{
			delete pEditAxis[Num];
		}
	}

	for (int Num = 0; Num < 2; Num++)
	{
		if (pStaticSystem[Num])
		{
			delete pStaticSystem[Num];
		}

		if (pEditSystem[Num])
		{
			delete pEditSystem[Num];
		}
	}

	CDialog::OnClose();
}
