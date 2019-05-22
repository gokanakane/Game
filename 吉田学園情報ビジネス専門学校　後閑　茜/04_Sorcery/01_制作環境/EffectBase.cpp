//=============================================================================
//
// �G�t�F�N�g���� [CEffect.cpp]
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
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CEffect::m_pTexture[MAX_EFFECTTEX] = {};

//=============================================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//=============================================================================
CEffect::~CEffect() {}
//=============================================================================
// �G�t�F�N�g�̐���
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
// �G�t�F�N�g�̏���������
//=============================================================================
HRESULT CEffect::Init(void)
{
	CScene2D::Init();
	return S_OK;
}

//=============================================================================
// �G�t�F�N�g�̏I������
//=============================================================================
void CEffect::Uninit(void)
{
 	CScene2D::Uninit();
}
//=============================================================================
// �G�t�F�N�g�̍X�V����
//=============================================================================
void CEffect::Update(void)
{
}

//=============================================================================
// �G�t�F�N�g�̕`�揈��
//=============================================================================
void CEffect::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}
	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}
//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void CEffect::SetEffect(D3DXVECTOR3 pos,float sizeW,float sizeH,EFFECTTYPE type)
{
	m_pos = pos;
	m_fSizeH = sizeH;
	m_fSizeW = sizeW;
	SetScene2D(m_pos, m_fSizeW, m_fSizeH);

}
//=============================================================================
// �e�N�X�`���̃��[�h
//=============================================================================
HRESULT CEffect::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MAGICTEAM, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BULLETEFFECT, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_STAR, &m_pTexture[2]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���̃A�����[�h
//=============================================================================
void CEffect::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_EFFECTTEX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
