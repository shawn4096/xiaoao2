#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",HIR"山洞"NOR);
        set("long",@LONG
这是一个小小的山洞，血刀老祖的藏身之地。由於此地比较隐秘，
仇家很难寻到这来。洞底有一张供桌，上面供了什麽东西，你看不清。
壁上画了一些模糊不清的文字图案，也不知道是些什么。
LONG );
        set("exits",([
                "out" : __DIR__"shandong2",
                //"midao" :"/d/city/kedian",
        ]));
        set("objects", ([
                //"quest/menpaijob/xuedao/xuedao" :1,
                "/d/xuedao/npc/x_lama" :1,
                
        ]));
        setup();
        "/clone/board/xuedao_b"->foo();
		//replace_program(ROOM);
}

void init()
{
	object me = this_player();
	if (me->query_temp("szj/wait_baohu"))
	   message_vision("jiegejigege",me);
	//call_out("clone_shui", 1, me);
}
/*
void clone_shui(object me)
{
	object *ob,obj;
	int i,j;

	if( environment(me) != this_object()) return;

	j=0;
	ob = all_inventory(environment(me));
	for(i=0; i<sizeof(ob); i++) {
		if ( (!userp(ob[i])) && ((string)ob[i]->query("id")=="shui sheng"))
		j=1;
	}
	if (!j) {
		obj=new(__DIR__"npc/shuisheng.c");
		obj->move(environment(me));
		message_vision(HIC"只听得叮玲玲，叮玲玲一阵铃声，一骑马自西至东，沿着江边驰来。\n"NOR, me);
	}
}
*/