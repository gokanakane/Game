//=============================================================================
//
// �e��{���� (C3DBullet)[bullet.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "bullet.h"
#include "manager.h"

#include "load.h"
#include "sceneBillboard.h"
#include "sceneX.h"
#include "game.h"

#include "debugProc.h"
#include "explosion.h"
#include "tutorial.h"

#include "LineOrbit.h"
#include "effect.h"
//=============================================================================
// �R���X�g���N�^���f�X�g���N�^	(CBulletBase)
//=============================================================================
C3DBullet::C3DBullet(int nPriority) : CScene(nPriority)
{
	m_Type = TYPE_NONE;
	m_fKnockBack = 0.0f;
	m_MoveResult = D3DXVECTOR3(0.0f,0.0f,0.0f);
}
C3DBullet::~C3DBullet()
{

}

//=============================================================================
// �ݒ菈��(CBulletBase)
//=============================================================================
void C3DBullet::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fSpeed, int nLife, int nID)
{
	m_pos = pos;
	m_rot = rot;
	m_fMove = fSpeed;
	m_nLife = nLife;
	m_nMaxLife = nLife;
	m_fHeight = pos.y;
	m_nID = (nID % 4);//�͈͊O�̐������������炻���0�`3�܂ł̐����ɂ���

	m_fCollisionRadius = 10.0f;
	m_fKnockBack = 7.0f;
	m_nCount = 0;
	//��ɉ�]�}�g���b�N�X���쐬���Ă���
	D3DXMatrixRotationYawPitchRoll(&m_mtxRotate, m_rot.y, m_rot.x, m_rot.z);

}

//=============================================================================
// ����������(CBulletBase)
//=============================================================================
HRESULT C3DBullet::Init(void)
{
	SetObjType(OBJTYPE_BULLET);//�^�C�v���Z�b�g

	/*�ϐ�������*/
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fMove = 0.0f;
	m_nLife = 0;
	m_nID = 0;
	m_fCollisionRadius = 10.0f;
	m_fKnockBack = 7.0f;
	D3DXMatrixRotationYawPitchRoll(&m_mtxRotate, m_rot.y, m_rot.x, m_rot.z);

	return S_OK;
}

//=============================================================================
// �I������(CBulletBase)
//=============================================================================
void C3DBullet::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V����(CBulletBase)
//=============================================================================
void C3DBullet::Update(void)
{
	m_posOld = m_pos;	//�P�t���[���O�̍��W��ϐ��Ɋi�[

	//�}�g���b�N�X���g�p���Ĉړ��ʂ����߂�
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, m_fMove);

	D3DXMATRIX Mtxmove, Mtxtrans;
	D3DXMatrixIdentity(&Mtxmove);

	D3DXMatrixTranslation(&Mtxtrans, move.x, move.y, move.z);
	D3DXMatrixMultiply(&Mtxmove, &Mtxmove, &Mtxtrans);

	//��]�}�g���b�N�X�͍ŏ��ɋ��߂����̂��g��
	D3DXMatrixMultiply(&Mtxmove, &Mtxmove, &m_mtxRotate);

	move = D3DXVECTOR3(Mtxmove._41, Mtxmove._42, Mtxmove._43);	//���W(�ړ���)�����o��

	//���Ƃ̓����蔻��
	CMeshField *pMesh = CManager::GetMeshField();
	float fHeight = pMesh->GetHeight(m_pos + move);
	if (m_pos.y < fHeight)
	{
		move.y = 0.0f;
	}

	m_MoveResult = move;	//���߂��������i�[
	m_pos += move;			//���W�Ɉړ��l���v���X

	//�ړ���̈ʒu�}�g���b�N�X�𐶐�
	D3DXMatrixTranslation(&m_mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	/*�f�o�b�N*/
	CDebugProc::Print("cf", "BULLET_ROT_Y", m_rot.y);
}

//=============================================================================
// �`�揈��(CBulletBase)
//=============================================================================
void C3DBullet::Draw(void)
{

}

//=============================================================================
// �I�u�W�F�N�g�Ƃ̓����蔻�菈��(CBulletBase)
//=============================================================================
bool C3DBullet::CollisionObject(CManager::DIRECTION* dir)
{//��������
	CScene* pScene = NULL;
	// �擪�̃I�u�W�F�N�g���擾
	pScene = CScene::GetTop(SCENEX_PRIORITY);
	while (pScene != NULL)
	{// �D�揇�ʂ�3�̃I�u�W�F�N�g��1��1�m���߂�
	 // �����̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// ���S�t���O�������Ă��Ȃ�����
			if (pScene->GetObjType() == CScene::OBJTYPE_SCENEX)
			{// �I�u�W�F�N�g�̎�ނ��m���߂�
				CSceneX *pSceneX = ((CSceneX*)pScene);		// CSceneX�փL���X�g(�^�̕ύX)
				if (pSceneX->GetCollsionType() == CSceneX::COLLISIONTYPE_BOX)
				{
					D3DXVECTOR3 vtxMin = pSceneX->GetVtxMin();
					D3DXVECTOR3 vtxMax = pSceneX->GetVtxMax();
					D3DXVECTOR3 OBJpos = pSceneX->GetPosition();

					if (m_pos.y <= OBJpos.y + vtxMax.y &&m_pos.y + m_fCollisionRadius >= OBJpos.y + vtxMax.y ||
						m_pos.y + m_fCollisionRadius >= OBJpos.y + vtxMin.y &&m_pos.y <= OBJpos.y + vtxMin.y ||
						m_pos.y + m_fCollisionRadius <= OBJpos.y + vtxMax.y  && m_pos.y >= OBJpos.y + vtxMin.y)
					{//�����͈͓��Ȃ�
						if (m_pos.z - m_fCollisionRadius <= OBJpos.z + vtxMax.z &&
							m_pos.z + m_fCollisionRadius >= OBJpos.z + vtxMin.z)
						{// z�͈̔͂̒�
							if (m_posOld.x + m_fCollisionRadius <= OBJpos.x + vtxMin.x
								&& m_pos.x + m_fCollisionRadius > OBJpos.x + vtxMin.x)
							{// X���W�̒��ɍ����������
								*dir = CManager::DIR_LEFT_WEST;
								return true;
							}
							else if (m_posOld.x - m_fCollisionRadius >= OBJpos.x + vtxMax.x
								   && m_pos.x - m_fCollisionRadius < OBJpos.x + vtxMax.x)
							{// X���W�̒��ɉE���������
								*dir = CManager::DIR_RIGHT_EAST;
								return true;
							}
						}

						if (m_pos.x - m_fCollisionRadius <= OBJpos.x + vtxMax.x &&
							m_pos.x + m_fCollisionRadius >= OBJpos.x + vtxMin.x)
						{// x�͈̔͂̒�
							if (m_posOld.z + m_fCollisionRadius <= OBJpos.z + vtxMin.z
								&& m_pos.z + m_fCollisionRadius > OBJpos.z + vtxMin.z)
							{// Z���W�̒��Ɏ�O���������
								*dir = CManager::DIR_DOWN_SOUTH;
								return true;
							}
							else if (m_posOld.z - m_fCollisionRadius >= OBJpos.z + vtxMax.z
								&& m_pos.z - m_fCollisionRadius < OBJpos.z + vtxMax.z)
							{// Z���W�̒��Ɍ�납�������
								*dir = CManager::DIR_UP_NORTH;
								return true;
							}
						}

					}
				}
			}
		}

		pScene = pSceneNext;	//�L�^��������T�����邽�߂Ƀ|�C���^���킽��
	}

	return false;
}
bool C3DBullet::SimpleCollision(void)
{//�����Ȃ�(������Ԃ����ɗL�̂ق����g��)
	CManager::DIRECTION dir;
	return CollisionObject(&dir);
}

//=============================================================================
// �ǔ�����(CBulletBase)
//=============================================================================
void C3DBullet::Homing(D3DXVECTOR3 HomingPos)
{
	D3DXQUATERNION Quat,HomingQuat,dest;
	//���݂̊p�x�}�g���b�N�X����N�H�[�^�j�I���𐶐�
	D3DXQuaternionRotationMatrix(&Quat,&m_mtxRotate);

	//�e�̈ʒu�x�N�g���ƃz�[�~���O���������̈ʒu�x�N�g������N�H�[�^�j�I�����쐬(Y����]�̂�)
	float fRotY = atan2f((HomingPos.x - m_pos.x), (HomingPos.z - m_pos.z));
	CUtilityMath::RotateNormarizePI(&fRotY);
	D3DXQuaternionRotationYawPitchRoll(&HomingQuat,fRotY,0.0f,0.0f);

	//��̃N�H�[�^�j�I�������ʕ�Ԃ���
	D3DXQuaternionSlerp(&dest,&Quat,&HomingQuat, BULLET_HOMING_COEFFICIENT);

	//���߂��N�H�[�^�j�I�����p�x�}�g���b�N�X�ɕϊ�
	D3DXMatrixRotationQuaternion(&m_mtxRotate,&dest);
}
//=============================================================================
//
// ���f���e���� (CModelBullet)[bullet.cpp]
// Author : Kodama Yuto
//
//=============================================================================
//=============================================================================
// �R���X�g���N�^���f�X�g���N�^	(CModelBullet)
//=============================================================================
CModelBullet::CModelBullet(int nPriority) : C3DBullet(nPriority)
{
	m_pModel = NULL;
	m_pOrbit = NULL;
	m_nCntEffect = 0;

}
CModelBullet::~CModelBullet()
{

}
//=============================================================================
// �ݒ菈��(CModelBullet)
//=============================================================================
CModelBullet* CModelBullet::Create(void)
{
	CModelBullet* pBullet = NULL;
	pBullet = new CModelBullet(BULLET_PRIORITY);
	if (pBullet != NULL)
	{
		pBullet->Init();
	}
	return pBullet;
}
//=============================================================================
// �ݒ菈��(CModelBullet)
//=============================================================================
void CModelBullet::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CLoad::MODEL model, BULLET_PROPERTY type,int nID, D3DXVECTOR3 RotateOffset)
{
	m_pModel = CSceneX::Create(pos,rot,D3DXVECTOR3(1.0f,1.0f,1.0f),model,0);
	m_Prop = type;
	//float fSpeed = 1.0f;

	//�^�C�v�ɂ���ď����𕪂���
	float fSpeed = 3.0f;
	int nLife = 100;
	switch (m_Prop)
	{
	case TYPE_HIGHSPEED:
		fSpeed = 8.0f;
		m_fKnockBack = 6.0f;
		m_pOrbit = CLineOrbit::Create();
		if (m_pOrbit != NULL)
		{
			m_pOrbit->Set(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, &m_mtxTrans, "",
				D3DXCOLOR(0.0f, 0.6f, 1.0f, 0.7f), 40, 1);
		}
		break;
	case TYPE_STINGER:
		fSpeed = 6.0f;
		m_fKnockBack = 9.0f;
		break;
	case TYPE_KNOCKBACK:
		fSpeed = 3.0f;
		m_fKnockBack = 20.0f;
		break;
	case TYPE_REFLECT:
		m_fKnockBack = 8.0f;
		break;
	case TYPE_MACHINEGUN:
		m_fKnockBack = 0.0f;
		fSpeed = 7.0f;
		nLife = 40;
		break;
	case TYPE_SHOTGUN:
		m_fKnockBack = 3.0f;
		fSpeed = 7.0f;
		nLife = 20;
		break;
	case TYPE_SHOTGUN_MEDIUM:
		m_fKnockBack = 3.0f;
		fSpeed = 6.5f;
		nLife = 20;
		break;
	case TYPE_SHOTGUN_SLOW:
		m_fKnockBack = 3.0f;
		fSpeed = 6.0f;
		nLife = 20;
		break;
	case TYPE_MISSILE_CENTER:
		fSpeed = 3.5f;
		m_fKnockBack = 1.0f;
		nLife = 80;
		break;
	case TYPE_MISSILE_SIDE:
		fSpeed = 4.0f;
		m_fKnockBack = 1.0f;
		nLife = 80;
		break;
	case TYPE_BOMB:
		fSpeed = 3.5f;
		m_fKnockBack = 10.0f;
		nLife = 60;
		break;
	default:
		fSpeed = 5.0f;
		m_fKnockBack = 6.0f;
		nLife = 30;
		break;
	}
	m_modelRotateOffSet = RotateOffset;
	C3DBullet::Set(pos,
		rot,
		fSpeed,
		nLife,
		nID);
}

//=============================================================================
// ����������(CModelBullet)
//=============================================================================
HRESULT CModelBullet::Init(void)
{
	C3DBullet::Init();
	m_pHomingChara = NULL;
	m_Type = TYPE_MODEL;
	m_fBombHaight = 100.0f;
	return S_OK;
}

//=============================================================================
// �I������(CModelBullet)
//=============================================================================
void CModelBullet::Uninit(void)
{
	CExplosion3D* p3D = NULL;
	switch (m_Prop)
	{
	case TYPE_HIGHSPEED:
		if (m_pOrbit != NULL)
		{
			m_pOrbit->Uninit();
			m_pOrbit = NULL;
		}
		break;
	case TYPE_KNOCKBACK:
		p3D = CExplosion3D::Create();
		if (p3D != NULL) { p3D->Set(GetPosition(), 0.001f, 80.0f, 120, 0.01f); }
		break;
	case TYPE_STINGER:
		p3D = CExplosion3D::Create();
		if (p3D != NULL) { p3D->Set(GetPosition(), 0.001f, 30.0f, 60, 0.01f); }
		break;
	case TYPE_REFLECT:
		p3D = CExplosion3D::Create();
		if (p3D != NULL) { p3D->Set(GetPosition(), 0.001f, 30.0f, 60, 0.01f); }
		break;
	case TYPE_MISSILE_CENTER:
		p3D = CExplosion3D::Create();
		if (p3D != NULL) { p3D->Set(GetPosition(), 0.001f, 30.0f, 60, 0.01f); }
		break;
	case TYPE_MISSILE_SIDE:
		p3D = CExplosion3D::Create();
		if (p3D != NULL) { p3D->Set(GetPosition(), 0.001f, 30.0f, 60, 0.01f); }
		break;
	case TYPE_BOMB:
		p3D = CExplosion3D::Create();
		if (p3D != NULL) { p3D->Set(GetPosition(), 0.001f, 80.0f, 120, 0.01f);
						   p3D->SetID(GetID());}
		break;

	default:
		break;
	}

	//���f��������
	if (m_pModel != NULL)
	{
		m_pModel->Uninit();
		m_pModel = NULL;
	}

	C3DBullet::Uninit();
}

//=============================================================================
// �X�V����(CModelBullet)
//=============================================================================
void CModelBullet::Update(void)
{
	int& nLife = GetLife();
	nLife--;
	m_nCntEffect++;
	m_nCount++;

	D3DXVECTOR3 pos = CModelBullet::GetPosition();
	if (m_Prop == TYPE_MISSILE_CENTER || m_Prop == TYPE_MISSILE_SIDE || m_Prop == TYPE_STINGER || m_Prop == TYPE_REFLECT)
	{//�~�T�C��
		if (m_nCntEffect % 6 == 0)
		{
			CEffect::Create(pos, 4, 4);
		}

		if (m_pHomingChara != NULL)
		{
			Homing(m_pHomingChara->GetPosition());
		}
	}
	else if (m_Prop == TYPE_KNOCKBACK || m_Prop == TYPE_BOMB)
	{//����
		float fUp = sinf((float)m_nCount / (float) ((float)m_nMaxLife / 4.0f));
		fUp *= m_fBombHaight;//�萔���|����

		GetPosition().y = m_fHeight + fUp;

		//���Ƃ̓����蔻��
		CMeshField *pMesh = CManager::GetMeshField();
		float fHeight = pMesh->GetHeight(GetPosition());
		if (GetPosition().y < fHeight)
		{
			Uninit();
			return;
		}

		if (m_nCntEffect % 6 == 0)
		{
			CEffect::Create(pos, 5, 5);
		}
	}
	else if (m_Prop == TYPE_MACHINEGUN)
	{//	�}�V���K��
		if (m_nCntEffect % 7 == 0)
		{
			CEffect::Create(pos, 5, 7);
		}
		if (m_nCntEffect % 14 == 0)
		{
			CEffect::Create(pos, 5, 8);

		}
	}
	else if (m_Prop == TYPE_NORMAL)
	{//�S�~
		if (m_nCntEffect % 6 == 0)
		{
			CEffect::Create(pos, 6, 5);
		}
	}

	C3DBullet::Update();

	//�e���f���ɐ������p�x��ݒ肷��
	if (m_pModel != NULL)
	{
		m_pModel->SetPosition(GetPosition());

		D3DXVECTOR3 Rotate = m_modelRotateOffSet + GetRotation();
		CUtilityMath::RotateNormarizePI(&Rotate);
		m_pModel->SetRot(Rotate);
	}

	//�����蔻��
	if (m_Prop != TYPE_BOMB)
	{//���e�͒n�`�𖳎�����(�Ȃ�ׂ������������ɓ�����Ȃ��悤��)
		if (SimpleCollision())
		{
			Uninit();//�������Ă��������
			return;
		}
	}
	//�̗͔���
	if (nLife < 0)
	{
		Uninit();//����0�Ȃ����
		return;
	}
}

//=============================================================================
// �`�揈��(CModelBullet)
//=============================================================================
void CModelBullet::Draw(void)
{

}

//=============================================================================
// ���f���̑傫���ݒ菈��(CModelBullet)
//=============================================================================
void  CModelBullet::SetModelScale(const D3DXVECTOR3& scale)
{
	if (m_pModel != NULL)
	{
		m_pModel->SetScale(scale);
	}
}

//=============================================================================
// ���f���̌����ݒ菈��(CModelBullet)
//=============================================================================
void  CModelBullet::SetModelRot(const D3DXVECTOR3& rot)
{
	if (m_pModel != NULL)
	{
		m_pModel->SetRot(rot);
	}
}

//=============================================================================
// ���ˏ���(CModelBullet)
//=============================================================================
void CModelBullet::Reflect(CManager::DIRECTION dir)
{
	D3DXVECTOR3& rot = GetRotation();

	switch (dir)
	{
	case CManager::DIR_RIGHT_EAST:	//��(+X����)
		rot.y *= -1.0f;		//���]
		break;
	case CManager::DIR_LEFT_WEST:	//��(-X����)
		rot.y *= -1.0f;		//���]
		break;
	case CManager::DIR_DOWN_SOUTH:  //��(-Z����)
		rot.y = (rot.y + D3DX_PI) * -1.0f;	//���Ώ́����]
		break;
	case CManager::DIR_UP_NORTH:	//�k(+Z����)
		rot.y = (rot.y + D3DX_PI) * -1.0f;  //���Ώ́����]
		break;
	default:
		return;	//�����ꂻ��ȊO�̒l�������Ă����Ƃ��͏������甲����
		break;
	}
	CUtilityMath::RotateNormarizePI(&rot.y);

	//���f���ɂ��p�x��ݒ�
	SetModelRot(rot);
}

//=============================================================================
//
// �����e���� (CWordBullet)[bullet.cpp]
// Author : Kodama Yuto
//
//=============================================================================
//=============================================================================
// �R���X�g���N�^���f�X�g���N�^	(CWordBullet)
//=============================================================================
CWordBullet::CWordBullet(int nPriority) : C3DBullet(nPriority)
{
	m_pWord = NULL;
}
CWordBullet::~CWordBullet()
{

}

//=============================================================================
// ��������(CWordBullet)
//=============================================================================
CWordBullet* CWordBullet::Create(void)
{
	CWordBullet* pBullet = NULL;
	pBullet = new CWordBullet(BULLET_PRIORITY);
	if (pBullet != NULL)
	{
		pBullet->Init();
	}
	return pBullet;
}

//=============================================================================
// �ݒ菈��(CWordBullet)
//=============================================================================
void CWordBullet::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fSpeed, int nLife, int nWordNum, int nID)
{
	C3DBullet::Set(pos, rot,fSpeed,nLife,nID);

	m_pWord = CSceneBillBoard::Create(pos,20.0f,20.0f,"WORD");
	if (m_pWord != NULL) { m_pWord->SetTexture(D3DXVECTOR2(0.0f + ((nWordNum / 5) * 0.1f), 0.0f + ((nWordNum % 5) * 0.2f)),
											   D3DXVECTOR2(0.1f + ((nWordNum / 5) * 0.1f), 0.2f + ((nWordNum % 5) * 0.2f))); };
}

//=============================================================================
// ����������(CWordBullet)
//=============================================================================
HRESULT CWordBullet::Init(void)
{
	C3DBullet::Init();
	m_Type = TYPE_WORD;

	return S_OK;
}

//=============================================================================
// �I������(CWordBullet)
//=============================================================================
void CWordBullet::Uninit(void)
{
	if (m_pWord != NULL)
	{
		m_pWord->Uninit();
		m_pWord = NULL;
	}

	C3DBullet::Uninit();
}

//=============================================================================
// �X�V����(CWordBullet)
//=============================================================================
void CWordBullet::Update(void)
{
	int& nLife = GetLife();
	nLife--;
	C3DBullet::Update();
	if (m_pWord != NULL)
	{
		m_pWord->Setpos(GetPosition());
	}

	if (SimpleCollision())
	{//�������Ă����
		Uninit();
		return;
	}
	if (nLife < 0)
	{
		Uninit();
		return;
	}
}

//=============================================================================
// �`�揈��(CWordBullet)
//=============================================================================
void CWordBullet::Draw(void)
{

}

