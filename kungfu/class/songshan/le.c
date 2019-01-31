// le.c 嵩山派第三代弟子 乐厚
// Lklv 2001.10.18 Modified

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
int ask_here();
int ask_idea();
int ask_yy();
int ask_yy2();
void create()
{
        set_name("乐厚", ({ "le hou", "le", "hou" }));
        set("nickname", HIC"大阴阳手"NOR);
        set("long", "这人矮矮胖胖，面皮黄肿，五十来岁年纪，嵩山派的一名好手。\n");
        set("gender", "男性");
        set("age", 46);
        set("per", 17);
        set("attitude", "heroism");
        set("shen_type", -1);
        set("str", 29);
        set("int", 23);
        set("con", 23);
        set("dex", 23);
        set("unique", 1);

        set("max_qi", 13000);
        set("max_jing", 5000);
        set("eff_jingli", 5000);
        set("jiali", 150);
        set("combat_exp", 6400000);
        set("shen", -130000);
	
		set_skill("songyang-jue", 160);

		set_skill("force", 400);
		set_skill("hanbing-zhenqi", 400);
		set_skill("dodge", 400);
		set_skill("zhongyuefeng", 400);
		set_skill("hand", 480);
		set_skill("songyang-shou", 480);
		set_skill("parry", 400);
		set_skill("sword", 400);
		set_skill("songshan-jian", 400);
		set_skill("literate", 200);
		map_skill("force", "hanbing-zhenqi");
		map_skill("dodge", "zhongyuefeng");
		map_skill("hand", "songyang-shou");
		map_skill("parry", "songyang-shou");
		map_skill("sword", "songshan-jian");
		prepare_skill("hand", "songyang-shou");
		create_family("嵩山派", 3, "弟子");
		set("inquiry", ([
					"here": (: ask_here() :),
					"方法": (: ask_idea() :),
					"大阴阳手": (: ask_yy() :),
				   // "大阴阳手绝技": (: ask_yy2() :),
					"阴阳绝技": (: ask_yy2() :),
			"嵩山派" : "我们嵩山派是五岳剑派之首！\n",
			"五岳剑派" : "我们五岳剑派在武林之中势力巨大，可与少林、武当抗衡。\n",
			"左冷禅" : "他就是我们的掌门人，功夫深不可测。\n",
		]) );
			set("chat_chance_combat", 60);
			set("chat_msg_combat", ({
				(: perform_action, "hand.yinyang" :),
				(: perform_action, "hand.junji" :),
				(: exert_function, "hanbing" :),
				(: exert_function, "juhan" :),
			}));
			setup();
			carry_object(ARMOR_D("changpao1"))->wear();
}

int ask_here()
{
	object me = this_player();

	if (!me->query_temp("ss/zsb_3") || me->query_skill("dodge")<250){
		command("say 这里是大铁梁峡，此处地势险恶，"+RANK_D->query_respect(me)+"您最好不要在此久留！\n若你的基本轻功不足250，下去也是枉然。\n");
		return 1;
	}
	me->delete_temp("ss/zsb_3");
	me->set_temp("ss/zsb_4",1);
	command("say 这里是大铁梁峡，此处地势险恶，谷底奇寒无比，当年我师伯的一条紫松鞭从这里掉下去再也没能找回来。");
	command("whisper "+me->query("id")+" 不过嘛，我倒有一个方法可以下去，不知"+RANK_D->query_respect(me)+"可愿前往？");
	command("whisper "+me->query("id")+" 我提醒你下，谷底奇寒无比，你当小心为上。\n");
	return 1;
}

int ask_idea()
{
	object me = this_player();

	if (!me->query_temp("ss/zsb_4")){
		command("? " + me->query("id"));
		return 1;
	}
	if (me->query_skill("dodge") < 450){
		command("say "+RANK_D->query_respect(me)+"，你的轻功修为太差，恐怕难以下谷。");
		return 1;
	}
	if (me->query_skill("force") < 450){
		command("say "+RANK_D->query_respect(me)+"，峡谷内寒冷异常，你恐怕难与谷内寒气相抗衡。");
		return 1;
	}
	if (me->query("con") < 40){
		command("say "+RANK_D->query_respect(me)+"，峡谷内寒冷异常，你先天根骨不足40,恐怕难与谷内寒气相抗衡。");
		return 1;
	}
	me->delete_temp("ss/zsb_4");
	me->set_temp("ss/zsb_5",1);
	command("whisper "+me->query("id")+" 我嵩山的松枝极其柔软，只需要找几枝松枝，撮成绳，就可以下谷了。");
	return 1;
}

int ask_yy()
{
	object me = this_player();

	if (!me->query("family") || me->query("family/family_name") != "嵩山派"){
		command("say "+RANK_D->query_respect(me)+"，这是我的绝技，但不传外派的。");
		return 1;
	}
	
	if (time()-me->query("quest/ss/sys/yinyang/time")<86400){
		command("say "+RANK_D->query_respect(me)+"，你来的太勤奋了。\n");
		return 1;
	}
	if (me->query_skill("songyang-shou",1) < 250){
			command("say "+RANK_D->query_respect(me)+"，你嵩阳手的功力太弱（<250），恐怕难以学会！\n");
			return 1;
	}
	if (me->query_skill("hanbing-zhenqi",1) < 250){
			command("say "+RANK_D->query_respect(me)+"，你寒冰真气的功力太弱（<250），恐怕难以学会！\n");
			return 1;
	}
	command("say "+RANK_D->query_respect(me)+"，我的大阴阳手绝技，那可是天下武功数一数二的！\n");
	me->set_temp("ss/yy1",1);
	return 1;
}

int ask_yy2()
{
	object me = this_player();
	object ob = this_object();
	int i,j;
	j = 20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	i=random(j);
	
	if (!me->query_temp("ss/yy1")){
		command("say "+RANK_D->query_respect(me)+"，你我无缘无故，这是什么意思？\n");
		return 1;
	}

	if (!me->query("quest/ss/sys/yingyang/pass")){
		if (me->query_skill("songyang-shou",1) < 250){
			command("say "+RANK_D->query_respect(me)+"，你嵩阳手的功力太弱（<250），恐怕难以学会！\n");
			return 1;
		}
		message_vision("$N在$n耳边悄悄说了几句话。\n",ob,me);
		if (i<4
			&&random(me->query("kar"))>23)
		{
			tell_object(me,HIY"乐厚随即将阴阳手的诀窍悉数传授于你，你终于学会了大阴阳手！\n"NOR);
			me->set("quest/ss/sys/yinyang/pass",1);
			me->set("quest/ss/sys/yingyang/time",time());

			log_file("quest/sysyinyang", sprintf("成功，%8s(%8s) 嵩阳手阴阳诀解密失败%d次后，解开阴阳手。经验：%d。\n", me->name(1),me->query("id"),me->query("quest/ss/sys/fail"),me->query("combat_exp")) );
			//return 1;
		}else {

			tell_object(me,HIG"乐厚虽然传授给你很多诀窍，但你还是太笨，领悟不了，解密失败！\n"NOR);

			log_file("quest/sysyinyang", sprintf("失败，%8s(%8s) 嵩阳手阴阳诀解密失败%d次。经验：%d。\n", me->name(1),me->query("id"),me->query("quest/ss/sys/fail"),me->query("combat_exp")) );
			me->add("quest/ss/sys/yinyang/fail",1);
			me->set("quest/ss/sys/yinyang/time",time());

		}
		me->delete_temp("ss/yy1");
		return 1;
	}
	else{
		command("say "+RANK_D->query_respect(me)+"，你已经掌握了大阴阳手绝技的精髓了呀！\n");
		return 1;
	}
}

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
	if(ob->query("party/gongji") < 5000 ){
		command("say 你的门派功绩不够5000，别来找我！");
		return;
	}
	if(ob->query_skill("hanbing-zhenqi",1) < 300 ){
		command("say 你的寒冰真气太弱了，不足300别来找我！");
		return;
	}
	if(ob->query_skill("songyang-shou",1) < 300 ){
		command("say 你的嵩阳手太弱了，不足300别来找我！");
		return;
	}
	if(ob->query("family/generation") <4){
		command("say 你已经拜我师兄为师了，我可不敢收你！");
		return;
	}
	if(ob->query("shen") > -1000000 ){
		command("say 嵩山剑法以狠辣著称（<-1m），你这娘娘腔一看就不够心狠手辣，快滚！");
		return;
	}
	command("say 好吧，师傅正要我多培育一些弟子来发扬嵩山派呢。");
	command("recruit " + ob->query("id"));
}
