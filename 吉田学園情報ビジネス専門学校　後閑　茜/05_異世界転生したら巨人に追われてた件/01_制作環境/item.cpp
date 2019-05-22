//=============================================================================
//
// �A�C�e������ [item.cpp]
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
#include "camera.h"			// �J����
#include "item.h"			// �A�C�e��
#include "itemicon.h"		// �A�C�e���̃A�C�R��
#include "life.h"			// �̗͕\��
#include "score.h"			// �X�R�A
#include "effect.h"			// �G�t�F�N�g
#include "sound.h"			// �T�E���h

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
LPDIRECT3DTEXTURE9 CItem::m_pTexture[ITEM_MAXTYPE] = {};

//=============================================================================
// �R���X�g���N�^								(public)	*** CItem ***
//=============================================================================
CItem::CItem() : CScene3D(CScene::PRIORITY_4, CScene::OBJTYPE_ITEM)
{
	m_ItemType = {};
}

//=============================================================================
// �f�X�g���N�^									(public)	*** CItem ***
//=============================================================================
CItem::~CItem()
{
}

//=============================================================================
//	�A�C�e���̐���
//=============================================================================
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, int itemType)
{
	CItem *pItem = {};

	if (pItem == NULL)
	{//	�A�C�e���̐���
		pItem = new CItem;
		if (pItem != NULL)
		{//�A�C�e���̏�����
			pItem->Init(pos, rot, size, col, TexUV, itemType);
		}
	}
	return pItem;
}

//=============================================================================
// ����������									(public)	*** CItem ***
//=============================================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, int itemType)
{
	CScene3D::SetInitAll(pos, rot, size, col, TexUV, CScene3D::SCENE3DTYPE_BILLBOARD);
	CScene3D::Init();
	CScene3D::BindTexture(m_pTexture[itemType]);
	m_ItemType = (ITEMTYPE)itemType;

	m_nCntAnim = 0;
	m_nPatternAnim = 0;
	m_Anim = false;
	return S_OK;
}

//=============================================================================
// �I������										(public)	*** CItem ***
//=============================================================================
void CItem::Uninit(void)
{
	CScene3D::Uninit();
}

//=============================================================================
// �X�V����										(public)	*** CItem ***
//=============================================================================
void CItem::Update(void)
{
	D3DXVECTOR3 posVDest = CManager::GetCamera()->GetPosVDest();	// ���_�擾
	D3DXVECTOR3 pos = CScene3D::Getpos();
	D3DXVECTOR3 size = CScene3D::Getsize();

	/* �A�j���[�V�������� */
	m_nCntAnim++;
	if (m_nCntAnim % 10 == 0)
	{
		if (m_Anim == false)
		{
			m_nPatternAnim++;
			if (m_nPatternAnim >= 5)
			{
				m_Anim = true;
			}
		}
		else
		{
			m_nPatternAnim--;
			if (m_nPatternAnim <= 0)
			{
				m_Anim = false;
			}
		}
	}
	SetTex(5, m_nPatternAnim, D3DXVECTOR2(0.2f, 0.25f), D3DXVECTOR2(1.0f, 1.0f));

	if (pos.x + size.x < posVDest.x - 500.0f)
	{
		Uninit();
	}

}

//=============================================================================
// �`�揈��										(public)	*** CItem ***
//=============================================================================
void CItem::Draw(void)
{
	CScene3D::Draw();
}
//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CItem::Load(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item\\speedup.png", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item\\lifeup.png", &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item\\Treasure000.png", &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item\\Treasure002.png", &m_pTexture[3]);

	return S_OK;
}
//=============================================================================
// �A�����[�h����								(public)	*** CItem ***
//=============================================================================
void CItem::Unload(void)
{
	for (int nCount = 0; nCount < ITEM_MAXTYPE; nCount++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}
//==============================================================================================================================
// �A�C�e���̂����蔻��̍쐬
//==============================================================================================================================
bool  CItem::CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{
	CSound *pSound = CManager::GetSound();

	bool bHit = false;
	D3DXVECTOR3 pos = CScene3D::Getpos();
	D3DXVECTOR3 size = CScene3D::Getsize();
	if (pos.x + (size.x / 2) >= pPos->x + sizeMin.x &&		// ��
		pos.x - (size.x / 2) <= pPos->x + sizeMax.x &&		// ��
		pos.z + (size.z / 2) >= pPos->z + sizeMin.z &&		// �E
		pos.z - (size.z / 2) <= pPos->z + sizeMax.z &&		// ��
		pos.y + (size.y/ 2) >= pPos->y + sizeMin.y &&		// ��O
		pos.y - (size.y*1.5) <= pPos->y + sizeMax.y)			// ��
	{// �A�C�e���ɂԂ������ꍇ

		if (m_ItemType == TYPE_SPEEDUP)
		{//	�X�s�[�h�A�C�e����������
			bHit = true;
			Uninit();
			CEffect::Create(pos, 3, 6);//�@�e�N�X�`���@�e�L�X�g
			CItemicon::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), TYPE_SPEEDUP);
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE004);
		}
		else if (m_ItemType == TYPE_LIFEUP)
		{//	�񕜃A�C�e����������
			CLife::Recovery();
			Uninit();
			CEffect::Create(pos, 3, 8);//�@�e�N�X�`���@�e�L�X�g
			CItemicon::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), TYPE_LIFEUP);
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE007);

		}
		else if (m_ItemType == TYPE_SCOREUP)
		{//	�X�R�A���Z�A�C�e����������
			CScore::AddScore(200);
			Uninit();
			CEffect::Create(pos, 3, 7);//�@�e�N�X�`���@�e�L�X�g
			CItemicon::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), TYPE_SCOREUP);
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE006);
		}
		else if (m_ItemType == TYPE_SCOREUP2)
		{//	�X�R�A���Z�A�C�e����������
			CScore::AddScore(500);
			Uninit();
			CEffect::Create(pos, 3, 7);//�@�e�N�X�`���@�e�L�X�g
			CItemicon::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), TYPE_SCOREUP2);
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE006);
		}
	}

	return bHit;
}