//=============================================================================
//
// �V�[������ [scene.h]
// Author : �ڍ� ������
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_OBJECT		(256)	// �e�N�X�`���̐�
#define NUM_PRIORITY	(8)		// �D�揇�ʂ̐�
#define SCENEX_PRIORITY	(3)
#define ENEMY_PRIORITY	(2)
#define PLAYER_PRIORITY	(2)
#define CPU_PRIORITY	(2)
#define SELECT_PRIORITY	(3)
#define SHADOW_PRIORITY	(6)

//========================================
// �N���X�̒�`
//========================================
//=====================
// �I�u�W�F�N�g�N���X
//=====================
class CScene
{
public:
	typedef enum
	{// �I�u�W�F�N�g�̎��
		OBJTYPE_NONE = 0,
		OBJTYPE_SCENE2D,	// 2D�|���S��
		OBJTYPE_SCENE3D,	// 3D�|���S��
		OBJTYPE_SCENEX,		// ���f��
		OBJTYPE_BILLBOARD,	// �r���{�[�h
		OBJTYPE_MESH_FIELD,	// ���b�V���t�B�[���h
		OBJTYPE_MESH_SPHERE,// �����b�V��
		OBJTYPE_SETOBJECT,	// �I�u�W�F�N�g�z�u
		OBJTYPE_PLAYER,
		OBJTYPE_ENEMY,
		OBJTYPE_SHADOW,
		OBJTYPE_UI,
		OBJTYPE_EFFECT,
		OBJTYPE_ANIM,
		OBJTYPE_WALL,
		OBJTYPE_FIELD,
		OBJTYPE_PARTICLE,
		OBJTYPE_PAUSE,
		OBJTYPE_WORD,		// ����
		OBJTYPE_WORD_EFFECT,	//
		OBJTYPE_MODESELECT,
		OBJTYPE_TIME,		// ����
		OBJTYPE_TUTOTIME,
		OBJTYPE_BULLET,
		OBJTYPE_POINT,		// �|�C���g
		OBJTYPE_EXPLOSION,	// ����
		OBJTYPE_ORBIT,		// �O��
		OBJTYPE_AVOIDUI,	// �v���C���[����UI
		OBJTYPE_BILLBOARDUI,// �r���{�[�hUI
		OBJTYPE_CROWN,		// ����
		OBJTYPE_BULLETUI,	// �e����UI
		OBJTYPE_MISSILEUI,	// �~�T�C������UI
		OBJTYPE_MAX			// ����
	} OBJTYPE;

	CScene(int nPriority = 3, OBJTYPE objType = OBJTYPE_NONE);	// �R���X�g���N�^
	virtual ~CScene();											// �f�X�g���N�^

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	//virtual void SetScene(D3DXVECTOR3 pos) = 0;

	static void ReleseAll(void);								// �S�ẴI�u�W�F�N�g�̉��
	static void UpdeteAll(void);								// �S�ẴI�u�W�F�N�g�̍X�V
	static void DrawAll(int nCamera);									// �S�ẴI�u�W�F�N�g�̕`��
	static CScene *GetTop(int nPriority);						// �擪�̃I�u�W�F�N�g���擾
	CScene *GetNext(void);										// ���̃I�u�W�F�N�g�̃|�C���^���擾
	bool GetDeath(void);										// ���S�t���O���擾
	OBJTYPE GetObjType(void);									// �I�u�W�F�N�g�̎�ނ̎擾
	void SetObjType(OBJTYPE objType);							// �I�u�W�F�N�g�̎�ނ̐ݒ�
	int GetPriority(void);
	static void SetbPause(bool bPause) { m_bPause = bPause;	};
	static bool GetbPause(void) { return m_bPause; };

protected:
	void Release(void);											// ���S�t���O�𗧂Ă�

	int m_nCount;												//�ėp�J�E���^
private:
	void DeleteAll(void);										// ���S�t���O���������I�u�W�F�N�g������

	static CScene *m_apTop[NUM_PRIORITY];						// �擪�I�u�W�F�N�g�ւ̃|�C���^
	static CScene *m_apCur[NUM_PRIORITY];						// ���݁i�Ō���j�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene *m_pPrev;											// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene *m_pNext;											// ���̃I�u�W�F�N�g�ւ̃|�C���^
	bool m_bDeath;												// ���S�t���O
	static int m_nNumAll;										// �G�̑��� �w�ÓI�����o�ϐ��x
	int m_nID;													// �������g��ID
	int m_nPriority;											// �D�揇�ʂ̔ԍ�
	static int m_nNumPriority[NUM_PRIORITY];					// ���̗D�揇�ʂɂ���I�u�W�F�N�g�̐�
	OBJTYPE m_objType;											// �I�u�W�F�N�g�̎��
	static bool	m_bPause;										// �|�[�Y
	static bool m_bDebug2Ddraw;									// 2D�\���̃t���O

};

#endif