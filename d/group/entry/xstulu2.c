// Room: tulu3.c

inherit ROOM;

void create()
{
	set("short", "藏边土路");
	set("long", @LONG
这里已经进入了西藏，地势越来越高，空气稀薄，连呼吸都困难起来。
阳光分外刺眼，晒得人皮肤发紧，口干舌燥。遥遥往见远处一座城池，让
人不由得振奋精神，加快了脚步。
LONG
	);

	set("exits", ([
		"northeast" : "/d/xueshan/tulu1",
		"southwest" : "/d/xueshan/tulu3",
	]));
	set("group", 1);
	set("outdoors", "大雪山");
	setup();
}
