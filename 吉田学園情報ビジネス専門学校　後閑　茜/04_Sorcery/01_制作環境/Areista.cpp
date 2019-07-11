//=============================================================================
//
// アレイスタ処理 [Areista.cpp]
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
#include "Areista.h"
#include "effectBase.h"
#include "fade.h"
#include "uiBase.h"
#include "cutinBase.h"
#include "optionBase.h"
#include "MagicEffect.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================

//*****************************************************************************
// ▽class CAreista
//*****************************************************************************
//=============================================================================
// コンストラクタ
//=============================================================================
CAreista::CAreista() {}
//=============================================================================
// デストラクタ
//=============================================================================
CAreista::~CAreista() {}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CAreista::Init(void)
{
	CPlayer::Init();
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CAreista::Uninit(void)
{
	CPlayer::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CAreista::Update(void)
{
	XINPUT_STATE state;
	XInputGetState(0, &state);
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	/* キーボードの取得 */
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
		if ((pInput->GetKeyboardTrigger(DIK_SPACE) == true) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
		{
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				CBullet::Create(m_pos, CBullet::BULLETTYPE_DRAIN, BULLET_MOVE);
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}
		if (m_nCntSkillTime >= 120)
		{
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
// 描画処理
//=============================================================================
void CAreista::Draw(void)
{
	CPlayer::Draw();
}