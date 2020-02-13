//=============================================================================
//
// �����b�V���N���X [meshSphere.h]
// Author : Kodama Yuto
//
//	�T�v
//	����ɒ��_���Ȃ����|���S���̉�𐶐�����N���X
//	��{�I�ɐe�N���X�Ƃ��Ďg��
//
//	���Ӂ@�����p�Ȃ̂ŒP�̂ł͎g��Ȃ����ƁI�I
//
//=============================================================================
#ifndef _MESH_SPHERE_H_
#define _MESH_SPHERE_H_

#include "scene.h"

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CMeshSphere : public CScene
{
public:
	CMeshSphere();
	CMeshSphere(int pri = 1, OBJTYPE type = OBJTYPE_MESH_SPHERE);
	~CMeshSphere();


	static CMeshSphere* Create(void);

	void Set(D3DXVECTOR3 pos, LPCSTR Tag, int nMeshWidth, int nMeshHeight, D3DXVECTOR3 Size,
		D3DXCOLOR Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3& GetPosition(void) { return m_pos; };
	D3DXVECTOR3& GetRotation(void) { return m_rot; };
	D3DXVECTOR3& GetScale(void) { return m_Size; };

	void SetColor(D3DXCOLOR col) ;

	void SetTexAnim(D3DXVECTOR2 Anim) { m_AnimTexUV = Anim; };
	void SetCntAnimTime(int nTime) { m_nCntTexAnim = nTime; };
private:
	void CreateVertex(LPDIRECT3DDEVICE9 pDev);
	void CreateIndex(LPDIRECT3DDEVICE9 pDev);

	LPDIRECT3DTEXTURE9		m_pTexture;							// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;							// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;							// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX				m_mtxWorld;							// ���[���h�}�g���b�N�X
	D3DXVECTOR3				m_pos;								// �|���S���̈ʒu
	D3DXVECTOR3				m_rot;								// �|���S���̌���
	D3DXCOLOR				m_Color;							// �J���[

	int						m_nVtxNum;							// ���_��
	int						m_nIdxNum;							// �C���f�b�N�X��
	int						m_nPolygonNum;						// �|���S����

	int						m_nMeshWidth;						// ���b�V���̕�����(X��)
	int						m_nMeshHeight;						// ���b�V���̕�����(Y��)
	D3DXVECTOR3				m_Size;								// �T�C�Y

	D3DXVECTOR2				m_AnimTexUV;					//�e�N�X�`���A�j���[�V�����p
	int						m_nCntTexAnim;					//�e�N�X�`�����W�X�V�܂ł̑ҋ@����

};

#endif // !_MESH_SPHERE_H_
