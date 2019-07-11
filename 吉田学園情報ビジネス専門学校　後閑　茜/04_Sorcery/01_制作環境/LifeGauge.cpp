//=============================================================================
//
// �̗̓Q�[�W���� [LifeGauge.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "GameUi.h"
#include "LifeGauge.h"
#include "playerBase.h"
#include "Input.h"
//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CLifeGauge::LifeState CLifeGauge::m_State = CLifeGauge::LIFESTATE_NONE;
LPDIRECT3DTEXTURE9 CLifeGauge::m_pTexture = NULL;
int CLifeGauge::m_nMaxLife = 0;

//*****************************************************************************
// ��class CLifeGauge
//*****************************************************************************
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLifeGauge::CLifeGauge() :CScene2D(5)
{
	m_State = LIFESTATE_NONE;
	m_nMaxLife = CPlayer::GetLife();
	m_fNowLifeGauge = 0.0f;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLifeGauge::~CLifeGauge() {}
//=============================================================================
// ��������
//=============================================================================
CLifeGauge *CLifeGauge::Create()
{
	CLifeGauge *pLifeGauge = NULL;
	if (pLifeGauge == NULL)
	{
		pLifeGauge = new CLifeGauge;
		pLifeGauge->Init();
		pLifeGauge->BindTexture(m_pTexture);
		pLifeGauge->SetScene2DLeftCenter(LIFEGAUGEPOS_CENTER, 800.0f, 50.0f);
		pLifeGauge->SetObjtype(CScene::OBJTYPE_UI);
	}
	return pLifeGauge;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CLifeGauge::Init(void)
{
	CScene2D::Init();
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CLifeGauge::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CLifeGauge::Update(void)
{
	float nNowLife = float(CPlayer::GetLife());	//Int�^�̗̑͂�float�ɕϊ����Ď擾���Ă���
	m_fNowLifeGauge = nNowLife / m_nMaxLife;	//���݂̗̑�/�S�̗̂̑͂őS�̂̉������������v�Z����

												//�v�Z���ʂ������ăQ�[�W�̑傫���𒲐�����B
	SetScene2DLeftCenter(D3DXVECTOR3(LIFEGAUGEPOS_CENTER), 800.0f*m_fNowLifeGauge, 50.0f);

	if (m_fNowLifeGauge <= 0.5f)
	{//�̗͂�50���؂�����
		m_State = LIFESTATE_HALF;
	}
	if (m_fNowLifeGauge <= 0.3f)
	{//�̗͂�30%�؂�����
		m_State = LIFESTATE_PINCH;
	}

	switch (m_State)
	{
	case LIFESTATE_NONE:
		m_State = LIFESTATE_MARGIN;
		break;

	case LIFESTATE_MARGIN:
		SetColor(LIFEGAUGECOL_MARGIN);
		break;

	case LIFESTATE_HALF:
		SetColor(LIFEGAUGECOL_HARF);
		break;

	case LIFESTATE_PINCH:
		SetColor(LIFEGAUGECOL_PINTH);
		break;
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CLifeGauge::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// �e�N�X�`���̃��[�h
//=============================================================================
HRESULT CLifeGauge::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, LIFEGAUGE_TEXTURE, &m_pTexture);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���̃A�����[�h
//=============================================================================
void CLifeGauge::UnLoad(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
