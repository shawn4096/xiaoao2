// guofu.c ��ܽ
// Lklv modify ������� at 2001.10.21

inherit NPC;
string ask_me();

void create()
{
        set_name("��ܽ", ({"guo fu", "guo", "fu"}));
        set("long","�����ǹ��������ص�Ů����ܽ��\n");

        set("gender", "Ů��");
        set("attitude", "peaceful");
        set("unique", 1);

        set("age", 25);
        set("shen_type", 1);
        set("str", 32);
        set("int", 32);
        set("con", 32);
        set("dex", 32);
        set("max_qi", 5500);
        set("max_jing", 5500);
        set("neili", 5500);
        set("max_neili", 5500);
        set("max_jingli", 5500);
        set("eff_jingli", 5500);
        set("jiali", 50);
        set("combat_exp", 1200000);
        set("chat_chance_combat", 40);

        set_skill("bihai-chaosheng", 165);
        set_skill("jieshou-jiushi", 165);
        set_skill("yuxiao-jian", 165);
        set_skill("luoying-zhang", 165);
        set_skill("anying-fuxiang", 165);
        set_skill("lanhua-shou",180);

        set_skill("hand", 165);
        set_skill("literate", 5);
        set_skill("strike", 165);
        set_skill("sword", 165);
        set_skill("parry", 165);
        set_skill("dodge", 165);
        set_skill("force", 165);

        map_skill("force", "bihai-chaosheng");
        map_skill("sword", "yuxiao-jian");
        map_skill("parry", "huifeng-jian");
        map_skill("dodge", "anying-fuxiang");
        map_skill("strike", "luoying-zhang");
        map_skill("hand", "lanhua-shou");
        prepare_skill("hand", "lanhua-shou");
        set("inquiry", ([
                "����" : "ѽ����Ҳ֪���ҵ��������֣�\n",
                "����" : "��������������ˡ�\n",
               // "Ү����" : "�����������ǡ���\n",
               //"���" : "������һֱ��֪������ʵ��Ӧ����ϲ�����ġ�\n",
                //"С��Ů" : "���������ʦ����\n",
                "�򹷰���" : (:ask_me:),
                "����" : "���������ã�����ֲ�֪��������ȥ�ˡ�\n",
        ]));

        setup();
        carry_object(BINGQI_D("changjian"))->wield();
        carry_object(ARMOR_D("changqun"))->wear();
        carry_object(ARMOR_D("xiupao"))->wear();
}
string ask_me()
{
	object me=this_player();
	if (me->query("family/family_name")!="ؤ��")
	{
		command("say ����������ؤ����������Ҵ���ʲô��");
		return "�ߣ�";
	}
	if (!me->query_temp("bangjue/asklu"))
	{
		command("say ����Ȼ��Ϊؤ����ӣ��Ե��ܲ�����ɱ��ȥ��û������������");
		return "�ߣ�";
	}
	command("say ��Ȼ����³�������������������ģ������Լ����ˡ�\n");
	command("giggle "+me->query("id"));
	command("smile "+me->query("id"));
	command("say ����Ͱְ���������������ס�ڳ����������С�\n");
	command("say �������Ҫ��³���ϴ��ڴ򹷰�����Ҫ������һ��ȥ������\n");
	me->set_temp("bangjue/askfu",1);
	return "���ȹ�ȥ����һ��͵�������һ��͵͵����һ������Ȥ!";
}