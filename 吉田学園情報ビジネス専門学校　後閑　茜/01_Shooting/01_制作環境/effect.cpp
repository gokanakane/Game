//=============================================================================
//
// エフェクトの処理 [effect.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "effect.h"


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureEffect = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	// 頂点バッファへのポインタ
EFFECT					g_aEffect[MAX_EFFECT];		// エフェクトの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fRadius = 0.0f;
		g_aEffect[nCntEffect].nLife = 0;
		g_aEffect[nCntEffect].bUse = false;
	}
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_EFFECT, &g_pTextureEffect);

	// 頂点情報の作成
	MakeVertexEffect(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect(void)
{	int nCntTex;

	// テクスチャの開放
	for (nCntTex = 0; nCntTex < MAX_EFFECT; nCntTex++)
	{
		//テクスチャの破棄
		if (g_pTextureEffect != NULL)
		{
			g_pTextureEffect->Release();
			g_pTextureEffect = NULL;
		}

	}
		// 頂点バッファの開放
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect(void)
{
	int nCnt;
	
	for (nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_aEffect[nCnt].bUse == true)
		{
			g_aEffect[nCnt].nLife--;

			if (g_aEffect[nCnt].nLife <= 0)
			{
				g_aEffect[nCnt].bUse = false;
			}

		}

	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect(void)
{
	int nCntEffect;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureEffect);

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	//アルファブレンドの設定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);//アルファブレンドの設定


	// ポリゴンの描画
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)//弾が使用されている
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntEffect,
				2);
		}
	}

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//=============================================================================
// 頂点の作成
//=============================================================================
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	int nCnt;
	VERTEX_2D *pVtx;//頂点情報へのポインタ


	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		// 頂点情報を設定	
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//一つ目の頂点の場所指定
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//三つ目の頂点の場所指定（右回り）

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点色
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）


		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0, 1.0f);

		//該当の位置まで進める
		pVtx += 4;
	}

	//頂点バッファのアンロック
	g_pVtxBuffEffect->Unlock();

}


//=============================================================================
// エフェクト設定
//=============================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife)
{
	int nCntEffect;
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{
			//頂点情報を設定
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].col = col;
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f);//一つ目の頂点の色指定（右回り）
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f);//二つ目の頂点の色指定（右回り）
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f);//三つ目の頂点の色指定（右回り）
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f);//三つ目の頂点の色指定（右回り）

			g_aEffect[nCntEffect].nLife = nLife;

			g_aEffect[nCntEffect].fRadius = fRadius;
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - fRadius, g_aEffect[nCntEffect].pos.y - fRadius, 0.0f);//左上の頂点Xの場所指定
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + fRadius, g_aEffect[nCntEffect].pos.y - fRadius, 0.0f);//左上の頂点Xの場所指定
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - fRadius, g_aEffect[nCntEffect].pos.y + fRadius, 0.0f);//左上の頂点Xの場所指定
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + fRadius, g_aEffect[nCntEffect].pos.y + fRadius, 0.0f);//左上の頂点Xの場所指定

			g_aEffect[nCntEffect].bUse = true;
			break;
		}
		pVtx += 4;//該当の位置まで進める
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();

}
