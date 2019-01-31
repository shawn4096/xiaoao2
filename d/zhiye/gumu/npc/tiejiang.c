// tiejiang.c 铁匠

inherit NPC;
inherit F_VENDOR;
int ask_me(); 
 
void create()
{
	set_name("孙铁匠", ({ "sun tiejiang", "sun", "tiejiang" }) );
	set("gender", "男性" );
	set("age", 34);
	set("long", "这是一位位正在抡着大铁锤，叮叮当当的打铁的铁匠。\n");
	set("combat_exp", 30000);
	set("attitude", "peaceful");
	set("rank_info/respect", "铁匠");
	set("vendor_goods", ({
		(["name":"d/suzhou/npc/obj/changjian","number":15]),
		(["name":"d/suzhou/npc/obj/gangjian","number":20]),
		(["name":"d/suzhou/npc/obj/gangdao","number":15]),
		(["name":"d/suzhou/npc/obj/caidao","number":10]),
		(["name":"d/suzhou/npc/obj/tiechui","number":10]),
		(["name":"d/suzhou/npc/obj/bishou","number":10])
	}));
	set("inquiry", ([
		"药锄": (: ask_me :),
		//"锄头": "锄头... 抱歉，锄头已经卖光了...", 
	]));
	setup();
	carry_object(ARMOR_D("cloth"))->wear();
}

void init()
{       
	object ob;

	::init();
	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
	add_action("do_buy", "buy");
	add_action("do_list", "list");
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	switch( random(2) ) {
		case 0:
			say( "铁匠笑咪咪地说道：这位" + RANK_D->query_respect(ob) + "，这里只要是铁的家伙，应有尽有。\n");
			break;
		case 1:
			say( "铁匠笑呵呵地说：这位" + RANK_D->query_respect(ob) + "，您想要点什么？\n");
			break;
	}
}

int ask_me()
{
	object chu, me, ob;

	me = this_object();
	ob = this_player();
    if (ob->query("family/family_name")!="全真教"||!ob->query_temp("qz/caiyao"))
    {
		command("heng "+ob->query("id"));
		command("say 药锄我倒是有，凭什么要给你？！\n");
		return 1;
    }     
	if ( present("yao chu", ob) ) {
		command("say 你不是有了吗，还想要什麽？\n");
		return 1;
	}
	command("look " + ob->query("id")); 
	command("say 既然是全真教鹿道长所指示，那就好！\n");

	command("say 这里正好有一把铁锄没什麽用，你要就拿去吧。\n");
	chu = new("/d/quanzhen/obj/yaochu");
	chu->set("no_sell", 1);
	chu->move(ob);
	message_vision("$N给了$n一把挖药专用的药锄。\n", me, ob);
	ob->start_busy(1);

	return 1;
}
