// /d/mr/didao1.c
// by leontt 11/10/2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void close_gate();
int do_open(string arg);

void create() 
{
	set("short",BLU"�ص�"NOR);
	set("long", @long
������Ľ�����ҵĵ���ͨ������ϸ�����ܷ���ǽ����һ������(door)��
long);
	set("exits",([
		"west" : __DIR__"cufang",
		"east" : __DIR__"sleeproom",
		"south" : __DIR__"didao",
	]));
	set("item_desc", ([
		"door" : "����һ�ȷǳ�������ţ������и�Կ�׿ס�\n", 
	]));
	setup();
}

void init()
{ 
	add_action("do_open", "open");        
}

int do_open(string arg)
{
	object room;
	object ob;

        if(!arg) return 
                notify_fail("��Ҫ��ʲô��\n");
        
        if(arg != "door")
                return notify_fail("��Ҫ��ʲô��\n");
        
        if (query("exits/down"))
                return notify_fail("���Ѿ��ǿ����ˡ�\n");
                
        if (!(ob = present("mrkey", this_player())))
                return notify_fail("�㲻������Ҫ�����ɣ�\n");
                
        message_vision("$N�ó���Կ�ײ�����ŵ�Կ�׿��У���ȻԿ���Ѿ���Ҳ�ò������ˡ�\nֻ�� ��ৡ���һ���������Ͽ��ٵ�����\n",this_player());
        destruct(ob);

        if(!( room = find_object(__DIR__"didao2")) )
                room = load_object(__DIR__"didao2");
        if(objectp(room))
        {
                set("exits/down", __DIR__"didao2"); 
                room->set("exits/up", __FILE__);
                message("vision","��ৡ���һ���������������������˰��Ŵ��ˡ�\n",room);
                remove_call_out("close_gate");
                call_out("close_gate", 4);
        }
        return 1;
}

void close_gate()
{
        object room;

        if(!( room = find_object(__DIR__"didao2")) )
                room = load_object(__DIR__"didao2");
        if(objectp(room)){
                delete("exits/down");
                message("vision","˲�������֡�ž����һ�����ٵ�������������\n",this_object());
                message("vision","�����۷�ֱ��֪���Լ��Ѿ�����ȥ��\n" , this_object());
                room->delete("exits/up"); 
                message("vision","˲�������֡�ž����һ�����ٵ�����������\n",room);
                message("vision","����Լ�е���ǰ������һ����Ӱ�ڻζ������ų�һ���亹��\n",room );
        }
}