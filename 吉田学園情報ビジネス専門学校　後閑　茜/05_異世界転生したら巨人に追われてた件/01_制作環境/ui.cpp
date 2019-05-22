//**************************************************************
//
//				�|���S���̏���[polygon.cpp]
//				Auther : Shun Yokomichi
//
//**************************************************************
#include "ui.h"				// UI�|���S��
#include "manager.h"		// �}�l�[�W���[
#include "renderer.h"		// �����_���[

//**************************************************************
//			�}�N����`
//**************************************************************
#define POLYGON_TEXNAME000		"data/TEXTURE/game/NumberOption.png"	// ���Ԃ̊Ԃ̓_
#define POLYGON_TEXNAME001		"data/TEXTURE/game/Frame_Distance.png"	// �~�j�}�b�v
#define POLYGON_TEXNAME002		"data/TEXTURE/game/UIPolygon.png"	// ���C�t�Q�[�W
#define POLYGON_TEXNAME003		"data/TEXTURE/game/TimeIcon.png"		// ����
#define POLYGON_TEXNAME004		"data/TEXTURE/game/player.png"			// �v���C���[
#define TEX_UV_U				(1.0f)									// �e�N�X�`��UV_U
#define TEX_UV_V				(1.0f)									// �e�N�X�`��UV_V

//**************************************************************
//		�ÓI�����o�ϐ�
//**************************************************************
LPDIRECT3DTEXTURE9 CUiPolygon::m_pTexture[MAX_POLYGON] = {};
float				CUiPolygon::m_colA = 1.0f;

//**************************************************************
//		UI�|���S���̐���
//**************************************************************
CUiPolygon*CUiPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, int nTexNum)
{
	CUiPolygon *pPolygon = NULL;

	// �V�[���̐���
	if (pPolygon == NULL)
	{
		pPolygon = new CUiPolygon;
		if (pPolygon != NULL)
		{
			pPolygon->Init(pos, size, col, nTexNum);
		}
	}

	return pPolygon;
}

//**************************************************************
//		�e�N�X�`���̓ǂݍ���
//**************************************************************
HRESULT CUiPolygon::Load(void)
{
	// �f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCntTex = 0; nCntTex < MAX_POLYGON; nCntTex++)
	{
		if (m_pTexture[nCntTex] == NULL)
		{
			// �e�N�X�`���̐���
			if (nCntTex == 0)
			{
				D3DXCreateTextureFromFile(pDevice, POLYGON_TEXNAME000, &m_pTexture[0]);
			}
			if (nCntTex == 1)
			{
				D3DXCreateTextureFromFile(pDevice, POLYGON_TEXNAME001, &m_pTexture[1]);
			}
			if (nCntTex == 2)
			{
				D3DXCreateTextureFromFile(pDevice, POLYGON_TEXNAME002, &m_pTexture[2]);
			}
			if (nCntTex == 3)
			{
				D3DXCreateTextureFromFile(pDevice, POLYGON_TEXNAME003, &m_pTexture[3]);
			}
			if (nCntTex == 4)
			{
				D3DXCreateTextureFromFile(pDevice, POLYGON_TEXNAME004, &m_pTexture[4]);
			}
		}
	}


	return S_OK;
}

//**************************************************************
//		�e�N�X�`���̊J��
//**************************************************************
void CUiPolygon::Unload(void)
{
	//�e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < MAX_POLYGON; nCntTex++)
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
CUiPolygon::CUiPolygon() : CScene2D(PRIORITY_UI, OBJTYPE_NUMBER)
{

}

//**************************************************************
//		�f�X�g���N�^
//**************************************************************
CUiPolygon::~CUiPolygon()
{

}

//**************************************************************
//		����������
//**************************************************************
HRESULT CUiPolygon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, int nTexNum)
{
	CScene2D::SetInitAll(pos, size, col, D3DXVECTOR2(TEX_UV_U, TEX_UV_V));		// �����l�ݒ�
	CScene2D::Init();
	CScene2D::BindTexture(m_pTexture[nTexNum]);
	m_colA = 1.0f;

	return S_OK;
}

//**************************************************************
//		�I������
//**************************************************************
void CUiPolygon::Uninit(void)
{
	CScene2D::Uninit();
}

//**************************************************************
//		�X�V����
//**************************************************************
void CUiPolygon::Update(void)
{
	CScene2D::Update();
}

//**************************************************************
//		�`�揈��
//**************************************************************
void CUiPolygon::Draw(void)
{
	CScene2D::Draw();
}