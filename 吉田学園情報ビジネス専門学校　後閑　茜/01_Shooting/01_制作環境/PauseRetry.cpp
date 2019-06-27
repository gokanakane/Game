//=============================================================================
//
// 背景処理 [bg.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "main.h"
#include "PauseRetry.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePauseRetry = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseRetry = NULL;
RETRYSTATE g_RetryState;

//=============================================================================
// ポリゴン初期化処理[InitPolygon]
//=============================================================================
void InitPauseRetry(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTUER, &g_pTexturePauseRetry);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseRetry, NULL);

	g_RetryState = RETRYSTATE_NOSELECT;

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffPauseRetry->Lock(0, 0, (void**)&pVtx, 0);

	//背景の座標設定
	pVtx[0].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_POS_Y + 120.0f, 0.0f);//一つ目の頂点の場所指定
	pVtx[1].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_POS_Y + 120.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
	pVtx[2].pos = D3DXVECTOR3(280 + 150, 400 + 120.0f - 80, 0.0f);//三つ目の頂点の場所指定（右回り）
	pVtx[3].pos = D3DXVECTOR3(640 + 150, 400 + 120.0f - 80, 0.0f);//三つ目の頂点の場所指定（右回り）

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
	g_pVtxBuffPauseRetry->Unlock();

}
//=============================================================================
//ポリゴン終了処理 [UninitPolygon]
//=============================================================================
void UninitPauseRetry(void)
{

	//テクスチャの破棄
	if (g_pTexturePauseRetry != NULL)
	{
		g_pTexturePauseRetry->Release();
		g_pTexturePauseRetry = NULL;
	}



	//頂点バッファの破棄
	if (g_pVtxBuffPauseRetry != NULL)
	{
		g_pVtxBuffPauseRetry->Release();
		g_pVtxBuffPauseRetry = NULL;
	}

}

//=============================================================================
// ポリゴン更新処理[UpdataPolygon]
//=============================================================================
void UpdatePauseRetry(void)
{
	VERTEX_2D*pVtx;//頂点情報へのポインタ
				   //頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffPauseRetry->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_RetryState)
	{
	case RETRYSTATE_SELECT:
		//背景色設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		break;

	case RETRYSTATE_NOSELECT:
		//背景色設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//一つ目の頂点の色指定（右回り）
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//一つ目の頂点の色指定（右回り）
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//一つ目の頂点の色指定（右回り）
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//一つ目の頂点の色指定（右回り）
		break;

	}
	//頂点バッファのアンロック
	g_pVtxBuffPauseRetry->Unlock();


}
//=============================================================================
// ポリゴン描写処理[DrawPolygon]
//=============================================================================
void DrawPauseRetry(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseRetry, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePauseRetry);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			2);
}
//=============================================================================
// QUIT設定処理[DrawPolygon]
//=============================================================================
void SetRetry(RETRYSTATE state)
{
	g_RetryState = state;
}
