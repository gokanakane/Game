//=============================================================================
//
// Text�ǂݍ��ݏ��� [loadText.cpp]
// Author : Shun Yokomichi
//
//=============================================================================
#include "loadText.h"
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "debugProc.h"
#include "manager.h"
#include "word_manager.h"
#include "bullet.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FILE_NAME				("data\\TEXT\\WordManager.txt")

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLoadText::CLoadText()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLoadText::~CLoadText()
{
}


//=============================================================================
// �I�u�W�F�N�g�̔z�u����ǂݍ���
//=============================================================================
void CLoadText::LoadFile(void)
{
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
	D3DXVECTOR3 ModelPos;	//���f���̈ʒu
	D3DXVECTOR3 ModelRot;
	D3DXVECTOR3 ModelScale;
	D3DXVECTOR3 AnswerNum;
	int			nCollisionType;
	int			nAnswerNum;
	int			nAnswerModel;
	int			nPoint;

	//�t�@�C�����J�� �ǂݍ���
	pFile = fopen(FILE_NAME, "r");
	//NULL�`�F�b�N
	if (pFile != NULL)
	{
		while (1)
		{
			//������̐擪��ݒ�
			pStrcur = ReadLine(pFile, &aLine[0]);
			//����������o��
			strcpy(aStr, pStrcur);

			if (memcmp(pStrcur, "ANSWERNUM = ", strlen("ANSWERNUM = ")) == 0)
			{
				//���o��
				pStrcur += strlen("ANSWERNUM = ");
				//������̐擪��ݒ�
				strcpy(aStr, pStrcur);
				//�����񔲂��o��
				nAnswerNum = atoi(pStrcur);
				//������̐擪��ݒ�
				pStrcur = ReadLine(pFile, &aLine[0]);
				CWordManager::SetWordAnswerNum(nAnswerNum);
			}
			//�I�u�W�F�N�g�ǂݍ���
			if (memcmp(pStrcur, "MODELSET", strlen("MODELSET")) == 0)
			{
				//���o��
				pStrcur += strlen("MODELSET");
				//������̐擪��ݒ�
				pStrcur = ReadLine(pFile, &aLine[0]);
				//���
				if (memcmp(pStrcur, "TYPE = ", strlen("TYPE = ")) == 0)
				{
					//���o��
					pStrcur += strlen("TYPE = ");
					//������̐擪��ݒ�
					strcpy(aStr, pStrcur);
					//�����񔲂��o��
					nType = atoi(pStrcur);
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);
				}
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
				}
				//ROT��ǂݍ���
				if (memcmp(pStrcur, "ROT = ", strlen("ROT = ")) == 0)
				{
					//���o��
					pStrcur += strlen("ROT = ");
					//������̐擪��ݒ�
					strcpy(aStr, pStrcur);

					//��������Ԃ��Ă��炤
					nWord = PopString(pStrcur, &aStr[0]);
					//������ϊ�
					ModelRot.x = (float)atof(pStrcur);
					//���������i�߂�
					pStrcur += nWord;
					//��������Ԃ��Ă��炤
					nWord = PopString(pStrcur, &aStr[0]);
					//������ϊ�
					ModelRot.y = (float)atof(pStrcur);

					//���������i�߂�
					pStrcur += nWord;
					//��������Ԃ��Ă��炤
					nWord = PopString(pStrcur, &aStr[0]);
					//������ϊ�
					ModelRot.z = (float)atof(pStrcur);
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);

					//�p�x��-�΁`�΂ɕ␳����
					CUtilityMath::RotateNormarizePI(ModelRot);
				}
				//SCALE��ǂݍ���
				if (memcmp(pStrcur, "SCALE = ", strlen("SCALE = ")) == 0)
				{
					//���o��
					pStrcur += strlen("SCALE = ");
					//������̐擪��ݒ�
					strcpy(aStr, pStrcur);

					//��������Ԃ��Ă��炤
					nWord = PopString(pStrcur, &aStr[0]);

					//������ϊ�
					ModelScale.x = fabsf((float)atof(pStrcur)); //�}�C�i�X������Ȃ��悤�ɐ�Βl���g��

					//���������i�߂�
					pStrcur += nWord;
					//��������Ԃ��Ă��炤
					nWord = PopString(pStrcur, &aStr[0]);
					//������ϊ�
					ModelScale.y = fabsf((float)atof(pStrcur));//�}�C�i�X������Ȃ��悤�ɐ�Βl���g��

					//���������i�߂�
					pStrcur += nWord;
					//��������Ԃ��Ă��炤
					nWord = PopString(pStrcur, &aStr[0]);
					//������ϊ�
					ModelScale.z = fabsf((float)atof(pStrcur));//�}�C�i�X������Ȃ��悤�ɐ�Βl���g��
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);
				}
				//COLLISION��ǂݍ���
				if (memcmp(pStrcur, "BULLETTYPE = ", strlen("BULLETTYPE = ")) == 0)
				{
					//���o��
					pStrcur += strlen("BULLETTYPE = ");
					//������̐擪��ݒ�
					strcpy(aStr, pStrcur);

					//��������Ԃ��Ă��炤
					nWord = PopString(pStrcur, &aStr[0]);
					//������ϊ�
					nCollisionType = (int)atoi(pStrcur);
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);

					if (nCollisionType >= (int)CModelBullet::TYPE_MAX||
						nCollisionType < 0)
					{//�e�^�C�v�ɕςȐ��l�������Ă����ꍇ�̓m�[�}���e�ɕς���(�G���[�h�~)
						nCollisionType = (int)CModelBullet::TYPE_NORMAL;
					}
				}
				//�����̐���
				if (memcmp(pStrcur, "ANSWER = ", strlen("ANSWER = ")) == 0)
				{
					//���o��
					pStrcur += strlen("ANSWER = ");
					//������̐擪��ݒ�
					strcpy(aStr, pStrcur);

					//��������Ԃ��Ă��炤
					nWord = PopString(pStrcur, &aStr[0]);
					//POS.X���
					AnswerNum.x = (float)atof(pStrcur);
					//���������i�߂�
					pStrcur += nWord;

					//��������Ԃ��Ă��炤
					nWord = PopString(pStrcur, &aStr[0]);
					//POS.Y���
					AnswerNum.y = (float)atof(pStrcur);
					//���������i�߂�
					pStrcur += nWord;

					//��������Ԃ��Ă��炤
					nWord = PopString(pStrcur, &aStr[0]);
					//POS.Z���
					AnswerNum.z = (float)atof(pStrcur);
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);
				}
				if (memcmp(pStrcur, "ANSWERMODEL = ", strlen("ANSWERMODEL = ")) == 0)
				{
					//���o��
					pStrcur += strlen("ANSWERMODEL = ");
					//������̐擪��ݒ�
					strcpy(aStr, pStrcur);
					//�����񔲂��o��
					nAnswerModel = atoi(pStrcur);
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);
				}
				if (memcmp(pStrcur, "POINT = ", strlen("POINT = ")) == 0)
				{
					//���o��
					pStrcur += strlen("POINT = ");
					//������̐擪��ݒ�
					strcpy(aStr, pStrcur);
					//�����񔲂��o��
					nPoint = atoi(pStrcur);
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);
				}
			}
			//���f���𐶐�
			if (memcmp(pStrcur, "END_MODELSET", strlen("END_MODELSET")) == 0)
			{
				//CSetObject::Create(ModelPos, ModelRot, D3DXVECTOR3(0.0f, 0.0f, 0.0f)
				//	, (CSetObject::MODELTYPE)nType, CSetObject::MOVETYPE_NONE, 1);
				//CObject::Create(ModelPos, ModelRot, ModelScale, (CSceneX::COLLISIONTYPE)nCollisionType, (CLoad::MODEL)nType);
				CWordManager::SetWordLoad(nType, AnswerNum, ModelScale, ModelRot, nCollisionType, nAnswerModel, nPoint);
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
}


//=============================================================================
//�@�t�@�C���ǂݍ��ݖ�������r��
//=============================================================================
char *CLoadText::ReadLine(FILE *pFile, char *pDst)
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
char * CLoadText::GetLineTop(char * pStr)
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
int CLoadText::PopString(char * pStr, char * pDest)
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
