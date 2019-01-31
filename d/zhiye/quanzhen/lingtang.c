#include <ansi.h>
inherit ROOM;
int do_fail();
void create()
{
        set("short", "����");
        set("long", @LONG
�˵��ǰڷ�ȫ����ƽ�����������ķ��䡣����ܴ�����
�Ĺ�ľ(guan)�ڷ��������룬�������������һ���ŵ��ʻ�����
�����е����������飬���������֮��������
LONG);
       // set("sleep_room",1);
        set("exits", ([
                "down" : __DIR__"laojundian",
        ]));
        set("item_desc", ([
                "guan": RED "����һ��Ӳľ��������ײģ��������˵��������������棬�����ྲ������������\n" NOR
        ]));
        set("objects", ([
                "/d/quanzhen/obj/xianglu": 1,
				"/d/quanzhen/obj/guancai": 1,
        ]));
        set("no_clean_up", 0);
        setup();
}

void init()
{
		if (!this_player()->query_temp("quest/qz/xtg/dingyang/start")) return;
		
        add_action("do_ketou","ketou");
		add_action("do_jingxiang","jingxiang");
		add_action("do_jibai","jibai");
		add_action("do_zhengli","zhengli");

}
int do_jingxiang()
{
	object me=this_player();
	if (me->query("family/family_name")!="ȫ���")
	{
		return notify_fail("����Ե�޹ʣ���ȫ��̵��ӣ�������������\n");
	}
	message_vision(MAG"$N����ǰ�����㰸��������̴֧�㣬��Ȼ�󹧹��������㣡\n"NOR,me);
	
	me->set_temp("marks/jingxiang",1);
	return 1;

}
int do_ketou(string arg)
{
	object me=this_player();
	if (!me->query_temp("marks/jingxiang"))
	{
		return notify_fail("����������ٿ�ͷ��\n");
	}
	if (!arg||arg!="������ʦ")
	{
		return notify_fail("��Ҫ��˭��ͷ��\n");
	}
	message_vision(HIC"$N�����������˹��֮ǰ��������������������ͷ���������죡\n"NOR,me);
	me->set_temp("marks/ketou",1);
	message_vision(HIY"\n\n��ʱ��˾�����Աߺ������������ݿ�ʼ����\n"
		HIW+"\n\n��Ȼ�䣬$N��Լ�����ݶ��ƺ�����΢����Ƭ���˵�������\n"NOR,me);

	return 1;

}
int do_jibai(string arg)
{
	object me=this_player();
	if (!me->query_temp("marks/ketou"))
	{
		return notify_fail("����ȿ�ͷ�ټ�����ʦ��\n");
	}
	if (!arg||arg!="������ʦ")
	{
		return notify_fail("��Ҫ����˭��\n");
	}
	message_vision(HIC"$N�����������˹��֮ǰ�������ϵ�ֽǮ�����������ͭ��֮�У�\n"NOR,me);
	message_vision(HIG"\n\n$NȻ�������¹��¿�ʼ����ʦ��ͷ��\n"NOR,me);

	message_vision(HIY"\n\n$N��Ϊȫ����ӣ������쳣��ʹ������ϰ�ף�Т��Т�ﵱΪ��ʦ�����Ǳ����ݣ�\n"NOR,me);
	
	me->set_temp("marks/jibai",1);
	//call_out("do_oyfcome",1,me);
	return 1;

}
int do_zhengli(string arg)
{
	object me=this_player();
	if (!me->query_temp("marks/jibai"))
	{
		return notify_fail("����ȼ���������������ʦ���ݣ�\n");
	}
	if (!arg||arg!="��ʦ����")
	{
		return notify_fail("�˵�������ʦ���ã���Ҫ��ʲô����\n");
	}
	message_vision(HIC"$N�����������˹��֮ǰ��Ϊ��ʦ�����Ǳ����ݣ�\n"NOR,me);
	message_vision(HIR"\n\n$N������ʦ�ճ�����Ȼ���������б�ʹ���̲�ס��Ҫ�������һ����\n"NOR,me);

	add_action("do_cry","cry");
	
	me->set_temp("marks/zhengli",1);
	//call_out("do_oyfcome",1,me);
	return 1;
}
int do_cry(string arg)
{
	object me=this_player();
	if (!me->query_temp("marks/zhengli"))
	{
		return notify_fail("�����������ʦ���ݣ�\n");
	}
	message_vision(HIC"$N�����������˹��֮ǰ������ʦ����������������ϧ������������ټ�֮�գ�\n"NOR,me);
	message_vision(HIR"\n\n$N�뵽�Ӵ�������;�������ټ�����������ʹ�ޣ��������£�\n"NOR,me);

	message_vision(HIY"\n\nȻ���������޳�������$N���ʹ�ޣ�����������Ȼ���ţ�һ��������\n"NOR,me);
	message_vision(HIR"\n\n��ʱ����������һ���੹�Ц���������������������ţ���֣���ľ���ô���ˡ���\n"NOR,me);

	me->set_temp("marks/zhengli",1);
	call_out("do_oyfcome",4+random(4),me);
	return 1;
}

int do_oyfcome(object me)
{
		object feng;
		int i;

		i=me->query("max_pot")-100;
		i=i+50+random(20);

		if (me->query("family/family_name")!="ȫ���")
		{
			me->move("/d/quanzhen/laojundian");
			return notify_fail("���ȫ��̵��ӣ���η��������\n");
		}
        message_vision(HIR "��Ȼ�䣬�������һ������׳����\n\n" NOR, me);
        if (!objectp(feng=present("ouyang feng",this_object())))
        {
			feng=new("/d/quanzhen/npc/feng");
			if (me->query("combat_ext")<18000000)
				feng->move("/d/quanzhen/lingshi");
			else{
				feng->set("combat_exp",me->query("combat_exp"));
				feng->set_skill("lingshe-zhangfa",i);
				feng->set_skill("lingshe-quan",i);
				feng->set_skill("hamagong",i);
				feng->set_skill("cuff",i);
				feng->set_skill("force",i);
				feng->set_skill("staff",i);
				feng->set_skill("dodge",i);
				feng->set_skill("hamabu",i);
				feng->move("/d/quanzhen/lingshi");
			}
        }
		feng->feng_say();

		//feng->kill_ob(me);
		//feng->check();
		
		message_vision(HIW"�ۼ��������������������������˹��ǰ����ͼ�ƿ���餣��ַ������ź���\n"NOR,me);
		message_vision(HIW"$N���д��һ����\n"NOR,me);
		add_action("do_zulan","zulan");
		
		if (objectp(feng=present("ouyang feng",this_object())))
	
		call_out("do_check",30,me,feng);

		me->query_temp("marks/times",time());		
        return 1;
}
//����ŷ����
int do_zulan(string arg)
{	
	object me,feng;
	me=this_player();
	//ŷ���治��ʧ��
	if (!arg||arg!="ŷ����")
	{
		return notify_fail("���˼����Ʒ���餣���Ҫ��ֹ˭����\n");
	}
	if (objectp(feng=present("ouyang feng",this_object())))
	message_vision(HIR"$N��ŭ������������$n��ǰ���ȵ����������������Ȼ��˲���Ϊ��Ҫ������ʦ�ź�����\n"NOR,me,feng);	
	feng->kill_ob(me);
	me->set_temp("marks/zulan",1);


}
int do_check(object me,object feng)
{
	if (!me) return 0;
	if (!feng) 
	{
		tell_object(me,"����������Ѿ�����ɱ����!����ʧ�ܣ�\n");
		
		return do_fail();
	}
	if (time()-me->query_temp("marks/times")>35
		||!me->query_temp("marks/zulan"))
	{
		message_vision(HIC"$nһ�и�󡹦���������������ϣ��������ڵ��Ǳ������澭��������Цת˲��ȥ��\n"
		+"\n\n��û���赲סŷ������������澭������ʧ�ܣ�\n"NOR,me,feng);
		if (objectp(feng))
			destruct(feng);
		return do_fail();
	}
	if (!me->is_fighting()
		||me->query("eff_qi")<me->query("max_qi")/2)
	{
		message_vision(HIC"$nһ�и�󡹦���������������ϣ��������ڵ��Ǳ������澭��������Цת˲��ȥ��\n"
		+"\n\n��û���赲סŷ������������澭������ʧ�ܣ�\n"NOR,me,feng);
		return do_fail();
	}
	message_vision(HIY"\n\n��ʱ������ͻ��\n"
		+"\n\n����$N��$n���Ҵ򶷵Ľ�Ҫ��ͷ��һֱ���������ڹ�����������˺�ȻԾ��\n"
		+"\n\n�����������µ����칦��һָ����$n�Ķ�ͷ��\n"
		+"\n\n$nһʱ������Ϊ������������$n�ĸ�󡹦��\n"
		"\n\n$n���һ�������о����֣�һ�������������Ӵܶ�ȥ��\n"NOR,me,feng);
	if (objectp(feng)) destruct(feng);

	call_out("wang_die",3+random(3),me);
}
int wang_die(object me)
{
	message_vision(HIC"$N�ۼ���ʦ���������д�ϲ����æ��ͷ�ݼ���ʦ��\n"NOR,me);
	message_vision(HIM"\n\n����������һ�Բ�����ֻ������Ŀ���$Nһ�ۣ���Ц������\n"NOR,me);
	message_vision(HIY"\n\n����ʱ�⣬����������Ȼһ��������$N��ʱ�ŷ�����ʦ��Ȼ����������\n"NOR,me);
	message_vision(HIG"\n\n$N��ʱ���򣬡�������ʦԭ���Ǽ�����Ŀ�ľ�����ƭŷ�������������û��������ĸ�󡹦����\n"NOR,me);
	message_vision(HIR"\n\n��ˣ���ͨ�����йؽڣ�$N����ߵͷ������������ޣ�\n"NOR,me);
	message_vision(HIR"\n�ڱ�ʹ�䣬$N��Ȼ����������������������һ��ֽ��\n"NOR,me);
	message_vision(HIR"\n\n����ϸһ��������д����������Ե֮�ˣ�����ɽ���ġ�---�������ˣ�\n"NOR,me);

 	message("channel:rumor", HIM"��ҥ�ԡ�ĳ�ˣ�"+me->query("name")+"��Ե�ɺϣ���������������ƪ���ĵ�������\n"NOR, users());
	me->set("quest/qz/xtg/dingyang/start",1);

	message("channel:chat", HIC"�����졿"+me->query("name")+"���������˲������ţ�ȫ��������ɽׯ�Ĳ�������\n"NOR, users());
	message("channel:chat", HIC"�����졿"+me->query("name")+"���Ҵ�ȫ��ؽ����𽭺���\n"NOR, users());
	return 1;
}
int do_fail()
{
	object me,feng;

	if (!me) return 0;
	me=this_player();
	me->delete_temp("marks");
	me->delete_temp("quest/qz");
	me->set("quest/qz/xtg/dingyang/time",time());
	me->add("quest/qz/xtg/dingyang/fail",1);
	tell_object(me,HIW"\n\n����ʧ�ܣ��ٽ�������\n"NOR);
	if (objectp(feng=present("ouyang feng",this_object())))
		destruct(feng);
	return 1;
}