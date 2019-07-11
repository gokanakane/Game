//=============================================================================
//
// �Q�[��UI���� [GameUi.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "GameUi.h"
#include "LifeGauge.h"
#include "button.h"
#include "TutorialUI.h"
#include "playerBase.h"
#include "Input.h"
#include "time.h"
#include "cutinBase.h"
#include "sound.h"
//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CUi::m_pTexture[MAX_UITEXTURE] = {};
CLifeGauge *CUi::m_pLifeGauge = NULL;
CButton *CUi::m_pButton = NULL;

//*****************************************************************************
// ��class CUi
//*****************************************************************************
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CUi::CUi() :CScene(5) {}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CUi::~CUi() {}
//=============================================================================
// �w�i�̐���
//=============================================================================
CUi *CUi::Create(void)
{
	CUi *pUi = NULL;

	if (pUi == NULL)
	{
		pUi = new CUi;
		pUi->Init();
	}

	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	pUi->SetObjtype(CScene::OBJTYPE_UI);

	return pUi;
}
//=============================================================================
// �w�i�̏���������
//=============================================================================
HRESULT CUi::Init(void)
{
	if (m_pLifeGauge == NULL)
	{
		m_pLifeGauge->Create();
	}
	if (m_pButton == NULL)
	{
		m_pButton->Create(BUTTONTYPE_NORMAL);
		//m_pButton->Create(BUTTONTYPE_KIWAME);
	}

	for (int nCnt = 0; nCnt < MAX_UITEXTURE; nCnt++)
	{
		if (nCnt == 0)
		{//�^����
			m_apScene2D[nCnt] = new CScene2D(5);
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(50.0f,SCREEN_HEIGHT/2, 0.0f), 5.0f, SCREEN_HEIGHT / 2);
			m_apScene2D[nCnt]->SetColor(DESTINYLINE_COL);
		}
		else if (nCnt == 1)
		{//�̗̓o�[
			m_apScene2D[nCnt] = new CScene2D(5);
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(455.0f, 60.0f, 0.0f), 400.0f, 50.0f);
		}
	}
	return S_OK;
}

//=============================================================================
// �w�i�̏I������
//=============================================================================
void CUi::Uninit(void)
{
	//m_apScene2D��j���i�|���S�����j�����ꂽ������Ui���͔̂j������Ă��Ȃ��j
	for (int nCnt = 0; nCnt < MAX_UITEXTURE; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt]->Uninit();
			m_apScene2D[nCnt] = NULL;
		}
	}

	if (m_pLifeGauge != NULL)
	{
		m_pLifeGauge->Uninit();
		m_pLifeGauge = NULL;
	}

	//Ui��j��
	Release();
}
//=============================================================================
// �w�i�̍X�V����
//=============================================================================
void CUi::Update(void) {}
//=============================================================================
// �w�i�̕`�揈��
//=============================================================================
void CUi::Draw(void) {}
//=============================================================================
// �e�N�X�`���̃��[�h
//=============================================================================
HRESULT CUi::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, NULL, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, UI_HPFREAM, &m_pTexture[1]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���̃A�����[�h
//=============================================================================
void CUi::UnLoad(void)
{
	// �e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_UITEXTURE; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
