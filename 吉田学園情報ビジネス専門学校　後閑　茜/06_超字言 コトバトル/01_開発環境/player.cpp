//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "player.h"
#include "charactor.h"
#include "manager.h"
#include "word_manager.h"
#include "object.h"
#include "point.h"
#include "game.h"
#include "tutorial.h"
#include "result.h"
#include "sceneX.h"
#include "time.h"
#include "debugProc.h"
#include "bullet.h"
#include "explosion.h"
#include "CameraManager.h"
#include "scene3D.h"
#include "fade.h"

#include "PlayerNumSelect.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_LOCKON_LENGTH (300.0f)								//���b�N�I���ł���ŉ�����
#define PLAYER_COLLISON (D3DXVECTOR3(5.0f, 40.0f, 5.0f))			//�L�����N�^�[�̓����蔻��
#define LOCKON_FUTURE_ROTATE (20.0f)								//���b�N�I���̒e�p�x���莞�ɓG�̈ړ����x�Ɋ|����萔

#define INU_BARANCE_LOADTEXT_UPPER "data/MOTION/motion_dog_up.txt"			//��(�o�����X�^)�̏㔼�g�̃��[�h�e�L�X�g
#define INU_BARANCE_LOADTEXT_LOWER "data/MOTION/motion_dog_down.txt"		//��(�o�����X�^)�̉����g�̃��[�h�e�L�X�g

#define KUMA_POWER_LOADTEXT_UPPER "data/MOTION/motion_bea_up.txt"			//�F(�p���[�^)�̏㔼�g�̃��[�h�e�L�X�g
#define KUMA_POWER_LOADTEXT_LOWER "data/MOTION/motion_bea_down.txt"			//�F(�p���[�^)�̉����g�̃��[�h�e�L�X�g

#define NECO_SPEED_LOADTEXT_UPPER "data/MOTION/motion_cat_up.txt"			//�L(�X�s�[�h�^)�̏㔼�g�̃��[�h�e�L�X�g
#define NECO_SPEED_LOADTEXT_LOWER "data/MOTION/motion_cat_down.txt"			//�L(�X�s�[�h�^)�̉����g�̃��[�h�e�L�X�g

#define USAGI_REACH_LOADTEXT_UPPER "data/MOTION/motion_rabbit_up.txt"			//�L(�X�s�[�h�^)�̏㔼�g�̃��[�h�e�L�X�g
#define USAGI_REACH_LOADTEXT_LOWER "data/MOTION/motion_rabbit_down.txt"			//�L(�X�s�[�h�^)�̉����g�̃��[�h�e�L�X�g

#define STEALTH_TIMER		(120)

#define GUNSCALE_TIME (30)

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CPlayer::PlayerLoadState CPlayer::m_PlayerLoadState[CPlayer::TYPE_MAX][BODY_MAX];		//���[�h���i�[�p

//=============================================================================
// �R���X�g���N�^&�f�X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority) : CScene(nPriority)
{
	m_bLand = false;
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pWordManager = NULL;
	m_nCntTransTime = 0;
	m_bAssist = true;
	m_bStealth = true;		//�X�e���X��ԂɂȂ�邩�ǂ���
	m_nStealthTimer = 0;
	m_BulletRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bMachineGun = false;
	m_MachineGunPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nMachineGunTime = 0;
	m_pBulletUI = NULL;
	m_pMissileUI = NULL;
	m_fBulletRotOld = 0.0f;
	m_nTargetID = MAX_PLAYER;
	m_nCntGunScale = 0;
	m_bBulletFlag = false;
	m_bVoice = false;
	m_bDamageVoice = false;
	m_nTimerDamageVoice = 0;

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{	//���v���C���[���猩���Ă��邩�ǂ���
		m_bVision[nCnt] = true;
	}
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		m_bInbush[nCnt] = false;
	}
	for (int nCntBody = 0; nCntBody < BODY_MAX; nCntBody++)
	{
		m_nCntKey[nCntBody] = 0;
		m_nCntFlame[nCntBody] = 0;
		m_motion[nCntBody] =  0;
		m_OldMotion[nCntBody] = 0;

		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			m_pPlayerParts[nCntParts][nCntBody] = NULL;
		}
	}
}
CPlayer::~CPlayer()
{

}

//=============================================================================
// ��������
//=============================================================================
CPlayer* CPlayer::Create(void)
{
	CPlayer* pPlayer = NULL;

	pPlayer = new CPlayer;

	if (pPlayer != NULL)
	{
		pPlayer->Init();
	}

	return pPlayer;
}
//=============================================================================
// �ݒ菈��
//=============================================================================
void CPlayer::Set(D3DXVECTOR3 pos, CCharaBase::CHARACTOR_MOVE_TYPE MoveType, int nPlayerID,PLAYER_TYPE PlayerType, D3DXVECTOR3 rot)
{
	//�L������ID�ݒ�
	m_nID = (nPlayerID % 4);//�͈͊O�̐������������炻���0�`3�܂ł̐����ɂ���
	m_PlayerType = PlayerType;
	//�L�������N���X����
	if (m_pCharactorMove == NULL)
	{
		if (ObjCreate(m_pCharactorMove))
		{
			m_pCharactorMove->Set(pos,rot, MoveType,this);
		}
	}


	// �����Ǘ��N���X����
	if (CManager::GetMode() != CManager::MODE_RESULT)
	{
		if (m_pWordManager == NULL)
		{
			ObjCreate(m_pWordManager);
			m_pWordManager->SetID(m_nID);
		}
	}
	if (CManager::GetXInput(m_nID) != NULL)
	{
		m_fStickRX = CManager::GetXInput(m_nID)->GetLStickRotX();
		m_fStickRY = CManager::GetXInput(m_nID)->GetLStickRotX();
	}


	//�L�������Ƃɓǂݍ��ރt�@�C���𕪂���(�t�@�C�����ł���܂ł͕����Ȃ�)
	switch (PlayerType)
	{
	case TYPE_BARANCE:
		ModelLoad(INU_BARANCE_LOADTEXT_UPPER, PlayerType, UPPER_BODY);
		ModelLoad(INU_BARANCE_LOADTEXT_LOWER, PlayerType,LOWER_BODY);
		break;
	case TYPE_POWER:
		ModelLoad(KUMA_POWER_LOADTEXT_UPPER, PlayerType, UPPER_BODY);
		ModelLoad(KUMA_POWER_LOADTEXT_LOWER, PlayerType, LOWER_BODY);
		break;
	case TYPE_SPEED:
		ModelLoad(NECO_SPEED_LOADTEXT_UPPER, PlayerType, UPPER_BODY);
		ModelLoad(NECO_SPEED_LOADTEXT_LOWER, PlayerType, LOWER_BODY);
		break;
	case TYPE_REACH:
		ModelLoad(USAGI_REACH_LOADTEXT_UPPER, PlayerType, UPPER_BODY);
		ModelLoad(USAGI_REACH_LOADTEXT_LOWER, PlayerType, LOWER_BODY);
		break;
	}

	//�㔼�g�Ɖ����g��A��
	if (m_pPlayerParts[0][0] != NULL &&
		m_pPlayerParts[0][1] != NULL)
	{//�㔼�g�̐e���f���Ɖ����g�̐e���f���̗��������݂��Ă����
		m_pPlayerParts[0][UPPER_BODY]->SetParent(m_pPlayerParts[0][LOWER_BODY]->GetMatrix());	//�㔼�g�̐e�������g
	}

	SetMotion(MOTION_LOWER_NEUTRAL,LOWER_BODY);
	SetMotion(MOTION_UPPER_NEUTRAL, UPPER_BODY);

	//�`��p���f������
	//m_pPlayerModel = CSceneX::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f),CLoad::MODEL_SAMPLE_PLAYER,1);
	SetObjType(CScene::OBJTYPE_PLAYER);
}

//=============================================================================
//	����������
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//�ϐ�������
	m_pCharactorMove = NULL;
	m_ChildCameraName = "";
	m_nCntTransTime = 0;
	m_pLockOnCharactor = NULL;
	m_nShotCameraMove = 0;

	m_bDamageVoice = false;
	m_nTimerDamageVoice = 0;

	//�R�}���h�Z�b�g
	CCommand::RegistCommand("PLAYER_BULLET", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_RELEASE, DIK_SPACE);
	CCommand::RegistCommand("PLAYER_BULLET", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_RELEASE, CInputXPad::XPAD_RIGHT_SHOULDER);

	CCommand::RegistCommand("PLAYER_SELF_AIM", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_HOLD, CInputXPad::XPAD_RIGHT_SHOULDER);
	CCommand::RegistCommand("PLAYER_SELF_AIM", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_HOLD, DIK_SPACE);

	CCommand::RegistCommand("SELF_AIM_UP",CCommand::INPUTTYPE_KEYBOARD,CCommand::INPUTSTATE_PRESS,DIK_UP);
	CCommand::RegistCommand("SELF_AIM_DOWN", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_DOWN);
	CCommand::RegistCommand("SELF_AIM_LEFT", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_LEFT);
	CCommand::RegistCommand("SELF_AIM_RIGHT", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_RIGHT);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
	//�L�������N���X�폜
	ObjRelease(m_pCharactorMove);

	for (int nCntBody = 0; nCntBody < BODY_MAX; nCntBody++)
	{
		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			ObjRelease(m_pPlayerParts[nCntParts][nCntBody]);
			m_pPlayerParts[nCntParts][nCntBody] = NULL;
		}
	}

	if (m_pBulletUI != NULL) { m_pBulletUI->Uninit(); m_pBulletUI = NULL; }

	// �����Ǘ��N���X�̍폜
	if (m_pWordManager != NULL)
	{
		ObjRelease(m_pWordManager);
	}
	//�v���C���[���̂̍폜
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	D3DXVECTOR3 testpos;
	D3DXVECTOR3 testmove;
	CCameraManager* pCameraManager = CManager::GetCameraManager();

	CPlayer *pPlayer[MAX_PLAYER];

	float fCameraLength = 250.0f;

	switch (*CPlayerSelect::GetModeSelectMode())
	{
	case CPlayerSelect::SELECTPLAYER_1P:
		fCameraLength = 250.0f;
		break;
	case CPlayerSelect::SELECTPLAYER_2P:
		fCameraLength = 220.0f;
		break;
	case CPlayerSelect::SELECTPLAYER_3P:
		fCameraLength = 180.0f;
		break;
	case CPlayerSelect::SELECTPLAYER_4P:
		fCameraLength = 180.0f;
		break;
	}


	// �v���C���[���擾
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		pPlayer[nCntPlayer] = CManager::GetPlayer(nCntPlayer);			// �v���C���[���擾
	}


	if (m_pCharactorMove != NULL &&
		(CManager::GetMode() == CManager::MODE_GAME ||CManager::GetMode() == CManager::MODE_TUTORIAL))
	{
		int nNear = GetNearPlayer();

		// �O�̃t���[���̈ʒu���
		m_posOld = m_pCharactorMove->GetPosition();
		//�ړ��A��]�̍X�V
		m_pCharactorMove->Update();
		//�e�Ƃ̓����蔻��
		CollisionDamageObj();

		// ���f���Ƃ̓����蔻��
		if ((CollisonObject(&m_pCharactorMove->GetPosition(), &D3DXVECTOR3(m_posOld.x, m_posOld.y, m_posOld.z), &m_pCharactorMove->GetMove(), PLAYER_COLLISON)) == true)
		{
			CollisonObject(&m_pCharactorMove->GetPosition(), &D3DXVECTOR3(m_posOld.x, m_posOld.y, m_posOld.z), &m_pCharactorMove->GetMove(), PLAYER_COLLISON);
		}
		testpos = m_pCharactorMove->GetPosition();
		testmove = m_pCharactorMove->GetMove();

		D3DXVECTOR3 testposFRONT = D3DXVECTOR3(sinf(m_pCharactorMove->GetRotation().y) * 10,
			sinf(m_pCharactorMove->GetRotation().x) * 10,
			cosf(m_pCharactorMove->GetRotation().y) * 10);
		testpos += testposFRONT;
		//�O��Object�����邩�ǂ���
		m_pCharactorMove->m_bFront = CollisonObject(&D3DXVECTOR3(testpos.x, testpos.y, testpos.z), &D3DXVECTOR3(m_posOld.x, m_posOld.y, m_posOld.z), &testmove, PLAYER_COLLISON);

		//�e�ł�(�v���C���[)
		if (m_pCharactorMove->GetMoveType() == C3DCharactor::MOVETYPE_PLAYER_INPUT && m_pCharactorMove->m_bWait == false)
		{
			//�Z�b�g
			CCamera* pCam = pCameraManager->GetCamera(m_ChildCameraName);
			static D3DXVECTOR3 BulletRot = {};
			BulletRot.y = m_pCharactorMove->GetRotation().y;
			D3DXVECTOR3 BulletPos(GetBulletMuzzle());
			D3DXVECTOR3 LockOnObjRot, LockOnObjPos, LockOnMove;

			// �e�̐���
			if (CCommand::GetCommand("PLAYER_BULLET", m_nID) && CGame::GetbStageSet() == false && m_bMachineGun == false)
			{
				C3DCharactor* pChara = NULL;
				if (nNear != -1)
				{//�߂��v���C���[������΂��̕����ɒe��ł�
					pChara = (C3DCharactor*)CManager::GetPlayer(nNear)->GetCharaMover();
				}
				if (m_bAssist == true)
				{//�I�[�g�G�C�����[�h�Ȃ�e�p�x��G�̕����ɍ��킹��
					if (pChara != NULL)
					{//�߂��v���C���[������΂��̕����ɒe��ł�
						LockOnObjPos = pChara->GetPosition();
						LockOnObjRot = pChara->GetRotation();
						BulletRot.y = atan2f((LockOnObjPos.x - BulletPos.x), (LockOnObjPos.z - BulletPos.z));
						m_pCharactorMove->GetRotation().y = BulletRot.y;
						CUtilityMath::RotateNormarizePI(&BulletRot.y);
					}
					else
					{//�߂��v���C���[�����Ȃ���΃v���C���[�̌����ɑł�
						BulletRot.y = m_pCharactorMove->GetRotation().y;
						//m_pCharactorMove->GetRotation().y = BulletRot.y;
					}
				}
				else if (m_bAssist == false)
				{	// �蓮�G�C���̏ꍇ
					BulletRot.y = m_fBulletRotOld;
					m_pCharactorMove->GetRotation().y = BulletRot.y;
					BulletUIUninit();
					m_bAssist = true;
				}

				//���˕����ێ�
				m_BulletRot.y = BulletRot.y;

				if (m_pWordManager->GetBulletFlag() == true)
				{	//����
					m_bStealth = false;
					//�}�V���K�����ˎ��ԏ�����
					m_nMachineGunTime = 0;
					m_bMachineGun = true;
				}

				if (m_PlayerType != TYPE_REACH && m_pWordManager->GetBulletFlag() == true)
				{	//�E�T�M�ȊO
					m_pWordManager->BulletCreate(m_nID, BulletPos, m_BulletRot, m_PlayerType,
						(m_PlayerType == TYPE_SPEED) ? pChara : NULL);

					m_nCntGunScale = GUNSCALE_TIME;
					//�{�C�X�Đ�
 					PlayVoice(m_PlayerType);
				}
			}

			if (CCommand::GetCommand("PLAYER_SELF_AIM", m_nID) == true)
			{
				//�܂��L�[�{�[�h�̖��L�[����p�x�����߂�
				if (CCommand::GetCommand("SELF_AIM_LEFT"))
				{
					if (CCommand::GetCommand("SELF_AIM_UP")) { m_fBulletRotOld = D3DX_PI * -0.25f; }
					else if (CCommand::GetCommand("SELF_AIM_DOWN")) { m_fBulletRotOld = D3DX_PI * -0.75f; }
					else { m_fBulletRotOld = D3DX_PI * -0.5f; }
				}
				else if (CCommand::GetCommand("SELF_AIM_RIGHT"))
				{
					if (CCommand::GetCommand("SELF_AIM_UP")) { m_fBulletRotOld = D3DX_PI * 0.25f; }
					else if (CCommand::GetCommand("SELF_AIM_DOWN")) { m_fBulletRotOld = D3DX_PI * 0.75f; }
					else { m_fBulletRotOld = D3DX_PI * 0.5f; }
				}
				else if (CCommand::GetCommand("SELF_AIM_UP")) {m_fBulletRotOld = D3DX_PI * 0.0f; }
				else if (CCommand::GetCommand("SELF_AIM_DOWN")) { m_fBulletRotOld = D3DX_PI * 1.0f; }

				//�p�b�h���h�����Ă���ꍇ�̓p�b�h�̉E�X�e�B�b�N�p�x��D�悷��
				if (CManager::GetXInput(m_nID) != NULL && CManager::GetXInput(m_nID)->GetConnect() == true)
				{//�X�e�B�b�N�p���擾���Ĕ��ˊp�Ƃ���
              		if (CManager::GetXInput(m_nID)->GetRStickRotY() == 0 && CManager::GetXInput(m_nID)->GetRStickRotX() == 0)
					{	// �E�̃X�e�B�b�N�𓮂����ĂȂ��ꍇ
						m_fBulletRotOld = CManager::GetXInput(m_nID)->GetStickRotOld(m_fStickRX, m_fStickRY, m_pCharactorMove->GetRotation().y);
					}
					else
					{
						m_fBulletRotOld = CManager::GetXInput(m_nID)->GetStickRot(false, m_pCharactorMove->GetRotation().y);
						m_fStickRX = CManager::GetXInput(m_nID)->GetRStickRotX();
						m_fStickRY = CManager::GetXInput(m_nID)->GetRStickRotY();
					}
				}
				//���˕����ێ�
				m_BulletRot.y = m_fBulletRotOld;

				if (m_pWordManager->GetStockNum() > 0)
				{
            		BulletUI(m_BulletRot);		// �e���˕\��
					pCameraManager->SetCameraLength(m_ChildCameraName, fCameraLength + 100.0f);
				}

				m_nShotCameraMove = 90;
				m_bAssist = false;//�Z���t�G�C�����[�h�ɐݒ�
			}
			else
			{
				//BulletRot.y = m_pCharactorMove->GetRotation().y;
				m_BulletRot.y = BulletRot.y;
				BulletUIUninit();
				if (m_bAssist == false)
				{
					m_nShotCameraMove = 90;
				}
				m_bAssist = true;
			}

			if (m_nShotCameraMove > 0)
			{
				m_nShotCameraMove--;
				if (m_nShotCameraMove <= 0)
				{
					pCameraManager->SetCameraLength(m_ChildCameraName, fCameraLength);
					m_nShotCameraMove = -1;
				}
			}
			CDebugProc::Print("cn","m_nShotCameraMove = ", m_nShotCameraMove);

			//�}�V���K������
			if (m_bMachineGun == true)
			{	// ���ˎ��͓����Ȃ�
				m_nMachineGunTime++;
				//�p�b�h���h�����Ă���ꍇ�̓p�b�h�̉E�X�e�B�b�N�p�x��D�悷��
				if (CManager::GetXInput(m_nID) != NULL && CManager::GetXInput(m_nID)->GetConnect() == true)
				{//�X�e�B�b�N�p���擾���Ĕ��ˊp�Ƃ���
					if (CManager::GetXInput(m_nID)->GetRStickRotY() == 0 && CManager::GetXInput(m_nID)->GetRStickRotX() == 0)
					{	// �E�̃X�e�B�b�N�𓮂����ĂȂ��ꍇ
						if (m_fStickRX == 0 && m_fStickRY == 0)
						{
							m_fBulletRotOld = m_pCharactorMove->GetRotation().y;
						}
						else
						{
							m_fBulletRotOld = CManager::GetXInput(m_nID)->GetStickRotOld(m_fStickRX, m_fStickRY, m_pCharactorMove->GetRotation().y);
						}
					}
					else
					{
						m_fBulletRotOld = CManager::GetXInput(m_nID)->GetStickRot(false, m_pCharactorMove->GetRotation().y);
						m_fStickRX = CManager::GetXInput(m_nID)->GetRStickRotX();
						m_fStickRY = CManager::GetXInput(m_nID)->GetRStickRotY();
					}
				}
				m_BulletRot.y = m_fBulletRotOld;
				m_pCharactorMove->GetRotation().y = m_fBulletRotOld;

				if (m_PlayerType == TYPE_REACH)
				{	// �^�C�v���E�T�M�Ȃ�}�V���K���̏���

					if (m_pWordManager->GetStock(0) != NOT_NUM && m_bBulletFlag == false)
					{
						if (m_bVoice == false)
						{	//�{�C�X�Đ�
							PlayVoice(m_PlayerType);
							m_bVoice = true;
						}

						if (m_nMachineGunTime % 10 == 0)
						{//10�t���[���Ɉ��e����
							m_MachineGunPos.x = (float)((rand() % 16) - (rand() % 16));
							m_MachineGunPos.z = (float)((rand() % 16) - (rand() % 16));
							m_pWordManager->BulletCreate(m_nID, BulletPos + m_MachineGunPos, BulletRot, m_PlayerType, NULL);
						}
						else if (m_nMachineGunTime > 60)
						{//6�񔭎˂�����e�����폜
							m_bMachineGun = false;
							m_pWordManager->Reset();
							m_bVoice = false;
						}
						m_nCntGunScale = GUNSCALE_TIME;
					}
					else if (m_pWordManager->GetStock(0) == NOT_NUM )
					{//�S�~���f���p�̔���
						if (m_bBulletFlag == false)
						{
							m_pWordManager->BulletCreate(m_nID, BulletPos + m_MachineGunPos, m_BulletRot, m_PlayerType, NULL);
							m_pWordManager->Reset();
							m_bBulletFlag = true;
							//�{�C�X�Đ�
							PlayVoice(m_PlayerType);
						}
						m_nCntGunScale = GUNSCALE_TIME;
					}

					if (m_bBulletFlag == true)
					{
						if (m_nMachineGunTime % 10 == 0)
						{
							m_bBulletFlag = false;
							m_bMachineGun = false;
						}
					}
				}
				else if (m_PlayerType != TYPE_REACH)
				{
					if (m_nMachineGunTime % 20 == 0)
					{
						m_bMachineGun = false;
					}
				}

			}


			//m_pCharactorMove->GetRotation().y = BulletRot.y;
			m_pCharactorMove->GetSpin().y = 0.0f;

			CDebugProc::Print("cfcfcf","BulletRot = X:",BulletRot.x,"| Y:",BulletRot.y,"| Z:",BulletRot.z);
		}

		//�e�̃X�P�[���ω�
		if (m_nCntGunScale > 0)
		{
			m_pPlayerParts[8][CPlayer::UPPER_BODY]->SetScale(1.7f);
			m_nCntGunScale--;

			if (m_nCntGunScale <= 0)
			{
				m_nCntGunScale = 0;
				m_pPlayerParts[8][CPlayer::UPPER_BODY]->SetScale(1.0f);
			}
		}

		//�e���ˎ��ɔ�����
		if(m_bStealth == false)
		{
			m_nStealthTimer++;
			if (m_nStealthTimer > STEALTH_TIMER)
			{
				m_bStealth = true;
				m_nStealthTimer = 0;
			}
			for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
			{
				if (pPlayer[nCntPlayer] != NULL && nCntPlayer != GetID())
				{	//���v���C���[�Ɍ����Ă���
					pPlayer[nCntPlayer]->SetVision(GetID(), true);
				}
			}
		}


		//�����Ǘ��N���X�̍X�V
		if (m_pWordManager != NULL)
		{
			if (m_pCharactorMove != NULL && m_pCharactorMove->GetMoveType() == CCharaBase::MOVETYPE_PLAYER_INPUT)
			{
				m_pWordManager->SearchWord();
			}
			m_pWordManager->Update();
		}

	}
	else
	{
		// �O�̃t���[���̈ʒu���
		m_posOld = m_pCharactorMove->GetPosition();
		//�ړ��A��]�̍X�V
		m_pCharactorMove->Update();
		// ���f���Ƃ̓����蔻��
	//	if ((CollisonObject(&m_pCharactorMove->GetPosition(), &D3DXVECTOR3(m_posOld.x, m_posOld.y, m_posOld.z), &m_pCharactorMove->GetMove(), PLAYER_COLLISON)) == true)
		{
			CollisonObject(&m_pCharactorMove->GetPosition(), &D3DXVECTOR3(m_posOld.x, m_posOld.y, m_posOld.z), &m_pCharactorMove->GetMove(), PLAYER_COLLISON);
		}
	}

	//���G���Ԃ̃J�E���g�_�E��
	if (m_nCntTransTime > 0)
	{
		m_nCntTransTime--;
	}
	else
	{
		m_nCntTransTime = -1;
		for (int nCntBody = 0; nCntBody < BODY_MAX; nCntBody++)
		{
			for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
			{
				if (m_pPlayerParts[nCntParts][nCntBody] != NULL)
				{
					m_pPlayerParts[nCntParts][nCntBody]->SetDrawFlag(true);
				}
			}
		}
	}

	//�_���[�W���̃J�E���g
	if (m_bDamageVoice == true)
	{
		m_nTimerDamageVoice++;
		if (m_nTimerDamageVoice > 40)
		{
			m_bDamageVoice = false;
			m_nTimerDamageVoice = 0;
		}
	}

	MotionUpdate(LOWER_BODY);
	MotionUpdate(UPPER_BODY);

	for (int nCntBody = 0; nCntBody < BODY_MAX; nCntBody++)
	{
		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			if (m_pPlayerParts[nCntParts][nCntBody] != NULL)
			{
				if (m_nCntTransTime % 2 == 0)
				{//�_���[�W���̓_�ŏ���
					m_pPlayerParts[nCntParts][nCntBody]->SetDrawFlag(!m_pPlayerParts[nCntParts][nCntBody]->GetDrawFlag());
				}

				m_pPlayerParts[nCntParts][nCntBody]->Update();
			}
		}
	}

	SetPauseFlag();	// �|�[�Y�Ăяo������

#ifdef _DEBUG
	testpos = m_pCharactorMove->GetPosition();
	testmove = m_pCharactorMove->GetMove();

	CDebugProc::Print("cfcfcf", "PLAYER.Pos :", testpos.x, " ", testpos.y, " ", testpos.z);
	CDebugProc::Print("cfcfcf", "PLAYER.Move :", testmove.x, " ", testmove.y, " ", testmove.z);
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	for (int nCntBody = 0; nCntBody < BODY_MAX; nCntBody++)
	{
		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			if (m_pPlayerParts[nCntParts][nCntBody] != NULL)
			{
				m_pPlayerParts[nCntParts][nCntBody]->Draw();
			}
		}
	}

	if (m_pPlayerParts[0][0] != NULL)
	{
		CDebugProc::Print("cf","ALPHA = ", m_pPlayerParts[0][0]->GetAlpha());
	}
}
//=============================================================================
// ���[�V�����X�V����
//=============================================================================
void CPlayer::MotionUpdate(BODY body)
{
	KeyProperty pKey, pKeyNext;

	float fFlameMotion;
	int nFutureKey;
	D3DXVECTOR3 aKeyPos[PLAYER_MODELNUM];
	D3DXVECTOR3 aKeyRot[PLAYER_MODELNUM];
	m_nCntFlame[body]++;

	switch (m_Mstate[body])
	{
	case STATE_NORMAL:
		nFutureKey = (m_nCntKey[body] + 1) % (m_propMotion[m_motion[body]][body].nKeyNum);
		pKey = m_propMotion[m_motion[body]][body].key[m_nCntKey[body]];
		pKeyNext = m_propMotion[m_motion[body]][body].key[nFutureKey];

		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			if (m_pPlayerParts[nCntParts][body] != NULL)
			{
				//���݂̊p�x���擾
				D3DXVECTOR3 rot = m_pPlayerParts[nCntParts][body]->GetRotation();

				//���݂̃L�[���玟�̃L�[�ւ̍Đ��t���[�����ɂ����郂�[�V�����J�E���^�[�̑��Βl���Z�o
				fFlameMotion = (float)(m_nCntFlame[body] + 1) / ((float)pKey.nFrame);

				//���݂̃L�[���玟�̃L�[�ւ̊p�x�̍������Z�o
				aKeyRot[nCntParts].x = (pKeyNext.Rot[nCntParts].x - pKey.Rot[nCntParts].x);
				aKeyRot[nCntParts].y = (pKeyNext.Rot[nCntParts].y - pKey.Rot[nCntParts].y);
				aKeyRot[nCntParts].z = (pKeyNext.Rot[nCntParts].z - pKey.Rot[nCntParts].z);

				//���߂����������݂̃L�[�ɌW�����|���Ȃ��瑫��
				rot = pKey.Rot[nCntParts] + (aKeyRot[nCntParts] * fFlameMotion);

				if (nCntParts == 0 && body == LOWER_BODY)
				{
					rot.y = 3.14f;
				}

				//�p�x�̐��K��
				CUtilityMath::RotateNormarizePI(&rot.x);
				CUtilityMath::RotateNormarizePI(&rot.y);
				CUtilityMath::RotateNormarizePI(&rot.z);

				m_pPlayerParts[nCntParts][body]->SetRotation(rot);
			}
		}

		if (m_nCntFlame[body] == m_propMotion[m_motion[body]][body].key[m_nCntKey[body]].nFrame)
		{//����̃t���[�����o�߂�����

			m_nCntFlame[body] = 0;
			m_nCntKey[body]++;	//�L�[�����Z
			if (m_nCntKey[body] >= m_propMotion[m_motion[body]][body].nKeyNum)
			{//�L�[������̐��l�ɒB������
				m_nCntKey[body] = 0;
				if (m_propMotion[m_motion[body]][body].nLoop == 0)
				{
					if (m_pWordManager->GetBulletFlag())
					{
						SetMotion(MOTION_UPPER_SETUP_NEUTRAL, UPPER_BODY);
					}
					else
					{
						SetMotion(MOTION_UPPER_NEUTRAL, UPPER_BODY);
					}

					SetMotion(MOTION_LOWER_NEUTRAL, LOWER_BODY);
				}
			}
		}
		break;
	case STATE_BLEND:
		if (m_motion[body] == 0)
		{
			pKey();
		}
		else
		{
			pKey = m_propMotion[m_OldMotion[body]][body].key[m_nCntKey[body]];
		}
		pKeyNext = m_propMotion[m_motion[body]][body].key[0];

		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			if (m_pPlayerParts[nCntParts][body] != NULL)
			{
				//���݂̊p�x���擾
				D3DXVECTOR3 rot = m_pPlayerParts[nCntParts][body]->GetRotation();

				//�u�����h�W�����Z�o
				fFlameMotion = (float)(m_nCntBlendMotion[body] + 1) / MOTION_BLENDTIME;

				//���݂̃L�[���玟�̃L�[�ւ̊p�x�̍������Z�o
				aKeyRot[nCntParts].x = (pKeyNext.Rot[nCntParts].x - pKey.Rot[nCntParts].x);
				aKeyRot[nCntParts].y = (pKeyNext.Rot[nCntParts].y - pKey.Rot[nCntParts].y);
				aKeyRot[nCntParts].z = (pKeyNext.Rot[nCntParts].z - pKey.Rot[nCntParts].z);

				//���߂����������݂̃L�[�ɌW�����|���Ȃ��瑫��
				rot = pKey.Rot[nCntParts] + (aKeyRot[nCntParts] * fFlameMotion);

				if (nCntParts == 0 && body == LOWER_BODY)
				{
					rot.y = 3.14f;
				}

				//�p�x�̐��K��
				CUtilityMath::RotateNormarizePI(&rot.x);
				CUtilityMath::RotateNormarizePI(&rot.y);
				CUtilityMath::RotateNormarizePI(&rot.z);

				m_pPlayerParts[nCntParts][body]->SetRotation(rot);
			}
		}

		m_nCntBlendMotion[body]++;
		if (m_nCntBlendMotion[body] >= MOTION_BLENDTIME)
		{//����̃t���[�����o�߂�����
			m_nCntBlendMotion[body] = 0;
			m_nCntKey[body] = 0;
			m_Mstate[body] = STATE_NORMAL;
		}
		break;
	}
	CDebugProc::Print("cn","MOTION = ",(int)m_motion[body]);
}

//=============================================================================
// ���[�V�����ݒ菈��
//=============================================================================
void	CPlayer::SetMotion(int motion, BODY body,MOTION_STATE state)
{
	if (motion != m_motion[body])
	{//���ݓ����Ă��郂�[�V�����ƈႤ���̂ł����
		//��O�̃��[�V������ۑ�����
		m_OldMotion[body] = m_motion[body];

		//���̑��ϐ��̏�����
		m_nCntBlendMotion[body] = 0;
		m_nCntFlame[body] = 0;
		if (state != STATE_BLEND)
		{
			if (m_Mstate[body] == STATE_BLEND)
			{//��O���u�����h�Ȃ�
				for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
				{
					if (m_pPlayerParts[nCntParts][body] != NULL)
					{
						//�u�����h���Ɏ��̃��[�V�����ɓ�������
						m_pPlayerParts[nCntParts][body]->SetRotation(m_propMotion[m_OldMotion[body]][body].key[0].Rot[nCntParts]);
					}
				}
			}
			m_nCntKey[body] = 0;
		}	//�u�����h���鎞�͏��������Ȃ�

		//�������
		m_motion[body] = motion;
		m_Mstate[body] = state;

	}
}

//=============================================================================
// �L�����̓����x�ݒ菈��
//=============================================================================
void CPlayer::SetPartsAlpha(float fAlpha)
{
	for (int nCntBody = 0; nCntBody < BODY_MAX; nCntBody++)
	{
		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			if (m_pPlayerParts[nCntParts][nCntBody] != NULL)
			{
				m_pPlayerParts[nCntParts][nCntBody]->SetAlpha(fAlpha);
			}
		}
	}
}



//=============================================================================
// �����蔻��(�e)����
//=============================================================================
bool CPlayer::CollisionDamageObj(void)
{
	bool bHit = false;
	CScene *pScene = NULL;
	CSound *pSound = CManager::GetSound();		//	���̎擾

	D3DXVECTOR3 PlayerPos = m_pCharactorMove->GetPosition();
	D3DXVECTOR3 ObjPos,ObjRot;
	float fObjSize = 0.0f;

	/*�e�Ƃ̓����蔻��*/
	// �擪�̃I�u�W�F�N�g���擾
	pScene = CScene::GetTop(BULLET_PRIORITY);

	while (pScene != NULL)
	{// �D�揇�ʂ��e�Ɠ����I�u�W�F�N�g��1��1�m���߂�
	 // �����̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
		CScene *pSceneNext = pScene->GetNext();
		if (pScene->GetDeath() == false)
		{// ���S�t���O�������Ă��Ȃ�����
			if (pScene->GetObjType() == CScene::OBJTYPE_BULLET)
			{// �I�u�W�F�N�g�̎�ނ��m���߂�
				C3DBullet *pBullet = ((C3DBullet*)pScene);		// CBulletBase�փL���X�g(�^�̕ύX)
				ObjPos = pBullet->GetPosition();
				ObjRot = pBullet->GetRotation();

				float X = (ObjPos.x - PlayerPos.x) * (ObjPos.x - PlayerPos.x);
				float Y = (ObjPos.y - PlayerPos.y) * (ObjPos.y - PlayerPos.y);
				float Z = (ObjPos.z - PlayerPos.z) * (ObjPos.z - PlayerPos.z);

				if(sqrtf(X + Y + Z) < BULLET_COLLISION_SIZE &&
					m_nID != pBullet->GetID())
				{//���̔���

					/*���_���Z (���Ă��L������ID��pBullet��GetID�Ŏ擾�ł���)*/
					if (pBullet->GetType() == C3DBullet::TYPE_MODEL)
					{	// ���f���̏ꍇ�̓|�C���g���Z
						CPoint *pPoint = NULL;
						pPoint = CManager::GetPoint(pBullet->GetID());

						CModelBullet *pModelBullet = ((CModelBullet*)pBullet);

						int nPoint = 0;
						switch (pModelBullet->GetType())
						{//���������e�̃^�C�v�ɉ����ē��_��ς���
						case CModelBullet::TYPE_NORMAL:			   nPoint = 1;			break;//�S�~�͂P�_
						case CModelBullet::TYPE_MACHINEGUN:		   nPoint = 1;			break;//�}�V���K����1�_(�~6)
						case CModelBullet::TYPE_SHOTGUN:		   nPoint = 1;			break;//�V���b�g�K����1�_(�~6)
						case CModelBullet::TYPE_SHOTGUN_MEDIUM:    nPoint = 1;			break;//����
						case CModelBullet::TYPE_SHOTGUN_SLOW:      nPoint = 1;			break;//����
						case CModelBullet::TYPE_MISSILE_CENTER:    nPoint = 2;			break;//�~�T�C���͒�����2�_
						case CModelBullet::TYPE_MISSILE_SIDE:      nPoint = 1;			break;//�[��1�_
						case CModelBullet::TYPE_BOMB:		       nPoint = 4;			break;//���e��4�_
						default:								   nPoint = 3;			break;//����ȊO��3�_
						}

						//�t�B�[�o�[�^�C�����ɓ��_�Q�{
						if (CTime::GetFeverFlag() == true)
						{
							nPoint *= 2;
						}

						if (pPoint != NULL) { pPoint->AddPoint(nPoint); }
						pSound->SetVolume(CSound::SOUND_LABEL_SE_POINTUP, 3.0f);
						pSound->PlaySound(CSound::SOUND_LABEL_SE_POINTUP);

						C3DBullet *pBullet = ((C3DBullet*)pModelBullet);		// CBulletBase�փL���X�g(�^�̕ύX)
					}

					//������΂�
					DamageReaction(pBullet->GetKnockBackPower(),ObjRot);
					m_nCntTransTime = 10;
					//�e�폜
					pBullet->Uninit();

					//����
					m_bStealth = false;

					return true;
				}
			}
		}
		pScene = pSceneNext;
	}

	if (m_nCntTransTime <= 0)
	{//���G���ԂłȂ��Ȃ�
	/*����*/
	// �擪�̃I�u�W�F�N�g���擾
	pScene = CScene::GetTop(EXPLOSION_PRIORITY);

	while (pScene != NULL)
	{// �D�揇�ʂ��e�Ɠ����I�u�W�F�N�g��1��1�m���߂�
	 // �����̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
		CScene *pSceneNext = pScene->GetNext();
		if (pScene->GetDeath() == false)
		{// ���S�t���O�������Ă��Ȃ�����
			if (pScene->GetObjType() == CScene::OBJTYPE_EXPLOSION)
			{// �I�u�W�F�N�g�̎�ނ��m���߂�
				CExplosion3D* pExp = (CExplosion3D*)pScene;
				ObjPos = pExp->GetPosition();
				fObjSize = pExp->GetSize();

				float fRot = atan2f((ObjPos.x - PlayerPos.x),(ObjPos.z - PlayerPos.z)) + D3DX_PI;
				float X = (ObjPos.x - PlayerPos.x) * (ObjPos.x - PlayerPos.x);
				float Y = (ObjPos.y - PlayerPos.y) * (ObjPos.y - PlayerPos.y);
				float Z = (ObjPos.z - PlayerPos.z) * (ObjPos.z - PlayerPos.z);

				CUtilityMath::RotateNormarizePI(&fRot);
				if (sqrtf(X + Y + Z) < fObjSize)
				{
					CPoint *pPoint = NULL;
					const int nExpID = pExp->GetID();
					if (nExpID != -1 && nExpID != this->GetID())
					{
						pPoint = CManager::GetPoint(nExpID);
						if (pPoint != NULL) { pPoint->AddPoint(3); }//���e�q�b�g��3�|�C���g�ǉ�
					}
					//������΂�
					DamageReaction(10.0f, D3DXVECTOR3(0.0f,fRot,0.0f));
					m_nCntTransTime = 60;
					return true;
				}

			}
		}
		pScene = pSceneNext;
	}

	}

	return false;
}

//=============================================================================
// �_���[�W�̔�������
//=============================================================================
void CPlayer::DamageReaction(float fDamageValue, D3DXVECTOR3 HitRotation)
{
	CSound *pSound = CManager::GetSound();		//	���̎擾

	D3DXVECTOR3& move = m_pCharactorMove->GetMove();

	//
	move.x += sinf(HitRotation.y) * fDamageValue * 2.0f;
	move.z += cosf(HitRotation.y) * fDamageValue * 2.0f;

	move.y += fDamageValue;


	if (m_bDamageVoice == false)
	{
		switch (m_PlayerType)
		{
		case CPlayer::TYPE_BARANCE:
			pSound->SetVolume(CSound::SOUND_LABEL_VOICE_DOG_DAMAGE00, 5.0f);
			pSound->PlaySound(CSound::SOUND_LABEL_VOICE_DOG_DAMAGE00);
			break;
		case CPlayer::TYPE_POWER:
			pSound->SetVolume(CSound::SOUND_LABEL_VOICE_BEAR_DAMAGE00, 5.0f);
			pSound->PlaySound(CSound::SOUND_LABEL_VOICE_BEAR_DAMAGE00);
			break;
		case CPlayer::TYPE_SPEED:
			pSound->SetVolume(CSound::SOUND_LABEL_VOICE_CAT_DAMAGE00, 2.0f);
			pSound->PlaySound(CSound::SOUND_LABEL_VOICE_CAT_DAMAGE00);
			break;
		case CPlayer::TYPE_REACH:
			pSound->SetVolume(CSound::SOUND_LABEL_VOICE_RABBIT_DAMAGE00, 5.0f);
			pSound->PlaySound(CSound::SOUND_LABEL_VOICE_RABBIT_DAMAGE00);
			break;
		default:
			break;
		}
		//�����Đ�����
		m_bDamageVoice = true;
	}

}
//=============================================================================
// �����蔻��(�I�u�W�F�N�g)����
//=============================================================================
bool CPlayer::CollisonObject(D3DXVECTOR3 *pos, D3DXVECTOR3 * posOld, D3DXVECTOR3 * move, D3DXVECTOR3 radius)
{
	bool bHit = false;
	CScene *pScene = NULL;
	CPlayer *pPlayer[MAX_PLAYER];
	CPoint *pPoint[MAX_PLAYER];

	int nCntBush = 0;

	// �擪�̃I�u�W�F�N�g���擾
	pScene = CScene::GetTop(SCENEX_PRIORITY);

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		pPlayer[nCntPlayer] = CManager::GetPlayer(nCntPlayer);			// �v���C���[���擾
		pPoint[nCntPlayer] = CManager::GetPoint(nCntPlayer);
	}

	while (pScene != NULL)
	{// �D�揇�ʂ�3�̃I�u�W�F�N�g��1��1�m���߂�
	 // �����̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false && pScene->GetObjType() == CScene::OBJTYPE_SCENEX)
		{// ���S�t���O�������Ă��Ȃ�����
			// �I�u�W�F�N�g�̎�ނ��m���߂�
			CSceneX *pSceneX = ((CSceneX*)pScene);		// CSceneX�փL���X�g(�^�̕ύX)
			if (pSceneX->GetCollsionType() != CSceneX::COLLISIONTYPE_NONE)
			{
				m_bLand = pSceneX->Collision(pos, posOld, move, radius, m_nID);

				CObject *pSceneObj = ((CObject*)pSceneX);		// CObject�փL���X�g(�^�̕ύX)
				for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
				{
					m_bInbush[nCnt] = false;
				}
				if (m_bLand == true)
				{// ���f���ɓ�����
					bHit = true;

					if (pSceneObj->GetRealTimeType() == CObject::REALTIME_NOTMOVE)
					{
						if (pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_CONVEYOR_FRONT || pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_CONVEYOR_BACK ||
							pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_CONVEYOR_LEFT || pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_CONVEYOR_RIHHT)
						{	// �x���g�R���x�A�̔���
							pSceneObj->BeltConveyor(move, pSceneObj->GetSwitch());
						}
						else if (pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_KNOCKBACK_SMALL || pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_KNOCKBACK_DURING ||
							pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_KNOCKBACK_BIG)
						{	// �m�b�N�o�b�N�̔���
							pSceneObj->KnockBack(move, m_nID);
						}
						else if (pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_SWITCH)
						{//	�X�C�b�`
							pSceneObj->SwitchBeltConveyor(m_bLand);
						}

					}
					else if (pSceneObj->GetRealTimeType() == CObject::REALTIME_INITPOS)
					{
						pSceneObj->AffectedLanding(move, m_nID);
					}

					if (pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_BUSH)
					{	//���ނ�ɂ���Ƃ������ɂ���
						PlayerAlpha(0.5f);
						//�����鑐�ނ�̔ԍ����擾
						m_nObjNumber = pSceneObj->GetSceneXNum();
						if (m_nID == 0)
						{
							m_bInbush[0] = true;
						}
						else if (m_nID == 1)
						{
							m_bInbush[1] = true;
						}
						else if (m_nID == 2)
						{
							m_bInbush[2] = true;
						}
						else if (m_nID == 3)
						{
							m_bInbush[3] = true;
						}

						for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
						{
							if (pPlayer[nCntPlayer] != NULL && nCntPlayer != GetID())
							{//���v���C���[�Ɍ����Ă��Ȃ�
								int ntest = GetID();
								if (m_nObjNumber != pPlayer[nCntPlayer]->GetLandObjNumber())
								{	//�������ނ�ɂ��Ȃ��Ƃ�
									pPlayer[nCntPlayer]->SetVision(GetID(), false);
									if (pPoint[nCntPlayer] != NULL) { pPoint[nCntPlayer]->SetVision(GetID(), false); }
								}
							}
						}
						nCntBush++;
						bHit = false;
					}

					break;
				}
				else
				{
					if (nCntBush == 0)
					{//���ނ�ɓ����Ă��Ȃ��Ƃ�
						//������߂�
						PlayerAlpha(1.0f);

						for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
						{
							if (pPlayer[nCntPlayer] != NULL && nCntPlayer != GetID())
							{	//���v���C���[�Ɍ����Ă���
								int nte = GetID();
								pPlayer[nCntPlayer]->SetVision(GetID(), true);
								if (pPoint[nCntPlayer] != NULL) { pPoint[nCntPlayer]->SetVision(GetID(), true); }
							}
						}
						//m_bStealth = true;
						bHit = false;
						m_nObjNumber = 0;
						//�����ȑ���߂�
						//CSceneX::SetTranslucentBush(0);
					}
				}
			}
		}
		// ���̃V�[���ɐi�߂�
		pScene = pSceneNext;
	}

	if (nCntBush == 0)
	{//���ނ�ɓ����Ă��Ȃ��Ƃ�
	 //�����ȑ���߂�
	 CSceneX::SetTranslucentBush(GetID(),0);
	}

	return bHit;
}
//=============================================================================
// �߂��v���C���[���擾���鏈��
//=============================================================================
int		CPlayer::GetNearPlayer(void)
{
	D3DXVECTOR3 PlayerPos[4] = {};
	CCharaBase* pChara = NULL;
	CPlayer* pPlayer = NULL;
	int nCntPlayer = 0;
	//�l�̎擾
	for (nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		pChara = NULL;
		pPlayer = NULL;
		int nid = m_nID;
		pPlayer = CManager::GetPlayer(nCntPlayer);			// �v���C���[���擾

		if (pPlayer != NULL && GetVision(nCntPlayer) == true)
		{
			pChara = pPlayer->GetCharaMover();
			if (pChara != NULL)
			{//�L�����N���X���ɂ�����W���擾
				PlayerPos[nCntPlayer] = pChara->GetPosition();
			}
			else
			{//�L�����N���X���������ꍇ������Ȓl������
				PlayerPos[nCntPlayer] = D3DXVECTOR3(-99999.9f, -99999.9f, -99999.9f);
			}
		}
		else
		{	//�v���C���[�����Ȃ��ꍇ�͋���Ȓl������
			PlayerPos[nCntPlayer] = D3DXVECTOR3(-99999.9f, -99999.9f, -99999.9f);
		}
	}

	//�l�̔�r
	float fNearLength = 99999.9f;
	int nPlayerNum = -1;
	for (nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nCntPlayer != m_nID)
		{//�����ȊO�Ɣ�����s��
			//�������擾(-�͏Ȃ�)
			float fLength = fabsf(sqrtf(powf(PlayerPos[m_nID].x - PlayerPos[nCntPlayer].x, 2.0f) +
				powf(PlayerPos[m_nID].z - PlayerPos[nCntPlayer].z, 2.0f)));

			if (fLength < fNearLength &&
				fLength < PLAYER_LOCKON_LENGTH)
			{
				nPlayerNum = nCntPlayer;
				fNearLength = fLength;
			}
		}
	}
	return nPlayerNum;
}

//=============================================================================
// �����x�̐ݒ菈��
//=============================================================================
void CPlayer::PlayerAlpha(float fAlpha)
{
	for (int nCntBody = 0; nCntBody < BODY_MAX; nCntBody++)
	{
		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			if (m_pPlayerParts[nCntParts][nCntBody] != NULL)
			{
				m_pPlayerParts[nCntParts][nCntBody]->SetAlpha(fAlpha, 300);
			}
		}
	}
}

//=============================================================================
// ���f�����[�h����
//=============================================================================
HRESULT CPlayer::ModelLoad(LPCSTR pFileName, PLAYER_TYPE type, BODY body)
{
	FILE* pFile = NULL;		// �t�@�C���|�C���^
	char ReadText[256];		// �ǂݍ��񂾕���������Ă���
	char HeadText[256];		// ��r�p
	char DustBox[256];		// �g�p���Ȃ����̂����Ă���

	int nCntMotionSetType = 0;					// ���[�V�����Z�b�g�̎�ނ̐�
	int nCntMotionType = 1;						// ���[�V�����̎�ނ̐�
	int nCntKeySet = 0;							// �L�[�Z�b�g��
	int nCntKey = 0;							// �L�[��
	int nCntPartsSet = 0;						// �p�[�c��
	int nCntFileNameNum = 0;
	int nPartsNum = 0;

		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			ObjRelease(m_pPlayerParts[nCntParts][body]);
			m_pPlayerParts[nCntParts][body] = NULL;
		}
	if (m_PlayerLoadState[type][body].bLoad == false)
	{//	�܂����̏�񂪃��[�h����Ă��Ȃ����
		for (int nCntMotion = 0; nCntMotion < MOTION_UPPER_MAX; nCntMotion++)
		{
			m_PlayerLoadState[type][body].prop[nCntMotion]();
		}

		//�t�@�C���I�[�v��
		pFile = fopen(pFileName, "r");

		if (pFile != NULL)
		{//�t�@�C�����J����Ă����
			while (strcmp(HeadText, "SCRIPT") != 0)
			{// "SCRIPT" ���ǂݍ��܂��܂ŌJ��Ԃ��������ǂݎ��
				fgets(ReadText, sizeof(ReadText), pFile);
				sscanf(ReadText, "%s", &HeadText);
			}
			if (strcmp(HeadText, "SCRIPT") == 0)
			{// "SCRIPT" ���ǂݎ�ꂽ�ꍇ�A�����J�n
				while (strcmp(HeadText, "END_SCRIPT") != 0)
				{// "END_SCRIPT" ���ǂݍ��܂��܂ŌJ��Ԃ��������ǂݎ��
					fgets(ReadText, sizeof(ReadText), pFile);
					sscanf(ReadText, "%s", &HeadText);

					if (strcmp(HeadText, "\n") == 0)
					{// ������̐擪�� [\n](���s) �̏ꍇ�������Ȃ�

					}
					else if (strcmp(HeadText, "MODEL_FILENAME") == 0)
					{
						sscanf(ReadText, "%s %c %s", &DustBox, &DustBox, m_PlayerLoadState[type][body].info[nCntFileNameNum].FileName);
						nCntFileNameNum++;
					}
					else if (strcmp(HeadText, "CHARACTERSET") == 0)
					{//�L����
						while (strcmp(HeadText, "END_CHARACTERSET") != 0)
						{// "END_CHARACTERSET" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
							fgets(ReadText, sizeof(ReadText), pFile);
							sscanf(ReadText, "%s", &HeadText);
							if (strcmp(HeadText, "\n") == 0)
							{// ������̐擪�� [\n](���s) �̏ꍇ�������Ȃ�

							}
							if (strcmp(HeadText, "NUM_PARTS") == 0)
							{
								sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &m_PlayerLoadState[type][body].nPartsNum);
							}
							else if (strcmp(HeadText, "PARTSSET") == 0)
							{//PARTSSET��ǂ݂Ƃ�����
								while (strcmp(HeadText, "END_PARTSSET") != 0)
								{
									fgets(ReadText, sizeof(ReadText), pFile);
									sscanf(ReadText, "%s", &HeadText);

									if (strcmp(HeadText, "\n") == 0)
									{// ������̐擪�� [\n](���s) �̏ꍇ�������Ȃ�

									}
									else if (strcmp(HeadText, "INDEX") == 0)
									{
										sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &m_PlayerLoadState[type][body].info[nCntPartsSet].nIndex);
									}
									else if (strcmp(HeadText, "PARENT") == 0)
									{
										sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &m_PlayerLoadState[type][body].info[nCntPartsSet].nParent);
									}
									else if (strcmp(HeadText, "POS") == 0)
									{
										sscanf(ReadText, "%s %c %f %f %f", &DustBox,
											&DustBox,
											&m_PlayerLoadState[type][body].info[nCntPartsSet].pos.x,
											&m_PlayerLoadState[type][body].info[nCntPartsSet].pos.y,
											&m_PlayerLoadState[type][body].info[nCntPartsSet].pos.z);
									}
									else if (strcmp(HeadText, "ROT") == 0)
									{
										sscanf(ReadText, "%s %c %f %f %f", &DustBox,
											&DustBox,
											&m_PlayerLoadState[type][body].info[nCntPartsSet].rot.x,
											&m_PlayerLoadState[type][body].info[nCntPartsSet].rot.y,
											&m_PlayerLoadState[type][body].info[nCntPartsSet].rot.z);
									}
								}
								nCntPartsSet++;

							}
						}
					}
					else if (strcmp(HeadText, "MOTIONSET") == 0)
					{//���[�V����
						while (strcmp(HeadText, "END_MOTIONSET") != 0)
						{// "END_MOTIONSET" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
							fgets(ReadText, sizeof(ReadText), pFile);
							sscanf(ReadText, "%s", &HeadText);

							if (strcmp(HeadText, "\n") == 0)
							{// ������̐擪�� [\n](���s) �̏ꍇ�������Ȃ�

							}
							else if (strcmp(HeadText, "LOOP") == 0)
							{//���[�v
								sscanf(ReadText, "%s %c %d", &DustBox, &DustBox,
									&m_PlayerLoadState[type][body].prop[nCntMotionType].nLoop);
							}
							else if (strcmp(HeadText, "NUM_KEY") == 0)
							{//�L�[��
								sscanf(ReadText, "%s %c %d", &DustBox, &DustBox,
									&m_PlayerLoadState[type][body].prop[nCntMotionType].nKeyNum);
							}
							else if (strcmp(HeadText, "KEYSET") == 0)
							{
								while (strcmp(HeadText, "END_KEYSET") != 0)
								{// "END_KEYSET" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
									fgets(ReadText, sizeof(ReadText), pFile);
									sscanf(ReadText, "%s", &HeadText);
									if (strcmp(HeadText, "\n") == 0)
									{// ������̐擪�� [\n](���s) �̏ꍇ�������Ȃ�

									}
									else if (strcmp(HeadText, "FRAME") == 0)
									{//��ԃt���[��
										sscanf(ReadText, "%s %c %d", &DustBox, &DustBox,
											&m_PlayerLoadState[type][body].prop[nCntMotionType].key[nCntKeySet].nFrame);
									}
									else if (strcmp(HeadText, "KEY") == 0)
									{//�L�[���
										while (strcmp(HeadText, "END_KEY") != 0)
										{// "END_KEY" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
											fgets(ReadText, sizeof(ReadText), pFile);
											sscanf(ReadText, "%s", &HeadText);

											if (strcmp(HeadText, "\n") == 0)
											{// ������̐擪�� [\n](���s) �̏ꍇ�������Ȃ�

											}
											else if (strcmp(HeadText, "POS") == 0)
											{//���W
												sscanf(ReadText, "%s %c %f %f %f", &DustBox,
													&DustBox,
													&m_PlayerLoadState[type][body].prop[nCntMotionType].key[nCntKeySet].Pos[nCntKey].x,
													&m_PlayerLoadState[type][body].prop[nCntMotionType].key[nCntKeySet].Pos[nCntKey].y,
													&m_PlayerLoadState[type][body].prop[nCntMotionType].key[nCntKeySet].Pos[nCntKey].z);
											}
											else if (strcmp(HeadText, "ROT") == 0)
											{//�p�x
												sscanf(ReadText, "%s %c %f %f %f", &DustBox,
													&DustBox,
													&m_PlayerLoadState[type][body].prop[nCntMotionType].key[nCntKeySet].Rot[nCntKey].x,
													&m_PlayerLoadState[type][body].prop[nCntMotionType].key[nCntKeySet].Rot[nCntKey].y,
													&m_PlayerLoadState[type][body].prop[nCntMotionType].key[nCntKeySet].Rot[nCntKey].z);
											}

										}
										nCntKey++;
									}
								}
								nCntKeySet++;
								nCntKey = 0;
							}
						}
						nCntMotionType++;
						nCntKeySet = 0;
					}
				}
				nCntMotionType = 0;
			}

		}
		fclose(pFile);
		m_PlayerLoadState[type][body].bLoad = true;
	}

	//���ݒ�
	int nCntParts = 0;
		for (nCntParts = 0; nCntParts < m_PlayerLoadState[type][body].nPartsNum; nCntParts++)
		{

			if (ObjCreate(m_pPlayerParts[nCntParts][body]))
			{//�������ꂽ��
				m_pPlayerParts[nCntParts][body]->Set(m_PlayerLoadState[type][body].info[nCntParts].FileName,
					m_PlayerLoadState[type][body].info[nCntParts].pos,
					m_PlayerLoadState[type][body].info[nCntParts].rot, NULL);

				switch (type)
				{//�^�C�v���Ƃ̏���
				case TYPE_BARANCE:
					m_pPlayerParts[nCntParts][body]->BindTexture("INU_UV");
					break;
				case TYPE_POWER:
					m_pPlayerParts[nCntParts][body]->BindTexture("KUMA_UV");
					break;
				case TYPE_SPEED:
					m_pPlayerParts[nCntParts][body]->BindTexture("NECO_UV");
					break;
				case TYPE_REACH:
					m_pPlayerParts[nCntParts][body]->BindTexture("USAGI_UV");
					break;
				}
			}
		}

	//�e�}�g���N�X�Z�b�g
	for (int nCntParts = 0; nCntParts < m_PlayerLoadState[type][body].nPartsNum; nCntParts++)
	{
		int nNum = m_PlayerLoadState[type][body].info[nCntParts].nParent;
		if (nNum != -1)
		{
			m_pPlayerParts[nCntParts][body]->SetParent(m_pPlayerParts[nNum][body]->GetMatrix());
		}
		else
		{
			m_pPlayerParts[nCntParts][body]->SetParent(m_pCharactorMove->GetMatrix());
		}
	}

	//���[�V��������ǂݍ��ݕϐ�����R�s�[
	for (int nCntMotion = 0; nCntMotion < (body == LOWER_BODY ? MOTION_LOWER_MAX : MOTION_UPPER_MAX); nCntMotion++)
	{//(body == LOWER_BODY ? MOTION_LOWER_MAX : MOTION_UPPER_MAX) : �㉺�̃��[�V�������ɉ����ă��[�v����ς���
		m_propMotion[nCntMotion][body] = m_PlayerLoadState[type][body].prop[nCntMotion];
	}
	return S_OK;
}

//=============================================================================
// ���f�����[�h����
//=============================================================================
D3DXVECTOR3     CPlayer::GetBulletMuzzle(void)
{
	if (m_pPlayerParts[8][UPPER_BODY] != NULL)
	{
		return m_pPlayerParts[8][UPPER_BODY]->GetWorldPosition();
	}
	else
	{
		if (m_pCharactorMove != NULL)
		{
			return m_pCharactorMove->GetPosition() + D3DXVECTOR3(0.0f,10.0f,0.0f);
		}
	}
	return D3DXVECTOR3(0.0f,0.0f,0.0f);
}

//=============================================================================
// �e����UI�\���̏���
//=============================================================================
void CPlayer::BulletUI(D3DXVECTOR3 rot)
{
	D3DXVECTOR3 size = {};
	D3DXVECTOR3 rotUI = {};
	int nType = NULL;
	C3DCharactor* pChara = NULL;
	int nNear = GetNearPlayer();
	bool bType = false;

	if (m_pWordManager != NULL)
	{
		if (m_pWordManager->GetStock(0) == NOT_NUM)
		{	// �S�~�̏ꍇ
			size = D3DXVECTOR3(20.0f, 0.0f, 200.0f);
			nType = 1;
			rotUI = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		else
		{
			// �K�v�ȃT�C�Y��UI�̎�ނ�ݒ�
			if (m_PlayerType == TYPE_SPEED)			// �v���C���[���L(�~�T�C��)�̏ꍇ
			{
				if (nNear != -1)	// �˒��͈͓�
				{
					pChara = (C3DCharactor*)CManager::GetPlayer(nNear)->GetCharaMover();
					m_nTargetID = nNear;
					size = D3DXVECTOR3(20.0f, 30.0f, 0.0f);
					bType = true;
				}
				else
				{
					size = D3DXVECTOR3(200.0f, 0.0f, 200.0f);
					nType = 0;
					rotUI = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}
			else if (m_PlayerType == TYPE_REACH)	// ������
			{
				size = D3DXVECTOR3(20.0f, 0.0f, 300.0f);
				nType = 1;
				rotUI = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
			else if (m_PlayerType == TYPE_BARANCE)	// �v���C���[����(�V���b�g�K��)�̏ꍇ
			{
				size = D3DXVECTOR3(100.0f, 0.0f, 190.0f);
				nType = 0;
				rotUI = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
			else if (m_PlayerType == TYPE_POWER)	// �v���C���[���N�}(���e)�̏ꍇ
			{
				size = D3DXVECTOR3(100.0f, 0.0f, 70.0f);
				nType = 2;
				rotUI = D3DXVECTOR3(sinf(rot.y) * 150.0f, 0.0f, cosf(rot.y) * 150.0f);
			}
		}
	}

	if (bType == false)
	{
		if (m_pMissileUI != NULL) { m_pMissileUI->Uninit(); m_pMissileUI = NULL; }	// �~�T�C��UI�j��
																					// �e��UI�\��(�v���C���[�̊p�x���擾����)
		if (m_pBulletUI == NULL)
		{
			char *capName[2] = { "BulletUI", "BulletUIEx" };
			int nNameNum = 0;

			if (m_pWordManager != NULL && m_pWordManager->GetStock(0) != NOT_NUM)
			{
				if (m_PlayerType == TYPE_POWER) { nNameNum = 1; }
			}

			m_pBulletUI = CScene3D::Create(D3DXVECTOR3(m_pCharactorMove->GetPosition().x, 1.0f, m_pCharactorMove->GetPosition().z + 30.0f), capName[nNameNum]);
			m_pBulletUI->SetScene3DType(CScene3D::SCENE3DTYPE_ADDSYNTHESIS);
			m_pBulletUI->SetObjType(CScene3D::OBJTYPE_BULLETUI);
			m_pBulletUI->SetAlphaTest(true);
			m_pBulletUI->SetTexUV(D3DXVECTOR2(1.0f, 1.0f));
			m_pBulletUI->SetRot(rot);
		}

		if (m_pBulletUI != NULL)
		{
			char *capName[2] = { "BulletUI", "BulletUIEx" };
			int nNameNum = 0;

			if (m_pWordManager != NULL && m_pWordManager->GetStock(0) != NOT_NUM)
			{	// �S�~�ȊO�Ȃ�
				if (m_PlayerType == TYPE_POWER) { nNameNum = 1; }
			}

			m_pBulletUI->BindTexture(capName[nNameNum]);
			m_pBulletUI->SetBulletUI(size, rot, nType);
			m_pBulletUI->SetPos(D3DXVECTOR3((m_pCharactorMove->GetPosition().x) + rotUI.x, m_pCharactorMove->GetPosition().y + 3.0f, m_pCharactorMove->GetPosition().z + rotUI.z));
			m_pBulletUI->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		}
	}
	else if (bType == true)
	{
		//if (m_pBulletUI != NULL) { m_pBulletUI->Uninit(); m_pBulletUI = NULL; }	// �e��UI�j��

		D3DXVECTOR3 pos = D3DXVECTOR3(pChara->GetPosition().x, pChara->GetPosition().y, pChara->GetPosition().z - 12.0f);

		if (m_pMissileUI == NULL)
		{
			m_pMissileUI = CSceneBillBoard::Create(pos, size.x, size.y, "TARGET");
			m_pMissileUI->SetObjType(CSceneBillBoard::OBJTYPE_MISSILEUI);
			m_pMissileUI->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}

		if (m_pMissileUI != NULL)
		{
			D3DXCOLOR col = m_pMissileUI->GetCol();
			D3DXVECTOR3 size = {};
			size.x = m_pMissileUI->GetSize(0);
			size.y = m_pMissileUI->GetSize(1);

			if (col.g < 0.8f && col.b < 0.8f) { col.g += 0.02f; col.b += 0.01f; }
			else { col.g = 0.0f; col.b = 0.0f; }

			if (size.x < 30.0f && size.y < 40.0f) {
				size.x += 0.5f; size.y += 0.5f;
			}
			else { size.x = 20.0f; size.y = 30.0f; }

			m_pMissileUI->SetCol(col);
			m_pMissileUI->SetBillboard(pos, size.y, size.x);

			m_fBulletRotOld = atan2f((pChara->GetPosition().x - m_pCharactorMove->GetPosition().x), (pChara->GetPosition().z - m_pCharactorMove->GetPosition().z));
		}

		char *capName = { "BulletUI" };

		if (m_pBulletUI == NULL)
		{
			m_pBulletUI = CScene3D::Create(D3DXVECTOR3(m_pCharactorMove->GetPosition().x, 1.0f, m_pCharactorMove->GetPosition().z + 30.0f), capName);
			m_pBulletUI->SetScene3DType(CScene3D::SCENE3DTYPE_ADDSYNTHESIS);
			m_pBulletUI->SetObjType(CScene3D::OBJTYPE_BULLETUI);
			m_pBulletUI->SetAlphaTest(true);
			m_pBulletUI->SetTexUV(D3DXVECTOR2(1.0f, 1.0f));
			m_pBulletUI->SetRot(rot);

		}

		if (m_pBulletUI != NULL)
		{
			m_pBulletUI->BindTexture(capName);
			m_pBulletUI->SetBulletUI(D3DXVECTOR3(20.0f, 0.0f, 300.0f), D3DXVECTOR3(rot.x, m_fBulletRotOld, rot.z), 1);
			m_pBulletUI->SetPos(D3DXVECTOR3((m_pCharactorMove->GetPosition().x), m_pCharactorMove->GetPosition().y + 3.0f, m_pCharactorMove->GetPosition().z));
			m_pBulletUI->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		}

	}
}

//=============================================================================
// �e����UI�\���̏���
//=============================================================================
void CPlayer::BulletUIUninit(void)
{
	if (m_pBulletUI != NULL)
	{	// �eUI
		// �����x�̎擾
		float ColA = m_pBulletUI->Getcol().a;

		// �����x��������
		ColA -= 0.03f;

		m_pBulletUI->SetColor(D3DXCOLOR(m_pBulletUI->Getcol().r, m_pBulletUI->Getcol().g, m_pBulletUI->Getcol().b, ColA));

		m_pBulletUI->SetPos(m_pBulletUI->GetPos());

		if (ColA < 0.3f)
		{// �w�肵���l���Ⴂ�ꍇ
			m_pBulletUI->Uninit();
			m_pBulletUI = NULL;
		}
	}
	else if (m_pMissileUI != NULL)
	{	// �~�T�C��UI
		// �����x�̎擾
		float ColA = m_pMissileUI->GetCol().a;

		// �����x��������
		ColA -= 0.03f;

		m_pMissileUI->SetCol(D3DXCOLOR(m_pMissileUI->GetCol().r, m_pMissileUI->GetCol().g, m_pMissileUI->GetCol().b, ColA));

		m_pMissileUI->Setpos(m_pMissileUI->GetPos());

		if (ColA < 0.3f)
		{// �w�肵���l���Ⴂ�ꍇ
			m_pMissileUI->Uninit();
			m_pMissileUI = NULL;
		}
	}

	m_nTargetID = MAX_PLAYER;
}

//=============================================================================
// �����Đ�����
//=============================================================================
void CPlayer::PlayVoice(CPlayer::PLAYER_TYPE type)
{
	CSound *pSound = CManager::GetSound();		//	���̎擾

												//�L�������Ƃ̉���(�����_���Q���)
	switch (type)
	{
	case CPlayer::TYPE_BARANCE:
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
		if (rand() % 2 == 0)
		{
			pSound->SetVolume(CSound::SOUND_LABEL_VOICE_CAT_ATTACK00, 5.0f);
			pSound->PlaySound(CSound::SOUND_LABEL_VOICE_CAT_ATTACK00);
		}
		else
		{
			pSound->SetVolume(CSound::SOUND_LABEL_VOICE_CAT_ATTACK01, 5.0f);
			pSound->PlaySound(CSound::SOUND_LABEL_VOICE_CAT_ATTACK01);
		}
		break;
	case CPlayer::TYPE_REACH:
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
		break;
	default:
		break;
	}
}

//=============================================================================
// �|�[�Y�ݒ�̏���
//=============================================================================
void CPlayer::SetPauseFlag(void)
{
	if (CCommand::GetCommand("PAUSE", m_nID) && CFade::GetFade() == CFade::FADE_NONE && CManager::GetMode() == CManager::MODE_GAME &&
		CScene::GetbPause() == false)
	{
		m_bPauseFlag =  true;
		CScene::SetbPause(true);
	}
}