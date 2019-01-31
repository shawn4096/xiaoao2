// /d/city/npc/wenfangshi

inherit NPC;
 
void create()
{
	set_name("�·�ʩ", ({ "wen fangshi", "wen", "fangshi" }));
	set("title", "�¼�����");
	set("long", 
        "�������¼����ϵ������·�ʩ��\n"
        "һ�������ʮ�����ߣ���ͷ���Ѿ���ס�\n");
	set("gender", "����");
	set("age", 50);
	set("attitude", "friendly");
	set("shen", -9000);
	set("str", 30);
	set("int", 30);
	set("con", 25);
	set("dex", 27);
	
	set("max_qi", 2000);
	set("max_jing", 1800);
	set("eff_jingli", 1800);
	set("neili", 2000);
	set("max_neili", 2000);
	set("jiali", 100);
	set("combat_exp", 850000);
	 

	set_skill("force", 240);
	set_skill("yijin-jing", 240);
	set_skill("dodge", 250);

	set_skill("shaolin-shenfa", 240);
	set_skill("cuff", 250);
	set_skill("wenjia-daofa", 230);
	set_skill("parry", 240);
	set_skill("blade", 240);
	set_skill("wenjia-quan", 250);
	set_skill("literate", 110);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("cuff", "wenjia-quan");
	map_skill("parry", "wenjia-daofa");
	map_skill("blade", "wenjia-daofa");
	prepare_skill("cuff", "wenjia-quan");

	setup(); 
	carry_object(ARMOR_D("cloth"))->wear();
	carry_object("/clone/weapon/blade1")->wield();
}
