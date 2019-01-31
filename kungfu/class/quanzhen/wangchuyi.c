#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_tiejiao();

void create()
{
        set_name("王处一", ({"wang chuyi", "wang"}));
        set("gender", "男性");
        set("age", 35);
        set("class", "taoist");
        set("nickname",RED"玉阳子"NOR);
        set("long",
                "他就是全真七子之五王处一王真人。他身材修长，服饰整洁，\n"
                "三绺黑须飘在胸前，神态潇洒。行走江湖，寻找优秀传人,江湖\n"
				"曾单脚站立悬崖三天三夜，威慑西北群寇，人称“铁脚仙”");
        set("attitude", "peaceful");
        set("shen_type",1);
        set("str", 32);
        set("int", 30);
        set("con", 32);
        set("dex", 30);

        set("title","全真七子之五");

        set("qi", 34500);
        set("max_qi", 34500);
		set("eff_qi",34500);
        set("jing", 5200);
        set("max_jing", 5200);
        set("neili", 24700);
        set("max_neili", 24700);
        set("jiali", 200);
        set("level", 18);
        set("combat_exp", 9400000);

        set_skill("force", 450);
        set_skill("xiantian-gong", 450);
        set_skill("sword", 450);
        set_skill("quanzhen-jianfa",450);
        set_skill("dodge", 450);
        set_skill("jinyan-gong", 450);
        set_skill("parry", 450);
        set_skill("literate",250);
        set_skill("strike", 450);
        set_skill("haotian-zhang", 450);
        set_skill("taoism",200);
	    set_skill("medicine", 200);
        set_skill("tiangang-beidouzhen", 450);
		set_skill("leg", 200);
        set_skill("yuanyang-lianhuantui", 450);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jianfa");
        map_skill("strike", "haotian-zhang");
		map_skill("leg", "yuanyang-lianhuantui");
        prepare_skill("strike","haotian-zhang");
		prepare_skill("leg", "yuanyang-lianhuantui");

        create_family("全真教", 2, "弟子");

        set("book_count",1);
	    set("inquiry", ([               
               "铁脚绝技" : (: ask_tiejiao :),
			   
        ]));	
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                 (: perform_action, "sword.sanqing" :),
                (: perform_action, "sword.qixing" :),
                (: perform_action, "sword.ding" :),
				(: perform_action, "sword.jianqi" :),
                (: perform_action, "sword.lian" :),
				(: exert_function, "daojue" :),
				(: exert_function, "wuqi" :),
				(: exert_function, "yusuo" :),
        }));
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/quanzhen/npc/obj/grayrobe")->wear();

}

void attempt_apprentice(object ob)
{
       if (ob->query("gender")!="男性")
       {
		   command("say 你一个女人家来拜我为师，难道是有什么企图不成？！\n");
		   command("say 我全真一脉，最终全在内丹修为上，关于坤丹的修炼我不擅长！\n");
		   command("say 你还是去寻找下师叔清静散人孙不二，看他是否收你？\n");
		   return ;

       }

	   if ((int)ob->query("shen") < 1500000) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在德行方面，" + RANK_D->query_respect(ob) +
                       "是否还做得不够？(1.5m)");
               return;
       }
	   if (ob->query("party/gongji") < 3000) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在教派功绩方面，" + RANK_D->query_respect(ob) +
                       "是否还做得不够？(需要3000点门派贡献值)\n");
               return;
       }
	   if (!ob->query("quest/qz/dichuan"))
	   {
		       command("say 你非我门中嫡传弟子，来此作甚？");
              return;

	   }
	   if (ob->query_skill("xiantian-gong",1) < 300) {
               command("say 我全真教一身功夫全在先天功，你先天功不足300，来此作甚？。");
               return;
       }
	 
       command("say 好吧，贫道就收下你了。");
       command("recruit " + ob->query("id"));
       ob->set("title", "全真七子亲传弟子");
       ob->set("class","taoism");
	   return;
}

string ask_tiejiao()
{
	object me;
	int i,j;
	me=this_player();
	if (me->query("family/family_name")!="全真教")
	{
		return "你不是我全真教弟子！\n";
	}
	if (me->query("shen") < 500000) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在德行方面，" + RANK_D->query_respect(me) +
                       "是否还做得不够500k？(1m)");
               return "";
       }
	   if (me->query("party/gongji") < 2500) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在教派功绩方面，" + RANK_D->query_respect(me) +
                       "是否还做得不够？(需要2500点门派贡献值)\n");
               return "";
       }
	   if (!me->query("quest/qz/dichuan"))
	   {
		       command("say 你非我门中嫡传弟子，来此作甚？");
              return "";

	   }
	   if (me->query_skill("xiantian-gong",1) < 200) {
               command("say 我全真教一身功夫全在先天功，你先天功不足200，来此作甚？。");
               return "";
       }
	   if (me->query_skill("yuanyang-lianhuantui",1) < 200) {
               command("say 我鸳鸯连环腿不足200，来此作甚？。");
               return "";
       }
	   	if (me->query("quest/qz/yylht/tiejiao/pass"))
		{
			return "你的连环鸳鸯腿的铁脚绝技已经解开了”！\n";
		}
		if (time()-me->query("quest/qz/yylht/tiejiao/time")<86400)
		{
			return "你来的太频繁了，明天再来！\n";
		}
	   command("say 事先声明，你向我请教需要扣除你的门派贡献值每次100点，如果不够你没资格请教我。\n\n\n\n");

       command("say 好吧，既然你如此努力，我就告诉你其中诀窍。\n");
       command("whisper "+me->query("id"));
	   if (me->is_busy())
	   {
		  return "你正在手忙脚乱中!\n";
	   }
		me->start_busy(10);
		if (me->query("party/gongji")<100)
		{
			return "你的门派贡献值不够100点，请继续努力去为门派奋斗吧\n";
		}
		me->add("party/gongji",-100);

		message_vision(HIC"$N严肃的看着$n，慢慢说道：“我派的下盘扎实可靠，不可浮夸，这和其他门派都不太相同。\n"
							"你既然到达如此程度，我就传给你这招“铁脚绝技”的奥秘，我给你演示一遍，看你自己的悟性了。\n"+
					   HIR"\n\n\n$N缓缓站起来，然后纵身跃起，双腿连环踢出，踢的空气“噗噗”作响！\n"NOR,this_object(),me);
		
	 
		i = 20;
		  if(me->query("m-card-vip")) i =  18;
		  if(me->query("y-card-vip")) i =  15;
		  if(me->query("buyvip"))     i =  10;
		  i=random(i);
		j=random(me->query("kar"));
		command("say 你看懂了么。\n");
		command("pat "+me->query("id"));
		if( i<5
			&& me->query("kar")<31
			&& j >= 22 ) 
		{
			tell_object(me,HIC"\n你听了的王处一的亲自指点，联想起早期自己所用连环鸳鸯腿的种种心得，两下印照。\n"NOR);
			tell_object(me,HIR"\n忽然脚底涌泉穴一股大力传来，你顿时感觉身轻如燕，腿部力量大增，瞬间领悟了这铁脚运气法门。\n"
						NOR);
			me->set("quest/qz/yylht/tiejiao/pass",1);
			log_file("quest/qztiejiao", sprintf("%8s(%8s) 失败%d次后，学到铁脚仙绝技,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
				me->name(1),me->query("id"), me->query("quest/qz/yylht/tiejiao/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
			command("haha"+me->query("id"));		
			
			return "恭喜解密铁脚仙绝技绝技成功!\n";
			
		}	
	   else
		{
			log_file("quest/qztiejiao", sprintf("%8s(%8s) 解密铁脚仙绝技绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
				me->name(1),me->query("id"), me->query("quest/qz/yylht/tiejiao/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
			
			tell_object(me,HIY"你听了王处一的指点，可是对连环鸳鸯腿决铁脚仙绝技的奥妙全然不得要领。\n\n"NOR);
			command("sigh "+me->query("id"));
			command("disapp "+me->query("id"));
			me->add("quest/qz/yylht/tiejiao/fail",1);
			me->set("quest/qz/yylht/tiejiao/time",time());
			me->start_busy(1+random(3));
			
			return "非常遗憾解密连环鸳鸯腿之铁脚仙绝技失败"+me->query("quest/qz/yylht/tiejiao/fail")+"次。\n";
		}

     
}

