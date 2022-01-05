#Find in def SetInventoryItem(self, slotIndex, window_type = player.INVENTORY):
		self.AddItemData(itemVnum, metinSlot, attrSlot)

#Add
		if app.__BL_CHEST_DROP_INFO__:
			self.AppendChestDropInfo(itemVnum)

#Find in def SetShopItem(self, slotIndex):
		self.AppendPrice(price)

#Add
		if app.__BL_CHEST_DROP_INFO__:
			self.AppendChestDropInfo(itemVnum)

#Find in def SetSafeBoxItem(self, slotIndex):
		self.AddItemData(itemVnum, metinSlot, attrSlot, safebox.GetItemFlags(slotIndex))

#Add
		if app.__BL_CHEST_DROP_INFO__:
			self.AppendChestDropInfo(itemVnum)

#Find in def SetMallItem(self, slotIndex):
		self.AddItemData(itemVnum, metinSlot, attrSlot)

#Add
		if app.__BL_CHEST_DROP_INFO__:
			self.AppendChestDropInfo(itemVnum)

#Find
	def __IsOldHair(self, itemVnum):
		return itemVnum > 73000 and itemVnum < 74000

#Add
	if app.__BL_CHEST_DROP_INFO__:
		def AppendChestDropInfo(self, itemVnum):
			hasinfo = item.HasDropInfo(itemVnum, True)
			if hasinfo:
				self.AppendSpace(5)
				self.AppendTextLine(localeInfo.CHEST_DROP_INFO, self.NORMAL_COLOR)
			
			hasinfo = item.HasDropInfo(itemVnum, False)
			if hasinfo:
				self.AppendSpace(5)
				self.AppendTextLine(localeInfo.CHEST_BASE_DROP_INFO, self.NORMAL_COLOR)