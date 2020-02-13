//=============================================================================
//
// �����ۊǂ�UI���� [tube.h]
// Author : �ڍ� ������
//
//=============================================================================
#include "tube.h"
#include "manager.h"
#include "debugProc.h"
#include "input.h"
#include "scene2D.h"
#include "scene2D.h"
#include "game.h"
#include "PlayerNumSelect.h"
#include "point.h"
#include "tutorial.h"
//=============================================================================
// �}�N���֐�
//=============================================================================
#define WORD_POS		(CScene2D::GetPosition())			// �����̈ʒu
#define POS_ONE_001		(D3DXVECTOR3(WORD_POS.x - 122.0f, WORD_POS.y - 71.0f, 0.0f))		// �ŏ��̈ʒu
#define POS_TOW_001		(D3DXVECTOR3(WORD_POS.x - 53.0f, WORD_POS.y - 55.0f, 0.0f))		// ��ڂ̈ʒu
#define POS_THREE_001	(D3DXVECTOR3(WORD_POS.x - 10.0f, WORD_POS.y + 21.0f, 0.0f))		// �O�ڂ̈ʒu

#define POS_ONE_002		(D3DXVECTOR3(WORD_POS.x - 82.0f, WORD_POS.y - 49.5f, 0.0f))		// �ŏ��̈ʒu
#define POS_TOW_002		(D3DXVECTOR3(WORD_POS.x - 35.0f, WORD_POS.y - 38.0f, 0.0f))		// ��ڂ̈ʒu
#define POS_THREE_002	(D3DXVECTOR3(WORD_POS.x - 7.0f, WORD_POS.y + 15.0f, 0.0f))		// �O�ڂ̈ʒu

#define SIZE_000		(D3DXVECTOR2(43.0f, 57.0f))
#define SIZE_001		(D3DXVECTOR2(28.0f, 40.0f))

#define POS_ANSWER_001	(D3DXVECTOR3(WORD_POS.x - 93.0f, WORD_POS.y + 45.0f, 0.0f))		// �����̈ʒu
#define POS_ANSWER_STOCK_001	(D3DXVECTOR3(WORD_POS.x + 53.0f, WORD_POS.y + 72.0f, 0.0f))		// �����̈ʒu
#define SIZE_ANSWER_001	(D3DXVECTOR2(60.0f, 70.0f))										// �����̈ʒu
#define SIZE_ANSWER_STOCK_001	(D3DXVECTOR2(60.0f / 2, 70.0f / 2))										// �����̈ʒu


#define POS_ANSWER_002	(D3DXVECTOR3(WORD_POS.x - 62.0f, WORD_POS.y + 32.0f, 0.0f))		// �����̈ʒu
#define POS_ANSWER_STOCK_002	(D3DXVECTOR3(WORD_POS.x + 35.0f, WORD_POS.y + 51.0f, 0.0f))		// �O�ڂ̈ʒu
#define SIZE_ANSWER_002	(D3DXVECTOR2(38.0f, 50.0f))										// �����̈ʒu
#define SIZE_ANSWER_STOCK_002	(D3DXVECTOR2(38.0f / 2, 48.0f / 2))										// �����̈ʒu

#define WHILE_1P		(70.0f)															// �X�g�b�N2�ڂƂ̊�
#define WHILE_2P		(47.0f)															// �X�g�b�N2�ڂƂ̊�

#define MOVE			(3.0f)
#define AREA			(2.0f * 2.0f)
#define AREA_STAR		(5.0f * 5.0f)

#define WORD_SCALE		(0.5f)															// �������k�ޑ��x
#define STAR_POS		(D3DXVECTOR3(640.0f, 300.0f, 0.0f))
#define UNINIT_TIME		(15 * 60)															// �����擾��I������܂ł̃t���[��
#define FLASHING_TIME	(8 * 60)															// �����擾��I������܂ł̃t���[��
#define FLASHING_TIME_SECOND	(12 * 60)															// �����擾��I������܂ł̃t���[��
//=============================================================================
// �V�[���N���X�̃R���X�g���N�^
//=============================================================================
CTube::CTube(int nPriority, OBJTYPE objType) : CScene2D(nPriority, objType)
{
	// �l���N���A
	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		m_apWord[nCntWord] = NULL;
		m_pAnswerModel[nCntWord] = NULL;
		m_pShootingStar[nCntWord] = NULL;
		m_anAnswerNum[nCntWord] = 0;
	}

	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_sizeAnswer = D3DXVECTOR2(0.0f, 0.0f);
	m_nAnswer = 0;
	m_nStockNum = 0;
	m_nAnswerModelNum = 0;
	m_nCntUninit = 0;
	m_bModelTexFlag = false;
	m_bCreateFlag = false;
	m_bTowardFlag = false;
}

//=============================================================================
// �I�u�W�F�N�g�̐�������
//=============================================================================
CTube *CTube::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,LPCSTR Tag,int nPriority)
{
	CTube *pTube = NULL;

	if (pTube == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pTube = new CTube(nPriority, OBJTYPE_SCENE2D);

		if (pTube != NULL)
		{
			pTube->Init(pos);
			pTube->SetWidthHeight(size.x, size.y);	// �T�C�Y�ݒ�
			pTube->BindTexture(Tag);
		}
	}

	return pTube;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTube::~CTube()
{
}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CTube::Init(D3DXVECTOR3 pos)
{
	CScene2D::Init(pos);

	CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();

	if (NumPlayer == 1) { m_AnswerPos = POS_ANSWER_001; m_size = SIZE_000; }
	else if (NumPlayer != 1) { m_AnswerPos = POS_ANSWER_002; m_size = SIZE_001; }

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CTube::Uninit(void)
{
	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		if (m_apWord[nCntWord] != NULL)
		{
			m_apWord[nCntWord]->Uninit();
			m_apWord[nCntWord] = NULL;
		}
	}

	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		if (m_pAnswerModel[nCntWord] != NULL) { m_pAnswerModel[nCntWord]->Uninit(); m_pAnswerModel[nCntWord] = NULL; }
	}

	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		if (m_pShootingStar[nCntWord] != NULL) { m_pShootingStar[nCntWord]->Uninit(); m_pShootingStar[nCntWord] = NULL; }
	}
	CScene2D::Uninit();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CTube::Update(void)
{
	if (m_bModelTexFlag == true) { Collect(); }		// ���S�_�ɏW�܂�

	Toward();

	WordCreate2D();

	if (m_bSizeFlag == true)
	{	// �T�C�Y�ύX
		if (m_pAnswerModel[m_nStockNum] != NULL)
		{
			D3DXVECTOR2 size = D3DXVECTOR2(m_pAnswerModel[m_nStockNum]->GetSize(0), m_pAnswerModel[m_nStockNum]->GetSize(1));
			SizeChange(size);
		}
	}

	CScene2D::Update();
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CTube::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �����̔ԍ��ݒ�̏���
//=============================================================================
void CTube::SetWordNum(int nWordNum, int nNum, int nStock)
{
	D3DXVECTOR3 pos = {};
	D3DXVECTOR2 size = {};
	D3DXVECTOR3 StockPos = {};
	D3DXVECTOR2 StockSize = {};
	D3DXVECTOR3 ToWardPos = {};
	float fWhile = 0.0f;
	//m_anAnswerNum[nNum] = nWordNum;

	CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();

	if (m_bCreateFlag == true)
	{
		UninitChack(true);		// �I�����Ă��邩�ǂ����̊m�F
	}

	if (NumPlayer == 1)
	{	// 1�l�v���C�̏ꍇ
		if (nNum == 0) { pos = POS_ONE_001; }
		else if (nNum == 1) { pos = POS_TOW_001; }
		else if (nNum == 2) { pos = POS_THREE_001; }
		ToWardPos = STAR_POS;
		if (nNum == 2)
		{
			m_sizeAnswer = SIZE_ANSWER_STOCK_001;
		}
	}
	else if (NumPlayer != 1)
	{ // 1�l�v���C����Ȃ��ꍇ
		if (nNum == 0) { pos = POS_ONE_002; }
		else if (nNum == 1) { pos = POS_TOW_002; }
		else if (nNum == 2) { pos = POS_THREE_002; }

		if (nNum == 2)
		{
			m_sizeAnswer = SIZE_ANSWER_STOCK_002;
		}
	}

	if(NumPlayer == 2)
	{
		if (m_nID == 0) { ToWardPos = D3DXVECTOR3(640.0f, 150.0f, 0.0f); }
		else if (m_nID == 1) { ToWardPos = D3DXVECTOR3(640.0f, 550.0f, 0.0f); }
	}
	else if (NumPlayer == 3 || NumPlayer == 4)
	{
		if (m_nID == 0) { ToWardPos = D3DXVECTOR3(340.0f, 150.0f, 0.0f); }
		if (m_nID == 1) { ToWardPos = D3DXVECTOR3(940.0f, 150.0f, 0.0f); }
		if (m_nID == 2) { ToWardPos = D3DXVECTOR3(340.0f, 550.0f, 0.0f); }
		if (m_nID == 3) { ToWardPos = D3DXVECTOR3(940.0f, 550.0f, 0.0f); }
	}



	if (m_apWord[nNum] == NULL)
	{
		m_apWord[nNum] = CScene2D::Create(pos, "WORD", 3);
		m_apWord[nNum]->SetWidthHeight(0.0f, 0.0f);	// �T�C�Y�ݒ�
		m_apWord[nNum]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apWord[nNum]->SetTex(D3DXVECTOR2(0.0f + ((nWordNum / 5) * 0.1f), 0.0f + ((nWordNum % 5) * 0.2f)), D3DXVECTOR2(0.1f + ((nWordNum / 5) * 0.1f), 0.2f + ((nWordNum % 5) * 0.2f)));
	}

	if (m_pShootingStar[nNum] == NULL)
	{
		m_pShootingStar[nNum] = CScene2D::Create(ToWardPos, "WORD", 3);
		m_pShootingStar[nNum]->SetWidthHeight(0.0f, 0.0f);	// �T�C�Y�ݒ�
		m_pShootingStar[nNum]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pShootingStar[nNum]->SetTex(D3DXVECTOR2(0.0f + ((nWordNum / 5) * 0.1f), 0.0f + ((nWordNum % 5) * 0.2f)), D3DXVECTOR2(0.1f + ((nWordNum / 5) * 0.1f), 0.2f + ((nWordNum % 5) * 0.2f)));
	}

	if (nNum == 2)
	{
		for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
		{
			if (m_apWord[nCntWord] != NULL)
			{
				 m_apWord[nCntWord]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}

		m_bCreateFlag = true;
		//m_bModelTexFlag = true;
	}
}

//=============================================================================
// �����̔ԍ��ݒ�̏���
//=============================================================================
void CTube::SetAnswer(int nAnswer, int nStock)
{
	CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();
	D3DXVECTOR3 StockPos = {};
	float fWhile = 0.0f;
	m_nAnswerModelNum = nAnswer;

	if (NumPlayer == 1)
	{	// 1�l�v���C�̏ꍇ
		StockPos = POS_ANSWER_STOCK_001;
		fWhile = WHILE_1P;
	}
	else if (NumPlayer != 1)
	{ // 1�l�v���C����Ȃ��ꍇ
		StockPos = POS_ANSWER_STOCK_002;
		fWhile = WHILE_2P;
	}

	if (m_pAnswerModel[nStock] == NULL)
	{	// ������3�����W�܂����ꍇ�ꍇ
		D3DXVECTOR2 AnswerSize = {};
		//int nAnswerNum =
		if (NumPlayer == 1)
		{	// 1�l�v���C�̏ꍇ
			m_AnswerPos = POS_ANSWER_001;
			if (nStock == 0)
			{
				m_sizeAnswer = SIZE_ANSWER_001;
			}
		}
		else if (NumPlayer != 1)
		{	// 1�l�v���C����Ȃ��ꍇ
			m_AnswerPos = POS_ANSWER_002;
			if (nStock == 0)
			{
				m_sizeAnswer = SIZE_ANSWER_002;
			}
		}

		if (NOT_NUM == m_nAnswerModelNum)
		{	// �S�~���f����tex���o��
			m_pAnswerModel[nStock] = CScene2D::Create(m_AnswerPos, "�S�~_���f��", 3);
			m_pAnswerModel[nStock]->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
		}
		else if (NOT_NUM != m_nAnswerModelNum)
		{	// �����̃��f�����o��
			m_pAnswerModel[nStock] = CScene2D::Create(m_AnswerPos, "���f��_TEX", 3);
			m_pAnswerModel[nStock]->SetTex(D3DXVECTOR2(0.0f + ((m_nAnswerModelNum / 10) * (1.0f / 12.0f)), 0.0f + ((m_nAnswerModelNum % 10) * 0.1f)),
						D3DXVECTOR2((1.0f / 12.0f) + ((m_nAnswerModelNum / 10) * (1.0f / 12.0f)), 0.1f + ((m_nAnswerModelNum % 10) * 0.1f)));
		}
		//	�����ō��郂�f�����܂Ƃ߂��摜�ɕς���
		m_pAnswerModel[nStock]->SetWidthHeight(0.0f, 0.0f);	// �T�C�Y�ݒ�
		m_pAnswerModel[nStock]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}

	if (m_pAnswerModel[nStock] != NULL)
	{
		if (nStock == 1 || nStock == 2)
		{
			m_pAnswerModel[nStock]->SetWidthHeight(0.0f, 0.0f);
			if (nStock == 1) { m_pAnswerModel[nStock]->SetPosition(StockPos); }
			else if (nStock == 2) { m_pAnswerModel[nStock]->SetPosition(D3DXVECTOR3(StockPos.x + fWhile, StockPos.y, StockPos.z)); }
		}
	}
}
//=============================================================================
// �S�Ă̕������폜
//=============================================================================
void CTube::AllDelete(int nNum)
{
	for (int nCntWord = nNum; nCntWord < MAX_WORD; nCntWord++)
	{
		if (m_apWord[nCntWord] != NULL)
		{
			m_apWord[nCntWord]->Uninit();
			m_apWord[nCntWord] = NULL;
		}
	}

	int nCount = 0;
	for (int nCntAnswerModel = 0; nCntAnswerModel < MAX_WORD - 1; nCntAnswerModel++)
	{
		if (m_pAnswerModel[nCntAnswerModel] != NULL && m_pAnswerModel[nCntAnswerModel + 1] != NULL)
		{
			m_pAnswerModel[nCntAnswerModel]->BindTexture(m_pAnswerModel[nCntAnswerModel + 1]->GetTexture());
			m_pAnswerModel[nCntAnswerModel]->SetTex(m_pAnswerModel[nCntAnswerModel + 1]->GetTex(0), m_pAnswerModel[nCntAnswerModel + 1]->GetTex(1));
			nCount++;
		}
	}

	if (m_pAnswerModel[nCount] != NULL) { m_pAnswerModel[nCount]->Uninit(); m_pAnswerModel[nCount] = NULL; }
}

//=============================================================================
// ����������ʒu�ɏW�߂�Tex�𐶐�
//=============================================================================
void CTube::Collect(void)
{
	int nCntNum = 0;

	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		if (m_apWord[nCntWord] != NULL)
		{
			if (m_apWord[nCntWord]->GetCol() != D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)) { m_apWord[nCntWord]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); }
			m_apWord[nCntWord]->SetWidthHeight(m_apWord[nCntWord]->GetSize(0) - WORD_SCALE, m_apWord[nCntWord]->GetSize(1) - WORD_SCALE);
			Approach(m_apWord[nCntWord]->GetPosition(), m_AnswerPos, nCntWord);
		}
		else if (m_apWord[nCntNum] == NULL) { nCntNum++; }
	}

	if (nCntNum == MAX_WORD)
	{
		if (m_pAnswerModel[m_nStockNum] != NULL)
		{
			D3DXVECTOR2 size = D3DXVECTOR2(m_pAnswerModel[m_nStockNum]->GetSize(0), m_pAnswerModel[m_nStockNum]->GetSize(1));

			//if (NOT_NUM == m_nAnswerModelNum)
			//{	// �S�~���f����tex���o��
			//	m_pAnswerModel[m_nStockNum]->BindTexture("�S�~_���f��");
			//	m_pAnswerModel[m_nStockNum]->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
			//}
			//else if (NOT_NUM != m_nAnswerModelNum)
			//{	// �����̃��f�����o��
			//	m_pAnswerModel[m_nStockNum]->BindTexture("���f��_TEX");
			//	m_pAnswerModel[m_nStockNum]->SetTex(D3DXVECTOR2(0.0f + ((m_nAnswerModelNum / 10) * 0.125f), 0.0f + ((m_nAnswerModelNum % 10) * 0.1f)),
			//		D3DXVECTOR2(0.125f + ((m_nAnswerModelNum / 10) * 0.125f), 0.1f + ((m_nAnswerModelNum % 10) * 0.1f)));
			//}

			for (int nCntModel = 0; nCntModel < MAX_WORD; nCntModel++)
			{
				if (m_pAnswerModel[nCntModel] != NULL)
				{
					m_pAnswerModel[nCntModel]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
			}

			SizeChange(size);	// �T�C�Y�̕ω�
		}
	}

	m_nCntUninit = 0;
}

//=============================================================================
// �v���C���[�ɏW�܂�̏���
//=============================================================================
void CTube::Approach(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, int nNum)
{
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �v���C���[�ɋ߂Â���
	move.x = sinf(atan2f(OtherPos.x - Pos.x, OtherPos.y - Pos.y)) * MOVE;
	move.y = cosf(atan2f(OtherPos.x - Pos.x, OtherPos.y - Pos.y)) * MOVE;

	if (m_apWord[nNum] != NULL)
	{
		Pos.x += move.x;
		Pos.y += move.y;

		// �͈͂𑪂�
		float fDistance = sqrtf((Pos.x - OtherPos.x)* (Pos.x - OtherPos.x) + (Pos.z - OtherPos.z)*(Pos.z - OtherPos.z));

		m_apWord[nNum]->SetPosition(Pos);

		// �͈͓��Ȃ�j�� Flag��߂�
		if (fDistance < AREA)
		{	// �������ɓ�������
			if (m_apWord[nNum] != NULL)
			{
				m_apWord[nNum]->Uninit();
				m_apWord[nNum] = NULL;
			}
		}

	}
}

//=============================================================================
// �|�C���g�̏���
//=============================================================================
void CTube::SetPoint(int nPoint, int nNum, bool bPoint)
{
	CSound *pSound = CManager::GetSound();		//	���̎擾
	CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();


	CPoint *pPoint = NULL;
	if (CManager::GetMode() == CManager::MODE_GAME) { pPoint = CGame::GetPoint(nNum); }
	else if (CManager::GetMode() == CManager::MODE_TUTORIAL) { /* �`���[�g���A���̍�Ƃɂ�肩�������ꍇ �����Ń`���[�g���A������|�C���g���擾 */ }

	//m_bSizeFlag = false;	// �T�C�Y�ύX�̃t���O��false��

	if (pPoint != NULL)
	{
		if (bPoint == false) { pPoint->AddPoint(nPoint);
		pSound->SetVolume(CSound::SOUND_LABEL_SE_POINTUP, 3.0f);
		pSound->PlaySound(CSound::SOUND_LABEL_SE_POINTUP);
		}
		else if (bPoint == true) { pPoint->SubtractionPoint(nPoint);
		pSound->SetVolume(CSound::SOUND_LABEL_SE_POINTDOWN, 3.0f);
		pSound->PlaySound(CSound::SOUND_LABEL_SE_POINTDOWN);
		}
	}
}

//=============================================================================
// �I�����Ă邩�ǂ����̊m�F����
//=============================================================================
void CTube::UninitChack(bool bFlag)
{
	if (bFlag == true)
	{	// �t���O��true�Ȃ當����j��
		m_bSizeFlag = true;
		for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
		{
			if (m_apWord[nCntWord] != NULL)
			{
				m_apWord[nCntWord]->Uninit();
				m_apWord[nCntWord] = NULL;
			}
		}
	}

	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		if (m_pShootingStar[nCntWord] != NULL) { m_pShootingStar[nCntWord]->Uninit(); m_pShootingStar[nCntWord] = NULL; }
	}

	m_bModelTexFlag = false;
	int nCount = 0;

	for (int nCntTex = 0; nCntTex < m_nStockNum; nCntTex++)
	{
		if (m_pAnswerModel[nCntTex] != NULL) { nCount++; }
		else if (m_pAnswerModel[nCntTex] == NULL) { break; }
	}

	if (m_pAnswerModel[nCount] != NULL)
	{
		//if (NOT_NUM == m_nAnswerModelNum)
		//{	// �S�~���f����tex���o��
		//	m_pAnswerModel[nCount]->BindTexture("�S�~_���f��");
		//	m_pAnswerModel[nCount]->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
		//}
		//else if (NOT_NUM != m_nAnswerModelNum)
		//{	// �����̃��f�����o��
		//	m_pAnswerModel[nCount]->BindTexture("���f��_TEX");
		//	m_pAnswerModel[nCount]->SetTex(D3DXVECTOR2(0.0f + ((m_nAnswerModelNum / 10) * 0.125f), 0.0f + ((m_nAnswerModelNum % 10) * 0.1f)),
		//		D3DXVECTOR2(0.125f + ((m_nAnswerModelNum / 10) * 0.125f), 0.1f + ((m_nAnswerModelNum % 10) * 0.1f)));
		//}

		for (int nCntModel = 0; nCntModel < MAX_WORD; nCntModel++)
		{
			if (m_pAnswerModel[nCntModel] != NULL)
			{
				m_pAnswerModel[nCntModel]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}

		//m_pAnswerModel[m_nStockNum]->SetWidthHeight(m_sizeAnswer.x, m_sizeAnswer.y);
	}

	m_nAnswerModelNum = 0;
	m_nCntUninit = 0;
	m_bCreateFlag = false;
}

//=============================================================================
// �ړI�̏ꏊ�Ɍ���������
//=============================================================================
void CTube::Toward(void)
{
	CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();
	float fMove = 0.0f;

	if (NumPlayer == 1) { fMove = 12.0f; }
	else if (NumPlayer != 1) { fMove = 10.0f; }


	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		if (m_apWord[nCntWord] != NULL && m_pShootingStar[nCntWord] != NULL)
		{
			float fDistance = 0.0f;
			float fRot = m_pShootingStar[nCntWord]->GetRot();
			D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 pos = m_pShootingStar[nCntWord]->GetPosition();
			D3DXVECTOR2 size = D3DXVECTOR2(m_pShootingStar[nCntWord]->GetSize(0), m_pShootingStar[nCntWord]->GetSize(1));

			// �ړ���������
			pos.y -= 3.0f;

			// �������Z
			//fRot += 0.1f;

			// �ړI�n�Ǝ��g�̈ʒu�𑪂�
			move.x = sinf(atan2f(m_apWord[nCntWord]->GetPosition().x - m_pShootingStar[nCntWord]->GetPosition().x, m_apWord[nCntWord]->GetPosition().y - m_pShootingStar[nCntWord]->GetPosition().y)) * fMove;
			move.y = cosf(atan2f(m_apWord[nCntWord]->GetPosition().x - m_pShootingStar[nCntWord]->GetPosition().x, m_apWord[nCntWord]->GetPosition().y - m_pShootingStar[nCntWord]->GetPosition().y)) * fMove;

			pos += move;

			// �T�C�Y����
			size.x += 1.0f;
			size.y += 1.0f;

			// �ʒu�ƃT�C�Y, �����ݒ�
			m_pShootingStar[nCntWord]->SetPosition(pos);
			m_pShootingStar[nCntWord]->SetWidthHeight(size.x, size.y);
			//m_pShootingStar[nCntWord]->SetRot(fRot);

			// �ړI�n�͈̔͂ɓ�������폜
			fDistance = sqrtf((m_pShootingStar[nCntWord]->GetPosition().x - m_apWord[nCntWord]->GetPosition().x)* (m_pShootingStar[nCntWord]->GetPosition().x - m_apWord[nCntWord]->GetPosition().x) +
				(m_pShootingStar[nCntWord]->GetPosition().z - m_apWord[nCntWord]->GetPosition().z)*(m_pShootingStar[nCntWord]->GetPosition().z - m_apWord[nCntWord]->GetPosition().z));


			// �͈͓��ɂ͂�������폜
			if (fDistance < AREA_STAR)
			{
				if (m_pShootingStar[nCntWord] != NULL) { m_pShootingStar[nCntWord]->Uninit(); m_pShootingStar[nCntWord] = NULL; }
			}
		}
	}
}

//=============================================================================
// �����̕\��2D����
//=============================================================================
void CTube::WordCreate2D(void)
{
	int nCount = 0;
	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		if (m_apWord[nCntWord] != NULL && m_pShootingStar[nCntWord] == NULL)
		{
			D3DXVECTOR2 size = D3DXVECTOR2(m_apWord[nCntWord]->GetSize(0), m_apWord[nCntWord]->GetSize(1));
			// �T�C�Y���g��
			size.x += 2.14f;
			size.y += 2.38f;

			// �w�肵���T�C�Y�ȏ�̏ꍇ
			if (size.x > m_size.x ) { size.x = m_size.x; }
			if (size.y > m_size.y) { size.y = m_size.y; }

			if (size.x >= m_size.x && size.y >= m_size.y)
			{
				nCount++;
			}

			m_apWord[nCntWord]->SetWidthHeight(size.x, size.y);
		}
	}

	if (nCount == MAX_WORD) { m_bModelTexFlag = true; }		// ���S�_�ɏW�܂�
	else if (nCount == MAX_WORD - 1) { WordUninit(); }
}

//=============================================================================
// �T�C�Y�ω��̏���
//=============================================================================
void CTube::SizeChange(D3DXVECTOR2 size)
{
	// �T�C�Y���g��
	size.x += 2.14f;
	size.y += 2.38f;

	// �w�肵���T�C�Y�ȏ�̏ꍇ
	if (size.x > m_sizeAnswer.x) { size.x = m_sizeAnswer.x; }
	if (size.y > m_sizeAnswer.y) { size.y = m_sizeAnswer.y; }

	if (size.x >= m_sizeAnswer.x && size.y >= m_sizeAnswer.y)
	{
		m_bModelTexFlag = false;
		m_bCreateFlag = false;
		m_bSizeFlag = false;

		m_nAnswerModelNum = 0;
	}

	if (m_pAnswerModel[m_nStockNum] != NULL)
	{
		m_pAnswerModel[m_nStockNum]->SetWidthHeight(size.x, size.y);
	}
}

//=============================================================================
// �����擾��A�I������܂ł̎���
//=============================================================================
void CTube::WordUninit(void)
{
	// �J�E���g����
	m_nCntUninit++;

	// �J�E���g���w�肵���l�ȏ�̏ꍇ
	if (m_nCntUninit > FLASHING_TIME && m_nCntUninit < FLASHING_TIME_SECOND)
	{	// �_�ŏ���
		for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
		{
			if (m_apWord[nCntWord] != NULL)
			{
				D3DXCOLOR fCol = m_apWord[nCntWord]->GetCol();

				if (fCol.a > 0.3f) { fCol.a -= 0.05f; }
				else { fCol.a = 1.0f; }
				m_apWord[nCntWord]->SetCol(fCol);
			}
		}
	}
	else if (m_nCntUninit >= FLASHING_TIME_SECOND && m_nCntUninit < UNINIT_TIME)
	{	// �_�ŏ���
		for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
		{
			if (m_apWord[nCntWord] != NULL)
			{
				D3DXCOLOR fCol = m_apWord[nCntWord]->GetCol();

				if (fCol.a > 0.3f) { fCol.a -= 0.2f; }
				else { fCol.a = 1.0f; }
				m_apWord[nCntWord]->SetCol(fCol);
			}
		}
	}
	if ((m_nCntUninit % UNINIT_TIME) == 0)
	{	// �����Ă��镶����j������
		for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
		{
			if (m_apWord[nCntWord] != NULL) { m_apWord[nCntWord]->Uninit(); m_apWord[nCntWord] = NULL; }
		}
		m_nCntUninit = 0;

		CManager::GetPlayer(m_nID)->GetWordManager()->WordReset();
	}
}