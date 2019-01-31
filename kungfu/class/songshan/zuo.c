// zuo.c 左冷禅
// Update by looklove at 2000/8/25
// Modify by Looklove for add log_file at 2000/9/1
// Looklove@SJ 2000/10/22 fixed fangqi's bug
// Modified by darken@SJ
// Lklv 2001.10.19 modified
// edit by sohu 2014 12/29
#include <ansi.h>
#include "zuo.h"

inherit NPC;

int do_chaozong();
int do_hanbing();
int do_ask();
int do_cancel();
int do_hanbing();
//int do_chaozong();
int do_hssb();
int do_jueji();
//int think_ssjf();
string ask_times();
string ask_hb();
string ask_grj();



void create()
{
	object ob,ob2,ob3;

	set_name("左冷禅", ({ "zuo lengchan", "zuo", "lengchan" }));
	set("nickname", HIR"五岳盟主"NOR);
	set("long", "嵩山掌门左冷禅更是当今武林中了不起的人物，武功固然出神入化，
		为人尤富机智，机变百出，江湖上一提到“左盟主”三字，无不惕然。\n");
	set("gender", "男性");
	set("age", 52);
	set("per", 20);
	set("attitude", "heroism");
	set("class", "songshan");
	set("shen_type", -1);
	set("str", 29);
	set("int", 28);
	set("con", 28);
	set("dex", 28);
	set("unique", 1);
	set("no_bark",1);

	set("max_qi", 29500);
	set("max_jing", 8000);
	set("eff_jingli", 8000);
	set("jiali", 200);
	set("combat_exp", 13000000);
	set("shen", -180000);
	set("max_neili", 26000);
	set("neili", 26000);

	set_skill("literate", 220);
	set_skill("songyang-jue", 220);
	set_skill("force", 500);
	set_skill("dodge", 500);
	set_skill("hand", 500);
	set_skill("strike", 500);
	set_skill("parry",500);
	set_skill("sword", 500);
	set_skill("songshan-jian", 500);
	set_skill("songyang-shou", 500);
	set_skill("zhongyuefeng", 500);
	set_skill("hanbing-shenzhang", 500);
	set_skill("hanbing-zhenqi", 500);

	map_skill("force", "hanbing-zhenqi");
	map_skill("dodge", "zhongyuefeng");
	map_skill("hand", "songyang-shou");
	map_skill("parry", "songshan-jian");
	map_skill("sword", "songshan-jian");
	map_skill("strike", "hanbing-shenzhang");
	prepare_skill("strike", "hanbing-shenzhang");
	set("inquiry", ([
		"job": (: do_ask() :),
		"任务": (: do_ask() :),
		"cancel": (: do_cancel() :),
		"放弃": (: do_cancel() :),
		"这个": (: ask_hb() :),
		"功劳": (: ask_times() :),

		"观日剑": (: ask_grj() :),
		"万岳朝宗": (: do_chaozong() :),
		"寒冰真气": (: do_hanbing() :),
        "华山石壁": (: do_hssb() :),
		"嵩山剑法绝技": (: do_jueji() :),

	]));
	create_family("嵩山派", 3, "掌门人");
	set("chat_chance_combat", 20);
	set("chat_msg_combat", ({
		(: perform_action, "sword.longfeng" :),
		(: perform_action, "sword.feiwu" :),
		(: perform_action, "strike.hanbing" :),
		(: exert_function, "juhan" :),
		(: exert_function, "hanbing" :),
	}));
	setup();
	if (clonep()) {
		ob = unew(BINGQI_D("sword/guanri-jian"));
		ob2 = unew(("d/meizhuang/obj/shuaiyitie"));
		ob3 = unew(("d/meizhuang/obj/lingqi"));
		ob2->move(this_object());
		ob3->move(this_object());
		if (!ob) ob = unew(BINGQI_D("gangjian"));
		ob->move(this_object());
		ob->wield();
		carry_object(ARMOR_D("changpao1"))->wear();
		carry_object(MEDICINE_D("tianwang"));
	}
	add_money("gold", 1);
}

void attempt_apprentice(object ob)
{
	if(ob->query("shen") > -2000000){
		command("say 我最瞧不起岳不群那样的伪君子，还是把你那点假道学收敛一下吧(神-2m)。\n");
		return;
	}
	if (!ob->query("quest/ss/dichuan"))
	{
		command("say 你尚未获得嫡传弟子身份，还不赶快去悔过！\n");
		return;
	}
	if(ob->query_skill("hanbing-zhenqi",1) < 350 ){
		command("say 你的武功还不够娴熟，再回去练练吧。");
		return;
	}

    if(ob->query("job_time/嵩山") < 300) {

	    command("say 你自从入我派以来，偷懒耍滑，不务正业，还想拜我为师？做足300次任务再说");
		return;
    }
	if (ob->query("family/master_id")=="zuo lengchan")
	{
		command("say 你已经拜我为师了，还啰嗦啥？\n");
		ob->set("title", HIC"五岳盟主亲传弟子"NOR);
		return;

	}
    command("say 好，我正想找些优秀弟子来亲自传授武功，看来你还不错嘛。");
	command("recruit " + ob->query("id"));
	ob->set("title", HIC"五岳盟主亲传弟子"NOR);
}

void init()
{
	object ob;
	ob = this_player();

	::init();
	if( interactive(ob = this_player()) && !is_fighting() && !is_busy()
	   && ob->query_temp("quest/family") == "嵩山派"
	   && ob->query_temp("quest/type") == "请") {
		remove_call_out("greeting");
		call_out("greeting", 2, ob);
	}
}

void greeting(object me)
{
	object target, ob;
	mapping quest;

	if( !me || environment(me) != environment() || !living(me)) return;

	if (!mapp(quest = me->query_temp("quest")) || quest["type"] != "请"
	|| !stringp(quest["id"])) return;

	command("nod "+me->query("id"));

	ob = this_object();

	if(objectp(target=present(quest["id"], environment(me)))
	  && target->query_temp("songshan_job") == me
	  && living(target)){
		me->add_busy(2);
		target->set_leader(0);
		command("haha");
		command("touch "+target->query("id"));
		command("say "+target->name()+"能来，我嵩山派又多了一份力量啦！哈哈！");
		call_out("done", 3, target, me, quest, 1);
		return;
	}
}

void done(object target, object me, mapping quest, int i)
{
       int count,exp,pot;

       if(me && i >= 0){
		if(target){
			message_vision("\n$N点头道："+me->name()+"这娃娃不赖，让我指点他几招，就当是迟来的见面礼吧！\n", target, me);
			tell_room( environment(me), target->name() + "在" + me->name()+ "耳边小声地说了些话。\n", ({ me, target }) );
			// give rewards.
			TASK_D->give_reward(me, me->query_temp("quest"), -1, ABS(me->query("job_time/嵩山")/100) , this_object(), "嵩山" );
			me->add("job_time/嵩山", 1);
			//GIFT_D->check_count(me,this_object(),"嵩山");
			if (random(me->query("job_time/嵩山"))>800&&random(me->query("kar"))>25 && !me->query("quest/ss/dichuan") && me->query("family/family_name")=="嵩山派")
			{
				message_vision("$N在"+me->query("job_time/嵩山")+"次嵩山请人任务中获得左冷禅的认可！把你当做核心弟子看待。\n",me);
				me->set("title",YEL"五岳盟主嫡传弟子"NOR);
				me->set("quest/ss/dichuan",1);
			}
			if (me->query("quest/ss/dichuan"))
			{
				
				me->set("title",YEL"五岳盟主嫡传弟子"NOR);
			}
			if ( me->query("family/family_name") == "嵩山派"
			&& me->query_skill("hanbing-zhenqi",1))
				me->improve_skill("hanbing-zhenqi",me->query("int")*2);
							
			count = me->query("job_time/嵩山");
			
			if (count<1) count=1;
			pot= me->query_temp("quest/pot_reward");
			exp= me->query_temp("quest/exp_reward");
			
			log_file("job/songshan",sprintf("%8s%-10s第%4d次嵩山请人任务获得%3d点经验，%2d点潜能，经验：%d\n",
				me->name(),"("+me->query("id")+")",count,exp,pot,me->query("combat_exp")),me);
			
			me->delete_temp("quest");
			me->delete_temp("songshan_job");
			me->clear_condition("job_busy");
			me->set("job_name", "嵩山并派");
			tell_room(environment(target), target->query("name")+"大笑两声，在知客弟子带领下到厢房休息去了。\n", ({target}));
			if(target->return_home()){
				target->delete_temp("songshan_job");
				target->delete_temp("last_lost_to");
				target->clear_condition("songshan_busy");
				target->set("chat_chance", target->query("chat_c"));
				if(!target->query_temp("location"))
				target->delete("location");
				target->set_leader(0);
				target->reincarnate();
			}
			else destruct(target);
		}
	}
	else if(target){
		tell_room(environment(target), target->query("name")+"大笑两声，在知客弟子带领下到厢房休息去了。\n", ({target}));
		destruct(target);
	}
}

int do_hanbing()
{
	object me=this_player();
	if (me->query("family/family_name") !="嵩山派")
	{
		command("say 你不是我派弟子，来此作甚？\n");
		return 1;
	}
	if (me->query("family/master_name") !="左冷禅")
	{
		command("say 你不是我的弟子，来此作甚？\n");
		return 1;
	}
	if (!me->query("quest/ss/dichuan"))
	{
		command("say 你不够忠诚，只有亲传弟子才能获得嵩山派无上内功心法\n你还是替我多去邀请各路英雄豪杰吧。\n");
		return 1;
	}
	if (me->query_skill("hanbing-zhenqi",1) <450)
	{
		command("say 你的寒冰真气尚未大飞（450），去了也是找死？\n");
		return 1;
	}
	if (me->is_busy())
	{
		command("say 你现在太忙了？\n");
		return 1;

	}
	if (me->query("quest/ss/hbzq/pass") )
	{
		command("say 你已经将寒冰真气融会贯通，无需再去那儿了。\n");
		me->set("title",HBBLU+HIW"寒冰真气传人"NOR);
		return 1;
	}
	if (me->query("con")<40 )
	{
		command("say 你的先天根骨不够40，还是继续修炼吧。\n");
		return 1;
	}
	if (time()-me->query("quest/ss/hbzq/time")<86400 )
	{
		command("say 你来的太频繁了。\n");
		return 1;
	}
	command("pat "+me->query("id"));
	command("look "+me->query("id"));
	command("say 我嵩山派有两大神功，享誉江湖，一为寒冰真气,二为嵩山剑法。\n");
	command("say 既然你问到这寒冰真气，而且如此忠心耿耿，我就告诉你咱门派中的一个大秘密。\n");
	command("say 寒冰真气乃是我派至高心法，既然你要想学，我就告诉你，看你是否有这个机缘了。\n");
	command("say 为师当初受祖师爷眷顾，就是在哪儿领悟了寒冰真气的奥秘。\n");
	command("say 那处极寒之地乃是大铁梁峡下面的一处深谷中，极其危险，你若去当处处小心，备好应急之物，\n");
	command("say 你听好了，抵御寒气的法门是如此这般这般，你去试试吧，能否成功看你的毅力了。\n");
	command("say 关于地址么，这个，这个，这个.....\n");
	command("consider ");
	command("whisper "+me->query("id"));
	command("look "+me->query("id"));
	me->set_temp("hbzq/askzuo",1);
	/*
	if (me->query("quest/ss/hbzq/thinking"))
	{
		message_vision(HIC"$N大袖一挥，以绝大功力将$n送到谷底!\n"NOR,this_object(),me);
		me->move("d/songshan/gudi");

	}*/
	return 1; 
   
}