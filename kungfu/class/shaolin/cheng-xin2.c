// Npc: /kungfu/class/shaolin/cheng-xin2.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;

string ask_ranmu();

void create()
{
	set_name("����", ({
		"chengxin luohan",
		"chengxin",
		"zhuangyan",
		"luohan",
	}));
	set("long",
		"����һλ�뷢���׵���ɮ����һϮ��ߺڲ����ġ�������ݸߣ�\n"
		"̫��Ѩ�߸߹����ƺ��������书��\n"
	);

	set("nickname", "ׯ���޺�");
	set("gender", "����");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 60);
	set("shen", 5000);
	set("str", 25);
	set("int", 25);
	set("con", 25);
	set("dex", 25);
	set("max_qi", 3500);
	set("max_jing", 2000);
	set("neili", 2500);
	set("max_neili", 2500);
	set("jiali", 50);
	set("combat_exp", 150000);
    set("unique", 1);

	set_skill("force", 120);
	set_skill("yijin-jing", 120);
	set_skill("dodge", 120);
	set_skill("shaolin-shenfa", 120);
	set_skill("blade", 120);
	set_skill("xiuluo-dao", 120);
	set_skill("parry", 120);
        set_skill("cuff", 120);
        set_skill("jingang-quan", 120);
	set_skill("buddhism", 150);
	set_skill("literate", 140);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("blade", "xiuluo-dao");
	map_skill("parry", "xiuluo-dao");
    map_skill("cuff", "jingang-quan");
    prepare_skill("cuff", "jingang-quan");

	create_family("������", 37, "����");
    set("inquiry", ([			
			    "ȼľ����"       : (: ask_ranmu :),
    ]));


	setup();

        carry_object("/d/shaolin/obj/jiedao")->wield();
        carry_object("/d/shaolin/obj/cheng-cloth")->wear();
}


#include "/kungfu/class/shaolin/cheng.h"

string ask_ranmu()
{
	object muchai;
	object me=this_player();
	if (!me->query_temp("rmdf/askkuranmu"))
	{
		command("say �����ǰ���������������Ҫ���ڵأ�������������������\n");
		return "û�������ʦ��ָʾ�鶼����͵ѧ��\n";
	}
	if (!present("mu chai",environment(me)))
	{
		muchai=new("d/shaolin/obj/muchai");
		muchai->move("d/shaolin/banruo6");
		command("say �ã���Ȼ�������ʦ������ѧϰ�ģ��ҾͰ���һ��æ�������Ķ���һ��ľ�����Լ�ȥ��ϰ�ɣ�\n");

	}
	command("say �����ʦ����˵����Ҫ������ȼľ�����������ľ��ȥ����ľ��\n");
	command("say ÿ����������Ҫ�Լ�Ϊ������ʽ������ֱ���������žŰ�ʮһ��Ϊֹ��\n");
	command("say ����Ǹոտ�ʼ��\n");
	command("say ������һ�ν���ľ���Ϳ���Ħ����ȼ��ľ����Ϊ���ɣ�\n");
	command("say ��Ҳ��ȼľ������������\n");
	command("say ���ְ�������ֻ�������ʦ��ϰ�ɹ����ɼ����Ź����ж�ô���ѣ�\n");
	command("say ������ѧ��ȥ���ԣ����ܷ�ﵽ���Ч���������������ҿ��ͷ����ɣ�\n");
	me->set_temp("rmdf/askchengxin",1);
	return "ȼľ����Ҫ���ǿ��������\n";

}