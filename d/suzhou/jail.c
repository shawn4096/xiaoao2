#include <room.h>
inherit ROOM;
#include "/d/suzhou/npc/lchj.h";//���Ǿ�
#include <ansi.h>
int do_fail(object me);

void create()
{
        set("short", "����");
        set("long", @LONG
�����Ǽ�����ԼĪ���ɼ�����һ���ʯ�ң�ǽ�ںͶ��嶼�Ǵ�ʯ������
ǽ�������һֻ��Ͱ�������ŵ��ľ��ǳ�����ù����������ǽ�ϵ�С����
ȥ�����Լ������ָ���һ�ǡ�
LONG
        );

        set("exits", ([
                  "east" : __DIR__"bingying",
        ]));
        set("objects", ([
                __DIR__"npc/dingdian" : 1,
        ]));

        set("cost", 0);
       set("coor/x",90);
  set("coor/y",-190);
   set("coor/z",0);
   set("incity",1);
	setup();
}

void init()
{
        add_action("do_guard","guard");
        add_action("do_guard","jingjie");
		add_action("do_guard","baohu");

}
int do_guard(string arg)
{
	object me;
	me=this_player();
	if (me->is_busy())
	{
		return notify_fail("����æ·�У����԰����\n");

	}
	if (!arg||arg!="����")
	{
		return notify_fail("��Ҫ�ڴ˿��ؾ��䱣��˭��\n");
	}
	if (!me->query_temp(QUESTDIR3+"kanshou"))
	{
		return notify_fail("�������������׷ǹʣ�����Ҫ��û�������ڣ�\n");

	}
	if (!present("ding dian",environment(me)))
	{
		return notify_fail("���䲻�ڴ˵أ���Ҫ����˭��\n");
	}
	if (time()-me->query(QUESTDIR+"time")<86400)
	{
		return notify_fail("������̫Ƶ���ˣ������������˺��֣�����������\n");

	}
	
		message_vision(HIY"$N�Զ������һ����˵�������붡�������ģ������ڣ��κ�����֮�ж��˲����㣡��\n"NOR,me);
		
		call_out("attacker_come",10+random(10),me);
		
		me->start_busy(10);
	
	return 1;
}

int attacker_come()
{
	object obj,ob,me;
	me=this_player();
	ob=present("ding dian",this_object());
	if (!ob)
	{
		return notify_fail("�����Ѿ�ΪѪ��������ɱ����Ҫ����˭��\n");

	}
	tell_object(me,HIY"�����ʱ�Ѿ���������״̬��ͷ�������뵣���ʱ��Ȼ�Ѿ����������Ľ�Ҫ��ͷ��\n"NOR);

	tell_object(me,HIC"$N�����Ĵ�����֮�ʣ�������ʵ���ţ���֪Ѫ���Ÿ��ֺ�ʱ�ܵ���������Υ�����ָʾ��\n" 
                       "��ʱ������һ����ٱ��ڵ�������������Ȼ�и����ڷ��ٳ��˴�������\n"NOR+
						"������ʶ�ط����ڶ�����ǰ����ʱ������һ���੹�Ц������õģ�ԭ��������������\n"NOR); 
     message_vision(HIR"\n$Nֻ����������վ���������������������䣬�ó����վ��������㲻��������������վ�����ļ��ա�\n"NOR, me);
    
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
	 //������
     obj=new("d/lanzhou/npc/heiyiren");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));    
     obj->kill_ob(me);
	 obj->kill_ob(ob);

	 call_out("check_fight",20+random(6),me,ob);

	return 1; 
}


int check_fight(object me,object ob)
{
	
	if (!me) return 1;

	if (!present("ding dian",environment(me))||!ob)
	{
		write("���䱻Ѫ���Ÿ�����ɱ������ʧ�ܣ�\n");

		do_fail(me);
		return notify_fail("���䱻Ѫ���Ÿ�����ɱ������ʧ�ܣ�\n");
	}

	if (environment(ob)!=environment(me))
	{
		write("���Ѿ��뿪������򣬱�����������ʧ�ܣ�\n");
		do_fail(me);
		return notify_fail("���Ѿ��뿪������򣬱�����������ʧ�ܣ�\n");
	}
	
	if (present("heiyi ren",environment(me)))
	{
		message_vision(HIR"�������ۼ�������Χס����Ȼ��һ������Ȼ�����Լ����ƣ�ƴ��ȫ���������򶡵�!\n"NOR,me);
		if (ob)
		{
			message_vision(HIY"������һ����ΪѪ���Ÿ���һ������!\n"NOR,me);
			ob->die();
		}
		write("���䱻Ѫ���Ÿ������շ�����ɱ������ʧ�ܣ�\n");

		do_fail(me);
		return notify_fail("���䱻Ѫ���Ÿ�����ɱ������ʧ�ܣ�\n");

	}
	me->set(QUESTDIR+"time",time());
	me->set(QUESTDIR+"combat",me->query("conbat_exp"));
	
	me->set(QUESTDIR3+"jingjieok",1);

	me->set_temp(QUESTDIR3+"jingjieok",1);

	tell_object(me,HIC"����˵����С��������Ӣ�£���Ȼ�ܽ���Щ�̿�ɱ��,������ѧǱ�ʡ�\n"NOR);
	tell_object(me,HIC"����˵���������Ͼ�Ҫ����ȥ��һ�����£������������ˣ���Ȼ��Ҫ���飬�ҿ��Ը���˵�µ����ֵܵĹ��¡�\n"NOR);
	tell_object(me,HIC"����˵���������ֵܵ�ʱҲ�Ǻ���һ��ɱ����Щ��ͽ��Ȼ��ȥ��ѩɽһ��������������Ѱ��ʲô�ˡ�\n"NOR);
	tell_object(me,HIC"����˵����ǰ�����ҳ�ȥ��̽ʱ���ƺ����仨��ˮ�����������������ˡ�\n"NOR);
	tell_object(me,HIC"����˵����������ħ��֣��������˶�������������\n"NOR);
	
	message_vision(HBBLU+HIW"$N�Ѿ���ɼ����ж��䲼�ø�������񣬱�������ɹ����������øд�����\n",me);	

	return 1;

}

int do_fail(object me)
{
	if (!me) return;
	
	me->add(QUESTDIR3+"fail",1);
	me->set(QUESTDIR+"time",time());
	me->set(QUESTDIR+"combat",me->query("conbat_exp"));
	me->delete_temp(QUESTDIR3);
	message_vision(HIC"�ڹ涨ʱ���ڶ��䱻������ɱ������ʧ�ܣ�\n"NOR,me);
	return 1;
}
