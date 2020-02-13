//=============================================================================
//
// 3D���f������ [sceneX.cpp]
// Author : �ڍ� ������
//
//=============================================================================
#include "sceneX.h"
#include "input.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "load.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define SCENEX_SIZE	(1.0f)	// �T�C�Y�̒���

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
int CSceneX::m_nTranslucentBush[4] = {0,0,0,0};

//=============================================================================
// 3D���f���N���X�̃R���X�g���N�^
//=============================================================================
CSceneX::CSceneX(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// �l���N���A
	m_pTexture = NULL;						// �e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
	m_pMesh = NULL;							// ���b�V�����i���_���j�ւ̃|�C���^
	m_pBuffMat = NULL;						// �}�e���A�����ւ̃|�C���^
	m_nNumMat = 0;							// �}�e���A�����̐�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//�傫��
	m_CollisionType = COLLISIONTYPE_NONE;
	m_nCollsionNum = 0;
	m_bDraw = true;
	m_nCamera = 0;

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_bTranslucent[nCnt] = false;
	}
	m_pParentMatrix = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSceneX::~CSceneX()
{
}

//=============================================================================
// �I�u�W�F�N�g�̐�������
//=============================================================================
CSceneX *CSceneX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Scale, CLoad::MODEL model, int nCollision)
{
	CSceneX *pSceneX = NULL;

	if (pSceneX == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pSceneX = new CSceneX;

		if (pSceneX != NULL)
		{
			pSceneX->m_ModelType = model;
			pSceneX->BindModel(CLoad::GetBuffMat(model), CLoad::GetNumMat(model), CLoad::GetMesh(model));
			pSceneX->m_pos = pos;
			pSceneX->m_rot = Rot;
			pSceneX->m_Scale = Scale;
			pSceneX->m_CollisionType = (COLLISIONTYPE)nCollision;
			pSceneX->Init(pos);
		}
	}

	return pSceneX;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSceneX::Init(D3DXVECTOR3 pos)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_SCENEX);

	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	SetPosition(pos);

	// ���_���W�̐ݒ�
	SetVtx();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSceneX::Uninit(void)
{
	//�|�C���^��NULL�`�F�b�N (��)
	if (m_pTexture != NULL)
	{
		for (int nCnt = 0; nCnt < (int)m_nNumMat; nCnt++)
		{
			//�|�C���^���̃|�C���^��NULL�`�F�b�N (�Ƌ�)
			if (m_pTexture[nCnt] != NULL)
			{
				//�e�N�X�`���j��
				//m_pTexture[nCnt]->Release();
				//m_pTexture[nCnt] = NULL;
			}
		}
		//���������J�� (���)
		//delete[] m_pTexture;
		//NULL������ (�X�n)
		//m_pTexture = NULL;
	}
	// �I�u�W�F�N�g�̉��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CSceneX::Update(void)
{
#ifdef _DEBUG
	//CDebugProc::Print("cfccfccfc", "ModelPos : x", m_pos.x, "f", "   y", m_pos.y, "f", "  z", m_pos.z, "f");
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void CSceneX::Draw(void)
{
#if 1

	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;					// �}�e���A���f�[�^�ւ̃|�C���^

	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	if (m_ModelType != CLoad::MODEL_BUSH)
	{
		// ���C�g�̖�����
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	}

	//���_�@���̎������K��
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	//�}�g���b�N�X�v�Z
	CUtilityMath::CalWorldMatrix(&m_mtxWorld,m_pos,m_rot,m_pParentMatrix,m_Scale);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);


	if (m_bDraw == true)
	{//���f�����������ԂȂ�
		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{

			if (m_bTranslucent[m_nCamera] == true)
			{	//���_�F�̃��l�ɒl�𔽉f����
				pMat[nCntMat].MatD3D.Diffuse.a = 0.6f;
			}
			else
			{	//���_�F�̃��l�ɒl�𔽉f����
				pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;
			}

			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			if (pMat[nCntMat].pTextureFilename != NULL)
			{// �}�e���A���Ƀe�N�X�`�����������ꍇ

				if (m_pTexture[nCntMat] != NULL)
				{
					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, m_pTexture[nCntMat]);
				}
				else
				{// �}�e���A���Ƀe�N�X�`�������������ꍇ
					pDevice->SetTexture(0, NULL);
				}
			}
			else
			{// �}�e���A���Ƀe�N�X�`�������������ꍇ
				pDevice->SetTexture(0, NULL);
			}

			// ���f��(�p�[�c)�̕`��
			m_pMesh->DrawSubset(nCntMat);
		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);

	}

	//���_�@���̎������K��
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	// ���C�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


#endif
}

//=============================================================================
// ���_���W�̐ݒ菈��
//=============================================================================
void CSceneX::SetVtx(void)
{
	DWORD sizeFvF;	//���_�t�H�[�}�b�g�̃T�C�Y
	D3DXVECTOR3 vtx;
	int nNumVtx;	//���_��
	BYTE *pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^

					// ���_�����擾
	nNumVtx = m_pMesh->GetNumVertices();
	// ���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFvF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	// ���_�̍ŏ��l�ƍő�l����
	m_VtxMin = D3DXVECTOR3(10000, 10000, 10000);
	m_VtxMax = D3DXVECTOR3(-10000, -10000, -10000);

	//���_�o�b�t�@�����b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{//���_���W�̑��
		vtx = *(D3DXVECTOR3*)pVtxBuff;

		if (m_VtxMin.x > vtx.x)
		{
			m_VtxMin.x = vtx.x;
		}
		if (m_VtxMin.y > vtx.y)
		{
			m_VtxMin.y = vtx.y;
		}
		if (m_VtxMin.z > vtx.z)
		{
			m_VtxMin.z = vtx.z;
		}

		if (m_VtxMax.x < vtx.x)
		{
			m_VtxMax.x = vtx.x;
		}
		if (m_VtxMax.y < vtx.y)
		{
			m_VtxMax.y = vtx.y;
		}
		if (m_VtxMax.z < vtx.z)
		{
			m_VtxMax.z = vtx.z;
		}

		//�T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFvF;
	}
	//���_�o�b�t�@���A�����b�N
	m_pMesh->UnlockVertexBuffer();

	// �傫���ɍ��킹�Ē���
	m_VtxMax = D3DXVECTOR3(m_VtxMax.x * m_Scale.x, m_VtxMax.y * m_Scale.y, m_VtxMax.z * m_Scale.z);
	m_VtxMin = D3DXVECTOR3(m_VtxMin.x * m_Scale.x, m_VtxMin.y * m_Scale.y, m_VtxMin.z * m_Scale.z);
}

//=============================================================================
// �u���b�N�Ƃ̓����蔻�菈��
//=============================================================================
bool CSceneX::Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius,int nPlayer)
{
	bool bLand = false;	// ����Ă��Ȃ����
	bool bHit = false;	// �q�b�g����̃t���O

	D3DXVECTOR3 ScaleVtxMax;
	D3DXVECTOR3 ScaleVtxMin;

	// �g��𔽉f
	ScaleVtxMax.x = m_VtxMax.x;
	ScaleVtxMax.y = m_VtxMax.y;
	ScaleVtxMax.z = m_VtxMax.z;
	ScaleVtxMin.x = m_VtxMin.x;
	ScaleVtxMin.y = m_VtxMin.y;
	ScaleVtxMin.z = m_VtxMin.z;

	if (m_CollisionType == CSceneX::COLLSIONTYPE_KNOCKBACK_DURING || m_CollisionType == CSceneX::COLLSIONTYPE_KNOCKBACK_SMALL ||
		m_CollisionType == CSceneX::COLLSIONTYPE_KNOCKBACK_BIG || m_CollisionType == CSceneX::COLLISIONTYPE_BOX)
	{	// �x���g�R���x�A�ȊO�̏ꍇ
		bHit = true;
	}

	if (m_CollisionType != COLLISIONTYPE_NONE && m_CollisionType != COLLSIONTYPE_FLOORCOLLSION && m_CollisionType != COLLSIONTYPE_BUSH)
	{
		if (pos->y <= m_pos.y + ScaleVtxMax.y - SCENEX_SIZE &&pos->y + radius.y >= m_pos.y + ScaleVtxMax.y - SCENEX_SIZE
			|| pos->y + radius.y >= m_pos.y + ScaleVtxMin.y &&pos->y <= m_pos.y + ScaleVtxMin.y
			|| pos->y + radius.y <= m_pos.y + ScaleVtxMax.y - SCENEX_SIZE && pos->y >= m_pos.y + ScaleVtxMin.y)
		{// y�͈̔͂̒�
			if (pos->z - radius.z <= m_pos.z + ScaleVtxMax.z && pos->z + radius.z >= m_pos.z + ScaleVtxMin.z)
			{// z�͈̔͂̒�
				if (posOld->x + radius.x <= m_pos.x + ScaleVtxMin.x && pos->x + radius.x > m_pos.x + ScaleVtxMin.x)
				{// X���W�̒��ɍ����������
					pos->x = posOld->x;
					if (m_CollisionType != CSceneX::COLLSIONTYPE_KNOCKBACK_DURING && m_CollisionType != CSceneX::COLLSIONTYPE_KNOCKBACK_SMALL && m_CollisionType != CSceneX::COLLSIONTYPE_KNOCKBACK_BIG)
					{	// �m�b�N�o�b�N�ȊO�̎�ނȂ�
						move->x = 0.0f;
					}
					m_nCollsionNum = 0;
					bLand = true;
				}
				else if (posOld->x - radius.x >= m_pos.x + ScaleVtxMax.x
					&& pos->x - radius.x < m_pos.x + ScaleVtxMax.x)
				{// X���W�̒��ɉE���������
					pos->x = posOld->x;
					if (m_CollisionType != CSceneX::COLLSIONTYPE_KNOCKBACK_DURING && m_CollisionType != CSceneX::COLLSIONTYPE_KNOCKBACK_SMALL && m_CollisionType != CSceneX::COLLSIONTYPE_KNOCKBACK_BIG)
					{	// �m�b�N�o�b�N�ȊO�̎�ނȂ�
						move->x = 0.0f;
					}
					m_nCollsionNum = 1;
					bLand = true;
				}
			}
			if (pos->x - radius.x <= m_pos.x + ScaleVtxMax.x &&
				pos->x + radius.x >= m_pos.x + ScaleVtxMin.x)
			{// x�͈̔͂̒�
				if (posOld->z + radius.z <= m_pos.z + ScaleVtxMin.z
					&& pos->z + radius.z > m_pos.z + ScaleVtxMin.z)
				{// Z���W�̒��Ɏ�O���������
					pos->z = posOld->z;
					if (m_CollisionType != CSceneX::COLLSIONTYPE_KNOCKBACK_DURING && m_CollisionType != CSceneX::COLLSIONTYPE_KNOCKBACK_SMALL && m_CollisionType != CSceneX::COLLSIONTYPE_KNOCKBACK_BIG)
					{	// �m�b�N�o�b�N�ȊO�̎�ނȂ�
						move->z = 0.0f;
					}
					m_nCollsionNum = 2;
					bLand = true;
				}
				else if (posOld->z - radius.z >= m_pos.z + ScaleVtxMax.z
					&& pos->z - radius.z < m_pos.z + ScaleVtxMax.z)
				{// Z���W�̒��Ɍ�납�������
					pos->z = posOld->z;
					if (m_CollisionType != CSceneX::COLLSIONTYPE_KNOCKBACK_DURING && m_CollisionType != CSceneX::COLLSIONTYPE_KNOCKBACK_SMALL && m_CollisionType != CSceneX::COLLSIONTYPE_KNOCKBACK_BIG)
					{	// �m�b�N�o�b�N�ȊO�̎�ނȂ�
						move->z = 0.0f;
					}
					m_nCollsionNum = 3;
					bLand = true;
				}
			}
		}

		if (pos->x - radius.x < m_pos.x + ScaleVtxMax.x - SCENEX_SIZE && pos->x + radius.x > m_pos.x + ScaleVtxMin.x + SCENEX_SIZE
			&& pos->z - radius.z <= m_pos.z + ScaleVtxMax.z - SCENEX_SIZE && pos->z + radius.z >= m_pos.z + ScaleVtxMin.z + SCENEX_SIZE)
		{// ��Q���̓����ɏ����
			if (bHit == false) { bLand = true; }	// �x���g�R���x�A�̏ꍇ
			if (posOld->y >= m_pos.y + ScaleVtxMax.y && m_pos.y + ScaleVtxMax.y >= pos->y)
			{// �ォ��u���b�N�ɓ��������Ƃ�
				bLand = true;  // ����������Ԃ�
				pos->y = m_pos.y + ScaleVtxMax.y;
				move->y = 0.0f;  // �ړ��ʂ��Ȃ���
			}
			else if (posOld->y + radius.y <= m_pos.y + ScaleVtxMin.y && pos->y + radius.y >= m_pos.y + ScaleVtxMin.y)
			{// ������u���b�N�ɓ��������Ƃ�
				pos->y = posOld->y;
				move->y = 0.0f;  // �ړ��ʂ��Ȃ���
				bLand = true;
			}
		}
	}

	if (m_CollisionType == COLLSIONTYPE_BUSH)
	{//�@���ނ�̔���
		if (pos->z - radius.z <= m_pos.z + ScaleVtxMax.z && pos->z + radius.z >= m_pos.z + ScaleVtxMin.z)
		{// z�͈̔͂̒�
			if (pos->x - radius.x <= m_pos.x + ScaleVtxMax.x && pos->x + radius.x> m_pos.x + ScaleVtxMin.x)
			{// X���W�̒��ɓ�����
				m_bTranslucent[nPlayer] = true;
				bLand = true;
				//�������Ă��鑐�̔ԍ�����
				m_nTranslucentBush[nPlayer] = m_nBushNum;
			}
			else if (m_nTranslucentBush[nPlayer] != m_nBushNum)
			{//���̔ԍ����Ⴄ�Ƃ�
				m_bTranslucent[nPlayer] = false;
			}
			else if (m_nTranslucentBush[nPlayer] == m_nBushNum)
			{//���̔ԍ�������
				m_bTranslucent[nPlayer] = true;
			}
		}
		else
		{
			if (m_nTranslucentBush[nPlayer] != m_nBushNum)
			{//���̔ԍ����Ⴄ�Ƃ�
				m_bTranslucent[nPlayer] = false;
			}
			else if(m_nTranslucentBush[nPlayer] == m_nBushNum)
			{//���̔ԍ�������
				m_bTranslucent[nPlayer] = true;
			}
		}
	}

	return bLand;	// �u���b�N�ɏ���Ă��邩�ǂ�����Ԃ�
}


//=============================================================================
// �u���b�N�Ƃ̓����蔻�菈�� (�͈͓����ǂ���)
//=============================================================================
bool CSceneX::CollisionIN(D3DXVECTOR3 pos,D3DXVECTOR3 radius)
{
	bool bHit = false;	// �q�b�g����̃t���O
	D3DXVECTOR3 ScaleVtxMax;
	D3DXVECTOR3 ScaleVtxMin;

	// �g��𔽉f
	ScaleVtxMax.x = m_VtxMax.x;
	ScaleVtxMax.y = m_VtxMax.y;
	ScaleVtxMax.z = m_VtxMax.z;
	ScaleVtxMin.x = m_VtxMin.x;
	ScaleVtxMin.y = m_VtxMin.y;
	ScaleVtxMin.z = m_VtxMin.z;

	if (m_CollisionType != COLLISIONTYPE_NONE && m_CollisionType != COLLSIONTYPE_FLOORCOLLSION)
	{
		if (pos.z <= m_pos.z + ScaleVtxMax.z + radius.z && pos.z >= m_pos.z + ScaleVtxMin.z - radius.z)
		{// z�͈̔͂̒�
			if (pos.x <= m_pos.x + ScaleVtxMax.x + radius.x && pos.x >= m_pos.x + ScaleVtxMin.x - radius.x)
			{
				bHit = true;
			}
		}
	}

	return bHit;
}

//=============================================================================
// �ʒu�̎擾
//=============================================================================
D3DXVECTOR3 CSceneX::GetPosition(void)
{
	return m_pos;
}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void CSceneX::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �ʒu�̎擾
//=============================================================================
D3DXVECTOR3 CSceneX::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void CSceneX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// ���f�������蓖�Ă�
//=============================================================================
void CSceneX::BindModel(LPD3DXBUFFER pBuffMat, DWORD nNumMat, LPD3DXMESH pMesh)
{
	m_pBuffMat = pBuffMat;
	m_nNumMat = nNumMat;
	m_pMesh = pMesh;

	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;
	//�}�e���A����񂩂�e�N�X�`���̎擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	//�e�N�X�`�����}�e���A���̐������I�m��
	//m_pTexture = new LPDIRECT3DTEXTURE9[m_nNumMat];

	m_pTexture = CLoad::GetTexture(m_ModelType);

	//�}�e���A���̐���
	//for (int nCntMatTex = 0; nCntMatTex < (int)m_nNumMat; nCntMatTex++)
	//{
	//	//NULL������ ���g�����
	//	m_pTexture[nCntMatTex] = NULL;

	//	if (pMat[nCntMatTex].pTextureFilename != NULL)
	//	{
	//		// �e�N�X�`���̐ݒ�
	//		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
	//			pMat[nCntMatTex].pTextureFilename,	// �t�@�C���̖��O
	//			&m_pTexture[nCntMatTex]);		// �e�N�X�`���ւ̃|�C���^
	//	}
	//}
}

//=============================================================================
// �e�N�X�`���}�e���A�������蓖�Ă�
//=============================================================================
void CSceneX::BindTex(LPDIRECT3DTEXTURE9 *pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
// ���_���̍ő�l�̎擾
//=============================================================================
D3DXVECTOR3 CSceneX::GetVtxMax(void)
{
	return m_VtxMax;
}

//=============================================================================
// ���_���̍ő�l�̐ݒ�
//=============================================================================
void CSceneX::SetVtxMax(D3DXVECTOR3 VtxMax)
{
	m_VtxMax = VtxMax;
}

//=============================================================================
// ���_���̍ŏ��l�̎擾
//=============================================================================
D3DXVECTOR3 CSceneX::GetVtxMin(void)
{
	return m_VtxMin;
}

//=============================================================================
// ���_���̍ŏ��l�̐ݒ�
//=============================================================================
void CSceneX::SetVtxMin(D3DXVECTOR3 VtxMin)
{
	m_VtxMin = VtxMin;
}