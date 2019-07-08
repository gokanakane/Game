//=============================================================================
//
// タイトル処理 [Title.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "Title.h"
#include "camera.h"
#include "light.h"
#include "Stage.h"
#include "fade.h"
#include "sound.h"
#include "input.h"
#include "Title_Select.h"
#include "Obj.h"
#include "Wall.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TEX] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;
RogoAnim g_Rogo;
RogoState state;
int g_nTimeRogo;
int g_nCntTitleTime;			//フェード時間
bool g_bSelect;

//=============================================================================
// タイトル初期化処理[InitTitle]
//=============================================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	g_nCntTitleTime = 0;

	InitCamera();
	InitLight();
	InitStage();
	InitWall();
	InitTitleSelect();
	InitObj();

	//胸像
	SetObj(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);


	g_bSelect = false;

				   //デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, TITLEROGO_TEXTUER, &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, TITLEROGO_TEXTUER1, &g_pTextureTitle[1]);

	g_Rogo.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Rogo.nChangeArpha = 0.05f;
	g_Rogo.bAnim = false;
	state = ROGO_NONE;
	g_nTimeRogo = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle, NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//タイトルロゴ--------------------------------------------------------
	//タイトル背景の座標設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//一つ目の頂点の場所指定
	pVtx[1].pos = D3DXVECTOR3(1200.0f, 0.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
	pVtx[2].pos = D3DXVECTOR3(0.0f, 300.0f, 0.0f);//三つ目の頂点の場所指定（右回り）
	pVtx[3].pos = D3DXVECTOR3(1200.0f, 300.0f, 0.0f);//三つ目の頂点の場所指定（右回り）

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//タイトル背景色設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）

	//タイトル背景テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//PRESS_ENTRE--------------------------------------------------------
	//タイトル背景の座標設定
	pVtx[4].pos = D3DXVECTOR3(300.0f, 600.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(1000.0f, 600.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(300.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(1000.0f, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//タイトル背景色設定
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//タイトル背景テクスチャの設定
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	g_pVtxBuffTitle->Unlock();


}
//=============================================================================
//タイトル終了処理 [UninitTitle]
//=============================================================================
void UninitTitle(void)
{
	UninitCamera();
	UninitLight();
	UninitStage();
	UninitWall();
	UninitTitleSelect();
	UninitObj();

	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureTitle[nCnt] != NULL)
		{
			g_pTextureTitle[nCnt]->Release();
			g_pTextureTitle[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

}

//=============================================================================
// タイトル更新処理[UpdataTitle]
//=============================================================================
void UpdateTitle(void)
{
	FADE g_fade;
	g_fade = GetFade();
	g_nCntTitleTime++;
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	UpdateCamera();
	UpdateLight();
	UpdateStage();
	UpdateWall();
	UpdateObj();

	switch (state)
	{
	case ROGO_NONE:
		if (g_Rogo.col.a <= 0.0f || g_Rogo.col.a >= 1.0f)
		{
			g_Rogo.nChangeArpha *= 1.0f;
		}
		g_Rogo.col.a += g_Rogo.nChangeArpha;

		//時間で切り替え
		if (g_nCntTitleTime > 600)
		{
			if (g_fade != FADE_OUT)
			{
				SetFade(MODE_RANKING);
			}
		}

		break;

	case ROGO_FLASH:
		g_Rogo.col.a = -0.1f;
		g_bSelect = true;
		break;
	}

	if (g_Rogo.col.a <= 0.0f || g_Rogo.col.a >= 1.0f)
	{
		g_Rogo.nChangeArpha *= -1;
	}
	g_Rogo.col.a += g_Rogo.nChangeArpha;

	//Enterキーが押された
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (g_fade != FADE_OUT)
		{
			PlaySound(SOUND_LABEL_SE_DECIDE);
			state = ROGO_FLASH;
		}
	}

	if (g_bSelect == true)
	{
		UpdateTitleSelect();
	}

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//タイトル背景色設定
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Rogo.col.a);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Rogo.col.a);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Rogo.col.a);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Rogo.col.a);

	//頂点バッファのアンロック
	g_pVtxBuffTitle->Unlock();


}
//=============================================================================
// タイトル描写処理[DrawTitle]
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デイスを取得する
	pDevice = GetDevice();

	SetCamera();
	DrawStage();
	DrawWall();
	DrawObj();
	DrawTitleSelect();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[nCnt]);

		//タイトルの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt*4,
			2);
	}

}