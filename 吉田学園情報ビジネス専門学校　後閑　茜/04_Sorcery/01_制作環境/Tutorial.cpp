//=============================================================================
//
// タイトル処理 [Tutorial.cpp]
// Author : 
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "fade.h"
#include "sound.h"
#include "tutorial.h"
#include "Input.h"
#include "bg.h"
#include "playerBase.h"
#include "enemyBase.h"
#include "bullet.h"
#include "effectBase.h"
#include "Explosion.h"
#include "uiBase.h"
#include "Button.h"
#include "TutorialUI.h"
#include "cutinBase.h"
#include "optionBase.h"

//*****************************************************************************
// グローバル変数/静的メンバ変数
//*****************************************************************************
CBg *CTutorial::m_pBG = NULL;
LPDIRECT3DTEXTURE9 CTutorial::m_pTexture[MAX_TUTORIALTEX] = {};
CTutorial::NarratorState CTutorial::m_state = NARRATORSTATE_STEP1;
CTutorial::MaskAlphaState CTutorial::m_MaskState = CTutorial::MASKALPHASTATE_NONE;
CTutorial::LectureState CTutorial::m_LectureState = CTutorial::LECTURESTATE_NONE;
CTutorial::CharactorSkillState CTutorial::m_CharactorSkill = CTutorial::CHARACTORSKILLSTATE_NONE;
bool CTutorial::m_bMake = false;
bool CTutorial::m_ButtonMake = false;
bool CTutorial::m_SkillUse = false;
bool CTutorial::m_bdisplay = false;

//=============================================================================
// コンストラクタ
//=============================================================================
CTutorial::CTutorial()
{
	CSound::PlaySound(CSound::SOUND_LABEL_TUTORIAL);
	m_fChangeAlpha = 0.05f;
	m_fMaskAlpha = 0.05f;
	m_fLectureAlpha = 0.15f;
	m_fLecturepos = 0.5f;
	m_col = DEFALT_COL_WHITE;
	m_MaskCol = DEFALT_COL_BLACK;
	m_LectureCol = DEFALT_COL_WHITE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Goalpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_StartPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = NARRATORSTATE_STEP1;
	m_bMake = false;
	m_ButtonMake = false;
	m_SkillUse = false;
	m_bdisplay = false;
	m_nCntRandomEnemyMake = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CTutorial::~CTutorial()
{
	CSound::StopSound(CSound::SOUND_LABEL_TUTORIAL);
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTutorial::Init(void)
{
	CBg::Load();
	CTutorial::Load();
	CTutorialUi::Load();
	CPlayer::Load();
	CEnemy::Load();
	CBullet::Load();
	CEffect::Load();
	CExplosion::Load();
	CButton::Load();
	CCutIn::Load();
	COption::Load();

	if (m_pBG == NULL)
	{
		m_pBG->Create();
	}

	for (int nCnt = 0; nCnt < MAXTUTORIALPOLYGON; nCnt++)
	{
		if (nCnt == 0)
		{//説明出すときのマスク
			m_apScene2D[nCnt] = new CScene2D(5);
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			m_apScene2D[nCnt]->SetColor(DEFALT_COL_BLACK);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_TUTORIAL);
		}
		if (nCnt == 1)
		{//字幕
			m_apScene2D[nCnt] = new CScene2D(6);
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt-1]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(730.0f, 100.0f, 0.0f), 580.0f, 100.0f);
			m_apScene2D[nCnt]->SetAnimY(1, 13, 0);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_TUTORIAL);
		}
		if (nCnt == 2)
		{//ナレーター
			m_apScene2D[nCnt] = new CScene2D(6);
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt-1]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(130.0f, 100.0f, 0.0f), 100.0f, 100.0f);
			m_apScene2D[nCnt]->SetAnimY(1, 5, 0);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_TUTORIAL);
		}
		if (nCnt == 3)
		{//案内人
			m_apScene2D[nCnt] = new CScene2D(6);
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt-1]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(130.0f, 180.0f, 0.0f), 50.0f, 30.0f);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_TUTORIAL);
		}
		if (nCnt == 4)
		{//スキップ
			m_apScene2D[nCnt] = new CScene2D(6);
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt-1]);
			m_apScene2D[nCnt]->SetColor(m_col);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(500.0f, 190.0f, 0.0f), 250.0f, 30.0f);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_TUTORIAL);
		}
		if (nCnt == 5)
		{//補足説明
			m_apScene2D[nCnt] = new CScene2D(6);
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt - 1]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(660.0f, 440.0f, 0.0f), 400.0f, 220.0f);
			m_apScene2D[nCnt]->SetColor(m_col);
			m_apScene2D[nCnt]->SetAnimY(1, 3, 0);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_TUTORIAL);
			m_Goalpos = D3DXVECTOR3(660.0f, 450.0f, 0.0f);
			m_StartPos = D3DXVECTOR3(660.0f, 440.0f, 0.0f);
		}
		if (nCnt == 6)
		{//キャラ別データ
			m_apScene2D[nCnt] = new CScene2D(6);
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt - 1]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(660.0f, 440.0f, 0.0f), 400.0f, 220.0f);
			m_apScene2D[nCnt]->SetColor(m_col);
			m_apScene2D[nCnt]->SetAnimY(1, 6, 0);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_TUTORIAL);
			m_Goalpos = D3DXVECTOR3(660.0f, 450.0f, 0.0f);
			m_StartPos = D3DXVECTOR3(660.0f, 440.0f, 0.0f);
		}
	}

	CTutorialUi::Create(CTutorialUi::TUTORIALUITYPE_ENTER_OR_A);

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CTutorial::Uninit(void)
{
	CBg::UnLoad();
	CTutorial::UnLoad();
	CTutorialUi::UnLoad();
	CPlayer::UnLoad();
	CEnemy::UnLoad();
	CBullet::UnLoad();
	CEffect::UnLoad();
	CExplosion::UnLoad();
	CButton::UnLoad();
	CCutIn::UnLoad();
	COption::UnLoad();

	if (m_pBG != NULL)
	{
		m_pBG->Uninit();
		m_pBG = NULL;
	}

	//m_apScene2Dを破棄
	for (int nCnt = 0; nCnt < MAXTUTORIALPOLYGON; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt]->Uninit();
		}
	}

	CScene::ReleaseAllFade();
}
//=============================================================================
// 更新処理
//=============================================================================
void CTutorial::Update(void)
{
	/* キーボードの取得 */
	CInputKeyBoard *pInput = NULL;
	CFade::FADEMODE g_fade = CFade::GetFade();
	XINPUT_STATE state;
	XInputGetState(0, &state);
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	if (pInput == NULL)
	{
		pInput = CManager::GetInput();
	}

	/* 字幕の更新 */
	m_apScene2D[1]->SetAnimY(1, 13, m_state);

	/* ナレーターのステップ */
	switch (m_state)
	{
	case NARRATORSTATE_STEP1:				//挨拶
		m_apScene2D[2]->SetAnimY(1, 5, 0);
		if (pInput->GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A && CDirectXInput::GetConnectionJoypad() == true))
		{//Enter押下
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				CSound::PlaySound(CSound::SOUND_LABEL_SE_CURSOR);
				m_state = NARRATORSTATE_STEP2;
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}
		break;

	case NARRATORSTATE_STEP2:				//スキップについて
		m_apScene2D[2]->SetAnimY(1, 5, 3);
		if (m_bMake == false)
		{
			CPlayer::Create(D3DXVECTOR3(300.0f, SCREEN_HEIGHT / 2, 0.0f), CManager::GetCharactorSelect());
			m_bMake = true;
		}
		if (pInput->GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A && CDirectXInput::GetConnectionJoypad() == true))
		{//Enter押下
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				CSound::PlaySound(CSound::SOUND_LABEL_SE_CURSOR);
				m_state = NARRATORSTATE_STEP3;
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}
		break;

	case NARRATORSTATE_STEP3:				//移動について
		m_apScene2D[2]->SetAnimY(1, 5, 0);
		if (m_bMake == true)
		{
			m_bMake = false;
		}
		if (pInput->GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A && CDirectXInput::GetConnectionJoypad() == true))
		{//Enter押下
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				CSound::PlaySound(CSound::SOUND_LABEL_SE_CURSOR);
				m_state = NARRATORSTATE_STEP4;
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}
		break;

	case NARRATORSTATE_STEP4:				//敵について
		if (m_bMake == false)
		{
			CEnemy::Create(D3DXVECTOR3(800.0f, SCREEN_HEIGHT / 2, 0.0f), CEnemy::ENEMYTYPE_TUTORIAL,1);
			m_bMake = true;
		}
		m_apScene2D[2]->SetAnimY(1, 5, 4);

		if (pInput->GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A && CDirectXInput::GetConnectionJoypad() == true))
		{//Enter押下
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				CSound::PlaySound(CSound::SOUND_LABEL_SE_CURSOR);
				m_state = NARRATORSTATE_STEP5;
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}
		break;

	case NARRATORSTATE_STEP5:				//弾発射について
		m_apScene2D[2]->SetAnimY(1, 5, 0);
		if (m_bMake == false)
		{
			m_nCntRandomEnemyMake++;
			if (m_nCntRandomEnemyMake >= 30)
			{
				float posX = float(rand() % 600 + 500);
				float posY = float(rand() % 300 + 200);
				CEnemy::Create(D3DXVECTOR3(posX, posY, 0.0f), CEnemy::ENEMYTYPE_TUTORIAL,1);
				m_bMake = true;
				m_nCntRandomEnemyMake = 0;
			}
		}
		if (pInput->GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A && CDirectXInput::GetConnectionJoypad() == true))
		{//Enter押下
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				CSound::PlaySound(CSound::SOUND_LABEL_SE_CURSOR);
				m_state = NARRATORSTATE_STEP6;
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}
		break;

	case NARRATORSTATE_STEP6:				//スコアについて
		if (m_bdisplay == false)
		{
			m_MaskState = MASKALPHASTATE_FADEIN;
			m_LectureState = LECTURESTATE_APPEARANCE;
			m_bdisplay = true;
		}
		m_apScene2D[2]->SetAnimY(1, 5, 1);
		if (pInput->GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A && CDirectXInput::GetConnectionJoypad() == true))
		{//Enter押下
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				CSound::PlaySound(CSound::SOUND_LABEL_SE_CURSOR);
				m_state = NARRATORSTATE_STEP7;
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}
		break;

	case NARRATORSTATE_STEP7:				//体力について
		m_apScene2D[2]->SetAnimY(1, 5, 2);
		m_apScene2D[5]->SetAnimY(1, 3, 1);
		if (m_bMake == true)
		{
			m_bMake = false;
		}
		if (pInput->GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A && CDirectXInput::GetConnectionJoypad() == true))
		{//Enter押下
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				CSound::PlaySound(CSound::SOUND_LABEL_SE_CURSOR);
				m_state = NARRATORSTATE_STEP8;
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}
		break;

	case NARRATORSTATE_STEP8:				//運命線について
		m_apScene2D[2]->SetAnimY(1, 5, 0);
		m_apScene2D[5]->SetAnimY(1, 3, 2);
		if (pInput->GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A && CDirectXInput::GetConnectionJoypad() == true))
		{//Enter押下
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				CSound::PlaySound(CSound::SOUND_LABEL_SE_CURSOR);
				m_state = NARRATORSTATE_STEP9;
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}
		break;

	case NARRATORSTATE_STEP9:				//魔法について
		m_apScene2D[2]->SetAnimY(1, 5, 0);
		if (m_bdisplay == true)
		{
			m_MaskState = MASKALPHASTATE_FADEOUT;
			m_LectureState = LECTURESTATE_EXIT;
			m_bdisplay = false;
		}
		if (m_bMake == false)
		{
			float posX = float(rand() % 600 + 500);
			float posY = float(rand() % 300 + 200);
			CEnemy::Create(D3DXVECTOR3(posX, posY, 0.0f), CEnemy::ENEMYTYPE_TUTORIAL,1);
			m_bMake = true;
		}
		if (m_ButtonMake == false)
		{
			CButton::Create(CUi::BUTTONTYPE_NORMAL);
			m_ButtonMake = true;
		}
		if (m_SkillUse == true)
		{
			m_state = NARRATORSTATE_STEP10;
			m_SkillUse = false;
		}
		break;

	case NARRATORSTATE_STEP10:				//魔法の注意事項
		m_apScene2D[2]->SetAnimY(1, 5, 2);
		if (m_bdisplay == false)
		{
			m_MaskState = MASKALPHASTATE_FADEIN;
			m_CharactorSkill = CHARACTORSKILLSTATE_APPEARANCE;
 			m_bdisplay = true;
		}
		if (m_bMake == true)
		{
			m_bMake = false;
		}
		if (pInput->GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A && CDirectXInput::GetConnectionJoypad() == true))
		{//Enter押下
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				CSound::PlaySound(CSound::SOUND_LABEL_SE_CURSOR);
				m_state = NARRATORSTATE_STEP11;
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}
		break;

	case NARRATORSTATE_STEP11:				//ポーズについて
		m_apScene2D[2]->SetAnimY(1, 5, 0);
		if (m_bdisplay == true)
		{
			m_MaskState = MASKALPHASTATE_FADEOUT;
			m_CharactorSkill = CHARACTORSKILLSTATE_EXIT;
			m_bdisplay = false;
		}
		if (pInput->GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A && CDirectXInput::GetConnectionJoypad() == true))
		{//Enter押下
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				CSound::PlaySound(CSound::SOUND_LABEL_SE_CURSOR);
				m_state = NARRATORSTATE_STEP12;
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}
		break;

	case NARRATORSTATE_STEP12:				//困ったら見てね
		m_apScene2D[2]->SetAnimY(1, 5, 2);
		if (pInput->GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A && CDirectXInput::GetConnectionJoypad() == true))
		{//Enter押下
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				CSound::PlaySound(CSound::SOUND_LABEL_SE_CURSOR);

				m_state = NARRATORSTATE_STEP13;
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}
		break;
			
	case NARRATORSTATE_STEP13:				//行ってらっしゃい
		m_apScene2D[2]->SetAnimY(1, 5, 1);
		if (pInput->GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A && CDirectXInput::GetConnectionJoypad() == true))
		{//Enter押下
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
				//モード設定
				CFade::SetFade(CManager::MODE_GAME);
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}
		break;
	}
	if (pInput->GetKeyboardTrigger(DIK_L) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_START && CDirectXInput::GetConnectionJoypad() == true))
	{//Enter押下
		if (g_fade != CFade::FADE_OUT)
		{
			CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			//モード設定
			CFade::SetFade(CManager::MODE_GAME);
		}
	}
	/* マスクのフェードイン・アウト */
	switch (m_MaskState)
	{
	case MASKALPHASTATE_NONE:
		break;

	case MASKALPHASTATE_FADEIN:
 		m_MaskCol.a += m_fMaskAlpha;
		m_apScene2D[0]->SetColor(m_MaskCol);

		if (m_MaskCol.a >= 0.8f)
		{//マスクが表示された
			m_MaskCol.a = 0.8f;
			m_MaskState = MASKALPHASTATE_NONE;
		}
		break;

	case MASKALPHASTATE_FADEOUT:

		m_MaskCol.a -= m_fMaskAlpha;
		m_apScene2D[0]->SetColor(m_MaskCol);

		if (m_MaskCol.a <= 0.0f)
		{//マスクが表示された
			m_MaskCol.a = 0.0f;
			m_MaskState = MASKALPHASTATE_NONE;
		}
		break;
	}

	/* 説明文の状態 */
	switch (m_LectureState)
	{
	case LECTURESTATE_NONE:
		break;

	case LECTURESTATE_APPEARANCE:		//登場
		/* 位置の更新 */
		m_pos = m_apScene2D[5]->GetPos();
		m_pos.y += m_fLecturepos;
		m_apScene2D[5]->SetPos(m_pos);
		if (m_Goalpos.y <= m_pos.y)
		{
			m_apScene2D[5]->SetPos(m_Goalpos);
		}

		/* 色の更新 */
		m_LectureCol.a += m_fLectureAlpha;
		m_apScene2D[5]->SetColor(m_LectureCol);
		if (m_LectureCol.a >= 1.0f)
		{
			m_LectureCol.a = 1.0f;
			m_apScene2D[5]->SetColor(m_LectureCol);
			m_LectureState = LECTURESTATE_NONE;
		}
		break;

	case LECTURESTATE_EXIT:				//退場
		/* 位置の更新 */
		m_pos = m_apScene2D[5]->GetPos();
		m_pos.y -= m_fLecturepos;
		m_apScene2D[5]->SetPos(m_pos);
		if (m_StartPos.y >= m_pos.y)
		{
			m_apScene2D[5]->SetPos(m_StartPos);
		}
		/* 色の更新 */
		m_LectureCol.a -= m_fLectureAlpha;
		m_apScene2D[5]->SetColor(m_LectureCol);
		if (m_LectureCol.a <= 0.0f)
		{
			m_LectureCol.a = 0.0f;
			m_apScene2D[5]->SetColor(m_LectureCol);
			m_LectureState = LECTURESTATE_NONE;
		}
		break;
	}
	/* キャラクタースキルの状態 */
	switch (m_CharactorSkill)
	{
	case CHARACTORSKILLSTATE_NONE:
		break;

	case CHARACTORSKILLSTATE_APPEARANCE:		//登場
		/* 位置の更新 */
		m_apScene2D[6]->SetAnimY(1, 6, CManager::GetCharactorSelect() - 1);
		m_pos = m_apScene2D[6]->GetPos();
		m_pos.y += m_fLecturepos;
		m_apScene2D[6]->SetPos(m_pos);
		if (m_Goalpos.y <= m_pos.y)
		{
			m_apScene2D[6]->SetPos(m_Goalpos);
		}

		/* 色の更新 */
		m_LectureCol.a += m_fLectureAlpha;
		m_apScene2D[6]->SetColor(m_LectureCol);
		if (m_LectureCol.a >= 1.0f)
		{
			m_LectureCol.a = 1.0f;
			m_apScene2D[6]->SetColor(m_LectureCol);
			m_CharactorSkill = CHARACTORSKILLSTATE_NONE;
		}
		break;

	case CHARACTORSKILLSTATE_EXIT:				//退場
		/* 位置の更新 */
		m_pos = m_apScene2D[6]->GetPos();
		m_pos.y -= m_fLecturepos;
		m_apScene2D[6]->SetPos(m_pos);
		if (m_StartPos.y >= m_pos.y)
		{
			m_apScene2D[6]->SetPos(m_StartPos);
		}
		/* 色の更新 */
		m_LectureCol.a -= m_fLectureAlpha;
		m_apScene2D[6]->SetColor(m_LectureCol);
		if (m_LectureCol.a <= 0.0f)
		{
			m_LectureCol.a = 0.0f;
			m_apScene2D[6]->SetColor(m_LectureCol);
			m_CharactorSkill = CHARACTORSKILLSTATE_NONE;
		}
		break;
	}

	m_col.a += m_fChangeAlpha;

	if (m_col.a <= 0.0f || m_col.a >= 1.0f)
	{
		m_fChangeAlpha *= -1;
	}
	m_apScene2D[4]->SetColor(D3DXCOLOR(1.0f,1.0f,1.0f,m_col.a));

	CDirectXInput::ResetInputJoyState(CDirectXInput::GetInputJoyState());
}
//=============================================================================
// 描画処理
//=============================================================================
void CTutorial::Draw(void)
{

}
//=============================================================================
// テクスチャのロード
//=============================================================================
HRESULT CTutorial::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	D3DXCreateTextureFromFile(pDevice, TEXTURE_DESXRIPTIONBOOK, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NARRATOR, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NARRATORSUBTITLE, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_SKIP, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_LECTURE, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_CHARACTORSKILL, &m_pTexture[5]);

	return S_OK;
}
//=============================================================================
// テクスチャのアンロード
//=============================================================================
void CTutorial::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_TUTORIALTEX; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}