//=============================================================================
//
// ���f������ [Obj.cpp]
// Author : 
//
//=============================================================================
#include "Obj.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "Player.h"
#include "Bullet.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureObj = NULL;	//�e�N�X�`���ւ̃|�C���^
Obj g_Obj;								//���f���̏��

//=============================================================================
// ����������
//=============================================================================
void InitObj(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nNumVtx;						//���_��
	DWORD sizeFVF;						//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;						//���_�o�b�t�@�̃|�C���^

	g_Obj.nNumMat = 0;

	g_Obj.vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
	g_Obj.vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(OBJ_1,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Obj.pBuffMat,
		NULL,
		&g_Obj.nNumMat,
		&g_Obj.pMesh);

	//���_���̎擾
	nNumVtx = g_Obj.pMesh->GetNumVertices();
	sizeFVF = D3DXGetFVFVertexSize(g_Obj.pMesh->GetFVF());

	//���_�o�b�t�@�̃��b�N
	g_Obj.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		if (g_Obj.vtxMin.x > vtx.x)
		{//X�̍ŏ��l�̏�������
			g_Obj.vtxMin.x = vtx.x;
		}
		if (g_Obj.vtxMin.z > vtx.z)
		{//X�̍ŏ��l�̏�������
			g_Obj.vtxMin.z = vtx.z;
		}
		if (g_Obj.vtxMax.x < vtx.x)
		{//X�̍ŏ��l�̏�������
			g_Obj.vtxMax.x = vtx.x;
		}
		if (g_Obj.vtxMax.z < vtx.z)
		{//X�̍ŏ��l�̏�������
			g_Obj.vtxMax.z = vtx.z;
		}

		pVtxBuff += sizeFVF;//�T�C�Y���|�C���^��i�߂�
	}
	//���_�o�b�t�@�̃A�����b�N
	g_Obj.pMesh->UnlockVertexBuffer();
	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, OBJ_TEXTURE, &g_pTextureObj);
	// �ʒu�E�����E�F�̏����ݒ�
	g_Obj.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Obj.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Obj.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	g_Obj.nType = 0;
	g_Obj.bUse = false;
}

//=============================================================================
// �I������
//=============================================================================
void UninitObj(void)
{
	for (int nCnt = 0; nCnt < MAX_OBJ; nCnt++)
	{
		// ���b�V���̊J��
		if (g_Obj.pMesh != NULL)
		{
			g_Obj.pMesh->Release();
			g_Obj.pMesh = NULL;
		}
		// �}�e���A���̊J��
		if (g_Obj.pBuffMat != NULL)
		{
			g_Obj.pBuffMat->Release();
			g_Obj.pBuffMat = NULL;
		}
	}
	
	if (g_pTextureObj != NULL)
	{
		g_pTextureObj->Release();
		g_pTextureObj = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateObj(void)
{
	if (g_Obj.bUse == true)
	{
		SetPositionShadow(g_Obj.nIdxShadow, g_Obj.pos);
	}
	else
	{
		DeleteShadow(g_Obj.nIdxShadow);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawObj(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;			//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;					//���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL *pMat;						//�}�e���A���f�[�^�ւ̃|�C���^


	//z�e�X�g
	//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	if (g_Obj.bUse == true)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Obj.mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Obj.rot.y, g_Obj.rot.x, g_Obj.rot.z);
		D3DXMatrixMultiply(&g_Obj.mtxWorld, &g_Obj.mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Obj.pos.x, g_Obj.pos.y, g_Obj.pos.z);
		D3DXMatrixMultiply(&g_Obj.mtxWorld, &g_Obj.mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Obj.mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Obj.pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat <= (int)g_Obj.nNumMat; nCntMat++)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureObj);

			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// ���f��(�p�[�c)�̕`��
			g_Obj.pMesh->DrawSubset(nCntMat);
		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
	//z�e�X�g
	//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

}
//=============================================================================
// ���f���̎擾
//=============================================================================
Obj*GetObj(void)
{
	return &g_Obj;
}
//=============================================================================
// ���f���ƃv���C���[�̂����蔻��
//=============================================================================
bool CollisionObj(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld ,D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax)
{
	Player *pPlayer;
	pPlayer = GetPlayer();
	bool bLand = false;
	if (g_Obj.bUse == true)
	{//���f���̎g�p��
		bLand = false;
		if (g_Obj.bUse == true)
		{//���f���̎g�p��
			bLand = false;
			if (pos->x + vtxMax.x > g_Obj.pos.x + g_Obj.vtxMin.x &&
				pos->x + vtxMin.x < g_Obj.pos.x + g_Obj.vtxMax.x)
			{//���͈͔̔���
				if (posOld->z + vtxMin.z >= g_Obj.pos.z + g_Obj.vtxMax.z &&
					g_Obj.pos.z + g_Obj.vtxMax.z > pos->z + vtxMin.z)
				{//����
					pos->z = g_Obj.pos.z + g_Obj.vtxMax.z - vtxMin.z;
					bLand = true;
				}
				else if (posOld->z + vtxMax.z <= g_Obj.pos.z + g_Obj.vtxMin.z &&
					g_Obj.pos.z + g_Obj.vtxMin.z < pos->z + vtxMax.z)
				{//��O�̖�
					pos->z = g_Obj.pos.z + g_Obj.vtxMin.z + vtxMin.z;
					bLand = true;
				}
			}
			if (pos->z + vtxMax.z < g_Obj.pos.z + g_Obj.vtxMax.z &&
				pos->z + vtxMax.z > g_Obj.pos.z + g_Obj.vtxMin.z)
			{//z�͈͔̔���
				if (posOld->x + vtxMin.x >= g_Obj.pos.x + g_Obj.vtxMax.x &&
					g_Obj.pos.x + g_Obj.vtxMax.x > pos->x + vtxMin.x)
				{//�E���̖�
					pos->x = g_Obj.pos.x + g_Obj.vtxMax.x - vtxMin.x+0.01f;
					bLand = true;
				}
				else if (posOld->x + vtxMax.x <= g_Obj.pos.x + g_Obj.vtxMin.x &&
					g_Obj.pos.x + g_Obj.vtxMin.x < pos->x + vtxMax.x)
				{//�����̖�
					pos->x = g_Obj.pos.x + g_Obj.vtxMin.x - vtxMax.x;
					bLand = true;
				}
			}
		}
	}
	return bLand;
}
//=============================================================================
// ���f���̐ݒ�
//=============================================================================
void SetObj(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	if (g_Obj.bUse == false)
	{
		g_Obj.pos = pos;
		g_Obj.rot = rot;
		g_Obj.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_Obj.nType = nType;
		g_Obj.bUse = true;

		g_Obj.nIdxShadow = SetShadow(g_Obj.pos, g_Obj.rot);
	}
}