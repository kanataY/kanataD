#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

#define RANKING_MAX_COUNT 10

#define RETURN_X 10
#define RETURN_Y 550
#define RETURN_SIZE 20

//�I�u�W�F�N�g�F�����L���O
class CObjRanking : public CObj
{
public:
	CObjRanking() {};
	~CObjRanking() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	float StringSize(wchar_t *str);
	void DrawNumber(float dst_top, float dst_left, float dst_size, int num);
private:
	float m_return_size;	//�߂�Ƃ��̕����̃T�C�Y
};