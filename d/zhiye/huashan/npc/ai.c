// NPC: /d/huashan/npc/ai.c
// Date: Look 99/03/25
// Lklv modify 2001.10.18

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

int ask_quest();
int ask_weigong();
int ask_zhangwuji();
int ask_liangyi();

void create()
{
        set_name("矮老者",({"ai laozhe","ai"}));
        set("title","华山派第十二代弟子");
        set("long", "这就是在江湖中隐居的华山派矮老者。");
        set("age", 50);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 32);
        set("int", 32);
        set("con", 32);
        set("dex", 32);

        set("max_qi",13500);
        set("qi", 13500);
        set("max_jing", 5500);
        set("jing",5500);
        set("eff_jingli", 5000);
        set("max_neili", 24000);
        set("neili", 24000);
        set("jiali", 200);
        set("combat_exp", 12000000);
        set("score", 30000);

        set_skill("blade",  450);
		set_skill("dodge",  450);
        set_skill("force",  450);
        set_skill("parry",  450);
        set_skill("cuff", 450);
	    set_skill("sword", 450);
	    set_skill("literate",100);
        set_skill("poyu-quan", 450);
	    set_skill("huashan-qigong", 450);
		set_skill("fanliangyi-dao", 450);
        set_skill("huashan-jianfa",  450);
        set_skill("huashan-shenfa",  450);
        set_skill("zhengqi-jue", 200);

	    map_skill("dodge", "huashan-shenfa");
	    map_skill("sword", "huashan-jianfa");
		map_skill("blade", "fanliangyi-dao");
        map_skill("force","huashan-qigong");
        map_skill("parry","poyu-quan");
        map_skill("cuff", "poyu-quan");

        prepare_skill("cuff","poyu-quan");
	    set("chat_chance_combat",50);
	    set("chat_msg_combat", ({
		(: perform_action, "blade.sanshenfeng" :),
		//(: perform_action, "sword.feijian" :),
		//(: perform_action, "sword.junzi" :),
		//(: perform_action, "sword.kuaijian" :),
		//(: perform_action, "sword.lianhuan" :),
		//(: perform_action, "sword.sanqing" :),
	}));
        create_family("华山派",12,"弟子");

        set("inquiry", ([
                "鲜于通": (: ask_quest :),
				"六大门派围攻明教": (: ask_weigong :),
				"张无忌": (: ask_zhangwuji :),
				"反两仪决": (: ask_liangyi :),
        ]));
        setup();
	    carry_object(ARMOR_D("cloth"))->wear();
	    carry_object(BINGQI_D("blade"))->wield();
}
/*
void attempt_apprentice(object ob)
{
       // mapping fam;
        if (ob->query("family/family_name")!= "华山派"
         && ob->query("is/huashan")==1 ||!ob->query("quest/huashan") )
		{
                message_vision(CYN "$N！你这个华山派的叛徒还回来干什么 ？？？\n"NOR, ob );
                command("slap "+ob->query("id"));
                return;
        }
		if ( ob->query("fengset")) {
			command("say 你不是已经拜了风清扬为师了么？");
			return;
		}
        if ((int)ob->query("shen") <= 2000000) {
	        command("say 我华山派乃是堂堂名门正派，对弟子要求极严。");
        	command("say 在德行方面不足2M，" + RANK_D->query_respect(ob) + "是否还做得不够？");
			return;
        }
        if ((int)ob->query("max_pot") < 450) {
		command("say " + RANK_D->query_respect(ob)+"现在不需要我来指导，回去安心找你师傅学艺去吧。");
		return;
        }
        if( (int)ob->query_skill("huashan-qigong", 1) < 350 ) {
		command("say 你的华山气功还未到火候,老朽我可不能收你为徒。\n");
		return;
        }

        if( (int)ob->query_skill("force") < 350 ) {
		command("say 你的内功还未到火候,老朽我可不能收你为徒。\n");
		return;
        }
        command("say 好吧，我就收下你了,你可要为我们华山派争口气。");
        command("recruit " + ob->query("id"));
}
*/
int ask_quest()
{
        object me = this_player();
	    if (!me->query_temp("hu/quest1")) {
		command("say 他是华山前任的掌门....你问这个做什么？");
		command("consider " + me->query("id"));
		return 1;
        }
        else {
		command("say 他是华山前任的掌门，自己害死师兄却嫁祸明教。");
		command("say 光明顶一战，他已经给明教教主张无忌杀了。");
		command("sneer");
		me->set_temp("hu/quest1",2);
		return 1;
        }
}

int ask_weigong()
{
        object me = this_player();
	    if (!me->query_temp("liangyi/askhe")) {
		command("say ....你问这个做什么？");
		command("consider " + me->query("id"));
		return 1;
        }
        else {
		command("say 少林、武当、华山、崆峒、峨嵋、昆仑六大门派相约围攻光明顶。");
		command("say 既然你是昆仑三圣的门人，我就跟你说下这当中缘由。");
		command("whisper "+me->query("id"));
		command("say 经过光明顶这一战，明教教主张无忌以乾坤大挪移和九阳神功打败六大门派。");
		command("say 但即便他张无忌乃当世高手也曾差点为我和我师弟所杀！哼！");
		command("sneer");
		me->set_temp("liangyi/askweigong",1);
		return 1;
        }
}
int ask_zhangwuji()
{
        object me = this_player();
	    if (!me->query_temp("liangyi/askweigong")) {
		command("say ....你问这个做什么？");
		command("consider " + me->query("id"));
		return 1;
        }
        else {
		command("say 张无忌在光明顶大战六大门派，乃当世第一高手。");
		command("say 当时我和师弟用华山反两仪刀法将他困住，差点就将他杀了。");
		command("haha "+me->query("id"));
		command("say 我华山反两仪刀乃是华山刀法精粹，可惜啊，那帮前山的臭小子都去学剑法，殊不知本门的刀法也是一绝。");
		command("say 当然若配合昆仑的正两仪决那更是如鱼得水。");
		command("hero ");
		me->set_temp("liangyi/askzwj",1);
		return 1;
        }
}
int ask_liangyi()
{
        object me = this_player();
	 
		if( time()-me->query("quest/kl/lyj/liangyi/time")<86400 ){
			command("你来的太勤快了，要心平气和，休养生息方可。\n");
			return 1;
		}
		if (me->query_skill("fanliangyi-jue",1)<200 && me->query("quest/kl/lyj/liangyi/jue"))
		{
			message_vision(CYN"$n弯下腰来向$N小心的请教关于反两仪诀的原理。\n"NOR,this_object(),me);
			me->improve_skill("fanliangyi-jue", 10+random(me->query_int(1)));
			me->receive_damage("jing",random(10),"精力透支而");
			return 1;
		}
		if( me->query("quest/kl/lyj/liangyi/jue") ) {
			command("say 你已经解密了这个两仪剑诀，又何故开此玩笑呢？\n");
			return 1;
		}
		if (!me->query_temp("liangyi/askzwj")) {
			command("say ....你问这个做什么？");
			command("consider " + me->query("id"));
			return 1;
        }
        else {
		command("say 反两仪决乃是和昆仑正两仪决相反的功法奥秘。");
		command("say 当时师弟和我以及昆仑派的铁琴先生夫妇一同抗衡九阳神功以及乾坤大挪移。");
		command("say 正反两仪决配合在一起竟然严丝合缝，威力无穷！");
		command("say 既然你是昆仑三圣的弟子，那么我就把这套功法传授予你，能否明白就看你的了。");
		command("say ..........。");
		command("whisper "+me->query("id"));
		
			me->set_temp("liangyi/askfly",1);
			me->start_busy(999);
			call_out("thinking",1,me);
			return 1;
        }
}

int thinking(object me)
{
  int i,j,total;
  if(!me) return 0;
	
  if(me->query_temp("liangyi/askfly")<(10+random(3)))
    { 
	  me->add_temp("liangyi/askfly",1);
      if(random(2)) tell_object(me,HIG"\n你认真回想着刚才矮长老给你讲的反两仪奥妙...\n"NOR);
             else tell_object(me,HIY"\n突然间，你似乎抓到了什么...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
	}
   else
   {  
	  me->delete_temp("liangyi/askfly");
      j = 20;
      if(me->query("m-card-vip")) j =  18;
      if(me->query("y-card-vip")) j =  15;
      if(me->query("buyvip"))     j =  10;
	  i= random(j);
 
 
    if(i<3 && random(me->query("kar"))>=26)
	 {
		tell_object(me,HIG"\n你按照矮长老的指点，对反两仪决的真正奥妙似乎有些心得。\n"NOR);
        tell_object(me, HIW"你按照矮长老所言，按照地上所留的脚印开始演习，一圈一圈的不断演练\n+"+
							"初时极为晦涩，这反两仪决和先前的正两仪决截然不同，甚至完全相反。\n"+
							"走着走着，忽然间你领悟了这套步伐的原理，心中不由地大畅！长啸一声。\n"NOR);
		
		tell_object(me,HIY"\n你历尽千辛挖苦，终于得偿所愿，将反两仪决融汇贯通。\n"NOR);
       	me->improve_skill("fanliangyi-jue", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("quest/kl/lyj/liangyi/jue",1);
		me->start_busy(1);
		log_file("quest/klfliangyi", sprintf("%8s(%8s) 失败%d次后，彻底领悟反两仪决的绝技。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/kl/lyj/liangyi/fail"),i,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/kl/lyj/liangyi/fail",1);
		me->set("quest/kl/lyj/liangyi/time",time());
		command("poor ");
		tell_object(me,HIY"你听了矮长老的指点，虽然听见了反两仪决的奥秘，可是对反两仪决的真正奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->start_busy(1);
		me->delete_temp("liangyi");
		log_file("quest/klfliangyi", sprintf("%8s(%8s) 反两仪决解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/kl/lyj/liangyi/fail"),i,me->query("combat_exp")) );
	  }
    	return 1;
  }

}
