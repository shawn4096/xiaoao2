// NPC: /d/huashan/npc/mu_renqing.c
// Date: Look 99/03/25
// Modify by Lklv 2001.10.18
#define QUESTDIR "quest/华山派/鹰蛇生死搏/"

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_quest1();
string ask_quest2();
string ask_miji();
int do_jiejian();

void create()
{
        set_name("穆人清",({"mu renqing", "mu", "renqing"}));
        set("nickname","神剑轩辕");
        set("long", "这就是在江湖中侠名远播，疾恶如仇，华山派神剑轩辕穆人清。\n");
        set("age", 70);
        set("attitude", "peaceful");
        set("shen_type", 1);

        set("per", 26);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 29000);
        set("max_jing", 7800);
        set("eff_jingli", 7500);
        set("max_neili", 26500);
        set("neili", 26500);
        set("jiali", 200);
        set("combat_exp", 15200000);
        set("score", 29000);
		set("questbusy", 0);

        set("chat_chance_combat", 70);
        set("chat_msg_combat", ({
                (: perform_action, "sword.jianzhang" :),
 
			    (: perform_action, "sword.shijiushi" :),
				(: perform_action, "sword.luomu" :), 
				(: perform_action, "sword.fengyi" :),
  
		}));
        set_skill("sword",  500);
        set_skill("dodge",  500);
        set_skill("force",  500);
        set_skill("cuff", 500);
        set_skill("poyu-quan", 500);
        set_skill("huashan-jianfa", 500);
        set_skill("parry",  500);
        set_skill("literate", 230);
        set_skill("huashan-qigong", 500);
		set_skill("strike", 500);

		set_skill("hunyuan-zhang", 500);

		set_skill("huashan-shenfa", 500);
       // set_skill("zhengqi-jue", 200);

        map_skill("dodge", "huashan-shenfa");
        map_skill("force","huashan-qigong");
        map_skill("cuff","poyu-quan");
	    map_skill("strike","hunyuan-zhang");
 
		map_skill("parry","huashan-jianfa");
        map_skill("sword","huashan-jianfa");
        prepare_skill("strike", "hunyuan-zhang");

	    set_temp("apply/damage", 80);
        set_temp("apply/dodge", 80);
        set_temp("apply/attack", 80);
        set_temp("apply/armor", 80);
        create_family("华山派",12,"弟子");

        set("inquiry", ([
         "鹰蛇相争" : (: ask_quest1 :),
         "鹰蛇生死搏" : (: ask_quest2 :),
         "秘籍" : (: ask_miji :),
		 "截剑式" : (: do_jiejian() :),
        ]));
        setup();
        carry_object(BINGQI_D("sword"))->wield();
        carry_object(ARMOR_D("cloth"))->wear();
}
void init()
{
     add_action("do_go", "gensui");
     add_action("do_go", "goto");
}


void attempt_apprentice(object ob)
{
        mapping fam;
    if (mapp(fam=ob->query("family")) 
		&& (string)fam["family_name"] != "华山派"  
		&& (int)ob->query("is/huashan")==1
		|| !ob->query("quest/huashan")) {
                message_vision(CYN "$N！你这个华山派的叛徒还回来干什么 ？？？\n"NOR, ob );
                command("slap "+ob->query("id"));
                return;
        }
	if (ob->query("fengset")) {
		command("say 你不是已经拜了风清扬他老人家为师了么？");
		return;
	}
	if(ob->query("quest/huashan")=="剑宗"){
                command("heng");
                command("say 哼哼！剑宗弟子早已离开华山，不再是华山派弟子，你又来这里，难道是想争夺这掌门之位？");
                return;
        }
	if (ob->query_skill("huashan-qigong",1) < 350 ) {
		command("say 你的华山气功修为太差，抓紧修炼吧。");
		return;
	}
    if ((int)ob->query("shen") <= 2000000) {
	        command("say 我华山派乃是堂堂名门正派，对弟子要求极严2m。");
	        command("say 在德行方面，" + RANK_D->query_respect(ob)+"是否还做得不够？");
	        return;
        }
    if ((int)ob->query("max_pot") < 450) {
	        command("say " + RANK_D->query_respect(ob)+"现在不需要我来指导，回去安心找你师傅学艺去吧。");
	        return;
        }
        command("say 好吧，我就收下你了,你可要为我们华山派气宗争口气。");
        command("recruit " + ob->query("id"));
        ob->set("title","华山派气宗亲传弟子");
        ob->set("quest/huashan","气宗");
		return;
}

string ask_quest1()
{
        mapping fam;
        object me;
        int exp, exp2, i;
        me = this_player();
        exp = (int)me->query("combat_exp", 1);
        exp2 = (int)me->query(QUESTDIR+"combat_exp", 1);
        i = (int)me->query("job_time/华山",1);
        fam = me->query("family");
        
        if (!fam || fam["family_name"] !="华山派")
                return RANK_D->query_respect(me)+"与本派素无来往，不知此话从何谈起？\n";

      if (!me->query(QUESTDIR+"归辛树/over"))
        return "我华山派有位前辈观看鹰蛇相争，创出一门鹰蛇生死搏的绝学！\n";

        if(me->query_temp(QUESTDIR+"start2"))
                return "我不是已经和你说过了吗？\n";

        if( i < 2000 )
                return "你为我华山派做出的贡献微薄，怎能告诉你这等机密要事？\n";
         //华山任务至少完成1000次 by daidai

        if(exp2 && exp-exp2 < 200000)
                return "你当前的经验恐怕还是难以有所帮助，还是抓紧去练功去吧。\n";
         //经验间隔200k by daidai

        if(me->query(QUESTDIR+"time") && time()-me->query(QUESTDIR+"time")<86400)
                return "今天就到这里吧，你明天再来吧。\n";
        
        if(me->query(QUESTDIR+"pass"))
                return "你不是已经会了吗？\n";

        if(me->query(QUESTDIR+"fail")>=3 && me->query("registered")<3)
                return "我已经和你讲过多次了，你年纪不比我大，为何记性如此差啊？\n";
        me->set_temp(QUESTDIR+"start2", 1);
        me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
        me->set(QUESTDIR+"time",time());
         message_vision(CYN"\n穆人清挥手招来一位仆人！\n"NOR, me);
        return "这松树林后面的山涧里常有鹰蛇出没，我华山派七十二路鹰蛇生死搏便是前辈高手在那里观看鹰蛇相斗有感而创。
你若有兴趣就让仆人带你去吧(gensui)，说不定有所收获呢！\n";
}

string ask_quest2()
{
        mapping fam;
        object me;
        me = this_player();
        fam = me->query("family");

        if (!fam || fam["family_name"] !="华山派")
                return RANK_D->query_respect(me)+"与本派素无来往，不知此话从何谈起？\n";

        if(!me->query(QUESTDIR+"over"))
          return "那是我华山派的绝学，自从第九代掌门丧命于光明顶之后就失传了，只留下一本无人能参透的秘籍残本。\n";
 
        tell_object(me,HIC"\n你将刚才所见以及自己的感悟一一告诉了穆人清。\n"NOR);
        me->set(QUESTDIR+"pass",1);
        me->delete(QUESTDIR+"over");
        return "既然如此，我这里有本鹰蛇生死搏的秘籍残本，也许你能从中学到点东西。\n";
}
string ask_miji()
{
        mapping fam;
        object me,book;
	int exp, exp2;
        me = this_player();
        fam = me->query("family");

        if (!fam || fam["family_name"] !="华山派")
                return RANK_D->query_respect(me)+"与本派素无来往，不知此话从何谈起？\n";

       if(me->query_temp(QUESTDIR+"归辛树/over"))
                return "你已经拿到秘籍了，还不快给我？\n";

      if(!me->query(QUESTDIR+"归辛树/over")){
                exp = (int)me->query("combat_exp", 1);
                exp2 = (int)me->query(QUESTDIR+"combat_exp", 1);

      if(exp2 && exp-exp2 < 200000)
                return "你当前的经验恐怕还是难以有所帮助，还是抓紧去练功去吧。\n";
         //经验间隔200k by daidai

        if(me->query(QUESTDIR+"time") && time()-me->query(QUESTDIR+"time")<86400)
                return "今天就到这里吧，你明天再来吧。\n";

        if(me->query_temp(QUESTDIR+"start"))
                return "我不是已经和你说过了吗，你还不去杭州找我徒儿？\n";

          me->set_temp(QUESTDIR+"start", 1);
                return "秘籍残本我交给我徒儿归辛树了，他在杭州一带，你去问他取回秘籍吧。\n";
          
           }
       if(!me->query(QUESTDIR+"pass"))
          return "秘籍？什么秘籍？我这里只有一本武学残篇，你可看不懂哦！\n";

        book = unew("/d/huashan/npc/obj/yingshe-book.c"); 
        if(!clonep(book)) return "你来晚了，鹰蛇生死搏的秘籍残本已被本派其他弟子拿走了。";
         
        if(clonep(book) && book->violate_unique()){
               destruct(book);
               return "你来晚了，鹰蛇生死搏的秘籍残本已被本派其他弟子拿走了。";
        }
        book->move(this_player());
        return "我这里有本「鹰蛇生死搏秘籍残本」，你拿回去好好钻研，务必重现本派绝学。";
}

int do_go(string arg)
 {
      object me;
      me = this_player();
      if(!living(me) ) return 0;
      if(! me->query_temp(QUESTDIR+"start2")) return 0;        
      if (me->is_busy() || me->is_fighting())
        return notify_fail("你正忙着哪！\n");
      if( !arg || arg != "puren")
        return notify_fail("你要跟谁走啊？\n"); 

         message_vision(CYN"\n仆人说道：“跟我来吧！”，然后向外走去，$N急忙跟上！\n"NOR, me);
          me->move("/d/huashan/ys_houshan");     
        return 1;
}


int accept_object(object who, object ob,object me)
{
        me= this_object();

        if( ob->query("id") != "muxia"){
                command("say 你给我这东西干吗？");
                return 0;
        }
        if( ob->query("owner") != who->query("id")
         || !who->query_temp(QUESTDIR+"归辛树/over")){
                command("haha");
                command("say 多谢"+RANK_D->query_respect(who) + "把我派秘籍找回，太感谢了。");
                who->delete_temp("limochou");
                call_out("dest", 1, ob);
                return 1;
        }
        command("say 太好了，你终于把这本秘籍残本取回来了。");

            command("say 近几日老是听到后山有鹰鸣之声，不知道.......");
        who->set(QUESTDIR+"归辛树/over", 1);
        who->delete_temp(QUESTDIR+"归辛树/over");
        call_out("dest", 1 ,ob);
        return 1;
}

void dest(object obj)
{
        if(! obj) return;
        destruct(obj);
}


int do_jiejian() 
{
	object me = this_player();
	
	
	if (this_object()->query("questbusy")) 
	{
		command("say 正忙着呢！\n");
		return 0;
	}
	if(this_object()->is_fighting()) return 0;
	if(me->query("family/family_name")!="华山派")
	{
		command("heng "+me->query_id());
		command("say 你和我门派有什么关系，赶紧给我滚！");
		return 1;
	}
	if(me->query("shen")<0)
	{
		command("heng "+me->query_id());
		command("say 华山乃名门正派，赶紧给我滚！");
		return 1;
	}
	if(me->query("quest/hs/hsjf/jiejian/pass"))
	{
		command("heng "+me->query_id());
		command("say 你已经将华山剑法截剑式融会贯通，来消遣我么？");
		return 1;
	}
	if(me->query("quest/hs/hsjf/jiejian/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say 已经多次传授，你怎么都还没有领悟,真够笨的！");
		command("puke "+me->query("id"));
		return 1;
	}
	
	if (me->query_skill("huashan-jianfa",1)<300)
	{
	   command("say 华山剑法威力不足300，说给你听也是白搭？\n");
	   return 1;
	}
	message_vision(HIC"$N向$n请教有关华山剑法截剑式绝技的终极奥妙。\n"NOR, me, this_object());
	
	command("look "+me->query("id"));	
	
	if( time()-me->query("quest/hs/hsjf/jiejian/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say 今天先教到这里吧，明天吧。");
		return 1;
	}
	
    
	me->set("quest/hs/hsjf/jiejian/time",time());
	me->set("quest/hs/hsjf/jiejian/combat_exp",me->query("combat_exp")); 
	
	command("sigh "+me->query("id"));
	command("think ");
	command("consider ");
	
	command("say 华山剑法自上代而流失太多，看在你如此勤奋的份上就将我所领悟的华山剑法奥秘说给你听听，看你有没有这个悟性了。");
    command("say 徒儿啊，这招绝技乃是为师多年心血所得，你要好好听好了。\n");
	command("whisper "+me->query("id"));
	
	command("smile "+me->query("id"));
	this_object()->set("questbusy",1);
	me->start_busy(999);
	remove_call_out("think_hsjf");
	call_out("think_hsjf",1,me);
	return 1;
}

int think_hsjf(object me)
{
	//object me=this_player();
    int i;
	i=random(10);
	if(me->query_temp("canwu_hsjf")<(10+random(5)))
    {  
	  me->add_temp("canwu_hsjf",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n你仔细聆听师傅的讲述，将师傅所传授的招式彼此印证，只觉得耳目一新...\n"NOR);
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

	  //remove_call_out("think_ssjf");
	  call_out("think_hsjf",3+random(3), me);
	  return 1;

   } 
	else if( i>=8 && random(me->query("kar"))>=28)
	{
		tell_object(me,HIC"\n你按照穆人清长老的指点，结合自己演习所得，对华山剑法截剑式的奥妙似乎有些心得。\n"NOR);
		tell_object(me,HIC"\n你把穆人清所传授的招式从头开始演练，一路演练下来，潇洒自如。越练越是纯熟。\n"NOR);
        tell_object(me,HIC"\n忽然间，你灵光一闪，以前无论如何也想不明白的问题忽然间豁然贯通，忍不住哈哈大笑.\n"NOR);		
		
		command("look "+me->query("id"));
		command("chat*haha "+me->query("id"));
        command("chat*pat "+me->query("id"));
		command("chat "+"哈哈哈哈！！虽然比我预想的结果晚了点，但你能领悟者截剑式，足见平时你修炼比较辛苦！");

		
		me->set("quest/hs/hsjf/jiejian/pass",1);
		//me->set("title",HIC"华山派"+HIY"华山剑法传人"NOR);
		me->set("quest/hs/hsjf/jiejian/time",time());
		log_file("quest/hsjfjiejian", sprintf("成功！%8s(%8s) 失败%d次后，彻底领悟华山剑法截剑式的绝技。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/hs/hsjf/jiejian/fail"),i,me->query("combat_exp")) );
		me->delete_temp("canwu_hsjf");
		this_object()->set("questbusy",0);
		//me->delete_temp("hssb");

	}
	else
	{
		command("heng "+me->query("id"));
		command("say 我看见过笨的，我就没见过你这号的。");
		command("say 当初我那弟子袁承志，短短几个时辰内就领会了这招，你居然还没学会，气死我了!\n");
		command("angry "+me->query("id"));
		tell_object(me,HIY"你听了穆人清的指点，虽然看见了华山剑法截剑式的厉害招式，可是对华山剑法截剑式的真正奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		log_file("quest/hsjfjiejian", sprintf("失败，%8s(%8s) 华山剑法截剑式解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/hs/hsjf/jiejian/fail"),i,me->query("combat_exp")) );
		me->set("quest/hs/hsjf/jiejian/time",time());
		me->add("quest/hs/hsjf/jiejian/fail",1);
		me->delete_temp("canwu_hsjf");
		this_object()->set("questbusy",0);
		//me->delete_temp("hssb");
	}
	me->start_busy(1);
	return 1;

}