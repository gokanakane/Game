//=============================================================================
//
// �����N���X [explosion.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "explosion.h"

#include "manager.h"
#include "sound.h"
//=============================================================================
// �R���X�g���N�^&�f�X�g���N�^
//=============================================================================
CExplosion3D::CExplosion3D(int pri, OBJTYPE type) : CMeshSphere(pri, type)
{
	m_bNotDup = false;
	m_nID = -1;
}
CExplosion3D::~CExplosion3D()
{

}

//=============================================================================
// ��������
//=============================================================================
CExplosion3D* CExplosion3D::Create(void)
{
	CExplosion3D* pExplosion = NULL;

	pExplosion = new CExplosion3D(EXPLOSION_PRIORITY, OBJTYPE_EXPLOSION);

	if (pExplosion != NULL)
	{
		pExplosion->Init();
	}

	return pExplosion;
}

//=============================================================================
// �ݒ菈��
//=============================================================================
void CExplosion3D::Set(D3DXVECTOR3 pos, float fStartSize, float fDestSize, int nLife, float fAnimSpeed, LPCSTR Tag)
{//�Z�k�ݒ��
	CMeshSphere::Set(pos, Tag, 40, 40,
		D3DXVECTOR3(fStartSize, fStartSize, fStartSize), D3DXCOLOR(0.90f,0.50f,0.05f,0.5f), D3DXVECTOR3(0.0f,0.0f,0.0f));
	CMeshSphere::SetTexAnim(D3DXVECTOR2(fAnimSpeed, -fAnimSpeed));
	CMeshSphere::SetCntAnimTime(1);

	m_fDestSize = fDestSize;
	m_fSize = fStartSize;
	m_DefaultSize = fStartSize;
	m_nLife = nLife;
	m_nExpandTime = nLife;
	m_nCount = 0;
	m_spinSpeed = D3DXVECTOR3(0.0f, 0.3f, 0.0f);	//�f�t�H���g�ŏ�����

	//���d�A�j���[�V���������邽�߂ɉ����d�˂�
	if (m_bNotDup == false)
	{
		CExplosion3D* p3D = CExplosion3D::Create();
		p3D->IsNotDup(true);
		if (p3D != NULL) { p3D->Set(pos, fStartSize, fDestSize, nLife, -0.01f); }

		p3D = CExplosion3D::Create();
		p3D->IsNotDup(true);
		if (p3D != NULL) { p3D->Set(pos, fStartSize, fDestSize, nLife, 0.04f); }

		p3D = CExplosion3D::Create();
		p3D->IsNotDup(true);
		if (p3D != NULL) { p3D->Set(pos, fStartSize, fDestSize, nLife, -0.03f); }

		CSound* pSound = CManager::GetSound();

		if (pSound != NULL) {
			pSound->SetVolume(CSound::SOUND_LABEL_SE_EXPLOSION, 5.0f);
			pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
		}
	}
	m_bNotDup = true;

}
void CExplosion3D::SetEX(D3DXVECTOR3 pos, float fStartSize, float fDestSize, int nLife, float fAnimSpeed,
	D3DXVECTOR3 rot, D3DXCOLOR col, LPCSTR Tag, int nMesh, int nExpandTime, D3DXVECTOR3 spinSpeed)
{//�ڍאݒ��
	CMeshSphere::Set(pos, Tag, nMesh, nMesh,
		D3DXVECTOR3(fStartSize, fStartSize, fStartSize) ,col,rot);

	CMeshSphere::SetTexAnim(D3DXVECTOR2(fAnimSpeed,-fAnimSpeed));
	CMeshSphere::SetCntAnimTime(1);

	m_nCount = 0;

	m_fDestSize = fDestSize;
	m_fSize = fStartSize;
	m_DefaultSize = fStartSize;
	m_nLife = nLife;
	m_nExpandTime = nExpandTime;
	m_spinSpeed = spinSpeed;

	//���d�A�j���[�V���������邽�߂ɉ����d�˂�
	if (m_bNotDup == false)
	{
		CExplosion3D* p3D = CExplosion3D::Create();
		p3D->IsNotDup(true);
		if (p3D != NULL) { p3D->SetEX(pos, fStartSize, fDestSize, nLife,-0.005f,
										rot,col,Tag,nMesh,nExpandTime,spinSpeed); }

		p3D = CExplosion3D::Create();
		p3D->IsNotDup(true);
		if (p3D != NULL) { p3D->SetEX(pos, fStartSize, fDestSize, nLife, 0.02f,
										rot, col, Tag, nMesh, nExpandTime, spinSpeed); }

		p3D = CExplosion3D::Create();
		p3D->IsNotDup(true);
		if (p3D != NULL) { p3D->SetEX(pos, fStartSize, fDestSize, nLife, -0.015f,
										rot, col, Tag, nMesh, nExpandTime, spinSpeed); }

	}
	m_bNotDup = true;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CExplosion3D::Init(void)
{
	m_nCount = 0;
	m_bNotDup = false;
	m_spinSpeed = D3DXVECTOR3(0.0f,0.0f,0.0f);
	CMeshSphere::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CExplosion3D::Uninit(void)
{
	CMeshSphere::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CExplosion3D::Update(void)
{
	//�T�C�Y�X�V
	D3DXVECTOR3 Size = D3DXVECTOR3(m_DefaultSize, m_DefaultSize, m_DefaultSize);
	D3DXVECTOR3 SizeDest = D3DXVECTOR3(m_fDestSize, m_fDestSize, m_fDestSize);

	if (m_nCount <= m_nExpandTime)
	{
		float fTime = ((float)(m_nCount + 1) / (float)m_nExpandTime);
		fTime = CEasingFunc::Easing(CEasingFunc::EASE_OUT_EXPO,fTime);
		D3DXVec3Lerp(&Size, &Size, &SizeDest, fTime);
	}

	GetScale() = Size;

	m_fSize = Size.x;	//�ǂ�������Ȃ̂œK���Ȑ��l������

	//��](spinSpeed�����Z����)
	GetRotation() += m_spinSpeed;

	//�e�N���X��Update
	CMeshSphere::Update();

	//���Ŕ���
	if (m_nCount > m_nLife)
	{
		Uninit();
	}
	m_nCount++;
}

//=============================================================================
// �`�揈��
//=============================================================================
void CExplosion3D::Draw(void)
{
	//�f�o�C�X���擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING,FALSE);

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CMeshSphere::Draw();

	//�ݒ�����Ƃɖ߂�
	pRenderer->ResetRenderState();
}