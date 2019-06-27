//=============================================================================
//
// アイテム処理 [Item.cpp]
// Author :Gokan akane
//
//=============================================================================
#include "Game.h"
#include "Player.h"
#include "Item.h"
#include "score.h"
#include "time.h"
#include "sound.h"
#include "Door.h"
#include "Explosion.h"

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureItem[MAX_ITEMTEX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;	// 頂点バッファへのポインタ
ITEM g_aItem[MAX_ITEM];				//アイテムの情報
int g_NumItem;

//=============================================================================
// 初期化処理
//=============================================================================
void InitItem(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// デバイスの取得
	pDevice = GetDevice();

	// アイテムの情報の初期化
	for(nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		g_aItem[nCntItem].nCntAnim = 0;
		g_aItem[nCntItem].nPatternAnim = 0;
		g_aItem[nCntItem].nType = 0;
		g_aItem[nCntItem].bUse = false;
		g_NumItem = 0;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTUER, &g_pTextureItem[0]);
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTUER1, &g_pTextureItem[1]);
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTUER2, &g_pTextureItem[2]);
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTUER3, &g_pTextureItem[3]);


	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
								D3DUSAGE_WRITEONLY, 
								FVF_VERTEX_2D, 
								D3DPOOL_MANAGED,
								&g_pVtxBuffItem,
								NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);//一つ目の頂点の場所指定
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);//三つ目の頂点の場所指定（右回り）

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);//一つ目の頂点の色指定（右回り）
		pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);//二つ目の頂点の色指定（右回り）
		pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);//三つ目の頂点の色指定（右回り）
		pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);//三つ目の頂点の色指定（右回り）

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//頂点データのポインタを４つずらす
	}

	//頂点バッファのアンロック
	g_pVtxBuffItem->Unlock();

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitItem(void)
{
	int nCnt;
	// テクスチャの開放
	//テクスチャの破棄
	for (nCnt = 0; nCnt < MAX_ITEMTEX; nCnt++)
	{
		if (g_pTextureItem[nCnt] != NULL)
		{
			g_pTextureItem[nCnt]->Release();
			g_pTextureItem[nCnt] = NULL;
		}

	}
	// 頂点バッファの開放
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateItem(void)
{
	int nCntItem;
	VERTEX_2D *pVtx;//頂点情報へのポインタ
	Player*pPlayer;
	pPlayer = GetPlayer();
	
	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)//アイテムが使用されている場合
		{
			if (g_aItem[nCntItem].nType == 2)
			{
				//カウンター加算
				g_aItem[nCntItem].nCntAnim++;

				if ((g_aItem[nCntItem].nCntAnim % 8) == 0)//一定時間が経過
				{
					//パターンを更新
					g_aItem[nCntItem].nPatternAnim++;
				}

				//テクスチャ画像の更新
				pVtx[0].tex = D3DXVECTOR2((g_aItem[nCntItem].nPatternAnim % COIN_PATTERN) * 0.25f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((g_aItem[nCntItem].nPatternAnim % COIN_PATTERN) * 0.25f + 0.25f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2((g_aItem[nCntItem].nPatternAnim % COIN_PATTERN) * 0.25f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2((g_aItem[nCntItem].nPatternAnim % COIN_PATTERN) * 0.25f + 0.25f, 1.0f);
			}
			else if (g_aItem[nCntItem].nType == 1 || g_aItem[nCntItem].nType == 3)
			{
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			}
			//位置の更新
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 25, g_aItem[nCntItem].pos.y - 30, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 25, g_aItem[nCntItem].pos.y - 30, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 25, g_aItem[nCntItem].pos.y + 30, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 25, g_aItem[nCntItem].pos.y + 30, 0.0f);

		}
		pVtx += 4;
	}

	//頂点バッファのアンロック
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)//アイテムが使用されている
		{	
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureItem[g_aItem[nCntItem].nType]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntItem,
				2);
		}
	}
}

//=============================================================================
// アイテムの設定処理
//=============================================================================
void SetItem(D3DXVECTOR3 pos,int Type)
{
	int nCntItem;
	VERTEX_2D *pVtx;//頂点情報へのポインタ


	//頂点をロックして頂点データへのポインタを取得
 	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{
			//頂点情報を設定
			g_aItem[nCntItem].pos = pos;
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 25,g_aItem[nCntItem].pos.y + 30, 0.0f);//左上の頂点Xの場所指定
			pVtx[1].pos = D3DXVECTOR3(25 + g_aItem[nCntItem].pos.x, 30 + g_aItem[nCntItem].pos.y, 0.0f);//左上の頂点Xの場所指定
			pVtx[2].pos = D3DXVECTOR3(25 + g_aItem[nCntItem].pos.x, 30 + g_aItem[nCntItem].pos.y, 0.0f);//左上の頂点Xの場所指定
			pVtx[3].pos = D3DXVECTOR3(25 + g_aItem[nCntItem].pos.x, 30 + g_aItem[nCntItem].pos.y, 0.0f);//左上の頂点Xの場所指定

			g_aItem[nCntItem].nCntAnim = 0;
			g_aItem[nCntItem].nPatternAnim = 0;

			//テクスチャ画像の更新
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			g_aItem[nCntItem].nType = Type;
			g_aItem[nCntItem].bUse = true;
			g_NumItem++ ;
			break;
		}
		pVtx += 4;//該当の位置まで進める
	}
	//頂点バッファのアンロック
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// アイテムのあたり判定[CollsionItem]
//=============================================================================
bool CollsionItem(D3DXVECTOR3 *pPos)
{
	ITEM*pItem;
	int nCntItem;
	Door*pDoor;
	bool bLand = false;

	pItem = GetItem();
	pDoor = GetDoor();
	
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			bLand = false;

			if (pItem->pos.x > pPos->x - 50
				&& pItem->pos.x < pPos->x + 50 + 10
				&& pItem->pos.y > pPos->y - 50 - 50
				&& pItem->pos.y < pPos->y + 90)
			{
				PlaySound(SOUND_LABEL_SE_HIT000);
				if (g_aItem[nCntItem].nType == 0)
				{
					SetExplosion(D3DXVECTOR3(g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y, 0.0f),
								D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	
					AddScore(100);
					DeleteItem(nCntItem);
					bLand = true;

				}
				else if (g_aItem[nCntItem].nType == 1)
				{
					SetExplosion(D3DXVECTOR3(g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y, 0.0f),
								D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					AddScore(300);
					DeleteItem(nCntItem);
					bLand = true;
				}
				else if (g_aItem[nCntItem].nType == 2)
				{
					SetExplosion(D3DXVECTOR3(g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y, 0.0f),
								D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					AddScore(500);
					DeleteItem(nCntItem);
					bLand = true;
				}
				else if (g_aItem[nCntItem].nType == 3)
				{
					SetExplosion(g_aItem[nCntItem].pos, g_aItem[nCntItem].col);
					SetExplosion(pDoor->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					AddScore(800);
					DeleteItem(nCntItem);
					pDoor->state = DOORSTATE_OPENSTART;
					bLand = true;
					PlaySound(SOUND_LABEL_SE_DOOR);

				}
			}
		}
	}
	return bLand;
}

//=============================================================================
// アイテムの消去[DeleteItem]
//=============================================================================
void DeleteItem(int nCnt)
{
	g_aItem[nCnt].bUse = false;
	g_NumItem--;
}
//=============================================================================
// アイテムの取得[GetItem]
//=============================================================================
ITEM*GetItem(void)
{
	return &g_aItem[0];
}
