//=============================================================================
//
// 身代わり処理 [migawari.cpp]
// Author :Gokan akane
//
//=============================================================================
#include "migawari.h"
#include "bow.h"
#include "Player.h"
#include "sound.h"
#include "Block.h"
#include "Explosion.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MIGAWARI_TEXTUER "data\\TEXTURE\\Migawari000.png"
#define MIGAWARI_TEXTUER1 "data\\TEXTURE\\Migawari001.png"
#define POS_Y (620)
#define MIGAWARI_MOVE (1.0f)
#define MIGAWARI_PATTERN		(5)
#define MAX_MIGAWARI_TYPE (2)
#define MAX_TEX (2)
//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureMigawari[MAX_TEX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMigawari = NULL;	// 頂点バッファへのポインタ
Migawari g_aMigawari;	//身代わりの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitMigawari(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 身代わりの情報の初期化
		g_aMigawari.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMigawari.posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMigawari.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMigawari.state = MIGAWARISTATE_NOMAL;
		g_aMigawari.nCntState = 0;
		g_aMigawari.bUse = false;
		g_aMigawari.type = 0;
		g_aMigawari.nLife = MIGAWARI_MAX_LIFE;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MIGAWARI_TEXTUER, &g_pTextureMigawari[0]);
	D3DXCreateTextureFromFile(pDevice, MIGAWARI_TEXTUER1, &g_pTextureMigawari[1]);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMigawari,
		NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffMigawari->Lock(0, 0, (void**)&pVtx, 0);

		//座標の設定
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);//一つ目の頂点の場所指定
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);//三つ目の頂点の場所指定（右回り）

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//色の設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）

		//テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	g_pVtxBuffMigawari->Unlock();

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMigawari(void)
{

	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureMigawari[nCnt] != NULL)
		{
			g_pTextureMigawari[nCnt]->Release();
			g_pTextureMigawari[nCnt] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffMigawari != NULL)
	{
		g_pVtxBuffMigawari->Release();
		g_pVtxBuffMigawari = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMigawari(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

					//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffMigawari->Lock(0, 0, (void**)&pVtx, 0);
		switch (g_aMigawari.state)
		{
		case MIGAWARISTATE_NOMAL:
			break;

		case MIGAWARISTATE_DAMAGE:
			g_aMigawari.nCntState--;
			if (g_aMigawari.nCntState <= 0)
			{
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）

				g_aMigawari.state = MIGAWARISTATE_NOMAL;

			}
			break;

		case MIGAWARISTATE_DEATH:
			g_aMigawari.bUse = false;
 			g_aMigawari.state = MIGAWARISTATE_NOMAL;
			break;

		}

		if (g_aMigawari.bUse == true)
		{
			g_aMigawari.posold = g_aMigawari.pos; //前回の位置を保存

			g_aMigawari.move.y += 3.5;//重力加算

			//位置の更新
			g_aMigawari.pos.x += g_aMigawari.move.x;
			g_aMigawari.pos.y += g_aMigawari.move.y;

			CollisionBlock(&g_aMigawari.pos, &g_aMigawari.posold, &g_aMigawari.move);

			pVtx[0].pos = D3DXVECTOR3(g_aMigawari.pos.x - 40, g_aMigawari.pos.y - 90, 0.0f);//一つ目の頂点の場所指定
			pVtx[1].pos = D3DXVECTOR3(g_aMigawari.pos.x + 40, g_aMigawari.pos.y - 90, 0.0f);//二つ目の頂点の場所指定（右回り）
			pVtx[2].pos = D3DXVECTOR3(g_aMigawari.pos.x - 40, g_aMigawari.pos.y, 0.0f);//三つ目の頂点の場所指定（右回り）
			pVtx[3].pos = D3DXVECTOR3(g_aMigawari.pos.x + 40, g_aMigawari.pos.y, 0.0f);//三つ目の頂点の場所指定（右回り）
		}
	//頂点バッファのアンロック
	g_pVtxBuffMigawari->Unlock();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMigawari(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffMigawari, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	// ポリゴンの描画
	// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureMigawari[g_aMigawari.type]);

		if (g_aMigawari.bUse == true)//身代わりが使用されている
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0,
				2);
		}
}

//=============================================================================
// 身代わりの設定処理
//=============================================================================
void SetMigawari(D3DXVECTOR3 pos, int Type)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffMigawari->Lock(0, 0, (void**)&pVtx, 0);

		if (g_aMigawari.bUse == false)
		{
			PlaySound(SOUND_LABEL_SE_MIGAWARI);

			g_aMigawari.pos = pos;
			//座標の設定
			pVtx[0].pos = D3DXVECTOR3(pos.x - 40, pos.y - 90, 0.0f);//一つ目の頂点の場所指定
			pVtx[1].pos = D3DXVECTOR3(pos.x + 40,pos.y - 90, 0.0f);//二つ目の頂点の場所指定（右回り）
			pVtx[2].pos = D3DXVECTOR3(pos.x - 40, pos.y, 0.0f);//三つ目の頂点の場所指定（右回り）
			pVtx[3].pos = D3DXVECTOR3(pos.x + 40, pos.y, 0.0f);//三つ目の頂点の場所指定（右回り）

			g_aMigawari.state = MIGAWARISTATE_NOMAL;
			g_aMigawari.nCntState = 0;
			g_aMigawari.bUse = true;
			g_aMigawari.type = Type;
			g_aMigawari.nLife = MIGAWARI_MAX_LIFE;
		}
	//頂点バッファのアンロック
	g_pVtxBuffMigawari->Unlock();
}
//=============================================================================
// 身代わりのダメージ
//=============================================================================
void HitMigawari(int nDamage)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	g_aMigawari.nLife -= nDamage;

	if (g_aMigawari.nLife == 0)
	{
		SetExplosion(g_aMigawari.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		g_aMigawari.state = MIGAWARISTATE_DEATH;
	}

	else
	{
		g_aMigawari.state = MIGAWARISTATE_DAMAGE;
		g_aMigawari.nCntState = 5;

		//頂点バッファをロック
		g_pVtxBuffMigawari->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//二つ目の頂点の色指定（右回り）
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//三つ目の頂点の色指定（右回り）
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//三つ目の頂点の色指定（右回り）

		// 頂点バッファをアンロックする
		g_pVtxBuffMigawari->Unlock();

	}

}
//=============================================================================
// 身代わりの設定処理
//=============================================================================
Migawari*GetMigawari(void)
{
	return &g_aMigawari;
}