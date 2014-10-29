
// Test_3DDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test_3D.h"
#include "Test_3DDlg.h"
#include "afxdialogex.h"
#include <afxpriv.h>
#include <MMSystem.h>
#include <vector>

#pragma comment(lib, "winmm.lib") 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTest_3DDlg �Ի���



CTest_3DDlg::CTest_3DDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CTest_3DDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTest_3DDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTest_3DDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)			// The fucking MFC trick
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CTest_3DDlg ��Ϣ�������

BOOL CTest_3DDlg::OnInitDialog()
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	this->MoveWindow(0, 0, 1024 + GetSystemMetrics(SM_CXFIXEDFRAME) * 2, 600 + GetSystemMetrics(SM_CYFIXEDFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION), TRUE);


	CRect rcClient;
	GetClientRect(&rcClient);
	int nSceneWidth = rcClient.Width();
	int nSceneHeight = rcClient.Height();
	CDC* pDC = GetDC();
	//	PlaySound(L"D:\\VS2010\\GameMedia\\Music\\Eternal Love (Short Version).wav", NULL, SND_FILENAME | SND_ASYNC|SND_LOOP);   //ѭ�����ű�������
	if (!g_objBase.Initialize(pDC->m_hDC, nSceneWidth, nSceneHeight) != S_OK)
	{
		this->MessageBox(L"3D ��ʼ��ʧ��!", L"error", MB_OK | MB_ICONERROR);
		this->EndDialog(IDCANCEL);
		ReleaseDC(pDC);
		return TRUE;
	}

	//ReleaseDC(pDC);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTest_3DDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTest_3DDlg::OnPaint()
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
HCURSOR CTest_3DDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CTest_3DDlg::OnKickIdle(WPARAM wp, LPARAM lCount)
{
	static DWORD timeLoop = 0;
	const DWORD FRAME_INTERVAL = 30; //30 ����

	DWORD timerNow = timeGetTime();

	if (timerNow < timeLoop + FRAME_INTERVAL)
	{
		::Sleep(timeLoop + FRAME_INTERVAL - timerNow);
	}
	else
	{
		////һ֡��Ҫ��ʱ�䣬���� �ٶ�
		float deltaTime = (timerNow - timeLoop)*0.001f;
		timeLoop = timeGetTime();
		Process();
	}
	return 1;
}
class EulerAngle
{
public:
	float m_fYaw, m_fPitch, m_fRoll;
public:
	EulerAngle(void) : m_fYaw(0.0f), m_fPitch(0.0f), m_fRoll(0.0f) {}
	~EulerAngle(void) {}
};


#define CLAMP(x , min , max) ((x) > (max) ? (max) : ((x) < (min) ? (min) : x))
EulerAngle GetEulerAngle(glm::quat q)
{
	EulerAngle ea;

	/// Cartesian coordinate System 
	//ea.m_fRoll  = atan2(2 * (w * x + y * z) , 1 - 2 * (x * x + y * y));
	//ea.m_fPitch = asin(2 * (w * y - z * x));
	//ea.m_fYaw   = atan2(2 * (w * z + x * y) , 1 - 2 * (y * y + z * z));

	ea.m_fRoll = atan2(2 * (q.w * q.z + q.x * q.y), 1 - 2 * (q.z * q.z + q.x * q.x));
	ea.m_fPitch = asin(CLAMP(2 * (q.w * q.x - q.y * q.z), -1.0f, 1.0f));
	ea.m_fYaw = atan2(2 * (q.w * q.y + q.z * q.x), 1 - 2 * (q.x * q.x + q.y * q.y));
	ea.m_fRoll = glm::degrees(ea.m_fRoll);
	return ea;
}

void CTest_3DDlg::Process()
{
	g_objGameManager.Process();
	

/*
	//g_objRender.DrawCube();
	//g_objRender.DrawCube(1);
	//g_objBase.DrawGLScene();
	float radians = 3.141592653*(::timeGetTime() / 1000.0f / 3);

	g_objRender.ShowTexture(300, 100, 800, 130, g_objTextureMgr.GetTexture("ExampleBillboard.dds")->m_TextureId);

	g_objRender.ShowTexture(200, 300, g_objTextureMgr.GetTexture("npc1.png"));
	CTexture* pTexture = g_objTextureMgr.GetTexture("npc1.png");
	RECT pSrcTmp;
	if (pTexture)
	{
		pSrcTmp.left = 0;
		pSrcTmp.right = pTexture->m_nWidth;
		pSrcTmp.top = 0;
		pSrcTmp.bottom = pTexture->m_nHeight;
	}
	
	g_objRender.ShowTextureEx(100, 100, &pSrcTmp, 300, 300, pTexture,0.0f);


	g_objRender.ShowRectEx(0, 0, 100, 100, DX_SCREEN_COLOR(0, 1, 0));*/
}

void CTest_3DDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	MousePos pos;
	pos.X = point.x;
	pos.Y = point.y;
	g_ojbInputManager.MouseEven(MouseDown, pos);
}

void CTest_3DDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	MousePos pos;
	pos.X = point.x;
	pos.Y = point.y;
	g_ojbInputManager.MouseEven(MouseMove, pos);
}

void CTest_3DDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	MousePos pos;
	pos.X = point.x;
	pos.Y = point.y;
	g_ojbInputManager.MouseEven(MouseUp, pos);
}

void CTest_3DDlg::OnDestroy()
{

}

