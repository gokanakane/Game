//=============================================================================
//
// 3D�|���S������ [scene3D.h]
// Author : �ڍ� ������
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GROUND_TEXTURE_NAME			"data\\TEXTURE\\field.jpg"	// �n�ʂ̃e�N�X�`����
#define GROUND_SIZE					(130.0f)							// �n�ʂ̑傫��
#define NUM_VTX						(4)								// ���_�̐�
//========================================
// �N���X�̒�`
//========================================
//=====================
// �I�u�W�F�N�g�N���X
//=====================
class CScene3D : public CScene
{
public:
	CScene3D(int nPriority = 3, OBJTYPE objType = OBJTYPE_SCENE3D);											// �R���X�g���N�^
	~CScene3D();										// �f�X�g���N�^

	typedef enum
	{// �V�[��3D�^�C�v
		SCENE3DTYPE_NORMAL = 0,				// �ʏ�
		SCENE3DTYPE_BILLBOARD,				// �r���{�[�h
		SCENE3DTYPE_BILLEFFECT,				// �r���{�[�h�G�t�F�N�g�p���Z��������
		SCENE3DTYPE_ADDSYNTHESIS,			// ���Z�����̂�
		SCENE3DTYPE_SUBSYNTHESIS,			// ���Z�����̂�
		SCENE3DTYPE_MAX
	}SCENE3DTYPE;

	HRESULT Init(void);							// 3D�I�u�W�F�N�g����������
	void Uninit(void);							// 3D�I�u�W�F�N�g�I������
	void Update(void);							// 3D�I�u�W�F�N�g�X�V����
	void Draw(void);							// 3D�I�u�W�F�N�g�`�揈��

	void SetInitAll(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, SCENE3DTYPE scene3dType)
	{// �����l�ݒ�
		m_pos = pos;					// �ʒu
		m_rot = rot;					// ����
		m_size = size;					// �傫��
		m_col = col;					// �F
		m_TexUV = TexUV;				// �e�N�X�`��UV
		m_scene3dType = scene3dType;			// �V�[��3D�^�C�v
	}


	D3DXVECTOR3 GetNor(int nIdx);				// �@�����擾
	void SetNor(D3DXVECTOR3 nor);				// �@����ݒ�

	float GetHeight(D3DXVECTOR3 pos);			// �����̎擾

	static CScene3D *Create(D3DXVECTOR3 pos, LPCSTR Tag);			// �I�u�W�F�N�g�̐���
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void BindTexture(LPCSTR TexTag);
	void SetSize(float fHeight,float fWidth);
	void SetSizeY(float fHeight, float fWidth);
	void SetRot(D3DXVECTOR3 rot);
	void SetAnimation(int m_PatternAnim, float fUV_U, float fUV_V);
	void SetAnimationTex(D3DXVECTOR2 texmin, D3DXVECTOR2 texmax);
	void SetColor(D3DXCOLOR col);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetTexUV(D3DXVECTOR2 TexUV) { m_TexUV = TexUV; }
	void SetAlphaTest(bool bTest) { m_bAlphaTest = bTest; }
	void SetLightEffect(bool bLight) { m_bLigntEffect = bLight; }
	void SetScene3DType(SCENE3DTYPE type) { m_scene3dType = type; };
	void SetBulletUI(D3DXVECTOR3 size, D3DXVECTOR3 rot, int nType);	// �e��UI�\���p

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	float GetSizeY(void) { return m_size.y; }
	float GetSizeX(void) { return m_size.x; }
	D3DXCOLOR Getcol(void) { return m_col; }			// �F�擾


private:
	LPDIRECT3DTEXTURE9		m_pTexture;					// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX				m_mtxWorld;					// ���[���h�}�g���b�N�X
	D3DXVECTOR3				m_Nor;						// �@��
	D3DXVECTOR3				m_aVec[NUM_VTX];			// �x�N�g��
	D3DXVECTOR3				m_pos;						// �|���S���̈ʒu
	D3DXVECTOR3				m_aPos[NUM_VTX];			// ���_�̈ʒu
	D3DXVECTOR3				m_rot;						// ������x�N�g��
	D3DXCOLOR               m_col;
	D3DXVECTOR3				m_size;						// �傫��
	D3DXVECTOR2				m_TexUV;
	SCENE3DTYPE m_scene3dType;					// �V�[��3D�^�C�v
	bool m_bAlphaTest;									//���e�X�g�̉�
	bool m_bLigntEffect;								//���C�g�̉e���̉�

};

#endif