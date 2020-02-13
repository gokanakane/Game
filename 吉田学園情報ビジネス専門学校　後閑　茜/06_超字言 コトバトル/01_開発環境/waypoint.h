//=============================================================================
//
// �o�H���̏��� [waypoint.h]
// Author :�@�ڍ� ������
//
//=============================================================================
#ifndef _WAYPOINT_H_
#define _WAYPOINT_H_

#include "sceneBillboard.h"
#include "game.h"

#define MAX_WAYPOINT	(SPLIT_WAYPOINT * SPLIT_WAYPOINT)	// �E�F�C�|�C���g�̍ő吔
#define SPLIT_WAYPOINT		(20)	// �E�F�C�|�C���g�̏c��������
#define WAYPOINT_HIT		(20)	// �E�F�C�|�C���g�͈̔�
#define WAYPOINT_POS_WIDE	(40)	// �E�F�C�|�C���g�̉���
#define WAYPOINT_RADIUS		(20)	// �E�F�C�|�C���g�̓����蔻�蕝

//*********************************************************************
//�r���{�[�h�N���X�̒�`
//*********************************************************************
class CWaypoint : public CScene //�h���N���X
{
public:
	typedef struct
	{
		CSceneBillBoard *pWayPoint;		//�r���{�[�h�|�C���^�[
		D3DXVECTOR3 WayPointPos;		//�ʒu���
		int	nWayPointNum;				//���}�X�ōs���邩
		bool bInPlayer;					//�v���C���[������Ă��邩
		bool bBlock;					//�u���b�N�Ɠ������Ă���
		bool bAdjacent;					//�אڂ��Ă���
	}WAYPOINT;

	typedef enum
	{
		FROMHIT_NONE,	//�������Ă��Ȃ�
		FROMHIT_FRONT,	//��O����
		FROMHIT_BACK,	//������
		FROMHIT_RIGHT,	//�E����
		FROMHIT_LEFT,	//������
		FROMHIT_IN,		//�������������Ă�
		FROMHIT_MAX
	}FROMHIT;		//�ǂ����瓖��������


	CWaypoint();
	~CWaypoint();
	HRESULT Init(/*D3DXVECTOR3 pos*/);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CWaypoint *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, LPCSTR Tag);
	void InRange(D3DXVECTOR3 pos);
	D3DXVECTOR3 &ReturnPointMove(void);	//�ړ��\�ȃ}�X�̈ʒu���
	int CntWayPoint(void);				//�ړ��\�}�X�����}�X���邩
	void CollisionObj(void);			//�I�u�W�F�N�g�Ɠ������Ă��邩
	WAYPOINT &GetWayPoint(void);	//�ړ��\�ȃ}�X�̈ʒu���

	//TEST
	int GetNumTargetPoint(int nWayPoint);			//�s�����Ƃ��Ă���}�X�ԍ�
	D3DXVECTOR3 GetNextWayPoint(int nWayPoint);		//�ׂ̍s����}�X��n��
	bool GetWPbBlock(int nWayPoint){ return WayPoint[nWayPoint].bBlock;	};


	int GetNowWP(void) { return m_nNumNowPoint; };
	// �֐�
private:
	D3DXVECTOR3 Move(D3DXVECTOR3 pos);
	void ScaleSize(void);

	WAYPOINT WayPoint[MAX_WAYPOINT];

	D3DXVECTOR3 m_size;		// �T�C�Y
	D3DXVECTOR3 m_sizeOld;	// �T�C�Y(�ߋ�)
	bool m_bFlagUninit;		// �I�����邽�߂̃t���O
	bool m_bMoveFlag;		// �㉺�ړ��̃t���O
	bool m_bScaleFlag;		// �g��k������t���O
	int m_nWaypointNum;		// �o�H���̔ԍ�

	D3DXVECTOR3 m_pWayPointPos[8];		// �|�C���^
	int m_nTargetNum[8];				// �s����̔ԍ�
	int m_nNumWayPoint;					// �s���\�Ȑ�

	int m_nNumNowPoint;				// ���݂̃}�X�ԍ�
	D3DXVECTOR3 m_PlayerPos;		// �v���C���[�̈ʒu�L��

	FROMHIT m_FromHit;

	int		m_nFlameCnt;	//�t���[�����𐔂���
	bool	m_bStageStart;	//�Q�[���J�n���ɓ���t���O
	bool	m_bStageSetEnd;	//�X�e�[�W���؂�ւ�����t���O

#ifdef _DEBUG
	int nNum2Cnt;
#endif

};

#endif