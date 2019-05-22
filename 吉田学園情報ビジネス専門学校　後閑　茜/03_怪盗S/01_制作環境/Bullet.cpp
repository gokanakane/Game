//=============================================================================
//
// 弾処理 [Bullet.cpp]
// Author : 後閑茜
//
//=============================================================================
#include "Bullet.h"
#include "shadow.h"
#include "input.h"
#include "Stage.h"
#include "explosion.h"
#include "Obj.h"
#include "Player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BULLET_TEXTUER "data\\TEXTURE\\bullet000.png"
#define BULLET_SPEED (3.0f)
#define MAX_VEC (4)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;//テクスチャへのポインタ
Bullet g_Bullet[MAX_BULLET];					//弾の最大数

//=============================================================================
// 初期化処理
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		g_Bullet[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].VecA = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].VecC = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].bUse = false;
	}

	MakeVertexBullet(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
	D3DXVECTOR3 aPos[4];//ベクトル計算
	float VecLine;		//あたり判定の計算結果

	aPos[0] = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
	aPos[1] = D3DXVECTOR3(350.0f, 0.0f, 50.0f);
	aPos[2] = D3DXVECTOR3(350.0f, 0.0f, -350.0f);
	aPos[3] = D3DXVECTOR3(-50.0f, 0.0f, -350.0f);


	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		g_Bullet[nCnt].posOld = g_Bullet[nCnt].pos;
		
		if (g_Bullet[nCnt].bUse == true)
		{
				g_Bullet[nCnt].pos.x -= sinf(g_Bullet[nCnt].rot.y)*BULLET_SPEED;
				g_Bullet[nCnt].pos.z -= cosf(g_Bullet[nCnt].rot.y)*BULLET_SPEED;

				SetPositionShadow(g_Bullet[nCnt].nIdxShadow, g_Bullet[nCnt].pos);

			for (int nCntVec = 0; nCntVec < MAX_VEC; nCntVec++)
			{
				//ベクトル計算
				g_Bullet[nCnt].VecA = aPos[nCntVec] - aPos[nCntVec + 1];
				g_Bullet[nCnt].VecC = g_Bullet[nCnt].pos - aPos[nCntVec];

				if (nCntVec == MAX_VEC - 1)
				{//ベクトル計算
					g_Bullet[nCnt].VecA = aPos[nCntVec] - aPos[0];
				}

				//あたり判定計算
				VecLine = (g_Bullet[nCnt].VecA.z*g_Bullet[nCnt].VecC.x) - (g_Bullet[nCnt].VecA.x*g_Bullet[nCnt].VecC.z);

				if (VecLine >= 0)
				{//正だったら左側
					g_Bullet[nCnt].bUse = false;
					DeleteShadow(g_Bullet[nCnt].nIdxShadow);
					SetExplosion(g_Bullet[nCnt].pos);
					break;
				}
				if (VecLine <= 0)
				{//負だったら右側
					g_Bullet[nCnt].bUse = false;
					DeleteShadow(g_Bullet[nCnt].nIdxShadow);
					SetExplosion(g_Bullet[nCnt].pos);

					break;
				}
			}



			////モデルと弾のあたり判定
			//if (CollisionObj1(&g_Bullet[nCnt].pos) == true)
			//{
			//	g_Bullet[nCnt].bUse = false;
			//	DeleteShadow(g_Bullet[nCnt].nIdxShadow);
			//	SetExplosion(g_Bullet[nCnt].pos);

			//}

		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxView;				//計算用マトリックス
	int nCntBullet;


	//αテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_Bullet[nCntBullet].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Bullet[nCntBullet].mtxWorld);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			g_Bullet[nCntBullet].mtxWorld._11 = mtxView._11;
			g_Bullet[nCntBullet].mtxWorld._12 = mtxView._21;
			g_Bullet[nCntBullet].mtxWorld._13 = mtxView._31;
			g_Bullet[nCntBullet].mtxWorld._21 = mtxView._12;
			g_Bullet[nCntBullet].mtxWorld._22 = mtxView._22;
			g_Bullet[nCntBullet].mtxWorld._23 = mtxView._32;
			g_Bullet[nCntBullet].mtxWorld._31 = mtxView._13;
			g_Bullet[nCntBullet].mtxWorld._32 = mtxView._23;
			g_Bullet[nCntBullet].mtxWorld._33 = mtxView._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Bullet[nCntBullet].pos.x, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_Bullet[nCntBullet].mtxWorld, &g_Bullet[nCntBullet].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Bullet[nCntBullet].mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0,
				sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBullet);

			// 弾の描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntBullet * 4,
				2);
		}
	}
	//αテストの無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;//頂点情報へのポインタ

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTUER, &g_pTextureBullet);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	// 頂点情報の設定
	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		//頂点座標を設定
		pVtx[0].pos = D3DXVECTOR3(-3.0f, 3.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(3.0f, 3.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-3.0f, -3.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(3.0f, -3.0f, 0.0f);

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

		pVtx += 4 ;
	}
	//頂点バッファのアンロック
	g_pVtxBuffBullet->Unlock();

}
//=============================================================================
// 弾の設定処理
//=============================================================================
void SetBullet(D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	int nCnt;
					
	for (nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		if (g_Bullet[nCnt].bUse == false)
		{
			g_Bullet[nCnt].pos = pos;
			g_Bullet[nCnt].rot = rot;
			g_Bullet[nCnt].bUse = true;

			g_Bullet[nCnt].nIdxShadow = SetShadow(g_Bullet[g_Bullet[nCnt].nIdxShadow].pos,g_Bullet[g_Bullet[nCnt].nIdxShadow].rot);

			break;
		}
	}
}
//=============================================================================
// 弾の取得
//=============================================================================
Bullet*GetBullet(void)
{
	return &g_Bullet[0];
}