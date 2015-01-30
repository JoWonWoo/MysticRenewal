#include "../Stdafx.h"

CSceneManager* CSceneManager::Singleton = NULL;

CSceneManager::CSceneManager()
{
}
CSceneManager::~CSceneManager()
{
}

void CSceneManager::PushScene(const int SceneNum, CScene * pScene)
{
	std::map<int, CScene*>::iterator it;
	it = m_SceneMap.find(SceneNum);
	if (m_SceneMap.end() != it)
	{
		CCLog("SceneNum = %d 는 이미 존재 하는 씬입니다.", SceneNum);
		ChangeTopSceneNum(SceneNum);
		return;
	}
	m_SceneMap.insert(std::pair<int, CScene*>(SceneNum, pScene));
	m_SceneVector.push_back(SceneNum);
	//	m_SceneStack.push(SceneNum);
}
void CSceneManager::ReplaceScene(const int SceneNum, CScene * pScene)
{
//	std::map<int, CScene*>::iterator it;
	auto it = m_SceneMap.find(SceneNum);
	if (m_SceneMap.end() != it)
	{
		DestroyScene(m_SceneVector.front());
		//			m_SceneStack.top());
	}
	m_SceneMap.insert(std::pair<int, CScene*>(SceneNum, pScene));
	m_SceneVector.push_back(SceneNum);
	//	m_SceneStack.push(SceneNum);
}
void CSceneManager::DestroyScene(const int SceneNum)
{
//	std::map<int, CScene*>::iterator it;
	auto it = m_SceneMap.find(SceneNum);
	if (m_SceneMap.end() == it)
	{
		CCLog("SceneNum = %d 에 해당하는 씬이 없습니다.", SceneNum);
		return;
	}
	CScene* _pCScene = it->second;
	_pCScene->Destroy();
	_pCScene->RemoveFromParent();
	_pCScene = NULL;
	m_SceneMap.erase(m_SceneMap.find(SceneNum));

	//Stack에서 해당하는 넘버 빼기
	//std::vector<int>::iterator it_vector;
	auto it_vector = m_SceneVector.begin();
	while (it_vector != m_SceneVector.end())
	{
		if (*it_vector == SceneNum)
		{
			m_SceneVector.erase(it_vector);
			break;
		}
		it_vector++;
	}
}
void CSceneManager::AllDestroyScene()
{
	std::map<int, CScene*>::iterator it;
	it = m_SceneMap.begin();

	while (it != m_SceneMap.end())
	{
		CScene* _pCScene = it->second;
		if (_pCScene != NULL)
		{
			if (!_pCScene->RemoveFromParent())
			{
				_pCScene->RemoveAllChildren();
				delete _pCScene;
				_pCScene = NULL;
			}
		}

		it = m_SceneMap.erase(it);
		it = m_SceneMap.begin();
		//		it++;
	}
	if (m_SceneMap.empty() != NULL)
	{
		m_SceneMap.clear();
	}
	m_SceneVector.clear();
}

CScene * CSceneManager::GetScene(const int SceneNum)
{
	std::map<int, CScene*>::iterator it;
	it = m_SceneMap.find(SceneNum);
	if (m_SceneMap.end() == it)
		CCLog("SceneNum = %d 에 해당하는 씬이 없습니다.", SceneNum);

	CScene* _pCScene = it->second;
	return _pCScene;
}

CScene * CSceneManager::GetTopScene()
{
		return GetScene(m_SceneVector.back());
}

CSceneManager* CSceneManager::GetInstance()
{
	if (Singleton == NULL)
		Singleton = new CSceneManager;
	return Singleton;
}

void CSceneManager::ChangeTopSceneNum(const int SceneNum)
{
	std::map<int, CScene*>::iterator it;
	it = m_SceneMap.find(SceneNum);
	if (m_SceneMap.end() == it)
	{
		CCLog("SceneNum = %d 에 해당하는 씬이 없습니다.", SceneNum);
		return;
	}

	//해당하는 넘버 최상위로 올리기
	std::vector<int>::iterator it_vector;
	it_vector = m_SceneVector.begin();
	while (it_vector != m_SceneVector.end())
	{
		if (*it_vector == SceneNum)
		{
			int Temp = *it_vector;
			m_SceneVector.erase(it_vector);
			m_SceneVector.push_back(Temp);
			break;
		}
		it_vector++;
	}

}

void CSceneManager::Destroy()
{
	if (Singleton != NULL)
		delete Singleton;
}
