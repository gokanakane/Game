//=============================================================================
//
// �~�j�}�b�v���� [minimap.h]
// Author : Shun Yokomichi
//
//=============================================================================
#ifndef _MINIMAP_H_
#define _MINIMAP_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include	"scene2d.h"		// �V�[��2D

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_MINI	(2)		// �ő吔

//*****************************************************************************
// �N���X��`	(CScene2D�̔h��)
//*****************************************************************************
class CMinimap : public CScene2D
{
public:
	typedef enum
	{
		TYPE_NONE = 0,		// �����Ȃ����
		TYPE_PLAYER,		// �v���C���[
		TYPE_ENEMY,			// �G
		TYPE_MAX
	}TYPE;		// �摜�̃^�C�v

	CMinimap();									// �R���X�g���N�^
	~CMinimap();								// �f�X�g���N�^

	static HRESULT Load(void);					// ���[�h
	static void Unload(void);					// �A�����[�h

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TYPE type, int nTex);		// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

	static CMinimap *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TYPE type, int nTex);		// ����

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_MINI];		// �e�N�X�`�����ւ̃|�C���^
	TYPE m_Type;
	float m_fPosX;
};

#endif // !_MINIMAP_H_

