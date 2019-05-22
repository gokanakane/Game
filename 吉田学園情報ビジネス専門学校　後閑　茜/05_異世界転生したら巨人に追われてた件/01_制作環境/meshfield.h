//=============================================================================
//
// ���b�V���t�B�[���h���� [meshfield.h]
// Author : Eisuke Sakagawa
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

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
class CMeshField : public CSceneMesh
{// ���b�V���t�B�[���h�i�e�FCSceneMesh�j
public:
	CMeshField();									// �R���X�g���N�^
	~CMeshField();									// �f�X�g���N�^

	static HRESULT Load(void);						// ���[�h
	static void Unload(void);						// �A�����[�h
	static CMeshField *Create(MESHTYPE meshType, D3DXVECTOR3 num, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, MESHTEX meshTex);		// ����

	HRESULT Init(MESHTYPE meshType, D3DXVECTOR3 num, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, MESHTEX meshTex);					// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	void Draw(void);								// �`�揈��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`�����ւ̃|�C���^

protected:

};

#endif