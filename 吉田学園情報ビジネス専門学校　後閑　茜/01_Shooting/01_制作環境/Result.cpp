//=============================================================================
//
// リザルト処理 [Result.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "main.h"
#include "Result.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureResult[MAX_RESULTTEX] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;

//=============================================================================
// リザルト初期化処理[InitPolygon]
//=============================================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	GAMESTATE pGame;
	pGame = GetGameState();

	if (pGame == GAMESTATE_CLEAR)
	{//ゲームクリアだったら
		//テクスチャ読み込み
		D3DXCreateTextureFromFile(pDevice, RESULT_TEXTUER, &g_pTextureResult[0]);
		D3DXCreateTextureFromFile(pDevice, RESULT_TEXTUER1, &g_pTextureResult[1]);
		
	}
	else if (pGame == GAMESTATE_OVER)
	{
		//テクスチャ読み込み
		D3DXCreateTextureFromFile(pDevice, RESULT_OVER, &g_pTextureResult[0]);
		D3DXCreateTextureFromFile(pDevice, RESULT_TEXTUER2, &g_pTextureResult[1]);

	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RESULTTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult, NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//リザルト背景の座標設定
	pVtx[0].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);//一つ目の頂点の場所指定
	pVtx[1].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_POS_Y, 0.0f);//二つ目の頂点の場所指定（右回り）
	pVtx[2].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）
	pVtx[3].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）

	 //rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//リザルト背景色設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//一つ目の頂点の色指定（右回り）
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);//二つ目の頂点の色指定（右回り）
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);//三つ目の頂点の色指定（右回り）
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);//三つ目の頂点の色指定（右回り）

	//リザルト背景テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//-----------リザルト文字------------
	//リザルトの座標設定
	pVtx[4].pos = D3DXVECTOR3(90, 90, 0.0f);//一つ目の頂点の場所指定
	pVtx[5].pos = D3DXVECTOR3(1100, 90, 0.0f);//二つ目の頂点の場所指定（右回り）
	pVtx[6].pos = D3DXVECTOR3(90, 500, 0.0f);//三つ目の頂点の場所指定（右回り）
	pVtx[7].pos = D3DXVECTOR3(1100, 500, 0.0f);//三つ目の頂点の場所指定（右回り）

	 //rhwの設定
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//リザルト色設定
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);//一つ目の頂点の色指定（右回り）
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);//二つ目の頂点の色指定（右回り）
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);//三つ目の頂点の色指定（右回り）
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);//三つ目の頂点の色指定（右回り）

	//リザルトテクスチャの設定
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);


	//頂点バッファのアンロック
	g_pVtxBuffResult->Unlock();

}
//=============================================================================
//リザルト終了処理 [UninitPolygon]
//=============================================================================
void UninitResult(void)
{
	int nCnt;
	for (nCnt = 0; nCnt < MAX_RESULTTEX; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureResult[nCnt] != NULL)
		{
			g_pTextureResult[nCnt]->Release();
			g_pTextureResult[nCnt] = NULL;
		}

	}

	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

}

//=============================================================================
// リザルト更新処理[UpdataPolygon]
//=============================================================================
void UpdateResult(void)
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
			SetFade(MODE_TITLE);
		}
	}
}
//=============================================================================
// リザルト描写処理[DrawPolygon]
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCnt;
	//デバイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	for (nCnt = 0; nCnt < MAX_RESULTTEX; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureResult[nCnt]);

		//リザルトの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt*4,
			2);

	}

}