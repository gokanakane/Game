//---------------------------------------------------------------------
// �Z���N�g���j���[���� [SelectMenu.cpp]
// Author : Mikiya Meguro/Akane Gokan
//---------------------------------------------------------------------
#include "SelectMenu.h"
#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"
#include "input.h"
#include "manager.h"
#include "PlayerNumSelect.h"
#include "fade.h"
#include "renderer.h"
#include "load.h"
#include "texture.h"
#include "debugProc.h"
#include "credit.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODESELECT_WIDTH		(1.0f)		//�|���S���̑傫��(��)
#define MODESELECT_HEIGHT		(1.0f)		//�|���S���̑傫��(�c)
#define MENU_WIDTH				(450.0f)	//�|���S���ƃ|���S���̊Ԃ̑傫��(��)
#define MENU_HEIGHT				(180.0f)	//�|���S���ƃ|���S���̊Ԃ̑傫��(�c)
#define MENU_INITPOS			(350.0f)	//���j���[�̏����ʒu
#define MENU_NUM_HEIGHT			(2)
#define MENU_NUM_WIDTH			(2)
#define MENU_INIT_POS			(370.0f)
#define MENU_BG					(150.0f)	//�|���S���̑傫��
#define NOSELECT_MENU_SIZE		(50.0f)		//�I�΂�Ă��Ȃ��Ƃ��̃|���S���̃T�C�Y

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
CSelectMenu::SELECT_MENU CSelectMenu::m_SelectMode = CSelectMenu::SELECT_MENU_NONE;
bool CSelectMenu::m_bModeSelect = false;

//--------------------------------------------
//�Z���N�g���j���[�N���X �R���X�g���N�^
//--------------------------------------------
CSelectMenu::CSelectMenu(int nPriority) : CScene(7)
{
	//�l�̏�����
	m_nSelect = 0;
	m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
	m_aModeSelectMenu[1].select = SELECTTYPE_NONE;
	m_aModeSelectMenu[2].select = SELECTTYPE_NONE;
	m_apPolygon3D_Ranking = NULL;

	for (int nCnt = 0; nCnt < MAX_SELECTMODE_MODESEL; nCnt++)
	{
		if (m_apPolygon_ModeSel[nCnt] != NULL)
		{
			m_apPolygon_ModeSel[nCnt] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < MAX_SELECTMODE_RANKING; nCnt++)
	{
		if (m_apPolygon2D_Ranking[nCnt] != NULL)
		{
			m_apPolygon2D_Ranking[nCnt] = NULL;
		}
	}
	m_fSpace = 0;
	m_fInitYpos = 0;

	/* ���o�ʕϐ��̏����� */
	m_nCntScrool = 0;
	m_nCntAnim = 0;
	m_nPatturnAnim = 0;
	m_nCntAnim2 = 0;
	m_nPatturnAnim2 = 0;
	m_fChangeMode = 0.3f;
	m_fMoveMode = 0.0f;
	m_fResultAlpha = 0.0f;
}

//--------------------------------------------
//�Z���N�g���j���[�N���X �f�X�g���N�^
//--------------------------------------------
CSelectMenu::~CSelectMenu()
{
}

//--------------------------------------------
//�I�u�W�F�N�g�̐���
//--------------------------------------------
CSelectMenu *CSelectMenu::Create(D3DXVECTOR3 pos, float m_fWidth, float fSpace, MENU_TYPE type)
{
	//�Z���N�g���j���[�̃|�C���^
	CSelectMenu *pMenuSelect;
	pMenuSelect = new CSelectMenu;
	pMenuSelect->m_MenuType = type;
	pMenuSelect->m_InitPos = pos;
	pMenuSelect->m_fWidth = m_fWidth;
	pMenuSelect->m_fHeight = m_fWidth;
	pMenuSelect->m_fSpace = fSpace;
	//�Z���N�g���j���[�̏�����
	pMenuSelect->Init();
	//�Z���N�g���j���[�̏���Ԃ�
	return pMenuSelect;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CSelectMenu::Init()
{
	switch (m_MenuType)
	{
	case MENU_TYPE_MODESELECT:
		m_nMaxMenu = 3;
		m_fInitYpos = 350.0f;

		InitSelectPolygon();
		break;

	case MENU_TYPE_RESULT:
		m_fInitYpos = 270.0f;
		m_nMaxMenu = 4;
		for (int nCnt = 0; nCnt < m_nMaxMenu; nCnt++)
		{//���j���[�|���S���̏�����
			m_apPolygon[nCnt] = NULL;
		}

		InitResultPolygon();
		break;
	case MENU_TYPE_PAUSE:
		m_nMaxMenu = 2;
		for (int nCnt = 0; nCnt < m_nMaxMenu; nCnt++)
		{//���j���[�|���S���̏�����
			m_apPolygon[nCnt] = NULL;
		}

		/* ���j���[�|���S���̐ݒ� */
		m_InitPos.y = MENU_INITPOS;

		for (int nCnt = 0; nCnt < m_nMaxMenu; nCnt++)
		{
			m_Pos[nCnt] = m_InitPos;
			m_Pos[nCnt].x = m_InitPos.x + m_fInitYpos;
			//�ʒu�����炷
			m_Pos[nCnt].x = m_Pos[nCnt].x + (m_fSpace * (nCnt - 2));


			if (m_apPolygon[nCnt] == NULL)
			{
				m_apPolygon[nCnt] = CScene2D::Create(D3DXVECTOR3(m_Pos[nCnt].x, m_Pos[nCnt].y, m_Pos[nCnt].z), "MODESELEXT_MENU");
				m_apPolygon[nCnt]->SetTex(D3DXVECTOR2(0.0f + (0.333f*nCnt), 0.0f), D3DXVECTOR2(0.333f + (0.333f*nCnt), 1.0f));
				m_apPolygon[nCnt]->SetWidthHeight(m_fWidth * MODESELECT_WIDTH, m_fHeight * MODESELECT_HEIGHT);
				m_apPolygon[nCnt]->SetbDraw(true);
			}
		}
		CSound *pSound = CManager::GetSound();		//	���̎擾

		//if (MenuSelect == SELECT_MENU_ONE)
		/*{
			pSound->SetVolume(CSound::SOUND_LABEL_1_PLAYER, 3.5f);
			pSound->PlaySound(CSound::SOUND_LABEL_1_PLAYER);
		}*/
		////else if (MenuSelect == SELECT_MENU_TWO)
		//{
		//	pSound->SetVolume(CSound::SOUND_LABEL_2_PLAYER, 3.5f);
		//	pSound->PlaySound(CSound::SOUND_LABEL_2_PLAYER);
		//}
		////else if (MenuSelect == SELECT_MENU_THREE)
		//{
		//	pSound->SetVolume(CSound::SOUND_LABEL_3_PLAYER, 3.5f);
		//	pSound->PlaySound(CSound::SOUND_LABEL_3_PLAYER);
		//}
		//else if (MenuSelect == SELECT_MENU_FOUR)
		//{
		//	pSound->SetVolume(CSound::SOUND_LABEL_4_PLAYER, 3.5f);
		//	pSound->PlaySound(CSound::SOUND_LABEL_4_PLAYER);
		//}
		break;
	}

	//�l�̏�����
	m_nSelect = 0;
	m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
	m_aModeSelectMenu[1].select = SELECTTYPE_NONE;
	m_aModeSelectMenu[2].select = SELECTTYPE_NONE;
	//�I�u�W�F�N�g��ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_MODESELECT);
	m_bResultFade = false;

	return S_OK;
}

//=============================================================================
// �Z���N�g���j���[�N���X �I������
//=============================================================================
void CSelectMenu::Uninit(void)
{
	for (int nCnt = 0; nCnt<MAX_SELECTMODE_MODESEL;nCnt++)
	{
		if (m_apPolygon_ModeSel[nCnt] != NULL)
		{
			m_apPolygon_ModeSel[nCnt]->Uninit();
			m_apPolygon_ModeSel[nCnt] = NULL;
		}
	}
	for (int nCnt = 0; nCnt<m_nMaxMenu; nCnt++)
	{
		if (m_apPolygon[nCnt] != NULL)
		{
			m_apPolygon[nCnt]->Uninit();
			m_apPolygon[nCnt] = NULL;
		}
	}
	for (int nCnt = 0; nCnt<MAX_SELECTMODE_RANKING; nCnt++)
	{
		if (m_apPolygon2D_Ranking[nCnt] != NULL)
		{
			m_apPolygon2D_Ranking[nCnt]->Uninit();
			m_apPolygon2D_Ranking[nCnt] = NULL;
		}
	}
	if (m_apPolygon3D_Ranking != NULL)
	{
		m_apPolygon3D_Ranking->Uninit();
		m_apPolygon3D_Ranking = NULL;
	}

	//������j��
	Release();
}

//=============================================================================
// �Z���N�g���j���[�N���X �X�V����
//=============================================================================
void CSelectMenu::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//�t�F�[�h���擾
	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();


	//�T�E���h�����擾
	CSound *pSound = CManager::GetSound(0);

	/* �����Ɖ��o */
	switch (m_MenuType)
	{
	case MENU_TYPE_MODESELECT:
		//���o
		ScrollMenu(SELECTMODETYPE_MODESEL_BAND_L, -0.005f);
		ScrollMenu(SELECTMODETYPE_MODESEL_BAND_R, 0.005f);

		SelectModeExplanation(m_nSelect);
		SelectAnimation(m_nSelect);

		SetSelectAnimation(POLYGONTYPE_BG, ANIMTYPE_X, 8, 4, 1, 15);
#ifdef _DEBUG
		if (CManager::GetRepeat() == true)
		{
			nCntFadeTime++;
			if (nCntFadeTime > 30)
			{
				m_SelectMode = SELECT_MENU_ONE;
				MenuDecide(SELECT_MENU_ONE);
			}
		}
#endif

		break;

	case MENU_TYPE_RESULT:
		/*�I�����̉��o*/
		if (m_bModeSelect == true && pFade->GetFade() == CFade::FADE_NONE)
		{
			SelectModeExplanation(m_nSelect);
		}
		if (m_bResultFade == false)
		{//�}�X�N�̃t�F�[�h���I������瓮������悤�ɂ���
			m_bResultFade = ResultMaskFade();
			return;
		}
		break;

	case MENU_TYPE_PAUSE:
		break;
	}
	//�ړ�����
	if (m_bModeSelect == true && pFade->GetFade() == CFade::FADE_NONE)
	{
		MoveMenu();
	}

#ifdef _DEBUG
	CDebugProc::Print("cn", "m_nSelect : ", m_nSelect);
#endif

}

//=============================================================================
// �Z���N�g���j���[�N���X �`�揈��
//=============================================================================
void CSelectMenu::Draw(void){}

//=============================================================================
// ���肵�����j���[�̏���
//=============================================================================
void CSelectMenu::MenuDecide(SELECT_MENU MenuSelect)
{
	//�t�F�[�h���擾
	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();
	CSound *pSound = CManager::GetSound();		//	���̎擾
	switch (m_MenuType)
	{
	case MENU_TYPE_MODESELECT:
		switch (MenuSelect)
		{
		case SELECT_MENU_ONE:
			CPlayerSelect::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), 150);
			Uninit();
			break;
		case SELECT_MENU_TWO:	// �N���W�b�g�p
			CCredit::Create();
			Uninit();
			break;
		case SELECT_MENU_THREE:
			CFade::SetFade(CManager::MODE_TITLE, pFade->FADE_OUT);
			break;
		case SELECT_MENU_FOUR:
			CFade::SetFade(CManager::MODE_TUTORIAL, pFade->FADE_OUT);
			break;
		}
		break;

	case MENU_TYPE_RESULT:
		switch (MenuSelect)
		{
		case SELECT_MENU_ONE:
			CFade::SetFade(CManager::MODE_GAME, pFade->FADE_OUT);
			break;
		case SELECT_MENU_TWO:
			CFade::SetFade(CManager::MODE_CHARASELECT, pFade->FADE_OUT);
			break;
		case SELECT_MENU_THREE:
			CFade::SetFade(CManager::MODE_STAGESELECT, pFade->FADE_OUT);
			break;
		case SELECT_MENU_FOUR:
			CFade::SetFade(CManager::MODE_TITLE, pFade->FADE_OUT);
			break;
		}
		break;
	case MENU_TYPE_PAUSE:

		switch (MenuSelect)
		{
		case SELECT_MENU_ONE:
			CFade::SetFade(CManager::MODE_GAME, pFade->FADE_OUT);
			break;
		case SELECT_MENU_TWO:
			CFade::SetFade(CManager::MODE_GAME, pFade->FADE_OUT);
			break;
		case SELECT_MENU_THREE:
			CFade::SetFade(CManager::MODE_GAME, pFade->FADE_OUT);
			break;
		case SELECT_MENU_FOUR:
			CFade::SetFade(CManager::MODE_GAME, pFade->FADE_OUT);
			break;
		}
		break;
	}
}
//=============================================================================
// ���[�h�I���̈ړ�����
//=============================================================================
void CSelectMenu::MoveMenu(void)
{
	CSound *pSound = CManager::GetSound();		//	���̎擾


	//�I������
	if (CCommand::GetCommand("RIGHT"))
	{
		pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT02);
		m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_NONE;
		if (m_nSelect < m_nMaxMenu - 1)
		{
			m_nSelect = (m_nSelect + 1) % m_nMaxMenu;
		}
		m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
	}
	else if (CCommand::GetCommand("LEFT"))
	{
		pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT02);
		m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_NONE;
		if (m_nSelect > 0)
		{
			m_nSelect = (m_nSelect + (m_nMaxMenu - 1)) % m_nMaxMenu;
		}
		m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
	}

	//�G���^�[�L�[
	if (CCommand::GetCommand("DECISION") == true)
	{
		pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT00);
		if (m_nSelect == 0)
		{
			m_SelectMode = SELECT_MENU_ONE;
			MenuDecide(SELECT_MENU_ONE);
			if (CManager::GetMode() == CManager::MODE_SELECT)
			{
				m_bModeSelect = false;
			}
		}
		else if (m_nSelect == 1)
		{
			m_SelectMode = SELECT_MENU_TWO;
			MenuDecide(SELECT_MENU_TWO);
		}
		else if (m_nSelect == 2)
		{
			m_SelectMode = SELECT_MENU_THREE;
			MenuDecide(SELECT_MENU_THREE);
			if (CManager::GetMode() == CManager::MODE_SELECT)
			{
				m_bModeSelect = false;
			}
		}
		else if (m_nSelect == 3)
		{
			m_SelectMode = SELECT_MENU_FOUR;
			MenuDecide(SELECT_MENU_FOUR);
			if (CManager::GetMode() == CManager::MODE_SELECT)
			{
				m_bModeSelect = false;
			}
		}
		if (CManager::GetMode() != CManager::MODE_SELECT)
		{
			m_bModeSelect = false;
		}
	}
}
//=============================================================================
// ���̕����X�N���[������
//=============================================================================
void CSelectMenu::ScrollMenu(SELECTMODETYPE_MODESEL type,float fScroolSpeed)
{
	m_nCntScrool++;
	m_apPolygon_ModeSel[type]->SetTex(D3DXVECTOR2(0.0f , 0.0f + (m_nCntScrool*fScroolSpeed)),D3DXVECTOR2(1.0f, 1.0f + (m_nCntScrool*fScroolSpeed)));
}

//=============================================================================
// �I�����Ɛ������̓�������
//=============================================================================
void CSelectMenu::SelectModeExplanation(int MenuSelect)
{
	if (m_MenuType == MENU_TYPE_MODESELECT)
	{
		switch (MenuSelect)
		{
		case 0:
			/* ���[�h�I���E�B���h */
			m_apPolygon[0]->SetPos(m_Pos[0], 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SelectMove(POLYGONTYPE_MENU, 0);	//�ړ����o����
			m_apPolygon[1]->SetPos(m_Pos[1], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[2]->SetPos(m_Pos[2], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

			/* ���[�h�����̃e�N�X�`�� */
			m_apPolygon_ModeSel[4]->SetAnimation(0, 0.333f, 1.0f);

			/* �A�j���[�V�����ʒu */
			m_apPolygon_ModeSel[5]->SetPos(D3DXVECTOR3(m_InitPos.x - 360.0f, MENU_INIT_POS, m_InitPos.z), 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SelectMove(POLYGONTYPE_BG, 5);		//�ړ����o����
			m_apPolygon_ModeSel[6]->SetPos(D3DXVECTOR3(m_InitPos.x, MENU_INIT_POS, m_InitPos.z), 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon_ModeSel[7]->SetPos(D3DXVECTOR3(m_InitPos.x + 350.0f, MENU_INIT_POS, m_InitPos.z), 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

			/* �I��UI */
			m_apPolygon_ModeSel[9]->SetPos(m_apPolygon[0]->GetPosition(), 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;

		case 1:
			/* ���[�h�I���E�B���h */
			m_apPolygon[0]->SetPos(m_Pos[0], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[1]->SetPos(m_Pos[1], 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SelectMove(POLYGONTYPE_MENU, 1);	//�ړ����o����
			m_apPolygon[2]->SetPos(m_Pos[2], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

			/* ���[�h�����̃e�N�X�`�� */
			m_apPolygon_ModeSel[4]->SetAnimation(1, 0.333f, 1.0f);

			/* �A�j���[�V�����ʒu */
			m_apPolygon_ModeSel[5]->SetPos(D3DXVECTOR3(m_InitPos.x - 360.0f, MENU_INIT_POS, m_InitPos.z), 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon_ModeSel[6]->SetPos(D3DXVECTOR3(m_InitPos.x, MENU_INIT_POS, m_InitPos.z), 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SelectMove(POLYGONTYPE_BG, 6);		//�ړ����o����
			m_apPolygon_ModeSel[7]->SetPos(D3DXVECTOR3(m_InitPos.x + 350.0f, MENU_INIT_POS, m_InitPos.z), 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

			/* �I��UI */
			m_apPolygon_ModeSel[9]->SetPos(m_apPolygon[1]->GetPosition(), 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

			break;

		case 2:
			/* ���[�h�I���E�B���h */
			m_apPolygon[0]->SetPos(m_Pos[0], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[1]->SetPos(m_Pos[1], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[2]->SetPos(m_Pos[2], 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SelectMove(POLYGONTYPE_MENU, 2);	//�ړ����o����

			/* ���[�h�����̃e�N�X�`�� */
			m_apPolygon_ModeSel[4]->SetAnimation(2, 0.333f, 1.0f);

			/* �A�j���[�V�����ʒu */
			m_apPolygon_ModeSel[5]->SetPos(D3DXVECTOR3(m_InitPos.x - 360.0f, MENU_INIT_POS, m_InitPos.z), 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon_ModeSel[6]->SetPos(D3DXVECTOR3(m_InitPos.x, MENU_INIT_POS, m_InitPos.z), 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon_ModeSel[7]->SetPos(D3DXVECTOR3(m_InitPos.x + 350.0f, MENU_INIT_POS, m_InitPos.z), 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SelectMove(POLYGONTYPE_BG,7);		//�ړ����o����

			/* �I��UI */
			m_apPolygon_ModeSel[9]->SetPos(m_apPolygon[2]->GetPosition(), 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

			break;
		}
	}
	else if (m_MenuType == MENU_TYPE_RESULT)
	{
		switch (MenuSelect)
		{
		case 0:
			/* ���[�h�I���E�B���h */
			m_apPolygon[0]->SetPos(m_Pos[0], 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SelectMove(POLYGONTYPE_MENU, 0);	//�ړ����o����
			m_apPolygon[1]->SetPos(m_Pos[1], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[2]->SetPos(m_Pos[2], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[3]->SetPos(m_Pos[3], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

			/* �I��UI */
			m_apPolygon2D_Ranking[0]->SetPos(m_apPolygon[0]->GetPosition(), 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;

		case 1:
			/* ���[�h�I���E�B���h */
			m_apPolygon[0]->SetPos(m_Pos[0], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[1]->SetPos(m_Pos[1], 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SelectMove(POLYGONTYPE_MENU, 1);	//�ړ����o����
			m_apPolygon[2]->SetPos(m_Pos[2], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[3]->SetPos(m_Pos[3], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			/* �I��UI */
			m_apPolygon2D_Ranking[0]->SetPos(m_apPolygon[1]->GetPosition(), 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;

		case 2:
			/* ���[�h�I���E�B���h */
			m_apPolygon[0]->SetPos(m_Pos[0], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[1]->SetPos(m_Pos[1], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[2]->SetPos(m_Pos[2], 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SelectMove(POLYGONTYPE_MENU, 2);	//�ړ����o����
			m_apPolygon[3]->SetPos(m_Pos[3], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			/* �I��UI */
			m_apPolygon2D_Ranking[0]->SetPos(m_apPolygon[2]->GetPosition(), 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;
		case 3:
			/* ���[�h�I���E�B���h */
			m_apPolygon[0]->SetPos(m_Pos[0], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[1]->SetPos(m_Pos[1], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[2]->SetPos(m_Pos[2], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[3]->SetPos(m_Pos[3], 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SelectMove(POLYGONTYPE_MENU, 3);	//�ړ����o����
			/* �I��UI */
			m_apPolygon2D_Ranking[0]->SetPos(m_apPolygon[3]->GetPosition(), 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;

		}
	}
}
//=============================================================================
// �Z���N�g���Ă郂�[�h�̃A�j���[�V����
//=============================================================================
void CSelectMenu::SelectAnimation(int MenuSelect)
{
	//�T�E���h�����擾
	CSound *pSound = CManager::GetSound(0);
	if (m_MenuType == MENU_TYPE_MODESELECT)
	{
		switch (MenuSelect)
		{
		case 0:
			m_nCntAnim++;
			if (m_nCntAnim > 20)
			{
				m_nPatturnAnim++;
				m_nCntAnim = 0;

				m_apPolygon_ModeSel[5]->SetTex(D3DXVECTOR2(0.0f + (0.5f*m_nPatturnAnim), 0.666f), D3DXVECTOR2(0.5f + (0.5f*m_nPatturnAnim), 0.999f));

				if (m_nPatturnAnim > 2)
				{
					m_nPatturnAnim = 0;
				}
			}
			break;

		case 1:
			m_nCntAnim++;
			if (m_nCntAnim > 20)
			{
				m_nPatturnAnim++;
				m_nCntAnim = 0;

				m_apPolygon_ModeSel[6]->SetTex(D3DXVECTOR2(0.0f + (0.5f*m_nPatturnAnim), 0.333f), D3DXVECTOR2(0.5f + (0.5f*m_nPatturnAnim), 0.666f));

				if (m_nPatturnAnim > 2)
				{
					m_nPatturnAnim = 0;
				}
			}
			break;

		case 2:
			m_nCntAnim++;
			if (m_nCntAnim > 20)
			{
				m_nPatturnAnim++;
				m_nCntAnim = 0;

				m_apPolygon_ModeSel[7]->SetTex(D3DXVECTOR2(0.0f + (0.5f*m_nPatturnAnim), 0.0f), D3DXVECTOR2(0.5f + (0.5f*m_nPatturnAnim), 0.333f));

				if (m_nPatturnAnim > 2)
				{
					m_nPatturnAnim = 0;
				}
			}
			break;
		}
		m_nCounter++;
		if (m_nCounter > 30 && m_nCounter < 33)
		{
			if (MenuSelect == 0)
			{
				pSound->SetVolume(CSound::SOUND_LABEL_PLAYSELECT, 4.5f);
				pSound->PlaySound(CSound::SOUND_LABEL_PLAYSELECT);
			}
			else if (MenuSelect == 1)
			{
				pSound->SetVolume(CSound::SOUND_LABEL_CREDIT, 4.5f);
				pSound->PlaySound(CSound::SOUND_LABEL_CREDIT);
			}
			else if (MenuSelect == 2)
			{
				pSound->SetVolume(CSound::SOUND_LABEL_TITLEBACK, 4.5f);
				pSound->PlaySound(CSound::SOUND_LABEL_TITLEBACK);
			}
		}
		if (CCommand::GetCommand("RIGHT") || CCommand::GetCommand("LEFT"))
		{
			m_nCounter = 0;
		}
	}
}

//=============================================================================
// �Z���N�g���Ă郂�[�h�̈ړ����o
//=============================================================================
void CSelectMenu::SelectMove(POLYGONTYPE type, int MenuNum)
{
	D3DXVECTOR3 SelectPos;
	switch (type)
	{
	case POLYGONTYPE_MENU:
		SelectPos = m_apPolygon[MenuNum]->GetPosition();

		if (m_fMoveMode >= 8.0f || m_fMoveMode <= -8.0f)
		{
			m_fChangeMode *= -1.0f;
		}

		//�ړ��ʂ����Z
		m_fMoveMode += m_fChangeMode;
		SelectPos.y += m_fMoveMode;

		m_apPolygon[MenuNum]->SetPos(SelectPos,0.0f,0.0f,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
		break;

	case POLYGONTYPE_BG:
		SelectPos = m_apPolygon_ModeSel[MenuNum]->GetPosition();

		if (m_fMoveMode >= 8.0f || m_fMoveMode <= -8.0f)
		{
			m_fChangeMode *= -1.0f;
		}

		//�ړ��ʂ����Z
		m_fMoveMode += m_fChangeMode;
		SelectPos.y += m_fMoveMode;

		m_apPolygon_ModeSel[MenuNum]->SetPos(SelectPos, 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	}

}
//=============================================================================
// �A�j���[�V��������
//=============================================================================
void CSelectMenu::SetSelectAnimation(POLYGONTYPE type, ANIMTYPE AnimType, int MenuNum, int MaxAnimPatternX, int MaxAnimPatternY, int AnimSpeed)
{
	m_nCntAnim2++;
	switch (type)
	{
	case POLYGONTYPE_MENU:
		if (AnimType == ANIMTYPE_X)
		{
			if (m_nCntAnim2 > AnimSpeed)
			{
				m_nPatturnAnim2++;
				m_nCntAnim2 = 0;
			}
			if (m_nPatturnAnim2 >= MaxAnimPatternX)
			{
				m_nPatturnAnim2 = 0;
			}
			m_apPolygon[MenuNum]->SetTex(D3DXVECTOR2(0.0f + ((1.0f/ MaxAnimPatternX)*m_nPatturnAnim2),0.0f + (1.0f / MaxAnimPatternY)),
										 D3DXVECTOR2(((1.0f / MaxAnimPatternX)*m_nPatturnAnim2) + ((1.0f / MaxAnimPatternX)*m_nPatturnAnim2),
													(1.0f / MaxAnimPatternY) + (1.0f / MaxAnimPatternY)));
		}
		else if (AnimType == ANIMTYPE_Y)
		{
			if (m_nCntAnim2 > AnimSpeed)
			{
				m_nPatturnAnim2++;
				m_nCntAnim2 = 0;
			}
			if (m_nPatturnAnim2 >= MaxAnimPatternY)
			{
				m_nPatturnAnim2 = 0;
			}

			m_apPolygon[MenuNum]->SetTex(D3DXVECTOR2(0.0f + (1.0f / MaxAnimPatternX), 0.0f + ((1.0f / MaxAnimPatternY) *m_nPatturnAnim2)),
										 D3DXVECTOR2((1.0f / MaxAnimPatternX)+ (1.0f / MaxAnimPatternX),
													((1.0f / MaxAnimPatternY)*m_nPatturnAnim2) + ((1.0f / MaxAnimPatternY)*m_nPatturnAnim2)));
		}
		break;

	case POLYGONTYPE_BG:
		if (AnimType == ANIMTYPE_X)
		{
			if (m_nCntAnim2 > AnimSpeed)
			{
				m_nPatturnAnim2++;
				m_nCntAnim2 = 0;
			}
			if (m_nPatturnAnim2 >= MaxAnimPatternX)
			{
				m_nPatturnAnim2 = 0;
			}

			m_apPolygon_ModeSel[MenuNum]->SetTex(D3DXVECTOR2(0.0f+(1.0f/MaxAnimPatternX)*m_nPatturnAnim2,
														0.0f + (1.0f / MaxAnimPatternY)),
										D3DXVECTOR2((1.0f / MaxAnimPatternX)+ ((1.0f / MaxAnimPatternX)*m_nPatturnAnim2),
													(1.0f / MaxAnimPatternY)+ (1.0f / MaxAnimPatternY)));
		}
		else if (AnimType == ANIMTYPE_Y)
		{
			if (m_nCntAnim2 > AnimSpeed)
			{
				m_nPatturnAnim2++;
				m_nCntAnim2 = 0;
			}
			if (m_nPatturnAnim2 >= MaxAnimPatternY)
			{
				m_nPatturnAnim2 = 0;
			}

			m_apPolygon_ModeSel[MenuNum]->SetTex(D3DXVECTOR2(0.0f + (1.0f / MaxAnimPatternX), 0.0f + ((1.0f / MaxAnimPatternY) *m_nPatturnAnim2)),
				D3DXVECTOR2((1.0f / MaxAnimPatternX) + (1.0f / MaxAnimPatternX),
				((1.0f / MaxAnimPatternY)*m_nPatturnAnim2) + ((1.0f / MaxAnimPatternY)*m_nPatturnAnim2)));
		}
		break;
	}
}
//=============================================================================
// �`���[�g���A���̃|���S���̏����ʒu
//=============================================================================
void CSelectMenu::InitSelectPolygon(void)
{
	/* ���j���[�|���S���̐ݒ� */
	m_InitPos.y = MENU_INITPOS;

	for (int nCnt = 0; nCnt < m_nMaxMenu; nCnt++)
	{//���j���[�|���S���̏�����
		m_apPolygon[nCnt] = NULL;
	}

	/* �w�i�ݒ� */
	//�w�i
	m_apPolygon_ModeSel[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, m_InitPos.z), "SELECTMODE_BG", 2);
	m_apPolygon_ModeSel[0]->SetWidthHeight(MENU_BG*6.0f, MENU_BG * 3.5f);

	//���[�h���сi���j
	m_apPolygon_ModeSel[1] = CScene2D::Create(D3DXVECTOR3(50.0f, SCREEN_HEIGHT / 2, m_InitPos.z), "SELECTMODE_UI", 2);
	m_apPolygon_ModeSel[1]->SetWidthHeight(MENU_BG*BAND_SIZE, MENU_BG * 3.5f);

	//���[�h���сi�E�j
	m_apPolygon_ModeSel[2] = CScene2D::Create(D3DXVECTOR3(1230.0f, SCREEN_HEIGHT / 2, m_InitPos.z), "SELECTMODE_UI", 2);
	m_apPolygon_ModeSel[2]->SetWidthHeight(MENU_BG*BAND_SIZE, MENU_BG * 3.5f);

	//�t���[��
	m_apPolygon_ModeSel[3] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 640.0f, m_InitPos.z), "FRAME", 2);
	m_apPolygon_ModeSel[3]->SetWidthHeight(SCREEN_WIDTH / 2 * 1.1f, MENU_BG * 0.7f);

	//������
	m_apPolygon_ModeSel[4] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 645.0f, m_InitPos.z), "SELECTMODE_EXPLANATION", 2);
	m_apPolygon_ModeSel[4]->SetWidthHeight(SCREEN_WIDTH / 2 * 1.0f, MENU_BG * 0.63f);
	m_apPolygon_ModeSel[4]->SetAnimation(0, 1.0f, 0.33f);

	//�A�j���[�V�����F�Q�[��
	m_apPolygon_ModeSel[5] = CScene2D::Create(D3DXVECTOR3(m_InitPos.x - 360.0f, MENU_INIT_POS, m_InitPos.z), "TITLEBACK_A");
	m_apPolygon_ModeSel[5]->SetWidthHeight(MENU_BG*1.5f, MENU_BG * 1.5f);
	m_apPolygon_ModeSel[5]->SetTex(D3DXVECTOR2(0.0f, 0.666f), D3DXVECTOR2(0.5f, 0.999f));

	//�A�j���[�V�����F�����ꗗ
	m_apPolygon_ModeSel[6] = CScene2D::Create(D3DXVECTOR3(m_InitPos.x, MENU_INIT_POS, m_InitPos.z), "TITLEBACK_A");
	m_apPolygon_ModeSel[6]->SetWidthHeight(MENU_BG*1.55f, MENU_BG * 1.55f);
	m_apPolygon_ModeSel[6]->SetTex(D3DXVECTOR2(0.0f, 0.333f), D3DXVECTOR2(0.5f, 0.666f));

	//�A�j���[�V�����F�^�C�g���ɖ߂�
	m_apPolygon_ModeSel[7] = CScene2D::Create(D3DXVECTOR3(m_InitPos.x + 350.0f, MENU_INIT_POS, m_InitPos.z), "TITLEBACK_A");
	m_apPolygon_ModeSel[7]->SetWidthHeight(MENU_BG*1.2f, MENU_BG * 1.2f);
	m_apPolygon_ModeSel[7]->SetAnimation(0, 0.5f, 0.333f);

	//UI_�X�e�B�b�N
	m_apPolygon_ModeSel[8] = CScene2D::Create(D3DXVECTOR3(m_InitPos.x, m_InitPos.y - 250.0f, m_InitPos.z), "UI_OPERATION1", 2);
	m_apPolygon_ModeSel[8]->SetWidthHeight(MENU_BG*0.7f, MENU_BG * 0.7f);
	m_apPolygon_ModeSel[8]->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.25f, 1.0f));

	//UI_�I��
	m_apPolygon_ModeSel[9] = CScene2D::Create(D3DXVECTOR3(m_InitPos.x, m_InitPos.y - 300.0f, m_InitPos.z), "UI_SELECT");
	m_apPolygon_ModeSel[9]->SetWidthHeight(m_fWidth*1.02f, m_fHeight * 1.05f);
	m_apPolygon_ModeSel[9]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));


	for (int nCnt = 0; nCnt < m_nMaxMenu; nCnt++)
	{
		m_Pos[nCnt] = m_InitPos;
		m_Pos[nCnt].x = m_InitPos.x + m_fInitYpos;
		//�ʒu�����炷
		m_Pos[nCnt].x = m_Pos[nCnt].x + (m_fSpace * (nCnt - 2));


		if (m_apPolygon[nCnt] == NULL)
		{
			m_apPolygon[nCnt] = CScene2D::Create(D3DXVECTOR3(m_Pos[nCnt].x, m_Pos[nCnt].y, m_Pos[nCnt].z), "MODESELEXT_MENU", 2);
			m_apPolygon[nCnt]->SetTex(D3DXVECTOR2(0.0f + (0.333f*nCnt), 0.0f), D3DXVECTOR2(0.333f + (0.333f*nCnt), 1.0f));
			m_apPolygon[nCnt]->SetWidthHeight(m_fWidth * MODESELECT_WIDTH, m_fHeight * MODESELECT_HEIGHT);
			m_apPolygon[nCnt]->SetbDraw(true);
		}
	}
}
//=============================================================================
// ���U���g�̃|���S���̏����ʒu
//=============================================================================
void CSelectMenu::InitResultPolygon(void)
{
	/* �}�X�N */
	if (m_apPolygon3D_Ranking == NULL)
	{
		m_apPolygon3D_Ranking = CScene3D::Create(D3DXVECTOR3(20.0f,0.0f,20.0f),"");
		m_apPolygon3D_Ranking->SetSize(100.0f, 100.0f);
		m_apPolygon3D_Ranking->SetRot(D3DXVECTOR3(D3DX_PI*0.5f, 0.0f, 0.0f));
		m_apPolygon3D_Ranking->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
	if (m_apPolygon2D_Ranking[0] == NULL)
	{
		//UI_�I��
		m_apPolygon2D_Ranking[0] = CScene2D::Create(D3DXVECTOR3(m_InitPos.x, m_InitPos.y - 300.0f, m_InitPos.z), "UI_SELECT",4);
		m_apPolygon2D_Ranking[0]->SetWidthHeight(m_fWidth * MODESELECT_WIDTH, 150.0f * MODESELECT_HEIGHT);
		m_apPolygon2D_Ranking[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
	/* ���j���[�|���S���̐ݒ� */
	for (int nCnt = 0; nCnt < m_nMaxMenu; nCnt++)
	{
		m_Pos[nCnt] = m_InitPos;
		m_Pos[nCnt].x = m_InitPos.x + m_fInitYpos;
		//�ʒu�����炷
		m_Pos[nCnt].x = m_Pos[nCnt].x + (m_fSpace * (nCnt - 2));


		if (m_apPolygon[nCnt] == NULL)
		{
			m_apPolygon[nCnt] = CScene2D::Create(D3DXVECTOR3(m_Pos[nCnt].x, m_Pos[nCnt].y, m_Pos[nCnt].z), "RNKINGSELECT_MENU");
			m_apPolygon[nCnt]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MAX_SELECTMENU)*nCnt), 0.0f), D3DXVECTOR2((1.0f / MAX_SELECTMENU) + ((1.0f / MAX_SELECTMENU)*nCnt), 1.0f));
			m_apPolygon[nCnt]->SetWidthHeight(m_fWidth * MODESELECT_WIDTH, 150.0f * MODESELECT_HEIGHT);
			m_apPolygon[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apPolygon[nCnt]->SetbDraw(true);
		}
	}
}
//=============================================================================
// ���U���g�̃}�X�N�̃t�F�[�h����
//=============================================================================
bool CSelectMenu::ResultMaskFade(void)
{
	bool bFade = false;

	if (m_apPolygon3D_Ranking != NULL)
	{
		m_fResultAlpha = m_apPolygon3D_Ranking->Getcol().a;
		if (m_fResultAlpha <= 0.7f)
		{//�}�X�N�̓����x��0.7��菬����
			m_fResultAlpha += 0.05f;
			m_apPolygon3D_Ranking->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_fResultAlpha));
		}
		else
		{
			m_apPolygon3D_Ranking->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f));
			bFade = true;
		}
	}
	return bFade;
}