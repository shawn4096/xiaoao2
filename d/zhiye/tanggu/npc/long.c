
inherit NPC;
inherit F_VENDOR;

void create()
{
	set_name("����ү", ({ "long sanye", "long", "sanye" }));
	set("shen_type", 1);

	set("gender", "����");
	set("age", 60);
	set("long",
		"���������ۣ�ͷ����ñ��һ�����Ǹ�����֮�ˡ�\n");
	set_skill("cuff", 40);
	set_skill("dodge", 40);
	set_temp("apply/damage", 80);

	set("combat_exp", 25000);
	set("attitude", "friendly");
	set("vendor_goods", ({
                (["name":  "/d/tanggu/obj/fengcai", "number":5]),
                (["name":  "/d/tanggu/obj/jinfo", "number":5]),
                (["name":  "/d/tanggu/obj/yinpan", "number":10]),
       	}));
	
	setup();
	carry_object(ARMOR_D("jinduan"))->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}