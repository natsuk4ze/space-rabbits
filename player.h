//=============================================================================
//
// �v���C���[���� [player.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_


// �}�N����`
#define	NUM_PLAYER		(2)					// �|���S����

#define TEXTURE_GAME_PLAYER	_T("data/TEXTURE/player0021.png")	// �摜
#define TEXTURE_PLAYER_SIZE_X	(80/2) // �e�N�X�`���T�C�Y
#define TEXTURE_PLAYER_SIZE_Y	(80/2) // ����

#define TEXTURE_PATTERN_DIVIDE_X	(1)//(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION				(8)//(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define PLAYER_MAX					(1) // �v���C���[�̍ő吔


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
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �v���C���[�̔��a
	float			BaseAngle;					// �v���C���[�̊p�x
	int             HP;
} PLAYER;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(int type);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(int no);


#endif
