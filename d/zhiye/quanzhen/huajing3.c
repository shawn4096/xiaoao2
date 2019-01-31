inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "����С·");
        set("long", @LONG
�����Ǻ�ɽ�ϵ�С·������С·�������˹������޳���
�ģ�Ҳ��ֻ����ǰ�Ĳ�ҩ�˲ȶ��ˣ��ֳ�����һ��С·��������
�����˸���Ұ�����������󣬷��ͻ��㣬��Ϊ�ľ�������ɽ����
�Ļ��伫Ϊ׳�ۣ��ִ���������ɽ��Ұ���ƺ��������߼ʡ�
LONG);
        set("outdoors", "quanzhen");
        set("exits", ([
               // "north" : __DIR__"baihuagu",
				"northwest" : __DIR__"huajing2",               
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}

void init()
{
        object me=this_player();
		message_vision(MAG"\n�����������·������һƬ����֮�У�������Ƣ������泩��\n"NOR,me);
		//me->add_busy(1);
		
		call_out("happen1",1,me);
		return;
}

int do_find(string arg)
{
        object me = this_player();
		object bee;
		
        if(!arg ||arg != "�۷�") 
        	return notify_fail("�㵽���ҳ�����ʲô��\n");        

	    if (me->is_busy())
                return notify_fail("����æ���ء�\n");
		me->add_busy(2);
		if(random(10)>4)
		{
			message_vision(HIY"\n\n\n$N��Ȼ�������Ե�һ����Ϸ���һֻ�۷䣬���ڲ��ۡ�\n"NOR,me);
			if (!random(3))
			{				
				if (!objectp(present("yu feng",environment(me))))
				{
					bee=new("d/gumu/npc/bee");
					bee->move(this_object());
				}
				message_vision(HIG"\n\n\n$N�������"HIW"���"HIG"������֣��ս�һ��������ֻС������ƺ��������֣�\n"NOR,me);
				me->set_temp("baihuagu/find1",1);
				add_action("do_gensui","gensui");
				return 1;
			}else {
				message_vision(HIC"\n\n\n$N�������С�۷����������ڵĲ��ۣ�����æµ��\n"NOR,me);
				if (!objectp(bee=present("mi feng",environment(me))))
				{
					bee=new("d/gumu/npc/bee4");
					bee->move(environment(me));
				}
			}
			return 1;

		}else message_vision(HIY"\n\n\nС�۷����������˵ط����ˡ�\n"NOR,me);
		me->add_busy(1);
		return 1;
}

int happen1(object me)
{
	if (!me) return 0;

	message_vision(HIC"��Χ��Ϊ�ž���$N�����ڻ���ĺ����У��������붯��\n$N���˻ᣬ��Ȼ���������д������˵���������æ������ϸ���ơ�\n",me);
	message_vision(HIR"ԭ�����ڻ���ͣ�˼�ֻ"HIY"�۷䡣\n"NOR,me);
	add_action("do_find", "find");
	return 1;
}

int do_gensui(string arg)
{
	object me=this_player();
	if (!arg||arg!="���")
	{
		return notify_fail("��Ҫ����ʲô�ߣ�\n");
	}
	if (!me->query_temp("baihuagu/find1"))
	{
		return notify_fail("�������ֻС�۷����˺ܾã�������ȥ�����ֻص���ԭ�㡣\n");
	}
	message_vision(HIC"���������Ǻ��棬��СС��������Ͼ�Ȼ���֣����������Ļ�����Ϊ�ģ�\n"NOR,me);
	message_vision(HIC"\n��ס���еĺ��棬������ֻС���ȥ������������ô���£�\n"NOR,me);
	message_vision(HIG"\n����ת�����ǰ��Ȼ���ʣ�\n"NOR,me);
	me->delete_temp("baihuagu");
	me->move("d/quanzhen/baihuagu");
	
	return 1;
}
