//=============================================================================
//
// �v���C���[�̑̃p�[�c���� [CharaParts.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "CharaParts.h"
#include "manager.h"

//=============================================================================
//	�R���X�g���N�^&�f�X�g���N�^
//=============================================================================
CCharaParts::CCharaParts(){
	m_pTexture = NULL;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_nNumMat = 0;
}
CCharaParts::~CCharaParts()
{

}

//=============================================================================
//	�ݒ菈��
//=============================================================================
void CCharaParts::Set(LPCSTR ModelFile, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXMATRIX* pParent)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�ϐ��ݒ�
	m_pParent = pParent;
	m_Pos = pos;
	m_Rot = rot;

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(ModelFile,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

}

//=============================================================================
//	����������
//=============================================================================
HRESULT CCharaParts::Init(void)
{
	m_pTexture = NULL;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_nNumMat = 0;

	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f,1.0f,1.0f);

	m_WorldPosition = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_bDrawFlag = true;

	m_fDiffuseAlpha = m_fOldAlpha = 0.5f;
	//m_fOldAlpha = 0.1f;
	m_fDestAlpha = 1.0f;
	m_nCount = 0;
	return S_OK;
}
//=============================================================================
//	�I������
//=============================================================================
void CCharaParts::Uninit(void)
{
	// ���b�V���̉��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//�}�e���A���̉��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//=============================================================================
//	�X�V����
//=============================================================================
void CCharaParts::Update(void)
{
	if (m_nCount < DIFFUSE_ALPHA_FLAME)
	{
		float fTime = (float)(m_nCount + 1) / (float)DIFFUSE_ALPHA_FLAME;
		float fEasing = CEasingFunc::Easing(CEasingFunc::EASE_OUT_CUBIC, fTime);
		m_fDiffuseAlpha = CUtilityMath::FloatLeap(m_fOldAlpha,m_fDestAlpha, fEasing);
		m_nCount++;
	}
	else
	{
		m_fDiffuseAlpha = m_fDestAlpha;
		m_fOldAlpha = m_fDestAlpha;
	}

}

//=============================================================================
//	�`�揈��
//=============================================================================
void CCharaParts::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DMATERIAL9 matDef;		//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;			//�}�e���A���f�[�^�̃|�C���^
	float fOrgMatAlpha = 0.0f;
	//�}�g���b�N�X�̌v�Z
	CUtilityMath::CalWorldMatrix(&m_mtxWorld,m_Pos,m_Rot,m_pParent,m_Scale);

	//���[���h�}�g���b�N�X������W�����o���ĕۊǂ���
	m_WorldPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	if (m_bDrawFlag == true)
	{
		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		if (m_pBuffMat != NULL)
		{
			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
			{
				//���X�̒l��ۑ�����
				fOrgMatAlpha = pMat[nCntMat].MatD3D.Diffuse.a;

				//���_�F�̃��l�ɒl�𔽉f����
				pMat[nCntMat].MatD3D.Diffuse.a = m_fDiffuseAlpha;

				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				/*�e�N�X�`���̐ݒ�*/
				pDevice->SetTexture(0, m_pTexture);//�e�N�X�`���̐ݒ�(�g��Ȃ����NULL������)

				// ���f��(�p�[�c)�̕`��
				m_pMesh->DrawSubset(nCntMat);

				//�F��߂�
				pMat[nCntMat].MatD3D.Diffuse.a = fOrgMatAlpha;
			}
		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);

	}
}

//=============================================================================
//	�e�N�X�`�����蓖�ď���
//=============================================================================
void CCharaParts::BindTexture(LPCSTR Tag)
{
	//�e�N�X�`���N���X����e�N�X�`�������炤
	m_pTexture = CTexture::GetTexture(Tag);
}

//=============================================================================
//	�����x���f����
//=============================================================================
void CCharaParts::SetAlpha(float& fAlpha,int nCount)
{
	m_fOldAlpha = m_fDiffuseAlpha;
	if (fAlpha < 0.0f)
	{
		fAlpha = 0.0f;
	}
	else if (fAlpha > 1.0f)
	{
		fAlpha = 1.0f;
	}

	m_fDestAlpha = fAlpha;
	m_nCount = nCount;
}