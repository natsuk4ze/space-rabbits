//=============================================================================
//
// �G���� [enemy.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_


// �}�N����`
#define	NUM_ENEMY				(2)			// �|���S����

#define TEXTURE_GAME_ENEMY		_T("data/TEXTURE/enemy001.png")	// �摜
#define TEXTURE_ENEMY_SIZE_X	(90/2)		// �e�N�X�`���T�C�Y
#define TEXTURE_ENEMY_SIZE_Y	(90/2)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_ENEMY	(4)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMY	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_ENEMY			(TEXTURE_PATTERN_DIVIDE_X_ENEMY*TEXTURE_PATTERN_DIVIDE_Y_ENEMY)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_ENEMY			(8)	// �A�j���[�V�����̐؂� �ւ��J�E���g

#define ENEMY_MAX						(2) // �G�̍ő吔

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
	int             HP;
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x

} ENEMY;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy(int type);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
ENEMY *GetEnemy(int no);


#endif
