//=============================================================================
//
// �Ǐ��� [wall.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _WALL_H_
#define _WALL_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		// ���C��
#include "scene3d.h"		// �V�[��
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_WALL_TEX (1)

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CWall : public CScene3D
{// �V�[��3D�i�e�FCScene�j
public:

	CWall();															// �R���X�g���N�^
	~CWall();															// �f�X�g���N�^
																		// ����������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, int nType,int nTexType);
	void Uninit(void);													// �I������
	void Update(void);													// �X�V����
	void Draw(void);													// �`�揈��
																		// ����
	static CWall *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, int nType, int nTexType);		// �����蔻��
	int GetType(void) { return m_nType; }
private:
	int m_nType;
	int m_nAnimCounter;
	int m_nCounter;
	D3DXVECTOR3 m_move;
	int m_TexCounter;

};

#endif