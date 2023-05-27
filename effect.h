//=============================================================================
//
// �o���b�g���� [bullet.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_


// �}�N����`
#define	NUM_EFFECT				(2)			// �|���S����

#define TEXTURE_GAME_EFFECT		_T("data/TEXTURE/deto.png")	// �摜
#define TEXTURE_EFFECT_SIZE_X	(150/2)		// �e�N�X�`���T�C�Y
#define TEXTURE_EFFECT_SIZE_Y	(150/2)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_EFFECT	(8)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_EFFECT	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_EFFECT			(TEXTURE_PATTERN_DIVIDE_X_EFFECT*TEXTURE_PATTERN_DIVIDE_Y_EFFECT)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_EFFECT			(3)	// �A�j���[�V�����̐؂�ւ��J�E���g
//#define TIME_END_EFFECT			(4)	// �A�j���[�V�������I���܂ł̃J�E���g

#define EFFECT_MAX						(20) // �o���b�g�̍ő吔



//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �o���b�g�\����
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

} EFFECT;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEffect(int type);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos);
EFFECT *GetEffect(int no);


#endif

