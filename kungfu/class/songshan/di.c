// di.c 嵩山派第四代弟子 狄修
// Lklv 2001.10.18 Modified

#include <ansi.h>
inherit NPC;
int ask_job();
string ask_fangqi();
string ask_gongji();
string ask_rupai();

inherit F_MASTER;


void create()
{
        set_name("狄修", ({ "di xiu", "di", "xiu" }));
        set("long", "这是一名精壮的汉子，是左冷禅的徒弟。\n");
		set("nickname", "嵩山一鞭");

        set("gender", "男性");
        set("age", 30);
        set("per", 20);
        set("attitude", "heroism");
        set("shen_type", -1);
        set("str", 23);
        set("int", 23);
        set("con", 23);
        set("dex", 24);
        set("unique", 1);

        set("max_qi", 8500);
        set("max_jing", 3000);
        set("eff_jingli", 3000);
        set("jiali", 120);
        set("combat_exp", 1700000);
        set("shen", -70000);
		set_skill("songyang-jue", 120);

		set_skill("force", 200);
		set_skill("hanbing-zhenqi", 200);
		set_skill("dodge", 200);
		set_skill("zhongyuefeng", 200);
		set_skill("hand", 200);
		set_skill("songyang-shou", 200);
		set_skill("parry", 200);
		//set_skill("whip", 200);
		//set_skill("songyang-bian", 200);
		set_skill("literate", 160);

		map_skill("force", "hanbing-zhenqi");
		map_skill("dodge", "zhongyuefeng");
		map_skill("hand", "songyang-shou");
		map_skill("parry", "songyang-shou");
		//map_skill("whip", "songyang-bian");

		prepare_skill("hand", "songyang-shou");

		create_family("嵩山派", 4, "弟子");

		set("class", "songshan");
		set("inquiry", ([
			"工作" :(: ask_job :),
			"门派功绩" :(: ask_gongji :),
			"拜入嵩山" :(: ask_rupai :),

			"放弃" :(: ask_fangqi :),
			"嵩山派" : "我们嵩山派是五岳剑派之首！你初入门可以向万大平师兄学鞭法，也可以向沙天江师兄学刀法\n",
			"五岳剑派" : "我们五岳剑派在武林之中势力巨大，可与少林、武当抗衡。我这一脉主修剑，但非核心弟子不传。\n",
			"左冷禅" : "他就是我们的掌门人，功夫深不可测。\n",
		]) );
		setup();
		carry_object(ARMOR_D("changpao1"))->wear();
		//carry_object(BINGQI_D("changjian"))->wield();
}

string ask_rupai()
{
	int i;
	object me=this_player();
	if (me->query("family/family_name")=="嵩山派")
	{
		command("say 你已经贵为我大嵩山弟子，来骚扰我作甚？\n");
		return "无聊！\n";
	}
	if (me->query("family"))
	{
		command("say 你这种作间隙也太假了吧！\n");
		command("say 别来烦我！\n");
		return "想蒙混过关？！\n";
	}
	if (me->query("combat_exp")>5000)
	{
		command("say 大嵩山要严防奸细，你这么高的经验值来当探子么？！\n");
		return "真弱智，居然想蒙混过关？！\n";
	}
	command("say 既然你想入我大嵩山，我要先看看你的表现，别光说不练！\n");
	command("say 你先替我做几天工作，我安排人去查查你老底，看是否别拍安排进来的奸细！\n");
//	me->set("family/family_name","嵩山派");
	me->set("party/join",1);
	command("say 掌门正在重修封禅台，你若有心就先去搬几块石头！\n");
	
	return "哼，大嵩山必将成为五岳之首！\n";

}

//#include "app4.h";
string ask_gongji()
{
	int i;
	object me=this_player();
	if (me->query("family/family_name")!="嵩山派" && !me->query("party/join"))
	{
		command("say 你这种作间隙也太假了吧！\n");
		command("say 别来烦我！\n");
		return "想蒙混过关？！\n";
	}

	i=me->query("party/gongji");

	command("say "+me->query("name")+"，现在门派中功绩为"+chinese_number(i)+"点贡献值。\n");
	
	return "你如此努力，大嵩山必将成为五岳之首！\n";

}

int ask_job()
{
	object me = this_player();
    if (me->query("family")&&me->query("family/family_name")!="嵩山派")
	{
		
       command("say 你不是我嵩山弟子，哪凉快哪歇着去吧！\n");
       command("sneer");
       return 1;
    }
	if (!me->query("party/join"))
	{
		command("say 你问过我同意你入派了么？\n");
		return 1;
	}
    if (me->query("combat_exp") >= 100000
		&&me->query("job_time/嵩山砌石")<100)
	{
		command("say 你的功夫已经很高了，再做下去我多没面子。\n");
		return 1;
	}
	if (me->query_temp("ss_qs/asked"))
	{
		command("say 你刚才不是问过了吗，怎么还不去？\n");
		return 1;
	}
	if (me->query_condition("job_busy")){
		command("say 你手头还有其他的事吧？过一会再来吧！\n");
		return 1;
	}
	
	me->set_temp("ss_qs/asked",1);
	me->apply_condition("job_busy",4);
	message_vision(HIC"狄修说道：掌门召开英雄会需要修整封禅台，$N速去观胜峰帮忙采石。\n"NOR,me);
	return 1;
}
string ask_fangqi()
{
        object me = this_player();

   //     if(me->query("family/family_name")!="嵩山派")
             // return "你非嵩山派弟子,跑这里瞎嚷嚷什麽?";
        if(!me->query_temp("ss_qs/asked"))
              return "什么放弃？放什么弃？";
        me->delete_temp("ss_qs");
        me->clear_condition("job_busy");
        me->start_busy(1);
        me->apply_condition("job_busy",3+random(3));
        return "好吧，那你就歇会先？";
}

void attempt_apprentice(object ob)
{
	if (!ob->query("quest/ss/rumen/pass"))
	{
		command("say 你有何德何能拜我为师？\n");
		command("say 我又何原何故收你为徒？\n");
		command("say 大嵩山需要忠诚的门徒，你还是先做给我看吧？\n");
		return;
	}
	if(ob->query("shen") > -10000 ){
		command("say 嵩山剑法以狠辣著称（<-100k），你这娘娘腔一看就不够心狠手辣，快滚！");
		return;
	}
	if(ob->query("shen") > -10000 ){
		command("say 嵩山剑法以狠辣著称（<-100k），你这娘娘腔一看就不够心狠手辣，快滚！");
		return;
	}
	if(ob->query("party/gongji") < 200 ){
		command("say 你的门派功绩不够200，别来找我！");
		return;
	}
	command("say 好吧，师傅正要我多培育一些弟子来发扬嵩山派呢。");
	command("recruit " + ob->query("id"));
}
