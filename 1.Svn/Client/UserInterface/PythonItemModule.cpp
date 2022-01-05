//Find
void initItem()

///Add Above
#if defined(__BL_CHEST_DROP_INFO__)
#include "../EterBase/grid.h"

PyObject* itemHasDropInfo(PyObject* poSelf, PyObject* poArgs)
{
	int iItemIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iItemIndex))
		return Py_BadArgument();

	bool bMain;
	if (!PyTuple_GetBoolean(poArgs, 1, &bMain))
		return Py_BadArgument();

	CItemManager::TChestDropItemInfoVec* vDropInfo = nullptr;
	
	if (bMain)
		vDropInfo = CItemManager::Instance().GetItemDropInfoVec(iItemIndex);
	else
		vDropInfo = CItemManager::Instance().GetBaseItemDropInfoVec(iItemIndex);

	return Py_BuildValue("b", (vDropInfo && !vDropInfo->empty()));
}

static int __CreateDropPage(CItemManager::TChestDropItemInfoVec* vDropInfo, PyObject* poList)
{
	int iPageCount(0);
	CGrid grid(5, 8);
	
	if (vDropInfo && !vDropInfo->empty())
	{
		for (CItemManager::TChestDropItemInfoVec::const_iterator it = vDropInfo->begin(); it != vDropInfo->end(); ++it)
		{
			const CItemManager::SDropItemInfo& dwDropInfo = *it;

			CItemData* pItemData;
			if (!CItemManager::Instance().GetItemDataPointer(dwDropInfo.dwDropVnum, &pItemData))
				continue;

			const BYTE bItemSize = pItemData->GetSize();

			while (true)
			{
				const int iPos = grid.FindBlank(1, bItemSize);

				if (iPos >= 0)
				{
					grid.Put(iPos, 1, bItemSize);
					PyList_Append(poList, Py_BuildValue("iiii", iPageCount, iPos, dwDropInfo.dwDropVnum, dwDropInfo.iCount));
					break;
				}
				else
				{
					grid.Clear();
					++iPageCount;
				}
			}
		}
	}

	return iPageCount;
}

PyObject* itemGetDropInfo(PyObject* poSelf, PyObject* poArgs)
{
	int iItemIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iItemIndex))
		return Py_BadArgument();

	bool bMain;
	if (!PyTuple_GetBoolean(poArgs, 1, &bMain))
		return Py_BadArgument();

	PyObject* poList = PyList_New(0);
	CItemManager::TChestDropItemInfoVec* vDropInfo = nullptr;

	if (bMain)
		vDropInfo = CItemManager::Instance().GetItemDropInfoVec(iItemIndex);
	else
		vDropInfo = CItemManager::Instance().GetBaseItemDropInfoVec(iItemIndex);

	return Py_BuildValue("iO", __CreateDropPage(vDropInfo, poList), poList);
}
#endif

//Find
		{ "LoadItemTable",					itemLoadItemTable,						METH_VARARGS },

///Add
#if defined(__BL_CHEST_DROP_INFO__)
		{ "HasDropInfo",					itemHasDropInfo,						METH_VARARGS },
		{ "GetDropInfo",					itemGetDropInfo,						METH_VARARGS },
#endif