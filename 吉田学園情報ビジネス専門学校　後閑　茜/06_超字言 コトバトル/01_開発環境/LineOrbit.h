//=============================================================================
//
// �O�ՃN���X [LineOrbit.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _LINE_ORBIT_H_
#define _LINE_ORBIT_H_

#include "scene.h"

//=============================================================================
// �N���X�̒�`
//=============================================================================

//--------------------------------------------------------------
//�O�ՃN���X(CLineOrbit)
//--------------------------------------------------------------
class CLineOrbit : public CScene
{
public:
	CLineOrbit();
	CLineOrbit(int pri = 1, OBJTYPE type = OBJTYPE_ORBIT);

	~CLineOrbit();

	static CLineOrbit* Create(void);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fScale, D3DXMATRIX* parent, LPCSTR	Tag,
		D3DXCOLOR col,unsigned int nMeshNum, unsigned int nPointCreateTime);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetParent(D3DXMATRIX* parent) { m_Parent = parent; };
private:
	LPDIRECT3DTEXTURE9		m_pTexture;									// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;									// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;									// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX				m_mtxWorld;

	D3DXVECTOR3 m_pos;					//���W
	D3DXVECTOR3 m_offset;
	D3DXVECTOR3 m_rot;					//�p�x
	float m_fScale;				//�傫��(�}�g���b�N�X�ɂ͊|�����A�O�Ղ̃T�C�Y�Z�o�Ɏg��)
	D3DXMATRIX* m_Parent;				//�e

	D3DXCOLOR m_color;					//�F

	int m_nVtxNum;
	int m_nIdxNum;

	int m_nPolygonNum;

	unsigned int m_nMeshNum;			//�O�Ղ��`������_�̏����
	unsigned int m_nPointCreateTime;	//�V�����_�𐶐�����܂ł̎���

	D3DXVECTOR3* m_apMesh;	//
};

#endif // !_LINE_ORBIT_H_
