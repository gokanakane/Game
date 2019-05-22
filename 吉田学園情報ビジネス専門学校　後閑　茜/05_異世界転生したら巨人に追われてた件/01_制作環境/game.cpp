//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : Eisuke Sakagawa
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "game.h"			// �Q�[��
#include "manager.h"		// �}�l�[�W���[
#include "renderer.h"		// �����_���[
#include "sound.h"			// �T�E���h
#include "input.h"			// ����
#include "camera.h"			// �J����
#include "fade.h"			// �t�F�[�h
#include "meshfield.h"		// ���b�V���t�B�[���h
#include "meshriver.h"		// ���b�V�����o�[
#include "player.h"			// �v���C���[
#include "block.h"			// �u���b�N
#include "item.h"			// �A�C�e��
#include "minimap.h"		// �~�j�}�b�v
#include "time.h"			// �^�C��
#include "bg.h"				// �Q�[���w�i
#include "ui.h"				// ui
#include "life.h"			// ���C�t
#include "score.h"			// �X�R�A
#include "ranking.h"		// �����L���O
#include "effect.h"			// �G�t�F�N�g
#include "item.h"			// �A�C�e��
#include "itemicon.h"		// �A�C�e���A�C�R��
#include "enemy.h"			// �G
#include "3dobject.h"		// 3D�w�i�I�u�W�F�N�g
#include "wall.h"			// ��
#include "start.h"			// �X�^�[�g

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SOUND_SECOND	(120)		// �b�̍ő�
#define SOUND_SECOND		(120)		// �b�̍ő傩�瑫���b

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CPlayer *CGame::m_pPlayer = NULL;
CEnemy *CGame::m_pEnemy = NULL;
CMeshField *CGame::m_pMeshField[m_MeshFieldMax] = { NULL };
CMeshRiver *CGame::m_pMeshRiver[m_MeshRiverMax] = { NULL };
CGame::MODEGAME CGame::m_game = MODE_NONE;

//=============================================================================
// �R���X�g���N�^									(public)	*** CGame ***
//=============================================================================
CGame::CGame()
{
	for (int nCountb = 0; nCountb < TEXT_OBJ_MAX; nCountb++)
	{//	�e�L�X�g�̃I�u�W�F�N�g�̎��
		m_textState[nCountb].nCnter = NULL;
		for (int nCount = 0; nCount < OBJ_MAX; nCount++)
		{//	�e�L�X�g�̒��g�̏�����
			m_textState[nCountb].nType[nCount] = NULL;
			m_textState[nCountb].ncolType[nCount] = NULL;
			m_textState[nCountb].pos[nCount] = {};
			m_textState[nCountb].size[nCount] = {};
			m_textState[nCountb].bUse[nCount] = false;
		}
	}
}

//=============================================================================
// �f�X�g���N�^										(public)	*** CGame ***
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// ���[�h����							(public)	*** CBullet ***
//=============================================================================
HRESULT CGame::Load(void)
{
	return S_OK;
}

//=============================================================================
// �A�����[�h����								(public)	*** CBullet ***
//=============================================================================
void CGame::Unload(void)
{

}

//=============================================================================
// ����������										(public)	*** CGame ***
//=============================================================================
HRESULT CGame::Init(void)
{
	ObjectLoad();					//	�A�C�e���̃e�L�X�g�ǂݍ���

	//	�G�t�F�N�g�̃e�L�X�g�̖��O�̓ǂݍ���
	CEffect::LoadNameEffect();
	CEffect::Load();

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

	CMeshRiver::Load();			// ���b�V�����o�[
	m_pMeshRiver[0] = CMeshRiver::Create(CSceneMesh::MESHTYPE_FIELD, D3DXVECTOR3(12.0f, 0.0f, 15.0f), D3DXVECTOR3(2320, 20.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(240.0f, 0.0f, 300.0f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.9f), D3DXVECTOR2(0.5f, 0.5f), CSceneMesh::MESHTEX_NUMSIZE, CMeshRiver::TEXTURE_DORO);

	m_pMeshRiver[1] = CMeshRiver::Create(CSceneMesh::MESHTYPE_FIELD, D3DXVECTOR3(14.0f, 0.0f, 15.0f), D3DXVECTOR3(8240, 20.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(280.0f, 0.0f, 300.0f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.9f), D3DXVECTOR2(0.5f, 0.5f), CSceneMesh::MESHTEX_NUMSIZE, CMeshRiver::TEXTURE_DORO);

	m_pMeshRiver[2] = CMeshRiver::Create(CSceneMesh::MESHTYPE_FIELD, D3DXVECTOR3(21.0f, 0.0f, 15.0f), D3DXVECTOR3(10500, 20.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(420.0f, 0.0f, 300.0f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.9f), D3DXVECTOR2(0.5f, 0.5f), CSceneMesh::MESHTEX_NUMSIZE, CMeshRiver::TEXTURE_DORO);

	m_pMeshRiver[3] = CMeshRiver::Create(CSceneMesh::MESHTYPE_FIELD, D3DXVECTOR3(16.0f, 0.0f, 15.0f), D3DXVECTOR3(12580, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(320.0f, 0.0f, 300.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f), D3DXVECTOR2(0.5f, 0.5f), CSceneMesh::MESHTEX_NUMSIZE, CMeshRiver::TEXTURE_RIVER);

	CPlayer::Load();			// �v���C���[
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(-400.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));

	CEnemy::Load();				//	�G
	m_pEnemy = CEnemy::Create(D3DXVECTOR3(-600.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CStart::Load();

	CItem::Load();
	CItemicon::Load();

	CBlock::Load();

	C3Dobject::Load();

	CBg::Load();				// �Q�[���w�i
	CBg::Create();

	CUiPolygon::Load();			// UI
	CUiPolygon::Create(D3DXVECTOR3(150.0f, 70.0f, 0.0f), D3DXVECTOR3(100.0f, 70.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2);		// �g(�̗�)
	CUiPolygon::Create(D3DXVECTOR3(950.0f, 70.0f, 0.0f), D3DXVECTOR3(120.0f, 70.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2);		// �g(�X�R�A)
	CUiPolygon::Create(D3DXVECTOR3(1182.0f, 70.0f, 0.0f), D3DXVECTOR3(98.0f, 70.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2);		// �g(�^�C��)
	CUiPolygon::Create(D3DXVECTOR3(560.0f, 70.0f, 0.0f), D3DXVECTOR3(280.0f, 70.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2);		// �g(�~�j�}�b�v)
	CUiPolygon::Create(D3DXVECTOR3(570.0f, 70.0f, 0.0f), D3DXVECTOR3(250.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1);		// �~�j�}�b�v
	CUiPolygon::Create(D3DXVECTOR3(1125.0f, 68.0f, 0.0f), D3DXVECTOR3(21.0f, 20.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3);		// ����
	CUiPolygon::Create(D3DXVECTOR3(100.0f, 70.0f, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 4);		// �v���C���[
	CUiPolygon::Create(D3DXVECTOR3(1196.0f, 67.0f, 0.0f), D3DXVECTOR3(17.0f, 20.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);		// ���Ԃ̊Ԃ̓_

	CMinimap::Load();			// �~�j�}�b�v�̃v���C���[ & ���l
	CMinimap::Create(D3DXVECTOR3(330.0f, 70.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CMinimap::TYPE_ENEMY, 1);
	CMinimap::Create(D3DXVECTOR3(330.0f, 70.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CMinimap::TYPE_PLAYER, 0);

	CTime::Create();			// �^�C��

	CScore::Create();			// �X�R�A

	CLife::Load();				// �̗�
	CLife::Create();

	return S_OK;
}

//=============================================================================
// �I������											(public)	*** CGame ***
//=============================================================================
void CGame::Uninit(void)
{
	CRanking::SaveRanking();
	CBg::Unload();
	CUiPolygon::Unload();
	CMeshField::Unload();
	CPlayer::Unload();
	CMinimap::Unload();
	CItem::Unload();
	CItemicon::Unload();
	CEffect::Unload();
	CEnemy::Unload();
	CBlock::Unload();
	C3Dobject::Unload();

	for (int nCount = 0; nCount < m_MeshFieldMax; nCount++)
	{
		if (m_pMeshField[nCount] != NULL)
		{// NULL�ȊO�̏ꍇ
			m_pMeshField[nCount]->Uninit();
			m_pMeshField[nCount] = NULL;
		}
	}

	if (m_pPlayer != NULL)
	{// NULL�ȊO�̏ꍇ
		m_pPlayer->Uninit();
		m_pPlayer = NULL;
	}

	CScene::ReleaseMode();	// ���[�h�I��
}

//=============================================================================
// �X�V����											(public)	*** CGame ***
//=============================================================================
void CGame::Update(void)
{
	SetStage();

#ifdef _DEBUG
	if (CFade::GetFade() == CFade::FADE_NONE)
	{// �t�F�[�h���Ă��Ȃ����
		if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN))
		{// �L�[�{�[�h�iENTER�j����͂�����
			m_game = MODE_GAMECLEAR;
			CFade::Create(CManager::MODE_RESULT, CFade::FADE_OUT);
		}
	}
#endif // _DEBUG

	int nRand = rand() % SOUND_SECOND + MAX_SOUND_SECOND;
	m_nCounter++;		// �J�E���^�[�̑���

	if ((m_nCounter % nRand) == 0)
	{	// �����ԍ������߂�
		//m_nSoundNum = rand() % 6 + 0;
		PlayES(rand() % 6 + 0);
	}

}

//=============================================================================
// �`�揈��											(public)	*** CGame ***
//=============================================================================
void CGame::Draw(void)
{

}

//=============================================================================
// �e�L�X�g�ǂݍ���
//=============================================================================
void CGame::ObjectLoad(void)
{
	FILE *pFile;
	char read[128];
	int nObjTypeCounter = 0;		//	�I�u�W�F�N�g�̎�ނ̍X�V

									//	�ǂݍ��ރe�L�X�g
	pFile = fopen("data/TEXT/object.txt", "r");
	if (pFile != NULL)
	{
		fscanf(pFile, "%s", &read[0]);
		if (strcmp(&read[0], "ITEM_MAX") == 0)
		{//	�A�C�e���̕K�v�Ȑ��̎擾
			fscanf(pFile, "%s%d", &read[0], &m_textState[0].nCnter);
		}
		fscanf(pFile, "%s", &read[0]);
		if (strcmp(&read[0], "BLOCK_MAX") == 0)
		{//	�u���b�N�̕K�v�Ȑ��̎擾
			fscanf(pFile, "%s%d", &read[0], &m_textState[1].nCnter);
		}
		//---------------------------------------------------------------
		//	�A�C�e���̐ݒ�̃e�L�X�g��R�����g�A�E�g
		//---------------------------------------------------------------
		for (int nCount = 0; nCount < 6; nCount++) 	{ fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		for (int nCount = 0; nCount < m_textState[nObjTypeCounter].nCnter;)
		{
			fscanf(pFile, "%s", &read[0]);
			if (strcmp(&read[0], "ITEM_SET") == 0)
			{//	�����񂪃A�C�e���Z�b�g��������
				do
				{
					fscanf(pFile, "%s", &read[0]);
					if (strcmp(&read[0], "POS") == 0)
					{//	�ʒu�̐ݒ�
						fscanf(pFile, "%s%f%f%f", &read[0], &m_textState[nObjTypeCounter].pos[nCount].x, &m_textState[nObjTypeCounter].pos[nCount].y, &m_textState[nObjTypeCounter].pos[nCount].z);
					}
					else if (strcmp(&read[0], "SIZE") == 0)
					{//	�傫���̐ݒ�
						fscanf(pFile, "%s%f%f%f", &read[0], &m_textState[nObjTypeCounter].size[nCount].x, &m_textState[nObjTypeCounter].size[nCount].y, &m_textState[nObjTypeCounter].size[nCount].z);
					}
					else if (strcmp(&read[0], "TYPE") == 0)
					{//	��ނ̐ݒ�
						fscanf(pFile, "%s%d", &read[0], &m_textState[nObjTypeCounter].nType[nCount]);
					}
				} while (strcmp(&read[0], "ITEM_END") != 0);
				nCount++;
			}
		}
		//---------------------------------------------------------------
		//	�u���b�N�̐ݒ�̃e�L�X�g��R�����g�A�E�g
		//---------------------------------------------------------------
		for (int nCount = 0; nCount < 31; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		nObjTypeCounter += 1;	//	�u���b�N�I�u�W�F�N�g
		for (int nCount = 0; nCount < m_textState[nObjTypeCounter].nCnter;)
		{
			fscanf(pFile, "%s", &read[0]);
			if (strcmp(&read[0], "BLOCK_SET") == 0)
			{//	�����񂪃A�C�e���Z�b�g��������
				do
				{
					fscanf(pFile, "%s", &read[0]);
					if (strcmp(&read[0], "POS") == 0)
					{//	�ʒu�̐ݒ�
						fscanf(pFile, "%s%f%f%f", &read[0], &m_textState[nObjTypeCounter].pos[nCount].x, &m_textState[nObjTypeCounter].pos[nCount].y, &m_textState[nObjTypeCounter].pos[nCount].z);
					}
					else if (strcmp(&read[0], "MODELTYPE") == 0)
					{//	��ނ̐ݒ�
						fscanf(pFile, "%s%d", &read[0], &m_textState[nObjTypeCounter].nType[nCount]);
					}
					else if (strcmp(&read[0], "COLTYPE") == 0)
					{//	��ނ̐ݒ�
						fscanf(pFile, "%s%d", &read[0], &m_textState[nObjTypeCounter].ncolType[nCount]);
					}
				} while (strcmp(&read[0], "BLOCK_END") != 0);
				nCount++;
			}
		}
		fclose(pFile);
	}
	FILE *pFile3DOBJ;
	//	�ǂݍ��ރe�L�X�g
	pFile3DOBJ = fopen("data/TEXT/3dobject.txt", "r");
	if (pFile3DOBJ != NULL)
	{
		fscanf(pFile3DOBJ, "%s", &read[0]);
		if (strcmp(&read[0], "3DPORIGON_MAX") == 0)
		{//	�u���b�N�̕K�v�Ȑ��̎擾
			fscanf(pFile3DOBJ, "%s%d", &read[0], &m_textState[2].nCnter);
		}
		//---------------------------------------------------------------
		//	�w�i�I�u�W�F�N�g�̐ݒ�̃e�L�X�g��R�����g�A�E�g
		//---------------------------------------------------------------
		for (int nCount = 0; nCount < 11; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		nObjTypeCounter += 1;	//	�u���b�N�I�u�W�F�N�g
		for (int nCount = 0; nCount < m_textState[nObjTypeCounter].nCnter;)
		{
			fscanf(pFile3DOBJ, "%s", &read[0]);
			if (strcmp(&read[0], "3DPORIGON_SET") == 0)
			{//	�����񂪃A�C�e���Z�b�g��������
				do
				{
					fscanf(pFile3DOBJ, "%s", &read[0]);
					if (strcmp(&read[0], "POS") == 0)
					{//	�ʒu�̐ݒ�
						fscanf(pFile3DOBJ, "%s%f%f%f", &read[0], &m_textState[nObjTypeCounter].pos[nCount].x, &m_textState[nObjTypeCounter].pos[nCount].y, &m_textState[nObjTypeCounter].pos[nCount].z);
					}
					else if (strcmp(&read[0], "SIZE") == 0)
					{//	��ނ̐ݒ�
						fscanf(pFile3DOBJ, "%s%f%f%f", &read[0], &m_textState[nObjTypeCounter].size[nCount].x, &m_textState[nObjTypeCounter].size[nCount].y, &m_textState[nObjTypeCounter].size[nCount].z);
					}
					else if (strcmp(&read[0], "TYPE") == 0)
					{//	��ނ̐ݒ�
						fscanf(pFile3DOBJ, "%s%d", &read[0], &m_textState[nObjTypeCounter].nType[nCount]);
					}
				} while (strcmp(&read[0], "3DPORIGON_END") != 0);
				nCount++;
			}
		}
		fclose(pFile3DOBJ);
	}
}

void CGame::SetStage(void)
{
	// �J�����ݒ�
	D3DXVECTOR3 posVDest = CManager::GetCamera()->GetPosVDest();	// ���_�擾

	for (int nCount = 0; nCount < m_textState[0].nCnter; nCount++)
	{//	�A�C�e���̐ݒ�
		if (m_textState[0].pos[nCount].x < posVDest.x + 1000.0f && m_textState[0].bUse[nCount] == false)
		{
			CItem::Create(m_textState[0].pos[nCount], D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_textState[0].size[nCount], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), m_textState[0].nType[nCount]);
			m_textState[0].bUse[nCount] = true;
		}
	}

	for (int nCount = 0; nCount < m_textState[1].nCnter; nCount++)
	{//	�u���b�N�̐ݒ�
		if (m_textState[1].pos[nCount].x < posVDest.x + 1000.0f && m_textState[1].bUse[nCount] == false)
		{
			CBlock::Create(m_textState[1].pos[nCount], (CBlock::MODELTYPE)m_textState[1].nType[nCount], (CBlock::COLTYPE)m_textState[1].ncolType[nCount]);
			m_textState[1].bUse[nCount] = true;
		}
	}

	for (int nCount = 0; nCount < m_textState[2].nCnter; nCount++)
	{//	�u���b�N�̐ݒ�
		if (m_textState[2].pos[nCount].x < posVDest.x + 1000.0f && m_textState[2].bUse[nCount] == false)
		{
			C3Dobject::Create(m_textState[2].pos[nCount], D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_textState[2].size[nCount], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), m_textState[2].nType[nCount]);
			m_textState[2].bUse[nCount] = true;
		}
	}
}

//=============================================================================
// ��������											(public)	*** CGame ***
//=============================================================================
void CGame::PlayES(int nSoundNum)
{
	CSound *pSound = CManager::GetSound();
	if (nSoundNum == 0)
	{	// ���̉�
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE022);
		nSoundNum = -1;
	}
	else if (nSoundNum == 1)
	{	// �����̉�
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE023);
		nSoundNum = -1;
	}
	else if (nSoundNum == 2)
	{	//	���敗�̉�
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE024);
		nSoundNum = -1;
	}
	else if (nSoundNum == 3)
	{	//	���̉�
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE034);
		nSoundNum = -1;
	}
	else if (nSoundNum == 4)
	{	//	��2�̉�
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE035);
		nSoundNum = -1;
	}
	else if (nSoundNum == 5)
	{	//	��3�̉�
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE036);
		nSoundNum = -1;
	}
	else if (nSoundNum == 6)
	{	//	���̉�
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE037);
		nSoundNum = -1;
	}
}