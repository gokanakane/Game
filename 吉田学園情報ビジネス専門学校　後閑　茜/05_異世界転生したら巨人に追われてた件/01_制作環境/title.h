//=============================================================================
//
// �^�C�g������ [title.h]
// Author : Shun Yokomichi
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		// �^�C�g��
#include "manager.h"	// �}�l�[�W���[

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLE_OBJ_MAX (1800)

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CRanking;
class CPress;
class CMeshField;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTitle
{// �^�C�g��
public:
	typedef struct
	{
		int				nCnter;					//	�I�u�W�F�N�g�̐��𐔂���
		D3DXVECTOR3		pos[TITLE_OBJ_MAX];			//	�I�u�W�F�N�g�|�W�V�����̐ݒ�
		int				nType[TITLE_OBJ_MAX];			//	�I�u�W�F�N�g��ނ̐ݒ�
		int				ncolType[TITLE_OBJ_MAX];		//	�I�u�W�F�N�g����̐ݒ�
		D3DXVECTOR3		size[TITLE_OBJ_MAX];			//	�I�u�W�F�N�g�T�C�Y�̐ݒ�
		bool			bUse[TITLE_OBJ_MAX];			// �g������
	}TEXTSTATE;

	typedef enum
	{
		TYPE_NONE = 0,	// �����Ȃ����
		TYPE_SCENEN000,	// ��������������
		TYPE_SCENEN001,	// �^�C�g�����S�\��
		TYPE_SCENEN002,	// �����L���O�\��
		TYPE_SCENE003,	// �N���W�b�g�\��
		TYPE_MAX		// ����
	}TYPE;
	CTitle();						// �R���X�g���N�^
	~CTitle();						// �f�X�g���N�^

	static HRESULT Load(void);		// ���[�h
	static void Unload(void);		// �A�����[�h

	void SetStage(void);

	HRESULT Init(void);				// ����������
	void Uninit(void);				// �I������
	void Update(void);				// �X�V����
	void Draw(void);				// �`�揈��
	void ObjectLoad(void);			// �I�u�W�F�N�g�̓ǂݍ���

private:

protected:
	int		m_nType;
	float	m_fColA;		// �J���[(���l)
	int		m_nCounter;		// ����
	TYPE	m_type;			// �^�C�v�̊Ǘ�
	CPress *m_pPress;

	// �ÓI�����o�ϐ�
	static CRanking *m_pRanking;		// �����L���O
	static CMeshField *m_pMeshField[8];	// ���b�V���t�B�[���h
	TEXTSTATE m_textState;		//	�e�L�X�g�ǂݍ��ޕϐ�[�ǂݍ��ރI�u�W�F�N�g�̎��]
};

#endif