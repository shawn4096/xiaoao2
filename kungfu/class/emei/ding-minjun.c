// /kungfu/class/emei/ding-minjun.c
// Creat by Lklv 2001.10.18

inherit NPC;
inherit F_MASTER;
void create()
{
        set_name("������", ({"ding minjun", "ding", "minjun"}));
        set("long", "�������ʦ̫�İ˴��׼ҵ���֮һ��\n");
        set("nickname","��������");
        set("gender", "Ů��");
        set("attitude", "friendly");
	    set("unique", 1);
        set("age", 25);
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
	    set("per", 12);
        set("max_qi", 3800);
        set("max_jing", 3800);
        set("neili", 3800);
        set("max_neili", 3800);
        set("jiali", 100);
	    set("combat_exp", 2000000);
        set("score", 100);

	set_skill("dacheng-fofa", 150);
	set_skill("linji-zhuang", 220);
	set_skill("huifeng-jian", 220);
	set_skill("sword", 220);
	set_skill("literate", 50);
	set_skill("parry", 220);
	set_skill("dodge", 220);
	set_skill("strike", 220);
	set_skill("sixiang-zhang", 220);
	set_skill("force", 220);
	set_skill("anying-fuxiang", 220);

	map_skill("force", "linji-zhuang");
	map_skill("sword", "huifeng-jian");
	map_skill("parry", "huifeng-jian");
	map_skill("dodge", "anying-fuxiang");
        create_family("������", 4, "����");

        setup();

	carry_object("/d/emei/obj/changjian")->wield();
	carry_object("/d/emei/obj/shoes")->wear();
	carry_object("/d/emei/obj/cloth")->wear();
}

void attempt_apprentice(object ob)
{
	if ((string)ob->query("class") == "bonze" ){
		command ("say ��ֻ���׼ҵ��ӡ�");
		return;
	}
	if ((string)ob->query("gender") == "����" ){
		command ("angry ");
		command ("say ��������ľ��ǲ��в�Ů֮�ˡ�");
		return;
	}
	command (":) ");
	command ("say �ðɣ��Ҿ����������������׼ҵ��ӡ�");
	command("recruit " + ob->query("id"));
	if( (string)ob->query("class")!="bonze" ){
		ob->set("title", "�������׼ҵ���");
//		ob->set("class","emsujia");
	}
}