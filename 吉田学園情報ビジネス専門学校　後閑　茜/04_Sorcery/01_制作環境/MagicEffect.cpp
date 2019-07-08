//=============================================================================
//
// ���@�G�t�F�N�g���� [MagicEffect.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "manager.h"
#include "effectBase.h"
#include "magicEffect.h"
#include "playerBase.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
int CMagicEffect::m_nIndex = 0;

//*****************************************************************************
// ��class CMagicEffect
//*****************************************************************************
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMagicEffect::CMagicEffect()
{
	//move�̊p�x��ݒ�
	Set(m_nIndex);
	m_nIndex++;
	if ((m_nIndex%MAX_MAGICEFFECTCREATE) == 0)
	{// �����������I�����
		m_nIndex = 0;
	}
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMagicEffect::~CMagicEffect() {}
//=============================================================================
// ����������
//=============================================================================
HRESULT CMagicEffect::Init(void)
{
	CEffect::Init();

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CMagicEffect::Uninit(void)
{
	CEffect::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CMagicEffect::Update(void)
{

	m_pos = CScene2D::GetPos();
	m_pos += m_move;
	SetPos(m_pos);
	m_nLife--;

	if (m_nLife <= 0)
	{
		this->Uninit();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CMagicEffect::Draw(void)
{
	CEffect::Draw();
}
//=============================================================================
// ���@�g�p���G�t�F�N�g�̐���
//=============================================================================
void CMagicEffect::SetMagicEffect(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < MAX_MAGICEFFECTCREATE; nCnt++)
	{
		switch (CManager::GetCharactorSelect())
		{
		case CManager::CHARACTORSTATE_DORAGON:
			Create(pos, EFFECTTYPE_MAGIC, EFFECTCOL_DORAGON);
			break;
		case CManager::CHARACTORSTATE_KARNERIAN:
			Create(pos, EFFECTTYPE_MAGIC, EFFECTCOL_KARNERIAN);
			break;
		case CManager::CHARACTORSTATE_VIVIAN:
			Create(pos, EFFECTTYPE_MAGIC, EFFECTCOL_VIVIAN);
			break;
		case CManager::CHARACTORSTATE_AREISTA:
			Create(pos, EFFECTTYPE_MAGIC, EFFECTCOL_AREISTA);
			break;
		case CManager::CHARACTORSTATE_RENGE:
			Create(pos, EFFECTTYPE_MAGIC, EFFECTCOL_RENGE);
			break;
		case CManager::CHARACTORSTATE_LILIY:
			Create(pos, EFFECTTYPE_MAGIC, EFFECTCOL_LILIY);
			break;

		}
	}
}
//=============================================================================
// ��΂��p�x��ݒ�
//=============================================================================
void CMagicEffect::Set(int nId)
{
	float fSpeed = 4.0f;

	switch (nId)
	{
	case 0:
		m_move.x = sinf(D3DX_PI)*fSpeed;
		m_move.y = cosf(D3DX_PI)*fSpeed;
		break;

	case 1:
		m_move.x = sinf(D3DX_PI*-0.75f)*fSpeed;
		m_move.y = cosf(D3DX_PI*-0.75f)*fSpeed;
		break;

	case 2:
		m_move.x = sinf(D3DX_PI* -0.5f)*fSpeed;
		m_move.y = cosf(D3DX_PI* -0.5f)*fSpeed;
		break;

	case 3:
		m_move.x = sinf(D3DX_PI* -0.25f)*fSpeed;
		m_move.y = cosf(D3DX_PI* -0.25f)*fSpeed;
		break;

	case 4:
		m_move.x = sinf(0.0f)*fSpeed;
		m_move.y = cosf(0.0f)*fSpeed;
		break;

	case 5:
		m_move.x = sinf(D3DX_PI* 0.75f)*fSpeed;
		m_move.y = cosf(D3DX_PI* 0.75f)*fSpeed;
		break;

	case 6:
		m_move.x = sinf(D3DX_PI* 0.5f)*fSpeed;
		m_move.y = cosf(D3DX_PI* 0.5f)*fSpeed;
		break;

	case 7:
		m_move.x = sinf(D3DX_PI* 0.25f)*fSpeed;
		m_move.y = cosf(D3DX_PI* 0.25f)*fSpeed;
		break;
	}
}