// Npc: /kungfu/class/shaolin/xuan-cheng.c
// Date: YZC 96/01/19

inherit NPC;
string ask_me();
string ask_yzc();

void create()
{
	set_name("���δ�ʦ", ({
		"xuancheng dashi",
		"xuancheng",
		"dashi",
	}));
	set("long",
		"����һλ�����ü����ɮ����һϮ��˿�ػ����ġ�����ĸߴ�\n"
		"���ֹ�ϥ��˫Ŀ������գ�ȴ��ʱ���һ�ƾ��⡣\n"
	);


	set("gender", "����");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 70);
	set("shen_type", 1);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	set("max_qi", 1500);
	set("max_jing", 1000);
	set("neili", 2000);
	set("max_neili", 2000);
	set("jiali", 150);
	set("combat_exp", 1000000);
	set("score", 500000);

	set_skill("buddhism", 160);
	set_skill("force", 450);
	set_skill("dodge", 450);
	set_skill("parry", 450);
	set_skill("strike", 450);
	set_skill("finger", 450);
	set_skill("leg", 450);
	set_skill("cuff", 450);

	set_skill("banruo-zhang", 450);
	set_skill("club", 450);
	set_skill("zui-gun", 450);
	set_skill("jingang-quan",450);
	set_skill("yizhi-chan",450);
	set_skill("yijin-jing", 450);
	set_skill("shaolin-shenfa", 450);
	set_skill("ruying-suixingtui",450);
	set_skill("buddhism", 180);
	set_skill("literate", 150);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("parry", "banrou-zhang");
	map_skill("strike", "banruo-zhang");
	map_skill("leg", "ruying-suixingtui");
	map_skill("cuff", "jingang-quan");
	map_skill("finger", "yizhi-chan");

	prepare_skill("strike", "yizhi-chan");
	prepare_skill("cuff", "jingang-quan");

	set("chat_chance",15);
        set("chat_msg",({
      "���δ�ʦ������ƶɮֻ��̰ͼ��ѧ������Ϊ���㣬ǿ�Զ�ѧ�ϳ��书������������ϡ���\n",
      "���δ�ʦ����������ǧ��������������ɮ���������ϵ�������Ϊ��һҪ�񡣡�\n",
      "���δ�ʦ������ƶɮ�����޷������书�������ղ�������Ħڭɮڮ�ɣ����޷𷨣��ɴ˿��򡣡�\n",                              
        }) );
        set("inquiry", ([
		"Ħڭɮڮ��" :    (: ask_me :),
		"һָ��" :    (: ask_yzc :),
		]));
        set("book_count",1);
	create_family("������", 36, "����");

	setup();

        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}
void heart_beat()
{
	::heart_beat();

	clear_conditions_by_type("poison");
	if( !is_fighting() && living(this_object()))
		reincarnate();
}

string ask_me()
{
	mapping fam; 
	object ob;
	
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "������")
		return RANK_D->query_respect(this_player()) + 
		"�뱾��������������֪�˻��Ӻ�̸��";

	if (  present("moheseng diyu", this_player()) )
		return RANK_D->query_respect(this_player()) + 
		"���������ϲ������Ȿ������������Ҫ�ˣ� ��ȥ�ú��ж��ɣ�";

	if (query("book_count") < 1) return "�Բ���Ħڭɮڮ���Ѿ�����Ҫ���ˣ�";

	ob = new("/d/shaolin/npc/obj/fojing3");
	ob->move(this_player());

	add("book_count", -1);
	

	message_vision("���δ�ʦ�ӻ���ȡ��һ���齻����$N��\n",this_player());
	return "�ðɣ���ס��һ��Ҫ�����ж����飬��������";

}

string ask_yzc()
{
	mapping fam; 
	object me=this_player();
	
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "������")
		return RANK_D->query_respect(this_player()) + 
		"�뱾��������������֪�˻��Ӻ�̸��";

	if (me->query_skill("yizhi-chan",1)<200)
	{
		command("say ���һָ����������200����������ȥ�ɣ�");
		return "";
	}
	if (me->query_skill("buddhism",1)<160)
	{
		command("say �����似��Ҫ�������⣬������ڷ𷨲���160����������ȥ�ɣ�");
		return "";
	}
	command("say ��������˭����\n");
	command("say �����ͷ���ع�\n");
	command("say ������ڹ������\n");
	command("say ��Ħ������Բͨ\n");
	command("buddhism ");
    me->set_temp("yzc/askxuancheng",1);
	
	message_vision("���δ�ʦ˫�ƺ�ʮ����̬��Ȼ��\n",this_player());
	return "�ðɣ�һ�н�ƾ��Ե��ȥ�ɡ�";

}