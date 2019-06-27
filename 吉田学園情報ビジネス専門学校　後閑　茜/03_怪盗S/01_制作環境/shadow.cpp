//=============================================================================
//
// 影処理 [Shadow.cpp]
// Author : 後閑茜
//
//=============================================================================
#include "shadow.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;//テクスチャへのポインタ
Shadow g_Shadow[MAX_SHADOW];			   //影の情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	for (int nCnt1 = 0; nCnt1 < MAX_SHADOW; nCnt1++)
	{
		g_Shadow[nCnt1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCnt1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCnt1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_Shadow[nCnt1].bUse = false;

	}

	MakeVertexShadow(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitShadow(void)
{
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateShadow(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	//減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP,
							D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND,
							D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,
							D3DBLEND_ONE);
	//zテスト
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Shadow[nCnt].g_mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Shadow[nCnt].rot.y, g_Shadow[nCnt].rot.x, g_Shadow[nCnt].rot.z);
			D3DXMatrixMultiply(&g_Shadow[nCnt].g_mtxWorld, &g_Shadow[nCnt].g_mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Shadow[nCnt].pos.x, g_Shadow[nCnt].pos.y, g_Shadow[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Shadow[nCnt].g_mtxWorld, &g_Shadow[nCnt].g_mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Shadow[nCnt].g_mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0,
				sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureShadow);

		if (g_Shadow[nCnt].bUse == true)
		{
			// 影の描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCnt * 4,
				2);
		}
	}

	//設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP,
							D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND,
							D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,
							D3DBLEND_INVSRCALPHA);
	//zテスト
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;//頂点情報へのポインタ

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice, SHADOW_TEXTUER, &g_pTextureShadow);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	// 頂点情報の設定
	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		//頂点座標を設定
		pVtx[0].pos = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
		pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0f, 0.0f, -10.0f);

		//法線の設定（中の数字を全部足して1.0になる）
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーを設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		//テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点データのポインタを４つずらす
		pVtx += 4;
	}

	//頂点バッファのアンロック
	g_pVtxBuffShadow->Unlock();

}
//=============================================================================
// 影の設定処理
//=============================================================================
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntShadow;

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == false)
		{
			g_Shadow[nCntShadow].pos = D3DXVECTOR3(pos.x, 0.0f, pos.z);
			g_Shadow[nCntShadow].rot = rot;
			g_Shadow[nCntShadow].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			g_Shadow[nCntShadow].bUse = true;

			break;
		}

	}
	return nCntShadow;
}

//=============================================================================
// 影の位置の設定処理
//=============================================================================
void SetPositionShadow(int IdxShadow, D3DXVECTOR3 pos)
{
	if (g_Shadow[IdxShadow].bUse == true)
	{
		g_Shadow[IdxShadow].pos = D3DXVECTOR3(pos.x, 0.0f, pos.z);

	}
}
//=============================================================================
// 影の消去処理
//=============================================================================
void DeleteShadow(int nIdxShadow)
{
	g_Shadow[nIdxShadow].bUse = false;
}
