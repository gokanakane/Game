//=============================================================================
//
// タイトル背景処理 [TitleBG.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "main.h"
#include "TitleBG.h"
#include"input.h"
#include "fade.h"
#include"sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TITLEBG_TEXTUER "data\\TEXTURE\\TitleBG00.png" //読み込むテクスチャ
#define TITLEBG_TEXTUER1 "data\\TEXTURE\\TitlePC.png" //読み込むテクスチャ

#define TITLEBG_POS_X (0)					   //タイトル左上X
#define TITLEBG_POS_Y (0)					   //タイトル左上Y
#define TITLEBG_WIDTH (SCREEN_WIDTH)			   //タイトルの幅
#define TITLEBG_HEIGHT (SCREEN_HEIGHT)		   //タイトル高さ
#define MAX_TEX (2)
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTitleBG[MAX_TEX] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleBG = NULL;
BGAnim g_BGAnim;
int g_nCntTitleBG;

//=============================================================================
// タイトル初期化処理[InitTitle]
//=============================================================================
void InitTitleBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, TITLEBG_TEXTUER,&g_pTextureTitleBG[0]);
	D3DXCreateTextureFromFile(pDevice, TITLEBG_TEXTUER1, &g_pTextureTitleBG[1]);

	g_BGAnim.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_BGAnim.nCntAnim = 0;
	g_BGAnim.PatternAnim = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffTitleBG, NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffTitleBG->Lock(0, 0, (void**)&pVtx,0);

		//タイトル背景の座標設定
		pVtx[0].pos = D3DXVECTOR3(TITLEBG_POS_X, TITLEBG_POS_Y, 0.0f);//一つ目の頂点の場所指定
		pVtx[1].pos = D3DXVECTOR3(TITLEBG_WIDTH, TITLEBG_POS_Y, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[2].pos = D3DXVECTOR3(TITLEBG_POS_X, TITLEBG_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[3].pos = D3DXVECTOR3(TITLEBG_WIDTH, TITLEBG_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//タイトル背景色設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//一つ目の頂点の色指定（右回り）
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);//二つ目の頂点の色指定（右回り）
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);//三つ目の頂点の色指定（右回り）
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);//三つ目の頂点の色指定（右回り）

		//タイトル背景テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//タイトル背景の座標設定
		pVtx[4].pos = D3DXVECTOR3(500, 220, 0.0f);//一つ目の頂点の場所指定
		pVtx[5].pos = D3DXVECTOR3(700, 220, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[6].pos = D3DXVECTOR3(500, 420, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[7].pos = D3DXVECTOR3(700, 420, 0.0f);//三つ目の頂点の場所指定（右回り）

		 //rhwの設定
		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;

		//タイトル背景色設定
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);//一つ目の頂点の色指定（右回り）
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);//二つ目の頂点の色指定（右回り）
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);//三つ目の頂点の色指定（右回り）
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);//三つ目の頂点の色指定（右回り）

		//タイトル背景テクスチャの設定
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(0.25f, 1.0f);

	//頂点バッファのアンロック
	g_pVtxBuffTitleBG->Unlock();

}
//=============================================================================
//タイトル終了処理 [UninitTitle]
//=============================================================================
void UninitTitleBG(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureTitleBG[nCnt] != NULL)
		{
			g_pTextureTitleBG[nCnt]->Release();
			g_pTextureTitleBG[nCnt] = NULL;
		}

	}

	//頂点バッファの破棄
	if (g_pVtxBuffTitleBG != NULL)
	{
		g_pVtxBuffTitleBG->Release();
		g_pVtxBuffTitleBG = NULL;
	}

}

//=============================================================================
// タイトル更新処理[UpdataTitle]
//=============================================================================
void UpdateTitleBG(void)
{
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	g_nCntTitleBG++;
	g_BGAnim.nCntAnim++;

	if ((g_BGAnim.nCntAnim % 5) == 0)//一定時間が経過
	{
		//パターンを更新
		g_BGAnim.PatternAnim++;
	}

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffTitleBG->Lock(0, 0, (void**)&pVtx, 0);

	//背景スクロール
	pVtx[0].tex = D3DXVECTOR2(0.0f + (g_nCntTitleBG*(0.008f + 1)), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f + (g_nCntTitleBG*(0.008f + 1)), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (g_nCntTitleBG*(0.008f + 1)), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + (g_nCntTitleBG*(0.008f + 1)), 1.0f);

	//走るキャラクター
	pVtx[4].tex = D3DXVECTOR2(g_BGAnim.PatternAnim*0.25f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(g_BGAnim.PatternAnim*0.25f + 0.25f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(g_BGAnim.PatternAnim*0.25f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(g_BGAnim.PatternAnim*0.25f + 0.25f, 1.0f);

	//頂点バッファのアンロック
	g_pVtxBuffTitleBG->Unlock();

}
//=============================================================================
// タイトル描写処理[DrawTitle]
//=============================================================================
void DrawTitleBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitleBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitleBG[nCnt]);

		//タイトルの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt*4,
			2);
	}

}