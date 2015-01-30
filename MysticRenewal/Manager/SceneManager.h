#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__
#include "Stdafx.h"

class CSceneManager
{
private:

protected:
	std::map<int, CScene*> m_SceneMap;	//�ڷᱸ�� map�� ���� �����ʿ�
	std::vector<int> m_SceneVector;	//�ڷᱸ�� queue�� ���� �����ʿ�

public:
	CSceneManager(void);
	~CSceneManager(void);

	void PushScene(const int SceneNum, CScene * pScene);		//�� �߰� (���� �� ����)
	void ReplaceScene(const int SceneNum, CScene * pScene);	//�� ��ü (���� �� �ı�)
	void ChangeTopSceneNum(const int SceneNum);
	void DestroyScene(const int SceneNum);	//�ش� �� �ı�
	void AllDestroyScene();	//��� �� �ı�
	CScene * GetScene(const int SceneNum);	//�� ����
	CScene * GetTopScene();	//�ֻ����� ����

	static CSceneManager* GetInstance();
	void Destroy();

protected:
	static CSceneManager* Singleton;

};

#endif