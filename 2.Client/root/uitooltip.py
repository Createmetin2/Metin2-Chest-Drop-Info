#Find in def AddItemData(self, itemVnum, metinSlot, attrSlot = 0, flags = 0, unbindTime = 0):
#At end of the function
			elif item.LIMIT_TIMER_BASED_ON_WEAR == limitType:
				self.AppendTimerBasedOnWearLastTime(metinSlot)
				#dbg.TraceError("1) REAL_TIME flag On ")		
		
		self.ShowToolTip()

#Change
			elif item.LIMIT_TIMER_BASED_ON_WEAR == limitType:
				self.AppendTimerBasedOnWearLastTime(metinSlot)
				#dbg.TraceError("1) REAL_TIME flag On ")

		if app.__BL_CHEST_DROP_INFO__:
			self.AppendChestDropInfo(itemVnum)
		
		self.ShowToolTip()

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