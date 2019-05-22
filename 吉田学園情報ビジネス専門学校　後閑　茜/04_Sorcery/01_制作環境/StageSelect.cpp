//=============================================================================
//
// タイトル処理 [StageSelect.cpp]
// Author : 
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "Input.h"
#include "fade.h"
#include "StageSelect.h"
#include "bg.h"
#include "sound.h"

//*****************************************************************************
// グローバル変数/静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CStageSelect::m_pTexture[MAX_TEXTURE_STAGESELECT] = {};
CBg *CStageSelect::m_pBG = NULL;
CScene2D *CStageSelect::m_apScene2D[MAX_TEXTURE_STAGESELECT] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CStageSelect::CStageSelect()
{
	for (int nCnt = 0; nCnt < MAX_SELECTSTAGE; nCnt++)
	{
		m_posOld[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	m_nSelectNum = 0;
	m_StageSelectState = CManager::STAGESELECT_NONE;
	m_StageSelectCol = STAGESELECTCOL_NONE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CSound::PlaySound(CSound::SOUND_LABEL_STAGESELECT);

}
//=============================================================================
// デストラクタ
//=============================================================================
CStageSelect::~CStageSelect()
{
	CSound::StopSound(CSound::SOUND_LABEL_STAGESELECT);

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CStageSelect::Init(void)
{
	CBg::Load();
	CStageSelect::Load();

	if (m_pBG == NULL)
	{
		m_pBG = new CBg;
		m_pBG->Create();
	}
	for (int nCnt = 0; nCnt < MAX_STAGESELECT_POLYGON; nCnt++)
	{//ステージアイコンとカーソル
		if (nCnt >= 0 && nCnt <= 3)
		{//アイコン
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[0]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(270.0f + (nCnt*260.0f), 260.0f, 0.0f), DEFAULT_ICONSIZE, DEFAULT_ICONSIZE);
			m_apScene2D[nCnt]->SetAnimX(4, 1, nCnt);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_STAGESELECT);
			m_posOld[nCnt] = m_apScene2D[nCnt]->GetPos();
		}
		else if (nCnt == 4)
		{//カーソル
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[1]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(280.0f, 200.0f, 0.0f), EXPANSION_ICONSIZE, EXPANSION_ICONSIZE);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_STAGESELECT);
		}
		else if (nCnt == 5)
		{//枠
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[2]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH / 2, 590.0f, 0.0f), SCREEN_WIDTH / 2, 130.0f);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_STAGESELECT);
		}
		else if (nCnt == 6)
		{//文字
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[3]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH / 2, 590.0f, 0.0f), 500.0f, 100.0f);
			m_apScene2D[nCnt]->SetAnimY(1, MAX_SELECTSTAGE, 0);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_STAGESELECT);
		}
		else if (nCnt == 7)
		{//サブタイトル
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[4]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(300.0f, 40.0f, 0.0f), 300.0f, 40.0f);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_STAGESELECT);
		}
		else
		{//カーソルUI
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[5]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(95.0f + ((nCnt - 8)*350.0f), 250.0f, 0.0f), 60.0f, 40.0f);
			m_apScene2D[nCnt]->SetAnimX(2,1, nCnt - 8);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_STAGESELECT);
		}
	}

	m_nSelectNum = 0;
	m_StageSelectState = CManager::STAGESELECT_NONE;
	m_StageSelectCol = STAGESELECTCOL_NONE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fCntMove = 0.1f;
	m_fChengeMove = 0.05f;

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CStageSelect::Uninit(void)
{
	CBg::UnLoad();
	CStageSelect::UnLoad();

	if (m_pBG != NULL)
	{
		m_pBG->Uninit();
		m_pBG = NULL;
	}
	for (int nCnt = 0; nCnt < MAX_STAGESELECT_POLYGON; nCnt++)
	{//ステージアイコンとカーソル
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt]->Uninit();
			m_apScene2D[nCnt] = NULL;
		}
	}
	CScene::ReleaseAllFade();
}
//=============================================================================
// 更新処理
//=============================================================================
void CStageSelect::Update(void)
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
	//選択処理
	if (pInput->GetKeyboardTrigger(DIK_D) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT && CDirectXInput::GetConnectionJoypad() == true))
	{
		if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
		{
			CSound::PlaySound(CSound::SOUND_LABEL_SE_CURSOR);
			m_nSelectNum = (m_nSelectNum + 1) % 4;
		}
		CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
	}
	if (pInput->GetKeyboardTrigger(DIK_A) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT && CDirectXInput::GetConnectionJoypad() == true))
	{
		if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
		{
			CSound::PlaySound(CSound::SOUND_LABEL_SE_CURSOR);
			m_nSelectNum = (m_nSelectNum + 3) % 4;
		}
		CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
	}

	if (pInput->GetKeyboardTrigger(DIK_L) == true)
	{
		if (g_fade != CFade::FADE_OUT)
		{
			//モード設定
			CFade::SetFade(CManager::MODE_TITLE);
		}
	}

	//選択された場所の処理
	if (m_nSelectNum == 0)
	{//ステージ1
		m_StageSelectCol = STAGESELECTCOL_STAGE1;
		SetMove(m_nSelectNum);

		if (pInput->GetKeyboardPress(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
		{//Enter押下
			if (g_fade != CFade::FADE_OUT)
			{
				CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
				m_StageSelectState = CManager::STAGESELECT_STAGE1;
			}
		}
	}
	if (m_nSelectNum == 1)
	{//ステージ2
		m_StageSelectCol = STAGESELECTCOL_STAGE2;
		SetMove(m_nSelectNum);

		if (pInput->GetKeyboardPress(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
		{//Enter押下
			if (g_fade != CFade::FADE_OUT)
			{
				CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
				m_StageSelectState = CManager::STAGESELECT_STAGE2;
			}
		}
	}
	if (m_nSelectNum == 2)
	{//ステージ3
		m_StageSelectCol = STAGESELECTCOL_STAGE3;
		SetMove(m_nSelectNum);
		if (pInput->GetKeyboardPress(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
		{//Enter押下
			if (g_fade != CFade::FADE_OUT)
			{
				CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
				m_StageSelectState = CManager::STAGESELECT_STAGE3;
			}
		}
	}
	if (m_nSelectNum == 3)
	{//ステージ4
		m_StageSelectCol = STAGESELECTCOL_STAGE4;
		SetMove(m_nSelectNum);
		if (pInput->GetKeyboardPress(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
		{//Enter押下
			if (g_fade != CFade::FADE_OUT)
			{
				CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
				m_StageSelectState = CManager::STAGESELECT_STAGE4;
			}
		}
	}
	//色と座標の設定
	switch (m_StageSelectCol)
	{
	case STAGESELECTCOL_NONE:
		break;

	case STAGESELECTCOL_STAGE1:
		m_pos = m_apScene2D[0]->GetPos();
		/* 色 */
		m_apScene2D[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apScene2D[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_apScene2D[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_apScene2D[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		
		/* サイズ */
		m_apScene2D[0]->SetSize(EXPANSION_ICONSIZE, EXPANSION_ICONSIZE);
		m_apScene2D[1]->SetSize(DEFAULT_ICONSIZE, DEFAULT_ICONSIZE);
		m_apScene2D[2]->SetSize(DEFAULT_ICONSIZE, DEFAULT_ICONSIZE);
		m_apScene2D[3]->SetSize(DEFAULT_ICONSIZE, DEFAULT_ICONSIZE);

		/* 位置を元に戻す */
		m_apScene2D[1]->SetPos(m_posOld[1]);
		m_apScene2D[2]->SetPos(m_posOld[2]);
		m_apScene2D[3]->SetPos(m_posOld[3]);

		/* あらすじ表示 */
		m_apScene2D[6]->SetAnimY(1, MAX_SELECTSTAGE,0);

		/* カーソルの位置 */
		m_apScene2D[4]->SetPos(m_pos);
		m_apScene2D[8]->SetPos(D3DXVECTOR3(m_posOld[0].x - 180.0f, m_posOld[0].y, 0.0f));
		m_apScene2D[9]->SetPos(D3DXVECTOR3(m_posOld[0].x + 180.0f, m_posOld[0].y, 0.0f));
		break;

	case STAGESELECTCOL_STAGE2:
		m_pos = m_apScene2D[1]->GetPos();
		/* 色 */
		m_apScene2D[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_apScene2D[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apScene2D[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_apScene2D[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		/* サイズ */
		m_apScene2D[0]->SetSize(DEFAULT_ICONSIZE, DEFAULT_ICONSIZE);
		m_apScene2D[1]->SetSize(EXPANSION_ICONSIZE, EXPANSION_ICONSIZE);
		m_apScene2D[2]->SetSize(DEFAULT_ICONSIZE, DEFAULT_ICONSIZE);
		m_apScene2D[3]->SetSize(DEFAULT_ICONSIZE, DEFAULT_ICONSIZE);

		/* 位置を元に戻す */
		m_apScene2D[0]->SetPos(m_posOld[0]);
		m_apScene2D[2]->SetPos(m_posOld[2]);
		m_apScene2D[3]->SetPos(m_posOld[3]);

		/* あらすじ表示 */
		m_apScene2D[6]->SetAnimY(1, MAX_SELECTSTAGE, 1);

		/* カーソルの位置 */
		m_apScene2D[4]->SetPos(m_pos);
		m_apScene2D[8]->SetPos(D3DXVECTOR3(m_posOld[1].x - 180.0f, m_posOld[1].y, 0.0f));
		m_apScene2D[9]->SetPos(D3DXVECTOR3(m_posOld[1].x + 180.0f, m_posOld[1].y, 0.0f));
		break;

	case STAGESELECTCOL_STAGE3:
		m_pos = m_apScene2D[2]->GetPos();
		/* 色 */
		m_apScene2D[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_apScene2D[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_apScene2D[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apScene2D[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		/* サイズ */
		m_apScene2D[0]->SetSize(DEFAULT_ICONSIZE, DEFAULT_ICONSIZE);
		m_apScene2D[1]->SetSize(DEFAULT_ICONSIZE, DEFAULT_ICONSIZE);
		m_apScene2D[2]->SetSize(EXPANSION_ICONSIZE, EXPANSION_ICONSIZE);
		m_apScene2D[3]->SetSize(DEFAULT_ICONSIZE, DEFAULT_ICONSIZE);

		/* 位置を元に戻す */
		m_apScene2D[0]->SetPos(m_posOld[0]);
		m_apScene2D[1]->SetPos(m_posOld[1]);
		m_apScene2D[3]->SetPos(m_posOld[3]);

		/* あらすじ表示 */
		m_apScene2D[6]->SetAnimY(1, MAX_SELECTSTAGE, 2);

		/* カーソルの位置 */
		m_apScene2D[4]->SetPos(m_pos);
		m_apScene2D[8]->SetPos(D3DXVECTOR3(m_posOld[2].x - 180.0f, m_posOld[2].y, 0.0f));
		m_apScene2D[9]->SetPos(D3DXVECTOR3(m_posOld[2].x + 180.0f, m_posOld[2].y, 0.0f));
		break;

	case STAGESELECTCOL_STAGE4:
		m_pos = m_apScene2D[3]->GetPos();
		/* 色 */
		m_apScene2D[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_apScene2D[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_apScene2D[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_apScene2D[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		/* サイズ */
		m_apScene2D[0]->SetSize(DEFAULT_ICONSIZE, DEFAULT_ICONSIZE);
		m_apScene2D[1]->SetSize(DEFAULT_ICONSIZE, DEFAULT_ICONSIZE);
		m_apScene2D[2]->SetSize(DEFAULT_ICONSIZE, DEFAULT_ICONSIZE);
		m_apScene2D[3]->SetSize(EXPANSION_ICONSIZE, EXPANSION_ICONSIZE);

		/* 位置を元に戻す */
		m_apScene2D[0]->SetPos(m_posOld[0]);
		m_apScene2D[1]->SetPos(m_posOld[1]);
		m_apScene2D[2]->SetPos(m_posOld[2]);

		/* あらすじ表示 */
		m_apScene2D[6]->SetAnimY(1, MAX_SELECTSTAGE, 3);

		/* カーソルの位置 */
		m_apScene2D[4]->SetPos(m_pos);
		m_apScene2D[8]->SetPos(D3DXVECTOR3(m_posOld[3].x - 180.0f, m_posOld[3].y, 0.0f));
		m_apScene2D[9]->SetPos(D3DXVECTOR3(m_posOld[3].x + 180.0f, m_posOld[3].y, 0.0f));
		break;
	}

	/* 選択ステージの状態別処理 */
	switch (m_StageSelectState)
	{
	case CManager::STAGESELECT_NONE:
		break;

	case CManager::STAGESELECT_STAGE1:
		CManager::SetStageState(m_StageSelectState);
		m_StageSelectState = CManager::STAGESELECT_NONE;
		//モード設定
		CFade::SetFade(CManager::MODE_CHARACTORSELECT);
		break;

	case CManager::STAGESELECT_STAGE2:
		CManager::SetStageState(m_StageSelectState);
		m_StageSelectState = CManager::STAGESELECT_NONE;
		//モード設定
		CFade::SetFade(CManager::MODE_CHARACTORSELECT);
		break;

	case CManager::STAGESELECT_STAGE3:
		CManager::SetStageState(m_StageSelectState);
		m_StageSelectState = CManager::STAGESELECT_NONE;
		//モード設定
		CFade::SetFade(CManager::MODE_CHARACTORSELECT);
		break;

	case CManager::STAGESELECT_STAGE4:
		CManager::SetStageState(m_StageSelectState);
		m_StageSelectState = CManager::STAGESELECT_NONE;
		//モード設定
		CFade::SetFade(CManager::MODE_CHARACTORSELECT);
		break;
	}

	CDirectXInput::ResetInputJoyState(CDirectXInput::GetInputJoyState());
}
//=============================================================================
// 描画処理
//=============================================================================
void CStageSelect::Draw(void)
{

}
//=============================================================================
// アイコンの上下移動
//=============================================================================
void CStageSelect::SetMove(int nNum)
{
	m_pos = m_apScene2D[nNum]->GetPos();

	//選択肢のアニメーション
	if (m_fCntMove >= 0.5f || m_fCntMove <= -0.5f)
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
HRESULT CStageSelect::Load(void)
{
	CManager::MODE mode = CManager::GetMode();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_STAGEICON_STAGEICON, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_STAGEICON_CURSOR, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_STAGECOMMENTWINDOW, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_STAGECOMMENT, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_STAGESUBTITLES, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_STAGEICON_CURSORUI, &m_pTexture[5]);

	return S_OK;
}
//=============================================================================
// テクスチャのアンロード
//=============================================================================
void CStageSelect::UnLoad(void)
{
	// テクスチャの破棄
	for (int nCnt = 0; nCnt < MAX_TEXTURE_STAGESELECT; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}