// Room: /d/huashan/hole2.c
// Date: Look 99/03/25
#include <ansi.h>
inherit ROOM;
int do_han(string arg);
void create()
{

	set("short", "石洞");
	set("long",@long
这是一个华山绝顶石壁上的一个不起眼的石洞，华山派高老者和矮老者就
隐居在此。华山派弟子一般很少能够见到他们，如果能够见到，武功必然得到
他们的大力指点。
long);
	set("exits",([
	"out" : __DIR__"song",
]));
	set("objects",([
	__DIR__"npc/gao" : 1,
	__DIR__"npc/ai" : 1,
]));
	setup();
}

void init()
{
    if (this_player()->query_temp("jianzong/bijian")|| this_player()->query("quest/huashan")=="剑宗")
    { 
		add_action("do_han","han");
		add_action("do_han","yell");
    }
   

}

int do_han(string arg)
{
    int i;
	object feng,cong,cheng;
	string ms;
	object me=this_player();
	i=me->query("kar");
	if (!arg||arg!="剑宗前辈")
      return notify_fail("荒山野岭的，你不怕喊来母狼？\n");
  
    ms=me->query("family/master_id");
	//write(ms);
	
    if (me->query("quest/huashan")=="剑宗")
	{	
		switch (ms)
		{
			case "cheng buyou":
				 if (!present("cheng buyou",environment(me)))
				 {
					cheng=new("/d/huashan/npc/sword/chengbuyu.c");
					cheng->move("/d/huashan/hole2");
					message_vision(HIC"成不忧轻轻咳嗽一声，闪身而出。\n"NOR,me);
					return 1;
				  }
			break;
			case "feng buping":
		          if (!present("feng buping",environment(me)))
				  {
					feng=new("/d/huashan/npc/sword/fengbuping.c");
					feng->move("/d/huashan/hole2");
					message_vision(HIC"封不平轻轻咳嗽一声，闪身而出。\n"NOR,me);
					return 1;
				  }
			break;
			
		}

		//return notify_fail("？\n");
	}
	if (!me->query_temp("jianzong/bijian"))
		  return notify_fail("再喊真的狼来了！\n");
	if (time()-me->query("hs/jianzong/time")<86400)
		  return notify_fail("你来的太勤快了？\n");
	if (i>30)
	{
		log_file("quest/bugzuobi",sprintf("%s(%s)在解密华山剑宗分支过程中作弊嫌疑。富源：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),me->query("kar"),me->query("hs/wushuang/fail"),me->query("combat_exp"),me));
		return 1;
	}
	if (me->query_temp("jianzong/bijian")&& i>26 || me->query("quest/huashan")=="剑宗")
	{
		  message_vision(HIC"谁家弟子在此大声喧哗？\n随着一声轻喝，三道人影忽然间出现在$N的面前。\n"NOR,me);
		  
		  if (!present("feng buping",environment(me)))
          {
			feng=new("/d/huashan/npc/sword/fengbuping.c");
			feng->move("/d/huashan/hole2");
			
          }else feng=present("feng buping",environment(me));
		  if (!present("chong buqi",environment(me)))
          {
			cong=new("/d/huashan/npc/sword/chongbuqi.c");
			cong->move("/d/huashan/hole2");
			cong->set_temp("jiali",60);
         }else cong=present("chong buqi",environment(me));
         
		 if (!present("cheng buyou",environment(me)))
         {
			cheng=new("/d/huashan/npc/sword/chengbuyu.c");
			cheng->move("/d/huashan/hole2");
         }else cheng=present("cheng buyu",environment(me));
        
			message_vision(HIW"$N成功寻找到华山剑宗的下落并可以拜师。\n", me);
			tell_object(me, BYEL"恭喜你，你成功解开华山剑宗谜题,并获得基本剑法加成奖励。\n"NOR);
			log_file("quest/jianzong",sprintf("%s(%s)成功找到剑宗分支，并开始准备修习剑宗绝技。富源：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),i,me->query("hs/jianzong/fail"),me->query("combat_exp"),me));
			me->add_skill("sword",10+random(10));
			me->set("quest/huashan","剑宗");
			me->set("title","华山派剑宗亲传弟子");
			me->delete_temp("jianzong/bijian");
			return 1;
			
    } else {
			message_vision(HIY"$N喊了半天，空谷传音回荡，人迹皆无。\n"NOR,me);
			message_vision(HIC"解密剑宗分支失败。\n"NOR,me);
			log_file("quest/jianzong",sprintf("%s(%s)解密剑宗分支失败。富源：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),i,me->query("hs/jianzong/fail"),me->query("combat_exp"),me));
			me->add("hs/jianzong/fail",1);
            me->set("hs/jianzong/time",time());
			me->delete_temp("jianzong/bijian");
            return 1;
		}


}
