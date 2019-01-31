// Npc: /d/tianshan/npc/zhujian.c
// By Linux
#include <ansi.h>

inherit NPC;
string ask_mimi();
void create()
{
	set_name("ͯ����Ů", ({ "shi nu", "shi", "shinu"}));
	set("long",
	    "���Ǹ���ò毺õ�Ů��, ��������,\n"+
	    "�������, �������.\n"+
	    "���ź�ͯ����ӵ�������Ů.\n");
		set("gender", "Ů��");
		set("age", 18);
		set("per",27);
        set("shen_type",1);
        set("attitude", "peaceful");

        set("str", 20);
        set("int", 25);
        set("con", 30);
        set("dex", 30);
		set("unique", 1);

        set("qi", 2500);
        set("max_qi", 2500);
        set("jing", 2500);
        set("max_jing", 2500);
        set("neili", 3500);
        set("max_neili", 3000);
        set("eff_jingli", 2500);
        set("jiali", 60);

        set("combat_exp", 1000000);
        set("score", 2000);

        set_skill("force", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("hand",100);
        set_skill("strike", 100);
        set_skill("sword",100);

        set_skill("tianyu-qijian",100);
        set_skill("zhemei-shou",100);
        set_skill("liuyang-zhang",100);
        set_skill("yueying-wubu",100);
        set_skill("bahuang-gong", 100);
        set_skill("literate", 130);
        set_skill("yangyanshu",130);

        map_skill("force", "bahuang-gong");
        map_skill("strike","liuyang-zhang");
        map_skill("dodge", "yueying-wubu");
        map_skill("hand", "zhemei-shou");
        map_skill("parry", "liuyang-zhang");
        map_skill("sword", "tianyu-qijian");
		prepare_skill("hand", "zhemei-shou");
		prepare_skill("strike", "liuyang-zhang");
		set("inquiry", ([
			"name": "ū�ҽ���"+this_object()->name()+"����ʮ�������Ͷ������ѧ�ա�",
			"rumors": "������ټ���������",
			"����"		: (: ask_mimi :),

			"here": "���������չ�����û�»��ǲ�Ҫ�����ת�ĺá�",
			//"������": "tete",
		//	"����" : (: ask_mimi :),

		]));

        create_family("���չ�",3,"����");
        setup();
        carry_object(__DIR__"obj/qingyi")->wear();
        carry_object(BINGQI_D("changjian"))->wield();
        add_money("silver",20+random(20));
}
string ask_mimi()
{
	object me=this_player();
	if (me->query("family/family_name")!="���չ�")
	{
		command("say �������ң���ʲô����֪������ֻ�������ź�ͯ����ӵ�һ��СѾ�߶��ѡ�\n");
		return "����~~~~~~~~~~~~~~~��\n	";
		//return 1;
	}
	if (me->query("quest/tonglao/pass"))
	{
		message_vision(HIC"С��Ů��Ŀ��˼Ƭ��, ˵��������Ȼ���Ѿ����ͯ���洫, �Ҿ͸������С���ܡ���\n"NOR,me);
        command("sigh" + me->query("id"));
		command("say �����ź�ͯ�����ʱ��ͯ����˯ǰ�Ӵ����ó�һ�����ڲ��Ϸ��ģ��Ҳ�֪����ʲô�飡");
		command("say ��֪���϶����书�޹أ���Ҳ��֪����ʲô�飬ֻ��֪��ͯ��ÿ�ο���󣬶����Ե÷ǳ����ᣡ\n");
		me->set_temp("askyangyanshu",1);
	}
	return "ͯ��ÿ��������Խ��Խ��С�����������ĺܣ�\n";
	//return 1;
}
