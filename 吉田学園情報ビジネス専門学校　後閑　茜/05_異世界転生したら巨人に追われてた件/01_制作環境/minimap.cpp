//=============================================================================
//
// �~�j�}�b�v���� [minimap.cpp]
// Author : Shun Yokomichi
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "minimap.h"		// �~�j�}�b�v
#include "manager.h"		// �}�l�[�W���[
#include "renderer.h"		// �����_���[
#include "player.h"			// �v���C���[
#include "game.h"			// �Q�[��
#include "enemy.h"			

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME000		"data\\TEXTURE\\game\\player.png"	// �e�N�X�`��
#define TEXTURE_NAME001		"data\\TEXTURE\\game\\enemy.png"	// �e�N�X�`��
#define TEX_UV_U			(1.0f)								// �e�N�X�`��UV_U
#define TEX_UV_V			(1.0f)								// �e�N�X�`��UV_V
#define POS_X_DIVISION		(30.0f)								// POS_X�̏��Z�̐���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9			CMinimap::m_pTexture[MAX_MINI] = {};			// �e�N�X�`�����ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^									(public)	*** CMinimap ***
//=============================================================================
CMinimap::CMinimap() : CScene2D(CScene::PRIORITY_UI, CScene::OBJTYPE_NUMBER)
{

}

//=============================================================================
// �f�X�g���N�^										(public)	*** CMinimap ***
//=============================================================================
CMinimap::~CMinimap()
{

}

//=============================================================================
// ���[�h����							(public)	*** CMinimap ***
//=============================================================================
HRESULT CMinimap::Load(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCntTex = 0; nCntTex < MAX_MINI; nCntTex++)
	{
		if (m_pTexture[nCntTex] == NULL)
		{
			// �e�N�X�`���̐���
			D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME000, &m_pTexture[0]);
			D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME001, &m_pTexture[1]);
		}
	}


	return S_OK;
}

//=============================================================================
// �A�����[�h����								(public)	*** CMinimap ***
//=============================================================================
void CMinimap::Unload(void)
{
	for (int nCntTex = 0; nCntTex < MAX_MINI; nCntTex++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCntTex] != NULL)
		{// NULL�ȊO�̏ꍇ
			m_pTexture[nCntTex]->Release();		// ���
			m_pTexture[nCntTex] = NULL;			// NULL��
		}
	}
}

//=============================================================================
// ��������										(public)	*** CMinimap ***
//=============================================================================
CMinimap *CMinimap::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TYPE type, int nTex)
{
	CMinimap *pMinimap = NULL;

	// �V�[���̐���
	if (pMinimap == NULL)
	{
		pMinimap = new CMinimap;
		if (pMinimap != NULL)
		{
			pMinimap->Init(pos, size, col, type, nTex);	// scene3D�̏�������
		}
	}

	return pMinimap;
}

//=============================================================================
// ����������										(public)	*** CMinimap ***
//=============================================================================
HRESULT CMinimap::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TYPE type, int nTex)
{
	CScene2D::SetInitAll(pos, size, col, D3DXVECTOR2(TEX_UV_U, TEX_UV_V));		// �����l�ݒ�
	CScene2D::Init();															// ����������
	CScene2D::BindTexture(m_pTexture[nTex]);											// �e�N�X�`�����f
	m_Type = type;
	m_fPosX = 0.0f;

	return S_OK;
}

//=============================================================================
// �I������											(public)	*** CNumber2D ***
//=============================================================================
void CMinimap::Uninit(void)
{
	CScene2D::Uninit();					// �I������
}

//=============================================================================
// �X�V����											(public)	*** CNumber2D ***
//=============================================================================
void CMinimap::Update(void)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���[�J��pos�̏�����
	if (m_Type == TYPE_ENEMY)
	{
		CScene *pScene = CScene::GetScene(CScene::PRIORITY_3);
		CScene *pSceneNext = NULL;

		while (pScene != NULL)
		{
			pSceneNext = pScene->GetSceneNext();
			if (pScene->GetObjType() == CScene::OBJTYPE_ENEMY)
			{//	�I�u�W�F�N�g�����f����������
				CEnemy *pEnemy = (CEnemy*)pScene;
				pos = pEnemy->Getpos();
				
			}
			pScene = pSceneNext;
		}
	}
	else if (m_Type == TYPE_PLAYER)
	{
		CPlayer *pPlayer = CGame::GetPlayer();	// �v���C���[���擾
		*pos = *pPlayer->Getpos();				// �v���C���[�̈ʒu���擾
	}

	switch (m_Type)
	{
	case TYPE_PLAYER:
		// �v���C���[�̏ꍇ
		m_fPosX = (pos.x / POS_X_DIVISION) + 330.0f;	// �v�Z�ێ��p�ϐ�
		break;

	case TYPE_ENEMY:
		// ���l�̏ꍇ
		m_fPosX = (pos.x / POS_X_DIVISION) + 330.0f;	// �v�Z�ێ��p�ϐ�
		break;
	}

	//	�͈͎w��
	if (m_fPosX >= 800.0f)
	{
		m_fPosX = 800.0f;
	}
	if (m_fPosX <= 330.0f)
	{
		m_fPosX = 330.0f;
	}

	CScene2D::Setpos(D3DXVECTOR3(m_fPosX, 70.0f, 0.0f));

	CScene2D::Update();					// �X�V����
}

//=============================================================================
// �`�揈��											(public)	*** CNumber2D ***
//=============================================================================
void CMinimap::Draw(void)
{
	CScene2D::Draw();					// �`�揈��
}