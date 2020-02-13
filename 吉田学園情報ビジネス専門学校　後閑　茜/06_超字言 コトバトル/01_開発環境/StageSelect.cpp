//=============================================================================
//
// �X�e�[�W�Z���N�g���� [StageSelect.cpp]
// Author : �ڍ� ������/��� ��
//
//=============================================================================
#include "StageSelect.h"
#include "manager.h"
#include "light.h"
#include "CameraManager.h"
#include "camera.h"
#include "scene3D.h"
#include "game.h"
#include "debugProc.h"
#include "scene.h"
#include "fade.h"
#include "input.h"
#include "InputKeyboard.h"
#include "SetObject.h"
#include "object.h"
#include "meshField.h"
#include "wall.h"
#include <time.h>

//============================================================================
//	�}�N����`
//============================================================================
#define SIZE_X (SCREEN_WIDTH/2)
#define SIZE_Y (SCREEN_HEIGHT/2)
#define DEFAULT_SIZE (150.0f)														//�|���S���T�C�Y�̊�{�̑傫��
#define DEFAULT_POS (D3DXVECTOR3(SIZE_X,SIZE_Y,0.0f))								//�������ʒu
#define DEFAULT_ROT (D3DXVECTOR3(0.0f,0.0f,0.0f))									//��������]
#define DEFAULT_COL_WHITE (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))							//�������F_��
#define STAGESELCHOICE_POS	(D3DXVECTOR3(380.0f,130.0f,0.0f))						//�I�����|���S���̈ʒu
#define STAGESELCHOICE_INTERVAL (480.0f)											//�I�����|���S�����m�̊Ԋu
#define STAGESEL_DIFF (0.3f)														//�ړ��̕ω���
#define MACHINE_STAGE_MACHINE	("data\\TEXT\\�@�B�X�e�[�W\\Machine_Stage_0.txt")	//�@�B�X�e�[�W
#define MACHINE_STAGE_WEATHER	("data\\TEXT\\�V��X�e�[�W\\Machine_Stage_0.txt")	//�V��X�e�[�W
//#define MACHINE_STAGE_MACHINE	("data\\TEXT\\�@�B�X�e�[�W\\TEST.txt")	//�@�B�X�e�[�W
//#define MACHINE_STAGE_WEATHER	("data\\TEXT\\�@�B�X�e�[�W\\TEST.txt")	//�V��X�e�[�W

//============================================================================
//�ÓI�����o�ϐ��錾
//============================================================================
CScene2D *CStageSelect::m_apScene2D[MAX_STAGESELECT_TEX] = {};
CScene2D *CStageSelect::m_apSelect2D[MAX_STAGESELECT] = {};
CScene2D *CStageSelect::m_pMask2D = NULL;
CMeshField *CStageSelect::m_pMeshField = NULL;
CWall *CStageSelect::m_pWall[4] = {};
int	CStageSelect::m_nSelect = 0;
//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CStageSelect::CStageSelect()
{
	m_nCntScrool = 0;
	m_type = SELECTTYPE_SELECT_MACHINE;
	m_typeOld = SELECTTYPE_SELECT_MACHINE;

	m_bLoad = false;
	m_CameraRot = DEFAULT_ROT;
	m_CameraPosV = DEFAULT_POS;
	m_CameraPosR = DEFAULT_POS;
	m_MaskFade = MASKFADE_NONE;
	m_fMaskAlpha = 0.05f;
	m_pObj = NULL;
	m_nCntAnim = 0;
	m_nPatturnAnim = 0;
	m_nSelect = 0;
	for (int nCnt = 0; nCnt < MAX_STAGE; nCnt++)
	{
		m_SelectPos[nCnt] = DEFAULT_POS;
		m_IconCol[nCnt] = DEFAULT_COL_WHITE;
		m_fWidth[nCnt] = 0.0f;
		m_fHeight[nCnt] = 0.0f;
	}
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CStageSelect::~CStageSelect()
{

}

//=============================================================================
// �X�e�[�W�Z���N�g�̏���������
//=============================================================================
void CStageSelect::Init(void)
{
	/* �|�C���^�̏��������� */
	InitPointer();

	/*2D�|���S���̏����ݒ�*/
	InitPolygon();

	//�J�����̐ݒ�
	CCameraManager *pCameraManager = CManager::GetCameraManager();
	pCameraManager->CreateCamera("STAGESELECT_CAMERA", CCamera::TYPE_SPECTOR, D3DXVECTOR3(20.0f, 1500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1000.0f);
	pCameraManager->SetCameraViewPort("STAGESELECT_CAMERA", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	CCamera *pCamera = pCameraManager->GetCamera("STAGESELECT_CAMERA");
	if (pCamera != NULL)
	{
		pCamera->SetPosR(D3DXVECTOR3(20.0f, 40.0f, 0.0f));
	}

	//�ǂݍ��ރe�L�X�g�f�[�^��o�^
	m_pcStageSelect[0] = MACHINE_STAGE_MACHINE;
	m_pcStageSelect[1] = MACHINE_STAGE_WEATHER;
}

//=============================================================================
// �X�e�[�W�Z���N�g�̏I������
//=============================================================================
void CStageSelect::Uninit(void)
{
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Uninit();
		m_pMeshField = NULL;
	}
	for (int nCnt = 0; nCnt< 4; nCnt++)
	{
		if (m_pWall[nCnt] != NULL)
		{
			m_pWall[nCnt]->Uninit();
			m_pWall[nCnt] = NULL;
		}
	}
	//�S�Ă̏I������
	CScene::ReleseAll();
}

//=============================================================================
// �X�e�[�W�Z���N�g�̍X�V����
//=============================================================================
void CStageSelect::Update(void)
{
	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();
	CCameraManager *pCameraManager = CManager::GetCameraManager();
	CCamera *pCamera = pCameraManager->GetCamera("STAGESELECT_CAMERA");
	CSound *pSound = CManager::GetSound();		//	���̎擾

	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	if (pFade->GetFade() == CFade::FADE_NONE)
	{//�t�F�[�h���ĂȂ��Ƃ��̂ݏ���
		/* �I������ */
		if (CCommand::GetCommand("RIGHT"))
		{//�E
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT02);

			//�ړ��������ɐ��l���ς��Ȃ��悤�ɂ���
				//pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT);
			m_nSelect = (m_nSelect + 1) % MAX_STAGESELECT;
		}
		else if (CCommand::GetCommand("LEFT"))
		{//��
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT02);

			//�ړ��������ɐ��l���ς��Ȃ��悤�ɂ���
				//pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT);
				m_nSelect = (m_nSelect + (MAX_STAGESELECT - 1)) % MAX_STAGESELECT;
		}


		//�^�C�v��ݒ�AEnter��������J�ڏ���
		m_type = (SELECTTYPE)m_nSelect;
		Selecttype(m_type, pFade, pManager);

		if (pCamera != NULL)
		{//�J�����̉�]
			m_CameraRot.y = pCamera->GetRotation().y;
			m_CameraPosV = pCamera->GetPosV();
			m_CameraPosR = pCamera->GetPosR();
			m_CameraRot.y += 0.001f;
			m_CameraPosV.x = m_CameraPosR.x + sinf(m_CameraRot.y - D3DX_PI) * pCamera->GetLength();
			m_CameraPosV.z = m_CameraPosR.z + cosf(m_CameraRot.y - D3DX_PI) * pCamera->GetLength();

			pCamera->SetRotation(D3DXVECTOR3(0.0f, m_CameraRot.y, 0.0f));
			pCamera->SetPosV(m_CameraPosV);

		}
		if (CCommand::GetCommand("DELETE") == true)
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT01);

			pFade->SetFade(pManager->MODE_CHARASELECT, pFade->FADE_OUT);
		}
		/* �}�X�N�̃t�F�[�h���� */
		MaskFade();
	}

	//�I��ԍ�����ԕϐ��ɔ��f���A��Ԃɂ��킹�ď������s��
	ProductionIcon(m_type);

	/* �т̃e�N�X�`���X�N���[�� */
	ScrollMenu(STAGESELECTTYPE_BAND_R, 0.005f);
	ScrollMenu(STAGESELECTTYPE_BAND_L, -0.005f);

	/* �A�j���[�V���� */
	SetSelectAnimation(STAGESELECTTYPE_UI_OPERATION,0,4,1,15);

#ifdef _DEBUG
	//CDebugProc::Print("c", "�X�e�[�W�Z���N�g");
	//CDebugProc::Print("cn", "m_nSelect : ", m_nSelect);
	//CDebugProc::Print("cf", "�J����Rot : ", m_CameraRot.y);

	CDebugProc::Print("c", "�^�C�g��");
	if (CManager::GetRepeat() == true)
	{
		nCntFadeTime++;
		if (nCntFadeTime > 120)
		{
			m_nSelect = 1;
			pFade->SetFade(pManager->MODE_GAME, pFade->FADE_OUT);
		}
	}
#endif
}

//=============================================================================
// �X�e�[�W�Z���N�g�̕`�揈��
//=============================================================================
void CStageSelect::Draw(void)
{

}
//=============================================================================
// �|���S���̏����ݒ�
//=============================================================================
void CStageSelect::InitPolygon(void)
{
	D3DXVECTOR3 Replacement = DEFAULT_POS;

	for (int nCnt = 0; nCnt < MAX_STAGESELECT; nCnt++)
	{
		/* �����ƍ��W�ƃe�N�X�`�� */
		m_apSelect2D[nCnt] = CScene2D::Create(D3DXVECTOR3(STAGESELCHOICE_POS.x + (STAGESELCHOICE_INTERVAL*nCnt),
			STAGESELCHOICE_POS.y,
			STAGESELCHOICE_POS.z), "STAGESEL_ICON");
		m_apSelect2D[nCnt]->SetWidthHeight(DEFAULT_SIZE*1.8f, DEFAULT_SIZE*1.2f);
		m_apSelect2D[nCnt]->SetTex(D3DXVECTOR2(0.0f+(1.0f/ MAX_STAGESELECT)*nCnt, 0.0f), D3DXVECTOR2((1.0f / MAX_STAGESELECT) + (1.0f / MAX_STAGESELECT)*nCnt, 1.0f));

		/* �I�����̏����ʒu���L������ */
		m_SelectPos[nCnt] = m_apSelect2D[nCnt]->GetPosition();
	}

	//�w�i
	m_apScene2D[STAGESELECTTYPE_BG] = CScene2D::Create(D3DXVECTOR3(SIZE_X, SIZE_Y, 0), "PLAYERNUMSEL_BG", 1);
	m_apScene2D[STAGESELECTTYPE_BG]->SetWidthHeight(DEFAULT_SIZE*6.0f, DEFAULT_SIZE*3.5f);
	m_apScene2D[STAGESELECTTYPE_BG]->SetbDraw(false);

	//���[�h���сi���j
	m_apScene2D[STAGESELECTTYPE_BAND_L] = CScene2D::Create(D3DXVECTOR3(50.0f, SIZE_Y, 0.0f), "STAGESEL_BAND", 4);
	m_apScene2D[STAGESELECTTYPE_BAND_L]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*3.5f);

	//���[�h���сi�E�j
	m_apScene2D[STAGESELECTTYPE_BAND_R] = CScene2D::Create(D3DXVECTOR3(1230.0f, SIZE_Y, 0.0f), "STAGESEL_BAND", 4);
	m_apScene2D[STAGESELECTTYPE_BAND_R]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*3.5f);

	//�����g
	m_apScene2D[STAGESELECTTYPE_FRAME] = CScene2D::Create(D3DXVECTOR3(SIZE_X, SCREEN_HEIGHT-90.0f, 0.0f), "FRAME");
	m_apScene2D[STAGESELECTTYPE_FRAME]->SetWidthHeight(DEFAULT_SIZE*5.0f, DEFAULT_SIZE*0.8f);

	//����
	m_apScene2D[STAGESELECTTYPE_EXPLANATION] = CScene2D::Create(D3DXVECTOR3(SIZE_X, SCREEN_HEIGHT - 80.0f, 0.0f), "STAGESEL_EXPLANATION");
	m_apScene2D[STAGESELECTTYPE_EXPLANATION]->SetWidthHeight(DEFAULT_SIZE*4.8f, DEFAULT_SIZE*0.8f);
	m_apScene2D[STAGESELECTTYPE_EXPLANATION]->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f / 2));

	//UI_�X�e�B�b�N
	m_apScene2D[STAGESELECTTYPE_UI_OPERATION] = CScene2D::Create(D3DXVECTOR3(200.0f, 465.0f, 0.0f), "UI_OPERATION1", 4);
	m_apScene2D[STAGESELECTTYPE_UI_OPERATION]->SetWidthHeight(DEFAULT_SIZE*0.8f, DEFAULT_SIZE * 0.8f);
	m_apScene2D[STAGESELECTTYPE_UI_OPERATION]->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.25f, 1.0f));

	//UI_�I��
	m_apScene2D[STAGESELECTTYPE_UI_DECISION] = CScene2D::Create(m_apSelect2D[0]->GetPosition(), "UI_SELECT", 4);
	m_apScene2D[STAGESELECTTYPE_UI_DECISION]->SetWidthHeight(DEFAULT_SIZE*1.85f, DEFAULT_SIZE*1.4f);
	m_apScene2D[STAGESELECTTYPE_UI_DECISION]->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	//�}�X�N
	m_pMask2D = CScene2D::Create(D3DXVECTOR3(SIZE_X, SIZE_Y, 0.0f), " ",2);
	m_pMask2D->SetWidthHeight(DEFAULT_SIZE*5.2f, DEFAULT_SIZE*4.0f);
	m_pMask2D->SetCol(DEFAULT_COL_WHITE);
}
//=============================================================================
// ���̕����X�N���[������
//=============================================================================
void CStageSelect::ScrollMenu(STAGESELECTTYPE type, float fScroolSpeed)
{
	m_nCntScrool++;
	if (m_apScene2D[type] != NULL)
	{
		m_apScene2D[type]->SetTex(D3DXVECTOR2(0.0f, 0.0f + (m_nCntScrool*fScroolSpeed)),
			D3DXVECTOR2(1.0f, 1.0f + (m_nCntScrool*fScroolSpeed)));
	}
}
//=============================================================================
// �I����Ԃ̊Ǘ�
//=============================================================================
void CStageSelect::Selecttype(CStageSelect::SELECTTYPE TYPE, CFade *pFade, CManager *pManager)
{
	/* �����̃e�N�X�`�����W�ړ� */
	m_apScene2D[STAGESELECTTYPE_EXPLANATION]->SetTex(D3DXVECTOR2(0.0f, (1.0f / 2)*m_nSelect),
													D3DXVECTOR2(1.0f, (1.0f / 2) + (1.0f / 2)*m_nSelect));

	CSound *pSound = CManager::GetSound();		//	���̎擾

	switch (TYPE)
	{
	case SELECTTYPE_SELECT_MACHINE:	//�@�B
		//�C�ӂ̃L�[ENTER
		if (CCommand::GetCommand("DECISION") == true)
		{
			pSound->SetVolume(CSound::SOUND_LABEL_MACHINESTAGE, 3.5f);
			pSound->PlaySound(CSound::SOUND_LABEL_MACHINESTAGE);
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT04);

			pFade->SetFade(pManager->MODE_GAME, pFade->FADE_OUT);
		}
		break;

	case SELECTTYPE_SELECT_WEATHER:	//�V��@
		if (CCommand::GetCommand("DECISION") == true)
		{
			pSound->SetVolume(CSound::SOUND_LABEL_NATURESTAGE, 3.5f);
			pSound->PlaySound(CSound::SOUND_LABEL_NATURESTAGE);
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT04);
			pFade->SetFade(pManager->MODE_GAME, pFade->FADE_OUT);
		}
		break;
	}
	if (m_bLoad == false)
	{//�X�e�[�W�ǂݍ��݂����Ă��Ȃ��ꍇ
		if (m_MaskFade == MASKFADE_NONE)
		{//�}�X�N�������ȂƂ��̂݃X�e�[�W�ǂݍ��݂��s��
			StageLoadState(STAGELOAD_LOAD, m_nSelect);
			m_bLoad = true;
		}
	}
	else
	{//�X�e�[�W�ǂݍ��݂�����Ă���
		if (m_MaskFade == MASKFADE_IN)
		{//�}�X�N���t�F�[�h�C�����I����Ă鎞�ɓǂݍ��܂ꂽ�X�e�[�W��j������
			StageLoadState(STAGELOAD_UNLOAD, m_nSelect);
			m_bLoad = false;
		}
	}
}
//=============================================================================
// �I�����̈ړ����o
//=============================================================================
void CStageSelect::ProductionIcon(SELECTTYPE type)
{
	switch (type)
	{
	case SELECTTYPE_SELECT_MACHINE:
		m_apSelect2D[0]->SetWidthHeight(DEFAULT_SIZE*1.8f, DEFAULT_SIZE*1.2f);
		m_apSelect2D[1]->SetWidthHeight(DEFAULT_SIZE*1.3f, DEFAULT_SIZE*0.9f);
		break;

	case SELECTTYPE_SELECT_WEATHER:
		m_apSelect2D[0]->SetWidthHeight(DEFAULT_SIZE*1.3f, DEFAULT_SIZE*0.9f);
		m_apSelect2D[1]->SetWidthHeight(DEFAULT_SIZE*1.8f, DEFAULT_SIZE*1.2f);
		break;
	case MASKFADE_MAX:
		break;
	}
	m_apScene2D[STAGESELECTTYPE_UI_DECISION]->SetPosition(m_apSelect2D[(int)type]->GetPosition());
	m_apScene2D[STAGESELECTTYPE_UI_DECISION]->SetWidthHeight(DEFAULT_SIZE*1.85f, DEFAULT_SIZE*1.15f);

	if (m_typeOld != type)
	{
		m_MaskFade = MASKFADE_IN;
	}

	m_typeOld = type;
}
//=============================================================================
// �X�e�[�W�����̏���
//=============================================================================
void CStageSelect::SetStage(int nNumState)
{
	if (m_pObj != NULL) { m_pObj->LoadFile(m_pcStageSelect[nNumState]); }
}
//=============================================================================
// �X�e�[�W�ǂݍ���
//=============================================================================
void CStageSelect::LoadStage(int nNum)
{
	if (m_pObj == NULL)
	{
		m_pObj = CSetObject::Create();
		SetStage(nNum);
	}
}
//=============================================================================
// �X�e�[�W�̓ǂݍ��ݏ�
//=============================================================================
void CStageSelect::StageLoadState(STAGELOAD Load, int nSel)
{
	switch (Load)
	{
	case STAGELOAD_NONE:
		break;

	case STAGELOAD_LOAD:		//�ǂݍ���
		LoadStage(m_nSelect);
		if (m_pMeshField == NULL)
		{//���̐���
			m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f),20, 20, 40);
		}
		if (m_pWall[0] == NULL&&m_pWall[1] == NULL&&m_pWall[2] == NULL&&m_pWall[3] == NULL)
		{//�����ʂ̐���
			m_pWall[0]=CWall::Create(D3DXVECTOR3(0.0f, -100.0f, 400.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(5.0f, 5.0f), 0, 0);
			m_pWall[1] = CWall::Create(D3DXVECTOR3(0.0f, -100.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(5.0f, 5.0f), 0, 0);
			m_pWall[2] = CWall::Create(D3DXVECTOR3(400.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(5.0f, 5.0f), 0, 0);
			m_pWall[3] = CWall::Create(D3DXVECTOR3(-400.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(5.0f, 5.0f), 0, 0);
		}
		m_MaskFade = MASKFADE_OUT;
		break;

	case STAGELOAD_UNLOAD:		//�j��
		if (m_pObj != NULL)
		{//�ǂݍ��݂���Ă���X�e�[�W�I�u�W�F�N�g��j��
			m_pObj->UnLoadObj();
			m_pObj = NULL;
		}
		if (m_pMeshField != NULL)
		{//���̔j��
			m_pMeshField->Uninit();
			m_pMeshField = NULL;
		}
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			if (m_pWall[nCnt] != NULL)
			{//���ʕǂ̔j��
				m_pWall[nCnt]->Uninit();
				m_pWall[nCnt] = NULL;
			}
		}
		break;
	}
}
//=============================================================================
// �}�X�N�̃t�F�[�h����
//=============================================================================
void CStageSelect::MaskFade(void)
{
	D3DXCOLOR col = m_pMask2D->GetCol();

	switch (m_MaskFade)
	{
	case MASKFADE_NONE:
		break;

	case MASKFADE_IN:		//�t�F�[�h�C��
		if (col.a >= 1.0f)
		{
			if (m_bLoad == true)
			{
				StageLoadState(STAGELOAD_UNLOAD, m_type);
				m_bLoad = false;
			}

			m_pMask2D->SetCol(D3DXCOLOR(DEFAULT_COL_WHITE.r, DEFAULT_COL_WHITE.g, DEFAULT_COL_WHITE.b, 1.0f));
			m_MaskFade = MASKFADE_OUT;
			m_bLoad = false;
		}
		else
		{
			col.a += m_fMaskAlpha;
			m_pMask2D->SetCol(D3DXCOLOR(DEFAULT_COL_WHITE.r, DEFAULT_COL_WHITE.g, DEFAULT_COL_WHITE.b, col.a));
		}
		break;

	case MASKFADE_OUT:		//�t�F�[�h�A�E�g
		if (col.a <= 0.0f)
		{
			m_pMask2D->SetCol(D3DXCOLOR(DEFAULT_COL_WHITE.r, DEFAULT_COL_WHITE.g, DEFAULT_COL_WHITE.b, 0.0f));
			m_MaskFade = MASKFADE_NONE;
		}
		else
		{
			if (m_bLoad == false)
			{
				StageLoadState(STAGELOAD_LOAD, m_type);
				m_bLoad = true;
			}
			col.a -= m_fMaskAlpha;
			m_pMask2D->SetCol(D3DXCOLOR(DEFAULT_COL_WHITE.r, DEFAULT_COL_WHITE.g, DEFAULT_COL_WHITE.b, col.a));
		}
		break;
	}
}
//=============================================================================
// �|�C���^�̏���������
//=============================================================================
void CStageSelect::InitPointer(void)
{
	for (int nCnt = 0; nCnt < MAX_STAGESELECT_TEX; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MAX_STAGESELECT; nCnt++)
	{
		if (m_apSelect2D[nCnt] != NULL)
		{
			m_apSelect2D[nCnt] = NULL;
		}
	}
	if (m_pMask2D != NULL)
	{
		m_pMask2D = NULL;
	}
	if (m_pMeshField != NULL)
	{
		m_pMeshField = NULL;
	}
	for (int nCnt = 0; nCnt< 4; nCnt++)
	{
		if(m_pWall[nCnt]!=NULL)
		{
			m_pWall[nCnt] = NULL;
		}
	}
}
//=============================================================================
// �A�j���[�V��������
//=============================================================================
void CStageSelect::SetSelectAnimation(STAGESELECTTYPE type, int AnimType, int MaxAnimPatternX, int MaxAnimPatternY, int AnimSpeed)
{
	m_nCntAnim++;
	if (AnimType == 0)
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

		m_apScene2D[type]->SetTex(D3DXVECTOR2(0.0f + (1.0f / MaxAnimPatternX)*m_nPatturnAnim,
			0.0f + (1.0f / MaxAnimPatternY)),
			D3DXVECTOR2((1.0f / MaxAnimPatternX) + ((1.0f / MaxAnimPatternX)*m_nPatturnAnim),
			(1.0f / MaxAnimPatternY) + (1.0f / MaxAnimPatternY)));
	}
	else if (AnimType == 1)
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

		m_apScene2D[type]->SetTex(D3DXVECTOR2(0.0f + (1.0f / MaxAnimPatternX), 0.0f + ((1.0f / MaxAnimPatternY) *m_nPatturnAnim)),
			D3DXVECTOR2((1.0f / MaxAnimPatternX) + (1.0f / MaxAnimPatternX),
			((1.0f / MaxAnimPatternY)*m_nPatturnAnim) + ((1.0f / MaxAnimPatternY)*m_nPatturnAnim)));
	}
}