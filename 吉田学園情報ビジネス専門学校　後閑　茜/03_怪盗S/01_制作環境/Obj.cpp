//=============================================================================
//
// モデル処理 [Obj.cpp]
// Author : 
//
//=============================================================================
#include "Obj.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "Player.h"
#include "Bullet.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureObj = NULL;	//テクスチャへのポインタ
Obj g_Obj;								//モデルの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitObj(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nNumVtx;						//頂点数
	DWORD sizeFVF;						//頂点フォーマットのサイズ
	BYTE *pVtxBuff;						//頂点バッファのポインタ

	g_Obj.nNumMat = 0;

	g_Obj.vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
	g_Obj.vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	// Xファイルの読み込み
	D3DXLoadMeshFromX(OBJ_1,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Obj.pBuffMat,
		NULL,
		&g_Obj.nNumMat,
		&g_Obj.pMesh);

	//頂点数の取得
	nNumVtx = g_Obj.pMesh->GetNumVertices();
	sizeFVF = D3DXGetFVFVertexSize(g_Obj.pMesh->GetFVF());

	//頂点バッファのロック
	g_Obj.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		if (g_Obj.vtxMin.x > vtx.x)
		{//Xの最小値の書き換え
			g_Obj.vtxMin.x = vtx.x;
		}
		if (g_Obj.vtxMin.z > vtx.z)
		{//Xの最小値の書き換え
			g_Obj.vtxMin.z = vtx.z;
		}
		if (g_Obj.vtxMax.x < vtx.x)
		{//Xの最小値の書き換え
			g_Obj.vtxMax.x = vtx.x;
		}
		if (g_Obj.vtxMax.z < vtx.z)
		{//Xの最小値の書き換え
			g_Obj.vtxMax.z = vtx.z;
		}

		pVtxBuff += sizeFVF;//サイズ分ポインタを進める
	}
	//頂点バッファのアンロック
	g_Obj.pMesh->UnlockVertexBuffer();
	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice, OBJ_TEXTURE, &g_pTextureObj);
	// 位置・向き・色の初期設定
	g_Obj.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Obj.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Obj.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	g_Obj.nType = 0;
	g_Obj.bUse = false;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitObj(void)
{
	for (int nCnt = 0; nCnt < MAX_OBJ; nCnt++)
	{
		// メッシュの開放
		if (g_Obj.pMesh != NULL)
		{
			g_Obj.pMesh->Release();
			g_Obj.pMesh = NULL;
		}
		// マテリアルの開放
		if (g_Obj.pBuffMat != NULL)
		{
			g_Obj.pBuffMat->Release();
			g_Obj.pBuffMat = NULL;
		}
	}
	
	if (g_pTextureObj != NULL)
	{
		g_pTextureObj->Release();
		g_pTextureObj = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateObj(void)
{
	if (g_Obj.bUse == true)
	{
		SetPositionShadow(g_Obj.nIdxShadow, g_Obj.pos);
	}
	else
	{
		DeleteShadow(g_Obj.nIdxShadow);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawObj(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;			//計算用マトリックス
	D3DMATERIAL9 matDef;					//現在のマテリアルの保存用
	D3DXMATERIAL *pMat;						//マテリアルデータへのポインタ


	//zテスト
	//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	if (g_Obj.bUse == true)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Obj.mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Obj.rot.y, g_Obj.rot.x, g_Obj.rot.z);
		D3DXMatrixMultiply(&g_Obj.mtxWorld, &g_Obj.mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTrans, g_Obj.pos.x, g_Obj.pos.y, g_Obj.pos.z);
		D3DXMatrixMultiply(&g_Obj.mtxWorld, &g_Obj.mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Obj.mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Obj.pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat <= (int)g_Obj.nNumMat; nCntMat++)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureObj);

			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// モデル(パーツ)の描画
			g_Obj.pMesh->DrawSubset(nCntMat);
		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);
	}
	//zテスト
	//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

}
//=============================================================================
// モデルの取得
//=============================================================================
Obj*GetObj(void)
{
	return &g_Obj;
}
//=============================================================================
// モデルとプレイヤーのあたり判定
//=============================================================================
bool CollisionObj(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld ,D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax)
{
	Player *pPlayer;
	pPlayer = GetPlayer();
	bool bLand = false;
	if (g_Obj.bUse == true)
	{//モデルの使用状況
		bLand = false;
		if (g_Obj.bUse == true)
		{//モデルの使用状況
			bLand = false;
			if (pos->x + vtxMax.x > g_Obj.pos.x + g_Obj.vtxMin.x &&
				pos->x + vtxMin.x < g_Obj.pos.x + g_Obj.vtxMax.x)
			{//ｘの範囲判定
				if (posOld->z + vtxMin.z >= g_Obj.pos.z + g_Obj.vtxMax.z &&
					g_Obj.pos.z + g_Obj.vtxMax.z > pos->z + vtxMin.z)
				{//奥面
					pos->z = g_Obj.pos.z + g_Obj.vtxMax.z - vtxMin.z;
					bLand = true;
				}
				else if (posOld->z + vtxMax.z <= g_Obj.pos.z + g_Obj.vtxMin.z &&
					g_Obj.pos.z + g_Obj.vtxMin.z < pos->z + vtxMax.z)
				{//手前の面
					pos->z = g_Obj.pos.z + g_Obj.vtxMin.z + vtxMin.z;
					bLand = true;
				}
			}
			if (pos->z + vtxMax.z < g_Obj.pos.z + g_Obj.vtxMax.z &&
				pos->z + vtxMax.z > g_Obj.pos.z + g_Obj.vtxMin.z)
			{//zの範囲判定
				if (posOld->x + vtxMin.x >= g_Obj.pos.x + g_Obj.vtxMax.x &&
					g_Obj.pos.x + g_Obj.vtxMax.x > pos->x + vtxMin.x)
				{//右側の面
					pos->x = g_Obj.pos.x + g_Obj.vtxMax.x - vtxMin.x+0.01f;
					bLand = true;
				}
				else if (posOld->x + vtxMax.x <= g_Obj.pos.x + g_Obj.vtxMin.x &&
					g_Obj.pos.x + g_Obj.vtxMin.x < pos->x + vtxMax.x)
				{//左側の面
					pos->x = g_Obj.pos.x + g_Obj.vtxMin.x - vtxMax.x;
					bLand = true;
				}
			}
		}
	}
	return bLand;
}
//=============================================================================
// モデルの設定
//=============================================================================
void SetObj(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	if (g_Obj.bUse == false)
	{
		g_Obj.pos = pos;
		g_Obj.rot = rot;
		g_Obj.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_Obj.nType = nType;
		g_Obj.bUse = true;

		g_Obj.nIdxShadow = SetShadow(g_Obj.pos, g_Obj.rot);
	}
}