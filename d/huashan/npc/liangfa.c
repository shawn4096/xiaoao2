// NPC: /d/huashan/npc/liangfa.c
// Date: Look 99/03/25

#include <ansi.h>

inherit NPC;
inherit F_MASTER;


void create()
{
	set_name("����", ({ "liang fa", "liang", "fa" }));
	set("nickname", "�����");
	set("long", 
"������ĸ��ݣ������е�ľ�ţ�����ȷ������������\n"
"ͬ�������е������ǻ�ɽ������һ���еĺ��֡�\n");
	set("gender", "����");
	set("age", 29);
	set("attitude", "friendly");
	set("shen_type", 1);
	set("per", 23);
	set("str", 23);
	set("int", 23);
	set("con", 24);
	set("dex", 28);
	
	set("max_qi", 5000);
	set("max_jing", 3800);
	set("neili", 5000);
	set("max_neili", 5000);
	set("eff_jingli", 3800);

	set("jiali", 50);
	set("combat_exp", 4000000);
	set("score", 4000);

	set_skill("force", 180);
	set_skill("huashan-qigong", 180);
	set_skill("dodge", 180);
	set_skill("parry", 180);
	set_skill("sword", 180);
	set_skill("cuff", 180);
	set_skill("strike", 180);
	set_skill("hunyuan-zhang", 180);
	set_skill("huashan-jianfa", 180);
	set_skill("poyu-quan", 180);
	set_skill("huashan-shenfa", 180);
	//set_skill("zhengqi-jue", 100);

	map_skill("force", "huashan-qigong");
	map_skill("dodge", "huashan-shenfa");
	map_skill("parry", "huashan-jianfa");
	map_skill("sword", "huashan-jianfa");
	map_skill("cuff", "poyu-quan");
	map_skill("strike", "hunyuan-zhang");

	prepare_skill("cuff", "poyu-quan");

	create_family("��ɽ��", 14, "����");

	setup();
	carry_object(BINGQI_D("sword/sword"))->wield();
	carry_object(ARMOR_D("armor/cloth"))->wear();
}
void attempt_apprentice(object ob)
{
       
        if (ob->query("shen") < 10000 ) {
		command("say �һ�ɽ�����������������ɣ��Ե���Ҫ����,����10k��Ҫ�����ҡ�");
		command("say �ڵ��з��棬" + RANK_D->query_respect(ob) + "�Ƿ����ò�����");
		return;
        }
       
        command("say �ðɣ��Ҿ���������,���ҪΪ���ǻ�ɽ����������");
        command("chat* ���ϸ��ֳ�һ˿Ц�ݣ�����"+ob->query("name")+"Ц�����һ�ɽ������Ϊ����֮�ס�");
        command("recruit " + ob->query("id"));
        ob->set("quest/huashan","����");
}