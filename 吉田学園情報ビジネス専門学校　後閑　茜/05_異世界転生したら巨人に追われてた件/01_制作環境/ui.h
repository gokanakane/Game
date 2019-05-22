//*****************************************************************************
//
//				�|���S���̏���[polygon.h]
//				Auther : Shun Yokomichi
//
//*****************************************************************************
#ifndef _UI_H_
#define _UI_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2D.h"

//*****************************************************************************
//		�}�N����`
//*****************************************************************************
#define MAX_POLYGON			(5)		// Texture�̍ő吔

//*****************************************************************************
//		�N���X��`(�|���S��)
//*****************************************************************************
class CUiPolygon : public CScene2D
{
public:
	CUiPolygon();
	~CUiPolygon();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, int nTexNum);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CUiPolygon * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, int nTexNum);
	static HRESULT Load(void);	//	�ǂݍ��ފ֐�(�e�N�X�`��)
	static void Unload(void);	// �J������֐�(�e�N�X�`��)
	static void SetA(float colA) { m_colA = colA; };

private:
	int m_nTexNum;

	// �ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_POLYGON];
	static float m_colA;
};

#endif
