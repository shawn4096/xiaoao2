// due.c
#include <ansi.h>

inherit NPC;
inherit F_MASTER;
#include "bai-du.h"
string ask_me();
string ask_kanshou();
string ask_rybjj();
string ask_rybronghe();

void create()
{
        object ob;
        set_name("渡厄", ({ "du e", "du", "e" }) );
        set("title", "少林长老");
        set("gender", "男性");
        set("class", "bonze");
        set("age", 90);
        set("long", "这是一个面颊深陷，瘦骨零丁的老僧，他脸色枯黄，如同一段枯木。\n");
        set("attitude", "peaceful");
        set("combat_exp",16500000);
        set("shen", 50000);
        set("str", 30);
        set("int", 25);
        set("dex", 28);
        set("con", 28);
        set("qi", 36000);
        set("max_qi",36000);
        set("max_jing", 9000);
        set("eff_jingli", 9500);
        set("neili",36000);
        set("max_neili",36000);
        set("jiali", 250);
        set("no_get", 1);
        set("unique", 1);

        create_family("少林派", 35, "弟子");
        assign_apprentice("弟子", 0);
        set_skill("force", 550);
		set_skill("club", 530);
        set_skill("zui-gun",530);
        set_skill("whip", 530);
        set_skill("parry", 530);
        set_skill("dodge", 530);
        set_skill("buddhism", 201);
        set_skill("literate", 250);
        set_skill("yijin-jing", 550);
        set_skill("riyue-bian", 550);
        set_skill("shaolin-shenfa", 530);
        set_skill("hand",530);
        set_skill("fumoquan-zhen",530);
        set_skill("leg",530);
        set_skill("blade", 530);
        set_skill("xiuluo-dao", 530);
        set_skill("qianye-shou",530);
        set_skill("ruying-suixingtui",530);
        map_skill("force", "yijin-jing");
        map_skill("blade", "xiuluo-dao");
        map_skill("whip",  "riyue-bian");
        map_skill("parry", "xiuluo-dao");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("hand","qianye-shou");
		map_skill("club","zui-gun");
        map_skill("leg","ruying-suixingtui");
        prepare_skill("hand","qianye-shou");
        prepare_skill("leg","ruying-suixingtui");
        set("inquiry", ([
                "伏魔金铙"     : (: ask_me :),
				"看守谢逊"     : (: ask_kanshou :),
				"伏魔圈绝技"     : (: ask_rybjj :),
				"日月鞭融合"     : (: ask_rybronghe :),

        ]));
        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "whip.chanrao" :),
                (: perform_action, "whip.fumoquan" :),
                (: perform_action, "hand.qianshou" :),
                (: perform_action, "leg.ruying" :),
        })); 
        setup();
        if (clonep()) {
                ob=unew(BINGQI_D("whip/heisuo"));
                if (!ob) ob = unew(BINGQI_D("changbian"));
                ob->move(this_object());
                ob->wield();
                carry_object("/d/shaolin/obj/du-cloth")->wear();
        }       
}

void init()
{
        int i, j;
        object me, ob;
        mapping fam;
        me = this_player();
        ob = this_object();
        ::init();
        if(interactive(me)){
                if (mapp(fam = me->query("family")) && fam["family_name"] == "少林派" 
                && fam["generation"] <= 36 ) {
                        me->set_temp("fighter", 1);
                        return;
		}
                if (mapp(fam = me->query("family")) && fam["family_name"] == "少林派" 
                && fam["generation"] > 36               
                && me->query("qi") < 50 ) {
                        me->move("/d/shaolin/qyping");
                        me->unconcious();
                        return;
		}
                if(base_name(environment(ob))!="/d/shaolin/fumoquan") return;
                command("say 阿弥陀佛！");
                i = me->query("combat_exp");
                j = me->query("potential");
                COMBAT_D->do_attack(ob, me, query_temp("weapon"), 2);
                COMBAT_D->do_attack(ob, me, query_temp("weapon"), 2);
                me->set("combat_exp", i);
                me->set("potential", j);
                me->set_temp("fighter", 1);
                remove_call_out("halt");
                call_out("halt", 0, me);
                return;
        }
        return;
}

void halt(object me)
{
	if(me->is_ghost()) return;
	if(!living(me) && environment(me) == environment()){
		message_vision("$N被渡厄用长鞭一卷，扔出了金刚伏魔圈！\n", me);
		me->move("/d/shaolin/qyping");  
		message_vision("$N被人丛金刚伏魔圈给扔了出来！\n", me);
	}
	else command("say 好吧，大家住手！ 看这家伙有什么话要说！");
}

string ask_me()
{
        object whip;
        object ob,me;
        me = this_player();
        
	if ( !this_player()->query_temp("fighter") 
	 ||  this_player()->query("combat_exp") < 5000 ){
		command("say 大胆鼠辈，乳臭未干，竟敢偷入金刚伏魔圈，且让老衲来超度与你！");
		this_object()->kill_ob(this_player());
		this_player()->kill_ob(this_object());
		return 0;
        }

        if ( present("huangjin nao", this_player()) || present("fumo nao", this_player()))
                return RANK_D->query_respect(this_player())+ "金铙只有一对，而且就在你身上，真是贪得无餍！";

        if ( present("huangjin nao", environment()) || present("fumo nao", environment()))
                return RANK_D->query_respect(this_player()) + 
                "金铙只有一对，而且就在这里任你取走，真是贪得无餍！";

        if(present("zhanyao nao", environment()) || present("zhanyao nao",this_player()))
                return RANK_D->query_respect(this_player())+ "你有了斩妖金铙，就不能再拿伏魔金铙，莫要贪得无餍！";

        if ( present("jingang zhao", this_player()) || present("jingang zhao", environment()) )
		return RANK_D->query_respect(this_player())+ "取了金刚罩，就不能再拿黄金铙，莫要贪得无餍！";

        if(me->query_temp("fmnao")) return "刚才伏魔金铙不是刚给你吗？"; 

	if( clonep()){
		ob= unew(BINGQI_D("blade/jinnao"));
		if(ob){
			destruct(ob);
			ob=unew(BINGQI_D("blade/jinnao1"));
		}
		if(ob) ob->move(this_object());
	}
	if ( present("fumo nao", this_object())){
		message_vision("\n渡厄长笑一声，点点头，将手中的伏魔金铙用布包好。\n\n", this_player());
		command("give fumo nao to "+this_player()->query("id")); 
		me->add_busy(2);
		me->set_temp("fmnao",1);
		whip = unew(BINGQI_D("whip/heisuo")); 
		if(clonep(whip)){
			whip->move(this_object());
			command("wield bian"); 
		}    
		else {
			if (!(whip = present("changbian", this_object()))) 
				whip = unew(BINGQI_D("changbian")); 
			whip->move(this_object());
			command("wield bian"); 
		}
		return "你既然能闯进金刚伏魔圈来，必然是当今武林中的非凡人物，这只铙是适逢其主了！";
	}
	return "抱歉，你来晚了，伏魔金铙已经给人取走了。";
}

string ask_kanshou()
{
	object me = this_player();

	
	if (time()-me->query("quest/sl/ryb/kanshou/time")<86400)
	{
		command("say 你来的太频繁了，明天再来试试!\n");
		return "阿弥陀佛!\n";
	}
	if ( me->query_skill("yijin-jing",1)<500 )
		return RANK_D->query_respect(me)+"，你的易筋经功力太浅，不足500级，还是等修炼高了再来吧！";
	
	if ( me->query_skill("riyue-bian",1)<500 )
		return RANK_D->query_respect(me)+"，你的日月鞭法功力太浅，不足500级，还是等修炼高了再来吧！";
	if ( me->query("int")<35 )
		return RANK_D->query_respect(me)+"，日月鞭法需要高悟性，你的先天悟性不足35，还是等修炼高了再来吧！";

	command("say 谢逊这恶贼乃我少林大敌，他杀了我师侄空空见，此仇不可不报！\n");
	command("say 既然你又如此心意，那就替老衲我们来看守此恶贼，千万不可懈怠！\n");
	command("say 听闻魔教教徒即将到达少林，我怕他们来抢劫此贼，你要守护好了！\n");
	command("say 可别让我等三个老僧失望！\n");
	me->set_temp("ryb/askdue",1);
	
	return "魔教贼子人人得而诛之，见一个杀一个\n" +
	       "这也是一种慈悲！\n";
}
string ask_rybronghe()
{
	object me = this_player();

	

	if ( me->query_skill("yijin-jing",1)<500 )
		return RANK_D->query_respect(me)+"，你的易筋经功力太浅，不足500级，还是等修炼高了再来吧！";
	
	if ( me->query_skill("riyue-bian",1)<500 )
		return RANK_D->query_respect(me)+"，你的日月鞭法功力太浅，不足500级，还是等修炼高了再来吧！";
//	command("say 日月鞭法乃是我少林三大兵器武技之一！\n");

	command("say 日月鞭法乃是我少林三大兵器武技之一！\n");
	command("say 不过，当初明教教主张无忌和峨嵋掌门周芷若联手攻我伏魔圈！\n");
	command("say 当时我见周掌门的鞭法很有特点，极致变化，更具诡异和不可测！\n");
	command("say 你若有心，就替我去拜访下周女侠，说不定看在我等薄面之上能传授你这鞭子的奥秘！\n");
		command("say 也许会将这日月鞭法推向更高的一个境界，这全凭缘法！\n");

	me->set_temp("ryb/jiuyin_askdue",1);
	
	return "周掌门的鞭子乃当世一绝技，虽不如日月鞭的刚劲强横，但却极尽变化之极致。\n";
}

int do_say()
{
  object me=this_player();
  command("congra "+me->query("id"));
  command("chat 魔教教徒纵横西域，我看也没什么了不起！\n");
  command("chat 更何况号称天下第一高手的张无忌也命丧"+me->query("name")+"之手！\n");
  command("chat 恭喜"+me->query("name")+"打跑了明教教徒！我大少林又增加一绝世高手！\n");
  return 1;
}


string ask_rybjj()
{
	int i,j;
	object me = this_player();
	
	if (me->query("quest/sl/ryb/fumoquan/pass"))
	{
		command("say 你已经解开了，何必在如此骚扰老僧!\n");
		me->set("title",HIY"少林派"+HIR"日"HIB"月"HIY"鞭法传人"NOR);
		me->set("mytitle/quest/riyuebiantitle",HIY"少林派"+HIR"日"HIB"月"HIY"鞭法传人"NOR);
		return "阿弥陀佛!\n";
	}
	if (me->query("family/family_name")!="少林派")
	{
		command("say 你非我少林弟子，来此作甚!\n");
		return "阿弥陀佛!\n";
	}
	if (me->query("int")<35)
	{
		command("say 日月鞭法讲究灵动，你的先天悟性不足35,来了也白搭!\n");
		return "阿弥陀佛!\n";
	}


	if (time()-me->query("quest/sl/ryb/fumoquan/time")<86400)
	{
		command("say 你来的太频繁了，明天再来试试!\n");
		return "阿弥陀佛!\n";
	}
	if ( me->query_skill("yijin-jing",1)<500 )
		return RANK_D->query_respect(me)+"，你的易筋经功力太浅，不足500级，还是等修炼高了再来吧！";
	
	if ( me->query_skill("riyue-bian",1)<500 )
		return RANK_D->query_respect(me)+"，你的日月鞭法功力太浅，不足500级，还是等修炼高了再来吧！";
	
	command("say 既然你守护有功，为我大少林成功开“屠师大会”李霞汗马功劳，我就将此鞭法要义传授给你！\n");
	command("say 能否领悟就看你自己的悟性了！\n");
	command("whisper "+me->query("id"));
	
	j = 20;
    if(me->query("m-card-vip")) j =  18;
    if(me->query("y-card-vip")) j =  15;
    if(me->query("buyvip"))     j =  10;
	if (me->query("class")=="bonze")
	     j=random(j-2);
	else j= random(j);
	
	i=random(me->query("kar"));
 
    if(j<3
		&& i>26
		&& random(me->query("int"))>35)
	 {
		tell_object(me,HIG"\n你按照渡厄的指点，对日月鞭法的真正奥妙似乎有些心得。\n"NOR);
        tell_object(me, HIW"你按照渡厄所言，内息起自“长强穴”，随后自腰俞、阳关、命门、悬枢\n+"+
"诸穴，一路沿着脊椎上升，走的都是背上督任各个要穴，然后是脊中、中枢、筋缩、至阳、\n"+
"灵台、神道、身柱、陶道、大椎、痖门、风府、脑户、强间、后顶、而至顶门的“百会穴”。\n"NOR);
		tell_object(me,HIY"\n\n\n恭喜你！你历尽千辛挖苦，终于得偿所愿，将日月鞭法伏魔圈精义融汇贯通。\n"NOR);
       	//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("quest/sl/ryb/fumoquan/pass",1);
		me->set("title",HIY"少林派"+HIR"日"HIB"月"HIY"鞭法传人"NOR);
		me->set("mytitle/quest/riyuebiantitle",HIY"少林派"+HIR"日"HIB"月"HIY"鞭法传人"NOR);
		me->start_busy(1);
		log_file("quest/fumoquan", sprintf("%8s(%8s) 失败%d次后，彻底领悟伏魔圈的绝技。i取值：%d|j取值：%d|int取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/sl/ryb/fumoquan/fail"),i,j,me->query("int"),me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/sl/ryb/fumoquan/fail",1);
		me->set("quest/sl/ryb/fumoquan/time",time());
		command("buddha ");
		tell_object(me,HIY"你听了渡厄的指点，虽然听见了伏魔圈的奥秘，可是对伏魔圈功的真正奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->start_busy(1);
		log_file("quest/fumoquan", sprintf("%8s(%8s) 伏魔圈解密失败%d次。i取值：%d|j取值：%d|int取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/sl/ryb/fumoquan/fail"),i,j,me->query("int"),me->query("combat_exp")) );
	  }
    		
		return "魔教贼子人人得而诛之，见一个杀一个\n" +
	       "这也是一种慈悲！\n";
}