//yangtiexin.c

inherit NPC;
#include <ansi.h>
int ask_yangjiaqiang();

#define QUESTDIR "quest/射雕英雄传/"

#define QUESTDIR1 "quest/射雕英雄传/风雪惊变/"
#define QUESTDIR6 "quest/射雕英雄传/yangjiaqiang/"

void greeting(object me);
string ask_hejiu();
string ask_baohu();
string ask_qubiaoji();

void create()
{
	set_name("杨铁心", ({ "yang tiexin", "yang", "tiexin" }) );
	set("gender", "男性" );
	set("nickname",HIY"杨家枪传人"NOR);
	set("age", 27);
	set("long",
"一个白净面皮的汉子。\n"
"他是岳飞麾下名将杨再兴的后代。\n");
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
	set_skill("spear", 350);
	set_skill("cuff",300); 
	set_skill("jinyan-gong",300);
	set_skill("taizu-quan",300);
	set_skill("xiantian-gong",300);
	set_skill("yangjia-qiang",350);
	map_skill("force","xiantian-gong");
	map_skill("cuff","taizu-quan");
	map_skill("dodge","jinyan-gong");
	map_skill("spear","yangjia-qiang");
	map_skill("parry","yangjia-qiang");
    prepare_skill("cuff", "taizu-quan");
	set("combat_exp", 4500000);
	set("max_qi", 20000);
	set("max_jing", 4000);
	set("max_neili", 15000);
	set("eff_jingli",4000);
	set("qi",30000);
	set("jing",4000);
	set("jingli",4000);
	set("neili", 15000);
   set("chat_chance_combat", 60);
    set("chat_msg_combat", ({
     //  (: exert_function, "wuqi" :),
       (: perform_action, "spear.tiaoji" :),
       (: perform_action, "spear.shanji" :),
	   (: perform_action, "spear.shenwei" :),
       (: perform_action, "spear.qinghe" :),
       (: perform_action, "spear.lihua" :),
       (: perform_action, "spear.jifeng" :),
       (: perform_action, "spear.huima" :),
  //     (: perform_action, "spear.shanji" :),

     }));

  set("inquiry", ([
   // "杨家枪": (: ask_yangjiaqiang :),
	 "喝酒": (: ask_hejiu :),
	// "保护成功": (: ask_baohu :),
	 //"去掉老标记": (: ask_qubiaoji :),

    "郭啸天" : "他是我义兄。",
    "包惜弱" : "她是我浑家。",
    "杨康" : "这是一个道人给我未出世的儿女取的名字。",
    "郭靖" : "这是我义兄郭啸天的骨肉。",
    "李萍" : "她是我嫂子",
	]));
	setup();
	carry_object("/clone/weapon/spear.c")->wield();
	carry_object("/clone/weapon/spear.c");
	carry_object("/clone/armor/cloth.c")->wear();
	
} 

void init()
{
  object me;
	::init();
  if (interactive(me = this_player())
	 && me->query(QUESTDIR+"tongyin")
	 && me->query(QUESTDIR+"start") 
	 && me->query(QUESTDIR1+"成功保护杨铁心")
	 && me->query_temp(QUESTDIR1+"fightjinbing")
	 && !me->query(QUESTDIR1+"over")) 
  {
  	   me->start_busy(1);
	   me->delete_temp(QUESTDIR1+"fightjinbing");
       call_out("greeting", 2, me);
  }       
}
string ask_qubiaoji()
{
	write(HIC"红尘滚滚，你决定对射雕英雄传故事从头再来！\n"NOR);
		this_player()->delete("quest/射雕英雄传");
		this_player()->delete_temp("quest/射雕英雄传");
	return "";
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

	if (me->query("quest/射雕英雄传/风雪惊变/yestongyin"))
	{
		command("say 我们不是一起痛饮么，还要再喝？\n");
		return "呼噜~~~~~~~~！\n";
	}

	command("say "+me->query("name")+"，既然你有如此好意，那就去找郭大哥，咱们一起去小酒馆喝酒！\n");
	me->set_temp(QUESTDIR1+"start",1);
	
	me->set(QUESTDIR1+"start",1);
	me->set(QUESTDIR+"start",1);
	//me->delete("quest/射雕英雄传");

	return "天寒地冻，喝点酒可以暖和暖和！\n";
}


void greeting(object me)
{
	int i,p;
	object ob;
	ob=this_object();
	
    if(!me) return;

	if(me->query_condition("killer"))
	{
		command("fear "+me->query("id"));
		command("say 小心官府通缉！");
		me->move(__DIR__"njroad3");
		return;
	}

  if(me->query(QUESTDIR+"start") 
	  && me->query(QUESTDIR1+"成功保护杨铁心")
	  && !me->query(QUESTDIR1+"over"))
  {
	me->start_busy(3);
  	tell_object(me,HIG"\n你突然发现后院栅栏处站着一个人，正是杨铁心，他弯腰鞠躬对你说道：“感谢这位大侠出手援助。”\n"NOR);
  	tell_object(me,HIG"\n杨铁心说道：“这场飞来横祸，始料不及，但我的妻子和郭大嫂下落不明。我将外出寻找。”\n"NOR);
  	tell_object(me,HIG"\n杨铁心说道：“这此地也非久留之地，大侠请自便。”\n"NOR);
		


		message_vision(HBYEL+HIW"恭喜你，于"+NATURE_D->game_time()+"完成《射雕英雄传》之第一章节《风雪惊变》正线的故事情节!\n"NOR,me);
		message_vision(HBYEL+HIW"经过不懈努力和浴血奋战，你成功帮助杨铁心脱险，杨铁心对你颇有好感!\n"NOR,me);
		message_vision(HBYEL+HIW"但令人遗憾的是包惜弱和李萍为敌人所掳走!尚待你去营救。\n"NOR,me);


  //	tell_object(me,HIC"你踌躇了一下，杨铁心说道："+me->query("name")+"，为感谢您救我一家，我可将闻名遐迩的杨家枪教授于你，你可以随时找我请教？\n"NOR);
  	me->delete_temp(QUESTDIR1);

	p=5+random(5);  	
	me->set(QUESTDIR1+"over",1);

    me->add("max_neili",p);		
	//me->add("combat_exp",(int)me->query_skill("force")+500);
    me->set("quest/射雕英雄传/time",time());
	me->set("quest/射雕英雄传/combat_exp",me->query("combat_exp"));
    i=180+random(40);
   	me->add("mana",i);
	
  	tell_object(me,HBYEL"\n你于"+NATURE_D->game_time()+"解开射雕英雄传风雪惊变篇，获得"+p+"点最大内力、"+((int)me->query_skill("force")+500)+"点经验奖励、"+i+"点声望。\n\n"NOR); 
    log_file("quest/SheDiao", sprintf("%s(%s) 风雪惊变完成。奖励：%d点最大内力，%d点经验，%d点声望。\n", me->name(1),me->query("id"), p,(me->query_skill("force")+500),i ) );

    return;
  }  	

}

//杨家枪解密函数

int ask_yangjiaqiang() 
{
	object me = this_player();
	object ob = this_object();
    
	if (ob->query("asked"))
	{
		command("say 不要着急，现在"+ob->query("asked")+"正在解这个谜题。\n");
		return 1;
	}
	if(me->query(QUESTDIR6+"pass"))
	{
	  command("disapp "+me->query("id"));
	  command("say 你不学已经学会杨家枪了吗。");
	  return 1;
	} 
    if(me->query(QUESTDIR6+"pass"))
	{
	  command("disapp "+me->query("id"));
	  command("say 你不学已经学会杨家枪了吗。");
	  return 1;
	} 
	 if(me->query(QUESTDIR6+"pass"))
	 {
	  command("disapp "+me->query("id"));
	  command("say 你不学已经学会杨家枪了吗。");
	  return 1;
	} 
 //武功学习之间需要间隔一天，经验需要间隔500K
	if(me->query(QUESTDIR6+"time") && time()-me->query(QUESTDIR6+"time")<86400)
	{
	  command("shake "+me->query("id"));
	  command("say 今天先切磋到这里吧，明天吧。");
	  return 1;
	}
	if(me->query(QUESTDIR6+"combat_exp") && me->query("combat_exp")-me->query(QUESTDIR6+"combat_exp")<100000 &&  !me->query("cw_exp") )
	{
	  command("look "+me->query("id"));
	  command("say 以你当前的经验恐怕还是难以领悟，还是抓紧去练功去吧。");
	  return 1;
	}
  
	if(me->query(QUESTDIR+"over") > 0)
    {
	  command("pat "+me->query("id"));
      message_vision(HIC"\n$n微笑着对$N说道：「可要看仔细了!」,伸手拿起墙上的铁枪舞动起来\n"NOR,me,ob); 
      me->set(QUESTDIR6+"time",time());
      me->set(QUESTDIR6+"combat_exp",me->query("combat_exp"));
      
	  ob->set("asked",me->query("name"));

	  remove_call_out("thinking");
	  call_out("thinking",5, me, ob);
      tell_object(me,YEL"你拼命地回忆杨铁心舞动的铁枪招式，你开始认真思索着.........\n"NOR);
      me->start_busy(2);
	  return 1;
	  }
	  else
	  {  
	  command("? "+me->query("id"));
         command("say 你问这个做什么?");
    return 1;
  }
}

int thinking(object me, object ob)
{
	int p;
	
	if(!me) return 0;
	
  if(me->query_temp("yjq_thinking")<(3+random(3)))
	{
		me->add_temp("yjq_thinking",1);
    if(random(2)) tell_object(me,HIG"\n你努力地回忆刚才杨铁心铁枪的招式,只觉得眼花缭乱...\n"NOR);
    else tell_object(me,HIY"\n突然间，你似乎抓到了什么，你努力地回忆刚才杨铁心铁枪的招式，你似乎感觉到了其中的变化所在...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，一服愁眉不展的样子。\n"NOR, ({}));
	  remove_call_out("thinking");
		call_out("thinking",3+random(3), me, ob);
	}
	else
	{
    me->delete_temp("yjq_thinking");

    p=random(15);

    if(p == 3 &&  random(me->query("kar"))>28  && me->query("pur")>25  && me->query("kar")<31 )
 {
       tell_object(me,HIG"\n你此时生怕将刚才的精妙招式忘了，当即跟着杨铁心的招式比划着。\n"NOR);
       message_vision(HIC"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
       tell_object(me,HIR"你听了杨铁心的指点,终于领悟了杨家枪的精华所在。\n"NOR);
       me->set(QUESTDIR6+"pass",1);
       me->set_skill("yangjia-qiang",11);
	   this_object()->delete("asked");
       message_vision(HIC"\n你的「杨家枪」进步了！”\n"NOR,me); 
	  log_file("quest/SheDiao", sprintf("%s(%s) 失败%d次成功解开杨家枪。富源：%d；经验：%d。\n", me->name(1),me->query("id"), me->query(QUESTDIR6+"fail"),me->query("kar"),me->query("combat_exp")) );
    }
    else
    {
       tell_object(me,HIG"\n你脑海里似乎抓住了什么，可是依然不是很明白。\n"NOR);
       message_vision(HIC"\n$N摇了摇头，道：“好像还是很困难的。”说罢，深深地叹了口气。\n"NOR,me); 
       command("poor "+me->query("id"));
	   this_object()->delete("asked");
       me->add(QUESTDIR6+"fail",1);
	  log_file("quest/SheDiao", sprintf("%s(%s) 解杨家枪：%d次。富源：%d；经验：%d。\n", me->name(1),me->query("id"), me->query(QUESTDIR6+"fail"),me->query("kar"),me->query("combat_exp")) );
    }
  }
  return 1;
}
