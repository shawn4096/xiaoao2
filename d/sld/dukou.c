#include <ansi.h>

inherit ROOM;
#include <wanted.h>
int do_yell(string arg);
int go_zhy(object me);


void create()
{
        set("short", "渡口");
        set("long", @LONG
眼前就是辽阔无边的茫茫大海，海水波涛起伏，一浪接着一浪地朝岸边击
来，一眼望去，只见几羽海鸥在海面上飞翔，偶而也可见到远处有帆影掠过。
这里是神龙岛唯一可以停靠船舶的地方，这里的东西两边都是沙滩，往北则有
一个树林。
LONG
        );

        set("exits", ([
"northeast" : __DIR__"sande",
 "northwest" : __DIR__"sandw",
"north" : __DIR__"trees1",
        ]));
		  set("objects", ([
   __DIR__"npc/chuanfu" :1,
	]));
	set("no_fight",1);
        set("outdoors", "神龙岛");
        set("coor/x",490);
  set("coor/y",420);
   set("coor/z",0);
   setup();
        
}
void init()
{

	add_action("do_yell","yell");
}
//神龙岛快捷通道去中原

int do_yell(string arg)
{
	object me;
	me = this_player();
	if (me->query("family/family_name")!="神龙教") return notify_fail("只有神龙岛弟子才有专属往来中原的船！\n");

	if ( (arg == "神龙教独霸天下" || arg == "神龙教一统江湖") && me->query("family/family_name")=="神龙教" ) {
		if ( is_wanted(me) ) return 0;
		else return go_zhy(me);
	}

}
int go_zhy(object me)
{
	object hc;
	string str ="师兄";
		
	if(!objectp(hc=find_object("/d/huanghe/hc1")))
		hc=load_object("/d/huanghe/hc1");
		if(hc->query_temp("curstatus",1)=="run") {
			if(!objectp(hc=find_object("/d/huanghe/hc2")))
				hc=load_object("/d/huanghe/hc2");
				if(hc->query_temp("curstatus",1)=="run") {
					if(!objectp(hc=find_object("/d/huanghe/hc3")))
						hc=load_object("/d/huanghe/hc3");
						if(hc->query_temp("curstatus",1)=="run")
							return notify_fail("你喊了几声，却什么事也没有发生。\n");
                        }
                }
	if(me->query("gender")=="女性") str="师姐";

	message_vision(CYN"一位小童走过来对$N鞠了一躬说道：这位"+str+"要回神龙岛么？我在这里等你多时了。\n" NOR,me);
	message_vision(CYN"只见一艘大船已经驶进海口，$N慢慢走了进去。\n" NOR,me);	
	me->move(hc);
	hc->set_temp("curstatus","run");
	me->set_temp("gohuanghe",1);
	return 1;
}
