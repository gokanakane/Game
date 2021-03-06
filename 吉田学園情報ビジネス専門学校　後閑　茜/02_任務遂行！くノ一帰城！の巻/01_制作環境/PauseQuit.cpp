//=============================================================================
//
// 背景処理 [PauseQuit.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "main.h"
#include "PauseQuit.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePauseQuit = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseQuit = NULL;
QUITSTATE g_QuitState;

//=============================================================================
// ポリゴン初期化処理[InitPolygon]
//=============================================================================
void InitPauseQuit(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	g_QuitState = QUITSTATE_NOSELECT;


	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTUER, &g_pTexturePauseQuit);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, 
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D, 
								D3DPOOL_MANAGED,
								&g_pVtxBuffPauseQuit, NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffPauseQuit->Lock(0, 0, (void**)&pVtx,0);

		//背景の座標設定
	pVtx[0].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_POS_Y + 240.0f, 0.0f);//一つ目の頂点の場所指定
	pVtx[1].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_POS_Y + 240.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
	pVtx[2].pos = D3DXVECTOR3(280 + 150, 400 + 240.0f - 80, 0.0f);//三つ目の頂点の場所指定（右回り）
	pVtx[3].pos = D3DXVECTOR3(640 + 150, 400 + 240.0f - 80, 0.0f);//三つ目の頂点の場所指定（右回り）

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
	g_pVtxBuffPauseQuit->Unlock();

}
//=============================================================================
//ポリゴン終了処理 [UninitPolygon]
//=============================================================================
void UninitPauseQuit(void)
{

	//テクスチャの破棄
	if (g_pTexturePauseQuit != NULL)
	{
		g_pTexturePauseQuit->Release();
		g_pTexturePauseQuit = NULL;
	}



	//頂点バッファの破棄
	if (g_pVtxBuffPauseQuit != NULL)
	{
		g_pVtxBuffPauseQuit->Release();
		g_pVtxBuffPauseQuit = NULL;
	}

}

//=============================================================================
// ポリゴン更新処理[UpdataPolygon]
//=============================================================================
void UpdatePauseQuit(void)
{
	VERTEX_2D*pVtx;//頂点情報へのポインタ

   //頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffPauseQuit->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_QuitState)
	{
	case QUITSTATE_SELECT:
		//背景色設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		break;

	case QUITSTATE_NOSELECT:
		//背景色設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//一つ目の頂点の色指定（右回り）
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//一つ目の頂点の色指定（右回り）
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//一つ目の頂点の色指定（右回り）
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//一つ目の頂点の色指定（右回り）
		break;


	}
	//頂点バッファのアンロック
	g_pVtxBuffPauseQuit->Unlock();


}
//=============================================================================
// ポリゴン描写処理[DrawPolygon]
//=============================================================================
void DrawPauseQuit(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseQuit, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePauseQuit);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}
//=============================================================================
// QUIT設定処理[DrawPolygon]
//=============================================================================
void SetQuit(QUITSTATE state)
{
	g_QuitState = state;
}
