// yaopu6.c
// 药圃
inherit ROOM;
void create()
{
	set("short","药圃");
	set("long",@long
这里是神龙岛的药圃，远远望去，药圃形似八卦图排列，每块
药圃旁边插了一个牌子，上面写了“坎”字样，这里靠海，灵气充沛
适合奇珍药材成长。
long);
	set("exits",([
	    "east" : __DIR__"yaopu1",
            "west" : __DIR__"yaopu7",
	    "north" : __DIR__"yaopu5",
]));
	set("no_clean_up",1);
	set("can_zhong",1);
	set("8type","坎");
	set("outdoors", "神龙岛");
	setup();
}
	    	
