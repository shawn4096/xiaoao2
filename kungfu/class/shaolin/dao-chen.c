// Npc: /kungfu/class/shaolin/dao-chen.c
// Date: YZC 96/01/19

inherit NPC;

string ask_me(string);

void create()
{
	set_name("������ʦ", ({
		"daochen chanshi",
		"daochen",
		"chanshi",
	}));
	set("long",
		"����һλ��ĸߴ������ɮ�ˣ����۴�׳��������Բ�����ֱֳ�\n"
		"�У���һϮ�Ҳ�������ģ��ƺ���һ�����ա�\n"
	);


	set("gender", "����");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 40);
	set("shen_type", 1);
	set("str", 20);
	set("int", 20);
	set("con", 20);
	set("dex", 20);
	set("max_qi", 400);
	set("max_jing", 300);
	set("neili", 450);
	set("max_neili", 450);
	set("jiali", 40);
	set("combat_exp", 80000);
	set("score", 100);

	set_skill("force", 80);
	set_skill("yijin-jing", 80);
	set_skill("dodge", 80);
	set_skill("shaolin-shenfa", 80);
	set_skill("strike", 80);
	set_skill("banruo-zhang", 80);
	set_skill("parry", 80);
	set_skill("damo-jian", 80);
	set_skill("buddhism", 80);
	set_skill("literate", 80);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("strike", "banruo-zhang");
	map_skill("parry", "damo-jian");

	prepare_skill("strike", "banruo-zhang");

	create_family("������", 39, "����");

        set("inquiry", ([
		"���" : (: ask_me, "qimeigun" :),
		"�䵶" :   (: ask_me, "jiedao" :),
                "ľ��" :   (: ask_me, "mudao" :),
		"����" :   (: ask_me, "chanzhang" :),
                "����" :   (: ask_me, "changjian" :),
                "Ƥ��" :   (: ask_me, "changbian" :),
        ]));

	set("wuqi_count", 25);

	setup();

        carry_object("/d/shaolin/obj/dao-cloth")->wear();
}

string ask_me(string name)
{
	mapping fam; 
	object ob;
	
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "������")
		return RANK_D->query_respect(this_player()) + 
		"�뱾��������������֪�˻��Ӻ�̸��";

	if (  present(name, this_player()) )
		return RANK_D->query_respect(this_player()) + 
		"���������ϲ�����������������������Ҫ�ˣ� ����̰�����У�";

	if (query("wuqi_count") < 1)
		return "��Ǹ�������ò���ʱ�������Ѿ������ˡ�";

	ob = new("/d/shaolin/obj/" + name);
	ob->move(this_player());

	add("wuqi_count", -1);

	message_vision("������$Nһ��" + ob->query("name") + "��\n", this_player());

	return "��ȥ�ɡ�����Ҫ��ס������ֻ�ɷ������䣬����ƾ��ɱ�����顣";
}
