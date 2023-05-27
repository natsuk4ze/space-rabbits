//=============================================================================
//
// �X�R�A���� [score.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

// �}�N����`
#define TEXTURE_GAME_SCORE00	_T("data/TEXTURE/number16x32.png")	// �T���v���p�摜
#define TEXTURE_SCORE00_SIZE_X	(16)	// �e�N�X�`���T�C�Y
#define TEXTURE_SCORE00_SIZE_Y	(32)	// ����
#define SCORE_POS_X			(530)		// �|���S���̏����ʒuX
#define SCORE_POS_Y			(20)		// ����
#define SCORE_MAX			(99999)		// �X�R�A�̍ő�l
#define SCORE_DIGIT			(5)			// ����

typedef struct	// �G�l�~�[�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	int						g_nScore;						// �X�R�A

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x

} SCORE;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitScore(int type);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void AddScore( int add );
SCORE *GetScore(int no);

#endif
