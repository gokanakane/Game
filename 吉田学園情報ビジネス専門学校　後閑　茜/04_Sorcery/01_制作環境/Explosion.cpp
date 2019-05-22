//=============================================================================
//
// �������� [bullet.cpp]
// Author : 
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "scene.h"
#include "bullet.h"
#include "Explosion.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
//bool g_bBool = false;
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CExplosion::CExplosion()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntAnim = -1;
	m_nPatturnAnim = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CExplosion::~CExplosion() {}
//=============================================================================
// �����̐���
//=============================================================================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion *pExplosion = NULL;

	if (pExplosion == NULL)
	{
		pExplosion = new CExplosion;
		pExplosion->Init();
		pExplosion->BindTexture(m_pTexture);
		pExplosion->SetScene2D(pos, BULLET_SIZE, BULLET_SIZE);
		pExplosion->SetAnimX(8, 1, 0);
	}
	return pExplosion;
}
//=============================================================================
// �����̏���������
//=============================================================================
HRESULT CExplosion::Init(void)
{
	CScene2D::Init();

	return S_OK;
}

//=============================================================================
// �����̏I������
//=============================================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// �����̍X�V����
//=============================================================================
void CExplosion::Update(void)
{
	//�A�j���[�V�����J�E���^�[�X�V
	m_nCntAnim++;

	if ((m_nCntAnim % 3) == 0)
	{//��莞�Ԍo��

		m_nPatturnAnim++;

		SetAnimX(8, 1, m_nPatturnAnim);

		if (m_nPatturnAnim >= MAX_ANIMATION)
		{//�A�j���[�V�������Ō�܂ōs����
			Uninit();
		}
	}
}
//=============================================================================
// �����̕`�揈��
//=============================================================================
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// �e�N�X�`���̃��[�h
//=============================================================================
HRESULT CExplosion::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_EXPLOSION, &m_pTexture);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���̃A�����[�h
//=============================================================================
void CExplosion::UnLoad(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}