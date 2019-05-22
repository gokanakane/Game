//=============================================================================
//
// ���b�V�����o�[���� [meshriver.h]
// Author : Eisuke Sakagawa
//
//=============================================================================
#ifndef _MESHRIVER_H_
#define _MESHRIVER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		// ���C��
#include "Scenemesh.h"	// �V�[�����b�V��

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CMeshRiver : public CSceneMesh
{// ���b�V���t�B�[���h�i�e�FCSceneMesh�j
public:
	typedef enum
	{
		TEXTURE_DORO = 0,
		TEXTURE_RIVER,
		TEXTURE_MAX
	}TEXTURE;

	CMeshRiver();									// �R���X�g���N�^
	~CMeshRiver();									// �f�X�g���N�^

	static HRESULT Load(void);						// ���[�h
	static void Unload(void);						// �A�����[�h
	static CMeshRiver *Create(MESHTYPE meshType, D3DXVECTOR3 num, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, MESHTEX meshTex, int nNum);		// ����

	HRESULT Init(MESHTYPE meshType, D3DXVECTOR3 num, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, MESHTEX meshTex);					// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	void Draw(void);								// �`�揈��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TEXTURE_MAX];			// �e�N�X�`�����ւ̃|�C���^
	float m_Sinrot;

protected:

};

#endif