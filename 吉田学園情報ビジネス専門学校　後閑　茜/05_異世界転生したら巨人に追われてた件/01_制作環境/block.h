//=============================================================================
//
// �u���b�N���� [block.h]
// Author : Eisuke Sakagawa
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		// ���C��
#include "scenex.h"		// �V�[��x

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBlock : public CSceneX
{// �u���b�N�e�FCSceneX�j
public:
	typedef enum
	{
		MODELTYPE_BOX_R = 0,	// ��(�u���b�N)
		MODELTYPE_BOX_W_1,		// ��
		MODELTYPE_BOX_W_2,		// ��(�w�i�p)
		MODELTYPE_SKY,			// �󒆏�(�����̗p����)
		MODELTYPE_ICE,			// ���鏰
		MODELTYPE_LOG,			// �ۑ�
		MODELTYPE_SEESAW,		// �V�[�\�[
		MODELTYPE_IVY,			// �c�^
		MODELTYPE_IVY_2,		// �c�^(�w�i�p)
		MODELTYPE_BOX_W_3,		// �؃u���b�N4��
		MODELTYPE_TREE,			// �w�i�̖�
		MODELTYPE_TREE2,		// �w�i�̖�2
		MODELTYPE_TREE3,		// �w�i�̖�2
		MODELTYPE_TREE4,		// �w�i�̖�2
		MODELTYPE_GRASS,		// ��
		MODELTYPE_GOAL,			// �S�[��
		MODELTYPE_PBROCK,		// �S�[��
		MODELTYPE_MAX
	}MODELTYPE;

	typedef enum
	{
		COLTYPE_NONE = 0,
		COLTYPE_BOX,
		COLTYPE_PUSH,
		COLTYPE_BREAK,
		COLTYPE_SKY,
		COLTYPE_ICE,
		COLTYPE_FALL,
		COLTYPE_SEESAW,
		COLTYPE_CLIMB,
		COLTYPE_WALLJUMP,
		COLTYPE_MAX
	}COLTYPE;

	const static int m_MaxModel = MODELTYPE_MAX;			// ���f����

	CBlock();										// �R���X�g���N�^
	~CBlock();										// �f�X�g���N�^

	static HRESULT Load(void);						// ���[�h
	static void Unload(void);						// �A�����[�h
	static CBlock *Create(D3DXVECTOR3 pos, MODELTYPE modelType, COLTYPE coltype);		// ����

	HRESULT Init(D3DXVECTOR3 pos, MODELTYPE modelType, COLTYPE coltype);				// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��

	void Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, float *fDownSpeed, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);
	bool OtherBlockCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);

	COLTYPE GetType(void) { return m_colType; }
	COLTYPE GetHitType(void) { COLTYPE coltype = m_colHitType; m_colHitType = COLTYPE_NONE; return coltype; }

	bool *GetHit(void) { return m_bHit; }

private:
	static LPDIRECT3DTEXTURE9	*m_pTexture[m_MaxModel];	// �e�N�X�`�����ւ̃|�C���^
	static LPD3DXMESH			m_pMesh[m_MaxModel];		// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER			m_pBuffMat[m_MaxModel];		// �}�e���A�����ւ̃|�C���^
	static DWORD				m_nNumMat[m_MaxModel];		// �}�e���A�����̐�

	MODELTYPE					m_modelType;
	COLTYPE						m_colType;			// ���
	COLTYPE						m_colHitType;
	D3DXVECTOR3					m_posOld;			// �ړ���
	D3DXVECTOR3					m_move;				// �ړ���
	bool						m_bHit[4];

	float						m_shadowHeight;

protected:

};

#endif