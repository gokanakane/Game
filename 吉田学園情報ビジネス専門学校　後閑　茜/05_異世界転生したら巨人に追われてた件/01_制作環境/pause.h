//*****************************************************************************
//
//				�|�[�Y�̏���[pause.h]
//				Auther : Shun Yokomichi
//
//*****************************************************************************
#ifndef _PAUSE_H_
#define _PAUSE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScene2D;				// �V�[��2D
class CPauseBg;				// �|�[�Y�̔w�i
class CPress;				//�@�{�^��

//*****************************************************************************
//		�}�N����`
//*****************************************************************************
#define POLYGON_PAUSE	(3)		// �|�[�Y��texture��
#define POLYGON_PRESS	(5)

//*****************************************************************************
//		�N���X��`(�|�[�Y)
//*****************************************************************************
class CPause
{
public:
	CPause();
	~CPause();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 UV);		// ������
	void Uninit(void);					// �I��
	void Update();						// �X�V
	void Draw(void);					// �`��
	
	// �ÓI�����o�֐�
	static CPause *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 UV);	// ����
	static HRESULT Load(void);				// �ǂݍ���
	static void Unload(void);				// texture�j��
	static void SetPause(bool bPause) { m_bPause = bPause; };
	static bool GetPause(void) { return m_bPause; };

private:
	int m_nNum;								// �ԍ�
	float m_fColA;							//�����x
	CScene2D *m_apScene2D[POLYGON_PAUSE];
	CPauseBg *m_pPauseBg;
	CPress   *m_pPress[POLYGON_PRESS];

	// �ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture[POLYGON_PAUSE];
	static bool				  m_bPause;
};

#endif

