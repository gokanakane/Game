//=============================================================================
//
// �A�C�e������ [item.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		// ���C��
#include "scene3d.h"		// �V�[��
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ITEM_MAXTYPE (4)	// �A�C�e���̎�ލő吔

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CItem : public CScene3D
{// �V�[��3D�i�e�FCScene�j
public:
	typedef enum
	{
		TYPE_SPEEDUP = 0,		//	�X�s�[�hUP�A�C�e��
		TYPE_LIFEUP,			//	�񕜃A�C�e��
		TYPE_SCOREUP,			//	�X�R�A���Z�A�C�e��
		TYPE_SCOREUP2,			//	�X�R�A���Z2�A�C�e��
		TYPE_MAX
	}ITEMTYPE;

	CItem();															// �R���X�g���N�^
	~CItem();															// �f�X�g���N�^
																		// ����������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, int itemType);
	void Uninit(void);													// �I������
	void Update(void);													// �X�V����
	void Draw(void);													// �`�揈��
																		// ����
	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, int itemType);
	static HRESULT Load(void);											// �e�N�X�`���̓ǂݍ���
	static void Unload(void);													// �j��
																				// �����蔻��
	bool CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture[ITEM_MAXTYPE];					// �e�N�X�`�����ւ̃|�C���^
	ITEMTYPE				m_ItemType;									// �A�C�e���̎��
	D3DXMATRIX				m_mtxWorld;									// ���[���h�}�g���b�N�X
	D3DXVECTOR2				m_TexUV;									// U
	CPlayer					*m_pPlayer;									// �v���C���[�̃|�C���^�^

	int m_nCntAnim, m_nPatternAnim;										//�A�j���[�V�����J�E���^�[�E�p�^�[��
	bool m_Anim;														//�A�j���[�V�����p�^�[����������邩������邩
protected:

};

#endif