//=============================================================================
//
// カーネリアン処理 [Karnerian.cpp]
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
#include "Karnerian.h"
#include "effectBase.h"
#include "fade.h"
#include "GameUi.h"
#include "cutinBase.h"
#include "optionBase.h"
#include "shield.h"
#include "MagicEffect.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
bool CKarnerian::m_bShield = false;

//*****************************************************************************
// ▽class CKarnerian
//*****************************************************************************
//=============================================================================
// コンストラクタ
//=============================================================================
CKarnerian::CKarnerian() { m_bShield = false; }
//=============================================================================
// デストラクタ
//=============================================================================
CKarnerian::~CKarnerian() {}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CKarnerian::Init(void)
{
	CPlayer::Init();
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CKarnerian::Uninit(void)
{
	CPlayer::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CKarnerian::Update(void)
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
		m_bShield = false;
		break;

	case PLAYERSKILL_NORMAL_TRUE:
		if (m_bShield == false)
		{
			COption::Create(COption::OPTIONTYPE_SHIELD, m_pos);
			m_bShield = true;
		}
		m_nCntSkillTime++;
		if (m_nCntSkillTime % 20 == 0)
		{
			CMagicEffect::SetMagicEffect(m_pos);
		}
		if (m_nCntSkillTime >= 180 || CShield::GetShieldEmergence() == false)
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
void CKarnerian::Draw(void)
{
	CPlayer::Draw();
}