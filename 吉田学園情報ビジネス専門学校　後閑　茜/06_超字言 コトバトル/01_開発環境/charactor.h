//=============================================================================
//
// �L�����N�^�[���� [charactor.h]
// Author : Kodama Yuto
//
//	�N���X�̊T�v
//	�EPosition��Rotation�ȂǁA�p������Ɏg���ϐ����������N���X�Q
//	�E�N���X���Ŏp��������s���AGet�֐��ł������擾����
//
//	C2DCharactor
//	�E2D�̃L�����N�^�[�p�̃N���X
//	�E�}�g���b�N�X���������APosition��Rotation�Ő��䂷��
//
//	C3DCharactor
//	�E3D�̃L�����N�^�[�p�̃N���X
//	�EPosition��Rotation�ɉ�����,�}�g���b�N�X���g���Ďp��������s��
//
//=============================================================================
#ifndef _CHARACTOR_H_
#define _CHARACTOR_H_

#include "scene.h"


class CWaypoint;
class CPlayer;
class CAvoidUi;
class CShadow;

class CCharaBase
{
public:
	typedef enum
	{
		MOVETYPE_PLAYER_INPUT,		//�v���C���[�̑���
		MOVETYPE_NPC_AI,			//NPC��AI�̑���
		MOVETYPE_RANKING_CHARA,		//�����L���O�̃L����
		MOVETYPE_MAX
	}CHARACTOR_MOVE_TYPE;

	typedef enum
	{
		THINK_NONE,				//�����l���ĂȂ�
		THINK_WORD,				//�������l����
		THINK_SIGHT,			//�G���������Ƃ�
		THINK_MISSING,			//�G�����������Ƃ�
		THINK_HAVEBULLET,		//�e�������Ă���Ƃ�
		THINK_NOTBULLET,		//�e�������ĂȂ��Ƃ�
		THINK_PICKUP,			//�e���E���ɍs��
		THINK_ENEMY_HAVEBULLET,	//�G���e�������Ă���Ƃ�
		THINK_ENEMY_NOBULLET,	//�G���e�������ĂȂ��Ƃ�
		THINK_ESCAPE,			//������
		THINK_DODGE,			//���킷
		THINK_ATTACK,			//�U��������Ƃ�
		THINK_NEAR_ENEMY,		//�߂�
		THINK_FUR_ENEMY,		//����
		THINK_MOVE,				//�ړ�
		THINK_ROTATION,			//��]
		THINK_PATROL,			//����
		THINK_HOMING,			//�ǂ�������
		THINK_WATCH,			//����
		THINK_WAYPOINTMOVE,		//�o�H���
		THINK_WAYPOINTROUTE,	//�ŒZ�̓��T��
		THINK_MAX
	}CPU_THINK;

	typedef enum
	{
		CPU_MOVE_FRONT,			//�O�ֈړ�
		CPU_MOVE_RIGHT,			//�E�ֈړ�
		CPU_MOVE_LEFT,			//���ֈړ�
		CPU_MOVE_BACK,			//���ֈړ�
		CPU_MOVE_PATROL,		//����
		CPU_MOVE_NONE,			//�ړ����Ă��Ȃ�
		CPU_MOVE_MAX
	}CPU_MOVE;

	typedef enum
	{
		CPU_ROTATION_RIGHT,			//�E�։�]
		CPU_ROTATION_LEFT,			//���։�]
		CPU_ROTATION_BACK,			//���։�]
		CPU_ROTATION_MAX
	}CPU_ROTATION;

	typedef enum
	{
		CPU_NODE_NONE,			//�������Ă��Ȃ�
		CPU_NODE_RUN,			//���s��
		CPU_NODE_SUCCESS,		//��������
		CPU_NODE_FAILURE,		//���s����
		CPU_NODE_MAX
	}CPU_NODE;

	typedef enum
	{
		CPU_TYPE_NONE,			//���ɂȂ�
		CPU_TYPE_PATROL,		//����^
		CPU_TYPE_ESCAPE,		//����
		CPU_TYPE_HOMING,		//�ǔ�
		CPU_TYPE_MAX
	}CPU_TYPE;

	CCharaBase() {};
	~CCharaBase() {};

	virtual void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CHARACTOR_MOVE_TYPE type, CPlayer* pThis);

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;

	D3DXVECTOR3& GetPosition(void) { return m_pos; };
	D3DXVECTOR3& GetRotation(void) { return m_rot; };
	D3DXVECTOR3& GetMove(void) { return m_Move; };
	D3DXVECTOR3& GetSpin(void) { return m_Spin; };
	float&		 GetSpeed(void) { return m_fSpeed; };
	float&		GetStep(void) { return m_fStep; };
	float&		 GetMoveCoeffient(void) { return m_fMoveCoeffient; };
	float&		GetSpinCoeffient(void) { return m_fSpinCoeffient; };
	float&		GetMoveCofBlend(void) { return m_fCofMoveBlend; };

	CHARACTOR_MOVE_TYPE GetMoveType(void) { return m_type; };
	void SetMoveType(CHARACTOR_MOVE_TYPE MoveType) { m_type = MoveType; };
	void SetWaitBool(bool bWait) { m_bWait = bWait; };

	void SetThisCharactor(CPlayer* pThis) { m_pThisCharactor = pThis; };

protected:
	CPlayer* GetThisCharactor(void) { return m_pThisCharactor; };
	int m_nCntStepCoolTime;		//�X�e�b�v�ړ��̃N�[���_�E�����ԑ���p
private:
	D3DXVECTOR3 m_pos;				//�ʒu
	D3DXVECTOR3 m_rot;				//�p�x
	D3DXVECTOR3 m_Move;				//�ړ���
	D3DXVECTOR3 m_Spin;				//��]��
	float m_fSpeed;					//�ړ����x
	float m_fStep;					//�X�e�b�v�ړ��̈ړ���
	float m_fMoveCoeffient;			//�ړ��̊���
	float m_fSpinCoeffient;			//��]�̊���

	CHARACTOR_MOVE_TYPE m_type;		//�ړ��^�C�v

	CPlayer* m_pThisCharactor;		//���̃C���X�^���X���������Ă���v���C���[


public:
	CPU_THINK m_CpuThink;		//���݂̍l��
	CPU_THINK m_OldCpuThink;	//�ߋ��̍l��
	CPU_MOVE m_CpuMove;			//�s��
	CPU_ROTATION m_CpuRotation;	//��]
	CPU_NODE m_CpuNode;			//�m�[�h�̏��
	CPU_TYPE m_Type;
	D3DXVECTOR3 m_RespawnPos;	//�o���ʒu
	CWaypoint *m_pWayPoint;		//�o�H���
	float m_fCofMoveBlend;	//�X�e�B�b�N�p�ɉ������ړ��W��
	bool m_bWait;			//�҂��̃u�[��
};

class C2DCharactor : public CCharaBase
{
public:
	C2DCharactor() {};
	~C2DCharactor() {};

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CHARACTOR_MOVE_TYPE type, CPlayer* pThis) { CCharaBase::Set(pos, rot, type, pThis); };

	HRESULT Init(void);
	void Uninit(void) {};
	void Update(void);
private:
};

class C3DCharactor : public CCharaBase
{
public:
	C3DCharactor() {};
	~C3DCharactor() {};

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CHARACTOR_MOVE_TYPE type, CPlayer* pThis) { CCharaBase::Set(pos, rot, type, pThis); };

	HRESULT Init(void);
	void Uninit(void) {};
	void Update(void);

	void SetCameraPosR(D3DXVECTOR3 posR) { m_CameraPosR = posR; };

	D3DXVECTOR3 GetCameraPosR(void) { return m_CameraPosR; };
	D3DXMATRIX* GetMatrix(void) { return &m_mtxWorld; };

private:
	void CharaMove_Input(void);
	void CharaMove_CPU(void);
	void Think_CPU(void);		//�l����
	void Action_CPU(void);		//�s��
	void DiffAngle(float fDiffAngle);		//��]����
	void Rotation_CPU(void);	//��]
	void Escape_CPU(void);		//����
	void Homing_CPU(void);		//�ǔ�
	void Attack_CPU(void);		//�U��
	void PickUP_CPU(void);		//�����E��
	void HaveBullet_CPU(void);	//�e�������Ă���
	void NotBullet_CPU(void);	//�e�������Ă��Ȃ�
	void NearOrFur_CPU(void);	//�߂���������
	void WayPointMove_CPU(void);	//�o�H���ړ�
	void WayPointRoute_CPU(void);	//�ŒZ���[�g�ړ�
	void WayPointBack_CPU(void);	//��ވړ�

	void StepMove(D3DXVECTOR3& move,float& fRot);

	D3DXVECTOR3 m_CameraPosR;	//�J�����̒����_����Ɏg���ϐ�
	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���b�N�X
	//CPU�Ŏg�������o�ϐ�
	int m_nThinkTimer;			//�l���鎞��
	int m_nActionTimer;			//�s�����Ă��鎞��
	int m_nSameCnt;				//�����s�������x������
	float m_fCompareRange;		//�����܂ł̋������r����
	int m_PatrolTimer;			//����̃^�C�}�[
	bool m_bNear[4];			//�߂��G�̃t���O
	bool m_bWordNear;
	bool m_bJyougai;
	D3DXVECTOR3 *m_pWayPointPos;	//�o�H���̈ʒu���|�C���^
	D3DXVECTOR3 m_MarkWayPoint;		//�ړ���̈ʒu
	bool m_bGoal;					//�ړ��擞���t���O
	bool m_bRandomGoal;				//�ړ��擞���t���O(�����_��)
	bool m_bSearch;					//�ړ���T���t���O
	bool m_bNearWard;				//�������߂��ɂ���t���O
	bool m_bBlock;					//�ړ����Q���t���O
	int m_nTimerMove;				//�ړ���ɍs���Ȃ��Ƃ��̃^�C�}�[
	bool m_bNotWayPoint;			//�ړ���ɍs���Ȃ��Ƃ��̃t���O
	int	m_nTargetWP;				//�ڕW�̃}�X�ԍ�
	D3DXVECTOR3 m_MarkWardPos;		//�ړ���̈ʒu
	float m_fOldCircle;				//�ړ���܂ł̋���
	int nTestCnt = 0;
	CAvoidUi *m_pCAvoidUi;
	CShadow *m_pShadow;
	//�e���ˏ��
	D3DXVECTOR3 m_BulletRot;		//�e���˕����ێ�
	int m_nMachineGunTime;			//�}�V���K�����ˎ���
	bool m_bMachineGun;				//�}�V���K���t���O
	D3DXVECTOR3 m_MachineGunPos;	//�}�V���K�����ˈʒu

	int m_nCounter;

public:
	bool m_bFront;
};

#endif // !_CHARACTOR_H_
