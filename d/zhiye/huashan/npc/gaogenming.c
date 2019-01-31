// NPC: /d/huashan/npc/gaogenming.c
// Date: Look 99/03/25
// Lklv Modify at 2001.10.18
#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("�߸���", ({ "gao genming", "gao", "genming" }));
	set("nickname", "�о�����");
	set("long",
"�߸�����Ľ��֣���һ��С����������������һ�˳ӣ�����\n"
"ͬ�������е��壬�ǻ�ɽ������һ���еĺ��֡�\n");
	set("gender", "����");
	set("age", 28);
	set("attitude", "friendly");
	set("shen_type", 1);
	set("per", 20);
	set("str", 28);
	set("int", 24);
	set("con", 20);
	set("dex", 20);

	set("max_qi", 3000);
	set("max_jing", 1800);
	set("neili", 3000);
	set("max_neili", 3000);
	set("eff_jingli", 1800);


	set("jiali", 150);
	set("combat_exp", 5000000);
	set("score", 5000);

	set_skill("force", 200);
	set_skill("dodge", 200);
	set_skill("parry", 200);
	set_skill("sword", 200);
	set_skill("cuff", 200);
	set_skill("huashan-qigong", 200);
	set_skill("huashan-jianfa", 200);
	set_skill("huashan-shenfa", 200);
	set_skill("poyu-quan", 200);
	//set_skill("zhengqi-jue", 100);

	map_skill("force", "huashan-qigong");
	map_skill("parry", "huashan-jianfa");
	map_skill("dodge", "huashan-shenfa");
	map_skill("sword", "huashan-jianfa");
	map_skill("cuff", "poyu-quan");

	prepare_skill("cuff", "poyu-quan");

	create_family("��ɽ��", 14, "����");

	setup();
	carry_object(BINGQI_D("sword"))->wield();
	carry_object(ARMOR_D("cloth"))->wear();
}

void attempt_apprentice(object ob)
{
       
        if (ob->query("shen") < 10000 ) {
		command("say �һ�ɽ�����������������ɣ��Ե���Ҫ����,����10k��Ҫ�����ҡ�");
		command("say �ڵ��з��棬" + RANK_D->query_respect(ob) + "�Ƿ����ò�����");
		return;
        }
		 if (ob->query("gender") =="Ů��" ) {
			command("say ʦ�ø���˵�ˣ�����Ů���Ӷ�ֻ���������㻹��ȥ�����ɡ�");
		return;
        }
       
        command("say �ðɣ��Ҿ���������,���ҪΪ���ǻ�ɽ����������");
        command("chat* ���ϸ��ֳ�һ˿Ц�ݣ�����"+ob->query("name")+"Ц�����һ�ɽ������Ϊ����֮�ס�");
        command("recruit " + ob->query("id"));
        ob->set("quest/huashan","����");
}
