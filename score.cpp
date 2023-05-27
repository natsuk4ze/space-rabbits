//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "main.h"
#include "score.h"
#include <stdio.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexScore(void);
void SetTextureScore(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureScore = NULL;		// �e�N�X�`���ւ̃|���S��
VERTEX_2D				g_vertexWkScore[SCORE_DIGIT][NUM_VERTEX];	// ���_���i�[���[�N
SCORE					scoreWk[SCORE_MAX];				// �G�l�~�[�\����

D3DXVECTOR3				g_posScore;						// �|���S���̈ړ���


//=============================================================================
// ����������
//=============================================================================
HRESULT InitScore(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SCORE *score = &scoreWk[0];

	
	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_SCORE00,				// �t�@�C���̖��O
			&g_pD3DTextureScore);				// �ǂݍ��ރ������̃|�C���^
	}

	g_posScore = D3DXVECTOR3((float)SCORE_POS_X, (float)SCORE_POS_Y, 0.0f);
	score->g_nScore = 0;

	// ���_���̍쐬
	MakeVertexScore();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	if( g_pD3DTextureScore != NULL )
	{	// �e�N�X�`���̊J��
		g_pD3DTextureScore->Release();
		g_pD3DTextureScore = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{
	// ���t���[�����s����鏈�����L�q����


	SetTextureScore();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int i;

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture( 0, g_pD3DTextureScore );

	// �X�R�A
	for( i = 0; i < SCORE_DIGIT; i++ )
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkScore[i], sizeof(VERTEX_2D));
	}

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexScore(void)
{
	int i;
	float habaX = 16.0f;	// �����̉���
	
	// ��������������
	for( i = 0; i < SCORE_DIGIT; i++ )
	{
		// ���_���W�̐ݒ�
		g_vertexWkScore[i][0].vtx.x = -habaX * i + g_posScore.x;
		g_vertexWkScore[i][0].vtx.y = g_posScore.y;
		g_vertexWkScore[i][0].vtx.z = 0.0f;
		g_vertexWkScore[i][1].vtx.x = -habaX * i + g_posScore.x + TEXTURE_SCORE00_SIZE_X;
		g_vertexWkScore[i][1].vtx.y = g_posScore.y;
		g_vertexWkScore[i][1].vtx.z = 0.0f;
		g_vertexWkScore[i][2].vtx.x = -habaX * i + g_posScore.x;
		g_vertexWkScore[i][2].vtx.y = g_posScore.y + TEXTURE_SCORE00_SIZE_Y;
		g_vertexWkScore[i][2].vtx.z = 0.0f;
		g_vertexWkScore[i][3].vtx.x = -habaX * i + g_posScore.x + TEXTURE_SCORE00_SIZE_X;
		g_vertexWkScore[i][3].vtx.y = g_posScore.y + TEXTURE_SCORE00_SIZE_Y;
		g_vertexWkScore[i][3].vtx.z = 0.0f;

		// rhw�̐ݒ�
		g_vertexWkScore[i][0].rhw =
		g_vertexWkScore[i][1].rhw =
		g_vertexWkScore[i][2].rhw =
		g_vertexWkScore[i][3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		g_vertexWkScore[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkScore[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkScore[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkScore[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		g_vertexWkScore[i][0].tex = D3DXVECTOR2( 0.0f, 0.0f );
		g_vertexWkScore[i][1].tex = D3DXVECTOR2( 1.0f, 0.0f );
		g_vertexWkScore[i][2].tex = D3DXVECTOR2( 0.0f, 1.0f );
		g_vertexWkScore[i][3].tex = D3DXVECTOR2( 1.0f, 1.0f );
	}

	return S_OK;
}
//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetTextureScore(void)
{
	SCORE *score = &scoreWk[0];

	int i;
	int number = score->g_nScore;
	
	for( i = 0; i < SCORE_DIGIT; i++ )
	{
		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(number % 10);
		g_vertexWkScore[i][0].tex = D3DXVECTOR2( 0.1f * x, 0.0f );
		g_vertexWkScore[i][1].tex = D3DXVECTOR2( 0.1f * ( x + 1 ),	 0.0f );
		g_vertexWkScore[i][2].tex = D3DXVECTOR2( 0.1f * x, 1.0f );
		g_vertexWkScore[i][3].tex = D3DXVECTOR2( 0.1f * ( x + 1 ),	 1.0f );
		number /= 10;
	}

}
//=============================================================================
// HP�f�[�^���Z�b�g����
// ����:add :�ǉ�����_���B�}�C�i�X���\�A�������ȂǂɁB
//=============================================================================
void AddScore( int add )
{
	SCORE *score = &scoreWk[0];

	score->g_nScore += add;

	if( score->g_nScore > SCORE_MAX )
	{
		score->g_nScore = SCORE_MAX;
	}
	else if( score->g_nScore < 0 )
	{
		score->g_nScore = 0;
	}

}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
SCORE *GetScore(int no)
{
	return(&scoreWk[no]);
}