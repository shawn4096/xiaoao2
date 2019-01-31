// xiaoer2.c �Ƶ�С��
// Lklv 2001.9.28
#include <ansi.h>
inherit WAITER;
inherit F_VENDOR;
string ask_addjiu();

void create()
{
        set_name("����", ({ "pao tang", "paotang", "waiter" }) );
	set("gender", "����" );
	set("age", 22);
	set("long", "��λ������Ц�����æ�ţ�����ʱ������ڲ����ϵ�Ĩ��������\n");
	set("combat_exp", 200);
	set("attitude", "friendly");
        set("rank_info/respect", "���");
	set("vendor_goods", ({
            (["name":FOOD_D("jitui"),   "number":10]),
            (["name":FOOD_D("kaoya"),   "number":10]),
            (["name":FOOD_D("yuebing"), "number":10]),
            (["name":FOOD_D("baozi"),   "number":10]),
            (["name":FOOD_D("jiudai"),  "number":10]),
	}));
	setup();
	set("inquiry", ([
          "ͭ��װ��" : (: ask_addjiu :),
	]) );
        carry_object(ARMOR_D("cloth"))->wear();
        carry_object(ARMOR_D("shoes"))->wear();
}

void init()
{
	object ob;
	mapping myfam;

	ob = this_player();

	::init();
	if (base_name(environment()) != query("startroom")) return;
	if( interactive(ob) && visible(ob) && !is_fighting() ) {
		if ( (myfam = ob->query("family"))
		&& myfam["family_name"] == "ؤ��"
                && ob->query_skill("begging",1) < 40 ){
			remove_call_out("saying");
			call_out("saying", 0, ob);
		}
		else{
			remove_call_out("greeting");
			call_out("greeting", 1, ob);
		}
	}

	add_action("do_buy", "buy");
	add_action("do_list", "list");
}
string ask_addjiu()
{
	object me,gang;
	me=this_player();
	if (!objectp(gang=present("tong gang",environment(me))))
	{
		return "�͹٣��㵹�ǰ�ͭ�׷��°�����û��װ��!\n";
	}
	gang->set("jiu",1);
	me->set_temp("quest/���Ӣ�۴�/�����߹�/zhuangjiu",1);

	message_vision(HIC"���õĴ�Ӧ�ţ������������ͭ��װ���˾ƣ�������˦��һ�����������õ�������л��\n"NOR,me);
	return "��л��Ǯ\n";
}
void greeting(object ob)
{
	object gang;
	if( !ob || environment(ob) != environment() || is_fighting(ob)) return;
	if (objectp(gang=present("tong gang",ob))
		&& ob->query_temp("quest/���Ӣ�۴�/�����߹�/jugang"))
	{
		command("say �ҵ��񰡣���ô���һ��ͭ�ף�����Ȼֱ����ô����!\n");
		command("admire "+ob->query("id"));
		command("say �Ͻ�����������ЪЪ��!\n");
	}
	switch( random(2) ) {
		case 0:
                        say( "����Ц�����˵������λ" + RANK_D->query_respect(ob)
				+ "�������ȱ��裬ЪЪ�Ȱɡ�\n");
			break;
		case 1:
                        say( "�����ò����ϵ�ë��Ĩ��Ĩ�֣�˵������λ" + RANK_D->query_respect(ob)
				+ "����������\n");
			break;
	}
}

void saying(object ob)
{
        if (!ob || environment(ob) != environment() || is_fighting(ob)) return;

        say("\n���ô��һ���������Ҫ���Ľ�����ʲô�� ���ҹ���ȥ��\n\n");
	remove_call_out("kicking");
	call_out("kicking", 1, ob);
}

void kicking(object ob)
{
        if (!ob || environment(ob) != environment()) return;

	ob->move("/d/jiaxing/nanhu");
	message("vision","ֻ����ƹ����һ����" +  ob->query("name") +
		"���˴�С�Ե���һ�����˳������Ǳ���״���ӿ��ˡ�\n", environment(ob), ob);
}
