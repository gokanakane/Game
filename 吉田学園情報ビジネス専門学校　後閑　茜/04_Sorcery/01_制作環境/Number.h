//=============================================================================
//
// �V�[��2D�|���S������ [scene2d.h]
// Author : 
//
//=============================================================================
#ifndef _NUBER_H
#define _NUBER_H

#include "main.h"
#include "scene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NUMBER "data\\TEXTURE\\UI\\Number000.png"

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X�i�h���j
//*****************************************************************************
class CNumber
{
public:
	CNumber();
	~CNumber();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CNumber*Create(void);
	static HRESULT Load(void);
	static void UnLoad(void);
	void SetNumber(int nNumber);
	void SetPos(D3DXVECTOR3 pos, int nCnt, float SizeX, float SizeY);
	void SetCol(D3DXCOLOR col);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
};

#endif
