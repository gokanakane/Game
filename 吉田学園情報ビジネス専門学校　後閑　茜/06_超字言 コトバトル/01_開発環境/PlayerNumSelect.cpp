//---------------------------------------------------------------------
// �v���C���[�l���I����ʏ��� [PlayerNumSelect.cpp]
// Author : Mikiya Meguro/Akane Gokan
//---------------------------------------------------------------------
#include "PlayerNumSelect.h"
#include "select.h"
#include "scene.h"
#include "scene2D.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "renderer.h"
#include "player.h"
#include "debugProc.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODESELECT_WIDTH		(1.5f)		//�|���S���̑傫��(��)
#define MODESELECT_HEIGHT		(1.5f)		//�|���S���̑傫��(�c)
#define MENU_WIDTH				(350.0f)	//�|���S���ƃ|���S���̊Ԃ̑傫��(��)
#define MENU_HEIGHT				(310.0f)	//�|���S���ƃ|���S���̊Ԃ̑傫��(�c)
#define MENU_INITPOS			(250.0f)	//���j���[�̏����ʒu
#define MENU_NUM_HEIGHT			(2)			//���j���[�̏c�i��
#define MENU_NUM_WIDTH			(2)			//���j���[�̉��i��
#define CAUTIONBG_WIDTH			(750.0f)	//�|���S���ƃ|���S���̊Ԃ̑傫��(��)
#define CAUTIONBG_HEIGHT		(450.0f)	//�|���S���ƃ|���S���̊Ԃ̑傫��(�c)
#define CAUTION_WIDTH			(450.0f)	//�|���S���ƃ|���S���̊Ԃ̑傫��(��)
#define CAUTION_HEIGHT			(150.0f)	//�|���S���ƃ|���S���̊Ԃ̑傫��(�c)
#define BAND_SIZE				(0.5f)		//�т̃T�C�Y
#define PLNUMMENU_BG			(150.0f)	//�|���S���̑傫��
#define NOSELECT_SIZE			(50.0f)		//�I�΂�Ă��Ȃ��Ƃ��̃|���S���̃T�C�Y

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9 CPlayerSelect::m_pTexture[MAX_PLAYER_SELECTMENU] = {};
LPDIRECT3DTEXTURE9 CPlayerSelect::m_pTextureBG = NULL;
CPlayerSelect::SELECTPLAYER CPlayerSelect::m_SelectMode = CPlayerSelect::SELECTPLAYER_NONE;
bool CPlayerSelect::m_bModeSelect = false;

//--------------------------------------------
//���[�h�Z���N�g�N���X �R���X�g���N�^
//--------------------------------------------
CPlayerSelect::CPlayerSelect(int nPriority) : CScene(7)
{
	//�l�̏�����
	m_nSelect = 0;
	m_TexMove = D3DXVECTOR3(0, 0, 0);
	m_ChoicePos[0] = D3DXVECTOR3(0, 0, 0);
	m_ChoicePos[1] = D3DXVECTOR3(0, 0, 0);
	m_aModeSelectMenu[0].select = SELECTTYPE_SELECT;
	m_aModeSelectMenu[1].select = SELECTTYPE_NONE;
	m_aModeSelectMenu[2].select = SELECTTYPE_NONE;
	m_bCaution = false;
	m_bCreate2D = false;
	m_bModeSelect = true;
	m_nSelectCaution = 1;
	m_SelectCaution[0].select = SELECTTYPE_NONE;
	m_SelectCaution[1].select = SELECTTYPE_SELECT;

	/* ���o�n�ϐ��̏����� */
	m_nCntScrool = 0;
	m_fChangeMode = 0.1f;
	m_fMoveMode = 0.0f;
	m_nCntAnim = 0;
	m_nPatturnAnim = 0;
	m_nCounter = 0;
}

//--------------------------------------------
//���[�h�Z���N�g�N���X �f�X�g���N�^
//--------------------------------------------
CPlayerSelect::~CPlayerSelect(){}

//--------------------------------------------
//�I�u�W�F�N�g�̐���
//--------------------------------------------
CPlayerSelect *CPlayerSelect::Create(D3DXVECTOR3 pos, float m_fWidth)
{
	//���[�h�Z���N�g�̃|�C���^
	CPlayerSelect *pModeSelect;
	pModeSelect = new CPlayerSelect;

	pModeSelect->m_InitPos = pos;
	pModeSelect->m_fWidth = m_fWidth;
	pModeSelect->m_fHeight = m_fWidth;
	//���[�h�Z���N�g�̏�����
	pModeSelect->Init();
	//���[�h�Z���N�g�̏���Ԃ�
	return pModeSelect;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayerSelect::Init(void)
{
	/* �e��|�C���^�̏����� */
	InitPointer();

	/* ���o�p�|�C���^�̏����ʒu�ݒ� */
	InitProductionPos();

	/* �I�����̏����ʒu�ݒ� */
	m_InitPos.y = MENU_INITPOS;

	for (int nCnt = 0; nCnt < MAX_PLAYER_SELECTMENU; nCnt++)
	{
		if (nCnt < 2)
		{
			//�|���S���̈ʒu������ɏ�����
			m_Pos[nCnt] = m_InitPos;
			m_Pos[nCnt].x = m_InitPos.x - (MENU_WIDTH / 2);
			//�ʒu�����炷
			m_Pos[nCnt].x = m_Pos[nCnt].x + (MENU_WIDTH * nCnt);
		}
		else if (nCnt > 1)
		{
			//�|���S���̈ʒu������ɏ�����
			m_Pos[nCnt] = m_InitPos;
			m_Pos[nCnt].x = m_InitPos.x - (MENU_WIDTH / 2);
			m_Pos[nCnt].y = m_InitPos.y + MENU_HEIGHT;
			//�ʒu�����炷
			m_Pos[nCnt].x = m_Pos[nCnt].x + (MENU_WIDTH * (nCnt - 2));
		}

		if (m_apPolygon[nCnt] == NULL)
		{
			m_apPolygon[nCnt] = CScene2D::Create(D3DXVECTOR3(m_Pos[nCnt].x, m_Pos[nCnt].y, m_Pos[nCnt].z), "PLAYERNUMSELECT_MENU");
			m_apPolygon[nCnt]->SetWidthHeight(m_fWidth * MODESELECT_WIDTH, m_fHeight * MODESELECT_HEIGHT);
			m_apPolygon[nCnt]->SetTex(D3DXVECTOR2(0.0f + (0.25f*nCnt), 0.0f), D3DXVECTOR2(0.25f + (0.25f*nCnt), 1.0f));
			m_apPolygon[nCnt]->SetbDraw(true);
		}
	}

	//�I�u�W�F�N�g��ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_MODESELECT);
	return S_OK;
}

//=============================================================================
// ���[�h�Z���N�g�N���X �I������
//=============================================================================
void CPlayerSelect::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_PLAYERNUMSEL_BG; nCnt++)
	{
		if (m_apPolygonBG[nCnt] != NULL)
		{
			m_apPolygonBG[nCnt]->Uninit();
			m_apPolygonBG[nCnt] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MAX_PLAYER_SELECTMENU; nCnt++)
	{
		if (m_apPolygon[nCnt] != NULL)
		{
			m_apPolygon[nCnt]->Uninit();
			m_apPolygon[nCnt] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MAX_CAUTIONMENU; nCnt++)
	{
		if (m_pSelect2D[nCnt] != NULL)
		{
			m_pSelect2D[nCnt]->Uninit();
			m_pSelect2D[nCnt] = NULL;
		}
	}
	if (m_pCaution2D != NULL)
	{
		m_pCaution2D->Uninit();
		m_pCaution2D = NULL;
	}
	if (m_pCaution2DBG != NULL)
	{
		m_pCaution2DBG->Uninit();
		m_pCaution2DBG = NULL;
	}

	//������j��
	Release();
}

//=============================================================================
// ���[�h�Z���N�g�N���X �X�V����
//=============================================================================
void CPlayerSelect::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//�t�F�[�h���擾
	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();
	//�T�E���h�����擾
	CSound *pSound = CManager::GetSound(0);

	//�\���ؑ�
	for (int nCnt = 0; nCnt < MAX_PLAYER_SELECTMENU; nCnt++)
	{
		m_apPolygon[nCnt]->SetbDraw(m_bModeSelect);
	}
	m_apPolygonBG[0]->SetbDraw(m_bModeSelect);

	//���[�h�Z���N�g��
	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		if (m_bModeSelect == false)
		{
			m_nCounter = 0;
		}
		if (m_bModeSelect == true)
		{
			//�I������
			if (CCommand::GetCommand("DOWN") && m_bCaution == false)
			{
				pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT02);
				m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_NONE;
				if (m_nSelect < 2)
				{
					m_nSelect = (m_nSelect + MAX_PLAYER_SELECTMENU / 2) % (MAX_PLAYER_SELECTMENU);
				}
				m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
			}
			else if (CCommand::GetCommand("UP") && m_bCaution == false)
			{
				pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT02);
				m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_NONE;
				if (m_nSelect > 1)
				{
					m_nSelect = m_nSelect - 2;
				}
				m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
			}
			else if (CCommand::GetCommand("RIGHT") && m_bCaution == false)
			{
				pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT02);
				m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_NONE;
				if (m_nSelect == 1)
				{
					m_nSelect = 1;
				}
				else if (m_nSelect == 3)
				{
					m_nSelect = 3;
				}
				else
				{
					m_nSelect = (m_nSelect + 1) % 4;
				}
				m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
			}
			else if (CCommand::GetCommand("LEFT") && m_bCaution == false)
			{
				pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT02);
				m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_NONE;
				if (m_nSelect == 0)
				{
					m_nSelect = 0;
				}
				else if (m_nSelect == 2)
				{
					m_nSelect = 2;
				}
				else
				{
					m_nSelect = (m_nSelect + 3) % 4;
				}
				m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
			}

			m_nCounter++;
			if (m_nCounter > 20&& m_nCounter < 22)
			{
				if (m_nSelect == 0)
				{
					pSound->SetVolume(CSound::SOUND_LABEL_1_PLAYER, 3.5f);
					pSound->PlaySound(CSound::SOUND_LABEL_1_PLAYER);
				}
				else if (m_nSelect == 1)
				{
					pSound->SetVolume(CSound::SOUND_LABEL_2_PLAYER, 3.5f);
					pSound->PlaySound(CSound::SOUND_LABEL_2_PLAYER);
				}
				else if (m_nSelect == 2)
				{
					pSound->SetVolume(CSound::SOUND_LABEL_3_PLAYER, 3.5f);
					pSound->PlaySound(CSound::SOUND_LABEL_3_PLAYER);
				}
				else if (m_nSelect == 3)
				{
					pSound->SetVolume(CSound::SOUND_LABEL_4_PLAYER, 3.5f);
					pSound->PlaySound(CSound::SOUND_LABEL_4_PLAYER);
				}
			}
			if (CCommand::GetCommand("DOWN") || CCommand::GetCommand("UP") || CCommand::GetCommand("RIGHT") || CCommand::GetCommand("LEFT"))
			{
				m_nCounter = 0;
			}

			//�G���^�[�L�[
			if (CCommand::GetCommand("DECISION") == true && m_bCaution == false)
			{
				pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT00);
				if (m_nSelect == 0)
				{
					m_SelectMode = SELECTPLAYER_1P;
					m_apPolygonBG[6]->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.25f, 1.0f));
				}
				else if (m_nSelect == 1)
				{
					m_SelectMode = SELECTPLAYER_2P;
					m_apPolygonBG[6]->SetTex(D3DXVECTOR2(0.25f, 0.0f), D3DXVECTOR2(0.5f, 1.0f));
				}
				else if (m_nSelect == 2)
				{
					m_SelectMode = SELECTPLAYER_3P;
					m_apPolygonBG[6]->SetTex(D3DXVECTOR2(0.5f, 0.0f), D3DXVECTOR2(0.75f, 1.0f));
				}
				else if (m_nSelect == 3)
				{
					m_SelectMode = SELECTPLAYER_4P;
					m_apPolygonBG[6]->SetTex(D3DXVECTOR2(0.75f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
				}
				//�x����\��
				m_bCaution = true;
			}

			//�ŏI�x��	2D���쐬���ꂽ��
			if (CCommand::GetCommand("DECISION") && m_bCreate2D == true)
			{
				pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT00);
				switch (m_SelectMode)
				{
				case SELECTPLAYER_1P:
					break;
				case SELECTPLAYER_2P:
					break;
				case SELECTPLAYER_3P:
					break;
				case SELECTPLAYER_4P:
					break;
				}
				//2D��j��
				Caution2DUninit();
				m_apPolygonBG[5]->SetbDraw(false);
				m_apPolygonBG[6]->SetbDraw(false);
				if (m_nSelectCaution == 0)
				{
					CFade::SetFade(CManager::MODE_TUTORIAL, pFade->FADE_OUT);
				}

				m_nSelectCaution = 1;
				m_SelectCaution[0].select = SELECTTYPE_NONE;
				m_SelectCaution[1].select = SELECTTYPE_SELECT;
				m_bCreate2D = false;
			}
			else if (pInput->GetTrigger(DIK_B) == true)
			{
				//2D��j��
				Caution2DUninit();

				m_nSelectCaution = 1;
				m_SelectCaution[0].select = SELECTTYPE_NONE;
				m_SelectCaution[1].select = SELECTTYPE_SELECT;
				m_bCreate2D = false;
			}

			//�x���\����
			if (m_bCaution == true)
			{
				m_apPolygonBG[5]->SetbDraw(true);
				m_apPolygonBG[6]->SetbDraw(true);

				if (m_bCreate2D == false)
				{
					//�x���𐶐�
					m_pCaution2DBG = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), "PLAYERNUMSEL_BG");
					m_pCaution2DBG->SetWidthHeight(CAUTIONBG_WIDTH, CAUTIONBG_HEIGHT);
					m_pCaution2DBG->SetbDraw(true);

					m_pCaution2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 100.0f, 0), "BLOCK", 4);
					m_pCaution2D->SetWidthHeight(CAUTION_WIDTH, CAUTION_HEIGHT);
					m_pCaution2D->BindTexture(CTexture::GetTexture("MENU_START"));
					m_pCaution2D->SetbDraw(true);

					//YES or NO�@�|���S������
					for (int nCnt = 0; nCnt < MAX_CAUTIONMENU; nCnt++)
					{
						//�|���S���̈ʒu������ɏ�����
						m_ChoicePos[nCnt] = m_InitPos;
						m_ChoicePos[nCnt].x = m_InitPos.x - (480 / 2);
						//�ʒu�����炷
						m_ChoicePos[nCnt].x = m_ChoicePos[nCnt].x + (500 * nCnt);
						m_ChoicePos[nCnt].y = 500.0f;
						if (m_pSelect2D[nCnt] == NULL)
						{	//����
							m_pSelect2D[nCnt] = CScene2D::Create(D3DXVECTOR3(m_ChoicePos[nCnt].x, m_ChoicePos[nCnt].y + 100.0f, m_ChoicePos[nCnt].z), "MENU_START");
							m_pSelect2D[nCnt]->SetWidthHeight(400, 200);
							if (nCnt == 0)
							{
								m_pSelect2D[nCnt]->BindTexture(CTexture::GetTexture("MENU_YES"));
							}
							if (nCnt == 1)
							{
								m_pSelect2D[nCnt]->BindTexture(CTexture::GetTexture("MENU_NO"));
							}
							m_pSelect2D[nCnt]->SetbDraw(true);
						}
					}
					//2D�|���S���𐶐�����
					m_bCreate2D = true;
				}
				else
				{
					//�F�ς�
					for (int nCnt = 0; nCnt < MAX_CAUTIONMENU; nCnt++)
					{
						if (m_SelectCaution[nCnt].select == SELECTTYPE_SELECT)
						{//�I�𒆂̐F
							m_SelectCaution[nCnt].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
							m_pSelect2D[nCnt]->SetCol(m_SelectCaution[nCnt].col);
						}
						else
						{//���I���̐F
							m_SelectCaution[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
							m_pSelect2D[nCnt]->SetCol(m_SelectCaution[nCnt].col);
						}
					}
				}

				if (CCommand::GetCommand("RIGHT") && m_bCaution == true)
				{
					pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT02);
					m_SelectCaution[m_nSelectCaution].select = SELECTTYPE_NONE;
					//�E�[�Ŏ~�܂�
					if (m_nSelectCaution < 1)
					{
						m_nSelectCaution = (m_nSelectCaution + 1) % MAX_CAUTIONMENU;
					}
					m_SelectCaution[m_nSelectCaution].select = SELECTTYPE_SELECT;
				}
				else if (CCommand::GetCommand("LEFT") && m_bCaution == true)
				{
					pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT02);
					m_SelectCaution[m_nSelectCaution].select = SELECTTYPE_NONE;
					//���[�Ŏ~�܂�
					if (m_nSelectCaution > 0)
					{
						m_nSelectCaution = (m_nSelectCaution + 1) % MAX_CAUTIONMENU;
					}
					m_SelectCaution[m_nSelectCaution].select = SELECTTYPE_SELECT;
				}
			}

			//���[�h�I���ɖ߂�
			if (CCommand::GetCommand("DELETE") == true && m_bCaution == false)
			{
				Uninit();
				pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT01);
				CManager::SetMode(CManager::MODE_SELECT);
				return;
			}
		}
	}
	/* ���[�h�^�C�g���т̃X�N���[������ */
	ScrollMenu(PLNUMSELECTBGTYPE_BAND_L, -0.005f);
	ScrollMenu(PLNUMSELECTBGTYPE_BAND_R, 0.005f);

	if (m_bCaution == false)
	{//�x�����o�ĂȂ��ꍇ�̑I�����̐ݒ�
		SetPlayerSelNumMenuPos(m_nSelect);
	}
	else
	{//�x�����o�Ă鎞�̑I�����̐ݒ�
		SetPlayerSelNumMenuPos(m_nSelectCaution);
	}

	/* ������@UI�̃A�j���[�V���� */
	SetSelectAnimation(PLNUMSELECTBGTYPE_BG, ANIMTYPE_X, 3, 4, 1, 15);


#ifdef _DEBUG
	CDebugProc::Print("cn", "m_nSelect : ", m_nSelect);
#endif

#ifdef _DEBUG
	if (CManager::GetRepeat() == true)
	{
		nCntFadeTime++;
		if (nCntFadeTime > 30)
		{
			m_SelectMode = SELECTPLAYER_4P;
			pFade->SetFade(pManager->MODE_TUTORIAL, pFade->FADE_OUT);
		}
	}
#endif

}

//=============================================================================
// ���[�h�Z���N�g�N���X �`�揈��
//=============================================================================
void CPlayerSelect::Draw(void){}

//=============================================================================
// �e�N�X�`���̔j������
//=============================================================================
void CPlayerSelect::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_PLAYER_SELECTMENU; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}

	if (m_pTextureBG != NULL)
	{
		m_pTextureBG->Release();
		m_pTextureBG = NULL;
	}
}
//=============================================================================
// �x��2D�̔j��
//=============================================================================
void CPlayerSelect::Caution2DUninit(void)
{
	//2D��j��
	if (m_pCaution2D != NULL)
	{
		m_pCaution2D->Uninit();
		m_pCaution2D = NULL;
		m_bCaution = false;
	}
	if (m_pCaution2DBG != NULL)
	{
		m_pCaution2DBG->Uninit();
		m_pCaution2DBG = NULL;
		m_bCaution = false;
	}
	for (int nCnt = 0; nCnt < MAX_CAUTIONMENU; nCnt++)
	{
		if (m_pSelect2D[nCnt] != NULL)
		{
			m_pSelect2D[nCnt]->Uninit();
			m_pSelect2D[nCnt] = NULL;
			m_pSelect2D[nCnt] = false;
		}
	}
}
//=============================================================================
// �e��|�C���^�̏�����
//=============================================================================
HRESULT CPlayerSelect::InitPointer(void)
{
	for (int nCnt = 0; nCnt < MAX_PLAYER_SELECTMENU; nCnt++)
	{/* �l���I���̃|�C���^ */
		if (m_apPolygon[nCnt] != NULL)
		{
			m_apPolygon[nCnt] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < MAX_CAUTIONMENU; nCnt++)
	{/* �x���̑I�����̃|�C���^ */
		if (m_pSelect2D[nCnt] != NULL)
		{
			m_pSelect2D[nCnt] = NULL;	//�x���̑I�����̃|�C���^�̏�����
		}
	}
	for (int nCnt = 0; nCnt < MAX_PLAYERNUMSEL_BG; nCnt++)
	{/* ���o�p�w�i�̃|�C���^ */
		if (m_apPolygonBG[nCnt] != NULL)
		{
			m_apPolygonBG[nCnt] = NULL;
		}
	}
	m_pCaution2D = NULL;	//�x���莚�̃|�C���^�̏�����
	m_pCaution2DBG = NULL;	//�x���w�i�̃|�C���^������

	return S_OK;
}
//=============================================================================
// ���o�̏����ʒu�̌���
//=============================================================================
void CPlayerSelect::InitProductionPos(void)
{
	//BG
	m_apPolygonBG[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, m_InitPos.z), "SELECTMODE_BG");
	m_apPolygonBG[0]->SetWidthHeight(PLNUMMENU_BG*6.0f, PLNUMMENU_BG * 3.5f);

	//���[�h���сi���j
	m_apPolygonBG[1] = CScene2D::Create(D3DXVECTOR3(50.0f, SCREEN_HEIGHT / 2, m_InitPos.z), "PLAYERNUMSEL_BAND");
	m_apPolygonBG[1]->SetWidthHeight(PLNUMMENU_BG*BAND_SIZE, PLNUMMENU_BG * 3.5f);

	//���[�h���сi�E�j
	m_apPolygonBG[2] = CScene2D::Create(D3DXVECTOR3(1230.0f, SCREEN_HEIGHT / 2, m_InitPos.z), "PLAYERNUMSEL_BAND");
	m_apPolygonBG[2]->SetWidthHeight(PLNUMMENU_BG*BAND_SIZE, PLNUMMENU_BG * 3.5f);

	//UI_�X�e�B�b�N
	m_apPolygonBG[3] = CScene2D::Create(D3DXVECTOR3(m_InitPos.x, m_InitPos.y - 300.0f, m_InitPos.z), "UI_OPERATION1", 4);
	m_apPolygonBG[3]->SetWidthHeight(PLNUMMENU_BG*0.5f, PLNUMMENU_BG * 0.5f);
	m_apPolygonBG[3]->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.25f, 1.0f));

	//UI_�I��
	m_apPolygonBG[4] = CScene2D::Create(D3DXVECTOR3(m_InitPos.x, m_InitPos.y - 300.0f, m_InitPos.z), "UI_SELECT", 4);
	m_apPolygonBG[4]->SetWidthHeight(m_fWidth*1.5f, m_fHeight * 1.5f);
	m_apPolygonBG[4]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	//�}�X�N
	m_apPolygonBG[5] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, m_InitPos.z), " ");
	m_apPolygonBG[5]->SetWidthHeight(PLNUMMENU_BG*6.5f, PLNUMMENU_BG * 3.5f);
	m_apPolygonBG[5]->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f));
	m_apPolygonBG[5]->SetbDraw(false);

	//�I�������l��Icon
	m_apPolygonBG[6] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 30.0f, m_InitPos.z), "PLAYERNUMSELECT_MENU", 4);
	m_apPolygonBG[6]->SetWidthHeight(m_fWidth * 1.8f, m_fHeight * 1.8f);
	m_apPolygonBG[6]->SetTex(D3DXVECTOR2(0.25f, 0.0f), D3DXVECTOR2(0.5f, 1.0f));
	m_apPolygonBG[6]->SetbDraw(false);

}
//=============================================================================
// ���̕����X�N���[������
//=============================================================================
void CPlayerSelect::ScrollMenu(PLNUMSELECTBGTYPE type, float fScroolSpeed)
{
	m_nCntScrool++;

	if (m_apPolygonBG[type] != NULL)
	{
		m_apPolygonBG[type]->SetTex(D3DXVECTOR2(0.0f, 0.0f + (m_nCntScrool*fScroolSpeed)), D3DXVECTOR2(1.0f, 1.0f + (m_nCntScrool*fScroolSpeed)));
	}
}

//=============================================================================
// �Z���N�g���Ă郂�[�h�̈ړ����o
//=============================================================================
void CPlayerSelect::PlayerSelectMove(PLNUMSELECTBGTYPE type, int MenuNum)
{
	D3DXVECTOR3 SelectPos;
	switch (type)
	{
	case PLNUMSELECTBGTYPE_MENU:	//�I�����̃|���S��
		SelectPos = m_apPolygon[MenuNum]->GetPosition();

		if (m_fMoveMode >= 1.5f || m_fMoveMode <= -1.5f)
		{
			m_fChangeMode *= -1.0f;
		}

		//�ړ��ʂ����Z
		m_fMoveMode += m_fChangeMode;
		SelectPos.y += m_fMoveMode;

		m_apPolygon[MenuNum]->SetPos(SelectPos, 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;

	case PLNUMSELECTBGTYPE_BG:		//���o�p�̃|���S��
		SelectPos = m_apPolygonBG[MenuNum]->GetPosition();

		if (m_fMoveMode >= 1.5f || m_fMoveMode <= -1.5f)
		{
			m_fChangeMode *= -1.0f;
		}

		//�ړ��ʂ����Z
		m_fMoveMode += m_fChangeMode;
		SelectPos.y += m_fMoveMode;

		m_apPolygonBG[MenuNum]->SetPos(SelectPos, 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	}
}
//=============================================================================
// �Z���N�g���Ă�A�C�R���Ƃ���ȊO�̃A�C�R���̏�Ԃ̈ʒu�ݒ�
//=============================================================================
void CPlayerSelect::SetPlayerSelNumMenuPos(int MenuNum)
{
	if (m_bCaution == false)
	{//�x�����o�Ă��Ȃ���
		m_apPolygonBG[4]->SetWidthHeight(m_fWidth*1.5f, m_fHeight * 1.5f);
		m_apPolygonBG[3]->SetPos(D3DXVECTOR3(m_InitPos.x, m_InitPos.y-200.0f, m_InitPos.z), 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apPolygonBG[3]->SetWidthHeight(PLNUMMENU_BG*0.5f, PLNUMMENU_BG * 0.5f);
		m_apPolygonBG[3]->BindTexture("UI_OPERATION2");
		switch (MenuNum)
		{//�l���I��
		case 0:	//��l
			m_apPolygon[0]->SetPos(m_Pos[0], 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apPolygon[1]->SetPos(m_Pos[1], 0.0f, -NOSELECT_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[2]->SetPos(m_Pos[2], 0.0f, -NOSELECT_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[3]->SetPos(m_Pos[3], 0.0f, -NOSELECT_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

			/* �J�[�\�� */
			m_apPolygonBG[4]->SetPos(m_apPolygon[0]->GetPosition(), 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;

		case 1://��l
			m_apPolygon[0]->SetPos(m_Pos[0], 0.0f, -NOSELECT_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[1]->SetPos(m_Pos[1], 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apPolygon[2]->SetPos(m_Pos[2], 0.0f, -NOSELECT_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[3]->SetPos(m_Pos[3], 0.0f, -NOSELECT_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

			/* �J�[�\�� */
			m_apPolygonBG[4]->SetPos(m_apPolygon[1]->GetPosition(), 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;

		case 2://�O�l
			m_apPolygon[0]->SetPos(m_Pos[0], 0.0f, -NOSELECT_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[1]->SetPos(m_Pos[1], 0.0f, -NOSELECT_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[2]->SetPos(m_Pos[2], 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apPolygon[3]->SetPos(m_Pos[3], 0.0f, -NOSELECT_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

			/* �J�[�\�� */
			m_apPolygonBG[4]->SetPos(m_apPolygon[2]->GetPosition(), 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;

		case 3://�l�l
			m_apPolygon[0]->SetPos(m_Pos[0], 0.0f, -NOSELECT_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[1]->SetPos(m_Pos[1], 0.0f, -NOSELECT_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[2]->SetPos(m_Pos[2], 0.0f, -NOSELECT_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[3]->SetPos(m_Pos[3], 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			/* �J�[�\�� */
			m_apPolygonBG[4]->SetPos(m_apPolygon[3]->GetPosition(), 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;
		}
		PlayerSelectMove(PLNUMSELECTBGTYPE_MENU, m_nSelect);
	}
	else
	{//�x���E�B���h
		m_apPolygonBG[4]->SetWidthHeight(200.0f, 120.0f);
		m_apPolygonBG[3]->SetPos(D3DXVECTOR3(m_InitPos.x, m_InitPos.y+350.0f, m_InitPos.z), 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apPolygonBG[3]->SetWidthHeight(PLNUMMENU_BG*0.8f, PLNUMMENU_BG * 0.8f);
		m_apPolygonBG[3]->BindTexture("UI_OPERATION1");

		switch (MenuNum)
		{
		case 0:	//YES
			m_pSelect2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pSelect2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

			/* �J�[�\�� */
			m_apPolygonBG[4]->SetPos(m_pSelect2D[0]->GetPosition(), 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;

		case 1:	//NO
			m_pSelect2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_pSelect2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			/* �J�[�\�� */
			m_apPolygonBG[4]->SetPos(m_pSelect2D[1]->GetPosition(), 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;
		}
	}
}

//=============================================================================
// �A�j���[�V��������
//=============================================================================
void CPlayerSelect::SetSelectAnimation(PLNUMSELECTBGTYPE type, ANIMTYPE AnimType, int MenuNum, int MaxAnimPatternX, int MaxAnimPatternY, int AnimSpeed)
{
	/*�@1�i�݂̂̃A�j���[�V�����ɑΉ����@*/

	m_nCntAnim++;
	switch (type)
	{
	case PLNUMSELECTBGTYPE_MENU:		//�I����
		if (AnimType == ANIMTYPE_X)
		{//������
			if (m_nCntAnim > AnimSpeed)
			{
				m_nPatturnAnim++;
				m_nCntAnim = 0;
			}
			if (m_nPatturnAnim >= MaxAnimPatternX)
			{
				m_nPatturnAnim = 0;
			}
			m_apPolygon[MenuNum]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MaxAnimPatternX)*m_nPatturnAnim), 0.0f + (1.0f / MaxAnimPatternY)),
				D3DXVECTOR2(((1.0f / MaxAnimPatternX)*m_nPatturnAnim) + ((1.0f / MaxAnimPatternX)*m_nPatturnAnim),
				(1.0f / MaxAnimPatternY) + (1.0f / MaxAnimPatternY)));
		}
		else if (AnimType == ANIMTYPE_Y)
		{//�c����
			if (m_nCntAnim > AnimSpeed)
			{
				m_nPatturnAnim++;
				m_nCntAnim = 0;
			}
			if (m_nPatturnAnim >= MaxAnimPatternY)
			{
				m_nPatturnAnim = 0;
			}

			m_apPolygon[MenuNum]->SetTex(D3DXVECTOR2(0.0f + (1.0f / MaxAnimPatternX), 0.0f + ((1.0f / MaxAnimPatternY) *m_nPatturnAnim)),
				D3DXVECTOR2((1.0f / MaxAnimPatternX) + (1.0f / MaxAnimPatternX),
				((1.0f / MaxAnimPatternY)*m_nPatturnAnim) + ((1.0f / MaxAnimPatternY)*m_nPatturnAnim)));
		}
		break;

	case PLNUMSELECTBGTYPE_BG:		//���o�p�|���S��
		if (AnimType == ANIMTYPE_X)
		{//������
			if (m_nCntAnim > AnimSpeed)
			{
				m_nPatturnAnim++;
				m_nCntAnim = 0;
			}
			if (m_nPatturnAnim >= MaxAnimPatternX)
			{
				m_nPatturnAnim = 0;
			}

			m_apPolygonBG[MenuNum]->SetTex(D3DXVECTOR2(0.0f + (1.0f / MaxAnimPatternX)*m_nPatturnAnim,
				0.0f + (1.0f / MaxAnimPatternY)),
				D3DXVECTOR2((1.0f / MaxAnimPatternX) + ((1.0f / MaxAnimPatternX)*m_nPatturnAnim),
				(1.0f / MaxAnimPatternY) + (1.0f / MaxAnimPatternY)));
		}
		else if (AnimType == ANIMTYPE_Y)
		{//�c����
			if (m_nCntAnim > AnimSpeed)
			{
				m_nPatturnAnim++;
				m_nCntAnim = 0;
			}
			if (m_nPatturnAnim >= MaxAnimPatternY)
			{
				m_nPatturnAnim = 0;
			}

			m_apPolygonBG[MenuNum]->SetTex(D3DXVECTOR2(0.0f + (1.0f / MaxAnimPatternX), 0.0f + ((1.0f / MaxAnimPatternY) *m_nPatturnAnim)),
				D3DXVECTOR2((1.0f / MaxAnimPatternX) + (1.0f / MaxAnimPatternX),
				((1.0f / MaxAnimPatternY)*m_nPatturnAnim) + ((1.0f / MaxAnimPatternY)*m_nPatturnAnim)));
		}
		break;
	}

}