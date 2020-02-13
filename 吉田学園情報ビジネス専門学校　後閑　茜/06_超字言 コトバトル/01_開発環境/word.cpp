//=============================================================================
//
// �����̃r���{�[�h���� [word.cpp]
// Author : Shun Yokomichi
//
//=============================================================================
#include "word.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "InputKeyboard.h"
#include "PlayerNumSelect.h"
#include "time.h"
#include "tutorial.h"

#include "debugProc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define AREA_CHASE		(35.5f)			// �G���A
#define AREA_COILLSION	(15.0f)			// �R���W�����͈̔�
#define CHASE_MOVE		(5.0f)			// �Ǐ]���̑��x
#define END_POS_Y		(15.0f)			// �����̏o���������̍ŏI�ʒu
#define FLOATING_MOVE	(0.5f)			// ���V���x
#define POP_POS_Y		(END_POS_Y + 10.0f)	// �o����̕��V���̍ő�ʒu
#define POP_POS_Y_SMALL		(END_POS_Y - 5.0f)	// �o����̕��V���̍ŏ��ʒu
#define NOT_NOM_DATA	(5)				// �����������

#define UNITI_TIME		(40)			// �I�����鎞��
#define ��_COL_TIME		(15)			// �����x�ω����̎���
#define ANIM_FRAME		(7)				// �A�j���[�V�����J�E���^�[
#define PATTERN_NUM		(10)			// �p�^�[����
#define COL_DEFAULT		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
#define STAGE_REST_TIME	(60)			// �X�e�[�W�؂�ւ����̕������Z�b�g

//--------------------------------
// �_�Ŋ֌W
//--------------------------------
#define TIME_FRAME		(60)
#define FLASHING_SMALL	(0.05f)			// �_��(������)
#define FLASHING_MAX	(0.2f)			// �_��(�傫��)
#define FLASHING_TIME_SMALL	(TIME_FRAME * 23)		// �_�ł���n�߂鎞��
#define FLASHING_TIME_MAX	(TIME_FRAME * 28)		// �_�ł�����������
#define REST_TIME		(TIME_FRAME * 30)			// �_�Ō�ɏI�����鎞��
#define LOST_TIME		(780)			// ���Ԍo�߂ŏ����鎞��


//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
int CWord::m_nAllNum = 0;
//--------------------------------------------
// �R���X�g���N�^
//--------------------------------------------
CWord::CWord() : CSceneBillBoard()
{
	m_bFlagUninit = false;
	m_bMoveFlag = false;
	m_bScaleFlag = false;
	m_nCntUninit = 0;
	m_bFlag = false;
	m_bPopFlag = false;
	m_bFlashingFlag = false;
	m_bRestFlag = false;
	m_fMoveY = 0.0f;
	m_col = COL_DEFAULT;
	m_pBillBoard[0] = NULL;
	m_pBillBoard[1] = NULL;
	m_nAnim = 0;
	m_nPatten = 0;
	m_colA = 0.4f;
	m_nCntFlashing = 0;
	m_nLostCut = 0;
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);		// �T�C�Y
	m_SelectNumSize = D3DXVECTOR2(0.0f, 0.0f);
	m_nLostType = 0;

	// 3������⎞�̕ϐ�
	m_bSearchFlag = false;
	m_nCntSearch = 0;

	for (int nCntPlayerID = 0; nCntPlayerID < MAX_PLAYER; nCntPlayerID++)
	{
		m_nPlayerID[nCntPlayerID] = NOT_NOM_DATA;
	}
}

//--------------------------------------------
// �f�X�g���N�^
//--------------------------------------------
CWord::~CWord()
{
}

//--------------------------------------------
// ����
//--------------------------------------------
CWord *CWord::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, LPCSTR Tag, int nWord, int LostType,int nNum)
{
	CWord *pWord = NULL;

	if (pWord == NULL)
	{
		pWord = new CWord;

		if (pWord != NULL)
		{
			pWord->m_nLostType = LostType;
			pWord->Init(pos);
			pWord->BindTexture(Tag);
			//�l�̑��
			pWord->SetBillboard(pos, fHeight, fWidth);
			pWord->m_size = D3DXVECTOR3(fHeight, fWidth, 0.0f);
			pWord->m_sizeOld = D3DXVECTOR3(fHeight, fWidth, 0.0f);
			pWord->m_nWordNum = nWord;
			pWord->SetTexture(nWord, 10, 5, 1);
			pWord->m_nNum = nNum;
			pWord->m_move = move;
			m_nAllNum++;
		}
	}

	return pWord;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CWord::Init(D3DXVECTOR3 pos)
{
	CSceneBillBoard::Init(pos);
	CSceneBillBoard::SetObjType(CScene::OBJTYPE_WORD);

	if (m_pBillBoard[0] == NULL)
	{
		m_pBillBoard[0] = CSceneBillBoard::Create(D3DXVECTOR3(pos.x, 0.0f, pos.z), 17.0f, 80.0f, "�����G�t�F�N�g");
		if (m_pBillBoard[0] != NULL) { m_pBillBoard[0]->SetTexture(5, 10, 1, 1); }
		m_pBillBoard[0]->SetObjType(CScene::OBJTYPE_WORD_EFFECT);
	}

	if (m_nLostType == 1)
	{//	���Ԍo�߂ŏ����镶��
		if (m_pBillBoard[1] == NULL)
		{
			m_pBillBoard[1] = CSceneBillBoard::Create(D3DXVECTOR3(pos.x, 0.0f, pos.z), 17.0f, 120.0f, "�����G�t�F�N�g");
			if (m_pBillBoard[1] != NULL) { m_pBillBoard[1]->SetTexture(5, 10, 1, 1); }
			m_pBillBoard[1]->SetObjType(CScene::OBJTYPE_WORD_EFFECT);
		}

	}

	int nNum = *CPlayerSelect::GetModeSelectMode();

	if (nNum == CPlayerSelect::SELECTPLAYER_1P || nNum == CPlayerSelect::SELECTPLAYER_2P) { m_SelectNumSize = MAX_SIZE; }
	if (nNum == CPlayerSelect::SELECTPLAYER_4P || nNum == CPlayerSelect::SELECTPLAYER_3P) { m_SelectNumSize = MAX_SIZE_3or4; }

	m_bFlag = false;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CWord::Uninit(void)
{
	if (m_pBillBoard[0] != NULL) { m_pBillBoard[0]->Uninit(); m_pBillBoard[0] = NULL; }
	if (m_pBillBoard[1] != NULL) { m_pBillBoard[1]->Uninit(); m_pBillBoard[1] = NULL; }
	m_nAllNum--;
	CSceneBillBoard::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CWord::Update(void)
{
	D3DXVECTOR3 pos = CSceneBillBoard::GetPos();	//�ʒu�̎擾
	D3DXVECTOR3 PosOld = pos;						// �ʒu��ۑ�
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// �ړ�

	if (m_bFlag == false) { FlashingCol(); }		// �_�ł̏���
	if (m_bRestFlag == true) { m_bFlagUninit = true; return; }

	if (m_bPopFlag == false)
	{	// �o�����̏ꍇ
		move.y += 1.0f;
		SizeScale(&m_size, 1.0f, m_SelectNumSize);
		if (pos.y >= END_POS_Y) { m_bPopFlag = true; }
	}
	else if (m_bPopFlag == true)
	{
		if (m_bFlagUninit == true) { return; }
		// ���[�J���ϐ�
		CPlayerSelect::SELECTPLAYER NumPlayer = {};
		if (CManager::GetMode() == CManager::MODE_TUTORIAL)
		{
			NumPlayer = *CPlayerSelect::GetModeSelectMode();
		}
		else if (CManager::GetMode() == CManager::MODE_GAME)
		{
			NumPlayer = CPlayerSelect::SELECTPLAYER_4P;//�e�X�g
		}

		CPlayer *pPlayer[MAX_PLAYER] = {};
		D3DXVECTOR3 PlayerPos[MAX_PLAYER];

		if (m_bFlag == false)
		{	// �E�����Ƃ��\�ȕ����̏ꍇ
			for (int nCntPlayer = 0; nCntPlayer < (int)NumPlayer; nCntPlayer++)
			{
				if (CManager::GetMode() == CManager::MODE_GAME)
				{// �v���C���[���擾
					pPlayer[nCntPlayer] = CGame::GetPlayer(nCntPlayer);
				}
				else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
				{
					pPlayer[nCntPlayer] = CTutorial::GetPlayer(nCntPlayer);
				}

				if (pPlayer[nCntPlayer] != NULL)
				{
					PlayerPos[nCntPlayer] = pPlayer[nCntPlayer]->GetPosition();	// �v���C���[�̈ʒu���擾
				}
			}

			for (int nCntPlayer = 0; nCntPlayer < (int)NumPlayer; nCntPlayer++)
			{
				if (pPlayer[nCntPlayer] != NULL)
				{
					if (pPlayer[nCntPlayer]->GetWordManager()->GetCntNum() < 3 && pPlayer[nCntPlayer]->GetWordManager()->GetGatherFlag() == false)
					{

						Distance(pos, PlayerPos[nCntPlayer], nCntPlayer);

						// �����蔻��(�~���g��������)
						Circle(pos, PlayerPos[nCntPlayer], AREA_COILLSION);

						if (m_bFlag == true)
						{	// �I���t���O���������ꍇ
							if (m_pBillBoard[0] != NULL) { m_pBillBoard[0]->Uninit(); m_pBillBoard[0] = NULL; }
							if (m_pBillBoard[1] != NULL) { m_pBillBoard[1]->Uninit(); m_pBillBoard[1] = NULL; }
							pPlayer[nCntPlayer]->GetWordManager()->SetWord(m_nWordNum);
							pPlayer[nCntPlayer]->SetbSetupBullet(true);
							move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
							m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
							m_col = COL_DEFAULT;
							if (m_nLostType == 0)
							{
								m_bFlagUninit = true;
							}
							break;
						}
					}
					else
					{	// 3���������Ȃ�
						Distance(pos, D3DXVECTOR3(9999999990.0f, 0.0f, 9999999990.0f), nCntPlayer);
					}
				}

			}

			if (m_bFlag == false)
			{	// �I���t���O�������Ă���ꍇ
				int nNum = ComparisonDistance((int)NumPlayer);

				// �������v���C���[�ɏW�܂�(�͈͂Ŕ�������)
				move = Approach(pos, PlayerPos[nNum], AREA_CHASE, m_fDistance[nNum]);
			}

			pos = Move(pos);
		}

		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			if (((CTime::GetStageTime() % STAGE_REST_TIME) == 0) && CManager::GetGame()->GetChangeNum() < 2)
			{
				Uninit();
				return;
			}
		}
	}
	if (m_nLostType == 1)
	{//	���Ԍo�߂ŏ����镶��
		if (m_nLostCut > LOST_TIME - 200)
		{
			m_nCntUninit++;	// �J�E���g�̉��Z
			m_size.x += 0.009f;
			m_size.y += 0.009f;
			//	�J���[�̕ύX
			if (m_nCntUninit % 10 == 0) { m_col.a = 0.0f; }
			else { m_col.a = 1.0f; }
		}
		if (pos.y < 15.0f)
		{//	�����G�t�F�N�g�̍폜
			if (m_pBillBoard[1] != NULL) { m_pBillBoard[1]->Uninit(); m_pBillBoard[1] = NULL; }
		}
		else if (pos.y > 25.0f)
		{//	���Ɉړ�������Ƃ��̉���
			move.y -= 1.0f;
		}

	}
	//if (pos.y < 15.0f)
	{
		move += m_move;
	}
	// �ʒu�X�V
	pos.x += move.x;
	pos.y += move.y;
	pos.z += move.z;
	if (m_pBillBoard[0] != NULL)
	{
		m_pBillBoard[0]->Setpos(D3DXVECTOR3(pos.x, 0.0f, pos.z));
	}
	CSceneBillBoard::Update();
	CSceneBillBoard::SetBillboard(pos, m_size.x, m_size.y);
	CSceneBillBoard::SetCol(m_col);
	if (m_nLostType == 1)
	{//	���Ԍo�߂ŏ����镶��
		m_nLostCut++;
		CDebugProc::Print("m_nLostCut : %d", m_nLostCut);

		if (m_move.x > 0.1f || m_move.z > 0.1f || m_move.x < -0.1f || m_move.z < -0.11f)
		{
			if (m_nLostCut > LOST_TIME-320)
			{//	�t���[���ŏ�����
				if (m_pBillBoard[0] != NULL) { m_pBillBoard[0]->Uninit(); m_pBillBoard[0] = NULL; }
				if (m_pBillBoard[1] != NULL) { m_pBillBoard[1]->Uninit(); m_pBillBoard[1] = NULL; }
				Uninit();
			}
		}
		else if (m_move.x == 0.0f || m_move.z == 0.0f || m_move.x == 0.0f || m_move.z == 0.0f)
		{
			if (m_nLostCut > LOST_TIME)
			{//	�t���[���ŏ�����
				if (m_pBillBoard[0] != NULL) { m_pBillBoard[0]->Uninit(); m_pBillBoard[0] = NULL; }
				if (m_pBillBoard[1] != NULL) { m_pBillBoard[1]->Uninit(); m_pBillBoard[1] = NULL; }
				Uninit();
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CWord::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (m_pBillBoard[0] != NULL) { m_pBillBoard[0]->Draw(); }
	if (m_nLostType == 1)
	{//	���Ԍo�߂ŏ����镶��
		if (m_pBillBoard[1] != NULL) { m_pBillBoard[1]->Draw(); }
	}

	CSceneBillBoard::Draw();
}

//=============================================================================
// �ړ�����
//=============================================================================
D3DXVECTOR3 CWord::Move(D3DXVECTOR3 pos)
{
	if (m_bMoveFlag == true)
	{
		pos.y += FLOATING_MOVE;
		m_colA += 0.01f;
		if (m_colA > 1.0f) { m_colA = 1.0f; }
		if (pos.y > POP_POS_Y)
		{	// �ʒu���w�肵���ꏊ���傫���ꍇ
			m_bMoveFlag = false;
			//m_colA = 1.0f;
		}
	}
	else if (m_bMoveFlag == false)
	{
		pos.y -= FLOATING_MOVE;
		m_colA -= 0.01f;
		if (m_colA < 0.38f) { m_colA = 0.38f; }
		if (pos.y < POP_POS_Y_SMALL)
		{	// �ʒu���w�肵���ꏊ��菬�����ꍇ
			m_bMoveFlag = true;
			m_nCntSearch++;
			//m_colA = 0.2f;
		}
	}

	if (m_pBillBoard[0] != NULL)
	{
		m_pBillBoard[0]->SetCol(D3DXCOLOR(m_pBillBoard[0]->GetCol().r, m_pBillBoard[0]->GetCol().g, m_pBillBoard[0]->GetCol().b, m_colA));
	}


	return pos;
}

//=============================================================================
// �g��k���̏���
//=============================================================================
void CWord::SizeScale(D3DXVECTOR3 *size, float fMove, D3DXVECTOR2 MaxSize)
{
	size->x += fMove;
	size->y += fMove;

	if (fMove >= 0)
	{	// 0�ȏ�̏ꍇ
		if (size->x > MaxSize.x) { size->x = MaxSize.x; }
		if (size->y > MaxSize.y) { size->y = MaxSize.y; }
	}
	else if (fMove < 0)
	{	// 0�ȉ��̏ꍇ
		if (size->x < MaxSize.x) { size->x = MaxSize.x; }
		if (size->y < MaxSize.y) { size->y = MaxSize.y; }
	}
}

//=============================================================================
// �v���C���[�ƕ����r���{�[�h�Ƃ̋����𑪂鏈��
//=============================================================================
void CWord::Distance(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, int nNumPlayer)
{
	// �����𑪂�
	m_fDistance[nNumPlayer] = ((Pos.x - OtherPos.x) * (Pos.x - OtherPos.x)) + ((Pos.z - OtherPos.z) * (Pos.z - OtherPos.z));
}

//=============================================================================
// ���������������Ɉ�ԋ߂�������I�ԏ���
//=============================================================================
int CWord::ComparisonDistance(int nNum)
{
	int nNumPlayer = 0;	//�߂��v���C���[���L��

	for (int nCntPlayer = 0; nCntPlayer < (int)nNum - 1; nCntPlayer++)
	{
#if 0
		//���̎�
		if (m_fDistance[nCntPlayer] > m_fDistance[nCntPlayer + 1])
		{	// ���l����
			nNumPlayer = nCntPlayer + 1;
		}
		//����
		//m_fDistance[0] = 5000;
		//m_fDistance[1] = 500;
		//m_fDistance[2] = 10000;
		//m_fDistance[3] = 100;

#endif
		if (m_fDistance[nNumPlayer] < m_fDistance[nCntPlayer + 1])
		{	//��ׂ��鑤���߂� // ���l���� 0��1 1��2 2��3
			nNumPlayer = nNumPlayer;
		}
		else
		{	//��ׂ鑤���߂�
			nNumPlayer = nCntPlayer + 1;
		}
	}

	return nNumPlayer;
}


//=============================================================================
// �͈͂̏���
//=============================================================================
void CWord::Circle(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, float fAngle)
{
	float fDistance = sqrtf((Pos.x - OtherPos.x)* (Pos.x - OtherPos.x) + (Pos.z - OtherPos.z)*(Pos.z - OtherPos.z));

	if (fDistance < fAngle)
	{
		m_bFlag = true;
	}
}



//=============================================================================
// �v���C���[�ɏW�܂�̏���
//=============================================================================
D3DXVECTOR3 CWord::Approach(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, float fAngle, float fDistance)
{
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f,0.0f);

	if (fDistance < fAngle * fAngle)
	{	// �������ɓ�������
		// �v���C���[�ɋ߂Â���
		move.x = sinf(atan2f(OtherPos.x - Pos.x, OtherPos.z - Pos.z)) * CHASE_MOVE;
		move.z = cosf(atan2f(OtherPos.x - Pos.x, OtherPos.z - Pos.z)) * CHASE_MOVE;
	}

	return move;
}

//=============================================================================
// 3�����ڂɌ��̐F�ݒ菈��
//=============================================================================
void CWord::SetSearchCol(int nID)
{
	if (m_nPlayerID[nID] == NOT_NOM_DATA)
	{
		m_nPlayerID[nID] = nID;		// ID�̑��
	}

	if (m_pBillBoard[0] != NULL)
	{
		m_pBillBoard[0]->SetColFlag(true);
	}
}

//=============================================================================
// 3�����ڌ�₪�����Ȃ����ꍇ
//=============================================================================
void CWord::UninitSearchCol(int nID)
{
	if (m_nPlayerID[nID] == nID)
	{	// �F���f�t�H���g�ɖ߂�
		m_nPlayerID[nID] = NOT_NOM_DATA;

		if (m_pBillBoard[0] != NULL)
		{
			m_pBillBoard[0]->SetColFlag(false);
		}
	}
}

//=============================================================================
//	�_�ł̏���
//=============================================================================
void CWord::FlashingCol(void)
{
	float fColA = 0.0f;
	if (m_nCntFlashing > FLASHING_TIME_MAX) { fColA = FLASHING_MAX; }
	else if (m_nCntFlashing > FLASHING_TIME_SMALL) { fColA = FLASHING_SMALL; }

	if (m_bFlashingFlag == false)
	{	// �s�������瓧��
		m_col.a -= fColA;
		if (m_col.a < 0.4f) { m_col.a = 0.4f; m_bFlashingFlag = true; }
	}
	else if (m_bFlashingFlag == true)
	{	// �s�������瓧��
		m_col.a += fColA;
		if (m_col.a > 1.0f) { m_col.a = 1.0f; m_bFlashingFlag = false; }
	}

	m_nCntFlashing++;

	if ((m_nCntFlashing % REST_TIME) == 0)
	{
		m_bRestFlag = true;
	}
}