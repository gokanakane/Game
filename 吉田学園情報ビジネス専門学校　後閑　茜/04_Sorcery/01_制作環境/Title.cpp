//=============================================================================
//
// �^�C�g������ [title.cpp]
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
// �O���[�o���ϐ�/�ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CTitle::m_pTexture[MAX_TEXTURE_TITLE] = {};
CBg *CTitle::m_pBG = NULL;
CScene2D *CTitle::m_apScene2D[MAX_TEXTURE_TITLE] = {};

//=============================================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{
	CSound::StopSound();
}
//=============================================================================
// ����������
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
		{//���S
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(300.0f, 150.0f, 0.0f), 270.0f, 150.0f);
			m_apScene2D[nCnt]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_TITLE);
		}
		else if (nCnt == 1)
		{//�R���N��
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(850.0f, 500.0f, 0.0f), 450.0f, 250.0f);
			m_apScene2D[nCnt]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_TITLE);
		}
		else if (nCnt == 2)
		{//�L�����A�j��
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
// �I������
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
// �X�V����
//=============================================================================
void CTitle::Update(void)
{
	/* �L�[�{�[�h�̎擾 */
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

	/* �^�C�g�����S�̏�� */
	switch (m_LogoState)
	{
	case LOGOSTATE_NONE:
		m_apScene2D[0]->SetColor(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
		m_nChangeMode++;
		if (pInput->GetKeyboardPress(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
		{//Enter����
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				m_State = PRESSSTATE_FLASHING;
				m_fChangeAlpha = 1.0f;
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}

		// 10�b�o�����烉���L���O�Ɉڍs
		if (m_nChangeMode >= 600)
		{
			if (g_fade != CFade::FADE_OUT)
			{
				//���[�h�ݒ�
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

	/* �O���t�B�b�N�̏�� */
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

	/* PRESS_ENTER�̏�� */
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
					//���[�h�ݒ�
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
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{

}
//=============================================================================
// �e�N�X�`���̃��[�h
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

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLE_LOGO, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLE_CONCRETE, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLE_ANIMATION, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLE_PRESS, &m_pTexture[3]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���̃A�����[�h
//=============================================================================
void CTitle::UnLoad(void)
{
	// �e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_TEXTURE_TITLE; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}