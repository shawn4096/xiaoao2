// sanpo6.c
// 山坡6
inherit ROOM;
void create()
{
	set("short","山坡");
	set("long",@long
山路到此处嘎然而止，不在向上延伸。此处山坡的中央是一大块空地，
有几个身穿白色劲装的人在练武，在空地边上有几间竹屋，其中中间一间
的门匾上写着“白龙门”三个字，这里的南面都是峭壁，西面有条路，往下
而去，北面则有条小路，通往总坛，西面是弟子们家属生活区。
long);
	set("exits",([
	    "north" : __DIR__"sanroada",
            "westdown" : __DIR__"sanroad8",
          "enter" : __DIR__"blm",
			"east"  : __DIR__"xiaolu1",
]));
	set("outdoors", "神龙岛");
        set("coor/x",520);
  set("coor/y",420);
   set("coor/z",60);
   setup();
}
	    	
