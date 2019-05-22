//=============================================================================
//
// �h���O�[������ [Doragon.cpp]
// Author : 
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
#include "Doragon.h"
#include "effectBase.h"
#include "magicEffect.h"
#include "fade.h"
#include "uiBase.h"
#include "cutinBase.h"
#include "optionBase.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================

//*****************************************************************************
// ��class CDragon
//*****************************************************************************
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CDoragon::CDoragon() {}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CDoragon::~CDoragon() {}
//=============================================================================
// ������
//=============================================================================
HRESULT CDoragon::Init(void)
{
	CPlayer::Init();
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CDoragon::Uninit(void)
{
	CPlayer::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CDoragon::Update(void)
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
		m_nCntSkillTime++;
		if (m_nCntSkillTime % 20 == 0)
		{
			CMagicEffect::SetMagicEffect(m_pos);
		}
		/* �e���� */
		if (pInput->GetKeyboardTrigger(DIK_SPACE) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
		{
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				CBullet::Create(m_pos, CBullet::BULLETTYPE_PLAYER, BULLET_MOVE);
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 30.0f, 0.0f), CBullet::BULLETTYPE_PLAYER, BULLET_MOVE);
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, 0.0f), CBullet::BULLETTYPE_PLAYER, BULLET_MOVE);
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}
		if (m_nCntSkillTime >= 150)
		{
			m_NormalSkillUse = PLAYERSKIL_NORMALL_FALSE;
			m_nCntSkillTime = 0;
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
void CDoragon::Draw(void)
{
	CPlayer::Draw();
}
