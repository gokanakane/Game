//=============================================================================
//
// 背景処理 [.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "tutorial.h"
#include "fade.h"
#include "input.h"
#include "Tutorial.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BG_POS_X (0)					   //背景左上X
#define BG_POS_Y (0)					   //背景左上Y
#define TUTOTIAL_TEXTUER0 " "
#define TUTOTIAL_TEXTUER "data\\TEXTURE\\Tutorial\\Tutorial204.png"
#define TUTOTIAL_TEXTUER1 "data\\TEXTURE\\Tutorial\\Tutorial001.png"
#define TUTOTIAL_TEXTUER2 "data\\TEXTURE\\Tutorial\\Tutorial002-5.png"
#define MAX_TEX  (4)					   //テクスチャの枚数
#define MAX_ANIM (4)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTutorial[MAX_TEX] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;

int g_nCntAnimT;									//アニメーションカウンター
int g_nPatturnAnimT;								//アニメーションパターン
bool g_bAnimT;										//アニメーションの使用状況7
int g_MoveTex;
//=============================================================================
// ポリゴン初期化処理[InitPolygon]
//=============================================================================
void InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	g_nCntAnimT = 0;
	g_nPatturnAnimT = 0;
	g_bAnimT = false;
	g_MoveTex = 0;

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, TUTOTIAL_TEXTUER0, &g_pTextureTutorial[0]);
	D3DXCreateTextureFromFile(pDevice, TUTOTIAL_TEXTUER, &g_pTextureTutorial[1]);
	D3DXCreateTextureFromFile(pDevice, TUTOTIAL_TEXTUER1, &g_pTextureTutorial[2]);
	D3DXCreateTextureFromFile(pDevice, TUTOTIAL_TEXTUER2, &g_pTextureTutorial[3]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);//一つ目の頂点の場所指定
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, BG_POS_Y, 0.0f);//二つ目の頂点の場所指定（右回り）
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, SCREEN_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）

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

	//背景------------------------------------------------------------
	//背景の座標設定
	pVtx[4].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);//一つ目の頂点の場所指定
	pVtx[5].pos = D3DXVECTOR3(SCREEN_WIDTH, BG_POS_Y, 0.0f);//二つ目の頂点の場所指定（右回り）
	pVtx[6].pos = D3DXVECTOR3(BG_POS_X, 400.0f, 0.0f);//三つ目の頂点の場所指定（右回り）
	pVtx[7].pos = D3DXVECTOR3(SCREEN_WIDTH, 400.0f, 0.0f);//三つ目の頂点の場所指定（右回り）

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
	pVtx[5].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(0.25f, 1.0f);

	//猫------------------------------------------------------------
	//背景の座標設定
	pVtx[8].pos = D3DXVECTOR3(900, 400, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(SCREEN_WIDTH, 400, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(900, SCREEN_HEIGHT, 0.0f);
	pVtx[11].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[8].rhw = 1.0f;
	pVtx[9].rhw = 1.0f;
	pVtx[10].rhw = 1.0f;
	pVtx[11].rhw = 1.0f;

	//背景色設定
	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//背景テクスチャの設定
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(0.25f, 1.0f);

	//吹き出し------------------------------------------------------------
	//背景の座標設定
	pVtx[12].pos = D3DXVECTOR3(100.0f, 400, 0.0f);
	pVtx[13].pos = D3DXVECTOR3(900, 400, 0.0f);
	pVtx[14].pos = D3DXVECTOR3(100.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[15].pos = D3DXVECTOR3(900, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[12].rhw = 1.0f;
	pVtx[13].rhw = 1.0f;
	pVtx[14].rhw = 1.0f;
	pVtx[15].rhw = 1.0f;

	//背景色設定
	pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//背景テクスチャの設定
	pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[15].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	g_pVtxBuffTutorial->Unlock();

}
//=============================================================================
//ポリゴン終了処理 [UninitPolygon]
//=============================================================================
void UninitTutorial(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (g_pTextureTutorial[nCnt] != NULL)
		{
			g_pTextureTutorial[nCnt]->Release();
			g_pTextureTutorial[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

}
//=============================================================================
// ポリゴン更新処理[UpdataPolygon]
//=============================================================================
void UpdateTutorial(void)
{
	FADE g_fade;
	g_fade = GetFade();
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	//Enterキーが押された
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (g_fade != FADE_OUT)
		{
			PlaySound(SOUND_LABEL_SE_DECIDE);
			SetFade(MODE_GAME);
		}
	}

	if (GetKeyboardTrigger(DIK_D) == true)
	{
		g_MoveTex += 1;
		PlaySound(SOUND_LABEL_SE_SELECT);

	}
	if (GetKeyboardTrigger(DIK_A) == true)
	{
		g_MoveTex -= 1;
		PlaySound(SOUND_LABEL_SE_SELECT);

	}

	g_nCntAnimT++;

	if (rand() % 50 == 0)
	{
		g_bAnimT = true;
	}
	if (g_bAnimT == true)
	{
		if (g_nCntAnimT % 4 == 0)
		{
			g_nPatturnAnimT++;
		}

		if (g_nPatturnAnimT >= MAX_ANIM)
		{
			g_nPatturnAnimT = 0;
			g_bAnimT = false;
		}
	}

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	//猫テクスチャ座標の設定
	pVtx[4].tex = D3DXVECTOR2(0.0f + (g_MoveTex*0.25f + 1), 0.0f);
	pVtx[5].tex = D3DXVECTOR2(0.25f + (g_MoveTex*0.25f + 1), 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f + (g_MoveTex*0.25f + 1), 1.0f);
	pVtx[7].tex = D3DXVECTOR2(0.25f + (g_MoveTex*0.25f + 1), 1.0f);

	pVtx[8].tex = D3DXVECTOR2(g_nPatturnAnimT*0.25f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(g_nPatturnAnimT*0.25f + 0.25f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(g_nPatturnAnimT*0.25f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(g_nPatturnAnimT*0.25f + 0.25f, 1.0f);

	//頂点バッファのアンロック
	g_pVtxBuffTutorial->Unlock();


}
//=============================================================================
// ポリゴン描写処理[DrawPolygon]
//=============================================================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;


	//デバイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTutorial[nCnt]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt*4,
			2);
	}

}