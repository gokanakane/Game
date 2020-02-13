//=============================================================================
//
// �V�[������ [scene2D.h]
// Author : �ڍ� ������
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_NAME		"data/TEXTURE/player000.png"	// �v���C���[�̃e�N�X�`����
#define BULLET_NAME		"data/TEXTURE/bullet000.png"	// �e�̃e�N�X�`����
#define MAX_TEX_TYPE	(2)								// �e�N�X�`���̎��

//========================================
// �N���X�̒�`
//========================================
//=====================
// �I�u�W�F�N�g�N���X
//=====================
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority = 3, OBJTYPE objType = OBJTYPE_SCENE2D);											// �R���X�g���N�^
	~CScene2D();										// �f�X�g���N�^

	HRESULT Init(void) { return S_OK; };
	virtual HRESULT Init(D3DXVECTOR3 pos);				// 2D�I�u�W�F�N�g����������

	virtual void Uninit(void);							// 2D�I�u�W�F�N�g�I������
	virtual void Update(void);							// 2D�I�u�W�F�N�g�X�V����
	virtual void Draw(void);							// 2D�I�u�W�F�N�g�`�揈��

	D3DXVECTOR3 GetPosition(void);						// �ʒu���擾
	void SetPosition(D3DXVECTOR3 pos);					// �ʒu��ݒ�

	static CScene2D *Create(D3DXVECTOR3 pos, LPCSTR Tag, int nPriority = 3);				// �I�u�W�F�N�g�̐���
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	void BindTexture(LPCSTR TexTag);

	void SetPos(D3DXVECTOR3 pos, float fSpin, float fScale, D3DXCOLOR col);
	void SetRot(float fSpin);
	void SetWidthHeight(float fWidth, float fHeight);
	void SetRIghtLeft(float fRight, float fLeft);
	void SetCol(D3DXCOLOR col);
	D3DXCOLOR GetCol(void) { return m_Col; }
	void SetTex(D3DXVECTOR2 texmin, D3DXVECTOR2 texmax);
	LPDIRECT3DVERTEXBUFFER9 GetBuff(void) { return m_pVtxBuff; }
	void SetBuff(LPDIRECT3DVERTEXBUFFER9 pVtxBuff) { m_pVtxBuff = pVtxBuff; }
	void SetbDraw(bool bDraw) { m_bDraw = bDraw; };
	void SetAnimation(int m_PatternAnim, float fUV_U, float fUV_V);
	void SetScale(float fScale);
	void SetScene2DLeftCenter(D3DXVECTOR3 pos, float sizeW, float sizeH);

	float GetSize(int nNum) { if (nNum == 0) { return m_fWidth; } else { return m_fHeight; } };
	LPDIRECT3DTEXTURE9 GetTexture(void) { return m_pTexture; };

	bool GetbDraw(void) { return m_bDraw; }
	D3DXVECTOR2 GetTex(int nNum) { return m_Tex[nNum]; };

	float GetRot(void) { return m_fSpin; }
	void SetAdd(bool bAdd) { m_bAddition = bAdd; }		//���Z�����t���O
private:
	LPDIRECT3DTEXTURE9		m_pTexture;					// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// ���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3				m_Pos;						// �|���S���̈ʒu
	float					m_fSpin;				// ��]
	float					m_fWidth, m_fHeight;	// ������
	float					m_fRight, m_fLeft;		// ���E�̒���
	float					m_fLength;				// �傫��
	float					m_fScale;				// �傫���ύX
	D3DXCOLOR				m_Col;
	bool					m_bDraw;
	bool					m_bAddition;					//���Z�����ɂ��邩�ۂ��̃t���O
	D3DXVECTOR2				m_Tex[2];				// �e�X�N�`���̍��W�m��					
};
#endif