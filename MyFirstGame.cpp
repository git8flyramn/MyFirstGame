﻿// MyFirstGame.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "MyFirstGame.h"
#include "Engine/Direct3D.h"
#include "Engine/Camera.h"
#include "Engine/Transform.h"
#include "Engine/Input.h"
#include "Engine/RootJob.h"
#include "Engine/Model.h"
#include "TestScene.h"
#include "Player.h"

#pragma comment(lib, "winmm.lib")

HWND hWnd = nullptr;

#define MAX_LOADSTRING 100

//グローバル変数の宣言

const wchar_t* WIN_CLASS_NAME = L"SAMPLE_GAME_WINDOW";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

RootJob* pRootJob = nullptr;
//先に描画する
TestScene* pTestScene = nullptr;
//エンターキーを押した時
Player* pPlayer = nullptr;
// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    /*
    *   HINSTANCE hInstance  インスタンスハンドルというものアプリを識別するための一意の値が入る

        HINSTANCE hPrevInstance,同じインスタンスハンドルでも、Win32API・Win16APIの互換性を保つために
                               用意された引数,常にNULLが入る。
        int   アプリをどのような形式で表示するかを示したもの、

        lpCmdLine コマンドライン引数を表す文字列へのポインタです

        nCmdShow メインアプリケーションウィンドウが最小化、
                 最大化、また正常に表示されるかどうかを示すグラフ。


    */
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ここにコードを挿入してください。


    // グローバル文字列を初期化する
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MYFIRSTGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    
   

    // アプリケーション初期化の実行:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }
   
    //Direct3Dの初期化
    HRESULT hr;
    hr = Direct3D::Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, hWnd);
    if (FAILED(hr))
    {
        return 0;
    }
    Camera::Initialize();
    Input::Initialize(hWnd); //入力の初期化
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYFIRSTGAME));

    MSG msg = {};
    //メンバ変数の物
    pRootJob = new RootJob(nullptr);
    pTestScene = new TestScene(nullptr);
    pPlayer= new Player(nullptr);
   //ゲームで増える物
    pRootJob->Initialize();
    pTestScene->Initialize();
    pPlayer->Initialize();
   /* Fbx* fbx = new Fbx();
   fbx->Load("ODEN2.fbx");*/
   // Transform* transform = new Transform();
 //  Dice* dice = new Dice();
  // hr = dice->Initialize();
  // hr = sprite->Initialize();
  //  ZeroMemory(&msg, sizeof(msg));
    // メイン メッセージ ループ:　ユーザー操作(クリックやキー入力)を受け取り、処理を続ける仕組み
    while (msg.message != WM_QUIT)
    {

        while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        //メッセージなし
        timeBeginPeriod(1);
        static DWORD countFps = 0; //FPS計測用カウンタ
        static DWORD startTime = timeGetTime();//初回の時間を保存
        DWORD nowTime = timeGetTime();//現在の時間を取得
        static DWORD lastUpdateTime = nowTime;
        if (nowTime - startTime >= 1000)
        {
            std::string str = "FPS" + std::to_string(nowTime - startTime) + "," + std::to_string(countFps);
            SetWindowTextA(hWnd, str.c_str());
            countFps = 0;
            startTime = nowTime;
        }

        if (nowTime - lastUpdateTime <= 1000.0f / 60)
        {
            continue;
        }
        lastUpdateTime = nowTime;
        countFps++;
       // startTime = nowTime;
        timeEndPeriod(1);
        //ゲームの処理
        Camera::Update(); // カメラの更新
        Input::Update();
        pRootJob->UpdateSub();

       
        pTestScene->Update();
        pPlayer->Update();

      /*  if (Input::IsKey(DIK_ESCAPE))
        {
            static int cnt = 0;
            cnt++;
            if (cnt > 3)
            {
                PostQuitMessage(0);
            }
        }*/
      
          
     
       
        Direct3D::BeginDraw();
         //pRootJobから、すべてのオブジェクトの描画
        static float time = 0.0f;
        time += 0.03f;
        if (time <= 25.0f)
        {
            pRootJob->DrawSub();
          
        }
        else
        {
            pPlayer->Draw();
        }
       
           
            //pPlayer->Draw();
           
       
       
       
       //  trans.position_.x = 1.0f;
      //  trans.rotate_.y  = 0.1f;
      //  trans.Calculation();
      //  fbx->Draw(trans);*/

        Direct3D::EndDraw();
       /* static Transform trans;
        trans.position_.x = 1.0f;
        trans.position_.y += 0.1f;
        trans.rotate_.z  = 0.0f;
        trans.rotate_.y += +1.0f;
        trans.Calculation();
        fbx->Draw(trans);   
       Direct3D::EndDraw();*/
       
    }
    Model::Release();
    pRootJob->ReleaseSub();
    Input::Release();
  //  pPlayer->Release();
    Direct3D::Release();
    return (int) msg.wParam;
}



//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    //ウィンドウの拡張スタイルを指定する
    wcex.cbSize = sizeof(WNDCLASSEX);

    //ウィンドウの外観や振る舞いを決定する属性です
    wcex.style          = CS_HREDRAW | CS_VREDRAW;

    //ウィンドウプロシージャへのポインタ。ウィンドウメッセージを処理します。
    wcex.lpfnWndProc    = WndProc;
    
    //ウィンドウクラスに追加のバイト数を指定します
    wcex.cbClsExtra   = 0;
    //wcex.cbClsExtra = 0;
    //ウィンドウに追加のバイト数を指定します
    wcex.cbWndExtra     = 0;
    // wcex.cbWndExtra  = 0;
    //ウィンドウクラスを登録したモジュールのハンドル
    wcex.hInstance      = hInstance;
    
    //ウィンドウのタイトルバーやタスクバーに表示されるアイコン
   //wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HAND));
   wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYFIRSTGAME));

    //マウスカーソルがウィンドウ内にある時に表示されるカーソル
    //wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    
    //ウィンドウのクライアント領域の背景色
    //wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    //ウィンドウに関連付けられたメニューの名前
    wcex.lpszMenuName = NULL;

    //ウィンドウクラスの名前
    wcex.lpszClassName = szWindowClass;


    
    //小さいアイコンのハンドル。
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    //wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    return RegisterClassExW(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する

   RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
   AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
   int winW = winRect.right - winRect.left;     //ウィンドウ幅
   int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ

   hWnd = CreateWindowW(szWindowClass, WIN_CLASS_NAME, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, winW,winH, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND  - アプリケーション メニューの処理
//  WM_PAINT    - メイン ウィンドウを描画する
//  WM_DESTROY  - 中止メッセージを表示して戻る
//
//

//ウィンドウに送信されたメッセージを処理する関数 メインメッセージループに応じた動きをする
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 選択されたメニューの解析:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: HDC を使用する描画コードをここに追加してください...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_MOUSEMOVE:
    {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        Input::SetMousePosition(x, y);
        OutputDebugStringA((std::to_string(x) + "." + std::to_string(y) + "\n").c_str());
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    
 
    }
    return 0;
}

// バージョン情報ボックスのメッセージ ハンドラーです。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

/*
CreateWindowExの引数と戻り値の意味
引数

dxExStyle
ウィンドウの拡張スタイルを指定する。

pczClassName
ウィンドウクラスの名前を表す文字列へのポインタを指定する。

pszWindowName
ウィンドウ名を表す文字列のアドレスを指定する。

dwStyle
作成されるウィンドウスタイルを指定する。

x,y
作成するウィンドウの座標を指定する。

nWidth,nHeight
作成するウィンドウのサイズを指定する。

hWndParent
作成されるウィンドウの親ウィンドウのハンドルを指定する。

hMenu
オーバーラップウィンドウやポップアップウィンドウを作成する場合のメニューのハンドル
の指定

hInstance
ウィンドウに関連付けされたモジュールのインスタンスハンドルを指定する

pPpram
WM_CREATEメッセージのParamパラメータとして渡される、CREATESTRUCT構造体のアドレスをする。

戻り値
成功すると、作成したウィンドウのハンドルが返ります。
失敗すると0(NULL)が返ります。
*/