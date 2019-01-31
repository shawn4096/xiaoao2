// /d/xingxiu/npc/ding.c 
// ding.c 丁春秋
// Update by caiji@SJ 8/8/2000

#include <ansi.h>
#include <get_place.h>

#include <jobround.h>
#include <job_mul.h>


#define TIME_TICK (time()*60)
//#include "/d/xingxiu/npc/ding.h"


inherit NPC;
inherit F_MASTER;

string *drugs = ({"/obj/yao","/obj/yao1","/obj/yao","/obj/yao2","/obj/yao","/obj/yao3","/obj/yao",});
int give_reward(object me);
int give_drug();
string ask_job5();
string ask_pantu();
string ask_job4();
string ask_job5_times();

string ask_fail();
int check(object ob);
string ask_job3();
string ask_job();
string ask_times();
string ask_san();
string ask_gou();
string ask_pay();
int ask_hgdf();
int ask_finish();

string ask_zhuihun();
void create()
{
	set_name("丁春秋", ({ "ding chunqiu", "ding" }));
	set("nickname", "星宿老怪");
	set("long",
	"星宿派开山祖师、令中原武林人士深恶痛绝的星宿老怪丁春秋。\n"
	"他脸色红润，满头白了，颏下三银髯，童颜鹤发。\n"
	"当真便如图画中的神仙人物一般。\n");
	set("gender", "男性");
	set("age", 60);
	set("per", 24);
	set("attitude", "friendly");
	set("no_bark",1);
	set("shen_type", -1);
	set("str", 40);
	set("int", 27);
	set("con", 40);
	set("dex", 32);
	set("max_qi", 80000);
	set("max_jing", 5000);
	set("eff_jingli", 3500);
	set("max_neili", 30000);
	set("jiali", 250);
	set("combat_exp", 15000000);
	set("unique", 1);
	set("quest/xx/hgdf/powerup",1);
    set("quest/xx/tsz/luanpifeng/pass",1);
	set("quest/xx/tsz/zhuihun/pass",1);
	set("shen", -200000);
	set("xx/zhg/pass",1);

	set_skill("force", 551);
	set_skill("huagong-dafa", 551);
	set_skill("dodge", 500);
	set_skill("zhaixingshu", 500);
	set_skill("strike", 551);
	set_skill("chousui-zhang", 551);
	set_skill("parry", 500);
	set_skill("claw", 500);
	set_skill("sanyin-zhua", 500);
	set_skill("staff", 500);
	set_skill("tianshan-zhang", 500);
	set_skill("literate", 250);
    set_skill("poison", 300);
    //set_skill("hook", 500);
    //set_skill("zhuihun-gou", 500);
	map_skill("force", "huagong-dafa");
	map_skill("hook", "zhuihun-gou");
	map_skill("dodge", "zhaixingshu");
	map_skill("strike", "chousui-zhang");
	map_skill("parry", "chousui-zhang");
	map_skill("claw", "sanyin-zhua");
	map_skill("staff", "tianshan-zhang");
	prepare_skill("strike", "chousui-zhang");
	prepare_skill("claw", "sanyin-zhua");
	create_family("星宿派", 1, "开山祖师");
	set("inquiry", ([
		 "毒药" : (: give_drug :),
		 "心情" : (: ask_job :),
	    //   "三笑散" : (: ask_san :),
	   //"三笑逍遥散" : (: ask_san :),
		"pantu" : (: ask_pantu :),
	    "毒虫谷" : (: ask_job4 :),
	    "duchonggu" : (: ask_job4 :),
		  //"叛徒": (: ask_job5 :),
		"叛徒": (: ask_pantu :),
		"放弃": (: ask_fail :),
		"fail": (: ask_fail :),
	    "化功大法奥秘": (: ask_hgdf :),
	  //  "杀叛徒次数": (: ask_job5_times :),
	    "完成": (: ask_finish :),
	    "追魂夺命绝技": (: ask_zhuihun :),

	     "神木王鼎" : "你敢偷，就废了你。",
		 "木鼎" : "抓虫子练毒用的。",
	]));

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: exert_function, "huadu" :),
		(: exert_function, "huajing" :),
		(: perform_action, "strike.huoqiu" :),
		(: perform_action, "strike.chousui" :),
		(: perform_action, "strike.yinhuo" :),
		(: perform_action, "strike.biyan" :),
	}));

	set("drug_count",15);
	set("class", "taoist");

	set_temp("apply/damage", 20);
	set_temp("apply/defense", 70);
	set_temp("apply/armor", 60);
	setup();

	if (clonep()) {
		UPDATE_D->get_cloth(this_object());
		add_money("gold", 2);
	}
}

int prevent_learn(object me,object weapon)
{
	mapping myfam;
	object ob;
	int shen;
	ob=this_player();
	myfam = (mapping)ob->query("family");
	if(!myfam || (myfam["family_name"] != "星宿派")) return 0;
	if(!ob->is_apprentice_of(this_object())) return 0;
	
	shen = ob->query("shen");
	if(shen > -1000 && shen < 0)
	{
		command("say 你怎么搞的？搅和了一身的白道气息！");
		return 1;
	}
	else if(shen >= 0 && shen < 100000)
	{
		command("say 好哇！你敢和白道的人搅和，不想活了是不是？");
		return 1;
	}
	else if(shen >= 100000){
		command("say 你竟敢和白道的人搅和！从我这里滚出去吧！");
		command("expell " + ob->query("id"));
		return 1;
	}
	return 0;
}

void init()
{
	object me, ob;
	::init();
	ob = this_player();
	me = this_object();

	if(ob->query("job_time/星宿熬药"))
	{
		ob->add("job_time/星宿熬膏",ob->query("job_time/星宿熬药"));
		ob->delete("job_time/星宿熬药");
	}
		
	if (interactive(ob = this_player()) && visible(ob) && !is_fighting()) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
	add_action("do_flatter", "flatter");
	add_action("do_xian", "xian");
	//add_action("do_begsan", "begsan");
}

string ask_san()
{

	if((int)this_player()->query("combat_exp") < 200000
	 || (string)this_player()->query("family/family_name") != "星宿派")
		  return "就凭你也想要三笑散？\n";

	if( query("started") != 1 ){
	   set("started", 1);
	   call_out("generate_sxs", 7200);//2 hours
	}

	if((int)this_player()->query_skill("poison", 1) < 200)
		  return "你的毒技还不够高，我不放心把三笑散交给你。";

	if((int)this_player()->query_skill("huagong-dafa", 1) < 450)
		  return "你的化功大法还不够高，我不放心把三笑散交给你。";

	message_vision("丁春秋对$N笑道：你用begsan试试缘分如何。\n", this_player());
	return "快试吧";
}

void generate_sxs()
{
	remove_call_out("generate_sxs");
	set("available", 1);
}

int do_begsan(string arg)
{
	object me, book;
	me = this_player();

	if( query("available") == 1 && clonep(book = unew(MEDICINE_D("sxs")))){
	  set("available", 0);
	  book -> move(me);
	  message_vision("$N咱们真是有缘，这一包三笑散就送给你了。\n", me);
	  command("chat "+ me->query("name")+"有缘，得到我的宝物“三笑逍遥散”！");
	  remove_call_out("generate_sxs");
	  call_out("generate_sxs", 7200);//2 hours
	  return 1;
	}
	return notify_fail("丁春秋说道：你来的不是时候。\n");
}

void greeting(object me)
{
	mapping myfam;
	int shen;

	if(!me || environment(me) != environment(this_object())) return;

	shen = me->query("shen");
        if ( file_name(environment(this_object())) != this_object()->query("startroom")) return;

	if(!myfam = (mapping)me->query("family"))
		command("say 你千里迢迢来天山, 莫不是想加入我星宿派？");
	else if(myfam["family_name"] != "星宿派" ){
		if(!me->query_temp("xx_job"))
			command("say 你千里迢迢来到天山，是仰慕本老仙我的仁德吧？");
		else    command("nod " + me->query("id"));
	}

	else if(shen > -1000 && shen < 0)
		command("say 你怎么搞的？搅和了一身的白道气息！");
	else if(shen >= 0 )//&& shen < 100000
		command("say 好哇！你敢和白道的人搅和，不想活了是不是？");
	else if(shen > 100000){
		command("say 你竟敢和白道的人搅和！从我这里滚出去吧！");
		command("expell " + me->query("id"));
	}   // I move this to prevent_learn By Ciwei@SJ
	else command("say 好徒儿，功夫练得怎么样了？");
	if(me->query("xx_job5_finished"))call_out("give_reward",1,me);
}

void attempt_apprentice(object me)
{
	if(me->query("family/family_name") != "星宿派"
	 && me->query("expell/family_name") != "星宿派"){
		say("老仙对"+me->name()+"理都不理。\n");
		return;
	}
	if ((int)me->query("shen") > -2000000) {
		command("say 老仙越看你越象白道派来卧底的。我星宿的都心狠手辣，哪个手底下没几百条人命啊。");
		return;
	}
    if (me->query("job_time/星宿")+me->query("job_time/星宿叛徒")+me->query("job_time/星宿熬膏") < 1500) {
		command("say 你应该多多为老仙我分担分担忧愁才是。");
		return;
	}
	if(me->query_skill("huagong-dafa",1) < 350){
		command("say 看来你的化功大法基础还不够啊，先去跟我徒儿学学吧。");
		return;
	}
	if(!me->query("quest/xx/dichuan")){
		command("say 你并没有为我大星宿做任何贡献，来此作甚？");
		return;
	}
	if( me->query_temp("pending/flatter") ) {
		command("say 你如此不把老仙放在眼里，老仙怎会收你？");
		return;
	}
	else {
		command("say 我星宿老仙比起古往今来的圣人怎么样啊？");
		message_vision("星宿老怪微闭双眼，手捻长须，一付等$N拍马(flatter)的样子。\n", me);
		me->set_temp("pending/flatter", 1);
	}

}

int do_flatter(string arg)
{
	object me, ob;
	me = this_player();
	ob = this_object();

	if( !arg ) return notify_fail("你要赞扬老仙的什么丰功伟绩？\n");
	if(me->query_condition("gb_mission") || me->query_condition("gb_busy"))
		return notify_fail("老仙最讨厌臭叫化子，先扔掉你的丐帮帮务再说！\n");
	if(this_player()->query("jing") < 10)
		return notify_fail("你太累了，等等再拍吧！\n");

	switch(random(5)) {
		case 0 : message_vision("\n$N对$n大声赞道：您老人家一蹬足天崩地裂，一摇手日月无光！\n", me,ob); break;
		case 1 : message_vision("\n$N对$n大声赞道：星宿老仙大袖摆动，口吐真言，叫旁门左道牛鬼蛇神，一个个死无葬身之地！\n", me,ob); break;
		case 2 : message_vision("\n$N对$n大声赞道：这天下武林盟主一席，非老仙莫属。只须老仙下令动手，小人赴汤蹈火，万死不辞！\n", me,ob); break;
		case 3 : message_vision("\n$N对$n大声赞道：日月无老仙之明，天地无老仙之大，自盘古氏开天辟地以来，更无第二人能有老仙的威德！\n", me,ob); break;
		case 4 : message_vision("\n$N对$n大声赞道：老仙神功盖世，天下第一，战无不胜，功无不克！\n", me,ob); break;
	}

	message_vision(HIY"$N大声唱道：" + arg + "\n"NOR, this_player());
	this_player()->set("jing", 1);
	
	if( strsrch(arg, "星宿老仙") >=0 && (strsrch(arg, "德配天地") >=0
	 && strsrch(arg, "威震寰宇") >=0 && strsrch(arg, "古今无比") >=0 )) {
		command("smile");
		command("say 这还差不多。\n");
		if(this_player()->query_temp("pending/flatter")){
			this_player()->delete_temp("pending/flatter");
			command("recruit " + this_player()->query("id"));
			this_player()->set("title", "星宿老怪座前高徒" );
			CHANNEL_D->do_channel(this_player(), "chat",  "星宿老仙，德配天地，威震寰宇，古今无比！");
			return 1;
		}
		else{
			command("say 你对老仙我这么恭敬，今后前途不可限量啊！\n");
			this_player()->set_temp("ding_flatter", 1);
			return 1;
		}
	}
	else command("say 没有了吗？");
	return 1;
}

int give_drug()
{
	object drug, me, ob;

	me = this_object();
	ob = this_player();

	if(ob->query("family/family_name") == "星宿派" && (ob->query_skill("huagong-dafa", 1) > 100)){
		if(me->query("drug_count") >= 1 && !ob->query_temp("drug_give")){
			add("drug_count", -1);
			drug = new("/d/xingxiu" + drugs[random(sizeof(drugs))] );
			drug->move(ob);
			ob->set_temp("drug_give", 1);
			message_vision("$N对$n点了点头，交给$n一小包药粉。\n", me, ob);
			return 1;
		}
		if(ob->query_temp("drug_give"))
			command("say 我不是给过你了吗？");
		else command("say 你来晚啦，都被你师兄们拿走了。");
		return 1;
	}
	else return 0;
}
//老仙分忧？

string ask_job()
{
	object me, ob;
	me = this_player();

	if (me->query("family/family_name") == "武当派"
	 || me->query("family/family_name") == "天龙寺"
	 || me->query("family/family_name") == "峨嵋派"
	 || me->query("family/family_name") == "全真教"
	 || me->query("family/family_name") == "丐帮"
	 || me->query("family/family_name") == "华山派"
	 || me->query("family/family_name") == "少林派")
		return "你是白道来卧底的吧，还不快给我滚出去！！！";
	if (me->query("combat_exp") < 1000000)
		return "哈哈哈，你再加把力练功，很快就可以为老仙我分忧了。";
	if (me->query("job_name") == "老仙分忧")
		return "老仙现在心情还好，不用你来为我分忧。";
	if (me->query("combat_exp") > 4000000)
		return "老仙我最近对什么都没兴趣，不用你来为我分忧。";
	if (me->query("shen") >= 0 || me->query("shen") > -(me->query("combat_exp")/10))
		return "徒儿，看来你的心肠还不够黑啊，有些事你不问也罢。";
	if (interactive(me) && me->query_temp("job_busy"))
		return "你说要替老仙分忧，怎么还在这里发呆？";
	if (interactive(me) && me->query_condition("wait_xx_task"))
		return "老仙现在心情还好，不用你来为我分忧。";
	if (me->query_condition("job_busy"))
		return "老仙现在心情还好，不用你来为我分忧。";

	ob = new("/d/xingxiu/obj/di");
	ob->move(me);
	ob->set("name", BLU"蓝玉短笛"NOR);
	ob->set("long", BLU"这玉笛短得出奇，只不来七寸来长、通体碧蓝，晶莹可爱。\n" NOR);
	ob->set("xx_user", getuid(me));
	me->set_temp("xx_job", 1);
	message_vision("$N拿出一只玉制短笛，交给$n。\n", this_object(), me);
	return "老仙我最近心情不佳，徒儿你要多多为我分忧才是！\n";
}

void destroying(object obj, object me)
{
	message_vision("$N拿起$n仔细地端详了一会儿，满意地点了点头，脸上露出了笑容。\n", me, obj);
	destruct(obj);
}

void dest(object ob)
{
	if (!ob) return;
	if (userp(ob)) command("drop "+ob->parse_command_id_list()[0]);
	else destruct(ob);
}
//调用献宝程序段
int do_xian(string arg)
{
	object who, me, ob;
	mapping quest;
	who = this_player();
	me = this_object();

	if(who->is_busy() || who->is_fighting())
		return notify_fail("你正忙着呢。\n");
	if(me->is_busy() || me->is_fighting())
		return notify_fail("没看见老仙正忙着吗？\n");
	if(!arg || !objectp(ob = present(arg, who)))
		return notify_fail("你要献给老仙什么东西？\n");
	if(!who->query_temp("xx_job"))
		return notify_fail("连老仙现在的心情还没摸清楚就乱献东西？\n");

	message_vision(HIY"\n$n毕恭毕敬地将"+ob->query("name")+HIY"拿出，双手捧上，想要献给$N。\n\n"NOR, me, who);

	if(me->is_busy()) {
		command("say 我正忙着呢，你等等。");
		return notify_fail("老仙让你等等。\n");
	}
	if(!mapp(quest = who->query_temp("quest")) || !quest["id"]){
		command("say 你拿个"+ob->name()+CYN"给我干嘛？"NOR);
		return notify_fail("老仙对这东西不感兴趣。\n");
	}
	if ( quest["time"] < TIME_TICK){
		command("say 嗯，这么久才办完，你干什么去了？给我滚一边去！");
		who->apply_condition("wait_xx_task", 40);
		return notify_fail("完了，老仙生气了。\n");
	}
	if(userp(ob)){
		command("stare " + who->query("id"));
		command("say 竟敢用假货来欺骗本老仙，给我滚出去！");
		message_vision("\n说完$N长袖一挥，一股内劲拂出，就将$n扫出洞外！\n\n", me, who);
		who->move("/d/xingxiu/ryd1");
		message("vision","只听“呼”地一声，紧接着"+who->query("name")+"从日月洞里直飞了出来，摔了个四脚朝天！\n", environment(who), who);
		who->receive_wound("jing", 200,"被老仙踢飞而摔");
		who->receive_wound("qi", 250,"被老仙踢飞而摔");
		who->receive_damage("neili", 600);
		who->receive_damage("jingli", 500);
		who->apply_condition("wait_xx_task", 30);
		who->delete_temp("quest");
		who->set_temp("last_id", quest["last_id"]);
		who->start_busy(5);
		return notify_fail("糟糕，穿邦了！\n");
	}
	if(ob->query("name") != quest["name"] || ob->query("id") != quest["id"]) {
		command("hmm " + who->query("id"));
		command("say 你拿个"+ob->query("name")+"给老仙我有什么用？");
		return notify_fail("好象是你献错东西了。\n");
	}

	ob->move(me);
	me->start_busy(random(2));
	who->start_busy(2);
	destroying(ob, me);
	call_out("done", 3, who);
	return 1;
}
//调用献宝奖励
void done(object me)
{
	int job,x,j;
	job=me->query("job_time/星宿");
	x=job%50;

	if(!me || environment(me) != environment(this_object())) return;

	command("pat " + me->query("id"));
	command("say 不错不错，既然你找到了老仙我想要的东西，我就指点指点你吧。");
	if(me->query("family/family_name") == "星宿派") {
		if(me->query_skill("huagong-dafa",1) < 180)
			me->improve_skill("huagong-dafa", me->query("job_time/星宿"));
		if(me->query_skill("poison",1) < 180)
			me->improve_skill("poison", me->query("job_time/星宿"));		
		tell_object(me, "你目前已经为老仙分担了"+chinese_number(me->query("job_time/星宿"))+"次忧愁。\n");
	}
	tell_object(me, "你听了老仙的指点，功夫进步了不少！\n");
	
	//TASK_D->give_reward(me, me->query_temp("quest"), -1, ABS(me->query("job_time/星宿")/25),this_object(),"星宿");
	//GIFT_D->check_count(me,this_object(),"星宿");
	//me->add("job_time/星宿", 1);
    //关掉转到杀叛徒
	/*
	j = 18;
    if(me->query("m-card-vip")) j =  17;
    if(me->query("y-card-vip")) j =  15;
    if(me->query("buyvip"))     j =  10;

	if( random(job) > 400
	&& x == 0
    && random(me->query_int()) >= 30 
    && random(me->query_str()) >= 30
    && random(me->query("kar")) >=25
	//&& me->query("family/family_name")=="星宿派"
	&& random(j)<3 
	&& !me->query("quest/xx/tsz/zhuihun/pass")){
		command("whisper "+me->query("id")+" 看你如此努力为我大星宿不辞劳苦工作，我就把追魂钩绝技传授给你吧。");
		me->set("quest/xx/zhg/pass", 1);
		log_file("quest/zhuihungou",sprintf("%8s%-10s星宿任务第%s次的时候，从丁春秋献宝时，学到追魂钩法。\n",
			me->name(1),"("+ capitalize(getuid(me))+")",chinese_number(job)), me);
	}
	*/
	TASKREWARD_D->get_reward(me,"星宿",-1,0,0,5+random(2),0,0,0,this_object());
	
	
	log_file("job/fenyou",sprintf("%-18s 做星宿JOB，得经验 %d，潜能 %d。\n",
		me->query("name")+"("+getuid(me)+")",
		me->query_temp("quest/exp_reward"), me->query_temp("quest/pot_reward")),me);
        me->set("job_name","老仙分忧");
		me->clear_condition("job_busy");
		me->delete_temp("xx_job");
		return;
	
}

string *exclude_place = ({
	"/d/wuguan/","/d/death/","/d/wizard/","/d/sld/",
});


//杀叛徒，作为公共job ,改为单人，增加负神job，难度定位类似武当。

string ask_job5()
{
	mapping fam;
	object pp,where,target, *living ,me , ob ,partner,*list;
	
	int i,j,busy_time,shen;
	string str,menpai;
	
	me= this_player();
	//if (!me) return 0;

	shen=me->query("shen");

	if(shen > -10000 ) return "我们星宿派不需要你来帮忙。";
//100k 后启动
	if( me->query("combat_exp") < 100000 )
		return "你的实战经验太少了点吧，派你去我可实在不大放心！\n";

	//if((!pp=me->query("xx/partner")) && me->query("xx/pantu"))
	 //   return "你和你搭档完成上一次任务后，干吗去了！\n"+
		 //  "你只能放弃（ask ding about 放弃）当前这次任务了，不过不会受到经验的惩罚！";

//	if( me->query("xx/pantu") && ((time()-(int)me->query("xx/pantu_time"))<(12*60)) )
//		return "我不是叫你和"+pp->query("name")+"("+capitalize(pp->query("id"))+")到"+me->query("xx/pantu_place")+"去阻击那个叛徒了嘛！";

	if(me->query_condition("gb_mission") || me->query_condition("gb_busy"))
		return "老仙最讨厌臭叫化子，先扔掉你的丐帮帮务再说！";

	if( !wizardp(me) && me->query_condition("job_busy") ) {
		command("pat "+(string)me->query("id"));
		    return "你刚完成一次任务，先去休息一会儿吧！";
	}

	if( me->query("job_name") == "星宿杀叛徒")
	       return "你刚完成一次任务，先去休息一会儿吧！";

	me->delete("xx/pantu_busy");

	living = livings();
	for (i=0;i < sizeof(living);i++){
		j = random(sizeof(living));
		if (j <= 1 || j == sizeof(living)-1) continue;
		if(check(living[j]) ){
			target = living[j];
			str = environment(target)->query("short");
			if (str == "兵营"
			 || str == HIW"长廊"NOR
			 || str == "武僧堂"
			 || str == "松树林"
			 || str == "杂货铺"
			 || str == "密道"
			 || str == HIR"心禅堂"NOR
			) continue;
			if( get_place(base_name(environment(target)))!="" )
				break;
		}
	}
/*
	if (me->query_temp("xx_count") > 50) {
		me->delete_temp("xx_count");
		return "没有合适的搭档，你完成不了这个任务。";
	}

	if( !target )
		return "哪里有那么多任务让你一个人去完成，你过一会再来找我吧。";
	
	list = filter_array(users(), (: $1->query("combat_exp")>49999 :));
	
	partner = list[random(sizeof(list))];

	where = environment(partner);
*/
	if ((!environment(partner))
	 || environment(partner)->query("short")=="桃花源"
	 || wizardp(partner)
	 || environment(partner)->query("short")=="监狱"
	 || environment(partner)->query("short")=="黑屋"
	 || environment(partner)->query("short")=="机器人法庭"
	 || ((string)partner->query("family/family_name") == "古墓派" && partner->query_skill("yunu-xinjing", 1) < 101)
	 || (!interactive(partner))
	 || environment(partner)->query("no_fight")
	 || partner->query_temp("have_partner")
	 || partner->query("combat_exp") < me->query("combat_exp")/ 5
	 || partner == me
	 || partner->query_temp("user_type") == "worker" ){
		me->add_temp("xx_count",1);
		call_out("ask_job5", 0, me);
		return "";
	}
	else {
		if(!fam = (mapping)partner->query("family")) menpai="普通百姓";
		else menpai=fam["family_name"];

		me->set("xx/pantu",1);
		me->set("xx/partner",partner);

		partner->delete("env/block");
		partner->set_temp("have_partner",1);

		busy_time = 40;
		me->set("xx/pantu_time",time());
		me->apply_condition("job_busy",busy_time);
		me->set("xx/pantu_place",get_place(base_name(environment(target)))+environment(target)->query("short"));
		if(wizardp(me)) tell_object(me,base_name(environment(target)));

		ob = new(__DIR__"pantu3");
		ob->set("xx_target", me);
		ob->set("xx_partner",partner);
		ob->set("xx_place", environment(target));

		if(random(20) != 1) {
			ob->do_copy(me,0);
			me->set("xx/pantu_super",0);
		}
		else {
			ob->do_copy(me,1);
			me->set("xx/pantu_super",1);
		}
		ob->move("/d/xingxiu/caiji_room");
		me->set("xx/pantu_obj",ob);
		command("hmm "+me->query("id"));

		log_file("job/pantu",sprintf("%8s%-10s第%5d次任务开始，总计e：%d，p：%d；exp：%d\n",
			me->name(),"("+me->query("id")+")",me->query("job_time/星宿叛徒")+1,me->query("xx_jobe"),me->query("xx_jobp"),
			me->query("combat_exp")),me);
		log_file("job/pantu",sprintf("%8s%-10s第%d次任务搭档，总计e：%d，p：%d；exp：%d\n",
			partner->name(),"("+partner->query("id")+")",me->query("job_time/星宿叛徒")+1,partner->query("xx_jobe"),partner->query("xx_jobp"),
			partner->query("combat_exp")),me);

		tell_object(partner,HIY+"星宿老仙丁春秋用千里传音告诉你，请去到"+me->query("xx/pantu_place")+"配合"+HIM+me->name()+HIW+"("+ capitalize(me->query("id")) + ")"+HIY+"完成杀叛徒的任务。\n"NOR);
		return "听说最近那个混蛋在"+me->query("xx/pantu_place")+CYN"附近出没，你和"+
			menpai+ partner->name()+"("+ capitalize(partner->query("id")) + ")一起去阻击这个叛徒吧。";
	}
}

/*
int give_reward(object me)
{
	int e,p,t,t1,partner,high,myexp,paexp,d,low,e2= 100 + random(51),p2= 20+random(9);

	command("welcome");
	command("say 很好，你为星宿派铲除这个败类，我应该好好嘉奖你。");
	command("touch "+me->query("id"));

	if(!partner = me->query("xx/partner")){
		me->delete("xx/pantu");
		me->delete("xx_job5_finished");
		me->delete("xx/panntu_place");
		me->apply_condition("job_busy",6);
		me->delete("xx/pantu_time");
		me->delete("xx/pantu_super");
		command("say 这次任务你完成的相当不好，我非常不满意你的作为！");
		command("say 你和你的搭档完成任务后不直接回来，干吗去了！");
		command("say 你只能放弃当前这次任务了，不过不会收到经验的惩罚！");
		return 1;
	}

	myexp=me->query("combat_exp");
	paexp=partner->query("combat_exp");

	high=(myexp>paexp)?myexp:paexp;
	if(high==paexp)low=myexp;
	else low=paexp;
	t1 = ABS(12-(time()-(int)me->query("xx/pantu_time"))/60);
	if(t1<2)t1=2;
	if(t1>5)t1=5;

	d=ABS(high-low);

	e = 180 + random(70);

	if (me->query("xx/pantu_super"))
		e = e * (100+random(50)) / 100;

	if ( e > 500 ) e = 400 + random(100);
	p = e/5 + random(e/10);

	me->delete("xx/pantu");
	me->delete("xx_job5_finished");
	me->delete("xx/panntu_place");
	t = time()-(int)me->query("xx/pantu_time");

	me->delete("xx/pantu_time");
	me->delete("xx/pantu_super");

	me->add("job_time/星宿叛徒",1);
	me->add("xx_jobe",e);
	me->add("xx_jobp",p);
	me->add("combat_exp",e);
	me->add("potential",p);
	me->set("job_name","星宿杀叛徒");

	me->clear_condition("job_busy");

	partner->add("combat_exp",e2);
	partner->add("potential",p2);
	partner->add("xx_jobe",e2);
	partner->add("xx_jobp",p2);
	partner->set_temp("have_partner",0);

	if ( (int)me->query("potential", 1) > (int)me->query("max_pot", 1) )
		me->set("potential" , me->query("max_pot", 1) );
	if ( (int)partner->query("potential", 1) > (int)partner->query("max_pot", 1) )
		partner->set("potential" , partner->query("max_pot", 1) );

	if ((string)me->query("family/family_name") == "星宿派"
	   && me->query_skill("poison",1) < 180)
		me->improve_skill("poison", e);

	tell_object(partner,HIC"你被奖励了"+CHINESE_D->chinese_number(e2)+"点经验，"+CHINESE_D->chinese_number(p2)+"点潜能！\n"NOR);
	tell_object(me,HIC"你被奖励了"+CHINESE_D->chinese_number(e)+"点经验，"+CHINESE_D->chinese_number(p)+"点潜能！\n"NOR);

	log_file( "job/pantu",sprintf("%8s%-10s第%5d次任务结束，经验：%d，潜能：%d；总计e：%d，p：%d；exp：%d\n",
		me->name(),"("+me->query("id")+")",me->query("job_time/星宿叛徒"),e,p,me->query("xx_jobe"),me->query("xx_jobp"),
		me->query("combat_exp")),me);
	log_file( "job/pantu",sprintf("%8s%-10s第%5d次搭档结束，经验：%d，潜能：%d；总计e：%d，p：%d；exp：%d\n",
		partner->name(),"("+partner->query("id")+")",me->query("job_time/星宿叛徒"),e2,p2,partner->query("xx_jobe"),partner->query("xx_jobp"),
		partner->query("combat_exp")),me);

	return 1;
}

string ask_job5_times()
{
	object ob = this_player();

	if(!ob->query("job_time/星宿叛徒"))
		return "对不起，"+ob->name()+"，你好象还没有在我这里领过任务呢，加油干吧！";
	return ""+ob->name()+"，你帮我派杀死了"+HIY+CHINESE_D->chinese_number((int)ob->query("job_time/星宿叛徒"))+NOR+"个叛徒！";
}*/
//捉虫
string ask_job4()
{
	object me=this_player();
	int shen=me->query("shen");

	if(shen > -10000 ) return "我们星宿派不需要你来帮忙。";
	if( me->query("combat_exp") < 100000 )
		return "你的实战经验太少了点吧，派你去我可实在不大放心！\n";
	if (me->query("family/family_name") !="星宿派"){
		command("? "+ (string)me->query("id"));
		return "你不是星宿弟子，不能随便进毒虫谷。\n";
	}
	if( me->query("combat_exp") > 2000000 )
	if (me->query("job_time/星宿")+me->query("job_time/星宿叛徒")+me->query("job_time/星宿熬膏") > 500 )
		return "你的经验够多了，还是让别人去做吧！";

     //   if( me->query("job_name") == "星宿抓虫子")
        	//return "你刚抓完虫子，还是去休息会吧。";
	if( me->query_condition("job_busy"))
		return "你还忙着干别的呢，呆会再来吧。";
	if(me->query_condition("gb_mission") || me->query_condition("gb_busy"))
		return "老仙最讨厌臭叫化子，先扔掉你的丐帮帮务再说！";

	command("ok "+ (string)me->query("id"));
	me->set_temp("chonggu_allow",1);
	me->set_temp("xx_job4", 1);
	me->set("job_name", "星宿抓虫子");
	me->apply_condition("job_busy", 10);
	return "好吧，你现在可以进毒虫谷去了。";
}

int ask_hgdf() 
{
	object me = this_player();
	int j;
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$N向$n请教有关化功大法的真正奥妙。\n"NOR, me, this_object());
	if(me->query("family/family_name")!="星宿派")
	{
		command("?");
		command("say 你不是我门派弟子，难道是想来消遣老仙？"NOR);
		command("kick "+me->query("id"));
		return 1;
	}
	if (!me->query("quest/xx/dichuan"))
	{
		command("say 你不是我门派中嫡传弟子，难道是想来消遣老仙？"NOR);
		command("kick "+me->query("id"));
		return 1;
	}
	if(me->query("quest/hgdf/powerup"))
	{
		command("?");
		if (me->query("title")!="化功大法传人")
		{
			me->set("title",HBBLU+HIY"化功大法传人"NOR);
			me->set("mytitle/quest/hgdftitle",HBBLU+HIY"化功大法传人"NOR);
			
		}
		command("say 你已经学会了化功大法，难道是想来消遣老仙？"NOR);
		command("kick "+me->query("id"));
		return 1;
	}
	command("look "+me->query("id"));	
	//普通玩家三次
	
	if(me->query("quest/hgdf/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say 已经多次传授，你怎么都还没有领悟,真够笨的！");
		command("puke "+me->query("id"));
		return 1;
	}
	//武功学习之间需要间隔一天，经验需要间隔50K
	if( time()-me->query("quest/hgdf/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say 今天先教到到这里吧，明天吧。");
		return 1;
	}

	if(me->query_skill("huagong-dafa",1)<450)
	{
		command("look "+me->query("id"));
		command("say 以你当前的化功大法等级恐怕不足450，还是难以领悟，还是抓紧去练功去吧。");
		return 1;
	}
	if (!me->query("hgdf/giveheadover"))
	{
		if (!me->query_temp("hgdf/giveheadhs"))
		{
			command("say 最近华山派甚是猖狂，发展势头很猛，有碍我统一武林大业，你去把华山长老穆人清给我杀了，提头来见！\n");
			command("heng ");
			command("不管你用什么手段，总之要提头来见！\n");
			return 1;
		}
		if (!me->query_temp("hgdf/giveheadxz"))
		{
			command("say 最近灵鹫宫甚是猖狂，发展势头很猛，有碍我统一武林大业，你去把虚竹给我杀了，提头来见！\n");
			command("heng ");
			command("不管你用什么手段，总之要提头来见！\n");
		//me->delete_temp("hgdf/giveheadhs");
			return 1;
		}
		if (!me->query_temp("hgdf/giveheadtls"))
		{
			command("say 最近天龙寺甚是猖狂，发展势头很猛，有碍我统一武林大业，你去把一灯大师给我杀了，提头来见！\n");
			command("heng ");
			command("不管你用什么手段，总之要提头来见！\n");
			return 1;
		}
		if (!me->query_temp("hgdf/giveheadwd"))
		{
			command("say 最近武当派甚是猖狂，发展势头很猛，有碍我统一武林大业，你去把张三丰给我杀了，提头来见！\n");
			command("heng ");
			command("不管你用什么手段，总之要提头来见！\n");
			return 1;
		}

	}
	
	me->set("quest/hgdf/time",time());
	me->set("quest/hgdf/combat_exp",me->query("combat_exp")); 
	//i= random(20);
    me->delete_temp("hgdf/giveheadhs");
	me->delete_temp("hgdf/giveheadxz");
	me->delete_temp("hgdf/giveheadtls");
	me->delete_temp("hgdf/giveheadwd");
	j = 20;
    if(me->query("m-card-vip")) j =  18;
    if(me->query("y-card-vip")) j =  15;
    if(me->query("buyvip"))     j =  10;

	command("sigh "+me->query("id"));
	command("say 化功大法绝技乃是我星宿派的最高武功。既然你想打听，我就说给你听听，看你有没有这个悟性了。");
	command("whisper "+me->query("id"));
	command("smile "+me->query("id"));
	if(random(j)<3 
	   && random(me->query("int"))>40
	   && random(me->query("kar"))>=26)
	{
		tell_object(me,HIY"\n你按照星宿老仙的指点，对化功大法的终极奥妙似乎有些心得。\n"NOR);
        tell_object(me,HIG"\n一股毒气从丹田开始，延着任脉和督脉循环一圈，旋即又下重楼、入玄关，走命门，沉丹田。\n"+
			"随后全身毒气越转越快，渐渐成涓流入海之势。你忽然感觉全身经脉豁然贯通，一片神清气爽。\n"NOR);
		tell_object(me,HIW"\n你将星宿老仙讲解的内容和先前自己所学相互印证，随即起身，忍不住哈哈大笑。\n"NOR);
		tell_object(me,HIC"\n恭喜你历经千辛万苦，终于将化功大法融汇贯通。\n"NOR);
       
		
		//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("flatter "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("title",HBBLU+HIY"化功大法传人"NOR);
		me->set("mytitle/quest/hgdftitle",HBBLU+HIY"化功大法传人"NOR);
		me->set("quest/hgdf/powerup",1);
		log_file("quest/hgdf", sprintf("%8s(%8s) 失败%d次彻底领悟化功大法的绝技奥秘。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/hgdf/fail"),j,me->query("combat_exp")) );
	}
	else
	{
		me->add("quest/hgdf/fail",1);
		command("buddha");
		tell_object(me,HIY"你听了星宿老仙的指点，虽然听说了化功大法的奥秘，可是对化功大法的终极奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		log_file("quest/hgdf", sprintf("%8s(%8s) 化功大法奥秘绝技解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/hgdf/fail"),j,me->query("combat_exp")) );
	}

	return 1;
}

int accept_object(object who, object obj)
{
	int job,x,j;
	object obb;
	job=who->query("job_time/星宿");
	x=job%50;
	
	obb=obj->query("kill_by");

	if (who->query("family/family_name")!="星宿派") return 0;
//只有杀人后交付短笛才有效果，否则和献宝重复
	if (obj->query("id")=="duan di"
		&&who->query_temp("quest/type") == "杀"
		&&who->query_temp("quest/killover")
		&&who->query_temp("quest/corpse"))
	{
		
		//TASK_D->give_reward(who, who->query_temp("quest"), -1, "丁春秋" ,"星宿");
		who->add("job_time/星宿", 1);
    
	    TASKREWARD_D->get_reward(who,"星宿",-1,0,0,5+random(2),0,0,0,this_object());
    
		who->set("job_name","老仙分忧");
		/*log_file("job/fenyou",sprintf("%-18s 做星宿JOB，得经验 %d，潜能 %d，目前经验：%d。\n",
			who->query("name")+"("+getuid(who)+")", who->query_temp("quest/exp_reward"),
			who->query_temp("quest/pot_reward"), who->query("combat_exp")),who);
		*/
		who->clear_condition("job_busy");
		who->delete_temp("xx_job");
		who->delete_temp("quest");
		return 1;
	
	}
	///TASK_D->give_reward(me, me->query_temp("quest"), -1); //屏蔽by sohu

	
	if (obj->query("id")=="shouji" &&obj->query("name")=="穆人清的首级" && obb->query("id")==who->query("id"))
	{
		command("say 好大的一颗头颅！你为我杀了穆人清这狗贼，看华山还能猖獗到何时？\n");
		command("laugh ");
		command("chat 哈哈！我大星宿灭了华山，何愁江湖人物不再归顺与我？\n");
		who->set_temp("hgdf/giveheadhs",1);
		destruct(obj);
		return 1;
	}
	
	if (obj->query("id")=="shouji" &&obj->query("name")=="虚竹的首级" && obb->query("id")==who->query("id"))
	{
		if (!who->query_temp("hgdf/giveheadhs"))
		{
			command("say 我让你给我去杀了华山穆人清，你去了么？\n");
			return 1;
		}
		command("say 好大的一颗头颅！你为我杀了虚竹这狗贼，看灵鹫宫还能猖獗到何时？\n");
		command("laugh ");
		command("chat 哈哈！我大星宿灭了灵鹫宫，何愁江湖人物不再归顺与我？\n");
		who->set_temp("hgdf/giveheadxz",1);
		destruct(obj);
		return 1;
	}
	
	if (obj->query("id")=="shouji" &&obj->query("name")=="一灯大师的首级" && obb->query("id")==who->query("id"))
	{
		if (!who->query_temp("hgdf/giveheadxz"))
		{
			command("say 我让你给我去杀了灵鹫宫虚竹，你去了么？\n");
			return 1;
		}
		command("say 好大的一颗头颅！你为我杀了一灯这狗贼，看天龙寺还能猖獗到何时？\n");
		command("laugh ");
		command("chat 哈哈！我大星宿灭了天龙大理，何愁江湖人物不再归顺与我？\n");
		who->set_temp("hgdf/giveheadtls",1);
		destruct(obj);
		return 1;
	}
	if (obj->query("id")=="shouji" &&obj->query("name")=="张三丰的首级" && obb->query("id")==who->query("id"))
	{
		if (!who->query_temp("hgdf/giveheadtls"))
		{
			command("say 我让你给我去杀了一灯这秃驴，你去了么？\n");
			return 1;
		}
		command("say 好大的一颗头颅！你为我杀了张三丰这狗贼，看武当派还能猖獗到何时？\n");
		command("laugh ");
		command("chat 哈哈！我大星宿灭了武当，何愁江湖人物不再归顺与我？\n");
		who->set_temp("hgdf/giveheadwd",1);
		who->set("hgdf/giveheadover",1);
		destruct(obj);
		return 1;
	}

}


//ask 杀叛徒
string ask_pantu()
{
	object me, ob, *living, target;
	string str,str2,title;
	string str_temp;
	object room, oroom, lastroom;
	int i, j, k, a, b,t;
	string * exits,*dirs;
	string far;

	me=this_player();
	str2 = me->query_temp("xx/xx_job_place");
	str_temp = "";

	if (me->query_temp("xx/xx_job") && !me->query_temp("xx/xx_job_place"))
		return "啊……，对不起，地点有误，你放弃重新再来吧。";

	if (me->query("combat_exp") < 100000 )
		return "这位" + RANK_D->query_respect(me) + "武功未成，还是去做别的工作吧！";

	if(me->query_temp("quest/busy")) 
		return "现在我这里没有给你的任务，你还是先处理好你其他事情再说吧。";

	if(!wizardp(me)){
		if (me->query("shen")>-10000)
			return "哼，你觉得自己一身正气，还来我这做什么？";

		if ( me->query_condition("killer"))
			return "你现在是官府捉拿的要犯，还想帮我星宿叛徒？";

		if (me->query_temp("xx/xx_job"))
			return "我不是告诉你了吗，有人在捣乱。你就快去吧！";

		if (me->query("job_name") =="星宿叛徒")
			return "你刚做完星宿叛徒任务，还是先去休息一会吧。";

		//if (me->query("shen") < 1 && !wizardp(me) )
			//return RANK_D->query_respect(me) + "的正气还不够，我无法放心让你做这个任务！";

		if ( me->query_condition("job_busy")){
			if (me->query("job_name")=="星宿叛徒")
				return "现在暂时还没有工作让你去做。";
			if( me->query("job_name"))
				return "你刚做完"+me->query("job_name")+"任务，还是先休息一会吧。";
			return "你正忙着别的事情呢。";
		}

		if (me->query_condition("xx_job"))
			return "现在暂时没有适合你的工作。";
  
	}

	ob=new(__DIR__"pantu");
	ob->move(environment(this_object()));
		
	living = livings();
	
	for (i=0;i<sizeof(living);i++)
	{
		j = random(sizeof(living));
		if (j <= 1 || j == sizeof(living)-1) continue;
		if(check(living[j]) )
		{
			target = living[j];
			room = environment(target);
			if( !mapp(room->query("exits")) || sizeof(room->query("exits"))<1 ) continue;
			if( get_place(base_name(room))!="" ) 
			{
				oroom = room;
				if ( random(10)<3 && target->query("race")=="人类" ) {
					j = 0;
					break;
				}

				lastroom = room;
				j = 1+random(4);//改得好找些:)
				for(k=0;k<j;k++) {
					if (!room->query("exits")) break;
					exits = values(room->query("exits"));
					dirs = keys(room->query("exits"));
					b = sizeof(exits);
					t =0;
					while( (a=random(b))>=0 && b>1 && t<10 ) {
						t++;
						if(!room->valid_leave(ob, dirs[a])) continue;
						if (b==2)
							if ((exits[0]==base_name(lastroom) && exits[1]==base_name(oroom))
							 || (exits[1]==base_name(lastroom) && exits[0]==base_name(oroom)))
								break;
						if (exits[a]==base_name(lastroom) || exits[a]==base_name(oroom)) continue;
						break;
					}
					//write(sprintf("%d\n",t));
					lastroom = room;
					//暂时修改一下
					//if(!arrayp(exits)||!exits[a]||!(room = find_object(exits[a])) )
					if(!arrayp(exits)||(sizeof(exits)<(a+1))||!exits[a] || !(oroom = find_object(exits[a])) )
					//	if( !(room = load_object(exits[a])) )
							break;
				}
				if(k<j) continue;
				break;
				}
			
		}
	}

	if( !target || !room )
		return "暂时没有任务需要做，你过一会儿再来吧。";
    me->set_temp("xx/ob",ob); //这里记录npc，以便将来删除
	me->set_temp("xx/xx_job",1);
	me->set_temp("xx/xx_job_place", get_place(base_name(oroom))+oroom->query("short"));
	me->apply_condition("xx_job",20+random(10));
	me->apply_condition("job_busy",20+random(10));
	command("nod "+me->query("id"));
        
	if (me->query("bonus/星宿叛徒") >= 10 || !me->query("bonus/星宿叛徒") || me->query("bonus/星宿叛徒") < 1)
	{
		if (me->query("bonus/星宿叛徒") == 10)
			me->set("bonus/星宿叛徒", 5);
		else
			me->set("bonus/星宿叛徒", 1);
	}
	else
		me->add("bonus/星宿叛徒", 1);        

	ob->set_temp("target", me->query("id") );
	ob->setparty(me->query("bonus/星宿叛徒"),me->query("max_pot")-100,me->query("combat_exp"));
	
	//这里加进去状态
	ob->copy_player(me);//先初始化npc气血，否则被玩家一下击倒	
	
	ob->move(room); 
	title=ob->query("title")+ob->query("family/family_name");
	ob->set("title",title);

	log_file("job/xx_job",sprintf("%s(%s)开始做星宿杀叛徒job,目前实战经验：%d\n", me->name(),me->query("id"),me->query("combat_exp")),me);
	str = strip(me->query_temp("xx/xx_job_place"));

	if(wizardp(me) && me->query("env/test")){
		tell_object(me,"目标Npc从 "+base_name(oroom)+" 移到-> "+base_name(room)+"    "+room->query("short")+"\n");
		tell_object(me,"Round:"+me->query("bonus/星宿叛徒")+" !\n");
	}
	if (j)
		far = HIY+"周围方圆"+CHINESE_D->chinese_number(j)+"里之内"+GRN;
	else
		far = "";

	if (strlen(str)<=1) {
		tell_object(me, GRN"丁春秋在你的耳边悄声说道：据说"+ob->query("title")+HIC+ob->query("name")+GRN"正在\n"
			+HIY+ CHINESE_D->font(str) + GRN + far +"捣乱，你马上去给我巡视一圈。\n");
                
	} else
		tell_object(me, GRN"丁春秋在你的耳边悄声说道：据说"+ob->query("title")+GRN+"的"+ob->query("name")+"正在"+ me->query_temp("xx/xx_job_place") +GRN + far + "捣乱，你马上去给我巡视一圈。\n");
		//tell_object(me, GRN"丁春秋在你的耳边悄声说道：据说"+ob->query("title")+GRN+ob->query("name")+"正在"+ me->query_temp("xx/xx_job_place") +GRN + far + "捣乱，你马上去给我巡视一圈。\n");
        
	if (ob->query("family/family_name")=="星宿派")
		str_temp += GRN"丁春秋在你的耳边悄声说道："+RANK_D->query_self(this_object())+"已追查到此人是我星宿出身，尤为擅长"HIC+to_chinese(ob->query("f_w_skill"))+GRN"的功夫。\n"+
			RANK_D->query_respect(ob)+"若能将其诛杀，不但为江湖除去一害，也能为"+RANK_D->query_self(this_object())+"讨个公道，自当感激不尽。\n";
	else {
		str_temp+=GRN"丁春秋在你的耳边悄声说道：据门派弟子来报，此人是来自"HIY+ob->query("family/family_name")+GRN"的";
		if (random(2)==0)
			str_temp+="叛徒，";
		else
			str_temp+="高手，";
		str_temp+= "尤为擅长"HIC+to_chinese(ob->query("f_w_skill"))+GRN"的功夫。\n";
	}

	switch ((int)me->query("bonus/星宿叛徒"))
	{
		case 6..7:
			str_temp+=GRN"丁春秋在你的耳边悄声说道：此人的武功" + HIC + "颇为了得" + GRN + "，你可得小心对付哦。\n"NOR;
			break;
		case 8..9:
			str_temp+=GRN"丁春秋在你的耳边悄声说道：此人的武功" + HIC + "极其厉害" + GRN + "，你可得小心应付。\n"NOR;
			break;
		case 10..11:
			str_temp+=GRN"丁春秋在你的耳边悄声说道：此人的武功" + HIW + "已入化境" + GRN + "，打不过可不要逞能。\n"NOR;
	}	
       		
	tell_object(me, str_temp);
	tell_room( environment(this_object()), this_object()->name() + "在" + me->name() + "耳边小声地说了些话。\n", ({ me, this_object() }) );              
	return "你快去快回，一切小心啊。";
}

int check(object ob)
{
	object room;
	string room_name;

	if(!objectp(ob)
	|| !ob->query("startroom")      
	|| ob->query("env/invisibility")
	|| ob->query("no_quest")
	//|| member_array(ob->query("id"), no_kill_list) != -1
	|| userp(ob)
	|| ob->query("attitude")=="aggressive"
	|| ob->query("have_master")
	|| !objectp(room=environment(ob))
	|| room->query("no_fight")
	|| room->query("quest")
	|| room->query("outdoors") == "昆仑翠谷"
	|| room->query("short") == "地下黑拳市"
	|| room->query("short") == "武僧堂"
	|| strsrch(room_name = file_name(room),"/d/") != 0                    
	|| strsrch(room_name, "/d/wizard/") == 0
	|| strsrch(room_name, "/d/wuguan/") == 0
	|| strsrch(room_name, "/d/death/") == 0
	|| strsrch(room_name, "/d/mingjiao/lsd/") == 0
	|| strsrch(room_name, "/d/mingjiao/bhd/") == 0
	|| strsrch(room_name, "/d/shaolin/fumoquan") == 0
	//|| strsrch(room_name, "/d/xiaoyao/") == 0
	//|| strsrch(room_name, "/d/quanzhen") == 0
	//|| strsrch(room_name, "/d/menggu/") == 0
	|| strsrch(room_name, "/d/xiakedao/") == 0
	|| strsrch(room_name, "/d/luoyang/") == 0    
	|| strsrch(room_name, "/d/beijing/") == 0
	|| strsrch(room_name, "/d/huashan/hamasuperquest") == 0
	|| strsrch(room_name, "/d/baituo/") == 0)
		return 0;
	return 1;
}


int ask_finish()
{
	int e,shen,count,j,i,time;
	int bo,s,job,x;
	mapping fam;
	object ob,silver;
	ob = this_player();

	job=ob->query("job_time/星宿叛徒");
	x=job%50;

	if (!ob) return; 

	fam = ob->query("family");
	count = ob->query("job_time/星宿叛徒",1);

	bo = (int)ob->query("bonus/星宿叛徒");
	j = ob->query("bonus/星宿叛徒");

	e = 110*j + random(100);        

	if(e <= 100) e = 100+random(25);
	if(e>=500) e = 400+random(20);
			
	if(ob->query_temp("xx/xx_job_lost2")) {
		command("faint "+ob->query("id"));
		command("say "+ob->name()+"，据门派弟子来报，"+ob->query_temp("xx/xx_job_lost2_man")+"已经帮你把那恶贼给赶跑了！");
		ob->delete_temp("xx/xx_job");
		ob->delete_temp("xx/xx_job_place");
		ob->delete_temp("xx/xx_job_lost2");
		ob->delete_temp("xx/xx_job_lost2_man");
		ob->delete_temp("xx/xx_jobok");
		ob->add("bonus/星宿叛徒",-3);
		ob->apply_condition("job_busy", 3);
		return 1;
	}
	if(ob->query_temp("xx/xx_job_lost") && !ob->query_temp("xx/xx_jobok") ) {
		command("sigh "+ob->query("id"));
		command("say "+ob->name()+"你怎么搞的，居然让那恶贼给跑了！");
		ob->delete_temp("xx/xx_job");
		ob->delete_temp("xx/xx_job_place");
		ob->delete_temp("xx/xx_job_lost");
		ob->delete_temp("xx/xx_jobok");
		ob->add("bonus/星宿叛徒",-3);
		ob->apply_condition("job_busy", 3);
		return 1;
	}
       
	if(ob->query_temp("xx/xx_jobok") ){        	
		command("thumb "+ob->query("id"));
		command("say 很好，祝贺你完成了任务，下去休息休息吧！");            
		count += 1;
		ob->set("job_name","星宿叛徒");
		
		ob->delete_temp("xx/xx_job");
		ob->delete_temp("xx/xx_job_place");
		ob->delete_temp("xx/xx_jobok");
		
		if( ob->query("family/family_name")!="桃花岛")
			shen = -1;
		else
			shen = 0;

		//新调整武当收益计算方式，随难度增加奖励增多模式
		switch(bo)
		{
			case 0..5:
				TASKREWARD_D->get_reward(ob,"星宿叛徒",shen,0,0,1 + random(2),0,0,0,"丁春秋");                           
			break;
			case 6..7:
				bo = bo + 6;
				TASKREWARD_D->get_reward(ob,"星宿叛徒",shen,0,0,bo,0,0,0,"丁春秋");                         
			break;
			case 8..9:
				bo = bo + 10;
				TASKREWARD_D->get_reward(ob,"星宿叛徒",shen,0,0,bo,0,0,0,"丁春秋");    
			break;
			case 10..11:
				bo = bo * 2 + 1;
				TASKREWARD_D->get_reward(ob,"星宿叛徒",shen,0,0,bo,0,0,0,"丁春秋");
			break;
			default:
				TASKREWARD_D->get_reward(ob,"星宿叛徒",shen,0,0,1 + random(2),0,0,0,"丁春秋");
			break;
		}
		silver=new("clone/money/silver");
		s=10+random(20);
		silver->set_amount(s);
		silver->move(ob);
		message_vision(CYN"\n丁春秋抬起头来，对$N嘿嘿笑道，看你有如此本事，我这里有点赏钱给你，你拿去换酒喝去吧！\n"NOR,ob);
		message_vision(CYN"丁春秋顺手递给$N"+chinese_number(s)+CYN"两白花花的"HIW"银锭"CYN"！\n"NOR,ob);

		

		i = 40 - ob->query_condition("xx_job");
		if (i >= 18)
		{
			ob->apply_condition("job_busy",1);            			
		}
		else ob->apply_condition("job_busy", 3);
		     ob->apply_condition("xx_job",1);
		    
			
				
		// yttlg quest.
		// 经验值大于 10M 武当的随机数大于 2000
		// 福缘随机数大于 25 24小时一次 加入次数限制。
		
		time = time() - ob->query("quest/xx/tsz/zhuihun/time");                                           
		


		if (random(ob->query("job_time/星宿叛徒")) > 2000 
		&& time > 86400
		&& ob->query("combat_exp")>1000000
		&& random(ob->query("kar")) > 27
		&& x==0
		&& random(10)==2
		&& !ob->query_temp("quest/xx/tsz/zhuihun/story")
		&& !ob->query("quest/xx/tsz/zhuihun/pass")
		&& ob->query("family/family_name")=="星宿派") 
		{      
			
			ob->set_temp("quest/xx/tsz/zhuihun/story",1);
			//ob->set("quest/xx/tsz/zhuihun/time", time()); 这里不能设置时间，不然无法领悟
			log_file("quest/xxzhuihun", sprintf(HIR"%s(%s) 触发天山杖法追魂绝技。富源：%d；经验：%d。\n"NOR, ob->name(1),ob->query("id"), ob->query("kar"),ob->query("combat_exp")) );

			command("say "+ob->query("name")+",今日是为老仙最为开心之日,见你比日常尤为勤快，所以决定传授你些绝招。\n");
			command("say 只是这门绝技领悟起来不是容易，乃是我星宿派最为犀利的招式武技。\n");
			command("say 你能领悟了天山杖法追魂绝技的精意，那么江湖谁是你的敌手？\n");
			command("say 你要及时跟老仙我请教！\n");
		}
		return 1;
	}
	else {
		command("? "+ob->query("id"));
		command("kick "+ob->query("id"));
		command("say "+ob->name()+"你怎么搞的，任务都没做,我看你是捣乱来了！");  
		return 1;
	}
	return 1;
}


string ask_fail()
{
	object ob = this_player();
	if(ob->query_temp("xx/xx_job")){
		ob->delete_temp("xx/xx_job");
		ob->delete_temp("xx/xx_job_place");
		ob->delete_temp("xx/xx_jobok");//这里也有和wd类似的bug
		ob->apply_condition("xx_job",10);//设置jobbusy
		if (ob->query_temp("xx/ob"))
		{	
	       destruct(ob->query_temp("xx/ob"));
           ob->delete_temp("xx/ob");   
		}


		if (ob->query("bonus/星宿叛徒")<=5)
		{
			ob->apply_condition("job_busy", 8);
			ob->set("bonus/星宿叛徒",0); 
			return ob->name()+"，你太让我失望了，居然这么点活都干不好，先退下吧！";
		}
		else if (ob->query("bonus/星宿叛徒")>5)
		{
			ob->apply_condition("job_busy", 4); 
			ob->add("bonus/星宿叛徒",-3);
			return ob->name()+"，这个任务确实比较难完成，下次给你简单的，先退下吧！";                	
		}
	}
	return ob->name()+"，你又没在我这里领任务，瞎放弃什么呀！\n";
}
// 追魂夺命杖 绝技
string ask_zhuihun()
{
	
	object me=this_player();
	
	if (me->query("quest/xx/tsz/zhuihun/pass"))
	{
		 me->set("title",HIB"星宿派 追魂夺命客"NOR);
		 me->set("mytitle/quest/zhuihuntitle",HIB"星宿派 追魂夺命客"NOR);
		return "你已经融会贯通了字画中的追魂夺命绝技奥意。\n";
	}

	if (!me->query_temp("quest/xx/tsz/zhuihun/story"))
	{
		command("say 好吃懒做，天天不干活，来骚扰本老仙？\n");
		return "";
	}
	if (me->query("family/family_name")!="星宿派"||me->query("family/master_name")!="丁春秋")
	{
		return "你不是星宿派弟子，来此观摩什么？\n";
	}
	if (me->query_skill("tianshan-zhang",1)<500)
	{
		command("say 你的天山杖法级别不足500级,无法观摩出来什么。\n");
		return "嗯~？\n";
	}
	
	if (me->query_skill("huagong-dafa",1)<500)
	{
		return "你的化功大法级别不足500级,无法观摩出来什么。\n";
	}
	
	if (me->is_busy())
	{
		return "你正在忙碌中，稍安勿躁！\n";
	}

	if (time()-me->query("quest/xx/tsz/zhuihun/time")<86400)
	{
		return "这字画全凭领悟，如果频繁来此有害无益。\n";
	}
	command("look "+me->query("id"));
	command("pat "+me->query("id"));
	command("say 既然你有这份机缘，我就帮你！\n");
	me->start_busy(99);
	me->delete_temp("quest/xx/tsz/zhuihun/story");//删除临时标记，避免漏洞
	if (me->query_temp("canwu_zhuihun"))
	{
		return "你正在参悟中，稍安勿躁！\n";
	}
	remove_call_out("thinking_zh");
	call_out("thinking_zh",1,me);
	return "哼！\n";
}

int thinking_zh(object me)
{
	int i,j;
	j = 20;
    if(me->query("m-card-vip")) j =  18;
    if(me->query("y-card-vip")) j =  15;
    if(me->query("buyvip"))     j =  10;
	i=random(j);

	if (me->query("kar")>30) 
	{
	  log_file("quest/bug", sprintf("%s(%s) 参悟追魂夺命杖时，KAR异常，当前经验：%d。年龄：%d。kar:%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
	}
	if(me->query_temp("canwu_zhuihun")<(10+random(10)))
	{  
	  me->add_temp("canwu_zhuihun",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n你仔细观摩老仙的一招一式，将这些武功彼此印证，只觉得耳目一新...\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n忽然，你似乎抓住了一些明悟。\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n你陷入馄饨状态，大脑一片空明，似乎要抓住那个线索了！..\n"NOR);
			break;
		case 3:
			tell_object(me,HIW"\n你枯坐哪儿，甚是无聊，神情抑郁，似乎有些累了.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n你自言自语，神情疲倦之际，似乎遇到瓶颈了..\n"NOR);
			break;
		case 5:
			tell_object(me,MAG"\n你思维漂浮在空中，宛如婴儿沐浴.神清气爽.\n"NOR);
			break;
		default:tell_object(me,YEL"\n你叹了一口气，精神总是不能有效集中.\n"NOR);
			break;
	  }
      
	  tell_room(environment(me),HIC"\n"+me->query("name")+"面色平和，浑然忘我，似乎在思索着什么...\n"NOR, ({}));
	  
	  remove_call_out("thinking_zh");
	  call_out("thinking_zh",3+random(3), me);

   } 
   else if (i<3
			&& random(me->query("kar"))>28
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIY"\n$N「哈哈」大笑，自言自语说道：“原来是这样啊，真乃神技！”\n"NOR,me); 
		 message_vision(HIR"\n$N 从字画中悟出了天山杖法中的《追魂夺命绝技》的奥义。\n"NOR,me); 
        // message_vision(HIY"\n$N`心下恍悟，终于领悟了苏荃所传授的腾龙匕法这【美人三招】的奥秘！”\n"NOR,me); 
         log_file("quest/tszzhuihun", sprintf("%s(%s) 解密成功！第%d次参悟，机缘巧合下，成功参悟天山杖法之追魂夺命绝技的奥秘，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xx/tsz/zhuihun/fail"),
		 i,
		 j,
         me->query("combat_exp")));

		 me->set("quest/xx/tsz/zhuihun/time",time());
		 me->set("quest/xx/tsz/zhuihun/pass",1);
		 me->set("title",HIB"星宿派 追魂夺命客"NOR);
		 me->set("mytitle/quest/zhuihuntitle",HIB"星宿派 追魂夺命客"NOR);
		 me->delete_temp("canwu_zhuihun");
		 me->start_busy(1);
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N长叹一生，自言自语地说道：“这鬼字画中到底存在什么样的奥秘，真是奇了怪了。”\n"NOR,me); 
		 message_vision(HBYEL+HIR"\n参悟日月洞字画解密失败！\n"NOR,me); 
         log_file("quest/tszzhuihun", sprintf("%s(%s) 失败！第%d次失败参悟天山杖法追魂夺命绝技，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xx/tsz/zhuihun/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/xx/tsz/zhuihun/fail",1);
		 me->set("quest/xx/tsz/zhuihun/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_zhuihun");
		 return 1;
   }
	

}