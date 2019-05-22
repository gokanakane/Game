//**************************************************************
//
//				�v���X�{�^���̏���[press.cpp]
//				Auther : Shun Yokomichi
//
//**************************************************************
#include "press.h"			// �v���X�{�^��
#include "manager.h"		// �}�l�[�W���[
#include "renderer.h"		// �����_���[

//**************************************************************
//			�}�N����`
//**************************************************************
#define TEXNAME000	"data/TEXTURE/title/TitleUI.png"				// ���Ԃ̊Ԃ̓_
#define TEXNAME001	"data/TEXTURE/tutorial/TutorialMarker.png"		// ���
#define TEXNAME002	"data/TEXTURE/tutorial/TutorialMarker001.png"	// �L�[�{�[�h(A)
#define TEXNAME003	"data/TEXTURE/tutorial/TutorialMarker002.png"	// �L�[�{�[�h(D)
#define TEXNAME004	"data/TEXTURE/tutorial/cross.png"				// �\���L�[
#define TEXNAME005	"data/TEXTURE/pause/w.png"						// �L�[�{�[�h(W)
#define TEXNAME006	"data/TEXTURE/pause/s.png"						// �L�[�{�[�h(S)
#define TEXNAME007	"data/TEXTURE/tutorial/Enter.png"				// �`���[�g���A���p
#define TEXNAME008	"data/TEXTURE/tutorial/B.png"					// B�{�^��
#define TEXNAME009	"data/TEXTURE/result/Enter.png"					// ���U���g�p
#define COL_A		(0.01f)											// �����x�̕ω���
#define TEX_UV_U	(1.0f)											// �e�N�X�`��UV_U
#define TEX_UV_V	(1.0f)											// �e�N�X�`��UV_V

//**************************************************************
//		�ÓI�����o�ϐ�
//**************************************************************
LPDIRECT3DTEXTURE9 CPress::m_pTexture[MAX_TEX_PRESS] = {};

//**************************************************************
//		UI�|���S���̐���
//**************************************************************
CPress*CPress::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, int nTex, float rot)
{
	CPress *pPress = NULL;

	// �V�[���̐���
	if (pPress == NULL)
	{
		pPress = new CPress;
		if (pPress != NULL)
		{
			pPress->Init(pos, size, col, nTex, rot);
		}
	}

	return pPress;
}

//**************************************************************
//		�e�N�X�`���̓ǂݍ���
//**************************************************************
HRESULT CPress::Load(void)
{
	// �f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXNAME000, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXNAME001, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXNAME002, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXNAME003, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, TEXNAME004, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, TEXNAME005, &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, TEXNAME006, &m_pTexture[6]);
	D3DXCreateTextureFromFile(pDevice, TEXNAME007, &m_pTexture[7]);
	D3DXCreateTextureFromFile(pDevice, TEXNAME008, &m_pTexture[8]);
	D3DXCreateTextureFromFile(pDevice, TEXNAME009, &m_pTexture[9]);

	return S_OK;
}

//**************************************************************
//		�e�N�X�`���̊J��
//**************************************************************
void CPress::Unload(void)
{
	//�e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < MAX_TEX_PRESS; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}

//**************************************************************
//		�R���X�g���N�^
//**************************************************************
CPress::CPress() : CScene2D(PRIORITY_UI, OBJTYPE_NONE)
{
	// �f�t�H���g�l
	m_fColA = 0.0f;
	m_type = CPress::TYPE_NONE;
}

//**************************************************************
//		�f�X�g���N�^
//**************************************************************
CPress::~CPress()
{

}

//**************************************************************
//		����������
//**************************************************************
HRESULT CPress::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, int nTex, float rot)
{
	CScene2D::SetInitAll(pos, size, col, D3DXVECTOR2(TEX_UV_U, TEX_UV_V));		// �����l�ݒ�
	CScene2D::Setrot(rot);
	CScene2D::Init();
	CScene2D::BindTexture(m_pTexture[nTex]);
	m_fColA = col.a;
	m_type = CPress::TYPE_OPAQUE;

	return S_OK;
}

//**************************************************************
//		�I������
//**************************************************************
void CPress::Uninit(void)
{
	CScene2D::Uninit();
}

//**************************************************************
//		�X�V����
//**************************************************************
void CPress::Update(void)
{
	switch (m_type)
	{
	case TYPE_OPAQUE:
		// ��������s����
		m_fColA += COL_A;	// �����x�̑���
		if (m_fColA > 1.0f)
		{	// �^�C�v�ω�
			m_type = TYPE_TRANSPARENCE;
		}
		break;

	case TYPE_TRANSPARENCE:
		// �s�������瓧��
		m_fColA -= COL_A;	// �����x�̑���
		if (m_fColA < 0.0f)
		{	// �^�C�v�ω�
			m_type = TYPE_OPAQUE;
		}
		break;

	case TYPE_MANUAL:
		// �蓮
		m_fColA = 0.0f;
		break;

	case TYPE_NONE:
		m_fColA = 1.0f;
		break;
	}

	CScene2D::Setcol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColA));
	CScene2D::Update();
}

//**************************************************************
//		�`�揈��
//**************************************************************
void CPress::Draw(void)
{
	CScene2D::Draw();
}