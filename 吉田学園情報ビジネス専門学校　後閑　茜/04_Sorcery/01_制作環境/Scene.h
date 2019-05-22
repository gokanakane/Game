//=============================================================================
//
// �V�[������ [scene.h]
// Author : 
//
//=============================================================================
#ifndef _SCENE_H
#define _SCENE_H

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_POLYGON (1000)				//�|���S���̍ő吔
#define MAX_MYPRIORITY (8)				//�D�揇��(�����Őݒ肵����)
//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X
//*****************************************************************************
class CScene
{
public:
	/* �I�u�W�F�N�g�̎�ށi��������ǉ�����j */
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_TUTORIAL,
		OBJTYPE_TITLE,
		OBJTYPE_RANKING,
		OBJTYPE_STAGESELECT,
		OBJTYPE_BG,
		OBJTYPE_PLAYER,
		OBJTYPE_ENEMY,
		OBJTYPE_BULLET,
		OBJTYPE_EXPLOTION,
		OBJTYPE_SCORE,
		OBJTYPE_EFFECT,
		OBJTYPE_FADE,
		OBJTYPE_PAUSE,
		OBJTYPE_UI,
		OBJTYPE_CUTIN,
		OBJTYPE_SHIELD,
		OBJTYPE_ABYSSGATE,
		OBJTYPE_PUTBULLET,
		OBJTYPE_MAX
	}OBJTYPE;

	/* 7:�@6:�t�F�[�h�@5:UI�n�@4:�v���C���[�@3:�G�@2:�G�t�F�N�g�@1:BG�@0: */
	CScene(int nPriority = 3);
	virtual ~CScene();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void ReleaseAll(void);
	static void ReleaseAllFade(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	void SetObjtype(OBJTYPE type);
	OBJTYPE GetObjtype(void) { return m_Objtype; }
	static CScene *GetScene(int nPriority,int nIdx);

protected:
	void Release(void);

private:
	static CScene *m_apScene[MAX_MYPRIORITY][MAX_POLYGON];
	static int m_nNumAll;
	int m_nId = 0;			//�������g�̔ԍ�
	OBJTYPE m_Objtype;
	int m_nPriority = 0;	//�D�揇��
};

#endif
