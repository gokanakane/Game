//=============================================================================
//
// ���b�V���t�B�[���h���� [meshfield.cpp]
// Author : Eisuke Sakagawa
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "meshriver.h"		// ���b�V�����o�[
#include "manager.h"		// �}�l�[�W���[
#include "input.h"			// ����
#include "renderer.h"		// �����_���[
#include "camera.h"			// �J����
#include "game.h"			// �Q�[��
#include "player.h"			// �v���C���[

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME_1	"data\\TEXTURE\\field003.jpg"		// �e�N�X�`��
#define TEXTURE_NAME_2	"data\\TEXTURE\\field002.jpg"		// �e�N�X�`��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	CMeshRiver::m_pTexture[TEXTURE_MAX] = { NULL };		// �e�N�X�`��

//=============================================================================
// �R���X�g���N�^									(public)	*** CMeshRiver ***
//=============================================================================
CMeshRiver::CMeshRiver() : CSceneMesh(CScene::PRIORITY_4, CScene::OBJTYPE_MESHFIELD)
{
	m_Sinrot = 0.0f;
}

//=============================================================================
// �f�X�g���N�^										(public)	*** CMeshRiver ***
//=============================================================================
CMeshRiver::~CMeshRiver()
{

}

//=============================================================================
// ���[�h����							(public)	*** CMeshRiver ***
//=============================================================================
HRESULT CMeshRiver::Load(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (m_pTexture[0] == NULL)
	{
		// �e�N�X�`���̐���
		D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_1, &m_pTexture[0]);
		D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_2, &m_pTexture[1]);
	}

	return S_OK;
}

//=============================================================================
// �A�����[�h����								(public)	*** CMeshRiver ***
//=============================================================================
void CMeshRiver::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// �m�ۏ���											(public)	*** CMeshRiver ***
//=============================================================================
CMeshRiver *CMeshRiver::Create(MESHTYPE meshType, D3DXVECTOR3 num, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, MESHTEX meshTex, int nNum)
{
	CMeshRiver *pMeshRiver = NULL;				// �V�[���|�C���^

	if (pMeshRiver == NULL)
	{// NULL�̏ꍇ
		pMeshRiver = new CMeshRiver;			// �V�[���������m��
	}

	if (pMeshRiver != NULL)
	{// NULL�ȊO�̏ꍇ
	 // �����������i�ʒu�A�傫���A�F�AUV�j
		pMeshRiver->Init(meshType, num, pos, rot, size, col, TexUV, meshTex);
		pMeshRiver->BindTexture(m_pTexture[nNum]);	// �e�N�X�`���ݒ�
	}

	return pMeshRiver;
}

//=============================================================================
// ����������										(public)	*** CMeshRiver ***
//=============================================================================
HRESULT CMeshRiver::Init(MESHTYPE meshType, D3DXVECTOR3 num, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, MESHTEX meshTex)
{
	CSceneMesh::SetInitAll(meshType, num, pos, rot, size, col, D3DXVECTOR2(TexUV.x, TexUV.y), meshTex);
	CSceneMesh::Init();		// ����������

	return S_OK;
}

//=============================================================================
// �I������											(public)	*** CMeshRiver ***
//=============================================================================
void CMeshRiver::Uninit(void)
{
	CSceneMesh::Uninit();						// �I������
}

//=============================================================================
// �X�V����											(public)	*** CMeshRiver ***
//=============================================================================
void CMeshRiver::Update(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();

	m_Sinrot += 0.05f;

	CSceneMesh::SinUpdate(CSceneMesh::SINTYPE_RIGHT, CSceneMesh::SINSTART_LU, pPlayer->Getpos(), m_Sinrot, 3.0f, 5.0f);

	if (CSceneMesh::ColInMesh(pPlayer->Getpos()))
		CSceneMesh::SinUpdate(CSceneMesh::SINTYPE_CIRCLE, CSceneMesh::SINSTART_POS, pPlayer->Getpos(), m_Sinrot, 4.0f, 3.0f, 100.0f);


	CSceneMesh::Update();						// �X�V����
}

//=============================================================================
// �`�揈��											(public)	*** CMeshRiver ***
//=============================================================================
void CMeshRiver::Draw(void)
{
	CSceneMesh::Draw();						// �`�揈��
}