//=============================================================================
//
// �e�N�X�`���N���X [texture.cpp] {CTexture}
// Author : Kodama Yuto
//
//
//	����ɕҏW���Ȃ����ƁI�I(�R�����g��OK)
//
//=============================================================================
#include "texture.h"
#include "manager.h"

//==================================================================
// �ÓI�����o�ϐ�
//==================================================================
std::vector<CTexture::TexData> CTexture::m_TexData;

//==================================================================
// �}�N����`
//==================================================================
#define TEXDATA ("data/TEXT/TexLoad.txt")		//�e�L�X�g�̃A�h���X

//==================================================================
// �e�N�X�`���ǂݍ���
//==================================================================
HRESULT CTexture::Load(void) {
	//�e�N�X�`���̃f�[�^�ǂݍ���
	//�ϐ��錾
	CRenderer *pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	FILE* pFile = NULL;		// �t�@�C���|�C���^
	char ReadText[256];		// �ǂݍ��񂾕���������Ă���
	char HeadText[256];		// ��r�p
	char DustBox[256];		// �g�p���Ȃ����̂����Ă���
	int nCntTexData = 0;	// �ǂݍ��ݐ��J�E���^

	TexData OneTexData;			//tex�Ƀf�[�^�����邽�߂̕ϐ�
	m_TexData.clear();


	//�t�@�C���I�[�v��
	pFile = fopen(TEXDATA, "r");

	if (pFile != NULL)
	{//�t�@�C�����J����Ă����
		while (strcmp(HeadText, "START_LOAD") != 0)
		{// "START_LOAD" ���ǂݍ��܂��܂ŌJ��Ԃ��������ǂݎ��
			fgets(ReadText, sizeof(ReadText), pFile);
			sscanf(ReadText, "%s", &HeadText);
		}
		if (strcmp(HeadText, "START_LOAD") == 0)
		{// "START_LOAD" ���ǂݎ�ꂽ�ꍇ�A�����J�n
			while (strcmp(HeadText, "END_LOAD") != 0)
			{// "END_LOAD" ���ǂݍ��܂��܂ŌJ��Ԃ��������ǂݎ��
				fgets(ReadText, sizeof(ReadText), pFile);
				sscanf(ReadText, "%s", &HeadText);

				if (strcmp(HeadText, "\n") == 0)
				{// ������̐擪�� [\n](���s) �̏ꍇ�������Ȃ�

				}
				else if (strcmp(HeadText, "DATA") == 0)
				{// "DATA" ���ǂݎ�ꂽ�ꍇ

					//DATA�����̃f�[�^���X�y�[�X��؂�œǂݍ���
					sscanf(ReadText, "%s %c %d %s %s",
						&DustBox, &DustBox,
						&OneTexData.nID,
						&OneTexData.TexAddress,
						&OneTexData.TexNameTag);

					//�ǂݎ�����e�N�X�`����vector�z��̒��ɓ����
					m_TexData.emplace_back(OneTexData);
				}
			}
		}

		//�t�@�C���N���[�Y
		if (pFile != NULL)
		{
			fclose(pFile);
			pFile = NULL;
		}

		if (m_TexData.size() > 0)
		{
			//�e�N�X�`���f�[�^�̏�����
			for (auto itr = m_TexData.begin(); itr != m_TexData.end(); ++itr)	//auto itr = vector�z����̈ʒu���w�������|�C���^�̂悤�Ȃ���(�C�e���[�^)
			{
				itr->pTexture = NULL;
			}
		}

	}
	else
	{//�����ɓ�������G���[(���̃t�@�C�����Ȃ�or�J���Ȃ�)
		MessageBox(NULL, "�e�N�X�`�����t�@�C�����J���܂���ł����B", NULL, MB_OK);
		return S_FALSE;
	}

	return S_OK;
}

//==================================================================
// �e�N�X�`�����
//==================================================================
void CTexture::Unload(void)
{
	//�e�N�X�`�����
	ReleaseAll();

	//�e�N�X�`���z��̏�����
	m_TexData.clear();
	m_TexData.shrink_to_fit();
}
//==================================================================
// �e�N�X�`���擾
//==================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(const int nID) {			//ID
	if (m_TexData.size() > 0)
	{//�e�N�X�`������0�ȏ�Ȃ�(����if�����ȗ����Ă�find�͓������A0�̎���find�̏������ȗ����邽�߂ɖ����I�ɂ���)
		auto result = std::find(m_TexData.begin(), m_TexData.end(), nID);

		if (result != m_TexData.end())
		{//ID����v������
			if (result->pTexture == NULL)
			{//�܂��e�N�X�`��������Ă��Ȃ���΍��
				Create(result->TexAddress, result->pTexture);
			}
			return result->pTexture;
		}
	}
	return NULL;
}
LPDIRECT3DTEXTURE9 CTexture::GetTexture(const LPCSTR Tag) {		//�^�O
	if (m_TexData.size() > 0)
	{//�e�N�X�`������0�ȏ�Ȃ�(����if�����ȗ����Ă�find�͓������A0�̎���find�̏������ȗ����邽�߂ɖ����I�ɂ���)
		auto result = std::find(m_TexData.begin(), m_TexData.end(), Tag);
		if (result != m_TexData.end())
		{//�^�O����v������
			if (result->pTexture == NULL)
			{//�܂��e�N�X�`��������Ă��Ȃ���΍��
				Create(result->TexAddress, result->pTexture);
			}
			return result->pTexture;
		}
	}
	return NULL;
}
//==================================================================
// ���ꂽ�e�N�X�`���̑S���
//==================================================================
void CTexture::ReleaseAll(void)
{
	if (m_TexData.size() > 0)
	{//�e�N�X�`������0�ȏ�Ȃ�
		for (auto itr = m_TexData.begin(); itr != m_TexData.end(); ++itr)
		{//�O�u�C���N�������g�̕�����u�C���N�������g��荂���炵���̂ł�������̗p
			//�e�N�X�`���̉��
			if (itr->pTexture != NULL)
			{
				itr->pTexture->Release();
				itr->pTexture = NULL;
			}
		}
	}
}

//==================================================================
// �g��Ȃ��Ȃ����e�N�X�`���̉��
//==================================================================
void CTexture::Release(const int nID)//ID
{
	if (m_TexData.size() > 0)
	{//�e�N�X�`������0�ȏ�Ȃ�(����if�����ȗ����Ă�find�͓������A0�̎���find�̏������ȗ����邽�߂ɖ����I�ɂ���)
		auto result = std::find(m_TexData.begin(), m_TexData.end(), nID);

		if (result != m_TexData.end())
		{//ID����v������
			if (result->pTexture != NULL)
			{//�e�N�X�`��������Ă���Ȃ�
				result->pTexture->Release();
				result->pTexture = NULL;
			}
		}
	}
}
void CTexture::Release(const LPCSTR Tag)//�^�O
{
	if (m_TexData.size() > 0)
	{//�e�N�X�`������0�ȏ�Ȃ�(����if�����ȗ����Ă�find�͓������A0�̎���find�̏������ȗ����邽�߂ɖ����I�ɂ���)
		auto result = std::find(m_TexData.begin(), m_TexData.end(), Tag);
		if (result != m_TexData.end())
		{//�^�O����v������
			if (result->pTexture != NULL)
			{//�e�N�X�`��������Ă���Ȃ�
				result->pTexture->Release();
				result->pTexture = NULL;
			}
		}
	}
}

//==================================================================
// �e�N�X�`������
//==================================================================
void CTexture::Create(LPCSTR address, LPDIRECT3DTEXTURE9& pTexture)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	if (pTexture == NULL)
	{//�e�N�X�`���̐���
		D3DXCreateTextureFromFile(pDevice,
			address,
			&pTexture);
	}
}

//==================================================================
// �e�N�X�`�����J�E���g
//==================================================================
int CTexture::GetTexNum(bool bCreate)
{
	int nTexNum = m_TexData.size();	//�e�N�X�`���̐�(�t�@�C������ǂݍ��񂾃e�N�X�`���̐��ŏ�����)

	if (bCreate == true)
	{//�e�N�X�`���|�C���^��������̂����J�E���g����Ȃ�
		nTexNum = 0;		//��������0�ŏ�����

		if (m_TexData.size() > 0)
		{//�ǂݍ��񂾃e�N�X�`������0�ȏ�Ȃ�

			for (auto itr = m_TexData.begin(); itr != m_TexData.end(); ++itr)
			{//Texture������Ă����++
				if (itr->pTexture != NULL)
				{
					++nTexNum;
				}
			}
		}
	}
	return nTexNum;
}
