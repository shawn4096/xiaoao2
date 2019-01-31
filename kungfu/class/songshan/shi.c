// Npc songshan shi.c 史登达
// Modify by baimo 2000,12,11 for a new job
// shi.c 嵩山派第四代弟子 史登达
// Lklv 2001.10.18 Modified

#include <ansi.h>
inherit NPC;
int ask_job();
string ask_fangqi();
inherit F_MASTER;

void create()
{
        set_name("史登达", ({ "shi dengda", "shi", "dengda" }));
        set("long", "这是左冷禅的徒弟，他是位身材甚高的黄衫汉子。\n");
        set("gender", "男性");
        set("age", 26);
        set("per", 20);
        set("attitude", "heroism");
        set("class", "songshan");
        set("shen_type", -1);
        set("str", 23);
        set("int", 20);
        set("con", 23);
        set("dex", 23);
        set("unique", 1);

        set("max_qi", 8400);
        set("max_jing", 3000);
        set("eff_jingli", 3000);
        set("jiali", 90);
        set("combat_exp", 2700000);
        set("shen", -70000);
		set_skill("songyang-jue", 120);

    	set_skill("force", 220);
    	set_skill("hanbing-zhenqi", 220);
    	set_skill("dodge", 220);
    	set_skill("zhongyuefeng", 220);
        set_skill("hand", 220);
        set_skill("songyang-shou", 220);
    	set_skill("parry", 220);
    	//set_skill("sword", 220);
    	//set_skill("songshan-jian", 220);
		set_skill("songyang-jue", 120);

    	set_skill("literate", 100);

    	map_skill("force", "hanbing-zhenqi");
    	map_skill("dodge", "zhongyuefeng");
        map_skill("hand", "songyang-shou");
    	map_skill("parry", "songyang-shou");
    	//map_skill("sword", "songshan-jian");
        prepare_skill("hand", "songyang-shou");

    	create_family("嵩山派", 4, "弟子");
        set("inquiry", ([
	//	"工作" :(: ask_job :),

	//	"放弃" :(: ask_fangqi :),
		"嵩山派" : "我们嵩山派是五岳剑派之首！\n",
		"五岳剑派" : "我们五岳剑派在武林之中势力巨大，可与少林、武当抗衡。\n",
		"左冷禅" : "他就是我们的掌门人，功夫深不可测。\n",
	]) );
        setup();
        carry_object(ARMOR_D("changpao1"))->wear();
      //  carry_object(BINGQI_D("changjian"))->wield();
}
//砌石任务
/*
int ask_job()
{
	object me = this_player();

    if (me->query("family/family_name")!="嵩山派"&&!me->query_temp("ss/job/qishi") )
	{
		
                command("say 你不是我嵩山弟子，哪凉快哪歇着去吧！\n");
                command("sneer");
                return 1;
    }
    if (me->query("combat_exp") >= 100000){
		command("say 你的功夫已经很高了，再做下去我多没面子。\n");
		return 1;
	}
	if (me->query_temp("ss_qs/asked")){
		command("say 你刚才不是问过了吗，怎么还不去？\n");
		return 1;
	}
	if (me->query_condition("job_busy")){
		command("say 你手头还有其他的事吧？过一会再来吧！\n");
		return 1;
	}
	me->set_temp("ss_qs/asked",1);
	me->apply_condition("job_busy",4);
	message_vision(HIC"史登达说道：掌门召开英雄会需要修整封禅台，$N速去观胜峰帮忙采石。\n"NOR,me);
	return 1;
}

string ask_fangqi()
{
        object me = this_player();

        if(me->query("family/family_name")!="嵩山派")
              return "你非嵩山派弟子,跑这里瞎嚷嚷什麽?";
        if(!me->query_temp("ss_qs/asked"))
              return "什么放弃？放什么弃？";
        me->delete_temp("ss_qs");
        me->clear_condition("job_busy");
        me->start_busy(1);
        me->apply_condition("job_busy",3+random(3));
        return "好吧，那你就歇会先？";
}*/

void attempt_apprentice(object ob)
{
	if (!ob->query("quest/ss/rumen/pass"))
	{
		command("say 你先通过狄修师弟的考验再说！\n");
		command("say 你有何德何能拜我为师？\n");
		command("say 我又何原何故收你为徒？\n");
		command("say 大嵩山需要忠诚的门徒，你还是先做给我看吧？\n");
		return;
	}
	if (ob->query("family/family_name")!="嵩山派")
	{
		command("say 一看就是鬼鬼祟祟之徒，为何到此？\n");
		return;
	}
	if(ob->query("party/gongji") < 1000 ){
		command("say 你的门派功绩不够1000，别来找我！");
		return;
	}
	if(ob->query_skill("hanbing-zhenqi",1) < 120 ){
		command("say 你的寒冰真气太弱了，不足120别来找我！");
		return;
	}
	if(ob->query("shen") > -10000 ){
		command("say 嵩山剑法以狠辣著称（<-100k），你这娘娘腔一看就不够心狠手辣，快滚！");
		return;
	}
	command("say 好吧，师傅正要我多培育一些弟子来发扬嵩山派呢。");
	command("recruit " + ob->query("id"));
}
