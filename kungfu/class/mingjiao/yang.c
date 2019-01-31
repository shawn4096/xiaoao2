// yang.c 杨逍
// 4/4/97 -qingyun
// 16.10.98 snowman
// Modify By River@sj 99.6
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_me();
string dagger();
int ask_xiaoyao();
void create()
{
        set_name("杨逍",({"yang xiao","yang","xiao"}));
        set("title", "明教光明左使");
        set("nickname",WHT"逍遥二仙"NOR);
        set("long", "他就是明教的光明左使，和范遥合称逍遥二仙的杨逍。\n"+
                    "他身着一身白衫，虽然已是中年，但看上去还十分英俊潇洒。\n");
        set("age", 50);
        set("attitude", "peaceful");
        set("shen", -15000);
        set("str", 26);
        set("per", 29);
        set("int", 29);
        set("con", 27);
        set("dex", 30);         
        set("max_qi",24000);
        set("max_jing", 6000);
        set("eff_jingli", 6000);
        set("jiali", 200);
        set("combat_exp", 9700000);
        set("unique", 1);
        set("no_get",1);
		set("quest/mj/xyj/luanjian/pass",1);
		set("xyjf/jueji","pass");

        set("no_quest", 1);
        set_skill("sword",500); 
        set_skill("blade",450);
        set_skill("literate",300);
        set_skill("hand", 450);
        set_skill("strike", 450);
        //set_skill("hanbing-mianzhang", 420);
        set_skill("xiaoyao-jian", 500);
        set_skill("dodge",450);
        set_skill("force", 480);
        set_skill("piaoyi-shenfa", 450);
        set_skill("lieyan-dao",450);
        //set_skill("liehuo-jian",420);
        set_skill("shenghuo-shengong", 480);
        set_skill("parry", 450); 

        map_skill("force", "shenghuo-shengong");
        map_skill("dodge", "piaoyi-shenfa");
        map_skill("sword", "xiaoyao-jian");
        map_skill("parry", "liehuo-jian");
        map_skill("blade", "lieyan-dao");
        map_skill("hand", "yingzhua-shou");
        //map_skill("strike", "hanbing-mianzhang");
       // prepare_skill("strike", "hanbing-mianzhang");
        //prepare_skill("hand","yingzhua-shou");
        create_family("明教",35,"使者");

        set("inquiry", ([
                "匕法概论" : (: dagger :),
                "book" : (: dagger :),
                "铁焰令" : (: ask_me :),
			    "逍遥剑绝技" : (: ask_xiaoyao :),
                "霹雳雷火弹":"听说西域有人从中国学得造火药之法，制出一种暗器。\n"
                        "叫作‘霹雳雷火弹’，中藏烈性火药，以强力弹簧机括发射。\n",
        ]));

        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: exert_function, "shenghuo" :),
			    (: perform_action, "xiao" :),
				(: perform_action, "xiaoyao" :),
				(: perform_action, "luanjian" :),


        }));
        setup(); 
        if( random(10) > 5)
        carry_object(BINGQI_D("changjian"))->wield();
        carry_object("/d/mingjiao/obj/white-cloth")->wear();
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
        if(fam["master_name"] == "范遥"){
                command("say 逍遥二仙不分你我，既然范兄最近事务繁忙，你就暂时来我这里吧。");
                ob->set("title", this_object()->query("title")+"座下弟子"); 
                command("recruit " + ob->query("id"));
                return;
                }
        if (fam["generation"] > (my_fam["generation"] + 2)){
                command("say 依我看你应该先在四位法王那里把本事学好再来。");
                return;
                }
        if ((int)ob->query_skill("shenghuo-shengong", 1) < 300) {
                command("say 要学更为高深的武功，必须有高深的内功修为。不到300不要来找我。"); 
                command("say " + RANK_D->query_respect(ob)+"是否还应该在圣火神功上多下点功夫？");
                return;
                }
        if ((int)ob->query_int() < 40) {
                command("say 逍遥二仙的武功博而杂，要学会这些武功，非得有极高的悟性。");
                command("say 在悟性方面不足40点，"+RANK_D->query_respect(ob)+"是否还不够？");
                return;
                }
        command("say 嗯，看你还是个学武的料，我就收下你吧！");
        command("say 多谢明尊敝佑，让我明教又得一良材，为康扶正义，把我明教发扬光大吧。");
        command("recruit " + ob->query("id"));
        ob->set("title", HIW+this_object()->query("title")+"座下弟子"NOR);
}
 
void init()
{
        object me, ob;
        mapping fam;
        ::init();
        ob = this_player();
        me = this_object();        
	 if(interactive(ob) && !wizardp(ob)
	 && base_name(environment(me))=="/d/mingjiao/longwang"
	 && ((fam = ob->query("family")) && fam["family_name"] != "明教" )){
		command("say 这里是明教的重地，别说是外人，就是明教中人也不能随意进出，赶快离开此地！");
		command("consider "+ob->query("id"));  
		remove_call_out("kill_ob");
		call_out("kill_ob", 5, ob); 
	}
	if(interactive(ob) && ob->query_temp("mj_jiaozhu"))           
		command("nod "+ob->query("id"));   
	else 
		command("hehe "+ob->query("id"));      
}

string dagger()
{
	mapping fam = this_player()->query("family");
	object ob;        
	if(!fam || fam["family_name"] != "明教")
		return RANK_D->query_respect(this_player())+"与本教素无来往，不知此话从何谈起？";

	if(this_player()->query_skill("dagger",1) > 100)
		return "你的匕法已经有一定基础了，这本书对你没什么用，还是留给别人吧";        

	if(! this_player()->query_skill("jiuyang-shengong", 1))
	if(this_player()->query_skill("shenghuo-shengong", 1) < 100)
		return "你在明教的时日尚短，过段时日再来吧。";
	ob = unew("/clone/book/dagger-book");
	if(!clonep(ob))
		return "你来晚了，我的「匕法概论」已经给别人拿走了。";   
	if(clonep(ob) && ob->violate_unique()){
		destruct(ob);
		return "你来晚了，我的「匕法概论」已经给别人拿走了。";  
	}      
	ob->move(this_player());
		return "好吧，教主放在我这的「匕法概论」就送给你了。";
}

string ask_me()
{ 
	mapping fam; 
	object ob, *clone;
	int i, j;

	if(!(fam = this_player()->query("family")) || fam["family_name"] != "明教")
		return RANK_D->query_respect(this_player())+"与本派素无来往，不知此话从何谈起？";
	if(! this_player()->query_skill("jiuyang-shengong", 1))
	if(this_player()->query_skill("shenghuo-shengong", 1) < 100)
		return "你在明教的时日尚短，没有权利使用铁焰令。";
	if(!this_player()->query_skill("shenghuo-lingfa"))
		return "你又不使用令法，拿铁焰令干什么？";
	ob=present("tieyan ling",this_player());
	if(ob && ob->query_amount() >= 2)
		return "你身上都已经这么多了，还要令干什么？";
	ob=unew(BINGQI_D("tieyan-ling"));        
	if(!clonep(ob)) return "你来晚了，铁焰令已给全部发出去了。"; 
	i = ob->query("unique");
	clone = filter_array(children(base_name(ob)), (: clonep :));
	j = sizeof(clone);
	while (j--) if (!clone[j]->query("clone_by_wizard")) i--; 
	if(clonep(ob) && i < 0){
		destruct(ob);
		return "抱歉，你来晚了，铁焰令已给全部发出去了。";
	}
	ob->move(this_player());
	return "好吧，这块铁焰令你就拿去吧，望你不要借它为恶，多多发展我明教教众。";
}

int ask_xiaoyao() 
{
	object me = this_player();
	int i,j;
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$N向$n请教有关逍遥剑诀的真正奥妙。\n"NOR, me, this_object());
	
	command("look "+me->query("id"));	
	//普通玩家三次
	if(me->query("family/family_name")!="明教")
	{
		command("heng "+me->query_id());
		command("say 你和我门派有什么关系，赶紧给我滚！");
		return 1;
	}
	if(me->query("xyjf/jueji")=="pass")
	{
		command("heng "+me->query_id());
		command("say 你已经解开此谜题，来消遣我么？");
		return 1;
	}
	if(me->query("xyjfjj/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say 已经多次传授，你怎么都还没有领悟,真够笨的！");
		command("puke "+me->query("id"));
		return 1;
	}
	//武功学习之间需要间隔一天，经验需要间隔50K
	if( time()-me->query("xyjfjj/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say 今天先教到这里吧，明天吧。");
		return 1;
	}
	if(me->query_skill("xiaoyao-jian",1)<300)
	{
		command("look "+me->query("id"));
		command("say 以你当前的剑法还没有小飞，恐怕还是难以领悟，还是抓紧去练功去吧。");
		return 1;
	}    
	me->set("xyjfjj/time",time());
	me->set("xyjfjj/combat_exp",me->query("combat_exp")); 
	
	command("sigh "+me->query("id"));
	command("say 逍遥剑法乃我逍遥二仙的绝技。既然你想打听，我就说给你听听，看你有没有这个悟性了。");
   	command("say 讲究的是博杂而融会贯通，天下任何武功，达到一定境界后，信手拈来，不拘一格。");
	command("whisper "+me->query("id"));
	command("smile "+me->query("id"));

	j = 18;
    if(me->query("m-card-vip")) j =  16;
    if(me->query("y-card-vip")) j =  12;
    if(me->query("buyvip"))     j =  8;
	  
	i= random(j); 
	if(i<5 && random(me->query("kar"))>=25)
	{
		tell_object(me,HIW"\n你按照杨逍的指点，对逍遥剑的真正奥妙似乎有些心得。\n"NOR);
		tell_object(me,HIC"\n你把杨逍交给你的招式从开始演练，一路演练下来，潇洒自如。\n"NOR);       
		tell_object(me,HIG"\n你忽而长剑化作长枪大戟，论起来猛砸，忽而化作匕首猛刺。\n"NOR);
		tell_object(me,HIR"\n你忽而以令化作判官笔，点、戳、捺、挑。忽地又变成右手钢鞭。\n"NOR);   
	    tell_object(me,HIY"\n你忽而左手化作铁尺，百忙中尚自兵器互击，发出哑哑之声以扰乱敌人心神。\n"NOR);
		tell_object(me,HIB"\n瞬间已连变了二十二般兵刃，每般兵刃均是两套招式，一共四十四套招式。\n"NOR);
        tell_object(me,HIC"\n你已经学习并领悟了杨逍的逍遥剑的绝技。\n"NOR);
		
		command("look "+me->query("id"));
		command("chat "+me->query("id")+"已经获得了我的真传，还请江湖同仁以后多照顾下这位兄弟。");
		command("haha "+me->query("id"));
		command("chat* congra"+me->query("id"));
		me->set("xyjf/jueji","pass");
		//me->set("title",HIC"");
		log_file("quest/xiaoyaojian", sprintf("%8s(%8s) 失败%d次后，彻底领悟逍遥剑的绝技。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("xyjfjj/fail"),i,me->query("combat_exp")) );
	}
	else
	{
		me->add("xyjfjj/fail",1);
		command("sigh ");
		tell_object(me,HIY"你听了杨逍的指点，虽然看见了逍遥剑的招式和真意，可是对逍遥剑绝技的真正奥妙全然不得要领。\n\n"NOR);
		command("poor "+me->query("id"));
		command("disapp "+me->query("id"));
		log_file("quest/xiaoyaojian", sprintf("%8s(%8s) 逍遥剑绝技解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("xyjfjj/fail"),i,me->query("combat_exp")) );
	}
	return 1;
}