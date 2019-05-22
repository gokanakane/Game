//=============================================================================
//
// タイム処理 [ItemGetUI.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "ItemGetUI.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_ITEMGET "data/TEXTURE/Item001.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_ITEMGET1 "data/TEXTURE/Item002.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_ITEMGET2 "data/TEXTURE/Item003.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_ITEMGET3 "data/TEXTURE/Item004.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_ITEMGET4 "data/TEXTURE/Key004.png"	// 読み込むテクスチャファイル名
#define MAX_TEX (5)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexItemGetUI(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureItemGetUI[MAX_TEX] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItemGetUI = NULL;		// 頂点バッファへのポインタ
ItemUI g_ItemUI[MAX_TEX];
//=============================================================================
// 初期化処理
//=============================================================================
void InitItemGetUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		g_ItemUI[nCnt].nType = 0;
		g_ItemUI[nCnt].bUse = false;
	}

			// 頂点情報の作成
	MakeVertexItemGetUI(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitItemGetUI(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		// テクスチャの開放
		if (g_pTextureItemGetUI[nCnt] != NULL)
		{
			g_pTextureItemGetUI[nCnt]->Release();
			g_pTextureItemGetUI[nCnt] = NULL;
		}
	}
	// 頂点バッファの開放
	if (g_pVtxBuffItemGetUI != NULL)
	{
		g_pVtxBuffItemGetUI->Release();
		g_pVtxBuffItemGetUI = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateItemGetUI(void)
{


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawItemGetUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCnt;

	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffItemGetUI, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (g_ItemUI[nCnt].bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureItemGetUI[g_ItemUI[nCnt].nType]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCnt * 4,
				2);
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexItemGetUI(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ITEMGET, &g_pTextureItemGetUI[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ITEMGET1, &g_pTextureItemGetUI[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ITEMGET2, &g_pTextureItemGetUI[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ITEMGET3, &g_pTextureItemGetUI[3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ITEMGET4, &g_pTextureItemGetUI[4]);


	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItemGetUI,
		NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffItemGetUI->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHeigth = 0; nCntHeigth < MAX_TEX; nCntHeigth++)
	{
		// 頂点情報を設定	
		pVtx[0].pos = D3DXVECTOR3(1160.0f, 190.0f + (130.0f * nCntHeigth), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1230.0f, 190.0f + (130.0f * nCntHeigth), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1160.0f, 290.0f + (130.0f * nCntHeigth), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1230.0f, 290.0f + (130.0f * nCntHeigth), 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点色
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//該当の位置まで進める
		pVtx += 4;
	}
	//頂点バッファのアンロック
	g_pVtxBuffItemGetUI->Unlock();

}

//=============================================================================
// アイテムゲットUIの設定
//=============================================================================
int SetItemGetUI(int nType)
{
	int nCnt;
	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (g_ItemUI[nCnt].bUse == false)
		{
			g_ItemUI[nCnt].nType = nType;
			g_ItemUI[nCnt].bUse = true;
			PlaySound(SOUND_LABEL_SE_ITEMGET);

			if (g_ItemUI[nCnt].nType > 3)
			{
				g_ItemUI[nCnt].nIdxItem = nCnt;
			}
			break;
		}
	}
	return nCnt;
}

//=============================================================================
// アイテムゲットUIの消去
//=============================================================================
void DeleteItemGetUI(int nType)
{
	g_ItemUI[nType].bUse = false;

}

//=============================================================================
// アイテムゲットの取得
//=============================================================================
ItemUI*GetItemUI(void)
{
	return &g_ItemUI[0];
}

