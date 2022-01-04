#Find
	def __UseItem(self, slotIndex):
		ItemVNum = player.GetItemIndex(slotIndex)
		item.SelectItem(ItemVNum)

#Add
		if app.__BL_CHEST_DROP_INFO__:
			if app.IsPressed(app.DIK_LCONTROL):
				isMain = not app.IsPressed(app.DIK_LSHIFT)
				if item.HasDropInfo(ItemVNum, isMain) and self.interface:
					self.interface.OpenChestDropWindow(ItemVNum, isMain)
				return