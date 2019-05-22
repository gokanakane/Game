//=============================================================================
//
// ���[�V�������� [motion.h]
// Author : Eisuke Sakagawa
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "motion.h"			// ���[�V����
#include "manager.h"		// �}�l�[�W���[
#include "input.h"			// ����
#include "renderer.h"		// �����_���[

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^								(public)	*** CMotion ***
//=============================================================================
CMotion::CMotion()
{
	// �����l�ݒ�
	m_nCntFrame = 0;							// �t���[���J�E���^
	m_nEditBFrame = -1;
	m_bEditBFrame = false;
	m_bSetrot = false;

	m_bAnimStop = false;
	m_bAnimChange = true;
	m_nAnimNextNum = 0;
	m_nAnimNum = 0;
	m_nAnimKeyNextNum = 0;
	m_nAnimKeyNum = 0;
}

//=============================================================================
// �f�X�g���N�^									(public)	*** CMotion ***
//=============================================================================
CMotion::~CMotion()
{

}

//=============================================================================
// ����������									(public)	*** CMotion ***
//=============================================================================
HRESULT CMotion::Init(void)
{
	return S_OK;
}

//=============================================================================
// �I������										(public)	*** CMotion ***
//=============================================================================
void CMotion::Uninit(void)
{

}

//=============================================================================
// �X�V����										(public)	*** CMotion ***
//=============================================================================
void CMotion::Update(int nModelMax, ANIM_INFO *AnimInfo, CModel *pModel, D3DXVECTOR3 posParent)
{
	if (m_nAnimNum != m_nAnimNextNum || m_bSetrot == true)
	{
		m_nCntFrame = 0;
		m_bAnimChange = true;
		m_nAnimNum = m_nAnimNextNum;
		m_nAnimKeyNum = m_nAnimKeyNextNum;

		if (m_bEditBFrame == false)
		{
			m_nEditBFrame = -1;
		}

		if (m_bSetrot == true)
		{
			pModel[0].Setpos(posParent + AnimInfo[m_nAnimNum].aKeyInfo[(m_nAnimKeyNum) % AnimInfo[m_nAnimNum].nKeyMax].aKey[0].pos);

			for (int nCntModel = 0; nCntModel < nModelMax; nCntModel++)
			{
				pModel[nCntModel].Setrot(AnimInfo[m_nAnimNum].aKeyInfo[(m_nAnimKeyNum) % AnimInfo[m_nAnimNum].nKeyMax].aKey[nCntModel].rot);
			}
			m_nCntFrame = AnimInfo[m_nAnimNum].aKeyInfo[m_nAnimKeyNum].nFrame;

			m_bSetrot = false;
		}
	}

	if (m_bAnimStop == false)
	{
		D3DXVECTOR3 Dest, Add;
		float fDiff, frac;

		if (m_bAnimChange == true)
		{
			if (m_bEditBFrame == false)
			{
				frac = (AnimInfo[m_nAnimNum].nBrendFrame - m_nCntFrame) * 1.0f;
			}
			else
			{
				frac = (m_nEditBFrame - m_nCntFrame) * 1.0f;
			}
		}
		else
		{
			frac = (AnimInfo[m_nAnimNum].aKeyInfo[m_nAnimKeyNum].nFrame - m_nCntFrame) * 1.0f;
		}

		if (m_bAnimChange == true)
		{
			Dest = posParent + AnimInfo[m_nAnimNum].aKeyInfo[0].aKey[0].pos;
		}
		else
		{
			Dest = posParent + AnimInfo[m_nAnimNum].aKeyInfo[(m_nAnimKeyNum + 1) % AnimInfo[m_nAnimNum].nKeyMax].aKey[0].pos;
		}

		// �����ݒ�
		fDiff = (Dest.x - pModel[0].Getpos().x);
		// ���݌����ݒ�
		Add.x = fDiff / frac;

		// �����ݒ�
		fDiff = (Dest.y - pModel[0].Getpos().y);
		// ���݌����ݒ�
		Add.y = fDiff / frac;

		// �����ݒ�
		fDiff = (Dest.z - pModel[0].Getpos().z);
		// ���݌����ݒ�
		Add.z = fDiff / frac;

		pModel[0].Setpos(pModel[0].Getpos() + Add);

		/*CFont *pFont = CRenderer::GetFont(CFont::FONTNUM_TEST);
		pFont->SetMessage(CFont::SETTYPE_ADD, "%.2f\n", fDiff);
		pFont->SetMessage(CFont::SETTYPE_ADD, "%.2f\n", Dest.y);
		pFont->SetMessage(CFont::SETTYPE_ADD, "%.2f\n", frac);
		pFont->SetMessage(CFont::SETTYPE_ADD, "%.2f\n", pModel[0].Getpos().y);*/

		for (int nCntModel = 0; nCntModel < nModelMax; nCntModel++)
		{
			if (m_bAnimChange == true)
			{
				// �����ύX
				Dest = AnimInfo[m_nAnimNum].aKeyInfo[0].aKey[nCntModel].rot;
			}
			else
			{
				// �����ύX
				Dest = AnimInfo[m_nAnimNum].aKeyInfo[(m_nAnimKeyNum + 1) % AnimInfo[m_nAnimNum].nKeyMax].aKey[nCntModel].rot;
			}

			{
				// �ڕW��������
				if (Dest.x > D3DX_PI) { Dest.x -= D3DX_PI * 2.0f; }
				if (Dest.x < -D3DX_PI) { Dest.x += D3DX_PI * 2.0f; }

				// �����ݒ�
				fDiff = (Dest.x - pModel[nCntModel].Getrot().x);

				// ������������
				if (fDiff > D3DX_PI) { fDiff -= D3DX_PI * 2.0f; }
				if (fDiff < -D3DX_PI) { fDiff += D3DX_PI * 2.0f; }

				// ���݌����ݒ�
				Add.x = fDiff / frac;

				// �ڕW��������
				if (Dest.y > D3DX_PI) { Dest.y -= D3DX_PI * 2.0f; }
				if (Dest.y < -D3DX_PI) { Dest.y += D3DX_PI * 2.0f; }

				// �����ݒ�
				fDiff = (Dest.y - pModel[nCntModel].Getrot().y);

				// ������������
				if (fDiff > D3DX_PI) { fDiff -= D3DX_PI * 2.0f; }
				if (fDiff < -D3DX_PI) { fDiff += D3DX_PI * 2.0f; }

				// ���݌����ݒ�
				Add.y = fDiff / frac;

				// �ڕW��������
				if (Dest.z > D3DX_PI) { Dest.z -= D3DX_PI * 2.0f; }
				if (Dest.z < -D3DX_PI) { Dest.z += D3DX_PI * 2.0f; }

				// �����ݒ�
				fDiff = (Dest.z - pModel[nCntModel].Getrot().z);

				// ������������
				if (fDiff > D3DX_PI) { fDiff -= D3DX_PI * 2.0f; }
				if (fDiff < -D3DX_PI) { fDiff += D3DX_PI * 2.0f; }

				// ���݌����ݒ�
				Add.z = fDiff / frac;
			}

			pModel[nCntModel].Setrot(pModel[nCntModel].Getrot() + Add);
		}

		m_nCntFrame++;

		if (m_bAnimChange == true)
		{
			if (m_bEditBFrame == false)
			{
				if (m_nCntFrame % AnimInfo[m_nAnimNum].nBrendFrame == 0)
				{
					m_nCntFrame = 0;
					m_bAnimChange = false;
				}
			}
			else
			{
				if (m_nCntFrame % m_nEditBFrame == 0)
				{
					m_nCntFrame = 0;
					m_bAnimChange = false;
					m_nEditBFrame = -1;
					m_bEditBFrame = false;
				}
			}
		}
		else
		{
			if (m_nCntFrame % AnimInfo[m_nAnimNum].aKeyInfo[m_nAnimKeyNum].nFrame == 0)
			{
				if (m_nAnimKeyNum + 1 == AnimInfo[m_nAnimNum].nKeyMax)
				{
					if (AnimInfo[m_nAnimNum].bLoop == 0)
					{
						m_nAnimNextNum = 0;
					}

					m_nAnimKeyNum = 0;
					m_nCntFrame = 0;
				}
				else
				{
					m_nAnimKeyNum = (m_nAnimKeyNum + 1) % AnimInfo[m_nAnimNum].nKeyMax;
					m_nCntFrame = 0;
				}
			}
		}
	}
}

//=============================================================================
// �`�揈��										(public)	*** CMotion ***
//=============================================================================
void CMotion::Draw(void)
{

}