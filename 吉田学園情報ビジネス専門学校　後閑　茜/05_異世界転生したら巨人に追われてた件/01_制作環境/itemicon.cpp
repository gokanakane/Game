//=============================================================================
//
// �A�C�e���̎擾���\�L���� [itemicon.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene3D.h"		// �V�[��3D
#include "manager.h"		// �}�l�[�W���[
#include "renderer.h"		// �����_���[
#include "input.h"			// ����
#include "font.h"			// �t�H���g
#include "itemicon.h"		// �A�C�e��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ICON_DELCNT (4)		//	�A�C�R���������鎞��
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CItemicon::m_pTexture[ITEMICON_MAXTYPE] = {};

//=============================================================================
// �R���X�g���N�^								(public)	*** CScene3D ***
//=============================================================================
CItemicon::CItemicon() : CScene3D(CScene::PRIORITY_4, CScene::OBJTYPE_ITEMICON)
{
	m_ItemIconType = {};
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^									(public)	*** CScene3D ***
//=============================================================================
CItemicon::~CItemicon()
{
}

//=============================================================================
//	�A�C�e���̐���
//=============================================================================
CItemicon *CItemicon::Create(D3DXVECTOR3 pos,  D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, int itemType)
{
	CItemicon *pItemIcon = {};

	if (pItemIcon == NULL)
	{//	�A�C�e���̐���
		pItemIcon = new CItemicon;
		if (pItemIcon != NULL)
		{//�A�C�e���̏�����
			pItemIcon->Init(pos,rot, size, col, TexUV, itemType);
		}
	}
	return pItemIcon;
}

//=============================================================================
// ����������									(public)	*** CScene3D ***
//=============================================================================
HRESULT CItemicon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, int itemType)
{
	CScene3D::SetInitAll(pos, rot, size, col, TexUV, CScene3D::SCENE3DTYPE_BILLBOARD);
	CScene3D::Init();
	CScene3D::BindTexture(m_pTexture[itemType]);

	return S_OK;
}

//=============================================================================
// �I������										(public)	*** CScene3D ***
//=============================================================================
void CItemicon::Uninit(void)
{
	CScene3D::Uninit();
}

//=============================================================================
// �X�V����										(public)	*** CScene3D ***
//=============================================================================
void CItemicon::Update(void)
{
	D3DXVECTOR3 pos = CScene3D::Getpos();
	m_posold = pos;		//	�ʒu�̕ۑ�

	m_move.y += 0.075f;
	pos += m_move;
	CScene3D::Setpos(pos);
	CScene3D::Setcol(CScene3D::Getcol() - D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.015f));
	CScene3D::Update();

	if (m_move.y > ICON_DELCNT)
	{
		Uninit();
	}
}

//=============================================================================
// �`�揈��										(public)	*** CScene3D ***
//=============================================================================
void CItemicon::Draw(void)
{
	CScene3D::Draw();
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CItemicon::Load(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\itemicon\\itemiconspeed.png", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\itemicon\\itemiconlife.png", &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item\\coin.png", &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item\\coin2.png", &m_pTexture[3]);

	return S_OK;
}

//=============================================================================
// �A�����[�h����								(public)	*** CItem ***
//=============================================================================
void CItemicon::Unload(void)
{
	for (int nCount = 0; nCount < ITEMICON_MAXTYPE; nCount++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}