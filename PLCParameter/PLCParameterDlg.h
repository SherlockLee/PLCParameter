// PLCParameterDlg.h : ͷ�ļ�
//

#pragma once


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
	DECLARE_MESSAGE_MAP()
public:
	CStatic * NewStatic(int nID, char * cName, CRect rect, int nStyle);
	CEdit * NewEdit(int nID, CRect rect, int nStyle);
	afx_msg void OnClose();
};
