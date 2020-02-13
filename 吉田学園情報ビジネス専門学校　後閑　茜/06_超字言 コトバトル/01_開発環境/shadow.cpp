//=============================================================================
//
// �e�̏��� [polygon.cpp]
// Author : �ڍ�������
//
//=============================================================================
#include "shadow.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "load.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEX_POS_X_INIT			(1.0f)		//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)		//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)		//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)		//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)		//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)		//�e�N�X�`�����WV��

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------

//--------------------------------------------
//�e�N���X �R���X�g���N�^
//--------------------------------------------
CShadow::CShadow() : CScene3D(SHADOW_PRIORITY)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			//�ʒu
	m_rot = D3DXVECTOR3(0, 0, 0);		//����
	D3DXMatrixIdentity(&m_mtxWorld);	//���[���h�}�g���b�N�X
}

//--------------------------------------------
//�e�N���X �f�X�g���N�^
//--------------------------------------------
CShadow::~CShadow()
{
}

//=============================================================================
// ��������
//=============================================================================
CShadow * CShadow::Create(D3DXVECTOR3 pos, float fWidth, float fDepth)
{
	CShadow *pShadow;

	pShadow = new CShadow;

	pShadow->m_pos = pos;
	pShadow->m_fWidth = fWidth;
	pShadow->m_fDepth = fDepth;
	pShadow->Init();

	return pShadow;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CShadow::Init(void)
{
	CScene3D::Init();
	CScene3D::SetSize(m_fDepth, m_fWidth);
	CScene3D::BindTexture("SHADOW");
	CScene3D::SetPos(m_pos);
	//�F�̐ݒ�
	CScene3D::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f));

	//�I�u�W�F�N�g��ނ̐ݒ�
	CScene3D::SetObjType(CScene::OBJTYPE_SHADOW);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CShadow::Uninit(void)
{
	//�I������
	CScene3D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CShadow::Update(void)
{
	//CScene3D::SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 10.0f, m_pos.z));
}

//=============================================================================
// �`�揈��
//=============================================================================
void CShadow::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾
	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�A���t�@�e�X�g(�����F��`�悵�Ȃ��悤��)
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 90);

	//�`�揈��
	CScene3D::Draw();

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// �ʒu�ݒ菈��
//=============================================================================
void CShadow::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}