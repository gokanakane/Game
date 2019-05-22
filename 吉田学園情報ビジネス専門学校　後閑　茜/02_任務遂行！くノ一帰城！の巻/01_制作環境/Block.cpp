//=============================================================================
//
// 爆発処理 [Block.cpp]
// Author :Gokan akane
//
//=============================================================================
#include "input.h"
#include "main.h"
#include "Player.h"
#include "block.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TEX	(5)
#define BLOCK_MOVE (3.0f) //ブロックの移動量
#define PLAYER_POS_X (25.0f)	//プレイヤーのPos.x
#define PLAYER_POS_Y (90.0f)	//プレイヤーのPos.y

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBlock[MAX_TEX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;	// 頂点バッファへのポインタ
Block g_aBlock[MAX_BLOCK];				//ブロックの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitBlock(void)
{	
	VERTEX_2D *pVtx;//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	// デバイスの取得
	pDevice = GetDevice();

	// ブロックの情報の初期化
	for(nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].fHeight = 0.0f;
		g_aBlock[nCntBlock].fWidth = 0.0f;
		g_aBlock[nCntBlock].bUse = false;
		g_aBlock[nCntBlock].bLand = false;
		g_aBlock[nCntBlock].nType = 0;
		g_aBlock[nCntBlock].ChengeMove = 0;
		g_aBlock[nCntBlock].Cntmove = 0;

	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTUER, &g_pTextureBlock[0]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTUER1, &g_pTextureBlock[1]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTUER2, &g_pTextureBlock[2]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTUER3, &g_pTextureBlock[3]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTUER4, &g_pTextureBlock[4]);


	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
								D3DUSAGE_WRITEONLY, 
								FVF_VERTEX_2D, 
								D3DPOOL_MANAGED,
								&g_pVtxBuffBlock,
								NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);//一つ目の頂点の場所指定
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);//三つ目の頂点の場所指定（右回り）

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//頂点データのポインタを４つずらす
	}

	//頂点バッファのアンロック
	g_pVtxBuffBlock->Unlock();

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBlock(void)
{
	int nCnt;
	
	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureBlock[nCnt] != NULL)
		{
			g_pTextureBlock[nCnt]->Release();
			g_pTextureBlock[nCnt] = NULL;
		}

	}
	// 頂点バッファの開放
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBlock(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		if (g_aBlock[nCnt].bUse == true)
		{
			if (g_aBlock[nCnt].nType == 1)
			{
				if (g_aBlock[nCnt].Cntmove > 80 || g_aBlock[nCnt].Cntmove < -80)
				{
					g_aBlock[nCnt].ChengeMove *= -1;//折り返し
				}
				g_aBlock[nCnt].Cntmove += g_aBlock[nCnt].ChengeMove;
				g_aBlock[nCnt].pos.x += g_aBlock[nCnt].ChengeMove;

			}

			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCnt].pos.x, g_aBlock[nCnt].pos.y, 0.0f);//左上の頂点Xの場所指定
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCnt].pos.x + g_aBlock[nCnt].fWidth, g_aBlock[nCnt].pos.y, 0.0f);//左上の頂点Xの場所指定
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCnt].pos.x, g_aBlock[nCnt].pos.y + g_aBlock[nCnt].fHeight, 0.0f);//左上の頂点Xの場所指定
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCnt].pos.x + g_aBlock[nCnt].fWidth, g_aBlock[nCnt].pos.y + g_aBlock[nCnt].fHeight, 0.0f);//左上の頂点Xの場所指定
		}
		//該当の位置まで進める
		pVtx += 4;
	}
	//頂点バッファのアンロック
	g_pVtxBuffBlock->Unlock();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)//ブロックが使用されている
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntBlock].nType]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntBlock,
				2);
		}
	}
}

//=============================================================================
// ブロックの設定処理
//=============================================================================
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType, int ChengeMove)
{
	int nCntBlock;
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点をロックして頂点データへのポインタを取得
 	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{
			//頂点情報を設定
			g_aBlock[nCntBlock].fHeight = fHeight;
			g_aBlock[nCntBlock].fWidth = fWidth;
			g_aBlock[nCntBlock].pos = pos;

			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);//左上の頂点Xの場所指定
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + fWidth, g_aBlock[nCntBlock].pos.y, 0.0f);//左上の頂点Xの場所指定
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + fHeight, 0.0f);//左上の頂点Xの場所指定
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + fWidth, g_aBlock[nCntBlock].pos.y + fHeight, 0.0f);//左上の頂点Xの場所指定

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(5.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(5.0f, 1.0f);

			g_aBlock[nCntBlock].nType = nType;
			g_aBlock[nCntBlock].bLand = false;
			g_aBlock[nCntBlock].bUse = true;
			g_aBlock[nCntBlock].Cntmove = 0;
			g_aBlock[nCntBlock].ChengeMove = ChengeMove;
			break;
		}
		pVtx += 4;//該当の位置まで進める
	}
	//頂点バッファのアンロック
	g_pVtxBuffBlock->Unlock();
}
//=============================================================================
// ブロックのあたり判定[CollisionBlock]
//=============================================================================
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove)//現在の位置、前回の位置、移動量
{
	bool bLand = false; //着地しているか
	int nCnt;

	for (nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		if (g_aBlock[nCnt].bUse == true)
		{//ブロックの使用状況
			g_aBlock[nCnt].bLand = false;
			if (pPosold->x + PLAYER_POS_X > g_aBlock[nCnt].pos.x
				&& pPos->x - PLAYER_POS_X < g_aBlock[nCnt].pos.x + g_aBlock[nCnt].fWidth)
			{//ブロックの範囲(横幅)
			 //上判定
				if (pPosold->y <= g_aBlock[nCnt].pos.y
					&&pPos->y >= g_aBlock[nCnt].pos.y)
				{//前回の位置がブロックよりも上,現在位置がブロックよりも下（めり込んだ）
					g_aBlock[nCnt].bLand = true;
					bLand = true;
					pPos->y = g_aBlock[nCnt].pos.y;
					pMove->y = 0.0f;
				}

				//移動ブロックの上判定
				if (g_aBlock[nCnt].bLand == true)
				{//乗っている
					if (g_aBlock[nCnt].nType == 1)
					{//横移動
						g_aBlock[nCnt].bLand = true;
						bLand = true;
						pPos->x = pPos->x + g_aBlock[nCnt].ChengeMove;
						pMove->y = 0.0f;
					}

					if (g_aBlock[nCnt].nType == 3)
					{//滑る床
						g_aBlock[nCnt].bLand = true;
						bLand = true;
						pPos->x = pPos->x + g_aBlock[nCnt].ChengeMove;
						pMove->y = 0.0f;
						pMove->x += g_aBlock[nCnt].ChengeMove;
					}
				}

				//下判定
				if (pPosold->y > g_aBlock[nCnt].pos.y + g_aBlock[nCnt].fHeight + 100
					&& pPos->y < g_aBlock[nCnt].pos.y + g_aBlock[nCnt].fHeight + 100)
				{//前回の位置がブロックよりも下,現在位置がブロックよりも上（めり込んだ）
					g_aBlock[nCnt].bLand = true;
					bLand = true;
					pPos->y = g_aBlock[nCnt].pos.y + g_aBlock[nCnt].fHeight + 100;
					pMove->y = 0.0f;
				}

				//横判定
				if (g_aBlock[nCnt].bLand == false)
				{//指定するブロックの上に載っていない
					if (pPosold->y > g_aBlock[nCnt].pos.y
						&& pPos->y < g_aBlock[nCnt].pos.y + g_aBlock[nCnt].fHeight)
					{//壁判定
						g_aBlock[nCnt].bLand = true;
						bLand = true;
						pPos->x = pPosold->x;
						pMove->x = 0.0f;
					}

					if (g_aBlock[nCnt].nType == 1)
					{//横移動ブロック
						if (pPosold->y > g_aBlock[nCnt].pos.y
							&& pPos->y - PLAYER_POS_Y < g_aBlock[nCnt].pos.y + g_aBlock[nCnt].fHeight)
						{//壁判定
							g_aBlock[nCnt].bLand = true;
							bLand = true;
							pPos->x = pPosold->x + g_aBlock[nCnt].ChengeMove;
							pMove->x = 0.0f;
						}
					}
					if (g_aBlock[nCnt].nType == 3)
					{//横移動ブロック
						if (pPosold->y > g_aBlock[nCnt].pos.y
							&& pPos->y - PLAYER_POS_Y < g_aBlock[nCnt].pos.y + g_aBlock[nCnt].fHeight)
						{//壁判定
							g_aBlock[nCnt].bLand = true;
							bLand = true;
							pPos->x = pPosold->x;
							pMove->x = 0.0f;
						}
					}

				}
			}
		}
	}
	return bLand;
}
//=============================================================================
// ブロックの取得[GetBlock]
//=============================================================================
Block*GetBlock(void)
{
	return &g_aBlock[0];
}