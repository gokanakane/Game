//=============================================================================
//
// 背景処理 [PauseContinue.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "main.h"
#include "PauseContinue.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PAUSECONRINUE_TEXTUER  "data\\TEXTURE\\Continue.png" //読み込むテクスチャ
#define PAUSE_POS_X (280 + 150)					    //ポーズ背景左上X
#define PAUSE_POS_Y (280 - 80)					    //ポーズ背景左上Y
#define PAUSE_WIDTH (640 + 150)					    //ポーズ背景の幅
#define PAUSE_HEIGHT (640 - 80)					    //ポーズ背景高さ

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePauseContinue = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseContinue = NULL;
CONTINUSTATE g_ContinueState;

//=============================================================================
// ポリゴン初期化処理[InitPolygon]
//=============================================================================
void InitPauseContinue(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;//頂点情報へのポインタ
	
	g_ContinueState = CONTINUSTATE_SELECT;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, PAUSECONRINUE_TEXTUER, &g_pTexturePauseContinue);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseContinue, NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffPauseContinue->Lock(0, 0, (void**)&pVtx, 0);

	//背景の座標設定
	//コンテニュー座標設定
	pVtx[0].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_POS_Y , 0.0f);//一つ目の頂点の場所指定
	pVtx[1].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_POS_Y , 0.0f);//二つ目の頂点の場所指定（右回り）
	pVtx[2].pos = D3DXVECTOR3(280 + 150, 400 - 80, 0.0f);//三つ目の頂点の場所指定（右回り）
	pVtx[3].pos = D3DXVECTOR3(640 + 150, 400 - 80, 0.0f);//三つ目の頂点の場所指定（右回り）
	
	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//背景色設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）

	//背景テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	g_pVtxBuffPauseContinue->Unlock();

}
//=============================================================================
//ポリゴン終了処理 [UninitPolygon]
//=============================================================================
void UninitPauseContinue(void)
{
	//テクスチャの破棄
	if (g_pTexturePauseContinue != NULL)
	{
		g_pTexturePauseContinue->Release();
		g_pTexturePauseContinue = NULL;
	}


	//頂点バッファの破棄
	if (g_pVtxBuffPauseContinue != NULL)
	{
		g_pVtxBuffPauseContinue->Release();
		g_pVtxBuffPauseContinue = NULL;
	}

}

//=============================================================================
// ポリゴン更新処理[UpdataPolygon]
//=============================================================================
void UpdatePauseContinue(void)
{
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffPauseContinue->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_ContinueState)
	{
	case CONTINUSTATE_SELECT:
		//背景色設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		break;

	case CONTINUSTATE_NOSELECT:
		//背景色設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//一つ目の頂点の色指定（右回り）
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//一つ目の頂点の色指定（右回り）
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//一つ目の頂点の色指定（右回り）
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//一つ目の頂点の色指定（右回り）
		break;


	}
	//頂点バッファのアンロック
	g_pVtxBuffPauseContinue->Unlock();


}
//=============================================================================
// ポリゴン描写処理[DrawPolygon]
//=============================================================================
void DrawPauseContinue(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseContinue, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePauseContinue);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

}
//=============================================================================
// QUIT設定処理[DrawPolygon]
//=============================================================================
void SetContinu(CONTINUSTATE state)
{
	g_ContinueState = state;
}
