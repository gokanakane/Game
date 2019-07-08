//=============================================================================
//
// �f�B�X�v���C���� [DisPlay.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "DisPlay.h"
#include "camera.h"
#include "Player.h"
#include "Item.h"
#include "sound.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureDisPlay = NULL;	//�e�N�X�`���ւ̃|�C���^
DisPlay g_DisPlay[MAX_DISPLAY];								//���f���̏��

//=============================================================================
// ����������
//=============================================================================
void InitDisPlay(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nNumVtx;						//���_��
	DWORD sizeFVF;						//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;						//���_�o�b�t�@�̃|�C���^

	for (int nCnt = 0; nCnt < MAX_DISPLAY; nCnt++)
	{
		g_DisPlay[nCnt].nNumMat = 0;

		g_DisPlay[nCnt].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_DisPlay[nCnt].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(DISPLAY_1,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_DisPlay[nCnt].pBuffMat,
			NULL,
			&g_DisPlay[nCnt].nNumMat,
			&g_DisPlay[nCnt].pMesh);

		//���_���̎擾
		nNumVtx = g_DisPlay[nCnt].pMesh->GetNumVertices();
		sizeFVF = D3DXGetFVFVertexSize(g_DisPlay[nCnt].pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_DisPlay[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			if (g_DisPlay[nCnt].vtxMin.x > vtx.x)
			{//X�̍ŏ��l�̏�������
				g_DisPlay[nCnt].vtxMin.x = vtx.x;
			}
			if (g_DisPlay[nCnt].vtxMin.z > vtx.z)
			{//X�̍ŏ��l�̏�������
				g_DisPlay[nCnt].vtxMin.z = vtx.z;
			}
			if (g_DisPlay[nCnt].vtxMax.x < vtx.x)
			{//X�̍ŏ��l�̏�������
				g_DisPlay[nCnt].vtxMax.x = vtx.x;
			}
			if (g_DisPlay[nCnt].vtxMax.z < vtx.z)
			{//X�̍ŏ��l�̏�������
				g_DisPlay[nCnt].vtxMax.z = vtx.z;
			}

			pVtxBuff += sizeFVF;//�T�C�Y���|�C���^��i�߂�
		}
		//���_�o�b�t�@�̃A�����b�N
		g_DisPlay[nCnt].pMesh->UnlockVertexBuffer();
		//�e�N�X�`���̐ݒ�
		D3DXCreateTextureFromFile(pDevice, DISPLAY_TEXTURE, &g_pTextureDisPlay);
		// �ʒu�E�����E�F�̏����ݒ�
		g_DisPlay[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_DisPlay[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_DisPlay[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_DisPlay[nCnt].nType = 0;
		g_DisPlay[nCnt].bUse = false;
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitDisPlay(void)
{
	for (int nCnt = 0; nCnt < MAX_DISPLAY; nCnt++)
	{
		// ���b�V���̊J��
		if (g_DisPlay[nCnt].pMesh != NULL)
		{
			g_DisPlay[nCnt].pMesh->Release();
			g_DisPlay[nCnt].pMesh = NULL;
		}
		// �}�e���A���̊J��
		if (g_DisPlay[nCnt].pBuffMat != NULL)
		{
			g_DisPlay[nCnt].pBuffMat->Release();
			g_DisPlay[nCnt].pBuffMat = NULL;
		}
	}
	
	if (g_pTextureDisPlay != NULL)
	{
		g_pTextureDisPlay->Release();
		g_pTextureDisPlay = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateDisPlay(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawDisPlay(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;			//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;					//���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL *pMat;						//�}�e���A���f�[�^�ւ̃|�C���^


	//z�e�X�g
	//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	for (int nCnt = 0; nCnt < MAX_DISPLAY; nCnt++)
	{

		if (g_DisPlay[nCnt].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_DisPlay[nCnt].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_DisPlay[nCnt].rot.y, g_DisPlay[nCnt].rot.x, g_DisPlay[nCnt].rot.z);
			D3DXMatrixMultiply(&g_DisPlay[nCnt].mtxWorld, &g_DisPlay[nCnt].mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_DisPlay[nCnt].pos.x, g_DisPlay[nCnt].pos.y, g_DisPlay[nCnt].pos.z);
			D3DXMatrixMultiply(&g_DisPlay[nCnt].mtxWorld, &g_DisPlay[nCnt].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_DisPlay[nCnt].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_DisPlay[nCnt].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat <= (int)g_DisPlay[nCnt].nNumMat; nCntMat++)
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureDisPlay);

				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// ���f��(�p�[�c)�̕`��
				g_DisPlay[nCnt].pMesh->DrawSubset(nCntMat);
			}

			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
	//z�e�X�g
	//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

}
//=============================================================================
// ���f���̎擾
//=============================================================================
DisPlay*GetDisPlay(void)
{
	return &g_DisPlay[0];
}
//=============================================================================
// ���f���ƃv���C���[�̂����蔻��
//=============================================================================
void CollisionDisPlay(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax)
{
	Player *pPlayer;
	pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < MAX_DISPLAY; nCnt++)
	{
		if (g_DisPlay[nCnt].bUse == true)
		{//���f���̎g�p��
			if (pos->x + vtxMax.x > g_DisPlay[nCnt].pos.x + g_DisPlay[nCnt].vtxMin.x &&
				pos->x + vtxMin.x < g_DisPlay[nCnt].pos.x + g_DisPlay[nCnt].vtxMax.x)
			{//���͈͔̔���
				if (posOld->z + vtxMin.z >= g_DisPlay[nCnt].pos.z + g_DisPlay[nCnt].vtxMax.z &&
					g_DisPlay[nCnt].pos.z + g_DisPlay[nCnt].vtxMax.z > pos->z + vtxMin.z)
				{//����
					pos->z = g_DisPlay[nCnt].pos.z + g_DisPlay[nCnt].vtxMax.z - vtxMin.z;
					DeleteItem(g_DisPlay[nCnt].nType);

					break;
				}
				else if (posOld->z + vtxMax.z <= g_DisPlay[nCnt].pos.z + g_DisPlay[nCnt].vtxMin.z &&
					g_DisPlay[nCnt].pos.z + g_DisPlay[nCnt].vtxMin.z < pos->z + vtxMax.z)
				{//��O�̖�
					pos->z = g_DisPlay[nCnt].pos.z + g_DisPlay[nCnt].vtxMin.z + vtxMin.z;
					DeleteItem(g_DisPlay[nCnt].nType);

					break;
				}
			}
			if (pos->z + vtxMax.z < g_DisPlay[nCnt].pos.z + g_DisPlay[nCnt].vtxMax.z &&
				pos->z + vtxMax.z > g_DisPlay[nCnt].pos.z + g_DisPlay[nCnt].vtxMin.z)
			{//z�͈͔̔���
				if (posOld->x + vtxMin.x >= g_DisPlay[nCnt].pos.x + g_DisPlay[nCnt].vtxMax.x &&
					g_DisPlay[nCnt].pos.x + g_DisPlay[nCnt].vtxMax.x > pos->x + vtxMin.x)
				{//�E���̖�
					pos->x = g_DisPlay[nCnt].pos.x + g_DisPlay[nCnt].vtxMax.x - vtxMin.x;
					DeleteItem(g_DisPlay[nCnt].nType);

					break;
				}
				else if (posOld->x + vtxMax.x <= g_DisPlay[nCnt].pos.x + g_DisPlay[nCnt].vtxMin.x &&
					g_DisPlay[nCnt].pos.x + g_DisPlay[nCnt].vtxMin.x < pos->x + vtxMax.x)
				{//�����̖�
					pos->x = g_DisPlay[nCnt].pos.x + g_DisPlay[nCnt].vtxMin.x - vtxMax.x;
					DeleteItem(g_DisPlay[nCnt].nType);

					break;
				}
			}
		}
	}
}
//=============================================================================
// ���f���̐ݒ�
//=============================================================================
void SetDisPlay(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	for (int nCnt = 0; nCnt < MAX_DISPLAY; nCnt++)
	{
		if (g_DisPlay[nCnt].bUse == false)
		{
			g_DisPlay[nCnt].pos = pos;
			g_DisPlay[nCnt].rot = rot;
			g_DisPlay[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			g_DisPlay[nCnt].nType = nType;
			g_DisPlay[nCnt].bUse = true;
			break;
		}
	}
}