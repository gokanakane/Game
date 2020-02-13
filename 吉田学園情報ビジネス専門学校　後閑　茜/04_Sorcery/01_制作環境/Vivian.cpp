//=============================================================================
//
// �r�r�A������ [Vivian.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "Input.h"
#include "scene2D.h"
#include "tutorial.h"
#include "bullet.h"
#include "playerBase.h"
#include "Vivian.h"
#include "effectBase.h"
#include "fade.h"
#include "uiBase.h"
#include "cutinBase.h"
#include "optionBase.h"
#include "abyssgate.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================

//*****************************************************************************
// ��class CVivian
//*****************************************************************************
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CVivian::CVivian() {}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CVivian::~CVivian() {}
//=============================================================================
// ������
//=============================================================================
HRESULT CVivian::Init(void)
{
	CPlayer::Init();
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CVivian::Uninit(void)
{
	CPlayer::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CVivian::Update(void)
{
	XINPUT_STATE state;
	XInputGetState(0, &state);
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	/* �L�[�{�[�h�̎擾 */
	CInputKeyBoard *pInput = NULL;

	if (pInput == NULL)
	{
		pInput = CManager::GetInput();
	}

	switch (m_NormalSkillUse)
	{
	case PLAYERSKIL_NORMALL_FALSE:
		CAbyssGate::SetAbyssGateEmergence(false);
		if ((pInput->GetKeyboardTrigger(DIK_SPACE) == true) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
		{
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				CBullet::Create(m_pos, CBullet::BULLETTYPE_PLAYER, BULLET_MOVE);
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}
		break;

	case PLAYERSKILL_NORMAL_TRUE:
		if (CAbyssGate::GetAbyssGateEmergence() == false)
		{
			COption::Create(COption::OPTIONTYPE_ABYSSGATE, m_pos);
			CAbyssGate::SetAbyssGateEmergence(true);
			m_NormalSkillUse = PLAYERSKIL_NORMALL_FALSE;
			if (CManager::GetMode() == CManager::MODE_TUTORIAL)
			{
				CTutorial::SetSkillUSe(true);
			}
		}
		break;
	}
	switch (m_KIWAMESkillUse)
	{
	case PLAYERSKILL_KIWAME_FALSE:
		break;

	case PLAYERSKILL_KIWAME_TRUE:
		break;
	}

	CPlayer::Update();
}
//=============================================================================
// �`�揈��
//=============================================================================
void CVivian::Draw(void)
{
	CPlayer::Draw();
}