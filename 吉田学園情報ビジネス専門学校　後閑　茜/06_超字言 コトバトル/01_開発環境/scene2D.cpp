//=============================================================================
//
// �V�[��2D���� [scene2D.h]
// Author : �ڍ� ������
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "input.h"

//=============================================================================
// �V�[���N���X�̃R���X�g���N�^
//=============================================================================
CScene2D::CScene2D(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// �l���N���A
	m_pTexture = NULL;

	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSpin = 0.0f;	//��]
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//�F
	m_fScale = 0.0f;	//�g��
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_fRight = 0.0f;
	m_fLeft = 0.0f;
	m_bDraw = true;
	m_bAddition = false;
}

//=============================================================================
// �I�u�W�F�N�g�̐�������
//=============================================================================
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, LPCSTR Tag,int nPriority)
{
	CScene2D *pScene2D = NULL;

	if (pScene2D == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pScene2D = new CScene2D(nPriority, OBJTYPE_SCENE2D);

		if (pScene2D != NULL)
		{
			pScene2D->Init(pos);
			pScene2D->BindTexture(Tag);
		}
	}

	return pScene2D;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{
}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos)
{
	// �|���S���̈ʒu��ݒ�
	m_Pos = pos;
	m_bDraw = true;

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	//SetObjType(CScene::OBJTYPE_SCENE2D);

	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x - 50.0f, m_Pos.y - 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Pos.x + 50.0f, m_Pos.y - 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x - 50.0f, m_Pos.y + 50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Pos.x + 50.0f, m_Pos.y + 50.0f, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CScene2D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �I�u�W�F�N�g�̉��
	Release();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CScene2D::Update(void)
{
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CScene2D::Draw(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}
	//�A���t�@�e�X�g(�����F��`�悵�Ȃ��悤��)
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 90);

	if (m_bAddition == true)
	{
		// ���u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	if (m_bDraw == true)
	{	// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
	if (m_bAddition == true)
	{
		// ���u�����f�B���O�����ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// �I�u�W�F�N�g�̎擾
//=============================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_Pos;
}

//=============================================================================
// �I�u�W�F�N�g�̐ݒ�
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos)
{
	m_Pos = pos;

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x - m_fWidth, m_Pos.y - m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Pos.x + m_fWidth, m_Pos.y - m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x - m_fWidth, m_Pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Pos.x + m_fWidth, m_Pos.y + m_fHeight, 0.0f);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �e�N�X�`���̐ݒ�
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//�����Ă���������
	m_pTexture = pTexture;
}

void CScene2D::BindTexture(LPCSTR TexTag)
{
	m_pTexture = CTexture::GetTexture(TexTag);
}

//=============================================================================
//�V�[��2D�ʒu�ݒ�
//=============================================================================
void CScene2D::SetPos(D3DXVECTOR3 pos, float fSpin, float fScale, D3DXCOLOR col)
{
	m_Pos = pos;		//�ʒu
	m_fSpin = fSpin;	//��]
	m_Col = col;		//�F
	m_fScale = fScale;	//�g��

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_Pos.x + sinf(D3DX_PI * -0.75f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[0].pos.y = m_Pos.y + cosf(D3DX_PI * -0.75f + m_fSpin) *  (m_fHeight + m_fScale);
	pVtx[1].pos.x = m_Pos.x + sinf(D3DX_PI * 0.75f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[1].pos.y = m_Pos.y + cosf(D3DX_PI * 0.75f + m_fSpin) *  (m_fHeight + m_fScale);
	pVtx[2].pos.x = m_Pos.x + sinf(D3DX_PI * -0.25f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[2].pos.y = m_Pos.y + cosf(D3DX_PI * -0.25f + m_fSpin) *  (m_fHeight + m_fScale);
	pVtx[3].pos.x = m_Pos.x + sinf(D3DX_PI * 0.25f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[3].pos.y = m_Pos.y + cosf(D3DX_PI * 0.25f + m_fSpin) *  (m_fHeight + m_fScale);

	//���_�J���[
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;


	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//=============================================================================
//�V�[��2D��]�ݒ�
//=============================================================================
void CScene2D::SetRot(float fSpin)
{
	m_fSpin = fSpin;	//��]

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
#if 1
	pVtx[0].pos.x = m_Pos.x + sinf(D3DX_PI * -0.75f + m_fSpin) * m_fWidth;
	pVtx[0].pos.y = m_Pos.y + cosf(D3DX_PI * -0.75f + m_fSpin) *  m_fHeight;
	pVtx[1].pos.x = m_Pos.x + sinf(D3DX_PI * 0.75f + m_fSpin) *  m_fWidth;
	pVtx[1].pos.y = m_Pos.y + cosf(D3DX_PI * 0.75f + m_fSpin) *  m_fHeight;
	pVtx[2].pos.x = m_Pos.x + sinf(D3DX_PI * -0.25f + m_fSpin) *  m_fWidth;
	pVtx[2].pos.y = m_Pos.y + cosf(D3DX_PI * -0.25f + m_fSpin) *  m_fHeight;
	pVtx[3].pos.x = m_Pos.x + sinf(D3DX_PI * 0.25f + m_fSpin) *  m_fWidth;
	pVtx[3].pos.y = m_Pos.y + cosf(D3DX_PI * 0.25f + m_fSpin) *  m_fHeight;
#endif
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//=============================================================================
//�V�[��2D�傫���ݒ�
//=============================================================================
void CScene2D::SetWidthHeight(float fWidth, float fHeight)
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_Pos.x + sinf(D3DX_PI * -0.75f) * m_fWidth;
	pVtx[0].pos.y = m_Pos.y + cosf(D3DX_PI * -0.75f) * m_fHeight;
	pVtx[1].pos.x = m_Pos.x + sinf(D3DX_PI * 0.75f) * m_fWidth;
	pVtx[1].pos.y = m_Pos.y + cosf(D3DX_PI * 0.75f) * m_fHeight;
	pVtx[2].pos.x = m_Pos.x + sinf(D3DX_PI * -0.25f) * m_fWidth;
	pVtx[2].pos.y = m_Pos.y + cosf(D3DX_PI * -0.25f) * m_fHeight;
	pVtx[3].pos.x = m_Pos.x + sinf(D3DX_PI * 0.25f) * m_fWidth;
	pVtx[3].pos.y = m_Pos.y + cosf(D3DX_PI * 0.25f) * m_fHeight;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
//�V�[��2D���E�̑傫���ݒ�
//=============================================================================
void CScene2D::SetRIghtLeft(float fRight, float fLeft)
{
	m_fRight = fRight;
	m_fLeft = fLeft;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_Pos.x + sinf(D3DX_PI * -0.75f) * (m_fWidth + m_fLeft);
	pVtx[0].pos.y = m_Pos.y + cosf(D3DX_PI * -0.75f) * m_fHeight;
	pVtx[1].pos.x = m_Pos.x + sinf(D3DX_PI * 0.75f) * (m_fWidth + m_fRight);
	pVtx[1].pos.y = m_Pos.y + cosf(D3DX_PI * 0.75f) * m_fHeight;
	pVtx[2].pos.x = m_Pos.x + sinf(D3DX_PI * -0.25f) * (m_fWidth + m_fLeft);
	pVtx[2].pos.y = m_Pos.y + cosf(D3DX_PI * -0.25f) * m_fHeight;
	pVtx[3].pos.x = m_Pos.x + sinf(D3DX_PI * 0.25f) * (m_fWidth + m_fRight);
	pVtx[3].pos.y = m_Pos.y + cosf(D3DX_PI * 0.25f) * m_fHeight;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
//�V�[��2D�F�̕ύX
//=============================================================================
void CScene2D::SetCol(D3DXCOLOR col)
{
	m_Col = col;		//�F

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}


//=============================================================================
// �A�j���[�V�����̐ݒ菈��
//=============================================================================
void CScene2D::SetAnimation(int m_PatternAnim, float fUV_U, float fUV_V)
{
	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

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
void CScene2D::SetTex(D3DXVECTOR2 texmin, D3DXVECTOR2 texmax)
{
	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(texmin.x, texmin.y);
	pVtx[1].tex = D3DXVECTOR2(texmax.x, texmin.y);
	pVtx[2].tex = D3DXVECTOR2(texmin.x, texmax.y);
	pVtx[3].tex = D3DXVECTOR2(texmax.x, texmax.y);

	m_Tex[0] = texmin;
	m_Tex[1] = texmax;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}


//=============================================================================
//�傫���ύX
//=============================================================================
void CScene2D::SetScale(float fScale)
{
	m_fScale = fScale;	//�g��

						//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_Pos.x + sinf(D3DX_PI * -0.75f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[0].pos.y = m_Pos.y + cosf(D3DX_PI * -0.75f + m_fSpin) *  (m_fHeight + m_fScale);
	pVtx[1].pos.x = m_Pos.x + sinf(D3DX_PI * 0.75f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[1].pos.y = m_Pos.y + cosf(D3DX_PI * 0.75f + m_fSpin) *  (m_fHeight + m_fScale);
	pVtx[2].pos.x = m_Pos.x + sinf(D3DX_PI * -0.25f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[2].pos.y = m_Pos.y + cosf(D3DX_PI * -0.25f + m_fSpin) *  (m_fHeight + m_fScale);
	pVtx[3].pos.x = m_Pos.x + sinf(D3DX_PI * 0.25f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[3].pos.y = m_Pos.y + cosf(D3DX_PI * 0.25f + m_fSpin) *  (m_fHeight + m_fScale);
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}
//=============================================================================
// 2D�|���S���̐ݒ�i���𒆐S���W�ɂ���j
//=============================================================================
void CScene2D::SetScene2DLeftCenter(D3DXVECTOR3 pos, float sizeW, float sizeH)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	m_Pos = pos;
	m_fWidth = sizeW;
	m_fHeight = sizeH;

	// ���_����ݒ�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̑傫���̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x, (m_Pos.y - m_fHeight), 0.0f);
	pVtx[1].pos = D3DXVECTOR3((m_Pos.x + m_fWidth), (m_Pos.y - m_fHeight), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x, (m_Pos.y + m_fHeight), 0.0f);
	pVtx[3].pos = D3DXVECTOR3((m_Pos.x + m_fWidth), (m_Pos.y + m_fHeight), 0.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}