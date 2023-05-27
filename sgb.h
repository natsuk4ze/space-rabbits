//=============================================================================
//
// �G���� [object01.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _SGB_H_
#define _SGB_H_


// �}�N����`
#define	NUM_SGB				(2)			// �|���S����

#define TEXTURE_GAME_SGB		_T("data/TEXTURE/object001.png")	// �摜
#define TEXTURE_SGB_SIZE_X	(50/2)		// �e�N�X�`���T�C�Y
#define TEXTURE_SGB_SIZE_Y	(50/2)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_SGB	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_SGB	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_SGB			(TEXTURE_PATTERN_DIVIDE_X_SGB*TEXTURE_PATTERN_DIVIDE_Y_SGB)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_SGB			(1)	// �A�j���[�V�����̐؂� �ւ��J�E���g

#define SGB_MAX						(8) // �G�̍ő吔

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �G�l�~�[�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x

} SGB;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSGB(int type);
void UninitSGB(void);
void UpdateSGB(void);
void DrawSGB(void);
SGB *GetSGB(int no);


#endif

