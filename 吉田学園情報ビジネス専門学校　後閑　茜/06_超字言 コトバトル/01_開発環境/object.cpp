//=============================================================================
//
// �I�u�W�F�N�g�̏��� [oblect.cpp]
// Author : �ڍ� ������
//
//=============================================================================
#include "object.h"
#include "input.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "load.h"
#include "player.h"
#include "game.h"
#include "time.h"
#include "scene3D.h"
#include "effect.h"
#include "word.h"
#include "PlayerNumSelect.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define BELTCONVEYER_MOVE			(0.15f)			// �x���g�R���x�A�̑��x
#define KNOCKBACK_MOVE_SMALL		(4.0f)			// �m�b�N�o�b�N�̋��x(��)
#define KNOCKBACK_MOVE_DURING		(6.0f)			// �m�b�N�o�b�N�̋��x(��)
#define KNOCKBACK_MOVE_BIG			(9.0f)			// �m�b�N�o�b�N�̋��x(��)
#define GEAR_ROT_Y					(0.1f)			// �M�A�̉�]�ʁ@�x�[�X���
#define MODEL_MOVE_Y				(-2.0f)			// ���f���ړ����̈ړ����x
#define AFFECTED_LANDING			(15.0f)			// ���f�����n���̃m�b�N�o�b�N�e����

#define ANIM_TIME					(5)				// �A�j���[�V��������
#define ANIM_FRAME					(10)			// �t���[����
#define ICON_SIZE_X					(80.0f)
#define ICON_SIZE_Y					(40.0f)
#define VIBRATION					(2.0f)
#define VIBRATION_MOVE				(4.0f)

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
bool CObject::m_bCreateFlag = false;
bool  CObject::m_bSwitch = false;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObject::CObject()
{
	m_bMoveFlag = false;		// �ړ��t���O
	m_bCreateFlag = false;
	m_pIcon = NULL;				// �x���g�R���x�A�̃A�C�R��
	m_nCntAnim = 0;
	m_nCntPattan = 0;
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fMove = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_InitPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_MoveState = 0;
	m_bSwitch = false;
	m_nCounter = 0;
	m_nTypeGimmick = GIMMICK_NONE;

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObject::~CObject()
{
}

//=============================================================================
// �I�u�W�F�N�g�̐�������
//=============================================================================
CObject *CObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Scale, CSceneX::COLLISIONTYPE type, CLoad::MODEL model, CObject::GIMMICKTYPE realtime,int nNumber)
{
	CObject *pObject = NULL;
	if (pObject == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pObject = new CObject;

		if (pObject != NULL)
		{
			pObject->m_nObjNumber = nNumber;	//�I�u�W�F�N�g�̔ԍ��ݒ�
			pObject->SetModelType(model);
			pObject->BindModel(CLoad::GetBuffMat(model), CLoad::GetNumMat(model), CLoad::GetMesh(model));		// ���f���̊��蓖��
			pObject->SetScale(Scale);	// �X�P�[���̐ݒ�
			pObject->m_nTypeGimmick = realtime;
			pObject->Init(pos);			// ������
			pObject->SetRot(rot);		// �����̐ݒ�
			pObject->SetCollsionType(type);	// �R���W�����̃^�C�v�ݒ�
		}
	}
	return pObject;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CObject::Init(D3DXVECTOR3 pos)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_SCENEX);

	if (m_nTypeGimmick == GIMMICK_MOYE_Y || m_nTypeGimmick == GIMMICK_MOYE_STAGE) { m_nRealTime = REALTIME_INITPOS; }
	else if (m_nTypeGimmick == GIMMICK_NONE) { m_nRealTime = REALTIME_NONE; }

	CSceneX::Init(pos);
	m_posOld = pos;
	m_InitPos = pos;
	if (CSceneX::GetModelType() == CLoad::MODEL_DRAWN_X)
	{//�h���[��X�ړ�
		m_MoveState = 1;
	}
	else if (CSceneX::GetModelType() == CLoad::MODEL_DRAWN_Z)
	{//�h���[��Z�ړ�
		m_MoveState = 1;
	}
	//	�����̑傫���̕ۑ�
	m_InitScale = CSceneX::GetScale();
	// �ԍ���ݒ�
	CSceneX::SetSceneXNum(m_nObjNumber);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CObject::Uninit(void)
{
	if (m_pIcon != NULL)
	{	// �A�C�R���̔j��
		m_pIcon->Uninit();
		m_pIcon = NULL;
	}
	CSceneX::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CObject::Update(void)
{
	CSceneX::COLLISIONTYPE Collsiontype = CSceneX::GetCollsionType();
	D3DXVECTOR3 pos = CSceneX::GetPosition();	// �ʒu�擾

	BGModelMove(pos);				// �w�i���f���̈ړ�

	if (m_nRealTime == REALTIME::REALTIME_NONE) { Rot(CSceneX::GetModelType()); return; }		// �����Ȃ��ꍇ�͉����ʂ��Ȃ�


	ModelMove(Collsiontype, pos);	// ���f���̈ړ�

	if (m_pIcon != NULL) { AnimationIcon(); }


#ifdef _DEBUG
	//CDebugProc::Print("cfccfccfc", "ModelPos : x", m_pos.x, "f", "   y", m_pos.y, "f", "  z", m_pos.z, "f");
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RSHIFT))
	{	// �ړ�Flag�ω��p
		m_nRealTime = REALTIME_ENDPOS;
	}
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void CObject::Draw(void)
{
	if (m_pIcon != NULL)
	{
		m_pIcon->Draw();
	}

	if (CSceneX::GetModelType() != CLoad::MODEL_BOX)
	{
		CSceneX::Draw();
	}
}

//=============================================================================
// /�X�C�b�`�̏���
//=============================================================================
void CObject::SwitchBeltConveyor(bool bSwitch)
{
	CSound *pSound = CManager::GetSound();		//	���̎擾
	D3DXVECTOR3 pos = CSceneX::GetPosition();

	if (bSwitch == true)
	{//	SwitchON
		m_nCounter++;
		if (m_nCounter > 120)
		{
			m_bSwitch = m_bSwitch ? false : true;
			if (m_bSwitch == true)
			{//	SwitchON
				pSound->SetVolume(CSound::SOUND_LABEL_SE_SWITCHON, 3.0f);
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SWITCHON);
			}
			else if (m_bSwitch == false)
			{
				pSound->SetVolume(CSound::SOUND_LABEL_SE_SWITCHOFF, 3.0f);
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SWITCHOFF);
			}
			m_nCounter = 0;
		}
		pos = D3DXVECTOR3(0.0f, -20.0, 0.0f);
		if (m_bSwitch == false)
		{//	SwitchOFF
			m_nCounter++;
			pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		}
	}
	SetPosition(pos);
}

//=============================================================================
// �x���g�R���x�A�̏���
//=============================================================================
void CObject::BeltConveyor(D3DXVECTOR3 *pMove, bool bSwitch)
{
	CSceneX::COLLISIONTYPE Collsiontype = CSceneX::GetCollsionType();

	switch (bSwitch)
	{
	case false:
		if (Collsiontype == CSceneX::COLLSIONTYPE_CONVEYOR_FRONT)
		{	// �O�i����
			pMove->z += BELTCONVEYER_MOVE;
		}
		else if (Collsiontype == CSceneX::COLLSIONTYPE_CONVEYOR_BACK)
		{	// ��ނ���
			pMove->z += -BELTCONVEYER_MOVE;
		}
		else if (Collsiontype == CSceneX::COLLSIONTYPE_CONVEYOR_RIHHT)
		{	// �E�ړ�
			pMove->x += -BELTCONVEYER_MOVE;
		}
		else if (Collsiontype == CSceneX::COLLSIONTYPE_CONVEYOR_LEFT)
		{	// ���ړ�
			pMove->x += BELTCONVEYER_MOVE;
		}
		break;
	case true:
		break;
	}
}

//=============================================================================
// �w�i���f���̋�������
//=============================================================================
void CObject::BGModelMove(D3DXVECTOR3 pos)
{
	CPlayerSelect::SELECTPLAYER NumPlayer = {};
	NumPlayer = *CPlayerSelect::GetModeSelectMode();	// �v���C���[�l���擾
	D3DXVECTOR2 size = {};

	if (NumPlayer == CPlayerSelect::SELECTPLAYER_1P || NumPlayer == CPlayerSelect::SELECTPLAYER_2P) { size = MAX_SIZE; }
	else if (NumPlayer == CPlayerSelect::SELECTPLAYER_4P || NumPlayer == CPlayerSelect::SELECTPLAYER_3P) { size = MAX_SIZE_3or4; }

	D3DXVECTOR3 scale = CSceneX::GetScale();
	if (CSceneX::GetModelType() == CLoad::MODEL_DRAWN_X)
	{//�@X���W�̈ړ�������h���[��
		m_nCounter++;
		int nAnswer = rand() % 48;
		//	�g���Ă��Ȃ������̗�O����
		if (nAnswer == 0 || nAnswer == 2 || nAnswer == 4 || nAnswer == 6 || nAnswer == 8 || nAnswer == 11) { nAnswer = 1; }
		else if (nAnswer == 13 || nAnswer == 14 || nAnswer == 16 || nAnswer == 17 || nAnswer == 18 || nAnswer == 21) { nAnswer = 7; }
		else if (nAnswer == 22 || nAnswer == 23 || nAnswer == 25 || nAnswer == 26 || nAnswer == 28 || nAnswer == 29) { nAnswer = 15; }
		else if (nAnswer == 31 || nAnswer == 32 || nAnswer == 33 || nAnswer == 34 || nAnswer == 36 || nAnswer == 37) { nAnswer = 30; }
		else if (nAnswer == 38 || nAnswer == 39 || nAnswer == 43 || nAnswer == 44 || nAnswer == 45 || nAnswer == 46) { nAnswer = 35; }
		else if (nAnswer == 47 || nAnswer == 48) { nAnswer = 17; }
		if (m_nCounter % 780 == 0)
		{//	�������o��
			if (CManager::GetMode() == CManager::MODE_GAME)
			{

				CWord::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), size.x, size.y, "WORD", nAnswer, 1, 45);
				scale.y = m_InitScale.y + 0.2f;
				pos.y = m_InitPos.y + 4.0f;
				m_nCounter = 0;
			}
		}
		if (m_nCounter > 20)
		{//	�傫����߂�
			scale.y = m_InitScale.y;
			pos.y = m_InitPos.y;
		}
		if (m_InitPos.x + 200 <= pos.x)
		{//	�����ʒu����+250�ȏ㗣�ꂽ�ꍇ
			m_MoveState = 2;
		}
		else if (m_InitPos.x - 200 >= pos.x)
		{//	�����ʒu����-250�ȏ㗣�ꂽ�ꍇ
			m_MoveState = 1;
		}
		switch (m_MoveState)
		{//	�����̃X�e�[�^�X
		case 0:
			m_move.x = 0.0f;
			break;
		case 1:
			m_move.x = 1.0f;
			break;
		case 2:
			m_move.x = -1.0f;
			break;
		}
		pos += m_move;				//	�����̉��Z

	}
	else if (CSceneX::GetModelType() == CLoad::MODEL_DRAWN_Z)
	{//�@X���W�̈ړ�������h���[��
		m_nCounter++;
		int nAnswer = rand() % 48;
		//	�g���Ă��Ȃ������̗�O����
		if (nAnswer == 0 || nAnswer == 2 || nAnswer == 4 || nAnswer == 6 || nAnswer == 8 || nAnswer == 11) { nAnswer = 1; }
		else if (nAnswer == 13 || nAnswer == 14 || nAnswer == 16 || nAnswer == 17 || nAnswer == 18 || nAnswer == 21) { nAnswer = 7; }
		else if (nAnswer == 22 || nAnswer == 23 || nAnswer == 25 || nAnswer == 26 || nAnswer == 28 || nAnswer == 29) { nAnswer = 15; }
		else if (nAnswer == 31 || nAnswer == 32 || nAnswer == 33 || nAnswer == 34 || nAnswer == 36 || nAnswer == 37) { nAnswer = 30; }
		else if (nAnswer == 38 || nAnswer == 39 || nAnswer == 43 || nAnswer == 44 || nAnswer == 45 || nAnswer == 46) { nAnswer = 35; }
		else if (nAnswer == 47 || nAnswer == 48) { nAnswer = 17; }

		if (m_nCounter % 780 == 0)
		{//	�������o��
			if (CManager::GetMode() == CManager::MODE_GAME)
			{
				CWord::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), size.x, size.y, "WORD", nAnswer, 1, 45);
				scale.y = m_InitScale.y + 0.2f;
				pos.y = m_InitPos.y + 2.0f;
				m_nCounter = 0;
			}
		}
		if (m_nCounter > 20)
		{//	�傫����߂�
			scale.y = m_InitScale.y;
			pos.y = m_InitPos.y;
		}
		if (m_InitPos.z + 200 <= pos.z)
		{//	�����ʒu����+250�ȏ㗣�ꂽ�ꍇ
			m_MoveState = 2;
		}
		else if (m_InitPos.z - 200 >= pos.z)
		{//	�����ʒu����-250�ȏ㗣�ꂽ�ꍇ
			m_MoveState = 1;
		}
		switch (m_MoveState)
		{//	�����̃X�e�[�^�X
		case 0:
			m_move.z = 0.0f;
			break;
		case 1:
			m_move.z = 1.0f;
			break;
		case 2:
			m_move.z = -1.0f;
			break;
		}
		pos += m_move;				//	�����̉��Z
	}

	if (CSceneX::GetModelType() == CLoad::MODEL_ALPHAMODEL00)
	{
		m_nCounter++;
		if (m_nCounter > 0 && m_nCounter < 360)
		{
			pos.y = 1000.0f;
			scale.x = 0.0f;
			scale.z = 0.0f;
		}
		else if (m_nCounter > 360 && m_nCounter < 360 * 2)
		{
			pos.y = 0.0f;
			//scale.x = m_InitScale.x;
			//scale.z = m_InitScale.z;
			scale.x = 0.0f;
			scale.z = 0.0f;
		}
		else  if (m_nCounter > 360 * 2)
		{
			m_nCounter = 0;
		}
		if (m_nCounter % 20 == 0)
		{//	���G�t�F�N�g
			if (m_InitScale.x == 2.3f) { CEffect::Create(pos + D3DXVECTOR3(0.0f, 15.0f, 0.0f), 2, 0); }
			else { CEffect::Create(pos + D3DXVECTOR3(0.0f, 15.0f, 0.0f), 2, 1); }
		}
		else if (m_nCounter % 30 == 0)
		{//	���G�t�F�N�g
			if (m_InitScale.x == 2.3f) { CEffect::Create(pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), 2, 0); }
			else { CEffect::Create(pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), 2, 1); }
		}
		else if (m_nCounter % 40 == 0)
		{//	���G�t�F�N�g
			if (m_InitScale.x == 2.3f) { CEffect::Create(pos + D3DXVECTOR3(0.0f, 25.0f, 0.0f), 2, 0); }
			else { CEffect::Create(pos + D3DXVECTOR3(0.0f, 25.0f, 0.0f), 2, 1); }
		}
	}
	else if (CSceneX::GetModelType() == CLoad::MODEL_ALPHAMODEL01)
	{
		m_nCounter++;
		if (m_nCounter > 0 && m_nCounter < 360)
		{
			pos.y = 0.0f;
			scale.x = 0.0f;
			scale.z = 0.0f;
		}
		else if (m_nCounter > 360 && m_nCounter < 360 * 2)
		{
			pos.y = 1000.0f;
			scale.x = 0.0f;
			scale.z = 0.0f;
		}
		else  if (m_nCounter >  360 * 2)
		{
			m_nCounter = 0;
		}
		if (m_nCounter % 20 == 0)
		{//	���G�t�F�N�g
			if (m_InitScale.x == 2.3f) { CEffect::Create(pos + D3DXVECTOR3(0.0f, 15.0f, 0.0f), 2, 0); }
			else { CEffect::Create(pos + D3DXVECTOR3(0.0f, 15.0f, 0.0f), 2, 1); }
		}
		else if (m_nCounter % 30 == 0)
		{//	���G�t�F�N�g
			if (m_InitScale.x == 2.3f) { CEffect::Create(pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), 2, 0); }
			else { CEffect::Create(pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), 2, 1); }
		}
		else if (m_nCounter % 40 == 0)
		{//	���G�t�F�N�g
			if (m_InitScale.x == 2.3f) { CEffect::Create(pos + D3DXVECTOR3(0.0f, 25.0f, 0.0f), 2, 0); }
			else { CEffect::Create(pos + D3DXVECTOR3(0.0f, 25.0f, 0.0f), 2, 1); }
		}
	}

	if (CSceneX::GetModelType() == CLoad::MODEL_FSymbol)
	{
		m_nCounter++;
		if (m_nCounter % 6 == 0)
		{
			 CEffect::Create(pos + D3DXVECTOR3(0.0f, 65.0f, 0.0f), 3, 3);

		}
		int nAnswer = rand() % 48;
		int nAnswerB = rand() % 3;

		//	�g���Ă��Ȃ������̗�O����
		if (nAnswer == 0 || nAnswer == 2 || nAnswer == 4 || nAnswer == 6 || nAnswer == 8 || nAnswer == 11) { nAnswer = 1; }
		else if (nAnswer == 13 || nAnswer == 14 || nAnswer == 16 || nAnswer == 17 || nAnswer == 18 || nAnswer == 21) { nAnswer = 7; }
		else if (nAnswer == 22 || nAnswer == 23 || nAnswer == 25 || nAnswer == 26 || nAnswer == 28 || nAnswer == 29) { nAnswer = 15; }
		else if (nAnswer == 31 || nAnswer == 32 || nAnswer == 33 || nAnswer == 34 || nAnswer == 36 || nAnswer == 37) { nAnswer = 30; }
		else if (nAnswer == 38 || nAnswer == 39 || nAnswer == 43 || nAnswer == 44 || nAnswer == 45 || nAnswer == 46) { nAnswer = 35; }
		else if (nAnswer == 47 || nAnswer == 48) { nAnswer = 17; }
		if (m_nCounter % 180 == 0)
		{//	�������o��
			if (CManager::GetMode() == CManager::MODE_GAME)
			{
				if (nAnswerB == 0){CWord::Create(pos + D3DXVECTOR3(10.0f, 50.0f, 0.0f), D3DXVECTOR3(0.8f, 0.0f, 0.0f), size.x, size.y, "WORD", nAnswer, 1, 45);}
				else if (nAnswerB == 1) { CWord::Create(pos + D3DXVECTOR3(-10.0f, 50.0f, 0.0f), D3DXVECTOR3(-0.8f, 0.0f, 0.0f), size.x, size.y, "WORD", nAnswer, 1, 45); }
				else if (nAnswerB == 2) { CWord::Create(pos + D3DXVECTOR3(0.0f, 50.0f, 10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.8f), size.x, size.y, "WORD", nAnswer, 1, 45); }
				//else if (nAnswerB == 3) { CWord::Create(pos + D3DXVECTOR3(0.0f, 50.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, -0.8f), 12.0f, 12.0f, "WORD", nAnswer, 1, 45); }
				m_nCounter = 0;
			}
		}
	}
	CSceneX::SetPosition(pos);	//	�ʒu�̐ݒ�
	CSceneX::SetScale(scale);	//	�傫���̐ݒ�
}

//=============================================================================
// �m�b�N�o�b�N�̏���
//=============================================================================
void CObject::KnockBack(D3DXVECTOR3 *pMove, int nID)
{
	CSceneX::COLLISIONTYPE Collsiontype = CSceneX::GetCollsionType();
	float fknockBackMove = 0.0f;	// �m�b�N�o�b�N�̋��x

	if (Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_SMALL)
	{	// �m�b�N�o�b�N�̈З͂�������
		fknockBackMove = KNOCKBACK_MOVE_SMALL;
	}
	else if (Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_DURING)
	{	// �m�b�N�o�b�N�̈З͂������炢
		fknockBackMove = KNOCKBACK_MOVE_DURING;
	}
	else if (Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_BIG)
	{	// �m�b�N�o�b�N�̈З͂��傫��
		fknockBackMove = KNOCKBACK_MOVE_BIG;
	}
	CSound *pSound = CManager::GetSound();		//	���̎擾
												// �v���C���[�̌����������]������悤�ɂȂ�����폜
	if (CSceneX::GetCollsionNum() == 0 || CSceneX::GetCollsionNum() == 1)
	{	// �� ���� �E ����̔���
		pMove->x *= -fknockBackMove;
	}
	else if (CSceneX::GetCollsionNum() == 2 || CSceneX::GetCollsionNum() == 3)
	{	// �O ���� ��� ����̔���
		pMove->z *= -fknockBackMove;
	}
	if (CSceneX::GetModelType() == CLoad::MODEL_ALPHAMODEL00 || CSceneX::GetModelType() == CLoad::MODEL_ALPHAMODEL01)
	{
		pSound->SetVolume(CSound::SOUND_LABEL_SE_BULLET000, 3.0f);
		pSound->PlaySound(CSound::SOUND_LABEL_SE_BULLET000);
	}

	// �v���C���[�̌����������]������悤�ɂȂ�����R�����g���O��
	/*float fPlayer = CGame::GetPlayer(nID)->GetRotation().y;
	pMove->x = sinf(fPlayer + (D3DX_PI * 1.0f)) * (20.0f);
	pMove->z = cosf(fPlayer + (D3DX_PI * 1.0f)) * (20.0f);*/
}

//=============================================================================
// ���f�����n���̎󂯂�e���̏���
//=============================================================================
void CObject::AffectedLanding(D3DXVECTOR3 *pMove, int nID)
{
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		float fPlayer = CGame::GetPlayer(nID)->GetRotation().y;
		pMove->x = sinf(fPlayer + (D3DX_PI * 1.0f)) * (AFFECTED_LANDING);
		pMove->z = cosf(fPlayer + (D3DX_PI * 1.0f)) * (AFFECTED_LANDING);
	}
}

//=============================================================================
// ���f���̈ړ��֌W�̏���
//=============================================================================
void CObject::ModelMove(CSceneX::COLLISIONTYPE Type, D3DXVECTOR3 pos)
{
	if (m_nRealTime == REALTIME_INITPOS)
	{	// �ړ��t���O��false �����Ȃ��ꍇ
		float fMove = 0;

		// ���ꂼ��ړ��l�����߂�
		if (CSceneX::GetModelType() == CLoad::MODEL_DODAI) { fMove = MODEL_MOVE_Y * -1; } // �y��̏ꍇ
			if(CSceneX::GetModelType() == CLoad::MODEL_STAGEFLOOR001 || CSceneX::GetModelType() == CLoad::MODEL_STAGEFLOOR002 ||
				CSceneX::GetModelType() == CLoad::MODEL_STAGEOUT) {
				fMove = MODEL_MOVE_Y * -1; } // �y��̏ꍇ
		else if (CSceneX::GetModelType() != CLoad::MODEL_DODAI) { fMove = MODEL_MOVE_Y; }	// �y��ȊO

																							// �U���̏���
		Vibration(&pos);

		ModelMove(Type, &pos, fMove);
		CSceneX::SetPosition(pos);
	}
	else if (m_nRealTime == REALTIME_NOTMOVE)
	{	// �����Ȃ��ꍇ
		Rot(CSceneX::GetModelType());

		if (((CTime::GetStageTime() % 60) == 0) && CManager::GetGame()->GetChangeNum() < 2)
		{
			m_nRealTime = REALTIME_ENDPOS;
		}
	}
	else if (m_nRealTime == REALTIME_ENDPOS)
	{	// �ړ��t���O��true �����ꍇ
		pos.y += MODEL_MOVE_Y;						// �ړ����x

													// �U���̏���
		Vibration(&pos);

		CSceneX::SetPosition(pos);

		if (pos.y + CSceneX::GetVtxMax().y < 0)
		{	// �n�ʂ�艺�̏ꍇ
			if (m_bCreateFlag == true) { m_bCreateFlag = false; }
			Uninit();
			return;
		}
	}
}

//=============================================================================
// �A�C�R���̃A�j���[�V�����̏���
//=============================================================================
void CObject::AnimationIcon(void)
{
	m_nCntAnim++;
	if (m_bSwitch == false)
	{//	Switch��ON�������ꍇ
		if ((m_nCntAnim % ANIM_TIME) == 0)
		{
			m_nCntPattan++;
			m_pIcon->SetAnimation(m_nCntPattan, 0.1f, 1.0f);
		}
	}
}

//=============================================================================
// �A�C�R���̐�������
//=============================================================================
void CObject::IconCreate(CSceneX::COLLISIONTYPE Type, D3DXVECTOR3 pos)
{
	if (m_pIcon == NULL)
	{
		float fRot = 0.0f;		// �p�x�ۊ�
		m_pIcon = CScene3D::Create(D3DXVECTOR3(pos.x, 1.0f, pos.z), "�x���g�R���x�A_�A�C�R��");
		m_pIcon->SetSize(ICON_SIZE_X, ICON_SIZE_Y);
		m_pIcon->SetAnimation(0, 0.1f, 1.0f);

		if (Type == CSceneX::COLLSIONTYPE_CONVEYOR_RIHHT) { fRot = D3DX_PI * -0.5f; }
		else if (Type == CSceneX::COLLSIONTYPE_CONVEYOR_LEFT) { fRot = D3DX_PI * 0.5f; }
		else if (Type == CSceneX::COLLSIONTYPE_CONVEYOR_FRONT) { fRot = 0.0f; }
		else if (Type == CSceneX::COLLSIONTYPE_CONVEYOR_BACK) { fRot = -D3DX_PI; }
		m_pIcon->SetRot(D3DXVECTOR3(0.0f, fRot, 0.0f));
	}
}

//=============================================================================
// �U���̏���
//=============================================================================
void CObject::Vibration(D3DXVECTOR3 *Pos)
{
	// �ړ����ɍ��E�ɓ���
	if (m_bMoveFlag == false)
	{
		m_fMove += VIBRATION_MOVE;
		if (m_fMove > VIBRATION) { m_bMoveFlag = true; }
	}
	else if (m_bMoveFlag == true)
	{
		m_fMove -= VIBRATION_MOVE;
		if (m_fMove < -VIBRATION) { m_bMoveFlag = false; }
	}

	Pos->x += m_fMove;
	Pos->z += m_fMove;
}

//=============================================================================
// ��]�̏���
//=============================================================================
void CObject::Rot(CLoad::MODEL mode)
{
	CSceneX::COLLISIONTYPE Collsiontype = CSceneX::GetCollsionType();

	if (mode == CLoad::MODE_GEAR || mode == CLoad::MODEL_PROPELLER)
	{	// �R���W�����^�C�v���m�b�N�o�b��������Ȃ�����̉�]��������
		D3DXVECTOR3 rot = CSceneX::GetRot();

		if (Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_SMALL)
		{
			// ����̎�ނɂ���ĉ�]�ʂ�ω�
			rot.y += GEAR_ROT_Y * 0.2f;
		}
		else if (Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_DURING)
		{
			// ����̎�ނɂ���ĉ�]�ʂ�ω�
			rot.y += GEAR_ROT_Y * 0.5;
		}
		else if (Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_BIG)
		{
			// ����̎�ނɂ���ĉ�]�ʂ�ω�
			rot.y += GEAR_ROT_Y * 1.0f;
		}
		else
		{
			// ����̎�ނɂ���ĉ�]�ʂ�ω�
			rot.y += GEAR_ROT_Y * 1.5f;
		}
		CSceneX::SetRot(rot);
	}
}

//=============================================================================
// ���f���ړ��̏���
//=============================================================================
void CObject::ModelMove(CSceneX::COLLISIONTYPE Type, D3DXVECTOR3 *pos, float fMove)
{
	pos->y += fMove;						// �ړ����x

	if (fMove < 0)
	{
		if (pos->y - CSceneX::GetVtxMin().y < 0)
		{	// �n�ʂɒ������ꍇ
			if (Type == CSceneX::COLLSIONTYPE_CONVEYOR_FRONT || Type == CSceneX::COLLSIONTYPE_CONVEYOR_BACK ||
				Type == CSceneX::COLLSIONTYPE_CONVEYOR_RIHHT || Type == CSceneX::COLLSIONTYPE_CONVEYOR_LEFT)
			{	// �x���g�R���x�A�̏ꍇ
				pos->y = pos->y - CSceneX::GetVtxMin().y - 1.9f;
				pos->x = m_posOld.x;
				pos->z = m_posOld.z;
				CSceneX::SetPosition(*pos);
				m_nRealTime = REALTIME_NOTMOVE;

				IconCreate(Type, *pos);	// �A�C�R���̐���
			}
			else if (Type != CSceneX::COLLSIONTYPE_CONVEYOR_FRONT && Type != CSceneX::COLLSIONTYPE_CONVEYOR_BACK &&
				Type != CSceneX::COLLSIONTYPE_CONVEYOR_RIHHT && Type != CSceneX::COLLSIONTYPE_CONVEYOR_LEFT)
			{	// �x���g�R���x�A�ȊO�̏ꍇ
				pos->y = pos->y - CSceneX::GetVtxMin().y;
				pos->x = m_posOld.x;
				pos->z = m_posOld.z;

				CSceneX::SetPosition(*pos);
				m_nRealTime = REALTIME_NOTMOVE;
			}
		}
	}
	else if (fMove >= 0)
	{
		if (CSceneX::GetModelType() == CLoad::MODEL_STAGEFLOOR001 || CSceneX::GetModelType() == CLoad::MODEL_STAGEFLOOR002 ||
			CSceneX::GetModelType() == CLoad::MODEL_STAGEOUT)
		{
			if (CTime::GetSatgeNum() == 0)
			{
				pos->y = pos->y + CSceneX::GetVtxMin().y;
				pos->x = m_posOld.x;
				pos->z = m_posOld.z;

				CSceneX::SetPosition(*pos);
				m_nRealTime = REALTIME_NOTMOVE;
				if (m_bCreateFlag == false) {
					m_bCreateFlag = true;
				}
			}
			else if (CTime::GetSatgeNum() != 0)
			{
				if (pos->y > 0)
				{
					pos->y = -1.0f;
					pos->x = m_posOld.x;
					pos->z = m_posOld.z;

					CSceneX::SetPosition(*pos);
					m_nRealTime = REALTIME_NOTMOVE;
					if (m_bCreateFlag == false) {
						m_bCreateFlag = true;
					}
				}
			}
		}
		else if (CSceneX::GetModelType() == CLoad::MODEL_DODAI)
		{
			if (pos->y > 0)
			{
				pos->y = pos->y - CSceneX::GetVtxMin().y;
				pos->x = m_posOld.x;
				pos->z = m_posOld.z;

				CSceneX::SetPosition(*pos);
				m_nRealTime = REALTIME_NOTMOVE;
				if (m_bCreateFlag == false) {
					m_bCreateFlag = true;
				}
			}
		}
	}

}