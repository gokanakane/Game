//=============================================================================
//
// 壁処理 [Explosion.cpp]
// Author : 後閑茜
//
//=============================================================================
#include "explosion.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define EXPLOSION_TEXTUER "data\\TEXTURE\\Effect\\explosion000.png"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;//テクスチャへのポインタ
Explosion g_Explosion[MAX_EXPLOSION];					//壁の最大数
//=============================================================================
// 初期化処理
//=============================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	for (int nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		g_Explosion[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Explosion[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Explosion[nCnt].nCntAnim = 0;
		g_Explosion[nCnt].nPatturnAnim = 0;
		g_Explosion[nCnt].bUse = false;

	}

	MakeVertexExplosion(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitExplosion(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateExplosion(void)
{
	VERTEX_3D *pVtx;//頂点情報へのポインタ

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		if (g_Explosion[nCnt].bUse == true)
		{
			g_Explosion[nCnt].nCntAnim++;
			if ((g_Explosion[nCnt].nCntAnim % 3) == 0)//一定時間が経過
			{
				//パターンを更新
				g_Explosion[nCnt].nPatturnAnim++;
			}

			pVtx[0].tex = D3DXVECTOR2((g_Explosion[nCnt].nPatturnAnim*0.125f) + 0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((g_Explosion[nCnt].nPatturnAnim*0.125f) + 0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2((g_Explosion[nCnt].nPatturnAnim*0.125f) + 0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((g_Explosion[nCnt].nPatturnAnim*0.125f) + 0.125f, 1.0f);

			if (g_Explosion[nCnt].nPatturnAnim >= 8)
			{
				g_Explosion[nCnt].bUse = false;
				g_Explosion[nCnt].nPatturnAnim = 0;
			}
		}

		pVtx += 4;

	}
	//頂点バッファのアンロック
	g_pVtxBuffExplosion->Unlock();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawExplosion(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxView;				//計算用マトリックス
	int nCntExplosion;

	//αテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//zテスト
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_Explosion[nCntExplosion].bUse == true)
		{

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Explosion[nCntExplosion].mtxWorld);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			g_Explosion[nCntExplosion].mtxWorld._11 = mtxView._11;
			g_Explosion[nCntExplosion].mtxWorld._12 = mtxView._21;
			g_Explosion[nCntExplosion].mtxWorld._13 = mtxView._31;
			g_Explosion[nCntExplosion].mtxWorld._21 = mtxView._12;
			g_Explosion[nCntExplosion].mtxWorld._22 = mtxView._22;
			g_Explosion[nCntExplosion].mtxWorld._23 = mtxView._32;
			g_Explosion[nCntExplosion].mtxWorld._31 = mtxView._13;
			g_Explosion[nCntExplosion].mtxWorld._32 = mtxView._23;
			g_Explosion[nCntExplosion].mtxWorld._33 = mtxView._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Explosion[nCntExplosion].pos.x, g_Explosion[nCntExplosion].pos.y, g_Explosion[nCntExplosion].pos.z);
			D3DXMatrixMultiply(&g_Explosion[nCntExplosion].mtxWorld, &g_Explosion[nCntExplosion].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Explosion[nCntExplosion].mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0,
				sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureExplosion);

			// 壁の描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntExplosion * 4,
				2);
		}
	}
	//αテストの無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//zテスト
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;//頂点情報へのポインタ

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TEXTUER, &g_pTextureExplosion);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	// 頂点情報の設定
	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		//頂点座標を設定
		pVtx[0].pos = D3DXVECTOR3(-10.0f, 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-10.0f, -10.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0f, -10.0f, 0.0f);

		//法線の設定（中の数字を全部足して1.0(-1.0)になる）
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーを設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファのアンロック
	g_pVtxBuffExplosion->Unlock();

}
//=============================================================================
// 壁の設定処理
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos)
{
	int nCnt;
					
	for (nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		if (g_Explosion[nCnt].bUse == false)
		{
			g_Explosion[nCnt].pos = pos;

			g_Explosion[nCnt].rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
			g_Explosion[nCnt].bUse = true;
			break;
		}
	}
}