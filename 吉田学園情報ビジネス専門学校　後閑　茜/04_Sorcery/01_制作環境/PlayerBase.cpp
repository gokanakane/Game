//=============================================================================
//
// �v���C���[�̊�Տ��� [playerBase.cpp]
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
// �ÓI�����o�ϐ�
//=============================================================================
//bool g_bBool = false;
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
CPlayer *CPlayer::pPlayer = NULL;
CManager::CHARACTORSELECT_STATE CPlayer::m_SelectCharactor = CManager::CHARACTORSELECT_NONE;
int  CPlayer::m_nLife = 0;
CPlayer::PlayerSkill_Normal CPlayer::m_NormalSkillUse = CPlayer::PLAYERSKIL_NORMALL_FALSE;
CPlayer::PlayerSkill_KIWAME CPlayer::m_KIWAMESkillUse = CPlayer::PLAYERSKILL_KIWAME_FALSE;

//=============================================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}
//=============================================================================
// �v���C���[�̐���
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
	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	pPlayer->SetObjtype(CScene::OBJTYPE_PLAYER);

	return pPlayer;
}
//=============================================================================
// �v���C���[�̏���������
//=============================================================================
HRESULT CPlayer::Init(void)
{
	CScene2D::Init();

	return S_OK;
}

//=============================================================================
// �v���C���[�̏I������
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// �v���C���[�̍X�V����
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

	/* �L�[�{�[�h�̎擾 */
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
				//���[�h�ݒ�
				CFade::SetFade(CManager::MODE_OVER);
			}
		}
		break;
	}

	if (m_state == PLAYERSTATE_NONE || m_state == PLAYERSTATE_INVINCIBLE)
	{
		/* �A�j���[�V���� */
		if (m_nCntAnim % 8 == 0)
		{
			m_nPatturnAnim++;
			SetCharaAnim(m_nPatturnAnim,0.0f);

			if (m_nPatturnAnim >= MAX_ANIMPATTURM)
			{
				m_nPatturnAnim = 0;
			}
		}
		/* �ړ����� */
		if ((pInput->GetKeyboardPress(DIK_D) == true) || (state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
		{
			if ((pInput->GetKeyboardPress(DIK_W) == true) || (state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
			{//�E��ړ�
				move.x += sinf(D3DX_PI*0.75f)* POLYGON_MOVE;
				move.y += cosf(D3DX_PI*0.75f)* POLYGON_MOVE;
			}
			else if ((pInput->GetKeyboardPress(DIK_S) == true) || (state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
			{//�E���ړ�
				move.x += sinf(D3DX_PI*0.25f)* POLYGON_MOVE;
				move.y += cosf(D3DX_PI*0.25f)* POLYGON_MOVE;
			}
			else
			{//�E�ړ�
				move.x += sinf(D3DX_PI*0.5f)* POLYGON_MOVE;
				move.y += cosf(D3DX_PI*0.5f)* POLYGON_MOVE;
			}
			SetCharaAnim(m_nPatturnAnim, 0.25f);
		}

		else if ((pInput->GetKeyboardPress(DIK_A) == true) || (state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
		{
			if ((pInput->GetKeyboardPress(DIK_W) == true) || (state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
			{//����ړ�
				move.x += sinf(D3DX_PI*-0.75f)* POLYGON_MOVE;
				move.y += cosf(D3DX_PI*-0.75f)* POLYGON_MOVE;
			}
			else if ((pInput->GetKeyboardPress(DIK_S) == true) || (state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
			{//�����ړ�
				move.x += sinf(D3DX_PI*-0.25f)* POLYGON_MOVE;
				move.y += cosf(D3DX_PI*-0.25f)* POLYGON_MOVE;
			}
			else
			{//���ړ�
				move.x += sinf(D3DX_PI*-0.5f)* POLYGON_MOVE;
				move.y += cosf(D3DX_PI*-0.5f)* POLYGON_MOVE;
			}
			SetCharaAnim(m_nPatturnAnim, 0.5f);
		}

		else if ((pInput->GetKeyboardPress(DIK_W) == true)|| (state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
		{//���ړ�
			move.x += sinf(D3DX_PI)* POLYGON_MOVE;
			move.y += cosf(D3DX_PI)* POLYGON_MOVE;
		}

		else if ((pInput->GetKeyboardPress(DIK_S) == true)|| (state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
		{//��ړ�
			move.x += sinf(0.0f)* POLYGON_MOVE;
			move.y += cosf(0.0f)* POLYGON_MOVE;
		}

		//�ړ����f
		m_pos.x += move.x;
		m_pos.y += move.y;

		if ((pInput->GetKeyboardPress(DIK_O) == true) || state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER && CDirectXInput::GetConnectionJoypad() == true)
		{//�ɖ��@
			CButton::SetButtonPush(true, CButton::PLAYERPUSH_KIWAME);
		} 
		if ((pInput->GetKeyboardPress(DIK_I) == true) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && CDirectXInput::GetConnectionJoypad() == true))
		{//���@
			CButton::SetButtonPush(true, CButton::PLAYERPUSH_NORMAL);
		}
	}

	MoveRestriction(m_pos);		//�ړ��͈͂̐���
	CScene2D::SetPos(m_pos);
}

//=============================================================================
// �v���C���[�̕`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// �v���C���[�̈ʒu�ݒ菈��
//=============================================================================
void CPlayer::SetPlayer(D3DXVECTOR3 pos)
{
	m_pos = pos;

	CScene2D::SetScene2D(m_pos, DEFOLT_SIZE, 60.0f);
}
//=============================================================================
// �v���C���[�̈ʒu�擾
//=============================================================================
D3DXVECTOR3 CPlayer::GetPlayerPos(void)
{
	return m_pos;
}
//=============================================================================
// �v���C���[�̎擾
//=============================================================================
CPlayer *CPlayer::GetPlayer(void)
{
	return pPlayer;
}
//=============================================================================
// �_���[�W����
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
// �񕜏���
//=============================================================================
void CPlayer::SetRecovery(int Recovery)
{
	m_nLife += Recovery;
	if (m_nLife >= MAX_LIFE)
	{//�̗�MAX�ȏ�ɂ͂Ȃ�Ȃ�
		m_nLife = MAX_LIFE;
	}
}
//=============================================================================
// �ړ�����
//=============================================================================
void CPlayer::MoveRestriction(D3DXVECTOR3 pos)
{
	/* ��ʔ͈� */
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
// ���G����
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
// �e�N�X�`���̃��[�h
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
// �e�N�X�`���̃A�����[�h
//=============================================================================
void CPlayer::UnLoad(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
