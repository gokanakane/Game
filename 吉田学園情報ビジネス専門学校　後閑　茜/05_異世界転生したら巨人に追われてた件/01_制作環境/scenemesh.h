//=============================================================================
//
// �V�[�����b�V������ [sceneMesh.h]
// Author : Eisuke Sakagawa
//
//=============================================================================
#ifndef _SCENEMESH_H_
#define _SCENEMESH_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		// ���C��
#include "scene.h"		// �V�[��

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSceneMesh : public CScene
{// �V�[�����b�V���i�e�FCScene�j
public:
	CSceneMesh(int nPriority, CScene::OBJTYPE objType);			// �R���X�g���N�^
	~CSceneMesh();									// �f�X�g���N�^

	typedef enum
	{// ���b�V���^�C�v
		MESHTYPE_FIELD = 0,			// �t�B�[���h
		MESHTYPE_WALL,				// �E�H�[��
		MESHTYPE_CYLINDER,			// �V�����_�[
		MESHTYPE_MAX
	}MESHTYPE;

	typedef enum
	{// �e�N�X�`���^�C�v
		MESHTEX_ALL = 0,			// �S��
		MESHTEX_NUMSIZE,			// ����
		MESHTEX_MAX
	}MESHTEX;

	typedef enum
	{
		SINTYPE_CIRCLE = 0,
		SINTYPE_RIGHT,
		SINTYPE_LEFT,
		SINTYPE_UP,
		SINTYPE_DOWN,
		SINTYPE_MAX
	}SINTYPE;

	typedef enum
	{
		SINSTART_POS = 0,
		SINSTART_CENTER,
		SINSTART_LU,
		SINSTART_RU,
		SINSTART_LD,
		SINSTART_RD,
		SINSTART_MAX
	}SINSTART;

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }		// �e�N�X�`�����f

	HRESULT Init(void);							// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

	void SetInitAll(MESHTYPE meshType, D3DXVECTOR3 num, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, MESHTEX meshTex);		// �����l�ݒ�

	void Setpos(D3DXVECTOR3 pos) { m_pos = pos; }	// �ʒu�ݒ�
	D3DXVECTOR3 Getpos(void) { return m_pos; }		// �ʒu�擾
	void Setrot(D3DXVECTOR3 rot) { m_rot = rot; }	// �ʒu�ݒ�
	D3DXVECTOR3 Getrot(void) { return m_rot; }		// �ʒu�擾
	D3DXVECTOR3 Getsize(void) { return m_size; }	// �ʒu�擾

	void SetTex(D3DXVECTOR2 TexMoveUV);				// �A�j���[�V�������ݒ�

	D3DXVECTOR3 GetVtx(int nNum);					// ���_
	D3DXVECTOR3 GetNor(int nNum);					// �@��

	bool ColInMesh(D3DXVECTOR3 pos);

	void SinUpdate(SINTYPE sinType, SINSTART sinStart, D3DXVECTOR3 pos, float frot, float fUp, float fLine);
	void SinUpdate(SINTYPE sinType, SINSTART sinStart, D3DXVECTOR3 pos, float frot, float fUp, float fLine, float fRange);

	void SetHeight(D3DXVECTOR3 pos, float fValue, float fRange);
	float GetHeight(D3DXVECTOR3 pos);				// �����擾
	float GetUpDown(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// �����擾
	float GetBlockNor(D3DXVECTOR3 pos);			// 

private:
	void SetVecNor(void);						// �@���v�Z

	LPDIRECT3DTEXTURE9		m_pTexture;			// �e�N�X�`�����ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@���ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;			// �C���f�b�N�X���ւ̃|�C���^
	D3DXMATRIX	m_mtxWorld;						// ���[���h�}�g���b�N�X
	int m_nMaxVtx;								// ���_�̍ő吔
	int m_nMaxIdx;								// �C���f�b�N�X�̍ő吔
	int m_nMaxPolygon;							// �|���S���̍ő吔

	MESHTYPE m_meshType;						// ���b�V���^�C�v
	MESHTEX m_meshTex;							// �e�N�X�`���^�C�v
	D3DXVECTOR3 m_num;							// ����
	D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR3 m_rot;							// ����
	D3DXVECTOR3 m_size;							// �傫��
	D3DXVECTOR2 m_TexUV;						// UV

protected:

};

#endif