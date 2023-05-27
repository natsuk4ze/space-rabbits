//=============================================================================
//
// �G���� [enemy.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_


// �}�N����`
#define	NUM_BOSS				(2)			// �|���S����

#define TEXTURE_GAME_BOSS		_T("data/TEXTURE/boss001.png")	// �摜
#define TEXTURE_BOSS_SIZE_X	(250/2)		// �e�N�X�`���T�C�Y
#define TEXTURE_BOSS_SIZE_Y	(200/2)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_BOSS	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BOSS	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_BOSS			(TEXTURE_PATTERN_DIVIDE_X_BOSS*TEXTURE_PATTERN_DIVIDE_Y_BOSS)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BOSS			(8)	// �A�j���[�V�����̐؂� �ւ��J�E���g

#define BOSS_MAX						(1) // �G�̍ő吔

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
	int				HP;

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x

} BOSS;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBoss(int type);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);
BOSS *GetBoss(int no);


#endif

