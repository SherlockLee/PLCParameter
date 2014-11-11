// PLCParameterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PLCParameter.h"
#include "PLCParameterDlg.h"
#include <malloc.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning(disable:4996)
TCHAR * StaticAxisNameArray[27] = {"Kv�ٶ�����", "Kf�ٶ�ǰ��", "Impulse�������", "Road�Ƕ�", "SwLimitNeg������λ����", 
								"SwLimitPos������λ����", "MaxVelocity����ٶ�", "MaxAcceleration�����ٶ�", "MaxDecelercation�����ٶ�", "MaxJerk���Ӽ���", 
								"MaxTorque�������", "MaxTorqueRamp", "TorqueTechUnitsDenom", "TorqueTechUnitsNum", "VelocityTechUnitsDenom", 
								"VelocityTechUnitsNum", "TnCyc", "T2", "TestMode", "ReglerMode", 
								"AxisType", "ExtEncoder", "CyclicDataInputs", "CyclicDataOutputs", "ProfileCurveChoose", 
								"AxisModMax", "AxisModMin"};

TCHAR * AxisValueUnit[27] = {"--", "--", "unit", "unit", "unit", 
							"unit", "unit/s", "unit/s^2", "unit/s^2", "unit/s^3", 
							"unit", "unit", "unit", "unit", "unit", 
							"unit", "ms", "ms", "--", "--", 
							"--", "--", "--", "--", "--", 
							"--", "--" };
TCHAR * StaticSystemNameArray[2] = {"TnCyc�岹����", "Multi��Ƶϵ��"};
TCHAR * SystemValueUnit[2] = {"ms", "--"};

CStatic *pStaticAxis[27];		// �������˵����Ϣ
CStatic *pStaticAxisUnit[27];	// ������ĵ�λ
CStatic *pStaticSystem[2];		// ϵͳ������˵����Ϣ
CStatic *pStaticSystemUnit[2];	// ϵͳ�����ĵ�λ
CEdit *pEditAxis[27];			// �������ֵ
CEdit *pEditSystem[2];			// ϵͳ������ֵ
CButton *pButtonCopy[1];		// ���ư�ť
CButton *pButtonAxisFlag[27];	// �������ѡ��ť
CButton *pButtonSystemFlag[2];	// ϵͳ������ѡ��ť

//////////////////////////////////////////////////////////////////////////

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CPLCParameterDlg �Ի���




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
	ON_BN_CLICKED(ID_BUTTON_1, &CPLCParameterDlg::OnBtnCopy)
END_MESSAGE_MAP()


// CPLCParameterDlg ��Ϣ�������

BOOL CPLCParameterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//////////////////////////////////////////////////////////////////////////
	// ��̬�ؼ�
	//////////////////////////////////////////////////////////////////////////
	//CRect rect(10, 10, 230, 30), rectSystem(10, 630, 230, 650), 
	CRect rect(10, 20, 230, 40), rectSystem(10, 640, 230, 660), 
		rectEdit(245, 20, 350, 40), rectSystemEdit(245, 640, 350, 660),
		rectAxisUnit(355, 20, 415, 40), rectSystemUnit(355, 640, 415, 660),
		rectAxisFlag(420, 20, 430, 40), rectSystemFlag(420, 640, 430, 660);
	TCHAR LabelName [256] = {0};
	TCHAR cNum[5] = {0};
	for (int Num = 0; Num < 27; Num++)
	{		
		SecureZeroMemory(LabelName, sizeof(LabelName));
		SecureZeroMemory(cNum, sizeof(cNum));

		sprintf(cNum, "%d. ", (Num + 1));
		strcat(LabelName, cNum);
		strcat(LabelName, StaticAxisNameArray[Num]);
		//////////////////////////////////////////////////////////////////////////
		// �����������
		//////////////////////////////////////////////////////////////////////////
		pStaticAxis[Num] = NewStatic(ID_STATIC_1 + Num, LabelName, rect, SS_SIMPLE|SS_SUNKEN);
		rect.top += 22;
		rect.bottom += 22;
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// ������ĵ�λ
		//////////////////////////////////////////////////////////////////////////
		pStaticAxisUnit[Num] = NewStatic(ID_STATIC_UNIT_1 + Num, AxisValueUnit[Num], rectAxisUnit, SS_CENTER|SS_SUNKEN);
		rectAxisUnit.top += 22;
		rectAxisUnit.bottom += 22;
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// �������ֵ
		//////////////////////////////////////////////////////////////////////////
		pEditAxis[Num] = NewEdit(ID_EDIT_1 + Num, rectEdit, ES_CENTER);
		rectEdit.top += 22;
		rectEdit.bottom += 22;
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// ������Ƿ�ʹ�õı�־
		//////////////////////////////////////////////////////////////////////////
		pButtonAxisFlag[Num] = NewButton(ID_CHECKBOX_1 + Num, rectAxisFlag, BS_CHECKBOX);
		rectAxisFlag.top += 22;
		rectAxisFlag.bottom += 22;
		//////////////////////////////////////////////////////////////////////////
	}
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// �༭��ؼ�
	//////////////////////////////////////////////////////////////////////////
	for (int Num = 0; Num < 2; Num++)
	{
		SecureZeroMemory(LabelName, sizeof(LabelName));
		SecureZeroMemory(cNum, sizeof(cNum));

		sprintf(cNum, "%d. ", (Num + 1));
		strcat(LabelName, cNum);
		strcat(LabelName, StaticSystemNameArray[Num]);
		//////////////////////////////////////////////////////////////////////////
		// ϵͳ����������
		//////////////////////////////////////////////////////////////////////////
		pStaticAxis[Num] = NewStatic(ID_STATIC_28 + Num, LabelName, rectSystem, SS_SIMPLE|SS_SUNKEN);
		rectSystem.top += 22;
		rectSystem.bottom += 22;
		//////////////////////////////////////////////////////////////////////////


		//////////////////////////////////////////////////////////////////////////
		// ϵͳ�����ĵ�λ
		//////////////////////////////////////////////////////////////////////////
		pStaticSystemUnit[Num] = NewStatic(ID_STATIC_UNIT_28 + Num, SystemValueUnit[Num], rectSystemUnit, SS_CENTER|SS_SUNKEN);
		rectSystemUnit.top += 22;
		rectSystemUnit.bottom += 22;
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// ϵͳ������ֵ
		//////////////////////////////////////////////////////////////////////////
		pEditAxis[Num] = NewEdit(ID_EDIT_28 + Num, rectSystemEdit, ES_CENTER);
		rectSystemEdit.top += 22;
		rectSystemEdit.bottom += 22;
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// ϵͳ�����Ƿ�ʹ�õı�־
		//////////////////////////////////////////////////////////////////////////
		pButtonSystemFlag[Num] = NewButton(ID_CHECKBOX_28 + Num, rectSystemFlag, BS_CHECKBOX);
		rectSystemFlag.top += 22;
		rectSystemFlag.bottom += 22;
		//////////////////////////////////////////////////////////////////////////
	}


	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// ���ư�ť
	//////////////////////////////////////////////////////////////////////////
	CRect rectWidth;
	GetWindowRect(&rectWidth);
	CRect rectButton(rectWidth.Width()/2 - 35, 695, rectWidth.Width()/2 + 35, 715);
	pButtonCopy[0] = NewButton(ID_BUTTON_1, rectButton, BS_DEFPUSHBUTTON);
	//////////////////////////////////////////////////////////////////////////


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPLCParameterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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

	pEdit->Create(WS_TABSTOP|WS_GROUP|WS_VISIBLE|WS_CHILD|ES_NOHIDESEL|nStyle, rect, this, nID);
	
	return pEdit;
}

void CPLCParameterDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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

		if (pStaticAxisUnit[Num])
		{
			delete pStaticAxisUnit[Num];
		}

		if (pButtonAxisFlag[Num])
		{
			delete pButtonAxisFlag[Num];
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

		if (pStaticSystemUnit[Num])
		{
			delete pStaticSystemUnit[Num];
		}

		if (pButtonSystemFlag[Num])
		{
			delete pButtonSystemFlag[Num];
		}
	}
	
	for (int Num = 0; Num < 1; Num++)
	{
		if (pButtonCopy[Num])
		{
			delete pButtonCopy[Num];
		}
	}
	CDialog::OnClose();
}

CButton* CPLCParameterDlg::NewButton(int nID, CRect rect, int nStyle)
{
	CButton *pButton = new CButton();
	ASSERT_VALID(pButton);

	pButton->Create("Copy", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|nStyle, rect, this, nID);

	return pButton;
}

void CPLCParameterDlg::OnBtnCopy()
{
	CString csContent(""), csTemp("");
	GetDlgItem(ID_EDIT_1)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\t";
	GetDlgItem(ID_EDIT_2)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\t";
	GetDlgItem(ID_EDIT_3)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\t";
	GetDlgItem(ID_EDIT_4)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\t";
	GetDlgItem(ID_EDIT_5)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\r\n";
	GetDlgItem(ID_EDIT_6)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\t";
	GetDlgItem(ID_EDIT_7)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\t";
	GetDlgItem(ID_EDIT_8)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\t";
	GetDlgItem(ID_EDIT_9)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\t";
	GetDlgItem(ID_EDIT_10)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\r\n";
	GetDlgItem(ID_EDIT_11)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\t";
	GetDlgItem(ID_EDIT_12)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\t";
	GetDlgItem(ID_EDIT_13)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\t";
	GetDlgItem(ID_EDIT_14)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\t";
	GetDlgItem(ID_EDIT_15)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\r\n";
	GetDlgItem(ID_EDIT_16)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\t";
	GetDlgItem(ID_EDIT_17)->GetWindowText(csTemp);	
	csContent += csTemp;
	csContent += "\t";
	GetDlgItem(ID_EDIT_18)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\t";
	GetDlgItem(ID_EDIT_19)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\t";
	GetDlgItem(ID_EDIT_20)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\r\n";
	GetDlgItem(ID_EDIT_21)->GetWindowText(csTemp);	
	csContent += csTemp;
	csContent += "\t";
	GetDlgItem(ID_EDIT_22)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\t";
	GetDlgItem(ID_EDIT_23)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\t";
	GetDlgItem(ID_EDIT_24)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\t";
	GetDlgItem(ID_EDIT_25)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\r\n";
	GetDlgItem(ID_EDIT_26)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\t";
	GetDlgItem(ID_EDIT_27)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\t";
	GetDlgItem(ID_EDIT_28)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\t";
	GetDlgItem(ID_EDIT_29)->GetWindowText(csTemp);
	csContent += csTemp;
	csContent += "\t";

	if (CopyStringToClipboard(AfxGetMainWnd()->m_hWnd, csContent))
	{
		MessageBox(csContent, "��Ϣ��ʾ", MB_OK|MB_ICONINFORMATION);
	}	
}

BOOL CPLCParameterDlg::CopyStringToClipboard(HWND hWnd, LPCTSTR lpszText)
{
	HGLOBAL hglbCopy = NULL;
	LPTSTR lptstrCopy;

	int nlen = strlen(lpszText);
	if (nlen == 0)
	{
		return FALSE;
	}

	if (!::OpenClipboard(hWnd))
	{
		return FALSE;
	} 
	
	hglbCopy = GlobalAlloc(GMEM_DDESHARE, (nlen + 1)*sizeof(char));

	if (hglbCopy == NULL)
	{
		CloseClipboard();
		return FALSE;
	}

	EmptyClipboard();

	lptstrCopy = (LPTSTR)GlobalLock(hglbCopy);
	memcpy(lptstrCopy, lpszText, nlen);
	lptstrCopy[nlen] = (TCHAR)0;
	SetClipboardData(CF_TEXT, hglbCopy);
	CloseClipboard();
	return TRUE;

	return 0;
}
