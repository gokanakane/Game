//=============================================================================
//
// プレイヤーの体パーツ処理 [CharaParts.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "CharaParts.h"
#include "manager.h"

//=============================================================================
//	コンストラクタ&デストラクタ
//=============================================================================
CCharaParts::CCharaParts(){
	m_pTexture = NULL;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_nNumMat = 0;
}
CCharaParts::~CCharaParts()
{

}

//=============================================================================
//	設定処理
//=============================================================================
void CCharaParts::Set(LPCSTR ModelFile, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXMATRIX* pParent)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//変数設定
	m_pParent = pParent;
	m_Pos = pos;
	m_Rot = rot;

	// Xファイルの読み込み
	D3DXLoadMeshFromX(ModelFile,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

}

//=============================================================================
//	初期化処理
//=============================================================================
HRESULT CCharaParts::Init(void)
{
	m_pTexture = NULL;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_nNumMat = 0;

	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f,1.0f,1.0f);

	m_WorldPosition = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_bDrawFlag = true;

	m_fDiffuseAlpha = m_fOldAlpha = 0.5f;
	//m_fOldAlpha = 0.1f;
	m_fDestAlpha = 1.0f;
	m_nCount = 0;
	return S_OK;
}
//=============================================================================
//	終了処理
//=============================================================================
void CCharaParts::Uninit(void)
{
	// メッシュの解放
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//マテリアルの解放
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//=============================================================================
//	更新処理
//=============================================================================
void CCharaParts::Update(void)
{
	if (m_nCount < DIFFUSE_ALPHA_FLAME)
	{
		float fTime = (float)(m_nCount + 1) / (float)DIFFUSE_ALPHA_FLAME;
		float fEasing = CEasingFunc::Easing(CEasingFunc::EASE_OUT_CUBIC, fTime);
		m_fDiffuseAlpha = CUtilityMath::FloatLeap(m_fOldAlpha,m_fDestAlpha, fEasing);
		m_nCount++;
	}
	else
	{
		m_fDiffuseAlpha = m_fDestAlpha;
		m_fOldAlpha = m_fDestAlpha;
	}

}

//=============================================================================
//	描画処理
//=============================================================================
void CCharaParts::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DMATERIAL9 matDef;		//現在のマテリアル保存用
	D3DXMATERIAL *pMat;			//マテリアルデータのポインタ
	float fOrgMatAlpha = 0.0f;
	//マトリックスの計算
	CUtilityMath::CalWorldMatrix(&m_mtxWorld,m_Pos,m_Rot,m_pParent,m_Scale);

	//ワールドマトリックスから座標を取り出して保管する
	m_WorldPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	if (m_bDrawFlag == true)
	{
		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		if (m_pBuffMat != NULL)
		{
			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
			{
				//元々の値を保存する
				fOrgMatAlpha = pMat[nCntMat].MatD3D.Diffuse.a;

				//頂点色のα値に値を反映する
				pMat[nCntMat].MatD3D.Diffuse.a = m_fDiffuseAlpha;

				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				/*テクスチャの設定*/
				pDevice->SetTexture(0, m_pTexture);//テクスチャの設定(使わなければNULLを入れる)

				// モデル(パーツ)の描画
				m_pMesh->DrawSubset(nCntMat);

				//色を戻す
				pMat[nCntMat].MatD3D.Diffuse.a = fOrgMatAlpha;
			}
		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);

	}
}

//=============================================================================
//	テクスチャ割り当て処理
//=============================================================================
void CCharaParts::BindTexture(LPCSTR Tag)
{
	//テクスチャクラスからテクスチャをもらう
	m_pTexture = CTexture::GetTexture(Tag);
}

//=============================================================================
//	透明度反映処理
//=============================================================================
void CCharaParts::SetAlpha(float& fAlpha,int nCount)
{
	m_fOldAlpha = m_fDiffuseAlpha;
	if (fAlpha < 0.0f)
	{
		fAlpha = 0.0f;
	}
	else if (fAlpha > 1.0f)
	{
		fAlpha = 1.0f;
	}

	m_fDestAlpha = fAlpha;
	m_nCount = nCount;
}