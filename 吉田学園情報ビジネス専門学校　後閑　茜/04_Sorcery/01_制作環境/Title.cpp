//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : 
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "Input.h"
#include "fade.h"
#include "title.h"
#include "bg.h"
#include "sound.h"

//*****************************************************************************
// グローバル変数/静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CTitle::m_pTexture[MAX_TEXTURE_TITLE] = {};
CBg *CTitle::m_pBG = NULL;
CScene2D *CTitle::m_apScene2D[MAX_TEXTURE_TITLE] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CTitle::CTitle()
{
	CSound::PlaySound(CSound::SOUND_LABEL_TITLE);
	m_State = PRESSSTATE_NONE;
	m_LogoState = LOGOSTATE_FADEIN;
	m_col = DEFALT_COL_WHITE;
	m_colLogo = DEFALT_COL_WHITE;
	m_fChangeAlpha = 0.05f;
	m_nCntFade = 0;
	m_nChangeMode = 0;
	m_nCntAnim = 0;
	m_nPatternAnim = 0;
	m_GraphicState = GRAPHICSTATE_ALPHA_0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CTitle::~CTitle()
{
	CSound::StopSound();
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitle::Init(void)
{
	CBg::Load();
	CTitle::Load();

	if (m_pBG == NULL)
	{
		m_pBG = new CBg;
		m_pBG->Create();
	}

	for (int nCnt = 0; nCnt < MAX_TEXTURE_TITLE; nCnt++)
	{
		if (nCnt == 0)
		{//ロゴ
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(300.0f, 150.0f, 0.0f), 270.0f, 150.0f);
			m_apScene2D[nCnt]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_TITLE);
		}
		else if (nCnt == 1)
		{//コンクリ
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(850.0f, 500.0f, 0.0f), 450.0f, 250.0f);
			m_apScene2D[nCnt]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_TITLE);
		}
		else if (nCnt == 2)
		{//キャラアニメ
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(950.0f, 480.0f, 0.0f), 250.0f, 200.0f);
			m_apScene2D[nCnt]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_TITLE);
			m_apScene2D[nCnt]->SetAnimX(2, 1, 0);
		}
		else
		{//PRESS_ENTER
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(220.0f, 280.0f, 0.0f), 150.0f, 30.0f);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_TITLE);
			m_apScene2D[nCnt]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}
	m_nCntFade = 0;
	m_nChangeMode = 0;
	m_nCntAnim = 0;
	m_nPatternAnim = 0;

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	CBg::UnLoad();
	CTitle::UnLoad();

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
void CTitle::Update(void)
{
	/* キーボードの取得 */
	CInputKeyBoard *pInput = NULL;
	CFade::FADEMODE g_fade = CFade::GetFade();
	XINPUT_STATE state;
	XInputGetState(0, &state);
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);
	m_nCntAnim++;

	if (pInput == NULL)
	{
		pInput = CManager::GetInput();
	}

	/* タイトルロゴの状態 */
	switch (m_LogoState)
	{
	case LOGOSTATE_NONE:
		m_apScene2D[0]->SetColor(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
		m_nChangeMode++;
		if (pInput->GetKeyboardPress(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
		{//Enter押下
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				m_State = PRESSSTATE_FLASHING;
				m_fChangeAlpha = 1.0f;
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}

		// 10秒経ったらランキングに移行
		if (m_nChangeMode >= 600)
		{
			if (g_fade != CFade::FADE_OUT)
			{
				//モード設定
				CFade::SetFade(CManager::MODE_RANKING);
			}
		}
		break;

	case LOGOSTATE_FADEIN:
		if (g_fade == CFade::FADE_NONE)
		{
			m_colLogo.a += 0.01f;
			m_apScene2D[0]->SetColor(m_colLogo);
			if (m_colLogo.a >= 1.0f)
			{
				m_LogoState = LOGOSTATE_NONE;
				m_GraphicState = GRAPHICSTATE_FADEIN;
				m_colLogo.a = 0.0f;
			}
		}
		if (pInput->GetKeyboardPress(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
		{
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				m_LogoState = LOGOSTATE_NONE;
				m_GraphicState = GRAPHICSTATE_NONE;
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}
		break;
	}

	/* グラフィックの状態 */
	switch (m_GraphicState)
	{
	case GRAPHICSTATE_NONE:
		if (m_nCntAnim % 30 == 0)
		{
			m_nPatternAnim++;
			m_apScene2D[2]->SetAnimX(2, 1, m_nPatternAnim);

			if (m_nPatternAnim >= MAX_TITLEANIM)
			{
				m_nPatternAnim = 0;
			}
		}
		m_apScene2D[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apScene2D[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		break;

	case GRAPHICSTATE_ALPHA_0:
		m_apScene2D[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_apScene2D[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		break;

	case GRAPHICSTATE_FADEIN:
		m_colLogo.a += 0.01f;
		m_apScene2D[1]->SetColor(m_colLogo);
		m_apScene2D[2]->SetColor(m_colLogo);
		if (m_colLogo.a >= 1.0f)
		{
			m_GraphicState = GRAPHICSTATE_NONE;
		}
		if (pInput->GetKeyboardPress(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
		{
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				m_GraphicState = GRAPHICSTATE_NONE;
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}
		break;
	}

	/* PRESS_ENTERの状態 */
	switch (m_State)
	{
	case PRESSSTATE_NONE:
		if (m_GraphicState == GRAPHICSTATE_NONE)
		{
			m_col.a += m_fChangeAlpha;
			if (m_col.a <= 0.0f || m_col.a >= 1.0f)
			{
				m_fChangeAlpha *= -1;
			}
			m_apScene2D[3]->SetColor(m_col);
		}
		break;

	case PRESSSTATE_FLASHING:
		if (m_LogoState == LOGOSTATE_NONE)
		{
			m_nCntFade++;
			if (m_nCntFade >= 60)
			{
				m_col.a += m_fChangeAlpha;
				if (m_col.a <= 0.0f || m_col.a >= 1.0f)
				{
					m_fChangeAlpha *= -1;
				}
				m_apScene2D[3]->SetColor(m_col);

				if (g_fade != CFade::FADE_OUT)
				{
					//モード設定
					CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
					CFade::SetFade(CManager::MODE_STAGESELECT);
				}
			}
		}
		break;
	}

	CDirectXInput::ResetInputJoyState(CDirectXInput::GetInputJoyState());
}
//=============================================================================
// 描画処理
//=============================================================================
void CTitle::Draw(void)
{

}
//=============================================================================
// テクスチャのロード
//=============================================================================
HRESULT CTitle::Load(void)
{
	CManager::MODE mode = CManager::GetMode();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLE_LOGO, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLE_CONCRETE, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLE_ANIMATION, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLE_PRESS, &m_pTexture[3]);

	return S_OK;
}
//=============================================================================
// テクスチャのアンロード
//=============================================================================
void CTitle::UnLoad(void)
{
	// テクスチャの破棄
	for (int nCnt = 0; nCnt < MAX_TEXTURE_TITLE; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}