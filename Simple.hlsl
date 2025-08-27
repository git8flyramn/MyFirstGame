//───────────────────────────────────────
// テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────

//  Sample3D.hlsl
Texture2D g_texture : register(t0); //テクスチャー
SamplerState g_sampler : register(s0); //サンプラー

//───────────────────────────────────────
// コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer global
{
    float4x4 matWVP; // ワールド・ビュー・プロジェクションの合成行列
    //float4x4 matW; //ワールド行列
    float4x4 matNomal;
    float4x4 matWorld;
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
                 //セマンティクス
    float4 pos : SV_POSITION; //位置
    float2 uv : TEXCOORD; //UV座標
    float4 color : COLOR; //色(明るさ)
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NOMAL)
{
	//ピクセルシェーダーへ渡す情報
    VS_OUT outData;

	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
	//スクリーン座標に変換し、ピクセルシェーダーへ
    //法線を回転
    //nomal = matW;
    outData.pos = mul(pos, matWVP);
    outData.uv = uv.xy;//UV座標はそのまま
    
    normal = mul(normal, matNomal);//法線ベクトルをワールドビュー・プロジェクション行列で変換
   
    normal = normalize(normal);//法線ベクトルを正規化=長さ1に
    normal.w = 0;//w成分は0にする
    
    float light = float4(-1, 0.5, -0.7, 0);
    light = normalize(light);
    
    outData.color = dot(normal, light);
    
    return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
    float4 color = g_texture.Sample(g_sampler, inData.uv) * inData.color;
    //float4 ret = float(inData.uv.x,inData.uv.y,0,1;
    return color;
}