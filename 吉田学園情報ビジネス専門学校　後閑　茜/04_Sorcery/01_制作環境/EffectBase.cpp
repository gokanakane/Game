//=============================================================================
//
// エフェクト処理 [CEffect.cpp]
// Author : 
//
//=============================================================================
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "manager.h"
#include "effectBase.h"
#include "bulletEffect.h"
#include "fallStarEffect.h"
#include "magicEffect.h"
#include "playerBase.h"
//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CEffect::m_pTexture[MAX_EFFECTTEX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CEffect::CEffect(int Priority):CScene2D(Priority)
{
	m_pVtxBuff = NULL;
	m_fSizeW = 0.0f;
	m_fSizeH = 0.0f;
	m_EffectType = EFFECTTYPE_NONE;
	m_nLife = 0;

}
//=============================================================================
// デストラクタ
//=============================================================================
CEffect::~CEffect() {}
//=============================================================================
// エフェクトの生成
//=============================================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos,EFFECTTYPE eftype,D3DXCOLOR col)
{
	CEffect *pEffect = NULL;
	if (pEffect == NULL)
	{
		switch (eftype)
		{
		case EFFECTTYPE_BULLET:
			pEffect = new CBulletEffect;
			pEffect->Init();
			pEffect->BindTexture(m_pTexture[1]);
			pEffect->SetEffect(pos, BULLET_SIZE, BULLET_SIZE, EFFECTTYPE_BULLET);
			pEffect->m_nLife = 7;
			pEffect->m_EffectType = eftype;
			pEffect->SetColor(col);
			pEffect->SetObjtype(CScene::OBJTYPE_EFFECT);
			break;

		case EFFECTTYPE_FALL:
			pEffect = new CFallStar;
			pEffect->Init();
			pEffect->BindTexture(m_pTexture[2]);
			pEffect->SetEffect(pos, BULLET_SIZE, BULLET_SIZE, EFFECTTYPE_FALL);
			pEffect->m_nLife = 7;
			pEffect->m_EffectType = eftype;
			pEffect->SetAnimY(2, 1, 0);
			pEffect->SetObjtype(CScene::OBJTYPE_EFFECT);
			break;

		case EFFECTTYPE_MAGIC:
			pEffect = new CMagicEffect;
			pEffect->Init();
			pEffect->BindTexture(m_pTexture[1]);
			pEffect->SetEffect(pos, BULLET_SIZE, BULLET_SIZE, EFFECTTYPE_BULLET);
			pEffect->m_nLife = 15;
			pEffect->m_EffectType = eftype;
			pEffect->SetColor(col);
			pEffect->SetObjtype(CScene::OBJTYPE_EFFECT);
			break;
		}
	}

	return pEffect;
}

//=============================================================================
// エフェクトの初期化処理
//=============================================================================
HRESULT CEffect::Init(void)
{
	CScene2D::Init();
	return S_OK;
}

//=============================================================================
// エフェクトの終了処理
//=============================================================================
void CEffect::Uninit(void)
{
 	CScene2D::Uninit();
}
//=============================================================================
// エフェクトの更新処理
//=============================================================================
void CEffect::Update(void)
{
}

//=============================================================================
// エフェクトの描画処理
//=============================================================================
void CEffect::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}
	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}
//=============================================================================
// 位置の設定
//=============================================================================
void CEffect::SetEffect(D3DXVECTOR3 pos,float sizeW,float sizeH,EFFECTTYPE type)
{
	m_pos = pos;
	m_fSizeH = sizeH;
	m_fSizeW = sizeW;
	SetScene2D(m_pos, m_fSizeW, m_fSizeH);

}
//=============================================================================
// テクスチャのロード
//=============================================================================
HRESULT CEffect::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MAGICTEAM, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BULLETEFFECT, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_STAR, &m_pTexture[2]);

	return S_OK;
}
//=============================================================================
// テクスチャのアンロード
//=============================================================================
void CEffect::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_EFFECTTEX; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
