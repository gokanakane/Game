//=============================================================================
//
// �w�i���� [MIST.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "main.h"
#include "Player.h"
#include "mist.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MIST_TEXTUER  "data\\TEXTURE\\BG\\mist.png" //�ǂݍ��ރe�N�X�`��
#define MIST_POS_X (0)					   //�w�i����X
#define MIST_POS_Y (500)					   //�w�i����Y
#define MAX_TEX  (2)					   //�e�N�X�`���̖���
#define MIST_MOVE (3.0f)
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureMist = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMist = NULL;
int g_nCntMist = 0;

//=============================================================================
// �|���S������������[InitPolygon]
//=============================================================================
void InitMist(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MIST_TEXTUER, &g_pTextureMist);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, 
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D, 
								D3DPOOL_MANAGED,
								&g_pVtxBuffMist, NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMist->Lock(0, 0, (void**)&pVtx,0);

		//�w�i�̍��W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(MIST_POS_X, MIST_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, MIST_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[2].pos = D3DXVECTOR3(MIST_POS_X, SCREEN_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�w�i�F�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);//��ڂ̒��_�̐F�w��i�E���j

		//�w�i�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMist->Unlock();

}
//=============================================================================
//�|���S���I������ [UninitPolygon]
//=============================================================================
void UninitMist(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMist != NULL)
	{
		g_pTextureMist->Release();
		g_pTextureMist = NULL;
	}



	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMist != NULL)
	{
		g_pVtxBuffMist->Release();
		g_pVtxBuffMist = NULL;
	}

}

//=============================================================================
// �|���S���X�V����[UpdataPolygon]
//=============================================================================
void UpdateMist(void)
{
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^
	g_nCntMist++;

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMist->Lock(0, 0, (void**)&pVtx, 0);

	//�w�i�̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + (-g_nCntMist*(0.001f + 1)), 0.0f);//��ڂ̒��_�̏ꏊ�w��
	pVtx[1].tex = D3DXVECTOR2(1.0f + (-g_nCntMist*(0.001f + 1)), 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[2].tex = D3DXVECTOR2(0.0f + (-g_nCntMist*(0.001f + 1)), 1.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[3].tex = D3DXVECTOR2(1.0f + (-g_nCntMist*(0.001f + 1)), 1.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMist->Unlock();

}
//=============================================================================
// �|���S���`�ʏ���[DrawPolygon]
//=============================================================================
void DrawMist(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMist, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMist);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			2);
}