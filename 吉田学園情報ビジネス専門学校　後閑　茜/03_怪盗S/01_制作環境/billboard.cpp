//=============================================================================
//
// 壁処理 [Billboard.cpp]
// Author : 後閑茜
//
//=============================================================================
#include "billboard.h"
#include "shadow.h"
#include "Player.h"
#include "Game.h"
#include "score.h"


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard= NULL;
LPDIRECT3DTEXTURE9 g_pTextureBillboard[MAX_TEX] = {};//テクスチャへのポインタ
Billboard g_Billboard[MAX_BILLBOARD];					//壁の最大数
//=============================================================================
// 初期化処理
//=============================================================================
void InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		g_Billboard[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Billboard[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Billboard[nCnt].bUse = false;
		g_Billboard[nCnt].IdxShadow = SetShadow(g_Billboard[g_Billboard[nCnt].IdxShadow].pos, g_Billboard[g_Billboard[nCnt].IdxShadow].rot);
	}


	MakeVertexBillboard(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBillboard(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (g_pTextureBillboard[nCnt] != NULL)
		{
			g_pTextureBillboard[nCnt]->Release();
			g_pTextureBillboard[nCnt] = NULL;
		}
	}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateBillboard(void)
{
	Player*pPlayer;
	pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		if (g_Billboard[nCnt].bUse == true)
		{
			SetPositionShadow(g_Billboard[nCnt].IdxShadow, g_Billboard[nCnt].pos);
			if (g_Billboard[nCnt].pos.x - 10 <= pPlayer->pos.x
				&&g_Billboard[nCnt].pos.x + 10 >= pPlayer->pos.x
				&&g_Billboard[nCnt].pos.z - 10 <= pPlayer->pos.z 
				&&g_Billboard[nCnt].pos.z + 10 >= pPlayer->pos.z)
			{//ビルボードのあたり判定
					g_Billboard[nCnt].bUse = false;
					AddScore(100);
			}

		}
		else
		{
			DeleteShadow(g_Billboard[nCnt].IdxShadow);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxView;				//計算用マトリックス
	int nCntBillboard;
	//ライトの無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//αテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_Billboard[nCntBillboard].bUse == true)
		{

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Billboard[nCntBillboard].mtxWorld);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			g_Billboard[nCntBillboard].mtxWorld._11 = mtxView._11;
			g_Billboard[nCntBillboard].mtxWorld._12 = mtxView._21;
			g_Billboard[nCntBillboard].mtxWorld._13 = mtxView._31;
			g_Billboard[nCntBillboard].mtxWorld._21 = mtxView._12;
			g_Billboard[nCntBillboard].mtxWorld._22 = mtxView._22;
			g_Billboard[nCntBillboard].mtxWorld._23 = mtxView._32;
			g_Billboard[nCntBillboard].mtxWorld._31 = mtxView._13;
			g_Billboard[nCntBillboard].mtxWorld._32 = mtxView._23;
			g_Billboard[nCntBillboard].mtxWorld._33 = mtxView._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Billboard[nCntBillboard].pos.x, g_Billboard[nCntBillboard].pos.y, g_Billboard[nCntBillboard].pos.z);
			D3DXMatrixMultiply(&g_Billboard[nCntBillboard].mtxWorld, &g_Billboard[nCntBillboard].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Billboard[nCntBillboard].mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0,
				sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBillboard[g_Billboard[nCntBillboard].Type]);

			// 壁の描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntBillboard * 4,
				2);
		}
	}
	//αテストの無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//ライトの無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;//頂点情報へのポインタ

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice, KEY_TEXTUER, &g_pTextureBillboard[0]);
	D3DXCreateTextureFromFile(pDevice, KEY_TEXTUER1, &g_pTextureBillboard[1]);
	D3DXCreateTextureFromFile(pDevice, KEY_TEXTUER2, &g_pTextureBillboard[2]);
	D3DXCreateTextureFromFile(pDevice, KEY_TEXTUER3, &g_pTextureBillboard[3]);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	// 頂点情報の設定
	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		//頂点座標を設定
		pVtx[0].pos = D3DXVECTOR3(-10.0f, 20.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f, 20.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);

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
	g_pVtxBuffBillboard->Unlock();

}
//=============================================================================
// 壁の設定処理
//=============================================================================
void SetBillboard(D3DXVECTOR3 pos, int Type)
{
	int nCnt;
					
	for (nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		if (g_Billboard[nCnt].bUse == false)
		{
			g_Billboard[nCnt].pos = pos;
			g_Billboard[nCnt].Type = Type;
			g_Billboard[nCnt].rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
			g_Billboard[nCnt].bUse = true;
			break;
		}
	}
}