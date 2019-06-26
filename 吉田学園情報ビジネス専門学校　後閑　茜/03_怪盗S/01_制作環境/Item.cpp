//=============================================================================
//
// 壁処理 [Item.cpp]
// Author : 後閑茜
//
//=============================================================================
#include "Item.h"
#include "shadow.h"
#include "Player.h"
#include "Game.h"
#include "score.h"
#include "ItemGetUI.h"
#include "sound.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ITEM_TEXTURE1 "data\\TEXTURE\\Object\\Item001.png"
#define ITEM_TEXTURE2 "data\\TEXTURE\\Object\\Item002.png"
#define ITEM_TEXTURE3 "data\\TEXTURE\\Object\\Item003.png"
#define ITEM_TEXTURE4 "data\\TEXTURE\\Object\\Item004.png"
#define ITEM_TEXTURE5 "data\\TEXTURE\\Object\\Key004.png"


#define MAX_TEX (5)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexItem(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem= NULL;
LPDIRECT3DTEXTURE9 g_pTextureItem[MAX_TEX] = {};//テクスチャへのポインタ
Item g_Item[MAX_ITEM];					//壁の最大数
//=============================================================================
// 初期化処理
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	{
		g_Item[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nCnt].bUse = false;
		g_Item[nCnt].IdxShadow = SetShadow(g_Item[g_Item[nCnt].IdxShadow].pos, g_Item[g_Item[nCnt].IdxShadow].rot);
	}


	MakeVertexItem(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitItem(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (g_pTextureItem[nCnt] != NULL)
		{
			g_pTextureItem[nCnt]->Release();
			g_pTextureItem[nCnt] = NULL;
		}
	}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateItem(void)
{
	Player*pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (g_Item[nCnt].bUse == true)
		{
			SetPositionShadow(g_Item[nCnt].IdxShadow, g_Item[nCnt].pos);
			if (g_Item[nCnt].pos.x - 10 < pPlayer->pos.x
				&&g_Item[nCnt].pos.x + 10 > pPlayer->pos.x
				&&g_Item[nCnt].pos.z - 10 < pPlayer->pos.z
				&&g_Item[nCnt].pos.z + 10 > pPlayer->pos.z)
			{//ビルボードのあたり判定
				g_Item[nCnt].bUse = false;
				DeleteShadow(g_Item[nCnt].IdxShadow);
				g_Item[nCnt].IdxItem = SetItemGetUI(nCnt);
				AddScore(2000);
				PlaySound(SOUND_LABEL_SE_ITEMGET);
			}
		}
	}

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxView;				//計算用マトリックス
	int nCntItem;

	//ライトの無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//αテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == true)
		{

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Item[nCntItem].mtxWorld);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			g_Item[nCntItem].mtxWorld._11 = mtxView._11;
			g_Item[nCntItem].mtxWorld._12 = mtxView._21;
			g_Item[nCntItem].mtxWorld._13 = mtxView._31;
			g_Item[nCntItem].mtxWorld._21 = mtxView._12;
			g_Item[nCntItem].mtxWorld._22 = mtxView._22;
			g_Item[nCntItem].mtxWorld._23 = mtxView._32;
			g_Item[nCntItem].mtxWorld._31 = mtxView._13;
			g_Item[nCntItem].mtxWorld._32 = mtxView._23;
			g_Item[nCntItem].mtxWorld._33 = mtxView._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Item[nCntItem].pos.x, g_Item[nCntItem].pos.y, g_Item[nCntItem].pos.z);
			D3DXMatrixMultiply(&g_Item[nCntItem].mtxWorld, &g_Item[nCntItem].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Item[nCntItem].mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffItem, 0,
				sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureItem[g_Item[nCntItem].Type]);

			// 壁の描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntItem * 4,
				2);
		}
	}
	//αテストの無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//ライトの有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexItem(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;//頂点情報へのポインタ

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTURE1, &g_pTextureItem[0]);
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTURE2, &g_pTextureItem[1]);
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTURE3, &g_pTextureItem[2]);
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTURE4, &g_pTextureItem[3]);
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTURE5, &g_pTextureItem[4]);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	// 頂点情報の設定
	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	{
		//頂点座標を設定
		pVtx[0].pos = D3DXVECTOR3(-5.0f, 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(5.0f, 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-5.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(5.0f, 0.0f, 0.0f);

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
	g_pVtxBuffItem->Unlock();

}
//=============================================================================
// アイテムの設定処理
//=============================================================================
void SetItem(D3DXVECTOR3 pos, int Type)
{
	int nCnt;

	for (nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	{
		if (g_Item[nCnt].bUse == false)
		{
			g_Item[nCnt].pos = pos;
			g_Item[nCnt].Type = Type;
			g_Item[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Item[nCnt].bUse = true;
			break;
		}
	}
}

//=============================================================================
// アイテムゲットUIの消去
//=============================================================================
void DeleteItem(int nType)
{
	if (g_Item[nType].bUse == true)
	{
		g_Item[nType].bUse = false;
		SetItemGetUI(nType);
		AddScore(2000);

	}
}
//=============================================================================
// アイテムの取得
//=============================================================================
Item *GetItem(void)
{
	return &g_Item[0];
}
