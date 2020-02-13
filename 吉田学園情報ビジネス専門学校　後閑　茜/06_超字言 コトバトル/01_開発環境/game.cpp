//=============================================================================
//
// ���C������ [game.cpp]
// Author :
//
//=============================================================================
#include "game.h"
#include "manager.h"
#include "light.h"
#include "scene3D.h"
#include "sceneX.h"
#include "meshField.h"
#include "game.h"
#include "debugProc.h"
#include "scene.h"
#include "fade.h"
#include "input.h"
#include "InputKeyboard.h"
#include "CameraManager.h"
#include "word_manager.h"
#include "word.h"
#include "tube.h"
#include "time.h"
#include "PlayerNumSelect.h"
#include "object.h"
#include "point.h"
#include "SetWord.h"
#include"StageSelect.h"
#include "pause.h"

#include "PlayerNumSelect.h"

#include "player.h"
#include "charactor.h"
#include "SetObject.h"
#include "loadText.h"
#include "wall.h"

#include "result.h"
#include "effect.h"
//============================================================================
//	�}�N����`
//============================================================================
#define CAMERA_LENGTH_1P_PLAY (250.0f)				//�J�����̋���(1p�v���C�p)
#define CAMERA_LENGTH_2P_PLAY (220.0f)				//�J�����̋���(2p�v���C�p)
#define CAMERA_LENGTH_3P4P_PLAY (180.0f)			//�J�����̋���(3p4p�v���C�p)
#define CAMERA_LENGTH_TOPVIEW_PLAY (650.0f)			//�J�����̋���(3p�v���C���̃g�b�v�r���[�J�����p)

#define CAMERA_ROTX (-D3DX_PI / 2)		//�J�����̃f�t�H���g�p�x(X)
#define CAMERA_POSR (100.0f)		//�J�����̒����_

#define PLAYER_INITPOS (50.0f)		//
//--------------------------
// �@�B�X�e�[�W
//--------------------------
#define MACHINE_STAGE_00	("data\\TEXT\\�@�B�X�e�[�W\\Machine_Stage_0.txt")
#define MACHINE_STAGE_01	("data\\TEXT\\�@�B�X�e�[�W\\Machine_Stage_1.txt")
#define MACHINE_STAGE_02	("data\\TEXT\\�@�B�X�e�[�W\\Machine_Stage_2.txt")
#define FILE_NAME00		("data\\TEXT\\�@�B�X�e�[�W\\�����o���ʒu\\Machine_Word_0.txt")
#define FILE_NAME01		("data\\TEXT\\�@�B�X�e�[�W\\�����o���ʒu\\Machine_Word_1.txt")
#define FILE_NAME02		("data\\TEXT\\�@�B�X�e�[�W\\�����o���ʒu\\Machine_Word_2.txt")

//--------------------------
// �V��X�e�[�W
//--------------------------
#define MACHINE_STAGE_10	("data\\TEXT\\�V��X�e�[�W\\Machine_Stage_0.txt")
#define MACHINE_STAGE_11	("data\\TEXT\\�V��X�e�[�W\\Machine_Stage_1.txt")
#define MACHINE_STAGE_12	("data\\TEXT\\�V��X�e�[�W\\Machine_Stage_2.txt")
#define FILE_NAME10		("data\\TEXT\\�V��X�e�[�W\\�����o���ʒu\\Machine_Word_0.txt")
#define FILE_NAME11		("data\\TEXT\\�V��X�e�[�W\\�����o���ʒu\\Machine_Word_1.txt")
#define FILE_NAME12		("data\\TEXT\\�V��X�e�[�W\\�����o���ʒu\\Machine_Word_2.txt")

//============================================================================
//�ÓI�����o�ϐ��錾
//============================================================================
CPlayer *CGame::m_pPlayer[MAX_PLAYER] = {};
CTube *CGame::m_apTube[MAX_PLAYER] = {};
CMeshField *CGame::m_pMeshField = NULL;
CPoint *CGame::m_pPoint[MAX_PLAYER] = {};
CSetWord *CGame::m_pWordCreate = NULL;
CWall *CGame::m_pWall = NULL;
CPlayer::PLAYER_TYPE CGame::m_type[MAX_PLAYER] = {};
int CGame::m_nNumStage = NULL;
CPause* CGame::m_pPause = NULL;
bool CGame::m_bStageSet = false;
//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CGame::CGame()
{
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// ����������
//=============================================================================
void CGame::Init(void)
{
	//	�G�t�F�N�g�̃e�L�X�g�̖��O�̓ǂݍ���
	CEffect::LoadNameEffect();			//	�G�t�F�N�g�̃e�L�X�g�ǂݍ���
	CEffect::LoadDataEffect();			//	�G�t�F�N�g�̃f�[�^�ǂݍ���
	CEffect::Load();					//	�G�t�F�N�g�̓ǂݍ���
	m_nChangeNum = 0;
	m_nNumStage = 0;
	m_bStageSet = false;

	m_nNumStage = CStageSelect::GetStageState();
	if (m_nNumStage == NULL)
	{//	�X�e�[�W�I����NULL���������ꍇ
		m_nNumStage = 0;
	}
	//�J�����̃N���G�C�g
	CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();
	CameraSetting((int)NumPlayer);

	//���b�V���t�B�[���h����
	m_pMeshField = NULL;
	if (m_pMeshField == NULL)
	{
		m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20, 20, 40.0f);
	}
	switch (m_nNumStage)
	{
	case 0:
		//	�@�B
		m_pcStageName[0][0] = { MACHINE_STAGE_00 };
		m_pcStageName[0][1] = { MACHINE_STAGE_01 };
		m_pcStageName[0][2] = { MACHINE_STAGE_02 };
		m_pcStageNameWord[0][0] = { FILE_NAME00 };
		m_pcStageNameWord[0][1] = { FILE_NAME01 };
		m_pcStageNameWord[0][2] = { FILE_NAME02 };


		m_pWall = NULL;

		if (m_pWall == NULL)
		{
			//	���̕�
			m_pWall = CWall::Create(D3DXVECTOR3(0.0f, -100.0f, 400.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(5.0f, 5.0f), 0, 0);
			m_pWall = CWall::Create(D3DXVECTOR3(0.0f, -100.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(5.0f, 5.0f), 0, 0);
			m_pWall = CWall::Create(D3DXVECTOR3(400.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(5.0f, 5.0f), 0, 0);
			m_pWall = CWall::Create(D3DXVECTOR3(-400.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(5.0f, 5.0f), 0, 0);
		}
		break;
	case 1:
		//	�V��
		m_pcStageName[1][0] = { MACHINE_STAGE_10 };
		m_pcStageName[1][1] = { MACHINE_STAGE_11 };
		m_pcStageName[1][2] = { MACHINE_STAGE_12 };
		m_pcStageNameWord[1][0] = { FILE_NAME10 };
		m_pcStageNameWord[1][1] = { FILE_NAME11 };
		m_pcStageNameWord[1][2] = { FILE_NAME12 };

		m_pWall = NULL;

		if (m_pWall == NULL)
		{
			//	���̕�
			m_pWall = CWall::Create(D3DXVECTOR3(0.0f, -100.0f, 400.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(5.0f, 5.0f), 0, 0);
			m_pWall = CWall::Create(D3DXVECTOR3(0.0f, -100.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(5.0f, 5.0f), 0, 0);
			m_pWall = CWall::Create(D3DXVECTOR3(400.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(5.0f, 5.0f), 0, 0);
			m_pWall = CWall::Create(D3DXVECTOR3(-400.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(5.0f, 5.0f), 0, 0);
			//	�����̕�
			m_pWall = CWall::Create(D3DXVECTOR3(0.0f, 5.0f, 100.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), D3DXVECTOR3(100.0f, 10.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f), D3DXVECTOR2(5.0f, 2.0f), 0, 5);
			m_pWall = CWall::Create(D3DXVECTOR3(0.0f, 5.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 10.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f), D3DXVECTOR2(5.0f, 2.0f), 0, 5);
			m_pWall = CWall::Create(D3DXVECTOR3(100.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(100.0f, 10.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f), D3DXVECTOR2(5.0f, 2.0f), 0, 5);
			m_pWall = CWall::Create(D3DXVECTOR3(-100.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(100.0f, 10.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f), D3DXVECTOR2(5.0f, 2.0f), 0, 5);
			//	�����̏�
			m_pWall = CWall::Create(D3DXVECTOR3(0.0f, 10.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f), D3DXVECTOR2(5.0f, 5.0f), 0, 5);
			m_pWall = CWall::Create(D3DXVECTOR3(0.0f, 15.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f), D3DXVECTOR2(5.0f, 5.0f), 0, 5);
			//	��������̐�
			m_pWall = CWall::Create(D3DXVECTOR3(200.0f, 1.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(200.0f,20.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f), D3DXVECTOR2(5.0f, 5.0f), 0, 6);
			m_pWall = CWall::Create(D3DXVECTOR3(-200.0f, 1.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(200.0f, 20.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f), D3DXVECTOR2(5.0f, 5.0f), 0, 6);
			m_pWall = CWall::Create(D3DXVECTOR3(0.0f, 1.0f, 200.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 200.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f), D3DXVECTOR2(5.0f, 5.0f), 0, 6);
		}
		break;
	}

	// �v���C���[�̐���
	PlayerSetting((int)NumPlayer);

	CLoadText::LoadFile();		// �����̃��\�[�X�ǂݍ���

	// �����̉���UI(2D)�̐���
	TubeSetting((int)NumPlayer);

	SetPointFrame((int)NumPlayer);	// �|�C���g�̐ݒ�

	//WordCreate();				// �����̐���
	m_pWordCreate = NULL;
	if (m_pWordCreate == NULL)
	{
		m_pWordCreate = CSetWord::Create();
	}

	CSetObject::Create();
	SetStage(m_nNumStage, m_nChangeNum);		// �X�e�[�W����

	CTime::Create((int)NumPlayer);

	//�f�o�b�N�p
	//CTime::SetTimeFlag(false);
	CCommand::RegistCommand("TIMECOUNT_STOP",CCommand::INPUTTYPE_KEYBOARD,CCommand::INPUTSTATE_TRIGGER,DIK_M);

	SetCreateWord();

	//�|�[�Y��ʂ̐���
	m_pPause = CPause::Create();

	//��Ƀe�N�X�`���𐶐����Ă���
	CTexture::GetTexture("���f��_TEX");
	CTexture::GetTexture("WORD");
	CTexture::GetTexture("EXPLOSION");
}
//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
	//���b�V���t�B�[���h�̔j��
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Uninit();
		m_pMeshField = NULL;
	}

	////�ǂ̔j��
	//for (int nCount = 0; nCount < MAX_WALLGAME; nCount++)
	//{
	//	if (m_pWall[nCount] != NULL)
	//	{
	//		m_pWall[nCount]->Uninit();
	//		m_pWall[nCount] = NULL;
	//	}
	//}

	CEffect::Unload();			//	�G�t�F�N�g�̊J��

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (m_pPlayer[nCntPlayer] != NULL)
		{	// �v���C���[�̔j��
			m_pPlayer[nCntPlayer]->Uninit();
			m_pPlayer[nCntPlayer] = NULL;
		}
	}
	for (int nCntTube = 0; nCntTube < MAX_PLAYER; nCntTube++)
	{
		if (m_apTube[nCntTube] != NULL)
		{	// �����̉���UI(2D)�̔j��
			m_apTube[nCntTube]->Uninit();
			m_apTube[nCntTube] = NULL;
		}
	}
	for (int nCntPoint = 0; nCntPoint < MAX_PLAYER; nCntPoint++)
	{
		if (m_pPoint[nCntPoint] != NULL)
		{	// �|�C���g�̔j��
			m_pPoint[nCntPoint]->Uninit();
			m_pPoint[nCntPoint] = NULL;
		}
	}


	if (m_pWordCreate != NULL)
	{
		m_pWordCreate->Uninit();
		m_pWordCreate = NULL;
	}

	if (m_pPause != NULL)
	{
		m_pPause->Uninit();
		m_pPause = NULL;
	}

	//�s�v�ȃJ�������폜
	CCameraManager *pCameraManager = CManager::GetCameraManager();
	if (pCameraManager != NULL)
	{
		pCameraManager->DeleteCamera("1P_CAMERA");
		pCameraManager->DeleteCamera("2P_CAMERA");
		pCameraManager->DeleteCamera("3P_CAMERA");
		pCameraManager->DeleteCamera("4P_CAMERA");
		pCameraManager->DeleteCamera("TOPVIEW_CAMERA");
	}
	//�S�Ă̏I������
	CScene::ReleseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	CDebugProc::Print("c", "�Q�[�����[�h");
	////�C�ӂ̃L�[ENTER
	//if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	//{
	//	for (int nCntPlayer = 0; nCntPlayer < 4; nCntPlayer++)
	//	{
	//		CResult::SetRanking(nCntPlayer, m_pPlayer[nCntPlayer]->GetID(), m_type[nCntPlayer], m_pPlayer[nCntPlayer]->GetMovetype(), m_pPoint[nCntPlayer]->GetPoint());
	//	}
	//	pFade->SetFade(pManager->MODE_RESULT, pFade->FADE_OUT);
	//}

	//�J��������i�e�X�g�j
	CCameraManager *pCameraManager = CManager::GetCameraManager();
	CCamera* pCam = pCameraManager->GetCamera("TOPVIEW_CAMERA");
	if (pCam != NULL)
	{
		pCam->SetRotation(pCam->GetRotation() + D3DXVECTOR3(0.0f,0.001f,0.0f));
	}

	//���Ԓ�~(�f�o�b�N�p)
	//if (CCommand::GetCommand("TIMECOUNT_STOP"))
	//{
	//	CTime::SetTimeFlag(!(CTime::GetTimeFlag()));	//���݂̃t���O�𔽓]������
	//}

	RankingUpdata();	// ���ʂ���ɕύX

#ifdef _DEBUG

#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{

}

//=============================================================================
// �J�����Z�b�g����
//=============================================================================
void CGame::CameraSetting(int nNumPlayer)
{
	//�J�����̃N���G�C�g
	CCameraManager *pCameraManager = CManager::GetCameraManager();
	if (pCameraManager != NULL)
	{
		switch (nNumPlayer)
		{
		case CPlayerSelect::SELECTPLAYER_1P:
			pCameraManager->CreateCamera("1P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_1P_PLAY);
			pCameraManager->SetCameraViewPort("1P_CAMERA", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			break;

		case CPlayerSelect::SELECTPLAYER_2P:
			pCameraManager->CreateCamera("1P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_2P_PLAY);
			pCameraManager->SetCameraViewPort("1P_CAMERA", 140, 0, 1000, 355);
			pCameraManager->CreateCamera("2P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_2P_PLAY);
			pCameraManager->SetCameraViewPort("2P_CAMERA", 140, 365, 1000, 355);
			break;

		case CPlayerSelect::SELECTPLAYER_3P:
			pCameraManager->CreateCamera("1P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("1P_CAMERA", 0, 0, 635, 355);

			pCameraManager->CreateCamera("2P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("2P_CAMERA", 645, 0, 635, 355);

			pCameraManager->CreateCamera("3P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("3P_CAMERA", 0, 365, 635, 355);

			pCameraManager->CreateCamera("TOPVIEW_CAMERA", CCamera::TYPE_TOPVIEW,
				D3DXVECTOR3(0.0f, -100.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), CAMERA_LENGTH_TOPVIEW_PLAY);
			pCameraManager->SetCameraViewPort("TOPVIEW_CAMERA", 645, 365, 635, 355);
			break;

		case CPlayerSelect::SELECTPLAYER_4P:
			pCameraManager->CreateCamera("1P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("1P_CAMERA", 0, 0, 635, 355);

			pCameraManager->CreateCamera("2P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("2P_CAMERA", 645, 0, 635, 355);

			pCameraManager->CreateCamera("3P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("3P_CAMERA", 0, 365, 635, 355);

			pCameraManager->CreateCamera("4P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(20.0f, 0.0f, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("4P_CAMERA", 645, 365, 635, 355);
			break;

		default:
			pCameraManager->CreateCamera("1P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("1P_CAMERA", 0, 0, 635, 355);

			pCameraManager->CreateCamera("2P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("2P_CAMERA", 645, 0, 635, 355);

			pCameraManager->CreateCamera("3P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("3P_CAMERA", 0, 365, 635, 355);

			pCameraManager->CreateCamera("4P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(20.0f, 0.0f, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("4P_CAMERA", 645, 365, 635, 355);
			break;
		}

		//�|�[�Y�p�J�����쐬
		pCameraManager->CreateCamera("PAUSE_CAMERA", CCamera::TYPE_TOPVIEW,
			D3DXVECTOR3(20.0f, 0.0f, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f),
			CAMERA_LENGTH_TOPVIEW_PLAY,CCameraManager::PROP_INIT_ZONLY);

		pCameraManager->SetCameraViewPort("PAUSE_CAMERA", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	}
}

//=============================================================================
// �l���ɉ����ăv���C���[�����̏���
//=============================================================================
void CGame::PlayerSetting(int nNum)
{
	CCameraManager *pCameraManager = CManager::GetCameraManager();

	if (nNum == 1 || nNum == 2 || nNum == 3 || nNum == 4)
	{
		// �l�����𐶐�
		for (int nCntPlayer = 0; nCntPlayer < nNum; nCntPlayer++)
		{
			if (m_pPlayer[nCntPlayer] == NULL)
			{
				m_pPlayer[nCntPlayer] = CPlayer::Create();
			}
		}

		for (int nCntPlayer = 0; nCntPlayer < 4; nCntPlayer++)
		{
			if (m_pPlayer[nCntPlayer] == NULL)
			{
				m_pPlayer[nCntPlayer] = CPlayer::Create();
			}
		}
		switch (m_nNumStage)
		{
		case 0:
			if (m_pPlayer[0] != NULL)
			{
				m_pPlayer[0]->Set(D3DXVECTOR3(PLAYER_INITPOS, 0.0f, PLAYER_INITPOS), CCharaBase::MOVETYPE_PLAYER_INPUT, 0, m_type[0]);
				m_pPlayer[0]->SetCameraName("1P_CAMERA");
				pCameraManager->SetCameraHomingChara("1P_CAMERA", (C3DCharactor*)m_pPlayer[0]->GetCharaMover());
			}

			if (m_pPlayer[1] != NULL)
			{
				if (nNum > 1)
				{
					m_pPlayer[1]->Set(D3DXVECTOR3(-PLAYER_INITPOS, 0.0f, PLAYER_INITPOS), CCharaBase::MOVETYPE_PLAYER_INPUT, 1, m_type[1], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				else
				{
					m_type[1] = (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM);
					m_pPlayer[1]->Set(D3DXVECTOR3(-PLAYER_INITPOS, 0.0f, PLAYER_INITPOS), CCharaBase::MOVETYPE_NPC_AI, 1, m_type[1], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				m_pPlayer[1]->SetCameraName("2P_CAMERA");
				pCameraManager->SetCameraHomingChara("2P_CAMERA", (C3DCharactor*)m_pPlayer[1]->GetCharaMover());
			}

			if (m_pPlayer[2] != NULL)
			{
				if (nNum > 2)
				{
					m_pPlayer[2]->Set(D3DXVECTOR3(PLAYER_INITPOS, 0.0f, -PLAYER_INITPOS), CCharaBase::MOVETYPE_PLAYER_INPUT, 2, m_type[2], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				else
				{
					m_type[2] = (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM);
					m_pPlayer[2]->Set(D3DXVECTOR3(PLAYER_INITPOS, 0.0f, -PLAYER_INITPOS), CCharaBase::MOVETYPE_NPC_AI, 2, m_type[2], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				m_pPlayer[2]->SetCameraName("3P_CAMERA");
				pCameraManager->SetCameraHomingChara("3P_CAMERA", (C3DCharactor*)m_pPlayer[2]->GetCharaMover());
			}

			if (m_pPlayer[3] != NULL)
			{
				if (nNum > 3)
				{
					m_pPlayer[3]->Set(D3DXVECTOR3(-PLAYER_INITPOS, 0.0f, -PLAYER_INITPOS), CCharaBase::MOVETYPE_PLAYER_INPUT, 3, m_type[3], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				else
				{
					m_type[3] = (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM);
					m_pPlayer[3]->Set(D3DXVECTOR3(-PLAYER_INITPOS, 0.0f, -PLAYER_INITPOS), CCharaBase::MOVETYPE_NPC_AI, 3, m_type[3], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				m_pPlayer[3]->SetCameraName("4P_CAMERA");
				pCameraManager->SetCameraHomingChara("4P_CAMERA", (C3DCharactor*)m_pPlayer[3]->GetCharaMover());
			}
			break;
		case 1:
			if (m_pPlayer[0] != NULL)
			{
				m_pPlayer[0]->Set(D3DXVECTOR3(200, 0.0f, 200), CCharaBase::MOVETYPE_PLAYER_INPUT, 0, m_type[0]);
				m_pPlayer[0]->SetCameraName("1P_CAMERA");
				pCameraManager->SetCameraHomingChara("1P_CAMERA", (C3DCharactor*)m_pPlayer[0]->GetCharaMover());
			}

			if (m_pPlayer[1] != NULL)
			{
				if (nNum > 1)
				{
					m_pPlayer[1]->Set(D3DXVECTOR3(-200, 0.0f, 200), CCharaBase::MOVETYPE_PLAYER_INPUT, 1, m_type[1], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				else
				{
					m_type[1] = (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM);
					m_pPlayer[1]->Set(D3DXVECTOR3(-200, 0.0f, 200), CCharaBase::MOVETYPE_NPC_AI, 1, m_type[1], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				m_pPlayer[1]->SetCameraName("2P_CAMERA");
				pCameraManager->SetCameraHomingChara("2P_CAMERA", (C3DCharactor*)m_pPlayer[1]->GetCharaMover());
			}

			if (m_pPlayer[2] != NULL)
			{
				if (nNum > 2)
				{
					m_pPlayer[2]->Set(D3DXVECTOR3(200, 0.0f, -200), CCharaBase::MOVETYPE_PLAYER_INPUT, 2, m_type[2], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				else
				{
					m_type[2] = (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM);
					m_pPlayer[2]->Set(D3DXVECTOR3(200, 0.0f, -200), CCharaBase::MOVETYPE_NPC_AI, 2, m_type[2], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				m_pPlayer[2]->SetCameraName("3P_CAMERA");
				pCameraManager->SetCameraHomingChara("3P_CAMERA", (C3DCharactor*)m_pPlayer[2]->GetCharaMover());
			}

			if (m_pPlayer[3] != NULL)
			{
				if (nNum > 3)
				{
					m_pPlayer[3]->Set(D3DXVECTOR3(-200, 0.0f, -200), CCharaBase::MOVETYPE_PLAYER_INPUT, 3, m_type[3], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				else
				{
					m_type[3] = (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM);
					m_pPlayer[3]->Set(D3DXVECTOR3(-200, 0.0f, -200), CCharaBase::MOVETYPE_NPC_AI, 3, m_type[3], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				m_pPlayer[3]->SetCameraName("4P_CAMERA");
				pCameraManager->SetCameraHomingChara("4P_CAMERA", (C3DCharactor*)m_pPlayer[3]->GetCharaMover());
			}
			break;
		}
//#endif
	}
	else
	{
		switch (m_nNumStage)
		{
		case 0:
			// �l�����𐶐�
			for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
			{
				if (m_pPlayer[nCntPlayer] == NULL)
				{
					m_pPlayer[nCntPlayer] = CPlayer::Create();
				}
			}

			if (m_pPlayer[0] != NULL)
			{
				m_pPlayer[0]->Set(D3DXVECTOR3(PLAYER_INITPOS, 0.0f, PLAYER_INITPOS), CCharaBase::MOVETYPE_PLAYER_INPUT, 0, (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_pPlayer[0]->SetCameraName("1P_CAMERA");
				pCameraManager->SetCameraHomingChara("1P_CAMERA", (C3DCharactor*)m_pPlayer[0]->GetCharaMover());
			}

			if (m_pPlayer[1] != NULL)
			{
				m_pPlayer[1]->Set(D3DXVECTOR3(-PLAYER_INITPOS, 0.0f, PLAYER_INITPOS), CCharaBase::MOVETYPE_PLAYER_INPUT, 1, (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_pPlayer[1]->SetCameraName("2P_CAMERA");
				pCameraManager->SetCameraHomingChara("2P_CAMERA", (C3DCharactor*)m_pPlayer[1]->GetCharaMover());
			}

			if (m_pPlayer[2] != NULL)
			{
				m_pPlayer[2]->Set(D3DXVECTOR3(PLAYER_INITPOS, 0.0f, -PLAYER_INITPOS), CCharaBase::MOVETYPE_PLAYER_INPUT, 2, (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_pPlayer[2]->SetCameraName("3P_CAMERA");
				pCameraManager->SetCameraHomingChara("3P_CAMERA", (C3DCharactor*)m_pPlayer[2]->GetCharaMover());
			}
			if (m_pPlayer[3] != NULL)
			{
				m_pPlayer[3]->Set(D3DXVECTOR3(-PLAYER_INITPOS, 0.0f, -PLAYER_INITPOS), CCharaBase::MOVETYPE_PLAYER_INPUT, 3, (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_pPlayer[3]->SetCameraName("4P_CAMERA");
				pCameraManager->SetCameraHomingChara("4P_CAMERA", (C3DCharactor*)m_pPlayer[3]->GetCharaMover());
			}
			break;
		case 1:
			// �l�����𐶐�
			for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
			{
				if (m_pPlayer[nCntPlayer] == NULL)
				{
					m_pPlayer[nCntPlayer] = CPlayer::Create();
				}
			}

			if (m_pPlayer[0] != NULL)
			{
				m_pPlayer[0]->Set(D3DXVECTOR3(200, 0.0f, 200), CCharaBase::MOVETYPE_PLAYER_INPUT, 0, (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_pPlayer[0]->SetCameraName("1P_CAMERA");
				pCameraManager->SetCameraHomingChara("1P_CAMERA", (C3DCharactor*)m_pPlayer[0]->GetCharaMover());
			}

			if (m_pPlayer[1] != NULL)
			{
				m_pPlayer[1]->Set(D3DXVECTOR3(-200, 0.0f, 200), CCharaBase::MOVETYPE_PLAYER_INPUT, 1, (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_pPlayer[1]->SetCameraName("2P_CAMERA");
				pCameraManager->SetCameraHomingChara("2P_CAMERA", (C3DCharactor*)m_pPlayer[1]->GetCharaMover());
			}

			if (m_pPlayer[2] != NULL)
			{
				m_pPlayer[2]->Set(D3DXVECTOR3(200, 0.0f, -200), CCharaBase::MOVETYPE_PLAYER_INPUT, 2, (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_pPlayer[2]->SetCameraName("3P_CAMERA");
				pCameraManager->SetCameraHomingChara("3P_CAMERA", (C3DCharactor*)m_pPlayer[2]->GetCharaMover());
			}
			if (m_pPlayer[3] != NULL)
			{
				m_pPlayer[3]->Set(D3DXVECTOR3(-200, 0.0f, -200), CCharaBase::MOVETYPE_PLAYER_INPUT, 3, (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_pPlayer[3]->SetCameraName("4P_CAMERA");
				pCameraManager->SetCameraHomingChara("4P_CAMERA", (C3DCharactor*)m_pPlayer[3]->GetCharaMover());
			}
			break;
		}
	}
}

//=============================================================================
// �l���ɉ��������̐�������
//=============================================================================
void CGame::TubeSetting(int nNum)
{
	switch (nNum)
	{
	case 1:
		if (m_apTube[0] == NULL)
		{
			m_apTube[0] = CTube::Create(WORD_TUBE001_POS_1P, WORD_SIZE_001, "TUBE", 3);
			m_apTube[0]->SetID(0);
		}
		break;

	case 2:
		for (int nCntTube = 0; nCntTube < nNum; nCntTube++)
		{
			if (m_apTube[nCntTube] == NULL)
			{
				if (nCntTube == 0) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE002_POS_1P, WORD_SIZE_002, "TUBE", 3); m_apTube[0]->SetID(0);}
				if (nCntTube == 1) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE002_POS_2P, WORD_SIZE_002, "TUBE", 3); m_apTube[1]->SetID(1);}
			}
		}
		break;

	case 3:
		for (int nCntTube = 0; nCntTube < nNum; nCntTube++)
		{
			if (m_apTube[nCntTube] == NULL)
			{
				if (nCntTube == 0) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_1P, WORD_SIZE_002, "TUBE", 3); m_apTube[0]->SetID(0);}
				if (nCntTube == 1) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_2P, WORD_SIZE_002, "TUBE", 3); m_apTube[1]->SetID(1);}
				if (nCntTube == 2) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_3P, WORD_SIZE_002, "TUBE", 3); m_apTube[2]->SetID(2);}
			}
		}
		break;

	case 4:
		for (int nCntTube = 0; nCntTube < nNum; nCntTube++)
		{
			if (m_apTube[nCntTube] == NULL)
			{
				if (nCntTube == 0) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_1P, WORD_SIZE_002, "TUBE", 3); m_apTube[0]->SetID(0);}
				if (nCntTube == 1) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_2P, WORD_SIZE_002, "TUBE", 3); m_apTube[1]->SetID(1);}
				if (nCntTube == 2) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_3P, WORD_SIZE_002, "TUBE", 3); m_apTube[2]->SetID(2);}
				if (nCntTube == 3) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE004_POS_4P, WORD_SIZE_002, "TUBE", 3); m_apTube[3]->SetID(3);}
			}
		}
		break;

	default:
		for (int nCntTube = 0; nCntTube < MAX_PLAYER; nCntTube++)
		{
			if (m_apTube[nCntTube] == NULL)
			{
				if (nCntTube == 0) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_1P, WORD_SIZE_002, "TUBE", 3); m_apTube[0]->SetID(0);}
				if (nCntTube == 1) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_2P, WORD_SIZE_002, "TUBE", 3); m_apTube[1]->SetID(1); }
				if (nCntTube == 2) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_3P, WORD_SIZE_002, "TUBE", 3); m_apTube[2]->SetID(2); }
				if (nCntTube == 3) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE004_POS_4P, WORD_SIZE_002, "TUBE", 3); m_apTube[3]->SetID(3); }
			}
		}
		break;
	}
}

//=============================================================================
// �|�C���g�̐�������
//=============================================================================
void CGame::SetPointFrame(int nNumPlayer)
{
	if (nNumPlayer <= MAX_PLAYER && nNumPlayer >= 0)
	{	// �w��l���͈͓̔�
		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{
			if (m_pPoint[nCount] == NULL)
			{
				if (nNumPlayer > nCount)
				{	// �v���C�l�����|�C���g����
					m_pPoint[nCount] = CPoint::Create(nCount, nNumPlayer, CPoint::TYPR_PLAYER);
				}
				else
				{	// CPU�̃|�C���g����
					m_pPoint[nCount] = CPoint::Create(nCount, nNumPlayer, CPoint::TYPE_CPU);
				}
			}
		}
	}
}

//=============================================================================
// �X�e�[�W�����̏���
//=============================================================================
void CGame::SetStage(int nNumState,int nCntState)
{
	if (nCntState < MAX_STAGE)
	{
		CSetObject::LoadFile(m_pcStageName[nNumState][nCntState]);
		m_nChangeNum = nCntState;
	}
}

//=============================================================================
// �X�e�[�W�����̏���
//=============================================================================
void CGame::SetCreateWord(void)
{
	if (m_pWordCreate != NULL) { m_pWordCreate->LoadFile(m_pcStageNameWord[m_nNumStage][m_nChangeNum]); }
}

//=============================================================================
// ����2D�����̎擾����
//=============================================================================
CTube *CGame::GetTube(int nNum)
{
	if (m_apTube[nNum] != NULL) { return m_apTube[nNum]; }
	return NULL;
}

//=============================================================================
// ���ʂ̍X�V����
//=============================================================================
void CGame::RankingUpdata(void)
{
	int nPoint[MAX_PLAYER] = {};
	int nRank[MAX_PLAYER] = {};
	int nNumWin[MAX_PLAYER] = {};

	for (int nCntPoint = 0; nCntPoint < MAX_PLAYER; nCntPoint++)
	{	// �|�C���g�Ǝ��g�̔ԍ����擾
		if (m_pPoint[nCntPoint] != NULL)
		{
			nPoint[nCntPoint] = m_pPoint[nCntPoint]->GetPoint();
		}
	}

	for (int nCntRank = 0; nCntRank < MAX_PLAYER; nCntRank++)
	{
		int nCntWin = 0;
		for (int nCntSort = 0; nCntSort < MAX_PLAYER; nCntSort++)
		{
			if (nPoint[nCntRank] >= nPoint[nCntSort])
			{	// �����������Z
				nCntWin++;
			}
		}

		nNumWin[nCntRank] = nCntWin;	// ���������
	}

	// Tex�ύX ���ʂ����킹��
	for (int nCntRankTex = 0; nCntRankTex < MAX_PLAYER; nCntRankTex++)
	{
		if (m_pPoint[nCntRankTex] != NULL)
		{
			m_pPoint[nCntRankTex]->RankLogoTex(MAX_PLAYER - nNumWin[nCntRankTex]);
		}
	}

}

#if 0
//=============================================================================
// �u���b�N�Ƃ̓����蔻�菈��
//=============================================================================
bool CGame::Collision(D3DXVECTOR3 *pos0, float fRadius0, D3DXVECTOR3 *pos1, float fRadius1)
{
	bool bHit = false;	// �������Ă��Ȃ����

	// ���S�ƒ��S�̍������߂�
	D3DXVECTOR3 DiffLength = D3DXVECTOR3(pos0->x - pos1->x, pos0->y - pos1->y, pos0->z - pos1->z);

	// ���S���璆�S�̃x�N�g���̒������Z�o
	float fLength = sqrtf((DiffLength.x * DiffLength.x) + (DiffLength.y * DiffLength.y) + (DiffLength.z * DiffLength.z));

	if (fLength < fRadius0 + fRadius1)
	{// ���������a�̘a��菬������Γ������Ă���
		bHit = true;
	}

	return bHit;	// �u���b�N�ɓ������Ă��邩�ǂ�����Ԃ�
}
#endif