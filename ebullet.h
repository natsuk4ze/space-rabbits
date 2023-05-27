//=============================================================================
//
// �o���b�g���� [bullet.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _EBULLET_H_
#define _EBULLET_H_


// �}�N����`
#define	NUM_EBULLET				(2)			// �|���S����

#define TEXTURE_GAME_EBULLET		_T("data/TEXTURE/ebullet001.png")	// �摜
#define TEXTURE_EBULLET_SIZE_X	(30/2)		// �e�N�X�`���T�C�Y
#define TEXTURE_EBULLET_SIZE_Y	(120/2)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_EBULLET	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_EBULLET	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_EBULLET			(TEXTURE_PATTERN_DIVIDE_X_EBULLET*TEXTURE_PATTERN_DIVIDE_Y_EBULLET)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_EBULLET			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define EBULLET_MAX						(1) // �o���b�g�̍ő吔

#define EBULLET_SPEED			(2.5f)		// �o���b�g�̈ړ��X�s�[�h


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

} EBULLET;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEBullet(int type);
void UninitEBullet(void);
void UpdateEBullet(void);
void DrawEBullet(void);
void SetEBullet(D3DXVECTOR3 pos);
EBULLET *GetEBullet(int no);


#endif

