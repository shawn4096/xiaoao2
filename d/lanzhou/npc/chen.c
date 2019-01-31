// By Spiderii fix bug
// chen.c
inherit NPC;
#include <ansi.h>;
string cxz();
void init()
{
        object me = this_player();
        if (me->query_temp("thd/onquest")==2) { 
           message_vision(HIY"$N见到黑风双煞来势猛恶，顿时想起靴旁的匕首(bishou)。\n"NOR,me);
           add_action("do_chou","chou");
        }
}

void create()
{
        set_name( "陈玄风" ,({ "chen xuanfeng", "chen" }));
        set("title", "黑风双煞");
        set("nickname", HIY"铜尸"NOR);
        set("gender", "男性");
        set("age", 35);
        set("long",
            "此人是黄药师的二弟子，他浓眉大眼，背厚膀宽，躯体甚是壮健，只是\n"
            "面色微微泛黄。\n");
        set("attitude", "aggressive");
        set("str", 37);
        set("int", 32);
        set("con", 35);

        set("unique", 1);
        set("no_quest", 1);
        set("max_qi",33500);
        set("qi",33500);
        set("max_jing",5000);
        set("neili", 34500);
        set("max_neili", 34500);
        set("jiali", 250);
        set("shen",-50000);

        set("combat_exp", 9500000);

        set_skill("claw", 450);
		set_skill("strike", 450);
        set_skill("force", 450);
        set_skill("parry", 450);
        set_skill("dodge", 450);
        set_skill("leg", 450);
        set_skill("jiuyin-baiguzhua", 450);
        set_skill("bihai-chaosheng", 450);
        set_skill("suibo-zhuliu", 450);
        set_skill("xuanfeng-tui", 450);
		set_skill("cuixin-zhang", 450);
		set("quest/jiuyin2/cuixin/pass", 1);
		
        map_skill("strike", "cuixin-zhang");
        map_skill("force", "bihai-chaosheng");
        map_skill("parry", "jiuyin-baiguzhua");
        map_skill("dodge", "suibo-zhuliu");
        map_skill("claw", "jiuyin-baiguzhua");
        map_skill("leg", "xuanfeng-tui");
        prepare_skill("strike", "cuixin-zhang");

        create_family("桃花岛", 2, "被逐弟子");
        set("inquiry", ([
           "铜尸":     "江湖上的人都这么叫我的，你怕不怕？哈哈哈哈。",
           "东邪":     "那是我师父的绰号。",
           "西毒":     "那是与家师齐名的高手之一，是个老毒物，住在白驼山。",
           "南帝":     "段王爷已出家当和尚去了，法名叫一灯。",
           "北丐":     "北丐统领中原的丐帮，势力颇为强大。",
           "洪七公":   "洪七公武功高强，而且教会郭靖那小儿降龙十八掌，可恨！",
           "黄蓉":     "她是我师父的独女，最是刁蛮任性。",
           "梅超风":   "她是我的师妹，也是我的内室。",
           "陈玄风":   "不就是我么？你是白痴啊？",
		   "催心掌": (: cxz :),
           "黄药师":   "他是我师父。"]) );
        setup();
        carry_object(ARMOR_D("cloth"))->wear();
}


string cxz()
{
	object me = this_player();
	object ob = this_object();
	object kulou;
	int exp, time, night;
	mixed *local;
	//night = 0;
	//local = localtime(time() * 60);
	//if (local[2] < 5 || local[2] >= 19) night = 1;	
	
	if(QUEST_D->queryquest(me,"jiuyin2/cuixin"))		
	{
		if( QUEST_D->queryquest(me,"jiuyin2/jybgz"))
		{
			QUEST_D->setmytitle(me,"jydowntitle",HIY"九阴真经·"HIB"白骨摧心"NOR);			
			me->delete("mytitle/quest/cxztitle");
			me->delete("mytitle/quest/jybgztitle");
		    return RANK_D->query_respect(me) + "，你已经学会九阴下的全部真谛，又何故开此玩笑呢？";			
		}
		else
		{
	   QUEST_D->setmytitle(me,"cxztitle",HIY"铜尸·催心"NOR);		
		return RANK_D->query_respect(me) + "，你已经得到催心掌秘诀，又何故开此玩笑呢？";
		}
	}
	
	if ( me->query("shen") > 0) return "你不够心狠手辣，如何学会催心掌的真谛。\n";
	
	if( me->is_busy() || me->is_fighting() ) return "你正忙着呢。\n";

	if( ob->is_busy() || ob->is_fighting() ) return ob->name()+"正忙着呢。\n";	    
    
	

    if( me->query_skill("cuixin-zhang", 1) < 300 )
		return RANK_D->query_respect(me) + "，你的催心掌造诣不够，无法领悟我的精要所在！";
 
	
	if (QUEST_D->queryquesttime(me,"jiuyin2/cuixin"))
		return "嗯？你不是刚来请教过我吗？还是再努力段时间吧！";
	
	
		me->start_busy(1);
		message_vision(CYN"$N对着$n说道：“请前辈指点"+RANK_D->query_self(me)+"催心掌要义！”\n"NOR, me, ob);	
	
	COMBAT_D->do_attack(ob, me, 0, 1);	
	COMBAT_D->do_attack(ob, me, 0,1);	
	COMBAT_D->do_attack(ob, me,0, 1);
	
	message_vision(HIY"\n$N拼命地回忆着刚才的招数，开始认真思索着.........\n", me);
	message_vision(HIY"\n$N拼命地回忆着刚才的招数，开始认真思索着.........\n", me);
	message_vision(HIY"\n$N拼命地回忆着刚才的招数，开始认真思索着.........\n", me);
	
	//if( random(me->query("kar")) > 28 && random(10)==3) {	// 随机福源
	//1，代表真人人品暂不参与，80代表四维属性随机基数，0代表不限制该quest在线人数，后面标记是判断在线人数的
	  
	   if (QUEST_D->questing(me,3,80,0,"jiuyin2/cuixin")) {	
	   
			message_vision(HIW"$N突然捕捉住交手瞬间的一幕，渐渐领悟出催心掌的要义。\n", me);
			tell_object(me, BYEL"恭喜你，你于" + NATURE_D->game_time() + "领悟了催心掌的要义。\n"NOR);
			
			QUEST_D->setmytitle(me,"cxztitle",HIY"铜尸·催心"NOR);	
			
			log_file("quest/cuixinzhang",sprintf("%-18s失败多次后，从陈玄风处学到催心掌真意，福：%d。\n",
              			me->name(1)+"("+capitalize(getuid(me))+")",me->query("kar")), me);
			return "恭喜，恭喜。";
		}
		else {
			message_vision(HIC"$N摇了摇头，道：“好像还是很困难的。”说罢，深深地叹了口气。\n", me);
			
			return "你太没有用，退下吧。";
		}	
	
	
}

void kill_ob(object me)
{
        object ob=this_object();
		object mei;
		
		mei = present("mei chaofeng",environment(me));
	if (mei) {
		mei->force_me("guard chen xuanfeng");
		mei->kill_ob(me);
	}		
		
        command("say 想抢我的九阴真经？没那么容易！");
        message_vision(HIY"陈玄风向$N急攻数招，夺路向外跑去。\n\n"NOR,me);
        COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 3);
        COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 3);
        COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 3);
        command("out");
        ::kill_ob(me);
}

void do_dest(object ob)
{
	::die();
}

int do_chou(string arg)
{
        object me = this_player();
        object ob = this_object();
        object obj;
        string msg;
        if (!arg||arg!="bishou")
                return notify_fail("什么？\n");
        if (me->query_temp("thd/onquest")!=2)
                return notify_fail("什么？\n");         
        if(arg=="bishou"&&me->query_temp("thd/onquest")==2)
        {
                msg = HIR"$N见到黑风双刹袭来，心中一惊，抽出匕首胡乱挥舞起来。\n";
                msg+= HIR"陈玄风冷笑一声，在$N肩头青门穴一弹，$N手一沉，竟然正好插在\n";
                msg+= HIR"他的肚脐上！\n\n"NOR;
                msg+= HIY"陈玄风瞪著$N，身子慢慢的软倒。\n\n"NOR;
                msg+= HIC"梅超风惨叫一声，不故性命的向你攻来！\n"NOR;
                        if (!objectp(obj = present("mei chaofeng",environment(me)))) {
                                call_out("do_dest",1,ob);
                                return 1;
                        }
                obj->set_temp("target",me->query("id"));
                message_vision(msg, me);
                me->set_temp("thd/onquest",3);
                ob->die();
                return 1;
         }
}

void die()
{
	object me = query_temp("last_damage_from");
	object skin;
	int i, time;
	    
		if (!objectp(me)) {
			::die();
		     return;
		}

        i = me->query("combat_exp") - 1000000;
		i /= 1000000;

		
		if(QUEST_D->queryquesttime(me,"jiuyin2"))		
   		{
				::die();
				return;
		}

	   if (me->query("quest/jiuyin2/fail") >= 3 && me->query("registered") < 2)
	   {
		::die();
		return;
    	}		
		
			
      //这里用简单quest函数
	    if(QUEST_D->queryquest(me,"jiuyin2") || QUEST_D->easy_questing(me,5,"jiuyin2"))
        {
            skin = unew(__DIR__"../obj/jiuyin-book2");
		     if(!clonep(skin))
			         {
						
			             ::die();
			             return;
		                    }
		    message_vision(HIY"\n$N看到陈玄风身上有一片皮革，顺手拿了起来。\n"NOR,me);
		    skin->set("owner", me->query("id"));
		    skin->move(me);
			
		if(!QUEST_D->queryquest(me,"jiuyin2"))
			
		
		::die();
		return;
	    }
	  

		me->set("quest/jiuyin2/combat_exp", me->query("combat_exp"));
		
	::die();
	return;
}
