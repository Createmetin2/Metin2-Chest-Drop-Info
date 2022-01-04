///Add
#if defined(__BL_CHEST_DROP_INFO__)

//#define __CHEST_DROP_USELZO__
#if defined(__CHEST_DROP_USELZO__)
static DWORD s_adwChestItemInfoKey[4] =
{
	173217,
	72619434,
	408587239,
	27973291
};
#endif

bool CItemManager::LoadChestDropInfo(const char* c_szFileName)
{
	if (m_ItemDropInfoMap.empty() == false)
		return true;

	CMappedFile file;
	LPCVOID pvData;

	if (!CEterPackManager::Instance().Get(file, c_szFileName, &pvData))
		return false;

#if defined(__CHEST_DROP_USELZO__)
	DWORD dwElements;
	file.Read(&dwElements, sizeof(DWORD));

	DWORD dwDataSize;
	file.Read(&dwDataSize, sizeof(DWORD));

	auto pbData = std::make_unique<BYTE[]>(dwDataSize);
	file.Read(pbData.get(), dwDataSize);

	CLZObject zObj;
	if (!CLZO::Instance().Decompress(zObj, pbData.get(), s_adwChestItemInfoKey))
		return false;

	struct SLZODropData { DWORD dwVnum; DWORD dwDropVnum; int iCount; };
	const SLZODropData* arrDropInfo = reinterpret_cast<const SLZODropData*>(zObj.GetBuffer());

	for (DWORD i = 0; i < dwElements; i++)
	{
		const SLZODropData& data = *(arrDropInfo + i);
		m_ItemDropInfoMap[data.dwVnum].push_back({ data.dwDropVnum, data.iCount });
	}
#else
	size_t mapSize = 0;
	file.Read(&mapSize, sizeof(mapSize));

	for (size_t i = 0; i < mapSize; i++)
	{
		DWORD dwItemVnum = 0;
		file.Read(&dwItemVnum, sizeof(dwItemVnum));

		size_t vecSize = 0;
		file.Read(&vecSize, sizeof(vecSize));

		TChestDropItemInfoVec& vecDrop = m_ItemDropInfoMap[dwItemVnum];
		vecDrop.reserve(vecSize);

		for (size_t j = 0; j < vecSize; j++)
		{
			DWORD dwDropVnum = 0;
			file.Read(&dwDropVnum, sizeof(dwDropVnum));

			int iCount = 0;
			file.Read(&iCount, sizeof(iCount));

			vecDrop.push_back({ dwDropVnum, iCount });
		}
	}
#endif

	for (CItemManager::TChestDropItemInfoMap::iterator it = m_ItemDropInfoMap.begin(); it != m_ItemDropInfoMap.end(); ++it)
	{
		CItemManager::TChestDropItemInfoVec& vecDrop = it->second;

		std::sort(vecDrop.begin(), vecDrop.end(),
			[](const CItemManager::SDropItemInfo& a, const CItemManager::SDropItemInfo& b)
			{
				CItemData* pItemData[2];
				if (CItemManager::Instance().GetItemDataPointer(a.dwDropVnum, &pItemData[0]) && CItemManager::Instance().GetItemDataPointer(b.dwDropVnum, &pItemData[1]))
					return pItemData[0]->GetSize() < pItemData[1]->GetSize();

				return false;
			});
	}

	return true;
}

CItemManager::TChestDropItemInfoVec* CItemManager::GetItemDropInfoVec(const DWORD dwVnum)
{
	//Items which in this chest.

	CItemManager::TChestDropItemInfoMap::iterator it = m_ItemDropInfoMap.find(dwVnum);
	if (it != m_ItemDropInfoMap.end())
		return &(it->second);

	return nullptr;
}

CItemManager::TChestDropItemInfoVec* CItemManager::GetBaseItemDropInfoVec(const DWORD dwVnum)
{
	//Chests which contains this item.

	CItemManager::TChestDropItemInfoMap::iterator it = m_BaseItemDropInfoMap.find(dwVnum);
	if (it != m_BaseItemDropInfoMap.end())
		return &(it->second);

	CItemManager::TChestDropItemInfoVec tempVec;
	for (CItemManager::TChestDropItemInfoMap::const_iterator it = m_ItemDropInfoMap.begin(); it != m_ItemDropInfoMap.end(); ++it)
	{
		const CItemManager::TChestDropItemInfoVec& info = it->second;
		CItemManager::TChestDropItemInfoVec::const_iterator itFind = std::find_if(info.begin(), info.end(),
			[&](const CItemManager::SDropItemInfo& data) { return data.dwDropVnum == dwVnum; });

		if (itFind != info.end())
			tempVec.push_back({ it->first, 1 });
	}

	if (tempVec.empty())
		return nullptr;

	CItemManager::TChestDropItemInfoVec& retVec = m_BaseItemDropInfoMap[dwVnum];
	retVec = std::move(tempVec);
	return &retVec;
}
#endif