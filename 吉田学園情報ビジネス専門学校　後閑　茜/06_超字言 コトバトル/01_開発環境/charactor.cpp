//=============================================================================
//
// �L�����N�^�[��{���� (CCharaBase)[charactor.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "charactor.h"
#include "manager.h"

#include "CameraManager.h"
#include "player.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "debugProc.h"
#include "meshField.h"
#include "word_manager.h"
#include "point.h"
#include "word.h"

#include "waypoint.h"

#include "effect.h"

#include "avoidui.h"
#include "shadow.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define MOVE_DEFAULT_SPEED (0.6f)			//�f�t�H���g�̈ړ��X�s�[�h
#define STEP_DEFAULT_MOVEMENT (10.0f)		//�f�t�H���g�̃X�e�b�v��
#define MOVE_DEFAULT_COEFFICIENT (0.20f)	//�f�t�H���g�̈ړ��ɂ�����W��
#define SPIN_DEFAULT_COEFFICIENT (0.50f)	//�f�t�H���g�̉�]�ɂ�����W��
#define CIRCLE_HOMING	 (3000)				//�ǔ��͈�(���)
#define CIRCLE_ANGLE	(100000)
#define PATROL_FLAME	(60)
#define CAMERA_MOVE_SPEED (0.05f)
#define NEAR_DISTANCE	(100)
#define FIELD_OUTSIDE	(300)

//CAvoidUi *C3DCharactor::m_pCAvoidUi = NULL;

//=============================================================================
// �ݒ菈��
//=============================================================================
void  CCharaBase::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CHARACTOR_MOVE_TYPE type, CPlayer* pThis)
{
	//�ϐ�������
	m_pos = pos;
	m_RespawnPos = pos;
	m_rot = rot;
	m_type = type;
	m_pThisCharactor = pThis;

	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Spin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSpeed = MOVE_DEFAULT_SPEED;
	m_fStep = STEP_DEFAULT_MOVEMENT;
	m_fMoveCoeffient = MOVE_DEFAULT_COEFFICIENT;
	m_fSpinCoeffient = SPIN_DEFAULT_COEFFICIENT;
	m_fCofMoveBlend = 1.0f;
	m_nCntStepCoolTime = 0;

	m_pWayPoint = NULL;
	if (m_pWayPoint == NULL)
	{
		//m_pWayPoint = CWaypoint::Create(m_pos, 10, 10, "NUMBER");
	}

	if (m_pThisCharactor != NULL)
	{
		if (m_pThisCharactor->GetPlayerType() == CPlayer::TYPE_SPEED)
		{
			m_fSpeed = MOVE_DEFAULT_SPEED + 0.05f;
		}
		else if (m_pThisCharactor->GetPlayerType() == CPlayer::TYPE_REACH)
		{
			m_fSpeed = MOVE_DEFAULT_SPEED - 0.05f;
		}
	}

	//�R�}���h��`
	CCommand::RegistCommand("PLAYERMOVE_UP", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_W);
	CCommand::RegistCommand("PLAYERMOVE_UP", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_UP);
	CCommand::RegistCommand("PLAYERMOVE_DOWN", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_S);
	CCommand::RegistCommand("PLAYERMOVE_DOWN", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_DOWN);
	CCommand::RegistCommand("PLAYERMOVE_RIGHT", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_D);
	CCommand::RegistCommand("PLAYERMOVE_RIGHT", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_RIGHT);
	CCommand::RegistCommand("PLAYERMOVE_LEFT", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_A);
	CCommand::RegistCommand("PLAYERMOVE_LEFT", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_LEFT);

	CCommand::RegistCommand("PLAYERMOVE_STEP", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_LSHIFT);
	CCommand::RegistCommand("PLAYERMOVE_STEP", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_LEFT_SHOULDER);

	CCommand::RegistCommand("CAMERAMOVE_LEFT", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_LEFT);
	CCommand::RegistCommand("CAMERAMOVE_LEFT", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_RIGHTSTICK_LEFT);
	CCommand::RegistCommand("CAMERAMOVE_RIGHT", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_RIGHT);
	CCommand::RegistCommand("CAMERAMOVE_RIGHT", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_RIGHTSTICK_RIGHT);
	CCommand::RegistCommand("CAMERAMOVE_UP", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_UP);
	CCommand::RegistCommand("CAMERAMOVE_UP", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_RIGHTSTICK_UP);
	CCommand::RegistCommand("CAMERAMOVE_DOWN", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_DOWN);
	CCommand::RegistCommand("CAMERAMOVE_DOWN", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_RIGHTSTICK_DOWN);

	CCommand::RegistCommand("TEST_FLY_UP", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_Y);
	CCommand::RegistCommand("TEST_FLY_DOWN", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_X);
}

//=============================================================================
//
// 3D�L�����N�^�[���� (C3DCharactor)[charactor.cpp]
// Author : Kodama Yuto
//
//=============================================================================
//=============================================================================
// ����������
//=============================================================================
HRESULT C3DCharactor::Init(void)
{
	m_nThinkTimer = 0;
	m_nActionTimer = 0;
	m_nSameCnt = 0;
	m_fCompareRange = 0;
	m_PatrolTimer = 0;
	m_bWordNear = false;
	m_bJyougai = false;
	m_bGoal = true;
	m_bRandomGoal = true;
	m_bSearch = false;
	m_bNearWard = false;
	m_bBlock = false;
	m_nTimerMove = 0;
	m_bNotWayPoint = false;
	m_nTargetWP = 0;
	nTestCnt = 0;
	m_bWait = false;
	m_fOldCircle = 0;
	m_BulletRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bMachineGun = false;
	m_MachineGunPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nMachineGunTime = 0;
	m_CpuThink = THINK_NONE;

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		m_bNear[nCnt] = false;
	}

	m_MarkWardPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pWayPointPos = NULL;								//�o�H���̈ʒu���|�C���^
	m_MarkWayPoint = D3DXVECTOR3(0.0f,0.0f,0.0f);		//�ړ���̈ʒu


	//	���UI
	m_pCAvoidUi = CAvoidUi::Create(CCharaBase::GetPosition() + D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f),
		D3DXVECTOR3(18.0f, 18.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));

	m_nCounter = 0;


	m_pShadow = CShadow::Create(CCharaBase::GetPosition(), 12, 12);


	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void C3DCharactor::Update(void)
{
	CCameraManager* pCameraManager = CManager::GetCameraManager();
	D3DXVECTOR3& pos = CCharaBase::GetPosition();
	D3DXVECTOR3& rot = CCharaBase::GetRotation();
	D3DXVECTOR3& move = CCharaBase::GetMove();
	m_nCounter++;
	CPlayer *pPlayer[MAX_PLAYER];
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		pPlayer[nCntPlayer] = CManager::GetPlayer(nCntPlayer);			// �v���C���[���擾
	}

	//�o�H���
	if (m_pWayPoint != NULL)
	{
		m_pWayPoint->InRange(pos);
	}
	if (m_bWait == false)
	{
		switch (CCharaBase::GetMoveType())
		{
		case CCharaBase::MOVETYPE_PLAYER_INPUT:
			if (m_pWayPoint == NULL)
			{
				//	m_nTargetWP = 1;
				//	m_pWayPoint = CWaypoint::Create(m_RespawnPos, 10, 10, "NUMBER");
			}
			CharaMove_Input();
			break;
		case CCharaBase::MOVETYPE_NPC_AI:
			if (CGame::GetbStageSet() == false)
			{
				if (m_nActionTimer == 0)
				{	//�l����
					Think_CPU();
				}
				else
				{	//�s������
					Action_CPU();
				}
			}
			//CPU����O�s���Ȃ��悤��
			if (m_bJyougai == false)
			{
				if (FIELD_OUTSIDE < pos.x || -FIELD_OUTSIDE > pos.x ||
					FIELD_OUTSIDE < pos.z || -FIELD_OUTSIDE > pos.z)
				{//��O�Ɉړ��������ɂȂ�����
					m_bJyougai = true;
					move.x = 0;
					move.z = 0;
					m_CpuThink = THINK_ROTATION;
					m_nActionTimer = 2;
					m_CpuRotation = (CPU_ROTATION)(rand() % 3);
				}
			}
			else
			{
				if (FIELD_OUTSIDE - 10 > pos.x && -FIELD_OUTSIDE + 10 < pos.x &&
					FIELD_OUTSIDE - 10 > pos.z && -FIELD_OUTSIDE + 10 < pos.z)
				{//����Ɉړ�����
					m_bJyougai = false;
				}
			}
			break;
		case CCharaBase::MOVETYPE_RANKING_CHARA:
			pos += move;
			//���x�ɌW�����|����
			CUtilityMath::MoveCoeffient(move, GetMoveCoeffient());
			true;
		}
	}

	if (m_pCAvoidUi != NULL)
	{
		for (int nCP = 0; nCP < MAX_PLAYER; nCP++)
		{	//�����Ă��Ȃ��v���C���[�̑�����UI����������
			if (pPlayer[nCP] != NULL)
			{
				m_pCAvoidUi->SetVision(nCP, pPlayer[nCP]->GetVision(GetThisCharactor()->GetID()));
			}
		}
	}

	//���b�V���t�B�[���h�Ƃ̓����蔻��
	CMeshField *pMesh = NULL;

	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		pMesh = CGame::GetMeshField();
	}
	else if (CManager::GetMode() == CManager::MODE_RESULT)
	{
		pMesh = CResult::GetMeshField();
	}
	else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		pMesh = CTutorial::GetMeshField();
	}

	float fHeight;

	if (pMesh != NULL)
	{
		fHeight = pMesh->GetHeight(pos);
	}

	if (pos.y < fHeight)
	{
		pos.y = fHeight;
	}

	//�d��
	move.y = -3.0f;
	//�������x
	if (pos.y <= -100.0f)
	{
		//�ݒ�
		pos = m_RespawnPos;
		GetThisCharactor()->SetOldPosition(m_RespawnPos);
		move.y = 0.0f;
		GetThisCharactor()->SetTransTime(60);

		CPoint *pPoint = NULL;
		if (CManager::GetMode() == CManager::MODE_GAME) { pPoint = CGame::GetPoint(GetThisCharactor()->GetID()); }
		else if (CManager::GetMode() == CManager::MODE_TUTORIAL) { /* �`���[�g���A���̍�Ƃɂ�肩�������ꍇ �����Ń`���[�g���A������|�C���g���擾 */ }

		if (pPoint != NULL)
		{
			pPoint->SubtractionPoint(1);
		}
	}

	//�X�e�b�v�̑ҋ@���Ԃ̃J�E���g�_�E��
	if (m_nCntStepCoolTime > 0)
	{
		m_nCntStepCoolTime--;
	}

	//�}�g���b�N�X�̌v�Z
	CUtilityMath::CalWorldMatrix(&m_mtxWorld, pos, rot);
	//�J�����̎Q�ƈʒu����
	m_CameraPosR = GetPosition() + D3DXVECTOR3(0.0f, 40.0f, 0.0f);

#ifdef _DEBUG

	if (m_pWayPoint != NULL)
	{
	CDebugProc::Print("cfcfcf", "MarkWayPoint : X ", m_MarkWayPoint.x, " Y ", m_MarkWayPoint.y, " Z ", m_MarkWayPoint.z);
	CDebugProc::Print("cn", "m_bGoal : ", (int)m_bGoal);
	CDebugProc::Print("cn", "m_bNearWard : ", (int)m_bNearWard);
	CDebugProc::Print("cn", "m_bSearch : ", (int)m_bSearch);
	}

	switch (m_CpuThink)
	{
	case  THINK_HAVEBULLET:
		CDebugProc::Print("c", "THINK_HAVEBULLET");
		break;
	case  THINK_NOTBULLET:
		CDebugProc::Print("c", "THINK_NOTBULLET");
		break;
	case  THINK_PICKUP:
		CDebugProc::Print("c", "THINK_PICKUP");
		break;
	case  THINK_WAYPOINTMOVE:
		CDebugProc::Print("c", "THINK_WAYPOINTMOVE");
		break;
	case  THINK_WAYPOINTROUTE:
		CDebugProc::Print("c", "THINK_WAYPOINTROUTE");
		break;
	default:
		break;
	}
#endif


	if (m_pCAvoidUi != NULL)
	{//	���UI���g�p����Ă�
		m_pCAvoidUi->SetPos(pos + D3DXVECTOR3(0.0f, 5.0f, 0.0f));

		if (GetMoveType() == MOVETYPE_PLAYER_INPUT)
		{
			if (GetThisCharactor()->GetID() == 0) { m_pCAvoidUi->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.7f)); }
			else if (GetThisCharactor()->GetID() == 1) { m_pCAvoidUi->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.9f, 0.7f)); }
			else if (GetThisCharactor()->GetID() == 2) { m_pCAvoidUi->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.7f)); }
			else if (GetThisCharactor()->GetID() == 3) { m_pCAvoidUi->SetColor(D3DXCOLOR(0.7f, 0.4f, 0.0f, 0.7f)); }
		}
		else if (GetMoveType() == MOVETYPE_NPC_AI)
		{
			m_pCAvoidUi->SetColor(D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.7f));
		}
	}
	if (GetThisCharactor()->GetID() == 0) {
		if (m_nCounter % 7 == 0 && (move.x > 0.1f || move.x < -0.1f || move.z > 0.1f || move.z < -0.1f) && pPlayer[0]->Getbush(0) == false)
		{//	��
			CEffect::Create(pos + D3DXVECTOR3(0.0f, 2.0f, 0.0f), 5, 9);
		}
		else if (m_nCounter % 7 == 0 && (move.x > 0.1f || move.x < -0.1f || move.z > 0.1f || move.z < -0.1f) && pPlayer[0]->Getbush(0) == true)
		{//	��
			CEffect::Create(pos + D3DXVECTOR3(0.0f, 30.0f, 0.0f), 5, 10);
		}
	}
	if (GetThisCharactor()->GetID() == 1) {
		if (m_nCounter % 7 == 0 && (move.x > 0.1f || move.x < -0.1f || move.z > 0.1f || move.z < -0.1f) && pPlayer[1]->Getbush(1) == false)
		{//	��
			CEffect::Create(pos + D3DXVECTOR3(0.0f, 2.0f, 0.0f), 5, 9);
		}
		else if (m_nCounter % 7 == 0 && (move.x > 0.1f || move.x < -0.1f || move.z > 0.1f || move.z < -0.1f) && pPlayer[1]->Getbush(1) == true)
		{//	��
			CEffect::Create(pos + D3DXVECTOR3(0.0f, 30.0f, 0.0f), 5, 10);
		}
	}
	if (GetThisCharactor()->GetID() == 2) {
		if (m_nCounter % 7 == 0 && (move.x > 0.1f || move.x < -0.1f || move.z > 0.1f || move.z < -0.1f) && pPlayer[2]->Getbush(2) == false)
		{//	��
			CEffect::Create(pos + D3DXVECTOR3(0.0f, 2.0f, 0.0f), 5, 9);
		}
		else if (m_nCounter % 7 == 0 && (move.x > 0.1f || move.x < -0.1f || move.z > 0.1f || move.z < -0.1f) && pPlayer[2]->Getbush(2) == true)
		{//	��
			CEffect::Create(pos + D3DXVECTOR3(0.0f, 30.0f, 0.0f), 5, 10);
		}
	}
	if (GetThisCharactor()->GetID() == 3) {
		if (m_nCounter % 7 == 0 && (move.x > 0.1f || move.x < -0.1f || move.z > 0.1f || move.z < -0.1f) && pPlayer[3]->Getbush(3) == false)
		{//	��
			CEffect::Create(pos + D3DXVECTOR3(0.0f, 2.0f, 0.0f), 5, 9);
		}
		else if (m_nCounter % 7 == 0 && (move.x > 0.1f || move.x < -0.1f || move.z > 0.1f || move.z < -0.1f) && pPlayer[3]->Getbush(3) == true)
		{//	��
			CEffect::Create(pos + D3DXVECTOR3(0.0f, 30.0f, 0.0f), 5, 10);
		}
	}

	if (m_pShadow != NULL)
	{
		m_pShadow->SetPos(pos + D3DXVECTOR3(0.0f, 4.0f, 0.0f));
	}
}

//=============================================================================
// �ړ�����
//=============================================================================
void C3DCharactor::CharaMove_Input(void)
{
	CCameraManager* pCameraManager = CManager::GetCameraManager();

	CCamera* pCamera = pCameraManager->GetCamera(GetThisCharactor()->GetCameraName());
	int nID = GetThisCharactor()->GetID();
	D3DXVECTOR3 CameraRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (pCamera != NULL)
	{
		CameraRot = pCamera->GetRotation();
	}

	//�e�N���X����l���擾(�Q�Ƃ��g��)
	D3DXVECTOR3& pos = CCharaBase::GetPosition();
	D3DXVECTOR3& move = CCharaBase::GetMove();
	D3DXVECTOR3& rot = CCharaBase::GetRotation();
	D3DXVECTOR3& spin = CCharaBase::GetSpin();
	float		 speed = CCharaBase::GetSpeed();

	//XPad�R���g���[���̃X�e�B�b�N���x�ݒ�
	float fMoveCoefficientX = 1.0f;	//�ړ��W��(X)
	float fMoveCoefficientZ = 1.0f;	//�ړ��W��(Z)
	m_fCofMoveBlend = 1.0f;	//�ړ��W���̓���|�����킹������
	if (CManager::GetXInput(nID) != NULL)
	{
		if (CManager::GetXInput(nID)->GetConnect() == true)
		{
			fMoveCoefficientX = fabsf(CCommand::GetXPadStickRotation(true, false, nID));
			fMoveCoefficientZ = fabsf(CCommand::GetXPadStickRotation(true, true, nID));
			m_fCofMoveBlend = (fMoveCoefficientX > fMoveCoefficientZ) ? fMoveCoefficientX : fMoveCoefficientZ;
		}
	}

	//�ړ��̌����ݒ�
	if (CCommand::GetCommand("PLAYERMOVE_RIGHT", nID))
	{
		if (CCommand::GetCommand("PLAYERMOVE_UP", nID))
		{//�E��
			move.x += sinf(CameraRot.y + (D3DX_PI * 0.25f)) * (speed * m_fCofMoveBlend);
			move.z += cosf(CameraRot.y + (D3DX_PI * 0.25f)) *  (speed * m_fCofMoveBlend);
			spin.y = D3DX_PI * 0.25f - rot.y;
		}
		else if (CCommand::GetCommand("PLAYERMOVE_DOWN", nID))
		{//�E��
			move.x += sinf(CameraRot.y + (D3DX_PI * 0.75f)) *  (speed * m_fCofMoveBlend);
			move.z += cosf(CameraRot.y + (D3DX_PI * 0.75f)) *  (speed * m_fCofMoveBlend);
			spin.y = D3DX_PI * 0.75f - rot.y;
		}
		else
		{//�E
			move.x += sinf(CameraRot.y + (D3DX_PI * 0.5f)) * (speed * fMoveCoefficientX);
			move.z += cosf(CameraRot.y + (D3DX_PI * 0.5f)) * (speed * fMoveCoefficientX);
			spin.y = D3DX_PI * 0.5f - rot.y;
		}
		if (GetThisCharactor()->GetMotion() != 6 &&
			GetThisCharactor()->GetMotion() != 7)

		{//���̃��[�V�������X�e�b�v�ł��e�ł��ł��Ȃ����

		 //���[�V��������
			if (GetThisCharactor()->GetWordManager()->GetBulletFlag())
			{
				GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_SETUP_WALK, CPlayer::UPPER_BODY);
			}
			else
			{
				GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_WALK, CPlayer::UPPER_BODY);
			}
			//GetThisCharactor()->SetMotion(CPlayer::MOTION_LOWER_WALK_RIGHT, CPlayer::LOWER_BODY);
			GetThisCharactor()->SetMotion(CPlayer::MOTION_LOWER_WALK_FRONT, CPlayer::LOWER_BODY);

		}
	}
	else if (CCommand::GetCommand("PLAYERMOVE_LEFT", nID))
	{
		if (CCommand::GetCommand("PLAYERMOVE_UP", nID))
		{//����
			move.x += sinf(CameraRot.y + (D3DX_PI * -0.25f)) *  (speed * m_fCofMoveBlend);
			move.z += cosf(CameraRot.y + (D3DX_PI * -0.25f)) *  (speed * m_fCofMoveBlend);
			spin.y = D3DX_PI * -0.25f - rot.y;


		}
		else if (CCommand::GetCommand("PLAYERMOVE_DOWN", nID))
		{//����
			move.x += sinf(CameraRot.y + (D3DX_PI * -0.75f)) *  (speed * m_fCofMoveBlend);
			move.z += cosf(CameraRot.y + (D3DX_PI * -0.75f)) *  (speed * m_fCofMoveBlend);
			spin.y = D3DX_PI * -0.75f - rot.y;

		}
		else
		{//��
			move.x += sinf(CameraRot.y + (D3DX_PI * -0.5f)) * (speed * fMoveCoefficientX);
			move.z += cosf(CameraRot.y + (D3DX_PI * -0.5f)) * (speed * fMoveCoefficientX);
			spin.y = D3DX_PI * -0.5f - rot.y;

		}
		if (GetThisCharactor()->GetMotion() != 6 &&
			GetThisCharactor()->GetMotion() != 7)

		{//���̃��[�V�������X�e�b�v�ł��e�ł��ł��Ȃ����

		 //���[�V��������
			if (GetThisCharactor()->GetWordManager()->GetBulletFlag())
			{
				GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_SETUP_WALK, CPlayer::UPPER_BODY);
			}
			else
			{
				GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_WALK, CPlayer::UPPER_BODY);
			}
			//GetThisCharactor()->SetMotion(CPlayer::MOTION_LOWER_WALK_LEFT, CPlayer::LOWER_BODY);
			GetThisCharactor()->SetMotion(CPlayer::MOTION_LOWER_WALK_FRONT, CPlayer::LOWER_BODY);

		}
	}
	else if (CCommand::GetCommand("PLAYERMOVE_UP", nID))
	{//��
		move.x += sinf(CameraRot.y + (D3DX_PI * 0.0f)) * (speed * fMoveCoefficientZ);
		move.z += cosf(CameraRot.y + (D3DX_PI * 0.0f)) * (speed * fMoveCoefficientZ);
		spin.y = D3DX_PI * 0.0f - rot.y;

		if (GetThisCharactor()->GetMotion() != 6 &&
			GetThisCharactor()->GetMotion() != 7)

		{//���̃��[�V�������X�e�b�v�ł��e�ł��ł��Ȃ����

		 //���[�V��������
			if (GetThisCharactor()->GetWordManager()->GetBulletFlag())
			{
				GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_SETUP_WALK, CPlayer::UPPER_BODY);
			}
			else
			{
				GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_WALK, CPlayer::UPPER_BODY);
			}
			GetThisCharactor()->SetMotion(CPlayer::MOTION_LOWER_WALK_FRONT, CPlayer::LOWER_BODY);
		}
	}
	else if (CCommand::GetCommand("PLAYERMOVE_DOWN", nID))
	{//��
		move.x += sinf(CameraRot.y + (D3DX_PI * 1.0f)) * (speed * fMoveCoefficientZ);
		move.z += cosf(CameraRot.y + (D3DX_PI * 1.0f)) * (speed * fMoveCoefficientZ);
		spin.y = D3DX_PI * 1.0f - rot.y;

		if (GetThisCharactor()->GetMotion() != 6 &&
			GetThisCharactor()->GetMotion() != 7)

		{//���̃��[�V�������X�e�b�v�ł��e�ł��ł��Ȃ����

		 //���[�V��������
			if (GetThisCharactor()->GetWordManager()->GetBulletFlag())
			{
				GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_SETUP_WALK, CPlayer::UPPER_BODY);
			}
			else
			{
				GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_WALK, CPlayer::UPPER_BODY);
			}
			GetThisCharactor()->SetMotion(CPlayer::MOTION_LOWER_WALK_FRONT, CPlayer::LOWER_BODY);
		}
	}
	else
	{
		if (GetThisCharactor()->GetMotion() != 6 &&
			GetThisCharactor()->GetMotion() != 7)
		{//���̃��[�V�������X�e�b�v�ł��e�ł��ł��Ȃ����
		 //���[�V��������
			if (GetThisCharactor()->GetWordManager()->GetBulletFlag())
			{
				GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_SETUP_NEUTRAL, CPlayer::UPPER_BODY);
			}
			else
			{
				GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_NEUTRAL, CPlayer::UPPER_BODY);
			}
			GetThisCharactor()->SetMotion(CPlayer::MOTION_LOWER_NEUTRAL, CPlayer::LOWER_BODY);
		}

	}

	//�X�e�b�v�ړ��̐ݒ�
	if (CCommand::GetCommand("PLAYERMOVE_STEP", nID))
	{
		if (m_nCntStepCoolTime <= 0)
		{
			//�X�e�b�v�̊p�x�ݒ�
			float fStepRot = rot.y;
			if (CCommand::GetCommand("PLAYERMOVE_UP", nID)) { fStepRot = D3DX_PI * 0.0f; }
			if (CCommand::GetCommand("PLAYERMOVE_DOWN", nID)) { fStepRot = D3DX_PI * 1.0f; }
			if (CCommand::GetCommand("PLAYERMOVE_LEFT", nID))
			{
				fStepRot = D3DX_PI * -0.5f;
				if (CCommand::GetCommand("PLAYERMOVE_UP", nID)) { fStepRot = D3DX_PI * -0.25f; }
				if (CCommand::GetCommand("PLAYERMOVE_DOWN", nID)) { fStepRot = D3DX_PI * -0.75f; }
			}
			if (CCommand::GetCommand("PLAYERMOVE_RIGHT", nID))
			{
				fStepRot = D3DX_PI * 0.5f;
				if (CCommand::GetCommand("PLAYERMOVE_UP", nID)) { fStepRot = D3DX_PI * 0.25f; }
				if (CCommand::GetCommand("PLAYERMOVE_DOWN", nID)) { fStepRot = D3DX_PI * 0.75f; }
			}

			fStepRot += CameraRot.y;

			StepMove(move, fStepRot);

		}
	}
	CDebugProc::Print("cn", "STEP_COOLTIME : ", m_nCntStepCoolTime);

	//�}�V���K���������Ă���Ԃ͈ړ��ʂ�������
	if (GetThisCharactor()->GetbMachineGun() == true)
	{
		move.x *= 0.75f;
		move.z *= 0.75f;
	}
	pos += move;

	//���x�ɌW�����|����
	CUtilityMath::MoveCoeffient(move, GetMoveCoeffient());

	//spin.y = CameraRot.y - rot.y;

	//��]����

	if (GetThisCharactor()->GetbMachineGun() == false)
	{//�e�������Ă��Ȃ��Ƃ��ɉ�]���Ȃ��悤��
		CUtilityMath::RotateNormarizePI(&spin.y);

		rot.y += spin.y * GetSpinCoeffient();

		CUtilityMath::RotateNormarizePI(&rot.y);

		spin.y = 0.0f;
	}

#ifdef _DEBUG
		// ���͏����擾
		CInputKeyboard *pInputKeyboard;
		pInputKeyboard = CManager::GetInputKeyboard();

		if (pInputKeyboard->GetTrigger(DIK_NUMPAD2))
		{
			m_nTargetWP = 1;
		}
		if (pInputKeyboard->GetTrigger(DIK_NUMPAD8))
		{
			m_nTargetWP = 6;
		}
		if (pInputKeyboard->GetTrigger(DIK_NUMPAD4))
		{
			m_nTargetWP = 3;
		}
		if (pInputKeyboard->GetTrigger(DIK_NUMPAD6))
		{
			m_nTargetWP = 4;
		}
		//�ڕW�̃}�X�̔ԍ���n��
		if (m_pWayPoint != NULL)
		{
			m_pWayPoint->ReturnPointMove();
			int nNextPoint = 0;
			nNextPoint = m_pWayPoint->GetNumTargetPoint(m_nTargetWP);

			if (m_pWayPoint->GetWPbBlock(nNextPoint) == true)
			{
				m_MarkWayPoint = m_pWayPoint->GetNextWayPoint(nNextPoint);
				m_bBlock = true;
			}
			CDebugProc::Print("cn", "�ڕW�}�X :", m_nTargetWP);
			CDebugProc::Print("cn", "���݂̃}�X :", m_pWayPoint->GetNowWP());
		}
#endif
}

//=============================================================================
// CPU�̎v�l����
//=============================================================================
void C3DCharactor::Think_CPU(void)
{
	m_OldCpuThink = m_CpuThink;

	m_CpuMove = CPU_MOVE_NONE;
	m_CpuNode = CPU_NODE_NONE;


	//�v���g�^�C�v�p
	switch (GetThisCharactor()->GetID())
	{
	case 1:

		break;
	case 2:
		m_Type = CPU_TYPE_HOMING;
		break;
	case 3:
		m_Type = CPU_TYPE_PATROL;
		break;
	default:
		break;
	}

#if 1
	if (m_pWayPoint == NULL)
	{
		m_pWayPoint = CWaypoint::Create(m_RespawnPos, 10, 10, "NUMBER");
	}

	if (m_CpuThink == THINK_NONE)
	{
		if ((GetThisCharactor()->GetWordManager()->GetBulletFlag() == true))
		{	//�e�������Ă���Ƃ�
			m_Type = CPU_TYPE_NONE;
			m_CpuThink = THINK_HAVEBULLET;
			m_nActionTimer = 30;
		}
		else
		{	//�e�������Ă��Ȃ��Ƃ�
			m_CpuThink = THINK_NOTBULLET;
			m_nActionTimer = 30;
		}
	}
#endif

#if 0
	if (m_pWayPoint == NULL)
	{
		m_pWayPoint = CWaypoint::Create(m_RespawnPos, 10, 10, "NUMBER");
	}
	if ((GetThisCharactor()->GetWordManager()->GetBulletFlag() == true))
	{	//�e�������Ă���Ƃ�
		m_Type = CPU_TYPE_NONE;
		m_CpuThink = THINK_HAVEBULLET;
		m_nActionTimer = 30;
	}
	else
	{	//�e�������Ă��Ȃ��Ƃ�
		m_CpuThink = THINK_NOTBULLET;
		m_nActionTimer = 30;
	}
#endif

}

//=============================================================================
// CPU�̍s������
//=============================================================================
void C3DCharactor::Action_CPU(void)
{
	D3DXVECTOR3& pos = CCharaBase::GetPosition();
	D3DXVECTOR3& move = CCharaBase::GetMove();
	D3DXVECTOR3& rot = CCharaBase::GetRotation();
	D3DXVECTOR3& spin = CCharaBase::GetSpin();
	float		 speed = CCharaBase::GetSpeed();

	//�s�������s�Ɉڂ�
	switch (m_CpuThink)
	{
	case  THINK_WORD:	//�������l����
		break;
	case  THINK_SIGHT:	//�G���������Ƃ�
		break;
	case  THINK_MISSING:	//�G����������
		Homing_CPU();
		break;
	case  THINK_HAVEBULLET:	//�e�������Ă���Ƃ�
		if (m_bMachineGun == true)
		{
			Attack_CPU();
		}
		else
		{
			HaveBullet_CPU();
		}

		break;
	case  THINK_NOTBULLET:	//�e�������Ă��Ȃ�
		NotBullet_CPU();
		break;
	case  THINK_PICKUP:	//�������E��
		if (m_bGoal == true && m_bNearWard == false && m_bSearch == false)
		{
			PickUP_CPU();
		}
		else if (m_bNotWayPoint == true)
		{
			WayPointMove_CPU();
		}
		else
		{
			//WayPointMove_CPU();
			WayPointRoute_CPU();
		}
		break;
	case  THINK_ESCAPE:	//������
		Homing_CPU();
		break;
	case  THINK_ENEMY_HAVEBULLET:	//�G���e�������Ă���Ƃ�
		break;
	case  THINK_ENEMY_NOBULLET:	//�G���e�������Ă���Ƃ�
		break;
	case  THINK_DODGE:	//���킷
		break;
	case  THINK_ATTACK:	//�U��
		Attack_CPU();
		break;
	case  THINK_NEAR_ENEMY:	//�G���߂�
		break;
	case  THINK_FUR_ENEMY:	//�G������
		break;
	case  THINK_MOVE:	//�ړ�����
		CharaMove_CPU();
		break;
	case  THINK_ROTATION:	//��]����
		m_bFront = false;
		Rotation_CPU();
		break;
	case  THINK_PATROL: //����
		Rotation_CPU();
		break;
	case  THINK_HOMING:	//�ǔ�
		Homing_CPU();
		break;
	case  THINK_WATCH:	//�G������
		Homing_CPU();
		break;
	case  THINK_WAYPOINTMOVE:	//�����_���o�H
		WayPointMove_CPU();
		break;
	case  THINK_WAYPOINTROUTE:	//�����_���o�H
		//WayPointMove_CPU();
		WayPointRoute_CPU();
		break;
	default:
		m_nActionTimer = 0;
		break;
	}

	if (m_CpuThink == THINK_ESCAPE)
	{	//������Ƃ������t�Ɉړ�
		pos.x -= move.x;
		pos.y += move.y;
		pos.z -= move.z;
	}
	else
	{
		pos += move;
	}

	//���x�ɌW�����|����
	CUtilityMath::MoveCoeffient(move, GetMoveCoeffient());

	//�^�C�}�[�����炷
	m_nActionTimer--;

	//�A�N�V�����̎��Ԃ��I��
	if (m_nActionTimer <= 0)
	{
		m_nActionTimer = 0;
		m_CpuThink = THINK_NONE;
	}
}

//=============================================================================
// CPU�̉�]����
//=============================================================================
void C3DCharactor::DiffAngle(float fDiffAngle)
{
	D3DXVECTOR3& rot = CCharaBase::GetRotation();

	// ����
	CUtilityMath::RotateNormarizePI(&fDiffAngle);
	rot.y += fDiffAngle * 0.1f;
	CUtilityMath::RotateNormarizePI(&rot.y);
}

//=============================================================================
// CPU�̏���
//=============================================================================
void C3DCharactor::CharaMove_CPU(void)
{
	CCameraManager* pCameraManager = CManager::GetCameraManager();

	CCamera* pCamera = pCameraManager->GetCamera(GetThisCharactor()->GetCameraName());
	D3DXVECTOR3 CameraRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (pCamera != NULL)
	{
		CameraRot = pCamera->GetRotation();
	}

	D3DXVECTOR3& pos = CCharaBase::GetPosition();
	D3DXVECTOR3& move = CCharaBase::GetMove();
	D3DXVECTOR3& rot = CCharaBase::GetRotation();
	D3DXVECTOR3& spin = CCharaBase::GetSpin();
	float		 speed = CCharaBase::GetSpeed();
	D3DXVECTOR3 ChangeRot(0.0f, 0.0f, 0.0f);


	//�ړ�����
	switch (m_CpuMove)
	{
	case CPU_MOVE_FRONT:
		move.x += sinf(rot.y + (D3DX_PI * 0.0f)) * speed;
		move.z += cosf(rot.y + (D3DX_PI * 0.0f)) * speed;
		break;
	case CPU_MOVE_BACK:
		move.x += sinf(rot.y + (D3DX_PI * 1.0f)) * speed;
		move.z += cosf(rot.y + (D3DX_PI * 1.0f)) * speed;
		break;
	case CPU_MOVE_RIGHT:
		move.x += sinf(rot.y + (D3DX_PI * 0.5f)) * speed;
		move.z += cosf(rot.y + (D3DX_PI * 0.5f)) * speed;
		break;
	case CPU_MOVE_LEFT:
		move.x += sinf(rot.y + (D3DX_PI * -0.5f)) * speed;
		move.z += cosf(rot.y + (D3DX_PI * -0.5f)) * speed;
		break;
	case CPU_MOVE_PATROL:
		if (m_PatrolTimer <= PATROL_FLAME * 1 && m_PatrolTimer > 0)
		{
			ChangeRot.y = (D3DX_PI * 0.0f);
			rot.y = ChangeRot.y;
			move.x += sinf(rot.y + (D3DX_PI * 0.0f)) * speed;
			move.z += cosf(rot.y + (D3DX_PI * 0.0f)) * speed;
		}
		else if (m_PatrolTimer <= PATROL_FLAME * 2 && m_PatrolTimer > PATROL_FLAME * 1)
		{
			ChangeRot.y = (D3DX_PI * 0.5f);
			rot.y = ChangeRot.y;
			move.x += sinf(rot.y + (D3DX_PI * 0.0f)) * speed;
			move.z += cosf(rot.y + (D3DX_PI * 0.0f)) * speed;
		}
		else if (m_PatrolTimer <= PATROL_FLAME * 3 && m_PatrolTimer > PATROL_FLAME * 2)
		{
			ChangeRot.y = (D3DX_PI * 1.0f);
			rot.y = ChangeRot.y;
			move.x += sinf(rot.y + (D3DX_PI * 0.0f)) * speed;
			move.z += cosf(rot.y + (D3DX_PI * 0.0f)) * speed;
		}
		else if (m_PatrolTimer <= PATROL_FLAME * 4 && m_PatrolTimer > PATROL_FLAME * 3)
		{
			ChangeRot.y = (D3DX_PI * -0.5f);
			rot.y = ChangeRot.y;
			move.x += sinf(rot.y + (D3DX_PI * 0.0f)) * speed;
			move.z += cosf(rot.y + (D3DX_PI * 0.0f)) * speed;
		}
		else if (m_PatrolTimer > PATROL_FLAME * 4)
		{
			m_PatrolTimer = 0;
		}
		m_PatrolTimer++;
		break;
	}

	if (CPU_MOVE_PATROL == m_CpuMove)
	{
		rot.y = ChangeRot.y;
	}
	else
	{
		spin.y = rot.y - rot.y;
	}
	//��]����
	CUtilityMath::RotateNormarizePI(&spin.y);

	rot.y += spin.y * GetSpinCoeffient();

	CUtilityMath::RotateNormarizePI(&rot.y);

	spin.y = 0.0f;

}


//=============================================================================
// CPU�̉�]����
//=============================================================================
void C3DCharactor::Rotation_CPU(void)
{
	D3DXVECTOR3& rot = CCharaBase::GetRotation();
	D3DXVECTOR3& spin = CCharaBase::GetSpin();
	D3DXVECTOR3 ChangeRot(0.0f, 0.0f, 0.0f);

	switch (m_CpuRotation)
	{
	case CPU_ROTATION_RIGHT:
		ChangeRot.y = (D3DX_PI * 0.5f) + rot.y;
		break;
	case CPU_ROTATION_LEFT:
		ChangeRot.y = (D3DX_PI * -0.5f) + rot.y;
		break;
	case CPU_ROTATION_BACK:
		ChangeRot.y = (D3DX_PI * 1.0f) + rot.y;
		break;
	}

	//��]����
	spin.y = ChangeRot.y - rot.y;

	//��]����
	CUtilityMath::RotateNormarizePI(&spin.y);

	rot.y += spin.y * GetSpinCoeffient();

	CUtilityMath::RotateNormarizePI(&rot.y);

	spin.y = 0.0f;

	m_CpuThink = THINK_MOVE;
	m_nActionTimer = 20;
	m_CpuMove = CPU_MOVE_FRONT;
}

//=============================================================================
// CPU�̓�������
//=============================================================================
void C3DCharactor::Escape_CPU(void)
{

}

//=============================================================================
// CPU�̒ǔ�(��������)����
//=============================================================================
void C3DCharactor::Homing_CPU(void)
{
	D3DXVECTOR3& Pos = CCharaBase::GetPosition();
	D3DXVECTOR3& move = CCharaBase::GetMove();
	D3DXVECTOR3& rot = CCharaBase::GetRotation();
	D3DXVECTOR3& spin = CCharaBase::GetSpin();
	float		 speed = CCharaBase::GetSpeed();

	float fAngle = CIRCLE_ANGLE;
	float fLength = 0;
	int	nLookPlayer = 0;	//�����Ă���v���C���[�̐�

	if (m_CpuThink == THINK_WATCH)
	{//WATCH�̎��͏�Ɍ���悤��
		fAngle += 50000;
		fLength = 0;
	}
	else if (m_CpuThink == THINK_ESCAPE)
	{//ESCAPE�̎��͖ڐ��ɓ�������������
		fLength = 0;
	}

	//�L�������Ƃ̎˒�����
	switch (GetThisCharactor()->GetPlayerType())
	{
	case CPlayer::TYPE_BARANCE:
		fLength = 30000;
		break;
	case CPlayer::TYPE_POWER:
		fLength = 70000;
		break;
	case CPlayer::TYPE_SPEED:
		fLength = 60000;
		break;
	case CPlayer::TYPE_REACH:
		fLength = 200000;
		break;
	default:
		break;
	}



	CPlayer *pPlayer[MAX_PLAYER];
	D3DXVECTOR3 PlayerPos[MAX_PLAYER];

	D3DXVECTOR3 TargetPos;
	float fCircle = 0;				//����
	float fCompare = 1000000;		//��ׂ�
	int nNearPlayer = 0;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		pPlayer[nCntPlayer] = CManager::GetPlayer(nCntPlayer);			// �v���C���[���擾
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (pPlayer[nCntPlayer] != NULL)
		{
			PlayerPos[nCntPlayer] = pPlayer[nCntPlayer]->GetPosition();	// �v���C���[�̈ʒu���擾
		}
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (pPlayer[nCntPlayer] != NULL)
		{
			if (pPlayer[nCntPlayer]->GetID() != GetThisCharactor()->GetID() && GetThisCharactor()->GetVision(nCntPlayer) == true)
			{//������ID�ƈ�v���Ă��Ȃ���Ύ��s
				// �������v���C���[���Z
				nLookPlayer++;
				 // �����𑪂�
				fCircle = ((Pos.x - PlayerPos[nCntPlayer].x) * (Pos.x - PlayerPos[nCntPlayer].x)) + ((Pos.z - PlayerPos[nCntPlayer].z) * (Pos.z - PlayerPos[nCntPlayer].z));
				if (fCircle < fCompare)
				{	//��ԋ߂��v���C���[���L��
					fCompare = fCircle;
					nNearPlayer = nCntPlayer;
				}
			}
		}
	}

	if (nLookPlayer == 0)
	{//�N��������Ȃ�����
		WayPointMove_CPU();
	}

#if 1
	if (fCompare < 100000 && GetThisCharactor()->GetWordManager()->GetBulletFlag() == false)
	{	// �������ɓ������瓦���邽�߂̏���
		if (m_CpuThink != THINK_WATCH)
		{
			// �v���C���[�ɋ߂Â���
			move.x += sinf(atan2f(PlayerPos[nNearPlayer].x - Pos.x, PlayerPos[nNearPlayer].z - Pos.z)) * speed;
			move.z += cosf(atan2f(PlayerPos[nNearPlayer].x - Pos.x, PlayerPos[nNearPlayer].z - Pos.z)) * speed;
		}
		float DiffDis = (PlayerPos[nNearPlayer].x + Pos.x) / 2;
		TargetPos = D3DXVECTOR3((PlayerPos[nNearPlayer].x + Pos.x) / 2, (PlayerPos[nNearPlayer].y + Pos.y) / 2, (PlayerPos[nNearPlayer].z + Pos.z) / 2);
		// �ړI�̊p�x
		float fDestAngle = atan2f((TargetPos.x - sinf(rot.y)) - Pos.x, (TargetPos.z - cosf(rot.y)) - Pos.z);
		// ����
		float fDiffAngle = fDestAngle - rot.y;
		DiffAngle(fDiffAngle);
		if (fDestAngle > D3DX_PI)
		{
			fDestAngle -= D3DX_PI * 2.0f;
		}
		if (fDestAngle < -D3DX_PI)
		{
			fDestAngle += D3DX_PI * 2.0f;
		}
	}
#endif

	if (fCompare < fLength && GetThisCharactor()->GetWordManager()->GetBulletFlag() == true)
	{// �������ɓ���e�������Ă��鎞
		TargetPos = D3DXVECTOR3((PlayerPos[nNearPlayer].x + Pos.x) / 2, (PlayerPos[nNearPlayer].y + Pos.y) / 2, (PlayerPos[nNearPlayer].z + Pos.z) / 2);
		if (m_bMachineGun == false)
		{
			// �ړI�̊p�x
			float fDestAngle = atan2f((TargetPos.x - sinf(rot.y)) - Pos.x, (TargetPos.z - cosf(rot.y)) - Pos.z);
			// ����
			float fDiffAngle = fDestAngle - rot.y;
			CUtilityMath::RotateNormarizePI(&fDiffAngle);
			DiffAngle(fDiffAngle);
			if (fDestAngle > D3DX_PI)
			{
				fDestAngle -= D3DX_PI * 2.0f;
			}
			if (fDestAngle < -D3DX_PI)
			{
				fDestAngle += D3DX_PI * 2.0f;
			}
			//������ɓ������猂��
			if (fDestAngle - 0.11f < rot.y && fDestAngle + 0.11f > rot.y)
			{
				m_CpuThink = THINK_ATTACK;
				m_nActionTimer = 60;
			}
		}
		else if(m_bMachineGun == true)
		{
			m_CpuThink = THINK_ATTACK;
			m_nActionTimer = 60;
		}
	}
	else if (fCompare >= fLength && GetThisCharactor()->GetWordManager()->GetBulletFlag() == true && m_CpuThink != THINK_MISSING)
	{// �����O�Œe�������Ă��鎞
		float	fMinCircle = 1000000;
		int nNumWP = 0;

#if 0
		//�ʒu�����擾
		m_pWayPointPos = &m_pWayPoint->ReturnPointMove();
		//�ړ��\�ȃ}�X�͉��}�X���邩
		int nCntWP = m_pWayPoint->CntWayPoint();
		//�ǂ̃}�X�Ɉړ����邩���߂�
		for (int nCnt = 0; nCnt < nCntWP; nCnt++)
		{
			// �����𑪂� ��ԋ߂��G�Ǝ����̎���̃E�F�C�|�C���g���ׂĂǂ̃|�C���g�ɍs�������߂�
			float fCircle = ((PlayerPos[nNearPlayer].x - m_pWayPointPos[nCnt].x) * (PlayerPos[nNearPlayer].x - m_pWayPointPos[nCnt].x)) + ((PlayerPos[nNearPlayer].z - m_pWayPointPos[nCnt].z) * (PlayerPos[nNearPlayer].z - m_pWayPointPos[nCnt].z));
			if (fCircle < fMinCircle)
			{
				fMinCircle = fCircle;
				nNumWP = nCnt;
				m_nTargetWP = nCnt;
			}
		}

		//�ڕW�̃}�X�̈ʒu��n��
		m_MarkWayPoint = m_pWayPointPos[m_nTargetWP];

		// �ړI�̊p�x
		float fDestAngle = atan2f((m_MarkWayPoint.x - sinf(rot.y)) - Pos.x, (m_MarkWayPoint.z - cosf(rot.y)) - Pos.z);
		// ����
		float fDiffAngle = fDestAngle - rot.y;
		DiffAngle(fDiffAngle);
		//�ړ�
		move.x += sinf(atan2f(m_MarkWayPoint.x - Pos.x, m_MarkWayPoint.z - Pos.z)) * speed;
		move.z += cosf(atan2f(m_MarkWayPoint.x - Pos.x, m_MarkWayPoint.z - Pos.z)) * speed;

		if (GetThisCharactor()->GetMotion() != 6 &&
			GetThisCharactor()->GetMotion() != 7)
		{//���̃��[�V�������X�e�b�v�ł��e�ł��ł��Ȃ����
		 //���[�V��������
			if (GetThisCharactor()->GetWordManager()->GetBulletFlag())
			{
				GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_SETUP_WALK, CPlayer::UPPER_BODY);
			}
			else
			{
				GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_WALK, CPlayer::UPPER_BODY);
			}
			GetThisCharactor()->SetMotion(CPlayer::MOTION_LOWER_WALK_FRONT, CPlayer::LOWER_BODY);
		}
#endif
		WayPointMove_CPU();
	}
	else if (m_CpuThink == THINK_MISSING)
	{// �߂��ɓG�����Ȃ��Č��������Ƃ�
		float	fMinCircle = 100000000;
		int nNumWP = 0;
#if 1

		for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
		{
			if (pPlayer[nCntPlayer] != NULL)
			{
				if (pPlayer[nCntPlayer]->GetID() != GetThisCharactor()->GetID())
				{
					// �����𑪂�
					fCircle = ((Pos.x - PlayerPos[nCntPlayer].x) * (Pos.x - PlayerPos[nCntPlayer].x)) + ((Pos.z - PlayerPos[nCntPlayer].z) * (Pos.z - PlayerPos[nCntPlayer].z));
					if (fCircle < fCompare)
					{	//��ԋ߂��v���C���[���L��
						nNearPlayer = nCntPlayer;
					}
				}
			}
		}

		//�ڕW�̃}�X�̈ʒu��n��
		m_MarkWayPoint = PlayerPos[nNearPlayer];
		// �ړI�̊p�x
		float fDestAngle = atan2f((m_MarkWayPoint.x - sinf(rot.y)) - Pos.x, (m_MarkWayPoint.z - cosf(rot.y)) - Pos.z);
		// ����
		float fDiffAngle = fDestAngle - rot.y;
		DiffAngle(fDiffAngle);
		//�ړ�
		move.x += sinf(atan2f(m_MarkWayPoint.x - Pos.x, m_MarkWayPoint.z - Pos.z)) * speed;
		move.z += cosf(atan2f(m_MarkWayPoint.x - Pos.x, m_MarkWayPoint.z - Pos.z)) * speed;

		//�ړ����ɕǂɂԂ�����
		if (m_bFront == true)
		{
			m_CpuThink = THINK_ROTATION;
			m_nActionTimer = 2;
			m_CpuRotation = (CPU_ROTATION)(rand() % 2);
			m_bFront = false;
		}

		if (GetThisCharactor()->GetMotion() != 6 &&
			GetThisCharactor()->GetMotion() != 7)
		{//���̃��[�V�������X�e�b�v�ł��e�ł��ł��Ȃ����
		 //���[�V��������
			if (GetThisCharactor()->GetWordManager()->GetBulletFlag())
			{
				GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_SETUP_WALK, CPlayer::UPPER_BODY);
			}
			else
			{
				GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_WALK, CPlayer::UPPER_BODY);
			}
			GetThisCharactor()->SetMotion(CPlayer::MOTION_LOWER_WALK_FRONT, CPlayer::LOWER_BODY);
		}
#endif
	}
}

//=============================================================================
// CPU�̍U������
//=============================================================================
void C3DCharactor::Attack_CPU(void)
{
	CSound *pSound = CManager::GetSound();		//	���̎擾

	C3DCharactor* pChara = NULL;
	int nNear = GetThisCharactor()->GetNearPlayer();

	//�e�̐���	�e�������Ă���Ƃ�����
	if (GetThisCharactor()->GetWordManager()->GetBulletFlag() == true && CGame::GetbStageSet() == false)
	{
		switch (GetThisCharactor()->GetPlayerType())
		{
		case CPlayer::TYPE_BARANCE:
			GetThisCharactor()->GetWordManager()->BulletCreate(GetThisCharactor()->GetID(), CCharaBase::GetPosition(), CCharaBase::GetRotation(), GetThisCharactor()->GetPlayerType());
			m_CpuThink = THINK_NONE;
			m_nActionTimer = 0;
			//�{�C�X�Đ�
			if (rand() % 2 == 0)
			{
				pSound->SetVolume(CSound::SOUND_LABEL_VOICE_DOG_ATTACK00, 5.0f);
				pSound->PlaySound(CSound::SOUND_LABEL_VOICE_DOG_ATTACK00);
			}
			else
			{
				pSound->SetVolume(CSound::SOUND_LABEL_VOICE_DOG_ATTACK01, 5.0f);
				pSound->PlaySound(CSound::SOUND_LABEL_VOICE_DOG_ATTACK01);
			}
			break;
		case CPlayer::TYPE_POWER:
			GetThisCharactor()->GetWordManager()->BulletCreate(GetThisCharactor()->GetID(), CCharaBase::GetPosition(), CCharaBase::GetRotation(), GetThisCharactor()->GetPlayerType());
			m_CpuThink = THINK_NONE;
			m_nActionTimer = 0;
			//�{�C�X�Đ�
			if (rand() % 2 == 0)
			{
				pSound->SetVolume(CSound::SOUND_LABEL_VOICE_BEAR_ATTACK00, 5.0f);
				pSound->PlaySound(CSound::SOUND_LABEL_VOICE_BEAR_ATTACK00);
			}
			else
			{
				pSound->SetVolume(CSound::SOUND_LABEL_VOICE_BEAR_ATTACK01, 5.0f);
				pSound->PlaySound(CSound::SOUND_LABEL_VOICE_BEAR_ATTACK01);
			}
			break;
		case CPlayer::TYPE_SPEED:
			pChara = (C3DCharactor*)CManager::GetPlayer(nNear)->GetCharaMover();
			GetThisCharactor()->GetWordManager()->BulletCreate(GetThisCharactor()->GetID(), CCharaBase::GetPosition(), CCharaBase::GetRotation(), GetThisCharactor()->GetPlayerType(), pChara);
			m_CpuThink = THINK_NONE;
			m_nActionTimer = 0;
			//�{�C�X�Đ�
			if (rand() % 2 == 0)
			{
				pSound->SetVolume(CSound::SOUND_LABEL_VOICE_CAT_ATTACK01, 5.0f);
				pSound->PlaySound(CSound::SOUND_LABEL_VOICE_CAT_ATTACK01);
			}
			else
			{
				pSound->SetVolume(CSound::SOUND_LABEL_VOICE_CAT_ATTACK01, 5.0f);
				pSound->PlaySound(CSound::SOUND_LABEL_VOICE_CAT_ATTACK01);
			}
			break;
		case CPlayer::TYPE_REACH:
			m_bMachineGun = true;

		default:
			break;
		}
		GetThisCharactor()->SetStealth(false);
	}
	else if(GetThisCharactor()->GetWordManager()->GetBulletFlag() == false
		&& GetThisCharactor()->GetWordManager()->GetCntNum() > 1 && CGame::GetbStageSet() == false)
	{
	//	GetThisCharactor()->GetWordManager()->BulletCreate(GetThisCharactor()->GetID(), CCharaBase::GetPosition(), CCharaBase::GetRotation(), GetThisCharactor()->GetPlayerType());
	}


	//�}�V���K������
	if (m_bMachineGun == true)
	{
		m_nMachineGunTime++;

		if (m_nMachineGunTime == 1)
		{	//�{�C�X�Đ�
			if (rand() % 2 == 0)
			{
				pSound->SetVolume(CSound::SOUND_LABEL_VOICE_RABBIT_ATTACK00, 5.0f);
				pSound->PlaySound(CSound::SOUND_LABEL_VOICE_RABBIT_ATTACK00);
			}
			else
			{
				pSound->SetVolume(CSound::SOUND_LABEL_VOICE_RABBIT_ATTACK01, 5.0f);
				pSound->PlaySound(CSound::SOUND_LABEL_VOICE_RABBIT_ATTACK01);
			}
		}


		if (m_nMachineGunTime % 10 == 0)
		{//10�t���[���Ɉ��e����
			m_MachineGunPos.x = (float)(rand() % 16) - (rand() % 16);
			m_MachineGunPos.z = (float)(rand() % 16) - (rand() % 16);
			GetThisCharactor()->GetWordManager()->BulletCreate(GetThisCharactor()->GetID(), CCharaBase::GetPosition() + m_MachineGunPos, CCharaBase::GetRotation(), GetThisCharactor()->GetPlayerType(), NULL);
		}
		else if (m_nMachineGunTime > 60)
		{//6�񔭎˂�����e�����폜
			m_bMachineGun = false;
			GetThisCharactor()->GetWordManager()->Reset();
			m_CpuThink = THINK_NONE;
			m_nMachineGunTime = 0;
		}
		else if (GetThisCharactor()->GetWordManager()->GetStock(0) == NOT_NUM)
		{//�S�~���f���p�̔���
			GetThisCharactor()->GetWordManager()->BulletCreate(GetThisCharactor()->GetID(), CCharaBase::GetPosition() + m_MachineGunPos, CCharaBase::GetRotation(), GetThisCharactor()->GetPlayerType(), NULL);
			m_bMachineGun = false;
			GetThisCharactor()->GetWordManager()->Reset();
			m_nMachineGunTime = 0;
			m_CpuThink = THINK_NONE;
		}
	}

}

//=============================================================================
// CPU�̕����T������
//=============================================================================
void C3DCharactor::PickUP_CPU(void)
{
	D3DXVECTOR3& Pos = CCharaBase::GetPosition();
	D3DXVECTOR3& move = CCharaBase::GetMove();
	D3DXVECTOR3& rot = CCharaBase::GetRotation();
	D3DXVECTOR3& spin = CCharaBase::GetSpin();
	float		 speed = CCharaBase::GetSpeed();

	CScene *pScene = NULL;
	m_fCompareRange = 1000000;	//�����̋�������߂����̂�I��
								//D3DXVECTOR3 MOKUHYO;	//��ԋ߂��ڕW�ʒu
	bool bWord = false;		//������������
	bool bTango = false;	//�P�ꂪ��������\��������
	int nCntNearWord = 0;		//�߂��ɉ����������邩

								// �擪�̃I�u�W�F�N�g���擾
	pScene = CScene::GetTop(5);

	int nCntData = GetThisCharactor()->GetWordManager()->SearchWord();	// �g�ݗ��Ă�����̉񐔂��擾
	float *fAnswerNum = NULL;
	if (nCntData > 0)
	{	// ��₪0�ȏ�̏ꍇ
		fAnswerNum = GetThisCharactor()->GetWordManager()->GetAnswerData();	// �������擾
	}

	while (pScene != NULL)
	{// �D�揇�ʂ�5�̃I�u�W�F�N�g��1��1�m���߂�
	 // �����̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// ���S�t���O�������Ă��Ȃ�����
			if (pScene->GetObjType() == CScene::OBJTYPE_WORD)
			{// �I�u�W�F�N�g�̎�ނ��m���߂�
				CWord *pWord = ((CWord*)pScene);		// CWord�փL���X�g(�^�̕ύX)
														// �����𑪂�
				float fCircle = ((Pos.x - pWord->GetPos().x) * (Pos.x - pWord->GetPos().x)) + ((Pos.z - pWord->GetPos().z) * (Pos.z - pWord->GetPos().z));
				if (bTango == false)
				{
					float fNum = (float)pWord->GetWordNum();	// �����̔ԍ����擾
					for (int nCntAnswer = 0; nCntAnswer < nCntData; nCntAnswer++)
					{	// ���̐��񂵂� �����ԍ��ƍ����Ă��邩���r
						if (fAnswerNum[nCntAnswer] == fNum)
						{	// �����Ă����ꍇ �ʒu���擾��break����
							m_fCompareRange = fCircle;
							m_MarkWardPos = pWord->GetPos();
							bWord = true;
							bTango = true;
							break;
						}

					}
					if (bTango == true)
					{
						break;
					}
				}

				if (GetThisCharactor()->GetWordManager()->GetCntNum() < 3 && fCircle < 50000 && bTango == false)
				{//�͈͓��ɕ�����������
					nCntNearWord++;
					 //��ԋ߂��������L��
					m_fCompareRange = fCircle;
					m_MarkWardPos = pWord->GetPos();
					bWord = true;
				}
			}
		}
		// ���̃V�[���ɐi�߂�
		pScene = pSceneNext;
	}

	//if (GetThisCharactor()->GetWordManager()->GetCntNum() == 2 && bTango == false)
	//{//
	//	m_CpuThink = THINK_ATTACK;
	//	m_nActionTimer = 60;
	//	bWord = true;
	//}

	//���[�h���͈͓��ɂ��鎞�ړ�����
	if (bWord == true)
	{
		WayPointRoute_CPU();
		m_nActionTimer = 120;
	}
	else if (nCntNearWord == 0)
	{//�߂��ɕ���������Ȃ�
		m_bWordNear = false;
		m_CpuThink = THINK_WAYPOINTMOVE;
		m_nActionTimer = 120;
	}

}

//=============================================================================
// �e�������Ă���Ƃ��̏���
//=============================================================================
void C3DCharactor::HaveBullet_CPU(void)
{
	int	nCntNear = 0;

	//�N���߂���
	NearOrFur_CPU();
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (m_bNear[nCntPlayer] == true)
		{
			nCntNear++;
		}
	}

	if (nCntNear > 0)
	{//�߂��ɓG������
		m_CpuThink = THINK_HOMING;
		m_nActionTimer = 60;
	}
	else
	{//�߂��ɓG�����Ȃ�
		m_CpuThink = THINK_MISSING;
		m_CpuMove = CPU_MOVE_FRONT;
		m_nActionTimer = 60;
	}

}

//=============================================================================
// �e�������Ă��Ȃ����̏���
//=============================================================================
void C3DCharactor::NotBullet_CPU(void)
{
	bool bPICKUP = false;
	int	nCntNear = 0;

	//�N���߂���
	NearOrFur_CPU();
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (m_bNear[nCntPlayer] == true)
		{
			nCntNear++;
		}
	}

	if (nCntNear < 3)
	{
		m_CpuThink = THINK_PICKUP;
		m_nActionTimer = 120;
	}
	else
	{
		m_CpuThink = THINK_PICKUP;
		m_nActionTimer = 120;
	}
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		m_bNear[nCntPlayer] = false;
	}

}

//=============================================================================
// �߂���������
//=============================================================================
void C3DCharactor::NearOrFur_CPU(void)
{
	D3DXVECTOR3& Pos = CCharaBase::GetPosition();

	CPlayer *pPlayer[MAX_PLAYER];
	D3DXVECTOR3 PlayerPos[MAX_PLAYER];
	m_fCompareRange = 1000000;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		pPlayer[nCntPlayer] = CManager::GetPlayer(nCntPlayer);			// �v���C���[���擾
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (pPlayer[nCntPlayer] != NULL)
		{
			PlayerPos[nCntPlayer] = pPlayer[nCntPlayer]->GetPosition();	// �v���C���[�̈ʒu���擾
		}
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (pPlayer[nCntPlayer] != NULL)
		{
			if (pPlayer[nCntPlayer]->GetID() != GetThisCharactor()->GetID())
			{//������ID�ƈ�v���Ă��Ȃ���Ύ��s
			 // �����𑪂�
				float fCircle = ((Pos.x - PlayerPos[nCntPlayer].x) * (Pos.x - PlayerPos[nCntPlayer].x)) + ((Pos.z - PlayerPos[nCntPlayer].z) * (Pos.z - PlayerPos[nCntPlayer].z));
				if (fCircle < 80000)
				{
					m_bNear[nCntPlayer] = true;
				}
			}
		}
	}
}

//=============================================================================
//�@�}�X�ڃ����_���ړ�
//=============================================================================
void C3DCharactor::WayPointMove_CPU(void)
{
	D3DXVECTOR3& Pos = CCharaBase::GetPosition();
	D3DXVECTOR3& move = CCharaBase::GetMove();
	D3DXVECTOR3& rot = CCharaBase::GetRotation();
	D3DXVECTOR3& spin = CCharaBase::GetSpin();
	float		 speed = CCharaBase::GetSpeed();

	int nRandPos = 0;
	int nNextPoint = 0;
	int nNowWp = 0;

	float fCircle = ((Pos.x - m_MarkWayPoint.x) * (Pos.x - m_MarkWayPoint.x)) + ((Pos.z - m_MarkWayPoint.z) * (Pos.z - m_MarkWayPoint.z));

	//�ڕW���߂���
	if (fCircle < 100)
	{
		m_bRandomGoal = true;
		if (m_bNotWayPoint == true)
		{
			m_bNotWayPoint = false;
		}
		m_nActionTimer = 0;
		m_CpuThink = THINK_NONE;
	}

	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	if (m_bRandomGoal == true)
	{
		//�ʒu�����擾
		m_pWayPointPos = &m_pWayPoint->ReturnPointMove();
		//�ړ��\�ȃ}�X�͉��}�X���邩
		int nCntWP = m_pWayPoint->CntWayPoint();
		//�����_���Ō��߂�
		int nRand = 0;

		if (nCntWP != 0)
		{
			nRand = rand() % nCntWP;
		}

		m_pWayPoint->ReturnPointMove();
		nNextPoint = m_pWayPoint->GetNumTargetPoint(nRand);
		nNowWp = m_pWayPoint->GetNowWP();

		if (m_pWayPointPos[nRand] != NULL)
		{
			//m_MarkWayPoint = m_pWayPointPos[nRand];
			m_MarkWayPoint = m_pWayPoint->GetNextWayPoint(nNextPoint);
			m_bRandomGoal = false;
		}
	}
	else if (m_bRandomGoal == false && m_bNotWayPoint == false)
	{//���ǂ蒅���Ȃ���Ԃ�������
		m_nTimerMove++;
		if (m_nTimerMove >= 150)
		{
			m_nTimerMove = 0;
			m_bNotWayPoint = true;
		}
	}

	//���ǂ蒅���Ȃ����� �ڕW��T���Ȃ���
	if (m_bNotWayPoint == true)
	{
		m_nTimerMove++;

		if (m_nTimerMove >= 30)
		{
			m_nTimerMove = 0;
			m_bRandomGoal = true;
			m_bNotWayPoint = false;
			m_CpuThink = THINK_NONE;
		}
	}

	//�ړ����ɕǂɂԂ�����
	if (m_bFront == true)
	{
		m_CpuThink = THINK_ROTATION;
		m_nActionTimer = 2;
		m_CpuRotation = (CPU_ROTATION)(rand() % 2);
		m_bFront = false;
	}

	// �ړI�̊p�x
	float fDestAngle = atan2f((m_MarkWayPoint.x - sinf(rot.y)) - Pos.x, (m_MarkWayPoint.z - cosf(rot.y)) - Pos.z);
	// ����
	float fDiffAngle = fDestAngle - rot.y;
	DiffAngle(fDiffAngle);
	//�ړ�
	move.x += sinf(atan2f(m_MarkWayPoint.x - Pos.x, m_MarkWayPoint.z - Pos.z)) * speed;
	move.z += cosf(atan2f(m_MarkWayPoint.x - Pos.x, m_MarkWayPoint.z - Pos.z)) * speed;

	if (GetThisCharactor()->GetMotion() != 6 &&
		GetThisCharactor()->GetMotion() != 7)
	{//���̃��[�V�������X�e�b�v�ł��e�ł��ł��Ȃ����
	 //���[�V��������
		if (GetThisCharactor()->GetWordManager()->GetBulletFlag())
		{
			GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_SETUP_WALK, CPlayer::UPPER_BODY);
		}
		else
		{
			GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_WALK, CPlayer::UPPER_BODY);
		}
		GetThisCharactor()->SetMotion(CPlayer::MOTION_LOWER_WALK_FRONT, CPlayer::LOWER_BODY);
	}

	//�������L��
	m_fOldCircle = fCircle;

#ifdef _DEBUG
	CDebugProc::Print("cfcfcf", "�ڕW�̃}�X�̈ʒu : X ", m_MarkWayPoint.x, " Y ", m_MarkWayPoint.y, " Z ", m_MarkWayPoint.z);
#endif
}

//=============================================================================
//�ŒZ���[�g����
//=============================================================================
void C3DCharactor::WayPointRoute_CPU(void)
{
#if 1
	D3DXVECTOR3& Pos = CCharaBase::GetPosition();
	D3DXVECTOR3& move = CCharaBase::GetMove();
	D3DXVECTOR3& rot = CCharaBase::GetRotation();
	D3DXVECTOR3& spin = CCharaBase::GetSpin();
	float		 speed = CCharaBase::GetSpeed();

	D3DXVECTOR3 MarkPos;	//��ԋ߂��ڕW�ʒu
	float	fMinCircle = 100000;
	int nRandPos = 0;
	int nNextPoint = 0;
	int nNowWp = 0;

	if (m_bGoal == true && /*m_bNearWard == false &&*/ m_bSearch == false)
	{
		//�ʒu�����擾
		m_pWayPointPos = &m_pWayPoint->ReturnPointMove();
		//�ړ��\�ȃ}�X�͉��}�X���邩
		int nCntWP = m_pWayPoint->CntWayPoint();
		//�ǂ̃}�X�Ɉړ����邩���߂�
		for (int nCnt = 0; nCnt < nCntWP; nCnt++)
		{
			// �����𑪂� ��ԋ߂������ƃE�F�C�|�C���g���ׂĂǂ̃|�C���g�ɍs�������߂�
			float fCircle = ((m_MarkWardPos.x - m_pWayPointPos[nCnt].x) * (m_MarkWardPos.x - m_pWayPointPos[nCnt].x)) + ((m_MarkWardPos.z - m_pWayPointPos[nCnt].z) * (m_MarkWardPos.z - m_pWayPointPos[nCnt].z));
			if (fCircle < fMinCircle)
			{
				fMinCircle = fCircle;
				//�ڕW�̃}�X�ԍ����L��
				m_nTargetWP = nCnt;
				if (m_bNearWard == false)
				{
					m_bSearch = true;
					m_bGoal = false;
				}
			}
		}
	}

	//�ړ�����
	//�ڕW�̃}�X�̔ԍ���n��
	if (m_bSearch == true)
	{
		m_pWayPoint->ReturnPointMove();
		nNextPoint = m_pWayPoint->GetNumTargetPoint(m_nTargetWP);
		nNowWp = m_pWayPoint->GetNowWP();
		//�ڕW�ɂ��Ă�����
		//if (m_pWayPoint->GetWPbBlock(nNowWp) == true)
		//{//�������u���b�N�}�X�ɂ��邩�̔���
		//	m_CpuThink = THINK_WAYPOINTMOVE;
		//	m_nActionTimer = 60;
		//	m_bGoal = false;
		//}

		if (nNextPoint > MAX_WAYPOINT)
		{
			nNextPoint = 0;
		}
		if (nNextPoint < 0)
		{
			nNextPoint = 0;
			nNextPoint = m_pWayPoint->GetNumTargetPoint(m_nTargetWP);
			nNowWp = m_pWayPoint->GetNowWP();
		}

		if (m_pWayPoint->GetWPbBlock(nNextPoint) == true && m_bNearWard == false)
		{//�ڕW�}�X���u���b�N�@�߂��ɕ������Ȃ�
			m_MarkWayPoint = m_pWayPoint->GetNextWayPoint(nNextPoint);
		}
		else if (m_pWayPoint->GetWPbBlock(nNextPoint) == false && m_bNearWard == false)
		{//�ڕW�}�X���u���b�N�ł͂Ȃ��@�߂��ɕ������Ȃ�
			m_MarkWayPoint = m_pWayPoint->GetNextWayPoint(nNextPoint);
		}
		else if (m_bNearWard == true || m_bBlock == false)
		{//�߂��ɕ���������@�u���b�N�}�X�ł͂Ȃ�
			m_MarkWayPoint = m_MarkWardPos;
		}

		m_bSearch = false;
	}

	if (m_bNearWard == true)
	{
		m_pWayPoint->ReturnPointMove();
		nNextPoint = m_pWayPoint->GetNumTargetPoint(m_nTargetWP);
		nNowWp = m_pWayPoint->GetNowWP();

		m_MarkWayPoint = m_MarkWardPos;
	}


	float fCircle = ((Pos.x - m_MarkWayPoint.x) * (Pos.x - m_MarkWayPoint.x)) + ((Pos.z - m_MarkWayPoint.z) * (Pos.z - m_MarkWayPoint.z));

	if (fCircle < 400 && m_bNearWard == false)
	{	//�����̋߂��̃}�X�܂ňړ�����
		m_bNearWard = true;
		m_bGoal = true;
		m_nTimerMove = 0;
	}
	else if (fCircle < 100 && m_bNearWard == true)
	{//�����̋߂��̃}�X�܂ňړ�����
		m_bNearWard = false;
		m_nTimerMove = 0;
		m_CpuThink = THINK_NONE;
		m_nActionTimer = 30;
	}
	else if (m_fOldCircle == fCircle)
	{
		m_nTimerMove++;

		if (m_nTimerMove >= 10)
		{
			m_nTimerMove = 0;
			m_bNotWayPoint = true;
			WayPointMove_CPU();
		}
	}
	else
	{
		//m_nActionTimer = 30;
	}

	//�ړ����ɕǂɂԂ�����
	//if (m_bFront == true)
	//{
	//	m_CpuThink = THINK_ROTATION;
	//	m_nActionTimer = 2;
	//	m_CpuRotation = (CPU_ROTATION)(rand() % 2);
	//	m_bFront = false;
	//}

	// �ړI�̊p�x
	float fDestAngle = atan2f((m_MarkWayPoint.x - sinf(rot.y)) - Pos.x, (m_MarkWayPoint.z - cosf(rot.y)) - Pos.z);
	// ����
	float fDiffAngle = fDestAngle - rot.y;
	DiffAngle(fDiffAngle);
	//�ړ�
	move.x += sinf(atan2f(m_MarkWayPoint.x - Pos.x, m_MarkWayPoint.z - Pos.z)) * speed;
	move.z += cosf(atan2f(m_MarkWayPoint.x - Pos.x, m_MarkWayPoint.z - Pos.z)) * speed;

	if (GetThisCharactor()->GetMotion() != 6 &&
		GetThisCharactor()->GetMotion() != 7)
	{//���̃��[�V�������X�e�b�v�ł��e�ł��ł��Ȃ����
	 //���[�V��������
		if (GetThisCharactor()->GetWordManager()->GetBulletFlag())
		{
			GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_SETUP_WALK, CPlayer::UPPER_BODY);
		}
		else
		{
			GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_WALK, CPlayer::UPPER_BODY);
		}
		GetThisCharactor()->SetMotion(CPlayer::MOTION_LOWER_WALK_FRONT, CPlayer::LOWER_BODY);
	}

	//�������L��
	m_fOldCircle = fCircle;

#endif
}

//=============================================================================
//��ވړ�����
//=============================================================================
void C3DCharactor::WayPointBack_CPU(void)
{
	D3DXVECTOR3& Pos = CCharaBase::GetPosition();
	D3DXVECTOR3& move = CCharaBase::GetMove();
	D3DXVECTOR3& rot = CCharaBase::GetRotation();
	D3DXVECTOR3& spin = CCharaBase::GetSpin();
	float		 speed = CCharaBase::GetSpeed();

	move.x += sinf(rot.y + (D3DX_PI * 1.0f)) * speed;
	move.z += cosf(rot.y + (D3DX_PI * 1.0f)) * speed;
}

//=============================================================================
// �X�e�b�v����
//=============================================================================
void C3DCharactor::StepMove(D3DXVECTOR3& move, float& fRot)
{
	move.x += sinf(fRot) * GetStep();
	move.z += cosf(fRot) * GetStep();

	GetThisCharactor()->SetMotion(CPlayer::MOTION_LOWER_STEP, CPlayer::LOWER_BODY, CPlayer::STATE_NORMAL);
	GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_STEP, CPlayer::UPPER_BODY, CPlayer::STATE_NORMAL);
	m_nCntStepCoolTime = 30;
	GetThisCharactor()->SetTransTime(5);
}