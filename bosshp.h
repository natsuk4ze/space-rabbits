//=============================================================================
//
// �G���� [enemy.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _BOSSHP_H_
#define _BOSSHP_H_


// �}�N����`
#define	NUM_BOSSHP				(2)			// �|���S����

#define TEXTURE_GAME_BOSSHP		_T("data/TEXTURE/playerhp001.png")	// �摜
#define TEXTURE_BOSSHP_SIZE_X	(15/2)		// �e�N�X�`���T�C�Y
#define TEXTURE_BOSSHP_SIZE_Y	(15/2)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_BOSSHP	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BOSSHP	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_BOSSHP			(TEXTURE_PATTERN_DIVIDE_X_BOSSHP*TEXTURE_PATTERN_DIVIDE_Y_BOSSHP)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BOSSHP			(2)	// �A�j���[�V�����̐؂� �ւ��J�E���g

#define BOSSHP_MAX						(60) // �G�̍ő吔

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

} BOSSHP;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBosshp(int type);
void UninitBosshp(void);
void UpdateBosshp(void);
void DrawBosshp(void);
void SetBosshp(D3DXVECTOR3 pos);

BOSSHP *GetBosshp(int no);


#endif



