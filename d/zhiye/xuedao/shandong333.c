#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",HIR"ɽ��"NOR);
        set("long",@LONG
����һ��СС��ɽ����Ѫ������Ĳ���֮�ء���춴˵رȽ����أ�
��Һ���Ѱ��������������һ�Ź��������湩��ʲ�ᶫ�����㿴���塣
���ϻ���һЩģ�����������ͼ����Ҳ��֪����Щʲô��
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
		message_vision(HIC"ֻ���ö����ᣬ������һ��������һ�����������������Ž��߳�����\n"NOR, me);
	}
}
*/