// fangtianlao.c ������

inherit NPC;
#include <ansi.h>
string ask_wei();
void create()
{
	set_name("������", ({ "fang tianlao","tianlao","fang" }) );
	set("gender", "����" );
	set("age", 52);
	set("long", "�������������ɰ��һ��������ӻ�Ҳ��죬Ц���е���Ϊ
�Ͱ����ס�ֻ�������Ϊ��С��\n");
	set("attitude", "peaceful");
        set("nickname", "�������ֳ���");
	set("class", "bonze");
	set("str", 35);
	set("con", 35);
	set("int", 25);
	set("dex", 35);

	set("unique", 1);
	set("max_qi", 23000);
	set("max_jing", 4500);
	set("neili", 13000);
	set("max_neili", 13000);
	set("jiali", 170);
	set("shen_type", 1);
	set("startroom","/d/shaolin/shijie8");
	set("combat_exp", 6900000);
	set("chat_chance_combat", 50);
		set("chat_msg_combat", ({
		//(: perform_action, "sword.sanjue" :),
			(: perform_action, "sword.sanjue" :)
        }));
	set_skill("force", 400);
	set_skill("finger", 400);
	set_skill("sword", 400);
	set_skill("dodge", 400);
	set_skill("parry", 400);
	set_skill("shaolin-shenfa", 400);
	set_skill("literate", 120);
	set_skill("yizhi-chan", 400);
    set_skill("damo-jian", 400);
	set_skill("yijin-jing", 400);
	set_skill("buddhism", 150);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
        map_skill("finger", "yizhi-chan");
        map_skill("parry", "damo-jian");
        map_skill("sword", "damo-jian");
        prepare_skill("finger", "yizhi-chan");
        
		

	create_family("��������", 19, "����");

	set("chat_chance", 20);
	set("inquiry", ([
		"������ʥ": (: ask_wei :),
	
	]));
	setup();
	carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

void init()
{
	object me=this_player();
	if (me->query_temp("klbs/askhe")&& present("fang tianlao",environment(me)))
	{
		message_vision(HIC"�����Ϳ�����һ�ۣ�������Ȼ���������������������ʥ�����������֣����ڴ˷��أ���֪����ʱ��������\n"NOR,me);
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
	me->set_temp("kl/baihe/fightfang",1);
	
	return "�������������ɣ�";
}