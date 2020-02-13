//=============================================================================
//
// 3D�|���S������ [scene3D.cpp]
// Author : �ڍ� ������
//
//=============================================================================
#include "scene3D.h"
#include "main.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "game.h"

//=============================================================================
// 3D�|���S���N���X�̃R���X�g���N�^
//=============================================================================
CScene3D::CScene3D(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// �l���N���A
	m_pTexture = NULL;						// �e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_TexUV = D3DXVECTOR2(1.0f, 1.0f);
	m_scene3dType = SCENE3DTYPE_NORMAL;
	m_bAlphaTest = false;
	m_bLigntEffect = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene3D::~CScene3D()
{
}

//=============================================================================
// �I�u�W�F�N�g�̐�������
//=============================================================================
CScene3D *CScene3D::Create(D3DXVECTOR3 pos, LPCSTR Tag)
{
	CScene3D *pScene3D = NULL;

	if (pScene3D == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pScene3D = new CScene3D;

		if (pScene3D != NULL)
		{
			pScene3D->Init();
			pScene3D->SetPos(pos);
			pScene3D->BindTexture(Tag);
		}
	}
	return pScene3D;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScene3D::Init(void)
{
	//	�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4
		, D3DUSAGE_WRITEONLY
		, FVF_VERTEX_3D
		, D3DPOOL_MANAGED
		, &m_pVtxBuff
		, NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^
						// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, m_size.z);
	pVtx[1].pos = D3DXVECTOR3(m_size.x, m_size.y, m_size.z);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y, -m_size.z);
	pVtx[3].pos = D3DXVECTOR3(m_size.x, -m_size.y, -m_size.z);

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//	�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_TexUV.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, m_TexUV.y);
	pVtx[3].tex = D3DXVECTOR2(m_TexUV.x, m_TexUV.y);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScene3D::Uninit(void)
{
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �I�u�W�F�N�g�̉��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene3D::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene3D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();			// �f�o�C�X�擾

	D3DXMATRIX mtxView;		// �v�Z�p�}�g���b�N�X
	if (m_bLigntEffect == false)
	{
		// ���C�g�e��
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	}
	if (m_bAlphaTest == true)
	{
		// �A���t�@�e�X�g�̐ݒ�
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 1);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	}

	if (m_scene3dType == SCENE3DTYPE_BILLBOARD || m_scene3dType == SCENE3DTYPE_BILLEFFECT
		|| m_scene3dType == SCENE3DTYPE_SUBSYNTHESIS)

	{//	�r���{�[�h�@			���Z��������r���{�[�h�G�t�F�N�g
		if (m_scene3dType == SCENE3DTYPE_BILLEFFECT|| m_scene3dType == SCENE3DTYPE_ADDSYNTHESIS)
		{
			// ���u�����f�B���O�����Z�����ɐݒ�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}
		else if (m_scene3dType == SCENE3DTYPE_SUBSYNTHESIS)
		{
			//// ���u�����f�B���O�����Z�����ɐݒ�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}
		// Z�o�b�t�@�ւ̏�������
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	}
	if (m_scene3dType == SCENE3DTYPE_ADDSYNTHESIS)
	{
		// ���u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	if (m_scene3dType == SCENE3DTYPE_NORMAL || m_scene3dType == SCENE3DTYPE_ADDSYNTHESIS)
	{
		CUtilityMath::CalWorldMatrix(&m_mtxWorld,m_pos,m_rot);
	}
	else if (m_scene3dType == SCENE3DTYPE_BILLBOARD || m_scene3dType == SCENE3DTYPE_BILLEFFECT)
	{//	�r���{�[�h�@			���Z��������r���{�[�h�G�t�F�N�g
	 // �t�s��
		CUtilityMath::CalWorldMatrix(&m_mtxWorld,m_pos,D3DXVECTOR3(0.0f,0.0f,0.0f),NULL,D3DXVECTOR3(1.0f,1.0f,1.0f),&mtxView);
	}

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�gd
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	if (m_scene3dType == SCENE3DTYPE_BILLEFFECT || m_scene3dType == SCENE3DTYPE_BILLBOARD
		|| m_scene3dType == SCENE3DTYPE_ADDSYNTHESIS || m_scene3dType == SCENE3DTYPE_SUBSYNTHESIS)
	{//	�r���{�[�h�@			���Z��������r���{�[�h�G�t�F�N�g
	 // Z�o�b�t�@�ւ̏�������
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		if (m_scene3dType == SCENE3DTYPE_BILLEFFECT || m_scene3dType == SCENE3DTYPE_ADDSYNTHESIS || m_scene3dType == SCENE3DTYPE_SUBSYNTHESIS)
		{//	�r���{�[�h
		 // ���u�����f�B���O�����ɖ߂�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		}
	}
	if (m_bLigntEffect == false)
	{
		// ���C�g�e��
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
	if (m_bAlphaTest == true)
	{
		// �A���t�@�e�X�g�𖳌�
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
}
//=============================================================================
// �������擾
//============================================================================
float CScene3D::GetHeight(D3DXVECTOR3 pos)
{
	return pos.y;
}

//=============================================================================
// �e�N�X�`���̐ݒ�
//=============================================================================
void CScene3D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//�����Ă���������
	m_pTexture = pTexture;
}
void CScene3D::BindTexture(LPCSTR TexTag)
{
	m_pTexture = CTexture::GetTexture(TexTag);
}
//=============================================================================
// �T�C�Y�̐ݒ�
//=============================================================================
void CScene3D::SetSize(float fHeight,float fWidth)
{
	//�擾�����T�C�Y����
	m_size.y = fHeight;
	m_size.x = fWidth;

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, 0.0f, m_size.y);
	pVtx[1].pos = D3DXVECTOR3(m_size.x, 0.0f, m_size.y);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, 0.0f, -m_size.y);
	pVtx[3].pos = D3DXVECTOR3(m_size.x, 0.0f, -m_size.y);

	for (int nCntPos = 0; nCntPos < NUM_VTX; nCntPos++)
	{
		m_aPos[nCntPos] = pVtx[nCntPos].pos;
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//=============================================================================
// �T�C�Y�̐ݒ�
//=============================================================================
void CScene3D::SetSizeY(float fHeight, float fWidth)
{
	//�擾�����T�C�Y����
	m_size.y = fHeight;
	m_size.x = fWidth;

	if (m_pVtxBuff == NULL) { return; }
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_size.x, m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_size.x, -m_size.y, 0.0f);

	for (int nCntPos = 0; nCntPos < NUM_VTX; nCntPos++)
	{
		m_aPos[nCntPos] = pVtx[nCntPos].pos;
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void CScene3D::SetRot(D3DXVECTOR3 rot)
{
	//�擾�����T�C�Y����
	m_rot = rot;
}

//=============================================================================
// �A�j���[�V�����̐ݒ菈��
//=============================================================================
void CScene3D::SetAnimation(int m_PatternAnim, float fUV_U, float fUV_V)
{
	VERTEX_3D*pVtx;	//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̍��W
	pVtx[0].tex = D3DXVECTOR2(fUV_U * m_PatternAnim, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fUV_U * m_PatternAnim + fUV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(fUV_U * m_PatternAnim, fUV_V);
	pVtx[3].tex = D3DXVECTOR2(fUV_U * m_PatternAnim + fUV_U, fUV_V);

	////�e�N�X�`���̍��W
	//pVtx[0].tex = D3DXVECTOR2(EXPLOSION_UV_U, EXPLOSION_UV_V * m_PatternAnim);
	//pVtx[1].tex = D3DXVECTOR2(0.0f, EXPLOSION_UV_V * m_PatternAnim);
	//pVtx[2].tex = D3DXVECTOR2(EXPLOSION_UV_U, EXPLOSION_UV_V * m_PatternAnim + EXPLOSION_UV_V);
	//pVtx[3].tex = D3DXVECTOR2(0.0f, EXPLOSION_UV_V * m_PatternAnim + EXPLOSION_UV_V);

	m_PatternAnim = 0;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �A�j���[�V�����̐ݒ菈��
//=============================================================================
void CScene3D::SetAnimationTex(D3DXVECTOR2 texmin, D3DXVECTOR2 texmax)
{
	VERTEX_3D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(texmin.x, texmin.y);
	pVtx[1].tex = D3DXVECTOR2(texmax.x, texmin.y);
	pVtx[2].tex = D3DXVECTOR2(texmin.x, texmax.y);
	pVtx[3].tex = D3DXVECTOR2(texmax.x, texmax.y);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �F�̐ݒ�
//=============================================================================
void CScene3D::SetColor(D3DXCOLOR col)
{
	m_col = col;

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

						// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �e��UI�\��
//=============================================================================
void CScene3D::SetBulletUI(D3DXVECTOR3 size, D3DXVECTOR3 rot, int nType)
{
	m_rot = rot;
	m_size = size;

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

						// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (nType == 0)	 // (���S�_ : �^�񒆉�) �~�T�C�� : �V���b�g�K���Ɏg�p
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_size.x, 0.0f, m_size.z);
		pVtx[1].pos = D3DXVECTOR3(m_size.x, 0.0f, m_size.z);
		pVtx[2].pos = D3DXVECTOR3(-m_size.x + (m_size.x - 10.0f), 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_size.x - (m_size.x - 10.0f), 0.0f, 0.0f);
	}
	else if (nType == 1)	// (���S�_ : �^�񒆉�) �}�V���K���Ɏg�p
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_size.x, 0.0f, m_size.z);
		pVtx[1].pos = D3DXVECTOR3(m_size.x, 0.0f, m_size.z);
		pVtx[2].pos = D3DXVECTOR3(-m_size.x, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_size.x, 0.0f, 0.0f);
	}
	else if (nType == 2)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_size.x, 0.0f, m_size.z);
		pVtx[1].pos = D3DXVECTOR3(m_size.x, 0.0f, m_size.z);
		pVtx[2].pos = D3DXVECTOR3(-m_size.x, 0.0f, -m_size.z);
		pVtx[3].pos = D3DXVECTOR3(m_size.x, 0.0f, -m_size.z);
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}