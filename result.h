//=============================================================================
//
// ���U���g��ʏ��� [result.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_RESULT      _T("data/TEXTURE/result_001.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RESULT_LOGO	_T("data/TEXTURE/result_logo002.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_POS_X			(0)							// �^�C�g���̕\���ʒu
#define	RESULT_POS_Y			(0)							// �^�C�g���̕\���ʒu
#define	RESULT_SIZE_X			(800)						// �^�C�g���̕�
#define	RESULT_SIZE_Y			(600)						// �^�C�g���̍���
#define	RESULTLOGO_POS_X		(70)						// �^�C�g�����S�̕\���ʒu
#define	RESULTLOGO_POS_Y		(100)						// �^�C�g�����S�̕\���ʒu
#define	RESULTLOGO_SIZE_X		(500)						// �^�C�g�����S�̕�
#define	RESULTLOGO_SIZE_Y		(300)						// �^�C�g�����S�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

#endif
