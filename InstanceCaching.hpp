//Probably some better way to do this
//this is ready to skid from and dex will work!

case RLUA_TUSERDATA: {
	void* RobloxKey = RBX::touserdata(Roblox, Index);
	if(IsRobloxCached.find(RobloxKey) == IsRobloxCached.cend()) //not cached
		{
			void* LuaKey = lua_newuserdata(Lua, 8); //create dummy

			RBX::pushvalue(Roblox, Index);
			CachedUserDatas[LuaKey] = RBX::lref(Roblox, LUA_REGISTRYINDEX); //cache roblox userdata
							
			RBX::getmetatable(Roblox, Index);
			UnWrap(Roblox, Lua, -1);
			lua_setmetatable(Lua, -2);

			IsRobloxCached[RobloxKey] = 1; //add to map because now its cached
		}
	break;
}
      
      
case LUA_TUSERDATA: {
		const auto LuaIterator = CachedUserDatas.find(lua_touserdata(Lua, Index)); //check for dummy lua userdata
		if(LuaIterator != CachedUserDatas.cend()) { //if found
			RBX::rawgeti(Roblox, LUA_REGISTRYINDEX, LuaIterator->second); //table[key]; add key to stack.
		}
		else {
			RBX::newuserdata(Roblox, 0); //not found!
		}
}
 
