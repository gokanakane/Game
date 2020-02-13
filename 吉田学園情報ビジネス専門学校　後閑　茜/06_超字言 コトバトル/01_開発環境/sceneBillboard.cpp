//=============================================================================
//
// �r���{�[�h���� [Billboard.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "sceneBillboard.h"
#include "manager.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEX_POS_X_INIT				(1.0f)								//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT				(1.0f)								//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT					(0.0f)								//�e�N�X�`�����WU��
#define TEX_RIGHT					(1.0f)								//�e�N�X�`�����WU�E
#define TEX_TOP						(0.0f)								//�e�N�X�`�����WV��
#define TEX_BOT						(1.0f)								//�e�N�X�`�����WV��

//--------------------------------------------
//�V�[���r���{�[�h�N���X �R���X�g���N�^
//--------------------------------------------
CSceneBillBoard::CSceneBillBoard() : CScene(5, CScene::OBJTYPE_BILLBOARD)
{
	//�����o�ϐ�
	m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	m_move = D3DXVECTOR3(0, 0, 0);
	m_fWidth = 0;
	m_fHeight = 0;
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtrxWorld);
	m_bColChange = false;
}

//--------------------------------------------
//�V�[���r���{�[�h�N���X �f�X�g���N�^
//--------------------------------------------
CSceneBillBoard::~CSceneBillBoard()
{
}

//--------------------------------------------
//�V�[���r���{�[�h�̐���
//--------------------------------------------
CSceneBillBoard *CSceneBillBoard::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, LPCSTR Tag)
{
	CSceneBillBoard *pBillBoard;

	pBillBoard = new CSceneBillBoard;

	//�l�̑��
	pBillBoard->m_pos = pos;
	pBillBoard->m_fHeight = fHeight;
	pBillBoard->m_fWidth = fWidth;

	pBillBoard->Init(pos);
	pBillBoard->BindTexture(Tag);

	return pBillBoard;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSceneBillBoard::Init(D3DXVECTOR3 pos)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	////�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//	BILLBOARD_TEXTURENAME000,
	//	&m_pTexture);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W (�T�C�Y�������߂�)
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth, m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth, 0.0f, 0.0f);

	//�@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(TEX_LEFT, TEX_TOP);
	pVtx[1].tex = D3DXVECTOR2(TEX_RIGHT, TEX_TOP);
	pVtx[2].tex = D3DXVECTOR2(TEX_LEFT, TEX_BOT);
	pVtx[3].tex = D3DXVECTOR2(TEX_RIGHT, TEX_BOT);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	CScene::SetObjType(OBJTYPE_BILLBOARD);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSceneBillBoard::Uninit(void)
{
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//����������(�V�[��2D��j��)
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CSceneBillBoard::Update(void)
{
	//�ʒu�X�V
	m_pos += m_move;
}

//=============================================================================
// �`�揈��
//=============================================================================
void CSceneBillBoard::Draw(void)
{
	/*if (m_bDrawFlag == false) { 
		return; }*/

	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX  mtxView;

	if (CScene::OBJTYPE_WORD_EFFECT == CScene::GetObjType())
	{
		// ���u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		//Z�o�b�t�@�̐ݒ�
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	}

	//�����_�[�X�e�[�g�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtrxWorld);

	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�}�g���b�N�X�̐ݒ�
	CUtilityMath::CalWorldMatrix(&m_mtrxWorld,
		m_pos,
		D3DXVECTOR3(0.0f,0.0f,0.0f),
		NULL,
		D3DXVECTOR3(1.0f,1.0f,1.0f),
		&mtxView);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtrxWorld);
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//���_�t�H�[�}�b�g��ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);
	// �r���{�[�h�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,	//�J�n���钸�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��

	if (CScene::OBJTYPE_WORD_EFFECT == CScene::GetObjType())
	{
		// ���u�����f�B���O�����ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		//Z�o�b�t�@���f�t�H���g�̐ݒ�ɖ߂�
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	}

	//���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// �r���{�[�h�̈ʒu�ݒ菈��
//=============================================================================
void CSceneBillBoard::Setpos(D3DXVECTOR3 pos)
{
	// �V�[���r���{�[�h�̈ʒu��ݒ�
	m_pos = pos;
}

//=============================================================================
// �r���{�[�h�̐ݒ菈��
//=============================================================================
void CSceneBillBoard::SetBillboard(D3DXVECTOR3 pos, float fHeight, float fWidth)
{
	VERTEX_3D *pVtx;//���_���ւ̃|�C���^
					//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	m_pos = pos;
	m_fHeight = fHeight;
	m_fWidth = fWidth;

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(-fWidth, fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(fWidth, fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-fWidth, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(fWidth, 0.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}


//=============================================================================
//�r���{�[�h�e�N�X�`���̐ݒ�
//=============================================================================
void CSceneBillBoard::BindTexture(LPDIRECT3DTEXTURE9 Texture)
{
	m_pTexture = Texture;
}

void CSceneBillBoard::BindTexture(LPCSTR TexTag)
{
	m_pTexture = CTexture::GetTexture(TexTag);
}
//=============================================================================
//�r���{�[�h�ʒu�擾
//=============================================================================
D3DXVECTOR3 CSceneBillBoard::GetPos(void)
{
	return m_pos;
}

//=============================================================================
//�r���{�[�h�F�ݒ�
//=============================================================================
void CSceneBillBoard::SetCol(D3DXCOLOR col)
{
	m_col = col;
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;
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
//�r���{�[�h���_�擾
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 CSceneBillBoard::GetVtx(void)
{
	return m_pVtxBuff;
}

//=============================================================================
// �A�j���[�V�����̏���
//=============================================================================
void CSceneBillBoard::SetTexture(int PatternAnim, int X, int Y, int nNum)
{
	VERTEX_3D *pVtx;//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2((PatternAnim / Y) * (1.0f / X) * (1 * nNum), (PatternAnim % Y) * (1.0f / Y));
	pVtx[1].tex = D3DXVECTOR2((PatternAnim / Y) * (1.0f / X) + (1.0f / X), (PatternAnim % Y) * (1.0f / Y));
	pVtx[2].tex = D3DXVECTOR2((PatternAnim / Y) * (1.0f / X) * (1 * nNum), (PatternAnim % Y) * (1.0f / Y) + (1.0f / Y));
	pVtx[3].tex = D3DXVECTOR2((PatternAnim / Y) * (1.0f / X) + (1.0f / X), (PatternAnim % Y) * (1.0f / Y) + (1.0f / Y));

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
void CSceneBillBoard::SetTexture(D3DXVECTOR2 minRect, D3DXVECTOR2 maxRect)
{
	VERTEX_3D *pVtx;//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(minRect.x, minRect.y);
	pVtx[1].tex = D3DXVECTOR2(maxRect.x, minRect.y);
	pVtx[2].tex = D3DXVECTOR2(minRect.x, maxRect.y);
	pVtx[3].tex = D3DXVECTOR2(maxRect.x, maxRect.y);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}