// kumu.c 枯木
// Created by sohu@xojh

inherit NPC;
#include <ansi.h>
string ask_duan();

void create()
{
   set_name("枯木大师",({"kumu dashi","kumu","dashi"}));
   set("gender","男性");
   set("long","净慈寺主持，枯木大师，长得此慈眉善目，甚是安详!\n");
   set("shen",80000);
   set("combat_exp",4500000);
   //set("nickname","灵隐寺主持");
   set("title","净慈寺主持");
   
   set("age",30);
   set("pur",12);
   set("kar",20);
   set("per",25);
   set("str",30);
	 set("int",25);
	 set("con",20);
	 set("dex",30);
	 set("max_qi", 13000);
	 set("max_jing", 5000);
	 set("eff_jingli", 5000);
	 set("neili", 15000);
	 set("max_neili", 15000);
	 set("jiali", 100);

   set_skill("dodge",400);
   set_skill("force",400);
   set_skill("parry",400);
   set_skill("sword",400);
   set_skill("cuff",400);
   //set_skill("stealing",380);
   set_skill("luohan-quan",400);
   set_skill("literate",200);
   set_skill("shaolin-shenfa",350);
   map_skill("dodge","shaolin-shenfa");
   map_skill("cuff","luohan-quan");
	prepare_skill("cuff","luohan-quan");
   setup();
       set("inquiry", ([
                //"全真教" :  "我全真教是天下道家玄门正宗,你若入我门来，不好好修炼，看我如何收拾你！\n",			      
                "段天德" : (: ask_duan :),
			  //  "李萍" : (: ask_liping :),
               //	"教中功绩" : (: ask_gongji :),
                 
        ]) );
   add_money("silver",70);
	carry_object("d/jiaxing/obj/cloth")->wear();
	carry_object("d/menggu/npc/obj/zheshan");
}


string ask_duan()
{
	object me,kumu;
	me=this_player();
	if (!me->query_temp("quest/射雕英雄传/江南七怪/findkumu"))
	{
		command("say 阿弥陀佛，善哉善哉！\n");

		return "何必如此大动肝火，善哉善哉？\n";
	}
	if (me->query_temp("quest/射雕英雄传/江南七怪/askkumu"))
	{
		command("say 阿弥陀佛，善哉善哉！\n");

		return "我不是跟你说过了么，真是聒噪？\n";
	}
	message_vision(HIG"\n$N方才是隐约听到有女声，但并不确定，而枯木道长一味的抵赖不认，也是怒火万丈!\n"NOR,me);
	message_vision(HIW"\n但找寻半天也没发现任何可疑之处！\n"NOR,me);
	message_vision(HIG"\n这时忽听隐约寺外传来女生愤怒的声音！“滚开”！\n"NOR,me);
	message_vision(HIY"\n你急忙追了出去，见远处一辆马车向嘉兴方向疾驰而去！随即展开轻功追寻而去！\n"NOR,me);
	
	me->set_temp("quest/射雕英雄传/江南七怪/askkumu",1);
	return "\n这人真是蛮不讲理！\n";
}
