// xiaoer2.c 酒店小二
// Lklv 2001.9.28
#include <ansi.h>
inherit WAITER;
inherit F_VENDOR;
string ask_addjiu();

void create()
{
        set_name("跑堂", ({ "pao tang", "paotang", "waiter" }) );
	set("gender", "男性" );
	set("age", 22);
	set("long", "这位跑堂正笑咪咪地忙着，还不时拿起挂在脖子上的抹布擦脸。\n");
	set("combat_exp", 200);
	set("attitude", "friendly");
        set("rank_info/respect", "伙计");
	set("vendor_goods", ({
            (["name":FOOD_D("jitui"),   "number":10]),
            (["name":FOOD_D("kaoya"),   "number":10]),
            (["name":FOOD_D("yuebing"), "number":10]),
            (["name":FOOD_D("baozi"),   "number":10]),
            (["name":FOOD_D("jiudai"),  "number":10]),
	}));
	setup();
	set("inquiry", ([
          "铜缸装酒" : (: ask_addjiu :),
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
		&& myfam["family_name"] == "丐帮"
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
		return "客官，你倒是把铜缸放下啊，我没法装酒!\n";
	}
	gang->set("jiu",1);
	me->set_temp("quest/射雕英雄传/江南七怪/zhuangjiu",1);

	message_vision(HIC"跑堂的答应着，立即将这个大铜缸装满了酒，你随手甩了一个银锭给跑堂的算作酬谢！\n"NOR,me);
	return "多谢赏钱\n";
}
void greeting(object ob)
{
	object gang;
	if( !ob || environment(ob) != environment() || is_fighting(ob)) return;
	if (objectp(gang=present("tong gang",ob))
		&& ob->query_temp("quest/射雕英雄传/江南七怪/jugang"))
	{
		command("say 我的神啊，这么大的一口铜缸，您居然直接这么举着!\n");
		command("admire "+ob->query("id"));
		command("say 赶紧放下来，先歇歇！!\n");
	}
	switch( random(2) ) {
		case 0:
                        say( "跑堂笑咪咪地说道：这位" + RANK_D->query_respect(ob)
				+ "，进来喝杯茶，歇歇腿吧。\n");
			break;
		case 1:
                        say( "跑堂用脖子上的毛巾抹了抹手，说道：这位" + RANK_D->query_respect(ob)
				+ "，请进请进。\n");
			break;
	}
}

void saying(object ob)
{
        if (!ob || environment(ob) != environment() || is_fighting(ob)) return;

        say("\n跑堂大喝一声：你这臭要饭的进来干什么？ 给我滚出去！\n\n");
	remove_call_out("kicking");
	call_out("kicking", 1, ob);
}

void kicking(object ob)
{
        if (!ob || environment(ob) != environment()) return;

	ob->move("/d/jiaxing/nanhu");
	message("vision","只听“乒”地一声，" +  ob->query("name") +
		"被人从小吃店里一脚踢了出来，狼狈万状的逃开了。\n", environment(ob), ob);
}
