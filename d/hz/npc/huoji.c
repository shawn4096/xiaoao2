// huoji. ҩ�̻��

inherit NPC;
inherit F_VENDOR;

void create()
{
        set_name("ҩ�̻��", ({ "yaopu huoji", "huoji" }));
        set("str", 20);
        set("gender", "����");
        set("age", 18);
        set("long", "������æµ�ţ�һ���������Ц��ӭ��ǰȥ��\n");
        set("combat_exp", 25000);
        set("attitude", "friendly");
        set("vendor_goods", ({
		(["name": MEDICINE_D("lianzi-wan"),"number":100]),
		(["name": MEDICINE_D("zhengqi-dan"),"number":100]),
		(["name": MEDICINE_D("huangqi"),"number":100]),
		(["name": MEDICINE_D("shouwu"),"number":10]),
		(["name": MEDICINE_D("tenghuang"),"number":100]),
		(["name": MEDICINE_D("xueteng"),"number":10]),
		(["name": MEDICINE_D("yuzhen"),"number":100]),
		(["name": MEDICINE_D("mahuang"),"number":10]),

	}));
        setup();
	carry_object(ARMOR_D("cloth"))->wear();
}

void init()
{
	add_action("do_list", "list");
	add_action("do_buy", "buy");
}
