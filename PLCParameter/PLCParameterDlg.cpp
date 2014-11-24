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
TCHAR * StaticAxisNameArray[19] = {"Kv��������", "Kf�ٶ�ǰ��", "Ȧ������", "Ȧλ��", "���������λ", 
								"���������λ", "����ٶ�", "�����ٶ�", "�����ٶ�", "���Ӽ���", 
								"�ٶ�ת����ĸ", "�ٶ�ת������", "λ���˲�ʱ�䳣��", "����ģʽ", "���Ʒ�ʽ", 
								"������", "��������", "����������", "����������"};

TCHAR * AxisValueUnit[19] = {"--", "--", "--", "unit", "unit", 
							"unit", "unit/s", "unit/s^2", "unit/s^2", "unit/s^3", 
							"--", "--", "ms", "--", "--", 
							"--", "--", "unit", "unit"};
TCHAR * StaticSystemNameArray[2] = {"PLC����", "PLC���ڷ�Ƶ"};
TCHAR * SystemValueUnit[2] = {"ms", "--"};

CStatic *pStaticAxis[19];		// �������˵����Ϣ
CStatic *pStaticAxisUnit[19];	// ������ĵ�λ
CStatic *pStaticSystem[2];		// ϵͳ������˵����Ϣ
CStatic *pStaticSystemUnit[2];	// ϵͳ�����ĵ�λ
CEdit *pEditAxis[19];			// �������ֵ
CEdit *pEditSystem[2];			// ϵͳ������ֵ
CButton *pButtonCopy[1];		// ���ư�ť
#if 0
CButton *pButtonAxisFlag[19];	// �������ѡ��ť
CButton *pButtonSystemFlag[2];	// ϵͳ������ѡ��ť
#endif

CString csConfigHead(
					 "(*@PROPERTIES_EX@\n"
					 "TYPE: POU\n"
					 "LOCALE: 0\n"
					 "IEC_LANGUAGE: ST\n"
					 "PLC_TYPE: independent\n"
					 "PROC_TYPE: independent\n"
					 "*)\n"
					 "(*@KEY@:DESCRIPTION*)\n"
					 "\n"
					 "(*@KEY@:END_DESCRIPTION*)\n"
					 "PROGRAM BoardInitFunction\n"
					 "\n"
					 "(*Group:Default*)\n"
					 "\n"
					 "\n"
					 );
CString csExternHead(
					 "VAR_EXTERNAL\n"
					 "SystemConf :	AXIS_CONFIG_CONST_TR;\n"
					 );
CString csExternMiddle(
					"AxisConf1 :	AXIS_CONFIG_CONST_TR;\n"
					 );
CString csExternTail(
					 "END_VAR\n"
					 "\n"
					 "\n"
					 "(*@KEY@: WORKSHEET\n"
					 "NAME: BoardInitFunction\n"
					 "IEC_LANGUAGE: ST\n"
					 "*)\n"
					 "(*System configuration, do not edit here*)\n"
					 "\n"
					 "\n"
					 );
CString csAxisConfig(
					 "AxisConf1.Kv := REAL#1.0;(*Speed gain factor of the P controller*)\n"
					 "AxisConf1.Kf := REAL#0.7;(*Evaluation factor of the speed precontrol*)\n"
					 "AxisConf1.Impulse := REAL#10000.0;(*Number of pulses for pulse evaluation*)\n"
					 "AxisConf1.Road := REAL#50.0;(*Equivalent path for pulse evaluation*)\n"
					 "AxisConf1.SwLimitNeg := REAL#0.0;(*Negative software limit switch*)\n"
					 "AxisConf1.SwLimitPos := REAL#0.0;(*Positive software limit switch*)\n"
					 "AxisConf1.MaxVelocity := REAL#2500.0;(*Maximum speed*)\n"
					 "AxisConf1.MaxAcceleration := REAL#10000.0;(*Maximum acceleration*)\n"
					 "AxisConf1.MaxDeceleration := REAL#10000.0;(*Maximum deceleration*)\n"
					 "AxisConf1.MaxJerk := REAL#100000.0;(*Maximum jerk*)\n"
					 "AxisConf1.VelocityTechUnitsDenom := REAL#1.0;(*Denominator for velocity conversion factor*)\n"
					 "							                 (*from Calculation data into technical units*)\n"
					 "AxisConf1.VelocityTechUnitsNum := REAL#1.0;(*Numerator for velocity conversion factor*)\n"
					 "										   (*from Calculation data into technical units*)\n"
					 "AxisConf1.T2 := REAL#0.0;(*Timer constant of actual position filter*)\n"
					 "AxisConf1.TestMode := USINT#0;(*Test mode without drives*)\n"
					 "AxisConf1.ReglerMode := USINT#2;(*Controlled or not controlled*)\n"
					 "AxisConf1.AxisType := USINT#0;(*Axis type*)\n"
					 "AxisConf1.ProfileCurveChoose := BOOL#0;(*Curve type choose*)\n"
					 "AxisConf1.AxisModMax := REAL#360.0;(*Maximum For rotary axis*)\n"
					 "AxisConf1.AxisModMin := REAL#0.0;(*Minimum For rotary axis*)\n"
					 "\n"
					 "\n"
					 );
CString csSystemConfig(
					   "SystemConf.TnCyc := REAL#1.0;(*System cycle*)\n"
					   "SystemConf.Multi := REAL#1.0;(*System cycle scale*)\n"
					 );
CString csConfigTail(
					 "(*@KEY@: END_WORKSHEET *)\n"
					 "END_PROGRAM\n"
					 );
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
	ON_BN_CLICKED(ID_BUTTON_1, &CPLCParameterDlg::OnBtnCopy)
	ON_WM_DESTROY()
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
	// ������̬�ؼ�
	//////////////////////////////////////////////////////////////////////////
	//CRect rect(10, 10, 230, 30), rectSystem(10, 630, 230, 650), 
	CRect rect(10, 20, 230, 40), rectSystem(10, 470, 230, 490), 
		rectEdit(245, 20, 350, 40), rectSystemEdit(245, 470, 350, 490),
		rectAxisUnit(355, 20, 415, 40), rectSystemUnit(355, 470, 415, 490),
		rectAxisFlag(420, 20, 430, 40), rectSystemFlag(420, 470, 430, 490);
	TCHAR LabelName [256] = {0};
	TCHAR cNum[5] = {0};
	for (int Num = 0; Num < 19; Num++)
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

#if 0
		//////////////////////////////////////////////////////////////////////////
		// ������Ƿ�ʹ�õı�־
		//////////////////////////////////////////////////////////////////////////
		pButtonAxisFlag[Num] = NewButton(ID_CHECKBOX_1 + Num, rectAxisFlag, BS_CHECKBOX);
		rectAxisFlag.top += 22;
		rectAxisFlag.bottom += 22;
		//////////////////////////////////////////////////////////////////////////
#endif
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
		pStaticAxis[Num] = NewStatic(ID_STATIC_20 + Num, LabelName, rectSystem, SS_SIMPLE|SS_SUNKEN);
		rectSystem.top += 22;
		rectSystem.bottom += 22;
		//////////////////////////////////////////////////////////////////////////


		//////////////////////////////////////////////////////////////////////////
		// ϵͳ�����ĵ�λ
		//////////////////////////////////////////////////////////////////////////
		pStaticSystemUnit[Num] = NewStatic(ID_STATIC_UNIT_20 + Num, SystemValueUnit[Num], rectSystemUnit, SS_CENTER|SS_SUNKEN);
		rectSystemUnit.top += 22;
		rectSystemUnit.bottom += 22;
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// ϵͳ������ֵ
		//////////////////////////////////////////////////////////////////////////
		pEditAxis[Num] = NewEdit(ID_EDIT_20 + Num, rectSystemEdit, ES_CENTER);
		rectSystemEdit.top += 22;
		rectSystemEdit.bottom += 22;
		//////////////////////////////////////////////////////////////////////////
#if 0
		//////////////////////////////////////////////////////////////////////////
		// ϵͳ�����Ƿ�ʹ�õı�־
		//////////////////////////////////////////////////////////////////////////
		pButtonSystemFlag[Num] = NewButton(ID_CHECKBOX_28 + Num, rectSystemFlag, BS_CHECKBOX);
		rectSystemFlag.top += 22;
		rectSystemFlag.bottom += 22;
		//////////////////////////////////////////////////////////////////////////

#endif
	}


	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// ���ư�ť
	//////////////////////////////////////////////////////////////////////////
	CRect rectWidth;
	GetWindowRect(&rectWidth);
	CRect rectButton(rectWidth.Width()/2 - 35, 530, rectWidth.Width()/2 + 35, 550);
	pButtonCopy[0] = NewButton(ID_BUTTON_1, rectButton, BS_DEFPUSHBUTTON, "Load");
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// ����BoardInitFunction.ST�ļ�
	//////////////////////////////////////////////////////////////////////////
	CreateConfigFile();
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// ��ȡBoardInitFunction.ST�ļ�����Ӧ������ֵ��GUI��
	//////////////////////////////////////////////////////////////////////////
	CString csFileName("\\BoardInitFunction.ST"), csFilePath("");
	csFilePath += GetExePath();
	csFilePath += csFileName;

	CStdioFile fRead;
	TCHAR OneLine[MAX_PATH*5] = {0}, cCurrentValue[MAX_PATH] = {0};
	CStringArray AxisValueArray;
	CString csAxisValue("");
	if (fRead.Open(csFilePath, CFile::modeRead|CFile::modeNoTruncate|CFile::modeNoInherit))
	{
		while(fRead.ReadString(OneLine, MAX_PATH*5))
		{
			for (int Num = 0; Num < MAX_PATH*5; Num++)
			{
				if (OneLine[Num] == '#')
				{
					int CurSel = 0;
					while(OneLine[++Num] != ';')
					{
						cCurrentValue[CurSel++] = OneLine[Num];
					}
					csAxisValue.Format("%s", cCurrentValue);
					csAxisValue.Trim();
					memset(cCurrentValue, 0, sizeof(cCurrentValue)/sizeof(TCHAR));
					memset(OneLine, 0, sizeof(OneLine)/sizeof(TCHAR));
					AxisValueArray.Add(csAxisValue);
					continue;
				}
			}
		}
	}
	fRead.Close();

	int Len = AxisValueArray.GetCount();
	for (int Num = 0; Num < Len; Num++)
	{
		GetDlgItem(ID_EDIT_1 + Num)->SetWindowText(AxisValueArray.GetAt(Num));
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

	pEdit->Create(ES_NUMBER|WS_TABSTOP|WS_GROUP|WS_VISIBLE|WS_CHILD|ES_NOHIDESEL|nStyle, rect, this, nID);
	
	return pEdit;
}

CButton* CPLCParameterDlg::NewButton(int nID, CRect rect, int nStyle, CString csButtonText)
{
	CButton *pButton = new CButton();
	ASSERT_VALID(pButton);

	pButton->Create(csButtonText, WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|nStyle, rect, this, nID);

	return pButton;
}

void CPLCParameterDlg::OnBtnCopy()
{
	CStringArray ParameterValueArray;
	CString csTemp("");
	ParameterValueArray.RemoveAll();
	for (int Num = 0; Num < 21; Num++)
	{
		GetDlgItem(ID_EDIT_1 + Num)->GetWindowText(csTemp);
		ParameterValueArray.Add(csTemp);
	}

	//////////////////////////////////////////////////////////////////////////
	// ���޸ĺ��ֵ���»�BoardInitFunction.ST�ļ���
	//////////////////////////////////////////////////////////////////////////
	int AxisItemCount = 0, SystemItemCount = 0, FirstFlag = 0, SemicolonFlag = 0;
	while(AxisItemCount < 19)
	{
		FirstFlag = csAxisConfig.Find('#', FirstFlag);
		SemicolonFlag = csAxisConfig.Find(';', FirstFlag);
		csAxisConfig.Delete(FirstFlag + 1, (SemicolonFlag - FirstFlag - 1));
		csAxisConfig.Insert(FirstFlag + 1, ParameterValueArray.GetAt(AxisItemCount));
		AxisItemCount++;
		FirstFlag++;
	}
	
	FirstFlag = 0;
	while(SystemItemCount < 2)
	{
		FirstFlag = csSystemConfig.Find('#', FirstFlag);
		SemicolonFlag = csSystemConfig.Find(';', FirstFlag);
		csSystemConfig.Delete(FirstFlag + 1, (SemicolonFlag - FirstFlag - 1));
		csSystemConfig.Insert(FirstFlag + 1, ParameterValueArray.GetAt(AxisItemCount + SystemItemCount));
		SystemItemCount++;
		FirstFlag++;
	}

	//////////////////////////////////////////////////////////////////////////

	CreateConfigFile();
#if 0
	if (CopyStringToClipboard(AfxGetMainWnd()->m_hWnd, csContent))
	{
		MessageBox(csContent, "��Ϣ��ʾ", MB_OK|MB_ICONINFORMATION);
	}	
#endif
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

void CPLCParameterDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	for (int Num = 0; Num < 19; Num++)
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

#if 0
		if (pButtonAxisFlag[Num])
		{
			delete pButtonAxisFlag[Num];
		}

#endif
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

#if 0
		if (pButtonSystemFlag[Num])
		{
			delete pButtonSystemFlag[Num];
		}
#endif
	}

	for (int Num = 0; Num < 1; Num++)
	{
		if (pButtonCopy[Num])
		{
			delete pButtonCopy[Num];
		}
	}
}

BOOL CPLCParameterDlg::IsFileExist(CString csFilePath)
{
	CFileFind fFind;	
	return fFind.FindFile(csFilePath);
}

CString CPLCParameterDlg::GetExePath(void)
{
	CString csCurrentPath("");
	TCHAR szCurrentPath[MAX_PATH];
	::GetCurrentDirectory(MAX_PATH, szCurrentPath);
	csCurrentPath.Format("%s", szCurrentPath);
	return csCurrentPath;
}

void CPLCParameterDlg::CreateConfigFile()
{
	CString csFileName("\\BoardInitFunction.ST"), csFilePath("");
	csFilePath += GetExePath();
	csFilePath += csFileName;
	//////////////////////////////////////////////////////////////////////////
	// ����BoardInitFunction.ST�ļ�
	//////////////////////////////////////////////////////////////////////////
	CString csBoardInitFunction("");
	csBoardInitFunction += csConfigHead;
	csBoardInitFunction += csExternHead;
	csBoardInitFunction += csExternMiddle;
	csBoardInitFunction += csExternTail;
	csBoardInitFunction += csAxisConfig;
	csBoardInitFunction += csSystemConfig;
	csBoardInitFunction += csConfigTail;
	CFile fFile(csFilePath, CFile::modeCreate|CFile::modeWrite);
	fFile.Write(csBoardInitFunction.GetBuffer(csBoardInitFunction.GetLength()), csBoardInitFunction.GetLength());
	fFile.Close();		
	//////////////////////////////////////////////////////////////////////////
}
