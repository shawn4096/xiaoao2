// lingqing jushi.c (雪山飞狐)
// By sohu
inherit NPC;
inherit F_MASTER;
#include <ansi.h>
string ask_anjin();
string ask_jiuwen();

void create()
{
	set_name("灵清居士", ({ "lingqing jushi", "lingqing" , "jushi"}));
	set("title", "昆仑派长老");
        set("nickname", HIC"雪溅清凉"NOR);
	set("long",
		"她就是昆仑派长老、名扬江湖的昆仑名宿灵清居士,因清凉扇和三阴手名闻天下。\n"
		"虽然年纪已大，但仍然看得出她年轻时的容貌极为秀丽。\n");
	set("gender", "女性");
	set("age", 40);
	set("attitude", "heroism");
	set("shen_type", -1);
	set("str", 25);
	set("int", 25);
	set("con", 25);
	set("dex", 25);

	set("max_qi", 33500);
	set("max_jing", 7000);
	set("neili", 29000);
	set("max_neili", 29000);
	set("eff_jingli", 7000);
	set("jiali", 200);
	set("combat_exp", 12500000);
	set("score", 4000);
	set_skill("art", 200);
    set_skill("literate", 250);
	set_skill("force", 500);
	set_skill("xuantian-wuji", 500);
	set_skill("dodge", 500);
	set_skill("taxue-wuhen", 500);
	set_skill("parry", 500);
	set_skill("brush", 500);
	set_skill("blade", 500);

	set_skill("liangyi-jue", 200);
	set_skill("qingliang-shan", 500);
	set_skill("hand", 500);
	set_skill("sanyin-shou", 500);
	set_skill("leg", 500);
	set_skill("chuanyun-tui", 500);
	set_skill("throwing", 500);

	map_skill("force", "xuantian-wuji");
	map_skill("leg", "chuanyun-tui");
	map_skill("dodge", "taxue-wuhen");
	map_skill("hand", "sanyin-shou");
	map_skill("parry", "qingliang-shan");
	map_skill("brush", "qingliang-shan");
	map_skill("throwing", "sanyin-shou");
	map_skill("blade", "qingliang-shan");


	prepare_skill("hand", "sanyin-shou");
	prepare_skill("leg", "chuanyun-tui");

	set("chat_chance_combat", 70);
	set("chat_msg_combat", ({
  		(: perform_action, "throwing.xuejian" :),
  		(: perform_action, "hand.sanyin" :),
		(: perform_action, "leg.chuanyun" :),
	//	(: perform_action, "hand.sanyin" :),
		//(: perform_action, "leg.chuanyun" :),

		(: exert_function, "wuji" :),			
  		(: perform_action, "dodge.taxue" :),
	}));
    create_family("昆仑派", 2, "门中长老");
	set("class", "taoist");

	set("inquiry", ([
		"飞雪四溅绝技" : (: ask_anjin :),
		"旧闻往事" : (: ask_jiuwen :),
		//"苏习之" : (: ask_su :),
		//"追杀" : (: ask_ding :),
	]));

	setup();
	carry_object(BINGQI_D("bqsm_ding"))->wield();
	carry_object("/d/kunlun/obj/pao2.c")->wear();

}
//接受东西
string ask_jiuwen()
{
	object me;
	me=this_player();
	if (me->query("family/family_name")!="昆仑派")
	{
		command("say 你非昆仑弟子，来此作甚？");
		return "哼！\n";

	}
	if (me->query("gender")!="女性")
	{
		command("say 你并非女性，来此作甚？");
		return "哼！\n";
	}
	if (me->query_skill("sanyin-shou",1)<350)
	{
		command("say 你三阴手不足350，如此偷懒，还指望清凉扇？");
		return "哼！\n";
	}
	if (me->query_skill("xuantian-wuji",1)<350)
	{
		command("say 你玄天无极不足350，如此偷懒，还指望清凉扇？");
		return "哼！\n";
	}
	if (me->query_temp("qls/askjiuwen"))
	{
		command("say 我已经跟你说了那些旧闻往事，为何不敢进去？");
		return "哼！\n";
	}
	if (me->query_skill("qingliang-shan",1)>1)
	{
		command("say 你已经学得了清凉扇绝技，还来啰嗦什么？");
		return "哼！\n";
	}
	command("say 这清凉扇原本是本派旁支三因观的绝技！\n");
	command("say 后来当时清凉扇传人朱子柳风云际会拜南帝一灯大师为师。\n");
	command("say 这门绝技也基本失传，实乃本门重大损失，我心中也留下极大遗憾！\n");
	command("say 你若有心就替我跑一趟大理，去问问朱子柳，看他是否愿意归还本门绝技？\n");
	me->set_temp("qls/askjiuwen",1);
	return "唉！\n";
}
int accept_object(object who,object obj)
{
//如果身份不同奖励不同

	if (who->query("quest/kl/qls/pass")
		&&obj->query("id")=="qingliang miji"
		&&obj->query("owner")==who->query("id"))
	{
		command("haha "+who->query("id"));
		command("say 你能将"+obj->query("name")+"给我找回来，我非常高兴！\n");
		command("pat "+who->query("id"));
		command("say 这说明你很有孝心，我很看好你！\n");
		command("say 你有什么想法就跟我说吧！\n");
		destruct(obj);
		who->set("quest/kl/qls/baishi",1);
		return 1;
	}	

	return 0;
}

void attempt_apprentice(object ob)
{
	if(ob->query("gender")=="男性"){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"你们这些臭男人我见了就烦，快给我走开！");
		return;
	}
	if(ob->query("appren_hezudao", 1) == 1) {
		command("say "+RANK_D->query_respect(ob)+"怎敢开这等玩笑，你已经拜了何足道祖师为师，真是折杀我了。");
		return;
	}  
	if(ob->query_skill("xuantian-wuji",1) < 350){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"你的玄天无极功不足350,我可不想收你。");
		return;
	}
		if(ob->query_skill("chuanyun-tui",1) < 350){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"你的穿云腿太差,不足350级别，我可不想收你。");
		return;
	}
	if(ob->query_skill("taxue-wuhen",1) < 350){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"你的踏雪无痕太差,不足350级别，我可不想收你。");
		return;
	}
	if(ob->query_skill("sanyin-shou",1) < 350){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"你的三阴手太差,不足350级别，我可不想收你。");
		return;
	}
	if (!ob->query("quest/kl/qls/pass")||!ob->query("quest/kl/qls/baishi"))
	{
		command("say 你我无缘无故，为何要来烦我！\m");
		return;
	}

	command("say 好吧，以后你就跟我学武功吧，你须得安心学艺，不可乱来。");
	command("recruit " + ob->query("id"));
	ob->set("title",HIC"昆仑派灵清居士传人"NOR);
	return;
}


//飞雪四溅

string ask_anjin()
{
	object me;
	int i,j;
	me=this_player();
	if (me->query("family/family_name")!="昆仑派")
	{
		return "你的不是昆仑派，难道不怕死么？！\n";
	}
	if (!me->query("quest/kl/dichuan"))
	{
		return "你竟然不是昆仑嫡传弟子？！\n";
	}
	if (me->query_skill("sanyin-shou",1)<250)
	{
		return "你的三阴手等级不足250，告诉你也没用！\n";
	}
	if (me->query("quest/kl/sys/xuejian/pass"))
	{
		return "你的三阴手“飞雪四溅”已经解开了！\n";
	}
	if (time()-me->query("quest/kl/sys/xuejian/time")<86400)
	{
		return "你来的太频繁了，明天再来！\n";
	}

	message_vision(HIC"$N严肃的看着$n，慢慢说道：“我派的三阴手讲究的轻灵路线，和其他门派的硬功都不太相同。\n"
						"这功夫本是我俗家的武技，后来观悟昆仑风云变幻所创，既然你如此感兴趣，我就演示，看你自己的悟性了。\n"+
				   HIR"\n\n\n$N纵身跃起，将三阴手飞雪四溅的诀窍演示给$n看。\n"NOR,this_object(),me);
	
 
    i = 20;
      if(me->query("m-card-vip")) i =  18;
      if(me->query("y-card-vip")) i =  15;
      if(me->query("buyvip"))     i =  10;
      i=random(i);
	j=random(me->query("kar"));
	command("say 你看懂了么。\n");
	command("pat "+me->query("id"));
	if( i<6
		&& me->query("kar")<31
		&& j >= 23 ) 
	{
		tell_object(me,HIY"\n你听了的灵清居士的亲自指点，联想起早期自己所用三阴手的种种心得，两下印照。\n"NOR);
		tell_object(me,HIG"\n你运气冲关，忽然寸关穴一痛，一股劲气若隐若现，如臂使指，灵活无比。\n"			    
						 +"你终于领悟了这门三阴手飞雪四溅的运用法门。心中大喜。\n"NOR);
		me->set("quest/kl/sys/xuejian/pass",1);
		log_file("quest/klxuejian", sprintf("%8s(%8s) 失败%d次后，学到三阴手飞雪四溅绝技,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/kl/sys/xuejian/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));		
		
		return "恭喜解密三阴手飞雪四溅绝技绝技成功!\n";
		
	}	
   else
	{
		log_file("quest/klxuejian", sprintf("%8s(%8s) 解密三阴手飞雪四溅绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/kl/sys/xuejian/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"你听了灵清居士的指点，可是对三阴手飞雪四溅绝技的奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/kl/sys/xuejian/fail",1);
		me->set("quest/kl/sys/xuejian/time",time());
		me->start_busy(1+random(3));
		
		return "非常遗憾解密三阴手飞雪四溅绝技失败"+me->query("quest/kl/sys/xuejian/fail")+"次。\n";
	}


}