// NPC zhangwuji.c 张无忌
// Modify By River@SJ 99.6

#include <ansi.h>
#include "zhangwuji.h";
inherit NPC;
inherit F_MASTER;
string ask_book();
string ask_qishang();
string ask_shu();
string ask_me();
int ask_hdg();
string ask_ling();
string ask_getling();
string ask_fel();
string ask_jiuyang();
string ask_xinfa();
string ask_was();
int ask_shlf();
int pfm_zhen();
int pfm_chan();
int pfm_yi();
int pfm_qishang();
int pfm_tougu();
int pfm_tisha();
int pfm_duanhun();
int ask_hu_quest();
int ask_hu();
int ask_ronghe();
int ask_qsqzj();

void create()
{
	object weapon;
	set_name("张无忌",({"zhang wuji","zhang","wuji"}));
	set("title",HIY"明教第三十四代教主"NOR);
	set("long", "他就是明教的第三十四代教主。脸上带着英资勃发的笑容。\n");
	set("age", 25);
	set("per", 32);
	set("attitude", "friendly");
	set("shen", 40000);
	set("str", 35);
	set("int", 30);
	set("con", 50);
	set("dex", 30);

	set("max_qi", 50000);
	set("max_jing", 7500);
	set("neili", 50000);
	set("eff_jingli", 7500);
	set("max_neili", 50000);
	set("jiali", 150);
	set("combat_exp", 15000000);
	set("unique", 1);
	set("no_bark",1);
	set("mj/qkdny/ronghe",1);
	set("mj/jiuyang/pass",3);
	set("mj/quest/yzs",1);
	//set("",1);


	set_skill("sword", 550);
	set_skill("dodge", 550);
	set_skill("force", 550);
	set_skill("dagger", 550);
	set_skill("strike", 550);
	set_skill("hanbing-mianzhang", 550);
	set_skill("piaoyi-shenfa", 550);
	set_skill("tiyunzong", 550);
	set_skill("shenghuo-lingfa", 550);
	set_skill("jiuyang-shengong", 550);
	set_skill("lieyan-dao", 550);
	set_skill("blade", 550);
	set_skill("liehuo-jian", 550);
	set_skill("taiji-jian", 550);
	set_skill("taiji-quan", 550);
	set_skill("parry", 550);
	set_skill("cuff", 550);
	set_skill("qiankun-danuoyi", 550);
	set_skill("qishang-quan", 550);
	set_skill("literate", 550);
	set_skill("medicine", 550);
	set_skill("xiaoyao-jian", 550);
    //set_skill("medicine", 550);
	set_skill("shenghuo-shengong", 550);
	set_skill("shenghuo-fumozhen", 550);
	set_skill("yingzhua-shou", 550);
	set_skill("hand", 550);

	map_skill("force", "jiuyang-shengong");
	map_skill("cuff","qishang-quan");
	map_skill("dagger","shenghuo-lingfa");
	map_skill("sword","taiji-jian");
	map_skill("dodge", "tiyunzong");
	map_skill("blade", "lieyan-dao");
	map_skill("strike", "hanbing-mianzhang");
	map_skill("parry", "qiankun-danuoyi");
	prepare_skill("cuff","qishang-quan");

	set("chat_chance_combat", 90);
	set("chat_msg_combat", ({
		(: pfm_hua :),
		//	(: pfm_hua :),
		(: pfm_tisha :),
		(: pfm_qishang :),
		(: pfm_tougu :),
		(: pfm_yi :),
		//(: pfm_zhen :),
		(: pfm_duanhun :),
	}));

	create_family("明教",34,"教主");

	set("inquiry", ([
		"波斯明教" : "我中土明教源于波斯明教，已有几百年厉史了，昔日小昭离我而去，\n"+
			"任波斯教主，不知她可好？吾心中常思念她，唉......",
		//"圣火令" : "圣火令是我明教的圣物，但已失落多年。",
		"谢逊" : "义父的踪迹，我是不会随便对人讲的。",
		"鲜于通"  : (: ask_hu_quest :),
		"胡青牛"  : (: ask_hu :),
		"蝴蝶谷"  : (: ask_hdg :),
		"秘籍"  : (: ask_book :),
		"七伤拳经"  : (: ask_qishang :),
		"七伤拳谱" : (: ask_shu :),
		"圣火令" : (: ask_me :),
		"铸令" : (: ask_ling :),
		"玄铁令" : (: ask_getling :),
		"乾坤大挪移神功" : (: ask_ronghe :),
		//"九阳神功" : (: ask_jiuyang :),
	    "圣火心法" : (: ask_xinfa :),
		"圣火令法绝技" : (: ask_shlf :),
		"七伤拳总决" : (: ask_qsqzj :),

		"赏善罚恶令" : (: ask_fel :),
		"万安寺" : (: ask_was :),
	]));

	set_temp("apply/damage", 90);
	set_temp("apply/dodge", 90);
	set_temp("apply/attack", 90);
	set_temp("apply/armor", 90);
	setup();

	if (clonep()){
		if( sizeof(filter_array(children(BINGQI_D("shangshan_ling")), (: clonep :))) > 0 )
			weapon = new(BINGQI_D("tieling"));
		else if( sizeof(filter_array(children(BINGQI_D("fae_ling")), (: clonep :))) > 0 )
			weapon = new(BINGQI_D("tieling"));
		else weapon = unew(BINGQI_D("sf_ling"));
		if (!weapon) weapon = new(BINGQI_D("tieling"));
		carry_object(BINGQI_D("sword"));
		weapon->move(this_object());
		weapon->wield();
		carry_object("/d/mingjiao/obj/white-cloth")->wear();
	}
}

void init()
{
	::init();
	add_action("do_lingwu","taojiao");
	add_action("do_kill", "kill");
	add_action("do_kill", "teamkill");
	add_action("do_kill", "tk");
	add_action("do_kill", "hit");
}

void reset()
{
	object ob;

	if (clonep()) {
		if (!(ob = unew(BINGQI_D("shangshan_ling"))))
			return;
		destruct(ob);
		if (!(ob = unew(BINGQI_D("fae_ling"))))
			return;
		destruct(ob);
		if (ob = unew(BINGQI_D("sf_ling"))) {
			ob->move(this_object());
			command("wield shangshanfae ling");
		}
	}
}

void attempt_apprentice(object ob)
{
	mapping fam = ob->query("family");
	if (!fam || fam["family_name"] != "明教"){
		command("say "+RANK_D->query_respect(ob)+"与本派素无来往，不知此话从何谈起？");
		return;
	}
	if((int)ob->query_skill("shenghuo-shengong", 1) < 350) {
		command("say 我明教之圣火神功乃极好的内家心法，不够350级圣火神功要继续修炼。");
		command("say " + RANK_D->query_respect(ob)+"是否还应该先在内功上多下点功夫？");
		return;
	}
	if((int)ob->query_skill("medicine", 1) < 80) {
		command("say 我所学极杂，所依者乃是熟读医书。");
		command("say "+RANK_D->query_respect(ob)+"是否还应该先在本草术理上多下点功夫？");
		return;
	}
	if((int)ob->query_skill("literate", 1) < 200) {
		command("say 我所学极杂，你要想学好必须先饱览诗书,不足200别来找我。");
		command("say "+RANK_D->query_respect(ob)+"是否还应该先在读书写字上多下点功夫？");
		return;
	}
	if((int)ob->query("shen") < 1000000) {
		command("say 学武之人，德义为先，功夫的高低倒还在其次，未练武，要先学做人。");
		command("say 你在德行方面不够1M正神，"+RANK_D->query_respect(ob)+"是否还做得不够？");
		return;
	}
	if(ob->query_int() < 32) {
		command("say 我的武功都要极高的悟性才能学会。");
		command("say 要能达到炉火纯青之境，体质什么的倒是无关紧要，悟性却是半点也马虎不得。");
		command("say "+RANK_D->query_respect(ob)+"的悟性还大有潜力可挖，还是请回吧。");
		return;
	}
	command("say 嗯，看你还是个学武的料，我就收下你吧！");
	command("say 多谢明尊敝佑，让我明教又得一良材，为康扶正义，把我明教发扬光大吧。");
	command("recruit " + ob->query("id"));
	ob->set("title",HIR"明教教主亲传弟子"NOR);
	/*if( ob->query_skill("dagger", 1) < ob->query_skill("balde", 1) ){
		ob->set_skill("dagger", ob->query_skill("balde", 1));
		tell_object(ob, "你受到教主指点，匕法已经达到了刀法的境界！\n");
	}*/
}

int do_kill(string arg)
{
	object ob,ob2;
	object me = this_player();
	ob2 = this_object();

	if (!arg) return 0;
	ob = present(arg, environment(me));
	if (ob == this_object() || ob == me) return 0;
	if (!ob || !ob->is_character()) return 0;


	if (userp(ob) && ob->query("family/family_name") == "明教") {
		if (me->query("family/family_name") == "明教") {
			message_vision(ob2->name()+"对$N喝道：身为明教弟子，竟然杀自己的同门？我宰了你！\n", me);
		}
		else {
			message_vision(ob2->name()+"对$N喝道：大胆狂徒，居然不把本教主放在眼里！\n", me);
			kill_ob(me);
		}
		me->set("vendetta/明教", 1);
		return 1;
	}
	return 0;
}

int ask_ronghe() 
{
	int i,j;
	object me = this_player();
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$N向$n请教有关乾坤大挪移绝技的真正奥妙。\n"NOR, me, this_object());
	if(me->query("family/family_name")!="明教"||me->query("family/master_id")!="zhang wuji")
	{
		command("?");
		command("say 你不是我的亲传弟子，难道是想来偷学？");
		command("kick "+me->query("id"));
		return 1;
	}
	if(me->query("int") < 40)
	{
		command("?");
		command("say 乾坤大挪移需要绝高的先天悟性，你的先天悟性不足40, 努力修炼去吧！"NOR);
		command("kick "+me->query("id"));
		return 1;
	}
	if(me->query("mjqkdny/pass"))
	{
		command("?");
		command("say 你已经彻底领会了乾坤大挪移绝技的奥秘，难道是想来消遣本公子？"NOR);
		command("kick "+me->query("id"));
		return 1;
	}
	command("look "+me->query("id"));	
	//普通玩家三次
	
	if(me->query("mjqkdny/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say 已经多次传授，你怎么都还没有领悟,真够笨的！");
		command("puke "+me->query("id"));
		return 1;
	}
	//武功学习之间需要间隔一天，经验需要间隔50K
	if( time()-me->query("mjqkdny/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say 今天先教到到这里吧，明天吧。");
		return 1;
	}
	if(me->query_skill("qiankun-danuoyi",1)<450)
	{
		command("look "+me->query("id"));
		command("say 以你当前的乾坤大挪移不足450级，恐怕还是难以领悟，还是抓紧去练功去吧。");
		return 1;
	}
    
	me->set("mjqkdny/time",time());
	me->set("mjqkdny/combat_exp",me->query("combat_exp")); 
	i= random(20);
	command("sigh "+me->query("id"));
	command("say 乾坤大挪移绝技乃是我明教的最高武功。既然你想打听，我就说给你听听，看你有没有这个悟性了。");
	command("whisper "+me->query("id"));
	command("smile "+me->query("id"));
	
	j = 20;
    if(me->query("m-card-vip")) j =  18;
    if(me->query("y-card-vip")) j =  15;
    if(me->query("buyvip"))     j =  10;
	i=random(j);
	if(i<3 
		&&random(me->query("int"))>40
		&& random(me->query("kar"))>=27)
	{
		tell_object(me,HIC"\n你按照张无忌的指点，对乾坤大挪移的终极奥妙似乎有些心得。\n"NOR);
        tell_object(me,RED"\n一股清凉的劲气从丹田开始，延着任脉和督脉循环一圈，旋即又下重楼、入玄关，走命门，沉丹田。\n"+
			"随后内力越转越快，渐渐成涓流入海之势。你感觉此时全身经脉豁然贯通，全身精力弥漫。\n"+
			"先前很多不明白的此时彻底想明白，幸亏先前那没有练成的十九句去强制修炼，否则非走火入魔不可。\n"NOR);
		tell_object(me,HIY"\n你将张无忌讲解的内容和先前自己所学相互印证，随即起身，忍不住哈哈大笑。\n"NOR);
		tell_object(me,HIC"\n恭喜你历经千辛万苦，终于解开乾坤大挪移终极奥秘。\n"NOR);
        tell_object(me,HIR"\n你已经将乾坤大挪移第七层神功彻底融汇贯通。\n"NOR);
       
		
		//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		//me->set(QUESTDIR4+"sword",1);
		me->set("mjqkdny/pass",1);
		me->set("title",HIR"乾坤"HIC"大"HIG"挪移"HIR"传人"NOR);		
		me->set("mytitle/quest/qkdnytitle",HIR"乾坤"HIC"大"HIG"挪移"HIR"传人"NOR);
		me->add("qkdny",1);
		log_file("quest/mjqkdny", sprintf("%8s(%8s) 失败%d次后，彻底领悟乾坤大挪移的绝技。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("mjqkdny/fail"),i,me->query("combat_exp")) );
	}
	else
	{
		me->add("mjqkdny/fail",1);
		command("poor ");
		tell_object(me,HIY"你听了张无忌的指点，虽然听说了这种武功的奥秘，可是对乾坤大挪移的终极奥妙全然不得要领。\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		//me->set("mj/qkdny/ronghe/time",time());
       // me->set("mj/qkdny/ronghe/time",time());
		log_file("quest/mjqkdny", sprintf("%8s(%8s) 乾坤大挪移终极奥秘解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("mjqkdny/fail"),i,me->query("combat_exp")) );
	}
	return 1;
}


int ask_shlf() 
{
	int i;
	object me = this_player();
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$N向$n请教有关圣火令法绝技的真正奥妙。\n"NOR, me, this_object());
	if(me->query("family/family_name")!="明教"||me->query("family/master_name")!="张无忌")
	{
		command("?");
		command("say 你不是我的亲传弟子，难道是想来偷学？");
		command("kick "+me->query("id"));
		return 1;
	}

	if(me->query("quest/mj/shlf/jueji/pass"))
	{
		command("?");
		command("say 你已经彻底领会了圣火令法绝技的奥秘，难道是想来消遣本教主？"NOR);
		command("kick "+me->query("id"));
		return 1;
	}
	command("look "+me->query("id"));	
	//普通玩家三次
	//先天臂力40
	if (me->is_busy())
	{
		command("say 你身处忙乱中!\n");
		return 1;
	}
	if(me->query("str")<40)
	{
		command("shrug "+me->query("id"));
		command("say 你的先天臂力太低了，不足40！");
		command("addoil "+me->query("id"));
		return 1;
	}
	if(me->query("quest/mj/shlf/jueji/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say 已经多次传授，你怎么都还没有领悟,真够笨的！");
		command("puke "+me->query("id"));
		return 1;
	}
	//武功学习之间需要间隔一天，经验需要间隔50K
	if( time()-me->query("quest/mj/shlf/jueji/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say 今天先教到到这里吧，明天吧。");
		return 1;
	}
	if(me->query_skill("shenghuo-lingfa",1)<450)
	{
		command("look "+me->query("id"));
		command("say 以你当前的七伤拳绝技不足450级，恐怕还是难以领悟，还是抓紧去练功去吧。");
		return 1;
	}
	if(!me->query("quest/mj/shlf/givezhang"))
	{
		command("look "+me->query("id"));
		command("say 你不去替我找到圣火令，恐怕对于这门绝技还是难以领悟，还是抓紧去完成这个任务吧。");
		return 1;
	}
	if (!me->query_temp("lianji/killcheng"))
	{
		command("say 成昆乃是我教中死敌，你去把他给我杀了，提人头来见，我就传授你此项绝技。");
		return 1;
	}
    if (!me->query_temp("lianji/songfa"))
	{
		command("say 你替我去办件事，向赵敏要一束我义父谢逊的金发，我怕她会坏我和周姑娘的大事。");
		command("smile zhang wuji");
		command("sigh zhang wuji");
		me->set_temp("lianji/askzhang",1);
		return 1;
	}
	me->set("quest/mj/shlf/jueji/time",time());
	me->set("quest/mj/shlf/jueji/combat_exp",me->query("combat_exp")); 
	i= random(20);
	command("sigh "+me->query("id"));
	command("say 圣火令法绝技乃是我明教的最高武功之一。既然你想打听，我就说给你听听，看你有没有这个悟性了。");
	command("whisper "+me->query("id")+"忽左忽右，右即为左，左即为左。...。");
	command("smile "+me->query("id"));
	me->start_busy(99);
	remove_call_out("thinking_shlf");
	call_out("thinking_shlf",1,me);	
	return 1;
}

int thinking_shlf(object me)
{
	int i,j,total;
	if(!me) return 0;
	
	if(me->query_temp("lianji/ask")<(3+random(3)))
    { 
	  me->add_temp("lianji/ask",1);
      if(random(2)) tell_object(me,HIG"\n你认真回想着刚才张无忌所讲述的圣火令法绝技的一招一式...\n"NOR);
             else tell_object(me,HIY"\n突然间，你似乎抓到了什么...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  remove_call_out("thinking_shlf");
	  call_out("thinking_shlf",3+random(3), me);
	}
	else
	{  
	  me->delete_temp("lianji/ask");
      total = me->query("str") + me->query("con")+ me->query("dex")+ me->query("int");
      j = 20;
      if(me->query("m-card-vip")) j =  18;
      if(me->query("y-card-vip")) j =  15;
      if(me->query("buyvip"))     j =  10;
	  i= random(j);
	  if(i<3 
		  &&random(me->query("str")>40)
		  && random(me->query("kar"))>=26)
	  {
		tell_object(me,HIC"\n你按照张无忌的指点，对圣火令法绝技的终极奥妙似乎有些心得。\n"NOR);
        tell_object(me,RED"\n你忽然体味到这圣火令法绝技的绝技精华，并回想在灵蛇岛中与波斯三使对战的经过。\n"NOR);
		tell_object(me,HIY"\n你将张无忌讲解的内容和先前自己所学相互印证，随即起身，忍不住哈哈大笑。\n"NOR);
		tell_object(me,HIC"\n恭喜你历经千辛万苦，终于解开圣火令法绝技终极奥秘。\n"NOR);
        tell_object(me,HIR"\n你已经将圣火令法绝技的终极奥秘彻底融汇贯通。\n"NOR);
    
		
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		//me->set(QUESTDIR4+"sword",1);
		me->set("quest/mj/shlf/jueji/pass",1);
		me->set("title",HBBLU+HIW"西域圣火令法绝技传人"NOR);
		me->set("mytitle/quest/shlftitle",HBBLU+HIW"西域圣火令法绝技传人"NOR);
		me->start_busy(1);
		log_file("quest/shlflianji", sprintf("%8s(%8s) 失败%d次后，彻底领悟圣火令法绝技奥秘。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/mj/shlf/jueji/fail"),i,me->query("combat_exp")) );
	   }
	   else
	   {
		me->add("quest/mj/shlf/jueji/fail",1);
		command("buddha");
		tell_object(me,HIY"你听了张无忌的指点，虽然听说了这种武功的奥秘，可是对圣火令法绝技的终极奥妙全然不得要领。\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		//me->set("mj/qkdny/ronghe/time",time());
       // me->set("mj/qkdny/ronghe/time",time());
	    me->start_busy(1);
		log_file("quest/shlflianji", sprintf("%8s(%8s) 圣火令法绝技终极奥秘解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/mj/shlf/jueji/fail"),i,me->query("combat_exp")) );
	   }
	 return 1;
	}

}

//七伤拳总决
int ask_qsqzj() 
{
	int i;
	object me = this_player();
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$N向$n请教有关七伤拳终极绝技的真正奥妙。\n"NOR, me, this_object());
	if(me->query("family/family_name")!="明教"||me->query("family/master_name")!="张无忌")
	{
		command("?");
		command("say 你不是我的亲传弟子，难道是想来偷学？");
		command("kick "+me->query("id"));
		return 1;
	}

	if(me->query("quest/mj/qsq/zongjue/pass"))
	{
		command("?");
		command("say 你已经彻底领会了七伤拳绝技的奥秘，难道是想来消遣本教主？"NOR);
		command("kick "+me->query("id"));
		me->set("title",HBRED+HIW"七伤断魂"NOR);
		me->set("mytitle/quest/qishangtitle",HBRED+HIW"七伤断魂"NOR);
		return 1;
	}
	command("look "+me->query("id"));	
	//普通玩家三次
	//先天臂力40
	if(me->query("con")<30)
	{
		command("shrug "+me->query("id"));
		command("say 你的先天根骨太低了，不足30！");
		command("addoil "+me->query("id"));
		return 1;
	}
	if(me->query("quest/mj/qsq/zongjue/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say 已经多次传授，你怎么都还没有领悟,真够笨的！");
		command("puke "+me->query("id"));
		return 1;
	}
	//武功学习之间需要间隔一天，经验需要间隔50K
	if( time()-me->query("quest/mj/qsq/zongjue/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say 今天先教到到这里吧，明天吧。");
		return 1;
	}
	if(me->query_skill("qishang-quan",1)<500)
	{
		command("look "+me->query("id"));
		command("say 以你当前的七伤拳绝技不足500级，恐怕还是难以领悟，还是抓紧去练功去吧。");
		return 1;
	}
	
	me->set("quest/mj/qsq/zongjue/time",time());
	me->set("quest/mj/qsq/zongjue/combat_exp",me->query("combat_exp")); 
	i= random(20);
	command("sigh "+me->query("id"));
	command("say 七伤拳绝技绝技乃是我明教的最高武功。既然你想打听，我就说给你听听，看你有没有这个悟性了。");
	command("whisper "+me->query("id")+"忽左忽右，右即为左，左即为左。...。");
	command("smile "+me->query("id"));
	
	remove_call_out("thinking_qsq");
	call_out("thinking_qsq",1,me);	
	return 1;
}

int thinking_qsq(object me)
{
	int i,j,total;
	if(!me) return 0;
	
	if(me->query_temp("qsq/ask")<(3+random(3)))
    { 
	  me->add_temp("qsq/ask",1);
      if(random(2)) tell_object(me,HIG"\n你认真回想着刚才张无忌所讲述的七伤拳绝技的一招一式...\n"NOR);
             else tell_object(me,HIY"\n突然间，你似乎抓到了什么...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  remove_call_out("thinking_qsq");
	  call_out("thinking_qsq",3+random(3), me);
	}
	else
	{  
	  me->delete_temp("qsq/ask");
      total = me->query("str") + me->query("con")+ me->query("dex")+ me->query("int");
      j = 20;
      if(me->query("m-card-vip")) j =  18;
      if(me->query("y-card-vip")) j =  15;
      if(me->query("buyvip"))     j =  10;
	  i= random(j);
	  if(i<3 && random(me->query("kar"))>=25)
	  {
		tell_object(me,HIC"\n你按照张无忌的指点，对七伤拳绝技的终极奥妙似乎有些心得。\n"NOR);
        tell_object(me,RED"\n你忽然体味到这七伤拳绝技的绝技精华\n"NOR);
		tell_object(me,HIY"\n你将张无忌讲解的内容和先前自己所学相互印证，随即起身，忍不住哈哈大笑。\n"NOR);
		tell_object(me,HIC"\n恭喜你历经千辛万苦，终于解开七伤拳绝技终极奥秘。\n"NOR);
        tell_object(me,HIR"\n你已经将七伤拳绝技的终极奥秘彻底融汇贯通。\n"NOR);
    
		
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		//me->set(QUESTDIR4+"sword",1);
		me->set("quest/mj/qsq/zongjue/pass",1);
		me->set("title",HBRED+HIW"七伤断魂"NOR);
		me->set("mytitle/quest/qishangtitle",HBRED+HIW"七伤断魂"NOR);
		
		log_file("quest/qsqzongjue", sprintf("%8s(%8s) 失败%d次后，彻底领悟七伤拳绝技奥秘。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/mj/qsq/zongjue/fail"),i,me->query("combat_exp")) );
	   }
	   else
	   {
		me->add("quest/mj/qsq/zongjue/fail",1);
		command("poke ");
		tell_object(me,HIY"你听了张无忌的指点，虽然听说了这种武功的奥秘，可是对七伤拳绝技的终极奥妙全然不得要领。\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		//me->set("mj/qkdny/ronghe/time",time());
       // me->set("mj/qkdny/ronghe/time",time());
		log_file("quest/qsqzongjue", sprintf("%8s(%8s) 七伤拳绝技终极奥秘解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/mj/qsq/zongjue/fail"),i,me->query("combat_exp")) );
	   }
	 return 1;
	}

}

string ask_was() 
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
	
	if (me->query("shen")<0) return "你坏事做多了，我不放心把这个任务交给你。";	
	if (me->query("combat_exp")<10000000) return "你武艺尚未有成，我不放心把这个任务交给你。";	
	
	 if (me->query("gmd_job/gmdscore"))
    {
	        command("say 你居然帮助过蒙古人，还围攻过我光明顶,但若是你能洗心革面悔过，并放弃以前得到的奖励。");
	        message_vision("张无忌要你放弃光明顶积分,你如果愿意就输入(answer yes ),不愿意就输入(answer no)！\n",me);
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
        
		 if (team[i]->query("gmd_job/gmdscore")) return "你的队伍里有人曾经帮助过蒙古郡主做事。";
		 
         if ((int)team[i]->query("shen")<0) 
			return "你的队伍里有奸佞小人，我不放心把这个任务交给你。";		 
		
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
		if (team[i]->query_condition("killer")) 
			return "你的队伍里有被官府通缉的人。";
		
		
		
		if (me == team[i]) continue;
/*
		if (!interactive(team[i]) || query_ip_number(team[i]) == query_ip_number(me)) {
		return "你还是将"+team[i]->query("name")+"换成其他人吧。;
		}*/

	}
      //if((maxexp-minexp) > 5000000){
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
	if (me->query_temp("was_job/asked") )
		return "你不是已经接过任务了吗？";
	
	if (me->query("job_name")=="勇闯万安寺")
		return "你刚做完勇闯万安寺任务，还是歇歇吧。";
	
	if (me->query("job_name")=="抗敌颂摩崖") return "你刚做完抗敌颂摩崖任务，还是歇歇吧。";
	
	if (me->query_condition("was_busy")) return "你刚做完勇闯万安寺任务，还是歇歇吧。";
	
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
	
			
	command("say 我刚才接到本教光明右使范遥的飞鸽传书，蒙古郡主赵敏派遣大批高手抓走了中原六大门派高手，并关押在万安寺内。\n" );
	

	me->set_temp("was_job/asked",1);
	me->apply_condition("job_busy", 30);
	me->apply_condition("was_busy", 30);
	me->apply_condition("was_job", 12);		
	command("say 万安寺内高手如云，你可潜入寺内救出六派高手。\n");
	
	
		
	if (team){
		
		me->set_temp("was_job/team",team);//记录队伍		
		
	}  		

	return "这批武士中不乏高手，你最好多带人手，待得人手到齐后，布下阵法，再去营救(yingjiu)，以策万全，切记切记。";	
	
}

int do_answer(string arg)
{
	object me = this_player();
	if (me->query_temp("fangqiscore")) {
	if (arg=="yes")
	{
		me->set("gmd_job/gmdscore",0);//清空gmd积分
		message_vision(HIY"$N对张无忌点了点头，说道，“既然是如此，我愿诚心辅佐教主！”\n"NOR,me);
	}
	else
	{
		message_vision(HIY"$N对张无忌摇了摇头，说道，“既然是如此，我是不能辅佐教主了！”\n"NOR,me);
	}
	remove_action("do_answer","answer");
	me->delete_temp("fangqiscore");
	}
	return 1;
}


