//=============================================================================
//
// 背景処理 [bg.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "main.h"
#include "Player.h"
#include "Tutorialbg.h"
#include "Item.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTutorialBG[MAX_TUTORIALBGTEX] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorialBG = NULL;
int g_nCntTutorialBG = 0;
TutorialCol g_Col;
TutorialCol g_Col2;
TutorialCol g_Col3;

int nTimeTutlial;

D3DXCOLOR FadeOut;
D3DXCOLOR FadeIN;
TutorialState state;
//=============================================================================
// ポリゴン初期化処理[InitPolygon]
//=============================================================================
void InitTutorialBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	nTimeTutlial = 0;
	state = TUTORIALSTATE_NONE;
	FadeOut = D3DXCOLOR(1.0f, 1.0f,1.0f,0.0f);
	FadeIN = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);;

	g_Col.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Col.nChangeArpha = -0.01f;

	g_Col2.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	g_Col2.nChangeArpha = 0.01f;

	g_Col3.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	g_Col3.nChangeArpha = 0.01f;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, BG_TUTOTIALTEXTUER, &g_pTextureTutorialBG[0]);
	D3DXCreateTextureFromFile(pDevice, BG_TUTOTIALTEXTUER1, &g_pTextureTutorialBG[1]);
	D3DXCreateTextureFromFile(pDevice, BG_TUTOTIALTEXTUER2, &g_pTextureTutorialBG[2]);
	D3DXCreateTextureFromFile(pDevice, BG_TUTOTIALTEXTUER3, &g_pTextureTutorialBG[3]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TUTORIALBGTEX, 
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D, 
								D3DPOOL_MANAGED,
								&g_pVtxBuffTutorialBG, NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffTutorialBG->Lock(0, 0, (void**)&pVtx,0);

		//背景の座標設定
		pVtx[0].pos = D3DXVECTOR3(BG_POS_X, -20, 0.0f);//一つ目の頂点の場所指定
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, -20, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[2].pos = D3DXVECTOR3(BG_POS_X, 300, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 300, 0.0f);//三つ目の頂点の場所指定（右回り）

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

		//操作説明1---------------------------------
		//背景の座標設定
		pVtx[4].pos = D3DXVECTOR3(300, 15, 0.0f);//一つ目の頂点の場所指定
		pVtx[5].pos = D3DXVECTOR3(1000, 15, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[6].pos = D3DXVECTOR3(300, 200, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[7].pos = D3DXVECTOR3(1000, 200, 0.0f);//三つ目の頂点の場所指定（右回り）

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

		//操作説明2-------------------------------
		//背景の座標設定
		pVtx[8].pos = D3DXVECTOR3(300, 40, 0.0f);//一つ目の頂点の場所指定
		pVtx[9].pos = D3DXVECTOR3(1000, 40, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[10].pos = D3DXVECTOR3(300, 190, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[11].pos = D3DXVECTOR3(1000, 190, 0.0f);//三つ目の頂点の場所指定（右回り）

		 //rhwの設定
		pVtx[8].rhw = 1.0f;
		pVtx[9].rhw = 1.0f;
		pVtx[10].rhw = 1.0f;
		pVtx[11].rhw = 1.0f;

		//背景色設定
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);//一つ目の頂点の色指定（右回り）
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);//一つ目の頂点の色指定（右回り）
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);//一つ目の頂点の色指定（右回り）
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);//一つ目の頂点の色指定（右回り）

		//背景テクスチャの設定
		pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);

		//操作説明2-------------------------------
		//背景の座標設定
		pVtx[12].pos = D3DXVECTOR3(900, 300, 0.0f);//一つ目の頂点の場所指定
		pVtx[13].pos = D3DXVECTOR3(SCREEN_WIDTH, 300, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[14].pos = D3DXVECTOR3(900, 400, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[15].pos = D3DXVECTOR3(SCREEN_WIDTH, 400, 0.0f);//三つ目の頂点の場所指定（右回り）

													//rhwの設定
		pVtx[12].rhw = 1.0f;
		pVtx[13].rhw = 1.0f;
		pVtx[14].rhw = 1.0f;
		pVtx[15].rhw = 1.0f;

		//背景色設定
		pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）

														 //背景テクスチャの設定
		pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[15].tex = D3DXVECTOR2(1.0f, 1.0f);


	//頂点バッファのアンロック
	g_pVtxBuffTutorialBG->Unlock();

}
//=============================================================================
//ポリゴン終了処理 [UninitPolygon]
//=============================================================================
void UninitTutorialBG(void)
{
	for (int nCnt = 0; nCnt < MAX_TUTORIALBGTEX; nCnt++)
	{//テクスチャの破棄
		if (g_pTextureTutorialBG[nCnt] != NULL)
		{
			g_pTextureTutorialBG[nCnt]->Release();
			g_pTextureTutorialBG[nCnt] = NULL;
		}

	}

	//頂点バッファの破棄
	if (g_pVtxBuffTutorialBG != NULL)
	{
		g_pVtxBuffTutorialBG->Release();
		g_pVtxBuffTutorialBG = NULL;
	}

}

//=============================================================================
// ポリゴン更新処理[UpdataPolygon]
//=============================================================================
void UpdateTutorialBG(void)
{
	VERTEX_2D*pVtx;//頂点情報へのポインタ
	nTimeTutlial++;
	
	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffTutorialBG->Lock(0, 0, (void**)&pVtx, 0);

	g_Col3.col.a += g_Col3.nChangeArpha;

	if (g_Col3.col.a <= 0.0f || g_Col3.col.a >= 1.0f)
	{
		g_Col3.nChangeArpha *= -1.0f;
	}

	if (nTimeTutlial > 180)
	{
		g_Col.col.a += g_Col.nChangeArpha;
		g_Col2.col.a += g_Col2.nChangeArpha;

		if (g_Col.col.a <= 0.0f || g_Col.col.a >= 1.0f)
		{
			if (g_Col2.col.a <= 0.0f || g_Col2.col.a >= 1.0f)
			{
				g_Col.nChangeArpha *= -1.0f;
				g_Col2.nChangeArpha *= -1.0f;

				nTimeTutlial = 0;
			}
		}
	}

	//背景色設定
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Col.col.a);//一つ目の頂点の色指定（右回り）
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Col.col.a);//一つ目の頂点の色指定（右回り）
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Col.col.a);//一つ目の頂点の色指定（右回り）
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Col.col.a);//一つ目の頂点の色指定（右回り）

	//背景色設定
	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Col2.col.a);//一つ目の頂点の色指定（右回り）
	pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Col2.col.a);//一つ目の頂点の色指定（右回り）
	pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Col2.col.a);//一つ目の頂点の色指定（右回り）
	pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Col2.col.a);//一つ目の頂点の色指定（右回り）

															 //背景色設定
	pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Col3.col.a);//一つ目の頂点の色指定（右回り）
	pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Col3.col.a);//一つ目の頂点の色指定（右回り）
	pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Col3.col.a);//一つ目の頂点の色指定（右回り）
	pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Col3.col.a);//一つ目の頂点の色指定（右回り）


	//頂点バッファのアンロック
	g_pVtxBuffTutorialBG->Unlock();


}
//=============================================================================
// ポリゴン描写処理[DrawPolygon]
//=============================================================================
void DrawTutorialBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorialBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TUTORIALBGTEX; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTutorialBG[nCnt]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt*4,
			2);
	}
}