// NPC: /d/huashan/npc/feng.c
// Date: Look 99/03/25
// Modify by Lklv 2001.10.18
// By KinGSo 增加独孤九剑 无招无式 2010

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_wuzhao();
string ask_jiushi();
void create()
{
	set_name("风清扬", ( {"feng qingyang","feng","qingyang"} ) );
	set("long", "他看起来神色抑郁，面如金纸。\n" );
	create_family("华山派", 12, "弟子");

	set("age", 91);
	set("gender", "男性");
	set("attitude", "friendly");
	set("shen_type", 1);
	set("shen",150000);
	set("no_quest",1);

        set("con", 45);
        set("dex", 40);
        set("int", 50);
        set("str", 40);
	    set("per", 24);
        set("max_jing", 9000);
        set("max_neili", 45000);
        set("max_qi", 47500);
        set("eff_jingli", 9000);
        set("neili", 45000);
        set("jiali", 250);
        set("combat_exp", 15000000);

        set_skill("sword",550);
        set_skill("force",500);
        set_skill("dodge",500);
	    set_skill("poyu-quan", 500);
	    set_skill("cuff", 500);
        set_skill("parry",500);
        set_skill("dugu-jiujian",550);
        set_skill("huashan-shenfa",500);
        set_skill("huashan-jianfa",550);
        set_skill("huashan-qigong",500);
        set_skill("zhengqi-jue",200);
		set_skill("ziyin-yin",200);


        map_skill("force","huashan-qigong");
        map_skill("sword","dugu-jiujian");
        map_skill("dodge","huashan-shenfa");
	    map_skill("parry","dugu-jiujian");
	    map_skill("cuff", "poyu-quan");
	    prepare_skill("cuff", "poyu-quan");

	    set_temp("apply/damage", 40);
        set_temp("apply/dodge", 40);
        set_temp("apply/attack", 40);
        set_temp("apply/armor", 40);
		set("inquiry", ([
			"无招无式"	: (: ask_wuzhao :),
			//"独孤九式"	: (: ask_jiushi :),
			]));
		set("chat_chance_combat",160);
        set("chat_msg_combat", ({
		    (: perform_action, "sword.jiushi" :),
			(: perform_action, "sword.wuzhao" :),
			(: perform_action, "sword.zongjue" :),
			(: perform_action, "sword.poqi" :),
			(: perform_action, "sword.pozhao" :),
			(: exert_function, "yujianshi" :),
	    }));
		
		setup();

        carry_object(BINGQI_D("sword"))->wield();
        carry_object(ARMOR_D("cloth"))->wear();
}

void attempt_apprentice(object ob)
{
        if (!ob->query("fengset")) {
		command("say 你我恐怕今生无缘，这位" + RANK_D->query_respect(ob)+"还是请回吧。");
		command("wave " + ob->query("id"));
		return;
        }
        if (ob->query("shen") < 1000000 ) {
		command("say 我华山派乃是堂堂名门正派，对弟子要求极严。");
		command("say 在德行方面，" + RANK_D->query_respect(ob) + "是否还做得不够？");
		return;
        }
        if ((int)ob->query_skill("huashan-qigong",1) < 350)
			
        if ((int)ob->query_skill("zixia-gong",1) < 350){

			command("say 这位" + RANK_D->query_respect(ob)+
                        "，你的特殊内功等级过低，怕不能领悟我独孤九剑精髓。");
                return;
        }
        if ((int)ob->query_skill("huashan-shenfa",1) < 350){
                command("say 这位" + RANK_D->query_respect(ob) +
                        "，你的华山身法等级过低，怕不能领悟我独孤九剑精髓。");
                return;
        }
        if ((int)ob->query_skill("huashan-jianfa",1) < 350){
                command("say 这位" + RANK_D->query_respect(ob) +
                        "，你的华山剑法等级过低，怕不能领悟我独孤九剑精髓。");
                return;
        }
        command("say 好吧，我就收下你了,你可要为我们华山派争口气。");
        command("chat* 脸上浮现出一丝笑容，对着"+ob->query("name")+"笑道：我华山后继有人了。");
        command("chat* nomatch feng");
        command("recruit " + ob->query("id"));
        ob->set("title", HIW"独孤·九剑"NOR);
		ob->set("mytitle/quest/dgjjtitle",HIW"独孤·九剑"NOR);
        ob->set("quest/huashan","剑宗");
}

string ask_wuzhao()
{
    object me;
    mapping fam;
    me=this_player();
   if ( mapp(fam=me->query("family"))
    && (string)fam["family_name"] != "华山派"){
    command("? "+me->query("id"));
    return "这位" + RANK_D->query_respect(me) + "从哪里听说的独孤九剑啊？\n";
    }
  
   if (me->query("quest/huashan")=="气宗")
       return "以气驭剑？简直就是胡扯！\n";

   if ((int)me->query("combat_exp") < 12000000)
       return "你的实战经验还不足，无法理解独孤九剑的『无招无式』！\n";

   if(me->query("quest/hs/dgjj/wuzhao/pass"))
   {

	   return "你不是已经领悟了无招无式？来消遣老头子我？\n";
   }
   if(me->query("int") < 40 )
   {
		return"独孤九剑奥义需要极高的悟性，依我看" + RANK_D->query_respect(me) + "的先天悟性资质不足40，似乎无法理解？\n";
   }
   
   if(me->query("dex") < 35)
   {
	   
		return"独孤九剑奥义需要极高的灵动性，依我看" + RANK_D->query_respect(me) + "的先天身法资质不足35，似乎无法施展？\n";
		
	}

   if ((int)me->query_skill("force",1) < 500){
                return"这位" + RANK_D->query_respect(me)+"，你的内功等级过低，不足500，怕不能领悟我独孤九剑奥义。\n";
   }

   if ((int)me->query_skill("dugu-jiujian",1) < 500){
                return"这位" + RANK_D->query_respect(me)+"，你的独孤九剑等级过低(500)，怕不能领悟我独孤九剑奥义。\n";
                
   }
   if (me->query("family/master_id")!="feng qingyang"){
                return"这位" + RANK_D->query_respect(me)+"，我不认识，所为何来？\n";
                
   }
    if (time()-me->query("quest/hs/dgjj/wuzhao/time")<86400){
                return"这位" + RANK_D->query_respect(me)+"，你来的太勤快了耶？\n";
                
   }
  
	command("say 独孤九剑，有进无退，招招都是进攻，极尽招式之技巧变化，可谓达到变化之极致。\n");
	command("say 但招式是死的，人是活的，我这一生，一直在追求剑道之极境--以无招而胜有招。\n");
	command("say 独孤九剑所有变化以及总决式我已经传授于你，至于未来能否达到这个境界，就看你个人机遇了。\n");

	command("say 不过，这独孤九剑乃是传自一代剑魔独孤求败前辈。\n");
	command("say 当时独孤前辈号称独孤求败，以求一败而不得“长剑空利，群雄束手”，这是多么寂寞和无奈啊。\n");
	command("say 我也曾听江湖传言，独孤前辈曾留下一座孤坟，号称“剑冢”。\n");
	command("say 在剑冢之中曾留下绝世武技，也许你去哪儿看看能找到些许机缘。\n");
	command("say “四十岁后，不滞于物，万物皆可为剑，以此渐修，终至无剑胜有剑境界”.....\n");
	me->set_temp("wuzhao/askfeng",1);
	return "无招胜有招，乃是一代剑道宗师的终极境界！\n"; 

}



int prevent_learn(object ob, string skill)
{
	
	if (skill=="ziyin-yin"||skill=="zhengqi-jue")
	{
		write("这种功夫只能靠个人从书中参悟所得，你从师父这儿能学到什么?\n");
		return 1;
	}
	return 0;
}
//九式暂时关闭
/*
string ask_jiushi()
{
    object me;
    mapping fam;
    me=this_player();
   if ( mapp(fam=me->query("family"))
    && (string)fam["family_name"] != "华山派"){
    command("? "+me->query("id"));
    return "这位" + RANK_D->query_respect(me) + "从哪里听说的独孤九剑啊？\n";
    }
   
   if (me->query("quest/huashan")=="气宗")
       return "以气驭剑？简直就是胡扯！\n";

   if ((int)me->query("combat_exp") < 12000000)
       return "你的实战经验还不足，无法理解独孤九剑的『独孤九式』！\n";

   if(me->query("quest/hs/dgjj/jiushi/pass"))
   {

	   return "你不是已经领悟了『独孤九式』？来消遣老头子我？\n";
    //        return;
   }

   if(me->query("int") < 40 )
   {
		return"独孤九剑奥义需要极高的悟性，依我看" + RANK_D->query_respect(me) + "的先天悟性资质不足40，似乎无法理解？\n";
   }
   
   if(me->query("dex") < 35)
   {
	   
		return"独孤九剑奥义需要极高的灵动性，依我看" + RANK_D->query_respect(me) + "的先天身法资质不足35，似乎无法施展？\n";
		
	}

   if ((int)me->query_skill("force",1) < 500){
                return"这位" + RANK_D->query_respect(me)+"，你的内功等级过低，不足500，怕不能领悟我独孤九剑奥义。\n";
   }

   if ((int)me->query_skill("dugu-jiujian",1) < 500){
                return"这位" + RANK_D->query_respect(me)+"，你的独孤九剑等级过低(500)，怕不能领悟我独孤九剑奥义。\n";
                
   }
   if (me->query("family/master_id")=="feng qingyang"){
                return"这位" + RANK_D->query_respect(me)+"，我不认识，所为何来？\n";
                
   }
   if (timer()-me->query("quest/hs/dujj/jiushi/time")<86400){
                return"这位" + RANK_D->query_respect(me)+"，武功贪多不烂，你来的太勤快了耶？\n";
                
   }
	command("say 独孤九剑，有进无退，招招都是进攻，极尽招式之技巧变化，可谓达到变化之极致。\n");
	command("say 但招式是死的，人是活的，你先把这九式合一再去追求无招胜有招的境界。\n");
	command("say 独孤九剑所有变化以及总决式我已经传授于你，至于未来能否达到这个境界，就看你个人机遇了。\n");

	command("say 不过，这独孤九剑乃是传自一代剑魔独孤求败前辈。\n");
	command("say 当时独孤前辈号称独孤求败，以求一败而不得“长剑空利，群雄束手”，这是多么寂寞和无奈啊。\n");
	command("say 我也曾听江湖传言，独孤前辈曾留下一座孤坟，号称“剑冢”。\n");
	command("say 在剑冢之中曾留下绝世武技，也许你去哪儿看看能找到些许机缘。\n");
	command("say “四十岁后，不滞于物，万物皆可为剑，以此渐修，终至无剑胜有剑境界”.....\n");
	me->set_temp("wuzhao/askfeng",1);
	return 1;

}

*/




