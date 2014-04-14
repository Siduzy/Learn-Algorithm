#include "HashMap.h"
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

struct HashMap::HashList
{
	string strKey;
	int nValue;
	HashList * pLink;
	
	HashList(){};
	HashList(const char *szKey, int nValue, HashList * pLink)
		: strKey(szKey)
		, nValue(nValue)
		, pLink(pLink)
	{}

};

bool HashMap::CheckPrimer(int num)
{
	for (int i = 2; i * i < num; ++i)
	{
		if (num % i == 0)
		{
			return false;
		}
	}
	return true;
}

int HashMap::PrimerLessThan(int num)
{
	for (int i = num; i > 2; --i)
	{
		if (CheckPrimer(i))
		{
			return i;
		}
	}
	return num;
}

unsigned HashMap::BKDRHash(char *str)
{
	unsigned int seed=131;// 31 131 1313 13131 131313 etc..    
    unsigned int hash=0;

    while(*str)
    { 
        hash=hash*seed+(*str++);
    }
    
    return(hash & 0x7FFFFFFF);
}

HashMap::~HashMap()
{
}

HashMap::HashMap(int nMaxList)
	: m_nMaxList(0)
	, m_pList(NULL)
{
	if (!CheckPrimer(nMaxList))
	{
		nMaxList = PrimerLessThan(nMaxList);
	}

	m_nMaxList = nMaxList;
	m_pList = new HashList * [m_nMaxList];
	if (m_pList == NULL)
	{
		throw "No enough memory!";
	}

	memset(m_pList, 0, sizeof(HashList *) * m_nMaxList);
}

void HashMap::Insert(const char *szKey, int nValue)
{
	unsigned nIndex = BKDRHash((char*)szKey)%m_nMaxList;
	HashList * pDummy = new HashList();
	pDummy->pLink = m_pList[nIndex];

	HashList * pIdx  = pDummy;
	while (true)
	{
		if (pIdx->pLink == NULL)
		{
			HashList * pNew = new HashList(szKey, nValue, NULL);
			pIdx->pLink = pNew;
			break;
		}
		int nCmp = strcmp(pIdx->pLink->strKey.c_str(), szKey);
		if (nCmp == 0)
		{
			pIdx->pLink->nValue++;
			break;
		}
		else if (nCmp > 0)
		{
			HashList * pNew = new HashList(szKey, nValue, pIdx->pLink);
			pIdx->pLink  = pNew;
			break;
		}
		else
		{
			pIdx = pIdx->pLink;	
		}
	}
	m_pList[nIndex] = pDummy->pLink;
	delete pDummy;
}

int HashMap::Find(const char *szKey)
{
	unsigned nIndex = BKDRHash((char *)szKey)%m_nMaxList;

	HashList * pIdx = m_pList[nIndex];
	while (pIdx != NULL)
	{
		if (strcmp(pIdx->strKey.c_str(), szKey) == 0)
		{
			return pIdx->nValue;	
		}
		pIdx = pIdx->pLink;
	}
	return 0;
}

int HashMap::Print()
{
	int cnt = 0;
	for (int i = 0; i < m_nMaxList; ++i)
	{
		HashList * pIdx = m_pList[i];
		while (pIdx != NULL)
		{
			++cnt;
			cout<< pIdx->strKey << "-" 
				<< pIdx->nValue << endl;
			pIdx = pIdx->pLink;
		}
	}
	return cnt;
}
