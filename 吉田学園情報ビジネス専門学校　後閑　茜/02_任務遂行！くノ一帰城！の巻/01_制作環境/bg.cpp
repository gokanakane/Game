//=============================================================================
//
// 背景処理 [bg.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "main.h"
#include "Player.h"
#include "bg.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureBG[MAX_TEX] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;
int g_nCntBG = 0;

//=============================================================================
// ポリゴン初期化処理[InitPolygon]
//=============================================================================
void InitBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, BG_TEXTUER, &g_pTextureBG[0]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTUER1, &g_pTextureBG[1]);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX, 
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D, 
								D3DPOOL_MANAGED,
								&g_pVtxBuffBG, NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx,0);

		//背景の座標設定
		pVtx[0].pos = D3DXVECTOR3(BG_POS_X, 0.0f, 0.0f);//一つ目の頂点の場所指定
		pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, 0.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_WIDTH, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_WIDTH, 0.0f);//三つ目の頂点の場所指定（右回り）

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

		//-----------------雲
		//背景の座標設定
		pVtx[4].pos = D3DXVECTOR3(0, 100, 0.0f);//一つ目の頂点の場所指定
		pVtx[5].pos = D3DXVECTOR3(BG_WIDTH, 100, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[6].pos = D3DXVECTOR3(0, 400, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[7].pos = D3DXVECTOR3(BG_WIDTH, 400, 0.0f);//三つ目の頂点の場所指定（右回り）

	 //rhwの設定
		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;

		//背景色設定
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）

		//背景テクスチャの設定
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

		//-----------------城壁
		////背景の座標設定
		//pVtx[8].pos = D3DXVECTOR3(0, 500, 0.0f);//一つ目の頂点の場所指定
		//pVtx[9].pos = D3DXVECTOR3(BG_WIDTH, 500, 0.0f);//二つ目の頂点の場所指定（右回り）
		//pVtx[10].pos = D3DXVECTOR3(0, BG_WIDTH, 0.0f);//三つ目の頂点の場所指定（右回り）
		//pVtx[11].pos = D3DXVECTOR3(BG_WIDTH, BG_WIDTH, 0.0f);//三つ目の頂点の場所指定（右回り）

		//											   //rhwの設定
		//pVtx[8].rhw = 1.0f;
		//pVtx[9].rhw = 1.0f;
		//pVtx[10].rhw = 1.0f;
		//pVtx[11].rhw = 1.0f;

		////背景色設定
		//pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		//pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		//pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		//pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）

		////背景テクスチャの設定
		//pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);


	//頂点バッファのアンロック
	g_pVtxBuffBG->Unlock();

}
//=============================================================================
//ポリゴン終了処理 [UninitPolygon]
//=============================================================================
void UninitBG(void)
{
	int nCnt;
	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureBG[nCnt] != NULL)
		{
			g_pTextureBG[nCnt]->Release();
			g_pTextureBG[nCnt] = NULL;
		}

	}

	//頂点バッファの破棄
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}

}

//=============================================================================
// ポリゴン更新処理[UpdataPolygon]
//=============================================================================
void UpdateBG(void)
{
	VERTEX_2D*pVtx;//頂点情報へのポインタ
	g_nCntBG++;

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//背景の座標設定
	pVtx[4].tex = D3DXVECTOR2(0.0f + (g_nCntBG*(0.001f + 1)), 0.0f);//一つ目の頂点の場所指定
	pVtx[5].tex = D3DXVECTOR2(1.0f + (g_nCntBG*(0.001f + 1)), 0.0f);//二つ目の頂点の場所指定（右回り）
	pVtx[6].tex = D3DXVECTOR2(0.0f + (g_nCntBG*(0.001f + 1)), 1.0f);//三つ目の頂点の場所指定（右回り）
	pVtx[7].tex = D3DXVECTOR2(1.0f + (g_nCntBG*(0.001f + 1)), 1.0f);//三つ目の頂点の場所指定（右回り）

	//頂点バッファのアンロック
	g_pVtxBuffBG->Unlock();

}
//=============================================================================
// ポリゴン描写処理[DrawPolygon]
//=============================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCnt;

	//デバイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBG[nCnt]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt * 4,
			2);
	}
}