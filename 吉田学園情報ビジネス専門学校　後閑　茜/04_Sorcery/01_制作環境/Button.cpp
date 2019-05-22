//=============================================================================
//
// UI���� [Ui.cpp]
// Author : 
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "uiBase.h"
#include "Button.h"
#include "playerBase.h"
#include "Input.h"
#include "sound.h"
#include "cutinBase.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CButton::m_pTexture[MAX_UITEXTURE] = {};
bool CButton::m_bPlayerPush = false;
CButton::PlayerPushButton CButton::m_PlayerPush = CButton::PLAYERPUSH_NONE;

//*****************************************************************************
// ��class CButton
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CButton::CButton() :CScene2D(5)
{
	m_State = BUTTONSTATE_NONE;
	m_fNowLifeGauge = 0.0f;
	nCntWait = 0;
	m_bPlayerPush = false;
	m_bPushNormal = false;
	m_bPushKIWAME = false;
	m_PlayerPush = PLAYERPUSH_NONE;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CButton::~CButton() {}
//=============================================================================
// ��������
//=============================================================================
CButton *CButton::Create(CUi::Buttontype type)
{
	CButton *pButton = NULL;

	switch (type)
	{
	case CUi::BUTTONTYPE_NORMAL:
		if (pButton == NULL)
		{
			pButton = new CButton;
			pButton->Init();
			pButton->BindTexture(m_pTexture[type]);
			if (CManager::GetMode() == CManager::MODE_GAME)
			{
				pButton->SetScene2D(D3DXVECTOR3(110.0f, 160.0f, 0.0f), 40.0f, 40.0f);
			}
			else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
			{
				pButton->SetScene2D(D3DXVECTOR3(110.0f, 260.0f, 0.0f), 40.0f, 40.0f);
			}
			pButton->SetObjtype(CScene::OBJTYPE_UI);
			pButton->SetButtonType(type);
		}
		break;
	case CUi::BUTTONTYPE_KIWAME:
		if (pButton == NULL)
		{
			pButton = new CButton;
			pButton->Init();
			pButton->BindTexture(m_pTexture[type]);
			if (CManager::GetMode() == CManager::MODE_GAME)
			{
				pButton->SetScene2D(D3DXVECTOR3(190.0f, 160.0f, 0.0f), 40.0f, 40.0f);
			}
			else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
			{
				pButton->SetScene2D(D3DXVECTOR3(190.0f, 260.0f, 0.0f), 40.0f, 40.0f);
			}
			pButton->SetObjtype(CScene::OBJTYPE_UI);
			pButton->SetButtonType(type);
		}
		break;
	}

	return pButton;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CButton::Init(void)
{
	CScene2D::Init();
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CButton::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CButton::Update(void)
{	/* �L�[�{�[�h�̎擾 */
	CInputKeyBoard *pInput = NULL;
	CUi::Buttontype Buttontype;

	if (pInput == NULL)
	{
		pInput = CManager::GetInput();
	}

	if (m_bPlayerPush == true)
	{//���@
		if (m_PlayerPush == PLAYERPUSH_NORMAL)
		{
			Buttontype = this->GetBottunType();
			if (Buttontype == CUi::BUTTONTYPE_NORMAL)
			{
				if (m_bPushNormal != true)
				{
					CSound::PlaySound(CSound::SOUND_LABEL_SE_SKILL);
					CPlayer::SetNormalSkill(CPlayer::PLAYERSKILL_NORMAL_TRUE);
					m_State = BUTTONSTATE_NORMAL;
					CCutIn::Create(CCutIn::CUTINTYPE_NORMAL, CManager::GetCharactorSelect());
					m_bPushNormal = true;
				}
			}
		}
		else if (m_PlayerPush == PLAYERPUSH_KIWAME)
		{
			Buttontype = this->GetBottunType();
			if (Buttontype == CUi::BUTTONTYPE_KIWAME)
			{
				if (m_bPushKIWAME != true)
				{
					CPlayer::SetKIWAMESkill(CPlayer::PLAYERSKILL_KIWAME_TRUE);
					m_State = BUTTONSTATE_KIWAME;
					CCutIn::Create(CCutIn::CUTINTYPE_KIWAME, CManager::GetCharactorSelect());
					m_bPushKIWAME = true;
				}
			}
		}
	}

	switch (m_State)
	{
	case BUTTONSTATE_NONE:
		this->SetColor(BUTTONCOL_NOPUSH);
		break;

	case BUTTONSTATE_NORMAL:
		if (m_bPushNormal == true)
		{
			Buttontype = this->GetBottunType();
			if (Buttontype == CUi::BUTTONTYPE_NORMAL)
			{
				nCntWait++;
				SetColor(BUTTONCOL_PUSH);
				if (nCntWait >= 180)
				{//����
					m_State = BUTTONSTATE_NONE;
					nCntWait = 0;
					m_bPlayerPush = false;
					m_bPushNormal = false;
				}
			}
		}
		break;

	case BUTTONSTATE_KIWAME:
		Buttontype = this->GetBottunType();
		if (Buttontype == CUi::BUTTONTYPE_KIWAME)
		{
			SetColor(BUTTONCOL_PUSH);
		}
		break;
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CButton::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// �`�揈
//=============================================================================
void CButton::SetButtonPush(bool bPush, PlayerPushButton Push)
{
	m_bPlayerPush = bPush;
	m_PlayerPush = Push;
}
//=============================================================================
// �{�^���̎�ނ̐ݒ�
//=============================================================================
void CButton::SetButtonType(CUi::Buttontype type)
{
	m_type = type;
}
//=============================================================================
// �e�N�X�`���̃��[�h
//=============================================================================
HRESULT CButton::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, MAGICBUTTON_NORMAL, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, MAGICBUTTON_KIWAME, &m_pTexture[1]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���̃A�����[�h
//=============================================================================
void CButton::UnLoad(void)
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
