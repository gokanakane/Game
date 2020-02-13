//=============================================================================
//
// �e�̏��� [Shadow.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"
#include "scene.h"
#include "scene3D.h"

//=====================================================================
// �}�N����`
//=====================================================================
#define MAX_SHADOW	(2)

//*********************************************************************
//�e�̃N���X�̒�`
//*********************************************************************
class CShadow : public  CScene3D//�h���N���X
{
public:
	CShadow();
	~CShadow();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static CShadow *Create(D3DXVECTOR3 pos, float fWidth, float fDepth);
	//�����o�ϐ�
private:
	LPDIRECT3DVERTEXBUFFER9				m_pVtxBuff = NULL;	//���_�o�b�t�@�ւ̃|�C���^
	float								m_Height;
	D3DXVECTOR3							m_pos;							//�ʒu
	D3DXVECTOR3							m_rot;							//����
	D3DXCOLOR							m_col;
	D3DXMATRIX							m_mtxWorld;						//���[���h�}�g���b�N�X
	float								m_fWidth, m_fDepth;				//���@���s��
};

#endif