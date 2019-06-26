//=============================================================================
//
// 爆発処理 [Explosion.cpp]
// Author :Gokan akane
//
//=============================================================================
#include "main.h"
#include "Player.h"
#include "Explosion.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_EXPLOSION		(128)		// 爆発の最大数
#define EXPLOSION_TEXTUER "data\\TEXTURE\\Effect\\explosion000.png"
#define MAX_PATTERN (3)

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	// 頂点バッファへのポインタ
Explosion g_aExplosion[MAX_EXPLOSION];				//爆発の情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitExplosion(void)
{	
	VERTEX_2D *pVtx;//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	// デバイスの取得
	pDevice = GetDevice();

	// 爆発の情報の初期化
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		g_aExplosion[nCntExplosion].nCntAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TEXTUER, &g_pTextureExplosion);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
								D3DUSAGE_WRITEONLY, 
								FVF_VERTEX_2D, 
								D3DPOOL_MANAGED,
								&g_pVtxBuffExplosion,
								NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
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
	g_pVtxBuffExplosion->Unlock();

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitExplosion(void)
{
	// テクスチャの開放
	//テクスチャの破棄
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateExplosion(void)
{
	int nCntExplosion;
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)//爆発が使用されている場合
		{//カウンター加算
			g_aExplosion[nCntExplosion].nCntAnim++;

			if ((g_aExplosion[nCntExplosion].nCntAnim % 4) == 0)//一定時間が経過
			{
				//パターンを更新
				g_aExplosion[nCntExplosion].nPatternAnim++;
			}
			
			if (g_aExplosion[nCntExplosion].nPatternAnim > MAX_PATTERN)
			{
				g_aExplosion[nCntExplosion].bUse = false;
			}
			
			//舞い上がらせる
			g_aExplosion[nCntExplosion].move.y -= 0.3f;
			//位置の更新
			g_aExplosion[nCntExplosion].pos.y += g_aExplosion[nCntExplosion].move.y;

			//頂点情報を更新
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 50, g_aExplosion[nCntExplosion].pos.y - 50, 0.0f);//左上の頂点Xの場所指定
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50, g_aExplosion[nCntExplosion].pos.y - 50, 0.0f);//左上の頂点Xの場所指定
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 50, g_aExplosion[nCntExplosion].pos.y + 50, 0.0f);//左上の頂点Xの場所指定
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50, g_aExplosion[nCntExplosion].pos.y + 50, 0.0f);//左上の頂点Xの場所指定

																															//テクスチャ画像の更新
			pVtx[0].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.25f) + 0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.25f) + 0.25f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.25f) + 0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.25f) + 0.25f, 1.0f);
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
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureExplosion);

	// ポリゴンの描画
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)//爆発が使用されている
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntExplosion,
				2);
		}
	}
}

//=============================================================================
// 爆発の設定処理
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点をロックして頂点データへのポインタを取得
 	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			//頂点情報を設定
			g_aExplosion[nCntExplosion].pos = pos;
			pVtx[nCntExplosion].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 25,g_aExplosion[nCntExplosion].pos.y + 25, 0.0f);//左上の頂点Xの場所指定
			pVtx[nCntExplosion].pos = D3DXVECTOR3(40 + g_aExplosion[nCntExplosion].pos.x, 25 + g_aExplosion[nCntExplosion].pos.y, 0.0f);//左上の頂点Xの場所指定
			pVtx[nCntExplosion].pos = D3DXVECTOR3(25 + g_aExplosion[nCntExplosion].pos.x, 40 + g_aExplosion[nCntExplosion].pos.y, 0.0f);//左上の頂点Xの場所指定
			pVtx[nCntExplosion].pos = D3DXVECTOR3(40 + g_aExplosion[nCntExplosion].pos.x, 40 + g_aExplosion[nCntExplosion].pos.y, 0.0f);//左上の頂点Xの場所指定

			//頂点情報（色）の設定
			g_aExplosion[nCntExplosion].col = col;
			pVtx[nCntExplosion].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);//一つ目の頂点の色指定（右回り）
			pVtx[nCntExplosion].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);//二つ目の頂点の色指定（右回り）
			pVtx[nCntExplosion].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);//三つ目の頂点の色指定（右回り）
			pVtx[nCntExplosion].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);//三つ目の頂点の色指定（右回り）

			g_aExplosion[nCntExplosion].nCntAnim = 0;
			g_aExplosion[nCntExplosion].nPatternAnim = 0;

			g_aExplosion[nCntExplosion].bUse = true;
			break;
		}
		pVtx += 4;//該当の位置まで進める
	}
	//頂点バッファのアンロック
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// ブロックの取得[GetExplosion]
//=============================================================================
Explosion*GetExplosion(void)
{
	return &g_aExplosion[0];
}