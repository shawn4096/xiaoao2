// fan.c 范遥
// 4/4/97 -qingyun
// 16.10.98 snowman
// Modify By River@sj 99.6
//modify by looklove@sj 2000.11
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_me();
string ask_luanjian();
void create()
{
        set_name("范遥",({"fan yao","fan","yao"}));
        set("title","明教光明右使");
        set("nickname",WHT"逍遥二仙"NOR);
        set("long", "他就是明教的光明右使，和杨逍合称逍遥二仙的范遥。\n"+
                    "他身着一身白衫，虽然已是中年，但看上去还十分英俊潇洒。\n");
        set("age", 46);
        set("attitude", "peaceful");
        set("shen", -10000);
        set("str", 36);
        set("per", 28);
        set("int", 29);
        set("con", 27);
        set("dex", 30);
        set("max_qi", 25000);
        set("max_jing", 4500);
        set("eff_jingli", 4500);
        set("jiali", 200);
        set("combat_exp", 9700000); 
        set("unique", 1);
		set("quest/mj/xyj/luanjian/pass",1);
		set("xyjf/jueji","pass");

        set_skill("sword",500); 
        set_skill("dodge",450);
        set_skill("force", 500);
        set_skill("blade",400);
        set_skill("literate",250);
        set_skill("hand",450);
        //set_skill("strike",420);
        //set_skill("hanbing-mianzhang",170);
        set_skill("yingzhua-shou",450);
        set_skill("piaoyi-shenfa", 450);
        set_skill("shenghuo-shengong", 500);
        set_skill("lieyan-dao",400);
        set_skill("xiaoyao-jian",500);
        set_skill("parry", 450);

        map_skill("force", "shenghuo-shengong");
        map_skill("dodge", "piaoyi-shenfa");
        map_skill("sword", "xiaoyao-jian");
        map_skill("parry", "lieyan-dao");
        map_skill("blade", "lieyan-dao");
        map_skill("hand", "yingzhua-shou");
       //map_skill("strike", "hanbing-mianzhang");
       // prepare_skill("strike", "hanbing-mianzhang");
        prepare_skill("hand","yingzhua-shou");

        create_family("明教",35,"使者");

        set("inquiry", ([
                 "黑玉断续膏" : (: ask_me :),
				"乱剑诀" : (: ask_luanjian :),
        ]));
        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: exert_function, "shenghuo" :),
			    (: perform_action, "xiao" :),
				(: perform_action, "xiaoyao" :),
				(: perform_action, "luanjian" :),

        }));
        setup();
        //if ( random(10) > 5 )
        carry_object(BINGQI_D("sword"))->wield();
        carry_object("/d/mingjiao/obj/white-cloth")->wear();
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
        if(fam["master_name"] == "杨逍"){
                command("say 逍遥二仙不分你我，既然逍兄最近公事繁忙，你就暂时来我这里吧。");
                ob->set("title", this_object()->query("title")+"座下弟子");
                command("recruit " + ob->query("id"));
                return;
                }
        if (fam["generation"] > (my_fam["generation"] + 2)){
                command("say 依我看你应该先在四位法王那里把本事学好再来。");
                return;
                }
        if ((int)ob->query_skill("shenghuo-shengong", 1) < 300) {
                command("say 要学更为高深的武功，必须有高深的内功修为。"); 
                command("say " + RANK_D->query_respect(ob)+"是否还应该在圣火神功上多下点功夫？");
                return;
                }
        if ((int)ob->query_int() < 40) {
                command("say 逍遥二仙的武功博而杂，要学会这些武功，非得有极高的悟性。");
                command("say 在悟性方面，"+RANK_D->query_respect(ob)+"是否还不够？");
                return;
                }
        command("say 嗯，看你还是个学武的料，我就收下你吧！");
        command("say 多谢明尊敝佑，让我明教又得一良材，为康扶正义，把我明教发扬光大吧。");
        command("recruit " + ob->query("id"));
        ob->set("title", HIW+this_object()->query("title")+"座下弟子"NOR);
}

string ask_me()
{
	mapping fam; 
	object ob, *clone;
	int i, j;

	if(!(fam = this_player()->query("family")) || fam["family_name"] != "明教")
		return RANK_D->query_respect(this_player())+"与本派素无来往，不知此话从何谈起？";

	if (! this_player()->query_skill("jiuyang-shengong"))
	if(this_player()->query_skill("shenghuo-shengong", 1) < 50)
		return "你在明教的时日尚短，这黑玉断续膏你还不够资格使用。";

	if(this_player()->query_temp("marks/膏1"))
		return "你不是刚拿了黑玉断续膏了吗，怎么还要？";

	if(present("heiyu duanxugao", this_player()))
		return "你身上不是带着黑玉断续膏吗，怎么还要？";

	if ((int)this_player()->query("eff_qi") == (int)this_player()->query("max_qi"))
		return "你现在不需要用黑玉断续膏。";

	ob=unew(MEDICINE_D("heiyu"));        
	if(!clonep(ob)) return "你来晚了，黑玉断续膏已给全部发出去了。"; 
	i = ob->query("unique");
	clone = filter_array(children(base_name(ob)), (: clonep :));
	j = sizeof(clone);
	while (j--) if (!clone[j]->query("clone_by_wizard")) i--; 
	if(clonep(ob) && i < 0){
		destruct(ob);
		return "抱歉，你来晚了，黑玉断续膏已经没有了。";
	} 
	ob->move(this_player());
	this_player()->set_temp("marks/膏1",1);
	return "好吧，这盒黑玉断续膏你就拿去用吧。";
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
        
	if (userp(ob) && ob->query("family/family_name") == "明教") {
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


string ask_luanjian()
{
	mapping fam; 
	object me;
	int i, j;
	me=this_player();
	if(!(fam = this_player()->query("family")) || fam["family_name"] != "明教")
		return RANK_D->query_respect(this_player())+"与本派素无来往，不知此话从何谈起？\n";

	if ( this_player()->query_skill("sword",1)<300) 
		return RANK_D->query_respect(this_player())+"你的基本剑法不足300，努力练习去！\n";

	if(this_player()->query_skill("xiaoyao-jian", 1) < 300)
		return "你的逍遥剑法不足300，努力练习去！\n";

	if(time()-me->query("quest/mj/xyj/luanjian/time")<86400)
		return "你如此勤快，真是大明教的好弟子!\n";
	if(me->query("quest/mj/xyj/luanjian/pass"))
		return "你已经解开这逍遥剑乱剑诀，真是大明教的好弟子!\n";
	j=18;
	if(me->query("m-card-vip")) j =  15;
    if(me->query("y-card-vip")) j =  12;
    if(me->query("buyvip"))     j =  8;
	i=random(j);
	command("say 这乱剑诀乃是我多年的心得，你若要学习要好好听好了。\n");
	command("say 学好这门武功的诀窍是你的武学修养要极其杂驳，取其广博之意。\n");
	command("say 这门武功靠的是悟性，若没有好的悟性也不行。\n");
	command("say 你听好。\n");
	if(i<3 && random(me->query("kar"))>=23)
	{
		tell_object(me,HIY"\n你按照范瑶的指点，对逍遥剑的乱剑诀奥秘似乎有些心得。\n"NOR);
		tell_object(me,HIY"\n你将范瑶讲解的内容和先前自己所学相互印证，随即起身，忍不住哈哈大笑。\n"NOR);
		tell_object(me,HIG"\n恭喜你历经千辛万苦，终于解开逍遥剑的乱剑诀秘密。\n"NOR);
     //   tell_object(me,HIR"\n你已经将乾坤大挪移第七层神功彻底融汇贯通。\n"NOR);
       
		
		//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		//me->set(QUESTDIR4+"sword",1);
		me->set("quest/mj/xyj/luanjian/pass",1);	
		log_file("quest/xyjluanjian", sprintf("%8s(%8s) 失败%d次后，彻底领悟逍遥剑乱剑诀的绝技。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/mj/xyj/luanjian/fail"),i,me->query("combat_exp")) );
	}
	else
	{
		me->add("quest/mj/xyj/luanjian/fail",1);
		command("poor ");
		tell_object(me,HIY"你听了范瑶的指点，虽然听说了这种武功的奥秘，可是对这招的奥秘全然不得要领。\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->set("quest/mj/xyj/luanjian/time",time());
		log_file("quest/xyjluanjian", sprintf("%8s(%8s) 逍遥剑乱剑诀解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/mj/xyj/luanjian/fail"),i,me->query("combat_exp")) );
	}
	return "嗯，这逍遥剑的乱剑诀是我多年的心得，你要好好的闯荡江湖，不要弱了我逍遥二仙的威名！\n";
	
}
