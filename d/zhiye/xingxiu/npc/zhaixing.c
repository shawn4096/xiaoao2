// zhaixing.c 摘星子
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

string ask_job();
string ask_laoyue();
void create()
{
	set_name("摘星子", ({ "zhaixing zi", "zhaixing", "zi" }));
	set("nickname", "星宿派大师兄");
	set("long", "一个二十七八岁的白衣年轻人。他身材高瘦，脸色青中泛黄，面目却颇英俊。\n");
	set("gender", "男性");
	set("age", 27);
        set("attitude", "peaceful");
        set("str", 30);
        set("int", 24);
        set("con", 23);
        set("dex", 30);
        set("per", 24);

        set("max_qi", 15500);
        set("max_jing", 6000);
        set("eff_jingli", 5500);
        set("combat_exp", 6800000);
        set("shen", -18000);

    	set_skill("force", 400);
    	set_skill("huagong-dafa", 400);
    	set_skill("dodge", 400);
    	set_skill("zhaixingshu", 400);
    	set_skill("strike", 400);
    	set_skill("chousui-zhang", 400);
    	set_skill("poison", 190);
    	set_skill("parry", 400);
    	set_skill("staff", 400);
    	set_skill("tianshan-zhang", 400);
    	set_skill("literate", 120);
    	set_skill("claw", 400);
    	set_skill("sanyin-zhua", 400);

    	map_skill("force", "huagong-dafa");
    	map_skill("dodge", "zhaixingshu");
    	map_skill("strike", "chousui-zhang");
    	map_skill("parry", "chousui-zhang");
    	map_skill("staff", "tianshan-zhang");
    	map_skill("claw", "sanyin-zhua");
    	prepare_skill("claw", "sanyin-zhua");
    	prepare_skill("strike", "chousui-zhang");

    	set("chat_chance_combat", 15);
    	set("chat_msg_combat", ({
                (: exert_function, "huagong" :),
                (: perform_action, "strike.huoqiu" :),
                (: perform_action, "strike.yinhuo" :),
                (: perform_action, "strike.biyan" :),
    	}));

    	create_family("星宿派", 2, "弟子");
    	set("inquiry", ([
		"星宿派" : "你想加入，就拜我为师。",
                "星宿海" : "去星宿海干什么？拜我为师就够你学的了。",
                "丁春秋" : "丁春秋是你叫的吗？没大没小的。以后叫老仙！",
				"海底捞月" : (: ask_laoyue :),
                "老仙" : (: ask_job :),
	]));
    	setup();
    	UPDATE_D->get_cloth(this_object());
    	carry_object("/d/xingxiu/obj/yao");
    	carry_object("/d/xingxiu/obj/yao1");
    	carry_object("/d/xingxiu/obj/yao3");
    	add_money("silver", 60);
}
void attempt_apprentice(object ob)
{
	if(ob->query("family/family_name") != "星宿派"){
        	say("摘星子对"+ob->name()+"理都不理。\n");
        	return;
        }
     	if(ob->query_skill("huagong-dafa",1) < 250 || ob->query("shen") > -50000){
        	command("say 你的条件还不够，我才不想收你呢。");
        	return;
        }
		if(ob->query_skill("poison",1) < 120 ){
			command("say 你的毒计还不够120，我才不想收你呢。");
			return;
		}
     	command("say 好吧，看来你的化功大法有点基础了，我就收下你吧。");
     	command("recruit " + ob->query("id"));
}
string ask_job()
{
  	object me, ob;
  	mapping fam;
  	int shen, exp;
  	me = this_player();
  	fam = (mapping)me->query("family");
  	shen = me->query("shen");
  	exp=me->query("combat_exp",1);
    
	if (!me->query_temp("ding_flatter"))
	{
		command("say 你不去讨好老仙，来此做什么？");
		return "摘星子神情似乎极为清冷，不知道在说什么。\n";
	}
    	if(!fam) return "看得出你对老仙态度恭敬，何不加入我星宿派呢？";
    	if(fam["family_name"] != "星宿派" && !me->query_temp("ding_flatter"))
       		return "你对老仙的态度看上去不太恭敬啊！";
    	if(exp < 1000000)
    		return "哈哈哈，你这点功夫出去还不够丢人的，再加把力练功吧。";
        //if(exp >= 1000000 )
    		//return "老仙最近的情况我不太清楚，你自己去问问他老人家吧。";
		if( me->query("job_name") == "老仙分忧")
			return "老仙现在心情还好，不用你来为老仙分忧。";
    	if(me->query_condition("wait_xx_task"))
    		return "上次搞砸了，这次你就等等吧。";
    	if( me->query_temp("xx_job"))
    		return "你怎么还在这里发呆？";
    	if( me->query_condition("wait_xx_task"))
    		return "老仙现在心情还好，不用你来为他分忧。";
    	ob = new("/d/xingxiu/obj/di");
    	ob->move(me);
    	ob->set("name", MAG "紫玉短笛" NOR);
    	ob->set("long", MAG"这玉笛短得出奇，只不来七寸来长、通体紫红，晶莹可爱。\n" NOR);
    	ob->set("xx_user", getuid(me));
    	if(fam["family_name"] != "星宿派")
      		me->set_temp("title", MAG"星宿派门客"NOR);
    	me->set_temp("xx_job", 1);
    	message_vision("\n$N拿出一只玉制短笛，交给$n。\n", this_object(), me);
    	return "老仙最近心情不佳，你可要多多为他老人家分忧才是！\n";
}
string ask_laoyue()
{
  	object me, ob;
  	mapping fam;
  	int shen, exp;
  	me = this_player();
  	fam = (mapping)me->query("family");
  	shen = me->query("shen");
  	exp=me->query("combat_exp",1);

    	if(!fam) return "看得出你对老仙态度恭敬，何不加入我星宿派呢？";
    	if(fam["family_name"] != "星宿派" && !me->query_temp("ding_flatter"))
       		return "你对老仙的态度看上去不太恭敬啊！";
    	if(exp < 150000)
    		return "哈哈哈，连150k都不到，你再加把力练功吧。";
        if(me->query_skill("huagong-dafa",1)<100 
			||me->query_skill("zhaixingshu",1)<100)
    		return "海底捞月全凭强大内功和轻功支持，这两项连100都不到，赶紧练功去。";
		
    	if (me->query("quest/xx/tsz/laoyue/pass"))
			return "这位"+RANK_D->query_respect(me)+"你已经解开了天山杖海底捞月绝技，别没事来骚扰我!";
        if (time()-me->query("quest/xx/tsz/laoyue/time")<86400)
			return "这位"+RANK_D->query_respect(me)+"你也太勤快点了，还是需要继续努力才好!";
        //标记状态
		me->set("quest/xx/tsz/laoyue/time",time());
		me->set("quest/xx/tsz/laoyue/exp",me->query("combat_exp"));
		command("say 这海底捞月乃是利用摘星术的身法，快速抓住飞出去杖法的一门技巧。\n");
		command("say 你若想学，就附耳过来听我仔细道来。\n");
        if(random(me->query("kar"))> 15) 
	    {
			command("heng "+me->query("id"));
	   	    command("pat "+me->query("id"));
		    message_vision(HIC"\n你终于领悟了摘星子说的海底捞月绝技。\n",me);
		    me->set("quest/xx/tsz/laoyue/pass",1);
			log_file("quest/xxlaoyue", sprintf("%s(%s) 失败%d次成功解开海底捞月绝技。富源：%d；经验：%d。\n",   
             me->name(1),
             me->query("id"), 
             me->query("quest/xx/tsz/laoyue/fail"),
             me->query("kar"),
             me->query("combat_exp")) );
			command("grin ");
            return "摘星子说道，好吧，以后你就是我这一脉的人了。否则我定会追杀到底！"; 
			
		  }
		  else {
	   	    command("say 很抱歉，我帮不了你。下次再来吧。");
			me->set("quest/xx/tsz/laoyue/time",time());
			me->set("quest/xx/tsz/laoyue/exp",exp);	
			log_file("quest/xxlaoyue", sprintf("%s(%s) 解海底捞月失败%d次。富源：%d；经验：%d。\n",   
             me->name(1),
             me->query("id"), 
             me->query("quest/xx/tsz/laoyue/fail"),
             me->query("kar"),
             me->query("combat_exp")) );
			me->add("quest/xx/tsz/laoyue/fail",1);
			return "摘星子扫了你几眼，悄声嘀咕道，“这货居然这么笨。不是我的菜啊。”\n";
		  }
}
