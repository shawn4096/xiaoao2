// huoji. ҩ�̻��

inherit NPC;
inherit F_VENDOR;

void create()
{
        set_name("ҩ�̻��", ({ "yaopu huoji", "huoji" }));
        set("str", 20);
        set("gender", "����");
        set("age", 18);
        set("long", "����һλ����������æ�Ļ�ơ�\n");
        set("combat_exp", 250);
        set("attitude", "friendly");
        set("vendor_goods", ({
           (["name":__DIR__"obj/lianzi-wan","number":100]),
           (["name":__DIR__"obj/zhengqi-dan","number":100]),
           (["name": MEDICINE_D("liuren-wan"), "number":100]),
		   (["name": MISC_D("xionghuang"), "number":100]),
  
		(["name":MEDICINE_D("jinchuang"),"number": 100]),
		(["name":MEDICINE_D("sanhuang"),"number": 100]),
		(["name":MEDICINE_D("huiyang"),"number": 100]),
		(["name":MEDICINE_D("jys"),"number": 100]),
		(["name":MEDICINE_D("shadansan"),"number": 100]),
		(["name":MEDICINE_D("shouwu"),"number": 100]),
		(["name":MEDICINE_D("xueliandan"),"number": 100]),
		(["name":MEDICINE_D("yangjing"),"number": 100]),
		(["name":MEDICINE_D("xueputi"),"number": 100]),
          }));

        setup();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

