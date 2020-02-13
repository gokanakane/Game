//=============================================================================
//
// �v���C���[�̑̃p�[�c���� [CharaParts.h]
// Author : Kodama Yuto
//
//	�N���X�̊T�v
//
//=============================================================================
#ifndef _CHARA_PARTS_H_
#define _CHARA_PARTS_H_

#include "main.h"
#include "UtilityMath.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define DIFFUSE_ALPHA_FLAME (30)		//m_fDiffuseAlpha��J�ڂ�����܂ł̎���

//=============================================================================
//	�N���X��`
//=============================================================================
class CCharaParts
{
public:
	CCharaParts();
	~CCharaParts();

	void Set(LPCSTR ModelFile, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXMATRIX* pParent);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos) { m_Pos = pos; };
	D3DXVECTOR3 GetPosition(void) { return m_Pos; };

	void SetRotation(D3DXVECTOR3 rot) { m_Rot = rot; };
	D3DXVECTOR3 GetRotation(void) { return m_Rot; };

	void SetScale(D3DXVECTOR3 scale) { m_Scale = scale; };
	void SetScale(float fSize) { m_Scale = D3DXVECTOR3(fSize,fSize,fSize); };
	D3DXVECTOR3 GetScale(void) { return m_Scale; };

	void SetParent(D3DXMATRIX* pParent) { m_pParent = pParent;};
	D3DXMATRIX* GetMatrix(void) { return &m_mtxWorld; };

	D3DXVECTOR3 GetWorldPosition(void) { return m_WorldPosition; };

	void SetDrawFlag(bool bFlag) { m_bDrawFlag = bFlag; };
	bool GetDrawFlag(void) { return m_bDrawFlag; };

	void BindTexture(LPCSTR Tag);

	void SetAlpha(float& fAlpha, int nCount = 0);
	float GetAlpha(void) { return m_fDiffuseAlpha; };
private:
	LPDIRECT3DTEXTURE9     m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
	LPD3DXMESH				m_pMesh;			// ���b�V�����i���_���j�ւ̃|�C���^
	LPD3DXBUFFER			m_pBuffMat;			// �}�e���A�����ւ̃|�C���^
	DWORD					m_nNumMat;			// �}�e���A�����̐�
	D3DXMATRIX				m_mtxWorld;			// ���[���h�}�g���b�N�X

	D3DXVECTOR3 m_Pos;		//�ʒu(�e���猩�����Έʒu)
	D3DXVECTOR3 m_Rot;		//�p�x(�e���猩�����Ίp�x)
	D3DXVECTOR3 m_Scale;	//�傫��
	D3DXMATRIX* m_pParent;	//�e�}�g���b�N�X

	float m_fDiffuseAlpha;	//���_�F�̃��l
	float m_fDestAlpha;		//m_fDiffuseAlpha�����炩�ɑJ�ڂ����邽�߂̖ڕW�l
	float m_fOldAlpha;		//�J�ڂ����邽�߂ɕێ�����ߋ��̒l

	D3DXVECTOR3 m_WorldPosition;	//���[���h���W�ł̈ʒu(m_mtxWorld������o��)
	bool m_bDrawFlag;				//�`�悷�邩�̃t���O

	int m_nCount;
};
#endif // !_CHARA_PARTS_H_
