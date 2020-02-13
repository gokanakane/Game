//=============================================================================
//
// �e�N�X�`������ [texture.cpp]
// Author : �ڍ� ������
//
//=============================================================================
#include "load.h"
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "debugProc.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_FILE_NAME				("data\\TEXT\\SetModel.txt")
#define WORDMODEL_FILE_NAME			("data\\TEXT\\SetWordOBJ.txt")

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPD3DXMESH *CLoad::m_pMesh = NULL;			// ���b�V�����i���_���j�ւ̃|�C���^
LPD3DXBUFFER *CLoad::m_pBuffMat = NULL;	// �}�e���A�����ւ̃|�C���^
DWORD *CLoad::m_nNumMat = 0;				// �}�e���A�����̐�
int	CLoad::m_nMaxModel = 0;
int	CLoad::m_nCntModel = 0;
char CLoad::m_apModelName[MODEL_MAX][256] = {NULL};
LPDIRECT3DTEXTURE9 *CLoad::m_pTexture[MODEL_MAX] = { NULL };
//const char *CLoad::m_apModelFilename[] =
//{// ���f��
//	"data\\MODEL\\car000.x",				//0
//	"data\\MODEL\\car001.x",				//1
//	"data\\MODEL\\box000.x",				//2
//};

//const char *CLoad::m_apModelFilename[] =
//{// ���f��
//	"data\\MODEL\\car000.x",				//0
//	"data\\MODEL\\car001.x",				//1
//	"data\\MODEL\\Desk.x",				//2 (��)
//	"data\\MODEL\\Pulin.x",				// �v����
//	"data\\MODEL\\Knife.x",				// �i�C�t
//	"data\\MODEL\\apple.x",				// �����S
//	"data\\MODEL\\box000.x",				//3
//	"data\\MODEL\\SampleModel_Player.x",	//3
//};


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLoad::CLoad()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLoad::~CLoad()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��ݏ���
//=============================================================================
HRESULT CLoad::LoadModel(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	if (m_pMesh != NULL)
	{
		// ���������������
		delete[] m_pMesh;
		m_pMesh = NULL;
	}

	if (m_pBuffMat != NULL)
	{
		// ���������������
		delete[] m_pBuffMat;
		m_pBuffMat = NULL;
	}

	if (m_nNumMat != NULL)
	{
		// ���������������
		delete[] m_nNumMat;
		m_nNumMat = NULL;
	}

	//�t�@�C���ǂݍ���
	LoadFile(MODEL_FILE_NAME);
	LoadFile(WORDMODEL_FILE_NAME);

	int nModelData = (sizeof m_apModelName);
	int nModelSize = (sizeof m_apModelName[0]);
	int nNumModel = nModelData / nModelSize;
	nNumModel = m_nMaxModel;
	// ���I�Ɋm��
	m_pMesh = new LPD3DXMESH[nNumModel];
	m_pBuffMat = new LPD3DXBUFFER[nNumModel];
	m_nNumMat = new DWORD[nNumModel];

	//���f���𐶐�
	for (int nCntModel = 0; nCntModel < MODEL_MAX; nCntModel++)
	{
		D3DXLoadMeshFromX(&m_apModelName[nCntModel][0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat[nCntModel],
			NULL,
			&m_nNumMat[nCntModel],
			&m_pMesh[nCntModel]);
	}


	for (int nCntModel = 0; nCntModel < MODEL_MAX; nCntModel++)
	{
		//�e�N�X�`��������
		TextureSetting(nCntModel);
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`���������
//=============================================================================
void CLoad::UnloadModel(void)
{
	//�|�C���^��NULL�`�F�b�N
	if (m_pTexture != NULL)
	{
		for (int nCntModel = 0; nCntModel < MODEL_MAX; nCntModel++)
		{
			for (int nCnt = 0; nCnt < (int)m_nNumMat[nCntModel]; nCnt++)
			{
				//�|�C���^���̃|�C���^��NULL�`�F�b�N
				if (m_pTexture[nCntModel][nCnt] != NULL)
				{
					//�e�N�X�`���j��
					m_pTexture[nCntModel][nCnt]->Release();
					m_pTexture[nCntModel][nCnt] = NULL;
				}
			}
			//���������J��
			delete[] m_pTexture[nCntModel];
		}
	}
	//NULL������
	*m_pTexture = NULL;



	if (m_pBuffMat != NULL)
	{
		// ���������������
		delete[] m_pBuffMat;
		m_pBuffMat = NULL;
	}

	if (m_nNumMat != NULL)
	{
		// ���������������
		delete[] m_nNumMat;
		m_nNumMat = NULL;
	}

	if (m_pMesh != NULL)
	{
		// ���������������
		delete[] m_pMesh;
		m_pMesh = NULL;
	}
}

//=============================================================================
// ���b�V���擾
//=============================================================================
LPD3DXMESH CLoad::GetMesh(int nIdx)
{
	return m_pMesh[nIdx];
}

//=============================================================================
// �}�e���A�����擾
//=============================================================================
LPD3DXBUFFER CLoad::GetBuffMat(int nIdx)
{
	return m_pBuffMat[nIdx];
}

//=============================================================================
// �}�e���A�����̐��擾
//=============================================================================
DWORD CLoad::GetNumMat(int nIdx)
{
	return m_nNumMat[nIdx];
}

//=============================================================================
// �e�N�X�`���̐ݒ�
//=============================================================================
void CLoad::TextureSetting(int nModel)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;
	//�}�e���A����񂩂�e�N�X�`���̎擾
	pMat = (D3DXMATERIAL*)m_pBuffMat[nModel]->GetBufferPointer();
	//�e�N�X�`�����}�e���A���̐������I�m��
	m_pTexture[nModel] = new LPDIRECT3DTEXTURE9[m_nNumMat[nModel]];
	//�}�e���A���̐���
	for (int nCntMatTex = 0; nCntMatTex < (int)m_nNumMat[nModel]; nCntMatTex++)
	{
		//NULL������ ���g�����
		m_pTexture[nModel][nCntMatTex] = NULL;

		if (pMat[nCntMatTex].pTextureFilename != NULL)
		{
			// �e�N�X�`���̐ݒ�
			D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
				pMat[nCntMatTex].pTextureFilename,			// �t�@�C���̖��O
				&m_pTexture[nModel][nCntMatTex]);		// �e�N�X�`���ւ̃|�C���^
		}
	}
}

//=============================================================================
// �e�N�X�`���̎擾����
//=============================================================================
LPDIRECT3DTEXTURE9 *CLoad::GetTexture(MODEL Model)
{
	return m_pTexture[Model];
}



//=============================================================================
// �I�u�W�F�N�g�̔z�u����ǂݍ���
//=============================================================================
void CLoad::LoadFile(char *pFileName)
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
	int nCntModel = 0;
	int nType = 0;			//���f���̎��
	D3DXVECTOR3 ModelPos;	//���f���̈ʒu
	D3DXVECTOR3 ModelRot;
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

			//�X�N���v�g�̏I���
			if (memcmp(pStrcur, "END_SCRIPT	", strlen("END_SCRIPT")) == 0)
			{
				break;
			}

			//������̃f�[�^ ��r���镶���� ��r���镶����
			if (memcmp(pStrcur, "NUM_MODEL = ", strlen("NUM_MODEL = ")) == 0)
			{
				//���o��
				pStrcur += strlen("NUM_MODEL = ");
				//������̐擪��ݒ�
				strcpy(aStr, pStrcur);
				//�����񔲂��o��
				nNumModel = atoi(pStrcur);
				m_nMaxModel += nNumModel;

				// ���I�Ɋm��
				//m_apModelName[0] = "test";
				//m_apModelName = new LPSTR[10];
				//m_apModelName[0] = "TEST0";
				//m_apModelName2 = new char[10];
				//m_apModelName2[0] = new char[10][50];
			}

			if (memcmp(pStrcur, "MODEL_FILENAME = ", strlen("MODEL_FILENAME = ")) == 0)
			{
				//���o��
				pStrcur += strlen("MODEL_FILENAME = ");

				//�������ݒ�
				strcpy(aStr, pStrcur);

				//�K�v�ȕ�����̍Ō�̕����܂ł̕������𐔂���
				int nNullNum = PopString(pStrcur, &aStr[0]);

				//����������߂�
				strcpy(aStr, pStrcur);

				//�Ō�̕�����NULL����������
				aStr[nNullNum - 2] = '\0';

				//�Ώۂ̕����񂩂甲���o��
				strcpy(&m_apModelName[m_nCntModel][0], aStr);

				//��������i�[
				//strcpy(&m_apModelName2[m_nCntModel], aStr);
				//	"data\\MODEL\\car000.x",				//0
				//	"data\\MODEL\\car001.x",				//1
				//	"data\\MODEL\\box000.x",				//2

				m_nCntModel += 1;
			}
		}
	}

	//�t�@�C�������
	fclose(pFile);
}


//=============================================================================
//�@�t�@�C���ǂݍ��ݖ�������r��
//=============================================================================
char *CLoad::ReadLine(FILE *pFile, char *pDst)
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
char * CLoad::GetLineTop(char * pStr)
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
int CLoad::PopString(char * pStr, char * pDest)
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
