//=============================================================================
//
// ポーズ背景処理 [PauseBG.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "main.h"
#include "PauseBG.h"
#include "bg.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePauseBG = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseBG = NULL;

//=============================================================================
// ポリゴン初期化処理[InitPolygon]
//=============================================================================
void InitPauseBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTUER, &g_pTexturePauseBG);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseBG, NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffPauseBG->Lock(0, 0, (void**)&pVtx, 0);

	//ポーズ背景の座標設定
	pVtx[0].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_POS_Y, 0.0f);//一つ目の頂点の場所指定
	pVtx[1].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_POS_Y, 0.0f);//二つ目の頂点の場所指定（右回り）
	pVtx[2].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）
	pVtx[3].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//ポーズ背景色設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);//一つ目の頂点の色指定（右回り）
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);//一つ目の頂点の色指定（右回り）
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);//一つ目の頂点の色指定（右回り）
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);//一つ目の頂点の色指定（右回り）

	//ポーズ背景テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//----------マスク-----------
	pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//一つ目の頂点の場所指定
	pVtx[5].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
	pVtx[6].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）
	pVtx[7].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）

	 //rhwの設定
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//ポーズ背景色設定
	pVtx[4].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);//一つ目の頂点の色指定（右回り）
	pVtx[5].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);//一つ目の頂点の色指定（右回り）
	pVtx[6].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);//一つ目の頂点の色指定（右回り）
	pVtx[7].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);//一つ目の頂点の色指定（右回り）

	//ポーズ背景テクスチャの設定
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);


	//頂点バッファのアンロック
	g_pVtxBuffPauseBG->Unlock();
}
//=============================================================================
//ポリゴン終了処理 [UninitPolygon]
//=============================================================================
void UninitPauseBG(void)
{
	//テクスチャの破棄
	if (g_pTexturePauseBG != NULL)
	{
		g_pTexturePauseBG->Release();
		g_pTexturePauseBG = NULL;
	}


	//頂点バッファの破棄
	if (g_pVtxBuffPauseBG != NULL)
	{
		g_pVtxBuffPauseBG->Release();
		g_pVtxBuffPauseBG = NULL;
	}

}

//=============================================================================
// ポリゴン更新処理[UpdataPolygon]
//=============================================================================
void UpdatePauseBG(void)
{

}
//=============================================================================
// ポリゴン描写処理[DrawPolygon]
//=============================================================================
void DrawPauseBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCnt;

	//デバイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (nCnt = 0; nCnt < 2; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePauseBG);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt*4,
			2);
	}
}