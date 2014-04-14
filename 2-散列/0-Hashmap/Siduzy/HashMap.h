#ifndef __HASH_MAP_H__
#define __HASH_MAP_H__

class HashMap
{
public:
	HashMap(int nMaxList = 1023);
	~HashMap();
	
	void Insert(const char *szKey, int nValue);
	int Find(const char * szKey);
	int Print();

private:
	HashMap(const HashMap&);
	HashMap& operator=(const HashMap&);

	bool CheckPrimer(int num);
	int PrimerLessThan(int num);

	unsigned BKDRHash(char *str);
	
private:
	int	m_nMaxList;

	struct HashList;
	HashList ** m_pList;
};
#endif
