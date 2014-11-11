// PLCParameterDlg.h : ͷ�ļ�
//

#pragma once

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

enum STATIC_UNIT_ID
{
	ID_STATIC_UNIT_1 = 11000,
	ID_STATIC_UNIT_2,
	ID_STATIC_UNIT_3,
	ID_STATIC_UNIT_4,
	ID_STATIC_UNIT_5,
	ID_STATIC_UNIT_6,
	ID_STATIC_UNIT_7,
	ID_STATIC_UNIT_8,
	ID_STATIC_UNIT_9,
	ID_STATIC_UNIT_10,
	ID_STATIC_UNIT_11,
	ID_STATIC_UNIT_12,
	ID_STATIC_UNIT_13,
	ID_STATIC_UNIT_14,
	ID_STATIC_UNIT_15,
	ID_STATIC_UNIT_16,
	ID_STATIC_UNIT_17,
	ID_STATIC_UNIT_18,
	ID_STATIC_UNIT_19,
	ID_STATIC_UNIT_20,
	ID_STATIC_UNIT_21,
	ID_STATIC_UNIT_22,
	ID_STATIC_UNIT_23,
	ID_STATIC_UNIT_24,
	ID_STATIC_UNIT_25,
	ID_STATIC_UNIT_26,
	ID_STATIC_UNIT_27,
	ID_STATIC_UNIT_28,
	ID_STATIC_UNIT_29
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

enum BUTTON_ID
{
	ID_BUTTON_1 = 30000,
};

enum CHECKBOX_ID
{
	ID_CHECKBOX_1 = 31000,
	ID_CHECKBOX_2,
	ID_CHECKBOX_3,
	ID_CHECKBOX_4,
	ID_CHECKBOX_5,
	ID_CHECKBOX_6,
	ID_CHECKBOX_7,
	ID_CHECKBOX_8,
	ID_CHECKBOX_9,
	ID_CHECKBOX_10,
	ID_CHECKBOX_11,
	ID_CHECKBOX_12,
	ID_CHECKBOX_13,
	ID_CHECKBOX_14,
	ID_CHECKBOX_15,
	ID_CHECKBOX_16,
	ID_CHECKBOX_17,
	ID_CHECKBOX_18,
	ID_CHECKBOX_19,
	ID_CHECKBOX_20,
	ID_CHECKBOX_21,
	ID_CHECKBOX_22,
	ID_CHECKBOX_23,
	ID_CHECKBOX_24,
	ID_CHECKBOX_25,
	ID_CHECKBOX_26,
	ID_CHECKBOX_27,
	ID_CHECKBOX_28,
	ID_CHECKBOX_29,
};
// CPLCParameterDlg �Ի���
class CPLCParameterDlg : public CDialog
{
// ����
public:
	CPLCParameterDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PLCPARAMETER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnCopy();
	DECLARE_MESSAGE_MAP()
public:
	CStatic * NewStatic(int nID, char * cName, CRect rect, int nStyle);
	CEdit * NewEdit(int nID, CRect rect, int nStyle);
	afx_msg void OnClose();
	CButton* NewButton(int nID, CRect rect, int nStyle);
	BOOL CopyStringToClipboard(HWND hWnd, LPCTSTR lpszText);
};
