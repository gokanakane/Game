//=============================================================================
//
// �A�C�e���̎擾���\�L���� [itemicon.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _ITEMICON_H_
#define _ITEMICON_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"			// ���C��
#include "scene3d.h"		// �V�[��
#include "player.h"			// �v���C���[

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ITEMICON_MAXTYPE (4)	// �A�C�e���̎�ލő吔

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CItemicon : public CScene3D
{// �V�[��3D�i�e�FCScene�j
public:
	typedef enum
	{
		ITEMICON_SPEEDUP = 0,		//	�X�s�[�hUP�A�C�e��
		ITEMICON_LIFEUP,			//	�񕜃A�C�e��
		ITEMICON_SCOREUP,			//	�X�R�A���Z�A�C�e��
		ITEMICON_SCOREUP2,			//	�X�R�A���Z2�A�C�e��
		ITEMICON_MAX
	}ITEMICONTYPE;

	CItemicon();														// �R���X�g���N�^
	~CItemicon();														// �f�X�g���N�^
																		// ����������
	HRESULT Init(D3DXVECTOR3 pos,D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, int itemType);
	void Uninit(void);													// �I������
	void Update(void);													// �X�V����
	void Draw(void);													// �`�揈��
																		// ����
	static CItemicon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, int itemType);
	static HRESULT Load(void);											// �e�N�X�`���̓ǂݍ���
	static void Unload(void);													// �j��
private:
	static LPDIRECT3DTEXTURE9		m_pTexture[ITEMICON_MAXTYPE];				// �e�N�X�`�����ւ̃|�C���^
	ITEMICONTYPE			m_ItemIconType;								// �A�C�e���̎��
	D3DXMATRIX				m_mtxWorld;									// ���[���h�}�g���b�N�X
	D3DXVECTOR2				m_TexUV;									// UV
	D3DXVECTOR3				m_move;										// ����
	D3DXVECTOR3				m_posold;									// �ߋ��̈ʒu

protected:

};

#endif