//=============================================================================
//
// ���b�V���t�B�[���h�̏��� [meshFiled.h]
// Author :
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHFIELD_TEXTURE_NAME	"data\\TEXTURE\\field001.jpg"	// �n�ʂ̃e�N�X�`����
#define	TOUL_FILENAME			"toul.bin"					// �c�[���̃e�L�X�g
#define POLYGON_X				(20)						// �|���S���̐��iX�j
#define POLYGON_Z				(20)						// �|���S���̐��iZ�j
#define MESHFIELD_SIZE			(40.0f)						// ���b�V���t�B�[���h�̑傫��
#define NUM_POLYGON				(100000)					// ���b�V���t�B�[���h�̑傫��
#define MESH_CENTER				((POLYGON_X / 2) * -MESHFIELD_SIZE + (MESHFIELD_SIZE))	//�����l

//========================================
// �N���X�̒�`
//========================================
//=========================
// ���b�V���t�B�[���h�N���X
//=========================
class CMeshField : public CScene
{
public:
	CMeshField(int nPriority = 3, OBJTYPE objType = OBJTYPE_MESH_FIELD);	// �R���X�g���N�^
	~CMeshField();														// �f�X�g���N�^

	static CMeshField *Create(D3DXVECTOR3 pos,int nSplitX, int nSplitZ,float fWidth);							// �I�u�W�F�N�g�̐���

	HRESULT Init(void);										// ���b�V���t�B�[���h����������
	void Uninit(void);													// ���b�V���t�B�[���h�I������
	void Update(void);													// ���b�V���t�B�[���h�X�V����
	void Draw(void);													// ���b�V���t�B�[���h�`�揈��

	float GetHeight(D3DXVECTOR3 pos);									// �����̎擾
	bool GetHeightbool(D3DXVECTOR3 &pos);								//�n�ʂƂ̓����蔻��
	void SetHeight(D3DXVECTOR3 pos, float fValue, float fRange);		// �����̐ݒ�

	void SaveHeight(void);												// �����̃Z�[�u
	void LoadHeight(void);												// �����̃��[�h

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void BindTexture(LPCSTR TexTag);


private:
	LPDIRECT3DTEXTURE9		m_pTexture;									// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;									// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;									// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX				m_mtxWorld;									// ���[���h�}�g���b�N�X
	D3DXVECTOR3				m_pos;										// �|���S���̈ʒu
	D3DXVECTOR3				m_rot;										// �|���S���̌���
	D3DXVECTOR3				m_aNor[NUM_POLYGON];
	int						m_nNumVerTex;								// ���_��
	int						m_nNumIndex;								// �C���f�b�N�X��
	int						m_nNumPolygon;								// �|���S����
	bool					m_bRand;									// �|���S���ɏ���Ă���
	float					m_fWidth = 0, m_fDepth = 0;							// ������
	int						m_nSplitX = 0, m_nSplitZ = 0;						// ������
};

#endif