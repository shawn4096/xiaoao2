// Update by Lklv 2001.10.18

#include <ansi.h>
inherit F_MASTER;
inherit NPC;
string ask_yangxiao();
string ask_yanxing();

void create()
{
	set_name("孤鸿子", ({"guhong zi", "zi", "guhong"}));
	set("long","他就是峨嵋派的掌门人师兄孤鸿子。\n"
		"他虽然衣衫褴褛，但自有一番威严，只是苍老的脸上时时露出忧郁的神色。\n"
	);
	set("gender", "男性");
	set("attitude", "friendly");
	set("unique", 1);
	set("age", 55);
	set("shen", 20000);
	set("str", 32);
	set("int", 25);
	set("con", 30);
	set("dex", 28);
	set("max_qi", 15500);
	set("max_jingli", 6000);
	set("max_jing", 6500);
	set("neili", 18500);
	set("max_neili", 18500);
	set("jiali", 200);
	set("combat_exp", 9300000);

	set_skill("dacheng-fofa", 200);
    set_skill("linji-zhuang", 450);

	set_skill("jieshou-jiushi", 450);
	set_skill("huifeng-jian", 450);
	set_skill("sixiang-zhang", 450);
	set_skill("yanxing-daofa", 470);
	set_skill("hand", 450);
	set_skill("literate", 200);
	set_skill("strike", 450);
	set_skill("linji-jianzhen", 450);
	set_skill("sword", 450);
	set_skill("blade", 470);
	set_skill("parry", 450);
	set_skill("dodge", 450);
    set_skill("force", 450);
	set_skill("anying-fuxiang", 450);

	map_skill("force", "linji-zhuang");
	map_skill("sword", "huifeng-jian");
	map_skill("blade", "yanxing-daofa");
	map_skill("parry", "yanxing-daofa");
	map_skill("dodge", "anying-fuxiang");
	map_skill("strike", "sixiang-zhang");
	map_skill("hand", "jieshou-jiushi");

	prepare_skill("hand", "jieshou-jiushi");
	set("chat_chance_combat", 40);
	set("chat_msg_combat", ({
		(: perform_action, "blade.luandao" :),
			(: perform_action, "blade.chuanliu" :),
			(: perform_action, "blade.feiyan" :),
		(: perform_action, "hand.foguang" :)
	}));
	set("inquiry",([
		"杨逍" : (: ask_yangxiao :),
		"雁行刀法绝技" : (: ask_yanxing :),
		//"光大峨嵋" : (: ask_dragon :),
		//"光大我派" : (: ask_dragon :),
        ]) );
	create_family("峨嵋派", 3, "门中长老");
	setup();
	set_temp("apply/dodge", 40);
	set_temp("apply/attack", 40);
	set_temp("apply/armor", 40);
	carry_object(BINGQI_D("blade"))->wield();
	UPDATE_D->get_cloth(this_object());
}

void init()
{
	object me, ob;
	::init();
	ob = this_player();
	me = this_object();
	if (interactive(ob = this_player()) && !is_fighting()) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

void greeting(object me)
{
	mapping myfam;
//	mapping lrn;
	int shen;
//	int lvl;
	myfam = (mapping)me->query("family");
	if (!myfam) return;
	shen = me->query("shen");
	if (shen < -200000 && myfam["master_name"] == "孤鸿子"){
		command("say 你满眼瘴气，身带邪气，再不思悔改，我要将你开除师门！");
	}
/*
        if ( me->query("class") != "bonze" && myfam["family_name"] == "峨嵋派"){
		lvl = (int)me->query_skill("linji-zhuang", 1);
		lrn = me->query_learned();
		if( !mapp(lrn) ) return;
		if( (int)lvl/10 == 14 && (int)me->query("emsujia")<1 ) {
			command("say 临济庄需要有高深的佛法相辅助，否则就会前功尽弃。");
			command("say 我们俗家弟子世俗缠身，不可能像佛门弟子那样潜心向佛。");
			command("say 你的内功修为虽说已到了一定层次，但你最好需要到后山修炼一下。");
			tell_object(me, "你听了师傅的话,深感有理。\n");
		}
		if( (int)lvl/10 == 16 && (int)me->query("emsujia")<2 ) {
			command("say 临济庄需要有高深的佛法相辅助，否则就会前功尽弃。");
			command("say 我们俗家弟子世俗缠身，不可能像佛门弟子那样潜心向佛。");
			command("say 你的内功修为虽说已到了一定层次，但你最好需要到后山修炼一下。");
			tell_object(me, "你听了师傅的话,深感有理。\n");
		}
		if( (int)lvl/10 == 17 && (int)me->query("emsujia")<3 ) {
			command("say 徒儿，你的功夫已经快赶上老夫了。为师有一桩心愿，那就是在为师的有生之年能够再看一眼(show)倚天剑。");
		}
	}
*/
}

void attempt_apprentice(object ob)
{
        object me;
        mapping ob_fam, my_fam;
        string name;

	me = this_object();
	my_fam  = me->query("family");
	name = ob->query("name");

	if (!(ob_fam = ob->query("family")) || ob_fam["family_name"] != "峨嵋派") {
		command("say " + RANK_D->query_respect(ob) + "与本派素无来往，不知此话从何谈起？");
		return;
	}
	if ((int)ob->query_skill("linji-zhuang",1) < 75) {
		command("say " + RANK_D->query_respect(ob) + "，你的临济十二庄修为不够，不能拜我为师。");
		return;
	}
        if (!ob->query("luohan_winner") ) {
		command("say " + RANK_D->query_respect(ob) + "，你的武学修为不够，不能拜我为师。");
		return;
        }
	if (ob->query("class") == "bonze" ) {
		command("say " + RANK_D->query_respect(ob) + "，我只收俗家弟子。");
		return;
        }
	command("chat* haha");
	command("say 老夫垂死之年，终得到一个衣钵传人，真是可喜可贺 !");
	command("recruit " + ob->query("id"));
	return;
}

int accept_object(object who, object ob)
{
	mapping myfam = (mapping)who->query("family");
	if(myfam["family_name"] != "峨嵋派"){
		command("say " + RANK_D->query_respect(who) + "与本派素无来往，不知此话从何谈起？");
		return 1;
	}
	//得到倚天剑
	if (ob->id("yitian jian") && !this_object()->query("jian"))  {
		command("say 这。。这就是当年被魔教恶人夺走的倚天剑啊！");
		command("say 老夫有生之年能再看到这把剑，真是死也瞑目了。");
		command("say 来，来，不能辜负了你的心意。");
		message_vision(HBGRN"孤鸿子对$N教导了一番，$N感觉胸中升起一股正气。\n"NOR,who);
		//who->set_temp("emei/jianjue",1);
        	who->add("shen",5000);
		call_out("dest", 1, ob);
        	set("jian",1);
		call_out("delete", 900, "jian");
        who->set_temp("yanxing/showyitian",1);
			return 1;
	}
	//得到人头
	if(ob->query("name") == "杨逍的首级" && ob->query("id") == "shouji")
	{
		
		if (!who->query_temp("yanxing/askghz"))
		{
			command("say 你莫名其妙的杀了个人，与我何干？\n");
			return 1;
		}
		if(ob->query("kill_by") != who){
			command("say 但他好象不是你杀的吧？你是怎么得到这人头的？");
			return 1;
		}
		
		command("say 好！你能杀了杨逍为为师报仇，不愧是我大峨嵋俗家大弟子！");
		command("thumb "+ (string)who->query("id"));
		who->set_temp("yanxing/killyang",1);
		call_out("dest", 1, ob);		
		
		who->add("shen", MAX(ABS(who->query("shen"))/5,50000) );//增加shen 降低exp奖励
		
		if(who->query("shen") > who->query("combat_exp"))
			who->set("shen", who->query("combat_exp"));//for hsdizi hehe
		who->add("combat_exp", 50+random(50));
		who->add("potential", 40);
		if(who->query("potential") > who->query("max_pot"))
			who->set("potential", who->query("max_pot"));
		tell_object(who,HIW"你被奖励了一些正神、潜能和经验值。\n"NOR);
		return 1;
	}
}

void dest(object ob)
{
	if (ob) destruct(ob);
}

string ask_yangxiao()
{
	object me,ob;
	me=this_player();
	ob=this_object();
	if (me->query("family/family_name")!="峨嵋派")
	{
		return "你不是我大峨嵋的弟子，难道是魔教的间隙？？\n";
	}
	if (me->query("family/master_name")!="孤鸿子")
	{
		return "你不是我的弟子，问了也是白问！\n";
	}
	
	message_vision(HIC"$N跪在$n面前虚心请教一些江湖故事。\n"NOR,me,ob);
	command("say 杨逍？！！！！！！！！！！！！！\n");
	message_vision(HIY"$n好像甚是激动，$n忍不住站起来身来，在屋内往复徘徊，似乎在想什么重大的事情一般！\n"NOR,me,ob);
	command("say 唉！你既然提起这件往事，为师就跟你说说这些陈芝麻乱谷子！\n");
	command("say 我年轻的时候曾经遇到一位武林高手，此人极为嚣张跋扈！\n");
	command("say 指名道姓挑战天下英豪，一时间，江湖尽是他的传说和故事！\n");
	command("say 为师受师命下山历练，和此人在一个小镇上相遇！\n");
	command("say 不出所料，我和他交手了！\n");
	command("say 这次交手为师我败于他的招式下！\n");
	command("say 当时我年轻气盛，气不过这件事情，也想不开，于是我就向师妹借了倚天剑去跟他斗！\n");
	command("say 谁知？二次交手我依然是被他打败！\n");
	command("say 甚至他将我的倚天剑都夺了去，随手丢在我的面前！\n");
	command("say 为师受此奇耻大辱！\n");
	command("say 回来后痛定思痛，决定放弃剑法，重修刀法！\n");
	message_vision(HIY"$N惊讶的“啊”了一声，道，“这是多难的一项决定啊？”\n"NOR,me);
	command("look "+me->query("id"));
	command("say 你能有这番见识，为师甚是欣慰！\n");
	command("say 这倒不是因为他羞辱我，所以弃剑学刀，而是我发现杨逍对于剑法有极深的造诣！\n");
	command("say 为师想过很久，如果从剑法上我终其一生恐怕都难以超越他，很难报此大仇！");
	command("say 为师只有另辟蹊径，在他不擅长的领域中才能压制他，否则.....\n");
	command("say 这门刀法乃是鹰爪雁行门的镇派之宝，后来为师机缘巧合习得此项绝技，体味之下方觉唯有此招能克制杨逍的招式.\n");
	command("say 既然你对这门刀法感兴趣，你去把杨逍这家伙的人头替为师拿来，我就跟你说下这当中的诀窍！\n");
	me->set_temp("yanxing/askghz",1);
	return "唉！杨逍杨逍，我不杀你誓不为人！\n";
}

string ask_yanxing()
{
	object me,ob;
	me=this_player();
	ob=this_object();
	if (me->query("family/family_name")!="峨嵋派")
	{
		return "你不是我大峨嵋的弟子，难道是魔教的间隙？？\n";
	}
	if (me->query("family/master_name")!="孤鸿子")
	{
		return "你不是我的弟子，问了也是白问！\n";
	}
	if (!me->query_temp("yanxing/killyang"))
	{
		return "不是让你去杀杨逍了么？你还在这磨蹭什么！\n";
	}
	if (!me->query_temp("yanxing/showyitian"))
	{
		return "我想看看倚天剑，哪怕死了也甘心！你还在这磨蹭什么！\n";
	}
	if (me->query("quest/em/yxdf/jueji/pass"))
	{
		return "我已经解开此谜，来此聒噪什么！\n";
	}
	if (me->query_temp("yanxing/askzi"))
		return "你正在请教中！\n";
	if (time()-me->query("quest/em/yxdf/jueji/time")<86400)
	{
		return "你来的太勤快了，贪多嚼不烂！\n";
	}
	me->set_temp("yanxing/askzi",1);

	command("pat "+me->query("id"));
	command("say 好，你真是深明我心，既然你如此奋发向上，为师就把这门绝学传授于你！\n");
	message_vision(HIC"$N跪了下来，恭恭敬敬给$n磕头,接受$n的教诲。\n"NOR,me,ob);
	
	command("say 这门刀法乃是鹰爪雁行门的镇派之宝，后来为师机缘巧合习得此项绝技，体味之下方觉唯有此招能克制杨逍的招式.\n");
	command("say 既然你对这门刀法感兴趣，也获得为师的信任，我就把这几年的体悟告知与你！\n");
	command("say 这门功法有几个招式，甚是特殊！\n");
	command("say 在以往过程中我并没有发现，只觉得这门刀法似乎还有很大的威力没有发挥出来，我一直不知道为什么！\n");
	command("say 但自从和杨逍一战后，为师一直在苦死如何打败杨逍！\n");
	command("say 在捉摸每一招式的过程中，为师发现之所以这门刀法在门派中威力不显！\n");
	command("say 主要原因是本门祖师以至于历代掌门均为女性，刀法对于她们来说比较沉重，不适合运使！\n");
	command("say 再加上本门心法崇尚大乘佛法修为，所以，更加和这刀法的重、猛、凶、狠的风格格格不入！\n");
	command("say 所以，要想把本门刀法发扬光大，必须要是心志坚定，对别人要狠，对自己更要狠的俗家男子方可修习！\n");
	command("say 这也是为师迟迟不出家的主要原因，唯如此方可将刀法要诀威力发挥出来！\n");
	command("say 你附耳过来，我说与你听.....\n");
	me->set_temp("yanxing/jueji",1);
	me->start_busy(999);
	call_out("yx_think",1,me);
	return "这门武功习得足矣纵横江湖，若能学的本门的无上内功心法九阴真经，必将更上一层楼！\n";
}
int yx_think(object me)
{
	int i,j;
	if(!me) return 1;
	me->set("quest/em/yxdf/jueji/time",time());
	if(me->query_temp("yanxing_thinking")<(10+random(3)))
	{
		me->add_temp("yanxing_thinking",1);
		if(random(2)) tell_object(me,HIG"\n你努力地回忆刚才孤鸿子所指导你的每一句话的真意,只觉得奥妙无穷...\n"NOR);
		else tell_object(me,HIY"\n突然间，这招式虽然有些粗糙，但的确是令人防不胜防。\n"NOR);
		tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，一服愁眉不展的样子。\n"NOR, ({}));
		remove_call_out("yx_think");
		call_out("yx_think",3+random(3), me);
	}
	else
	{
		me->delete_temp("yanxing_thinking");
	
		i= 20;
		j=random(me->query("kar"));
		if(me->query("m-card-vip")) i =  18;
		if(me->query("y-card-vip")) i =  15;
		if(me->query("buyvip"))     i =  10;
		i= random(i);
	
		if (me->query("kar")<31
			&&j>=26
			&&i<4)
		{
			message_vision(HIC"\n\n$N终于将雁行刀发绝技最后三招学全，融会贯通，威力大增\n"NOR,me);
			me->start_busy(1);

			message("channel:rumor", HIM"【谣言】某人："+me->query("name")+"机缘巧合，学全雁行刀发绝技，刀法达到了运用自如的境界！\n"NOR, users());
			message("channel:chat", HIC"【聊天】孤鸿子："+me->query("name")+"乃是我孤鸿子终于收到了一位得意弟子，还请各位江湖大佬以后多多眷顾。！\n"NOR, users());

			log_file("quest/yanxingjueji",sprintf("%s(%s) 从孤鸿子哪儿得到雁行刀发秘诀。随机富源：%d。随机数：%d。失败：%d。经验值：%d。\n",
				me->name(1), me->query("id"),j,i,me->query("quest/em/yxdf/jueji/fail"),me->query("combat_exp"),me));
			me->set("title",HIC"峨嵋"HIG"孤鸿子传人"NOR);
			me->set("mytitle/quest/guhongzititle",HIC"峨嵋"HIG"孤鸿子传人"NOR);
			
			me->set("quest/em/yxdf/jueji/pass",1);
			me->delete_temp("yanxing");
			return 1;
		}
		else
		{
			message_vision(HIY"\n\n$N虽然听孤鸿子说了明白了这些诀窍，但对于如何使用的劲力法门一时之间却是难以理解\n"
			+"雁行刀发威力并没有发挥出来，看来你还是有待于重新跟孤鸿子学习了。\n"NOR,me);
			log_file("quest/yanxingjueji",sprintf("%s(%s) 从孤鸿子学习雁行刀法秘诀失败。随机富源：%d。随机数：%d。失败：%d。经验值：%d。\n",
				me->name(1), me->query("id"),j,i,me->query("quest/em/yxdf/jueji/fail"),me->query("combat_exp"),me));
			me->start_busy(1);

			message("channel:chat", HIC"【聊天】孤鸿子长叹一声，似乎对"+me->query("name")+"甚是失望。！\n"NOR, users());
			message("channel:chat", HIC"【聊天】孤鸿子喃喃自语道，”一日不杀了杨逍，老子一天寝食难安“。！\n"NOR, users());

			me->add("quest/em/yxdf/jueji/fail",1);
			me->set("quest/em/yxdf/jueji/time",time());
			me->delete_temp("yanxing"); 	
			return 1;
		}  
	}
}