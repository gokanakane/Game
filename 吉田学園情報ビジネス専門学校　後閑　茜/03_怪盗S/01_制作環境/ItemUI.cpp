//=============================================================================
//
// タイム処理 [ItemUI.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "ItemUI.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexItemUI(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureItemUI[MAX_ITEMUITEX] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItemUI = NULL;		// 頂点バッファへのポインタ
//=============================================================================
// 初期化処理
//=============================================================================
void InitItemUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ITEMUI1, &g_pTextureItemUI[0]);
	D3DXCreateTextureFromFile(pDevice,TEXTURE_ITEMUI,&g_pTextureItemUI[1]);	


	// 頂点情報の作成
	MakeVertexItemUI(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitItemUI(void)
{
	for (int nCnt = 0; nCnt < MAX_ITEMUITEX; nCnt++)
	{
		// テクスチャの開放
		if (g_pTextureItemUI[nCnt] != NULL)
		{
			g_pTextureItemUI[nCnt]->Release();
			g_pTextureItemUI[nCnt] = NULL;
		}
	}
	// 頂点バッファの開放
	if (g_pVtxBuffItemUI != NULL)
	{
		g_pVtxBuffItemUI->Release();
		g_pVtxBuffItemUI = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateItemUI(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawItemUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCnt;

	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffItemUI, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_HEIGTH; nCnt++)
	{
		if (nCnt < 4)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureItemUI[1]);
		}
		else
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureItemUI[0]);

		}
		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt * 4,
			2);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexItemUI(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_HEIGTH,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItemUI,
		NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffItemUI->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHeigth = 0; nCntHeigth < MAX_HEIGTH - 1; nCntHeigth++)
	{
		// 頂点情報を設定	
		pVtx[0].pos = D3DXVECTOR3(1135.0f, 180.0f + (130.0f * nCntHeigth), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1250.0f, 180.0f + (130.0f * nCntHeigth), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1135.0f, 300.0f + (130.0f * nCntHeigth), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1250.0f, 300.0f + (130.0f * nCntHeigth), 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点色
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

		
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//該当の位置まで進める
		pVtx += 4;
	}
	// 頂点情報を設定	
	pVtx[0].pos = D3DXVECTOR3(1100.0f, 130.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 130.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(1100.0f, 180.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 180.0f, 0.0f);

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


	//頂点バッファのアンロック
	g_pVtxBuffItemUI->Unlock();

}
