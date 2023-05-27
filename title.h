//=============================================================================
//
// �^�C�g����ʏ��� [title.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TITLE		_T("data/TEXTURE/title003.jpg")			// �ǂݍ��ރe�N�X�`���t�@�C����
//#define	TEXTURE_TITLE_LOGO	_T("data/TEXTURE/title_logo.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLE_POS_X			(0)								// �^�C�g���̕\���ʒu
#define	TITLE_POS_Y			(0)								// �^�C�g���̕\���ʒu
#define	TITLE_SIZE_X		(650)							// �^�C�g���̕�
#define	TITLE_SIZE_Y		(500)							// �^�C�g���̍���
//#define	TITLELOGO_POS_X		(160)							// �^�C�g�����S�̕\���ʒu
//#define	TITLELOGO_POS_Y		(200)							// �^�C�g�����S�̕\���ʒu
//#define	TITLELOGO_SIZE_X	(480)							// �^�C�g�����S�̕�
//#define	TITLELOGO_SIZE_Y	(80)							// �^�C�g�����S�̍���


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif
