// tang.c 嵩山派第三代弟子 汤英鹗
// Lklv 2001.10.18 Modified

#include <ansi.h>
inherit NPC;
string ask_job();
string ask_fangqi();

void create()
{
        set_name("汤英鹗", ({ "tang yinge", "tang", "yinge" }));
        set("nickname", HIC"第七太保"NOR);
		set("title","苍髯铁掌");
        set("long", "这是一名瘦削的老者，这是左冷禅的师弟。\n虽说此人武功不高，但极其富有心机。是嵩山的师爷。\n");
        set("gender", "男性");
        set("age", 45);
        set("per", 20);
        set("attitude", "heroism");
		set("class", "songshan");
        set("shen_type", -1);
        set("str", 26);
        set("int", 26);
        set("con", 26);
        set("dex", 27);
        set("unique", 1);

        set("max_qi", 13000);
        set("max_jing", 4000);
        set("eff_jingli", 4000);
        set("jiali", 100);
        set("combat_exp", 4500000);
        set("shen", -15000);
		set_skill("songyang-jue", 120);

		set_skill("force", 350);
		set_skill("hanbing-zhenqi", 350);
		set_skill("dodge", 360);
		set_skill("zhongyuefeng", 360);
		set_skill("hand", 350);
		set_skill("songyang-shou", 350);
		set_skill("parry", 350);
		set_skill("sword", 350);
		set_skill("songshan-jian",350);
		set_skill("literate", 100);

		map_skill("force", "hanbing-zhenqi");
		map_skill("dodge", "zhongyuefeng");
		map_skill("hand", "songyang-shou");
		map_skill("parry", "songshan-jian");
		map_skill("sword", "songshan-jian");

		prepare_skill("hand", "songyang-shou");
		create_family("嵩山派", 3, "弟子");
		set("chat_chance_combat", 10);
		set("chat_msg_combat", ({
					(: perform_action, "sword.feiwu" :),
					(: perform_action, "hand.junji" :),
					//(: perform_action, "hand." :),
					(: exert_function, "hanbing" :),
			}));
		set("inquiry", ([
			"密探" :(: ask_job :),
			//"门派功绩" :(: ask_gongji :),
			//"拜入嵩山" :(: ask_rupai :),

			"放弃" :(: ask_fangqi :),
			"嵩山派" : "我们嵩山派是五岳剑派之首！你初入门可以向万大平师兄学鞭法，也可以向沙天江师兄学刀法\n",
			"五岳剑派" : "我们五岳剑派在武林之中势力巨大，可与少林、武当抗衡。我这一脉主修剑，但非核心弟子不传。\n",
			"左冷禅" : "他就是我们的掌门人，功夫深不可测。\n",
		]) );
			setup();
			carry_object(ARMOR_D("changpao1"))->wear();
			carry_object(BINGQI_D("changjian"))->wield();
			add_money("gold", 1);
}
//武当、少林、华山、恒山、衡山、天龙寺、丐帮、昆仑派、桃花岛、峨嵋派、全真教

string ask_job()
{
	object me,ob;
	string type;
	me=this_player();
	if (me->query("family/family_name")!="嵩山派")
		return "你不是嵩山派弟子，来此作甚？\n";
	if (!me->query("quest/ss/dichuan"))
		return "你非嵩山核心弟子，做不了这工作！\n";
	if (me->query("combat_exp")<200)
		return "你的经验不足2m,无法做这么凶险的任务";
	command("pat "+me->query("id"));
	
	tell_object(me,"左掌门最近忧心忡忡，担心有人破坏五岳剑派联手之势，"+me->query("name")+"就辛苦一趟,替我去打探一番！\n");
	command("say 这个任务比较危险，非心智坚韧之辈无法完成这个工作！\n");
	//type=random(2)?偷听:探查;
	//第一步：先去掌门房间偷听信息
	//第二步：然后根据提示看那人的表现，然后杀掉回来交付令牌。
	ob=new("d/songshan/obj/songyang_ling");
	ob->move(this_object());
	ob->set("owner",me->query("id"));
	
	me->set_temp("ss/jxjob/start",1);
	me->apply_condition("ssjianxi_job",10);
	
	switch (random(1))
	{
		case 0:
			ob->set_temp("ss/jxjob/party","少林派");
			me->set_temp("ss/jxjob/party","少林派");
			ob->set_temp("ss/jxjob/place","/d/shaolin/xctang");
			me->set_temp("ss/jxjob/place","/d/shaolin/xctang");
			tell_object(me,me->query("name")+"，少林派方生大师最近频繁和武当张三丰道长走动，试图不利与我派。\n");
			tell_object(me,me->query("name")+"，现在命令你先去方生大师住处打探一番，看能否发现什么异常。\n");
			message_vision(HIY"$N要记住，如果异常你定要打探清楚，回来报告我，必有重赏！\n"NOR,me);
			me->set_temp("apply/title","少林派第三十五代弟子");
			break;
		case 1:
			ob->set_temp("ss/jxjob/party","华山派");
			me->set_temp("ss/jxjob/party","华山派");
			ob->set_temp("ss/jxjob/place","/d/huashan/zhengqi");
			me->set_temp("ss/jxjob/place","/d/huashan/zhengqi");
			tell_object(me,me->query("name")+"，华山派岳不群这伪君子最近频繁去往洛阳和福州一带，试图不利与我派。\n");
			tell_object(me,me->query("name")+"，现在命令你先去岳不群住处打探一番，看能否发现什么异常。\n");
			message_vision(HIY"$N，如果异常你定要打探清楚，回来报告我，必有重赏！\n"NOR,me);
			break;
	}
	tell_object(me,"我这里有一块掌门令牌，你拿去也好辨认身份，将经过详细记录在上，回来交付与我！\n");
	
	ob->move(me);
	return "一路上危险重重，一定要小心再三！\n";
}
