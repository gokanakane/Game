//=============================================================================
//
// ���UI���� [avoidui.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _AVOIDUI_H_
#define _AVOIDUI_H_

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
class CAvoidUi : public CScene3D
{// �V�[��3D�i�e�FCScene�j
public:

	CAvoidUi();															// �R���X�g���N�^
	~CAvoidUi();														// �f�X�g���N�^
																		// ����������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV);
	void Uninit(void);													// �I������
	void Update(void);													// �X�V����
	void Draw(void);													// �`�揈��
																		// ����
	static CAvoidUi *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV);		// �����蔻��

	void SetDrawFlag(bool bDraw) { m_bDraw = bDraw; };
	void SetCameraNum(int nCamera) { m_nCamera = nCamera; };
	bool GetVision(int nPlayer) { return m_bVision[nPlayer]; };
	void SetVision(int nPlayer, bool Vision) { m_bVision[nPlayer] = Vision; };

private:
	int m_nCounter;
	bool m_bDraw;
	D3DXVECTOR3 m_move;
	int	m_nCamera;			//�J�����̔ԍ�
	bool m_bVision[4];		//�����Ă��邩�ǂ���
};

#endif