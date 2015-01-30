#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__
#include "Stdafx.h"

class CSceneManager
{
private:

protected:
	std::map<int, CScene*> m_SceneMap;	//자료구조 map에 대해 설명필요
	std::vector<int> m_SceneVector;	//자료구조 queue에 대해 설명필요

public:
	CSceneManager(void);
	~CSceneManager(void);

	void PushScene(const int SceneNum, CScene * pScene);		//씬 추가 (이전 씬 저장)
	void ReplaceScene(const int SceneNum, CScene * pScene);	//씬 교체 (이전 씬 파괴)
	void ChangeTopSceneNum(const int SceneNum);
	void DestroyScene(const int SceneNum);	//해당 씬 파괴
	void AllDestroyScene();	//모든 씬 파괴
	CScene * GetScene(const int SceneNum);	//씬 리턴
	CScene * GetTopScene();	//최상위씬 리턴

	static CSceneManager* GetInstance();
	void Destroy();

protected:
	static CSceneManager* Singleton;

};

#endif