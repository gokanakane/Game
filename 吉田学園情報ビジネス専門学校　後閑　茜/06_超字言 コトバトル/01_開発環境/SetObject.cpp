//---------------------------------------------------------------------
//	�I�u�W�F�N�g�z�u����(SetObject.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "SetObject.h"
#include "game.h"
#include "fade.h"
#include "sceneX.h"
#include "object.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_SPEED     (5.0f)
#define MODEL_DEPTH     (50.0f)

#define PLAYER_DEPTH	(15)		// �v���C���[�̕������p
#define PLAYER_HEIGHT	(50.0f)		// �v���C���[�̔w�̍���

#define FILE_NAME0				("data\\TEXT\\�@�B�X�e�[�W\\Machine_Stage_0.txt")

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------

//--------------------------------------------
//�I�u�W�F�N�g�N���X �R���X�g���N�^
//--------------------------------------------
CSetObject::CSetObject() : CScene(3, CScene::OBJTYPE_SETOBJECT)
{
}

//--------------------------------------------
//�I�u�W�F�N�g�N���X �f�X�g���N�^
//--------------------------------------------
CSetObject::~CSetObject()
{
}

//--------------------------------------------
//�I�u�W�F�N�g�̐���
//--------------------------------------------
CSetObject *CSetObject::Create()
{
	//�I�u�W�F�N�g�|�C���^
	CSetObject *pSetObject = NULL;
	if (pSetObject == NULL)
	{
		pSetObject = new CSetObject;
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
HRESULT CSetObject::Init()
{
	//�I�u�W�F�N�g��ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_SETOBJECT);

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̏I������
//=============================================================================
void CSetObject::Uninit(void)
{
	//����������(�I�u�W�F�N�g��j��)
	Release();
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V����
//=============================================================================
void CSetObject::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

	if (pInput->GetTrigger(DIK_RCONTROL) == true)
	{	//�t�@�C�����[�h
		//LoadFile(FILE_NAME0);
	}
}

//=============================================================================
// �I�u�W�F�N�g�̕`�揈��
//=============================================================================
void CSetObject::Draw(void)
{
	//�f�o�C�X���擾
	//CRenderer *pRenderer = CManager::GetRenderer();
	//LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	//D3DXMATRIX mtxParent;

}


//=============================================================================
// �I�u�W�F�N�g�̔z�u����ǂݍ���
//=============================================================================
void CSetObject::LoadFile(char *pFileName)
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
	int			nCollisionType;
	int			nGimmickType;

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
					ModelScale.x = (float)atof(pStrcur);

					//���������i�߂�
					pStrcur += nWord;
					//��������Ԃ��Ă��炤
					nWord = PopString(pStrcur, &aStr[0]);
					//������ϊ�
					ModelScale.y = (float)atof(pStrcur);

					//���������i�߂�
					pStrcur += nWord;
					//��������Ԃ��Ă��炤
					nWord = PopString(pStrcur, &aStr[0]);
					//������ϊ�
					ModelScale.z = (float)atof(pStrcur);
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);
				}
				//COLLISION��ǂݍ���
				if (memcmp(pStrcur, "COLLISION = ", strlen("COLLISION = ")) == 0)
				{
					//���o��
					pStrcur += strlen("COLLISION = ");
					//������̐擪��ݒ�
					strcpy(aStr, pStrcur);

					//��������Ԃ��Ă��炤
					nWord = PopString(pStrcur, &aStr[0]);
					//������ϊ�
					nCollisionType = (int)atoi(pStrcur);
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);
				}
				//�X�e�[�W�̃I�u�W�F�N�g�̎��
				if (memcmp(pStrcur, "GIMMICK = ", strlen("GIMMICK = ")) == 0)
				{
					//���o��
					pStrcur += strlen("GIMMICK = ");
					//������̐擪��ݒ�
					strcpy(aStr, pStrcur);

					//��������Ԃ��Ă��炤
					nWord = PopString(pStrcur, &aStr[0]);
					//������ϊ�
					nGimmickType = (int)atoi(pStrcur);
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);
				}
				if (memcmp(pStrcur, "BUSH = ", strlen("BUSH = ")) == 0)
				{
					//���o��
					pStrcur += strlen("BUSH = ");
					//������̐擪��ݒ�
					strcpy(aStr, pStrcur);

					//��������Ԃ��Ă��炤
					nWord = PopString(pStrcur, &aStr[0]);
					//������ϊ�
					nNumModel = (int)atoi(pStrcur);
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);
				}
			}
			//���f���𐶐�
			if (memcmp(pStrcur, "END_MODELSET", strlen("END_MODELSET")) == 0)
			{
				CObject::Create(ModelPos, ModelRot, ModelScale, (CSceneX::COLLISIONTYPE)nCollisionType, (CLoad::MODEL)nType, (CObject::GIMMICKTYPE)nGimmickType, nNumModel);
				//nNumModel++;
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
char *CSetObject::ReadLine(FILE *pFile, char *pDst)
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
char * CSetObject::GetLineTop(char * pStr)
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
int CSetObject::PopString(char * pStr, char * pDest)
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

//=============================================================================
//�@�I�u�W�F�N�g�̏����i�X�e�[�W�Z���N�g�p�j
//=============================================================================
void CSetObject::UnLoadObj(void)
{
	CScene *pScene = NULL;
	// �擪�̃I�u�W�F�N�g���擾
	pScene = CScene::GetTop(3);

	while(pScene!=NULL)
	{
		CScene *pSceneNext = pScene->GetNext();
		if (pScene->GetDeath() == false && pScene->GetObjType() == CScene::OBJTYPE_SCENEX)
		{// ���S�t���O�������Ă��Ȃ�����
			CObject *pWord = ((CObject*)pScene);		// CBulletBase�փL���X�g(�^�̕ύX)
				pWord->Uninit();
				pWord = NULL;
		}
		pScene = pSceneNext;
	};

}