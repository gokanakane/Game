//=============================================================================
//
// タイトル背景処理 [TitleRogo.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "main.h"
#include "TitleRogo.h"
#include"input.h"
#include "fade.h"
#include"sound.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTitleRogo[MAX_TITLEROGOTEX] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleRogo = NULL;
RogoAnim g_Rogo;
RogoState state;
int g_nTimeRogo;

//=============================================================================
// タイトル初期化処理[InitTitle]
//=============================================================================
void InitTitleRogo(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, TITLEROGO_TEXTUER,&g_pTextureTitleRogo[0]);
	D3DXCreateTextureFromFile(pDevice, TITLEROGO_TEXTUER1, &g_pTextureTitleRogo[1]);
	D3DXCreateTextureFromFile(pDevice, TITLEROGO_TEXTUER2, &g_pTextureTitleRogo[2]);
	D3DXCreateTextureFromFile(pDevice, TITLEROGO_TEXTUER3, &g_pTextureTitleRogo[3]);

	g_Rogo.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Rogo.nCntAnim = 0;
	g_Rogo.nPatturnAnim = 0;
	g_Rogo.nChangeArpha = 0.15f;
	g_Rogo.bAnim = false;

	state = ROGO_NONE;

	g_nTimeRogo = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TITLEROGOTEX,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffTitleRogo, NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffTitleRogo->Lock(0, 0, (void**)&pVtx,0);

		//タイトル背景の座標設定
		pVtx[0].pos = D3DXVECTOR3(50, 50, 0.0f);//一つ目の頂点の場所指定
		pVtx[1].pos = D3DXVECTOR3(1200, 50, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[2].pos = D3DXVECTOR3(50, 200, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[3].pos = D3DXVECTOR3(1200, 200, 0.0f);//三つ目の頂点の場所指定（右回り）

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

		//手裏剣----------------------------------------
		pVtx[4].pos = D3DXVECTOR3(750, 100, 0.0f);//一つ目の頂点の場所指定
		pVtx[5].pos = D3DXVECTOR3(850, 100, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[6].pos = D3DXVECTOR3(750, 170, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[7].pos = D3DXVECTOR3(850, 170, 0.0f);//三つ目の頂点の場所指定（右回り）

	  //rhwの設定
		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;

		//タイトル背景色設定
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）

		//タイトル背景テクスチャの設定
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(0.25f, 1.0f);

		//PRESS_ENTER----------------------------------------
		pVtx[8].pos = D3DXVECTOR3(400, 600, 0.0f);//一つ目の頂点の場所指定
		pVtx[9].pos = D3DXVECTOR3(900, 600, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[10].pos = D3DXVECTOR3(400, 700, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[11].pos = D3DXVECTOR3(900, 700, 0.0f);//三つ目の頂点の場所指定（右回り）

		 //rhwの設定
		pVtx[8].rhw = 1.0f;
		pVtx[9].rhw = 1.0f;
		pVtx[10].rhw = 1.0f;
		pVtx[11].rhw = 1.0f;

		//タイトル背景色設定
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）

		//タイトル背景テクスチャの設定
		pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);


		//任務遂行----------------------------------------
		pVtx[12].pos = D3DXVECTOR3(100, 30, 0.0f);//一つ目の頂点の場所指定
		pVtx[13].pos = D3DXVECTOR3(450, 30, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[14].pos = D3DXVECTOR3(100, 130, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[15].pos = D3DXVECTOR3(450, 130, 0.0f);//三つ目の頂点の場所指定（右回り）

												   //rhwの設定
		pVtx[12].rhw = 1.0f;
		pVtx[13].rhw = 1.0f;
		pVtx[14].rhw = 1.0f;
		pVtx[15].rhw = 1.0f;

		//タイトル背景色設定
		pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
		pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
		pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）

														 //タイトル背景テクスチャの設定
		pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[15].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	g_pVtxBuffTitleRogo->Unlock();

}
//=============================================================================
//タイトル終了処理 [UninitTitle]
//=============================================================================
void UninitTitleRogo(void)
{
	for (int nCnt = 0; nCnt < MAX_TITLEROGOTEX; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureTitleRogo[nCnt] != NULL)
		{
			g_pTextureTitleRogo[nCnt]->Release();
			g_pTextureTitleRogo[nCnt] = NULL;
		}

	}

	//頂点バッファの破棄
	if (g_pVtxBuffTitleRogo != NULL)
	{
		g_pVtxBuffTitleRogo->Release();
		g_pVtxBuffTitleRogo = NULL;
	}

}

//=============================================================================
// タイトル更新処理[UpdataTitle]
//=============================================================================
void UpdateTitleRogo(void)
{
	VERTEX_2D*pVtx;//頂点情報へのポインタ
	FADE g_fade;
	g_fade = GetFade();

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffTitleRogo->Lock(0, 0, (void**)&pVtx, 0);

	switch (state)
	{
	case ROGO_NONE:
		break;

	case ROGO_FLASH:

		if (g_Rogo.col.a <= 0.0f)
		{
			g_Rogo.col.a = 1.0f;
			if (g_Rogo.col.a >= 1.0f)
			{
				g_Rogo.col.a = 0.0f;
			}
		}
		g_Rogo.col.a += g_Rogo.nChangeArpha;

		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Rogo.col.a);//一つ目の頂点の色指定（右回り）
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Rogo.col.a );//二つ目の頂点の色指定（右回り）
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Rogo.col.a );//三つ目の頂点の色指定（右回り）
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Rogo.col.a);//三つ目の頂点の色指定（右回り）

		g_nTimeRogo++;

		if (g_nTimeRogo < 30)
		{
			//モード設定
			SetFade(MODE_TUTORIAL);

		}
		break;
	}

	g_Rogo.nCntAnim++;


	if (rand() % 100 == 0)
	{
		g_Rogo.bAnim = true;
	}

	if (g_Rogo.bAnim == true)
	{
		if (g_Rogo.nCntAnim % 4 == 0)
		{
			g_Rogo.nPatturnAnim++;
		}

		//手裏剣テクスチャの設定
		pVtx[4].tex = D3DXVECTOR2(g_Rogo.nPatturnAnim*0.25f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(g_Rogo.nPatturnAnim*0.25f + 0.25f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(g_Rogo.nPatturnAnim*0.25f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(g_Rogo.nPatturnAnim*0.25f + 0.25f, 1.0f);

		if (g_Rogo.nPatturnAnim >= MAX_ANIMATION)
		{
			g_Rogo.nPatturnAnim = 0;
			g_Rogo.bAnim = false;
		}
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

	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Rogo.col.a);//一つ目の頂点の色指定（右回り）
	pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Rogo.col.a);//二つ目の頂点の色指定（右回り）
	pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Rogo.col.a);//三つ目の頂点の色指定（右回り）
	pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Rogo.col.a);//三つ目の頂点の色指定（右回り）

	 //頂点バッファのアンロック
	g_pVtxBuffTitleRogo->Unlock();


}
//=============================================================================
// タイトル描写処理[DrawTitle]
//=============================================================================
void DrawTitleRogo(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitleRogo, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TITLEROGOTEX; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitleRogo[nCnt]);

		//タイトルの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt*4,
			2);
	}

}
//=============================================================================
// 状態の取得
//=============================================================================
RogoState*GetState(void)
{
	return &state;
}