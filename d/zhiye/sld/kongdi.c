// 空地.c
// 空地
#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short","林间空地");
	set("long",@long
这里是林间的一块空地，一走进这里就可以闻到一股浓浓的雄黄味扑鼻而
来。在空地上有两三间竹屋，屋子的墙壁、屋顶均由碗口大小的粗竹所编，看
来甚是坚定。屋后有道山溪垂山而下。
long);
	set("exits",([
	    "north" : __DIR__"treen2",
           "south" : __DIR__"trees2",
           "northup" : __DIR__"sanroad1",
           "enter" : __DIR__"lgxroom",
	]));
	set("objects",([
	    "kungfu/class/sld/maodongzhu" : 1,
        "kungfu/class/sld/dengbingchun" : 1,
		//"/d/sld/npc/blackjz" : 1,

	]));
	set("outdoors", "神龙岛");
	set("no_fight",1);
    set("valid_startroom", 1);
    setup();
     //   "/clone/board/quanzhen_b"->foo();
    //setup();
    call_other( "/clone/board/sld_b", "???" );
}
	    	
