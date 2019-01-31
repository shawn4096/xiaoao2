// tiejiang.c 铁匠
#include <ansi.h>

inherit NPC;
inherit F_VENDOR;
string ask_name();
 
void create()
{
	set_name("铁匠", ({ "tie jiang", "tie", "jiang" }) );
	set("gender", "男性" );
	set("age", 34);
	set("long", "这是一位位正在抡着大铁锤，叮叮当当的打铁的铁匠。\n");
	set("combat_exp", 30000);
	set("attitude", "peaceful");
	set("rank_info/respect", "铁匠");
	set("vendor_goods", ({
		(["name":__DIR__"obj/changjian","number":15]),
		(["name":__DIR__"obj/gangjian","number":20]),
		(["name":__DIR__"obj/gangdao","number":15]),
		(["name":__DIR__"obj/caidao","number":10]),
		(["name":__DIR__"obj/tiechui","number":10]),
		(["name":__DIR__"obj/bishou","number":10])
	}));
	set("inquiry", ([
		//"name" : "本人姓王，打小就住在苏州城，你想问啥？\n",
		//"rumors" : "我爹被朝廷拉去修运河，他老人家身子骨不好，前些天不幸逝去了。\n",
		//"here" : "这里是城里唯一的打铁铺了，什么人都到我这里来打东西。\n",
		"name": (: ask_name :),
		//"玄铁令": "锄头... 抱歉，锄头已经卖光了...", 
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


string ask_name()
{
	object me,obj;
	me=this_player();

	if (!me->query_temp("quest/侠客行/玄铁令/start"))
	{
		command("say 我根本就不认识你，别来烦我？\n");
		command("heng");
		return "真是奇怪，我发现最近有不少陌生人出现在本镇！\n";
	}

	command("say 哼，既然被你们知道了，那就别怪我心狠手辣了！？\n");
	message_vision(HIR"吴道通忽然抓起火炉旁边的一个烧饼，朝$N扔了过来！\n"NOR,me);
	message_vision(HIY"\n$N手轻轻一拨这块烧饼落到大街上去，吴道通随即一步越出门外，向外窜去！\n"NOR,me);
	me->set_temp("quest/侠客行/玄铁令/findwu",1);
	message_vision(CYN"\n\n\n你刚想向外冲去，这时，忽然从屋外窜进来一个强盗来！\n"NOR,me);
	message_vision(HIR"\n大声喝道，“在我黑风寨的地盘上竟然有人作恶，纳命来！”！\n"NOR,me);
    me->add_busy(1);
	obj=new("d/lanzhou/npc/heiyiren");
     obj->set("kill_id",me->query("id"));
	 obj->set_name("喽啰", ({ "lou luo", "louluo", "lou" }) );	 
	 obj->set("title", "黑风寨喽啰");
     obj->move(environment(me));
	 obj->kill_ob(me);
	
	return "";
}
