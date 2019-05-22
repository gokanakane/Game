//=============================================================================
//
// �Q�[������ [game.h]
// Author : Eisuke Sakagawa
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		// ���C��
#include "manager.h"	// �}�l�[�W���[

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define OBJ_MAX (1800)
#define TEXT_OBJ_MAX (3)		//	�e�L�X�g�̒��̃I�u�W�F�N�g�̍ő吔

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPlayer;
class CEnemy;
class CMeshField;
class CMeshRiver;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGame
{// �Q�[��
public:
	typedef struct
	{
		int				nCnter;					//	�I�u�W�F�N�g�̐��𐔂���
		D3DXVECTOR3		pos[OBJ_MAX];			//	�I�u�W�F�N�g�|�W�V�����̐ݒ�
		int				nType[OBJ_MAX];			//	�I�u�W�F�N�g��ނ̐ݒ�
		int				ncolType[OBJ_MAX];		//	�I�u�W�F�N�g����̐ݒ�
		D3DXVECTOR3		size[OBJ_MAX];			//	�I�u�W�F�N�g�T�C�Y�̐ݒ�
		bool			bUse[OBJ_MAX];			// �g������
	}TEXTSTATE;

	typedef enum
	{	// �Q�[���̏��(CLEAR & GameOver)
		MODE_NONE = 0,
		MODE_GAMEOVER000,		// ���l�ɕ߂܂�
		MODE_GAMEOVER001,		// �̗̓[��
		MODE_GAMECLEAR,			// ����
		MODE_MAX
	}MODEGAME;

	static const int m_MeshFieldMax = 8;
	static const int m_MeshRiverMax = 4;

	CGame();						// �R���X�g���N�^
	~CGame();						// �f�X�g���N�^

	static HRESULT Load(void);		// ���[�h
	static void Unload(void);		// �A�����[�h

	HRESULT Init(void);				// ����������
	void Uninit(void);				// �I������
	void Update(void);				// �X�V����
	void Draw(void);				// �`�揈��

	void ObjectLoad(void);			// �I�u�W�F�N�g�̓ǂݍ���
	void SetStage(void);
	void PlayES(int nSoundNum);		// �T�E���h�̔ԍ��Ŋ������o��

	static void SetPlayer(void) { m_pPlayer = NULL; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static void SetEnemy(void) { m_pEnemy = NULL; }
	static CEnemy *GetEnemy(void) { return m_pEnemy; }
	static void SetMeshField(CMeshField *pMeshField)
	{
		for (int nCount = 0; nCount < m_MeshFieldMax; nCount++)
		{
			if (m_pMeshField[nCount] == pMeshField)
			{
				m_pMeshField[nCount] = NULL;
				break;
			}
		}
	}
	static CMeshField *GetMeshField(int nNum) { return m_pMeshField[nNum]; }
	static CMeshRiver *GetMeshRiver(int nNum) { return m_pMeshRiver[nNum]; }

	// �Q�[���̏�Ԏ擾�Ɛݒ�
	static void SetGame(MODEGAME pGame) { m_game = pGame; };
	static MODEGAME GetGame() { return m_game; };

private:
	static CPlayer *m_pPlayer;
	static CEnemy *m_pEnemy;
	static CMeshField *m_pMeshField[m_MeshFieldMax];
	static CMeshRiver *m_pMeshRiver[m_MeshRiverMax];

	TEXTSTATE m_textState[TEXT_OBJ_MAX];		//	�e�L�X�g�ǂݍ��ޕϐ�[�ǂݍ��ރI�u�W�F�N�g�̎��]
	static MODEGAME m_game;

	int m_nCounter;

protected:

};

#endif