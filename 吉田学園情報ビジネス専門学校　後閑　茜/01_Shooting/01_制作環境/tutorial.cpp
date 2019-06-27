//=============================================================================
//
// 背景処理 [tutorial.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "main.h"
#include "tutorial.h"
#include "fade.h"
#include "input.h"
#include "sound.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTutorial = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;
int g_nCntTutorial = 0;

//=============================================================================
// ポリゴン初期化処理[InitPolygon]
//=============================================================================
void InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTUER1, &g_pTextureTutorial);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 , 
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D, 
								D3DPOOL_MANAGED,
								&g_pVtxBuffTutorial, NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx,0);

		//背景の座標設定
		pVtx[0].pos = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y, 0.0f);//一つ目の頂点の場所指定
		pVtx[1].pos = D3DXVECTOR3(TUTORIAL_WIDTH, TUTORIAL_POS_Y, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[2].pos = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[3].pos = D3DXVECTOR3(TUTORIAL_WIDTH, TUTORIAL_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）

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
	g_pVtxBuffTutorial->Unlock();

}
//=============================================================================
//ポリゴン終了処理 [UninitPolygon]
//=============================================================================
void UninitTutorial(void)
{
	//テクスチャの破棄
	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();
		g_pTextureTutorial = NULL;
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

	//Enterキーが押された
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		PlaySound(SOUND_LABEL_SE_DECIDE);

		if (g_fade != FADE_OUT)
		{
			//モード設定
			SetFade(MODE_GAME);
		}
	}


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
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTutorial);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			2);
}