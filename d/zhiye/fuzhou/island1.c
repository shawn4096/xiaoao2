// island1.c С��
// Modify by Looklove 2k/5/18
// 2001.9.27 update

#include <ansi.h>
inherit ROOM;
int do_fail(object me);
int do_baohu(string arg);
void create()
{
        set("short",YEL"С��"NOR);
        set("long", @LONG
����һ�����½��Զ��С���������м�ǳǳ�ĺ�Ͽ���������������½��
����ۡ����������ɳ̲�ϲ����������ı��ǣ�һЩС��СϺ���ڰ��ߵĺ�ˮ
���������ڵ�������ȥ����ˮһ��һ��ӿ��������ʪ�����Ь�ӡ�
LONG
        );
        set("outdoors","����");
        set("exits",([
		"west"  : __DIR__"island"+(1+random(3)),
		"east"  : __DIR__"island"+(1+random(3)),
		"north" : __DIR__"island3",
		"south" : __DIR__"island"+(1+random(3)),
        ]));
	set("objects", ([
		MISC_D("beike") : 1,
		"/d/kunlun/npc/keshuang" : 1,
		"/d/kunlun/npc/klbaobiao" : 1,
		"/d/kunlun/npc/jiapu" : 1,

	]));
        setup();
}

void init()
{
        add_action("do_swim","swim");
        add_action("do_swim","youyong");
		add_action("do_kill","kill");
		add_action("do_baohu","baohu");

}

int do_swim()
{
        object me = this_player();

        if (me->is_busy())
		return notify_fail("��������æ���أ�");

        message_vision("$Nһ�����壬�������������һ��Ͳ����ˡ�\n", me);
        tell_object(me,"������һ�ᣬת�۵��˰��ߣ�����ʯ��һ����Ծ����ȥ��\n");
        me->move(__DIR__"haigang");
        tell_room(environment(me), me->name() +
	"ץ�Ű�����ʯ�������������������\n", me);
        return 1;
}

int do_kill(string arg)
{
	object me,ob1,ob2;
	me=this_player();
	ob1=present("zheng keshuang",this_object());
	ob2=present("huyuan dizi",this_object());

	if (!arg)
	{
		return notify_fail("��Ҫɱ˭��\n");
	}
	if (arg=="zheng keshuang"||arg=="zheng"||arg=="keshuang")
	{
		message_vision(HIR"֣��ˬ��ߵı���һ��$NҪɱ�Լ������ˣ���ʱ��ŭ������ɱ�֣�\n"NOR,me);
		ob2->kill_ob(me);

	}
	
}


int do_baohu(string arg)
{
	object me;
	me=this_player();
	if (!arg||arg!="֣��ˬ")
	{
		return notify_fail("��Ҫ����˭��\n");
	}
	if (!me->query_temp("quest/kl/baifxf/askzheng"))
	{
		return notify_fail("���֣���ӷ��׷ǹʣ�����Ҫ��û�������ڣ�\n");

	}
	if (!present("zheng keshuang",environment(me)))
	{
		return notify_fail("֣��ˬ���ٴ˵أ���Ҫ����˭��\n");
	}
	if (time()-me->query("quest/kl/baifxf/time")<86400)
	{
		return notify_fail("������̫Ƶ���ˣ�����������\n");

	}
	if (me->query_temp("quest/kl/baifxf/askzheng")&&arg=="֣��ˬ")
	{
		message_vision(HIY"$N��֣��ˬ����һ����˵��������С��ү���ģ������ڣ��κ�����֮�ж��˲����㣡��\n"NOR,me);
		
		call_out("do_guard",10+random(10),me);
		me->start_busy(10);
	}
	return 1;
}

int do_guard(object me)
{
	object obj,ob;
	//me=this_player();
	ob=present("zheng keshuang",environment(me));
	if (!ob)
	{
		return notify_fail("֣��ˬ�Ѿ�Ϊ����ɱ����Ҫ����˭��\n");

	}
	tell_object(me,HIC"$N�����Ĵ�����֮�ʣ�������ʵ���ţ���֪�̿ͺ�ʱ�ܵ���������Υ�볤�ϵ�ָʾ��\n" 
                       "��ʱ������һ������������������������Ȼ�и����ڷ��ٳ��˴�������\n"NOR+
                    RED"\n����Ϯ����Ϯ����"NOR+HIC"�������֣��ˬ��ǰ���;��������������һ�ɸ����ޱȵ�����ֱ���Լ����ģ�\n"NOR); 
     message_vision(HIY"\n$NƮȻ��أ�ֻ��ǰ����վ���ĸ������ˣ�����һ�������˺���������һ���ϡ�\n"NOR, me);
     obj=new("d/lanzhou/npc/heiyiren");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));
	 obj->kill_ob(me);
	 obj->kill_ob(ob);
     
	 obj=new("d/lanzhou/npc/heiyiren");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));
	 obj->kill_ob(me);
	 obj->kill_ob(ob);

     obj=new("d/lanzhou/npc/heiyiren");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));    
     obj->kill_ob(me);
	 obj->kill_ob(ob);

     obj=new("d/lanzhou/npc/heiyiren");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));    
     obj->kill_ob(me);
	 obj->kill_ob(ob);

	 call_out("check_fight",50,me,ob);

	return 1;
}
int check_fight(object me,object ob)
{
	
	if (!me) return 1;
	if (environment(ob)!=environment(me))
	{
		write("���Ѿ��뿪������򣬱���֣��ˬ����ʧ�ܣ�\n");
		do_fail(me);
		return notify_fail("���Ѿ��뿪������򣬱���֣��ˬ����ʧ�ܣ�\n");
	}
	
	if (!present("zheng keshuang",environment(me)))
	{
		write("֣��ˬ���̿���ɱ������ʧ�ܣ�\n");

		do_fail(me);
		return notify_fail("֣��ˬ���̿���ɱ������ʧ�ܣ�\n");
	}
	if (present("heiyi ren",environment(me)))
	{
		message_vision(HIR"�������ۼ�������Χס����Ȼ��һ������Ȼ�����Լ����ƣ�ƴ��ȫ����������֣��ˬ!\n"NOR,me);
		if (ob)
		{
			message_vision(HIY"֣��ˬ���һ����Ϊ�̿�һ������!\n"NOR,me);
			ob->die();
		}
		write("֣��ˬ���̿����շ�����ɱ������ʧ�ܣ�\n");

		do_fail(me);
		return notify_fail("֣��ˬ���̿���ɱ������ʧ�ܣ�\n");

	}
	me->set("quest/kl/baifxf/baohu",1);
	me->set("quest/kl/baifxf/time",time());
	me->set("quest/kl/baifxf/combat",me->query("conbat_exp"));
	me->delete_temp("quest/kl");
	message_vision(HBBLU+HIW"$N�Ѿ���ɷ��������ϵ����񣬱���֣��ˬ�ɹ������Ի�ȥ�����ˣ�\n",me);	
	return 1;


}

int do_fail(object me)
{
	if (!me) return;
	
	me->add("quest/kl/baifxf/fail",1);
	me->set("quest/kl/baifxf/time",time());
	me->set("quest/kl/baifxf/combat",me->query("conbat_exp"));
	me->delete_temp("quest/kl");
	message_vision(HIC"�ڹ涨ʱ����֣��ˬ��������ɱ������ʧ�ܣ�\n"NOR,me);
	return 1;
}
