
//姬清虚，四代弟子
//jiqingxu.c
//sohu@xojh
//女性师傅
#include <ansi.h>

inherit NPC;
inherit F_MASTER;
string ask_rumen();

void create()
{
        set_name("姬清虚", ({"ji qingxu", "ji", "qingxu"}));
        set("gender", "女性");
        set("age", 24);
        set("class", "taoist");
        set("long",
                "她是一位身材苗条，容貌青秀的全真女修士，拜程瑶迦为师,她负责接待女性玩家拜师事物。\n");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 26);
        set("int", 25);
        set("con", 25);
        set("dex", 26);
		set("no_throw",1);
		set("no_steal",1);
        set("per", 26);

		set("qi", 3000);
        set("max_qi", 3000);
		//set("eff_qi",5000);
        set("jing", 2500);
        set("max_jing", 2500);
		//set("eff_jing",4000);
        set("jingli", 3000);
        set("max_jingli", 3000);
				set("eff_jingli",3000);

        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 50);

        set("combat_exp", 500000);

        set_skill("force", 220);
        set_skill("xiantian-gong", 220);
        set_skill("leg", 220);
        set_skill("yuanyang-lianhuantui",220);
        set_skill("dodge", 220);
        set_skill("jinyan-gong", 220);
        set_skill("parry", 220);
        set_skill("whip",220);
        set_skill("qiufeng-chenfa", 220);
        set_skill("literate",150);
        set_skill("taoism",100);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
		map_skill("whip", "qiufeng-chenfa");

        map_skill("parry", "qiufeng-chenfa");
        map_skill("leg", "yuanyang-lianhuantui");
        prepare_skill("leg", "yuanyang-lianhuantui");
		
		set("chat_chance_combat", 40);
		set("chat_msg_combat", ({
			(: exert_function, "daojue" :),
			(: exert_function, "yusuo" :),
			(: perform_action, "whip.sao" :),
			(: perform_action, "whip.chan" :),
			(: perform_action, "whip.lihua" :),
		}));

        create_family("全真教", 4, "弟子");

        set("inquiry", ([
                "全真教" :  "我全真教是天下道家玄门正宗,你若入我门来，不好好修炼，看我如何收拾你！\n",			      
                "入教" : (: ask_rumen :),
			   // "采药" : (: ask_caiyao :),
               //	"教中功绩" : (: ask_gongji :),
                 
        ]) );
		setup();

        carry_object("/clone/weapon/fuchen")->wield();
        carry_object("/d/quanzhen/npc/obj/grayrobe")->wear();



}

string ask_rumen()
{
	object me=this_player();

	if (!me->query("family/master_id"))
	{
		command("say 你尚未拜师，还是先去鹿清笃师兄处领取任务，尽快积攒功德，我方可收你为徒！\n");
		command("say 100k正神且积攒了500点贡献值就可以过来找我啦！\n");
		return "你要诚心正意方可拜入我大全真教";
	}
	command("say 你不是已经入了全真教了么？\n");
	return "别偷懒，先天功是天下第一等的内功！\n";
}

void attempt_apprentice(object ob)
{
       if (ob->query("gender")!="女性")
       {
		   command("say 你一个男人家来拜我为师，难道是有什么企图不成？！\n");
		   command("say 我全真一脉，最终全在内丹修为上，关于乾丹的修炼我不擅长！\n");
		   command("say 你还是去寻找下师伯赵志敬门下弟子鹿清笃师兄，看他是否收你？\n");
		   return ;

       }

	   if ((int)ob->query("shen") < 50000) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在德行方面，" + RANK_D->query_respect(ob) +
                       "是否还做得不够？(50k)");
               return;
       }
	   if (ob->query("party/gongji") < 500) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在教派功绩方面，" + RANK_D->query_respect(ob) +
                       "是否还做得不够？(需要500点门派贡献值)\n");
               return;
       }
	   if (!ob->query("party/rumen")) {
               command("say 你还没通过全真教鹿师兄的考研呢！赶紧干活去！\n");
               return;
       }
	
       command("say 好吧，贫道就收下你了。");
       command("recruit " + ob->query("id"));
       ob->set("class","taoism");
	   return;
}
