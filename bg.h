//=============================================================================
//
// �w�i���� [bg.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

// �}�N����`
#define TEXTURE_GAME_BG00		_T("data/TEXTURE/bg003.jpg")	// �T���v���p�摜
#define BG00_SIZE_X			(800)	// �e�N�X�`���T�C�Y
#define BG00_SIZE_Y			(600)	// ����
#define BG00_POS_X			(0)		// �|���S���̏����ʒuX(����)
#define BG00_POS_Y			(0)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_BG	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BG	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_BG			(TEXTURE_PATTERN_DIVIDE_X_BG*TEXTURE_PATTERN_DIVIDE_Y_BG)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BG			(8)	// �A�j���[�V�����̐؂�ւ��J�E���g
#define BG_MAX					(1) // �v���C���[�̍ő吔

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �v���C���[�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	int				HP;
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �v���C���[�̔��a
	float			BaseAngle;					// �v���C���[�̊p�x

} BG;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBG(int type);
void UninitBG(void);
void UpdateBG(void);
void DrawBG(void);
BG *GetBG(int no);

#endif
