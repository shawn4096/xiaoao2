// shagu.c

inherit NPC;

void create()
{
        set_name("����", ({"qu san","qusan","qu"}) );
        set("gender", "����" );
        set("age", 21);
        set("long", "����һ��ȳ�ӣ���������һ�����ȣ������С�Ƶ��ϰ塣\n");

        set("combat_exp", 4500000);
	set("shen", 0);
	set("shen_type", 0);
        set("str", 32);
        set("dex", 18);
        set("con", 18);
        set("int", 10);
	set("max_qi", 4900);
	set("max_jing", 4720);
	set("neili", 15000);
	set("max_neili", 15000);
	set("jiali", 120);

	set_skill("force", 360);
	set_skill("bihai-chaosheng", 360);
	set_skill("dodge", 360);
	set_skill("suibo-zhuliu", 365);
	set_skill("parry", 360);
	set_skill("strike", 380);
	set_skill("luoying-zhang", 380);
	set_skill("qimen-bagua", 130);

	map_skill("force", "bihai-chaosheng");
	map_skill("dodge", "suibo-zhuliu");
	map_skill("strike", "luoying-zhang");
	map_skill("parry", "luoying-zhang");
	prepare_skill("strike", "luoying-zhang");

	//set("rank_info/respect", "С����");
/*
	set("inquiry", ([
		"name": "���Ƕ�������ɵ�á�",
		"rumors": "���ֵܴ��˹ù�һ�ƣ����ֵܾ����ˡ�",
		"here": "������ţ�Ҵ塣",
		"�ù�": "�Ǹ�ɵС�ӽ������ض���",
		"ʦ��": "ʦ�����Ҵ�ȭ�档",
	]) );
	*/
        set("chat_chance", 4);
        set("chat_msg", ({
		"���˲�������\n",
		"ʦ�������д��\n",
		"˭�кõ��ֻ����һ��ؽ��չ�\n",
        }) );
	setup();

        carry_object(ARMOR_D("cloth"))->wear();
      //  carry_object(ARMOR_D("shoes"))->wear();
}

