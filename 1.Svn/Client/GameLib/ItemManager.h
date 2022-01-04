//Find
#include "ItemData.h"

///Add
#include "../UserInterface/Locale_inc.h"
#if defined(__BL_CHEST_DROP_INFO__)
#include <unordered_map>
#endif

//Find
		CItemData *		MakeItemData(DWORD dwIndex);

///Add
#if defined(__BL_CHEST_DROP_INFO__)
		struct SDropItemInfo
		{
			DWORD	dwDropVnum;
			int		iCount;
		};

		using							TChestDropItemInfoVec = std::vector<SDropItemInfo>;
		using							TChestDropItemInfoMap = std::unordered_map<DWORD, TChestDropItemInfoVec>;

		bool							LoadChestDropInfo(const char* c_szFileName);
		
		TChestDropItemInfoVec*			GetItemDropInfoVec(const DWORD dwVnum);
		TChestDropItemInfoVec*			GetBaseItemDropInfoVec(const DWORD dwVnum);
#endif

//Find
		CItemData * m_pSelectedItemData;

///Add
#if defined(__BL_CHEST_DROP_INFO__)
		TChestDropItemInfoMap m_ItemDropInfoMap;
		TChestDropItemInfoMap m_BaseItemDropInfoMap;
#endif
