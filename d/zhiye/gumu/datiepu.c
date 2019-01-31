inherit ROOM;
void create()
{
	set("short", "打铁铺");
	set("long", @LONG
这是一家终南山下简陋的打铁铺，铺中炉火把四周照得一片通红，温度
甚高，你一走进去就感到浑身火热。墙角堆满了已完工和未完工的菜刀、铁
锤、铁棍、匕首、盔甲等物。一位铁匠挥舞着铁锤，正专心致志地在打铁。
LONG
	);
        set("objects",([
                __DIR__"npc/tiejiang" : 1,
        ]));
		set("exits", ([
			"north" : __DIR__"jishi",
		]));

	set("coor/x",150);
  set("coor/y",-220);
   set("coor/z",0);
   set("incity",1);
	setup();
}

