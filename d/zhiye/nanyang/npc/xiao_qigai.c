// qigai.c
// 早期石破天
inherit NPC;
string ask_shaobing();
string ask_name();

#include <ansi.h>

#define XKX_QUEST2 "quest/侠客行/玄铁令/"

void create()
{
	set_name("小乞丐", ({ "xiao qigai","beggar","qigai" }) );
	set("title", "流浪");
//	set("title", "乞丐");
	set("gender", "男性" );
	set("age", 16);
	set("long", "那是一个十二三岁的小叫化子，他已饿了一整天，有气没力的坐在墙角边。\n");

	set("str", 25);
	set("cor", 25);
	set("cps", 25);
	set("int", 25);

	set("max_qi", 500);
	set("max_jing", 100);
	set("neili", 500);
	set("max_neili", 500);
	set("jiali", 50);
	set("shen_type", 0);

	set_temp("apply/attack",  20);
	set_temp("apply/defense", 20);
	set_temp("apply/damage",  20);

	set("combat_exp", 20000);
	set("str", 27);
	set("kar", 100);
	set("thief", 0);
	set("force", 200);
	set("shaobing", 1);

	set("max_force", 200);
	set("force_factor", 2);

	set_skill("unarmed", 50);
	set_skill("sword", 50);
	set_skill("dodge", 80);
	set_skill("parry", 80);
	set_skill("stealing", 100);
	setup();
	set("inquiry", ([
		"name": (: ask_name :),
		 "烧饼": (: ask_shaobing :),
		// "玄铁令": (: ask_shaobing :),
	]));        carry_object("/clone/food/jitui");
        carry_object("/clone/food/jiudai");
	add_money("silver", 10);
}

string ask_name()
{
	object me;
	me=this_player();

	if (!me->query_temp(XKX_QUEST2+"findqigai")) return "我害怕，怕....\n";
	if (me->query_temp(XKX_QUEST2+"askqgname"))
	{
		return "你已经问过了，烦不烦？\n";
	}
	command("say 我叫“狗杂种”\n");
	message_vision(HIY"$N听后心中又气又好笑，喝道，“我不跟你开玩笑，你到底叫啥名字？”\n"NOR,me);
	command("say “狗杂种”");
	me->set_temp(XKX_QUEST2+"askshiname",1);
	//安出来，杀之
	
	call_out("an_come",3+random(4),me);

	return "啊！~~救命啊~！\n";
}

//安再次出现，救护石破天
int an_come()
{
	object me;
	me=this_player();
	message_vision(HIY"\n谁知就在此时，异变突起。\n"NOR,me);
	message_vision(CYN"先前已经死掉的吴道通竟然晃晃悠悠的站了起来，试图一把夺过了小乞丐手中的烧饼。\n"NOR,me);
	message_vision(HIY"吴道通心中大急，目露凶光，对那个小乞丐喝道，“赶紧你给我拿过来！”\n"NOR,me);
	message_vision(HIM"说完，吴道通拿起判官笔，扑向了那个小乞丐，此时，救还是不救？"HIY"(baohu)。\n"NOR,me);
	me->set_temp(XKX_QUEST2+"wucome",1);
	//add_action("do_help","jiuhu");
	return 1;
}



//然后ask 烧饼
string ask_shaobing()
{
	object me,ob;
	me=this_player();
	if (!me->query_temp(XKX_QUEST2+"askshiname")||!me->query_temp(XKX_QUEST2+"helpshi"))
	{
		command("say 我不认识你，这是我的烧饼！！！");
		command("say 你干嘛要抢我的烧饼！");
		return "";
	}
	message_vision(YEL"$N小心翼翼的走到小乞丐的跟前，说道，带有疑惑的心态说道，“这烧饼”？\n"NOR,me);
	command("say 我不能给你，这是我的晚饭，我饿了！");
	command("consider ");
	command("think ");
	message_vision(YEL"小乞丐估计是饿狠了，拿起手中的烧饼一口咬了下去？\n"NOR,me);

	if (me->query_temp(XKX_QUEST2+"haoren")
		&&this_object()->query("shaobing")
		&&!me->query(XKX_QUEST2+"giveshaobing"))
	{

		command("say 方才你救了我，一看就是好人");
		command("say 这位漂亮的妈妈也是好人");
		command("say 你们都是好人");
		this_object()->add("shaobing",-1);
		command("say 好人要有好报的，你方才救了我，这个烧饼就给你吧\n");
		message_vision(CYN"小乞丐恋恋不舍的看了一眼烧饼，咽了下口水，即要将这烧饼递给了$N。\n"NOR,me);
		ob=new("d/nanyang/obj/shaobing");
		ob->set("owner",me->query("id"));
		ob->move(me);
		me->set(XKX_QUEST2+"giveshaobing",1);
		me->set_temp(XKX_QUEST2+"giveshaobing",1);

	}
	return "这个烧饼闻起来就应该很好吃！\n";

}

