//=============================================================================
//
// �J�b�g�C������ [cutin.cpp]
// Author : 
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "cutinBase.h"
#include "cutinNormal.h"
#include "cutinKIWAME.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CCutIn::m_pTexture[MAX_CUTINTEX] = {};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCutIn::CCutIn() :CScene2D(5)
{
	m_nCntPlayCutImNormal = 0;
	m_nCntPlayCutInKIWAME = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCutIn::~CCutIn() {}
//=============================================================================
// �w�i�̐���
//=============================================================================
CCutIn *CCutIn::Create(CutinType type, CManager::CHARACTORSELECT_STATE state)
{
	CCutIn *m_pUi = NULL;

	switch (type)
	{
	case CUTINTYPE_NORMAL:
		if (m_pUi == NULL)
		{
			m_pUi = new CCutInNormal;
			m_pUi->Init();
			m_pUi->BindTexture(m_pTexture[0]);
			m_pUi->SetScene2D(D3DXVECTOR3(1100.0f, 520.0f, 0.0f), 200.0f, 200.0f);
			m_pUi->SetAnimY(1, 6, state - 1);
		}
		break;
	case CUTINTYPE_KIWAME:
		if (m_pUi == NULL)
		{
			m_pUi = new CCutInKIWAME;
			m_pUi->Init();
			m_pUi->BindTexture(m_pTexture[1]);
			m_pUi->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH/2,300.0f, 0.0f), SCREEN_WIDTH / 2, 150.0f);
			m_pUi->SetAnimY(1, 6, state - 1);

		}
		break;
	}

	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	m_pUi->SetObjtype(CScene::OBJTYPE_UI);

	return m_pUi;
}
//=============================================================================
// �w�i�̏���������
//=============================================================================
HRESULT CCutIn::Init(void)
{
	CScene2D::Init();
	return S_OK;
}

//=============================================================================
// �w�i�̏I������
//=============================================================================
void CCutIn::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// �w�i�̍X�V����
//=============================================================================
void CCutIn::Update(void)
{
	CScene2D::Update();
}
//=============================================================================
// �w�i�̕`�揈��
//=============================================================================
void CCutIn::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// �e�N�X�`���̃��[�h
//=============================================================================
HRESULT CCutIn::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, CUTINTEX_NORMAL, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, CUTINTEX_KIWAME, &m_pTexture[1]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���̃A�����[�h
//=============================================================================
void CCutIn::UnLoad(void)
{
	// �e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_CUTINTEX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
