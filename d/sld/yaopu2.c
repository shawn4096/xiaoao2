// yaopu2.c
// 药圃
inherit ROOM;
void create()
{
	set("short","药圃");
	set("long",@long
这里是神龙岛的药圃，远远望去，药圃形似八卦图排列，每块
药圃旁边插了一个牌子，上面写了“兑”字样，这里靠海，灵气充沛
适合奇珍药材成长。
long);
	set("exits",([
	    "west" : __DIR__"yaopu5",
            "north" : __DIR__"yaopu3",
            "south" : __DIR__"yaopu1",
]));
	set("no_clean_up",1);
	set("can_zhong",1);
	set("8type","兑");
	set("outdoors", "神龙岛");
	setup();
}
	    	
