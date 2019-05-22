//=============================================================================
//
// ���f������ [Enemy.cpp]
// Author : ��Ձ@��
//
//=============================================================================
#include "Enemy.h"
#include "input.h"
#include "shadow.h"
#include "Stage.h"
#include "Player.h"
#include "Wall.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENEMY_TEXTUER " "
#define ENEMY_1 "data\\MODEL\\Enemy\\00_Body.x"		//��[0]

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureEnemy = NULL;//�e�N�X�`���ւ̃|�C���^
Enemy g_Enemy[MAX_ENEMY];								//���f���̏��

//=============================================================================
// ����������
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nNumVtx;						//���_��
	DWORD sizeFVF;						//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;						//���_�o�b�t�@�̃|�C���^

	for (int nCnt1 = 0; nCnt1 < MAX_ENEMY; nCnt1++)
	{
		g_Enemy[nCnt1].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_Enemy[nCnt1].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);

		g_Enemy[nCnt1].aModel.NumMat = 0;

		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(ENEMY_1,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Enemy[nCnt1].aModel.pBuffMat,
			NULL,
			&g_Enemy[nCnt1].aModel.NumMat,
			&g_Enemy[nCnt1].aModel.pMesh);

		//���_���̎擾
		nNumVtx = g_Enemy[nCnt1].aModel.pMesh->GetNumVertices();
		sizeFVF = D3DXGetFVFVertexSize(g_Enemy[nCnt1].aModel.pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_Enemy[nCnt1].aModel.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCnt = 0; nCnt <= nNumVtx; nCnt++)
		{//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			if (g_Enemy[nCnt1].vtxMin.x > vtx.x)
			{//X�̍ŏ��l�̏�������
				g_Enemy[nCnt1].vtxMin.x = vtx.x;
			}
			if (g_Enemy[nCnt1].vtxMin.z > vtx.z)
			{//Z�̍ŏ��l�̏�������
				g_Enemy[nCnt1].vtxMin.z = vtx.z;
			}
			if (g_Enemy[nCnt1].vtxMax.x < vtx.x)
			{//X�̍ŏ��l�̏�������
				g_Enemy[nCnt1].vtxMax.x = vtx.x;
			}
			if (g_Enemy[nCnt1].vtxMax.z < vtx.z)
			{//Z�̍ŏ��l�̏�������
				g_Enemy[nCnt1].vtxMax.z = vtx.z;
			}

			pVtxBuff += sizeFVF;//�T�C�Y���|�C���^��i�߂�
		}
		//���_�o�b�t�@�̃A�����b�N
		g_Enemy[nCnt1].aModel.pMesh->UnlockVertexBuffer();

		//�e�N�X�`���̐ݒ�
		D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTUER, &g_pTextureEnemy);

		// �ʒu�E�����E�F�̏����ݒ�
		g_Enemy[nCnt1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCnt1].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCnt1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCnt1].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCnt1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_Enemy[nCnt1].VecA= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCnt1].VecC = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCnt1].nType = 0;
		g_Enemy[nCnt1].bUse = false;

		//�㔼�g
		g_Enemy[nCnt1].aModel.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCnt1].aModel.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}
}
//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	for (int nCnt2 = 0; nCnt2 < MAX_ENEMY; nCnt2++)
	{
		// ���b�V���̊J��
		if (g_Enemy[nCnt2].aModel.pMesh != NULL)
		{
			g_Enemy[nCnt2].aModel.pMesh->Release();
			g_Enemy[nCnt2].aModel.pMesh = NULL;
		}
		// �}�e���A���̊J��
		if (g_Enemy[nCnt2].aModel.pBuffMat != NULL)
		{
			g_Enemy[nCnt2].aModel.pBuffMat->Release();
			g_Enemy[nCnt2].aModel.pBuffMat = NULL;
		}
	}
	//�e�N�X�`���̏�����
	if (g_pTextureEnemy != NULL)
	{
		g_pTextureEnemy->Release();
		g_pTextureEnemy = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	Stage*pField;
	pField = GetStage();
	Player*pPlayer = GetPlayer();
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		g_Enemy[nCnt].posOld = g_Enemy[nCnt].pos;

		if (g_Enemy[nCnt].bUse == true)
		{
			if (g_Enemy[nCnt].nType == 0)
			{
				//�O��̈ʒu��������
				g_Enemy[nCnt].nCntMove += g_Enemy[nCnt].nChengeMove;
				g_Enemy[nCnt].pos.x += g_Enemy[nCnt].nChengeMove;

				if (CollisionWall_HEIDTH_ENE(&g_Enemy[nCnt].pos, g_Enemy[nCnt].pos, &g_Enemy[nCnt].posOld, &g_Enemy[nCnt].rot) == true)
				{
					g_Enemy[nCnt].nChengeMove *= -1.0f;
				}
			}

			//�X�e�[�W�̂����蔻��
			CollisionStageEN();

			SetPositionShadow(g_Enemy[nCnt].nIdxShadow, g_Enemy[nCnt].pos);
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;			//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;					//���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL *pMat;						//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxParent;

	//z�e�X�g
	//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == true)
		{
			//�v���C���[�̕`��------------------------------------
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Enemy[nCntEnemy].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nCntEnemy].rot.y, g_Enemy[nCntEnemy].rot.x, g_Enemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].mtxWorld, &g_Enemy[nCntEnemy].mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].mtxWorld, &g_Enemy[nCntEnemy].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntEnemy].mtxWorld);

			//�e���f���̃C���f�b�N�X��"-1"
			mtxParent = g_Enemy[nCntEnemy].mtxWorld;

			//���f���̕`��------------------------------------
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Enemy[nCntEnemy].aModel.mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nCntEnemy].aModel.rot.y, g_Enemy[nCntEnemy].aModel.rot.x, g_Enemy[nCntEnemy].aModel.rot.z);
			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].aModel.mtxWorld, &g_Enemy[nCntEnemy].aModel.mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Enemy[nCntEnemy].aModel.pos.x, g_Enemy[nCntEnemy].aModel.pos.y, g_Enemy[nCntEnemy].aModel.pos.z);
			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].aModel.mtxWorld, &g_Enemy[nCntEnemy].aModel.mtxWorld, &mtxTrans);

			//�e�̃��f���Ɗ֘A�t��
			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].aModel.mtxWorld, &g_Enemy[nCntEnemy].aModel.mtxWorld, &mtxParent);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntEnemy].aModel.mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Enemy[nCntEnemy].aModel.pBuffMat->GetBufferPointer();

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEnemy);


			for (int nCntMat = 0; nCntMat <= (int)g_Enemy[nCntEnemy].aModel.NumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// ���f��(�p�[�c)�̕`��
				g_Enemy[nCntEnemy].aModel.pMesh->DrawSubset(nCntMat);
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
Enemy*GetEnemy(void)
{
	return &g_Enemy[0];
}

//=============================================================================
// ���f���̐ݒ�
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float ChengeMove,int Type)
{
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (g_Enemy[nCnt].bUse == false)
		{
			g_Enemy[nCnt].pos = pos;
			g_Enemy[nCnt].rot = rot;
			g_Enemy[nCnt].nChengeMove = ChengeMove;
			g_Enemy[nCnt].nType = Type;
			g_Enemy[nCnt].bUse = true;

			g_Enemy[nCnt].nIdxShadow = SetShadow(g_Enemy[nCnt].pos, g_Enemy[nCnt].rot);
			break;
		}
	}
}
//=============================================================================
// �X�e�[�W1�̕ӂ蔻��
//=============================================================================
void CollisionStageEN(void)
{
	float VecLine[4];		//�����蔻��̌v�Z����
	D3DXVECTOR3 aPos[4];

	aPos[0] = D3DXVECTOR3(-40.0f, 0.0f, 40.0f);
	aPos[1] = D3DXVECTOR3(590.0f, 0.0f, 40.0f);
	aPos[2] = D3DXVECTOR3(590.0f, 0.0f, -590.0f);
	aPos[3] = D3DXVECTOR3(-40.0f, 0.0f, -590.0f);

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (g_Enemy[nCnt].bUse == true)
		{
			//��ǂ����蔻��--------------------------------------------------------------
			//�x�N�g���v�Z
			g_Enemy[nCnt].VecA = aPos[0] - aPos[1];
			g_Enemy[nCnt].VecC = g_Enemy[nCnt].pos - aPos[0];


			//�����蔻��v�Z
			VecLine[0] = (g_Enemy[nCnt].VecA.z*g_Enemy[nCnt].VecC.x) - (g_Enemy[nCnt].VecA.x*g_Enemy[nCnt].VecC.z);

			if (VecLine[0] >= 0)
			{//���������獶��
				g_Enemy[nCnt].rot.y = 0.0f;
				g_Enemy[nCnt].nChengeMove *= -1.0f;

			}
			//���ǂ����蔻��--------------------------------------------------------------
			//�x�N�g���v�Z
			g_Enemy[nCnt].VecA = aPos[2] - aPos[3];
			g_Enemy[nCnt].VecC = g_Enemy[nCnt].pos - aPos[2];


			//�����蔻��v�Z
			VecLine[1] = (g_Enemy[nCnt].VecA.z*g_Enemy[nCnt].VecC.x) - (g_Enemy[nCnt].VecA.x*g_Enemy[nCnt].VecC.z);

			if (VecLine[1] >= 0)
			{//���������獶��
				g_Enemy[nCnt].rot.y = D3DX_PI;
				g_Enemy[nCnt].nChengeMove *= -1.0f;

			}

			//�E�ǂ����蔻��--------------------------------------------------------------
			//�x�N�g���v�Z
			g_Enemy[nCnt].VecA = aPos[1] - aPos[2];
			g_Enemy[nCnt].VecC = g_Enemy[nCnt].pos - aPos[1];


			//�����蔻��v�Z
			VecLine[2] = (g_Enemy[nCnt].VecA.z*g_Enemy[nCnt].VecC.x) - (g_Enemy[nCnt].VecA.x*g_Enemy[nCnt].VecC.z);

			if (VecLine[2] >= 0)
			{//���������獶��
				g_Enemy[nCnt].rot.y = D3DX_PI*0.5f;
				g_Enemy[nCnt].nChengeMove *= -1.0f;

			}
			//���ǂ����蔻��--------------------------------------------------------------
			//�x�N�g���v�Z
			g_Enemy[nCnt].VecA = aPos[3] - aPos[0];
			g_Enemy[nCnt].VecC = g_Enemy[nCnt].pos - aPos[3];


			//�����蔻��v�Z
			VecLine[3] = (g_Enemy[nCnt].VecA.z*g_Enemy[nCnt].VecC.x) - (g_Enemy[nCnt].VecA.x*g_Enemy[nCnt].VecC.z);

			if (VecLine[3] >= 0)
			{//���������獶��
				g_Enemy[nCnt].rot.y = D3DX_PI*0.5f;
				g_Enemy[nCnt].nChengeMove *= -1.0f;

			}
		}
	}
}
//=============================================================================
// �G�ƃv���C���[�̂����蔻��
//=============================================================================
bool CollisionEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax)
{
	bool bLand = false;

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (g_Enemy[nCnt].bUse == true)
		{
			bLand = false;

			if (g_Enemy[nCnt].pos.x + g_Enemy[nCnt].vtxMax.x > pos.x + vtxMax.x &&
				g_Enemy[nCnt].pos.x + g_Enemy[nCnt].vtxMin.x < pos.x + vtxMin.x)
			{
				if (g_Enemy[nCnt].pos.z + g_Enemy[nCnt].vtxMax.z > pos.z + vtxMax.z &&
					g_Enemy[nCnt].pos.z + g_Enemy[nCnt].vtxMin.z < pos.z + vtxMin.z)
				{
					bLand = true;
					break;
				}
			}
		}
	}
	return bLand;
}