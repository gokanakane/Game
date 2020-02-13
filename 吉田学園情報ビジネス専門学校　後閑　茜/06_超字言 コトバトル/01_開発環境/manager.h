//=============================================================================
//
// �}�l�[�W������ [manager.h]
// Author : �ڍ� ������
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "sound.h"
#include "renderer.h"

#include "texture.h"
#include "Command.h"
#include "UtilityMath.h"

//=============================================================================
// �O���錾
//=============================================================================
class CRenderer;
class CInputKeyboard;
class CCamera;
class CLight;
class CDebugProc;
class CMask;
class CFade;
class CGame;
class CTitle;
class CSelect;
class CResult;
class CUltimate;
class CCharacterMove;
class CInputXPad;
class CSound;
class CTutorial;
class CCharaSelect;
class CStageSelect;
class CCameraManager;

class CPlayer;
class CTube;
class CSetWord;
class CMeshField;
class CPoint;
//=============================================================================
// �}�N��
//=============================================================================
#define PLAYER_RIGHT		(DIK_D)
#define PLAYER_LEFT			(DIK_A)
#define PLAYER_A_BUTTON		(DIK_F)
#define PLAYER_B_BUTTON		(DIK_G)
#define PLAYER_C_BUTTON		(DIK_S)

#define ENEMY_RIGHT			(DIK_NUMPAD6)
#define ENEMY_LEFT			(DIK_NUMPAD4)
#define ENEMY_A_BUTTON		(DIK_ADD)
#define ENEMY_B_BUTTON		(DIK_NUMPADENTER)
#define ENEMY_C_BUTTON		(DIK_NUMPAD5)
#define PLAYER_C_BUTTON		(DIK_S)
#define MAX_SOUND			(4)
#define MAX_PLAYER			(4)

//=============================================================================
// �}�N��(�R���g���[���[)
//=============================================================================

//=============================================================================
// �N���X�̒�`
//=============================================================================
//=====================
// �}�l�[�W���N���X
//=====================
class CManager
{
public:
	typedef enum
	{
		DIR_RIGHT_EAST,
		DIR_LEFT_WEST,
		DIR_DOWN_SOUTH,
		DIR_UP_NORTH,
	}DIRECTION;

	typedef enum
	{//���[�h�̍\����
		MODE_NONE = 0,
		MODE_TITLE,
		MODE_SELECT,
		MODE_TUTORIAL,
		MODE_STAGESELECT,
		MODE_CHARASELECT,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	}MODE;

	CManager();		// �R���X�g���N�^
	~CManager();	// �f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetInputKeyboard(void);
	//static CCamera *GetCamera(void);
	static CMask *GetMask(void);
	static CCharacterMove *GetCharacterMove(void);
	static CFade *GetFade(void) { return m_pFade; };
	static MODE GetMode(void) { return m_mode; };
	static void SetMode(MODE mode);
	static CGame *GetGame(void) { return m_pGame; }
	static CTitle *GetTitle(void) { return m_pTitle; }
	static CSelect *GetSelect(void) { return m_pSelect; }
	static CTutorial *GetTutorial(void) { return m_pTutorial; }
	static CCharaSelect *GetCharaSelect(void) { return m_pCharaSelect; }
	static CStageSelect *GetStageSelect(void) { return m_pStageSelect; }
	static CResult *GetResult(void) { return m_pResult; }
	static CInputXPad *GetXInput(int nID) { return m_pXInput[nID]; }
	static CSound *GetSound(int nNum);
	static CSound *GetSound(void) { return m_pSound[0]; }			// �T�E���h�擾

	static CCameraManager* GetCameraManager(void) { return m_pCameraManager; };
#ifdef _DEBUG
	static bool GetRepeat(void) { return bRepeatGame; };
#endif

	//�����̃��[�h�������Ă���l���擾
	static CPlayer* GetPlayer(int nID);
	static CTube* GetTube(int nID);
	static CSetWord* GetWordCreate(void);
	static CMeshField* GetMeshField(void);
	static CPoint* GetPoint(int nNum);
private:
	static CRenderer *m_pRenderer;
	static CInputKeyboard *m_pInputKeyboard;
	//static CCamera *m_pCamera;
	static CLight *m_pLight;
	static CDebugProc *m_pDebugProc;

	static CMask *m_pMask;
	static CFade *m_pFade;
	static CCharacterMove *m_pCharacterMove;
	static CGame *m_pGame;
	static CTitle *m_pTitle;
	static CSelect *m_pSelect;
	static CTutorial *m_pTutorial;
	static CResult *m_pResult;
	static CCharaSelect *m_pCharaSelect;
	static CStageSelect *m_pStageSelect;

	static CCameraManager* m_pCameraManager;
	static CInputXPad *m_pXInput[MAX_PLAYER];
	static MODE m_mode;
	static CSound	*m_pSound[MAX_SOUND];	// �T�E���h�̃|�C���^


#ifdef _DEBUG
	static bool bRepeatGame;
	static int nTitleCnt;
	static int nSelectCnt;
	static int nTutoCnt;
	static int nCharaSelCnt;
	static int nStaSelCnt;
	static int nGameCnt;
	static int nResultCnt;
#endif
};

//==================================================================================================//
//     �e���v���[�g��`(Scene�n�ȊO�̐���)
//==================================================================================================//
template<class T> bool ObjCreate(T *&pObj)
{
	pObj = NULL;
	pObj = new T;
	if (pObj != NULL) { pObj->Init(); return true; }
	return false;
}

//==================================================================================================//
//     �e���v���[�g��`(Scene�n�ȊO�̉��)
//==================================================================================================//
template<class T> bool ObjRelease(T *&pObj)
{
	if (pObj != NULL)
	{
		pObj->Uninit();
		delete pObj;
		pObj = NULL;
		return true;
	}
	return false;
}

#endif