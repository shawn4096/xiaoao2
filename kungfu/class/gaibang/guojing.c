#define YT_BOOK "/d/zhiye/obj/book.c"

//定义任务刷新地点，方便检查标记。 By lsxk@hsbbs 2007/7/12
#define JOB_CHECK_PLACE "/d/xiangyang/cross2"

#include <ansi.h>
inherit NPC;
int ask_defend_job();
int ask_yt();
int ask_paiyun();
int ask_h7g();
int ask_huangrong();
int ask_chengyaojia();
int ask_niujiacun();
int ask_ouyangke();
int ask_slbw();
int ask_dgbf();
void create()
{
        set_name("郭靖", ({"guo jing", "guo", "jing"}));
        set("nickname", HIY"北侠"NOR);
        set("gender", "男性");
        set("age", 40);
        set("long", "他就是威振天下的大侠郭靖，第二次华山论剑后号称“北侠”。\n");
        set("xy_npc", "1");
        set("attitude", "friendly");
        set("str", 40);
        set("int", 10);
        set("con", 40);
        set("dex", 25);
        //set("unique", 1);
        set("no_get", 1);
        set("no_quest", 1);
		set("double_attack", 1);

        set("max_qi", 50000);
        set("max_jing", 8000);
        set("neili", 58000);
        set("max_neili", 58000);
        set("jiali", 250);
        set("eff_jingli",9000);
        set("combat_exp", 17000000);

        set_temp("special_die",1);
        set_temp("xyjob/xy_defend",1);
        set_temp("living", 1);

        set_skill("force", 550);
        set_skill("medicine",120);
        //set_skill("tanzhi-shentong",300);
        //set_skill("yiyang-zhi",300);
        //set_skill("claw",300);
        //set_skill("jiuyin-baiguzhua",300);
        set_skill("huntian-qigong", 550);
        set_skill("strike", 550);
        set_skill("xianglong-zhang", 550);
        set_skill("dodge", 500);
        set_skill("jinyan-gong", 500);
        set_skill("parry", 500);

        map_skill("force", "huntian-qigong");
        map_skill("strike", "xianglong-zhang");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "xianglong-zhang");
       // map_skill("finger","tanzhi-shentong");
       // map_skill("claw", "jiuyin-baiguzhua");
        prepare_skill("strike", "xianglong-zhang");

        set("inquiry", ([
//               "守城": (: ask_defend_job :),
                "倚天屠龙术": (:ask_yt:),
 //                 "排云双掌": (:ask_paiyun:),
				 "洪七公": (: ask_h7g :),
			     "黄蓉": (: ask_huangrong :),
				 "程瑶迦": (: ask_chengyaojia :),
				 "牛家村": (: ask_niujiacun :),
			     "欧阳克": (: ask_ouyangke :),
				 "神龙摆尾": (: ask_slbw :),
				 "打狗棒法": (: ask_dgbf :),


        ]) );

        set_temp("apply/damage",100);
        set_temp("apply/defence",100);
        set_temp("double_attack",1);

        set("start",1);
        set("thjob",3);
        set("gbjob",3);
        set("gmjob",3);
        set("emjob",3);
        set("job",7);
        set("finish",0);

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "strike.feilong" :),
			    (: perform_action, "strike.lushuang" :),
				(: exert_function, "huntian" :),
                (: perform_action, "strike.kanglong" :),
        }));
        create_family("丐帮", 18, "帮主亲传弟子");
        setup();

        if (clonep()) carry_object("/d/thd/obj/grn-cloth.c")->wear();
}

void init()
{
	::init();
	
	add_action("do_answer",({"answer","huida"}));
}

void kill_ob(object me)
{
	if (!me->query_temp("xyjob") || !me->query_temp("living"))
	{
        	me->remove_killer(this_object());
 		remove_killer(me);
 		return;
 	}
        ::kill_ob(me);
}


void die()
{
	object killer;

        command("chat 蓉....蓉儿，我先走...一步了！");
        command("chat 盼你完成屠龙刀....和....和倚.....");

	if(objectp(killer = query_temp("last_damage_from")) && killer->query_temp("xyjob/mg_attack"))
		killer->add_temp("xyjob/attack", 1);
	if(objectp(killer = query_temp("last_damage_from")) && killer->query_temp("xyjob/xy_defend"))
		killer->add_temp("xyjob/defend", -1);
	::die();
}
int accept_object(object who, object obj)
{
    object me = present("guo jing", load_object("/d/xiangyang/xuanwumen"));

    if(obj->query("id")!="xiangyang mihan"){
        command("? "+ who->query("id"));
        return 0;
    }
/*
    if(JOB_CHECK_PLACE->query("xyjobing")){
        command("say 我军都已经在和蒙古先锋军苦战了，"+who->query("name")+"你到现在才送这封密函来。。。。。");
        command("sigh "+ who->query("id"));
        command("kick2 "+ who->query("id"));
        call_out("destroy_letter",1,obj);
        log_file("job/xyjob", sprintf(HIR"%8s%s欲在xyjob过程中使用"+HIW+"襄阳密函"+HIR+"开启襄阳攻防战,开启失败。"NOR, ctime(time())[4..19],who->name(1)+"("+who->query("id")+")")  );
        return 1;
    }
*/ 
   command("thank "+who->query("id"));
    command("say 多谢"+who->query("name")+"前来送信，原来目前蒙古先锋军粮草不足，即便来攻也不足为惧！");
    command("haha");
    command("say 这点东西就当是襄阳守军送给"+who->query("name")+"的谢礼吧！");

         who->add("SJ_Credit",20+random(10));
         who->add("combat_exp",1000+random(1000));
         who->add("shen",1000+random(1000));
       tell_object(who, "你感觉到心中澎湃着侠义正气！\n");
       tell_object(who, "你的江湖阅历增加了！\n");
//    me->start_call_out( (: call_other, "/d/xiangyang/cross2", "xyjob_1" :),2 );



        log_file("job/xyjob", sprintf(HIG"%8s%s使用"+HIW+"襄阳密函"+HIG+"成功开启襄阳攻防战。"NOR, ctime(time())[4..19],who->name(1)+"("+who->query("id")+")")  );
    call_out("destroy_letter",1,obj);
    return 1;
}
void destroy_letter(object obj)
{
   if (!obj) return;
   destruct(obj);
   return;
}

int ask_defend_job()
{
	int i, a_exp = 0, d_exp= 0;
        object me, meng, room;
	object *attackers = filter_array("/cmds/std/xyjob"->player_list(), (: $1->query_temp("xyjob/mg_attack") :));
        object *defenders = filter_array("/cmds/std/xyjob"->player_list(), (: $1->query_temp("xyjob/xy_defend") :));

        me = this_player();
        room = load_object("/d/xiangyang/yingzhang");
        meng = present("meng ge", room);

  /*      if (wizardp(me))
        {
           command("say 神仙还是不要参加的好!");
        	return 1;
        }
*/
        if (!query("ready_defend") || !meng)
        {
        	command("say 目前蒙古军暂时不会攻击，请先休息一下吧。");
        	command("sweat " + me->query("id"));
        	return 1;
        }

	if (query("start_defend"))
        {
        	command("say 蒙古军已经在进攻了，还问什么？！");
        	command("sweat " + me->query("id"));
        	return 1;
        }

        if (me->query("combat_exp")<1000000)
        {
            	command("thank " + me->query("id"));
            	command("say 多谢好意，但是这里对你来说太危险了。");
            	return 1;
        }

        if (me->query_conditions_by_type("poison") || me->query_conditions_by_type("hurt"))
        {
        	command("say 你身中剧毒，如何帮助我守城？");
        	return 1;
        }

        if (me->query_condition("killer")) {
                notify_fail("你还是了结完江湖恩怨再来帮忙吧。\n");
                return 1;
        }

        if (me->query_temp("xyjob"))
        {
            	command("say 别心急，蒙古精锐随时会进攻。");
            	return 1;
        }

	for(i = 0; i < sizeof(defenders); i++)
	{
		d_exp += defenders[i]->query("combat_exp");
		if (query_ip_number(defenders[i]) == query_ip_number(me))
		{
			command("say 壮士不是已经在帮助我们了，开什么玩笑？");
			return 1;
		}
	}
    	for(i = 0; i < sizeof(attackers); i++)
    	{
		a_exp += attackers[i]->query("combat_exp");
		if (query_ip_number(attackers[i]) == query_ip_number(me))
		{
			command("say 你已经在帮助蒙古了，难道还想来做奸细？");
			return 1;
		}
	}
	if (d_exp - a_exp > 10000000)
	{
		command("say 这里高手云集，守住襄阳城不在话下，不用劳烦阁下了。");
		command("thank " + me->query("id"));
		return 1;
	}

        command("ok");
        command("say 请务必守住城门，如果有投降蒙古的武人来犯，为成大义，只有杀之。");
        "/cmds/std/xyjob"->add_xyjob(me);
        me->set_temp("xyjob/xy_defend", 1);
        me->set_temp("xyjob/defend", 1);
        me->set_temp("special_die", 1);
        me->set_temp("special_poison", 1);
        me->set_temp("living", 1);
        me->set_temp("apply/short", ({HIW"襄阳城守军 "NOR+me->name()+"("+capitalize(me->query("id"))+")"}));
        me->apply_condition("job_busy", 100);
        me->set("job_name", "襄阳攻防战");
        return 1;
}
int ask_paiyun()
{
         object me = this_player();
	     
         if (me->query("family/family_name")!="丐帮" ){
                 command("say 你又不是我丐帮弟子，想找死啊。");
                 return 1;
}
	if( (int)me->query_skill("xianglong-zhang", 1) < 400 )
		return notify_fail("你是否对我丐帮武学研究还不够。\n");
       {
		command("whisper "+me->query("id")+" 就是要作到"YEL"心神合一 心随意动"NOR"，希望你能继续为丐帮做出重大贡献。");
		me->set_temp("xlz/py_power", 1);
                me->add_temp("xlz/py_add",1);
		return 1;
	}
	return 1;
}
int ask_yt()
{
	object me = this_player();
	
	if(is_busy()) return 0;
	if(is_fighting()) return 0;
	
	if(me->query_skill("duanzao",1) < 220
	&& me->query_skill("caikuang",1) < 220
	&& me->query_skill("zhizao",1) < 220
	&& me->query_skill("nongsang",1) < 220 )
	{
		command("say 什么屠龙术……？为国为民，侠之大者，世上无龙，研究什么屠龙术？");
		return 1;
	}
	
	if(me->query("worker/guogift"))
	{
		command("say 你上次不是来问过了么？……");
		command("kick3 "+me->query("id"));
		return 1;
	}
	
	me->start_busy(50);
	this_object()->start_busy(50);
	
	command("say 蓉儿曾遇到一位韩前辈，传授她『倚天屠龙术』，据说是锻造兵器之用，蓉儿说将来可以用来保存《九阴真经》和《武穆遗书》，可惜我悟性不高，一直不能领会，……");
	
	message_vision(CYN"$N上下打量了$n两眼。\n",this_object(),me);
	command("say 你有意助我参详？只是此事关系重大，恕我需要考较考较你的功夫。你真有意助我？"HIY"（answer y/n）"NOR);
	me->set_temp("guo_yt",1);
	
	return 1;
}

int do_answer(string arg)
{
	object me = this_player();
	
	if(!me->query_temp("guo_yt")) return 0;
	
	if(me->query("worker/guogift")) return 0;

	if( !living(this_object()) ) return 0;
	
	if(!me->is_busy())
	{
		me->delete_temp("guo_yt");
		return 0;
	}
	
	me->delete_temp("guo_yt");
	
	if(arg && (arg=="Y" || arg=="y"))
	{
		command("ok");
		call_out("do_fight",0,me);
		return 1;
	}
	
	command("say 既然如此，那算了吧，将来或许还有机会……");
	this_object()->interrupt_me();
	this_object()->start_busy(-1);
	this_object()->interrupt_me();
	me->interrupt_me();
	me->start_busy(-1);
	me->interrupt_me();
	return 1;
}

void do_fight(object me)
{
	object ob = this_object();
	
	if(!me) return;
	
	if(me->query("worker/guogift")) return;
	
	if(environment(me)!=environment(this_object())) return;	
	
	add_temp("apply/damage",300);
	add_temp("apply/attack",300);
	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
	if(ob)
	{
		add_temp("apply/attack",-300);
		add_temp("apply/damage",-300);
		call_out("do_check",1,me);
	}
}

void do_check(object me)
{
	object ob = this_object();
	object obj;
		
	if(!me) return;
	
	if(me->query("worker/guogift")) return;
	
	if(environment(me)!=environment(this_object())) return;	
	
	if(!living(me) || me->query("qi") < 0 )
	{
		command("say 你的壮志可嘉，但是身手……");
		message_vision(CYN"$N摇了摇头。\n"NOR,ob);
		this_object()->interrupt_me();
		this_object()->start_busy(-1);
		this_object()->interrupt_me();
		me->interrupt_me();
		me->start_busy(-1);
		me->interrupt_me();
		return;
	}
	
	obj = new(YT_BOOK);
	obj->set_level(1+random(2));
	
	if(obj)
	{
		command("say 其实我天生笨拙，不懂那些精致的技巧，我只知道师傅教我，对襄阳百姓，对大宋子民有利的，乃至对凡夫俗子生计安康有利的，就是大道，其他的技能，不过是屠龙之术，看上去煞有介事，其实百无一用");
		command("say "+RANK_D->query_respect(me)+"既然有这般身手，我这里有一篇《"+obj->name()+"》，是当年高人所赠，今天就转赠于你，但愿你能修得屠龙术，造福在苍生……");
		command("bow "+me->query("id"));
		message_vision("$N给$n一"+obj->query("unit")+obj->name()+NOR"。\n",ob,me);
		
		if(obj->move(me)) me->set("worker/guogift",1);
        	me->interrupt_me();
		me->start_busy(-1);
		me->interrupt_me();		
		this_object()->interrupt_me();
		this_object()->start_busy(-1);
		this_object()->interrupt_me();		
	}
}

int ask_h7g()
{
	object me= this_player();
	if (me->query("family/family_name")!= "丐帮"||me->query("family/master_name")!= "洪七公") {
		command("say 你又不是我丐帮弟子，跑这里来瞎嚷嚷什么？");
		return 1;
	}
	if (!me->query_temp("slbw/askhuang4")) {
		command("say 洪七公跟你有啥关系，你跑这里来瞎嚷嚷什么？");
		return 1;
	}
	command("say 洪七公乃是我的恩师，他老人家乃是丐帮帮主，江湖号称九指神丐。\n");
	command("say 师傅他老人家最厉害的功夫乃是降龙十八掌，这是天下最霸道的掌法。\n");
	command("sigh ");
	command("say 当初多亏了蓉儿帮我，否则我根本就不可能拜七公为师傅。\n");
	me->delete_temp("slbw/askhuang4");
	me->set_temp("slbw/askguo1",1);
	return 1;
}
int ask_huangrong()
{
	object me= this_player();
	
	if (me->query("family/family_name")!= "丐帮"||me->query("family/master_name")!= "洪七公") {
		command("say 你又不是我丐帮弟子，跑这里来瞎嚷嚷什么？");
		return 1;
	}
	if (me->query_temp("slbw/askguo1"))
	{	
	command("say 蓉儿是我的娇妻，我是桃花岛女婿，我很爱她，她也很爱我，我们两个生死不渝。\n");
	command("say 起初七公只传授了我十五掌，剩下三掌根本没传授。后来发生了一件意外才促成了七公老人家传给我最后三掌。\n");
	command("say 当时我和蓉儿是一起到太湖归云庄，遇到程瑶迦后才发生了一件奇怪的事情。\n");
	me->delete_temp("slbw/askguo1");
	me->set_temp("slbw/askguo2",1);
	return 1;
	}
	else command("say 蓉儿是我娇妻。\n");	
	return 1;
}
int ask_chengyaojia()
{
	object me= this_player();
	if (me->query("family/family_name")!= "丐帮"||me->query("family/master_name")!= "洪七公") {
		command("say 你又不是我丐帮弟子，跑这里来瞎嚷嚷什么？");
		return 1;
	}
	if (me->query_temp("slbw/askguo2"))
	{	
	command("sigh ");
	//command("think ");
	command("say 那天我和蓉儿一起到归云庄，庄主是陆乘风，他是蓉儿的大师兄。不过那天恰好遇到全真教的一位师妹遇险。\n");
	command("say 后来才知道她就是程瑶迦，主要是欧阳克这个奸贼看到程瑶迦漂亮就想图谋不轨，唉，真是一言难尽。\n");
	command("think ");
	command("say 我看你还是去一趟归云庄吧。");
	me->delete_temp("slbw/askguo2");
	me->set_temp("slbw/askguo3",1);
	return 1;
	} 
	else 
	{
		command("say 程瑶迦是全真教清静散人孙不二师叔的弟子，是我的师妹。\n");
	    return 1;
	}
}
int ask_niujiacun()
{
	object me= this_player();
	
	if (me->query_temp("slbw/askcheng"))
	{	
	
	command("think ");
	command("say 嗯，既然你已经发现程姑娘有难，我看你还是去看看。\n");
	command("say 欧阳克最厉害的功夫是蛤蟆功和灵蛇拳，当时我根本打不过他，你可一定要替我教训他一次。\n");
	command("say 不过他是西毒欧阳锋的侄子，据说是西毒的亲生儿子，你可千万不要杀了他，否则西毒欧阳锋跟你没完。\n");
	me->delete_temp("slbw/askcheng");
	me->set_temp("slbw/askguo4",1);
	return 1;
	} 
	else 
	{
		command("say 牛家村是我故乡，虽小，但风景很美。\n");
	    return 1;
	}
}
int ask_ouyangke()
{
	object me= this_player();
	
	if (me->query_temp("slbw/askguo4"))
	{	
	
	command("hate ");
	command("say 这家伙就是一个淫贼，看到漂亮小姑娘就会把人家糟蹋了，真该死。\n");
	command("say 你跟他较量的时候最好能弄到较高的防御，否则很难坚持二十个回合。\n");
	command("say 当然，你若能带上必备的丹药，关键时刻还是很有用的。\n");
	command("say 降龙十八掌要想学会这神龙摆尾、履霜冰至、时乘六龙的绝招，需要下一番苦功夫。\n");
	me->delete_temp("slbw/askguo4");
	me->set_temp("slbw/askguo5",1);
	return 1;
	} 
	else 
	{
		command("say 欧阳克号称玉面蛇心，你可要小心了。\n");
	    return 1;
	}
}
int ask_slbw()
{
	object me= this_player();
	
	if (me->query_temp("slbw/askguo5"))
	{	
	
	command("think ");
	command("say 时乘六龙是连出六下，如乘龙飞临，飘逸潇洒，是十八掌中难得的招式。\n");
	command("say 履霜冰至乃是降龙掌中阴阳颠倒，阴阳互换的绝招，只有能发能收，阴阳不定降龙掌才算是大乘。\n");
	command("say 神龙摆尾这一招出自《易经》中的“履”卦，始创“降龙十八掌”的那位高人本来取名为“履虎尾”，\n好比攻虎之背，一脚踏在老虎尾巴上，老虎回头反咬一口，自然厉害猛恶之至。\n后来的传人嫌《易经》中这些文绉绉的封名说来太不顺口，改作了“神龙摆尾”。\n");
	command("say 看你性格这么坚韧，到时符合练习降龙掌的要求。\n");
	me->delete_temp("slbw/askguo5");
	me->set_temp("slbw/story1",1);
	return 1;
	} 
	else 
	{
		command("say 神龙摆尾是最厉害的防守反击招式。\n");
	    return 1;
	}
}
int ask_dgbf()
{
	object me= this_player();
	
	if (me->query("family/family_name")!= "丐帮"||me->query("family/master_name")!= "洪七公") {
		command("say 你又不是我丐帮弟子，跑这里来瞎嚷嚷什么？");
		return 1;
	}
	if (me->query_skill("dagou-bang",1)<500)
	{
		command("say 你的打狗棒法不足500级，去了也领悟不了。");
		return 1;
	}
	if (time()-me->query("quest/gb/dgb/wugou/time")<86400)
	{
		command("say 你去的太频繁了，不怕滚下来？");
		return 1;
	}
	if (me->query("quest/gb/dgb/wugou/pass"))
	{
		command("say 你已经学会了天下无狗，还去做什么？");
		return 1;
	}
	command("say 打狗棒法和降龙掌乃是我丐帮不传之谜，当初我学了降龙掌，蓉儿学了打狗棒法。\n");
	command("say 听师傅老人家说，这打狗棒法最厉害的莫过于天下无狗这招。\n");
	command("say 这打狗棒分为棒诀和招式，二者缺一不可，只有彼此融合方可显示大威力。\n");
	command("say 师傅他老人家去云游去了，据有人说曾在华山一带见过他的踪迹。\n");
	
	me->set_temp("wugou/askguo",1);
	return 1;
	
}




