//=============================================================================
//
// セレクト画面Yes処理 [Select_Yes.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "Title_Select.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "Font.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTitleSelect[MAX_TEX] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleSelect = NULL;
Colstate g_ColState;
int g_nSelectManuT;

//=============================================================================
// 初期化処理[InitPolygon]
//=============================================================================
void InitTitleSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	g_ColState = COLSTATE_GAMESTATE;
	g_nSelectManuT = 0;

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, TITLESELECT_TEXTUER, &g_pTitleSelect[0]);
	D3DXCreateTextureFromFile(pDevice, TITLESELECT_TEXTUER1, &g_pTitleSelect[1]);
	//D3DXCreateTextureFromFile(pDevice, TITLESELECT_TEXTUER2, &g_pTitleSelect[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitleSelect, NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffTitleSelect->Lock(0, 0, (void**)&pVtx, 0);

	//選択肢-------------------------------------------
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//座標設定
		pVtx[0].pos = D3DXVECTOR3(TITLESELECT_POS_X, TITLESELECT_POS_Y + (nCnt * 200.0f), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(TITLESELECT_WIDTH, TITLESELECT_POS_Y + (nCnt * 200.0f), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(TITLESELECT_POS_X, TITLESELECT_HEIGHT + (nCnt * 200.0f), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(TITLESELECT_WIDTH, TITLESELECT_HEIGHT + (nCnt * 200.0f), 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//背景色設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

		//背景テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
		
	}

	////カーソル-------------------------------------------
	////座標設定
	//pVtx[8].pos = D3DXVECTOR3(100, 500, 0.0f);
	//pVtx[9].pos = D3DXVECTOR3(300, 500, 0.0f);
	//pVtx[10].pos = D3DXVECTOR3(100, 600, 0.0f);
	//pVtx[11].pos = D3DXVECTOR3(300, 600, 0.0f);

	////rhwの設定
	//pVtx[8].rhw = 1.0f;
	//pVtx[9].rhw = 1.0f;
	//pVtx[10].rhw = 1.0f;
	//pVtx[11].rhw = 1.0f;

	////背景色設定
	//pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	////背景テクスチャの設定
	//pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);


	//頂点バッファのアンロック
	g_pVtxBuffTitleSelect->Unlock();

}
//=============================================================================
//終了処理 [UninitPolygon]
//=============================================================================
void UninitTitleSelect(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)

	{//テクスチャの破棄
		if (g_pTitleSelect[nCnt] != NULL)
		{
			g_pTitleSelect[nCnt]->Release();
			g_pTitleSelect[nCnt] = NULL;
		}
	}


	//頂点バッファの破棄
	if (g_pVtxBuffTitleSelect != NULL)
	{
		g_pVtxBuffTitleSelect->Release();
		g_pVtxBuffTitleSelect = NULL;
	}

}

//=============================================================================
// 更新処理[UpdataPolygon]
//=============================================================================
void UpdateTitleSelect(void)
{
	VERTEX_2D*pVtx;//頂点情報へのポインタ
	FADE g_Fade = GetFade();

	//セレクト
	if (GetKeyboardTrigger(DIK_DOWN) == true)
	{
		PlaySound(SOUND_LABEL_SE_SELECT);
		g_nSelectManuT = (g_nSelectManuT + 1) % 2;
	}
	
	if (GetKeyboardTrigger(DIK_UP) == true)
	{
		PlaySound(SOUND_LABEL_SE_SELECT);
		g_nSelectManuT = (g_nSelectManuT + 1) % 2;
	}

	if (g_nSelectManuT == 0)
	{//潜入開始
		g_ColState = COLSTATE_GAMESTATE;
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (g_Fade != FADE_OUT)
			{
				PlaySound(SOUND_LABEL_SE_DECIDE);
				SetFade(MODE_GAME);
			}
		}
	}

	if (g_nSelectManuT == 1)
	{//チュートリアル
		g_ColState = COLSTATE_TUTORIAL;
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (g_Fade != FADE_OUT)
			{
				PlaySound(SOUND_LABEL_SE_DECIDE);
				SetFade(MODE_TUTORIAL);
			}
		}
	}


	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffTitleSelect->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_ColState)
	{
	case COLSTATE_GAMESTATE:
		//背景色設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）

		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//一つ目の頂点の色指定（右回り）
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//一つ目の頂点の色指定（右回り）
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//一つ目の頂点の色指定（右回り）
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//一つ目の頂点の色指定（右回り）
		
		break;

	case COLSTATE_TUTORIAL:
		//背景色設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//一つ目の頂点の色指定（右回り）
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//一つ目の頂点の色指定（右回り）
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//一つ目の頂点の色指定（右回り）
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//一つ目の頂点の色指定（右回り）

		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）

		break;
	}
	//頂点バッファのアンロック
	g_pVtxBuffTitleSelect->Unlock();


}
//=============================================================================
// 描写処理[DrawPolygon]
//=============================================================================
void DrawTitleSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitleSelect, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTitleSelect[nCnt]);

		//の描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt*4,
			2);
	}
}
