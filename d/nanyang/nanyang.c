// Room: /d/nanyang/nanyang.c
// Lklv Modify 2001.10.10
#include <ansi.h>

inherit ROOM;
#define XKX_QUEST2 "quest/������/������/"
int do_soushen(string arg);
int do_find(string arg);
int do_help(string arg);
void create()
{
	set("short", "������");
	set("long", @LONG
����������������ġ��������������ס�ڸ�����¡�������ڡ���������
�粻�󣬷�Բ������ʮ�������Ϊ�ش��ϱ���Ҫ���ϣ��������������ĸ���
�������˺ܶࡣ������һ�Ҿ�¥�������˿����٣��������ⲻ�Ǻ�����������
�������ֱͨ���ݳǡ�
LONG
	);
	set("outdoors", "����");
	set("exits", ([
		"south" : __DIR__"yidao2",
		"north" : __DIR__"yidao3",
		"west" : __DIR__"jiulou1",
				"east" : __DIR__"datiepu",

	]));
	set("objects",([
		__DIR__"npc/xiao-fan" : 1,
		__DIR__"npc/xiao_qigai" : 1,
	]));
	setup();
}

void init()
{
	object me,wu;
	me=this_player();
	
	if (me->query_temp(XKX_QUEST2+"findwu"))
	{
		if (!objectp(wu=present("wu daotong",environment(me))))
		{
			message_vision(HIR"���ͨ�ȵ������������ɣ���\n"NOR,me);
			wu=new("d/nanyang/npc/wudaotong");
			wu->move(environment(me));
		}
		me->add_busy(1);
		wu->kill_ob(me);
		me->kill_ob(wu);
		
		//add_action("do_soushen","soushen");
		//add_action("do_soushen","search");

		me->delete_temp(XKX_QUEST2+"findwu");
		me->set_temp(XKX_QUEST2+"meetwu",1);
	}
		add_action("do_soushen","soushen");
		add_action("do_find","xunzhao");
		add_action("do_help","baohu");

	//Ҫ������ʱ���Է���������
}

int do_soushen(string arg)
{
	object me,ob,obb,obj;
	me=this_player();
	ob=present("corpse",environment(me));
	if (ob)
		obb=ob->query("kill_by");

	if (!arg||arg!="���ͨ��ʬ��")
	{
		return notify_fail("��Ҫ��˭����\n");
	}
	if (!me->query_temp(XKX_QUEST2+"meetwu"))
	{
		return notify_fail("��Ҫ��������ʲô��\n");
	}
	if (!objectp(ob=present("corpse",environment(me))))
	{
		return notify_fail("���ֲ��ǽ�����������ʲô��\n");
	}
	if (ob->query("name")!="���ͨ��ʬ��"
		&&obb->query("id")!=me->query("id"))
	{
		return notify_fail("������ɱ��ʬ��ô��");
	}
	message_vision(HIC"$N���������ͨ��ʬ����������ȥ������һ��С����֮�⣬���ʲôҲû���ҵ���\n"NOR,me);
	message_vision(HIC"$N��ϸ������Ǹ����ͨ������Ǹ�С����������һЩ�����Ӻͻ�ʯ������֮�⣬ʲôҲû���ҵ���\n"NOR,me);

	message_vision(HIY"\n$Nվ���Ƕ������������̣�������⣬�ѵ������ͨ����û�д�˵�������\n"NOR,me);
	

	//message_vision(HIG"\n\n\$N��������һĻ��ͷ��β������һ�飬Ҳû�з���������Ψһֵ�ÿ��ɵ����Ǹ������Ǹ��ձ���\n"NOR,me);
	//message_vision(HIC"$N�ڸ������˰��죬Ҳû�з����Ǹ��ձ�����ȥ�Ķ��ˡ�\n"NOR,me);
	me->set_temp(XKX_QUEST2+"soushen",1);



	message_vision(YEL"\n\n������ʱ����Ȼ�������˺����������������������еĶ����������Һڷ�կ������û�棡��\n"NOR,me);
	message_vision(YEL"\n\n�ڽֿڳ����ĸ�ɽկ��ǿ��ͷ�ӣ���ͼ���������еĶ�����\n"NOR,me);
	 me->start_busy(1);

	 obj=new("d/lanzhou/npc/heiyiren");
     obj->set("kill_id",me->query("id"));
	 obj->set_name("����", ({ "zhou mu", "zhou", "mu" }) );	 
	 obj->set("title", "�ڷ�կ����");
     obj->move(environment(me));
	 obj->kill_ob(me);

	 obj=new("d/lanzhou/npc/heiyiren");
     obj->set("kill_id",me->query("id"));
	 obj->set_name("����", ({ "yang wei", "yang", "wei" }) );	 
	 obj->set("title", "�ڷ�կ����");
     obj->move(environment(me));
	 obj->kill_ob(me);

	 obj=new("d/lanzhou/npc/heiyiren");
     obj->set("kill_id",me->query("id"));
	 obj->set_name("���֮", ({ "li chongzhi", "li", "chongzhi" }) );	 
	 obj->set("title", "�ڷ�կ����");
     obj->move(environment(me));
	 obj->kill_ob(me);
	 obj=new("d/lanzhou/npc/heiyiren");
     obj->set("kill_id",me->query("id"));
	 obj->set_name("��һ��", ({ "zhang yifeng", "zhang", "yifeng" }) );	 
	 obj->set("title", "�ڷ�կ����");
     obj->move(environment(me));
	 obj->kill_ob(me);
	return 1;
}


int do_find(string arg)
{
	object me,qigai;
	me=this_player();

	if (me->is_fighting()||me->is_busy())
	{
	   return notify_fail("������æµ�С�");

	}	
	if (!arg||arg!="������")
	{
	   return notify_fail("��ҪѰ��ʲô��\n");

	}
	if (!me->query_temp(XKX_QUEST2+"soushen")) 
	{
	   return notify_fail("������˰��죬Ҳû��������������ȥ�Ķ��ˡ�");
	}
	if (!objectp(qigai=present("xiao qigai",environment(me))))
	{
		return notify_fail("������˰��죬Ҳû��������������ȥ�Ķ���!�������ǰ��ա�\n");
	}
	//�ȴ�ʯ�����
	if (me->query_temp(XKX_QUEST2+"helpshi"))
	{
		message_vision(HIC"$N����Ѱ�Ҹ�������������ٴμ�������ͨ���µ�����������û�ҵ���ö�����\n"NOR,me);
		message_vision(HIC"$N���з�ŭ֮�ʣ����������Ǹ�С������˳�־����ӳ�ȥ��\n",me);
		message_vision(HIY"\n\n��ʱ����Ȼ�����ֽ���һ��������������𣬡���磬�㿴�Ǹ������������ǵļ������\n"NOR,me);

		call_out("sxz_come",3+random(4),me);
		return 1;
	}
	message_vision(HIC"$N��Ѱ�Ҽ䣬��Ȼ���ֽ�ͷһ����һ��С��ؤ����ͷ���棬����������һ���ձ��ٳԣ�\n"NOR,me);
//	message_vision("$N���´�ϲ������Ѹ�ٳ��Ǹ�С��ؤ���˹�ȥ�����룡\n",me);
	message_vision(HIY"�Ǹ���ͷ�����С��ؤ���˿����е��ձ����������ǲ��ᣬÿ�ζ�����ҧһС�ڣ�\n"NOR,me);
	
	me->set_temp(XKX_QUEST2+"findqigai",1);
	return 1;
}
//�Ȼ�ʯ����

int do_help(string arg)
{
	object me,ob,wu;
	me=this_player();
	ob=present("xiao qigai",environment(me));

	if (!arg||arg!="С��ؤ")
	{
		if (ob)
		{
			ob->die();
		}
		me->delete_temp("quest/������/������");
		me->set("quest/������/time",time());

		write("С��ؤΪ���ͨ��ɱ��������ֹ���ڴ��´λ���\n");
		return 1;
		
	}
	if (!ob)
	{
				
				//write("С��ؤΪ���ͨ��ɱ��������ֹ���ڴ��´λ���\n");
		me->delete_temp("quest/������/������");
		me->set("quest/������/time",time());

		return notify_fail("С��ؤ����������������ֹ���ڴ��´λ���\n");

	}
	if (!me->query_temp(XKX_QUEST2+"wucome"))
	{
		me->delete_temp("quest/������/������");
		me->set("quest/������/time",time());

		return notify_fail("���ͨ�Ѿ����ˣ�����������ֹ���ڴ��´λ���\n");

	}
	
	if (me->query_temp(XKX_QUEST2+"helpshi"))
	{
		//me->set("quest/������/time",time());

		return notify_fail("���Ѿ�������һ���ˣ�����������ֹ���ڴ��´λ���\n");

	}
	me->set("quest/������/time",time());

	message_vision(HIR"$N��Ȼ������У������Ǹ�С��ؤ�϶��ǹ��������Ĺؼ�������������С��ؤ��ǰ�����������ͨ���ɱ�У�\n"NOR,me);

	if (!objectp(wu=present("wu daotong",environment(me))))
	{
		wu=new("d/nanyang/npc/wudaotong");
		wu->move(this_object());
		wu->set("combat_exp",me->query("combat_exp")*3/2);
		me->start_busy(1);
		wu->kill_ob(me);
	}
	me->set_temp(XKX_QUEST2+"helpshi",1);
	return 1;
}

int sxz_come(object me)
{
	object shi,min;
	
	message_vision(CYN"˵��֮�䣬��ƥ�����۶�����һ��һ�ڣ�������������ׯׯ��������ˣ���\n"NOR,me);
	message_vision(CYN"�������س�����Ī����ĸ�������Ǹ�С��ؤ�����簮�������Լ�����������һ������\n"NOR,me);
	message_vision(CYN"�Ǹ�С��ؤҲ�Ƕ�����֮�飬�̲�ס�����������衱��\n"NOR,me);

	message_vision(HIG"\n\n������ׯ��ʯ��ȵ�������������\n"NOR,me);
	message_vision(HIG"\nʯ��˵��������λӢ���Ƿ���Խ��������ͨ���е����¸��ҿ�������\n"NOR,me);
    message_vision(HIG"\n�㻹����ԥ�䣬ʯ����������֣��ȵ����������ˣ����С�\n"NOR,me);


	if (!objectp(shi=present("shi qing",environment(me))))
	{
		shi=new("d/motianya/npc/shiqing");
		shi->set("combat_exp",(int)me->query("combat_exp")*3/2);
		shi->set_skill("shangqing-jian",(int)me->query_skill("force",1)*4/3);

		shi->move(environment(me));
		
	}

	if (!objectp(min=present("min rou",environment(me))))
	{
		min=new("d/motianya/npc/minrou");
		min->set("combat_exp",(int)me->query("combat_exp")*3/2);
		min->set_skill("shangqing-jian",(int)me->query_skill("force",1)*4/3);
		min->move(environment(me));
	}
	shi->kill_ob(me);
	min->kill_ob(me);

	//me->kill_ob(shi);
	me->set_temp(XKX_QUEST2+"killshiqing",1);
	call_out("checking",10+random(5),me,shi,min);
	return 1;
}
int checking(object me,object shi,object min)
{
	if (!me) return 0;
	
	if (!shi)
	{
		me->delete_temp("quest/������/������");
		me->set("quest/������/time",time());

		return notify_fail("��ʧ�ְ�����ׯ��ʯ���ɱ�ˣ�ʯ��������֮��ǣ�������ֹ��\n");
	}
	if (!min)
	{
		me->delete_temp("quest/������/������");
		me->set("quest/������/time",time());

		return notify_fail("��ʧ�ְ�����ׯ���������ɱ�ˣ�ʯ��������֮��ǣ�������ֹ��\n");
	}
	
	message_vision(HIR"\n��ʱ���Ǹ�С��ؤ����������ˣ�����ˣ����Ƕ��Ǻ��ˣ�\n"NOR,me);
	message_vision(CYN"С��ؤ�޺���������ˣ�����ˣ����Ƕ��Ǻ��ˣ�\n"NOR,me);
	message_vision(CYN"������һ���ձ�ô������ˣ��Ҹ�������ˣ�\n"NOR,me);
	message_vision(HIC"С��ؤ�������������~~~\n"NOR,me);

	shi->remove_all_enemy();
	shi->start_busy(2);
	min->remove_all_enemy();
	min->start_busy(2);

	me->remove_all_enemy();
	me->start_busy(2);
	me->set_temp(XKX_QUEST2+"haoren",1);
	return 1;
}