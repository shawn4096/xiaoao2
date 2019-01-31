// /kungfu/class/emei/mie-jue.c
// 死尼姑灭绝
// Lklv 2001.10.18 update

#include <ansi.h>
inherit F_MASTER;
inherit NPC;
#include "miejue.h"
int ask_sword();
int ask_zhou();
int ask_guo();
int ask_jiuyin();
int ask_dragon();
int ask_mie();
int ask_jue();
int ask_jiuyang();
void create()
{
	set_name("灭绝师太", ({"miejue shitai", "miejue", "shitai"}));
	set("long","她就是峨嵋派第三代掌门人灭绝师太了。\n"
"她容貌算得极美，但两条眉毛斜斜下垂，一副面相便变得极是诡异，几乎\n"
"有点儿戏台上的吊死鬼味道。\n"
	);
	set("gender", "女性");
	set("attitude", "friendly");
	set("unique", 1);
	set("class", "bonze");

	set("age", 50);
	set("shen_type", 1);
	set("str", 42);
        set("int", 42);
        set("con", 42);
        set("dex", 42);
        set("max_qi", 13500);
        set("max_jing", 6500);
        set("neili", 14500);
        set("max_neili", 14500);
        set("jiali", 100);
		set("em/jiuyang/pass", 1);
		set("em/mie/pass", 1);
		set("em/jue/pass", 1);
		set("quest/em/hfj/liaoyuan/pass", 1);
	    set("combat_exp", 10000000);
	    set("chat_chance_combat", 40);
	    set("chat_msg_combat", ({
                (: perform_action, "sword.mie" :),
				(: perform_action, "sword.jue" :),
        	    (: perform_action, "sword.liaoyuan" :), 
					(: exert_function, "fengyun" :),   
					(: exert_function, "riyue" :), 
					(: exert_function, "youming" :),  
					(: exert_function, "tiandi" :),  
	    }));
        set_skill("dacheng-fofa", 200);
        set_skill("linji-jianzhen", 500);
        set_skill("linji-zhuang", 480);
        set_skill("jieshou-jiushi", 500);
        set_skill("huifeng-jian", 500);
        set_skill("sixiang-zhang", 480);
        set_skill("yanxing-daofa", 480);
        set_skill("hand", 500);
        set_skill("literate", 180);
        set_skill("strike", 480);
        set_skill("sword", 500);
        set_skill("blade", 480);
        set_skill("parry", 480);
        set_skill("dodge", 480);
        set_skill("force", 500);
        set_skill("anying-fuxiang",480);
        set("inquiry",([
		"倚天剑" : (: ask_sword :),
		"九阴真经" : (: ask_jiuyin :),
		"周芷若" : (: ask_zhou :),
		"郭靖" : (: ask_guo :),
		"黄蓉" : (: ask_guo :),
		"倚天屠龙" : (: ask_dragon :),
		"武林至尊" : (: ask_dragon :),
		"灭剑绝技" : (: ask_mie :),
		"绝剑绝技" : (: ask_jue :),
		"峨嵋九阳" : (: ask_jiuyang :),
        ]) );

        map_skill("force", "linji-zhuang");
        map_skill("sword", "huifeng-jian");
        map_skill("blade", "yanxing-daofa");
        map_skill("parry", "huifeng-jian");
        map_skill("dodge", "anying-fuxiang");
        map_skill("strike", "sixiang-zhang");
        map_skill("hand", "jieshou-jiushi");
        prepare_skill("parry", "huifeng-jian");
        prepare_skill("hand", "jieshou-jiushi");

        create_family("峨嵋派", 3, "掌门");

        setup();
        carry_object(BINGQI_D("changjian"))->wield();
        carry_object("/d/emei/obj/shoes")->wear();
        carry_object("/d/emei/obj/cloth")->wear();
}

void init()
{
        object me, ob;
        ::init();
        ob = this_player();
        me = this_object();
        if (interactive(ob = this_player()) && !wizardp(ob) && !is_fighting()) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
        }
}

void greeting(object me)
{
        int shen;
        if(!me) return;
        shen = me->query("shen");

        if ( file_name(environment(this_object())) != this_object()->query("startroom")) return;

        if(shen <= -200000 && me->query("family/family_name") == "峨嵋派"){
        	command("chat* kick2 "+me->query("id"));
        	command("say 你满眼瘴气，身带邪气，再和邪魔外道来往我开除你出峨嵋派！");
	}
	if(shen <0 && shen > -200000 && me->query("family/family_name") == "峨嵋派"){
		command("look "+me->query("id"));
		command("say 我看你满眼瘴气，身带邪气，最近是不是在外面做了什么坏事？");
	}
	else command("buddhi miejue shitai");
}

int ask_mie() 
{
	object me = this_player();
	int i;
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$N向$n请教有关灭剑绝技的真正奥妙。\n"NOR, me, this_object());
	
	command("look "+me->query("id"));	
	//普通玩家三次
	if(me->query("family/family_name")!="峨嵋派")
	{
		command("heng "+me->query_id());
		command("say 你和我门派有什么关系，赶紧给我滚！");
		return 1;
	}
	if(me->query("em/mie/pass"))
	{
		command("heng "+me->query_id());
		command("say 你已经解开此谜题，来消遣我老尼么？");
		return 1;
	}
	if(me->query("em/mie/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say 已经多次传授，你怎么都还没有领悟,真够笨的！");
		command("puke "+me->query("id"));
		return 1;
	}
	//武功学习之间需要间隔一天，经验需要间隔50K
	if( time()-me->query("em/mie/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say 今天先教到这里吧，明天吧。");
		return 1;
	}
	if(me->query("combat_exp")<4500000)
	{
		command("look "+me->query("id"));
		command("say 以你当前的经验恐怕还是难以领悟，还是抓紧去练功去吧。");
		return 1;
	}
    
	me->set("em/mie/time",time());
	me->set("em/mie/combat_exp",me->query("combat_exp")); 
	
	if (me->query("class")=="bonze")
	   i=random(14);
	else i= random(7);
	command("sigh "+me->query("id"));
	command("say 灭剑乃是我峨嵋回风拂柳剑的绝技。既然你想打听，我就说给你听听，看你有没有这个悟性了。");
	command("whisper "+me->query("id"));
	command("smile "+me->query("id"));
    command("say 徒儿啊，这招绝技乃是为师多年心血所得，你学习后一定要用此绝技把明教教徒给我全杀了。");
	command("say 看你方才点头的态度很真，我暂且相信你的誓言，否则我做鬼也饶不了你。");
	if(i>5 && random(me->query("kar"))>=20)
	{
		tell_object(me,HIG"\n你按照灭绝师太的指点，对灭剑的真正奥妙似乎有些心得。\n"NOR);
		tell_object(me,HIC"\n你把灭绝师太的招式从开始演练，一路演练下来，潇洒自如。\n"NOR);
       
		
		//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("buddha "+me->query("id"));
		command("haha "+me->query("id"));
		//me->set(QUESTDIR4+"sword",1);
		me->set("em/mie/pass",1);
		log_file("quest/miejian", sprintf("%8s(%8s) 失败%d次后，彻底领悟回风拂柳剑灭剑的绝技。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("em/mie/fail"),i,me->query("combat_exp")) );
	}
	else
	{
		me->add("em/mie/fail",1);
		me->set("em/mie/time",time());
		command("buddha");
		tell_object(me,HIY"你听了灭剑绝技的指点，虽然看见了灭剑的招式，可是对灭剑绝技的真正奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		log_file("quest/miejian", sprintf("%8s(%8s) 灭剑绝技解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("em/mie/fail"),i,me->query("combat_exp")) );
	}
	return 1;
}
int ask_jue() 
{
	object me = this_player();
	int i;
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$N向$n请教有关绝剑绝技的真正奥妙。\n"NOR, me, this_object());
	
	command("look "+me->query("id"));	
	//普通玩家三次
	if(me->query("family/family_name")!="峨嵋派")
	{
		command("heng "+me->query_id());
		command("say 你和我门派有什么关系，赶紧给我滚！");
		return 1;
	}
	if(me->query("em/jue/pass"))
	{
		command("heng "+me->query_id());
		command("say 你已经解开此谜题，来消遣我老尼么？");
		return 1;
	}
	if(me->query("em/jue/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say 已经多次传授，你怎么都还没有领悟,真够笨的！");
		command("puke "+me->query("id"));
		return 1;
	}
	//武功学习之间需要间隔一天，经验需要间隔50K
	if( time()-me->query("em/jue/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say 今天先教到这里吧，明天吧。");
		return 1;
	}

	me->set("em/jue/time",time());
	me->set("em/jue/combat_exp",me->query("combat_exp")); 
	if (me->query("class")=="bonze")
	   i=random(14);
	else i= random(7);
	command("sigh "+me->query("id"));
	command("say 绝剑乃是我峨嵋回风拂柳剑的绝技。既然你想打听，我就说给你听听，看你有没有这个悟性了。");
    command("say 徒儿啊，这招绝技乃是为师多年心血所得，你学习后一定要用此绝技把明教教徒给我全杀了。");
	command("say 看你方才点头的态度很真，我暂且相信你的誓言，否则我做鬼也饶不了你。");
	command("whisper "+me->query("id"));
	command("smile "+me->query("id"));
	if(i>5 && random(me->query("kar"))>=20)
	{
		tell_object(me,HIG"\n你按照灭绝师太的指点，对绝剑的真正奥妙似乎有些心得。\n"NOR);
		tell_object(me,HIC"\n你把灭绝师太的招式从开始演练，一路演练下来，潇洒自如。\n"NOR);
       
		
		//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("buddha "+me->query("id"));
		command("haha "+me->query("id"));
		//me->set(QUESTDIR4+"sword",1);
		me->set("em/jue/pass",1);
		log_file("quest/juejian", sprintf("%8s(%8s) 失败%d次后，彻底领悟回风拂柳剑绝剑的绝技。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("em/jue/fail"),i,me->query("combat_exp")) );
	}
	else
	{
		me->add("em/jue/fail",1);
		me->set("em/jue/time",time());
		command("buddha");
		tell_object(me,HIY"你听了灭剑绝技的指点，虽然看见了绝剑的招式，可是对绝剑绝技的真正奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		log_file("quest/juejian", sprintf("%8s(%8s) 绝剑绝技解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("em/jue/fail"),i,me->query("combat_exp")) );
	}
	return 1;
}
int ask_jiuyang() 
{
	object me = this_player();
	int i;
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$N向$n请教有关峨眉九阳的真正奥妙。\n"NOR, me, this_object());
	
	command("look "+me->query("id"));	
	//普通玩家三次
	if(me->query("family/family_name")!="峨嵋派")
	{
		command("heng "+me->query_id());
		command("say 你和我门派有什么关系，赶紧给我滚！");
		return 1;
	}
	if(me->query("emjy/pass"))
	{
		command("heng "+me->query_id());
		me->set("title",HIC"峨嵋"+HIR"九阳功"+HIG"传人"NOR);
		me->set("mytitle/quest/emjiuyangtitle",HIC"峨嵋"+HIR"九阳功"+HIG"传人"NOR);

		command("say 你已经解开此谜题，来消遣我老尼么？");
		return 1;
	}
	
	if (me->is_busy())
	{
		command("say 你在忙碌中！\n");
		return 1;
	}
	if(me->query("em/jiuyang/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say 已经多次传授，你怎么都还没有领悟,真够笨的！");
		command("puke "+me->query("id"));
		return 1;
	}
	//武功学习之间需要间隔一天，经验需要间隔50K
	if( time()-me->query("em/jiuyang/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say 今天先教到这里吧，明天吧。");
		return 1;
	}
	if(me->query_skill("linji-zhuang",1)<500)
	{
		command("pat "+me->query("id"));
		command("say 你的临济庄不够500级，尚未融汇贯通，说了你也不懂，还是抓紧去练功去吧。");
		return 1;
	}
	if(me->query("con")<40)
	{
		command("pat "+me->query("id"));
		command("say 峨眉九阳，全凭根骨，你的先天根骨不够40级，还是抓紧去练功去吧。");
		return 1;
	}
    
	me->set("em/jiuyang/time",time());
	me->set("em/jiuyang/combat_exp",me->query("combat_exp")); 
	
	command("sigh "+me->query("id"));
	command("say 峨嵋九阳乃是我峨嵋最高心法。既然你想打听，我就说给你听听，看你有没有这个悟性了。");
	command("say 徒儿啊，这招绝技乃是为师多年心血所得，你学习后一定要用此绝技把明教教徒给我全杀了。");
	command("say 看你方才点头的态度很真，我暂且相信你的誓言，否则我做鬼也饶不了你。");
	command("whisper "+me->query("id"));
	command("smile "+me->query("id"));
	
	message_vision(HIC"灭绝师太长叹一声后，缓缓说道，“峨嵋九阳功”乃是峨嵋派独门内功心法，\n"+
		"乃是由郭襄在觉远圆寂前口颂《九阳真经》时所默记下的部分经文衍生而来，\n"+
		HIY+"峨嵋派开宗立派的武功，主要根源就在于这一部分的《九阳真经》，与少林九阳功\n"+
		"武当九阳功及后来张无忌练成的九阳神功本属同源。觉远口诵《九阳真经》时，郭襄\n"+
		"和无色禅师、张君宝各自在旁默记了一部分《九阳真经》的经文，但因三人悟性及武学\n"+
		"根底不同，所学亦有所偏颇，而郭襄早年于武学一道所学甚博，故其后来自创的峨嵋九阳功\n"+
		"便是得其“博”之益，并凭此创立峨嵋派。。。。。。\n\n\n\n"+
		HIW"灭绝师太将这峨嵋最大的秘闻娓娓道来，你不禁听的如醉如痴，浑然忘记了时间的流逝.\m"NOR,me);
	
	tell_object(me,HIG"\n你按照灭绝师太的指点，正在对峨嵋九阳的真正奥妙用心思考。\n"NOR);
	me->set_temp("em/jiuyang/ask",1);
	me->start_busy(999);  
	remove_call_out("thinking");
	call_out("thinking",2,me);	
	return 1;
}

int thinking(object me)
{
  int i,j,total;
  if(!me) return 0;
	
 if(me->query_temp("em/jiuyang/ask")<(3+random(3)))
    { 
	  me->add_temp("em/jiuyang/ask",1);
      if(random(2)) tell_object(me,HIG"\n你认真回想着刚才灭绝师太的一招一式...\n"NOR);
             else tell_object(me,HIY"\n突然间，你似乎抓到了什么...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
	}
   else
   {  
	  me->delete_temp("em/jiuyang/ask");
      total = me->query("str") + me->query("con")+ me->query("dex")+ me->query("int");
      j = 25;
      if(me->query("m-card-vip")) j =  20;
      if(me->query("y-card-vip")) j =  17;
      if(me->query("buyvip"))     j =  15;
	  if (me->query("class")=="bonze")
	     i=random(j-2);
	  else i= random(j);
		
 
    if(i<3
		&& random(me->query("con"))>40
		&& random(me->query("kar"))>26)
	 {
		tell_object(me,HIG"\n你按照灭绝师太的指点，对峨嵋九阳的真正奥妙似乎有些心得。\n"NOR);
        tell_object(me, HIW"你按照灭绝师太所言，内息起自“长强穴”，随后自腰俞、阳关、命门、悬枢\n+"+
"诸穴，一路沿着脊椎上升，走的都是背上督任各个要穴，然后是脊中、中枢、筋缩、至阳、\n"+
"灵台、神道、身柱、陶道、大椎、痖门、风府、脑户、强间、后顶、而至顶门的“百会穴”。\n"NOR);
		tell_object(me,HIY"\n你历尽千辛万苦，终于得偿所愿，将峨嵋九阳融汇贯通。\n"NOR);
       	//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("emjy/pass",1);
		me->set("title",HIC"峨嵋"+HIR"九阳功"+HIG"传人"NOR);
		me->set("mytitle/quest/emjiuyangtitle",HIC"峨嵋"+HIR"九阳功"+HIG"传人"NOR);
		me->start_busy(1);
		log_file("quest/emjiuyang", sprintf("%8s(%8s) 失败%d次后，彻底领悟峨眉九阳的绝技。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("em/jiuyang/fail"),i,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("em/jiuyang/fail",1);
		me->set("em/jiuyang/time",time());
		command("buddha ");
		tell_object(me,HIY"你听了灭绝师太的指点，虽然听见了峨眉九阳的奥秘，可是对峨眉九阳功的真正奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->start_busy(1);
		log_file("quest/emjiuyang", sprintf("%8s(%8s) 峨眉九阳解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("em/jiuyang/fail"),i,me->query("combat_exp")) );
	  }
    	return 1;
  }

}
