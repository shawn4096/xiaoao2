//�����䵶.c
//����job��Ҫ��
#include <ansi.h>

inherit ITEM;
int do_gongji(object me);
int do_cairou(string arg);
void create()
{
	set_name("С�䵶", ({ "xiao peidao", "peidao", "dao", "blade" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�Ѳ���Ѱ���䱸�������С�䵶�������������ҡ�\n"
			+"�������˲��ĺ�װ�Σ����·�д�ˡ�Ѫ���š�����������\n"
			+"����job�ǲ�Ѫ������ɱ����,����caixue(caiji) xx����caixue ye zhu��\n"
			+"����ǲ���job��ɱ���������ָ��Ϊcairou corpse\n"
			+"����jobִ���������ָ��chakan peidao\n");
		set("value", 1000);
		set("material", "iron");
	}
} 

int init()
{
	add_action("do_cairou","cairou");
	add_action("do_caixue","caixue");
	add_action("do_caixue","jixue");
	add_action("do_report","chakan");

}
int do_caixue(string arg)
{
	object me,ob,at;
	string arg1;
	me=this_player();
	
	if (!arg)
	{
		return notify_fail("��Ҫ��ʲô�����Ѫ��");
	}
	if (me->query("combat_exp")>100000)
	{
		return notify_fail("��ľ���ֵ�Ѿ����ߵ���,����100k������Щ�ͼ������ø�ʦ����ȥ���ɣ�\n");
	}
	if (!me->query_temp("xuedao/askcaixue"))
	{
		return notify_fail("����Ե�޹����˲�ʲôѪ��\n");
	}
	/*
	switch (arg)
	{
		case : Ұ��
			arg1==ye zhu;
			break;
		case : ÷��¹
			arg1==ye zhu;
			break;
	}*/
	ob=present(arg,environment(me));

	if (!ob) return notify_fail("��Ҫ�ɼ��Ķ��ﲻ�ڴ˴�!\n");
	
	if (ob->query("id")=="corpse")
		return notify_fail("��Ҫ�ɼ�����߶���ʬ�����Ѿ����ã��޷��ɼ�!\n");
	if (ob->query("owner")!=me->query("id"))
		return notify_fail("�ⲻ���㷢�ֵ�������޷��ɼ�!\n");

	if (ob->query("name")=="÷��¹")
	{
		message_vision(HIC"$NС��ǰ�У�Ǳ���ڲݴ��У���׼����ͷ÷��¹����Ѫ�����������������ַ���С�䵶���˳�ȥ��\n"NOR,me);
		if (random(me->query("combat_exp"))>me->query("combat_exp")/3)
		{
			message_vision(HIR"С�䵶������ͷ÷��¹�����ʵ�ѪҺ����ע�����пյ�Ѫ�ۣ�Ȼ�����������\n"NOR,me);
			
		}else me->add_busy(2);
	
		this_object()->add("xuedao/caixue/luxue",1);

	}else if (ob->query("name")=="Ұ��")
	{
		message_vision(HIB"$N���ٱ��ܣ��ܵ�Ұ��ǰ���ó�С�䵶��������һ����\n"NOR,me);
		this_object()->add("xuedao/caixue/zhuxue",1);

	}else if (ob->query("name")=="Ұ��")
	{
		if (me->query_skill("jingang-liantishu",1)<10) return notify_fail("��Ľ��������̫�ͣ�����10�����޷�ʩչѪ���Ŷ��з��ţ�\n");
		if (random(me->query("combat_exp"))>me->query("combat_exp")/3)
		{			
			message_vision(HIY"$N��ʹѪ�����ھ��ַ����������䵶,�������������������һ�����зɱ��е�Ұ�á�\n"NOR,me);

		}else me->add_busy(2);

		this_object()->add("xuedao/caixue/tuxue",1);

	}else if (ob->query("name")=="Ұӥ")
	{
		
		message_vision(HIR"$N�����������ó�С�䵶��ʼ����ͷҰӥ���ϲ���Ѫ����,���ַ�����ߵĴ����С�\n"NOR,me);
		this_object()->add("xuedao/caixue/yingxue",1);

	}else if (ob->query("name")=="���")
	{
		message_vision(HIG"$N�����������ó�С�䵶��ʼ����ͷ������ϲ���Ѫ����,���ַ�����ߵĴ����С�\n"NOR,me);
		this_object()->add("xuedao/caixue/zhangzixue",1);

	}
	if (this_object()->query("xuedao/caixue/luxue")
		&&this_object()->query("xuedao/caixue/tuxue")
		&&this_object()->query("xuedao/caixue/yingxue")
		&&this_object()->query("xuedao/caixue/zhangzixue")
		&&this_object()->query("xuedao/caixue/zhuxue"))
	{
		message_vision(HIM"\n\n$N��������Լ�����Ƥ�ң������Ѿ��ɼ�����ʦ�����������ֲ�ͬ����ѪҺ�����Ի�ȥ�����ˣ�\n"NOR,me);
		this_object()->set("xuedao/caixue/ok",1);
		me->set_temp("xuedao/caixue/ok",1);
		me->start_busy(1);
	}
	me->start_busy(1);
	message_vision("\n��ͷ"+ob->query("name")+"�ܵ��˾��ţ��������ߣ�$N����Ѫ���е�����ѪҺ��ע�������Ƥ���У�\n",me);

	destruct(ob);
	me->receive_damage("qi",10);
	me->receive_damage("jing",10);


	return 1;
	
}
int do_cairou(string arg)
{
	object me,ob,obb;
	me=this_player();
	
	if (!arg)
	{
		return notify_fail("��Ҫ��ʲô������⣿");
	}
	ob=present(arg,environment(me));
	
	if (!ob) return notify_fail("��Ҫ�ɼ��Ķ���ʬ�岻�ڴ˴�!\n");
	
	obb=ob->query("kill_by");

	if (obb->query("id")!=me->query("id"))
		return notify_fail("�ⲻ����ɱ��������޷����⣡\n");
	if (!me->query_temp("xuedao/askdalie"))
	{
		return notify_fail("����Ե�޹����˲�ʲôѪ��\n");
	}

	if (me->query("combat_exp")>300000&&me->query("quest/xuedao/baishi/pass"))
	{
		return notify_fail("��ľ���ֵ�Ѿ����ߵ��ˣ�����300k������Щ�ͼ������ø�ʦ����ȥ���ɣ�\n");
	}

	if (ob->query("id")!="corpse")
		return notify_fail("��Ҫ�ɼ�����߶���ʬ�����Ѿ����ã��޷��ɼ�!\n");
	if (ob->query("name")=="÷��¹��ʬ��")
	{
		message_vision(HIC"$N�����������ó�С�䵶��ʼ����ͷ÷��¹���ϲ���Ѫ���������ַ�����ߵĴ����С�\n"NOR,me);
		this_object()->add("xuedao/cairou/lurou",1);

	}else if (ob->query("name")=="Ұ���ʬ��")
	{
		message_vision(HIC"$N�����������ó�С�䵶��ʼ����ͷҰ�����ϲ���Ѫ����,���ַ�����ߵĴ����С�\n"NOR,me);
		this_object()->add("xuedao/cairou/zhurou",1);

	}else if (ob->query("name")=="Ұ�õ�ʬ��")
	{
		message_vision(HIC"$N�����������ó�С�䵶��ʼ����ͷҰ�����ϲ���Ѫ����,���ַ�����ߵĴ����С�\n"NOR,me);
		this_object()->add("xuedao/cairou/turou",1);

	}else if (ob->query("name")=="Ұӥ��ʬ��")
	{
		message_vision(HIC"$N�����������ó�С�䵶��ʼ����ͷҰӥ���ϲ���Ѫ����,���ַ�����ߵĴ����С�\n"NOR,me);
		this_object()->add("xuedao/cairou/yingrou",1);

	}else if (ob->query("name")=="��ӵ�ʬ��")
	{
		message_vision(HIC"$N�����������ó�С�䵶��ʼ����ͷ������ϲ���Ѫ����,���ַ�����ߵĴ����С�\n"NOR,me);
		this_object()->add("xuedao/cairou/zhangzirou",1);

	}
	if (this_object()->query("xuedao/cairou/lurou")
		&&this_object()->query("xuedao/cairou/zhurou")
		&&this_object()->query("xuedao/cairou/turou")
		&&this_object()->query("xuedao/cairou/yingrou")
		&&this_object()->query("xuedao/cairou/zhangzirou"))
	{
		message_vision(HIM"\n\n$N��������Լ�������ӣ������Ѿ��ɼ�����ʦ�����������ֲ�ͬ�⣬���Ի�ȥ�����ˣ�\n"NOR,me);
		this_object()->set("xuedao/cairou/ok",1);
		me->set_temp("xuedao/cairou/ok",1);
		me->start_busy(1);
		if (me->query("combat_exp")>100000)
			do_gongji(me);
	}
	me->start_busy(1);
	message_vision("\n$N�������ʬ����⾫���ɼ��ɾ������ֽ��Ǽ��ӵ�һ�ߵĲݴ�֮�У�\n",me);
	destruct(ob);

	return 1;
	
}
int do_gongji(object me)
{
	object ob;
	if (!random(4))
	{
		ob=new("d/xuedao/npc/xuebao");
		if (me->query("combat_exp")>260000)
			ob->set("combat_exp",me->query("combat_exp"));
		ob->set("max_qi",(int)me->query("qi")*3/2);
		ob->set("eff_qi",(int)me->query("qi")*3/2);
		ob->set("max_jing",(int)me->query("qi")*3/2);
		ob->set("eff_jing",(int)me->query("jing")*3/2);
		ob->move(environment(me));
		ob->kill_ob(me);	
		message_vision(RED"��ʱ����Ȼ�Ӳݴ��дܳ�һ��������ѩ��������Ϯ����\n"NOR,me);
		return 1;

	}else if (random(4)>1)
	{
		ob=new("d/xuedao/npc/chailang");
		ob->set("combat_exp",me->query("combat_exp"));
		ob->set("max_qi",(int)me->query("qi")*3/2);
		ob->set("eff_qi",(int)me->query("qi")*3/2);
		ob->set("max_jing",(int)me->query("qi")*3/2);
		ob->set("eff_jing",(int)me->query("jing")*3/2);
		ob->move(environment(me));
		ob->kill_ob(me);	
		message_vision(RED"��ʱ����Ȼ�Ӳݴ��дܳ�һ�����͵Ĳ��ǣ�����Ϯ����\n"NOR,me);
		return 1;
	} else {
		ob=new("d/xuedao/npc/zigou");
		ob->set("combat_exp",me->query("combat_exp"));
		ob->set("max_qi",(int)me->query("qi"));
		ob->set("eff_qi",(int)me->query("qi"));
		ob->set("max_jing",(int)me->query("qi"));
		ob->set("eff_jing",(int)me->query("jing"));
		ob->move(environment(me));
		ob->kill_ob(me);	
		message_vision(RED"��ʱ����Ȼ�Ӳݴ��дܳ�һ�������Ĳ��ǣ�����Ϯ����\n"NOR,me);
		return 1;

	}
}

int do_report(string arg)
{
	object me,ob,at;
	string msg;
	me=this_player();
	ob=this_object();
	
	if (!arg||arg!="peidao")
	{
		return notify_fail("��Ҫ�鿴ʲô��");
	}

	if (me->query_temp("xuedao/askcaixue") && query("job")=="��Ѫ")
	{
		msg="ע�⣬������Ѽ�������Ѫ����Ѫ��ӥѪ�����Ѫ��¹Ѫ�����������\n"
			+"������ִ�в�Ѫ����\n";
		if (ob->query("xuedao/caixue/luxue"))
		{
			msg+="���Ѿ��Ѽ���"+ob->query("xuedao/caixue/luxue")+"��¹Ѫ��\n";
		}
		if (ob->query("xuedao/caixue/tuxue"))
		{
			msg+="���Ѿ��Ѽ���"+ob->query("xuedao/caixue/tuxue")+"����Ѫ��\n";
		}
		if (ob->query("xuedao/caixue/zhuxue"))
		{
			msg+="���Ѿ��Ѽ���"+ob->query("xuedao/caixue/zhuxue")+"����Ѫ��\n";
		}
		if (ob->query("xuedao/caixue/yingxue"))
		{
			msg+="���Ѿ��Ѽ���"+ob->query("xuedao/caixue/yingxue")+"��ӥѪ��\n";
		}
		if (ob->query("xuedao/caixue/zhangzixue"))
		{
			msg+="���Ѿ��Ѽ���"+ob->query("xuedao/caixue/zhangzixue")+"�����Ѫ��\n";
		}
		if (ob->query("xuedao/caixue/ok"))
		{
			msg+="��Ĳ�Ѫ�����Ѿ�����ˣ��Ͻ���ȥ�����ɡ�\n";

		}

		tell_object(me,msg);
		return 1;
	}
	if (me->query_temp("xuedao/askdalie")&& query("job")=="����")
	{
		msg="ע�⣬������Ѽ��������⡢���⡢ӥ�⡢����⡢¹������������\n"
			+"������ִ�в�������\n";
		if (ob->query("xuedao/cairou/lurou"))
		{
			msg+="���Ѿ��Ѽ���"+ob->query("xuedao/cairou/lurou")+"��¹�⡣\n";
		}
		if (ob->query("xuedao/cairou/turou"))
		{
			msg+="���Ѿ��Ѽ���"+ob->query("xuedao/cairou/turou")+"�����⡣\n";
		}
		if (ob->query("xuedao/cairou/zhurou"))
		{
			msg+="���Ѿ��Ѽ���"+ob->query("xuedao/cairou/zhurou")+"�����⡣\n";
		}
		if (ob->query("xuedao/cairou/yingrou"))
		{
			msg+="���Ѿ��Ѽ���"+ob->query("xuedao/cairou/yingrou")+"��ӥ�⡣\n";
		}
		if (ob->query("xuedao/cairou/zhangzirou"))
		{
			msg+="���Ѿ��Ѽ���"+ob->query("xuedao/cairou/zhangzirou")+"������⡣\n";
		}
		if (ob->query("xuedao/cairou/ok"))
		{
			msg+="��Ĳ��⹤���Ѿ�����ˣ��Ͻ���ȥ�����ɡ�\n";

		}
		tell_object(me,msg);
		return 1;
	}
	
	return notify_fail("��Ŀǰû���κ�job\n");
	
}