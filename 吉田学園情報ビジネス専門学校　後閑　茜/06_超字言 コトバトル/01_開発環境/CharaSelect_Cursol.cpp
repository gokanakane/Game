//=============================================================================
//
// �L�����Z���N�g���� [CharaSelect.cpp]
// Author : ��Ձ@��
//
//=============================================================================
#include "CharaSelect_Cursol.h"
#include "manager.h"
#include "debugProc.h"
#include "fade.h"
#include "input.h"
#include "InputKeyboard.h"
#include"game.h"

//============================================================================
//	�}�N����`
//============================================================================
#define SIZE_X (SCREEN_WIDTH/2)									//����
#define SIZE_Y (SCREEN_HEIGHT/2)								//�c��
#define DEFAULT_POS	(D3DXVECTOR3(0.0f,0.0f,0.0f))				//�|���S���̏����ʒu
#define DEFAULT_SIZE (150.0f)									//�|���S���T�C�Y�̊�{�̑傫��
#define CURSOL_INITPOS (D3DXVECTOR3(250.0f,545.0f,0.0f))		//�J�[�\���̏����ʒu
#define CHARASELCHOICE_INTERVAL (260.0f)						//�I�����|���S�����m�̊Ԋu
#define CURSOR_MOVE (3.0f)										//�J�[�\���̈ړ����x
#define CURSOR_SIZE (0.3f)										//�J�[�\���̃T�C�Y

//============================================================================
//�ÓI�����o�ϐ��錾
//============================================================================

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CCharaSelCursol::CCharaSelCursol()
{
	m_nId = 0;
	m_nCntGauge = 0;
	m_fGaugeSizeX = 0.0f;
	m_fMaxGaugeX = 0.0f;
	m_CharaType = CPlayer::TYPE_MAX;
	m_CharaTypeOld = CPlayer::TYPE_MAX;
	m_SelectState = CCharaSelect::SELECTSTATE_NOSELECT;
	m_SelectStateold = CCharaSelect::SELECTSTATE_NOSELECT;
	m_pos = DEFAULT_POS;
	m_move = DEFAULT_POS;
	m_bPCSelMove = false;
	m_bPlayer = false;
}
//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CCharaSelCursol::~CCharaSelCursol() {}

//=============================================================================
//	��������
//=============================================================================
CCharaSelCursol *CCharaSelCursol::Create(int nId)
{
	CCharaSelCursol *pCursol = NULL;
	if (pCursol == NULL)
	{
		pCursol = new CCharaSelCursol;
	}
	if (pCursol != NULL)
	{
		pCursol->Init();
		pCursol->Set(nId);
		pCursol->InitCharaSelectPoly();
	}
	return pCursol;
}
//=============================================================================
//	�ݒ�
//=============================================================================
void CCharaSelCursol::Set(int nId)
{
	m_nId = nId;
}
//=============================================================================
//	����������
//=============================================================================
HRESULT CCharaSelCursol::Init(void)
{
	Initpointer();
	SetCommand();

	return S_OK;
}
//=============================================================================
//	�I������
//=============================================================================
void CCharaSelCursol::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		if (m_apCursor2D != NULL)
		{
			m_apCursor2D->Uninit();
			m_apCursor2D = NULL;
		}
		if (m_apBadge2D != NULL)
		{
			m_apBadge2D->Uninit();
			m_apBadge2D = NULL;
		}
		if (m_apGauge2D != NULL)
		{
			m_apGauge2D->Uninit();
			m_apGauge2D = NULL;
		}
	}

	Release();
}
//=============================================================================
//	�X�V����
//=============================================================================
void CCharaSelCursol::Update(void)
{
	CManager *pManager = NULL;
	CFade *pFade = CManager::GetFade();
	CCharaSelect *pCharaSel = CManager::GetCharaSelect();

	//�ړ�����
	if (pCharaSel->GetCardPro() == true)
	{
		if (m_bPlayer == true)
		{
			Move(pFade, pManager, m_nId);
			pCharaSel->SelectProduction(m_nId, m_SelectState, m_SelectStateold, m_CharaType);
			pCharaSel->CharaSelTex(m_nId, m_SelectState, m_CharaType);
			pCharaSel->SetPlayerWindowChara(m_nId, m_CharaType);
		}

	}
}
//=============================================================================
//	�`�揈��
//=============================================================================
void CCharaSelCursol::Draw(void) {}

//=============================================================================
// �R�}���h�̐ݒ�
//=============================================================================
void CCharaSelCursol::SetCommand(void)
{
	CCommand::RegistCommand("RIGHT_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_RIGHT);
	CCommand::RegistCommand("RIGHT_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_D);
	CCommand::RegistCommand("RIGHT_R", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_RIGHT);

	CCommand::RegistCommand("LEFT_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_LEFT);
	CCommand::RegistCommand("LEFT_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_A);
	CCommand::RegistCommand("LEFT_R", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_LEFT);

	CCommand::RegistCommand("UP_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_UP);
	CCommand::RegistCommand("UP_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_W);
	CCommand::RegistCommand("UP_R", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_UP);

	CCommand::RegistCommand("DOWN_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_DOWN);
	CCommand::RegistCommand("DOWN_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_S);
	CCommand::RegistCommand("DOWN_R", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_DOWN);

	CCommand::RegistCommand("RELEASE_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_RETURN);
	CCommand::RegistCommand("RELEASE_R", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_A);
	CCommand::RegistCommand("RELEASE_R", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_RIGHT_SHOULDER);

	CCommand::RegistCommand("RELEASE_L", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_BACKSPACE);
	CCommand::RegistCommand("RELEASE_L", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_X);
	CCommand::RegistCommand("RELEASE_L", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_LEFT_SHOULDER);

}
//=============================================================================
// �|�C���^�̏���������
//=============================================================================
void CCharaSelCursol::Initpointer(void)
{
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		if (m_apCursor2D != NULL) { m_apCursor2D = NULL; }
		if (m_apBadge2D != NULL) { m_apBadge2D = NULL; }
		if (m_apGauge2D != NULL) { m_apGauge2D = NULL; }
	}
}
//=============================================================================
// �|���S���̏����ݒ�
//=============================================================================
void CCharaSelCursol::InitCharaSelectPoly(void)
{
	/* �v���C���[�̐l���擾 */
	m_PlayerNum = CPlayerSelect::GetModeSelectMode();

	//�o�b�W
	m_apBadge2D = CScene2D::Create(D3DXVECTOR3(CURSOL_INITPOS.x + (CHARASELCHOICE_INTERVAL*m_nId),
		CURSOL_INITPOS.y,
		CURSOL_INITPOS.z), "CHARASEL_BADGE");
	m_apBadge2D->SetWidthHeight(DEFAULT_SIZE*CURSOR_SIZE, DEFAULT_SIZE*CURSOR_SIZE);

	//�J�[�\��
	m_apCursor2D = CScene2D::Create(D3DXVECTOR3(CURSOL_INITPOS.x + (CHARASELCHOICE_INTERVAL*m_nId),
		CURSOL_INITPOS.y,
		CURSOL_INITPOS.z), "CHARASEL_BADGE", 5);
	m_apCursor2D->SetWidthHeight(DEFAULT_SIZE*CURSOR_SIZE, DEFAULT_SIZE*CURSOR_SIZE);

	//�߂钷�������̃Q�[�W
	m_apGauge2D = CScene2D::Create(D3DXVECTOR3(m_apCursor2D->GetPosition().x - 45.0f,
		m_apCursor2D->GetPosition().y + 50.0f,
		m_apCursor2D->GetPosition().z), " ", 4);
	m_apGauge2D->SetScene2DLeftCenter(m_apGauge2D->GetPosition(), DEFAULT_SIZE*CURSOR_SIZE, DEFAULT_SIZE*0.03f);
	m_apGauge2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_fMaxGaugeX = m_apGauge2D->GetSize(0);
	m_apGauge2D->SetbDraw(false);

	/* �v���C���[�l���ɍ��킹�Đݒ� */
	if (m_nId < (int)*m_PlayerNum)
	{
		//�J�[�\���ƃo�b�W
		m_apBadge2D->SetTex(D3DXVECTOR2(0.0f + (1.0f / 5)*m_nId, 0.5f), D3DXVECTOR2((1.0f / 5) + (1.0f / 5)*m_nId, 1.0f));
		m_apCursor2D->SetTex(D3DXVECTOR2(0.0f + (1.0f / 5)*m_nId, 0.0f), D3DXVECTOR2((1.0f / 5) + (1.0f / 5)*m_nId, 0.5f));
		m_bPlayer = true;
	}
	else
	{
		//�J�[�\���ƃo�b�W
		m_apBadge2D->SetTex(D3DXVECTOR2(0.8f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
		m_apCursor2D->SetTex(D3DXVECTOR2(0.8f, 0.0f), D3DXVECTOR2(1.0f, 0.5f));
		m_bPlayer = false;
	}
}
//=============================================================================
// �߂钷�������Q�[�W�̏���
//=============================================================================
void CCharaSelCursol::PressGauge(CFade *pFade, CManager *pManager, int operation)
{
	CSound *pSound = CManager::GetSound();		//	���̎擾
	if (m_apGauge2D->GetbDraw() == true)
	{
		if (CCommand::GetCommand("RELEASE_L", operation) == true)
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT01);
			m_nCntGauge++;
			if (m_nCntGauge >= 90)
			{//3�b�o������
				pFade->SetFade(pManager->MODE_SELECT, pFade->FADE_OUT);
			}
		}
		else if (CCommand::GetCommand("RELEASE_L", operation) == false)
		{
			m_nCntGauge --;
			if (m_nCntGauge <= 0)
			{
				m_nCntGauge = 0;
			}
		}
		m_fGaugeSizeX = (float)m_nCntGauge / m_fMaxGaugeX;
		m_apGauge2D->SetScene2DLeftCenter(D3DXVECTOR3(m_apGauge2D->GetPosition().x - 45.0f, m_apGauge2D->GetPosition().y, m_apGauge2D->GetPosition().z),
			m_fMaxGaugeX * m_fGaugeSizeX, m_apGauge2D->GetSize(1));
	}

	switch (operation)
	{
	case 0:
		m_apGauge2D->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		break;
	case 1:
		m_apGauge2D->SetCol(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
		break;
	case 2:
		m_apGauge2D->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		break;
	case 3:
		m_apGauge2D->SetCol(D3DXCOLOR(0.9f, 0.9f, 0.0f, 1.0f));
		break;

	}
}
//=============================================================================
// �J�[�\���̈ړ�����
//=============================================================================
D3DXVECTOR3 CCharaSelCursol::MoveRestriction(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 mPos;
	mPos = pos;

	if (pos.y <= 0.0f + (DEFAULT_SIZE*CURSOR_SIZE))
	{
		mPos.y = 0.0f + (DEFAULT_SIZE*CURSOR_SIZE);
	}
	if (pos.y >= SCREEN_HEIGHT - (DEFAULT_SIZE*CURSOR_SIZE))
	{
		mPos.y = SCREEN_HEIGHT - (DEFAULT_SIZE*CURSOR_SIZE);
	}
	if (pos.x <= 100.0f + (DEFAULT_SIZE*CURSOR_SIZE))
	{
		mPos.x = 100.0f + (DEFAULT_SIZE*CURSOR_SIZE);
	}
	if (pos.x >= 1180.0f - (DEFAULT_SIZE*CURSOR_SIZE))
	{
		mPos.x = 1180.0f - (DEFAULT_SIZE*CURSOR_SIZE);
	}

	return mPos;
}
//=============================================================================
// �ړ�����
//=============================================================================
void CCharaSelCursol::Move(CFade *pFade, CManager *pManager, int nControllNum)
{
	CSound *pSound = CManager::GetSound();		//	���̎擾
	CCharaSelect *pCharaSel = CManager::GetCharaSelect();

	if (m_apCursor2D != NULL)
	{
		m_pos = m_apCursor2D->GetPosition();
	}

	//�t�F�[�h�����I����/�J�n�O�̂ݓ�������
	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		/* �I�������o�֐� */
		if (pCharaSel->GetConf() == false)
		{
			pCharaSel->SelectProduction(nControllNum, m_SelectState,
				m_SelectStateold, m_CharaType);
		}

		if (pCharaSel->GetConf() == true)
		{//�I���m�肪�\�ɂȂ�����
			pCharaSel->DecisionCharactor(pFade, pManager, nControllNum);
		}

		/* �J�[�\���ړ�����  */
		if (CCommand::GetCommand("RIGHT_R", nControllNum) == true)
		{//������
			if (CCommand::GetCommand("UP_R", nControllNum) == true)
			{//�㉟��
				m_move.x += sinf(D3DX_PI * 0.75f)*CURSOR_MOVE;
				m_move.y += cosf(D3DX_PI * 0.75f)*CURSOR_MOVE;
			}
			else if (CCommand::GetCommand("DOWN_R", nControllNum) == true)
			{//������
				m_move.x += sinf(D3DX_PI * 0.25f)*CURSOR_MOVE;
				m_move.y += cosf(D3DX_PI * 0.25f)*CURSOR_MOVE;
			}
			else
			{
				m_move.x += sinf(D3DX_PI * 0.5f)*CURSOR_MOVE;
				m_move.y += cosf(D3DX_PI * 0.5f)*CURSOR_MOVE;
			}
		}
		else if (CCommand::GetCommand("LEFT_R", nControllNum) == true)
		{//������
			if (CCommand::GetCommand("UP_R", nControllNum) == true)
			{//�㉟��
				m_move.x += sinf(-D3DX_PI * 0.75f)*CURSOR_MOVE;
				m_move.y += cosf(-D3DX_PI * 0.75f)*CURSOR_MOVE;
			}
			else if (CCommand::GetCommand("DOWN_R", nControllNum) == true)
			{//������
				m_move.x += sinf(-D3DX_PI * 0.25f)*CURSOR_MOVE;
				m_move.y += cosf(-D3DX_PI * 0.25f)*CURSOR_MOVE;
			}
			else
			{
				m_move.x += sinf(-D3DX_PI * 0.5f)*CURSOR_MOVE;
				m_move.y += cosf(-D3DX_PI * 0.5f)*CURSOR_MOVE;
			}
		}
		else if (CCommand::GetCommand("UP_R", nControllNum) == true)
		{//�㉟��
			m_move.x += sinf(D3DX_PI)*CURSOR_MOVE;
			m_move.y += cosf(D3DX_PI)*CURSOR_MOVE;
		}
		else if (CCommand::GetCommand("DOWN_R", nControllNum) == true)
		{//������
			m_move.x -= sinf(D3DX_PI)*CURSOR_MOVE;
			m_move.y -= cosf(D3DX_PI)*CURSOR_MOVE;
		}

		/* �ړ��͈͐��� */
		m_pos = MoveRestriction(m_pos);

		/* ���� */
		m_move.x += (0.0f - m_move.x) * 0.3f;
		m_move.y += (0.0f - m_move.y) * 0.3f;

		/* �ړ� */
		m_pos += m_move;

		/* �ړ��𔽉f */
		m_apCursor2D->SetPosition(m_pos);

		/* ���I�����̂݃J�[�\���ɒǏ] */
		if (m_bPCSelMove == false)
		{
			m_apBadge2D->SetPosition(D3DXVECTOR3(m_apCursor2D->GetPosition().x,
				m_apCursor2D->GetPosition().y - 50.0f,
				m_apCursor2D->GetPosition().z));
		}

		m_apGauge2D->SetPosition(D3DXVECTOR3(m_apCursor2D->GetPosition().x,
			m_apCursor2D->GetPosition().y + 50.0f,
			m_apCursor2D->GetPosition().z));

		/* �o�����X�Ɠ������Ă��� */
		if (pCharaSel->collision(nControllNum, CPlayer::TYPE_BARANCE) == true)
		{
			m_CharaType = CPlayer::TYPE_BARANCE;
			pCharaSel->SetWindowCharaDraw(nControllNum, true);
			if (CCommand::GetCommand("DECISION", nControllNum) == true && m_SelectState == CCharaSelect::SELECTSTATE_NOSELECT)
			{
				pSound->SetVolume(CSound::SOUND_LABEL_VOICE_SELECT_DOG, 5.0f);
				pSound->PlaySound(CSound::SOUND_LABEL_VOICE_SELECT_DOG);
				m_SelectState = CCharaSelect::SELECTSTATE_FLASH;
				m_bPCSelMove = true;
			}
		}
		/* �p���[�Ɠ������Ă��� */
		else if (pCharaSel->collision(nControllNum, CPlayer::TYPE_POWER) == true)
		{
			m_CharaType = CPlayer::TYPE_POWER;
			pCharaSel->SetWindowCharaDraw(nControllNum, true);
			if (CCommand::GetCommand("DECISION", nControllNum) == true && m_SelectState == CCharaSelect::SELECTSTATE_NOSELECT)
			{
				pSound->SetVolume(CSound::SOUND_LABEL_VOICE_SELECT_BEAR, 5.0f);
				pSound->PlaySound(CSound::SOUND_LABEL_VOICE_SELECT_BEAR);
				m_SelectState = CCharaSelect::SELECTSTATE_FLASH;
				m_bPCSelMove = true;
			}
		}
		/* �X�s�[�h�Ɠ������Ă��� */
		else if (pCharaSel->collision(nControllNum, CPlayer::TYPE_SPEED) == true)
		{
			m_CharaType = CPlayer::TYPE_SPEED;
			pCharaSel->SetWindowCharaDraw(nControllNum, true);
			if (CCommand::GetCommand("DECISION", nControllNum) == true && m_SelectState == CCharaSelect::SELECTSTATE_NOSELECT)
			{
				pSound->SetVolume(CSound::SOUND_LABEL_VOICE_SELECT_CAT, 5.0f);
				pSound->PlaySound(CSound::SOUND_LABEL_VOICE_SELECT_CAT);
				m_SelectState = CCharaSelect::SELECTSTATE_FLASH;
				m_bPCSelMove = true;
			}
		}
		/* ���[�`�Ɠ������Ă��� */
		else if (pCharaSel->collision(nControllNum, CPlayer::TYPE_REACH) == true)
		{
			m_CharaType = CPlayer::TYPE_REACH;
			pCharaSel->SetWindowCharaDraw(nControllNum, true);
			if (CCommand::GetCommand("DECISION", nControllNum) == true && m_SelectState == CCharaSelect::SELECTSTATE_NOSELECT)
			{
				pSound->SetVolume(CSound::SOUND_LABEL_VOICE_SELECT_RABBIT, 5.0f);
				pSound->PlaySound(CSound::SOUND_LABEL_VOICE_SELECT_RABBIT);
				m_SelectState = CCharaSelect::SELECTSTATE_FLASH;
				m_bPCSelMove = true;
			}
		}
		/* �����_���Ɠ������Ă��� */
		else if (pCharaSel->collision(nControllNum, CPlayer::TYPE_RANDOM) == true)
		{
			m_CharaType = CPlayer::TYPE_RANDOM;
			pCharaSel->SetWindowCharaDraw(nControllNum, true);
			if (CCommand::GetCommand("DECISION", nControllNum) == true && m_SelectState == CCharaSelect::SELECTSTATE_NOSELECT)
			{
				m_SelectState = CCharaSelect::SELECTSTATE_FLASH;
				m_bPCSelMove = true;
			}
		}
		else
		{
			pCharaSel->SetWindowCharaDraw(nControllNum, false);
		}
		if (m_SelectState == CCharaSelect::SELECTSTATE_SELECT)
		{
			if (CCommand::GetCommand("DELETE", nControllNum) == true)
			{
				m_SelectState = CCharaSelect::SELECTSTATE_NOSELECT;
				m_bPCSelMove = false;
			}
		}

		/* �߂� */
		if (pCharaSel->collisionBackMode(nControllNum) == true)
		{
			pCharaSel->SetBackMode(m_nId,true);
			m_apGauge2D->SetbDraw(true);
			m_apBadge2D->SetbDraw(false);
			PressGauge(pFade, pManager, nControllNum);
		}
		else
		{
			pCharaSel->SetBackMode(m_nId, false);
			m_apGauge2D->SetbDraw(false);
			m_apBadge2D->SetbDraw(true);
		}
	}
}
