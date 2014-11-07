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
//////////////////////////////////////////////////////////////////////////
// �ؼ��õ���ȫ�ֱ���
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

TCHAR * StaticAxisNameArray[27] = {"Kv�ٶ�����", "Kf�ٶ�ǰ��", "Impulse�������", "Road�Ƕ�", "SwLimitNeg������λ����", 
								"SwLimitPos������λ����", "MaxVelocity����ٶ�", "MaxAcceleration�����ٶ�", "MaxDecelercation�����ٶ�", "MaxJerk���Ӽ���", 
								"MaxTorque�������", "MaxTorqueRamp", "TorqueTechUnitsDenom", "TorqueTechUnitsNum", "VelocityTechUnitsDenom", 
								"VelocityTechUnitsNum", "TnCyc", "T2", "TestMode", "ReglerMode", 
								"AxisType", "ExtEncoder", "CyclicDataInputs", "CyclicDataOutputs", "ProfileCurveChoose", 
								"AxisModMax", "AxisModMin"};
TCHAR * StaticSystemNameArray[27] = {"TnCyc�岹����", "Multi��Ƶϵ��"};

CStatic *pStaticAxis[27];
CStatic *pStaticSystem[2];
CEdit *pEditAxis[27];
CEdit *pEditSystem[2];

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
	// ��̬�ؼ�/�༭��ؼ�����
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

	pEdit->Create(WS_VISIBLE|WS_CHILD|nStyle, rect, this, nID);
	
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
