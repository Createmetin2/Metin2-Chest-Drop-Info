///Add
#if defined(__BL_CHEST_DROP_INFO__)
static DWORD s_adwChestItemInfoKey[4] =
{
	173217,
	72619434,
	408587239,
	27973291
};

bool CItemManager::LoadChestDropInfo(const char* c_szFileName)
{
	if (m_ItemDropInfoMap.empty() == false)
		return true;

	CMappedFile file;
	LPCVOID pvData;

	if (!CEterPackManager::Instance().Get(file, c_szFileName, &pvData))
		return false;

	DWORD dwElements; 
	file.Read(&dwElements, sizeof(DWORD));

	DWORD dwDataSize;;
	file.Read(&dwDataSize, sizeof(DWORD));

	auto pbData = std::make_unique<BYTE[]>(dwDataSize);
	file.Read(pbData.get(), dwDataSize);

	CLZObject zObj;
	if (!CLZO::Instance().Decompress(zObj, pbData.get(), s_adwChestItemInfoKey))
		return false;

	DWORD* arrDropInfo = reinterpret_cast<DWORD*>(zObj.GetBuffer());

	for (DWORD i = 0; i < dwElements; i++)
	{
		const DWORD dwItemVnum = *(arrDropInfo++);
		const DWORD dwDropVnum = *(arrDropInfo++);
		m_ItemDropInfoMap[dwItemVnum].push_back(dwDropVnum);
	}
	
	for (TChestDropItemInfoMap::iterator it = m_ItemDropInfoMap.begin(); it != m_ItemDropInfoMap.end(); ++it)
	{
		TChestDropItemInfoVec& vecDrop = it->second;
		
		std::sort(vecDrop.begin(), vecDrop.end(),
			[this](TChestDropItemInfoVec::value_type const a, TChestDropItemInfoVec::value_type const b)
			{
				CItemData* pItemData[2];
				if (GetItemDataPointer(a, &pItemData[0]) && GetItemDataPointer(b, &pItemData[1]))
					return pItemData[0]->GetSize() < pItemData[1]->GetSize();

				return false;
			});
	}

	return true;
}

const CItemManager::TChestDropItemInfoVec* CItemManager::GetItemDropInfoVec(const DWORD dwVnum) const
{
	TChestDropItemInfoMap::const_iterator it = m_ItemDropInfoMap.find(dwVnum);
	if (it != m_ItemDropInfoMap.end())
	{
		const TChestDropItemInfoVec* pVec = &(it->second);
		return pVec;
	}

	return nullptr;
}
#endif