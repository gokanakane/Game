//=============================================================================
//
// �X�e�[�W�Ǐ��� [Wall.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "Wall.h"
#include "Player.h"
#include "Enemy.h"
#include "ItemGetUI.h"
#include "Item.h"
#include "sound.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall[MAX_WALL] = {};	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureWall[MAX_WALLTEX] = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffWall[MAX_WALL] = {};		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
Wall g_Wall[MAX_WALL];
int g_nCntLockWall;

//=============================================================================
// ����������
//=============================================================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		g_Wall[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCnt].bUse = false;
		g_Wall[nCnt].Heidth = 0;
		g_Wall[nCnt].Width = 0;
		g_Wall[nCnt].VertexStage = 0;
		g_Wall[nCnt].IndexStage = 0;
		g_Wall[nCnt].PolygonStage = 0;
		g_Wall[nCnt].nTexType = 0;
	}
	g_nCntLockWall = 0;

	//�l��---------------------------------
	SetWall(13, 1, D3DXVECTOR3(0.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),0);
	SetWall(13, 1, D3DXVECTOR3(550.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 0);
	SetWall(13, 1, D3DXVECTOR3(-50.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f), 0);
	SetWall(13, 1, D3DXVECTOR3(600.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	
	//��----------------------------------
	SetWall(10, 1, D3DXVECTOR3(100.0f, 0.0f, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(2, 1, D3DXVECTOR3(150.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(50.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(100.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(550.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(550.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(550.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(500.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(2, 1, D3DXVECTOR3(400.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(2, 1, D3DXVECTOR3(100.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(50.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(0.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);

	//��----------------------------------
	SetWall(2, 1, D3DXVECTOR3(0.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(2, 1, D3DXVECTOR3(150.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(8, 1, D3DXVECTOR3(50.0f, 0.0f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(500.0f, 0.0f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(500.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(500.0f, 0.0f, -350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(200.0f, 0.0f, -450.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(100.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(500.0f, 0.0f, -350.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(450.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(2, 1, D3DXVECTOR3(500.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(4, 1, D3DXVECTOR3(250.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);

	//��----------------------------------
	SetWall(7, 1, D3DXVECTOR3(150.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(2, 1, D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(2, 1, D3DXVECTOR3(550.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(200.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(2, 1, D3DXVECTOR3(450.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(50.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(50.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(2, 1, D3DXVECTOR3(100.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(2, 1, D3DXVECTOR3(200.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(400.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(2, 1, D3DXVECTOR3(450.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(500.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(3, 1, D3DXVECTOR3(400.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);

	//�B�̕�----------------------------------
	SetWall(2, 1, D3DXVECTOR3(200.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4);
	SetWall(1, 1, D3DXVECTOR3(300.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4);
	SetWall(1, 1, D3DXVECTOR3(150.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 4);
	SetWall(2, 1, D3DXVECTOR3(300.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 4);
	SetWall(1, 1, D3DXVECTOR3(250.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 5);//��C
	SetWall(1, 1, D3DXVECTOR3(400.0f, 0.0f, -450.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 4);
	SetWall(1, 1, D3DXVECTOR3(400.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 5);//��A
	SetWall(2, 1, D3DXVECTOR3(300.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 4);
	SetWall(2, 1, D3DXVECTOR3(250.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 4);
	SetWall(1, 1, D3DXVECTOR3(300.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 4);
	SetWall(1, 1, D3DXVECTOR3(350.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 5);//��B
	SetWall(1, 1, D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 4);
	SetWall(1, 1, D3DXVECTOR3(250.0f, 0.0f, -50.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 5);//��D
	SetWall(2, 1, D3DXVECTOR3(200.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 4);
	SetWall(2, 1, D3DXVECTOR3(350.0f, 0.0f, -350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4);
	SetWall(1, 1, D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4);
	SetWall(1, 1, D3DXVECTOR3(250.0f, 0.0f, -50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4);
	SetWall(1, 1, D3DXVECTOR3(350.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4);
	SetWall(2, 1, D3DXVECTOR3(300.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4);


	MakeVertexWall(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitWall(void)
{
	for (int nCnt = 0; nCnt < MAX_WALLTEX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureWall[nCnt] != NULL)
		{
			g_pTextureWall[nCnt]->Release();
			g_pTextureWall[nCnt] = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (g_pVtxBuffWall[nCnt] != NULL)
		{
			g_pVtxBuffWall[nCnt]->Release();
			g_pVtxBuffWall[nCnt] = NULL;
		}
		//�C���f�b�N�X�o�b�t�@�̔j��
		if (g_pIdxBuffWall[nCnt] != NULL)
		{
			g_pIdxBuffWall[nCnt]->Release();
			g_pIdxBuffWall[nCnt] = NULL;
		}
	}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateWall(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X


	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (nCnt >= 4)
		{
			// �����_�[�X�e�[�g�̐ݒ�
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// ���ʂ��J�����O
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

		}
		if (g_Wall[nCnt].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Wall[nCnt].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[nCnt].rot.y, g_Wall[nCnt].rot.x, g_Wall[nCnt].rot.z);
			D3DXMatrixMultiply(&g_Wall[nCnt].mtxWorld, &g_Wall[nCnt].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Wall[nCnt].pos.x, g_Wall[nCnt].pos.y, g_Wall[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Wall[nCnt].mtxWorld, &g_Wall[nCnt].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Wall[nCnt].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffWall[nCnt], 0,
				sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffWall[nCnt]);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureWall[g_Wall[nCnt].nTexType]);
			// �X�e�[�W1�̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
				0,
				0,
				g_Wall[nCnt].VertexStage,	  //���_��
				0,
				g_Wall[nCnt].PolygonStage);//�|���S����
		}
	
		// �����_�[�X�e�[�g�̐ݒ�
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
		//���e�X�g�̖�����
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	}

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;//���_���ւ̃|�C���^
	WORD*pIdx;		//�C���f�b�N�X�f�[�^�ւ̃|�C���^
	int nCntIdx;	//�C���f�b�N�X�̃J�E���^�[

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, WALL_TEXTUER, &g_pTextureWall[0]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEXTUER1, &g_pTextureWall[1]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEXTUER2, &g_pTextureWall[2]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEXTUER3, &g_pTextureWall[3]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEXTUER4, &g_pTextureWall[4]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEXTUER5, &g_pTextureWall[5]);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		// ���_�o�b�t�@�𐶐�
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_Wall[nCnt].VertexStage * MAX_WALL,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffWall[nCnt],
			NULL);

		//�C���f�b�N�X�o�b�t�@�̐���
		pDevice->CreateIndexBuffer(sizeof(WORD) * g_Wall[nCnt].IndexStage*MAX_WALL,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,		//16bit�m�ۂ���
			D3DPOOL_MANAGED,
			&g_pIdxBuffWall[nCnt],
			NULL);


		// ���_���̐ݒ�----------------------------------------
		//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffWall[nCnt]->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCntz = 0; nCntz <= g_Wall[nCnt].Heidth; nCntz++)
		{//�c
			for (int nCntx = 0; nCntx <= g_Wall[nCnt].Width; nCntx++)
			{//��
				//���_���W��ݒ�
				pVtx[0].pos = D3DXVECTOR3(-WALLVTX_X + (WALLVTX_X * nCntx), WALLVTX_Y - (WALLVTX_Y * nCntz), 0.0f);

				//�@���̐ݒ�i���̐�����S��������1.0(-1.0)�ɂȂ�j
				pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				//���_�J���[��ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//�e�N�X�`���̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f + (1.0f * nCntx), 0.0f + (1.0f * nCntz));

				pVtx += 1;
			}
		}
		//���_�o�b�t�@�̃A�����b�N
		g_pVtxBuffWall[nCnt]->Unlock();

		// �C���f�b�N�X���̐ݒ�----------------------------------------
		//�C���f�b�N�X�o�b�t�@�����b�N���ăC���f�b�N�X�o�b�t�@�f�[�^�ւ̃|�C���^���擾
		g_pIdxBuffWall[nCnt]->Lock(0, 0, (void**)&pIdx, 0);

		nCntIdx = 0;//�C���f�b�N�X�J�E���^�[�̏�����

		for (int nCntIdx_Z = 0; nCntIdx_Z < g_Wall[nCnt].Heidth; nCntIdx_Z++)
		{//Z��
			for (int nCntIdx_X = 0; nCntIdx_X <= g_Wall[nCnt].Width; nCntIdx_X++, nCntIdx++)
			{//X���iIdx���ꏏ�ɐ�����j
				pIdx[0] = (g_Wall[nCnt].Width + 1) + nCntIdx;		//(����+1)+Idx�J�E���g
				pIdx[1] = nCntIdx;									//Idx�J�E���g�̐�
				pIdx += 2;											//�j�R�C�`�Ői�߂�

			//�����̒[�܂œ��B�����@&&�@�c���̃J�E���g���c��-1��菬����
				if (nCntIdx_X == g_Wall[nCnt].Width && nCntIdx_Z < g_Wall[nCnt].Heidth - 1)
				{
					pIdx[0] = nCntIdx;									//Idx�J�E���g�̐�
					pIdx[1] = (g_Wall[nCnt].Width + 1) + nCntIdx + 1;	//(����+1)+Idx�J�E���g+1
					pIdx += 2;											//�j�R�C�`�Ői�߂�
				}
			}
		}
		//�C���f�b�N�X�o�b�t�@�̃A�����b�N
		g_pIdxBuffWall[nCnt]->Unlock();
	}

	//���_���W��ݒ�
	//pVtx[0].pos = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
	//pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
	//pVtx[2].pos = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	//pVtx[3].pos = D3DXVECTOR3(-50.0f, 0.0f, 0.0f);
	//pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[5].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	//pVtx[6].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	//pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -50.0f);
	//pVtx[8].pos = D3DXVECTOR3(50.0f, 0.0f, -50.0f);

	////���_���W��ݒ�
	//pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(0.0f, 1.0f);
	//pVtx[2].pos = D3DXVECTOR3(0.0f, 2.0f);
	//pVtx[3].pos = D3DXVECTOR3(1.0f, 0.0f);
	//pVtx[4].pos = D3DXVECTOR3(1.0f, 1.0f);
	//pVtx[5].pos = D3DXVECTOR3(1.0f, 2.0f);
	//pVtx[6].pos = D3DXVECTOR3(2.0f, 0.0f);
	//pVtx[7].pos = D3DXVECTOR3(2.0f, 1.0);
	//pVtx[8].pos = D3DXVECTOR3(2.0f, 2.0f);

	//�C���f�b�N�X�̐ݒ�
	//pIdx[0] = 3;
	//pIdx[1] = 0;

	//pIdx[2] = 4;
	//pIdx[3] = 1;

	//pIdx[4] = 5;
	//pIdx[5] = 2;

	//pIdx[6] = 2;
	//pIdx[7] = 6;

	//pIdx[8] = 6;
	//pIdx[9] = 3;

	//pIdx[10] = 7;
	//pIdx[11] = 4;

	//pIdx[12] = 8;
	//pIdx[13] = 5;


}

//=============================================================================
// �X�e�[�W1�̔z�u
//=============================================================================
void SetWall(int Width, int Heidth, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int TexType)
{
	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (g_Wall[nCnt].bUse == false)
		{
			g_Wall[nCnt].Heidth = Heidth;
			g_Wall[nCnt].Width = Width;
			g_Wall[nCnt].pos = pos;
			g_Wall[nCnt].rot = rot;
			g_Wall[nCnt].nTexType = TexType;

			//Vtx,Index,Polygon�̌v�Z
			g_Wall[nCnt].VertexStage = (Width + 1) * (Heidth + 1);
			g_Wall[nCnt].IndexStage = (Width * Heidth) * 2 + (4 * (Heidth - 1)) + 2;
			g_Wall[nCnt].PolygonStage = (Width * Heidth * 2) + (4 * (Heidth - 1));
			g_Wall[nCnt].bUse = true;

			if (nCnt >= 4)
			{
				// �x�N�g���v�Z�̂��߂ɕǂ̃x�N�g���i���j���擾
				if (rot.y == 0)
				{//����Ă��Ȃ�
					g_Wall[nCnt].aPos[0] = D3DXVECTOR3(-50.0f + pos.x, 0.0f, pos.z + 10.0f);
					g_Wall[nCnt].aPos[1] = D3DXVECTOR3(-50.0f + pos.x + (50.0f*Width), 0.0f, pos.z + 10.0f);
					g_Wall[nCnt].aPos[2] = D3DXVECTOR3(-50.0f + pos.x + (50.0f*Width), 0.0f, pos.z - 10.0f);
					g_Wall[nCnt].aPos[3] = D3DXVECTOR3(-50.0f + pos.x, 0.0f, pos.z - 10.0f);
				}
				else
				{//����Ă���
					g_Wall[nCnt].aPos[0] = D3DXVECTOR3(pos.x - 10.0f, 0.0f, 50.0f + pos.z);
					g_Wall[nCnt].aPos[1] = D3DXVECTOR3(pos.x + 10.0f, 0.0f, 50.0f + pos.z);
					g_Wall[nCnt].aPos[2] = D3DXVECTOR3(pos.x + 10.0f, 0.0f, 50.0f + pos.z + (-50.0f*Width));
					g_Wall[nCnt].aPos[3] = D3DXVECTOR3(pos.x - 10.0f, 0.0f, 50.0f + pos.z + (-50.0f*Width));

				}
			}
			else
			{
				g_Wall[nCnt].aPos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_Wall[nCnt].aPos[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_Wall[nCnt].aPos[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_Wall[nCnt].aPos[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			}

		break;
		}
	}
}
//=============================================================================
// �������̕ǂ����蔻��i�v���C���[�j
//=============================================================================
void CollisionWall_WIDTH_PL(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[MAX_WALL];		//�����蔻��̌v�Z����
	Player*pPlayer = GetPlayer();

	for (int nCnt = 4; nCnt < MAX_WALL; nCnt++)
	{//�ǂ̖���
		if (g_Wall[nCnt].bUse == true)
		{//�ǂ��o�Ă���
			if (g_Wall[nCnt].rot.y == 0.0f)
			{//����Ă��Ȃ���
				if (g_Wall[nCnt].aPos[0].x < pPlayer->pos.x &&
					g_Wall[nCnt].aPos[1].x > pPlayer->pos.x)
				{//�ǂ͈̔�
					if (g_Wall[nCnt].pos.z > posOld->z)
					{//�O���瓖������

						//�x�N�g���v�Z
						g_Wall[nCnt].VecA = g_Wall[nCnt].aPos[2] - g_Wall[nCnt].aPos[3];
						g_Wall[nCnt].VecC = pPlayer->pos - g_Wall[nCnt].aPos[2];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall[nCnt].VecA.z*g_Wall[nCnt].VecC.x) - (g_Wall[nCnt].VecA.x*g_Wall[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							pPlayer->pos.z = g_Wall[nCnt].aPos[2].z - pPlayer->vtxMax.z + 5.0f;
							break;
						}
					}
					else if (g_Wall[nCnt].pos.z < posOld->z)
					{//��납�瓖������

						//�x�N�g���v�Z
						g_Wall[nCnt].VecA = g_Wall[nCnt].aPos[0] - g_Wall[nCnt].aPos[1];
						g_Wall[nCnt].VecC = pPlayer->pos - g_Wall[nCnt].aPos[0];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall[nCnt].VecA.z*g_Wall[nCnt].VecC.x) - (g_Wall[nCnt].VecA.x*g_Wall[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							pPlayer->pos.z = g_Wall[nCnt].aPos[0].z - pPlayer->vtxMax.z + 5.0f;
							break;
						}

					}
				}
			}
		}
	}
}
//=============================================================================
// �c�����ǂ����蔻��i�v���C���[�j
//=============================================================================
void CollisionWall_HEIDTH_PL(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[MAX_WALL];		//�����蔻��̌v�Z����
	Player*pPlayer = GetPlayer();
	ItemUI*pItemUI = GetItemUI();

	for (int nCnt = 4; nCnt < MAX_WALL; nCnt++)
	{//�ǂ̖���
		if (g_Wall[nCnt].bUse == true)
		{//�ǂ��o�Ă���
			if (g_Wall[nCnt].rot.y != 0.0f)
			{//����Ă���
				if (g_Wall[nCnt].aPos[1].z > pPlayer->pos.z &&
					g_Wall[nCnt].aPos[2].z < pPlayer->pos.z)
				{//�ǂ͈̔�
					if (g_Wall[nCnt].pos.x < posOld->x)
					{//�E���瓖������

					 //�x�N�g���v�Z
						g_Wall[nCnt].VecA = g_Wall[nCnt].aPos[1] - g_Wall[nCnt].aPos[2];
						g_Wall[nCnt].VecC = pPlayer->pos - g_Wall[nCnt].aPos[1];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall[nCnt].VecA.z*g_Wall[nCnt].VecC.x) - (g_Wall[nCnt].VecA.x*g_Wall[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							if (g_Wall[nCnt].nTexType == 5)
							{
								if (pItemUI->bUse == true)
								{
									g_Wall[nCnt].bUse = false;
									PlaySound(SOUND_LABEL_SE_OAPNDOOR);
									g_nCntLockWall++;

								}
							}
							pPlayer->pos.x = g_Wall[nCnt].aPos[1].x - pPlayer->vtxMin.x - 5.0f;
							break;
						}
					}
					if (g_Wall[nCnt].pos.x > posOld->x)
					{//�����瓖������

					 //�x�N�g���v�Z
						g_Wall[nCnt].VecA = g_Wall[nCnt].aPos[3] - g_Wall[nCnt].aPos[0];
						g_Wall[nCnt].VecC = pPlayer->pos - g_Wall[nCnt].aPos[3];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall[nCnt].VecA.z*g_Wall[nCnt].VecC.x) - (g_Wall[nCnt].VecA.x*g_Wall[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							if (g_Wall[nCnt].nTexType == 5)
							{
								if (pItemUI->bUse == true)

								{
									g_Wall[nCnt].bUse = false;
									PlaySound(SOUND_LABEL_SE_OAPNDOOR);
									g_nCntLockWall++;

								}
							}
							pPlayer->pos.x = g_Wall[nCnt].aPos[3].x + pPlayer->vtxMin.x + 5.0f;
							break;
						}
					}
				}
			}
		}
	}
	if (g_nCntLockWall == 4)
	{
		DeleteItemGetUI(0);
		g_nCntLockWall = 0;
	}

}
//=============================================================================
// �������̕ǂ����蔻��i�G�j
//=============================================================================
bool CollisionWall_WIDTH_ENE(D3DXVECTOR3 *pos, D3DXVECTOR3 aPos, D3DXVECTOR3 *posOld,D3DXVECTOR3 *rot)
{//aPos == ��ׂ�p
	float VecLine[MAX_WALL];		//�����蔻��̌v�Z����
	bool bLand;

	for (int nCnt = 4; nCnt < MAX_WALL; nCnt++)
	{//�ǂ̖���
		if (g_Wall[nCnt].bUse == true)
		{//�ǂ��o�Ă���

			bLand = false;
			
			if (g_Wall[nCnt].rot.y == 0.0f)
			{//����Ă��Ȃ���

				if (g_Wall[nCnt].aPos[0].x < aPos.x &&
					g_Wall[nCnt].aPos[1].x > aPos.x)
				{//�ǂ͈̔�
					if (g_Wall[nCnt].pos.z > posOld->z)
					{//�O���瓖������

					 //�x�N�g���v�Z
						g_Wall[nCnt].VecA = g_Wall[nCnt].aPos[2] - g_Wall[nCnt].aPos[3];
						g_Wall[nCnt].VecC = aPos - g_Wall[nCnt].aPos[2];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall[nCnt].VecA.z*g_Wall[nCnt].VecC.x) - (g_Wall[nCnt].VecA.x*g_Wall[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							rot->y = 0.0f;
							bLand = true;
							break;
						}
					}
					else if (g_Wall[nCnt].pos.z < posOld->z)
					{//��납�瓖������

					 //�x�N�g���v�Z
						g_Wall[nCnt].VecA = g_Wall[nCnt].aPos[0] - g_Wall[nCnt].aPos[1];
						g_Wall[nCnt].VecC = aPos - g_Wall[nCnt].aPos[0];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall[nCnt].VecA.z*g_Wall[nCnt].VecC.x) - (g_Wall[nCnt].VecA.x*g_Wall[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							rot->y = D3DX_PI;
							bLand = true;
							break;
						}
					}
				}
			}
		}
	}
	return bLand;

}
//=============================================================================
// �c�����̕ǂ����蔻��i�G�j
//=============================================================================
bool CollisionWall_HEIDTH_ENE(D3DXVECTOR3 *pos, D3DXVECTOR3 aPos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *rot)
{
	float VecLine[MAX_WALL];		//�����蔻��̌v�Z����
	bool bLand;

	for (int nCnt = 4; nCnt < MAX_WALL; nCnt++)
	{//�ǂ̖���
		if (g_Wall[nCnt].bUse == true)
		{//�ǂ��o�Ă���

			bLand = false;

			if (g_Wall[nCnt].rot.y != 0.0f)
			{//����Ă���
				if (g_Wall[nCnt].aPos[1].z > aPos.z &&
					g_Wall[nCnt].aPos[2].z < aPos.z)
				{//�ǂ͈̔�
					if (g_Wall[nCnt].pos.x < posOld->x)
					{//�E���瓖������

					 //�x�N�g���v�Z
						g_Wall[nCnt].VecA = g_Wall[nCnt].aPos[1] - g_Wall[nCnt].aPos[2];
						g_Wall[nCnt].VecC = aPos - g_Wall[nCnt].aPos[1];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall[nCnt].VecA.z*g_Wall[nCnt].VecC.x) - (g_Wall[nCnt].VecA.x*g_Wall[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							rot->y = D3DX_PI * -0.5f;
							bLand = true;
							break;
						}
					}
					if (g_Wall[nCnt].pos.x > posOld->x)
					{//�����瓖������

					 //�x�N�g���v�Z
						g_Wall[nCnt].VecA = g_Wall[nCnt].aPos[3] - g_Wall[nCnt].aPos[0];
						g_Wall[nCnt].VecC = aPos - g_Wall[nCnt].aPos[3];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall[nCnt].VecA.z*g_Wall[nCnt].VecC.x) - (g_Wall[nCnt].VecA.x*g_Wall[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							rot->y = D3DX_PI * 0.5f;
							bLand = true;
							break;
						}
					}
				}
			}
		}
	}

	return bLand;
}

//=============================================================================
// �X�e�[�W1�̎擾
//=============================================================================
Wall*GetWall(void)
{
	return &g_Wall[0];
}