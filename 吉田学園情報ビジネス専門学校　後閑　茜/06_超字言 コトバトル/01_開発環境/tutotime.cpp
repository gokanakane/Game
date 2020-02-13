//=============================================================================
//
// �^�C�}�[���� [tutotime.cpp]
// Author : Meguroo Mikiya
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "tutotime.h"
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
#define GAME_TUTOTIME_MAX		(9)								// �Q�[���̎��ԍő吔
#define POWER_X				(10)
#define TIME_POS_1P			(D3DXVECTOR3(SCREEN_WIDTH / 2 + 30.0f, 70.0f, 0.0f))	// �������Ԃ̈ʒu(1P�����̏ꍇ)
#define TIME_POS_2P			(D3DXVECTOR3(SCREEN_WIDTH / 2 + 50.0f, 440.0f, 0.0f))	// �������Ԃ̈ʒu(2P�����̏ꍇ)
#define TIME_POS_3P			(D3DXVECTOR3(SCREEN_WIDTH / 2 + 150.0f, 440.0f, 0.0f))	// �������Ԃ̈ʒu(3P�����̏ꍇ)
#define TIME_POS_4P			(D3DXVECTOR3(SCREEN_WIDTH / 2 + 160.0f, 380.0f, 0.0f))	// �������Ԃ̈ʒu(4P�����̏ꍇ)
#define WAIT_TIME_END		(60)							// �҂�����

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
int						CTutoTime::m_nTime = 0;
int						CTutoTime::m_nTimeCount = 0;
bool					CTutoTime::m_bCountFlag = true;			//���Ԃ��J�E���g���邩
int						CTutoTime::m_nTimeOld = 0;
int						CTutoTime::m_nTimeOne = 3;
int						CTutoTime::m_nStageNum = 0;
//=============================================================================
// ��������
//=============================================================================
CTutoTime *CTutoTime::Create(int nNumPlayer)
{
	CTutoTime *pTime = NULL;

	//NULL�`�F�b�N
	if (pTime == NULL)
	{//���I�m��
		pTime = new CTutoTime;

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
CTutoTime::CTutoTime(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	m_nTimeCount = 0;
	m_nTimeNum = 3;
	m_nWaitTime = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutoTime::~CTutoTime() {}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTutoTime::Init(void)
{
	int nTexData = 0;
	m_nTime = 0;
	m_nTimeOld = GAME_TIME - 30;
	m_nTimeNum = PowerCalculation(m_nTime, 0);
	m_nTimeOne = 3;
	int nHeight = 0;
	int nWidth = 0;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		for (int nCntTime = 0; nCntTime < TUTOTIME_MAX; nCntTime++)
		{
			m_apNumber[nCntTime][nCntPlayer] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		m_pScene2D[nCnt] = NULL;
	}

	if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		for (int nCntPlayer = 0; nCntPlayer < m_nNumPlayer; nCntPlayer++)
		{
			for (int nCntTime = 0; nCntTime < TUTOTIME_MAX; nCntTime++)
			{	// �^�C�}�[�����ݒ�
				m_apNumber[nCntTime][nCntPlayer] = new CNumber;
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
					m_apNumber[nCntTime][nCntPlayer]->Init(D3DXVECTOR3(100.0f, 200.0f, 0.0f), 0);
					m_apNumber[nCntTime][nCntPlayer]->SetSize(D3DXVECTOR2(50, 70), D3DXVECTOR2(410.0f + (68 * nCntTime), 650.0f));
					m_apNumber[nCntTime][nCntPlayer]->SetNumber(0);
					m_apNumber[nCntTime][nCntPlayer]->SetbDraw(true);
				}

				if (m_nNumPlayer == 1)
				{
					m_apNumber[nCntTime][nCntPlayer]->SetSize(D3DXVECTOR2(50, 70), D3DXVECTOR2(450.0f - (68 * nCntTime), 650.0f));
					m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(700, 650, m_pos.z), "TUTOTIME");
					m_pScene2D[0]->SetWidthHeight(500, 80);

				}
				else if(m_nNumPlayer == 2)
				{
					m_apNumber[nCntTime][nCntPlayer]->SetSize(D3DXVECTOR2(30, 50), D3DXVECTOR2(480.0f - (50 * nCntTime), 310.0f + (360 * nCntPlayer)));
					m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(700, 310, m_pos.z), "TUTOTIME");
					m_pScene2D[0]->SetWidthHeight(470, 50);
					m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(700, 670, m_pos.z), "TUTOTIME");
					m_pScene2D[1]->SetWidthHeight(470, 50);
				}
				else if (m_nNumPlayer == 3)
				{
					if (nCntPlayer == 1)
					{
						nHeight = 1;
					}
					if (nCntPlayer == 2)
					{
						nWidth = 1;
						nHeight = 0;
					}

					m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(400, 320, m_pos.z), "TUTOTIME");
					m_pScene2D[0]->SetWidthHeight(210, 40);
					m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(1040, 320, m_pos.z), "TUTOTIME");
					m_pScene2D[1]->SetWidthHeight(210, 40);
					m_pScene2D[2] = CScene2D::Create(D3DXVECTOR3(400, 680, m_pos.z), "TUTOTIME");
					m_pScene2D[2]->SetWidthHeight(210, 40);

					m_apNumber[nCntTime][nCntPlayer]->SetSize(D3DXVECTOR2(25, 35), D3DXVECTOR2(290.0f - (35 * nCntTime) + (640 * nWidth), 320.0f + (360 * nHeight)));
				}
				else if (m_nNumPlayer == 4)
				{
					if (nCntPlayer == 1)
					{
						nHeight = 1;
					}
					if (nCntPlayer == 2)
					{
						nWidth = 1;
						nHeight = 0;
					}
					if (nCntPlayer == 3)
					{
						nWidth = 1;
						nHeight = 1;
					}

					m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(400, 320, m_pos.z), "TUTOTIME");
					m_pScene2D[0]->SetWidthHeight(210, 40);
					m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(1040, 320, m_pos.z), "TUTOTIME");
					m_pScene2D[1]->SetWidthHeight(210, 40);
					m_pScene2D[2] = CScene2D::Create(D3DXVECTOR3(400, 680, m_pos.z), "TUTOTIME");
					m_pScene2D[2]->SetWidthHeight(210, 40);
					m_pScene2D[3] = CScene2D::Create(D3DXVECTOR3(1040, 680, m_pos.z), "TUTOTIME");
					m_pScene2D[3]->SetWidthHeight(210, 40);

					m_apNumber[nCntTime][nCntPlayer]->SetSize(D3DXVECTOR2(25, 35), D3DXVECTOR2(290.0f - (35 * nCntTime) + (640 * nWidth), 320.0f + (360 * nHeight)));
				}
			}
		}
		// �����̃e�N�X�`���ݒ�
		m_nTime = 30;
		TexTime(nTexData, m_nTimeOne);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTutoTime::Uninit(void)
{
	m_nStageNum = 0;
	if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		for (int nCntPlayer = 0; nCntPlayer < PLAYER_MAX; nCntPlayer++)
		{
			for (int nCntTime = 0; nCntTime < TUTOTIME_MAX; nCntTime++)
			{	// �^�C�}�[�̔j��
				if (m_apNumber[nCntTime][nCntPlayer] != NULL)
				{
					m_apNumber[nCntTime][nCntPlayer]->Uninit();
					m_apNumber[nCntTime][nCntPlayer] = NULL;
				}
			}

			if (m_pScene2D[nCntPlayer] != NULL)
			{
				m_pScene2D[nCntPlayer]->Uninit();
				m_pScene2D[nCntPlayer] = NULL;
			}
		}
	}

	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTutoTime::Update(void)
{
	CSound *pSound = CManager::GetSound();		//	���̎擾

	//���݂̃��[�h�̎擾
	CManager::MODE GameMode = CManager::GetMode();
	DebugKey();		// �f�o�b�N�p

	if (GameMode == CManager::MODE_TUTORIAL)
	{//��������
	 //�Q�[��
		if (m_bCountFlag == true)
		{
			m_nTimeCount++;
			TimeManagement();	// ���Ԃ̊Ǘ�
		}

		int nTexData = 0;
		// �����̃e�N�X�`���ݒ�
		TexTime(nTexData, m_nTimeOne);

		if (m_nTime == 0 && GameMode == CManager::MODE_TUTORIAL)
		{
			// �Q�[���I��
			m_nWaitTime++;	// �҂����Ԃ̉��Z
			if ((m_nWaitTime % WAIT_TIME_END) == 0)
			{
				CFade::SetFade(CManager::MODE_CHARASELECT, CFade::FADE_OUT);
			}
		}
	}

	//CountDown();	// �J�E���g�_�E������

}

//=============================================================================
// �`�揈��
//=============================================================================
void CTutoTime::Draw(void)
{
	for (int nCntPlayer = 0; nCntPlayer < m_nNumPlayer; nCntPlayer++)
	{
		for (int nCntTime = 0; nCntTime < TUTOTIME_MAX; nCntTime++)
		{
			if (m_apNumber[nCntTime][nCntPlayer] != NULL)
			{
				m_apNumber[nCntTime][nCntPlayer]->Draw();
			}
		}
	}
}

//=============================================================================
// �J�E���g�_�E��
//=============================================================================
void CTutoTime::CountDown(void)
{
	CSound *pSound = CManager::GetSound();		//	���̎擾
}
//=============================================================================
// �^�C�}�[��Texture�Ǘ�
//=============================================================================
void CTutoTime::TexTime(int nTexData, int nTimeOne)
{
	int nTime[4] = { 0,0,0,0 };
	nTexData = m_nTime;

	for (int nCntPlayer = 0; nCntPlayer < PLAYER_MAX; nCntPlayer++)
	{
		nTime[nCntPlayer] = m_nTime;
		for (int nCntTime = 0; nCntTime < TUTOTIME_MAX; nCntTime++)
		{// �e�N�X�`���ɔ��f
			if (m_apNumber[nCntTime][nCntPlayer] != NULL)
			{
				if (nCntTime < 2)
				{
					m_apNumber[nCntTime][nCntPlayer]->SetNumber(nTime[nCntPlayer]);
					nTime[nCntPlayer] /= 10;
				}
				else if (nCntTime == 2)
				{
					m_apNumber[nCntTime][nCntPlayer]->SetNumber(nTime[nCntPlayer]);
					nTime[nCntPlayer] /= 10;
				}
			}
		}
	}
}
//=============================================================================
// �^�C�����Z����
//=============================================================================
void CTutoTime::AddTime(int nTime)
{
	if (m_nTime > 0)
	{
		m_nTimeOne += nTime;
	}

	if (GAME_TUTOTIME_MAX < m_nTimeOne) { m_nTimeOne = GAME_TUTOTIME_MAX; }
}
//=============================================================================
// �ׂ���̌v�Z
//=============================================================================
int CTutoTime::PowerCalculation(int nData, int nOperation)
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
			if (nNum >= TUTOTIME_MAX) { nNum = TUTOTIME_MAX; }
		}
	}
	return nNum;
}

//=============================================================================
// ���Ԃ̊Ǘ�
//=============================================================================
void CTutoTime::TimeManagement(void)
{
	if (m_nTime == 0 && m_nTimeOne == 0) {m_nTime = 0; return; }

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
		if (m_nTime < 0) { m_nTime = 0; m_nTimeOne -= 1; 	DefaultCol();}
		//m_nTimeNum = PowerCalculation(m_nTime, 0);
	}
}
//=============================================================================
// �X�e�[�W�ؑ֎��̉��o
//=============================================================================
void CTutoTime::ChangeStage(void)
{

}

//=============================================================================
// �F�����ɖ߂�
//=============================================================================
void CTutoTime::DefaultCol(void)
{
	for (int nCntPlayer = 0; nCntPlayer < PLAYER_MAX; nCntPlayer++)
	{
		for (int nCntTime = 0; nCntTime < TUTOTIME_MAX; nCntTime++)
		{// �e�N�X�`���ɔ��f
			if (m_apNumber[nCntTime][nCntPlayer] != NULL)
			{
				m_apNumber[nCntTime][nCntPlayer]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}
	}
}

//=============================================================================
// �f�o�b�N�p
//=============================================================================
void CTutoTime::DebugKey(void)
{
	// �f�o�b�N�p
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_NUMPAD0))
	{	// �������ԉ��Z
		AddTime(1);
	}

	if (CManager::GetInputKeyboard()->GetPress(DIK_NUMPAD6))
	{	// �������ԉ��Z
		m_nTimeCount--;
	}
	if (CManager::GetInputKeyboard()->GetPress(DIK_NUMPAD4))
	{	// �������ԉ��Z
		m_nTimeCount++;
	}
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_NUMPAD9))
	{	// ���U���g��ʂ�
		m_nTime = 0;
		m_nTimeOne = 0;
	}
}