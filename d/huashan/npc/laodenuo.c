// NPC: /d/huashan/npc/laodenuo.c
// Date: Look 99/03/25
// Lklv Modify at 2001.10.18
// By Spiderii@yt修改俸禄
#include <ansi.h>
inherit NPC;
//inherit F_MASTER;

string ask_me(object who);
int ask_gold(object who);

void create()
{
        set_name("劳德诺", ({ "lao denuo", "lao", "denuo" }));
        set("nickname", "老好人");
        set("long",
"劳德诺身材矮胖，满面红光，成天笑眯眯的，他在\n"
"同门中排行第二，是华山派年轻一代中唯一带艺投师的。\n");
        set("gender", "男性");
        set("age", 54);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 24);
        set("per", 18);
        set("int", 25);
        set("con", 20);
        set("dex", 20);

        set("max_qi", 3000);
        set("max_jing", 1800);
        set("neili", 3000);
        set("max_neili", 3000);
        set("eff_jingli", 1800);

        set("jiali", 150);
        set("combat_exp", 3000000);
        set("score", 6000);
        set("miji",1);
        set_skill("force", 250);
        set_skill("dodge", 250);
        set_skill("parry", 250);
        set_skill("sword", 350);
        set_skill("cuff", 250);
        set_skill("hand", 250);
        set_skill("songshan-jian", 250);
        set_skill("huashan-jianfa", 350);
        set_skill("huashan-shenfa", 250);
        set_skill("poyu-quan", 250);
        set_skill("hanbing-zhenqi", 250);
        set_skill("songyang-shou", 250);
       // set_skill("zhengqi-jue", 100);
        set_skill("huashan-qigong", 250);

        map_skill("hand", "songyang-shou");
        map_skill("dodge", "huashan-shenfa");
        map_skill("force", "huashan-qigong");
        map_skill("parry", "huashan-jianfa");
        map_skill("sword", "huashan-jianfa");
        map_skill("cuff", "poyu-quan");

        prepare_skill("cuff", "poyu-quan");
        prepare_skill("hand", "songyang-shou");
        set("chat_msg_combat", ({
               	(: perform_action, "sword.fengyi" :),
				(: exert_function, "juli" :),
        }) );
        set("chat_chance", 100);
        set("chat_msg", ({
                
        }) );
        set("inquiry", ([
                "紫霞秘籍" : (: ask_me :),
                 "左掌门" : (: ask_gold :),
        ]) );

        create_family("华山派", 14, "弟子");

        setup();
        carry_object(BINGQI_D("sword/sword"))->wield();
        carry_object(ARMOR_D("armor/cloth"))->wear();
}
/*void reset()
{
	object obb;
	if (clonep() && (obb = unew(__DIR__"obj/zixia")))
		obb->move(this_object());
} */

string ask_me(object who)
{
       int i;
        object *ob;
		object book,me;
        me=this_player();
		//if (!me->query_temp("zixia_asklao")) return "「紫霞秘籍」是我华山第一武技？";
		if ( present("zixia miji", me))
		     return "咦？「紫霞秘籍」不是在你身上么？还问我作甚？";
		
	  
       
		book = new(BOOK_D("zixia"));
		book->move(this_object());
        if (me->query("quest/zixia/pass"))
		{
			message_vision(HIC"劳德诺对$N翻了一个白眼，冷哼一声，知道他对自己的底细，交给$N一本紫霞秘籍后就转过身去。\n"NOR,me);
			
			book->move(me);
			return "劳德诺不再是以前的劳德诺了，随后鬼鬼祟祟的装作若无其事的样子，但神情甚是紧张,似乎做了什么亏心事一样。\n";
		}
		if( (time()- me->query("quest/zixia/time"))<86400)		
     		return "你来的也太勤快了耶，还是去休息一下吧。\n";
	    if( is_fighting() || !me->query_temp("quest/huashan/zixia5") )
            return "对不起，这件事，我不清楚，你还是问我师傅去吧！\n";
       	me->delete_temp("quest/huashan/zixia5");
		me->set_temp("zixia_asklao",1);
		
		set_temp("apply/attack",  150);
        set_temp("apply/defense", 150);
		set_temp("apply/armor",   150);
        set_temp("apply/damage",  150);
		set_temp("apply/sword",   150);
		
        message("vision",
                YEL "看来这件事你都知道了？臭贼，去死吧！\n"
                "劳德诺使开长剑，招数精奇，狠辣无比，一改整日笑咪咪的模样。\n" NOR,
                environment(), this_object() );
        
       ob = all_inventory(environment(this_object()));
	   for(i=sizeof(ob)-1; i>=0; i--) {
                if( !userp(ob[i]) ) continue;
                /*if( ob[i]->query_temp("quest/huashan/zixia5"))
                        {
                         ob[i]->delete_temp("hs/askzixia");
						// book = unew(__DIR__"obj/zixia");
						
                         if( clonep(book)){
							 book->move(this_object());
							 write("eeeeeeeee");}
						}*/
              
			   kill_ob(ob[i]);
               ob[i]->fight(this_object());
        }
                            
        return "\n我带艺投师，忍辱负重，你竟敢打我的主意，去死吧！\n";
}

void die()
{
        
		int i,j;
		object me = query_temp("last_damage_from");
		//object me = this_player();
	    object ob = present("zixia miji", this_object());
		
		if (objectp(me))
		{	
		
	    //if (!me->query_temp("zixia_asklao")) return "「紫霞秘籍」是我华山第一武技？";
     	j = 25;
		if(me->query("m-card-vip")) j =  22;
		if(me->query("y-card-vip")) j =  18;
		if(me->query("buyvip"))     j =  15;
		j=random(j);
		i=random(me->query("kar"));
		if ( ob ) {		
		    if (objectp(me)
				&& me->query_temp("zixia_asklao")
				&& me->query("kar")<31
				&& i > 28
				&& random(me->query("con"))>40
				&& j<3)      
              {
			     command("say 哈哈，你我也算是有缘之人，这本「紫霞秘籍」就交给你吧。");
				 message_vision(HIC"\n 恭喜！「华山九功，紫霞第一」，你历经艰辛万苦终于得偿所愿。\n", me);
			
			     me->set("quest/zixia/pass", 1);
			     me->delete_temp("zixia_asklao");
				 log_file("quest/zixia", sprintf("%s(%s) 失败%d次后，历经千辛万苦终于成功解开紫霞功。富源：%d；经验：%d。\n", me->name(1),me->query("id"), me->query("quest/zixia/fail"),me->query("kar"),me->query("combat_exp")) );
				 me->set("title",HIM"紫霞功传人"NOR);
			     ob->set("owner", me);
			     ob->move(me);
	        }
            else {
			     message_vision(CYN"\n$N怒叫道：「即使我死了，你等也休想得到「紫霞秘籍」，哈哈哈哈……」\n"NOR, this_object());
			     message_vision("$N将那「紫霞秘籍」放在双掌中一搓，功力到处，一本原已十分陈旧的册页登时化作碎片。\n\n", this_object());
			     log_file("quest/zixia", sprintf("%s(%s) 解密紫霞功失败%d次。富源：%d；经验：%d。\n", me->name(1),me->query("id"), me->query("quest/zixia/fail"),me->query("kar"),me->query("combat_exp")) );
				 if ( objectp(me)) {
				    me->add("quest/zixia/fail", 1);
				    me->set("quest/zixia/time", time());
					}
			     ob->set("name", HIW"紫霞秘籍的碎片"NOR);
			     ob->move(environment(this_object()));
				 me->delete_temp("zixia_asklao");
               }
			me->delete_temp("zixia_asklao");
		}
		}
	::die();
}
int ask_gold(object who)
{
        object me = this_player();
        

        if( me->query("family/family_name") != "华山派" ) {
                command("hmm "+(string)me->query("id"));
                command("say 你非我派弟子，也敢来滥竽充数！\n");
                return 1;
        }

        if( me->query("shen") < 10000 ) {
                command("noway "+(string)me->query("id"));
                command("say 你目露凶光,给你钱财怕不能用在正处！\n");
                return 1;
        }
        if( (int)me->query("huashan_given") <(int)me->query("age")){
                 command("nod "+(string)me->query("id"));
               who->add_money("gold",(int)(me->query_skill("huashan-jianfa", 1)/2) );
               command("give "+me->query("id")+" "+(int)(me->query_skill("huashan-jianfa", 1))/2+" gold");
                me->set("huashan_given",(int)me->query("age"));

                command("say 看来" + RANK_D->query_respect(me) + "对我的身份已经略有所知了，不过左掌门一向器重人才！");
		command("say 我这里有些小意思，还请" + RANK_D->query_respect(me) + "帮我保守秘密啊！");
        } else command("say " + RANK_D->query_respect(me) + "如想得到左掌门的赏识，在剑法方面还需多多努力啊！");

        return 1;
}