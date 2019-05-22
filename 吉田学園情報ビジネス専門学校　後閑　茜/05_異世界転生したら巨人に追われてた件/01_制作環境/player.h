//=============================================================================
//
// �v���C���[���� [player.h]
// Author : Eisuke Sakagawa
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		// ���C��
#include "scene.h"		// �V�[��
#include "motion.h"		// ���[�V����

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CModel;			// ���f��
class CMotion;			// ���[�V����

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayer : public CScene
{// �v���C���[�i�e�FCScene�j
public:
	typedef enum
	{
		STATE_NONE = 0,
		STATE_DAMAGE,
		STATE_DEATH,
		STATE_MAX
	}STATE;

	typedef struct
	{
		char cFileName[256];
		int nIndex;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
	}MODEL_INFO;

	CPlayer();										// �R���X�g���N�^
	~CPlayer();										// �f�X�g���N�^

	static HRESULT Load(void);						// ���[�h
	static void Unload(void);						// �A�����[�h
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		// ����
	static bool GetFalling(void) { return m_bFalling; }		//Life���ŗ�������Ԃ��ǂ���������Ƃ��Ɏg�p����B

	HRESULT Init(void);										// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��

	void Setpos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 Getpos(void) { return m_pos; }

	static char *ReadFile(FILE *pFile, char *pDest)
	{
		fgets(pDest, 256, pFile);

		if (memcmp(pDest, "#", strlen("#")) == 0 || memcmp(pDest, "\n", strlen("\n")) == 0)
		{
			ReadFile(pFile, pDest);
		}
		else
		{
			do
			{
				if (memcmp(pDest, "#", strlen("#")) == 0 || memcmp(pDest, "\n", strlen("\n")) == 0)
				{
					ReadFile(pFile, pDest);
				}
				else if (memcmp(pDest, " ", strlen(" ")) == 0)
				{
					wsprintf(&pDest[0], &pDest[strlen(" ")]);
				}
				else if (memcmp(pDest, "\t", strlen("\t")) == 0)
				{
					wsprintf(&pDest[0], &pDest[strlen("\t")]);
				}
				else if (memcmp(pDest, "�@", strlen("�@")) == 0)
				{
					wsprintf(&pDest[0], &pDest[strlen("�@")]);
				}
			} while (
				memcmp(pDest, "#", strlen("#")) == 0 || memcmp(pDest, "\n", strlen("\n")) == 0 ||
				memcmp(pDest, " ", strlen(" ")) == 0 || memcmp(pDest, "\t", strlen("\t")) == 0 ||
				memcmp(pDest, "�@", strlen("�@")) == 0);
		}

		return pDest;
	}
	static char *PopString(char *pSrc)
	{
		do
		{
			if (memcmp(pSrc, "=", strlen("=")) == 0)
			{
				wsprintf(&pSrc[0], &pSrc[strlen("=")]);
			}
			else if (memcmp(pSrc, " ", strlen(" ")) == 0)
			{
				wsprintf(&pSrc[0], &pSrc[strlen(" ")]);
			}
			else if (memcmp(pSrc, "\t", strlen("\t")) == 0)
			{
				wsprintf(&pSrc[0], &pSrc[strlen("\t")]);
			}
			else if (memcmp(pSrc, "�@", strlen("�@")) == 0)
			{
				wsprintf(&pSrc[0], &pSrc[strlen("�@")]);
			}
		} while (
			memcmp(pSrc, "=", strlen("=")) == 0 ||
			memcmp(pSrc, " ", strlen(" ")) == 0 || memcmp(pSrc, "\t", strlen("\t")) == 0 ||
			memcmp(pSrc, "�@", strlen("�@")) == 0);

		int nCntEnd = 0;
		char cStr[256];
		strcpy(cStr, pSrc);

		do
		{
			if (memcmp(cStr, "#", strlen("#")) == 0)
			{
				wsprintf(&cStr[0], &cStr[strlen("#")]);
			}
			else if (memcmp(cStr, "\n", strlen("\n")) == 0)
			{
				wsprintf(&cStr[0], &cStr[strlen("\n")]);
			}
			else if (memcmp(cStr, " ", strlen(" ")) == 0)
			{
				wsprintf(&cStr[0], &cStr[strlen(" ")]);
			}
			else if (memcmp(cStr, "\t", strlen("\t")) == 0)
			{
				wsprintf(&cStr[0], &cStr[strlen("\t")]);
			}
			else if (memcmp(cStr, "�@", strlen("�@")) == 0)
			{
				wsprintf(&cStr[0], &cStr[strlen("�@")]);
			}
			else
			{
				wsprintf(&cStr[0], &cStr[1]);
			}

			nCntEnd++;
		} while (
			memcmp(cStr, "#", strlen("#")) != 0 && memcmp(cStr, "\n", strlen("\n")) != 0 &&
			memcmp(cStr, " ", strlen(" ")) != 0 && memcmp(cStr, "\t", strlen("\t")) != 0 &&
			memcmp(cStr, "�@", strlen("�@")) != 0);

		strcpy(cStr, pSrc);
		wsprintf(&pSrc[0], &pSrc[nCntEnd]);
		cStr[nCntEnd] = '\0';

		return cStr;
	}

private:
	static int					m_MaxModel;			// ���f����
	static int					m_MaxAnim;			// �A�j���[�V������

	static LPDIRECT3DTEXTURE9	**m_pTexture;		// �e�N�X�`�����ւ̃|�C���^
	static LPD3DXMESH			*m_pMesh;			// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER			*m_pBuffMat;		// �}�e���A�����ւ̃|�C���^
	static DWORD				*m_nNumMat;			// �}�e���A�����̐�

	static MODEL_INFO			*m_ModelInfo;
	static CMotion::ANIM_INFO	*m_AnimInfo;

	static bool					m_bFalling;			// ���������ǂ������m�F����

	D3DXMATRIX					m_mtxWorld;			// ���[���h�}�g���b�N�X
	CModel						*m_pModel;			// ���f��
	CMotion						*m_pMotion;			// ���[�V����
	int							m_AnimEditCounter;

	STATE						m_state;
	int							m_nCntState;

	bool						m_bStart;			// �X�^�[�g
	bool						m_bEnd;				//	�I��
	int							m_nCntStart;

	D3DXVECTOR3					m_vtxMax;			// ����MAX
	D3DXVECTOR3					m_vtxMin;			// ����MIN
	D3DXVECTOR3					m_pos;				// �ʒu
	D3DXVECTOR3					m_posOld;			// �ʒu�O��
	D3DXVECTOR3					m_rot;				// ����
	D3DXVECTOR3					m_move;				// �ړ���
	float						m_frotDest;			// �ڕW����
	bool						m_bJump;			// �W�����v
	bool						m_bMove;			// �ړ��ł��邩
	bool						m_bSlip;			// �����Ă��邩
	float						m_fSliprot;			// �����Ă������
	float						m_fDownSpeed;		// ����
	int							m_nWallJump;		// �ǃL�b�N�J�E��
	bool						m_bWallJump;		// �ǃL�b�N���Ă�
	float						m_bWallJumpmove;	// �ǃL�b�N�ړ���

	bool						m_bmoveUp;			// �A�C�e���ŃX�s�[�h���オ���Ă����邩�ǂ���
	int							m_nMoveCounter;		// �X�s�[�hUP���鎞�Ԃ̃J�E���^�[
	int							m_SoundCounter;		// �T�E���h�J�E���^
	int							m_nCntEffect;

	bool						m_bClear;			//�Q�[���N���A�̃t���O

	float						m_shadowHeight;

protected:

};

#endif