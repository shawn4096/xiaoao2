
inherit NPC;
#include <ansi.h>
string ask_wei();

void create()
{
	set_name("������", ({ "wei tianwang","wei" }) );
	set("gender", "����" );
	set("age", 58);
	set("long", " \n");
	set("attitude", "peaceful");
	set("nickname", "�������ֳ���");
	set("unique", 1);
	set("str", 20);
	set("con", 35);
	set("int", 25);
	set("dex", 35);

	set("max_qi", 13000);
	set("max_jing", 4500);
	set("neili", 13000);
	set("max_neili", 13000);
	set("jiali", 150);
	set("shen_type", 1);
	set("combat_exp", 6800000);

	set_skill("force", 400);
	set_skill("cuff", 400);
	set_skill("sword", 400);
	set_skill("dodge", 400);
	set_skill("parry", 400);
	set_skill("shaolin-shenfa", 400);
	set_skill("literate", 100);
	set_skill("jingang-quan", 400);
	set_skill("yijin-jing", 400);
	set_skill("buddhism", 150);
	set_skill("damo-jian", 400);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("cuff", "jingang-quan");
	map_skill("parry", "damo-jian");
	map_skill("sword", "damo-jian");
	prepare_skill("cuff", "jingang-quan");
	set("inquiry", ([
		"������ʥ": (: ask_wei :),
	
	]));
	create_family("��������", 19, "����");
	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

void kill_ob(object me)
{
	set("chat_chance_combat", 50);
	set("chat_msg_combat", ({
		(: perform_action, "sword.sanjue" :)
	}));
	::kill_ob(me);
}

void init()
{
	object me=this_player();
	if (me->query_temp("klbs/askhe")&& present("wei tianwang",environment(me)))
	{
		message_vision(HIC"������������һ�ۣ�������Ȼ���������������������ʥ�����������֣����ڴ˷��أ���֪����ʱ��������\n"NOR,me);
		command("chat ��˵������ʥҪ�����ֲ����������ֵ���ʱ�̷��أ�");

	}
}

string ask_wei()
{
	object me=this_player();
	if (!me->query_temp("klbs/askhe"))
		return "��Ϲ����ʲô������û��ϵ��\n";
    message_vision(HIC"$N��$n���˸���������$nС��˵������������ʥ....��\n"NOR,me,this_object());
	this_object()->kill_ob(me);
	me->set_temp("kl/baihe/fightwei",1);
	
	return "�������������ɣ�";/**/
}