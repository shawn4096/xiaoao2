// suxingh.c
// shilling 97.2
#include <ansi.h>

inherit NPC;
//inherit F_MASTER;
int ask_zhenlong();

void create()
{
	set_name("苏星河",({"su xinghe","su"}));
	set("gender", "男性" );
	set("nickname", "聪辩老人");
	set("shen_type", 0);
	set("class", "scholar");
	set("age",60);
	set("str", 35);
	set("con", 30);
	set("int", 45);
	set("dex", 35);
	set("per", 30);

	set("no_clean_up",1);

	set("long",
"此人就是号称聪辩老人的苏星河，据说他能言善辩， \n"
"是一个武林中的智者，而他的武功也是无人能知。\n");

	set("combat_exp", 100000000);
	set("attitude", "peaceful");
	set("chat_chance", 1);

	set("max_qi", 18000);
	set("max_jing", 18000);
	set("neili", 25000);
	set("max_neili",18000);
	set("jiali", 200);

	set_skill("force", 580);
	set_skill("dodge", 580);
	set_skill("parry", 580);
	set_skill("blade", 580);
  set_skill("qingyun-shou", 550);
	set_skill("beiming-shengong", 580);
	set_skill("ruyi-dao", 580);
	set_skill("liuyang-zhang", 580);
	set_skill("zhemei-shou", 580);
	set_skill("literate", 500);
	set_skill("piaomiao-shenfa", 580);
	set_skill("hand", 580);
	set_skill("strike", 580);
	set_skill("art", 220);
	set_skill("medicine", 220);

	map_skill("strike", "liuyang-zhang");
	map_skill("parry", "ruyi-dao");
	map_skill("blade", "ruyi-dao");
	map_skill("dodge", "piaomiao-shenfa");
	map_skill("force", "beiming-shengong");
	map_skill("hand", "zhemei-shou");
	prepare_skill("hand","zhemei-shou");
	prepare_skill("strike","liuyang-zhang");	
	set("chat_chance_combat", 90);  
	set("chat_msg_combat", ({
                (: perform_action, "blade.wanshi" :),
                (: perform_action, "blade.ruyi" :),
           
	}) );

	create_family("逍遥派", 2, "弟子");
	set("title","逍遥派第二代大弟子");
	set("inquiry", ([
                "无涯子" :  "当年师弟背叛师门，害得先师饮恨谢世，将我打得无法还手。在下本当一死殉师，但想起师父有个心愿未了，倘若不觅人破解，死后也难见师父之面，是以忍辱偷生，苟活至今。这些年来，在下遵守师弟之约，不言不语，不但自己做了聋哑老人，连门下新收的弟子，也都强着他们做了聋子哑子。唉，三十年来，一无所成，这个棋局，仍是无人能够破解。。\n",                
                "珍珑棋局": (: ask_zhenlong :),

        ]));
	
	
	
	
	setup();
	carry_object(__DIR__"obj/cloth")->wear();
	carry_object(__DIR__"obj/blade")->wield();
}


void attempt_apprentice(object ob)
{
	
	if (!QUEST_D->queryquest(ob,"xiaoyao/zhenlong")) 
	{
		command("say 拜入我逍遥，需要先解开珍珑棋局。"); 
		return;
	}
	
	if ((int)ob->query_skill("beiming-shengong", 1) < 100) {
		command("say 我逍遥派内功的源泉来自于北冥神功的心法。"); 
		command("say " + RANK_D->query_respect(ob) + 
			"的北冥神功是否还应该有所提高啊？");
		return;
	}
	
if ((string)ob->query("gender")=="男性")
   {
		message_vision("苏星河垂目沉思片刻, 说道：“好吧, 我就收下你了。”\n",ob);
       command("recruit " + ob->query("id"));
       ob->set("title", "逍遥派第三代弟子");
       return;}
   else
      {
		message_vision("我逍遥派从不收女流之辈?”\n",ob);
       return;}
 }
 
 
 int ask_zhenlong()
{
	object me=this_player();
//第一步要求，男性，容貌上佳	

if (QUEST_D->queryquest(me,"xiaoyao/zhenlong"))
{
	 command("say 原来是破解珍珑棋局之人来了！");
	  return 1;
}

  if(QUEST_D->queryquesttime(me,"xiaoyao/zhenlong"))		
   	{
	  command("say 你还是去休息一下吧，解珍珑棋局不急！");
	  return 1;
	}

	if (me->query("gender")=="男性")
	{
		if( me->query("combat_exp")<20000000)
	     {
	        command("say 你功力太浅了，先练功去吧。");
	        return 1;
	     }
		 
		if (me->query("per") < 28) 
		{
			command("sigh ");
			command("say 你容貌欠佳，怕是不行，这中间大有干系，大有干系。。。");
			return 1;
		}
		if (me->query_temp("xiaoyao/zhenlong/step1"))
		{
			command("say 你已经问过了。");
			return 1;
		}
	   me->set_temp("xiaoyao/zhenlong/step1",1);//得到珍珑第一步的标记
      command("say 这个‘珍珑’，牵涉异常重大，你过来好好的瞧上一瞧，倘能破解得开，那是一件大大的妙事。");
	  return 1;
	}
	else
		return 0;	
}

