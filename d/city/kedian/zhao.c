#include <ansi.h>
#include <job_mul.h>
//inherit F_MASTER;

inherit NPC;
int ask_job();
int ask_finish();
int ask_quit();
int ask_cure();
int ask_zhang();
int ask_zhou();
int ask_xie();
int ask_jinmao();
int ask_gmd();
int accept_object(object who, object ob);

object ppl;

void create()
{
	set_name("赵敏", ({ "zhao min", "zhao", "min" }));
	set("gender", "女性");
	set("long", "这是蒙古汝阳王的长女赵敏，长得如花似玉，美人中的极品。\n");
	set("age", 18);
	set("str", 20);
	set("int",35);
	set("con",20);
	set("dex",30);
	set("per",45);
	set("no_get", 1);
	set("combat_exp", 5000000);
	set("attitude", "friendly");
	set("max_qi",12000);
	set("max_jing",4000);
	set("neili",12000);
	set("max_neili",12000);
	set("qi",12000);
	set("jing",4000);
	set("jingli",4000);

	set_skill("force", 300);
	set_skill("dodge", 300);
	set_skill("parry", 300);
	set_skill("literate", 300);

	set("inquiry", ([
//                "工作": (: ask_job :),
		"完成": (: ask_finish :),
		"退出": (: ask_quit :),
		"解药": (: ask_cure :),
		"周芷若": (: ask_zhou :),
		"张无忌": (: ask_zhang :),
		"谢逊": (: ask_xie :),
		"金毛": (: ask_jinmao :),
		"围攻光明顶": (: ask_gmd :),
	]) );

	setup();
	carry_object(ARMOR_D("wcloth"))->wear();
	carry_object(ARMOR_D("pixue"))->wear();
}

void init()
{
	::init();
	add_action("do_quit", "abandon");
}

int ask_job()
{
	object me = this_player();
	int  exp;
	object where, target, *list;

	exp = me->query("combat_exp");
	if (me->query_temp("zhao")){
		command("say 快去找人呀！");
		return 1;
	}
	if (exp < 500000) {
		command("say 你武功太差啦。\n");
		return 1;
	}
	if (me->query("potential") > me->query("max_pot")){
		command("say 请先去发掘你的潜能吧，如此才能事半功倍。");
		command("giggle");
		return 1;
	}
	if( me->query_condition("job_busy")){
		command("say 暂时我没有什么有兴趣的武功。\n");
		return 1;
	}
	ppl = me;
	list = filter_array(users(), (:
    	    $1->query("combat_exp")/3 > ppl->query("combat_exp")/4
    	 && $1->query("combat_exp")/5 < ppl->query("combat_exp")/4
    	 && !wizardp($1)
    	 && $1->query_temp("user_type") != "worker"
    	 && query_idle($1)<120
    	 && !$1->query("menggu")
    	 && environment($1)
    	 && !$1->query_temp("caught")
    	 && !$1->query_temp("pigging_seat")
    	 && $1->query("duanzhi")<10
    	 && !$1->query_condition("ruanjin_poison")
    	 && $1->query("family")
    	 && query_ip_number($1) != query_ip_number(ppl)
   	 && !$1->query_condition("relax")
    	 && !$1->query_condition("wuguan_job")
	 && !$1->query_condition("killer")
    	:));
	list -= ({me,0});

	if(sizeof(list) < random(10)+1) {
		command("say 现在没什么高手，算了吧。\n");
		return 1;
	}

	target = list[random(sizeof(list))];
	if (target->query_temp("zm_job_time") > uptime()) {
		command("say 现在没什么高手，算了吧。\n");
		return 1;
	}
	target->set_temp("zm_job_time", uptime() + 3600);
	where = environment(target);
	me->set_temp("zhao/target",target->query("name"));
	me->set_temp("zhao/targetid",target->query("id"));
	me->apply_condition("job_busy", 4 + random(2));
	command("say 我想学点" + target->query("family/family_name") + "的武功，你帮我去抓个人来好吗？");
	command("wink");
	command("whisper " + me->query("id") + " 请到" HIR+ where->query("short") + CYN"带"HIW
	+ target->query("name") + HIY"(" + target->query("id") + ")"GRN"来这里。");
	command("say 这包十香软筋散你拿去吧。");
	command("say 假如无法劝降(quanxiang)，就让他服(fu)下这个。");
	new(__DIR__"letter")->move(me);
	new(__DIR__"ruanjin")->move(me);
	message_vision(HIY"$N得到了一小包十香软筋散与一封书信。\n"NOR,me);
	return 1;
}

int ask_finish()
{
	object me, ob;
	int exp, pot;
	string ob_id;

	me = this_player();
	if (!me->query_temp("zhao")){
		command("?");
		return 1;
	}
	ob_id = me->query_temp("zhao/targetid");
	ob = present(ob_id, environment(me));
	if (!ob){
		command("say 人呢？");
		command("angry");
		return 1;
	}
	if (sizeof(filter_array(deep_inventory(ob), (:userp:)))) {
		command("hmm");
		command("whisper "+me->query("id")+ " 这家伙怎么还背着个人啊？");
		return 1;
	}
	if( !ob->query_condition("ruanjin_poison")
	 && (!ob->query_temp("convinced"))) {
		command("hmm");
		command("whisper "+me->query("id")+ " 你怎么没把这家伙“处理”一下呀？");
		return 1;
	}
	command("hehe "+ob->query("id"));
	ob->apply_condition("wuguan_job",10+random(ob->query_kar()));
	message_vision("赵敏召来两个士兵，把$N带走了。\n",ob);
	ob->move(__DIR__"jail");
	command("smile "+me->query("id"));
	command("say 这里没你的事情了，请下去休息吧。");
	exp = random(4)+2;
	pot = me->query("combat_exp",1)/100000;
	pot += 100 + random(20) + me->query("job_time/赵敏");
	if (me->query("menggu")) pot += 30 + random(10);
	
       	/*奖励控制开始*/
        if (me->query("registered")==3){
			exp = exp * ZM_JOB_MUL * VIP_MUL /10000;
            		pot = pot * ZM_JOB_MUL * VIP_MUL /10000;
		}
		else
		{
			exp = exp * ZM_JOB_MUL /100;
           		pot = pot * ZM_JOB_MUL /100;
		}
		/*奖励控制结束*/ 	
	
	
	me->add("combat_exp",exp);
	me->add("potential",pot);
	if (me->query("menggu")) me->add("balance", exp*10000);
	me->add("job_time/赵敏",1);
	log_file("job/zhaomin", sprintf("%8s%-10s第%4d次抓人得到经验%2d，潜能%4d，现经验%d。\n",
		me->name(1),"("+me->query("id")+")",(int)me->query("job_time/赵敏"),exp,pot, me->query("combat_exp")), me);

	me->delete_temp("zhao");
	message_vision(HIW"$N得到了 "HIM+exp+HIW" 点经验，"
		HIG+pot+HIW" 点潜能！$N总共已抓了 "HIR+me->query("job_time/赵敏")+HIW" 个人。\n" NOR, me);
	GIFT_D->check_count(me,this_object(),"赵敏");
	me->apply_condition("job_busy", 5 + random(3));
	return 1;
}

int do_quit()
{
	object me = this_player();
	object ob;

	if (ob = present("shixiang ruanjinsan", me)) {
		command("look " + me->query("id"));
		destruct(ob);
		command("kick3 " + me->query("id"));
		me->delete_temp("zhao");
		me->add_condition("job_busy", 6 + random(4));
		return 1;
	}
	return 0;
}

int ask_quit()
{
	object me = this_player();

	if (me->query("menggu")) {
		command("sneer");
		command("say 我们也不需要你这种反复无常的家伙。");
		me->set("potential",0);
		me->add("combat_exp",-me->query("combat_exp")/100);
		message_vision(BLINK+HIR"$N因为反复无常，经验，潜能都降低了。\n"NOR,me);
		me->delete("menggu");
		return 1;
	}
	return 0;
}

int accept_object(object who, object ob)
{
	//if(userp(ob)) return 0;
	
	if (!who->query_temp("lianji/askmin2")) {
		command("idle " +who->query("id"));
		command("say 你跟我什么关系，滚！ ");
		return 0;
	}
	//给钱
	if (ob->query("money_id") && ob->value() >= 500000) {
		if (!wizardp(who)) {
			command("en");
			return 1;
		}
		else {
			command("blush");
			command("remove all");
			command("lean "+who->query("id"));
			command("sweat "+who->query("id"));
			command("wear all ");
		}
		return 1;
	}
	//周芷若首级 ob->query("name") == "周芷若的首级" && && !who->query("zhou_shouji")
	if (ob->query("id")=="shouji"&& ob->query("name") == "周芷若的首级" )
	{
		if(ob->query("victim_user")) {
			command("say 这不是真的周芷若首级！");
			return 0;
		}
		if(ob->query("kill_by") != who){
			command("say 但他好象不是你杀的吧？你是怎么得到这块人头的？");
			return 0;
		}
		command("say 这竟然是"+ob->query("name"));

		command("say 好！你能杀了周芷若为谢狮王报仇，我就放心了！");
		command("thumb "+ (string)who->query("id"));
		who->set_temp("lianji/killzhou",1);
		destruct(ob);	
		//who->add("shen", -MAX(ABS(who->query("shen"))/5,50000) );//增加shen 降低exp奖励
		
		//if(who->query("shen") > who->query("combat_exp"))
		//	who->set("shen", who->query("combat_exp"));//for hsdizi hehe
		
		//who->add("combat_exp", 400+random(100));
		//who->add("potential", 40);
		
		who->set("zhou_shouji",1);//避免反复刷exp by renlai
		
		//if(who->query("potential") > who->query("max_pot"))
		//	who->set("potential", who->query("max_pot"));
		
		//tell_object(who,HIW"你被奖励了一些负神、潜能和经验值。\n"NOR);
		return 1;
	}
	
	return 0;
}

int ask_cure()
{
	object me = this_player();
	if (!me->query("menggu")) {
		command("en "+me->query("id"));
		return 1;
	}
//	else {
//		if (me->query("job_time/赵敏")/25 > me->query("zhaocure")) {
			command("ok zhao min");
			new(__DIR__"cure")->move(me);
			me->add("zhaocure",1);
			message_vision(HIG"$N得到了一包药粉。\n",me);
			return 1;
//		}
/*		else {
			command("en");
			command("say 你再帮忙我多作点事吧。");
			return 1;
		}
	}
*/
}

void kill_ob(object me)
{
	object ob;
	command("sneer " + me->query("id"));
	ob = present("lu zhangke",environment(me));
	if (ob) {
		ob->force_me("guard zhao min");
		ob->kill_ob(me);
	}
	ob = present("he biweng",environment(me));
	if (ob) {
		ob->force_me("guard zhao min");
		ob->kill_ob(me);
	}
	remove_all_enemy();
}

int ask_zhang()
{
	object me=this_player();
	if (!me->query_temp("lianji/askzhang"))
	{
		command("say 张无忌这个小鬼，看着就不是好东西，难道又在哪儿鬼混？");
		command("say 不知道从哪儿出来个疯子，竟然疯言疯语。");
		return 1;
	}
	command("heng");
	command("say 他让你来做什么？");
	command("say 你一副贼眉鼠脸的样子，看起来就是张无忌那短命的小鬼一个样子。");
	me->delete_temp("lianji/askzhang");
	me->set_temp("lianji/askmin1",1);
	return 1;

}
int ask_zhou()
{
	object me=this_player();
	if (!me->query_temp("lianji/askmin1"))
	{
		command("say 周芷若这个小妞，看着软绵绵的，实则一副狠毒心肠。");
		return 1;
	}	

	command("heng");
	command("say 杀了这阴险的小妞，我的胜算就大了很多！");
	me->delete_temp("lianji/askmin1");
	me->set_temp("lianji/askmin2",1);
	return 1;
}

int ask_xie()
{
	object me=this_player();
	if (!me->query_temp("lianji/askmin2"))
	{
		command("say 你问的是那个谢逊？我不认识他。");
		//command("say 哼！连周芷若都对付不了，还假惺惺令人作呕！\n");
		return 1;
	}
	if (!me->query_temp("lianji/killzhou"))
	{
		//command("say 你问的是那个谢逊？我不认识他。");
		command("say 哼！连周芷若都对付不了，还假惺惺令人作呕！\n");
		return 1;
	}
	command("heng");
	command("say 看你比较顺眼，我就告诉你真相吧，在灵蛇岛上回来后，谢逊是被周芷若陷害的！");
	command("say 我也是是被周芷若陷害的！否则，哼哼！");
	command("say 这小妞看似人畜无害，实则阴险毒辣的很！");
	command("angry ");
	command("say 张无忌这个狠心短命的小鬼！");
	me->delete_temp("lianji/askmin2");
	me->delete_temp("lianji/killzhou");
	me->set_temp("lianji/askmin3",1);
	return 1;

}

int ask_jinmao()
{
	object me=this_player();
	object jinmao;
	jinmao=new("d/mingjiao/obj/jinmao");
	if (!me->query_temp("lianji/askmin3"))
	{
		command("say 什么金毛？我不知道。");
		return 1;
	}
	
	command("heng");
	command("say 好吧，看来张无忌那个小鬼还是蛮不错的，这个就给你吧！");
	command("heng ");
	command("angry");
	jinmao->move(me);
	me->delete_temp("lianji/askmin3");
	
	me->set_temp("lianji/givejinmao",1);
	return 1;
}

int greet_zhang()
{
	command("hi zhang sanfeng");
	command("say 晚生执掌明教张无忌，今日得见武林中北斗之望，幸也何如！”");
	command("xixi");
	command("say 宋大侠、俞二侠、张四侠、莫七侠四位，目下是在本教手中。每个人受了点儿伤，性命却是无碍。");
	command("say 张真人对武当绝学可也当真自负得紧。你既说他们中毒，就算是中毒罢。");
	command("say 晚生有一句良言相劝，不知张真人肯俯听否？");
	command("say 普天之下，莫非王土，率土之滨，莫非王臣。我蒙古皇帝威加四海。张真人若能效顺，皇上立颁殊封，\n武当派大蒙荣宠，宋大侠等人人无恙，更是不在话下。");
	command("say 弃暗投明，自来识时务者为俊杰。少林派自空闻、空智神僧以下，个个投效，尽忠朝廷。本教也不过见\n大势所趋，追随天下贤豪之后而已，何足奇哉？");
	command("say 我本来不是男子汉大丈夫，阴险毒辣了，你便怎样？");
	command("say 江湖上传言武当乃正大门派，岂知耳闻争如目见？原来武当派暗中和魔教勾勾搭搭，全仗魔教撑腰，本门武功可说不值一哂。");
	command("say 听他吹这等大气！你去试试，瞧他有什么真才实学。");
	return 1;

}

int greet_ada()
{
	command("say 该死，该死！我先入为主，一心以为小鬼在外布置，没想到他竟假装道童，在此捣鬼，坏我大事。");
	command("say 你怎地如此没出息，假扮起小道童来？满口太师父长、太师父短，也不害羞。");
	command("angry ");
	command("say 什么好外孙、好徒孙！两个老不死，养了一个奸诈狡狯的小鬼出来。阿大，你去试试他的剑法。");
	command("say 小鬼，你懂得什么？灭绝老尼从我家中盗得此剑，此刻物归原主，倚天剑跟峨嵋派有什么干系？");
	command("say 我干么要跟你说？不将你碎尸万段，难抵当日绿柳庄铁牢中，对我轻薄羞辱之罪！");
	command("say 去把这小子两条臂膀斩下来！");
	
	return 1;

}


int do_answer(string arg)
{
	object me = this_player();
	if (me->query_temp("fangqiscore")) {
	if (arg=="yes")
	{
		me->set("was_job/wasscore",0);//清空was积分
		message_vision(HIY"$N对赵敏点了点头，说道，“既然是如此，我愿诚心辅佐郡主！”\n"NOR,me);
	}
	else
	{
		message_vision(HIY"$N对赵敏摇了摇头，说道，“既然是如此，我是不能辅佐郡主了！”\n"NOR,me);
	}
	remove_action("do_answer","answer");
	me->delete_temp("fangqiscore");
	}
	return 1;
}



string ask_gmd() 
{
	
	object me = this_player(), ob = this_object();
	int max,i;
	int totalexp=0, maxexp, minexp;//防止exp差距太大
	object obj1;
	object *ob_list;
	object ob2;
	object fbroom;
	object *team;
	
	
	team = me->query_team();
	
	if (me->query("shen")>0) return "你这人心底太好，我不放心把这个任务交给你。";	
	if (me->query("combat_exp")<10000000) return "你武艺尚未有成，我不放心把这个任务交给你。";

   if (me->query("was_job/wasscore"))
    {
	        command("say 哼，你居然帮助过明教，还坏过我大事,若是你能洗心革面悔过，并放弃以前得到的奖励。");
	        message_vision("赵敏要你放弃万安寺积分,你如果愿意就输入(answer yes ),不愿意就输入(answer no)！\n",me);
			add_action("do_answer","answer");
			me->set_temp("fangqiscore",1);
			return "嘿嘿...";
	}


	
	//如果是组队模式
	if (team){		
		
		
		if (team[0] != me) {		
		return "只有队伍首领才能接任务。";
	    }
		if (sizeof(team) > 5 ){
		 return "此去行动不易人多，五人足矣。";
		}
		
		maxexp=minexp=team[0]->query("combat_exp");
		
		
		for (i=0;i<sizeof(team);i++){			
			
		totalexp = totalexp + team[i]->query("combat_exp");
		
		if(team[i]->query("combat_exp") > maxexp) {
			maxexp=team[i]->query("combat_exp");
			//maxplayer=team[i];
		}
		else if(team[i]->query("combat_exp") < minexp)
			  minexp=team[i]->query("combat_exp");		
			
			
		if (!team[i]){
			return "你的队伍出现了问题，请解散并重新组建。";
		}
		
         if (!present(team[i])){			
			return "咦？怎么好象人不全啊？"+team[i]->query("name")+"怎么没来？";
		}
        
		 if (team[i]->query("was_job/wasscore")) return "你的队伍里有人曾经帮助过明教教主做事。";
		  
         if ((int)team[i]->query("shen")>0) 
			return "你的队伍里有正人君子，我不放心把这个任务交给你。";		 
		
		 if (team[i]->query("combat_exp")<10000000) 
			 
		 return "你的队伍里有人武艺尚未有成，我不放心把这个任务交给你。";	
   
		if( team[i]->query_temp("quest/busy")) //added by tangfeng 与quest冲突
		{			
			return "你们有人在解密之中，你们还是先处理好你其他事情再说吧。";
		}
		
		if (team[i]->query("job_name")=="勇闯万安寺") //added by tangfeng 与quest冲突
		{			
			return "你们队中有人刚做完勇闯万安寺，你们还是先等他处理好再说吧。";
		}
		
		if (team[i]->query("job_name")=="围攻光明顶") //added by tangfeng 与quest冲突
		{			
			return "你们队中有人刚做完围攻光明顶，你们还是先等他处理好再说吧。";
		}
		
		if (team[i]->query("job_name")=="抗敌颂摩崖") //added by tangfeng 与quest冲突
		{			
			return "你们队中有人刚做完颂摩崖，你们还是先等他处理好再说吧。";
		}
		
		if (team[i]->query("job_name")=="抗敌蒙古入侵" )
		return "你们队中有人刚做完蒙古入侵任务。";
		
		if (team[i]->query_condition("job_busy"))
		{			
			return "你们队中有人刚做完任务还需要休息。";
		}
		
		if (team[i]->query_condition("was_busy"))
		{			
			return "你们队中有人刚做完勇闯万安寺任务还需要休息。";
		}
		if (team[i]->query_condition("gmd_busy"))
		{			
			return "你们队中有人刚做完围攻光明顶任务还需要休息。";
		}
		if (team[i]->query_condition("killer")) 
			return "你的队伍里有被官府通缉的人。";
		
		
		
		if (me == team[i]) continue;
/*
		if (!interactive(team[i]) || query_ip_number(team[i]) == query_ip_number(me)) {
		return "你还是将"+team[i]->query("name")+"换成其他人吧。;
		}*/

	}
      if (minexp>100000000)
		  {
			  if ((maxexp-minexp)>maxexp*0.1)  return "此去任务艰辛，我看诸位队员差距过大，似乎无此能力。";			
		  }
		  else
		  {
			  if((maxexp-minexp) > 5000000) return "此去任务艰辛，我看诸位队员差距过大，似乎无此能力。";
		  }

		
	}  //组队
	
	//单人
	
	
//	if (!wizardp(me))	
//              return "暂时关闭,开放日期另行通知!";
 if (!wizardp(me))	{
	if (me->query_temp("gmd_job/asked") )
		return "你不是已经接过任务了吗？";
	
	if (me->query("job_name")=="勇闯万安寺")
		return "你刚做完勇闯万安寺任务，还是歇歇吧。";
	
	if (me->query("job_name")=="抗敌颂摩崖") return "你刚做完抗敌颂摩崖任务，还是歇歇吧。";
	
	if (me->query_condition("was_busy")) return "你刚做完勇闯万安寺任务，还是歇歇吧。";
	
	if (me->query_condition("gmd_busy")) return "你刚做完围攻光明顶任务，还是歇歇吧。";
	
	if (me->apply_condition("gb_job_busy")) return "你刚做完抗敌颂摩崖任务，还是歇歇吧。";
	
	if (me->query_condition("job_busy"))
		{			
			return "你刚做完任务还需要休息。";
		}
	
 }

	ob2 = new("/clone/npc/zhong-shentong");
	if( ob2 ){
		destruct(ob2);
	}	
	
			
	command("say 我奉父王之命要剿灭众多反贼，明教乃是首当其冲，若能将光明顶圣火扑灭，明教之势自然消弭瓦解。\n" );	

	me->set_temp("gmd_job/asked",1);
	me->apply_condition("job_busy", 30);
	me->apply_condition("gmd_busy", 30);
	me->apply_condition("gmd_job", 12);		
	command("say 明教内高手如云，你可潜到光明顶附近待各派到齐后再一起围攻光明顶。\n");	
	
		
	if (team){
		
		me->set_temp("gmd_job/team",team);//记录队伍		
		
	}

	return "明教中不乏高手，你最好多带人手，待得人手到齐后，布下阵法，再去围攻(weigong)，以策万全，切记切记。";	
	
}


