//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : 
//
//=============================================================================
#include "manager.h"
#include "scene.h"
#include "scene2D.h"
#include "Input.h"
#include "fade.h"
#include "game.h"
#include "number.h"
#include "StageBase.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Stage4.h"
#include "playerBase.h"
#include "bullet.h"
#include "Explosion.h"
#include "scoreBase.h"
#include "effectBase.h"
#include "Pause.h"
#include "uiBase.h"
#include "LifeGauge.h"
#include "Button.h"
#include "time.h"
#include "cutinBase.h"
#include "optionBase.h"
#include "sound.h"

//*****************************************************************************
// �O���[�o���ϐ�/�ÓI�����o�ϐ�
//*****************************************************************************
CPlayer *CGame::m_pPlayer = NULL;
CScore *CGame::m_pScore = NULL;
CPause *CGame::m_pPause = NULL;
CUi *CGame::m_pUi = NULL;
CStage *CGame::m_pStage = NULL;
int CGame::m_nCntState = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	m_GameState = GAMESTATE_NONE;
	m_SelectStage = CManager::GetStageSelect();

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CGame::Init(void)
{
	//�e�N�X�`���̂�݂���
	CPlayer::Load();
	CBullet::Load();
	CExplosion::Load();
	CNumber::Load();
	CEffect::Load();
	CPause::Load();
	CUi::Load();
	CLifeGauge::Load();
	CButton::Load();
	CCutIn::Load();
	COption::Load();

	if (CManager::GetStageSelect() == CManager::STAGESELECT_STAGE1)
	{
		/* �X�e�[�W�̐��� */
		if (m_pStage == NULL)
		{
			m_pStage = new CStage1;
			m_pStage->Init();
			CSound::PlaySound(CSound::SOUND_LABEL_STAGE1);
		}
	}
	else if (CManager::GetStageSelect() == CManager::STAGESELECT_STAGE2)
	{
		/* �X�e�[�W�̐��� */
		if (m_pStage == NULL)
		{
			m_pStage = new CStage2;
			m_pStage->Init();
			CSound::PlaySound(CSound::SOUND_LABEL_STAGE2);
		}
	}
	else if (CManager::GetStageSelect() == CManager::STAGESELECT_STAGE3)
	{
		/* �X�e�[�W�̐��� */
		if (m_pStage == NULL)
		{
			m_pStage = new CStage3;
			m_pStage->Init();
			CSound::PlaySound(CSound::SOUND_LABEL_STAGE3);
		}
	}
	else if (CManager::GetStageSelect() == CManager::STAGESELECT_STAGE4)
	{
		/* �X�e�[�W�̐��� */
		if (m_pStage == NULL)
		{
			m_pStage = new CStage4;
			m_pStage->Init();
			CSound::PlaySound(CSound::SOUND_LABEL_STAGE4);
		}
	}

	/* �v���C���[�̐��� */
	if (m_pPlayer == NULL)
	{
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, 0.0f),CManager::GetCharactorSelect());
	}
	/* �X�R�A�̐��� */
	if (m_pScore == NULL)
	{
		m_pScore = CScore::Create(CScore::SCORETYPE_GAME);
	}

	/* Ui�̐��� */
	if (m_pUi == NULL)
	{
		m_pUi = CUi::Create();
	}

	CTime::Create();

	/* �|�[�Y�̐��� */
	if (m_pPause == NULL)
	{
		m_pPause = CPause::Create();
	}
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
	//�e�N�X�`���̔j��
	CPlayer::UnLoad();
	CBullet::UnLoad();
	CExplosion::UnLoad();
	CNumber::UnLoad();
	CEffect::UnLoad();
	CPause::UnLoad();
	CUi::UnLoad();
	CLifeGauge::UnLoad();
	CButton::UnLoad();
	CCutIn::UnLoad();
	COption::UnLoad();
	
	//BGM�̒�~
	if (CManager::GetStageSelect() == CManager::STAGESELECT_STAGE1)
	{
		CSound::StopSound(CSound::SOUND_LABEL_STAGE1);
	}
	else if (CManager::GetStageSelect() == CManager::STAGESELECT_STAGE2)
	{
		CSound::StopSound(CSound::SOUND_LABEL_STAGE2);
	}
	else if (CManager::GetStageSelect() == CManager::STAGESELECT_STAGE3)
	{
		CSound::StopSound(CSound::SOUND_LABEL_STAGE3);
	}
	else if (CManager::GetStageSelect() == CManager::STAGESELECT_STAGE4)
	{
		CSound::StopSound(CSound::SOUND_LABEL_STAGE4);
	}
	/* �e��|�C���^�̏����� */
	if (m_pPause != NULL)
	{//�|�[�Y
		m_pPause->Uninit();
		m_pPause = NULL;
	}
	if (m_pUi != NULL)
	{//Ui
		m_pUi->Uninit();
		m_pUi = NULL;
	}
	if (m_pScore != NULL)
	{//�X�R�A
		m_pScore->Uninit();
		m_pScore = NULL;
	}
	if (m_pPlayer != NULL)
	{//�v���C���[
		m_pPlayer->Uninit();
		m_pPlayer = NULL;
	}
	if (m_pStage != NULL)
	{//�X�e�[�W
		m_pStage->Uninit();
		m_pStage = NULL;
	}
	CScene::ReleaseAllFade();
}
//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	CFade::FADEMODE g_fade = CFade::GetFade();
	/* �L�[�{�[�h�̎擾 */
	CInputKeyBoard *pInput = NULL;
	XINPUT_STATE state;
	XInputGetState(0, &state);
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	bool bPause = CPause::GetPause();

	if (pInput == NULL)
	{
		pInput = CManager::GetInput();
	}

	if (pInput->GetKeyboardTrigger(DIK_P) == true || state.Gamepad.wButtons & XINPUT_GAMEPAD_START)
	{//�|�[�YON/OFF
		if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
		{
			bPause = bPause ? false : true;
			CPause::SetPause(bPause);
		}
		CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
	}

	if (m_pPause != NULL)
	{
		if (bPause == true)
		{
			m_pPause->Update();
		}
	}

	switch (m_GameState)
	{
	case GAMESTATE_NORMAL:
		break;

	case GAMESTATE_CLEAR:
		m_nCntState++;
		if (m_nCntState <= 60)
		{
			nCntFade++;
			if (nCntFade > 10)
			{
				if (g_fade != CFade::FADE_OUT)
				{
					//���[�h�ݒ�
					CFade::SetFade(CManager::MODE_CLEAR);
				}
			}
		}
		break;

	case GAMESTATE_OVER:
		m_nCntState++;
		if (m_nCntState <= 60)
		{
			nCntFade++;
			if (nCntFade > 10)
			{
				if (g_fade != CFade::FADE_OUT)
				{
					//���[�h�ݒ�
					CFade::SetFade(CManager::MODE_OVER);
				}
			}
		}
		break;
	}

	CDirectXInput::ResetInputJoyState(CDirectXInput::GetInputJoyState());
}
//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{

}
//=============================================================================
// �`�揈��
//=============================================================================
void CGame::SetGameState(GAMESTATE gamestate)
{
	m_GameState = gamestate;
	m_nCntState = 0;
}