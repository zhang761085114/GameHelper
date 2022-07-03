
// MFCHelperDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCHelper.h"
#include "MFCHelperDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCHelperDlg 对话框



CMFCHelperDlg::CMFCHelperDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCHELPER_DIALOG, pParent)
	, m_szSpeed(_T(""))
	, m_szNum(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCHelperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, EDT_SPEED, m_szSpeed);
	DDX_Text(pDX, EDT_NUM, m_szNum);
}

BEGIN_MESSAGE_MAP(CMFCHelperDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BTN_WUDI, &CMFCHelperDlg::OnBnClickedWudi)
	ON_BN_CLICKED(BTN_SPEED, &CMFCHelperDlg::OnBnClickedSpeed)
	ON_BN_CLICKED(BTN_NUM, &CMFCHelperDlg::OnBnClickedNum)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCHelperDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CMFCHelperDlg 消息处理程序

BOOL CMFCHelperDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCHelperDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCHelperDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCHelperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCHelperDlg::OnBnClickedWudi()
{
	//无敌模式
	HWND hWndGame = ::FindWindow(NULL, "摿孭");

	DWORD dwPid = 0;
	GetWindowThreadProcessId(hWndGame, &dwPid);
	HANDLE hGame = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);

	BYTE btBuf = 0xeb;
	BOOL bRet = WriteProcessMemory(
	  hGame, //目标进程的句柄
	  (LPVOID)0x00403616,//写入的地址
	  &btBuf, sizeof(btBuf), //写入的数据
	  NULL
	  );


}


void CMFCHelperDlg::OnBnClickedSpeed()
{
	//改变速度，值越大，速度越慢
	HWND hWndGame = ::FindWindow(NULL, "摿孭");

	DWORD dwPid = 0;
	GetWindowThreadProcessId(hWndGame, &dwPid);
	HANDLE hGame = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);

	
	//将用户输入的值作为速度
	UpdateData(TRUE);
	BYTE bSpeed = atoi(m_szSpeed);

	BOOL bRet = WriteProcessMemory(
		hGame, //目标进程的句柄
		(LPVOID)0x004020F5,//写入的地址
		&bSpeed, sizeof(bSpeed), //写入的数据
		NULL
	);

}


void CMFCHelperDlg::OnBnClickedNum()
{
	//修改子弹个数
	HWND hWndGame = ::FindWindow(NULL, "摿孭");

	DWORD dwPid = 0;
	GetWindowThreadProcessId(hWndGame, &dwPid);
	HANDLE hGame = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);


	//将用户输入的值作为速度
	UpdateData(TRUE);
	DWORD dNum = atoi(m_szNum);

	BOOL bRet = WriteProcessMemory(
		hGame, //目标进程的句柄
		(LPVOID)0x00406DA8,//写入的地址
		&dNum, sizeof(dNum), //写入的数据
		NULL
	);
}


void CMFCHelperDlg::OnBnClickedButton4()
{
	//自动躲子弹
	HWND hWndGame = ::FindWindow(NULL, "摿孭");

	DWORD dwPid = 0;
	GetWindowThreadProcessId(hWndGame, &dwPid);
	HANDLE hGame = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);

	DWORD dDiw = 0;
	ReadProcessMemory(hGame,
		(LPVOID)0x00406D80,
		&dDiw, sizeof(dDiw),
		NULL);

	DWORD dNum = 15;
	WriteProcessMemory(
		hGame, //目标进程的句柄
		(LPVOID)0x00406DA8,//写入的地址
		&dNum, sizeof(dNum), //写入的数据
		NULL
	);

	BYTE bSpeed = 30;

	WriteProcessMemory(
		hGame, //目标进程的句柄
		(LPVOID)0x004020F5,//写入的地址
		&bSpeed, sizeof(bSpeed), //写入的数据
		NULL
	);

	//初始将飞机置于屏幕中央
	DWORD dPlanX_Init = 152;
	DWORD dPlanY_Init = 113;


	BOOL bDanger = FALSE;		//危险标志，为TRUE，优先躲子弹，为FALSE，可以考虑往中心靠

	while (dDiw == 0) {			//无限循环，对飞机坐标进行位移，躲避子弹

		


		//获取死亡标志
		ReadProcessMemory(hGame,
			(LPVOID)0x00406D80,
			&dDiw, sizeof(dDiw),
			NULL);



		//获取飞机的坐标
		DWORD dPlanX = 0;
		DWORD dPlanY = 0;

		ReadProcessMemory(hGame,
			(LPVOID)0x00406D6C,
			&dPlanX, sizeof(dPlanX),
			NULL);

		ReadProcessMemory(hGame,
			(LPVOID)0x00406D70,
			&dPlanY, sizeof(dPlanY),
			NULL);

		//让飞机尽量往中心靠
		//如果飞机左边有中心，向左移动一点点
		if (!bDanger) {
			Sleep(10);
			if (dPlanX_Init < dPlanX - 4 && dPlanY - 4 < dPlanY_Init && dPlanY_Init < dPlanY + 4) {

				dPlanX -= 1;
				WriteProcessMemory(
					hGame, //目标进程的句柄
					(LPVOID)0x00406D6C,//写入的地址
					&dPlanX, sizeof(dPlanX), //写入的数据
					NULL
				);
			}

			//如果飞机左上有中心，向左上移动一点点
			if (dPlanX_Init < dPlanX - 4 && dPlanY + 4 < dPlanY_Init) {

				dPlanX -= 1;
				dPlanY += 1;
				WriteProcessMemory(
					hGame, //目标进程的句柄
					(LPVOID)0x00406D6C,//写入的地址
					&dPlanX, sizeof(dPlanX), //写入的数据
					NULL
				);
				WriteProcessMemory(
					hGame, //目标进程的句柄
					(LPVOID)0x00406D70,//写入的地址
					&dPlanY, sizeof(dPlanY), //写入的数据
					NULL
				);
			}
			//如果飞机左下有中心，向左下移动一点点
			if (dPlanX_Init < dPlanX - 4 &&dPlanY_Init < dPlanY - 4) {

				dPlanX -= 1;
				dPlanY -= 1;
				WriteProcessMemory(
					hGame, //目标进程的句柄
					(LPVOID)0x00406D6C,//写入的地址
					&dPlanX, sizeof(dPlanX), //写入的数据
					NULL
				);
				WriteProcessMemory(
					hGame, //目标进程的句柄
					(LPVOID)0x00406D70,//写入的地址
					&dPlanY, sizeof(dPlanY), //写入的数据
					NULL
				);
			}

			//如果飞机下边有中心，向下边移动一点点
			if (dPlanX - 4 < dPlanX_Init && dPlanX_Init < dPlanX + 4 && dPlanY_Init < dPlanY - 4) {

				dPlanY -= 1;
				WriteProcessMemory(
					hGame, //目标进程的句柄
					(LPVOID)0x00406D70,//写入的地址
					&dPlanY, sizeof(dPlanY), //写入的数据
					NULL
				);
			}

			//如果飞机右边有中心，向右边移动一点点
			if (dPlanX + 4 < dPlanX_Init && dPlanY - 4 < dPlanY_Init && dPlanY_Init < dPlanY + 4) {

				dPlanX += 1;
				WriteProcessMemory(
					hGame, //目标进程的句柄
					(LPVOID)0x00406D6C,//写入的地址
					&dPlanX, sizeof(dPlanX), //写入的数据
					NULL
				);
			}
			//如果飞机上边有中心，向上边移动一点点
			if (dPlanX - 4 < dPlanX_Init && dPlanX_Init < dPlanX + 4 && dPlanY + 4 < dPlanY_Init) {

				dPlanY += 1;
				WriteProcessMemory(
					hGame, //目标进程的句柄
					(LPVOID)0x00406D70,//写入的地址
					&dPlanY, sizeof(dPlanY), //写入的数据
					NULL
				);
			}


			//如果飞机右上有中心，向右上移动一点点
			if (dPlanX + 4 < dPlanX_Init && dPlanY + 4 < dPlanY_Init) {

				dPlanX += 1;
				dPlanY += 1;
				WriteProcessMemory(
					hGame, //目标进程的句柄
					(LPVOID)0x00406D6C,//写入的地址
					&dPlanX, sizeof(dPlanX), //写入的数据
					NULL
				);
				WriteProcessMemory(
					hGame, //目标进程的句柄
					(LPVOID)0x00406D70,//写入的地址
					&dPlanY, sizeof(dPlanY), //写入的数据
					NULL
				);
			}
			//如果飞机右下有中心，向右下移动一点点
			if (dPlanX + 4 < dPlanX_Init && dPlanY_Init < dPlanY - 4) {

				dPlanX += 1;
				dPlanY -= 1;
				WriteProcessMemory(
					hGame, //目标进程的句柄
					(LPVOID)0x00406D6C,//写入的地址
					&dPlanX, sizeof(dPlanX), //写入的数据
					NULL
				);
				WriteProcessMemory(
					hGame, //目标进程的句柄
					(LPVOID)0x00406D70,//写入的地址
					&dPlanY, sizeof(dPlanY), //写入的数据
					NULL
				);
			}
		}




		//获取当前子弹个数
		DWORD dNum = 0;
		ReadProcessMemory(hGame,
			(LPVOID)0x00406DA8,
			&dNum, sizeof(dNum),
			NULL);

		//获取每个子弹的当前坐标
		DWORD dBulletX[50] = { 0 };
		DWORD dBulletY[50] = { 0 };
		for (int i = 0; i < dNum; i++) {

			BOOL bRet = ReadProcessMemory(hGame,
				(LPVOID)(0x00406E10 + i * 0xf + 0),
				&dBulletX[i], sizeof(DWORD),
				NULL);

			ReadProcessMemory(hGame,
				(LPVOID)(0x00406E10 + i * 0xf + 4),
				&dBulletY[i], sizeof(DWORD),
				NULL);

			dBulletX[i] >>= 6;
			dBulletX[i] -= 4;
			dBulletY[i] >>= 6;
			dBulletY[i] -= 4;
		}
		for (int j = 0; j < dNum; j++) {
		
			bDanger = FALSE;
			//如果飞机左边有子弹，向右移动一点点
			if (dPlanX - 20 < dBulletX[j] && dBulletX[j] < dPlanX - 4 && dPlanY - 4 < dBulletY[j] && dBulletY[j] < dPlanY + 4) {

				dPlanX += 1;
				WriteProcessMemory(
					hGame, //目标进程的句柄
					(LPVOID)0x00406D6C,//写入的地址
					&dPlanX, sizeof(dPlanX), //写入的数据
					NULL
				);
				bDanger = TRUE;
				break;
			}

			//如果飞机左上有子弹，向右下移动一点点
			if (dPlanX - 20 < dBulletX[j] && dBulletX[j] < dPlanX - 4 && dPlanY + 4 < dBulletY[j] && dBulletY[j] < dPlanY + 20) {

				dPlanX += 1;
				dPlanY -= 1;
				WriteProcessMemory(
					hGame, //目标进程的句柄
					(LPVOID)0x00406D6C,//写入的地址
					&dPlanX, sizeof(dPlanX), //写入的数据
					NULL
				);
				WriteProcessMemory(
					hGame, //目标进程的句柄
					(LPVOID)0x00406D70,//写入的地址
					&dPlanY, sizeof(dPlanY), //写入的数据
					NULL
				);
				bDanger = TRUE;
				break;
			}
			//如果飞机左下有子弹，向右上移动一点点
			if (dPlanX - 20 < dBulletX[j] && dBulletX[j] < dPlanX - 4 && dPlanY - 20 < dBulletY[j] && dBulletY[j] < dPlanY - 4) {

				dPlanX += 1;
				dPlanY += 1;
				WriteProcessMemory(
					hGame, //目标进程的句柄
					(LPVOID)0x00406D6C,//写入的地址
					&dPlanX, sizeof(dPlanX), //写入的数据
					NULL
				);
				WriteProcessMemory(
					hGame, //目标进程的句柄
					(LPVOID)0x00406D70,//写入的地址
					&dPlanY, sizeof(dPlanY), //写入的数据
					NULL
				);
				bDanger = TRUE;
				break;
			}

			//如果飞机下边有子弹，向上移动一点点
			if (dPlanX - 4 < dBulletX[j] && dBulletX[j] < dPlanX + 4 && dPlanY - 20 < dBulletY[j] && dBulletY[j] < dPlanY - 4) {

				dPlanY += 1;
				WriteProcessMemory(
					hGame, //目标进程的句柄
					(LPVOID)0x00406D70,//写入的地址
					&dPlanY, sizeof(dPlanY), //写入的数据
					NULL
				);
				bDanger = TRUE;
				break;
			}

			//如果飞机右边有子弹，向左移动一点点
			if (dPlanX + 4 < dBulletX[j] && dBulletX[j] < dPlanX + 20 && dPlanY - 4 < dBulletY[j] && dBulletY[j] < dPlanY + 4) {

				dPlanX -= 1;
				WriteProcessMemory(
					hGame, //目标进程的句柄
					(LPVOID)0x00406D6C,//写入的地址
					&dPlanX, sizeof(dPlanX), //写入的数据
					NULL
				);
				bDanger = TRUE;
				break;
			}
			//如果飞机上边有子弹，向下移动一点点
			if (dPlanX - 4 < dBulletX[j] && dBulletX[j] < dPlanX + 4 && dPlanY + 4 < dBulletY[j] && dBulletY[j] < dPlanY + 20) {

				dPlanY -= 1;
				WriteProcessMemory(
					hGame, //目标进程的句柄
					(LPVOID)0x00406D70,//写入的地址
					&dPlanY, sizeof(dPlanY), //写入的数据
					NULL
				);
				bDanger = TRUE;
				break;
			}
				

			//如果飞机右上有子弹，向左下移动一点点
			if (dPlanX + 4 < dBulletX[j] && dBulletX[j] < dPlanX + 20 && dPlanY + 4 < dBulletY[j] && dBulletY[j] < dPlanY + 20) {

				dPlanX -= 1;
				dPlanY -= 1;
				WriteProcessMemory(
					hGame, //目标进程的句柄
					(LPVOID)0x00406D6C,//写入的地址
					&dPlanX, sizeof(dPlanX), //写入的数据
					NULL
				);
				WriteProcessMemory(
					hGame, //目标进程的句柄
					(LPVOID)0x00406D70,//写入的地址
					&dPlanY, sizeof(dPlanY), //写入的数据
					NULL
				);
				bDanger = TRUE;
				break;
			}
			//如果飞机右下有子弹，向左上移动一点点
			if (dPlanX + 4 < dBulletX[j] && dBulletX[j] < dPlanX + 20 && dPlanY - 20 < dBulletY[j] && dBulletY[j] < dPlanY - 4) {

				dPlanX -= 1;
				dPlanY += 1;
				WriteProcessMemory(
					hGame, //目标进程的句柄
					(LPVOID)0x00406D6C,//写入的地址
					&dPlanX, sizeof(dPlanX), //写入的数据
					NULL
				);
				WriteProcessMemory(
					hGame, //目标进程的句柄
					(LPVOID)0x00406D70,//写入的地址
					&dPlanY, sizeof(dPlanY), //写入的数据
					NULL
				);
				bDanger = TRUE;
				break;
			}





		}


	}
}
