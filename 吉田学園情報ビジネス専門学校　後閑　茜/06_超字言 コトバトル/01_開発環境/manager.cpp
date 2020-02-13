//=============================================================================
//
// �}�l�[�W������ [manager.cpp]
// Author : �ڍ� ������
//
//=============================================================================
#include "manager.h"
#include "main.h"

#include "scene2D.h"
#include "scene3D.h"
#include "sceneX.h"
#include "renderer.h"
#include "input.h"
#include "InputKeyboard.h"
#include "camera.h"
#include "light.h"
#include "debugProc.h"
#include "fade.h"
#include "game.h"
#include "sound.h"
#include "title.h"
#include "result.h"
#include "tutorial.h"
#include "select.h"
#include "CharaSelect.h"
#include "StageSelect.h"
#include "mask.h"
#include "Command.h"
#include "CameraManager.h"

#include "player.h"
#include "tube.h"
#include "SetWord.h"
#include "meshField.h"
#include "point.h"
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
//CCamera *CManager::m_pCamera = NULL;
CCameraManager* CManager::m_pCameraManager = NULL;
CLight *CManager::m_pLight = NULL;
CDebugProc *CManager::m_pDebugProc = NULL;
CMask *CManager::m_pMask = NULL;
CGame *CManager::m_pGame = NULL;
CTitle *CManager::m_pTitle = NULL;
CSelect *CManager::m_pSelect = NULL;
CCharaSelect *CManager::m_pCharaSelect = NULL;
CStageSelect *CManager::m_pStageSelect = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CResult *CManager::m_pResult = NULL;
CFade *CManager::m_pFade = NULL;
CCharacterMove *CManager::m_pCharacterMove = NULL;
CInputXPad *CManager::m_pXInput[MAX_PLAYER] = {};
CManager::MODE CManager::m_mode = CManager::MODE_TITLE;	//�Q�[���N�����̃��[�h
CSound	*CManager::m_pSound[MAX_SOUND] = {};

#ifdef _DEBUG
//�񐔃J�E���g�p true�Ȃ烊�s�[�g���[�h
bool CManager::bRepeatGame = false;

int CManager::nTitleCnt    = 0;
int CManager::nSelectCnt   = 0;
int CManager::nTutoCnt     = 0;
int CManager::nCharaSelCnt = 0;
int CManager::nStaSelCnt   = 0;
int CManager::nGameCnt     = 0;
int CManager::nResultCnt   = 0;
#endif

//=============================================================================
// �}�l�[�W���N���X�̃R���X�g���N�^
//=============================================================================
CManager::CManager()
{
}

//==================================================6===========================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// �}�l�[�W������������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	if (m_pRenderer == NULL)
	{
		// �����_�����O�N���X�̐���
		m_pRenderer = new CRenderer;

		if (m_pRenderer != NULL)
		{
			// ����������
			if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
			{
				return -1;
			}
		}
	}

	//�J�����E���C�g�̐���
	if (ObjCreate(m_pCameraManager))
	{
		m_pCameraManager->CreateCamera("DEFAULT_CAMERA", CCamera::TYPE_TPS,
			D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f);
		m_pCameraManager->SetCameraViewPort("DEFAULT_CAMERA", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}


	if (m_pLight == NULL)
	{
		// ���C�g�N���X�̐���
		m_pLight = new CLight;

		if (m_pLight != NULL)
		{
			m_pLight->Init();
		}
	}

	if (m_pInputKeyboard == NULL)
	{
		// ���̓N���X(�L�[�{�[�h)�̐���
		m_pInputKeyboard = new CInputKeyboard;

		if (m_pInputKeyboard != NULL)
		{
			m_pInputKeyboard->Init(hInstance, hWnd);
		}
	}
	for (int nCntXPad = 0; nCntXPad < MAX_PLAYER; nCntXPad++)
	{
		//���̓N���X(XInput�R���g���[���[)�̐���
		if (m_pXInput[nCntXPad] == NULL)
		{
			m_pXInput[nCntXPad] = new CInputXPad;
			if (m_pXInput[nCntXPad] != NULL)
			{
				m_pXInput[nCntXPad]->Init(hInstance, hWnd);
			}
		}
	}

	if (m_pMask == NULL)
	{
		m_pMask = CMask::Create();
	}

	//�T�E���h
	for (int nCnt = 0; nCnt < MAX_SOUND; nCnt++)
	{
		m_pSound[nCnt] = new CSound;
		if (m_pSound[nCnt] != NULL)
		{
			m_pSound[nCnt]->InitSound(hWnd);
		}
	}
#ifdef _DEBUG
	if (m_pDebugProc == NULL)
	{
		// �f�o�b�N�\���N���X�̐���
		m_pDebugProc = new CDebugProc;

		if (m_pDebugProc != NULL)
		{
			m_pDebugProc->Init();
		}
	}
#endif

	//�e�N�X�`�����[�h
	CTexture::Load();
	//���f�����[�h
	CLoad::LoadModel();

	if (m_pFade == NULL)
	{
		//�t�F�[�h�̐���
		m_pFade = CFade::Create();

		if (m_pFade != NULL)
		{
			m_pFade->SetFade(m_mode, m_pFade->FADE_IN);
		}
	}

	// ���[�h�ؑ�
	//SetMode(m_mode);

	//�Q�[���X�^�[�g
	CCommand::RegistCommand("ENTER", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_RETURN);
	CCommand::RegistCommand("ENTER", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_TRIGGER, CInputXPad::XPAD_START);

	//����
	CCommand::RegistCommand("DECISION", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_RETURN);
	CCommand::RegistCommand("DECISION", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_TRIGGER, CInputXPad::XPAD_A);
	CCommand::RegistCommand("DECISION", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_TRIGGER, CInputXPad::XPAD_RIGHT_SHOULDER);

	CCommand::RegistCommand("RIGHT", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_D);
	CCommand::RegistCommand("RIGHT", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_TRIGGER, CInputXPad::XPAD_RIGHT);

	CCommand::RegistCommand("LEFT", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_A);
	CCommand::RegistCommand("LEFT", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_TRIGGER, CInputXPad::XPAD_LEFT);

	CCommand::RegistCommand("UP", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_W);
	CCommand::RegistCommand("UP", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_TRIGGER, CInputXPad::XPAD_UP);

	CCommand::RegistCommand("DOWN", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_S);
	CCommand::RegistCommand("DOWN", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_TRIGGER, CInputXPad::XPAD_DOWN);

	CCommand::RegistCommand("PAUSE", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_P);
	CCommand::RegistCommand("PAUSE", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_TRIGGER, CInputXPad::XPAD_START);

	CCommand::RegistCommand("DELETE", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_BACKSPACE);
	CCommand::RegistCommand("DELETE", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_X);
	CCommand::RegistCommand("DELETE", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_LEFT_SHOULDER);

	CCommand::RegistCommand("DEBUG2D", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_O);

	return S_OK;
}

//=============================================================================
// �}�l�[�W���I������
//=============================================================================
void CManager::Uninit(void)
{
	if (m_pMask != NULL)
	{// �t�F�[�h�̏I��
		m_pMask->Uninit();
		delete m_pMask;
		m_pMask = NULL;
	}

	if (m_pRenderer != NULL)
	{// �����_�����O�N���X�̔j��
		// �I������
		m_pRenderer->Uninit();

		// ���������J��
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//�J����
	ObjRelease(m_pCameraManager);


	if (m_pLight != NULL)
	{// ���C�g�N���X�̔j��
	 // �I������
		m_pLight->Uninit();

		// ���������J��
		delete m_pLight;
		m_pLight = NULL;
	}

	if (m_pInputKeyboard != NULL)
	{// �����_�����O�N���X�̔j��
		 // �I������
		m_pInputKeyboard->Uninit();

		// ���������J��
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
	for (int nCntXPad = 0; nCntXPad < MAX_PLAYER; nCntXPad++)
	{
		if (m_pXInput[nCntXPad] != NULL)
		{
			// �I������
			m_pXInput[nCntXPad]->Uninit();

			// ���������J��
			delete m_pXInput[nCntXPad];
			m_pXInput[nCntXPad] = NULL;
		}

	}

	//�e�N�X�`���̔j��
	CTexture::Unload();
	//���f���̔j��
	CLoad::UnloadModel();
	//�t�F�[�h�N���X�̔j��
	if (m_pFade != NULL)
	{
		// �I������
		m_pFade->Uninit();

		//�������̊J��
		delete m_pFade;

		//NULL�ɂ���
		m_pFade = NULL;
	}

#ifdef _DEBUG
	if (m_pDebugProc != NULL)
	{// �f�o�b�N�\���N���X�̔j��
		// �I������
		m_pDebugProc->Uninit();

		// ���������J��
		delete m_pDebugProc;
		m_pDebugProc = NULL;
	}
#endif

	switch (m_mode)
	{
		//�^�C�g�����[�h�̏I������
	case CManager::MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;

			//�^�C�g����BGM���~�߂�
			m_pSound[0]->StopSound(CSound::SOUND_LABEL_BGM_TITLE);
		}
		break;

	case CManager::MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			delete m_pTutorial;
			m_pTutorial = NULL;
		}
		break;

		//�Q�[�����[�h�̏I������
	case CManager::MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		break;

		//���U���g���[�h�̏I������
	case CManager::MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
			//�^�C�g����BGM���~�߂�
		//	m_pSound[0]->StopSound(CSound::SOUND_LABEL_BGM_RESULT);
		}
		break;

		//�Z���N�g���[�h�̏I������
	case CManager::MODE_SELECT:
		if (m_pSelect != NULL)
		{
			m_pSelect->Uninit();
			delete m_pSelect;
			m_pSelect = NULL;

			//�^�C�g����BGM���~�߂�
			//	m_pSound[0]->StopSound(CSound::SOUND_LABEL_BGM_RESULT);
		}
		break;
		//�L�����Z���N�g���[�h�̏I������
	case CManager::MODE_CHARASELECT:
		if (m_pCharaSelect != NULL)
		{
			m_pCharaSelect->Uninit();
			delete m_pCharaSelect;
			m_pCharaSelect = NULL;
		}
		break;
		//�X�e�[�W�Z���N�g���[�h�̏I������
	case CManager::MODE_STAGESELECT:
		if (m_pStageSelect != NULL)
		{
			m_pStageSelect->Uninit();
			delete m_pStageSelect;
			m_pStageSelect = NULL;
		}
		break;
	}

	//�T�E���h
	for (int nCnt = 0; nCnt < MAX_SOUND; nCnt++)
	{
		if (m_pSound[nCnt] != NULL)
		{
			m_pSound[nCnt]->UninitSound();
			delete m_pSound[nCnt];
			m_pSound[nCnt] = NULL;
		}
	}

	CCommand::ResetCommandAll();
	// �S�ẴI�u�W�F�N�g�����
	CScene::ReleseAll();
}

//=============================================================================
// �}�l�[�W���X�V����
//=============================================================================
void CManager::Update(void)
{
#ifdef _DEBUG
	// �f�o�b�N�\��������
	CDebugProc::ReleseStr();
	//�񐔃J�E���g�p
	CDebugProc::Print("cn", "nTitleCnt    = ", nTitleCnt);
	CDebugProc::Print("cn", "nSelectCnt   = ", nSelectCnt);
	CDebugProc::Print("cn", "nTutoCnt     = ", nTutoCnt);
	CDebugProc::Print("cn", "nCharaSelCnt = ", nCharaSelCnt);
	CDebugProc::Print("cn", "nStaSelCnt   = ", nStaSelCnt);
	CDebugProc::Print("cn", "nGameCnt     = ", nGameCnt);
	CDebugProc::Print("cn", "nResultCnt   = ", nResultCnt);

	CDebugProc::Print("cn", "FADESTATE = ", (int)m_pFade->GetFade());
#endif

	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	if (m_pRenderer != NULL)
	{// �����_���[�X�V����
		m_pRenderer->Update();
	}

	//�J����
	if (m_pCameraManager != NULL)
	{
		m_pCameraManager->Update();
	}

	if (m_pLight != NULL)
	{// ���C�g�X�V����
		m_pLight->Update();
	}

	if (m_pInputKeyboard != NULL)
	{// �L�[�{�[�h���͍X�V����
		m_pInputKeyboard->Update();
	}

	bool bConnect = false;
	for (int nCntXPad = 0; nCntXPad < MAX_PLAYER; nCntXPad++)
	{
		if (m_pXInput[nCntXPad] != NULL)
		{
			// XInput�R���g���[���X�V����
			m_pXInput[nCntXPad]->Update();
			bConnect = m_pXInput[nCntXPad]->GetConnect();
		}
		m_pDebugProc->Print("cn", "XINPUT_CONNECT ::", (bConnect == true) ? 1 : 0);
	}
	if (m_pMask != NULL)
	{// �t�F�[�h�X�V����
		m_pMask->Update();
	}

	if (m_pFade != NULL)
	{//�t�F�[�h�̍X�V����
		m_pFade->Update();
	}

	switch (m_mode)
	{
		//�^�C�g�����[�h�̍X�V����
	case CManager::MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Update();
		}
		break;

	case CManager::MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Update();
		}
		break;

		//�Q�[�����[�h�̍X�V����
	case CManager::MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pSound[0]->SetVolume(CSound::SOUND_LABEL_BGM_GAME000, 0.2f);
			m_pGame->Update();
		}
		break;

		//���U���g���[�h�̍X�V����
	case CManager::MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Update();
		}
		break;

		//�Z���N�g���[�h�̍X�V����
	case CManager::MODE_SELECT:
		if (m_pSelect != NULL)
		{
			m_pSound[0]->SetVolume(CSound::SOUND_LABEL_BGM_SELECT, 0.7f);

			m_pSelect->Update();
		}
		//�L�����Z���N�g���[�h�X�V����
	case CManager::MODE_CHARASELECT:
		if (m_pCharaSelect != NULL)
		{
			m_pCharaSelect->Update();
		}
		break;
		//�X�e�[�W�Z���N�g���[�h�̍X�V����
	case CManager::MODE_STAGESELECT:
		if (m_pStageSelect != NULL)
		{
			m_pStageSelect->Update();
		}
		break;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{// �����_���[�`�揈��
		m_pRenderer->Draw();
	}

	switch (m_mode)
	{
		//���U���g���[�h�̍X�V����
	case CManager::MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Draw();
		}
		break;
	}
}

//=============================================================================
// �����_���[�̎擾
//=============================================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
// ���͏��̎擾
//=============================================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
// �}�X�N�̎擾
//=============================================================================
CCharacterMove *CManager::GetCharacterMove(void)
{
	return m_pCharacterMove;
}

//=============================================================================
// �}�X�N�̎擾
//=============================================================================
CMask *CManager::GetMask(void)
{
	return m_pMask;
}

//=============================================================================
// �}�l�[�W���[�N���X �T�E���h���擾
//=============================================================================
CSound *CManager::GetSound(int nNum)
{
	return m_pSound[nNum];
}

//=============================================================================
// ���[�h�̐ݒ�
//=============================================================================
void CManager::SetMode(MODE mode)
{
	switch (m_mode)
	{
	case CManager::MODE_TITLE:
		//�^�C�g���N���X�̔j��
		if (m_pTitle != NULL)
		{
			// �I������
			m_pTitle->Uninit();

			//�������̊J��
			delete m_pTitle;

			//NULL�ɂ���
			m_pTitle = NULL;

			//�^�C�g����BGM���~�߂�
			m_pSound[0]->StopSound(CSound::SOUND_LABEL_BGM_TITLE);
		}
		break;
	case CManager::MODE_SELECT:
		//���U���g�N���X�̔j��
		if (m_pSelect != NULL)
		{
			// �I������
			m_pSelect->Uninit();

			//�������̊J��
			delete m_pSelect;

			//NULL�ɂ���
			m_pSelect = NULL;

			//���U���g��BGM���~�߂�
			m_pSound[0]->StopSound(CSound::SOUND_LABEL_BGM_SELECT);
		}
		break;
	case CManager::MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			delete m_pTutorial;
			m_pTutorial = NULL;
			//�Q�[����BGM���~�߂�
			m_pSound[0]->StopSound(CSound::SOUND_LABEL_BGM_TUTORIAL);
		}
		break;
	case CManager::MODE_CHARASELECT:
		//�L�����Z���N�g���[�h�j��
		if (m_pCharaSelect != NULL)
		{
			// �I������
			m_pCharaSelect->Uninit();
			//�������̊J��
			delete m_pCharaSelect;
			//NULL�ɂ���
			m_pCharaSelect = NULL;
			//�Q�[����BGM���~�߂�
			m_pSound[0]->StopSound(CSound::SOUND_LABEL_BGM_CHARACTERSELECT);
		}
		break;
	case CManager::MODE_STAGESELECT:
		//�X�e�[�W�Z���N�g���[�h�̔j��
		if (m_pStageSelect != NULL)
		{
			// �I������
			m_pStageSelect->Uninit();
			//�������̊J��
			delete m_pStageSelect;
			//NULL�ɂ���
			m_pStageSelect = NULL;
			//�Q�[����BGM���~�߂�
			m_pSound[0]->StopSound(CSound::SOUND_LABEL_BGM_STAGESELECT);
		}
		break;
	case CManager::MODE_GAME:
		//�Q�[���N���X�̔j��
		if (m_pGame != NULL)
		{
			// �I������
			m_pGame->Uninit();

			delete m_pGame;

			m_pGame = NULL;

			//�Q�[����BGM���~�߂�
			m_pSound[0]->StopSound(CSound::SOUND_LABEL_BGM_GAME000);
		}
		break;

	case CManager::MODE_RESULT:
		//���U���g�N���X�̔j��
		if (m_pResult != NULL)
		{
			// �I������
			m_pResult->Uninit();
			//NULL�ɂ���
			m_pResult = NULL;
			CScene::ReleseAll();
			//���U���g��BGM���~�߂�
			m_pSound[0]->StopSound(CSound::SOUND_LABEL_BGM_RANKING);
		}
		break;
	}
	m_mode = mode;

	//�g���Ă����e�N�X�`�������
	CTexture::ReleaseAll();

	switch (mode)
	{
	case CManager::MODE_TITLE:
		//�^�C�g���̏�����
		if (m_pTitle == NULL)
		{//�L�[�{�[�h�̃������𓮓I�m��
			m_pTitle = new CTitle;
			if (m_pTitle != NULL)
			{//�^�C�g����BGM���Đ�
				m_pSound[0]->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);
				// ����������
				m_pTitle->Init();
#ifdef _DEBUG
				//�񐔃J�E���g�p
				nTitleCnt++;
#endif

			}
			else
			{
				MessageBox(0, "NULL����Ȃ��ł�", "�x��", MB_OK);
			}
		}
		else
		{
			MessageBox(0, "aaaNULL�ł���", "�x��", MB_OK);
		}

		break;
	case CManager::MODE_CHARASELECT:
		//�L�����Z���N�g���[�h������
		if (m_pCharaSelect == NULL)
		{//�L�����Z���N�g���[�h�������𓮓I�m��
			m_pCharaSelect = new CCharaSelect;
			if (m_pCharaSelect != NULL)
			{//�L�����Z���N�g��BGM���Đ�
				m_pSound[0]->PlaySound(CSound::SOUND_LABEL_BGM_CHARACTERSELECT);
				// ����������
				m_pCharaSelect->Init();
#ifdef _DEBUG
				//�񐔃J�E���g�p
				nCharaSelCnt++;
#endif
			}
			else
			{
				MessageBox(0, "NULL����Ȃ��ł�", "�x��", MB_OK);
			}
		}
		else
		{
			MessageBox(0, "NULL�ł���", "�x��", MB_OK);
		}
		break;
	case CManager::MODE_STAGESELECT:
		//�X�e�[�W�Z���N�g���[�h�̏�����
		if (m_pStageSelect == NULL)
		{//�X�e�[�W�Z���N�g���[�h�̃������𓮓I�m��
			m_pStageSelect = new CStageSelect;
			if (m_pStageSelect != NULL)
			{//�X�e�[�W�Z���N�g���[�h��BGM���Đ�
				m_pSound[0]->PlaySound(CSound::SOUND_LABEL_BGM_STAGESELECT);
				// ����������
				m_pStageSelect->Init();
#ifdef _DEBUG
				//�񐔃J�E���g�p
				nStaSelCnt++;
#endif
			}
			else
			{
				MessageBox(0, "NULL����Ȃ��ł�", "�x��", MB_OK);
			}
		}
		else
		{
			MessageBox(0, "NULL�ł���", "�x��", MB_OK);
		}
		break;
	case CManager::MODE_GAME:
		//�Q�[���̏�����
		if (m_pGame == NULL)
		{//�Q�[���̃������𓮓I�m��
			m_pGame = new CGame;
			if (m_pGame != NULL)
			{
				m_pSound[0]->PlaySound(m_pSound[0]->SOUND_LABEL_BGM_GAME000);
				// ����������
				m_pGame->Init();
#ifdef _DEBUG
				//�񐔃J�E���g�p
				nGameCnt++;
#endif
			}
			else
			{
				MessageBox(0, "NULL����Ȃ��ł�", "�x��", MB_OK);
			}
		}
		else
		{
			MessageBox(0, "NULL�ł���", "�x��", MB_OK);
		}
		break;

	case CManager::MODE_RESULT:
		//���U���g�̏�����
		if (m_pResult == NULL)
		{//���U���g�̃������𓮓I�m��
			m_pResult = new CResult;
			if (m_pResult != NULL)
			{
				//���U���g��BGM���Đ�
				m_pSound[0]->PlaySound(CSound::SOUND_LABEL_BGM_RANKING);
				// ����������
				m_pResult->Init();
#ifdef _DEBUG
				//�񐔃J�E���g�p
				nResultCnt++;
#endif
			}
			else
			{
				MessageBox(0, "NULL����Ȃ��ł�", "�x��", MB_OK);
			}
		}
		else
		{
			MessageBox(0, "NULL�ł���", "�x��", MB_OK);
		}
		break;

	case CManager::MODE_TUTORIAL:
		if (m_pTutorial == NULL)
		{
			m_pTutorial = new CTutorial;
			if (m_pTutorial != NULL)
			{
				//���U���g��BGM���Đ�
				m_pSound[0]->PlaySound(CSound::SOUND_LABEL_BGM_TUTORIAL);
				m_pTutorial->Init();
#ifdef _DEBUG
				//�񐔃J�E���g�p
				nTutoCnt++;
#endif
			}
			else
			{
				MessageBox(0, "NULL����Ȃ��ł�", "�x��", MB_OK);
			}
		}
		else
		{
			MessageBox(0, "NULL�ł���", "�x��", MB_OK);
		}
		break;
	case CManager::MODE_SELECT:
		//���U���g�̏�����
		if (m_pSelect == NULL)
		{
			//���U���g�̃������𓮓I�m��
			m_pSelect = new CSelect;

			if (m_pSelect != NULL)
			{//���U���g��BGM���Đ�
				m_pSound[0]->PlaySound(CSound::SOUND_LABEL_BGM_SELECT);
				// ����������
				m_pSelect->Init();
#ifdef _DEBUG
				//�񐔃J�E���g�p
				nSelectCnt++;
#endif
			}
			else
			{
				MessageBox(0, "NULL����Ȃ��ł�", "�x��", MB_OK);
			}
		}
		else
		{
			MessageBox(0, "NULL�ł���", "�x��", MB_OK);
		}
		break;
	}

}

//=============================================================================
// �v���C���[�̎擾
//=============================================================================
CPlayer* CManager::GetPlayer(int nID)
{
	switch (m_mode)
	{
	case MODE_GAME:
		return CGame::GetPlayer(nID);
		break;
	case MODE_TUTORIAL:
		return CTutorial::GetPlayer(nID);
		break;
	case MODE_RESULT:
		return CResult::GetPlayer(nID);
		break;
	}

	return NULL;
}

//=============================================================================
// ���̎擾
//=============================================================================
CTube* CManager::GetTube(int nID)
{
	switch (m_mode)
	{
	case MODE_GAME:
		return CGame::GetTube(nID);
		break;
	case MODE_TUTORIAL:
		return CTutorial::GetTube(nID);
		break;
	}

	return NULL;
}

//=============================================================================
// �����z�u�I�u�W�F�N�g�̎擾
//=============================================================================
CSetWord* CManager::GetWordCreate(void)
{
	switch (m_mode)
	{
	case MODE_GAME:
		return CGame::GetWordCreate();
		break;
	case MODE_TUTORIAL:
		return CTutorial::GetWordCreate();
		break;
	}
	return NULL;
}

//=============================================================================
//	���I�u�W�F�N�g�̎擾
//=============================================================================
CMeshField* CManager::GetMeshField(void)
{
	switch (m_mode)
	{
	case MODE_GAME:
		return CGame::GetMeshField();
		break;
	case MODE_TUTORIAL:
		return CTutorial::GetMeshField();
		break;
	}

	return NULL;
}

CPoint* CManager::GetPoint(int nNum)
{
	switch (m_mode)
	{
	case MODE_GAME:
		return CGame::GetPoint(nNum);
		break;
	case MODE_TUTORIAL:
		return CTutorial::GetPoint(nNum);
		break;
	}

	return NULL;

}