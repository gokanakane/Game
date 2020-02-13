//=============================================================================
//
// �I�u�W�F�N�g�z�u���� [SetObject.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _SETOBJECT_H_
#define _SETOBJECT_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
//�@�O���錾
//*****************************************************************************
class CSceneX;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_MATTEX	(20)

//*********************************************************************
//�v���C���[�N���X�̒�`
//*********************************************************************
class CSetObject : public CScene //�h���N���X
{
public:
	//���f���̎��
	typedef enum
	{
		MODELTYPE_BOX000 = 0,	//BOX
		MODELTYPE_MAX,			//�ő吔
	}MODELTYPE;

	CSetObject();
	~CSetObject();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static CSetObject *Create();
	D3DXVECTOR3 GetPos(void);

	static void LoadFile(char *pFileName);
	void UnLoadObj(void);
	static char *ReadLine(FILE *pFile, char *pDst);	//1�s�ǂݍ���
	static char *GetLineTop(char *pStr);			//�s�̐擪���擾
	static int  PopString(char *pStr, char *pDest);	//�s�̍Ō��؂�̂�


private:
	//�����o�ϐ�
public:
};

#endif