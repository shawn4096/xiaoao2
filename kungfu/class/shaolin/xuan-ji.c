// By Spiderii
#include <ansi.h>
inherit NPC;

void create()
{
	set_name("���Ŵ�ʦ", ({
		"xuanji dashi",
		"xuanji",
		"dashi",
	}));
	set("long",
		"����һλ�����ü����ɮ����һϮ��˿�ػ����ġ�����ĸߴ�\n"
		"���ֹ�ϥ��˫Ŀ������գ�ȴ��ʱ���һ�ƾ��⡣\n"
	);


	set("nickname", "����Ժ����");
	set("gender", "����");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 70);
	set("shen_type", 1);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	set("max_qi", 20000);
	set("max_jing", 8000);
	set("neili", 30000);
	set("max_neili", 30000);
	set("jiali", 200);
	set("combat_exp", 10000000);
	set("score", 500000);

	set_skill("force", 480);
	set_skill("yijin-jing", 480);
	set_skill("dodge", 480);
	set_skill("shaolin-shenfa", 480);
	set_skill("parry", 480);
	set_skill("hand", 480);
	set_skill("claw", 480);
	set_skill("strike", 480);
	set_skill("club", 480);
	set_skill("staff", 480);
	set_skill("zui-gun", 480);
	set_skill("pudu-zhang", 480);
	set_skill("qianye-shou", 480);
	set_skill("yingzhua-gong", 480);
	set_skill("sanhua-zhang", 480);
	set_skill("buddhism", 140);
	set_skill("literate", 140);

	map_skill("force", "yijin-jing");
	map_skill("strike", "sanhua-zhang");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("finger", "nianhua-zhi");
	map_skill("hand", "qianye-shou");
	map_skill("claw", "yingzhua-gong");
	map_skill("staff", "pudu-zhang");
	map_skill("club", "zui-gun");
	map_skill("parry", "sanhua-zhang");

	prepare_skill("finger", "nianhua-zhi");
    prepare_skill("strike", "sanhua-zhang");
    set("chat_chance_combat", 70);
	set("chat_msg_combat", ({
		(: perform_action, "strike.sanhua" :),
		(: perform_action, "finger.fuxue" :),
		(: exert_function, "jingang" :),
	}));
	create_family("������", 36, "����");

	setup();

        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

void attempt_apprentice(object ob)
{
	object me; 
	mapping ob_fam, my_fam;
	string name;

	me = this_object();
	my_fam  = me->query("family");
	name = ob->query("name");

	if (!(ob_fam = ob->query("family")) || ob_fam["family_name"] != "������")
	{
		command("say " + RANK_D->query_respect(ob) + "�뱾��������������֪�˻��Ӻ�̸��");
		return;
	}

	if ( (string)ob->query("class")!="bonze" && ob_fam["family_name"] == "������") 
	{
		command("say " + RANK_D->query_respect(ob) + "���׼ҵ��ӣ�����������ѧ�ա�");
		return;
	}

	if ( ob_fam["generation"] <= my_fam["generation"] )
	{
		command("say " + RANK_D->query_respect(ob) + "��ƶɮ����ҵ� !");
		return;
	}

	if ( ob_fam["generation"] == (my_fam["generation"] + 1) && name[0..1] == "��")
	{
		command("say " + ob_fam["master_name"] + "��ͽ�������ܵ���������ˣ������� !");
		command("recruit " + ob->query("id"));
	}
	else
	{
		command("say " + RANK_D->query_respect(ob) + "���㱲�ݲ��ϣ�����Խ����ʦ��");
		return;
	}

	return;
}
