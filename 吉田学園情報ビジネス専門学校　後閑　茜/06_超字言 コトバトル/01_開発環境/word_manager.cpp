//=============================================================================
//
// �����̊Ǘ����� [word_manager.cpp]
// Author : ���� �x
//
//=============================================================================
#include "word_manager.h"
#include "input.h"
#include "InputKeyboard.h"
#include "manager.h"
#include "sceneX.h"
#include "debugProc.h"
#include "game.h"
#include "SetWord.h"
#include "point.h"
#include "word.h"
#include "PlayerNumSelect.h"

#include "bullet.h"
#include "CameraManager.h"
#include "tutorial.h"

#include "sound.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define COL_1P	(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))		// 1P�J���[ (��)
#define COL_2P	(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f))		// 2P�J���[ (��)
#define COL_3P	(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f))		// 3P�J���[	(��)
#define COL_4P	(D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f))		// 4P�J���[	(�I�����W)
#define COL_CPU	(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f))		// CPU�J���[(�N���[)

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
D3DXVECTOR3 *CWordManager::m_AnswerNum = &D3DXVECTOR3(NOT_NUM, NOT_NUM, NOT_NUM);
int CWordManager::m_nAnswerDataNum = 0;
D3DXVECTOR3 *CWordManager::m_Scale = &D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 *CWordManager::m_rot = &D3DXVECTOR3(0.0f, 0.0f, 0.0f);
int *CWordManager::m_type = 0;
int *CWordManager::m_nAnswerTypeModel = 0;
int *CWordManager::m_nPoint = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWordManager::CWordManager()
{
	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{	// �Ǘ��̒��g��������
		m_aWord[nCntWord].nNum = EMPTINESS_NUM;
		m_aWord[nCntWord].cWord = "NULL";
		m_aWord[nCntWord].bClearFlag = false;

		m_nStock[nCntWord] = EMPTINESS_NUM;

	}
	m_nCntNum = 0;			// �񐔂̃J�E���g
	m_nCreateType = NOT_NUM;// ��������^�C�v
	m_nCntaAnswer = 0;		// �����Ƃ̔�r���č����Ă��鐔
	m_nPlayerID = 0;		// �v���C���[�����Ԃ��̕ۑ�
	m_bPress = false;		// �w�肵�������ȏ������Ȃ��t���O
	m_bSearch = false;		// �T�[�`���J�n���鎞�̃t���O
	m_bFlag = false;
	m_bAnswerCheck = false;

	m_fAnswerData = NULL;
	m_Scale = NULL;
	m_type = NULL;
	m_nAnswerTypeModel = NULL;
	m_rot = NULL;
	m_nPoint = NULL;

	m_nCntStock = 0;
	m_bGatherFlag = false;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CWordManager::~CWordManager() {}

//=============================================================================
// ����������
//=============================================================================
void CWordManager::Init()
{

}

//=============================================================================
// �I������
//=============================================================================
void CWordManager::Uninit(void)
{
	if (m_AnswerNum != NULL)
	{
		delete[] m_AnswerNum;
		m_AnswerNum = NULL;
	}

	if (m_fAnswerData != NULL && m_bSearch == true)
	{
		delete[] m_fAnswerData;
		m_fAnswerData = NULL;
	}

	if (m_Scale != NULL)
	{
		delete[] m_Scale;
		m_Scale = NULL;
	}

	if (m_rot != NULL)
	{
		delete[] m_rot;
		m_rot = NULL;
	}

	if (m_type != NULL)
	{
		delete[] m_type;
		m_type = NULL;
	}

	if (m_nAnswerTypeModel != NULL)
	{
		delete[] m_nAnswerTypeModel;
		m_nAnswerTypeModel = NULL;
	}

	if (m_nPoint != NULL)
	{
		delete[] m_nPoint;
		m_nPoint = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CWordManager::Update(void)
{
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	CreateOblDebug();		// �����ŕ����̊Ǘ�(�f�o�b�N�p)

	if (CManager::GetWordCreate()->GetCreateFlag() == true)
	{
		m_bSearch = false;
		SearchWord();
		CManager::GetWordCreate()->SetCreateFlagr(false);
	}

	if (m_nCntNum != 2 && m_bSearch == true)
	{ // �����Ă��镶����2�����ȊO�Ȃ�T�[�`�̃t���O��ύX
		m_bSearch = false;
		UninitAssist();
		if (m_fAnswerData != NULL)
		{
			delete[] m_fAnswerData;
			m_fAnswerData = NULL;
		}
		//*m_fAnswerData = 99.0f;		// ��̔ԍ��������
	}

	if (m_nCntNum == MAX_WORD)
	{	// �ő�Ȃ炱��ȏ㐔��������Ȃ�
		m_bPress = true;
		m_bAnswerCheck = false;
	}

	if (m_bAnswerCheck == true && m_bPress == false)
	{
		//m_bAnswerCheck = false;
	}

	if (m_bPress == true && m_bAnswerCheck == false)
	{
		if (m_nCntaAnswer == 0)
		{
			for (int nCntAnswer = 0; nCntAnswer < m_nAnswerDataNum; nCntAnswer++)
			{	// �����̐�������
				for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
				{	// ���Ƃ̔�r
					if (m_AnswerNum[nCntAnswer].x == m_aWord[nCntWord].nNum && m_bAnswer[0] == false) { m_bAnswer[0] = true; }
					else if (m_AnswerNum[nCntAnswer].y == m_aWord[nCntWord].nNum && m_bAnswer[1] == false) { m_bAnswer[1] = true; }
					else if (m_AnswerNum[nCntAnswer].z == m_aWord[nCntWord].nNum && m_bAnswer[2] == false) { m_bAnswer[2] = true; }
				}

				if (m_bAnswer[0] == true && m_bAnswer[1] == true && m_bAnswer[2] == true) { m_nCntaAnswer = MAX_WORD; m_bFlag = false; }
				else if (m_nCntaAnswer < MAX_WORD)
				{
					for (int nCount = 0; nCount < MAX_WORD; nCount++)
					{
						m_bAnswer[nCount] = false;
						m_bFlag = true;
					}
				}

				if (m_nCntaAnswer == MAX_WORD)
				{
					m_nCntNum = 0;
					m_nCreateType = nCntAnswer;
					m_nStock[m_nCntStock] = nCntAnswer;
					if (CManager::GetTube(m_nPlayerID) != NULL)
					{
						CManager::GetTube(m_nPlayerID)->SetAnswer(nCntAnswer, m_nCntStock);
						CManager::GetTube(m_nPlayerID)->SetPoint(m_nPoint[m_nCreateType], m_nPlayerID, false);
						CManager::GetTube(m_nPlayerID)->SetStockNum(m_nCntStock);
					}

					// ����model�̃T�E���h�Đ�
					int nCntSound = 0;
					nCntSound = m_nCreateType + (int)CSound::SOUND_LABEL_WORDVOICE_KURUMA;	// �Ԃ̃{�C�X����

					CManager::GetSound()->SetVolume((CSound::SOUND_LABEL)nCntSound, 8.0f);
					CManager::GetSound()->PlaySoundA((CSound::SOUND_LABEL)nCntSound);

					m_nCntaAnswer = 0;
					m_nCntStock++;
					if (m_nCntStock >= MAX_WORD) { m_nCntStock = MAX_WORD;  m_bGatherFlag = true; }

					m_bAnswerCheck = true;
					return;
				}
				else { m_nCntaAnswer = 0; }
			}

			//if (m_nCreateType > m_nAnswerDataNum )
			//{
			//	if (CGame::GetTube(m_nPlayerID) != NULL)
			//	{
			//		CGame::GetTube(m_nPlayerID)->SetAnswer(NOT_NUM);
			//		//CGame::GetTube(m_nPlayerID)->SetPoint(-3, m_nPlayerID);
			//	}
			//}
		}

		//�e�X�g
		//if (pInputKeyboard->GetTrigger(DIK_LSHIFT))
		//{	// �e�̐���
		//	BulletCreate(0);
		//}

		m_bAnswerCheck = true;
	}

	// �X�g�b�N������ꍇ �e��łĂ�t���O�𗧂Ă�
	if (m_nCntStock > 0) { m_bPress = true; }

	if (m_bFlag == true)
	{
		if (CManager::GetTube(m_nPlayerID) != NULL)
		{
			CManager::GetTube(m_nPlayerID)->SetAnswer(NOT_NUM, m_nCntStock);
			CManager::GetTube(m_nPlayerID)->SetPoint(1, m_nPlayerID, true);
			CManager::GetTube(m_nPlayerID)->SetStockNum(m_nCntStock);
		}
		m_nStock[m_nCntStock] = NOT_NUM;
		m_nCntNum = 0;
		m_nCntaAnswer = 0;
		m_bFlag = false;

		m_nCntStock++;
		if (m_nCntStock >= MAX_WORD)
		{
			m_nCntStock = MAX_WORD;
			m_bGatherFlag = true;
		}
	}



#ifdef _DEBUG
	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		CDebugProc::Print("cc", "m_aWord = ", m_aWord[nCntWord].cWord);
	}
#endif
}

//=============================================================================
// �ݒ菈��
//=============================================================================
void CWordManager::SetWord(int nType)
{
	CSound *pSound = CManager::GetSound();		//	���̎擾
	if (m_nCntNum < MAX_WORD)
	{
		if (m_nCntNum == 0)
		{
			for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
			{
				m_aWord[nCntWord].nNum = EMPTINESS_NUM;
			}
			pSound->SetVolume(CSound::SOUND_LABEL_SE_GETTEXT000, 0.5f);
			pSound->PlaySound(CSound::SOUND_LABEL_SE_GETTEXT000);
		}
		else if (m_nCntNum == 1)
		{
			pSound->SetVolume(CSound::SOUND_LABEL_SE_GETTEXT001, 0.5f);
			pSound->PlaySound(CSound::SOUND_LABEL_SE_GETTEXT001);
		}
		else if (m_nCntNum == 2)
		{
			pSound->SetVolume(CSound::SOUND_LABEL_SE_GETTEXT002, 0.5f);
			pSound->PlaySound(CSound::SOUND_LABEL_SE_GETTEXT002);
		}
		m_aWord[m_nCntNum].nNum = nType;
		WordDebug(m_nCntNum);
		if (CManager::GetTube(m_nPlayerID) != NULL)
		{	// NULL�`�F�b�N
			CManager::GetTube(m_nPlayerID)->SetWordNum(nType, m_nCntNum, m_nCntStock);
		}
		m_nCntNum++;
	}
}

//=============================================================================
// ���Z�b�g�֐�
//=============================================================================
void CWordManager::Reset(void)
{
	if (m_nStock > 0)
	{
		for (int nCntWord = m_nCntNum; nCntWord < MAX_WORD; nCntWord++)
		{
			m_aWord[nCntWord].nNum = EMPTINESS_NUM;
			m_aWord[nCntWord].cWord = "NULL";
		}
	}

	for (int nCount = 0; nCount < MAX_WORD; nCount++)
	{
		m_bAnswer[nCount] = false;
	}

	m_nStock[0] = EMPTINESS_NUM;
	for (int nCntStcok = 0; nCntStcok < MAX_WORD - 1; nCntStcok++)
	{
		int nAnswerStock = m_nStock[nCntStcok];
		m_nStock[nCntStcok] = m_nStock[nCntStcok + 1];
		m_nStock[nCntStcok + 1] = nAnswerStock;
	}

	m_bGatherFlag = false;
	m_nCntStock--;
	if (m_nCntStock < 0) { m_nCntStock = 0; }
	if (CManager::GetTube(m_nPlayerID) != NULL)
	{
		CManager::GetTube(m_nPlayerID)->SetStockNum(m_nCntStock);
		CManager::GetTube(m_nPlayerID)->AllDelete(m_nCntNum);
		CManager::GetTube(m_nPlayerID)->UninitChack(false);
	}

	m_nCntaAnswer = 0;

	if (m_nStock[0] < m_nAnswerDataNum || m_nStock[0] == NOT_NUM)
	{
		m_bPress = true;
	}
	else { m_bPress = false;}
}

//=============================================================================
// �������Z�b�g�֐�
//=============================================================================
void CWordManager::WordReset(void)
{
	m_nCntNum = 0;

	if (m_nStock > 0)
	{
		for (int nCntWord = m_nCntNum; nCntWord < MAX_WORD; nCntWord++)
		{
			m_aWord[nCntWord].nNum = EMPTINESS_NUM;
			m_aWord[nCntWord].cWord = "NULL";
		}
	}

	for (int nCount = 0; nCount < MAX_WORD; nCount++)
	{
		m_bAnswer[nCount] = false;
	}

	m_bGatherFlag = false;

	m_nCntaAnswer = 0;
}

//=============================================================================
// �e�̐���  Editor : Kodama Yuto
//=============================================================================
void CWordManager::BulletCreate(int nID, D3DXVECTOR3 BulletMuzzle, D3DXVECTOR3 BulletRot, CPlayer::PLAYER_TYPE type, C3DCharactor* pChara)
{
	CSound *pSound = CManager::GetSound();		//	���̎擾

	CCameraManager *pCameraManager = CManager::GetCameraManager();

	if (type == CPlayer::TYPE_RANDOM)
	{//�����_�����I�΂��͕̂s���Ȃ̂ŏ�����ł��؂�
		return;
	}

	/*���[�h�ɂ���ď�����ς���*/
	if (CManager::GetPlayer(nID) != NULL)
	{//�w�肵���v���C���[�����݂��Ă����
		if (m_nCntStock > 0)
		{
			if (m_nStock[0] < m_nAnswerDataNum)
			{	// �w�肵�������Ȃ�e�𐶐�����
				int nType = 0;
				CModelBullet* pModel = NULL;
				D3DXVECTOR3 Sector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				nType = m_nStock[0];
				m_nCreateType = m_nAnswerTypeModel[nType] + (int)CLoad::MODEL_CAR0;	//�e�ɂȂ郂�f���̈ʒu�܂Ń^�C�v�����炷


				switch (type)
				{
				case CPlayer::TYPE_SPEED://�L�̓~�T�C���^
					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{
						pModel->Set(BulletMuzzle, BulletRot + D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							(CLoad::MODEL)m_nCreateType,
							CModelBullet::TYPE_MISSILE_CENTER,
							nID, m_rot[nType]);
						pModel->SetModelScale(m_Scale[nType]);	//�傫���̐ݒ�
						pModel->SetHomingChara(pChara);
					}

					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{//0.75f
						pModel->Set(BulletMuzzle, BulletRot + D3DXVECTOR3(0.0f, 0.85f, 0.0f),
							(CLoad::MODEL)m_nCreateType,
							CModelBullet::TYPE_MISSILE_SIDE,
							nID, m_rot[nType]);
						pModel->SetModelScale(m_Scale[nType]);	//�傫���̐ݒ�
						pModel->SetHomingChara(pChara);
					}

					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{
						pModel->Set(BulletMuzzle, BulletRot + D3DXVECTOR3(0.0f, -0.85f, 0.0f),
							(CLoad::MODEL)m_nCreateType,
							CModelBullet::TYPE_MISSILE_SIDE,
							nID, m_rot[nType]);
						pModel->SetModelScale(m_Scale[nType]);	//�傫���̐ݒ�
						pModel->SetHomingChara(pChara);
					}

					m_nCreateType = EMPTINESS_NUM;
					break;
				case CPlayer::TYPE_REACH://�������̓}�V���K���^
					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{
						pModel->Set(BulletMuzzle, BulletRot,
							(CLoad::MODEL)m_nCreateType,
							CModelBullet::TYPE_MACHINEGUN,
							nID, m_rot[nType]);
						pModel->SetModelScale(m_Scale[nType]);	//�傫���̐ݒ�
					}

					m_nCreateType = EMPTINESS_NUM;
					break;
				case CPlayer::TYPE_BARANCE://���̓V���b�g�K���^
					//�e����
					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{
						Sector.y = 0.4f;
						pModel->Set(BulletMuzzle, BulletRot + Sector,
							(CLoad::MODEL)m_nCreateType,
							CModelBullet::TYPE_SHOTGUN_SLOW,
							nID, m_rot[nType]);
						pModel->SetModelScale(m_Scale[nType]);	//�傫���̐ݒ�
					}
					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{
						Sector.y = -0.4f;
						pModel->Set(BulletMuzzle, BulletRot + Sector,
							(CLoad::MODEL)m_nCreateType,
							CModelBullet::TYPE_SHOTGUN_SLOW,
							nID, m_rot[nType]);
						pModel->SetModelScale(m_Scale[nType]);	//�傫���̐ݒ�
					}

					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{
						Sector.y = 0.2f;
						pModel->Set(BulletMuzzle, BulletRot + Sector,
							(CLoad::MODEL)m_nCreateType,
							CModelBullet::TYPE_SHOTGUN_MEDIUM,
							nID, m_rot[nType]);
						pModel->SetModelScale(m_Scale[nType]);	//�傫���̐ݒ�
					}

					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{
						Sector.y = -0.2f;
						pModel->Set(BulletMuzzle, BulletRot + Sector,
							(CLoad::MODEL)m_nCreateType,
							CModelBullet::TYPE_SHOTGUN_MEDIUM,
							nID, m_rot[nType]);
						pModel->SetModelScale(m_Scale[nType]);	//�傫���̐ݒ�
					}
					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{
						Sector.y = 0.1f;
						pModel->Set(BulletMuzzle, BulletRot + Sector,
							(CLoad::MODEL)m_nCreateType,
							CModelBullet::TYPE_SHOTGUN,
							nID, m_rot[nType]);
						pModel->SetModelScale(m_Scale[nType]);	//�傫���̐ݒ�
					}

					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{
						Sector.y = -0.1f;
						pModel->Set(BulletMuzzle, BulletRot + Sector,
							(CLoad::MODEL)m_nCreateType,
							CModelBullet::TYPE_SHOTGUN,
							nID, m_rot[nType]);
						pModel->SetModelScale(m_Scale[nType]);	//�傫���̐ݒ�
					}
					m_nCreateType = EMPTINESS_NUM;
					break;
				case CPlayer::TYPE_POWER://�F�͔��e�^
					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{
						pModel->Set(BulletMuzzle, BulletRot + D3DXVECTOR3(0.0f, 0.1f, 0.0f),
							(CLoad::MODEL)m_nCreateType,
							CModelBullet::TYPE_BOMB,
							nID, m_rot[nType]);
						pModel->SetModelScale(m_Scale[nType]);	//�傫���̐ݒ�
						pModel->SetHomingChara(pChara);
					}

					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{
						pModel->Set(BulletMuzzle, BulletRot + D3DXVECTOR3(0.0f, -0.1f, 0.0f),
							(CLoad::MODEL)m_nCreateType,
							CModelBullet::TYPE_BOMB,
							nID, m_rot[nType]);
						pModel->SetModelScale(m_Scale[nType]);	//�傫���̐ݒ�
						pModel->SetHomingChara(pChara);
					}

					break;
				default:
					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{
						//pModel->Set(BulletMuzzle, BulletRot, (CLoad::MODEL)m_nCreateType, (CModelBullet::BULLET_PROPERTY)m_type[nType], nID, m_rot[nType]);
						pModel->Set(BulletMuzzle, BulletRot, (CLoad::MODEL)m_nCreateType, CModelBullet::TYPE_BOMB, nID, m_rot[nType]);

						pModel->SetModelScale(m_Scale[nType]);	//�傫���̐ݒ�
						if (m_type[nType] == CModelBullet::TYPE_MISSILE_CENTER)
						{
							pModel->SetHomingChara(pChara);
						}
						m_nCreateType = EMPTINESS_NUM;

						if ((CModelBullet::BULLET_PROPERTY)m_type[nType] == (CModelBullet::BULLET_PROPERTY)m_type[0])
						{
							pSound->SetVolume(CSound::SOUND_LABEL_SE_BULLET000, 3.0f);
							pSound->PlaySound(CSound::SOUND_LABEL_SE_BULLET000);
						}
						else if ((CModelBullet::BULLET_PROPERTY)m_type[nType] == (CModelBullet::BULLET_PROPERTY)m_type[1])
						{
							pSound->SetVolume(CSound::SOUND_LABEL_SE_BULLET001, 3.0f);
							pSound->PlaySound(CSound::SOUND_LABEL_SE_BULLET001);
						}
						else if ((CModelBullet::BULLET_PROPERTY)m_type[nType] == (CModelBullet::BULLET_PROPERTY)m_type[2])
						{
							pSound->SetVolume(CSound::SOUND_LABEL_SE_BULLET002, 3.0f);
							pSound->PlaySound(CSound::SOUND_LABEL_SE_BULLET002);
						}
						else if ((CModelBullet::BULLET_PROPERTY)m_type[nType] == (CModelBullet::BULLET_PROPERTY)m_type[3])
						{
							pSound->SetVolume(CSound::SOUND_LABEL_SE_BULLET003, 3.0f);
							pSound->PlaySound(CSound::SOUND_LABEL_SE_BULLET003);
						}
					}
					break;
				}

			}
			else if (m_nStock[0] == NOT_NUM)
			{	// �S�~���f�����o��
				CModelBullet* pModel = CModelBullet::Create();
				if (pModel != NULL)
				{
					pModel->Set(BulletMuzzle, BulletRot, CLoad::MODE_DUST, CModelBullet::TYPE_NORMAL, nID);
					pModel->SetModelScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));//�傫���̐ݒ�
				}
			}

			if (CManager::GetMode() == CManager::MODE_GAME)
			{
				//�u�����h�����Œe�ł����[�V�����Ɉڍs
				CGame::GetPlayer(nID)->SetMotion(CPlayer::MOTION_UPPER_SHOT, CPlayer::UPPER_BODY, CPlayer::STATE_NORMAL);
				CGame::GetPlayer(nID)->SetMotion(CPlayer::MOTION_LOWER_SHOT, CPlayer::LOWER_BODY, CPlayer::STATE_NORMAL);

				if (type != CPlayer::TYPE_REACH)
				{
					Reset();		// �ݒ��߂�
				}
			}
			else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
			{
				//�u�����h�����Œe�ł����[�V�����Ɉڍs
				CTutorial::GetPlayer(nID)->SetMotion(CPlayer::MOTION_UPPER_SHOT, CPlayer::UPPER_BODY, CPlayer::STATE_NORMAL);
				CTutorial::GetPlayer(nID)->SetMotion(CPlayer::MOTION_LOWER_SHOT, CPlayer::LOWER_BODY, CPlayer::STATE_NORMAL);
				if (type != CPlayer::TYPE_REACH)
				{
					Reset();		// �ݒ��߂�
				}
			}

		}
	}
}

//=============================================================================
// Text����ǂݍ��� �����̊��蓖��
//=============================================================================
void CWordManager::SetWordLoad(int nNumModel, D3DXVECTOR3 AnswerNum, D3DXVECTOR3 scale, D3DXVECTOR3 rot, int type, int Model, int nPoint)
{
	m_AnswerNum[nNumModel] = AnswerNum;
	m_Scale[nNumModel] = scale;
	m_type[nNumModel] = type;
	m_nAnswerTypeModel[nNumModel] = Model;
	m_rot[nNumModel] = rot;
	m_nPoint[nNumModel] = nPoint;
}

//=============================================================================
// Text����ő吔�ǂݍ��� ���I�m��
//=============================================================================
void CWordManager::SetWordAnswerNum(int nAnswerNum)
{
	m_nAnswerDataNum = nAnswerNum;
	m_AnswerNum = new D3DXVECTOR3[m_nAnswerDataNum];
	m_Scale = new D3DXVECTOR3[m_nAnswerDataNum];
	m_rot = new D3DXVECTOR3[m_nAnswerDataNum];
	m_type = new int[m_nAnswerDataNum];
	m_nAnswerTypeModel = new int[m_nAnswerDataNum];
	m_nPoint = new int[nAnswerNum];
}

//=============================================================================
// �����̑g�ݍ��킹�������Ă��邩�ǂ������擾
//=============================================================================
int CWordManager::SearchWord(void)
{
	if (m_nCntNum == 2 && m_bSearch == false)
	{	// �E�����������Q�����̏ꍇ
		int nData = 0;
		if (m_fAnswerData == NULL)
		{
			m_fAnswerData = new float[m_nAnswerDataNum];
		}

		for (int nCntAnswer = 0; nCntAnswer < m_nAnswerDataNum; nCntAnswer++)
		{	// �����̐�������
			int nAnswer = 0;
			for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
			{	// ���Ƃ̔�r
				if (m_AnswerNum[nCntAnswer].x == m_aWord[nCntWord].nNum && m_bAnswer[0] == false) { m_bAnswer[0] = true; nAnswer++; }
				else if (m_AnswerNum[nCntAnswer].y == m_aWord[nCntWord].nNum && m_bAnswer[1] == false) { m_bAnswer[1] = true; nAnswer++; }
				else if (m_AnswerNum[nCntAnswer].z == m_aWord[nCntWord].nNum && m_bAnswer[2] == false) { m_bAnswer[2] = true; nAnswer++; }

				if (nAnswer == 2)
				{	// �����Ă��鏊��2�ӏ��̏ꍇ
					for (int nCntData = 0; nCntData < MAX_WORD; nCntData++)
					{
						if (m_bAnswer[nCntData] == false)
						{	// false�̏ꏊ��T�� ��������������
							if (nCntData == 0) { m_fAnswerData[nData] = m_AnswerNum[nCntAnswer].x; }
							else if (nCntData == 1) { m_fAnswerData[nData] = m_AnswerNum[nCntAnswer].y; }
							else if (nCntData == 2) { m_fAnswerData[nData] = m_AnswerNum[nCntAnswer].z; }
							nData++;		// �񐔂𑝂₷
						}
					}
					nAnswer = 0;	// �����Ă���񐔂����Z�b�g
				}
			}

			for (int nCount = 0; nCount < MAX_WORD; nCount++)
			{	// �S��false�ɖ߂�
				m_bAnswer[nCount] = false;
			}
		}

		// 3�����ڌ��̃A�V�X�g
		SearchAssist(nData);

		m_bSearch = true;		// Flag��ture��
		return nData;			// �����̏o����
	}

	return 0;
}

//=============================================================================
// �����T���A�V�X�g�̏���
//=============================================================================
void CWordManager::SearchAssist(int nCntData)
{
	if (nCntData == 0) { return; }
	int nNum = 0;
	int nCount = 0;

	CScene *pScene = NULL;

	nNum = CManager::GetWordCreate()->GetPopNum();

	while (nCount < CWord::GetAllNum())
	{
		// �擪�̃I�u�W�F�N�g���擾
		pScene = CScene::GetTop(5);

		while (pScene != NULL)
		{// �D�揇�ʂ��e�Ɠ����I�u�W�F�N�g��1��1�m���߂�
		 // �����̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
			CScene *pSceneNext = pScene->GetNext();
			if (pScene->GetDeath() == false && pScene->GetObjType() == CScene::OBJTYPE_WORD)
			{// ���S�t���O�������Ă��Ȃ�����
				CWord *pWord = ((CWord*)pScene);		// CBulletBase�փL���X�g(�^�̕ύX)
				for (int nCntWord = 0; nCntWord < nCntData; nCntWord++)
				{
					if (pWord->GetWordNum() == m_fAnswerData[nCntWord])
					{
						pWord->SetSearchCol(m_nPlayerID);
					}
				}
				nCount++;
			}
			pScene = pSceneNext;
		}
	}
}

//=============================================================================
// 3�����ڌ��̃A�V�X�g�J���[���f�t�H���g�ɕύX
//=============================================================================
void CWordManager::UninitAssist(void)
{
	int nNum = 0;
	int nCount = 0;

	CScene *pScene = NULL;

	if (CManager::MODE_GAME == CManager::GetMode()) { nNum = CGame::GetWordCreate()->GetPopNum(); }
	if (CManager::MODE_TUTORIAL == CManager::GetMode()) { nNum = CTutorial::GetWordCreate()->GetPopNum(); }

	while (nCount < CWord::GetAllNum())
	{
		// �擪�̃I�u�W�F�N�g���擾
		pScene = CScene::GetTop(5);

		while (pScene != NULL)
		{// �D�揇�ʂ��e�Ɠ����I�u�W�F�N�g��1��1�m���߂�
		 // �����̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
			CScene *pSceneNext = pScene->GetNext();
			if (pScene->GetDeath() == false && pScene->GetObjType() == CScene::OBJTYPE_WORD)
			{// ���S�t���O�������Ă��Ȃ�����
				CWord *pWord = ((CWord*)pScene);		// CBulletBase�փL���X�g(�^�̕ύX)
				pWord->UninitSearchCol(m_nPlayerID);
				nCount++;
			}
			pScene = pSceneNext;
		}
	}
}


//=============================================================================
// �����Ő����̃f�o�b�N�p(�����Ǘ�)
//=============================================================================
void CWordManager::CreateOblDebug(void)
{
	CInputKeyboard *pKey = CManager::GetInputKeyboard();

	if (m_bPress == false)
	{
		if (pKey->GetPress(DIK_1))
		{	// ���s
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// ��
				m_aWord[m_nCntNum].nNum = 0;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ��
				m_aWord[m_nCntNum].nNum = 1;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ��
				m_aWord[m_nCntNum].nNum = 2;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// ��
				m_aWord[m_nCntNum].nNum = 3;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// ��
				m_aWord[m_nCntNum].nNum = 4;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_2))
		{	// ���s
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// ��
				m_aWord[m_nCntNum].nNum = 5;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ��
				m_aWord[m_nCntNum].nNum = 6;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ��
				m_aWord[m_nCntNum].nNum = 7;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// ��
				m_aWord[m_nCntNum].nNum = 8;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// ��
				m_aWord[m_nCntNum].nNum = 9;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_3))
		{	// ���s
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// ��
				m_aWord[m_nCntNum].nNum = 10;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ��
				m_aWord[m_nCntNum].nNum = 11;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ��
				m_aWord[m_nCntNum].nNum = 12;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// ��
				m_aWord[m_nCntNum].nNum = 13;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// ��
				m_aWord[m_nCntNum].nNum = 14;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_4))
		{	// ���s
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// ��
				m_aWord[m_nCntNum].nNum = 15;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ��
				m_aWord[m_nCntNum].nNum = 16;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ��
				m_aWord[m_nCntNum].nNum = 17;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// ��
				m_aWord[m_nCntNum].nNum = 18;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// ��
				m_aWord[m_nCntNum].nNum = 19;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_5))
		{	// �ȍs
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// ��
				m_aWord[m_nCntNum].nNum = 20;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ��
				m_aWord[m_nCntNum].nNum = 21;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ��
				m_aWord[m_nCntNum].nNum = 22;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// ��
				m_aWord[m_nCntNum].nNum = 23;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// ��
				m_aWord[m_nCntNum].nNum = 24;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_6))
		{	// �͍s
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// ��
				m_aWord[m_nCntNum].nNum = 25;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ��
				m_aWord[m_nCntNum].nNum = 26;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ��
				m_aWord[m_nCntNum].nNum = 27;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// ��
				m_aWord[m_nCntNum].nNum = 28;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// ��
				m_aWord[m_nCntNum].nNum = 29;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_7))
		{	// �܍s
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// ��
				m_aWord[m_nCntNum].nNum = 30;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ��
				m_aWord[m_nCntNum].nNum = 31;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ��
				m_aWord[m_nCntNum].nNum = 32;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// ��
				m_aWord[m_nCntNum].nNum = 33;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// ��
				m_aWord[m_nCntNum].nNum = 34;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_8))
		{	// ��s
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// ��
				m_aWord[m_nCntNum].nNum = 35;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ��
				m_aWord[m_nCntNum].nNum = 36;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ��
				m_aWord[m_nCntNum].nNum = 37;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_9))
		{	// ��s
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// ��
				m_aWord[m_nCntNum].nNum = 38;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ��
				m_aWord[m_nCntNum].nNum = 39;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ��
				m_aWord[m_nCntNum].nNum = 40;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// ��
				m_aWord[m_nCntNum].nNum = 41;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// ��
				m_aWord[m_nCntNum].nNum = 42;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_0))
		{	// ��s
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// ��
				m_aWord[m_nCntNum].nNum = 43;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ��
				m_aWord[m_nCntNum].nNum = 44;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ��
				m_aWord[m_nCntNum].nNum = 45;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
		}
	}

	if (m_nCntNum == MAX_WORD)
	{	// �ő�Ȃ炱��ȏ㐔��������Ȃ�
		m_bPress = true;
	}
}

//=============================================================================
// �����̃f�o�b�N�p
//=============================================================================
void CWordManager::WordDebug(int nCntNum)
{
	if (m_aWord[nCntNum].nNum == 0)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 1)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 2)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 3)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 4)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 5)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 6)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 7)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 8)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 9)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 10)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 11)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 12)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 13)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 14)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 15)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 16)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 17)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 18)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 19)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 20)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 21)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 22)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 23)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 24)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 25)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 26)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 27)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 28)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 29)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 30)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 31)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 32)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 33)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 34)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 35)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 36)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 37)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 38)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 39)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 40)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 41)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 42)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 43)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 44)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 45)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == NOT_NUM)
	{	// ��̏��
		m_aWord[nCntNum].cWord = "NULL";
	}
}


