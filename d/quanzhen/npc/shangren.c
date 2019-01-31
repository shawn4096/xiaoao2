// waiter.c


inherit NPC;
inherit F_VENDOR;

void create()
{
	set_name("商人", ({"shang ren","shangren" }) );
	set("gender", "男性" );
	set("age", 22);
	set("long", "这位商人正笑咪咪地忙着，迎来送往，还不时拿起挂在脖子上的抹布擦脸。\n");
	set("combat_exp", 100);
	set("attitude", "friendly");
	set("rank_info/respect", "伙计");

	set("vendor_goods", ({
		//(["name": MISC_D("denglong"), "number":10]),
		(["name": MISC_D("fire"), "number":10]),
		(["name": "/d/quanzhen/npc/obj/guijia", "number":1]),
		//(["name": MISC_D("fire"), "number":10]),
	}));

	set("inquiry", ([
	//	"查老学士" : (: ask_me :),
       //	"zhaxueshi" : (: ask_me :),
	]));
	set("per", 15);

	setup();/**/
}
void init()
{
	add_action("do_buy", "buy");
	add_action("do_list", "list");
}
/*
void die()
{
	object ob;
	
	
	if (!query_temp("living"))
	{
		ob = new("/d/quanzhen/npc/shangren");
		
		
		   ob->move("/d/gumu/jishi");
	}
	::die();
}
*/