// Npc: /kungfu/class/shaolin/hui-xiu.c

#include <ansi.h>
inherit NPC;
string ask_me();

void create()
{
	set_name("�۾�����", ({
		"huijing zunzhe",
		"huijing",
		"zunzhe",
	}));
	set("long",
		"���з����Ѽ�����ļ��ְ�����Ȼ�Ǹ�������\n"
		"̫��Ѩ΢͹��˫Ŀ��������\n"
	);

	set("gender", "����");
	set("attitude", "friendly");
	set("class", "bonze");

        set("age", 50);
        set("shen_type", 1);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("max_qi", 450);
        set("max_jing", 300);
        set("neili", 600);
        set("max_neili", 600);
 
		set("jiali", 50);
		set("combat_exp", 120000);
		set("score", 100);

        set_skill("force", 100);
        set_skill("yijin-jing", 100);
        set_skill("dodge", 100);
        set_skill("shaolin-shenfa", 100);
        set_skill("cuff", 100);
        set_skill("jingang-quan", 100);
        set_skill("staff", 100);
        set_skill("pudu-zhang", 100);
        set_skill("parry", 100);
        set_skill("buddhism", 100);
        set_skill("literate", 100);
   		map_skill("force", "yijin-jing");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("cuff", "jingang-quan");
        map_skill("staff", "pudu-zhang");
        map_skill("parry", "pudu-zhang");

        prepare_skill("cuff", "jingang-quan");

		create_family("������", 38, "����");
        set("inquiry",  ([
			"����" : (: ask_me :),
		]));
	setup();

        carry_object("/d/shaolin/obj/chanzhang")->wield();
        carry_object("/d/shaolin/obj/hui-cloth")->wear();
}


string ask_me()
{
        object me=this_player();
        
		if (!me->query_temp("bingcan/askbingcan"))
		{
			return "�������ҿɰ���С������˭���������͵��!\n";
		}
		
		command("say �������Ƕ���֮�����ǿ����ҵ�С��������\n");
		command("say ����ϱ����Ҵ���ɽ��ɽһ��ɽ���������֡�\n");
		command("say ����ϲ����涾�ޱȣ����ұ�����ǣ����в�����Ϊ�����������\n");
		command("say ��ǰһ���������ֹ�������ϧ���˸�͵���ˡ�\n");
		command("say ����Ը������ȥ�һ����Ҿ͸������Ǹ����ڡ�\n");
		command("say �мǣ��������޶���ȵ�һ��С·�����ߵ�һ����������\n");
		command("say ȥ֮ǰҪ׼����һ����«����Ӧ����ǵ�������������ץ������\n");
		me->set_temp("bingcan/askxiu",1);
		return "�ðɣ�ȥ�Ķ�Ӧ��С�ķ�������ֹ�����ϸ�������\n";
}
