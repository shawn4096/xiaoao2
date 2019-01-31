// lgxys.c
// 陆高轩家药室

inherit ROOM;
void create()
{
	set("short","炼药室");
	set("long",@long
这里是神龙岛的炼药室，由门中护法陆高轩负责，一进门，就闻到很浓
的草药味，地上摆放了一个巨大的炼药炉，有不少弟子在此忙碌，有些药师
蹲在地上帮忙分拣药草。
long);
	set("exits",([
	    "east" : __DIR__"lgxroom",
	]));
	set("objects",([
		__DIR__"npc/obj/yaolu" : 1,
		__DIR__"npc/yunsumei" : 1,
	]));
	//set("yaozhong",15);
     setup();
}
