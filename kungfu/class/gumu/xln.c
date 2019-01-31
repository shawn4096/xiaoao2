// xln.c 小龙女
// By River@SJ 99.05
// 增加 乐音绝技Quest By River@SJ 9.25.2001

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

string ask_suo(); 
string ask_zhen();
string ask_shoutao();
string ask_yueyin();
string ask_qufengshu();
string ask_ynjfjj();
int pfm_yufeng();
int pfm_hebi();
int ask_hubo();

void create()
{
	object ob;
	set_name("小龙女", ({ "xiao longnv", "xiao", "longnv" }));
	set("title",HIW"古墓侠侣"NOR);
	set("nickname",HIC"神雕侠侣"NOR);
	set("long","盈盈而站着一位秀美绝俗的女子，肌肤间少了一层血色，显得苍白异常。\n"+
		"披著一袭轻纱般的白衣，犹似身在烟中雾里。\n");
	set("gender", "女性");
	set("age", 39);
	set("attitude", "friendly");
	set("no_bark",1);

	set("per", 48);
	set("str", 24);
	set("dex", 40);
	set("con", 25);
	set("int", 40);

	set("gmsanwu", 1);
	set("yueyin", 1);
	set("double_attack", 1);
	set_temp("double_attack", 1);
	set("shen", 10000);

	set("combat_exp", 12000000);
	set("max_qi", 29500);
	set("max_jing", 7600);
	set("eff_jingli", 6000);
	set("max_neili", 26000);
	set("neili", 26000);
	set("jiali", 200);
	set("unique", 1);

	set_skill("parry", 500);
    set_skill("hand", 500);
	set_skill("tianluo-diwang", 500);
	set_skill("force", 500);
	set_skill("dodge", 550);
	set_skill("sword", 500);
	set_skill("throwing", 500);
	set_skill("whip", 500);
	set_skill("meinu-quanfa", 500);
	set_skill("cuff", 500);
	set_skill("yunu-shenfa", 550);
	set_skill("yinsuo-jinling", 500);
	set_skill("yunu-jianfa", 500);
	set_skill("quanzhen-jianfa", 500);
	set_skill("yunu-xinjing", 500);
	set_skill("literate", 300);

	map_skill("force", "yunu-xinjing");
    map_skill("hand", "tianluo-diwang");
	map_skill("dodge", "yunu-shenfa");
	map_skill("cuff", "meinu-quanfa");
	map_skill("sword", "yunu-jianfa");
	map_skill("whip", "yinsuo-jinling");
	map_skill("parry","yinsuo-jinling");
	prepare_skill("cuff", "meinu-quanfa");

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: exert_function, "xinjing" :),
		(: perform_action, "whip.yueyin" :),
		(: perform_action, "whip.sanwu" :),
		(: perform_action, "whip.dian" :),
		(: perform_action, "whip.duoci" :),
		(: pfm_yufeng :),
	}));

	create_family("古墓派", 3, "女主人");

	set("inquiry", ([
		"杨过" : "过儿是我夫君，我知道他很爱我，可一直呆在这真怕他会闷。",
		"钥匙" : "嗯....这我可记不清楚，好象是放在古墓里面了吧。",
		"金铃索" : (: ask_suo :),
		"玉蜂针" : (: ask_zhen :),
		"手套" : (: ask_shoutao :),
		"白金手套" : (: ask_shoutao :),
		"乐音" : (: ask_yueyin :),
		"乐音绝技" : (: ask_yueyin :),
		"驱蜂术" : (: ask_qufengshu :),
		"周伯通" : (: ask_hubo :),
		"双手互博绝技" : (: ask_ynjfjj :),
			
	]));

	set_temp("apply/damage", 80);
	set_temp("apply/dodge", 100);
	set_temp("apply/attack", 100);
	set_temp("apply/armor", 80);
        
	setup();
	if (clonep()){
		ob = unew("/d/gumu/obj/shoutao");
		if (ob) {
			ob->move(this_object());
			ob->wear();        
		}
	}
	carry_object(BINGQI_D("changbian"))->wield();
	carry_object(BINGQI_D("changjian"));
	carry_object("/d/gumu/obj/yfzhen");
	carry_object("/d/gumu/obj/buxue1")->wear();
	carry_object("/d/gumu/obj/qun1")->wear(); 
}

void reset()
{
	object ob;

	if (clonep() && (ob = unew("/d/gumu/obj/shoutao"))) {
		ob->move(this_object());
		command("wear baijin shoutao");
	}
}

void attempt_apprentice(object ob)
{
	mapping fam = ob->query("family");
	if (!fam || fam["family_name"] != "古墓派"){
		command("say "+RANK_D->query_respect(ob)+"与本派素无来往，不知此话从何谈起？");
		return;
	}
	if( ob->query("gender") != "女性") {
		command("wanfu " + ob->query("id"));
		command("say 我可只收女徒，你去找我夫君试试吧。");

		return;
	}
	if (!ob->query("quest/gm/dichuan"))
	{
		command("say 你并非我古墓嫡传弟子，来找我作甚？");
		return;
	}
	if((int)ob->query_skill("yunu-xinjing", 1) < 350) {
		command("say 我古墓武功内功是基础,玉女心经不足350，不用来找我。"); 
		command("say " + RANK_D->query_respect(ob)+"是否还应该先在内功上多下点功夫？");
		return;
	}
	if((int)ob->query_skill("sword", 1) < 350) {
		command("say 你剑法这么差，我教的你不一定学得会。"); 
		command("say "+RANK_D->query_respect(ob)+"是否还应该在剑法（350）上多下点功夫？");
		return;
	}
	if((int)ob->query_int() < 50) {
		command("say 我的武功都要极高的悟性才能学会（后天50）。");
		command("say 要能达到炉火纯青之境，体质什么的倒是无关紧要，悟性却是半点也马虎不得。");
		command("say 这位"+RANK_D->query_respect(ob)+"的悟性还大有潜力可挖，还是请回吧。");
		return;
	}
	if((int)ob->query("shen") < 2000){
		command("say 我古墓弟子虽然不强调正神，但我讨厌歪门邪道。");
		command("say 这位" + RANK_D->query_respect(ob)+"正气不够2k，去做几件侠义的事后再来吧？");
		return;
	}
	command("say 嗯，看你还是个学武的料，我就收下你吧！");
	command("recruit " + ob->query("id"));
	ob->set("title","古墓派神雕侠侣传人");
	//return "我古墓本就人丁单薄，你要好好为我光大我古墓！\n";
}

string ask_suo()
{
	object ob = this_player();
	mapping fam = ob->query("family");
	if (!fam || fam["family_name"] != "古墓派" ||ob->query("family/master_name")!="小龙女")
		return RANK_D->query_respect(ob)+"，我已经多年未用金铃索了，也不知道放在何处了。";
	if (ob->query_skill("yinsuo-jinling", 1) < 350)
		return "这位"+ RANK_D->query_respect(ob) +"，金铃索灵活异常，你是否应该把武功练高些？";
	ob->set_temp("marks/银索", 1);
	command("nod " + ob->query("id"));
	return "不错，金铃索就放在此屋中，你自个找找吧。";       
}

int pfm_yufeng()
{
	object me,weapon;
	me = this_object();
	weapon = present("changbian",me);
	if( me->is_busy()) return 0;
	if( me->query_temp("hebi")) return 0;
	if( objectp(weapon)){
		set("jiali", 1);
		command("wield bian");
		command("perform yufeng");
		if(random(10) > 5){
			set("jiali", 50);
			command("unwield bian");
		}
		return 1;
	}
	else {
		if(present("changbian", environment(me)))
		command("get bian");
		else new(BINGQI_D("whip"))->move(me);
		command("wield bian");
		set("jiali", 1);
		command("wield bian");
		command("perform yufeng");
		if(random(10) > 5){
			set("jiali", 50);
			command("unwield bian");
		}
		return 1;
	}
	return 1;
}

string ask_zhen()
{
	object me = this_player();
	object *list;
	int i, j=0;

	if (me->query("family/family_name") != "古墓派"||me->query("family/master_name")!="小龙女")
		return "你不是我古墓派传人，你要这玉蜂针何用？";

	if( me->query("family/generation") > 4 )
		return "你现在还用不到玉蜂针。";

	if (present("yufeng zhen",me))
		return "你身上还有玉蜂针，怎么还来要？";

	if ( me->query_temp("yfzhen"))
		return "你不是刚要过了玉蜂针了么？不要这么贪心啊。";

	list = filter_array(objects(), (: $1->query("id") == "yufeng zhen":));

	i =  sizeof(list);
	while (i--)
		j += list[i]->query_amount();

	if ( j > 61)
		return "哎哟，玉蜂针已经发完了，你等会来要吧。";

	new("/d/gumu/obj/yfzhen")->move(this_object());
	command("give 10 yufeng zhen to " + me->query("id"));
	me->set_temp("yfzhen", 1);
	return "这些玉蜂针你先拿去用吧！";
}

string ask_shoutao()
{
	object me = this_player();

	if (me->query("family/master_name")!="小龙女")
		return ("这手套是我古墓派的宝物，你并非我的传人，不能给你！");

	if (present("baijin shoutao",this_object())) {
		command("give baijin shoutao to " + me->query("id"));
		return("这手套就给你了，你可要妥善保管好！");
	}
	else return ("你来晚了，手套已经让我送与他人了。");
}

string ask_yueyin()
{
	object me = this_player();
	mapping fam = me->query("family");
	object *dest;
	int i, j = 0;

	if (!fam || fam["family_name"] != "古墓派"||fam["master_name"] != "小龙女")
		return RANK_D->query_respect(me)+"与本派素无来往，不知此话从何谈起？";

	if(me->query_skill("yunu-xinjing", 1) < 150 )
		return "你的玉女心经等级不够，无法运力自如，练不了乐音! ";

	if(me->query_skill("yinsuo-jinling", 1) < 150 )
		return "你的银索金玲等级不够，还是先练练招式再说吧。 ";

	if(me->query("yueyin")) {
		command("? "+me->query("id"));
		return RANK_D->query_respect(me)+"不是已经掌握了乐音绝技了么？";
	}

	if ( me->query_temp("yueyin/ask"))
		return "你还不快去修炼？";

	dest = users();
	i = sizeof(dest);
	while(i--) {
		if (userp(dest[i]) && !wizardp(dest[i]) && dest[i]->query_temp("yueyin/ask"))
		j++;
	}
	if(j >= 1)
		return "嗯，我现在比较忙，刚指导了别人，你等会来打听吧。";

	command("say 嗯，乐音绝技就是将乐理融入武技中，银索金铃正可使用此技巧，不过可需要多多练习。");
	me->set_temp("yueyin/ask", 1);
	return "出大屋有片花丛，比较适合修炼，你专心去修炼吧，可不要忘记带一根鞭子哦。";
}

void kill_ob(object me)
{
	command("heng");
	command("throw yufeng zhen at " + me->query("id"));
	::kill_ob(me);
}


int ask_hubo()
{
	object me= this_player();
	if(!me->query_temp("marks/askzhou")|| me->query("gmhb"))
	{
		command("say 老顽童和一灯大师瑛姑三人在百花谷中隐居，养蜂种菜，莳花灌田，过得倒也逍遥自在。");
	  	command("say 你有空的时候拿我的玉蜂针做信物，去帮我探望他一下吧。");  
	  	return 1;
	}

    if( me->query_temp("marks/askzhou") )
    {
  	
  		command("say 我古墓派玉女心经，练的便是摒除七情六欲的扎根基功夫，这左右互搏之技，关键诀窍全在“分心二用”四字，凝神守一，心地空明。 ");
  		command("say 你且凝神静气，暗自默想如何右手使玉女剑法，左手使全真剑法，双手试演数招，自然豁然贯通。 ");
		command("say 你就安心在我这儿演练，我当面指导你，能否领悟就看你的悟性了。 ");
		command("say 别到处乱跑，就在我面前继续请教关于双手互博的知识吧。");

		me->delete_temp("marks/askzhou");
		me->set_temp("tryhb",1);
		me->set("quest/gumu/tryhb",1);
		return 1;
  	}

		command("pat " + me->query("id"));
		return 1;	
	
}
string ask_qufengshu()
{
	object me=this_player();

	if (me->query_skill("qufengshu",1)<150)
	{
		command("say 你的驱蜂术本领太低，我即便传授给你，也没什么大用。修炼到150级再来找我。\n");
		return "你可以去捅捅蜂巢，说不定会有收获。\n";
	}
	if (me->query("quest/gm/ynxj/qufeng/pass"))
	{
		command("say 你的驱蜂术已经学会了，别来烦我。\n");
		return "老大不小了，还这么调皮。\n";
	}
	if (time()-me->query("quest/gm/ynxj/qufeng/time")<86400)
	{
		command("say 你今天已经问过好几次了。\n");
		return "老大不小了，又这么调皮。\n";
	}
	if (me->query("family/family_name")!="古墓派"||me->query("family/master_name")!="小龙女")
	{
		command("你非我古墓派弟子，来问这个问题不觉得很奇怪么？");
		return "我大古墓的武功深奥无比。\n";
	}
	command("say 既然你想学习这门武技，我就传授于你，你的先驯养一箱蜜蜂，然后不断训化，慢慢这箱子蜜蜂就会听从你的指挥了.\n");
	command("say 这是我曾经用过的箱子，你先训练试试。\n");
	message_vision(HIY"\n\n\n\n小龙女递给$N一个白玉蜂的蜂箱。\n\n\n"NOR,me);
	call_out("xun_feng",1,me);
	return "";
}

int xun_feng(object me)
{
  int i,j; 
  if(!me) return 0;
	i=random(me->query("kar"));
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
  
  if(me->query_temp("canwu_xunfeng")<(10+random(10)))
   {  
	  me->add_temp("canwu_xunfeng",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n你仔细聆听小龙女的讲述，将小龙女所传授的训蜂术彼此印证，只觉得耳目一新...\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n忽然，几只小玉蜂嗡嗡地飞来。\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n你陷入馄饨状态，大脑一片空明，似乎要抓住那个线索了！..\n"NOR);
			break;
		case 3:
			tell_object(me,HIW"\n你枯坐哪儿，怎么指挥蜜蜂也不听你指挥，甚是无聊，神情抑郁，似乎有些累了.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n你自言自语，神情疲倦之际，觉得小蜜蜂太不挺好了，好像放弃.\n"NOR);
			break;
		case 5:
			tell_object(me,MAG"\n你思维漂浮在空中，宛如婴儿沐浴.神清气爽，小玉蜂越来越多.\n"NOR);
			break;
		default:tell_object(me,YEL"\n你叹了一口气，精神总是不能有效集中.\n"NOR);
			break;

	  }
      

	  tell_room(environment(me),HIC""+me->query("name")+"面色平和，浑然忘我，似乎在思索着什么...\n"NOR, ({}));

	  remove_call_out("xun_feng");
	  call_out("xun_feng",3+random(3), me);

   } 
   else if (i>25
			&& random(j)<6
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIC"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HIY"\n$N经过不断领悟，终于领悟了小龙女所传授的训蜂术的口诀奥秘！”\n"NOR,me); 
         log_file("quest/xlnxunfeng", sprintf("%s(%s) 成功！第%d次参悟，机缘巧合下，成功参悟训蜂术绝技的奥秘，当前幸运值：%d,当前随机值：%d,当前经验：%d,\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/gm/ynxj/qufeng/fail"),
		 i,
		 j,
         me->query("combat_exp"),
		 ));
              
		 me->set("quest/gm/ynxj/qufeng/time",time());
		 me->set("quest/gm/ynxj/qufeng/pass",1);
		 me->delete_temp("canwu_xunfeng");

		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N长叹一生，自言自语地说道：“看来这训蜂术真是不好解啊，继续努力吧。”\n"NOR,me); 
		 message_vision(HIY"\n参悟训蜂术绝技解密失败！\n"NOR,me); 
         log_file("quest/xlnxunfeng", sprintf("%s(%s) 失败！第%d次失败参悟训蜂术，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/gm/ynxj/qufeng/fail",1),
		 i,
		 j,
         me->query("combat_exp"),
		));        
		 me->add("quest/gm/ynxj/qufeng/fail",1);
		 me->set("quest/gm/ynxj/qufeng/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_xunfeng");
		 return 1;
   }

}

string ask_ynjfjj()
{
	object me=this_player();
	if (!me->query("quest/gumu/tryhb"))
	{
		command("say 我让你去先寻找周伯通打听下，你去了么？");
		return "怎么遇到这么个疲沓的弟子\n";
	}
	if (me->query_skill("yunu-jianfa",1)<500)
	{
		command("say 你的玉女剑法太低，我即便传授给你，也没什么大用。修炼到500级再来找我。\n");
		return "你可以去练习剑法吧。\n";
	}
	if (me->query_skill("yunu-xinjing",1)<500)
	{
		command("say 你的玉女剑法太低，我即便传授给你，也没什么大用。修炼到500级再来找我。\n");
		return "你可以去练习内功去吧。\n";
	}
	if (me->query("quest/gm/ynjf/hubo/pass"))
	{
		command("say 你的双手互博已经学会了，别来烦我。\n");
		me->set("mytitle/quest/ynjhubo",HIM"古墓玉女剑法真传"NOR);
		return "老大不小了，还这么调皮。\n";
	}
	if (time()-me->query("quest/gm/ynjf/hubo/time")<86400)
	{
		command("say 你今天已经问过好几次了。\n");
		return "老大不小了，又这么调皮。\n";
	}
	if (me->query("family/family_name")!="古墓派"||me->query("family/master_name")!="小龙女")
	{
		command("你非我古墓派弟子，来问这个问题不觉得很奇怪么？");
		return "我大古墓的武功深奥无比。\n";
	}
	if (!me->query("hubo/givejunzi"))
	{
		if (me->query("gender")=="女性")
			command("say 好吧，你就替我去寻找淑女剑，这淑女剑乃是我为过儿准备的礼物。");
		else command("say 好吧，你就替我去寻找君子剑，这君子剑乃是我为过儿准备的礼物。");
		return "君子淑女剑相配岂不是我大古墓的标志么？";
	}
	command("say 既然你想学习这门武技，我就传授于你,这奥秘我也是学自周伯通，.\n");
	command("say 能学好这门神奇武技的，一为我派的玉女心经，因其无欲无求而达到心境空灵，另外一门功夫就是先天功。\n");
	command("say 当初我是在襄阳城外，帮助老顽童训练玉蜂，他同时传授给我的这门绝技。\n");
	command("say 你可看好了，这就是我派玉女心经的终极奥秘。\n");
	message_vision(HIY"\n\n\n\n小龙女刷地抽出两把剑,玉女心经最后一章的功夫顿显，刹那间剑气纵横。\n\n\n"NOR,me);
	remove_call_out("think_hubo");
	call_out("think_hubo",1,me);
	return ""; 
}

int think_hubo(object me)
{
  int i,j; 
  if(!me) return 0;
  i=random(me->query("kar"));
  //j=random(10);
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;


  if(me->query_temp("canwu_hubo")<(10+random(10)))
   {  
	  me->add_temp("canwu_hubo",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n你仔细聆听师傅的讲述，将师傅所传授的双手互博彼此印证，只觉得耳目一新...\n"NOR);
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
      

	  tell_room(environment(me),HIC""+me->query("name")+"面色平和，浑然忘我，似乎在思索着什么...\n"NOR, ({}));

	  remove_call_out("think_hubo");
	  call_out("think_hubo",3+random(3), me);

   } 
   else if (i >= 26
	        && me->query("kar") <31
	        && random(j) <5
	        && random(me->query("int")) > 40)
 	{ 
        
         me->start_busy(1);     
         message_vision(HIC"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HIY"\n$N经过不断领悟，终于领悟了小龙女所传授的双剑互博的的口诀奥秘！”\n"NOR,me); 
		 message_vision(HIY"\n$N陡然醒悟，这不正是古墓中玉女心经最后一章的武功么？！”\n"NOR,me); 
         log_file("quest/gumuhubo", sprintf("%s(%s) 成功！第%d次参悟，机缘巧合下，成功双手互搏绝技的奥秘，当前幸运值：%d,当前随机值：%d,当前经验：%d,\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/gm/ynjf/hubo/fail"),
		 i,
		 j,
         me->query("combat_exp"),
		 ));

		 me->set("quest/gm/ynjf/hubo/time",time());
		 me->set("quest/gm/ynjf/hubo/pass",1);
		 me->set("title",HIM"古墓玉女剑法真传"NOR);
		 me->set("mytitle/quest/ynjhubo",HIM"古墓玉女剑法真传"NOR);
		 me->delete_temp("canwu_hubo");

		 return 1;
     }
	 else {
		 message_vision(HIG"\n$N双手运使，怎么也难以领悟这双手各自运使带来的技巧，好几次差点伤了自己。”\n"NOR,me); 
	     message_vision(HIG"\n$N长叹一生，自言自语地说道：“看来这玉女心经最后一章的武功真是不好练啊，继续努力吧。”\n"NOR,me); 
		 message_vision(HIY"\n参悟玉女剑法双手互搏绝技解密失败！\n"NOR,me); 
         log_file("quest/gumuhubo", sprintf("%s(%s) 失败！第%d次失败参悟玉女剑法双手互搏绝技，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/gm/ynjf/hubo/fail",1),
		 i,
		 j,
         me->query("combat_exp"),
		));        
		 me->add("quest/gm/ynjf/hubo/fail",1);
		 me->set("quest/gm/ynjf/hubo/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_hubo");
		 return 1;
   }

}
int accept_object(object me, object obj,object ob)
{
	ob = this_object();
		
	if (me->query("gender")=="男性" &&obj->query("id")=="junzi jian")
	{
		message_vision(HIC"$N将这柄君子剑拿在手中，翻来覆去的观看，面上脸色甚是欢喜。\n"NOR,ob);
		command("say 这把剑真是犀利无比，这么多年了，竟然还是如此的锋利。\n");
		command("say 嗯，既然你这么有心，我就收下这小礼物了。\n");
		message_vision(HIC"$N将这柄君子剑插入剑鞘，顺手扔到一旁，不再理会，但对你的态度明显有所好转。\n"NOR,ob);
		me->set_temp("hubo/givejunzi",1);
		me->set("hubo/givejunzi",1);
		destruct(obj);
		return 1;

	}
	if (me->query("gender")=="女性" &&obj->query("id")=="shunu jian")
	{
		message_vision(HIC"$N将这柄淑女剑拿在手中，翻来覆去的观看，面上脸色甚是欢喜。\n"NOR,ob);
		command("say 这把剑真是犀利无比，这么多年了，竟然还是如此的锋利。\n");
		command("say 嗯，既然你这么有心，我就收下这小礼物了。\n");
		message_vision(HIC"$N将这柄淑女剑插入剑鞘，顺手扔到一旁，不再理会，但对你的态度明显有所好转。\n"NOR,ob);
		me->set_temp("hubo/givejunzi",1);
		me->set("hubo/givejunzi",1);
		destruct(obj);
		return 1;

	}

}