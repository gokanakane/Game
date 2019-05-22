//=============================================================================
//
// ���b�V���t�B�[���h���� [meshfield.cpp]
// Author : Eisuke Sakagawa
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "meshfield.h"		// ���b�V���t�B�[���h
#include "manager.h"		// �}�l�[�W���[
#include "input.h"			// ����
#include "renderer.h"		// �����_���[
#include "camera.h"			// �J����
#include "game.h"			// �Q�[��
#include "player.h"			// �v���C���[
#include "wall.h"			// ��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME_1	"data\\TEXTURE\\fieldmesh.png"		// �e�N�X�`��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	CMeshField::m_pTexture = {};		// �e�N�X�`��

//=============================================================================
// �R���X�g���N�^									(public)	*** CMeshField ***
//=============================================================================
CMeshField::CMeshField() : CSceneMesh(CScene::PRIORITY_1, CScene::OBJTYPE_MESHFIELD)
{

}

//=============================================================================
// �f�X�g���N�^										(public)	*** CMeshField ***
//=============================================================================
CMeshField::~CMeshField()
{

}

//=============================================================================
// ���[�h����							(public)	*** CMeshField ***
//=============================================================================
HRESULT CMeshField::Load(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (m_pTexture == NULL)
	{
		// �e�N�X�`���̐���
		D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_1, &m_pTexture);
	}

	return S_OK;
}

//=============================================================================
// �A�����[�h����								(public)	*** CMeshField ***
//=============================================================================
void CMeshField::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �m�ۏ���											(public)	*** CMeshField ***
//=============================================================================
CMeshField *CMeshField::Create(MESHTYPE meshType, D3DXVECTOR3 num, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, MESHTEX meshTex)
{
	CMeshField *pMeshField = NULL;				// �V�[���|�C���^

	if (pMeshField == NULL)
	{// NULL�̏ꍇ
		pMeshField = new CMeshField;			// �V�[���������m��
	}

	if (pMeshField != NULL)
	{// NULL�ȊO�̏ꍇ
	 // �����������i�ʒu�A�傫���A�F�AUV�j
		pMeshField->Init(meshType, num, pos, rot, size, col, TexUV, meshTex);
		pMeshField->BindTexture(m_pTexture);	// �e�N�X�`���ݒ�
	}

	return pMeshField;
}

//=============================================================================
// ����������										(public)	*** CMeshField ***
//=============================================================================
HRESULT CMeshField::Init(MESHTYPE meshType, D3DXVECTOR3 num, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, MESHTEX meshTex)
{
	CSceneMesh::SetInitAll(meshType, num, pos, rot, size, col, D3DXVECTOR2(TexUV.x, TexUV.y), meshTex);
	CSceneMesh::Init();		// ����������

	CWall::Create(D3DXVECTOR3(pos.x - size.x, -150.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(size.z, 150.0f, 0.0f));
	CWall::Create(D3DXVECTOR3(pos.x + size.x, -150.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(size.z, 150.0f, 0.0f));

	return S_OK;
}

//=============================================================================
// �I������											(public)	*** CMeshField ***
//=============================================================================
void CMeshField::Uninit(void)
{
//	CGame::SetMeshField(this);
	CSceneMesh::Uninit();						// �I������
}

//=============================================================================
// �X�V����											(public)	*** CMeshField ***
//=============================================================================
void CMeshField::Update(void)
{
	/*D3DXVECTOR3 posVDest = CManager::GetCamera()->GetPosVDest();	// ���_�擾
	D3DXVECTOR3 pos = CSceneMesh::Getpos();
	D3DXVECTOR3 size = CSceneMesh::Getsize();
	if (pos.x + size.x < posVDest.x - 500.0f)
	{
		Uninit();
	}*/
}

//=============================================================================
// �`�揈��											(public)	*** CMeshField ***
//=============================================================================
void CMeshField::Draw(void)
{
	CSceneMesh::Draw();						// �`�揈��
}