// NPC yin.c 殷天正
// Modify By River@sj 99.06
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_me();
string ask_jueji();
string ask_book();
void create()
{
        set_name("殷天正",({"yin tianzheng","yin","tianzheng"}));
        set("title","明教护教法王");
        set("nickname",HIW"白眉鹰王"NOR);
        set("long", "他就是明教的四大护法之一，一个身材魁梧的秃顶老者。\n"+
                    "他长眉胜雪，垂下眼角，鼻子钩曲，有若鹰嘴。\n");                    
        set("age", 61);
        set("attitude", "peaceful");
        set("shen", -13000);
        set("str", 35);
        set("per", 20);
        set("int", 25);
        set("con", 28);
        set("dex", 25);        
        set("max_qi", 30000);
        set("max_jing", 12700);
        set("eff_jingli", 12700);
        set("jiali", 200);
        set("combat_exp", 9500000);
        set("unique", 1);
        
        set_skill("dodge",400);
        set_skill("force", 480);
        set_skill("literate",210);
        set_skill("piaoyi-shenfa", 400);
        set_skill("shenghuo-shengong",480);
		set_skill("lieyan-dao",400);
		set_skill("blade",400);
        set_skill("yingzhua-shou",480);
        set_skill("hand",480); 
        set_skill("parry", 480);        
        map_skill("force", "shenghuo-shengong");
		map_skill("blade", "lieyan-dao");
        map_skill("dodge", "piaoyi-shenfa");
        map_skill("hand", "yingzhua-shou");
        map_skill("parry", "yingzhua-shou");
        prepare_skill("hand","yingzhua-shou");

        create_family("明教", 36, "法王");
        set("inquiry", ([
                 "宝剑" : (: ask_me :),
                 "白虹剑" : (:ask_me :),
                 "鹰爪手法" : (: ask_book :),
			     "鹰爪绝技" : (: ask_jueji :),
        ]));
		set("chat_chance_combat", 60);
         set("chat_msg_combat", ({
                (: perform_action, "hand.qinna" :),
				(: perform_action, "hand.yingyang" :),        
				(: exert_function, "shenghuo" :),  
					
	    }));
        setup();
        carry_object("/d/mingjiao/obj/yel-cloth")->wear();
}

void init()
{
	::init();
        add_action("do_kill", "kill");
        add_action("do_kill", "tk");
        add_action("do_kill", "teamkill");
        add_action("do_kill", "hit");
}

void attempt_apprentice(object ob)
{
        object me  = this_object();
        mapping fam = ob->query("family");
        mapping my_fam = me->query("family");
        if(!fam || fam["family_name"] != "明教"){
                command("say "+RANK_D->query_respect(ob) + "与本派素无来往，不知此话从何谈起？");
                return;
                }
        if(fam["master_name"] == "张无忌"){
                command("haha");
                command("say "+RANK_D->query_respect(ob)+"已是教主亲传弟子，"+RANK_D->query_self(me)+"怎敢再收你为徒？"); 
                return;
                }
        if (fam["generation"] == my_fam["generation"]){
                command("shake");
                command("say "+RANK_D->query_respect(ob)+"已拜光明使为师，"+RANK_D->query_self(me)+"怎敢再收你为徒？");
                return;
                }
        if ((int)ob->query_skill("shenghuo-shengong", 1) < 100) {
                command("say 要学更为高深的武功，必须有高深的内功修为。"); 
                command("say " + RANK_D->query_respect(ob)+"是否还应该在圣火神功上多下点功夫？");
                return;
                }     
        if ((int)ob->query_str() < 28) {
                command("say 想学我的鹰爪手法，必须要有足够的力量。");
                command("say 在臂力方面，"+RANK_D->query_respect(ob)+"是否还嫌差了点？");
                return;
                }   
        command("say 嗯，看你还是个学武的料，我就收下你吧！");
        command("say 多谢明尊敝佑，让我明教又得一良材，为康扶正义，把我明教发扬光大吧。");
        command("recruit " + ob->query("id"));
        ob->set("title", HIW"明教白眉鹰王属下教众"NOR);
}

string ask_me()
{
	object me = this_player();
        object ob;

        if (!me->query("family") || me->query("family/family_name") != "明教")
        	return RANK_D->query_respect(this_player())+"与本派素无来往，不知此话从何谈起？"; 

        if (me->query("combat_exp") < 100000)
        	return RANK_D->query_respect(me)+"看来功力不够，恐怕不能保住这把宝剑。";

        ob=unew(BINGQI_D("sword/baihong-jian"));
        if(!clonep(ob)) return "你来晚了，我的白虹宝剑已给别人拿走了。";  
        if(clonep(ob) && ob->violate_unique()){
           destruct(ob);
           return "你来晚了，我的白虹宝剑已给别人拿走了。";
        } 
        ob->move(me);
        return "好吧，这把白虹宝剑你就拿去吧，望你不要借它为恶，常为行侠仗义。";
}

string ask_jueji()
{
	    object me = this_player();
        object ob;
		int exp1,exp2,t1;

        if (!me->query("family") || me->query("family/family_name") != "明教")
        	return RANK_D->query_respect(this_player())+"与本派素无来往，不知此话从何谈起？"; 

        if (me->query("combat_exp") < 200000)
        	return RANK_D->query_respect(me)+"看来功力不够，恐怕不能领悟老夫的鹰爪绝技。";
		 exp1=(int)me->query("combat_exp",1);
		 exp2=exp1-me->query("mj/quest/yzs/exp");

        if (me->query("mjyzs/pass"))
			return "这位"+RANK_D->query_respect(me)+"你已经解开了鹰抓手绝技，别没事来骚扰我!";
        if (time()-me->query("mj/quest/yzs/time")<86400)
			return "这位"+RANK_D->query_respect(me)+"你也太勤快点了，还是需要继续努力才好!";
        //标记状态
		me->set("mj/quest/yzs/time",time());
		me->set("mj/quest/yzs/exp",me->query("combat_exp"));

        if(random(me->query("kar"))> 20) 
	      {
			command("haha");
	   	    command("pat "+me->query("id"));
		    message_vision(HIC"\n你终于领悟了白眉鹰王的鹰爪绝技。\n",me);
		    me->set("mjyzs/pass",1);
			log_file("quest/mjyzs", sprintf("%s(%s) 失败%d次成功解开鹰抓手绝技。富源：%d；经验：%d。\n",   
             me->name(1),
             me->query("id"), 
             me->query("mj/quest/yzs/fail"),
             me->query("kar"),
             me->query("combat_exp")) );
            return "殷天正说道，好吧，望你不要借此绝技为恶江湖，常为行侠仗义。否则老夫定会追杀到底！"; 
			
		  }
		  else {
	   	    command("say 很抱歉，我帮不了你。下次再来吧。");
			me->set("mj/quest/yzs/time",time());
			me->set("mj/quest/yzs/exp",exp1);	
			log_file("quest/mjyzs", sprintf("%s(%s) 解白眉鹰抓手失败%d次。富源：%d；经验：%d。\n",   
             me->name(1),
             me->query("id"), 
             me->query("mj/quest/yzs/fail"),
             me->query("kar"),
             me->query("combat_exp")) );
			me->add("mj/quest/yzs/fail",1);
			return "殷天正白眉轩扬，说道，我很看好你，继续努力。\n";
		  }
		
}
string ask_book()
{
        mapping fam; 
        object ob;
        if(!(fam = this_player()->query("family")) || fam["family_name"] != "明教")
            return RANK_D->query_respect(this_player())+"与本派素无来往，不知此话从何谈起？"; 
        if(this_player()->query_skill("hand", 1) > 30 )
            return RANK_D->query_respect(this_player())+"看来已经不需要这本书了，还是留给其他明教弟子用吧！";
        ob = unew("/d/mingjiao/obj/hand_book");
        if(!clonep(ob)) return "你来晚了，「鹰爪手法」已经被你师兄拿去了。";
        if(clonep(ob) && ob->violate_unique()){
           destruct(ob);
           return "你来晚了，「鹰爪手法」已经被你师兄拿去了。";
        } 
        ob->move(this_player());
        return "好吧，这本「鹰爪手法」你拿回去好好钻研。";
}

void die()
{
        object me,sword;
        me = query_temp("last_damage_from");
	if (objectp(me))
        if (clonep()) {
          sword = unew(BINGQI_D("sword/baihong-jian"));
          if (!sword) sword = unew(BINGQI_D("changjian"));
          message_vision("\n$N从殷天正的身上搜出一把"+sword->name()+"。\n", me);
          sword->move(me); 
        }
        ::die();
}

int do_kill(string arg)
{
        object ob,ob2; 
        object me = this_player();
        ob2 = this_object();

        if (!arg) return 0;
        ob = present(arg, environment(me));
        if (ob == this_object() || ob == me) return 0;
        if (!ob || !ob->is_character()) return 0;

        
        if (userp(ob) 
         && ob->query("family/family_name") == "明教") {
                if (me->query("family/family_name") == "明教") { 
                        message_vision(ob2->name()+"对$N喝道：身为明教弟子，竟然杀自己的同门？我宰了你！\n", me);
                }
                else {
                        message_vision(ob2->name()+"对$N喝道：大胆狂徒，居然敢来明教撒野！\n", me);
                        kill_ob(me);
                }
                me->set("vendetta/明教", 1);
                return 1;
        }
        return 0;
}
