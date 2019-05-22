//*****************************************************************************
//
//				���C�t�̏���[life.h]
//				Auther : Shun Yokomichi
//
//*****************************************************************************
#ifndef _LIFE_H_
#define _LIFE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"
#include "scene2D.h"

//*****************************************************************************
//		�}�N����`
//*****************************************************************************
#define		MAX_LIFE		(3)		// ���C�t�̍ő吔

//*****************************************************************************
//		�N���X��`(���C�t)
//*****************************************************************************
class CLife : public CScene
{
public:
	CLife();
	~CLife();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//	�ÓI�����o�֐�
	static HRESULT Load(void);	//	�ǂݍ��ފ֐�(�e�N�X�`��)
	static void Unload(void);	// �J������֐�(�e�N�X�`��)
	static CLife * Create();
	static void HitDamage();		// �_���[�W�p
	static void Recovery();			// �񕜗p
	static int GetLife() { int nLife = 0; for (int nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++) { if (m_bUse[nCntLife]) { nLife++; } } return nLife; };			// �񕜗p

private:
	static int m_nLife;

	// �ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;	// ���L�e�N�X�`���ւ̃|�C���^
	static bool m_bUse[MAX_LIFE];
	CScene2D *m_apScene[MAX_LIFE];		// CScene2D�̃|�C���^

};

#endif
