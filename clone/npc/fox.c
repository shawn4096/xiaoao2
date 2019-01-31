// fox.c

inherit NPC;
#include <ansi.h>

void create()
{
	set_name(HIG"九尾灵狐"NOR, ({ "jiuwei linghu","linghu", "fox" }) );
	set("race", "野兽");
	set("age", 3);
	set("long", "一只浑身红毛的九尾灵狐,一双大眼睛不断眨动，宛如会说话似得。\n");

	set("str", 32);
	set("dex", 1360);
	set_skill("dodge", 1360);
	set("combat_exp", 5360000);
	set("limbs", ({ "头部", "身体", "前脚", "後脚", "尾巴" }) );
	set("verbs", ({ "bite", "claw" }) );

	set("chat_chance", 60);
	set("chat_msg", ({
		(: this_object(), "random_move" :),
		"九尾灵狐冲你摇了摇头。\n",
		"九尾灵狐在远处冲你妩媚的一笑，似乎甚是嘲弄。\n",
		"九尾灵狐对著你摇了摇尾巴，甚是不屑一顾。\n",
		"九尾灵狐用後腿抓了抓自己的耳朵。\n" }) );

	set_temp("apply/attack", 100);
	set_temp("apply/armor", 300);
	setup();
}
/*
int accept_object(object who, object ob)
{
	if( ob->id("bone") ) {
		set_leader(who);
		message("vision", name() + "高兴地汪汪叫了起来。\n", environment());
		return 1;
	}
}*/
int init()
{
	add_action("do_zhuo","zhuo");
	add_action("do_kill","kill");
}

int do_zhuo(string arg)
{
	object me=this_player();
	
	if (!arg||arg!="九尾灵狐")
	{
		return notify_fail("你要捉什么？\n");
	}
	message_vision(HIY"$N伸手试图去捉这只九尾灵狐！\n"NOR,me);
	//只有瑛姑传授经验并指点，才能抓住
	if (random(me->query_dex(1))>30 && me->query_temp("quest/shendiao/大雪风陵渡/yingok"))
	{
		message_vision(HIC"$N一把将抓住九尾灵狐的尾巴，将这只小兽捉住！\n"NOR,me);
		message_vision(HIC"$N谨记瑛姑的教诲，不可轻易杀了这小兽，决定返回后取点血就足够！\n"NOR,me);
		
		me->set_temp("anran/caixue",1);
		//destruct(this_object());
		this_object()->move(me);
		return 1;
	}else message_vision(HIR"九尾灵狐身形敏捷，立即遁走，边走边回头看，挤眉弄眼，甚是嘲弄！\n"NOR,me);
	return 1;
}
//暂时封闭，怕出错
/*
int do_kill()
{
	object me=this_player();
	object ying;
	if (!objectp(ying=present("ying gu",environment(me))))
	{
		ying=new("clone/npc/yinggu");
		ying->move(environment(me));		
	}
	ying->kill_ob(me);

	destruct(this_object());
	return 1;	

}*/