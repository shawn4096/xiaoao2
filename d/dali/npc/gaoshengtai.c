// NPC :gaoshengtai.c 高升泰
// Modify By River 98/12

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string huanggong();

void create()
{
        object ob;
        set_name("高升泰", ({ "gao shengtai", "gao","shengtai" }));
        set("title", "大理国善阐侯府侯爷");
        set("gender", "男性");
        set("age", 40);
        set("str", 28);
        set("dex", 20);
        set("long", "这是一个宽袍大袖的中年男子，三绺长须，形貌高雅，
双手持着一枝铁笛,此人便是人称为“高君侯”的高升泰。\n");
        set("max_qi", 2000);
        set("max_jing", 1000);
        set("neili", 2000);
        set("max_neili", 2000);
        set("eff_jingli",1000);
        set("jiali",30);
        set("combat_exp", 500000);
        set("shen_type", 1);
        set("attitude", "peaceful");

        set("quest/tls/ailao/pass",1);

        set_skill("force",380);
        set_skill("sword",380);
        set_skill("cuff",380);
        set_skill("duanjia-quan",380);
        set_skill("buddhism",120);
		set_skill("literate",120);
        set_skill("dodge",380);
        set_skill("tianlong-xiang",390);
        set_skill("parry",380);
        set_skill("qiantian-yiyang",430);
        set_skill("duanjia-jianfa",430);
        map_skill("parry", "duanjia-jianfa");
        map_skill("dodge", "tianlong-xiang");
        map_skill("cuff","duanjia-quan");
        map_skill("force", "qiantian-yiyang");
        map_skill("sword", "duanjia-jianfa");
        
		prepare_skill("cuff","duanjia-quan");
        set("chat_chance_combat", 40);
	    set("chat_msg_combat",({
			(: perform_action, "sword.fenglei" :),
			(: exert_function, "liao" :),
			(: exert_function, "jingxin" :),
	    }));
		create_family("天龙寺", 14 , "俗家弟子");
        set("inquiry", ([
			"入皇宫" : (: huanggong :),
        ]));

        set_temp("apply/attack", 70);
       
        set_temp("apply/defense", 70);
        set_temp("apply/armor", 70);
        set_temp("apply/damage", 20);

        setup();
	    if (clonep(this_object()))
	    if (ob = carry_object(BINGQI_D("sword/tiedi"))) ob->wield();
	    carry_object(ARMOR_D("cloth"))->wear();
}

void attempt_apprentice(object ob)
{
	object me  = this_object();
	mapping fam = ob->query("family");
	if (ob->query("gender") == "女性"){
		command ("say 这位小姑娘，本王府不收女徒，你还是请回吧。");
		return;
	}
	if (ob->query("tls") && fam["family_name"]=="天龙寺" ){
		command ("say 你已经是天龙寺出家弟子了，我不能再收你了！");
		return;
	}
	if(ob->query("int") < 25){
		command("say 学我大理段家武功悟性奇高，依我看" + RANK_D->query_respect(ob) + "的悟性不足25，资质似乎不宜修习？");
		return;
	}
	if ((int)ob->query("shen") < 100000){
		command ("say  我大理段氏乃堂堂正派，依我看" + RANK_D->query_respect(ob) +"正神不足100k，不适合入我大理段氏。");
		return;
	}
	if ( fam && fam["master_name"] == "段正淳"){
		command("shake");
		command("say "+RANK_D->query_respect(ob)+"已拜镇南王为师，"+RANK_D->query_self(me)+"怎敢再收你为徒？");
		return;
	}
	if( fam && fam["master_name"] == "段正明"){
		command("haha");
		command("say "+RANK_D->query_respect(ob)+"已是皇上身前的侍卫，"+RANK_D->query_self(me)+"怎敢再收你为徒？");
		return;
	}
    if( ob->query_skill("qiantian-yiyang",1)<250){
		command("sigh ");
		command("say "+RANK_D->query_respect(ob)+"你的乾天一阳功不足250，怎敢再收你为徒？你去三大司空处拜师去吧！\n");
		return;
	}
    if( (int)me->query("family/generation")<14){
		command("sigh ");
		command("say "+RANK_D->query_respect(ob)+"你已经有前辈名师教导，怎敢再收你为徒？");
		return;
	}
	command("smile");
	command("say 很好，" + RANK_D->query_respect(ob) + "只要肯为我大理多做事，他日必定能有所成就。");
	command("recruit " + ob->query("id") );
	ob->set("title","大理国镇南王府管家");
	return;
}

void recruit_apprentice(object ob)
{
      if( ::recruit_apprentice(ob) )
      ob->set("class", "officer");
}

string huanggong()
{
        object ob=this_player();
	if (!ob->query_temp("dali_join"))
		return RANK_D->query_respect(ob) + "，你不是本王府随从，此话从何说起？";
	if (ob->query("job_time/大理") + ob->query("job_time/送信") < 200)
		return "我看你为镇南王府做事做的还不够啊，努力做吧！";
	ob->set_temp("huanggong",1);
	return RANK_D->query_respect(ob)+"只要说是镇南王府的，就可以入宫了。";
}

