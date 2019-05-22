//=============================================================================
//
// �G�t�F�N�g���� [effect.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"			// ���C��
#include "scene3d.h"		// �V�[��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_EFFECTTYPE (15)
#define MAX_EFFECT (1000)

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEffect : public CScene
{// �V�[��3D�i�e�FCScene�j
public:
	CEffect();																// �R���X�g���N�^
	~CEffect();																// �f�X�g���N�^
	HRESULT Init(void);														// ����������
	void Uninit(void);														// �I������
	void Update(void);														// �X�V����
	void Draw(void);														// �`�揈��
	static CEffect *Create(D3DXVECTOR3 pos, int nTextureType,int nTxstType);// ����
	static HRESULT Load(void);												// �e�N�X�`���̓ǂݍ���
	static void Unload(void);												// �j��
	void LoadSetEffect(int nTxsttype);										// �G�t�F�N�g�̏��ǂݍ���
	void LoadDataEffect(FILE *pFile,char read[128]);						// �G�t�F�N�g�̏��ǂݍ���(�f�[�^�ǂݍ���)
	static void LoadNameEffect(void);										// �G�t�F�N�g�̏��ǂݍ���(�e�L�X�g�̖��O�ǂݍ���)
	static void LoadTexNameEffect(void);									// �G�t�F�N�g�̏��ǂݍ���(�G�t�F�N�g�̉摜�̖��O�ǂݍ���)
private:
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_EFFECTTYPE];					// �e�N�X�`�����ւ̃|�C���^
	D3DXMATRIX					m_mtxWorld;									// ���[���h�}�g���b�N�X
	CScene3D					*m_apScene3D[MAX_EFFECT];								// �V�[��3D�̃|�C���^�^�ϐ�4
	static int					m_nEffectType;								// �G�t�F�N�g�̎��
	static D3DXVECTOR3			m_pos;										// �ʒu
	D3DXVECTOR2					m_TexUV;									// UV
	D3DXCOLOR					m_col;										// �F
	D3DXVECTOR3					m_rot;										// ����
	D3DXVECTOR3					m_size;										// �傫��
	int							m_nSetPoriMAX;								// �|���S���̐�
	int							m_nLife;									// �̗�
	D3DXVECTOR3					m_posRange;									// �ʒu�͈̔�
	D3DXVECTOR3					m_move;										// ����
	int							m_nBillType;								// ���Z�������邩�Ȃ������
	float						m_fGravity;									// �d��
	D3DXVECTOR3					m_NumMove[MAX_EFFECT];						// �����̊��蓖��
	int							m_nNumLife[MAX_EFFECT];						// �̗͊��蓖�Ă̐ݒ�
	static char					m_cTextName[MAX_EFFECTTYPE][128];			// �e�L�X�g�̖��O
	static char					m_cTextureName[MAX_EFFECTTYPE][128];		// �e�L�X�g�̖��O
	static int					m_nBindText;								// �ǂ̃e�L�X�g���G�t�F�N�g�Ɋ��蓖�Ă邩
	static int					m_nTexttureType;							// �e�N�X�`���̎��
	int							m_nAnimCounter;								// �A�j���[�V�����J�E���^�[
	int							m_nPatternCounter;							// �p�^�[���J�E���^�[
protected:

};

#endif