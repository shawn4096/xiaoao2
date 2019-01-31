// sun.c 孙不二

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_chongyang();
string ask_baojian();

void create()
{
        set_name("孙不二", ({"sun buer", "sun"}));
        set("gender", "女性");
        set("age", 33);
        set("class", "taoist");
        set("nickname",CYN"清净散人"NOR);
        set("long",
                "她就是全真教二代弟子中唯一的女弟子孙不二孙真人。她本是\n"
                "马钰入道前的妻子，道袍上绣着一个骷髅头。\n");
        set("attitude", "peaceful");
        set("shen_type",1);
        set("str", 30);
        set("int", 29);
        set("con", 29);
        set("dex", 29);
		//set("");
        set("title","全真七子之末");

        set("qi", 23700);
        set("max_qi", 23700);
        set("jing", 4800);
        set("max_jing", 4800);
        set("neili", 14100);
        set("max_neili", 14100);
        set("jiali", 200);

        set("combat_exp", 9600000);

        set_skill("force", 450);
        set_skill("xiantian-gong", 450);
        set_skill("sword", 450);
        set_skill("quanzhen-jianfa",450);
        set_skill("dodge", 450);
        set_skill("jinyan-gong", 450);
        set_skill("parry", 450);
        set_skill("strike", 450);
        set_skill("haotian-zhang", 450);
        set_skill("literate",200);
        set_skill("taoism",200);
	    set_skill("tiangang-beidouzhen", 450);
		set_skill("whip",450);
		set_skill("qiufeng-chenfa",350);
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
                "王重阳" :  (:ask_chongyang():),
				"七星宝剑" :  (:ask_baojian():),
        ]) );
		set("chat_chance_combat", 50);
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
       if (ob->query("gender")!="女性")
       {
		   command("say 你一个男人家来拜我为师，难道是有什么企图不成？！\n");
		   command("say 我全真一脉，最终全在内丹修为上，关于乾丹的修炼我不擅长！\n");
		   command("say 你还是去寻找全真其余六子，看他们是否收你？\n");
		   return ;

       }

	   if ((int)ob->query("shen") < 2000000) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在德行方面，" + RANK_D->query_respect(ob) +
                       "是否还做得不够？(2m)");
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
	   if (ob->query_skill("xiantian-gong",1) < 350) {
               command("say 我全真教一身功夫全在先天功，你先天功不足350，来此作甚？。");
               return;
       }
	 
       command("say 好吧，贫道就收下你了。");
       command("recruit " + ob->query("id"));
       ob->set("title", "全真七子亲传弟子");
       ob->set("class","taoism");
	   return;
}
string ask_chongyang()
{
	object me;
	me=this_player();
	if (me->query("family/family_name")!="全真教")
	{
		command("say 你与我派无缘无故，为何有此一问？\n");
		return "哼！\n";
	}
	if (me->query("family/generation")>3)
	{
		command("say 你非三代弟子，拿了去给人送宝物么？\n");
		return "哼！\n";
	}
	if (!me->query("quest/qz/dichuan"))
	{
		command("say 你非我派嫡传，为何有此一问？\n");
		return "哼！\n";
	}
	if (me->query("party/gongji")<100)
	{
		command("say 你的门派贡献值不足100，无功焉能受禄？\n");
		return "哼！\n";
	}
	command("say 每次借用宝物都将扣除你的100点门派贡献值！\n");
	command("say 重阳真人是五绝之首，人送称号为“中神通”\n");
	command("say 他是我们七子的师傅，师傅对我们恩重如山\n");
	command("say 因我是七子中唯一的女性，为了让我自保，特意将七星宝剑留我防身！\n");
	me->set_temp("qixing/asksun",1);
	return "七星宝剑是我全真教至高无上宝物！\n";
}

string ask_baojian()
{
	object me,ob;
	object room;
	me=this_player();
	room=load_object("/d/quanzhen/qingjing");

	if (me->query("family/family_name")!="全真教")
	{
		command("say 你与我派无缘无故，为何有此一问？\n");
		return "哼！\n";
	}
	if (file_name(environment(this_object()))!="/d/quanzhen/qingjing")
	{
		command("say 此地无银三百两，这哪儿啊？\n");
		return "哼！\n";
	}
	if (!me->query_temp("qixing/asksun"))
	{
		command("say 身在全真当懂得感恩，你知道门派祖师是谁么？\n");
		return "哼！\n";
	}
	if (me->query_temp("qixing/gived"))
	{
		command("say 我方才不是给你了么？\n");
		return "哼！\n";
	}

/*	if ((int)room->query("qixing")<1)
	{
		command("say 我刚把这把宝剑送给门中弟子了，你待会来再来!\n");
		return "最近我全真教越来越兴旺了!\n";
	}*/

	ob=unew("/clone/weapon/sword/qixing-jian");
	if (!objectp(ob)) 
	{
		command("say 七星宝剑不在我手里，我已经送人了！\n");
		return "七星宝剑是师傅送给我的宝物！\n";
	}
	ob->move(me);
//	environment(this_object())->add("qixing",-1);

	command("say 好，既然你是我全真核心弟子，那我就把这把宝剑暂借给你用！\n");
	message_vision(HIC"$n抽出一把寒光四射的宝剑递给$N!\n"NOR,me,this_object());
	me->set_temp("qixing/gived",1);
	me->delete_temp("qixing/asksun");
	return "";
}