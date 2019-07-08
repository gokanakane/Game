//=============================================================================
//
// ディスプレイ処理 [DisPlay.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "DisPlay.h"
#include "camera.h"
#include "Player.h"
#include "Item.h"
#include "sound.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureDisPlay = NULL;	//テクスチャへのポインタ
DisPlay g_DisPlay[MAX_DISPLAY];								//モデルの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitDisPlay(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nNumVtx;						//頂点数
	DWORD sizeFVF;						//頂点フォーマットのサイズ
	BYTE *pVtxBuff;						//頂点バッファのポインタ

	for (int nCnt = 0; nCnt < MAX_DISPLAY; nCnt++)
	{
		g_DisPlay[nCnt].nNumMat = 0;

		g_DisPlay[nCnt].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_DisPlay[nCnt].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		// Xファイルの読み込み
		D3DXLoadMeshFromX(DISPLAY_1,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_DisPlay[nCnt].pBuffMat,
			NULL,
			&g_DisPlay[nCnt].nNumMat,
			&g_DisPlay[nCnt].pMesh);

		//頂点数の取得
		nNumVtx = g_DisPlay[nCnt].pMesh->GetNumVertices();
		sizeFVF = D3DXGetFVFVertexSize(g_DisPlay[nCnt].pMesh->GetFVF());

		//頂点バッファのロック
		g_DisPlay[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			if (g_DisPlay[nCnt].vtxMin.x > vtx.x)
			{//Xの最小値の書き換え
				g_DisPlay[nCnt].vtxMin.x = vtx.x;
			}
			if (g_DisPlay[nCnt].vtxMin.z > vtx.z)
			{//Xの最小値の書き換え
				g_DisPlay[nCnt].vtxMin.z = vtx.z;
			}
			if (g_DisPlay[nCnt].vtxMax.x < vtx.x)
			{//Xの最小値の書き換え
				g_DisPlay[nCnt].vtxMax.x = vtx.x;
			}
			if (g_DisPlay[nCnt].vtxMax.z < vtx.z)
			{//Xの最小値の書き換え
				g_DisPlay[nCnt].vtxMax.z = vtx.z;
			}

			pVtxBuff += sizeFVF;//サイズ分ポインタを進める
		}
		//頂点バッファのアンロック
		g_DisPlay[nCnt].pMesh->UnlockVertexBuffer();
		//テクスチャの設定
		D3DXCreateTextureFromFile(pDevice, DISPLAY_TEXTURE, &g_pTextureDisPlay);
		// 位置・向き・色の初期設定
		g_DisPlay[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_DisPlay[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_DisPlay[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_DisPlay[nCnt].nType = 0;
		g_DisPlay[nCnt].bUse = false;
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitDisPlay(void)
{
	for (int nCnt = 0; nCnt < MAX_DISPLAY; nCnt++)
	{
		// メッシュの開放
		if (g_DisPlay[nCnt].pMesh != NULL)
		{
			g_DisPlay[nCnt].pMesh->Release();
			g_DisPlay[nCnt].pMesh = NULL;
		}
		// マテリアルの開放
		if (g_DisPlay[nCnt].pBuffMat != NULL)
		{
			g_DisPlay[nCnt].pBuffMat->Release();
			g_DisPlay[nCnt].pBuffMat = NULL;
		}
	}
	
	if (g_pTextureDisPlay != NULL)
	{
		g_pTextureDisPlay->Release();
		g_pTextureDisPlay = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateDisPlay(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawDisPlay(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;			//計算用マトリックス
	D3DMATERIAL9 matDef;					//現在のマテリアルの保存用
	D3DXMATERIAL *pMat;						//マテリアルデータへのポインタ


	//zテスト
	//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	for (int nCnt = 0; nCnt < MAX_DISPLAY; nCnt++)
	{

		if (g_DisPlay[nCnt].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_DisPlay[nCnt].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_DisPlay[nCnt].rot.y, g_DisPlay[nCnt].rot.x, g_DisPlay[nCnt].rot.z);
			D3DXMatrixMultiply(&g_DisPlay[nCnt].mtxWorld, &g_DisPlay[nCnt].mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTrans, g_DisPlay[nCnt].pos.x, g_DisPlay[nCnt].pos.y, g_DisPlay[nCnt].pos.z);
			D3DXMatrixMultiply(&g_DisPlay[nCnt].mtxWorld, &g_DisPlay[nCnt].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_DisPlay[nCnt].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_DisPlay[nCnt].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat <= (int)g_DisPlay[nCnt].nNumMat; nCntMat++)
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_pTextureDisPlay);

				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// モデル(パーツ)の描画
				g_DisPlay[nCnt].pMesh->DrawSubset(nCntMat);
			}

			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}
	}
	//zテスト
	//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

}
//=============================================================================
// モデルの取得
//=============================================================================
DisPlay*GetDisPlay(void)
{
	return &g_DisPlay[0];
}
//=============================================================================
// モデルとプレイヤーのあたり判定
//=============================================================================
void CollisionDisPlay(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax)
{
	Player *pPlayer;
	pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < MAX_DISPLAY; nCnt++)
	{
		if (g_DisPlay[nCnt].bUse == true)
		{//モデルの使用状況
			if (pos->x + vtxMax.x > g_DisPlay[nCnt].pos.x + g_DisPlay[nCnt].vtxMin.x &&
				pos->x + vtxMin.x < g_DisPlay[nCnt].pos.x + g_DisPlay[nCnt].vtxMax.x)
			{//ｘの範囲判定
				if (posOld->z + vtxMin.z >= g_DisPlay[nCnt].pos.z + g_DisPlay[nCnt].vtxMax.z &&
					g_DisPlay[nCnt].pos.z + g_DisPlay[nCnt].vtxMax.z > pos->z + vtxMin.z)
				{//奥面
					pos->z = g_DisPlay[nCnt].pos.z + g_DisPlay[nCnt].vtxMax.z - vtxMin.z;
					DeleteItem(g_DisPlay[nCnt].nType);

					break;
				}
				else if (posOld->z + vtxMax.z <= g_DisPlay[nCnt].pos.z + g_DisPlay[nCnt].vtxMin.z &&
					g_DisPlay[nCnt].pos.z + g_DisPlay[nCnt].vtxMin.z < pos->z + vtxMax.z)
				{//手前の面
					pos->z = g_DisPlay[nCnt].pos.z + g_DisPlay[nCnt].vtxMin.z + vtxMin.z;
					DeleteItem(g_DisPlay[nCnt].nType);

					break;
				}
			}
			if (pos->z + vtxMax.z < g_DisPlay[nCnt].pos.z + g_DisPlay[nCnt].vtxMax.z &&
				pos->z + vtxMax.z > g_DisPlay[nCnt].pos.z + g_DisPlay[nCnt].vtxMin.z)
			{//zの範囲判定
				if (posOld->x + vtxMin.x >= g_DisPlay[nCnt].pos.x + g_DisPlay[nCnt].vtxMax.x &&
					g_DisPlay[nCnt].pos.x + g_DisPlay[nCnt].vtxMax.x > pos->x + vtxMin.x)
				{//右側の面
					pos->x = g_DisPlay[nCnt].pos.x + g_DisPlay[nCnt].vtxMax.x - vtxMin.x;
					DeleteItem(g_DisPlay[nCnt].nType);

					break;
				}
				else if (posOld->x + vtxMax.x <= g_DisPlay[nCnt].pos.x + g_DisPlay[nCnt].vtxMin.x &&
					g_DisPlay[nCnt].pos.x + g_DisPlay[nCnt].vtxMin.x < pos->x + vtxMax.x)
				{//左側の面
					pos->x = g_DisPlay[nCnt].pos.x + g_DisPlay[nCnt].vtxMin.x - vtxMax.x;
					DeleteItem(g_DisPlay[nCnt].nType);

					break;
				}
			}
		}
	}
}
//=============================================================================
// モデルの設定
//=============================================================================
void SetDisPlay(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	for (int nCnt = 0; nCnt < MAX_DISPLAY; nCnt++)
	{
		if (g_DisPlay[nCnt].bUse == false)
		{
			g_DisPlay[nCnt].pos = pos;
			g_DisPlay[nCnt].rot = rot;
			g_DisPlay[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			g_DisPlay[nCnt].nType = nType;
			g_DisPlay[nCnt].bUse = true;
			break;
		}
	}
}