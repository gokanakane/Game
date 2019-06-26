//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : 
//
//=============================================================================
#include "renderer.h"
#include "manager.h"
#include "scene2D.h"
#include "result.h"
#include "Input.h"
#include "bg.h"
#include "fade.h"
#include "sound.h"
#include "scoreBase.h"
#include "number.h"
//*****************************************************************************
// グローバル変数/静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CResult::m_pTexture[MAX_TEXTURERESULT] = {};
CBg *CResult::m_pBG = NULL;
bool CResult::m_MakeScore = false;
//=============================================================================
// コンストラクタ
//=============================================================================
CResult::CResult()
{
	for (int nCnt = 0; nCnt < MAX_TEXTURERESULT; nCnt++)
	{
		m_apScene2D[nCnt] = NULL;
	}
	m_nCntMode = 0;
	m_Logopos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_GoalLogopos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scorepos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_GoalScorepos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_LogoMove = 0.2f;
	m_LogoAlpha = 0.01f;
	m_ScoreMove = 0.2f;
	m_ScoreAlpha = 0.01f;
	m_Col = DEFALT_COL_WHITE;
	m_Scorecol = DEFALT_COL_WHITE;
	m_state = RESULTLOGOSTATE_FADEIN;

	switch (CManager::GetMode())
	{
	case CManager::MODE_CLEAR:
		CSound::PlaySound(CSound::SOUND_LABEL_GAMECLEAR);
		break;

	case CManager::MODE_OVER:
		CSound::PlaySound(CSound::SOUND_LABEL_GAMEOVER);
		break;
	}
}
//=============================================================================
// デストラクタ
//=============================================================================
CResult::~CResult()
{
	switch (CManager::GetMode())
	{
	case CManager::MODE_CLEAR:
		CSound::StopSound(CSound::SOUND_LABEL_GAMECLEAR);
		break;

	case CManager::MODE_OVER:
		CSound::StopSound(CSound::SOUND_LABEL_GAMEOVER);
		break;
	}

}
//=============================================================================
// 初期化処理
//=============================================================================
void CResult::Init(void)
{
	CBg::Load();
	CResult::Load();
	CNumber::Load();

	if (m_pBG == NULL)
	{
		m_pBG->Create();
	}
	for (int nCnt = 0; nCnt < MAX_TEXTURERESULT; nCnt++)
	{
		if (nCnt == 0)
		{
			m_apScene2D[nCnt] = new CScene2D(5);
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(300.0f, 90.0f, 0.0f), 300.0f, 100.0f);
			switch (CManager::GetMode())
			{
			case CManager::MODE_CLEAR:
				m_apScene2D[nCnt]->SetAnimY(1, 2, 0);
				break;
			case CManager::MODE_OVER:
				m_apScene2D[nCnt]->SetAnimY(1, 2, 1);
				break;
			}
			m_GoalLogopos = D3DXVECTOR3(300.0f, 100.0f, 0.0f);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_RESULT);
		}
		else if (nCnt == 1)
		{
			m_apScene2D[nCnt] = new CScene2D(5);
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(900.0f, 440.0f, 0.0f), 300.0f, 200.0f);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_RESULT);
			m_GoalScorepos = D3DXVECTOR3(900.0f, 450.0f, 0.0f);
		}
	}
}
//=============================================================================
// 終了処理
//=============================================================================
void CResult::Uninit(void)
{
	CBg::UnLoad();
	CResult::UnLoad();
	CNumber::UnLoad();

	if (m_pBG != NULL)
	{
		m_pBG->Uninit();
		m_pBG = NULL;
	}

	CScene::ReleaseAllFade();
}
//=============================================================================
// 更新処理
//=============================================================================
void CResult::Update(void)
{
	CFade::FADEMODE g_fade = CFade::GetFade();
	/* キーボードの取得 */
	CInputKeyBoard *pInput = NULL;
	XINPUT_STATE state;
	XInputGetState(0, &state);
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);
	m_nCntMode++;

	if (pInput == NULL)
	{
		pInput = CManager::GetInput();
	}

	switch (m_state)
	{
	case RESULTLOGOSTATE_NONE:
		m_apScene2D[0]->SetColor(m_Col);
		m_apScene2D[0]->SetPos(m_GoalLogopos);
		m_apScene2D[1]->SetColor(m_Scorecol);
		m_apScene2D[1]->SetPos(m_GoalScorepos);
		if (m_MakeScore == false)
		{
			CScore::Create(CScore::SCORETYPE_RESULT);
			m_MakeScore = true;
		}
		break;
	case RESULTLOGOSTATE_FADEIN:
		//ロゴ
		/* 移動 */
		m_Logopos = m_apScene2D[0]->GetPos();
		m_Logopos.y += m_LogoMove;
		m_apScene2D[0]->SetPos(m_Logopos);
		if (m_GoalLogopos.y <= m_Logopos.y)
		{
			m_apScene2D[0]->SetPos(m_GoalLogopos);
		}
		/* 色の更新 */
		m_Col.a += m_LogoAlpha;
		m_apScene2D[0]->SetColor(m_Col);
		if (m_Col.a >= 1.0f)
		{
			m_Col.a = 1.0f;
			m_apScene2D[0]->SetColor(m_Col);
		}
		//スコア板
		/* 移動 */
		m_Scorepos = m_apScene2D[1]->GetPos();
		m_Scorepos.y += m_LogoMove;
		m_apScene2D[1]->SetPos(m_Scorepos);
		if (m_GoalScorepos.y <= m_Scorepos.y)
		{
			m_apScene2D[1]->SetPos(m_GoalScorepos);
		}
		/* 色の更新 */
		m_Scorecol.a += m_ScoreAlpha;
		m_apScene2D[0]->SetColor(m_Scorecol);
		if (m_Scorecol.a >= 1.0f)
		{
			m_Scorecol.a = 1.0f;
			m_apScene2D[1]->SetColor(m_Scorecol);
			m_state = RESULTLOGOSTATE_NONE;
		}
		break;
	}

	if (pInput->GetKeyboardPress(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
	{//Enter押下
		if (g_fade != CFade::FADE_OUT)
		{
			CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			//モード設定
			CFade::SetFade(CManager::MODE_RANKING);
		}
	}
	if (m_nCntMode >= 600)
	{
		if (g_fade != CFade::FADE_OUT)
		{
			//モード設定
			CFade::SetFade(CManager::MODE_RANKING);
		}
	}

	CDirectXInput::ResetInputJoyState(CDirectXInput::GetInputJoyState());
}
//=============================================================================
// 描画処理
//=============================================================================
void CResult::Draw(void)
{

}
//=============================================================================
// テクスチャのロード
//=============================================================================
HRESULT CResult::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_RESULT_LOGO, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_RESULT_SCORE, &m_pTexture[1]);

	return S_OK;
}
//=============================================================================
// テクスチャのアンロード
//=============================================================================
void CResult::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXTURERESULT; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
