//=============================================================================
//
// �I�u�W�F�N�g���� [object.h]
// Author : ���� �x
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "scenex.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//========================================
// �N���X�̒�`
//========================================
class CScene3D;

//=====================
// �I�u�W�F�N�g�N���X
//=====================
class CObject : public CSceneX
{
public:
	typedef enum
	{	// �M�~�b�N�̎��
		GIMMICK_NONE = 0,
		GIMMICK_MOYE_Y,
		GIMMICK_MOYE_STAGE,
		GIMMICK_MAX
	}GIMMICKTYPE;

	typedef enum
	{	// �X�e�[�W�ω����̕ϐ�
		REALTIME_NONE = 0,	// �����Ȃ�
		REALTIME_INITPOS,	// �ŏ��̈ʒu����o��
		REALTIME_NOTMOVE,	// �w�莞�Ԃ܂œ����Ȃ�
		REALTIME_ENDPOS,	// �Ō�̈ʒu�Ɍ����Ĉړ�
		REALTIME_MAX		// ����
	}REALTIME;

	CObject();					// �R���X�g���N�^
	~CObject();									// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos);				// 3D�I�u�W�F�N�g����������
	void Uninit(void);							// 3D�I�u�W�F�N�g�I������
	void Update(void);							// 3D�I�u�W�F�N�g�X�V����
	void Draw(void);							// 3D�I�u�W�F�N�g�`�揈��

	static bool GetSwitch(void) { return m_bSwitch; }
	void SwitchBeltConveyor(bool bSwitch);					// �X�C�b�`�̏���
	void BeltConveyor(D3DXVECTOR3 *pMove,bool bSwitch);			// �ړ����̏���
	void KnockBack(D3DXVECTOR3 *pMove, int nID);			// �m�b�N�o�b�N
	void AffectedLanding(D3DXVECTOR3 *pMove, int nID);		// ���f���̒��n���̉e��

	static CObject *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Scale,CSceneX::COLLISIONTYPE type, CLoad::MODEL mode , CObject::GIMMICKTYPE realtime,int nNumver = 0);	// �I�u�W�F�N�g�̐���
	static HRESULT Load(void);
	static void UnLoad(void);

	// �ݒ� �擾�̊֐�
	REALTIME GetRealTimeType(void) { return m_nRealTime; }
	static bool GetCreateFlag(void) { return m_bCreateFlag; }

private:
	void ModelMove(CSceneX::COLLISIONTYPE Type, D3DXVECTOR3 *pos, float fMove);
	void Rot(CLoad::MODEL mode);

	static bool m_bCreateFlag;					// ��������t���O
	void ModelMove(CSceneX::COLLISIONTYPE Type, D3DXVECTOR3 pos);
	void BGModelMove( D3DXVECTOR3 pos);

	void AnimationIcon(void);					// �A�C�R���̃A�j���[�V����
	void IconCreate(CSceneX::COLLISIONTYPE Type, D3DXVECTOR3 pos);	// �A�C�R���̐���
	void Vibration(D3DXVECTOR3 *Pos);			// �U��

	bool m_bMoveFlag;				// �ړ��t���O
	REALTIME m_nRealTime;			// ���A���^�C���ňړ�����Flag�̕ϐ�
	D3DXVECTOR3 m_posOld;			// �ʒu�ۊ�
	CScene3D *m_pIcon;
	float m_fMove;
	int m_nCntAnim;
	int m_nCntPattan;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_InitPos;
	int m_MoveState;
	int m_nCounter;
	GIMMICKTYPE m_nTypeGimmick;

	D3DXVECTOR3 m_InitScale;			// �����傫���ۊ�

	int m_nObjNumber;		//�I�u�W�F�N�g�̔ԍ�

	//	SWITCH
	static bool m_bSwitch;				//	�X�C�b�`

};

#endif