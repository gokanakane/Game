//---------------------------------------------------------------------
//	�����z�u����(SetWord.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "SetWord.h"
#include "game.h"
#include "fade.h"
#include "word.h"
#include "word_manager.h"
#include "sceneBillboard.h"
#include "time.h"
#include <stdlib.h>
#include <time.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define POP_TIME				(60)		// �����l��������o���܂ł̎���

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------

//--------------------------------------------
//�I�u�W�F�N�g�N���X �R���X�g���N�^
//--------------------------------------------
CSetWord::CSetWord() : CScene(3, CScene::OBJTYPE_SETOBJECT)
{
	m_pWordPos = NULL;
	m_AnswerNum = NULL;
	m_nAnswerNumCount = 0;
	m_nNum = 0;
	m_bUninitFlag = false;
}

//--------------------------------------------
//�I�u�W�F�N�g�N���X �f�X�g���N�^
//--------------------------------------------
CSetWord::~CSetWord()
{
}

//--------------------------------------------
//�I�u�W�F�N�g�̐���
//--------------------------------------------
CSetWord *CSetWord::Create()
{
	//�I�u�W�F�N�g�|�C���^
	CSetWord *pSetObject = NULL;
	if (pSetObject == NULL)
	{
		pSetObject = new CSetWord;
		if (pSetObject != NULL)
		{//�I�u�W�F�N�g�̏�����
			pSetObject->Init();
		}
	}
	//�I�u�W�F�N�g�̏���Ԃ�
	return pSetObject;
}

//=============================================================================
// �I�u�W�F�N�g�̏���������
//=============================================================================
HRESULT CSetWord::Init()
{
	srand((unsigned int)time(0));		// �����_���̂��

	//�I�u�W�F�N�g��ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_NONE);
	m_AnswerNum = CWordManager::GetAnswerNum();
	m_nAnswer = CWordManager::GetAnswerDataNum();
	m_nRandAnswerNum = rand() % m_nAnswer;
	m_bCreate = false;
	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̏I������
//=============================================================================
void CSetWord::Uninit(void)
{
	if (m_pWordPos != NULL)
	{
		delete[] m_pWordPos;
		m_pWordPos = NULL;
	}

	//����������(�I�u�W�F�N�g��j��)
	Release();
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V����
//=============================================================================
void CSetWord::Update(void)
{
	WordUninit();	// �����̏I���t���O�������Ă���ꍇ �I��������

	PopWord();		// �����̏o��
}

//=============================================================================
// �I�u�W�F�N�g�̕`�揈��
//=============================================================================
void CSetWord::Draw(void)
{
}

//=============================================================================
//�@�ʒu�̊��蓖��
//=============================================================================
void CSetWord::WordCreate(void)
{
	int nCntNum = 0;
	int nRandNum = 0;
	float fWord = 99.0f;
	while (m_nNum != nCntNum)
	{	// �J�E���g�������ɂȂ����ꍇ������

		// rand�ňʒu���߂�
		nRandNum = rand() % m_nNum;	// �s���p�^�[���̐��������߂�

		// if���Ŏg���Ă��邩���o��
		if (m_pWordPos[nRandNum].bUse == false)
		{
			m_pWordPos[nRandNum].bUse = true;
			if (m_nAnswerNumCount == 0) { fWord = m_AnswerNum[m_nRandAnswerNum].x; }
			if (m_nAnswerNumCount == 1) { fWord = m_AnswerNum[m_nRandAnswerNum].y; }
			if (m_nAnswerNumCount == 2) { fWord = m_AnswerNum[m_nRandAnswerNum].z; }

			CWord::Create(m_pWordPos[nRandNum].pos,D3DXVECTOR3(0.0f,0.0f,0.0f), 0.0f, 0.0f, "WORD", (int)fWord, nRandNum);
			// �g���Ă���ꍇ�̓J�E���g����
			nCntNum++;
			m_nAnswerNumCount++;

			if (m_nAnswerNumCount % 3 == 0)
			{
				// rand�ňʒu���߂�
				m_nRandAnswerNum = rand() % m_nAnswer;	// �s���p�^�[���̐��������߂�
				m_nAnswerNumCount = 0;
			}
		}
	}
}

//=============================================================================
//�@�����l����̏I������
//=============================================================================
void CSetWord::WordUninit(void)
{
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		if (CGame::GetbStageSet() == true) { m_bUninitFlag = true; }
		else if (CGame::GetbStageSet() == false) { m_bUninitFlag = false; }
	}

	CScene *pScene = NULL;
	int nNum = m_nNum;

	// �擪�̃I�u�W�F�N�g���擾
	pScene = CScene::GetTop(5);

	while (pScene != NULL)
	{// �D�揇�ʂ��e�Ɠ����I�u�W�F�N�g��1��1�m���߂�
	 // �����̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
		CScene *pSceneNext = pScene->GetNext();
		if (pScene->GetDeath() == false && pScene->GetObjType() == CScene::OBJTYPE_WORD)
		{// ���S�t���O�������Ă��Ȃ�����
			CWord *pWord = ((CWord*)pScene);		// CBulletBase�փL���X�g(�^�̕ύX)
			if (pWord->GetUninitFlag() == true && m_bUninitFlag == false)
			{
				nNum = pWord->GetNum();		// �ԍ����擾
				if (nNum < m_nNum)
				{
					m_pWordPos[nNum].bUse = false;
				}
				pWord->Uninit();
				pWord = NULL;
			}
			else if (m_bUninitFlag == true)
			{
				pWord->Uninit();
				pWord = NULL;
			}
		}
		pScene = pSceneNext;
	}
}

//=============================================================================
//�@�����̏o������
//=============================================================================
void CSetWord::PopWord(void)
{
	float fWord = 99.0f;
	int nCount = 0;

	for (int nCntPos = 0; nCntPos < m_nNum; nCntPos++)
	{
		if (m_pWordPos[nCntPos].bUse == false)
		{
			m_pWordPos[nCntPos].nCntPop++;

			if ((m_pWordPos[nCntPos].nCntPop % POP_TIME) == 0)
			{
				if (m_nAnswerNumCount == 0) { fWord = m_AnswerNum[m_nRandAnswerNum].x; }
				if (m_nAnswerNumCount == 1) { fWord = m_AnswerNum[m_nRandAnswerNum].y; }
				if (m_nAnswerNumCount == 2) { fWord = m_AnswerNum[m_nRandAnswerNum].z; }

				CWord::Create(m_pWordPos[nCntPos].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, "WORD", (int)fWord,0,nCntPos);
				m_nAnswerNumCount++;
				m_pWordPos[nCntPos].nCntPop = 0;
				m_pWordPos[nCntPos].bUse = true;
				nCount++;
				m_bCreate = true;

				if (m_nAnswerNumCount % 3 == 0)
				{
					// rand�ňʒu���߂�
					m_nRandAnswerNum = rand() % m_nAnswer;	// �s���p�^�[���̐��������߂�
					m_nAnswerNumCount = 0;
				}
			}
		}
	}

	//if (nCount == m_nNum) { m_bCreate = true; }
}

//=============================================================================
// �I�u�W�F�N�g�̔z�u����ǂݍ���
//=============================================================================
void CSetWord::LoadFile(char *pFileName)
{
	m_bCreate = false;
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�t�@�C���ǂݍ��ݗp�ϐ�
	FILE *pFile;			//�t�@�C���|�C���^
	char *pStrcur;			//���݂̐擪�̕�����
	char aLine[256];		//������
	char aStr[256];			//�ꎞ�ۑ�������
	int nIndex = 0;			//���݂̃C���f�b�N�X
	int nWord = 0;			//�|�b�v�ŕԂ��ꂽ�l��ێ�
	int nNumModel = 0;		//���f���̐�
	int nType = 0;			//���f���̎��
	int nCntNum = 0;
	D3DXVECTOR3 ModelPos;	//���f���̈ʒu

	if (m_pWordPos != NULL)
	{	// �ʒu�֌W�̍\���̂̊J��
		delete[] m_pWordPos;
		m_pWordPos = NULL;
	}

	//�t�@�C�����J�� �ǂݍ���
	pFile = fopen(pFileName, "r");
	//NULL�`�F�b�N
	if (pFile != NULL)
	{
		while (1)
		{
			//������̐擪��ݒ�
			pStrcur = ReadLine(pFile, &aLine[0]);
			//����������o��
			strcpy(aStr, pStrcur);

			if (memcmp(pStrcur, "NUM_MODEL = ", strlen("NUM_MODEL = ")) == 0)
			{
				//���o��
				pStrcur += strlen("NUM_MODEL = ");
				//������̐擪��ݒ�
				strcpy(aStr, pStrcur);
				//�����񔲂��o��
				m_nNum = atoi(pStrcur);
				//������̐擪��ݒ�
				pStrcur = ReadLine(pFile, &aLine[0]);

				if (m_pWordPos == NULL)
				{
					m_pWordPos = new Word_Pos[m_nNum];
				}

				//CWordManager::SetWordAnswerNum(nAnswerNum);
			}

			//�I�u�W�F�N�g�ǂݍ���
			if (memcmp(pStrcur, "MODELSET", strlen("MODELSET")) == 0)
			{
				//���o��
				pStrcur += strlen("MODESET");
				//������̐擪��ݒ�
				pStrcur = ReadLine(pFile, &aLine[0]);
				//�ʒu
				if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
				{
					//���o��
					pStrcur += strlen("POS = ");
					//������̐擪��ݒ�
					strcpy(aStr, pStrcur);

					//��������Ԃ��Ă��炤
					nWord = PopString(pStrcur, &aStr[0]);
					//POS.X���
					ModelPos.x = (float)atof(pStrcur);
					//���������i�߂�
					pStrcur += nWord;

					//��������Ԃ��Ă��炤
					nWord = PopString(pStrcur, &aStr[0]);
					//POS.Y���
					ModelPos.y = (float)atof(pStrcur);
					//���������i�߂�
					pStrcur += nWord;

					//��������Ԃ��Ă��炤
					nWord = PopString(pStrcur, &aStr[0]);
					//POS.Z���
					ModelPos.z = (float)atof(pStrcur);
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);

					if (&m_pWordPos[nCntNum] != NULL)
					{	// �ݒ�
						m_pWordPos[nCntNum].pos = ModelPos;
						m_pWordPos[nCntNum].bUse = false;
						m_pWordPos[nCntNum].nCntPop = 0;

						nCntNum++;
					}
				}
			}
			//���f���𐶐�
			if (memcmp(pStrcur, "END_MODELSET", strlen("END_MODELSET")) == 0)
			{
				//CWord::Create(D3DXVECTOR3(380.0f, 0.0f, 380.0f), 12.0f, 12.0f, "WORD", 38);

			}
			//�X�N���v�g�̏I���
			if (memcmp(pStrcur, "END_SCRIPT	", strlen("END_SCRIPT")) == 0)
			{
				break;
			}
		}
	}

	//�t�@�C�������
	fclose(pFile);

	//WordCreate();	// �����̐���
}


//=============================================================================
//�@�t�@�C���ǂݍ��ݖ�������r��
//=============================================================================
char *CSetWord::ReadLine(FILE *pFile, char *pDst)
{
	while (1)
	{
		//�P�s���ǂݍ���
		fgets(&pDst[0], 256, pFile);

		//������̃f�[�^ ��r���镶���� ��r���镶����
		if (memcmp(pDst, "#", strlen("#")) == 0)
		{
			pDst += strlen("\n");
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pDst, "\t", strlen("\t")) == 0)
		{
			pDst += strlen("\t");
			while (1)
			{
				if (memcmp(pDst, "\t", strlen("\t")) == 0)
				{
					pDst += strlen("\t");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pDst, " ", strlen(" ")) == 0)
		{
			pDst += strlen(" ");
			while (1)
			{
				if (memcmp(pDst, " ", strlen(" ")) == 0)
				{
					pDst += strlen(" ");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pDst, "\n", strlen("\n")) == 0)
		{
			pDst += strlen("\n");
		}
		else
		{
			break;
		}
	}
	return pDst;
}

//=============================================================================
//�@�t�@�C���ǂݍ��ݐ擪��r��
//=============================================================================
char * CSetWord::GetLineTop(char * pStr)
{
	while (1)
	{
		//������̃f�[�^ ��r���镶���� ��r���镶����
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{
			pStr += strlen(" ");
			while (1)
			{
				if (memcmp(pStr, " ", strlen(" ")) == 0)
				{
					pStr += strlen(" ");
				}
				else
				{
					break;
				}
				break;
			}
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{
			pStr += strlen("\t");
			while (1)
			{
				if (memcmp(pStr, "\t", strlen("\t")) == 0)
				{
					pStr += strlen("\t");
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	return pStr;
}

//=============================================================================
//�@��������Ԃ�
//=============================================================================
int CSetWord::PopString(char * pStr, char * pDest)
{
	int nWord = 0;

	while (1)
	{	//���o��
		pStr += 1;
		nWord += 1;
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{	//���o��
			pStr = "\0";
			nWord += 1;
			break;
		}
		if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{	//���o��
			pStr = "\0";
			nWord += strlen("\t");
			break;
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pStr, "\n", strlen("\n")) == 0)
		{
			//���o��
			nWord += strlen("\n");
			break;
		}
	}
	strcpy(pDest, pStr);
	//������̐���Ԃ�
	return nWord;
}
