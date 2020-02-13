//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : �ڍ� ������/Akane Gokan
//
//=============================================================================
#include "title.h"
#include "debugProc.h"
#include "input.h"
#include "InputKeyboard.h"
#include "manager.h"
#include "fade.h"
#include "time.h"
#include "scene3D.h"
#include "scene2D.h"
#include "sceneX.h"
#include "sceneBillboard.h"
#include "SetObject.h"
#include "PlayerNumSelect.h"
//============================================================================
//	�}�N����`
//============================================================================

//============================================================================
//�ÓI�����o�ϐ��錾
//============================================================================

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// �|���S���̏���������
//=============================================================================
void CTitle::Init(void)
{
	//�����o�ϐ�������
	m_bProductionSkip = false;					//���o�X�L�b�v����Ă��Ȃ�
	m_FlashSkip = false;						//�t���b�V���X�L�b�v����Ă��Ȃ�
	m_ProductionState = PRODUCTIONSTATE_NONE;	//���o��Ԃ̏�����
	m_FlashSate = FLASHSTATE_NONE;				//�t���b�V����Ԃ̏�����
	m_bTitleCall = false;
	m_bSubTitleCall = false;
	m_nTitleCallCnt = 0;

	/*�Ή�*/
	m_fChangeSparkMove = 3.5f;
	m_fSparkX = 0.0f;

	/*�t���b�V���n*/
	m_fCntFade = 0.0f;
	m_fAlpha = 0.0f;
	m_nCntFadeTime = 0;

	/*�v���X�{�^��*/
	m_nCntFlashPress = 0;
	m_fPressAlpha = 1.0f;
	m_bPressMode = false;

	/* �^�C�g�����S */
	m_fTitleScal = 100;
	/* �V�[��2D�̏����ݒ� */
	InitpScene2D();

	/* �V�[��2D�̏����ݒ菈�� */
	SetScene2D();

#ifdef _DEBUG
	nCntFadeTime = 0;
#endif
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CTitle::Uninit(void)
{
	// Scene2D�̔j��
	UninitpScene2D();

	//�S�Ă̏I������
	CScene::ReleseAll();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CTitle::Update(void)
{
	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();
	CSound *pSound = CManager::GetSound();		//	���̎擾

	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	//CXInputJoyPad *pXInput = NULL;
	//pXInput = CManager::GetXInput();

	/* ���o�����֐��Ăяo�� */
	Production();
	Flash();

	//�C�ӂ̃L�[ENTER
	if (m_bProductionSkip == true)
	{//���o�X�L�b�v�ς�
		SparkProduction();	//�ΉԈړ�����
		if (m_FlashSkip == true)
		{// �t���b�V�����o�X�L�b�v�ς�
			if (CCommand::GetCommand("DECISION"))
			{//�G���^�[����
				m_bPressMode = true;
				if (pFade->GetFade() != CFade::FADE_OUT)
				{
					pSound->PlaySound(CSound::SOUND_LABEL_SE_TITLE);
				}
				pFade->SetFade(pManager->MODE_SELECT, pFade->FADE_OUT);
			}
		}
	}

	if (m_bProductionSkip == false)
	{//���o���X�L�b�v
		if (m_FlashSkip == false)
		{// �t���b�V�����o���X�L�b�v
			if (CCommand::GetCommand("DECISION"))
			{//�G���^�[����
				m_ProductionState = PRODUCTIONSTATE_FLASH;	//�t���b�V�����J�n
				m_bProductionSkip = true;
			}
		}
	}
	else if (m_bProductionSkip == true)
	{//���o�X�L�b�v�ς�
		if (m_FlashSkip == false)
		{// �t���b�V�����o���X�L�b�v
			if (CCommand::GetCommand("DECISION"))
			{//�G���^�[����
				m_FlashSate = FLASHSTATE_FINISH;
			}
		}
	}

	//�^�C�g���R�[��
	if (m_bTitleCall == true)
	{
		if(m_nTitleCallCnt == 0  && m_bSubTitleCall == false)
		{
			pSound->PlaySound(CSound::SOUND_LABEL_VOICE_TITLECALL00);
			m_bSubTitleCall = true;
		}
		if (m_nTitleCallCnt == 40)
		{
			pSound->SetVolume(CSound::SOUND_LABEL_VOICE_TITLECALL01, 5.0f);
			pSound->PlaySound(CSound::SOUND_LABEL_VOICE_TITLECALL01);
			m_bTitleCall = false;
		}
		m_nTitleCallCnt++;
	}


#ifdef _DEBUG
	CDebugProc::Print("c", "�^�C�g��");

	if (CManager::GetRepeat() == true)
	{
		nCntFadeTime++;
		if (nCntFadeTime > 600)
		{
			pFade->SetFade(pManager->MODE_SELECT, pFade->FADE_OUT);
		}
	}
#endif
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CTitle::Draw(void)
{

}
//=============================================================================
// �|�C���^�̏���������
//=============================================================================
void CTitle::InitpScene2D(void)
{

	/* �|�C���^�̏����� */
	for (int nCnt = 0; nCnt < MAX_TITLEPOLYGON; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{
			m_pScene2D[nCnt] = NULL;
		}
	}
}
//=============================================================================
// 2D�|���S���̏I������
//=============================================================================
void  CTitle::UninitpScene2D(void)
{
	/* �|�C���^�̏����� */
	for (int nCnt = 0; nCnt < MAX_TITLEPOLYGON; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{
			m_pScene2D[nCnt]->Uninit();
			m_pScene2D[nCnt] = NULL;
		}
	}

}
//=============================================================================
// 2D�|���S���̏����ݒ�
//=============================================================================
void CTitle::SetScene2D(void)
{
	if (m_pScene2D[POLYGONTYPE_BALANCEBOY] == NULL)
	{//�l��_�o�����X�j�q
		/* �e��ݒ� */
		m_pScene2D[POLYGONTYPE_BALANCEBOY] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT/2, 0.0f), "TITLE_HUMAN");
		m_pScene2D[POLYGONTYPE_BALANCEBOY]->SetWidthHeight(BG_HUMAN_SIZE_W, 510.0f); //�T�C�Y
		m_pScene2D[POLYGONTYPE_BALANCEBOY]->SetPos(D3DXVECTOR3(130.0f, SCREEN_HEIGHT + SCREEN_HEIGHT - 300.0f, 0.0f), 0.0f, 1.0f, COL_DEFAULT);
		m_pScene2D[POLYGONTYPE_BALANCEBOY]->SetAnimation(POLYGONTYPE_BALANCEBOY, 0.25f, 1.0f);			//�A�j���[�V����
	}
	if (m_pScene2D[POLYGONTYPE_REACHGIRL] == NULL)
	{//�l��_���[�`���q
		/* �e��ݒ� */
		m_pScene2D[POLYGONTYPE_REACHGIRL] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), "TITLE_HUMAN");
		m_pScene2D[POLYGONTYPE_REACHGIRL]->SetWidthHeight(BG_HUMAN_SIZE_W, 510.0f); //�T�C�Y
		m_pScene2D[POLYGONTYPE_REACHGIRL]->SetPos(D3DXVECTOR3(460.0f, 0.0f - SCREEN_HEIGHT + 300.0f, 0.0f), 0.0f, 1.0f, COL_DEFAULT);
		m_pScene2D[POLYGONTYPE_REACHGIRL]->SetAnimation(POLYGONTYPE_REACHGIRL, 0.25f, 1.0f);			//�A�j���[�V����
	}
	if (m_pScene2D[POLYGONTYPE_POWORBOY] == NULL)
	{//�l��_�p���[�j�q
		/* �e��ݒ� */
		m_pScene2D[POLYGONTYPE_POWORBOY] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), "TITLE_HUMAN");
		m_pScene2D[POLYGONTYPE_POWORBOY]->SetWidthHeight(BG_HUMAN_SIZE_W, 510.0f); //�T�C�Y
		m_pScene2D[POLYGONTYPE_POWORBOY]->SetPos(D3DXVECTOR3(790.0f, SCREEN_HEIGHT + SCREEN_HEIGHT - 300.0f , 0.0f), 0.0f, 1.0f, COL_DEFAULT);
		m_pScene2D[POLYGONTYPE_POWORBOY]->SetAnimation(POLYGONTYPE_POWORBOY, 0.25f, 1.0f);			//�A�j���[�V����
	}
	if (m_pScene2D[POLYGONTYPE_SPEEDGIRL] == NULL)
	{//�l��_�X�s�[�h���q
		/* �e��ݒ� */
		m_pScene2D[POLYGONTYPE_SPEEDGIRL] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), "TITLE_HUMAN");
		m_pScene2D[POLYGONTYPE_SPEEDGIRL]->SetWidthHeight(BG_HUMAN_SIZE_W, 510.0f);	//�T�C�Y
		m_pScene2D[POLYGONTYPE_SPEEDGIRL]->SetPos(D3DXVECTOR3(1120.0f, 0.0f - SCREEN_HEIGHT + 300.0f, 0.0f), 0.0f, 1.0f, COL_DEFAULT);
		m_pScene2D[POLYGONTYPE_SPEEDGIRL]->SetAnimation(POLYGONTYPE_SPEEDGIRL, 0.25f, 1.0f);			//�A�j���[�V����
	}
	if (m_pScene2D[POLYGONTYPE_KOTOMON] == NULL)
	{//�R�g����
		/* �e��ݒ� */
		m_pScene2D[POLYGONTYPE_KOTOMON] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2+50.0f, SCREEN_HEIGHT / 2-20.0f, 0.0f), "TITLE_KOTOMON");
		m_pScene2D[POLYGONTYPE_KOTOMON]->SetWidthHeight(SCREEN_WIDTH - 300.0f, SCREEN_HEIGHT - 180.0f);	//�T�C�Y
		m_pScene2D[POLYGONTYPE_KOTOMON]->SetCol(COL_DEFAULT_TRANSPARENT);
	}
	if (m_pScene2D[POLYGONTYPE_SPARK] == NULL)
	{//�Ή�
		/* �e��ݒ� */
		m_pScene2D[POLYGONTYPE_SPARK] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), "TITLE_HIBANA");
		m_pScene2D[POLYGONTYPE_SPARK]->SetWidthHeight(250.0f, 250.0f);	//�T�C�Y
		m_pScene2D[POLYGONTYPE_SPARK]->SetCol(COL_DEFAULT_TRANSPARENT);

	}
	if (m_pScene2D[POLYGONTYPE_ROGO_MAIN] == NULL)
	{//�^�C�g�����S�F�R�g�o�g��
		/* �e��ݒ� */
		m_pScene2D[POLYGONTYPE_ROGO_MAIN] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), "TITLE_ROGO_M");
		m_pScene2D[POLYGONTYPE_ROGO_MAIN]->SetWidthHeight(550.0f, 200.0f);	//�T�C�Y
		m_pScene2D[POLYGONTYPE_ROGO_MAIN]->SetCol(COL_DEFAULT_TRANSPARENT);
	}
	if (m_pScene2D[POLYGONTYPE_ROGO_SUB] == NULL)
	{//�^�C�g�����S�F������
		/* �e��ݒ� */
		m_pScene2D[POLYGONTYPE_ROGO_SUB] = CScene2D::Create(D3DXVECTOR3(400.0f, 250.0f, 0.0f), "TITLE_ROGO_S");
		m_pScene2D[POLYGONTYPE_ROGO_SUB]->SetWidthHeight(250.0f, 70.0f);	//�T�C�Y
		m_pScene2D[POLYGONTYPE_ROGO_SUB]->SetCol(COL_DEFAULT_TRANSPARENT);
	}
	if (m_pScene2D[POLYGONTYPE_FLASH] == NULL)
	{//�t���b�V���p
		/* �e��ݒ� */
		m_pScene2D[POLYGONTYPE_FLASH] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), " ");
		m_pScene2D[POLYGONTYPE_FLASH]->SetWidthHeight(SCREEN_WIDTH - 350.0f, SCREEN_HEIGHT - 200.0f);	//�T�C�Y
		m_pScene2D[POLYGONTYPE_FLASH]->SetCol(COL_DEFAULT_TRANSPARENT);								//�F
	}
	if (m_pScene2D[POLYGONTYPE_PRESSBUTTON] == NULL)
	{//�v���X�{�^��
	 /* �e��ݒ� */
		m_pScene2D[POLYGONTYPE_PRESSBUTTON] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT-100.0f, 0.0f), "PRESS");
		m_pScene2D[POLYGONTYPE_PRESSBUTTON]->SetWidthHeight(SCREEN_WIDTH/3 , SCREEN_HEIGHT/10);	//�T�C�Y
		m_pScene2D[POLYGONTYPE_PRESSBUTTON]->SetCol(COL_DEFAULT);								//�F
	}

	// ���o�J�n��ԂɕύX
	m_ProductionState = PRODUCTIONSTATE_START;
}
//=============================================================================
// ���o����
//=============================================================================
void CTitle::Production(void)
{
	CSound *pSound = CManager::GetSound();		//	���̎擾

	switch (m_ProductionState)
	{
	case PRODUCTIONSTATE_NONE:
		/* ���o���Ȃ���� */
		break;

	case PRODUCTIONSTATE_START:
		/* ���o�̊J�n */
		m_ProductionState = PRODUCTIONSTATE_MOVE_B;
		break;

	case PRODUCTIONSTATE_MOVE_B:
		/* �o�����X�j�q�ړ� */
		if (MoveBGCharactor(POLYGONTYPE_BALANCEBOY) == true)
		{
			m_ProductionState = PRODUCTIONSTATE_MOVE_R;
		}
		break;

	case PRODUCTIONSTATE_MOVE_R:
		/* ���[�`���q�ړ� */
		if (MoveBGCharactor(POLYGONTYPE_REACHGIRL) == true)
		{
			m_ProductionState = PRODUCTIONSTATE_MOVE_P;
		}
		break;

	case PRODUCTIONSTATE_MOVE_P:
		/* �p���[�j�q�ړ� */
		if (MoveBGCharactor(POLYGONTYPE_POWORBOY) == true)
		{
			m_ProductionState = PRODUCTIONSTATE_MOVE_S;
		}
		break;

	case PRODUCTIONSTATE_MOVE_S:
		/* �X�s�[�h���q�ړ� */
		if (MoveBGCharactor(POLYGONTYPE_SPEEDGIRL) == true)
		{
			m_ProductionState = PRODUCTIONSTATE_TITLE_SUB;
		}
		break;

	case PRODUCTIONSTATE_TITLE_SUB:
		/* �T�u�^�C�g�� */
		if (TitleScaling(POLYGONTYPE_ROGO_SUB) == true)
		{
			m_ProductionState = PRODUCTIONSTATE_TITLE_MAIN;
		}

		pSound->PlaySound(CSound::SOUND_LABEL_VOICE_TITLECALL00);
		m_bSubTitleCall = true;
		break;

	case PRODUCTIONSTATE_TITLE_MAIN:
		/* ���C���^�C�g�� */
		if (TitleScaling(POLYGONTYPE_ROGO_MAIN) == true)
		{
			m_ProductionState = PRODUCTIONSTATE_FLASH;
		}
		m_bTitleCall = true;
		break;

	case PRODUCTIONSTATE_FLASH:
		/* �t���b�V���J�n�ƃ|���S�����t���b�V���I����̐F�֕ύX */
		HumanProductionPos();

		m_FlashSate = FLASHSTATE_START;
		m_ProductionState = PRODUCTIONSTATE_FINISH;
		break;

	case PRODUCTIONSTATE_FINISH:
		/* ���o�S�H�����I����� */
		m_bProductionSkip = true;					//���o���X�L�b�v���
		m_ProductionState = PRODUCTIONSTATE_NONE;	//���o���Ȃ���Ԃɖ߂�
		m_bTitleCall = true;
		break;
	}
	Flash();
	PressProduction();
}
//=============================================================================
// ���o����
//=============================================================================
void CTitle::Flash(void)
{
	switch (m_FlashSate)
	{
	case FLASHSTATE_NONE:
		break;

	case FLASHSTATE_START:
		m_pScene2D[POLYGONTYPE_FLASH]->SetCol(COL_DEFAULT);
		m_fCntFade = 1.0f;
		m_nCntFadeTime++;

		if (m_nCntFadeTime >= 30)
		{//0.5�b����ʂɂȂ�����
			m_FlashSate = FLASHSTATE_FADEOUT;
		}
		break;

	case FLASHSTATE_FADEOUT:
		if (m_fAlpha < 0.0f)
		{//�����x��0�ȉ�
			m_pScene2D[POLYGONTYPE_FLASH]->SetCol(COL_DEFAULT_TRANSPARENT);
			m_FlashSate = FLASHSTATE_FINISH;
			m_ProductionState = PRODUCTIONSTATE_FINISH;
		}
		else
		{
			m_fCntFade = m_fCntFade - 0.008f;
			m_fAlpha = m_fCntFade;
		}
		m_pScene2D[POLYGONTYPE_FLASH]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha));
		break;

	case FLASHSTATE_FINISH:
		m_pScene2D[POLYGONTYPE_FLASH]->SetCol(COL_DEFAULT_TRANSPARENT);
		m_FlashSkip = true;
		m_FlashSate = FLASHSTATE_NONE;
		break;
	}
}
//=============================================================================
// �w�i�ړ�����
//=============================================================================
bool CTitle::MoveBGCharactor(int Num)
{
	bool bMove = false;
	float fMoveY = -20.0f;	//�ړ�������p(�����O��)
	D3DXVECTOR3 Pos = m_pScene2D[Num]->GetPosition();

	if (Num % 2 != 0)
	{//��������Ȃ�������ړ������̕ύX
		fMoveY *= -1.0f;
	}

	/* �e�N�X�`���̈ړ� */
	Pos.y += fMoveY;
	m_pScene2D[Num]->SetPos(Pos, 0.0f, 1.0f, COL_DEFAULT);

	if (Num % 2 == 0)
	{//�����̏ꍇ
		if (Pos.y <= SCREEN_HEIGHT / 2)
		{
			bMove = true;
		}
	}
	else if (Num % 2 != 0)
	{//��������Ȃ��ꍇ
		if (Pos.y >= SCREEN_HEIGHT / 2)
		{
			bMove = true;
		}
	}
	return bMove;
}
//=============================================================================
// �^�C�g�����S�̊g�k����
//=============================================================================
bool CTitle::TitleScaling(int Num)
{
	bool bTitleScaling = false;

	if (Num % 2 == 0)
	{//�����i���C���j
		m_pScene2D[Num]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - TITLEROGO_CORRECTION, 0.0f), 0.0f, m_fTitleScal, COL_DEFAULT);
		m_fTitleScal -= 8.0f;

		if (m_fTitleScal <= 1.0f)
		{
			bTitleScaling = true;
			m_fTitleScal = 0.0f;
		}
	}
	else
	{//��i�T�u�j
		m_pScene2D[Num]->SetPos(D3DXVECTOR3(400.0f, 250.0f - TITLEROGO_CORRECTION, 0.0f), 0.0f, m_fTitleScal, COL_DEFAULT);
		m_fTitleScal -= 5.0f;
		if (m_fTitleScal <= 1.0f)
		{
			bTitleScaling = true;
			m_fTitleScal = 200.0f;
		}
	}

	return bTitleScaling;
}
//=============================================================================
// �X�L�b�v�������̈ʒu�ύX����
//=============================================================================
void CTitle::HumanProductionPos(void)
{
	/* �o�����X�j�q */
	m_pScene2D[POLYGONTYPE_BALANCEBOY]
		->SetPos(D3DXVECTOR3(m_pScene2D[POLYGONTYPE_BALANCEBOY]->GetPosition().x, POS_DEFOLT.y, POS_DEFOLT.z), 0.0f, 0.0f, COL_PRODUCTION_HUMAN);
	/* ���[�`���q */
	m_pScene2D[POLYGONTYPE_REACHGIRL]
		->SetPos(D3DXVECTOR3(m_pScene2D[POLYGONTYPE_REACHGIRL]->GetPosition().x, POS_DEFOLT.y, POS_DEFOLT.z), 0.0f, 0.0f, COL_PRODUCTION_HUMAN);
	/* �p���[�j�q */
	m_pScene2D[POLYGONTYPE_POWORBOY]
		->SetPos(D3DXVECTOR3(m_pScene2D[POLYGONTYPE_POWORBOY]->GetPosition().x, POS_DEFOLT.y, POS_DEFOLT.z), 0.0f, 0.0f, COL_PRODUCTION_HUMAN);
	/* �X�s�[�h���q */
	m_pScene2D[POLYGONTYPE_SPEEDGIRL]
		->SetPos(D3DXVECTOR3(m_pScene2D[POLYGONTYPE_SPEEDGIRL]->GetPosition().x, POS_DEFOLT.y, POS_DEFOLT.z), 0.0f, 0.0f, COL_PRODUCTION_HUMAN);
	/* ���C���^�C�g�� */
	m_pScene2D[POLYGONTYPE_ROGO_MAIN]
		->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - TITLEROGO_CORRECTION, 0.0f),0.0f,0.0f,COL_DEFAULT);
	m_pScene2D[POLYGONTYPE_ROGO_MAIN]->SetCol(COL_DEFAULT);
	/* �T�u�^�C�g�� */
	m_pScene2D[POLYGONTYPE_ROGO_SUB]
		->SetPos(D3DXVECTOR3(400.0f, 250.0f - TITLEROGO_CORRECTION, 0.0f), 0.0f, 0.0f, COL_DEFAULT);
	m_pScene2D[POLYGONTYPE_ROGO_SUB]->SetCol(COL_DEFAULT);

	/* �R�g���� */
	m_pScene2D[POLYGONTYPE_KOTOMON]->SetCol(COL_DEFAULT);

	/* �Ή� */
	m_pScene2D[POLYGONTYPE_SPARK]->SetCol(COL_DEFAULT);

}
//=============================================================================
// �ΉԂ̉��o����
//=============================================================================
void CTitle::SparkProduction(void)
{
	D3DXVECTOR3 SparkPos = m_pScene2D[POLYGONTYPE_SPARK]->GetPosition();

	if (m_fSparkX >= 5.0f|| m_fSparkX <= -5.0f)
	{
		m_fChangeSparkMove *= -1.0f;
	}

	//�ړ��ʂ����Z
	m_fSparkX += m_fChangeSparkMove;
	SparkPos.x += m_fSparkX;

	m_pScene2D[POLYGONTYPE_SPARK]->SetPos(SparkPos, 0.0f, 0.0f, COL_DEFAULT);
}
//=============================================================================
// �v���X�{�^���̉��o����
//=============================================================================
void CTitle::PressProduction(void)
{
	m_nCntFlashPress++;
	if (m_bPressMode == false)
	{
		if (m_nCntFlashPress >= 30)
		{
			m_pScene2D[POLYGONTYPE_PRESSBUTTON]->SetCol(D3DXCOLOR(COL_DEFAULT.r, COL_DEFAULT.g, COL_DEFAULT.b, m_fPressAlpha));
			m_fPressAlpha *= -1.0f;
			m_nCntFlashPress = 0;
		}
	}
	else
	{
		if (m_nCntFlashPress >= 3)
		{
			m_pScene2D[POLYGONTYPE_PRESSBUTTON]->SetCol(D3DXCOLOR(COL_DEFAULT.r, COL_DEFAULT.g, COL_DEFAULT.b, m_fPressAlpha));
			m_fPressAlpha *= -1.0f;
			m_nCntFlashPress = 0;
		}
	}
}