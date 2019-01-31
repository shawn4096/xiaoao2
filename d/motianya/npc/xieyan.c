// xieyan.c
//by sohu@xojh

#include <ansi.h>

inherit NPC;

string ask_lingp();
string ask_bizhen();
//int accept_object(object me, object ob);

#define XKX_QUEST1 "quest/侠客行/摩天崖/"
#define XKX_QUEST2 "quest/侠客行/玄铁令/"

void create()
{
        seteuid(getuid());
        set_name("谢烟客", ({ "xie yanke", "xie" }));
        set("long", @LONG
摩天居士谢烟客乃天下第一奇人，武功高强，曾经散出
玄铁令三枚，誓言可以满足拥有此令的三人任何愿望。
LONG );
        set("nickname", HIG "摩天居士" NOR);
        set("gender", "男性");
        set("age", 71);
        set("shen_type", 1);
        set("attitude", "friendly");

        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("qi", 45000);
        set("max_qi", 45000);
        set("jing", 6500);
        set("max_jing", 6500);
        set("neili", 35000);
        set("max_neili", 35000);
        set("max_jingli", 8000);
        set("jingli", 8000);
        set("eff_jingli", 8000);
        set("jiali", 220);

        set("combat_exp", 15500000);

        set_skill("force", 500);
        set_skill("dodge", 500);
        set_skill("parry", 500);
        set_skill("strike", 500);
        set_skill("luohan-fumogong", 500);
        set_skill("shexing-lifan", 500);
        set_skill("bizhen-qingzhang", 500);
        set("quest/xkx/lsfmst/luohan", 1);
        map_skill("force", "luohan-fumogong");
        map_skill("dodge", "shexing-lifan");
        map_skill("strike", "bizhen-qingzhang");
        map_skill("parry", "bizhen-qingzhang");

        prepare_skill("strike", "bizhen-qingzhang");
        set("chat_chance_combat", 80);
        
		set("chat_msg_combat", ({
		(: exert_function, "luohan" :),
		(: perform_action, "strike.pengpai" :),
		//(: perform_action, "hand.qianshou" :),
		//(: perform_action, "leg.ruying" :),
	}));

        set("inquiry", ([
               "碧针清掌" : (: ask_bizhen :),
               // "绝招"     : (: ask_me :),
               // "澎湃"     : (: ask_me :),
              //  "绝技"     : (: ask_me :),
               // "玄铁令"   : "两枚玄铁令我已经收回,还有一枚失落江湖。最近匪人甚多，你可以去赵城之那里看看。",
			   "玄铁令"     : (: ask_lingp :),
			  // "石中玉帮主"     : (: ask_bangzhu :),

                "石破天"   : "狗杂种那个白痴还没死么？",
        ]));
        setup();
        carry_object("/clone/armor/cloth")->wear();
}
void init()
{
	if (this_player()->query(XKX_QUEST2+"givexieling"))
	{
		command("nod "+this_player()->query("id"));
	}
}
string ask_lingp()
{
	object me;
	me=this_player();
	command("say 我摩天居士谢烟客一项是一言九鼎");
	command("say 诺大的武林还没有我摩天居士办不了的事。");
	command("say 三十年前我曾经发出三枚玄铁令，也是三个承诺");
	command("say 无论是谁，只要持玄铁令找我，我都会答应替他办一件事");
	command("say 至今为止我已经回收了两枚玄铁令了，还差最后一枚没有收回");
	command("say 我摩天居士谢烟客是首信诺的人，这枚玄铁令一天不回来我一天寝食难安");
	command("say 这一枚玄铁令不知道藏在谁的手中，唉！");

	if (me->query(XKX_QUEST2+"start")
		&& objectp(present("xuantie lingp",me))
		&& me->query(XKX_QUEST2+"findxtl"))
	{
		command("nod "+me->query("id"));
		command("say 看你风尘仆仆，匆匆来此，一副兴冲冲的样子，难道是有事情么？\n");
		me->set_temp(XKX_QUEST2+"meetxie",1);
	}
	return "这枚玄铁令都快成了我梦魇了，不知何时能收回来！\n";
	
}

int accept_object(object me, object ob)
{				

        //消除各种bug，防止作弊
//			write("11");

		if (ob->query("id") == "xuantie lingp"
			//&&ob->query("name") =="玄铁令牌" 
			&&ob->query("owner")==me->query("id")
			&&me->query(XKX_QUEST2+"start")
			&&me->query(XKX_QUEST2+"findxtl")
			&&me->query_temp(XKX_QUEST2+"meetxie"))
		{
//			write("22");
			command("ah");
			command("say 我的第三枚玄铁令！");
			command("say 我曾经发出三枚玄铁令，凡是得到我玄铁令的人都可跟我提一个要求。");
			command("say 我谢烟客都将极力满足他的要求。");
			command("say 有两枚玄铁令已经被我收回了，就差这最后一枚了，没想到居然让你给得到了。");
			command("say 我非常看好你，你以后可以随便进出摩天崖了。");

			command("say 你有什么请求跟我说吧。");
			command("smile "+me->query("id"));
			destruct(ob);
			//me->delete_temp(XKX_QUEST2+"meetxie");
			me->set_temp(XKX_QUEST2+"givexieling",1);
			me->set(XKX_QUEST2+"givexieling",1);
			message_vision(HBYEL+HIW"\n\n恭喜$N完成了《侠客行》故事系列二之《玄铁令篇》\n"NOR,me);
			return 1;

		}else
		return 0;
}

string ask_bizhen()
{
		object me;
		int i,j;
		me=this_player();
		message_vision(HIM"你小心翼翼的凑近谢烟客，满脸谄媚，说道，“久闻摩天居士谢烟客的碧针清掌名闻天下”\n"NOR,me);
		message_vision(HIM"我想学这门绝学，不知道是否愿意教我？\n"NOR,me);
        if (!me->query(XKX_QUEST2+"givexieling"))
		{
            return "没事献殷勤，非奸即盗，我认识你么？\n";

		}
		if (me->query("quest/xkx/bzqz/pass")) 
		{
			me->set("title",HIC"碧针清掌传人"NOR);
            return "能教的已经教完了，还来找我干嘛？\n";
		}
        if (me->query_skill("force",1)<350)
                return "你的基本内功太低，不足350，学了这招神功也没用！\n";
		if (me->query_skill("strike",1)<350)
                return "你的基本掌法太低，不足350，学了这招神功也没用！\n";
        
		if (time()-me->query("quest/xkx/bzqz/time")<86400)
		{
			return "你来的也太勤快点了！\n";
		}
	

        message_vision(HIW "$n" HIW "冷笑一声，双掌陡然挥舞"
                       "出一个大圈，横推而出，顿时一股汹涌澎"
                       "湃的劲气如波浪一般向" HIW "涌来。\n$N"
                       HIW "大骇，硬接了这一招，只感内息翻腾"
                       "，全身骨骼快要散架一般。突然目光一亮"
                       "，似乎明白了什么。\n" NOR,
                       me, this_object());

        command("grin");
		
    i = 25;
    if(me->query("m-card-vip")) i =  23;
    if(me->query("y-card-vip")) i =  20;
    if(me->query("buyvip"))     i =  18;
    i=random(i);
	j=random(me->query("kar"));
	command("say 本门碧针清掌乃是武林绝学，讲究的是劲气由后背运气于掌，经胸肋处直达劳宫穴，是这门掌法的精要所在。\n");
	command("pat "+me->query("id"));
	if( i<2
		&& me->query("kar")<31
		&& j > 27 ) 
	{
		tell_object(me,HIY"\n你听了谢烟客的亲自指点，联想起早期自己所用摩天崖掌的种种心得，两下印照。\n"NOR);
		tell_object(me,HIG"\n你丹田气劲盘旋游走，忽然间顺夹脊而上，汇聚于劳宫穴,双掌立即炙热无比。\n"
							"忽然间一股劲气震荡，如长江大河，滔滔不绝，顿时突破劳宫穴而达手掌。\n"
						 +"你终于领悟了这门<碧针清掌>绝技的运用法门。心中大喜。\n"NOR);
		me->set("quest/xkx/bzqz/pass",1);

		log_file("quest/xkxbizhen", sprintf("%8s(%8s) 失败%d次后，学到碧针清掌绝技,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/xkx/bzqz/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		command("haha"+me->query("id"));		
		me->improve_skill("bizhen-qingzhang",1000);
		return "恭喜解密摩天崖碧针清掌绝技成功!\n";
		
	}	
   else
	{
		log_file("quest/xkxbizhen", sprintf("%8s(%8s) 解密碧针清掌绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/xkx/bzqz/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"你听了谢烟客的指点，可是对摩天崖掌碧针清掌的奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/xkx/bzqz/fail",1);
		me->set("quest/xkx/bzqz/time",time());
		me->start_busy(1+random(3));
		
		return "非常遗憾解密摩天崖碧针清掌失败"+me->query("quest/xkx/bzqz/fail")+"次。\n";
	}


}
