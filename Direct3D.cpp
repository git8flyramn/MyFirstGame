#include "Direct3D.h"
#include <d3dcompiler.h>
#include <DirectXMath.h>
namespace Direct3D
{
	ID3D11Device* pDevice;		                 //デバイス
	ID3D11DeviceContext* pContext;		         //デバイスコンテキスト
	IDXGISwapChain* pSwapChain;		             //スワップチェイン
	ID3D11RenderTargetView* pRenderTargetView;	 //レンダーターゲットビュー

    struct SHADER_BUNDOLE
    {
        ID3D11VertexShader* pVertexShader;
        ID3D11PixelShader* pPixelShader;
        ID3D11InputLayout* pVertexLayOut;
        ID3D11RasterizerState* pRasterizerState;
    };

    ID3D11VertexShader* pVertexShader = nullptr;	//頂点シェーダー
    ID3D11PixelShader* pPixelShader = nullptr;		//ピクセルシェーダー

    ID3D11InputLayout* pVertexLayout = nullptr;	//頂点インプットレイアウト
    ID3D11RasterizerState* pRasterizerState = nullptr;	//ラスタライザー
    
    SHADER_BUNDOLE shaderBundle[SHADER_MAX];
}

HRESULT Direct3D::InitShader()
{
    if (FAILED(InitShader3D))
    {
        return E_FAIL;
    }
    if (FAILED(InitShader2D))
    {
        return E_FAIL;
    }
    return S_OK;
}

HRESULT Direct3D::InitShader3D()
{
    HRESULT hr;
    // 頂点シェーダの作成（コンパイル）
    ID3DBlob* pCompileVS = nullptr;
    D3DCompileFromFile(L"Simple.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
    assert(pCompileVS != nullptr);
    
   hr =  pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(),
         pCompileVS->GetBufferSize(), NULL, &(shaderBundle[SHADER_3D].pVertexShader));

    
   if (FAILED(hr))
   {
       MessageBox(nullptr, L"頂点シェーダの作成に失敗しました", L"エラー", MB_OK);
       return hr;
   }
   
    // ピクセルシェーダの作成（コンパイル）
    ID3DBlob* pCompilePS = nullptr;
    D3DCompileFromFile(L"Simple.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
    assert(pCompilePS != nullptr);
    hr = pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(),
         pCompilePS->GetBufferSize(), NULL, &(shaderBundle[SHADER_3D].pPixelShader));
    if (FAILED(hr))
    {
        MessageBox(nullptr, L"ピクセルシェーダの作成に失敗しました", L"エラー", MB_OK);
        return hr;
    }

    //頂点インプットレイアウト
    D3D11_INPUT_ELEMENT_DESC layout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },//位置
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,sizeof(DirectX::XMFLOAT4) , D3D11_INPUT_PER_VERTEX_DATA, 0},//UV座標
        {  "NORMAL",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(DirectX::XMFLOAT4)+ sizeof(DirectX::XMFLOAT4),	D3D11_INPUT_PER_VERTEX_DATA, 0},//法線
    };

    hr = pDevice->CreateInputLayout(layout, 3, pCompileVS->GetBufferPointer(),
        pCompileVS->GetBufferSize(), &(shaderBundle[SHADER_3D].pVertexLayOut));

    if (FAILED(hr))
    {
        MessageBox(nullptr, L"頂点インプットレイアウトの作成に失敗しました", L"エラー", MB_OK);
        return hr;
    }
    pCompilePS->Release();
    pCompileVS->Release();



    //ラスタライザ作成
    D3D11_RASTERIZER_DESC rdc = {};
    rdc.CullMode = D3D11_CULL_BACK;
    rdc.FillMode = D3D11_FILL_SOLID;
    rdc.FrontCounterClockwise = FALSE;
    pDevice->CreateRasterizerState(&rdc, &(shaderBundle[SHADER_3D].pRasterizerState));

    //それぞれをデバイスコンテキストにセット
    //pContext->VSSetShader(pVertexShader, NULL, 0);	//頂点シェーダー
    //pContext->PSSetShader(pPixelShader, NULL, 0);	//ピクセルシェーダー
    //pContext->IASetInputLayout(pVertexLayout);	//頂点インプットレイアウト
    //pContext->RSSetState(pRasterizerState);		//ラスタライザー

    return S_OK;
}

HRESULT Direct3D::InitShader2D()
{
    HRESULT hr;
    // 頂点シェーダの作成（コンパイル）
    ID3DBlob* pCompileVS = nullptr;
    D3DCompileFromFile(L"Simple2D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
    assert(pCompileVS != nullptr);

    hr = pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL,&(shaderBundle[SHADER_2D].pVertexShader));

    if (FAILED(hr))
    {
        MessageBox(nullptr, L"頂点シェーダの作成に失敗しました", L"エラー", MB_OK);
        return hr;
    }

    // ピクセルシェーダの作成（コンパイル）
    ID3DBlob* pCompilePS = nullptr;
    D3DCompileFromFile(L"Simple2D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
    assert(pCompilePS != nullptr);
    hr = pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), 
         pCompilePS->GetBufferSize(), NULL, &(shaderBundle[SHADER_2D].pPixelShader));
    if (FAILED(hr))
    {
        MessageBox(nullptr, L"ピクセルシェーダの作成に失敗しました", L"エラー", MB_OK);
        return hr;
    }

    //頂点インプットレイアウト
    D3D11_INPUT_ELEMENT_DESC layout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },//位置
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,sizeof(DirectX::XMVECTOR) , D3D11_INPUT_PER_VERTEX_DATA, 0},//UV座標
    };

    hr = pDevice->CreateInputLayout(layout, 2, pCompileVS->GetBufferPointer(),
        pCompileVS->GetBufferSize(), &(shaderBundle[SHADER_2D].pVertexLayOut));

    if (FAILED(hr))
    {
        return hr;
    }
    pCompileVS->Release();
    pCompilePS->Release();



    //ラスタライザ作成
    D3D11_RASTERIZER_DESC rdc = {};
    rdc.CullMode = D3D11_CULL_NONE;
    rdc.FillMode = D3D11_FILL_SOLID;
    rdc.FrontCounterClockwise = FALSE;
    pDevice->CreateRasterizerState(&rdc, &(shaderBundle[SHADER_2D].pRasterizerState));

    //それぞれをデバイスコンテキストにセット
    //pContext->VSSetShader(pVertexShader, NULL, 0);	//頂点シェーダー
    //pContext->PSSetShader(pPixelShader, NULL, 0);	//ピクセルシェーダー
    //pContext->IASetInputLayout(pVertexLayout);	//頂点インプットレイアウト
    //pContext->RSSetState(pRasterizerState);		//ラスタライザー
    
    return S_OK;
}

void Direct3D::SetShader(SHADER_TYPE type)
{
    pContext->VSSetShader(shaderBundle[type].pVertexShader, NULL, 0);	//頂点シェーダー
   pContext->PSSetShader(shaderBundle[type].pPixelShader, NULL, 0);	//ピクセルシェーダー
   pContext->IASetInputLayout(shaderBundle[type].pVertexLayOut);	//頂点インプットレイアウト
   pContext->RSSetState(shaderBundle[type].pRasterizerState);		//ラスタライザー

}


HRESULT Direct3D::Initialize(int winW, int winH, HWND hWnd)
{
    //Direct3Dの初期化
    DXGI_SWAP_CHAIN_DESC scDesc = {};
    ZeroMemory(&scDesc, sizeof(scDesc));
    scDesc.BufferDesc.Width = winW;
    scDesc.BufferDesc.Height = winH;
    scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    //FPS（1/60秒に1回）
    scDesc.BufferDesc.RefreshRate.Numerator = 60;
    scDesc.BufferDesc.RefreshRate.Denominator = 1;

    //その他
    scDesc.Windowed = TRUE;			//ウィンドウモードかフルスクリーンか
    scDesc.OutputWindow = hWnd;		//ウィンドウハンドル
    scDesc.BufferCount = 1;			//バックバッファの枚数
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//バックバッファの使い道＝画面に描画するために
    scDesc.SampleDesc.Count = 1;		//MSAA（アンチエイリアス）の設定
    scDesc.SampleDesc.Quality = 0;		//　〃

    ////////////////上記設定をもとにデバイス、コンテキスト、スワップチェインを作成////////////////////////
    D3D_FEATURE_LEVEL level;
    D3D11CreateDeviceAndSwapChain(
        nullptr,				// どのビデオアダプタを使用するか？既定ならばnullptrで
        D3D_DRIVER_TYPE_HARDWARE,		// ドライバのタイプを渡す。ふつうはHARDWARE
        nullptr,				// 上記をD3D_DRIVER_TYPE_SOFTWAREに設定しないかぎりnullptr
        0,					// 何らかのフラグを指定する。（デバッグ時はD3D11_CREATE_DEVICE_DEBUG？）
        nullptr,				// デバイス、コンテキストのレベルを設定。nullptrにしとけばOK
        0,					// 上の引数でレベルを何個指定したか
        D3D11_SDK_VERSION,			// SDKのバージョン。必ずこの値
        &scDesc,				// 上でいろいろ設定した構造体
        &pSwapChain,				// 無事完成したSwapChainのアドレスが返ってくる
        &pDevice,				// 無事完成したDeviceアドレスが返ってくる
        &level,					// 無事完成したDevice、Contextのレベルが返ってくる
        &pContext);				// 無事完成したContextのアドレスが返ってくる

    ///////////////////////////レンダーターゲットビュー作成///////////////////////////////
    //スワップチェーンからバックバッファを取得（バックバッファ ＝ レンダーターゲット）
    ID3D11Texture2D* pBackBuffer;
    pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    //レンダーターゲットビューを作成
    pDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);

    //一時的にバックバッファを取得しただけなので解放
    pBackBuffer->Release();


    ///////////////////////////ビューポート（描画範囲）設定///////////////////////////////
    //レンダリング結果を表示する範囲
    D3D11_VIEWPORT vp;
    vp.Width = (float)winW;	//幅
    vp.Height = (float)winH;//高さ
    vp.MinDepth = 0.0f;	//手前
    vp.MaxDepth = 1.0f;	//奥
    vp.TopLeftX = 0;	//左
    vp.TopLeftY = 0;	//上

    //データを画面に描画するための一通りの設定（パイプライン）
    //Topology = 繋がり
    pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);  // データの入力種類を指定
    pContext->OMSetRenderTargets(1, &pRenderTargetView, nullptr);            // 描画先を設定
    pContext->RSSetViewports(1, &vp);

    HRESULT hr;
    hr = InitShader();
    if (FAILED(hr))
    {
        return hr;
    }
    return S_OK;
}

void Direct3D::BeginDraw()
{
    //背景の色
    float clearColor[4] = { 0.0f, 0.5f, 0.5f, 1.0f };//R,G,B,A
    //画面をクリア
    pContext->ClearRenderTargetView(pRenderTargetView, clearColor);

}

void Direct3D::EndDraw()
{
    //スワップ（バックバッファを表に表示する）
    pSwapChain->Present(0, 0);
}

void Direct3D::Release()
{
    SAFE_RELEASE(pRasterizerState);
    SAFE_RELEASE(pVertexLayout);
    SAFE_RELEASE(pPixelShader);
    SAFE_RELEASE(pVertexShader);

    SAFE_RELEASE(pDevice);
    SAFE_RELEASE(pContext);
    SAFE_RELEASE(pSwapChain);
    SAFE_RELEASE(pRenderTargetView)
    //pRasterizerState->Release();
    //pVertexLayout->Release();
    //pPixelShader->Release();
    //pVertexShader->Release();
 
    //pDevice->Release();		                 //デバイス
    //pContext->Release();		         //デバイスコンテキスト
    //pSwapChain->Release();		             //スワップチェイン
    //pRenderTargetView->Release();	 //レンダーターゲットビュー
}
