//=============================================================================
//
// �v���C���[�l���I����ʏ��� [PlayerNumSelect.h]
// Author : Mikiya Meguro/Akane Gokan
//
//=============================================================================
#ifndef _PLAYERSELECT_H_
#define _PLAYERSELECT_H_

#include "main.h"
#include "input.h"
#include "scene.h"

//*****************************************************************************
//�@�O���錾
//*****************************************************************************
class CScene2D;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PLAYER_SELECTMENU		(4)	//�v���C���[�l���̍ő�l
#define MAX_CAUTIONMENU				(2)	//�x���̑I�����̍ő吔
#define MAX_PLAYERNUMSEL_BG			(7)	//BG�̍ő�|���S���i���o�p�j

//*********************************************************************
//�Q�[���N���X�̒�`
//*********************************************************************
class CPlayerSelect : public CScene //�h���N���X
{
public:
	/* �v���C���[�l���̎�� */
	typedef enum
	{
		SELECTPLAYER_NONE = 0,
		SELECTPLAYER_1P,			//�v���C�l���F1�l
		SELECTPLAYER_2P,			//�v���C�l���F2�l
		SELECTPLAYER_3P,			//�v���C�l���F3�l
		SELECTPLAYER_4P,			//�v���C�l���F4�l
		SELECTPLAYER_MAX			//��Ԃ̑���
	}SELECTPLAYER;

	/* �I�����̏�� */
	typedef enum
	{
		SELECTTYPE_NONE = 0,	//�I�΂�Ă��Ȃ����
		SELECTTYPE_SELECT,		//�I�΂�Ă���	���
		SELECTTYPE_MAX			//��Ԃ̑���
	}SELECT;

	/* ���j���[�̗񋓌^ */
	typedef struct
	{
		SELECT		select;		//�Z���N�g
		D3DXVECTOR3 pos;		//�ʒu
		D3DXCOLOR	col;		//�J���[
	}SELECTMENU;

	CPlayerSelect(int nPriority = 7);
	~CPlayerSelect();
	static CPlayerSelect *Create(D3DXVECTOR3 pos, float fLength);
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static SELECTPLAYER *GetModeSelectMode(void) { return &m_SelectMode; }						//�I���������[�h�̎擾
	static HRESULT Load(void) { return S_OK; }													//�ǂݍ���
	static void UnLoad(void);																	//�j��
	static bool GetModeSelectBool(void) { return m_bModeSelect; }								//���[�h���I�΂ꂽ���̎擾
	static void SetModeSelectBool(bool ModeSelectBool) { m_bModeSelect = ModeSelectBool; }		//���[�h���I�΂ꂽ���̐ݒ�
	void Caution2DUninit(void);																	//�x���̏I������

private:

	/* �w�i�̎�� */
	typedef enum
	{
		PLNUMSELECTBGTYPE_BG = 0,
		PLNUMSELECTBGTYPE_BAND_L,
		PLNUMSELECTBGTYPE_BAND_R,
		PLNUMSELECTBGTYPE_FRAME,
		PLNUMSELECTBGTYPE_MENU

	}PLNUMSELECTBGTYPE;

	/* �A�j���[�V�����̊������� */
	typedef enum
	{
		ANIMTYPE_NONE = 0,
		ANIMTYPE_X,
		ANIMTYPE_Y,
		ANIMTYPE_MAX

	}ANIMTYPE;

	HRESULT InitPointer(void);													//�e��|�C���^�̏�����
	void InitProductionPos(void);												//���o�|���S���̏����ݒ�
	void ScrollMenu(PLNUMSELECTBGTYPE type, float fScroolSpeed);				//�X�N���[��
	void PlayerSelectMove(PLNUMSELECTBGTYPE type, int MenuNum);					//�|���S���ړ����o
	void SetPlayerSelNumMenuPos(int MenuNum);									//�I�����̊�{�ʒu
	void SetSelectAnimation(PLNUMSELECTBGTYPE type, ANIMTYPE AnimType,
		int MenuNum, int MaxAnimPatternX, int MaxAnimPatternY, int AnimSpeed);	//�A�j���[�V����

	D3DXVECTOR3					m_InitPos;										//�l���I���̏����ʒu
	D3DXVECTOR3					m_ChoicePos[MAX_CAUTIONMENU];					//�x���̏����ʒu
	float						m_fWidth, m_fHeight;							// ������
	D3DXVECTOR3					m_TexMove;										//�e�N�X�`���̈ړ���


	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_PLAYER_SELECTMENU];				// �e�N�X�`���|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;										// ���_�o�b�t�@�ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	m_pTextureBG;									// �e�N�X�`���|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuffBG;									// ���_�o�b�t�@�ւ̃|�C���^
	CScene2D					*m_apPolygonBG[MAX_PLAYERNUMSEL_BG];			// ���j���[�̃|���S��

	SELECTMENU					m_aModeSelectMenu[MAX_PLAYER_SELECTMENU];		// �|�[�Y���j���[
	D3DXVECTOR3					m_Pos[MAX_PLAYER_SELECTMENU];					// �ʒu
	static SELECTPLAYER			m_SelectMode;									// �I�����Ă郂�[�h
	int							m_nSelect;										// �I�����Ă���ԍ�
	CScene2D					*m_apPolygon[MAX_PLAYER_SELECTMENU];			// ���j���[�̃|���S��
	static	bool				m_bModeSelect;									// �|�[�Y�̏��
	bool						m_bCaution;										// ����̌x��
	bool						m_bCreate2D;									// 2D����������ǂ���

	CScene2D					*m_pCaution2D;									// �x���̃|���S��
	CScene2D					*m_pCaution2DBG;								// �x���̃|���S��BG
	CScene2D					*m_pSelect2D[MAX_CAUTIONMENU];					// ���j���[�̃|���S��
	int							m_nSelectCaution;								// �I�����Ă���ԍ�
	SELECTMENU					m_SelectCaution[MAX_CAUTIONMENU];				// ���j���[

	/* ���o�ʕϐ� */
	int m_nCntScrool;		//�X�N���[���̃J�E���^�[
	int m_nCntAnim;			//�A�j���[�V�����̃J�E���^�[
	int m_nPatturnAnim;		//�A�j���[�V�����̃p�^�[��
	float m_fChangeMode;	//�I�𒆃��[�h�A�C�R���̈ړ�����J�E���^�[
	float m_fMoveMode;		//�I�𒆃��[�h�A�C�R���̈ړ��ʂ��v��

	int m_nCounter;			//�J�E���g


#ifdef _DEBUG
	int nCntFadeTime = 0;
#endif
};

#endif