// wujiang.c �佫

#include <ansi.h>
inherit NPC;
string ask_name();
string ask_liping();

void create()
{
	set_name(HIC"��ָ��ʷ"NOR, ({ "fu zhihuishi", "zhihuishi", "jiangjun"}));
	set("gender", "����");
	set("age", random(10) + 30);
	set("str", 25);
	set("dex", 16);
	set("con", 25);
	set("int", 16);

	set("long", "���Ǻ��ݵ���ָ������ָ��ʷ��վ����������໰�����ڵ�ȷ��˵���������硣\n");
	set("combat_exp", 75000);
	set("shen_type", 1);
	set("attitude", "peaceful");

	set_skill("cuff", 160);
	set_skill("force", 160);
	set_skill("sword", 160);
	set_skill("dodge", 160);
	set_skill("parry", 160);
	set_skill("taizu-quan", 160);
	set_skill("baduan-jin", 160);
	set_skill("caoshang-fei", 160);
	map_skill("force","baduan-jin");
	map_skill("dodge","caoshang-fei");
	map_skill("cuff","taizu-quan");
	map_skill("parry","taizu-quan");
	prepare_skill("cuff","taizu-quan");

	set_temp("apply/attack", 50);
	set_temp("apply/defense", 50);
	set_temp("apply/armor", 50);
	set_temp("apply/damage", 30);

	set("neili", 4000); 
	set("max_neili", 4000);
	set("jiali", 100);
    set("inquiry", ([
                //"ȫ���" :  "��ȫ��������µ�����������,�����������������ú����������������ʰ�㣡\n",			      
                "�����" : (: ask_name :),
			   // "��Ƽ" : (: ask_liping :),
               //	"���й���" : (: ask_gongji :),
                 
        ]) );
	setup();
	carry_object(BINGQI_D("gangjian"))->wield();
	carry_object(ARMOR_D("armor"))->wear();
}


string ask_name()
{
	object me,bing,duan;
	me=this_player();
	if (!me->query_temp("quest/���Ӣ�۴�/�����߹�/hanhua"))
	{
		command("say �ֵ��ǣ������ϣ����������ӣ�\n");
		if (present("bing",environment(this_object())))
		{
			kill_ob(me);
		}
		kill_ob(me);
		me->apply_condition("killer",10);

		return "��Ȼ�Ҵ���Ӫ��������ˣ�\n";
	}
	command("say ����ʹ���ˣ�����ô�����ò��ã�\n");
	command("say �����ҿ����δ��˴Ӻ����ȥ�ˣ�\n");
	message_vision(HIY"$N�����������ָ��ʷ������һ����������ӣ��ƺ�������˵�ѣ����к޺޲��ѣ����������������������\n"NOR,me);
	command("say ������������ȷʵ���Ƕ�����\n");
	message_vision(HIY"$N���е���𴦻�����֮�£��������׷�ʣ���ʱ��Ȼ�������ָ��ʷ�Աߴܳ�һ����Ӱ������Ϯ��\n"NOR,me);
	message_vision(HIR"$N���Ǹ����ּ��½��ּ������ǲ��죬����Ȼ������ԭ�书����ʱ���о�Ȼ������˸��֣�\n"NOR,me);
	if (!objectp(bing=present("jinguo gaoshou",environment(this_object()))))
	{
		bing=new("d/thd/niujia/npc/jinguogaoshou");
		bing->set("jiali",250);
		bing->move(environment(this_object()));
	}
	bing->kill_ob(me);
	this_object()->set_name(HIY"�����"NOR, ({ "duan tiande", "duan", "tiande" }));
	message_vision(HIG"\n��ʱ����ȴ�ڿ񺰣���ץס�������������͡���һ�ߺ��ţ�һ��ץ����ߵ�һ��ʿ����������ȥ��\n"NOR,me);
	message_vision(HIC"\n$N�����Ǹ�ʿ����Ȼ����Ů������ϡ����Ƽ����ò����ʱ����ѩ�������ﻹ��֪���⸱ָ��ʷ���Ƕ�����⹷����\n"NOR,me);
	message_vision(HIC"\n$N֪����ֻ��ץס�����������֪����Ƽ�İ�Σ��\n"NOR,me);

	me->set_temp("quest/���Ӣ�۴�/�����߹�/findduan",1);
	me->add_condition("killer",6);
	return "ɱ������\n";
}
