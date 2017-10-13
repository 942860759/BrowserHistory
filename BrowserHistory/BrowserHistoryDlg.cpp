
// BrowserHistoryDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BrowserHistory.h"
#include "BrowserHistoryDlg.h"
#include "afxdialogex.h"

//#include "stdafx.h"  
#include <vector>  
#include <iostream>  
#include "afxwin.h"  
#include "BrowserAlgorithm.h"
#include <fstream>  

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBrowserHistoryDlg �Ի���



CBrowserHistoryDlg::CBrowserHistoryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BROWSERHISTORY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBrowserHistoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}

BEGIN_MESSAGE_MAP(CBrowserHistoryDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CBrowserHistoryDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CBrowserHistoryDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CBrowserHistoryDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CBrowserHistoryDlg ��Ϣ�������

BOOL CBrowserHistoryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CRect rectTemp;
	GetDlgItem(IDC_LIST1)->GetWindowRect(rectTemp);
	int columnWidth = (rectTemp.right - rectTemp.left) / 3;

	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListCtrl.InsertColumn(0, _T("���"), LVCFMT_LEFT, columnWidth);        // �����1�е�����  
	m_ListCtrl.InsertColumn(1, _T("��ַ"), LVCFMT_LEFT, columnWidth);        // �����2�е�����  
	m_ListCtrl.InsertColumn(2, _T("ʱ��"), LVCFMT_LEFT, columnWidth);        // �����3�е�����  
	
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CBrowserHistoryDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBrowserHistoryDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBrowserHistoryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBrowserHistoryDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BrowsHistory browseHistory;
	browseHistory.Init();
	while (!browseHistory.m_bStatus);//�ȴ���ȡ���  
	std::vector<BrowsData> data = browseHistory.GetBrowsHistory();
	std::vector<BrowsData>::iterator it = data.begin();

	int orderNumber = 1;
	CString stringNumber;
	CString txt;
	CString tmpStr;
	CString time;
	CString year;
	CString month;
	CString day;
	CString hour;
	CString minute;
	CString second;

	
	CStdioFile File;
	File.Open(_T("E:\\out.txt"),CFile::modeReadWrite | CFile::modeNoTruncate | CFile::modeCreate);
	File.SetLength(0);
	File.SeekToEnd();
	
	for (; it<data.end(); ++it)
	{
		wprintf(_T("%s\n"), it->strURL);
		stringNumber.Format(_T("%d"), orderNumber);
		tmpStr = stringNumber + ' ' + ' ' + ' ' + it->strURL;
		year.Format(_T("%d"), it->year); 
		month.Format(_T("%d"), it->month);
		day.Format(_T("%d"), it->day);
		hour.Format(_T("%d"), it->hour);
		minute.Format(_T("%d"), it->minute);
		second.Format(_T("%d"), it->second);
		time = year + '/' + month + '/' + day + ' ' + hour + ':' + minute + ':' + second + ' ';
		txt = txt+ tmpStr + ' ' + ' ' + ' ' + ' ' + ' ' + ' ' + ' ' + ' ' + ' ' + time +'\r'+'\n' ;
		//SetDlgItemText(IDC_EDIT1, txt);

		m_ListCtrl.InsertItem(orderNumber-1, _T(""));                          // ������  
		m_ListCtrl.SetItemText(orderNumber-1, 0, stringNumber);                     // ���õ�1��(���)  
		m_ListCtrl.SetItemText(orderNumber-1, 1, it->strURL);                     // ���õ�2��(��ַ)  
		m_ListCtrl.SetItemText(orderNumber-1, 2, time);                     // ���õ�3��(ʱ��)  

		orderNumber++;
	}

	File.WriteString(txt);
	File.Close();
}


void CBrowserHistoryDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
