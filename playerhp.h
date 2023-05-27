//=============================================================================
//
// �G���� [enemy.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _PLAYERHP_H_
#define _PLAYERHP_H_


// �}�N����`
#define	NUM_PLAYERHP				(2)			// �|���S����

#define TEXTURE_GAME_PLAYERHP		_T("data/TEXTURE/playerhp001.png")	// �摜
#define TEXTURE_PLAYERHP_SIZE_X	(40/2)		// �e�N�X�`���T�C�Y
#define TEXTURE_PLAYERHP_SIZE_Y	(40/2)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_PLAYERHP	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_PLAYERHP	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_PLAYERHP			(TEXTURE_PATTERN_DIVIDE_X_PLAYERHP*TEXTURE_PATTERN_DIVIDE_Y_PLAYERHP)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_PLAYERHP			(2)	// �A�j���[�V�����̐؂� �ւ��J�E���g

#define PLAYERHP_MAX						(9) // �G�̍ő吔

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

} PLAYERHP;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayerhp(int type);
void UninitPlayerhp(void);
void UpdatePlayerhp(void);
void DrawPlayerhp(void);
PLAYERHP *GetPlayerhp(int no);


#endif

