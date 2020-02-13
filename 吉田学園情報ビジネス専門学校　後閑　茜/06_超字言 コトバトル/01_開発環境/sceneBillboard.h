//=============================================================================
//
// �r���{�[�h�̏��� [billboard.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"
#include "scene.h"

//*********************************************************************
//�r���{�[�h�N���X�̒�`
//*********************************************************************
class CSceneBillBoard : public CScene //�h���N���X
{
public:
	CSceneBillBoard();
	~CSceneBillBoard();
	HRESULT Init(void) { return S_OK; };
	HRESULT Init(D3DXVECTOR3 pos);

	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	void SetBillboard(D3DXVECTOR3 pos, float fHeight, float fWidth);
	static CSceneBillBoard *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, LPCSTR Tag);
	void BindTexture(LPDIRECT3DTEXTURE9	Texture);	//TEXTURE�����蓖�Ă�
	void BindTexture(LPCSTR TexTag);
	D3DXVECTOR3 GetPos(void);
	void SetCol(D3DXCOLOR col);
	LPDIRECT3DVERTEXBUFFER9 GetVtx(void);
	void SetTexture(int PatternAnim, int X, int Y, int nNum);
	void SetTexture(D3DXVECTOR2 minRect,D3DXVECTOR2 maxRect);

	void SetColFlag(bool bFlag) { m_bColChange = bFlag; }
	bool GetColFlag(void) { return m_bColChange; }
	D3DXCOLOR GetCol(void) { return m_col; }
	float GetSize(int nNum) { if (nNum == 0) { return m_fWidth; } else if (nNum == 1) { return m_fHeight; } return 0.0f; }

private:
	//�����o�ϐ�
	D3DXCOLOR				m_col;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;			//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;			// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3				m_pos;						// �|���S���̈ʒu
	D3DXVECTOR3				m_move;						// �ړ���
	D3DXVECTOR3				m_size;						// �T�C�Y
	float					m_fWidth, m_fHeight;		// ��,����
	D3DXMATRIX				m_mtrxWorld;				// ���[���h�}�g���b�N�X
	bool					m_bColChange;

};

#endif