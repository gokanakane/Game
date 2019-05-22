//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : Akane Gokan
//
//=============================================================================
#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "scene2D.h"
#include "manager.h"
#include "input.h"
#include "game.h"
#include "fade.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9 CFade::m_pTexture = NULL;
CFade::FADEMODE CFade::m_fade = CFade::FADE_NONE;
CManager::MODE CFade::m_modeNext = CManager::MODE_TITLE;
D3DXCOLOR CFade::m_colFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
LPDIRECT3DVERTEXBUFFER9 CFade::m_pVtxBuff = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFade::CFade() : CScene(7)
{
	m_fade = FADE_NONE;
	m_modeNext = CManager::MODE_MAX;
	m_colFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);			//�������

	m_pScene2D = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFade::~CFade() {}

//=============================================================================
// ����������
//=============================================================================
HRESULT CFade::Init(void)
{
	VERTEX_2D * pVtx;
	LPDIRECT3DDEVICE9 pDevice = NULL;
	CRenderer *pRenderer = CManager::GetRenderer();

	CScene::SetObjtype(CScene::OBJTYPE_FADE);
	CFade::m_fade = FADE_IN;
	CFade::m_modeNext = CManager::MODE_TITLE;
	CFade::m_colFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);			//�������

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�|���S���̐F�ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	if (m_pScene2D == NULL)
	{
		m_pScene2D = new CScene2D;
		m_pScene2D->Init();
		m_pScene2D->BindTexture(m_pTexture);
		m_pScene2D->SetScene2D(D3DXVECTOR3(980.0f, 650.0f, 0.0f), 300.0f, 50.0f);
		m_pScene2D->SetObjtype(CScene::OBJTYPE_FADE);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CFade::Uninit(void)
{
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CFade::Update(void)
{
	VERTEX_2D * pVtx;			//���_���ւ̃|�C���^

	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{	//�t�F�[�h�C�����
			m_colFade.a -= 0.03f;				//��ʂ𓧖��ɂ���
			if (m_colFade.a <= 0.0f)
			{
				m_colFade.a = 0.0f;
				m_fade = FADE_NONE;			//�������Ă��Ȃ���Ԃɂ���
			}
		}
		else if (m_fade == FADE_OUT)
		{	//�t�F�[�h�A�E�g���
			m_colFade.a += 0.03f;				//��ʂ�s�����ɂ���
			if (m_colFade.a >= 1.0f)
			{
				m_colFade.a = 1.0f;
				m_fade = FADE_IN;					//�t�F�[�h�C�����

				//���[�h�̐ݒ�
				CManager::SetMode(m_modeNext);
			}
		}

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�|���S���̐F�ݒ�
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colFade.a);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colFade.a);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colFade.a);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colFade.a);

		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}

	if (m_pScene2D != NULL)
	{
		m_pScene2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_colFade.a));
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CFade::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;							//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();		//�����_�����O�N���X�̎擾

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
							0,
							2);
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Draw();
	}

}
//=============================================================================
// �t�F�[�h�̐ݒ�
//=============================================================================
void CFade::SetFade(CManager::MODE modeNext)
{
	m_fade = FADE_OUT;
	m_modeNext = modeNext;
	m_colFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}
//=============================================================================
// �e�N�X�`���̃��[�h
//=============================================================================
HRESULT CFade::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	D3DXCreateTextureFromFile(pDevice, FADETEXTURE_NOWLOADING, &m_pTexture);
	return S_OK;
}
//=============================================================================
// �e�N�X�`���̃A�����[�h
//=============================================================================
void CFade::UnLoad(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}