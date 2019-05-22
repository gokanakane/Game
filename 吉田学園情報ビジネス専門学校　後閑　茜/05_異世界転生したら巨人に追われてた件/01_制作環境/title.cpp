//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : Shun Yokomichi
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "title.h"			// �^�C�g��
#include "manager.h"		// �}�l�[�W���[
#include "renderer.h"		// �����_���[
#include "sound.h"			// �T�E���h
#include "input.h"			// ����
#include "fade.h"			// �t�F�[�h
#include "titlelogo.h"		// �^�C�g�����S
#include "titleframe.h"		// �^�C�g���t���[��
#include "press.h"			// �v���X�{�^��
#include "ranking.h"		// �����L���O
#include "camera.h"			// �J����
#include "meshfield.h"		// ���b�V���t�B�[���h
#include "bg.h"				// �w�i
#include "block.h"
#include "wall.h"
#include "3dobject.h"		// 3D�w�i�I�u�W�F�N�g

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CMeshField *CTitle::m_pMeshField[8] = {};
CRanking *CTitle::m_pRanking = NULL;

//=============================================================================
// �R���X�g���N�^									(public)	*** CTitle ***
//=============================================================================
CTitle::CTitle()
{
	m_textState.nCnter = NULL;

	for (int nCount = 0; nCount < TITLE_OBJ_MAX; nCount++)
	{//	�e�L�X�g�̒��g�̏�����
		m_textState.nType[nCount] = NULL;
		m_textState.ncolType[nCount] = NULL;
		m_textState.pos[nCount] = {};
		m_textState.size[nCount] = {};
		m_textState.bUse[nCount] = false;
	}
}

//=============================================================================
// �f�X�g���N�^										(public)	*** CTitle ***
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// ���[�h����							(public)	*** CTitle ***
//=============================================================================
HRESULT CTitle::Load(void)
{
	return S_OK;
}

//=============================================================================
// �A�����[�h����								(public)	*** CTitle ***
//=============================================================================
void CTitle::Unload(void)
{

}

//=============================================================================
// ����������										(public)	*** CTitle ***
//=============================================================================
HRESULT CTitle::Init(void)
{
	ObjectLoad();					//	�A�C�e���̃e�L�X�g�ǂݍ���

	CTitleLogo::Load();			// �^�C�g�����S
	CPress::Load();				// �v���X�{�^��

	CTitleFrame::Load();		// �^�C�g���t���[��

	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	CTitleFrame::Create(pos, D3DXVECTOR3(95.0f, 54.0f, 0.0f), D3DX_PI, 1);
	CTitleFrame::Create(pos, D3DXVECTOR3(70.0f, 100.0f, 0.0f), (D3DX_PI * 0.5f), 0);
	CTitleFrame::Create(pos, D3DXVECTOR3(130.0f, 75.0f, 0.0f), 0.0f, 0);
	CTitleFrame::Create(pos, D3DXVECTOR3(100.0f, 145.0f, 0.0f), (D3DX_PI * -0.5f), 1);
	CTitleFrame::Create(pos, D3DXVECTOR3(185.0f, 110.0f, 0.0f), D3DX_PI, 0);
	CTitleFrame::Create(pos, D3DXVECTOR3(135.0f, 200.0f, 0.0f), (D3DX_PI * 0.5f), 1);
	CTitleFrame::Create(pos, D3DXVECTOR3(255.0f, 140.0f, 0.0f), 0.0f, 1);
	CTitleFrame::Create(pos, D3DXVECTOR3(180.0f, 270.0f, 0.0f), (D3DX_PI * -0.5f), 0);
	CTitleFrame::Create(pos, D3DXVECTOR3(330.0f, 210.0f, 0.0f), D3DX_PI, 1);
	CTitleFrame::Create(pos, D3DXVECTOR3(222.0f, 350.0f, 0.0f), (D3DX_PI * 0.5f), 0);
	CTitleFrame::Create(pos, D3DXVECTOR3(440.0f, 230.0f, 0.0f), 0.0f, 0);
	CTitleFrame::Create(pos, D3DXVECTOR3(290.0f, 450.0f, 0.0f), (D3DX_PI * -0.5f), 1);
	CTitleFrame::Create(pos, D3DXVECTOR3(550.0f, 300.0f, 0.0f), D3DX_PI, 0);
	CTitleFrame::Create(pos, D3DXVECTOR3(370.0f, 560.0f, 0.0f), (D3DX_PI * 0.5f), 0);
	CTitleFrame::Create(pos, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 0.0f, 0);

	CCamera *pCamera = CManager::GetCamera();		// �J�����擾
	pCamera->SetPos(D3DXVECTOR3(50.0f, 230.0f, -500.0f), D3DXVECTOR3(50.0f, 170.0f, 0.0f));

	CWall::Load();
	CWall::Create(D3DXVECTOR3(3430.0f, -150.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 150.0f, 0.0f));
	CWall::Create(D3DXVECTOR3(4450.0f, -150.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 150.0f, 0.0f));
	CWall::Create(D3DXVECTOR3(4925.0f, -150.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(25.0f, 150.0f, 0.0f));
	CWall::Create(D3DXVECTOR3(6595.0f, -150.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(45.0f, 150.0f, 0.0f));
	CWall::Create(D3DXVECTOR3(7615.0f, -150.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(55.0f, 150.0f, 0.0f));
	CWall::Create(D3DXVECTOR3(11785.0f, -150.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(115.0f, 150.0f, 0.0f));

	CMeshField::Load();			// ���b�V���t�B�[���h
	m_pMeshField[0] = CMeshField::Create(CSceneMesh::MESHTYPE_FIELD, D3DXVECTOR3(110.0f, 0.0f, 15.0f), D3DXVECTOR3(1180.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(2200.0f, 0.0f, 300.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), CSceneMesh::MESHTEX_NUMSIZE);

	m_pMeshField[1] = CMeshField::Create(CSceneMesh::MESHTYPE_FIELD, D3DXVECTOR3(28.0f, 0.0f, 15.0f), D3DXVECTOR3(3940, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(460.0f, 0.0f, 300.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), CSceneMesh::MESHTEX_NUMSIZE);

	m_pMeshField[2] = CMeshField::Create(CSceneMesh::MESHTYPE_FIELD, D3DXVECTOR3(10.0f, 0.0f, 15.0f), D3DXVECTOR3(4700.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(200.0f, 0.0f, 300.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), CSceneMesh::MESHTEX_NUMSIZE);

	m_pMeshField[3] = CMeshField::Create(CSceneMesh::MESHTYPE_FIELD, D3DXVECTOR3(30.0f, 0.0f, 15.0f), D3DXVECTOR3(5750.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(800.0f, 0.0f, 300.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), CSceneMesh::MESHTEX_NUMSIZE);

	m_pMeshField[4] = CMeshField::Create(CSceneMesh::MESHTYPE_FIELD, D3DXVECTOR3(23.0f, 0.0f, 15.0f), D3DXVECTOR3(7100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(460.0f, 0.0f, 300.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), CSceneMesh::MESHTEX_NUMSIZE);

	m_pMeshField[5] = CMeshField::Create(CSceneMesh::MESHTYPE_FIELD, D3DXVECTOR3(100.0f, 0.0f, 15.0f), D3DXVECTOR3(9670.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(2000.0f, 0.0f, 300.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), CSceneMesh::MESHTEX_NUMSIZE);

	m_pMeshField[6] = CMeshField::Create(CSceneMesh::MESHTYPE_FIELD, D3DXVECTOR3(12.0f, 0.0f, 15.0f), D3DXVECTOR3(12020.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(240.0f, 0.0f, 300.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), CSceneMesh::MESHTEX_NUMSIZE);

	m_pMeshField[7] = CMeshField::Create(CSceneMesh::MESHTYPE_FIELD, D3DXVECTOR3(40.0f, 0.0f, 15.0f), D3DXVECTOR3(13700.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(800.0f, 0.0f, 300.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), CSceneMesh::MESHTEX_NUMSIZE);

	//CBlock::Load();
	//for (int nCount = 0; nCount < m_textState.nCnter; nCount++)
	//{//	�u���b�N�̐ݒ�
	//	CBlock::Create(m_textState.pos[nCount], (CBlock::MODELTYPE)m_textState.nType[nCount], (CBlock::COLTYPE)m_textState.ncolType[nCount]);
	//}

	C3Dobject::Load();

	CBg::Load();				// �Q�[���w�i
	CBg::Create();


	// ������
	m_nType = 1;
	m_fColA = 0.0f;
	m_nCounter = 0;
	m_type = TYPE_SCENEN001;	// �^�C�g���t���[����
	m_pPress = NULL;

	return S_OK;
}

//=============================================================================
// �I������											(public)	*** CTitle ***
//=============================================================================
void CTitle::Uninit(void)
{
	CMeshField::Unload();
	C3Dobject::Unload();
	CBg::Unload();
	CTitleLogo::Unload();
	CPress::Unload();
	CTitleFrame::Unload();
	CBlock::Unload();

	if (m_pRanking != NULL)
	{	// NULL����Ȃ��Ȃ�
		m_pRanking->Uninit();
		delete m_pRanking;
		m_pRanking = NULL;
	}
	for (int nCount = 0; nCount < 8; nCount++)
	{
		if (m_pMeshField[nCount] != NULL)
		{// NULL�ȊO�̏ꍇ
			m_pMeshField[nCount]->Uninit();
			m_pMeshField[nCount] = NULL;
		}
	}
	if (m_pPress != NULL)
	{
		m_pPress->Uninit();
		m_pPress = NULL;
	}

	CScene::ReleaseMode();	// ���[�h�I��
}

//=============================================================================
// �X�V����											(public)	*** CTitle ***
//=============================================================================
void CTitle::Update(void)
{
	CSound *pSound = CManager::GetSound();

	SetStage();

	switch (m_type)
	{
	case TYPE_SCENEN000:
		m_nCounter++;
		if ((m_nCounter % 60) == 0)
		{	// 1�b�o�ߌ�
			m_nType = 1;
			m_type = TYPE_SCENEN001;  // �^�C�g���\����
		}
		break;

	case TYPE_SCENEN001:
		if (m_nType == 1)
		{	// �^�C�g�����S�̐���
			CTitleLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CTitleLogo::TYPE_LOGO, 0);
			m_nType = 0;		// �t���O��0��
		}

		if (int nPattern = CTitleLogo::GetPattern() == 1)
		{	// �v���X�{�^���̐���
			if (m_pPress == NULL)
			{
				m_pPress = new CPress;
				m_pPress->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, 650.0f, 0.0f), D3DXVECTOR3(550.0f, 200.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 0, 0.0f);
			}
			nPattern = 2;		// �t���O��2��
			CTitleLogo::SetPattern(nPattern);
		}
		else if (int nPattern = CTitleLogo::GetPattern() == 3)
		{	// �t���O��3�Ȃ�
			m_nType = 1;				// �t���O��1��
			m_type = TYPE_SCENEN002;	//�@�����L���O�\����
			if (m_pPress != NULL)
			{
				m_pPress->Uninit();
				m_pPress = NULL;
			}
		}

		break;

	case TYPE_SCENEN002:
		if (m_nType == 1)
		{	// �t���O���P�̏ꍇ
			if (m_pRanking == NULL)
			{
				m_pRanking = new CRanking;
				if (m_pRanking != NULL)
				{	// �����L���O��Init��
					m_pRanking->Init(D3DXVECTOR3(1000.0f, 260.0f, 0.0f));
				}
			}
			if (m_pPress == NULL)
			{
				m_pPress = new CPress;
				m_pPress->Init(D3DXVECTOR3(1100.0f, 680.0f, 0.0f), D3DXVECTOR3(250.0f, 130.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 0, 0.0f);
			}
			m_nType = 0;		// �t���O���O��
		}

		if (m_pRanking != NULL)
		{	// NULL����Ȃ��Ȃ�
			m_pRanking->Update();
		}
		if (int nPattern = CRanking::GetPattern() == 1)
		{	// �t���O��1�Ȃ�
			m_nType = 1;				// �t���O���P��
			m_type = TYPE_SCENE003;		// �^�C�g�����S��
			m_pRanking->Uninit();
			delete m_pRanking;
			m_pRanking = NULL;
		}

		break;

	case TYPE_SCENE003:
		if (m_nType == 1)
		{	// �^�C�g�����S�̐���
			CTitleLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f), D3DXVECTOR3(600.0f, 300.0f, 0.0f), CTitleLogo::TYPE_CREDIT, 1);
			m_nType = 0;		// �t���O��0��
		}

		if (int nPattern = CTitleLogo::GetPattern() == 1)
		{	// �t���O��3�Ȃ�
			m_nType = 1;				// �t���O��1��
			m_type = TYPE_SCENEN001;	// �����L���O�\����

			if (m_pPress != NULL)
			{
				m_pPress->Uninit();
				m_pPress = NULL;
			}
		}
		break;
	}

	if (CFade::GetFade() == CFade::FADE_NONE)
	{// �t�F�[�h���Ă��Ȃ����
		if (CManager::GetInputKeyboard()->GetALL(1) == true || CManager::GetInputXPad()->GetALL(1, 0) == true)
		{// �L�[�{�[�h�iENTER�j����͂�����
			CFade::Create(CManager::MODE_TUTORIAL, CFade::FADE_OUT);
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE001);
		}
	}
}

//=============================================================================
// �`�揈��											(public)	*** CTitle ***
//=============================================================================
void CTitle::Draw(void)
{

}

//=============================================================================
// �e�L�X�g�ǂݍ���
//=============================================================================
void CTitle::ObjectLoad(void)
{
	FILE *pFile;
	char read[128];
									//	�ǂݍ��ރe�L�X�g
	pFile = fopen("data/TEXT/3dobject.txt", "r");
	if (pFile != NULL)
	{
		fscanf(pFile, "%s", &read[0]);
		if (strcmp(&read[0], "3DPORIGON_MAX") == 0)
		{//	�u���b�N�̕K�v�Ȑ��̎擾
			fscanf(pFile, "%s%d", &read[0], &m_textState.nCnter);
		}

		//---------------------------------------------------------------
		//	�u���b�N�̐ݒ�̃e�L�X�g��R�����g�A�E�g
		//---------------------------------------------------------------
		for (int nCount = 0; nCount < 12; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		for (int nCount = 0; nCount < m_textState.nCnter; nCount++)
		{
			fscanf(pFile, "%s", &read[0]);
			if (strcmp(&read[0], "3DPORIGON_SET") == 0)
			{//	�����񂪃A�C�e���Z�b�g��������
				do
				{
					fscanf(pFile, "%s", &read[0]);
					if (strcmp(&read[0], "POS") == 0)
					{//	�ʒu�̐ݒ�
						fscanf(pFile, "%s%f%f%f", &read[0], &m_textState.pos[nCount].x, &m_textState.pos[nCount].y, &m_textState.pos[nCount].z);
					}
					else if (strcmp(&read[0], "SIZE") == 0)
					{//	��ނ̐ݒ�
						fscanf(pFile, "%s%f%f%f", &read[0], &m_textState.size[nCount].x, &m_textState.size[nCount].y, &m_textState.size[nCount].z);
					}
					else if (strcmp(&read[0], "TYPE") == 0)
					{//	��ނ̐ݒ�
						fscanf(pFile, "%s%d", &read[0], &m_textState.nType[nCount]);
					}
				} while (strcmp(&read[0], "3DPORIGON_END") != 0);
			}
		}
		fclose(pFile);
	}
}

void CTitle::SetStage(void)
{
	// �J�����ݒ�
	D3DXVECTOR3 posVDest = CManager::GetCamera()->GetPosVDest();	// ���_�擾

	for (int nCount = 0; nCount < m_textState.nCnter; nCount++)
	{//	�u���b�N�̐ݒ�
		if (m_textState.pos[nCount].x < posVDest.x + 1000.0f && m_textState.bUse[nCount] == false)
		{
			C3Dobject::Create(m_textState.pos[nCount], D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_textState.size[nCount], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), m_textState.nType[nCount]);
			m_textState.bUse[nCount] = true;
		}
	}
}