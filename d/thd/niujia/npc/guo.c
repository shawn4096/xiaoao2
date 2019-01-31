//ytx.c

inherit NPC;
#include <ansi.h>
int ask_jiuyuan();
#define QUESTDIR "quest/射雕英雄传/"
#define QUESTDIR1 "quest/射雕英雄传/风雪惊变/"

void greeting(object me);
string ask_hejiu();

void create()
{
	set_name("郭啸天", ({ "guo xiaotian", "guo", "xiaotian" }) );
	set("gender", "男性" );
	//set("title", "");
	set("nickname", "郭靖之父");
	set("age", 28);
	set("long",
"他身材魁梧，浓眉大眼。\n"
"他是梁山泊好汉地佑星赛仁贵郭盛的后代。\n");
	set("str", 25);
	set("dex", 25);
	set("con", 25);
	set("int", 25);
	set("per", 25);
	set("shen_type", 1);
  set("no_get", 1);
  set("no_bark", 1);
	set_skill("force", 300);
	set_skill("dodge", 300);
	set_skill("parry", 300);
	set_skill("cuff",300); 
	set_skill("jinyan-gong",300);
	set_skill("taizu-quan",300);
	set_skill("xiantian-gong",300);
	map_skill("force","xiantian-gong");
	map_skill("cuff","taizu-quan");
	map_skill("dodge","jinyan-gong");
    prepare_skill("cuff", "taizu-quan");
    
	set("combat_exp", 4000000);
	set("max_qi", 20000);
	set("max_jing", 5000);
	set("max_neili", 15000);
	set("eff_jingli",4000);
	set("qi",20000);
	set("jing",5000);
	set("jingli",4000);
	set("neili", 15000);

  set("inquiry", ([
    "救援": (: ask_jiuyuan :),
	 "喝酒": (: ask_hejiu :),

		"杨铁心": "他是我义弟。",
    "李萍" : "她是我浑家。",
    "郭靖" : "这是一个道人给我未出世的儿女取的名字。",
    "杨康" : "这是我义弟杨铁心的骨肉。",
    "包惜弱" : "她是我弟媳。",

	]));
	set("chat_chance", 10);
        set("chat_msg", ({
		"村里不怎么的出现大批金兵，这到底是发生了什么事情、、、\n",
		"内子和弟媳快要生了，这节骨眼上怎么会发生这种事情呢、、、\n",
        }) );
     setup();
	carry_object("/clone/armor/cloth.c")->wear();
	carry_object(ARMOR_D("shoes"))->wear();
} 
string ask_hejiu()
{
	object me=this_player();
	if (me->query("shen")<0)
	{
		command("say 你一身邪气，居然敢来找我喝酒，活的不耐烦了么？\n");
		return "哼！\n";
	}
	if (me->query("combat_exp")<2000000)
	{
		command("say 你经验值不足2m,来此找我喝酒，难道不觉得自己很弱小么？\n");
		return "哼！\n";
	}
	if (!me->query_temp(QUESTDIR1+"start"))
	{
		command("say 酒无好酒，无缘无故请我喝酒难道是有预谋？\n");
		return "哼！\n";
	}
	command("say "+me->query("name")+"，既然杨老弟托你来找我喝酒，那你就先去哪儿，我和杨老弟一会到！\n");
	me->set_temp(QUESTDIR1+"askguo",1);
	return "天寒地冻，喝点酒可以暖和暖和！\n";

}

int ask_jiuyuan()
{
	object me = this_player();
	if(!me->query(QUESTDIR1+"killsongbing"))
    {
	   command("sigh "+me->query("id"));
	   command("say 这位"+RANK_D->query_respect(this_player())+"，现在天下太平，要不咱们再喝一顿？？\n");
	   return 1;
    } 

	if(me->query_temp(QUESTDIR1+"jiuyuan"))
    {
	   command("beg1 "+me->query("id"));
	   command("say 这位"+RANK_D->query_respect(this_player())+"，快去救我义弟啊，要不他顶不住了？");
	   return 1;
    } 
	if(me->query(QUESTDIR1+"over"))
    {
	  command("beg1 "+me->query("id"));
	  command("say 多谢这位"+RANK_D->query_respect(this_player())+"出手救我义弟呀？");		
	  return 1;
    } 
    if( me->query("combat_exp") < 2000000 )
    {
	  command("disapp "+me->query("id"));
	  command("say 以你当前的经验恐怕还不能帮忙救援我义弟，还是抓紧去练功去吧。\n");
      return 1;
    }  	
    if(me->query(QUESTDIR+"time") && time()-me->query(QUESTDIR+"time")<86400)
	{
	  command("shake "+me->query("id"));
	  command("say 今天先帮到这里吧，明天吧。");
	  return 1;
    }
    if(!me->query(QUESTDIR1+"over"))
    {
	   me->set_temp(QUESTDIR1+"jiuyuan", 1);
	   me->set(QUESTDIR+"time",time());
	   me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
	   command("cry "+me->query("id"));
	   command("say 昨日我和义弟救援一位被金兵追杀的道士，没想到今日却来有金兵来抓我们，\n"+
				   "这位大侠请赶快去我义弟家解救我义弟杨铁心吧，我准备下武器随后就到。");
	   return 1;
    }
}

