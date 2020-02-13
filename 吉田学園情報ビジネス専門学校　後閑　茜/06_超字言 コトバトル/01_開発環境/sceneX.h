//=============================================================================
//
// 3D���f������ [sceneX.h]
// Author : �ڍ� ������
//
//=============================================================================
#ifndef _SCENEX_H_
#define _SCENEX_H_

#include "main.h"
#include "scene.h"
#include "load.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//========================================
// �N���X�̒�`
//========================================
//=====================
// �I�u�W�F�N�g�N���X
//=====================
class CSceneX : public CScene
{
public:
	//���f���̎��
	typedef enum
	{
		COLLISIONTYPE_NONE = 0,	//����
		COLLISIONTYPE_BOX,		//��
		COLLSIONTYPE_CONVEYOR_FRONT,	// �����蔻��(�x���g�R���x�A �O��)
		COLLSIONTYPE_CONVEYOR_RIHHT,	// �����蔻��(�x���g�R���x�A �E)
		COLLSIONTYPE_CONVEYOR_BACK,		// �����蔻��(�x���g�R���x�A ���)
		COLLSIONTYPE_CONVEYOR_LEFT,		// �����蔻��(�x���g�R���x�A ��)
		COLLSIONTYPE_KNOCKBACK_SMALL,	// �����蔻��(�m�b�N�o�b�N ��)
		COLLSIONTYPE_KNOCKBACK_DURING,	// �����蔻��(�m�b�N�o�b�N ��)
		COLLSIONTYPE_KNOCKBACK_BIG,		// �����蔻��(�m�b�N�o�b�N ��)
		COLLSIONTYPE_SWITCH,			// �����蔻��(�X�C�b�`)
		COLLSIONTYPE_BREAK,				// �����蔻��(����)
		COLLSIONTYPE_ICEFLOOR,			// �����蔻��(���鏰)
		COLLSIONTYPE_FLOORCOLLSION,		// �����蔻��(���̔��̓����蔻��)
		COLLSIONTYPE_BUSH,				// �����蔻��(���ނ�)
	}COLLISIONTYPE;

	CSceneX(int nPriority = SCENEX_PRIORITY, OBJTYPE objType = OBJTYPE_SCENEX);					// �R���X�g���N�^
	~CSceneX();									// �f�X�g���N�^
	HRESULT Init(void) { return S_OK; };
	HRESULT Init(D3DXVECTOR3 pos);				// 3D�I�u�W�F�N�g����������

	void Uninit(void);							// 3D�I�u�W�F�N�g�I������
	void Update(void);							// 3D�I�u�W�F�N�g�X�V����
	void Draw(void);							// 3D�I�u�W�F�N�g�`�揈��

	static CSceneX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Scale, CLoad::MODEL model, int nCollision = 0);	// �I�u�W�F�N�g�̐���

	D3DXVECTOR3 GetPosition(void);		 				// �ʒu�̎擾
	void SetPosition(D3DXVECTOR3 pos);					// �ʒu�̐ݒ�

	D3DXVECTOR3 GetRot(void);						// �����̎擾
	void SetRot(D3DXVECTOR3 rot);					// �����̐ݒ�

	D3DXVECTOR3 GetVtxMax(void);						// �ő�l�̎擾
	void SetVtxMax(D3DXVECTOR3 VtxMax);					// �ő�l�̐ݒ�

	D3DXVECTOR3 GetVtxMin(void);						// �ŏ��l�̎擾
	void SetVtxMin(D3DXVECTOR3 VtxMin);					// �ŏ��l�̐ݒ�

	void SetVtx(void);																// ���_���W�̐ݒ�
	bool Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius,int nPlayer);	// �����蔻��

	bool CollisionIN(D3DXVECTOR3 pos,D3DXVECTOR3 radius);		// �����蔻�� (�͈͓����ǂ���)


	void BindModel(LPD3DXBUFFER pBuffMat, DWORD nNumMat, LPD3DXMESH pMesh);	// ���f�������蓖�Ă�
	void BindTex(LPDIRECT3DTEXTURE9	*m_pTexture);	// �e�N�X�`���}�e���A�������蓖�Ă�

	void SetCollsionType(COLLISIONTYPE type) { m_CollisionType = type; }
	COLLISIONTYPE GetCollsionType(void) { return m_CollisionType; }		// �����蔻��̎�ނ��擾

	void SetScale(D3DXVECTOR3 Scale) { m_Scale = Scale; }				// �X�P�[����ݒ�
	D3DXVECTOR3 GetScale(void) { return m_Scale; }						// �X�P�[���̎擾

	void SetModelType(CLoad::MODEL model) { m_ModelType = model; }		// ���f���̎�ސݒ�
	CLoad::MODEL GetModelType(void) { return m_ModelType; }				// ���f���̎�ގ擾

	bool GetDrawFlag(void) { return m_bDraw; };
	void SetDrawFlag(bool bDraw) { m_bDraw = bDraw; };
	int GetCollsionNum(void) { return m_nCollsionNum; }
	void SetParent(D3DXMATRIX* pParent) { m_pParentMatrix = pParent; };
	void SetCameraNum(int nCamera) { m_nCamera = nCamera; };

	void SetSceneXNum(int nNumber) { m_nBushNum = nNumber; };
	int GetSceneXNum(void) {return m_nBushNum; };
	static void SetTranslucentBush(int nPlayer,int nNumber) { m_nTranslucentBush[nPlayer] = nNumber; };
private:
	LPDIRECT3DTEXTURE9		*m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
	LPD3DXMESH				m_pMesh;			// ���b�V�����i���_���j�ւ̃|�C���^
	LPD3DXBUFFER			m_pBuffMat;			// �}�e���A�����ւ̃|�C���^
	D3DXMATRIX				m_mtxWorld;			// ���[���h�}�g���b�N�X
	DWORD					m_nNumMat;			// �}�e���A�����̐�
	D3DXVECTOR3				m_VtxMin, m_VtxMax;	// ���f���̍ŏ��l�A�ő�l
	D3DXVECTOR3				m_pos;				// �|���S���̈ʒu
	D3DXVECTOR3				m_rot;				// ������x�N�g��
	D3DXVECTOR3				m_Scale;			// �X�P�[��
	CLoad::MODEL			m_ModelType;		// ���f���ԍ�
	COLLISIONTYPE			m_CollisionType;	// �����蔻��
	int						m_nCollsionNum;		// �����蔻����s�����ꏊ

	bool					m_bDraw;			//�������t���O(false�ŏ�����)
	bool					m_bTranslucent[4];	//���������t���O(true�ŏ�����)
	D3DXMATRIX*				m_pParentMatrix;	//�e�}�g���b�N�X
	int						m_nCamera;			//�J�����̔ԍ�
	int						m_nBushNum;			//���̔ԍ�
	static int				m_nTranslucentBush[4]; //�����ȑ��̔ԍ�
};

#endif