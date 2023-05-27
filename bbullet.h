//=============================================================================
//
// �o���b�g���� [bullet.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _BBULLET_H_
#define _BBULLET_H_


// �}�N����`
#define	NUM_BBULLET				(2)			// �|���S����

#define TEXTURE_GAME_BBULLET		_T("data/TEXTURE/ninjin004.png")	// �摜
#define TEXTURE_BBULLET_SIZE_X	(50/2)		// �e�N�X�`���T�C�Y
#define TEXTURE_BBULLET_SIZE_Y	(50/2)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_BBULLET	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BBULLET	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_BBULLET			(TEXTURE_PATTERN_DIVIDE_X_BBULLET*TEXTURE_PATTERN_DIVIDE_Y_BBULLET)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BBULLET			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define BBULLET_MAX						(6) // �o���b�g�̍ő吔

#define BBULLET_SPEED			(2.0f)		// �o���b�g�̈ړ��X�s�[�h


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

} BBULLET;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBBullet(int type);
void UninitBBullet(void);
void UpdateBBullet(void);
void DrawBBullet(void);
void SetBBullet(D3DXVECTOR3 pos);
BBULLET *GetBBullet(int no);


#endif


