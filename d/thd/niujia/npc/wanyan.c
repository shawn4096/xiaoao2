// wanyanhonglie.c

inherit NPC;
#include <ansi.h>
string ask_name();
string ask_help();
#define QUESTDIR1 "quest/���Ӣ�۴�/��ѩ����/"

void create()
{
       // set_name("���պ���", ({"wanyan honglie", "honglie", "wanyan"}));
        set_name("��������", ({"zhongnan nanzi", "nanzi", "man"}));
		set("gender", "����");
       // set("title", HIY"��������ү"NOR);
        set("age", 31);
        set("class", "officer");
	      set("long","[1;31m�����������˺��ص��ˣ�����ȥ��Ҫ�����ˡ�[0m\n");
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 26);
        set("per", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 26);

        set("qi", 20000);
        set("max_qi", 20000);
        set("jing", 3200);
        set("max_jing", 3200);
        set("neili", 8300);
        set("max_neili", 8300);
        set("jiali", 10);
		
        set("combat_exp", 2500000);
        set("score", 10000);
		set("inquiry", ([
			"name" : (:ask_name:),
			"����" : (:ask_help:),
			]));

        set_skill("force", 250);
        set_skill("dodge", 240);
        set_skill("parry", 240);
        set_skill("cuff",240);
		set_skill("caoshang-fei",250);
		set_skill("taizu-quan",250);

        set_skill("baduan-jin",250);
		map_skill("force","baduan-jin");
       	map_skill("dodge","caoshang-fei");
       	map_skill("cuff","taizu-quan");
       	map_skill("parry","taizu-quan");

		setup();
        carry_object("/clone/armor/jinduan")->wear();
        carry_object("d/mr/obj/guanxue")->wear();

}

string ask_name()
{
	object me=this_player();
	if (!me->query("quest/���Ӣ�۴�/��ѩ����/notongyin"))
	{
		return "�Ҳ������㣬����˭����ʲô��ͼ��\n";
	}
	command("say ��Ȼ��λӢ����������嵨���Ҿ����������㣡\n");
	command("say ���Ǵ�����ү���պ��ң���׳ʿ���ң��ز����㣡\n");
	set_name("���պ���", ({"wanyan honglie", "honglie", "wanyan"}));
	set("title", HIY"��������ү"NOR);
	me->set_temp("quest/���Ӣ�۴�/��ѩ����/askwanyanname",1);
	return "Ӣ������һ·�����һؾ�������������л��\n";
}
string ask_help()
{
	object me=this_player();
	if (!me->query("quest/���Ӣ�۴�/��ѩ����/notongyin"))
	{
		return "�����ϲ⣬�ѵ����Σ���\n";
	}

	if (!me->query_temp("quest/���Ӣ�۴�/��ѩ����/askwanyanname"))
	{
		return "��һ����������������£�һ����ò��û�У�\n";
	}
	message_vision(HIY"$N�������ӣ�����˵������������ǰԺ�Ⱦƣ��������㣬��Ҫ����ҡ�!\n"NOR,me);
	command("say ׳ʿ���ң������ز����㣡\n");
	apply_condition("liuxue",1000);
	apply_condition("neishang",1000);
	me->set_temp("quest/���Ӣ�۴�/��ѩ����/answerhelpwanyan",1);

	return "Ӣ�ۼ�Ȼ��Ӧ���ң�����������л��\n";
}