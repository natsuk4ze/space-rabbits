//=============================================================================
//
// ���U���g��ʏ��� [result.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _RESULT2_H_
#define _RESULT2_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_RESULT2      _T("data/TEXTURE/bg005.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RESULT2_LOGO	_T("data/TEXTURE/resultlogo003.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT2_POS_X			(0)							// �^�C�g���̕\���ʒu
#define	RESULT2_POS_Y			(0)							// �^�C�g���̕\���ʒu
#define	RESULT2_SIZE_X			(800)						// �^�C�g���̕�
#define	RESULT2_SIZE_Y			(600)						// �^�C�g���̍���
#define	RESULT2LOGO_POS_X		(70)						// �^�C�g�����S�̕\���ʒu
#define	RESULT2LOGO_POS_Y		(100)						// �^�C�g�����S�̕\���ʒu
#define	RESULT2LOGO_SIZE_X		(480)						// �^�C�g�����S�̕�
#define	RESULT2LOGO_SIZE_Y		(300)						// �^�C�g�����S�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitResult2(void);
void UninitResult2(void);
void UpdateResult2(void);
void DrawResult2(void);

#endif

