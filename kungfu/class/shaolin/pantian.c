// pantiangeng.c �����

inherit NPC;
#include <ansi.h>
string ask_wei();
void create()
{
	set_name("�����", ({ "pan tiangeng","pan","tiangeng" }) );
	set("gender", "����" );
	set("age", 64);
	set("long", "���������òƽƽ���棬ֻ����ɫ���ƣ�΢�����ݡ���˵һ��
��ħ���������޳����ҡ�/n");
	set("attitude", "peaceful");
	set("nickname", "�������ֳ���");
	set("class", "bonze");
	set("str", 35);
	set("con", 35);
	set("int", 25);
	set("dex", 35);


	set("max_qi", 13000);
	set("max_jing", 4500);
	set("neili", 13000);
	set("max_neili", 13000);
	set("jiali", 150);
	set("shen_type", 1);
	set("startroom","/d/shaolin/shijie8");
	set("unique", 1);
	set("combat_exp", 6900000);
	set("chat_chance_combat", 50);
		set("chat_msg_combat", ({
		//(: perform_action, "sword.sanjue" :),
			(: perform_action, "sword.sanjue" :)
        }));

	set("combat_exp", 6500000);

	set_skill("force", 400);
	set_skill("finger", 400);
	set_skill("sword", 400);
	set_skill("dodge", 400);
	set_skill("parry", 400);
	set_skill("shaolin-shenfa", 400);
	set_skill("literate", 150);
	set_skill("yizhi-chan",400);
        set_skill("fumo-jian", 400);
	set_skill("yijin-jing", 400);
	set_skill("buddhism", 400);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
        map_skill("finger", "yizhi-chan");
        map_skill("parry", "yizhi-chan");
        map_skill("sword", "fumo-jian");
        prepare_skill("finger", "yizhi-chan");

	create_family("��������", 19, "����");

	set("chat_chance", 20);
	set("inquiry", ([
		"������ʥ": (: ask_wei :),
	
	]));
	setup();
       //  carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

void init()
{
	object me=this_player();
	if (me->query_temp("klbs/askhe")&& present("pan tiangeng",environment(me)))
	{
		message_vision(HIC"�����������һ�ۣ�������Ȼ���������������������ʥ�����������֣����ڴ˷��أ���֪����ʱ��������\n"NOR,me);
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
	me->set_temp("kl/baihe/fightpan",1);
	
	return "�������������ɣ�";
}