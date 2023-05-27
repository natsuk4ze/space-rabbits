//=============================================================================
//
// �G���� [enemy.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _ENEMYHP_H_
#define _ENEMYHP_H_


// �}�N����`
#define	NUM_ENEMYHP				(2)			// �|���S����

#define TEXTURE_GAME_ENEMYHP		_T("data/TEXTURE/playerhp001.png")	// �摜
#define TEXTURE_ENEMYHP_SIZE_X	(15/2)		// �e�N�X�`���T�C�Y
#define TEXTURE_ENEMYHP_SIZE_Y	(15/2)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_ENEMYHP	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMYHP	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_ENEMYHP			(TEXTURE_PATTERN_DIVIDE_X_ENEMYHP*TEXTURE_PATTERN_DIVIDE_Y_ENEMYHP)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_ENEMYHP			(2)	// �A�j���[�V�����̐؂� �ւ��J�E���g

#define ENEMYHP_MAX						(8) // �G�̍ő吔

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

} ENEMYHP;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemyhp(int type);
void UninitEnemyhp(void);
void UpdateEnemyhp(void);
void DrawEnemyhp(void);
void SetEnemyhp(D3DXVECTOR3 pos);

ENEMYHP *GetEnemyhp(int no);


#endif


