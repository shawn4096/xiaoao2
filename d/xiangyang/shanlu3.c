// /d/xiangyang/shanlu3.c
// Lklv Modify 2001.9.22
#include <ansi.h>

inherit ROOM;
int nanhai_eshen(object me,object mu);
int do_help(string arg);

void create()
{
	set("short", "山间小路");
	set("long", @LONG
你进入了一片小森林，走在林间小路上，密密麻麻的树林挡住了阳光，
这里显得十分阴暗，树木交错纵横，这里没有什么出路了.
LONG
	);
        set("outdoors", "襄阳");
        set("xyjob", 1);
	set("exits", ([
		"northeast" : __DIR__"shanlu2",
	]));

	set("objects",([
		__DIR__"npc/dingpopo" : 1,
		__DIR__"npc/pingpopo" : 1,
		__DIR__"npc/ruipopo" : 1,

	]));

	setup();
}

void init()
{
    object yuzhuo;
	object me=this_player();
	yuzhuo=present("yu zhuozi",me);
	if (me->query_temp("yyzhi/muzhuo")
		&& objectp(yuzhuo))
		//&& yuzhuo->query("give_player")==me->query("id") 
	{
		//message_vision("eee",me);
		call_out("help_mu",3+random(3),me);
		me->delete_temp("yyzhi/muzhuo");
	}
  
}
int help_mu(object me)
{
	object mu;
	
	if (!objectp(mu=present("mu wanqing",this_object())))
	{
		tell_object(me,YEL"\n\n\n\n\n\n忽然一阵马蹄声由远及近传来.....\n"NOR);
		tell_object(me,HIB"\n\n\n这是一匹黑色的马，正疾驰而来，马上一位蒙面姑娘正策马狂飙而来。\n"NOR);
		tell_object(me,HIC"\n\n\n只见这位小姑娘面色白皙如玉，面带黑纱巾，看不清眉目，但却感觉到\n"+
			"是一位少见的美女。她正是段王爷让你要寻找并保护的木婉清姑娘。\n"NOR);
		mu=new("d/dali/wuliang/npc/mu_wanqing");
		mu->move(this_object());
				
	}
	if (me && mu)
		call_out("nanhai_eshen",4+random(3),me,mu);
	
	return 1;

}
int nanhai_eshen(object me,object mu)
{
		object yue;
       if (!objectp(yue=present("nanhai eshen",this_object())))
       { 
		   tell_object(me,HIR"\n\n\n这时，忽然有一个粗豪的声音喊道，‘我南海鳄神岳老二来了！’\n\n"NOR);
		   yue=new("d/dali/wuliang/npc/eshen");
		   yue->move(this_object());
		   tell_object(me,HIC"他奶奶的，老子紧赶慢赶才赶上，我说那个小妞在哪儿？乖乖滴跟本大爷回去。\n"NOR);
       }
	   tell_object(me,HIC"四大恶人之三南海鳄神岳老三已经到达，须得保护好木婉清"HIR"（baohu 木婉清）"HIC"，否则王爷定不饶恕！。\n"NOR);
	   add_action("do_help","baohu");
	   yue->kill_ob(mu);
	   yue->kill_ob(me);
	   return 1;

}

int do_help(string arg)
{
	
	
	object ping,ding,rui,yue,me,mu;
	me=this_player();
	ping=present("ping popo",this_object());
	ding=present("ding popo",this_object());
	rui=present("rui popo",this_object());
	yue=present("nanhai eshen",this_object());	
	mu=present("mu wanqing",this_object());
   
	if (!arg)
		return notify_fail("你要保护谁？\n");
	
	if (!objectp(mu)){
		me->delete_temp("yyzhi");
		tell_object(me,HIW"木婉清已经死亡，任务失败！\n"NOR);
		return notify_fail("木姑娘都已经被杀了，你现在才出手？真是贪生怕死。\n");
	}
	if (!objectp(yue))
	{
		return notify_fail("多年的江湖经验使你觉得，再等会看看,以防受到高手偷袭。\n");
	}
	if (arg=="木婉清"||arg=="木姑娘")
	{
		message_vision(HIC"$N朗声笑道，木姑娘不要担心，我来帮你！\n"NOR,me,mu);
		if (objectp(ping))
			ping->kill_ob(me);	
		if (objectp(rui))
			rui->kill_ob(me);
		if (objectp(ding))
			ding->kill_ob(me);
		if (objectp(yue))
			yue->kill_ob(me);
    
		call_out("checking",1,me,mu);
		return 1;
	}
}

int checking(object me,object mu)
{
 	object ping,ding,rui,yue;
	ping=present("ping popo",this_object());
	ding=present("ding popo",this_object());
	rui=present("rui popo",this_object());
	yue=present("nanhai eshen",this_object());
   
   if (!mu&&!me->is_fighting()&&!me->query_temp("yyzhi/helpmuover"))
   {
	   tell_object(me,HIW"\n\n\n木婉清下落不明，保护木婉清任务失败！\n\n\n"NOR);
	   me->delete_temp("yyzhi");
	   return 1;
   }
   if (objectp(mu) && mu->query("qi")< (mu->query("max_qi")/3) &&!me->query_temp("yyzhi/helpmuover"))
   {
	   tell_object(me,HIW"\n\n\n木婉清受伤甚是严重，保护木婉清任务失败！\n\n\n"NOR);
	   me->delete_temp("yyzhi");
	   return 1;
   }
   if (!objectp(rui) && !objectp(ping) && !objectp(ding) && !objectp(yue)&&objectp(mu))
   {
      tell_object(me,HIY"\n\n\n经过大半个时辰的浴血奋战，你终于将所有敌人全部杀死！\n\n\n"NOR);
	  message_vision(HIC"\n\眼见强敌已经退走，$N走上前去检查木婉清的伤势。\n\n"NOR,me);

      tell_object(me,HIC"\n\你见木婉清伤势不是太重，就决定先带她回去面见段王爷！\n\n\n"NOR);
	  me->delete_temp("yyzhi/muzhuo");
	  me->set_temp("yyzhi/helpmuover",1);
	  me->set("quest/tls/yyz/start/helpmu",1);
	  if (mu) destruct(mu);
	
	  return 1;

   }    
   
	call_out("checking",3,me,mu);
	return 1;

}
