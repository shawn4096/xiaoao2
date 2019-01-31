// zhong.c 嵩山派第三代弟子 钟镇
// Lklv 2001.10.18 Modified

#include <ansi.h>
inherit NPC;
string ask_jueji();

void create()
{
        set_name("钟镇", ({ "zhong zhen", "zhong", "zhen" }));
        set("nickname", HIC"九曲剑"NOR);
        set("long", "这是一名瘦削的老者，一手嵩山剑法在江湖上赫赫有名。\n");
        set("gender", "男性");
        set("age", 45);
        set("per", 20);
        set("attitude", "heroism");
	set("class", "songshan");
        set("shen_type", -1);
        set("str", 26);
        set("int", 26);
        set("con", 26);
        set("dex", 27);
        set("unique", 1);

        set("max_qi", 23000);
        set("max_jing", 6000);
        set("eff_jingli", 6000);
        set("jiali", 200);
        set("combat_exp", 6500000);
        set("eff_neili", 5000);
        set("shen", -1500000);
		set_skill("songyang-jue", 150);

		set_skill("literate", 200);
		set_skill("force", 400);
		set_skill("parry", 450);
		set_skill("sword", 450);
		set_skill("dodge", 400);
		set_skill("hand", 400);
		set_skill("zhongyuefeng", 400);
		set_skill("songyang-shou", 400);
		set_skill("hanbing-zhenqi", 400);
		set_skill("songshan-jian", 450);

		map_skill("force", "hanbing-zhenqi");
		map_skill("dodge", "zhongyuefeng");
		map_skill("hand", "songyang-shou");
		map_skill("parry", "songshan-jian");
		map_skill("sword", "songshan-jian");
		prepare_skill("hand", "songyang-shou");

		create_family("嵩山派", 3, "弟子");
		
		set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: perform_action, "sword.feiwu" :),
			(: perform_action, "sword.jiuqu" :),
			(: perform_action, "sword.leiting" :),
			//(: perform_action, "sword.longfeng" :),
			(: perform_action, "hand.junji" :),
			(: exert_function, "hanbing" :),
		}));
			setup();
		set("inquiry", ([
			//"嵩山派" : "我们嵩山派是五岳剑派之首！\n",
			//"五岳剑派" : "我们五岳剑派在武林之中势力巨大，可与少林、武当抗衡。\n",
			//"左冷禅" : "他就是我们的掌门人，功夫深不可测。\n",
		//	"九曲剑绝技": (: ask_jueji() :),
		]) );
			carry_object(ARMOR_D("changpao1"))->wear();
			carry_object(BINGQI_D("changjian"))->wield();
}

#include "app3.h";



string ask_jueji()
{
	object me;
	int i,j;

	me=this_player();
	if (me->query_skill("sword",1)<300)
	{
		command("say 你的基本剑法不足200，告诉你也学不会！\n");
		return "九曲变化剑中极致！\n";
	}
	if (me->is_busy()) return "你很忙啊！\n";
	
	if (me->query_skill("songshan-jian",1)<300)
	{
		command("say 你的嵩山剑法不足300，告诉你也学不会！\n");
		return "九曲变化剑中极致！\n";
	}
	if (time()-me->query("quest/ss/ssj/jiuqu/time")<86400) 
		return "你来的太勤快了，这对武功修炼是不利的！\n";
	
		command("say 嵩山剑法九曲剑绝技乃是我独创，你想学我就告诉你？\n");
		command("say 好小子，既然你想学，你听好了！\n");
		  j = 20;
		  if(me->query("m-card-vip")) j =  18;
		  if(me->query("y-card-vip")) j =  15;
		  if(me->query("buyvip"))     j =  10;
		  i=random(j);

		  if (i<4 
			 && me->query("kar")<31
			 && random(me->query("kar"))>26)
		  {       
			  tell_object(me,HIC"\n你按照钟镇的指点将浑身真气注入手臂中，手顿时重了许多！\n"NOR);
			  message_vision(HIR"\n$N对如何使用这个九曲剑的技巧一下子豁然贯通。”\n"NOR,me); 
			  tell_object(me,HIG"恭喜您解密九曲剑绝技成功！\n"NOR);
			  me->set("quest/ss/ssj/jiuqu/pass",1);
			  log_file("quest/ssjiuqu", sprintf("%s(%s) 失败%d次成功解开九曲剑。富源：%d；经验：%d。\n",   
			  me->name(1),
			  me->query("id"), 
			  me->query("quest/ss/ssj/jiuqu/fail"),
			  me->query("kar"),
			  me->query("combat_exp")) );
			  me->start_busy(1);
			}
			else
			{
			 tell_object(me,HIG"\n你沉思许久，不得要领。\n"NOR);
			 message_vision(HIC"\n$N摇了摇头，深深地叹了口气,觉得自己真实笨死了。\n"NOR,me); 
			 tell_object(me,HBBLU"\n很可惜，你本次尝试九曲剑绝技秘密失败！\n"NOR);
			 tell_object(me,HBBLU"你目前的经验是" + me->query("combat_exp") + "，现在时间是书剑"+ NATURE_D->game_time() + "，请记录。\n"NOR);
			 tell_object(me,HBBLU"你将在间隔24小时后获得下一次机会！。\n\n"NOR);
			 log_file("quest/ssjiuqu", sprintf("%s(%s) 解密九曲剑绝技失败%d次。富源：%d；经验：%d。\n",   
			 me->name(1),
			 me->query("id"), 
			 me->query("quest/ss/ssj/jiuqu/fail"),
			 me->query("kar"),
			 me->query("combat_exp")) );
			 me->add("quest/ss/ssj/jiuqu/fail",1);
			 me->set("quest/ss/ssj/jiuqu/exp", me->query("combat_exp") );
			 me->start_busy(1);
			 me->set("quest/ss/ssj/jiuqu/time",time());
			}
		me->add_busy(2);
		return "九曲连环剑是嵩山剑绝技！\n";
	 
		
}