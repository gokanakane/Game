//=============================================================================
//
// �^�C�}�[���� [time.cpp]
// Author : Shun Yokomichi
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "time.h"
#include "number.h"
#include "game.h"
#include "fade.h"
#include "player.h"
#include "scene2D.h"
#include "charactor.h"
#include "result.h"
#include "point.h"
#include "sceneBillboard.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define CENTER_WIDTH		(SCREEN_WIDTH / 2)				// X�̒��S���W
#define TIMER_SPACE1P2P		(18.0f)							// �����Ɛ����̊Ԃ̃T�C�Y(�Q�[������)
#define TIMER_SPACE3P4P		(22.0f)							// �����Ɛ����̊Ԃ̃T�C�Y(�Q�[������)
#define TIMER_WIDTH1P2P		(40.0f)							// �����Ɛ����̊Ԃ̃T�C�Y(�Q�[������)
#define TIMER_WIDTH3P4P		(30.0f)							// �����Ɛ����̊Ԃ̃T�C�Y(�Q�[������)
#define TIMER_HEIGHT1P2P	(20.0f)							// �����Ɛ����̊Ԃ̃T�C�Y(�Q�[������)
#define TIMER_HEIGHT3P4P	(15.0f)							// �����Ɛ����̊Ԃ̃T�C�Y(�Q�[������)
#define TIMER_POSITION_Y	(40.0f)							// �^�C�}�[��Y���W(�Q�[������)
#define GAME_TIME			(130)							// �Q�[���J�n���̎���
#define GAME_TIME_MAX		(9)								// �Q�[���̎��ԍő吔
#define POWER_X				(10)
#define TIME_POS_1P			(D3DXVECTOR3(SCREEN_WIDTH / 2 + 30.0f, 70.0f, 0.0f))	// �������Ԃ̈ʒu(1P�����̏ꍇ)
#define TIME_POS_2P			(D3DXVECTOR3(SCREEN_WIDTH / 2 + 50.0f, 440.0f, 0.0f))	// �������Ԃ̈ʒu(2P�����̏ꍇ)
#define TIME_POS_3P			(D3DXVECTOR3(SCREEN_WIDTH / 2 + 150.0f, 440.0f, 0.0f))	// �������Ԃ̈ʒu(3P�����̏ꍇ)
#define TIME_POS_4P			(D3DXVECTOR3(SCREEN_WIDTH / 2 + 160.0f, 380.0f, 0.0f))	// �������Ԃ̈ʒu(4P�����̏ꍇ)
#define WAIT_TIME_END		(180)							// �҂�����

#define COUNTDOWN_SCALE		(3.5f)							// �҂�����
#define DEFAULT_SIZE		(D3DXVECTOR3(10.0f, 15.0f, 0.0f))	// �f�t�H���g�T�C�Y
#define DEFAULT_SIZE1P2P	(D3DXVECTOR3(12.0f, 20.0f, 0.0f))	// �f�t�H���g�T�C�Y
#define DEFAULT_SIZE3P4P	(D3DXVECTOR3(12.0f, 20.0f, 0.0f))	// �f�t�H���g�T�C�Y
#define SCALE_CHANGE_TIME	(10)								// �X�P�[���ω��̎���
#define SCALE_UI			(100)								// UI�̑傫��
#define SCALE_UI_WIDTH		(200)								// UI�̑傫��
#define FEVER_COLOR			(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))
//=============================================================================
//	�ÓI�����o�ϐ�
//=============================================================================
int						CTime::m_nTime = 0;
int						CTime::m_nTimeCount = 0;
bool					CTime::m_bCountFlag = true;			//���Ԃ��J�E���g���邩
int						CTime::m_nTimeOld = 0;
int						CTime::m_nStageChange = 1;
int						CTime::m_nTimeOne = 3;
bool					CTime::m_bFever = false;
int						CTime::m_nStageNum = 0;
//=============================================================================
// ��������
//=============================================================================
CTime *CTime::Create(int nNumPlayer)
{
	CTime *pTime = NULL;

	//NULL�`�F�b�N
	if (pTime == NULL)
	{//���I�m��
		pTime = new CTime;

		//NULL�`�F�b�N
		if (pTime != NULL)
		{
			//�ʒu�̐ݒ�
#if 0
			if (nNumPlayer == 1) { pTime->m_pos = TIME_POS_1P; }
			if (nNumPlayer == 2 && m_nTimeNumCount == 0) { pTime->m_pos = TIME_POS_1P; }
			else if (nNumPlayer == 2 && m_nTimeNumCount == 1) { pTime->m_pos = TIME_POS_2P; }
			if (nNumPlayer == 3) { pTime->m_pos = TIME_POS_3P; }
			if (nNumPlayer == 4) { pTime->m_pos = TIME_POS_4P; }
#endif
			pTime->m_pos = D3DXVECTOR3(20.0f, 80.0f, 0.0f);

			pTime->m_nNumPlayer = nNumPlayer;

			//����������
			pTime->Init();
		}
	}

	return pTime;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTime::CTime(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	m_nTimeCount = 0;
	m_nTimeNum = 3;
	m_nWaitTime = 0;
	m_pColon = NULL;
	m_bStageCreate = false;
	m_nStageChange = 1;
	m_StageCounter = 0;
	//�l�̏�����
	m_bCntDown = false;
	m_ScaleCounter = 0;
	m_fScale = 0;
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nColorFlash = 0;
	m_nType = 0;
	m_fWidth = 100;
	m_fHeight = 100;
	m_bEndCntDown = false;
	m_bChangeStage = false;
	m_fWarningCol = 0.0f;
	m_bWarning = false;
	m_bScaleFlag = false;
	m_nCntScale = 0;
	m_nFeverTime = 0;
	m_bFever = 0;
	m_nStageNum = 0;
	m_nCntUIRepeat = 0;
	m_bStopUI = false;
	m_pFeverBillBoard = NULL;
	m_nUIScaleCounter = 0;
	m_fUIScale = 0;
	m_fUIAddScale = 0;
	m_bStartSound = false;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		m_pPlayer[nCntPlayer] = NULL;			// �v���C���[���擾
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTime::~CTime() {}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTime::Init(void)
{
	int nTexData = 0;
	m_nTime = 0;
	m_nTimeOld = GAME_TIME - 30;
	m_nTimeNum = PowerCalculation(m_nTime, 0);
	m_nTimeOne = 3;
	m_StageCounter = 0;
	m_fUIAddScale = 1.0f;
	m_bStartSound = false;

	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
		{	// �^�C�}�[�����ݒ�
			m_apNumber[nCntTime] = new CBillNumber;
			float Space = 0.0f;
			if (m_nNumPlayer == 1 || m_nNumPlayer == 2)
			{
				Space = TIMER_SPACE1P2P;
			}
			else
			{
				Space = TIMER_SPACE3P4P;
			}


			if (nCntTime < 2)
			{	// �R���܂�
				m_apNumber[nCntTime]->Init(D3DXVECTOR3((m_pos.x - Space * nCntTime), m_pos.y, m_pos.z));
				m_apNumber[nCntTime]->SetPos(D3DXVECTOR3((m_pos.x - Space * nCntTime), m_pos.y, m_pos.z));
			}
			else if (nCntTime == 2)
			{	// 3����
				m_apNumber[nCntTime]->Init(D3DXVECTOR3(((m_pos.x - 10.0f) - Space * nCntTime), m_pos.y, m_pos.z));
				m_apNumber[nCntTime]->SetPos(D3DXVECTOR3(((m_pos.x - 10.0f) - Space * nCntTime), m_pos.y, m_pos.z));
			}
			if (m_nNumPlayer == 1 || m_nNumPlayer == 2)
			{
				m_apNumber[nCntTime]->SetSize(DEFAULT_SIZE1P2P);
			}
			else
			{
				m_apNumber[nCntTime]->SetSize(DEFAULT_SIZE3P4P);
			}
		}
		// �����̃e�N�X�`���ݒ�
		TexTime(nTexData, m_nTimeOne);
	}

	// Time�̃��S
	if (m_nNumPlayer == 1 || m_nNumPlayer == 2)
	{
		m_pLogo = CSceneBillBoard::Create(D3DXVECTOR3(10.0f, 105.0f, 0.0f), TIMER_WIDTH1P2P, TIMER_HEIGHT1P2P, "TIME");
		m_pLogo->SetBillboard(D3DXVECTOR3(10.0f, 115.0f, 0.0f), TIMER_HEIGHT1P2P, TIMER_WIDTH1P2P);
	}
	else
	{
		m_pLogo = CSceneBillBoard::Create(D3DXVECTOR3(-5.0f, 105.0f, 0.0f), TIMER_WIDTH3P4P, TIMER_HEIGHT3P4P, "TIME");
		m_pLogo->SetBillboard(D3DXVECTOR3(-5.0f, 120.0f, 0.0f), TIMER_HEIGHT3P4P, TIMER_WIDTH3P4P);
	}
	m_pLogo->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	//�r���{�[�h�ݒ�
	if (m_pColon == NULL)
	{
		if (m_nNumPlayer == 1 || m_nNumPlayer == 2)
		{
			m_pColon = CSceneBillBoard::Create(D3DXVECTOR3(-10.0f, 88.0f, 0.0f), 5.0f, 10.0f, "COLON");
		}
		else
		{
			m_pColon = CSceneBillBoard::Create(D3DXVECTOR3(-17.0f, 86.0f, 0.0f), 7.0f, 10.0f, "COLON");
		}
		m_pColon->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	if (m_pFeverBillBoard == NULL)
	{
		m_pFeverBillBoard = CSceneBillBoard::Create(D3DXVECTOR3(0.0f, 500.0f, 0.0f), 40.0f, 40.0f, "FEVERUI2");
		m_pFeverBillBoard->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f));
	}

	//�J�E���g�_�E������
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		m_pScene2D[nCnt] = NULL;
		m_pFeverUI[nCnt] = NULL;
	}

	if (m_nNumPlayer == 1)
	{
		//�J�E���g�_�E���̈ʒu�ݒ�
		m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2+50, m_pos.z), "COUNTDOWN0");
		m_pScene2D[0]->SetWidthHeight(m_fWidth, m_fHeight);
		//�t�B�[�o�[�̈ʒu�ݒ�
		m_pFeverUI[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, SCREEN_HEIGHT / 2 - 100, m_pos.z), "FEVERUI2");
		m_pFeverUI[0]->SetWidthHeight(SCALE_UI_WIDTH, SCALE_UI);
		m_pFeverUI[0]->SetCol(FEVER_COLOR);
	}
	else if (m_nNumPlayer == 2)
	{
		//�J�E���g�_�E���̈ʒu�ݒ�
		m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 200.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[0]->SetWidthHeight(m_fWidth, m_fHeight);
		m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 570.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[1]->SetWidthHeight(m_fWidth, m_fHeight);
		//�t�B�[�o�[�̈ʒu�ݒ�
		m_pFeverUI[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, 180.0f, m_pos.z), "FEVERUI2");
		m_pFeverUI[0]->SetWidthHeight(SCALE_UI_WIDTH, SCALE_UI);
		m_pFeverUI[0]->SetCol(FEVER_COLOR);
		m_pFeverUI[1] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, 550.0f, m_pos.z), "FEVERUI2");
		m_pFeverUI[1]->SetWidthHeight(SCALE_UI_WIDTH, SCALE_UI);
		m_pFeverUI[1]->SetCol(FEVER_COLOR);

	}
	else if (m_nNumPlayer == 3)
	{
		//�J�E���g�_�E���̈ʒu�ݒ�
		m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(320.0f, 200.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[0]->SetWidthHeight(m_fWidth, m_fHeight);
		m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(940.0f, 200.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[1]->SetWidthHeight(m_fWidth, m_fHeight);
		m_pScene2D[2] = CScene2D::Create(D3DXVECTOR3(320.0f, 570.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[2]->SetWidthHeight(m_fWidth, m_fHeight);
		//�t�B�[�o�[�̈ʒu�ݒ�
		m_pFeverUI[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, 180.0f, m_pos.z), "FEVERUI2");
		m_pFeverUI[0]->SetWidthHeight(SCALE_UI_WIDTH, SCALE_UI);
		m_pFeverUI[0]->SetCol(FEVER_COLOR);
		m_pFeverUI[1] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, 550.0f, m_pos.z), "FEVERUI2");
		m_pFeverUI[1]->SetWidthHeight(SCALE_UI_WIDTH, SCALE_UI);
		m_pFeverUI[1]->SetCol(FEVER_COLOR);
	}
	if (m_nNumPlayer == 4)
	{
		//�J�E���g�_�E���̈ʒu�ݒ�
		m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(320.0f, 200.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[0]->SetWidthHeight(m_fWidth, m_fHeight);
		m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(940.0f, 200.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[1]->SetWidthHeight(m_fWidth, m_fHeight);
		m_pScene2D[2] = CScene2D::Create(D3DXVECTOR3(320.0f, 570.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[2]->SetWidthHeight(m_fWidth, m_fHeight);
		m_pScene2D[3] = CScene2D::Create(D3DXVECTOR3(940.0f, 570.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[3]->SetWidthHeight(m_fWidth, m_fHeight);
		//�t�B�[�o�[�̈ʒu�ݒ�
		m_pFeverUI[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, 180.0f, m_pos.z), "FEVERUI2");
		m_pFeverUI[0]->SetWidthHeight(SCALE_UI_WIDTH, SCALE_UI);
		m_pFeverUI[0]->SetCol(FEVER_COLOR);
		m_pFeverUI[1] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, 550.0f, m_pos.z), "FEVERUI2");
		m_pFeverUI[1]->SetWidthHeight(SCALE_UI_WIDTH, SCALE_UI);
		m_pFeverUI[1]->SetCol(FEVER_COLOR);
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{	// �v���C���[���擾
		m_pPlayer[nCntPlayer] = CGame::GetPlayer(nCntPlayer);
		if (m_pPlayer[nCntPlayer] != NULL)
		{
			m_pPlayer[nCntPlayer]->GetCharaMover()->SetWaitBool(true);
		}
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTime::Uninit(void)
{
	m_nStageNum = 0;
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
		{	// �^�C�}�[�̔j��
			if (m_apNumber[nCntTime] != NULL)
			{
				m_apNumber[nCntTime]->Uninit();
				m_apNumber[nCntTime] = NULL;
			}
		}
	}

	if (m_pColon != NULL)
	{
		m_pColon->Uninit();
		m_pColon = NULL;
	}

	if (m_pFeverBillBoard != NULL)
	{
		m_pFeverBillBoard->Uninit();
		m_pFeverBillBoard = NULL;
	}

	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{
			m_pScene2D[nCnt]->Uninit();
			m_pScene2D[nCnt] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pFeverUI[nCnt] != NULL)
		{
			m_pFeverUI[nCnt]->Uninit();
			m_pFeverUI[nCnt] = NULL;
		}
	}


	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTime::Update(void)
{
	CSound *pSound = CManager::GetSound();		//	���̎擾

	//���݂̃��[�h�̎擾
	CManager::MODE GameMode = CManager::GetMode();
	DebugKey();		// �f�o�b�N�p

	if ((GameMode == CManager::MODE_GAME) && m_bEndCntDown == true || (GameMode == CManager::MODE_TUTORIAL) && m_bEndCntDown == true)
	{//��������
	 //�Q�[��
		if (m_bCountFlag == true)
		{
			m_nTimeCount++;
			TimeManagement();	// ���Ԃ̊Ǘ�
		}

		//�t�B�[�o�[�^�C��
		if (m_nTimeCount == 60 * 150)
		{
			m_bFever = true;
			m_pLogo->BindTexture("FEVERUI2");
		}

		if (m_bFever == true)
		{
			m_nFeverTime++;
			if (m_nFeverTime == 60 * 30)
			{
				m_bStopUI = false;
				m_bFever = false;
				m_nFeverTime = 0;
				m_nCntUIRepeat = 0;
				m_fUIAddScale = 1.0f;
				m_nUIScaleCounter = 0;
				m_fUIScale = 0;

				if (m_nNumPlayer == 1)
				{
					m_pFeverUI[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, SCREEN_HEIGHT / 2, 0.0f));
				}
				if (m_nNumPlayer == 2)
				{
					m_pFeverUI[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, 180.0f, 0.0f));
					m_pFeverUI[1]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, 550.0f, 0.0f));
				}
				if (m_nNumPlayer == 3)

				{
					m_pFeverUI[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, 180.0f, 0.0f));
					m_pFeverUI[1]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, 550.0f, 0.0f));
				}
				if (m_nNumPlayer == 4)
				{
					m_pFeverUI[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, 180.0f, 0.0f));
					m_pFeverUI[1]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, 550.0f, 0.0f));
				}

				if (m_nNumPlayer == 1 || m_nNumPlayer == 2)
				{
					m_pLogo->SetBillboard(D3DXVECTOR3(5.0f, 105.0f, 0.0f), TIMER_HEIGHT1P2P, TIMER_WIDTH1P2P);
				}
				else
				{
					m_pLogo->SetBillboard(D3DXVECTOR3(5.0f, 120.0f, 0.0f), TIMER_HEIGHT3P4P, TIMER_WIDTH3P4P);
				}


				m_pLogo->BindTexture("TIME");
				m_pFeverBillBoard->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f));
			}
		}

		//�t�B�[�o�[�^�C����UI�ʒu�X�V
		if (m_bFever == true)
		{
			for (int nCntPlayer = 0; nCntPlayer < 2; nCntPlayer++)
			{
				if (m_pFeverUI[nCntPlayer] != NULL)
				{
					D3DXVECTOR3 UIPos = m_pFeverUI[nCntPlayer]->GetPosition();
					if (m_bStopUI == false)
					{
						UIPos.x -= 5;
					}
					m_pFeverUI[nCntPlayer]->SetPosition(UIPos);
					if (UIPos.x < -SCALE_UI_WIDTH)
					{
						if (nCntPlayer == 0)
						{
							m_nCntUIRepeat++;
						}
						UIPos.x = SCREEN_WIDTH + SCALE_UI_WIDTH;
						m_pFeverUI[nCntPlayer]->SetPosition(UIPos);
						if (m_nCntUIRepeat == 2)
						{
							m_bStopUI = true;
						}
					}
				}
			}
			//�r���{�[�h�g��k��
			if (m_bStopUI == true)
			{
				m_pFeverBillBoard->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f));
			}
			else if (m_bStopUI == false)
			{
				m_pFeverBillBoard->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f));
			}
			m_nUIScaleCounter++;
			m_fUIScale += m_fUIAddScale;
			m_pFeverBillBoard->SetBillboard(D3DXVECTOR3(0.0f, 120.0f, 0.0f), 40.0f + m_fUIScale, 40.0f + m_fUIScale);

			if (m_nNumPlayer == 1 || m_nNumPlayer == 2)
			{
				m_pLogo->SetBillboard(D3DXVECTOR3(5.0f, 105.0f, 0.0f), TIMER_HEIGHT1P2P + (m_fUIScale / 2), TIMER_WIDTH1P2P + (m_fUIScale / 2));
			}
			else
			{
				m_pLogo->SetBillboard(D3DXVECTOR3(5.0f, 120.0f, 0.0f), TIMER_HEIGHT3P4P + (m_fUIScale / 2), TIMER_WIDTH3P4P + (m_fUIScale / 2));
			}


			for (int nCntPlayer = 0; nCntPlayer < 2; nCntPlayer++)
			{
				if (m_pFeverUI[nCntPlayer] != NULL)
				{
					m_pFeverUI[nCntPlayer]->SetWidthHeight(SCALE_UI_WIDTH + m_fUIScale, SCALE_UI + m_fUIScale);
				}
			}

			if (m_nUIScaleCounter == 30)
			{
				m_fUIAddScale *= -1;
				m_nUIScaleCounter = 0;
			}
		}

		int nTexData = 0;
		// �����̃e�N�X�`���ݒ�
		TexTime(nTexData, m_nTimeOne);

		if (m_nTime == 0 && m_nTimeOne == 0 && GameMode == CManager::MODE_GAME)
		{
			//�Q�[���I���{�C�X
			if (m_bStartSound == false)
			{
				m_bStartSound = true;
				pSound->PlaySound(CSound::SOUND_LABEL_SE_GAMEEND);
			}
			for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
			{	// �v���C���[���s���ł��Ȃ��悤��
				m_pPlayer[nCntPlayer]->GetCharaMover()->SetWaitBool(true);
				m_pPlayer[nCntPlayer]->SetMotion(CPlayer::MOTION_UPPER_NEUTRAL, CPlayer::UPPER_BODY);
				m_pPlayer[nCntPlayer]->SetMotion(CPlayer::MOTION_LOWER_NEUTRAL, CPlayer::LOWER_BODY);

				if (m_pScene2D[nCntPlayer] != NULL)
				{
					m_pScene2D[nCntPlayer]->BindTexture("GAME_END");
					m_pScene2D[nCntPlayer]->SetCol(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
					m_pScene2D[nCntPlayer]->SetWidthHeight(m_fWidth + 200, m_fHeight);
					m_pScene2D[nCntPlayer]->SetScale(200.0f);
				}
			}

			// �Q�[���I��
			m_nWaitTime++;	// �҂����Ԃ̉��Z
			if ((m_nWaitTime % WAIT_TIME_END) == 0)
			{
				for (int nCntPlayer = 0; nCntPlayer < 4; nCntPlayer++)
				{
					CResult::SetRanking(nCntPlayer, CGame::GetPlayer(nCntPlayer)->GetID(), CGame::GetPlayerType(nCntPlayer), CGame::GetPlayer(nCntPlayer)->GetMovetype(), CGame::GetPoint(nCntPlayer)->GetPoint());
				}

				CFade::SetFade(CManager::MODE_RESULT, CFade::FADE_OUT);
			}
		}

		if (m_bChangeStage == true)
		{	// �X�e�[�W�ω��̐F�ω�
			ChangeStage();
		}

		ScaleNumber();	// �T�C�Y�̐ؑ�
	}

	CountDown();	// �J�E���g�_�E������

	//�X�e�[�W���������^�C�}�[
	if (CGame::GetbStageSet() == true)
	{
		m_StageCounter++;
		if (m_StageCounter > 120)
		{
			CManager::GetGame()->SetCreateWord();
			m_StageCounter = 0;
			CGame::bStageSet(false);
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void CTime::Draw(void)
{
	for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{
		if (m_apNumber[nCntTime] != NULL)
		{
			m_apNumber[nCntTime]->Draw();
		}
	}

	if (m_pColon != NULL)
	{
		m_pColon->Draw();
	}
	if (m_pFeverBillBoard != NULL)
	{
		if (m_bFever == true)
		{
			m_pFeverBillBoard->Draw();
		}
	}
}

//=============================================================================
// �J�E���g�_�E��
//=============================================================================
void CTime::CountDown(void)
{
	CSound *pSound = CManager::GetSound();		//	���̎擾

	//�J�E���g�_�E��
	if (m_bEndCntDown == false)
	{
		if (m_bStartSound == false)
		{
			pSound->SetVolume(CSound::SOUND_LABEL_SE_GAMESTART00, 5.0f);
			pSound->PlaySound(CSound::SOUND_LABEL_SE_GAMESTART00);
			m_bStartSound = true;
		}

		//�傫���ω�
		m_fScale += COUNTDOWN_SCALE;
		//�����x�グ
		if (m_fScale > 200 && m_fScale <= 250)
		{
			//�J�E���^�[���Z
			if (m_bCntDown == false)
			{
				m_Col.a -= 0.1f;
			}
		}
		//�傫���ő�
		if (m_fScale > COUNTDOWN_SCALE * 75)
		{
			m_fScale = COUNTDOWN_SCALE * 75;
			if (m_nType < 1)
			{
				//�e�N�X�`���ւ�
				m_bCntDown = true;
				m_nType += 1;
				m_fScale = 0;
				m_Col.a = 1.0f;

				pSound->SetVolume(CSound::SOUND_LABEL_SE_GAMESTART01, 5.0f);
				pSound->PlaySound(CSound::SOUND_LABEL_SE_GAMESTART01);
			}
			else if (m_nType == 1)
			{
				m_bEndCntDown = true;
				m_bStartSound = false;
				m_Col.a = 0.0f;
				for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
				{	// �v���C���[���擾
					m_pPlayer[nCntPlayer] = CGame::GetPlayer(nCntPlayer);
					if (m_pPlayer[nCntPlayer] != NULL)
					{
						m_pPlayer[nCntPlayer]->GetCharaMover()->SetWaitBool(false);
					}
				}
			}

			for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
			{
				if (m_pScene2D[nCnt] != NULL)
				{
					switch (m_nType)
					{
					case 0:
						m_pScene2D[nCnt]->BindTexture("COUNTDOWN0");
						break;
					case 1:
						//�X�^�[�g�\��
						m_pScene2D[nCnt]->BindTexture("COUNTDOWN1");
						m_pScene2D[nCnt]->SetWidthHeight(m_fWidth + 100, m_fHeight + 100);
						break;
					default:
						break;
					}
				}
			}
		}
		//�F�E�傫���X�V
		for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
		{
			if (m_pScene2D[nCnt] != NULL)
			{
				m_pScene2D[nCnt]->SetCol(m_Col);
				m_pScene2D[nCnt]->SetScale(m_fScale);
			}
		}
	}

}
//=============================================================================
// �^�C�}�[��Texture�Ǘ�
//=============================================================================
void CTime::TexTime(int nTexData, int nTimeOne)
{
	nTexData = m_nTime;

	for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{// �e�N�X�`���ɔ��f

		if (m_apNumber[nCntTime] != NULL)
		{
			if (nCntTime < 2)
			{
				m_apNumber[nCntTime]->SetNumber(nTexData);
				nTexData /= 10;
			}
			else if (nCntTime == 2)
			{
				m_apNumber[nCntTime]->SetNumber(nTimeOne);
				nTexData /= 10;
			}
			if (m_bChangeStage == false)
			{
				// �F�̐ݒ�
				if (m_nTime <= 10 && m_nTimeOne == 0)
				{ // 10�b�ȉ� �F��Ԃ�
					m_apNumber[nCntTime]->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
					if (m_pColon != NULL) { m_pColon->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)); }
				}
				else
				{
					m_apNumber[nCntTime]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					if (m_pColon != NULL) { m_pColon->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); }
				}
			}
		}
	}
}
//=============================================================================
// �^�C�����Z����
//=============================================================================
void CTime::AddTime(int nTime)
{
	if (m_nTime > 0)
	{
		m_nTimeOne += nTime;
	}

	if (GAME_TIME_MAX < m_nTimeOne) { m_nTimeOne = GAME_TIME_MAX; }
}
//=============================================================================
// �ׂ���̌v�Z
//=============================================================================
int CTime::PowerCalculation(int nData, int nOperation)
{
	int nNum = 1;
	int nPower = (int)std::pow(POWER_X, nNum);
	int nDataNum = nData;
	while ((nDataNum / nPower) != 0)
	{
		nNum++;
		nPower = (int)std::pow(POWER_X, nNum);		// �ׂ��悷��(����O��Ȃ�)
		if (nOperation == 0)
		{	// ��������
			if (nNum >= TIME_MAX) { nNum = TIME_MAX; }
		}
	}
	return nNum;
}

//=============================================================================
// ���Ԃ̊Ǘ�
//=============================================================================
void CTime::TimeManagement(void)
{
	if (m_nTime == 0 && m_nTimeOne == 0) {m_nTime = 0; return; }

	if ((m_nStageChange % 60) == 0 && m_bStageCreate == false)
	{	// 60�b���ƂɃX�e�[�W���ς��
		m_bStageCreate = true;
		CGame::bStageSet(true);
		int nStageNum = (m_nStageChange / 60);
		m_nStageNum = (m_nStageChange / 60);
		CManager::GetGame()->SetStage(CGame::GetNumStage(),nStageNum);
	}

	if (m_nTime == 10 && m_nTimeOne != 0)
	{	// �x���̎���
		m_bChangeStage = true;
	}


	//���s�[�g���[�h�̎��͑���
	int nFlameSecond = 60;
#ifdef _DEBUG
	if (CManager::GetRepeat() == true)
	{
		nFlameSecond = 1;
	}
#endif
	if (m_nTimeCount % nFlameSecond == 0)
	{// 1�b���ƂɌ��Z(��������)
		m_nTime--;
		m_nStageChange++;
		m_bStageCreate = false;

		if (m_nTime < 0) { m_nTime = 59; m_nTimeOne -= 1; 	DefaultCol();}
		//m_nTimeNum = PowerCalculation(m_nTime, 0);
	}
}
//=============================================================================
// �X�e�[�W�ؑ֎��̉��o
//=============================================================================
void CTime::ChangeStage(void)
{
	for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{// �e�N�X�`���ɔ��f
		if (m_apNumber[nCntTime] != NULL)
		{
			// �F�̐ݒ�
			if (m_bWarning == false)
			{
				m_fWarningCol -= 0.01f;
				if (m_fWarningCol < 0.2f) { m_fWarningCol = 0.2f;  m_bWarning = true; }
			}
			else if (m_bWarning == true)
			{
				m_fWarningCol += 0.01f;
				if (m_fWarningCol > 1.0f) { m_fWarningCol = 1.0f;  m_bWarning = false; }
			}
			m_apNumber[nCntTime]->SetCol(D3DXCOLOR(1.0f, m_fWarningCol, 0.0f, 1.0f));
			if (m_pColon != NULL) { m_pColon->SetCol(D3DXCOLOR(1.0f, m_fWarningCol, 0.0f, 1.0f)); }
		}
	}
}

//=============================================================================
// �F�����ɖ߂�
//=============================================================================
void CTime::DefaultCol(void)
{
	for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{// �e�N�X�`���ɔ��f
		if (m_apNumber[nCntTime] != NULL)
		{
			m_apNumber[nCntTime]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			if (m_pColon != NULL) { m_pColon->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); }
		}
	}

	m_bChangeStage = false;
}

//=============================================================================
// �X�e�[�W�^�C���̊g��k������
//=============================================================================
void CTime::ScaleNumber(void)
{
	if (m_bChangeStage == false)
	{	// �X�e�[�W�؂�ւ��̌x���t���O��false�Ȃ�T�C�Y��߂�
		for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
		{
			if (m_apNumber[nCntTime] != NULL && m_apNumber[nCntTime]->GetSize() != DEFAULT_SIZE)
			{
				if (m_nNumPlayer == 1 || m_nNumPlayer == 2)
				{
					m_apNumber[nCntTime]->SetSize(DEFAULT_SIZE1P2P);
				}
				else
				{
					m_apNumber[nCntTime]->SetSize(DEFAULT_SIZE3P4P);
				}
			}
		}
		m_nCntScale = 0;
		return;
	}

	m_nCntScale++;	// ���Z
	for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{
		if (m_apNumber[nCntTime] != NULL)
		{
			// �T�C�Y�̎擾
			D3DXVECTOR3 size = m_apNumber[nCntTime]->GetSize();
			float fSizeChange = 0.5f;

			// �t���O��false�Ȃ�k��
			if (m_bScaleFlag == false)
			{
				size.x += fSizeChange / 2;
				size.y += fSizeChange;

				if ((m_nCntScale % SCALE_CHANGE_TIME) == 0) { m_bScaleFlag = true; }
			}
			// �t���O��true�Ȃ�g��
			else if (m_bScaleFlag == true)
			{
				size.x -= fSizeChange / 2;
				size.y -= fSizeChange;

				if ((m_nCntScale % SCALE_CHANGE_TIME) == 0) {
					m_bScaleFlag = false; }
			}

			// �T�C�Y�̐ݒ�
			m_apNumber[nCntTime]->SetSize(size);
		}
	}
}

//=============================================================================
// �f�o�b�N�p
//=============================================================================
void CTime::DebugKey(void)
{
	// �f�o�b�N�p
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_NUMPAD0))
	{	// �������ԉ��Z
		AddTime(1);
	}

	if (CManager::GetInputKeyboard()->GetPress(DIK_NUMPAD6))
	{	// �������ԉ��Z
		m_nTimeCount--;
		m_nStageChange--;
	}
	if (CManager::GetInputKeyboard()->GetPress(DIK_NUMPAD4))
	{	// �������ԉ��Z
		m_nTimeCount++;
		m_nStageChange++;
	}
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_NUMPAD9))
	{	// ���U���g��ʂ�
		m_nTime = 0;
		m_nTimeOne = 0;
	}
}