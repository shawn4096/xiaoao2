// Npc: /kungfu/class/shaolin/dao-guo.c
// Date: YZC 96/01/19

#include <ansi.h>

inherit NPC;

string ask_me();

void create()
{
	set_name("道果禅师", ({
		"daoguo chanshi",
		"daoguo",
		"chanshi",
	}));
	set("long",
		"他是一位身材高大的中年僧人，两臂粗壮，膀阔腰圆。他手持兵\n"
		"刃，身穿一袭灰布镶边袈裟，似乎有一身武艺。\n"
	);

	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 40);
	set("shen_type", 1);
	set("str", 20);
	set("int", 20);
	set("con", 20);
	set("dex", 20);
	set("max_qi", 400);
	set("max_jing", 300);
	set("neili", 450);
	set("max_neili", 450);
	set("jiali", 40);
	set("combat_exp", 80000);
	set("score", 100);

	set_skill("force", 80);
	set_skill("yijin-jing", 80);
	set_skill("dodge", 80);
	set_skill("shaolin-shenfa", 80);
	set_skill("strike", 80);
	set_skill("banruo-zhang", 80);
	set_skill("parry", 80);
	set_skill("sword", 80);
	set_skill("damo-jian", 80);
	set_skill("buddhism", 80);
	set_skill("literate", 80);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("strike", "banruo-zhang");
	map_skill("sword", "damo-jian");
	map_skill("parry", "damo-jian");

	prepare_skill("strike", "banruo-zhang");

	create_family("少林派", 39, "弟子");

	set("inquiry", ([
		
		"修理"	   : (: ask_me :)
		
	]));

	setup();

        carry_object("/d/shaolin/obj/changjian")->wield();
        carry_object("/d/shaolin/obj/dao-cloth")->wear();
}

void init()
{	
	object me, ob;

	me = this_object();

	::init();
	if( objectp(ob = present("mu ren", environment())) )
	{
		remove_call_out("repairing_1");
		call_out("repairing_1", 5, me, ob);
	}

        if( objectp(ob = present("tong ren", environment())) )
	{
		remove_call_out("repairing_5");
		call_out("repairing_5", 5, me, ob);
	}

        if( objectp(ob = present("jin ren", environment())) )
	{
		remove_call_out("repairing_9");
		call_out("repairing_9", 5, me, ob);
	}
       
}

int repairing_1(object me, object ob)
{
	if ( !present(ob, environment()) ) return 1; 

	command("say 是这个木人吧？ 唔，我来瞧瞧！ 你在边上呆着，看能帮我什么忙。");
	
	remove_call_out("repairing_2");
	call_out("repairing_2", 2+random(3), me, ob);

	return 1;
}

int repairing_2(object me, object ob)
{
	if ( !present(ob, environment()) ) return 1; 

	if( ob->query("damaged") )
	{
		message_vision(GRN "\n道果禅师对着木人瞧了一会，又试着扳动木人的四肢和脑袋，嘴里喃喃念叨着什么。\n\n" NOR, me);
		remove_call_out("repairing_3");
		call_out("repairing_3", 2+random(2), me, ob);
	}
	else
	{
		command("say 这木人好端端地又没坏！ 还大老远地拖着我过来！");
		command("follow none");

		message_vision(GRN "\n道果禅师气鼓鼓地走了。\n" NOR, me);
		me->move("/d/shaolin/twdian");

		remove_call_out("do_back");
		call_out("do_back", random(15), me);
	}

	return 1;
}
	
int repairing_3(object me, object ob)
{
	command("say 唔，原来如此，我来修修看吧！");
	message_vision(GRN "\n他接着从怀里掏出一大堆工具来，打开木人的身体，摆弄了几下。\n\n" NOR, me);

	remove_call_out("repairing_4");
	call_out("repairing_4", 3+random(3), me, ob);

	return 1;
}

int repairing_4(object me, object ob)
{
	if( random(2) == 0 ) 
	{		
		command("say 好，修好了！");
		ob->delete("damaged");
		ob->set("fight_times", 0);	
		message_vision(GRN "\n木人的身体吱吱地扭动了几下，恢复了正常站立的姿态。\n\n" NOR, me);
	}
	else 
		message_vision(GRN "\n道果禅师叹了口气，说道：看来不行，这木人损坏得太厉害了，没法子修了！\n" NOR, me);

	command("say 好，那我走了！");
	command("wave");
	command("follow none");

	message_vision(GRN "\n道果禅师走了出去。\n" NOR, me);
	me->move("/d/shaolin/twdian");

	remove_call_out("do_back");
	call_out("do_back", random(15), me);

	return 1;
}

int repairing_5(object me, object ob)
{
	if ( !present(ob, environment()) ) return 1; 

	command("say 是这个铜人吧？ 唔，我来瞧瞧！ 你在边上呆着，看能帮我什么忙。");
	
	remove_call_out("repairing_6");
	call_out("repairing_6", 2+random(3), me, ob);

	return 1;
}

int repairing_6(object me, object ob)
{
	if ( !present(ob, environment()) ) return 1; 

	if( ob->query("damaged") )
	{
		message_vision(BLU "\n道果禅师对着铜人瞧了一会，又试着扳动铜人的四肢和脑袋，嘴里喃喃念叨着什么。\n\n" NOR, me);
		remove_call_out("repairing_7");
		call_out("repairing_7", 2+random(2), me, ob);
	}
	else
	{
		command("say 这铜人好端端地又没坏！ 还大老远地拖着我过来！");
		command("follow none");

		message_vision(BLU "\n道果禅师气鼓鼓地走了。\n" NOR, me);
		me->move("/d/shaolin/twdian");

		remove_call_out("do_back");
		call_out("do_back", random(15), me);
	}

	return 1;
}
	
int repairing_7(object me, object ob)
{
	command("say 唔，原来如此，我来修修看吧！");
	message_vision(BLU "\n他接着从怀里掏出一大堆工具来，打开铜人的身体，摆弄了几下。\n\n" NOR, me);

	remove_call_out("repairing_8");
	call_out("repairing_8", 3+random(3), me, ob);

	return 1;
}

int repairing_8(object me, object ob)
{
	if( random(2) == 0 ) 
	{		
		command("say 好，修好了！");
		ob->delete("damaged");
		ob->set("fight_times", 0);	
		message_vision(BLU "\n铜人的身体吱吱地扭动了几下，恢复了正常站立的姿态。\n\n" NOR, me);
	}
	else 
		message_vision(BLU "\n道果禅师叹了口气，说道：看来不行，这铜人损坏得太厉害了，没法子修了！\n" NOR, me);

	command("say 好，那我走了！");
	command("wave");
	command("follow none");

	message_vision(BLU "\n道果禅师走了出去。\n" NOR, me);
	me->move("/d/shaolin/twdian");

	remove_call_out("do_back");
	call_out("do_back", random(15), me);

	return 1;
}

int repairing_9(object me, object ob)
{
	if ( !present(ob, environment()) ) return 1; 

	command("say 是这个金人吧？ 唔，我来瞧瞧！ 你在边上呆着，看能帮我什么忙。");
	
	remove_call_out("repairing_10");
	call_out("repairing_10", 2+random(3), me, ob);

	return 1;
}

int repairing_10(object me, object ob)
{
	if ( !present(ob, environment()) ) return 1; 

	if( ob->query("damaged") )
	{
		message_vision(HIY "\n道果禅师对着金人瞧了一会，又试着扳动金人的四肢和脑袋，嘴里喃喃念叨着什么。\n\n" NOR, me);
		remove_call_out("repairing_11");
		call_out("repairing_11", 2+random(2), me, ob);
	}
	else
	{
		command("say 这金人好端端地又没坏！ 还大老远地拖着我过来！");
		command("follow none");

		message_vision(HIY "\n道果禅师气鼓鼓地走了。\n" NOR, me);
		me->move("/d/shaolin/twdian");

		remove_call_out("do_back");
		call_out("do_back", random(15), me);
	}

	return 1;
}
	
int repairing_11(object me, object ob)
{
	command("say 唔，原来如此，我来修修看吧！");
	message_vision(HIY "\n他接着从怀里掏出一大堆工具来，打开金人的身体，摆弄了几下。\n\n" NOR, me);

	remove_call_out("repairing_12");
	call_out("repairing_12", 3+random(3), me, ob);

	return 1;
}

int repairing_12(object me, object ob)
{
	if( random(2) == 0 ) 
	{		
		command("say 好，修好了！");
		ob->delete("damaged");
		ob->set("fight_times", 0);	
		message_vision(HIY "\n金人的身体吱吱地扭动了几下，恢复了正常站立的姿态。\n\n" NOR, me);
	}
	else 
		message_vision(HIY "\n道果禅师叹了口气，说道：看来不行，这金人损坏得太厉害了，没法子修了！\n" NOR, me);

	command("say 好，那我走了！");
	command("wave");
	command("follow none");

	message_vision(HIY "\n道果禅师走了出去。\n" NOR, me);
	me->move("/d/shaolin/twdian");

	remove_call_out("do_back");
	call_out("do_back", random(15), me);

	return 1;
}

int do_back(object me)
{
	me->move("/d/shaolin/twdian");
	return 1;
}

string ask_me()
{
	mapping fam; 
	object ob;

	ob = this_player();
	
	if (!(fam = ob->query("family")) || fam["family_name"] != "少林派")
		return RANK_D->query_respect(ob) + 
		"与本派素无来往，不知此话从何谈起？";

	command("say 打坏了是吧？ 好吧，我跟你去看看。");
	command("follow " + ob->query("id"));

	return "我们走罢！";
}
