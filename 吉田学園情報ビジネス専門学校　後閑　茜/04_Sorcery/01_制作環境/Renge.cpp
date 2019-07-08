//=============================================================================
//
// 蓮華処理 [Renge.cpp]
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
#include "Renge.h"
#include "effectBase.h"
#include "fade.h"
#include "uiBase.h"
#include "cutinBase.h"
#include "optionBase.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================

//*****************************************************************************
// ▽class CRenge
//*****************************************************************************
//=============================================================================
// コンストラクタ
//=============================================================================
CRenge::CRenge() {}
//=============================================================================
// デストラクタ
//=============================================================================
CRenge::~CRenge() {}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CRenge::Init(void)
{
	CPlayer::Init();
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CRenge::Uninit(void)
{
	CPlayer::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CRenge::Update(void)
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

	if ((pInput->GetKeyboardTrigger(DIK_SPACE) == true) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
	{
		if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
		{
			CBullet::Create(m_pos, CBullet::BULLETTYPE_PLAYER, BULLET_MOVE);
		}
		CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
	}

	switch (m_NormalSkillUse)
	{
	case PLAYERSKIL_NORMALL_FALSE:
		if (m_state == PLAYERSTATE_INVINCIBLE)
		{
			m_state = PLAYERSTATE_NONE;
		}
		break;

	case PLAYERSKILL_NORMAL_TRUE:
		m_nCntSkillTime++;
		if (m_state != PLAYERSTATE_INVINCIBLE)
		{
			m_state = PLAYERSTATE_INVINCIBLE;
		}
		if (m_nCntSkillTime >= 300)
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
// 描画処理
//=============================================================================
void CRenge::Draw(void)
{
	CPlayer::Draw();
}
