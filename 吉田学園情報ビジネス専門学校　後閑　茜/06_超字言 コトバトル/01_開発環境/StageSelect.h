//=============================================================================
//
// �X�e�[�W�Z���N�g�̏��� [StageSelect.h]
// Author : �ڍ�������
//
//=============================================================================
#ifndef _STAGESELECT_H_
#define _STAGESELECT_H_

#include "scene.h"

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;
class CFade;
class CManager;
class CSetObject;
class CMeshField;
class CWall;
class CPlayerSelect;
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_STAGESELECT		(2)
#define MAX_STAGESELECT_TEX (7)

class CStageSelect
{
public:
	CStageSelect();
	~CStageSelect();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CStageSelect *Create(void);
	static int GetStageState(void) { return m_nSelect; }

private:
	/* �|���S���̎�� */
	typedef enum
	{
		STAGESELECTTYPE_BG = 0,			//�w�i
		STAGESELECTTYPE_BAND_L,			//�сF��
		STAGESELECTTYPE_BAND_R,			//�сF�E
		STAGESELECTTYPE_FRAME,			//�����g
		STAGESELECTTYPE_EXPLANATION,	//����
		STAGESELECTTYPE_UI_OPERATION,	//����UI
		STAGESELECTTYPE_UI_DECISION,	//�I��UI
		STAGESELECTTYPE_MAX				//�ő吔
	}STAGESELECTTYPE;

	/* �I����� */
	typedef enum
	{
		SELECTTYPE_SELECT_MACHINE = 0,			//�@�B�X�e�[�W
		SELECTTYPE_SELECT_WEATHER,				//�V��X�e�[�W
		SELECTTYPE_MAX							//��Ԃ̑���
	}SELECTTYPE;

	/* �X�e�[�W�ǂݍ��݂̏�� */
	typedef enum
	{
		STAGELOAD_NONE = 0,
		STAGELOAD_LOAD,
		STAGELOAD_UNLOAD,
		STAGELOAD_MAX
	}STAGELOAD;

	/* �}�X�N�̃t�F�[�h��� */
	typedef enum
	{
		MASKFADE_NONE = 0,
		MASKFADE_IN,
		MASKFADE_OUT,
		MASKFADE_MAX
	}MASKFADE;

	void InitPolygon(void);												//�|���S���̏����ݒ�
	void ScrollMenu(STAGESELECTTYPE type, float fScroolSpeed);			//�e�N�X�`���X�N���[������
	void Selecttype(SELECTTYPE state, CFade *pFade, CManager *pManager);//�I����Ԃ̊Ǘ�
	void ProductionIcon(SELECTTYPE type);								//�I�����̈ړ����o
	void SetStage(int nNumState);										//�X�e�[�W�����̏���
	void LoadStage(int nNum);											//�X�e�[�W�̃��[�h����
	void StageLoadState(STAGELOAD Load,int nSel);						//�X�e�[�W���[�h�̏��
	void MaskFade(void);												//�}�X�N�̃t�F�[�h����
	void InitPointer(void);												//�|�C���^�̏���������
	void SetSelectAnimation(STAGESELECTTYPE type, int AnimType, int MaxAnimPatternX, int MaxAnimPatternY, int AnimSpeed);

	/* �ϐ� */
	static CScene2D *m_apScene2D[MAX_STAGESELECT_TEX];				//���o�n2D
	static CScene2D *m_apSelect2D[MAX_STAGESELECT];					//�I����2D
	static CScene2D *m_pMask2D;										//�J�����}�X�N
	static int	m_nSelect;											// �I�����Ă���ԍ�
	static CMeshField *m_pMeshField;								//��
	static CWall *m_pWall[4];										//��
	SELECTTYPE m_type, m_typeOld;												//�I������Ă���ԍ��̏��
	char *m_pcStageSelect[MAX_STAGESELECT];							// �X�e�[�W�̖��O�ۊ�
	CSetObject *m_pObj;

	/* ���o�n�ϐ� */
	int m_nCntScrool;												//�X�N���[���̃J�E���^�[
	D3DXVECTOR3 m_SelectPos[MAX_STAGESELECT];						//�Z���N�g�̈ʒu��ۑ�
	float m_fWidth[MAX_STAGESELECT], m_fHeight[MAX_STAGESELECT];	//�c�Ɖ��̌`��ۑ����Ă���
	D3DXCOLOR m_IconCol[MAX_STAGESELECT];							//�F��ۑ����Ă���
	D3DXVECTOR3 m_CameraRot, m_CameraPosV,m_CameraPosR;				//�J����
	bool m_bLoad;													//�X�e�[�W�̓ǂݍ��݂��P�񂾂����t���O
	MASKFADE m_MaskFade;											//�}�X�N�̃t�F�[�h����
	float m_fMaskAlpha;
	int m_nCntAnim;													//�A�j���[�V�����̃J�E���^�[
	int m_nPatturnAnim;												//�A�j���[�V�����̃p�^�[��

#ifdef _DEBUG
	int nCntFadeTime = 0;
#endif
};
#endif