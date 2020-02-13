//=============================================================================
//
// �L�����Z���N�g���� [CharaSelect.cpp]
// Author : �ڍ� ������/��Ձ@��
//
//=============================================================================
#include "CharaSelect.h"
#include "manager.h"
#include "debugProc.h"
#include "fade.h"
#include "input.h"
#include "InputKeyboard.h"
#include"game.h"
#include "CharaSelect_Cursol.h"

//============================================================================
//	�}�N����`
//============================================================================
#define SIZE_X (SCREEN_WIDTH/2)									//����
#define SIZE_Y (SCREEN_HEIGHT/2)								//�c��
#define DEFAULT_SIZE (150.0f)									//�|���S���T�C�Y�̊�{�̑傫��
#define DEFAULT_POS	(D3DXVECTOR3(0.0f,0.0f,0.0f))				//�|���S���̏����ʒu
#define CHARASELCHOICE_POS	(D3DXVECTOR3(211.0f,230.0f,0.0f))	//�I�����|���S���̈ʒu
#define TEX_CORRECTION (0.001f)									//�e�N�X�`�����W�̕␳
#define CHARASELICON_INTERVAL (215.0f)							//�I�����A�C�R�����m�̊Ԋu

//============================================================================
//�ÓI�����o�ϐ��錾
//============================================================================
CScene2D *CCharaSelect::m_apScene2D[MAX_CHARASELTEX] = {};
CScene2D *CCharaSelect::m_apSelect2D[MAX_CHARASELECT] = {};
CScene2D *CCharaSelect::m_apConfirm2D = NULL;
CCharaSelCursol *CCharaSelect::m_apCursol[MAX_PLAYER] = {};
bool CCharaSelect::m_bCharaCard = false;
bool CCharaSelect::m_bBackModeColl[MAX_PLAYER] = { false,false ,false ,false };
//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CCharaSelect::CCharaSelect()
{
	m_PlayerNum = NULL;
	/* ���o�n�ϐ������� */
	m_nCntScrool = 0;
	m_CntFlash = 0;
	m_CntFadeF = 0;
	m_moveConfPro = 0.0f;
	m_CnfProState = CONFPRODUCTION_NONE;
	m_bConfProFinish = false;
	m_bConf = false;
	m_bConfProStart = false;
	m_bCnfFlash = false;
	m_bCharaCard = false;
	m_CharaCardProduction = CHARACARDPRO_START;
	m_fCharaCardPro_FinishWH[0] = 0.0f;
	m_fCharaCardPro_FinishWH[1] = 0.0f;
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		m_fFlashAlpha[nCnt] = 0.0f;
		m_fGaugeSizeX[nCnt] = 0.0f;
		m_fMaxGaugeX[nCnt]= 0.0f;
	}
	for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
	{
		m_CharaCardPro_FinishPos[nCnt] = DEFAULT_POS;
		m_fCardWidth[nCnt][0] = m_fCharaCardPro_FinishWH[0];
		m_fCardWidth[nCnt][1] = m_fCharaCardPro_FinishWH[1];
	}
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CCharaSelect::~CCharaSelect()
{

}

//=============================================================================
// �L�����Z���N�g�̏���������
//=============================================================================
void CCharaSelect::Init(void)
{
	//�C���X�^���X
	CManager *pManager = NULL;

	/* �|�C���^�̏��������� */
	Initpointer();

	/* �|���S���̏����ݒ� */
	InitCharaSelectPoly();

	/* �J�[�\���ƃo�b�W�̐��� */
	m_apCursol[0] = CCharaSelCursol::Create(0);
	m_apCursol[1] = CCharaSelCursol::Create(1);
	m_apCursol[2] = CCharaSelCursol::Create(2);
	m_apCursol[3] = CCharaSelCursol::Create(3);
}
//=============================================================================
// �L�����Z���N�g�̏I������
//=============================================================================
void CCharaSelect::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_CHARASELTEX; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt]->Uninit();
			m_apScene2D[nCnt] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
	{
		if (m_apSelect2D[nCnt] != NULL)
		{
			m_apSelect2D[nCnt]->Uninit();
			m_apSelect2D[nCnt] = NULL;
		}
	}
	if (m_apConfirm2D != NULL)
	{
		m_apConfirm2D->Uninit();
		m_apConfirm2D = NULL;
	}

	//�S�Ă̏I������
	CScene::ReleseAll();
}

//=============================================================================
// �L�����Z���N�g�̍X�V����
//=============================================================================
void CCharaSelect::Update(void)
{

	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	/*�J�[�h���o*/
	if (m_bCharaCard == false)
	{
		ProductionCard();
	}

	if (ConfirmationSelect() == true)
	{//�S���I������
		if (m_bConfProStart == false)
		{//���o���n�܂��Ă��Ȃ�������n�߂�
			m_CnfProState = CONFPRODUCTION_MOVE_START;
			m_bConfProStart = true;
		}
		if (m_bConfProStart == true)
		{//���o���n�܂�����
			m_bConfProFinish = ProductionConf();
		}
		if (m_bConfProFinish == true)
		{//���o���I������
			m_bConf = true;	//�I�𑀍�\�ɂ���
		}
	}
	else
	{//�S���I�����Ă��Ȃ�
		m_apConfirm2D->SetbDraw(false);
		m_bConfProFinish = false;
		m_bConf = false;
		m_bConfProStart = false;
	}

	/* �т̃e�N�X�`���X�N���[�� */
	ScrollMenu(CHARASEL_POLYGONTYPE_BAND_R, 0.005f);
	ScrollMenu(CHARASEL_POLYGONTYPE_BAND_L, -0.005f);

	/* �m��|���̃t���b�V�����o */
	if (m_bCnfFlash == true) { FlashConf();}

	/* �߂�|���S���̉��o */
	SetBackModeTex();
#ifdef _DEBUG
	CDebugProc::Print("c", "�L�����Z���N�g");
	if (CManager::GetRepeat() == true)
	{
		nCntFadeTime++;
		if (nCntFadeTime > 120)
		{
			m_CharaType[0] = CPlayer::TYPE_BARANCE;
			m_CharaType[1] = CPlayer::TYPE_POWER;
			m_CharaType[2] = CPlayer::TYPE_SPEED;
			m_CharaType[3] = CPlayer::TYPE_REACH;
			for (int nCnt = 0; nCnt < *m_PlayerNum; nCnt++)
			{//�v���C���[�l�����L�����̎�ނ�n��
				CGame::SetCharaSelect(nCnt, m_CharaType[nCnt]);
			}
			pFade->SetFade(pManager->MODE_STAGESELECT, pFade->FADE_OUT);
		}
	}
#endif
}

//=============================================================================
// �L�����Z���N�g�̕`�揈��
//=============================================================================
void CCharaSelect::Draw(void) {}

//=============================================================================
// �|�C���^�̏���������
//=============================================================================
void CCharaSelect::Initpointer(void)
{
	for (int nCnt = 0; nCnt < MAX_CHARASELTEX; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL) { m_apScene2D[nCnt] = NULL; }
	}
	for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
	{
		if (m_apSelect2D[nCnt] != NULL) { m_apSelect2D[nCnt] = NULL; }
	}
	if (m_apConfirm2D != NULL) { m_apConfirm2D = NULL; }
}
//=============================================================================
// �|���S���̏����ݒ�
//=============================================================================
void CCharaSelect::InitCharaSelectPoly(void)
{
	/* �v���C���[�̐l���擾 */
	m_PlayerNum = CPlayerSelect::GetModeSelectMode();

	/* �I���� */
	for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
	{
		/* �����ƍ��W�ƃe�N�X�`�� */
		m_apSelect2D[nCnt] = CScene2D::Create(D3DXVECTOR3(CHARASELCHOICE_POS.x + (CHARASELICON_INTERVAL*nCnt),
			CHARASELCHOICE_POS.y,
			CHARASELCHOICE_POS.z), "PLAYERSELECT_BACK");
		/* �T�C�Y�ݒ� */
		m_apSelect2D[nCnt]->SetWidthHeight(DEFAULT_SIZE*1.0f, DEFAULT_SIZE*1.3f);

		m_CharaCardPro_FinishPos[nCnt] = m_apSelect2D[nCnt]->GetPosition();
		m_fCharaCardPro_FinishWH[0] = m_apSelect2D[nCnt]->GetSize(0);
		m_fCharaCardPro_FinishWH[1] = m_apSelect2D[nCnt]->GetSize(1);
		m_fCardWidth[nCnt][0] = m_apSelect2D[nCnt]->GetSize(0);
		m_fCardWidth[nCnt][1] = m_apSelect2D[nCnt]->GetSize(1);
	}

	/* ���o */
	// �w�i
	m_apScene2D[0] = CScene2D::Create(D3DXVECTOR3(SIZE_X, SIZE_Y, 0), "PLAYERNUMSEL_BG", 1);
	m_apScene2D[0]->SetWidthHeight(DEFAULT_SIZE*6.0f, DEFAULT_SIZE*3.5f);

	//���[�h���сi���j
	m_apScene2D[1] = CScene2D::Create(D3DXVECTOR3(50.0f, SIZE_Y, 0.0f), "CHARACTORSEL_BAND", 4);
	m_apScene2D[1]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*3.5f);

	//���[�h���сi�E�j
	m_apScene2D[2] = CScene2D::Create(D3DXVECTOR3(1230.0f, SIZE_Y, 0.0f), "CHARACTORSEL_BAND", 4);
	m_apScene2D[2]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*3.5f);

	//�߂�
	m_apScene2D[3] = CScene2D::Create(D3DXVECTOR3(SIZE_X, (DEFAULT_SIZE*0.4f) / 2, 0.0f), "CHARASEL_BACKMODE");
	m_apScene2D[3]->SetWidthHeight(DEFAULT_SIZE*5.2f, DEFAULT_SIZE*0.4f);
	m_apScene2D[3]->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 0.5f));

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		//�v���C���[�E�B���h
		/* �����ƍ��W�ƃe�N�X�`�� */
		m_apScene2D[nCnt + 4] = CScene2D::Create(D3DXVECTOR3(250.0f+(260.0f*nCnt), 545.0f, 0.0f), "PLAYER_UIWINDOW", 2);
		/* �T�C�Y�ݒ� */
		m_apScene2D[nCnt + 4]->SetWidthHeight(DEFAULT_SIZE*1.2f, DEFAULT_SIZE*1.6f);
		m_apScene2D[nCnt + 4]->SetTex(D3DXVECTOR2(0.0f, 0.8f), D3DXVECTOR2(0.2f, 1.0f));//�����ݒ�͑S��COM�A����SWICH�ōĐݒ�

		// �v���C���[�E�B���h�}�X�N
		/* �����ƍ��W�ƃe�N�X�`�� */
		m_apScene2D[nCnt + 8] = CScene2D::Create(D3DXVECTOR3(250.0f + (260.0f*nCnt), 545.0f, 0.0f), " ");
		/* �T�C�Y�ݒ� */
		m_apScene2D[nCnt + 8]->SetWidthHeight(DEFAULT_SIZE*1.2f, DEFAULT_SIZE*1.6f);
		m_apScene2D[nCnt + 8]->SetbDraw(false);

		//�v���C���[�E�B���h�E�ɕ\������L�����N�^�[
		/* �����ƍ��W�ƃe�N�X�`�� */
		m_apScene2D[nCnt + 12] = CScene2D::Create(D3DXVECTOR3(250.0f + (260.0f*nCnt), 545.0f+20.0f, 0.0f), "CHARACTORSEL_CHARA", 2);
		/* �T�C�Y�ݒ� */
		m_apScene2D[nCnt + 12]->SetWidthHeight(DEFAULT_SIZE*1.1f, DEFAULT_SIZE*1.2f);
		m_apScene2D[nCnt + 12]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MAX_CHARASELECT)*nCnt), 0.5f),
			D3DXVECTOR2((1.0f / MAX_CHARASELECT) + ((1.0f / MAX_CHARASELECT)*nCnt) - TEX_CORRECTION, 1.0f));
		m_apScene2D[nCnt + 12]->SetbDraw(false);
		/* �v���C���[�l���ɍ��킹�Đݒ� */
		// �v���C���[�E�B���h�E�̃e�N�X�`�����W
		if (nCnt < (int)*m_PlayerNum)
		{
			m_apScene2D[nCnt + 4]->SetTex(D3DXVECTOR2(0.0f, 0.0f + (1.0f / 5)*nCnt), D3DXVECTOR2(0.2f, 0.2f + (1.0f / 5)*nCnt));
		}
		else
		{
			m_apScene2D[nCnt + 4]->SetTex(D3DXVECTOR2(0.0f, 0.8f), D3DXVECTOR2(0.2f, 1.0f));
		}
	}

	/* �L�����I���m�� */
	m_apConfirm2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), "PLAYER_CONFIRM",4);
	m_apConfirm2D->SetWidthHeight(DEFAULT_SIZE*4.5f, DEFAULT_SIZE*0.8f);
	m_apConfirm2D->SetbDraw(false);
}
//=============================================================================
// ���̕����X�N���[������
//=============================================================================
void CCharaSelect::ScrollMenu(CHARASEL_POLYGONTYPE type, float fScroolSpeed)
{
	m_nCntScrool++;
	if (m_apScene2D[type] != NULL)
	{
		m_apScene2D[type]->SetTex(D3DXVECTOR2(0.0f, 0.0f + (m_nCntScrool*fScroolSpeed)),
									D3DXVECTOR2(1.0f, 1.0f + (m_nCntScrool*fScroolSpeed)));
	}
}
//=============================================================================
// �I�����o����
//=============================================================================
void CCharaSelect::SelectProduction(int nNum, SELECT_STATE &Sel, SELECT_STATE &Selold, CPlayer::PLAYER_TYPE type)
{
	switch (Sel)
	{
	case SELECTSTATE_NONE:
		break;

	case SELECTSTATE_FLASH:		//���o��
		if (Selold != SELECTSTATE_FLASH)
		{//�O��̃��[�h��Flash�ȊO�̏ꍇa�l��������
			m_fFlashAlpha[nNum] = 1.0f;
		}
		m_apScene2D[nNum + 8]->SetbDraw(true);											//�}�X�N�̕`�悷��
		m_apScene2D[nNum + 8]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fFlashAlpha[nNum]));	//�F

		if (m_fFlashAlpha[nNum] <= 0.0f)
		{//�����x��������؂���
			m_apScene2D[nNum + 8]->SetbDraw(false);								//�}�X�N��`�悵�Ȃ��󋵂�
			m_apScene2D[nNum + 8]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//�}�X�N�̐F����ɖ߂��Ă���
			m_fFlashAlpha[nNum] = 0.0f;											//a�l���Y��Ȑ����ɕύX
			Sel = SELECTSTATE_SELECT;											//�I�����ꂽ��ԂɕύX
		}
		else
		{
			m_fFlashAlpha[nNum] -= 0.02f;
			m_apScene2D[nNum + 8]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fFlashAlpha[nNum]));
		}
		break;

	case SELECTSTATE_SELECT:	//�I������Ă���
		if (m_apScene2D[nNum + 8]->GetbDraw() != false)
		{
			m_apScene2D[nNum + 8]->SetbDraw(false);
		}
		break;

	case SELECTSTATE_NOSELECT:	//�I������Ă��Ȃ�
		if (m_apScene2D[nNum + 8]->GetbDraw() != false)
		{
			m_apScene2D[nNum + 8]->SetbDraw(false);
		}
		break;
	}

	//����̑I����Ԃ�O��̑I����ԂƂ��ĕۑ�
	Selold = Sel;
}
//=============================================================================
// �����蔻��
//=============================================================================
bool CCharaSelect::collision(int operation, CPlayer::PLAYER_TYPE type)
{
	bool bColl = false;

	/* �����蔻�� */
	if (m_apCursol[operation]->GetpBadge()->GetPosition().x - (m_apCursol[operation]->GetpBadge()->GetSize(0) / 2) <= m_apSelect2D[type]->GetPosition().x + (m_apSelect2D[operation]->GetSize(0) / 2) &&
		m_apCursol[operation]->GetpBadge()->GetPosition().x + (m_apCursol[operation]->GetpBadge()->GetSize(0) / 2) >= m_apSelect2D[type]->GetPosition().x - (m_apSelect2D[operation]->GetSize(0) / 2) &&
		m_apCursol[operation]->GetpBadge()->GetPosition().y + (m_apCursol[operation]->GetpBadge()->GetSize(1) / 2) >= m_apSelect2D[type]->GetPosition().y - (m_apSelect2D[operation]->GetSize(1) / 2) &&
		m_apCursol[operation]->GetpBadge()->GetPosition().y - (m_apCursol[operation]->GetpBadge()->GetSize(1) / 2) <= m_apSelect2D[type]->GetPosition().y + (m_apSelect2D[operation]->GetSize(1) / 2))
	{
		bColl = true;
	}

	return bColl;
}
//=============================================================================
// �e�N�X�`�����W�Ǘ�
//=============================================================================
void CCharaSelect::CharaSelTex(int nNum, SELECT_STATE Sel, CPlayer::PLAYER_TYPE &type)
{
	switch (Sel)
	{/* �I�΂ꂽ���̃e�N�X�`�����W */
	case SELECTSTATE_FLASH:	//�I�΂�Ă���
		m_apScene2D[nNum + 4]->SetTex(D3DXVECTOR2(0.2f + (1.0f / 5)*(int)type, 0.0f + (1.0f / 5)*nNum),
			D3DXVECTOR2(0.4f + (1.0f / 5)*(int)type, 0.2f + (1.0f / 5)*nNum));
		if (type == CPlayer::TYPE_MAX)
		{//�����_���̏ꍇ
			m_apScene2D[nNum + 4]->SetTex(D3DXVECTOR2(0.0f, 0.0f + (1.0f / 5)*nNum),
				D3DXVECTOR2(0.2f, 0.2f + (1.0f / 5)*nNum));
		}
		break;
	case SELECTSTATE_NOSELECT:
		m_apScene2D[nNum + 4]->SetTex(D3DXVECTOR2(0.0f, 0.0f + (1.0f / 5)*nNum),
			D3DXVECTOR2(0.2f, 0.2f + (1.0f / 5)*nNum));
		break;
	}

}
//=============================================================================
// �v���C���[���S���I���������m�F����
//=============================================================================
bool CCharaSelect::ConfirmationSelect(void)
{
	bool bCnfirmation = false;
	int nCount = 0;
	for (int nCnt = 0; nCnt < (int)*m_PlayerNum; nCnt++)
	{
		if (m_apCursol[nCnt]->GetSelMove() == true)
		{
			nCount++;
		}
	}

	if (nCount == (int)*m_PlayerNum)
	{
		bCnfirmation = true;

	}
	return bCnfirmation;
}
//=============================================================================
// �����蔻��
//=============================================================================
bool CCharaSelect::collisionConf(int operation)
{
	bool bColl = false;

	/* �����蔻�� */
	if (m_apCursol[operation]->GetpCursor()->GetPosition().x - (m_apCursol[operation]->GetpCursor()->GetSize(0) / 2) <= m_apConfirm2D->GetPosition().x + m_apConfirm2D->GetSize(0) &&
		m_apCursol[operation]->GetpCursor()->GetPosition().x + (m_apCursol[operation]->GetpCursor()->GetSize(0) / 2) >= m_apConfirm2D->GetPosition().x - m_apConfirm2D->GetSize(0) &&
		m_apCursol[operation]->GetpCursor()->GetPosition().y + (m_apCursol[operation]->GetpCursor()->GetSize(1) / 2) >= m_apConfirm2D->GetPosition().y - m_apConfirm2D->GetSize(1) &&
		m_apCursol[operation]->GetpCursor()->GetPosition().y - (m_apCursol[operation]->GetpCursor()->GetSize(1) / 2) <= m_apConfirm2D->GetPosition().y + m_apConfirm2D->GetSize(1))
	{
		bColl = true;
	}

	return bColl;
}
//=============================================================================
// �m��|���̉��o
//=============================================================================
bool CCharaSelect::ProductionConf(void)
{
	bool bFinish = false;
	D3DXVECTOR3 pos= m_apConfirm2D->GetPosition();
	switch (m_CnfProState)
	{
	case CONFPRODUCTION_NONE:

		break;

	case CONFPRODUCTION_MOVE_START:

		m_apConfirm2D->SetPosition(D3DXVECTOR3(0.0f- DEFAULT_SIZE*5.1f, SCREEN_HEIGHT / 2, 0.0f));
		m_apConfirm2D->SetbDraw(true);
		m_moveConfPro = 100.0f;
		m_CnfProState = CONFPRODUCTION_MOVE;
		break;

	case CONFPRODUCTION_MOVE:

		pos.x += m_moveConfPro;
		if (m_apConfirm2D->GetPosition().x >= SCREEN_WIDTH/2 - 50.0f)
		{
			m_CnfProState = CONFPRODUCTION_MOVE_END;
			m_moveConfPro = 0.0f;
		}
		else
		{
			m_apConfirm2D->SetPosition(pos);
		}
		break;

	case CONFPRODUCTION_MOVE_END:


		m_apConfirm2D->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		if (m_fFlashAlpha[0] <= 0.0f&&m_fFlashAlpha[1] <= 0.0f&&m_fFlashAlpha[2] <= 0.0f&&m_fFlashAlpha[3] <= 0.0f)
		{
			m_CnfProState = CONFPRODUCTION_NONE;
			bFinish = true;
		}
		break;
	}
	return bFinish;
}
//=============================================================================
// �m��|���̓_�ŏ���
//=============================================================================
void CCharaSelect::FlashConf(void)
{
	CSound *pSound = CManager::GetSound();		//	���̎擾
	m_CntFlash++;
	if (m_CntFlash >= 3)
	{
		m_apConfirm2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
		m_CntFlash = 0;
	}
	else
	{
		m_apConfirm2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	}
	pSound->SetVolume(CSound::SOUND_LABEL_AREYOUREADY, 4.5f);
	pSound->PlaySound(CSound::SOUND_LABEL_AREYOUREADY);
}
//=============================================================================
// �L�����I���J�[�h�̉��o����
//=============================================================================
void CCharaSelect::ProductionCard(void)
{
	D3DXVECTOR3 pos = DEFAULT_POS;
	bool bFinish[MAX_CHARASELECT] = { false };
	switch (m_CharaCardProduction)
	{
	case CHARACARDPRO_NONE:			//�������Ȃ�
		break;

	case CHARACARDPRO_START:		//�J�n
		for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
		{
			m_apSelect2D[nCnt]->SetPosition(D3DXVECTOR3(-1.0f, m_CharaCardPro_FinishPos[nCnt].y, DEFAULT_POS.z));
			m_apSelect2D[nCnt]->SetWidthHeight(m_fCharaCardPro_FinishWH[0], m_fCharaCardPro_FinishWH[1]);
		}
		m_CharaCardProduction = CHARACARDPRO_MOVE;
		break;

	case CHARACARDPRO_MOVE:			//�ړ�
		for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
		{
			pos = m_apSelect2D[nCnt]->GetPosition();
			if (pos.x >= m_CharaCardPro_FinishPos[nCnt].x)
			{
				m_apSelect2D[nCnt]->SetPosition(m_CharaCardPro_FinishPos[nCnt]);
			}
			else
			{
				pos.x += 10.0f + nCnt;
				m_apSelect2D[nCnt]->SetPosition(pos);
			}
			m_apSelect2D[nCnt]->SetWidthHeight(m_fCharaCardPro_FinishWH[0], m_fCharaCardPro_FinishWH[1]);
		}
		if (m_apSelect2D[4]->GetPosition().x == m_CharaCardPro_FinishPos[4].x)
		{
			m_CharaCardProduction = CHARACARDPRO_TURNOVER_B;
		}
		break;

	case CHARACARDPRO_TURNOVER_B:	//���Ԃ�

		for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
		{
			m_fCardWidth[nCnt][0] -= 10.0f;
			m_apSelect2D[nCnt]->SetWidthHeight(m_fCardWidth[nCnt][0], m_fCharaCardPro_FinishWH[1]);
			if (m_fCardWidth[nCnt][0] <= 0.0f)
			{
				m_apSelect2D[nCnt]->BindTexture("CHARACTORSEL_CHARA");
				m_apSelect2D[nCnt]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MAX_CHARASELECT)*nCnt),0.0f),
					D3DXVECTOR2((1.0f / MAX_CHARASELECT) + ((1.0f / MAX_CHARASELECT)*nCnt),0.5f));
				m_CharaCardProduction = CHARACARDPRO_FACEUP;
			}
		}
		break;

	case CHARACARDPRO_FACEUP:		//�\�ʂɂȂ�
		for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
		{
			m_fCardWidth[nCnt][0] += 10.0f;
			m_apSelect2D[nCnt]->SetWidthHeight(m_fCardWidth[nCnt][0], m_fCharaCardPro_FinishWH[1]);
			if (m_fCardWidth[nCnt][0] >= m_fCharaCardPro_FinishWH[0])
			{
				m_apSelect2D[nCnt]->SetWidthHeight(m_fCharaCardPro_FinishWH[0], m_fCharaCardPro_FinishWH[1]);
				bFinish[nCnt] = true;
			}
		}
		if (bFinish[0] == true&& bFinish[1] == true&& bFinish[2] == true&& bFinish[3] == true&& bFinish[4] == true)
		{
			m_CharaCardProduction = CHARACARDPRO_FINISH;
		}
		break;

	case CHARACARDPRO_FINISH:		//�I��
		m_bCharaCard = true;
		m_CharaCardProduction = CHARACARDPRO_NONE;
		break;
	}
}
//=============================================================================
// ���[�h�߂�|���S���Ƃ̂����蔻��
//=============================================================================
bool CCharaSelect::collisionBackMode(int operation)
{
	bool bColl = false;

	/* �����蔻�� */
	if (m_apCursol[operation]->GetpCursor()->GetPosition().x - (m_apCursol[operation]->GetpCursor()->GetSize(0) / 2) <= m_apScene2D[3]->GetPosition().x + m_apScene2D[3]->GetSize(0) &&
		m_apCursol[operation]->GetpCursor()->GetPosition().x + (m_apCursol[operation]->GetpCursor()->GetSize(0) / 2) >= m_apScene2D[3]->GetPosition().x - m_apScene2D[3]->GetSize(0) &&
		m_apCursol[operation]->GetpCursor()->GetPosition().y + (m_apCursol[operation]->GetpCursor()->GetSize(1) / 2) >= m_apScene2D[3]->GetPosition().y - m_apScene2D[3]->GetSize(1) &&
		m_apCursol[operation]->GetpCursor()->GetPosition().y - (m_apCursol[operation]->GetpCursor()->GetSize(1) / 2) <= m_apScene2D[3]->GetPosition().y + m_apScene2D[3]->GetSize(1))
	{
		bColl = true;
	}

	return bColl;
}
//=============================================================================
// �m�菈��
//=============================================================================
void CCharaSelect::DecisionCharactor(CFade *pFade, CManager *pManager, int operation)
{
	CSound *pSound = CManager::GetSound();		//	���̎擾
	if (collisionConf(operation) == true)
	{//�|���S���͈͓̔�
		if (CCommand::GetCommand("DECISION", operation) == true)
		{
			m_bCnfFlash = true;
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT04);

			for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
			{//�����_����I�������l������
				m_CharaType[nCnt] = m_apCursol[nCnt]->GetPlayerType();
				if (m_CharaType[nCnt] == CPlayer::TYPE_RANDOM)
				{//�����_���������ꍇ
					m_CharaType[nCnt] = (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM);
				}
			}
			for (int nCnt = 0; nCnt < *m_PlayerNum; nCnt++)
			{//�v���C���[�l�����L�����̎�ނ�n��
				CGame::SetCharaSelect(nCnt, m_CharaType[nCnt]);
			}

			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				pFade->SetFade(pManager->MODE_STAGESELECT, pFade->FADE_OUT);
			}
		}
	}
}
//=============================================================================
// �߂�|���S���̃e�N�X�`�����W�ݒ�
//=============================================================================
void CCharaSelect::SetBackModeTex(void)
{
	if (m_bBackModeColl[0] == true|| m_bBackModeColl[1] == true|| m_bBackModeColl[2] == true|| m_bBackModeColl[3] == true)
	{
		m_apScene2D[3]->SetTex(D3DXVECTOR2(0.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	}
	else
	{
		m_apScene2D[3]->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 0.5f));
	}
}
//=============================================================================
// �v���C���[�E�B���h�E�̕\��
//=============================================================================
void CCharaSelect::SetWindowCharaDraw(int nNum, bool bDraw)
{ m_apScene2D[nNum + 12]->SetbDraw(bDraw); }

//=============================================================================
// �v���C���[�E�B���h�E�ɕ\������L�����N�^�[�̐ݒ�
//=============================================================================
void CCharaSelect::SetPlayerWindowChara(int operation, CPlayer::PLAYER_TYPE type)
{
	if (m_apScene2D[operation + 12]->GetbDraw() == true)
	{
		m_apScene2D[operation + 12]->SetTex(D3DXVECTOR2(0.0f + (1.0f / MAX_CHARASELECT)*(int)type,0.5f),
			D3DXVECTOR2((1.0f / MAX_CHARASELECT) + (1.0f / MAX_CHARASELECT)*(int)type,1.0f));
	}
}