//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : Eisuke Sakagawa
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"		// �}�l�[�W���[
#include "sound.h"			// �T�E���h
#include "input.h"			// ����
#include "camera.h"			// �J����
#include "light.h"			// ���C�g
#include "renderer.h"		// �����_���[
#include "fade.h"			// �t�F�[�h
#include "title.h"			// �^�C�g��
#include "game.h"			// �Q�[��
#include "tutorial.h"		// �`���[�g���A��
#include "result.h"			// ���U���g
#include "scene.h"			// �V�[��
#include "ranking.h"		// �����L���O
#include "pause.h"			// �|�[�Y

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CManager::MODE		CManager::m_mode			= CManager::MODE_NONE;	// ���[�h
CSound				*CManager::m_pSound			= NULL;					// �T�E���h
CInputKeyboard		*CManager::m_pInputKeyboard = NULL;					// �L�[�{�[�h
CInputDIPad			*CManager::m_pInputDIPad	= NULL;					// DI�p�b�h
CInputXPad			*CManager::m_pInputXPad		= NULL;					// X�p�b�h
CRenderer			*CManager::m_pRenderer		= NULL;					// �����_���[
CCamera				*CManager::m_pCamara		= NULL;					// �J����
CLight				*CManager::m_pLight			= NULL;					// ���C�g
CTitle				*CManager::m_pTitle			= NULL;					// �^�C�g��
CGame				*CManager::m_pGame			= NULL;					// �Q�[��
CTutorial			*CManager::m_pTutorial		= NULL;					// �`���[�g���A��
CResult				*CManager::m_pResult		= NULL;					// ���U���g
CRanking			*CManager::m_pRanking		= NULL;					// �����L���O	
int					CManager::m_nPlayNum		= 0;					// �v���C�l��
CPause              *CManager::m_pPause			= NULL;
//=============================================================================
// �R���X�g���N�^								(public)	*** CManager ***
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
// �f�X�g���N�^									(public)	*** CManager ***
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// ����������									(public)	*** CManager ***
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// �T�E���h
	{
		if (m_pSound == NULL)
		{// NULL�̏ꍇ
			m_pSound = new CSound;		// �T�E���h�������m��
		}
		else
		{// NULL�ȊO�̏ꍇ
			MessageBox(0, "(manager�uInit] : Sound��NULL�łȂ�", "�x��", MB_OK);
		}

		if (m_pSound != NULL)
		{// NULL�ȊO�̏ꍇ
		 // �T�E���h����������
			if (FAILED(m_pSound->Init(hWnd)))
			{
				return -1;
			}
		}
		else
		{// NULL�̏ꍇ
			MessageBox(0, "(manager�uInit] : Sound��NULL", "�x��", MB_OK);
		}
	}

	// �L�[�{�[�h
	{
		if (m_pInputKeyboard == NULL)
		{// NULL�̏ꍇ
			m_pInputKeyboard = new CInputKeyboard;		// �L�[�{�[�h�������m��
		}
		else
		{// NULL�ȊO�̏ꍇ
			MessageBox(0, "(manager�uInit] : InputKeyboard��NULL�łȂ�", "�x��", MB_OK);
		}

		if (m_pInputKeyboard != NULL)
		{// NULL�ȊO�̏ꍇ
			// �L�[�{�[�h����������
			if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
			{
				return -1;
			}
		}
		else
		{// NULL�̏ꍇ
			MessageBox(0, "(manager�uInit] : InputKeyboard��NULL", "�x��", MB_OK);
		}
	}
	// DI�p�b�h
	{
		if (m_pInputDIPad == NULL)
		{// NULL�̏ꍇ
			m_pInputDIPad = new CInputDIPad;		// DI�p�b�h�������m��
		}
		else
		{// NULL�ȊO�̏ꍇ
			MessageBox(0, "(manager�uInit] : InputDIPad��NULL�łȂ�", "�x��", MB_OK);
		}

		if (m_pInputDIPad != NULL)
		{// NULL�ȊO�̏ꍇ
			// DI�p�b�h����������
			if (FAILED(m_pInputDIPad->Init(hInstance, hWnd)))
			{
				return -1;
			}
		}
		else
		{// NULL�̏ꍇ
			MessageBox(0, "(manager�uInit] : InputDIPad��NULL", "�x��", MB_OK);
		}
	}
	// X�p�b�h
	{
		if (m_pInputXPad == NULL)
		{// NULL�̏ꍇ
			m_pInputXPad = new CInputXPad;		// DI�p�b�h�������m��
		}
		else
		{// NULL�ȊO�̏ꍇ
			MessageBox(0, "(manager�uInit] : InputXPad��NULL�łȂ�", "�x��", MB_OK);
		}

		if (m_pInputXPad != NULL)
		{// NULL�ȊO�̏ꍇ
		 // DI�p�b�h����������
			if (FAILED(m_pInputXPad->Init(hInstance, hWnd)))
			{
				return -1;
			}
		}
		else
		{// NULL�̏ꍇ
			MessageBox(0, "(manager�uInit] : InputXPad��NULL", "�x��", MB_OK);
		}
	}

	// �����_���[
	{
		if (m_pRenderer == NULL)
		{// NULL�̏ꍇ
			m_pRenderer = new CRenderer;			// �����_���[�������m��
		}
		else
		{// NULL�ȊO�̏ꍇ
			MessageBox(0, "(manager�uInit] : Renderer��NULL�łȂ�", "�x��", MB_OK);
		}

		if (m_pRenderer != NULL)
		{// NULL�ȊO�̏ꍇ
			// �����_���[����������
			if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
			{
				return -1;
			}
		}
		else
		{// NULL�̏ꍇ, 
			MessageBox(0, "(manager�uInit] : Renderer��NULL", "�x��", MB_OK);
		}
	}

	// �J����
	{
		if (m_pCamara == NULL)
		{// NULL�̏ꍇ
			m_pCamara = new CCamera;		// �J�����������m��
		}
		else
		{// NULL�ȊO�̏ꍇ
			MessageBox(0, "(manager�uInit] : Camera��NULL�łȂ�", "�x��", MB_OK);
		}

		if (m_pCamara != NULL)
		{// NULL�ȊO�̏ꍇ
			// �J��������������
			if (FAILED(m_pCamara->Init(D3DXVECTOR3(0.0f, 80.0f, -150.0f), D3DXVECTOR3(0.0f, 30.0f, 0.0f))))
			{
				return -1;
			}
		}
		else
		{// NULL�̏ꍇ
			MessageBox(0, "(manager�uInit] : Camera��NULL", "�x��", MB_OK);
		}
	}

	// ���C�g
	{
		if (m_pLight == NULL)
		{// NULL�̏ꍇ
			m_pLight = new CLight;			// ���C�g�������m��
		}
		else
		{// NULL�ȊO�̏ꍇ
			MessageBox(0, "(manager�uInit] : Light��NULL�łȂ�", "�x��", MB_OK);
		}

		if (m_pLight != NULL)
		{// NULL�ȊO�̏ꍇ
		 // ���C�g����������
			if (FAILED(m_pLight->Init()))
			{
				return -1;
			}
		}
		else
		{// NULL�̏ꍇ
			MessageBox(0, "(manager�uInit] : Light��NULL", "�x��", MB_OK);
		}
	}

	SetMode(MODE_TITLE);
	m_bPause = false;

	return S_OK;
}

//=============================================================================
// �I������										(public)	*** CManager ***
//=============================================================================
void CManager::Uninit(void)
{
	// �T�E���h
	{
		if (m_pSound != NULL)
		{// NULL�ȊO�̏ꍇ
			// �I������
			m_pSound->Uninit();

			delete m_pSound;	// �T�E���h�������J��
			m_pSound = NULL;	// NULL
		}
	}

	// �L�[�{�[�h
	{
		if (m_pInputKeyboard != NULL)
		{// NULL�ȊO�̏ꍇ
			// �I������
			m_pInputKeyboard->Uninit();

			delete m_pInputKeyboard;	// �L�[�{�[�h�������J��
			m_pInputKeyboard = NULL;	// NULL
		}
	}
	// DI�p�b�h
	{
		if (m_pInputDIPad != NULL)
		{// NULL�ȊO�̏ꍇ
			// �I������
			m_pInputDIPad->Uninit();

			delete m_pInputDIPad;	// DI�p�b�h�������J��
			m_pInputDIPad = NULL;	// NULL
		}
	}
	// X�p�b�h
	{
		if (m_pInputXPad != NULL)
		{// NULL�ȊO�̏ꍇ
		 // �I������
			m_pInputXPad->Uninit();

			delete m_pInputXPad;	// X�p�b�h�������J��
			m_pInputXPad = NULL;	// NULL
		}
	}

	// �|�[�Y
	{
		if (m_pPause != NULL)
		{
			m_pPause->Uninit();

			delete m_pPause;	
			m_pPause = NULL;	// NULL
		}
	}

	switch (m_mode)
	{// ���[�h
	case CManager::MODE_TITLE:		// �^�C�g��
		if (m_pTitle != NULL)
		{// NULL�ȊO�̏ꍇ
			m_pTitle->Unload();		// �A�����[�h
			m_pTitle->Uninit();		// �I������
			delete m_pTitle;
			m_pTitle = NULL;		// NULL��
		}

		break;
	case CManager::MODE_GAME:		// �Q�[��
		if (m_pGame != NULL)
		{// NULL�ȊO�̏ꍇ
			m_pGame->Uninit();		// �I������
			delete m_pGame;
			m_pGame = NULL;			// NULL��
		}

		break;

	case CManager::MODE_TUTORIAL:	// �`���[�g���A��
		if (m_pTutorial != NULL)
		{	// NULL�ȊO�̏ꍇ
			m_pTutorial->Uninit();
			delete m_pTutorial;
			m_pTutorial = NULL;
		}
		break;

	case CManager::MODE_RESULT:	// ���U���g
		if (m_pResult != NULL)
		{	// NULL�ȊO�̏ꍇ
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		break;

	case CManager::MODE_RANKING:	// �����L���O
		if (m_pRanking != NULL)
		{	// NULL�ȊO�̏ꍇ
			m_pRanking->Uninit();
			delete m_pRanking;
			m_pRanking = NULL;
		}
		break;

	}

	// �����_���[
	{
		if (m_pRenderer != NULL)
		{// NULL�ȊO�̏ꍇ
			// �I������
			m_pRenderer->Uninit();

			delete m_pRenderer;	// �����_���[�������J��
			m_pRenderer = NULL;	// NULL
		}
	}

	// �J����
	{
		if (m_pCamara != NULL)
		{// NULL�ȊO�̏ꍇ
			// �I������
			m_pCamara->Uninit();

			delete m_pCamara;	// �J�����������J��
			m_pCamara = NULL;	// NULL
		}
	}

	// ���C�g
	{
		if (m_pLight != NULL)
		{// NULL�ȊO�̏ꍇ
			// �I������
			m_pLight->Uninit();

			delete m_pLight;	// ���C�g�������J��
			m_pLight = NULL;	// NULL
		}
	}
}

//=============================================================================
// �X�V����										(public)	*** CManager ***
//=============================================================================
void CManager::Update(void)
{
	// �L�[�{�[�h
	{
		if (m_pInputKeyboard != NULL)
		{// NULL�ȊO�̏ꍇ
			// �L�[�{�[�h�X�V����
			m_pInputKeyboard->Update();
		}
	}
	// DI�p�b�h
	{
		if (m_pInputDIPad != NULL)
		{// NULL�ȊO�̏ꍇ
			// DI�p�b�h�X�V����
			m_pInputDIPad->Update();
		}
	}
	// X�p�b�h
	{
		if (m_pInputXPad != NULL)
		{// NULL�ȊO�̏ꍇ
			// X�p�b�h�X�V����
			m_pInputXPad->Update();
		}
	}

	DebugFont();

	switch (m_mode)
	{// ���[�h
	case CManager::MODE_TITLE:		// �^�C�g��
		if (m_pTitle != NULL)
		{// NULL�ȊO�̏ꍇ
			m_pTitle->Update();		// �X�V����
		}

		break;
	case CManager::MODE_GAME:		// �Q�[��
		if (m_pGame != NULL)
		{// NULL�ȊO�̏ꍇ
			if (m_pInputKeyboard->GetTrigger(DIK_P) && CFade::GetFade() == CFade::FADE_NONE || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_START, 0) == true && CFade::GetFade() == CFade::FADE_NONE)
			{
				m_bPause = m_bPause ? false : true;

				if (m_bPause == true)
				{
					m_pPause = new CPause;
					m_pPause->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, 170.0f, 0.0f), D3DXVECTOR3(150.0f, 70.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
				}
				CPause::SetPause(m_bPause);
				m_pSound->PlaySoundA(CSound::SOUND_LABEL_SE000);
			}

			if (m_bPause == true)
			{
				if (m_pPause != NULL)
				{
					m_pPause->Update();
					m_bPause = m_pPause->GetPause();
				}
			}
			else
			{
				m_pGame->Update();		// �X�V����

				if (m_pPause != NULL)
				{
					m_pPause->Uninit();
					delete m_pPause;
					m_pPause = NULL;
				}
			}
		}

		break;

	case CManager::MODE_TUTORIAL:	// �`���[�g���A��
		if (m_pTutorial != NULL)
		{	// NULL�ȊO�̏ꍇ
			m_pTutorial->Update();
		}
		break;

	case CManager::MODE_RESULT:	// ���U���g
		if (m_pResult != NULL)
		{	// NULL�ȊO�̏ꍇ
			m_pResult->Update();
		}
		break;

	case CManager::MODE_RANKING:	// �����L���O
		if (m_pRanking != NULL)
		{	// NULL�ȊO�̏ꍇ
			m_pRanking->Update();
		}
		break;
	}

	// �����_���[
	{
		if (m_pRenderer != NULL)
		{// NULL�ȊO�̏ꍇ
			// �����_���[�X�V����
			m_pRenderer->Update();
		}
	}

	// �J����
	{
		if (m_pCamara != NULL)
		{// NULL�ȊO�̏ꍇ
			// �J�����X�V����
			m_pCamara->Update();
		}
	}

	// ���C�g
	{
		if (m_pLight != NULL)
		{// NULL�ȊO�̏ꍇ
			// ���C�g�X�V����
			m_pLight->Update();
		}
	}
}

//=============================================================================
// �`�揈��										(public)	*** CManager ***
//=============================================================================
void CManager::Draw(void)
{
	// �����_���[
	{
		if (m_pRenderer != NULL)
		{// NULL�ȊO�̏ꍇ
			// �����_���[�`�揈��
			m_pRenderer->Draw();
		}
	}

	// �J����
	{
		if (m_pCamara != NULL)
		{// NULL�ȊO�̏ꍇ
			// �J�����`�揈��
			m_pCamara->SetCamera();
		}
	}
}

//=============================================================================
// ���[�h�ݒ菈��								(public)	*** CManager ***
//=============================================================================
void CManager::SetMode(CManager::MODE mode)
{
	CGame::MODEGAME pGame = m_pGame->GetGame();		// �Q�[���̏�Ԏ擾
	switch (m_mode)
	{// ���[�h�i���݁j
	case CManager::MODE_TITLE:			// �^�C�g��
		if (m_pTitle != NULL)
		{// NULL�ȊO�̏ꍇ
			if (m_mode != mode)
			{// ���[�h���������
				m_pTitle->Unload();		// �A�����[�h
			}
			m_pTitle->Uninit();			// �I������
			delete m_pTitle;
			m_pTitle = NULL;			// NULL��
		}

		m_pSound->StopSound(CSound::SOUND_LABEL_BGM000);

		break;
	case CManager::MODE_GAME:			// �Q�[��
		if (m_pGame != NULL)
		{// NULL�ȊO�̏ꍇ
			if (m_mode != mode)
			{// ���[�h���������
				m_pGame->Unload();		// �A�����[�h
			}
			m_pGame->Uninit();			// �I������
			delete m_pGame;
			m_pGame = NULL;				// NULL��
		}

		m_pSound->StopSound(CSound::SOUND_LABEL_BGM001);

		break;

	case CManager::MODE_TUTORIAL:		// �`���[�g���A��
		if (m_pTutorial != NULL)
		{	// NULL�ȊO�̏ꍇ
			if (m_mode != mode)
			{	// ���[�h���������
				m_pTutorial->Unload();	// �A�����[�h
			}
			m_pTutorial->Uninit();		// �I������
			delete m_pTutorial;
			m_pTutorial = NULL;			// NULL��
		}

		m_pSound->StopSound(CSound::SOUND_LABEL_BGM005);

		break;

	case CManager::MODE_RESULT:		// ���U���g
		if (m_pResult != NULL)
		{	// NULL�ȊO�̏ꍇ
			if (m_mode != mode)
			{	// ���[�h���������
				m_pResult->Unload();	// �A�����[�h
			}
			m_pResult->Uninit();		// �I������
			delete m_pResult;
			m_pResult = NULL;			// NULL��
		}
		break;

	case CManager::MODE_RANKING:		// �����L���O
		if (m_pRanking != NULL)
		{	// NULL�ȊO�̏ꍇ
			m_pRanking->Uninit();		// �I������
			delete m_pRanking;
			m_pRanking = NULL;			// NULL��
		}

		m_pSound->StopSound();
		break;
	}

	//m_pSound->StopSound();

	char cName[32];

	switch (mode)
	{// ���[�h�i����j
	case CManager::MODE_TITLE:			// �^�C�g��
		wsprintf(cName, "Title");
		break;
	case CManager::MODE_GAME:			// �Q�[��
		wsprintf(cName, "Game");
		break;
	case CManager::MODE_TUTORIAL:			// �^�C�g��
		wsprintf(cName, "Tutorial");
		break;
	case CManager::MODE_RESULT:			// �Q�[��
		wsprintf(cName, "Result");
		break;
	case CManager::MODE_RANKING:			// �^�C�g��
		wsprintf(cName, "Ranking");
		break;
	}

	CFont *pFont = CRenderer::GetFont(CFont::FONTNUM_LOG);

	if (pFont != NULL)
	{
		pFont->SetMessage(CFont::SETTYPE_LOG, "\n");
		pFont->SetMessage(CFont::SETTYPE_LOG, "Mode Change[%s]-----\n", cName);
	}

	switch (mode)
	{// ���[�h�i����j
	case CManager::MODE_TITLE:			// �^�C�g��
		if (m_pTitle == NULL)
		{// NULL�̏ꍇ
			m_pTitle = new CTitle;		// �������m��

			if (m_pTitle != NULL)
			{// NULL�ȊO�̏ꍇ
				if (m_mode != mode)
				{// ���[�h���������
					m_pTitle->Load();	// ���[�h
				}
				m_pTitle->Init();		// ����������
				SetPlayNum(0);			// �v���C���[��������
			}
		}

		m_pSound->PlaySoundA(CSound::SOUND_LABEL_BGM000);

		break;
	case CManager::MODE_GAME:			// �Q�[��
		if (m_pGame == NULL)
		{// NULL�̏ꍇ
			m_pGame = new CGame;		// �������m��

			if (m_pGame != NULL)
			{// NULL�ȊO�̏ꍇ
				if (m_mode != mode)
				{// ���[�h���������
					m_pGame->Load();	// ���[�h
				}
				m_pGame->Init();		// ����������
			}
		}

		m_pSound->PlaySoundA(CSound::SOUND_LABEL_BGM001);

		break;

	case CManager::MODE_TUTORIAL:		// �`���[�g���A��
		if (m_pTutorial == NULL)
		{	// NULL�̏ꍇ
			m_pTutorial = new CTutorial;	// �������m��

			if (m_pTutorial != NULL)
			{
				if (m_mode != mode)
				{	// NULL�ȊO�̏ꍇ
					m_pTutorial->Load();	// ���[�h
				}
				m_pTutorial->Init();		// ����������
			}
		}

		m_pSound->PlaySoundA(CSound::SOUND_LABEL_BGM005);

		break;

	case CManager::MODE_RESULT:		// ���U���g
		if (m_pResult == NULL)
		{	// NULL�̏ꍇ
			m_pResult = CResult::Create(pGame);	// �������m��

			if (m_pResult != NULL)
			{
				if (m_mode != mode)
				{	// NULL�ȊO�̏ꍇ
					m_pResult->Load();	// ���[�h
				}
				//m_pResult->SetGameMODE(pGame);	// �Q�[���̏�Ԃ�ݒ�
				m_pResult->Init();		// ����������
			}
		}
		break;

	case CManager::MODE_RANKING:		// �����L���O
		if (m_pRanking == NULL)
		{	// NULL�̏ꍇ
			m_pRanking = new CRanking;	// �������m��
			m_pRanking->Init(D3DXVECTOR3(1000.0f, 260.0f, 0.0f));		// ����������
		}
		break;
	}

	m_mode = mode;			// ���[�h�ύX
}

//=============================================================================
// �f�o�b�O�t�H���g����									(public)	*** CManager ***
//=============================================================================
void CManager::DebugFont(void)
{
	LPDIRECT3DDEVICE9 pDevice = m_pRenderer->GetDevice();

	CFont *pFont[CFont::FONTNUM_MAX] = {};

	// ������
	for (int nCntFont = 0; nCntFont < CFont::FONTNUM_MAX; nCntFont++)
	{
		pFont[nCntFont] = CRenderer::GetFont(nCntFont);
	}

	// �f�o�b�O���\���p�t�H���g(FPS�X�V)
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_TAB) == true)
	{
		if (pFont[CFont::FONTNUM_LOG] != NULL)
		{// NULL�ȊO�̏ꍇ
			pFont[CFont::FONTNUM_LOG]->SetMessage(CFont::SETTYPE_NEW, "");
		}
	}

	if (pFont[CFont::FONTNUM_DATA] != NULL)
	{
		pFont[CFont::FONTNUM_DATA]->SetMessage(CFont::SETTYPE_NEW, "");
	}

	if (pFont[CFont::FONTNUM_TEST] != NULL)
	{
		pFont[CFont::FONTNUM_TEST]->SetMessage(CFont::SETTYPE_NEW, "");
	}

	//----------------------------------------------------------------------------

	// �f�o�b�O�V�X�e��

	static int nSelectNum = 0;
	static int nSelectMax = 4;
	static bool bMain = false;
	static bool bLog = false;
	static bool bDebug = false;
	static bool bDraw = false;
	static bool bData = false;

	static int bDebugNum = -1;
	static bool bDataDips[CScene::OBJTYPE_MAX] = { false };
	static int nFillMode = 1;

	if (CFont::GetDispAll() == true)
	{
		if (m_pInputKeyboard->GetTrigger(DIK_1))
		{
			nSelectNum = (nSelectNum + nSelectMax - 1) % nSelectMax;
		}
		else if (m_pInputKeyboard->GetTrigger(DIK_2))
		{
			nSelectNum = (nSelectNum + 1) % nSelectMax;
		}

		// �f�o�b�O���\���p�t�H���g(FPS�X�V)
		if (pFont[CFont::FONTNUM_COMMAND] != NULL)
		{// NULL�ȊO�̏ꍇ
			pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_NEW, "command->");

			if (bMain == false) pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "\n");
			else if (bLog == true) pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "log\n");
			else if (bDebug == true) pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "debug\n");
			else if (bDraw == true) pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "draw\n");
			else if (bData == true) pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "data\n");

			if (nSelectNum == 0 && bMain == false)
			{
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�Z");
			}
			if (bMain == false)
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@log\n");
			if (bLog == true)
			{
				if (nSelectNum == 0)pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@�Z");
				else pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@");
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@disp [bool:%d]\n", pFont[CFont::FONTNUM_LOG]->GetDisp());
				if (nSelectNum == 1)pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@�Z");
				else pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@");
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@add line\n");
				if (nSelectNum == 2)pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@�Z");
				else pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@");
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@reset\n");
				if (nSelectNum == 3)pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@�Z");
				else pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@");
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@exit\n");
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "\n");
			}

			if ((nSelectNum == 1 && bMain == false))
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�Z");
			if (bMain == false)
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@debug\n");
			if (bDebug == true)
			{
				if (nSelectNum == 0)pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@�Z");
				else pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@");
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@mode\n");
				if (nSelectNum == 1)pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@�Z");
				else pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@");
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@unknow\n");
				if (nSelectNum == 2)pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@�Z");
				else pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@");
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@exit\n");
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "\n");
			}

			if ((nSelectNum == 2 && bMain == false))
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�Z");
			if (bMain == false)
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@draw\n");
			if (bDraw == true)
			{
				if (nSelectNum == 0)pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@�Z");
				else pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@");
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@wire [bool:%d]\n", nFillMode ^ 1);
				if (nSelectNum == 1)pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@�Z");
				else pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@");
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@unknow\n");
				if (nSelectNum == 2)pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@�Z");
				else pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@");
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@exit\n");
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "\n");
			}

			if ((nSelectNum == 3 && bMain == false))
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�Z");
			if (bMain == false)
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@data\n");
			if (bData == true)
			{
				if (nSelectNum == 0)pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@�Z");
				else pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@");
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@disp [bool:%d]\n", pFont[CFont::FONTNUM_DATA]->GetDisp());
				if (nSelectNum == 1)pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@�Z");
				else pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@");
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@player\n");
				if (nSelectNum == 2)pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@�Z");
				else pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@");
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@camera\n");
				if (nSelectNum == 3)pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@�Z");
				else pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@");
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "�@exit\n");
				pFont[CFont::FONTNUM_COMMAND]->SetMessage(CFont::SETTYPE_ADD, "\n");
			}
		}

		if (m_pInputKeyboard->GetTrigger(DIK_3))
		{
			if (bMain == false)
			{// ���C�����j���[���
				switch (nSelectNum)
				{// ���j���[�ԍ�
				case 0:					
					bLog = true;
					nSelectMax = 4;
					break;
				case 1:
					bDebug = true;
					nSelectMax = 3;
					break;
				case 2:
					bDraw = true;
					nSelectMax = 3;
					break;
				case 3:
					bData = true;
					nSelectMax = 4;
					break;
				}

				bMain = true;
				nSelectNum = 0;		// �I��ԍ�������
			}
			else if (bLog == true)
			{// �f�o�b�O���j���[
				switch (nSelectNum)
				{
				case 0:
					pFont[CFont::FONTNUM_LOG]->SetDisp(pFont[CFont::FONTNUM_LOG]->GetDisp() ? false : true);
					break;
				case 1:
					pFont[CFont::FONTNUM_LOG]->SetMessage(CFont::SETTYPE_LOG, "\n");
					break;
				case 2:
					pFont[CFont::FONTNUM_LOG]->SetMessage(CFont::SETTYPE_NEW, "");
					break;
				case 3:
					bLog = false;
					bMain = false;
					nSelectNum = 0;
					nSelectMax = 4;
					break;
				}
			}
			else if (bDebug == true)
			{// �f�o�b�O���j���[
				switch (nSelectNum)
				{
				case 0:
					bDebugNum = 0;
					break;
				case 1:
					bDebugNum = 1;
					break;
				case 2:
					bDebugNum = -1;
					bDebug = false;
					bMain = false;
					nSelectNum = 0;
					nSelectMax = 4;
					break;
				}
			}
			else if (bDraw == true)
			{// �`�惁�j���[
				switch (nSelectNum)
				{
				case 0:
					nFillMode = (nFillMode + 1) % 2;
					pDevice->SetRenderState(D3DRS_FILLMODE, (nFillMode + 2));			// ���C���[�t���[��
					break;
				case 1:
					break;
				case 2:
					bDraw = false;
					bMain = false;
					nSelectNum = 0;
					nSelectMax = 4;
					break;
				}
			}
			else if (bData == true)
			{// �f�[�^���j���[
				switch (nSelectNum)
				{
				case 0:
					pFont[CFont::FONTNUM_DATA]->SetDisp(pFont[CFont::FONTNUM_DATA]->GetDisp() ? false : true);
					break;
				case 1:
					bDataDips[CScene::OBJTYPE_PLAYER] = bDataDips[CScene::OBJTYPE_PLAYER] ? false : true;
					break;
				case 2:
					bDataDips[CScene::OBJTYPE_CAMERA] = bDataDips[CScene::OBJTYPE_CAMERA] ? false : true;
					break;
				case 3:
					bData = false;
					bMain = false;
					nSelectNum = 0;
					nSelectMax = 4;
					break;
				}
			}
		}

		if (bDebug == true)
		{// �f�o�b�O���j���[
			switch (bDebugNum)
			{
			case 0:
				pFont[CFont::FONTNUM_DEBUG]->SetMessage(CFont::SETTYPE_ADD, "Mode[Title] : (DIK_4)\n");
				pFont[CFont::FONTNUM_DEBUG]->SetMessage(CFont::SETTYPE_ADD, "Mode[Game] : (DIK_5)\n");

				if (CFade::GetFade() == CFade::FADE_NONE)
				{
					if (CManager::GetInputKeyboard()->GetTrigger(DIK_4))		CFade::Create(CManager::MODE_TITLE, CFade::FADE_OUT);
					else if (CManager::GetInputKeyboard()->GetTrigger(DIK_5))	CFade::Create(CManager::MODE_GAME, CFade::FADE_OUT);
				}
				break;
			}
		}

		for (int nCntObj = 0; nCntObj < CScene::OBJTYPE_MAX; nCntObj++)
		{
			if (bDataDips[nCntObj] == true)
			{
				pFont[CFont::FONTNUM_DATA]->SetMessage(CFont::SETTYPE_ADD, "%s", CFont::GetMessageData((CScene::OBJTYPE)nCntObj));				
			}
		}
	}

	for (int nCntObj = 0; nCntObj < CScene::OBJTYPE_MAX; nCntObj++)
	{
		CFont::SetMessageData((CScene::OBJTYPE)nCntObj, CFont::SETTYPE_NEW, "");
	}
}