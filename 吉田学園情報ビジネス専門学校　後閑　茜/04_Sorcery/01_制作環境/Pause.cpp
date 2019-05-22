//=============================================================================
//
// 背景処理 [Pause.cpp]
// Author : 
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "fade.h"
#include "Input.h"
#include "Pause.h"
#include "enemyBase.h"
#include "sound.h"
//=============================================================================
// 静的メンバ変数
//=============================================================================
bool CPause::m_bPause = false;
LPDIRECT3DTEXTURE9 CPause::m_pTexture[MAX_PAUSETEXTURE] = {};
int CPause::m_nSelectNum = 0;
CScene2D *CPause::m_apScene2D[MAX_PAUSEPOLYGON] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CPause::CPause():CScene(5)
{
	for (int nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		m_posOld[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	m_PauseCol = PAUSECOL_NONE;
	m_fCntMove = 0;
	m_fChengeMove = 0.0f;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//=============================================================================
// デストラクタ
//=============================================================================
CPause::~CPause()
{

}
//=============================================================================
// 背景の生成
//=============================================================================
CPause *CPause::Create(void)
{
	CPause *pPause = NULL;

	if (pPause == NULL)
	{
		pPause = new CPause;
		pPause->Init();
	}
	m_bPause = false;

	//オブジェクトの種類の設定
	pPause->SetObjtype(CScene::OBJTYPE_PAUSE);

	return pPause;
}
//=============================================================================
// 背景の初期化処理
//=============================================================================
HRESULT CPause::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_PAUSEPOLYGON; nCnt++)
	{
		if (nCnt == 0)
		{//マスク
			m_apScene2D[nCnt] = new CScene2D(5);
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			m_apScene2D[nCnt]->SetColor(PAUSE_MASK);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_PAUSE);
		}
		else if (nCnt == 1)
		{//背景
			m_apScene2D[nCnt] = new CScene2D(5);
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), PAUSE_WIDTH, PAUSE_HEIGHT);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_PAUSE);
		}
		else if (nCnt >= 2 && nCnt <= 4)
		{//コンテニュー・クイット・リトライ
			m_apScene2D[nCnt] = new CScene2D(5);
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[2]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(500.0f, 230.0f + (120.0f*(nCnt - 2)), 0.0f), 120.0f, 50.0f);
			m_apScene2D[nCnt]->SetAnimY(1, MAX_PAUSEMENU, nCnt-2);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_PAUSE);
			m_posOld[nCnt-2] = m_apScene2D[nCnt]->GetPos();

		}
		else
		{//ステージセレクト・キャラクターセレクト
			m_apScene2D[nCnt] = new CScene2D(5);
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[2]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(780.0f, 320.0f + 120.0f*(nCnt - 5), 0.0f), 120.0f, 50.0f);
			m_apScene2D[nCnt]->SetAnimY(1, MAX_PAUSEMENU, nCnt - 2);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_PAUSE);
			m_posOld[nCnt-2] = m_apScene2D[nCnt]->GetPos();
		}
	}

	m_nSelectNum = 0;
	m_PauseCol = PAUSECOL_NONE;
	m_fCntMove = 0.1f;
	m_fChengeMove = 0.1f;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}

//=============================================================================
// 背景の終了処理
//=============================================================================
void CPause::Uninit(void)
{
	//m_apScene2Dを破棄（ポリゴンが破棄されただけでPause自体は破棄されていない）
	for (int nCnt = 0; nCnt < MAX_PAUSETEXTURE; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt]->Uninit();
		}
	}

	//Pauseを破棄
	Release();
}
//=============================================================================
// 背景の更新処理
//=============================================================================
void CPause::Update(void)
{
	CFade::FADEMODE fade = CFade::GetFade();
	CInputKeyBoard *pInput = NULL;
	XINPUT_STATE state;
	XInputGetState(0, &state);
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	if (pInput == NULL)
	{
		pInput = CManager::GetInput();
	}

	if (m_bPause == true)
	{
		//選択処理
		if (pInput->GetKeyboardTrigger(DIK_S) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN && CDirectXInput::GetConnectionJoypad() == true))
		{
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				m_nSelectNum = (m_nSelectNum + 1) % 5;
				CSound::PlaySound(CSound::SOUND_LABEL_SE_CURSOR);
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}

		if (pInput->GetKeyboardTrigger(DIK_W) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP && CDirectXInput::GetConnectionJoypad() == true))
		{
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				m_nSelectNum = (m_nSelectNum + 4) % 5;
				CSound::PlaySound(CSound::SOUND_LABEL_SE_CURSOR);
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}

		//選択された場所の処理
		if (m_nSelectNum == 0)
		{//コンテニュー
			m_PauseCol = PAUSECOL_CONTINUE;
			SetMove(m_nSelectNum + 2);

			if (pInput->GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
			{
				if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
				{
					if (fade != CFade::FADE_OUT)
					{
						CEnemy::SetFinishGame(true);
						CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
						m_PauseType = PAUSETYPE_CONTINUE;
					}
				}
				CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
			}
		}
		if (m_nSelectNum == 1)
		{//クイット
			m_PauseCol = PAUSECOL_QUIT;
			SetMove(m_nSelectNum + 2);

			if (pInput->GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
			{
				if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
				{
					if (fade != CFade::FADE_OUT)
					{
						CEnemy::SetFinishGame(true);
						CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
						m_PauseType = PAUSETYPE_QUIT;
					}
				}
				CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
			}
		}
		if (m_nSelectNum == 2)
		{//リトライ
			m_PauseCol = PAUSECOL_RETRY;
			SetMove(m_nSelectNum + 2);


			if (pInput->GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
			{
				if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
				{
					if (fade != CFade::FADE_OUT)
					{
						CEnemy::SetFinishGame(true);
						CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
						m_PauseType = PAUSETYPE_RETRY;
					}
					CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
				}

			}
		}
		if (m_nSelectNum == 3)
		{//ステージセレクト
			m_PauseCol = PAUSECOL_STAGESELECT;
			SetMove(m_nSelectNum + 2);

			if (pInput->GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
			{
				if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
				{
					if (fade != CFade::FADE_OUT)
					{
						CEnemy::SetFinishGame(true);
						CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
						m_PauseType = PAUSETYPE_STAGESELECT;
					}
					CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
				}
			}
		}
		if (m_nSelectNum == 4)
		{//キャラセレクト
			m_PauseCol = PAUSECOL_CHARACTORSELECT;
			SetMove(m_nSelectNum + 2);

			if (pInput->GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
			{
				if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
				{
					if (fade != CFade::FADE_OUT)
					{
						CEnemy::SetFinishGame(true);
						CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
						m_PauseType = PAUSETYPE_CHARACTORSELECT;
					}
					CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
				}
			}
		}
		//色と座標の設定
		switch (m_PauseCol)
		{
		case PAUSECOL_NONE:
			break;

		case PAUSECOL_CONTINUE:
			m_apScene2D[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apScene2D[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[3]->SetPos(m_posOld[1]);
			m_apScene2D[4]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[4]->SetPos(m_posOld[2]);
			m_apScene2D[5]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[5]->SetPos(m_posOld[3]);
			m_apScene2D[6]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[6]->SetPos(m_posOld[4]);
			break;

		case PAUSECOL_QUIT:
			m_apScene2D[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[2]->SetPos(m_posOld[0]);
			m_apScene2D[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apScene2D[4]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[4]->SetPos(m_posOld[2]);
			m_apScene2D[5]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[5]->SetPos(m_posOld[3]);
			m_apScene2D[6]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[6]->SetPos(m_posOld[4]);
			break;

		case PAUSECOL_RETRY:
			m_apScene2D[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[2]->SetPos(m_posOld[0]);
			m_apScene2D[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[3]->SetPos(m_posOld[1]);
			m_apScene2D[4]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apScene2D[5]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[5]->SetPos(m_posOld[3]);
			m_apScene2D[6]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[6]->SetPos(m_posOld[4]);
			break;

		case PAUSECOL_STAGESELECT:
			m_apScene2D[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[2]->SetPos(m_posOld[0]);
			m_apScene2D[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[3]->SetPos(m_posOld[1]);
			m_apScene2D[4]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[4]->SetPos(m_posOld[2]);
			m_apScene2D[5]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apScene2D[6]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[6]->SetPos(m_posOld[4]);
			break;

		case PAUSECOL_CHARACTORSELECT:
			m_apScene2D[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[2]->SetPos(m_posOld[0]);
			m_apScene2D[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[3]->SetPos(m_posOld[1]);
			m_apScene2D[4]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[4]->SetPos(m_posOld[2]);
			m_apScene2D[5]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[5]->SetPos(m_posOld[3]);
			m_apScene2D[6]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		}

		/* ポーズのタイプ別処理 */
		switch (m_PauseType)
		{
		case PAUSETYPE_NONE:
			break;

		case PAUSETYPE_CONTINUE:
			m_PauseType = PAUSETYPE_NONE;
			SetPause(false);
			break;

		case PAUSETYPE_QUIT:
			m_PauseType = PAUSETYPE_NONE;
			CFade::SetFade(CManager::MODE_TITLE);
			break;

		case PAUSETYPE_RETRY:
			m_PauseType = PAUSETYPE_NONE;
			CFade::SetFade(CManager::MODE_GAME);
			break;

		case PAUSETYPE_STAGESELECT:
			m_PauseType = PAUSETYPE_NONE;
			CFade::SetFade(CManager::MODE_STAGESELECT);
			break;

		case PAUSETYPE_CHARACTORSELECT:
			m_PauseType = PAUSETYPE_NONE;
			CFade::SetFade(CManager::MODE_CHARACTORSELECT);
			break;
		}
	}
	else
	{
		m_nSelectNum = 0;
	}
}
//=============================================================================
// 背景の描画処理
//=============================================================================
void CPause::Draw(void)
{

}
//=============================================================================
// 背景の表示状況の表示
//=============================================================================
void CPause::SetPause(bool bPause)
{
	m_bPause = bPause;
}
//=============================================================================
// アイコンの上下移動
//=============================================================================
void CPause::SetMove(int nNum)
{
	m_pos = m_apScene2D[nNum]->GetPos();

	//選択肢のアニメーション
	if (m_fCntMove >= 1 || m_fCntMove <= -1)
	{
		m_fChengeMove *= -1.0f;//折り返し
	}
	m_fCntMove += m_fChengeMove;
	m_pos.y += m_fCntMove;

	m_apScene2D[nNum]->SetPos(m_pos);
}
//=============================================================================
// テクスチャのロード
//=============================================================================
HRESULT CPause::Load(void)
{
	CManager::MODE mode = CManager::GetMode();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, NULL, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSEBG, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSE_ITEM, &m_pTexture[2]);
	
	return S_OK;
}
//=============================================================================
// テクスチャのアンロード
//=============================================================================
void CPause::UnLoad(void)
{
	// テクスチャの破棄
	for (int nCnt = 0; nCnt < MAX_PAUSETEXTURE; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}