//=============================================================================
//
// プレイヤーの基盤処理 [playerBase.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "Input.h"
#include "scene2D.h"
#include "tutorial.h"
#include "playerBase.h"
#include "Doragon.h"
#include "Karnerian.h"
#include "Vivian.h"
#include "Areista.h"
#include "Renge.h"
#include "Liliy.h"
#include "fade.h"
#include "GameUi.h"
#include "Button.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
//bool g_bBool = false;
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
CPlayer *CPlayer::pPlayer = NULL;
CManager::CHARACTORSELECT_STATE CPlayer::m_SelectCharactor = CManager::CHARACTORSELECT_NONE;
int  CPlayer::m_nLife = 0;
CPlayer::PlayerSkill_Normal CPlayer::m_NormalSkillUse = CPlayer::PLAYERSKIL_NORMALL_FALSE;
CPlayer::PlayerSkill_KIWAME CPlayer::m_KIWAMESkillUse = CPlayer::PLAYERSKILL_KIWAME_FALSE;

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer():CScene2D(3)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntAnim = 0;
	m_nPatturnAnim = 0;
	m_nLife = 0;
	m_state = PLAYERSTATE_NONE;
	m_nCntFade = 0;
	m_nCntState = 0;
	m_NormalSkillUse = PLAYERSKIL_NORMALL_FALSE;
	m_Col = D3DXCOLOR(1.0f,1.0f,0.0f,1.0f);
	m_ChangeCol = 1.0f;
}
//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}
//=============================================================================
// プレイヤーの生成
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos,CManager::CHARACTORSELECT_STATE state)
{
	switch (state)
	{
	case CManager::CHARACTORSTATE_DORAGON:
		pPlayer = new CDoragon;
		break;

	case CManager::CHARACTORSTATE_KARNERIAN:
		pPlayer = new CKarnerian;
		break;

	case CManager::CHARACTORSTATE_VIVIAN:
		pPlayer = new CVivian;
		break;

	case CManager::CHARACTORSTATE_AREISTA:
		pPlayer = new CAreista;
		break;

	case CManager::CHARACTORSTATE_RENGE:
		pPlayer = new CRenge;
		break;

	case CManager::CHARACTORSTATE_LILIY:
		pPlayer = new CLiliy;
		break;
	}

	pPlayer->Init();
	pPlayer->BindTexture(m_pTexture);
	pPlayer->SetPlayer(pos);
	pPlayer->SetCharaAnim(0, 0.0f);;
	pPlayer->SetLife(MAX_LIFE);
	//オブジェクトの種類の設定
	pPlayer->SetObjtype(CScene::OBJTYPE_PLAYER);

	return pPlayer;
}
//=============================================================================
// プレイヤーの初期化処理
//=============================================================================
HRESULT CPlayer::Init(void)
{
	CScene2D::Init();

	return S_OK;
}

//=============================================================================
// プレイヤーの終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// プレイヤーの更新処理
//=============================================================================
void CPlayer::Update(void)
{
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = CScene2D::GetPos();
	m_nCntAnim++;
	CFade::FADEMODE g_fade = CFade::GetFade();
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

	switch (m_state)
	{
	case PLAYERSTATE_NONE:
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;

	case PLAYERSTATE_INVINCIBLE:
		SetInvincible();
		break;

	case PLAYERSTATE_DAMAGE:

		if (m_nLife <= 0)
		{
			m_state = PLAYERSTATE_DEATH;
		}
		else
		{
			m_nCntState--;
			if (m_nCntState <= 0)
			{
				m_state = PLAYERSTATE_NONE;
			}
		}
		break;

	case PLAYERSTATE_DEATH:
		m_nCntFade++;
		if (m_nCntFade > 10)
		{
			if (g_fade != CFade::FADE_OUT)
			{
				//モード設定
				CFade::SetFade(CManager::MODE_OVER);
			}
		}
		break;
	}

	if (m_state == PLAYERSTATE_NONE || m_state == PLAYERSTATE_INVINCIBLE)
	{
		/* アニメーション */
		if (m_nCntAnim % 8 == 0)
		{
			m_nPatturnAnim++;
			SetCharaAnim(m_nPatturnAnim,0.0f);

			if (m_nPatturnAnim >= MAX_ANIMPATTURM)
			{
				m_nPatturnAnim = 0;
			}
		}
		/* 移動処理 */
		if ((pInput->GetKeyboardPress(DIK_D) == true) || (state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
		{
			if ((pInput->GetKeyboardPress(DIK_W) == true) || (state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
			{//右上移動
				move.x += sinf(D3DX_PI*0.75f)* POLYGON_MOVE;
				move.y += cosf(D3DX_PI*0.75f)* POLYGON_MOVE;
			}
			else if ((pInput->GetKeyboardPress(DIK_S) == true) || (state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
			{//右下移動
				move.x += sinf(D3DX_PI*0.25f)* POLYGON_MOVE;
				move.y += cosf(D3DX_PI*0.25f)* POLYGON_MOVE;
			}
			else
			{//右移動
				move.x += sinf(D3DX_PI*0.5f)* POLYGON_MOVE;
				move.y += cosf(D3DX_PI*0.5f)* POLYGON_MOVE;
			}
			SetCharaAnim(m_nPatturnAnim, 0.25f);
		}

		else if ((pInput->GetKeyboardPress(DIK_A) == true) || (state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
		{
			if ((pInput->GetKeyboardPress(DIK_W) == true) || (state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
			{//左上移動
				move.x += sinf(D3DX_PI*-0.75f)* POLYGON_MOVE;
				move.y += cosf(D3DX_PI*-0.75f)* POLYGON_MOVE;
			}
			else if ((pInput->GetKeyboardPress(DIK_S) == true) || (state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
			{//左下移動
				move.x += sinf(D3DX_PI*-0.25f)* POLYGON_MOVE;
				move.y += cosf(D3DX_PI*-0.25f)* POLYGON_MOVE;
			}
			else
			{//左移動
				move.x += sinf(D3DX_PI*-0.5f)* POLYGON_MOVE;
				move.y += cosf(D3DX_PI*-0.5f)* POLYGON_MOVE;
			}
			SetCharaAnim(m_nPatturnAnim, 0.5f);
		}

		else if ((pInput->GetKeyboardPress(DIK_W) == true)|| (state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
		{//下移動
			move.x += sinf(D3DX_PI)* POLYGON_MOVE;
			move.y += cosf(D3DX_PI)* POLYGON_MOVE;
		}

		else if ((pInput->GetKeyboardPress(DIK_S) == true)|| (state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
		{//上移動
			move.x += sinf(0.0f)* POLYGON_MOVE;
			move.y += cosf(0.0f)* POLYGON_MOVE;
		}

		//移動反映
		m_pos.x += move.x;
		m_pos.y += move.y;

		if ((pInput->GetKeyboardPress(DIK_O) == true) || state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER && CDirectXInput::GetConnectionJoypad() == true)
		{//極魔法
			CButton::SetButtonPush(true, CButton::PLAYERPUSH_KIWAME);
		} 
		if ((pInput->GetKeyboardPress(DIK_I) == true) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && CDirectXInput::GetConnectionJoypad() == true))
		{//魔法
			CButton::SetButtonPush(true, CButton::PLAYERPUSH_NORMAL);
		}
	}

	MoveRestriction(m_pos);		//移動範囲の制限
	CScene2D::SetPos(m_pos);
}

//=============================================================================
// プレイヤーの描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// プレイヤーの位置設定処理
//=============================================================================
void CPlayer::SetPlayer(D3DXVECTOR3 pos)
{
	m_pos = pos;

	CScene2D::SetScene2D(m_pos, DEFOLT_SIZE, 60.0f);
}
//=============================================================================
// プレイヤーの位置取得
//=============================================================================
D3DXVECTOR3 CPlayer::GetPlayerPos(void)
{
	return m_pos;
}
//=============================================================================
// プレイヤーの取得
//=============================================================================
CPlayer *CPlayer::GetPlayer(void)
{
	return pPlayer;
}
//=============================================================================
// ダメージ処理
//=============================================================================
void CPlayer::SetDamage(int Damage)
{
	m_nLife -= Damage;
	m_nCntState = 5;
	SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	if (m_nLife <= 0)
	{
		m_state = PLAYERSTATE_DEATH;
	}
}
//=============================================================================
// 回復処理
//=============================================================================
void CPlayer::SetRecovery(int Recovery)
{
	m_nLife += Recovery;
	if (m_nLife >= MAX_LIFE)
	{//体力MAX以上にはならない
		m_nLife = MAX_LIFE;
	}
}
//=============================================================================
// 移動制限
//=============================================================================
void CPlayer::MoveRestriction(D3DXVECTOR3 pos)
{
	/* 画面範囲 */
	if (pos.x > SCREEN_WIDTH - DEFOLT_SIZE)
	{
		pos.x = SCREEN_WIDTH - DEFOLT_SIZE;
	}
	if (pos.x < 50.0f + DEFOLT_SIZE)
	{
		pos.x = 50.0f + DEFOLT_SIZE;
	}
	if (pos.y < 130.0f + DEFOLT_SIZE)
	{
		pos.y = 130.0f + DEFOLT_SIZE;

	}
	if (pos.y > SCREEN_HEIGHT - DEFOLT_SIZE)
	{
		pos.y = SCREEN_HEIGHT - DEFOLT_SIZE;
	}

	m_pos = pos;
}
//=============================================================================
// 無敵時間
//=============================================================================
void CPlayer::SetInvincible(void)
{
	m_Col.b += m_ChangeCol;
	if (m_Col.b <= 0.2f || m_Col.b >= 1.0f)
	{
		m_ChangeCol *= -1;
	}
	SetColor(D3DXCOLOR(1.0f,1.0f, m_Col.b, m_Col.b));
}
//=============================================================================
// テクスチャのロード
//=============================================================================
HRESULT CPlayer::Load(void)
{
	m_SelectCharactor = CManager::GetCharactorSelect();

	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	switch (m_SelectCharactor)
	{
	case CManager::CHARACTORSTATE_DORAGON:
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PLAYER_DRAGON, &m_pTexture);
		break;

	case CManager::CHARACTORSTATE_KARNERIAN:
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PLAYER_KARNERIAN, &m_pTexture);
		break;

	case CManager::CHARACTORSTATE_VIVIAN:
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PLAYER_VIVIAN, &m_pTexture);
		break;

	case CManager::CHARACTORSTATE_AREISTA:
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PLAYER_AREISTA, &m_pTexture);
		break;

	case CManager::CHARACTORSTATE_RENGE:
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PLAYER_RENGE, &m_pTexture);
		break;

	case CManager::CHARACTORSTATE_LILIY:
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PLAYER_LILIY, &m_pTexture);
		break;
	}
	return S_OK;
}
//=============================================================================
// テクスチャのアンロード
//=============================================================================
void CPlayer::UnLoad(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
