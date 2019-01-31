
inherit NPC;
inherit F_VENDOR;


void create()
{
        set_name("�ӻ����ϰ�", ({ "lao ban", "laoban" }));
        set("shen_type", 1);

        set("gender", "����");
        set("age", 45);
        set("long",
                "�ϰ������������������ˣ����˼�ʮ���С������\n");
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_temp("apply/damage", 15);

        set("combat_exp", 40000);
        set("attitude", "friendly");
        set("vendor_goods", ({
                    (["name": BOOK_D("quanpu"),"number":1]),
					(["name": BOOK_D("caoshangfei"),"number":1]),

					//(["name": BOOK_D("yeqiuquanpu"),"number":100]),

					(["name": MISC_D("mabudai"), "number": 50]),
					(["name": MISC_D("xionghuang"), "number": 150]),

					(["name": ARMOR_D("beixin"),"number":20])
        }));
        
        setup();
        carry_object(ARMOR_D("cloth"))->wear();
        add_money("silver",1);
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

