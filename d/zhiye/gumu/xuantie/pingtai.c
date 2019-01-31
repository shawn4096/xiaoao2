// pingtai.c
// By River 98/08/28

inherit ROOM;
#include <ansi.h>
void create()
{
    set("short", HIC"平台"NOR);
    set("long", @LONG
你置身平台上面，四周树木苍翠，山气清佳。环顾左右，只见许多石块堆
著一个大坟。这坟背向山谷，俯仰空阔，单是这座剑冢便已占尽形势。仔细一
看大石上「剑冢」两个大字之旁，尚有两行字体较小的石刻（zi）。 
LONG
        );

    set("item_desc", ([
       "zi": HIY"「剑魔独孤求败既无敌於天下，乃埋剑於斯。」\n" +
                "\n「呜呼！群雄束手，长剑空利，不亦悲夫！」\n"NOR,
    ]));

    set("outdoors", "襄阳");

    setup();
}

void init()
{
        add_action("do_move", "move");
        add_action("do_move", "yi");
		add_action("do_yanlian", "yanlian");
        add_action("do_tiao", ({"tiao", "zong"}));
}

int do_move(string arg)
{
        object me;
        me = this_player();
        if (!arg) return 0;
        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着哪！\n");
        if ( arg == "stone" || arg == "shikuai"){
        if ( me->query("max_neili") < 1500 && me->query_str() < 30 )
          return notify_fail("你费劲地想移动石块，但它纹丝不动。\n");
        if ( me->query_temp("weapon"))
          return notify_fail("你拿着兵刃怎么移动石块？\n");
           message_vision(YEL"$N深深地吸了口气，缓缓推动石块。\n\n"NOR,me);
           write(HIG"只见石块慢慢地移动，你把石块移开了！露出了剑冢的入口。\n"NOR);
           set("exits/enter", __DIR__"jianzhong");
           me->receive_damage("neili", 200);
	   me->receive_damage("jingli", 200); 
           remove_call_out("close");
           call_out("close", 5, this_object());
           return 1;
           }
          return notify_fail("你要移动什么？\n");
}

void close(object room)
{
        message("vision",HIY"石块慢慢移回了原位，又挡住了入口。\n"NOR, room);
        room->delete("exits/enter");
}

int do_tiao(string arg)
{ 
        object me;
        me = this_player();
        if ( !arg || arg != "down")
         return notify_fail ("你往哪里跳？");
        if ( arg == "down")
         message_vision(HIG"$N身形陡转，点击突石借力，纵下峭壁。\n"NOR,me);
         me->move(__DIR__"qiaobi");
         me->receive_damage("qi", 200);
		 me->receive_damage("jingli", 200);
         tell_room(environment(me),HIG + me->name() + "身形陡转，点击突石借力，从平台上跳了下来。\n"NOR, ({ me }));
         return 1;
} 

int do_yanlian(string arg)
{
	object me;
	me=this_player();
	if (me->is_busy()) return notify_fail("你正忙碌中....\n");
	if (me->query_temp("wuzhao/yanlian")) return notify_fail("你正在演练中....\n");

	if (!arg||arg!="无招胜有招") return notify_fail("领悟什么？\n");
	
	if (me->query("quest/hs/dgjj/wuzhao/pass")||me->query("quest/xtj/wuzhao/pass"))
	{
		QUEST_D->setmytitle(me,"wuzhaotitle",HBWHT+HIC"独孤九剑·无招胜有招"NOR);
		return notify_fail("你已经领悟了这无招胜有招的绝技，还来此比划作甚？\n");
	}
    
	if (!me->query_temp("wuzhao/askfeng")&&!me->query_temp("wuzhao/askyang")) return notify_fail("在这荒山野岭的，你瞎比划作甚？\n");
	
	//if (!me->query_temp("wuzhao/tigangjian")) return notify_fail("你没观摩过剑坟中的钢剑境界！\n");
	//if (!me->query_temp("wuzhao/tizhongjian")) return notify_fail("你没观摩过剑坟中的重剑境界！\n");
	if (!me->query_temp("wuzhao/timujian")) return notify_fail("你没观摩过剑坟中的木剑境界！\n");

	
	if (time()-me->query("quest/hs/dgjj/wuzhao/time")<86400||time()-me->query("quest/xtj/wuzhao/time")<86400)
	{
		return notify_fail("你来的太勤快了。\n");
	}
	
	if (me->query_temp("wuzhao/askfeng")&& me->query_temp("wuzhao/timujian"))
	{
		me->start_busy(99);
		me->set_temp("wuzhao/yanlian",1);
		//remove_call_out("jj_think");
		call_out("jj_think",1,me);
		return 1;
	}
	if (me->query_temp("wuzhao/askyang"))
	{
		me->start_busy(99);
		remove_call_out("xtj_think");
		call_out("xtj_think",2,me);
		return 1;
	}
	return notify_fail("领悟什么?\n");

}
int jj_think(object me)
{
  int i,j,total;
  if(!me) return 0;
	
  if(me->query_temp("wuzhao_dgjj")<(10+random(3)))
    { 
	  me->add_temp("wuzhao_dgjj",1);
	  switch (random(6))
	  {
		case 0:
			tell_object(me,HIG"\n.「凌厉刚猛，无坚不摧，弱冠前以之与河朔群雄争锋。」。。.\n\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n\n「剑魔独孤求败既无敌於天下，乃埋剑於斯。」。\n"NOR);
			break;
		case 2:
			tell_object(me,HIG"\n\n「重剑无锋，大巧不工。四十岁前恃之横行天下。」\n"NOR);
			break;
		case 3:
			tell_object(me,RED"\n\n「四十岁後，不滞於物，草木竹石均可为剑。自此精修，渐进於无剑胜有剑之境。」。\n"NOR);
			me->add_temp("wuzhao/wujian",1);
			break;
		case 4:
			tell_object(me,HIC"\n\n「紫薇软剑，三十岁前所用，误伤义不祥，乃弃之深谷。」\n"NOR);
			break;
		case 5:
			tell_object(me,HIY"\n\n突然间，灵光乍现，你瞬间领悟到了什么...\n"NOR);
			break;
	  }
 	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  
	  call_out("jj_think",3+random(3), me);

  } else
   {  
	  me->delete_temp("wuzhao_dgjj");
      total = me->query("int")+me->query("str")+me->query("dex")+me->query("con");
      j = 25;
      if(me->query("m-card-vip")) j =  23;
      if(me->query("y-card-vip")) j =  20;
      if(me->query("buyvip"))     j =  15;
      i=random(j-me->query_temp("wuzhao/wujian"));
     
	 if (me->query("kar")<31
		 && i < 2 
		 && random(me->query("kar"))>28
		 && random(total) >= 130) 		 
     {       
          tell_object(me,HIM"你按照剑冢所留提示，在实战中一一体验，结合自己多年的实战经验，颇有心得！\n"NOR);
          message_vision(HIG"$N陡然间忽然明白了这无招胜有招的剑道极境的意境。”\n"NOR,me); 
          tell_object(me,HIR"你这时体味到了以无招胜有招的道理诀窍，对于无招胜有招的认识大大不同！\n"NOR);
		  tell_object(me,HIW"你将方才的所得暗暗思索，顿觉脑中对无招胜有招的理解进入了一个前所未有的新境\n"NOR);
		  
		
		  tell_object(me,HBRED+HIW"恭喜"+me->query("name")+HBRED+HIW"经过千辛万苦，终于修成无招胜有招。\n");
          
		  me->set("quest/hs/dgjj/wuzhao/pass", 1);
		  QUEST_D->setmytitle(me,"wuzhaotitle",HBWHT+HIC"独孤九剑·无招胜有招"NOR);
          //me->set("title",HBWHT+HIC"剑道宗师"NOR);
          log_file("quest/dgjjwuzhao", sprintf("%s(%s) 失败%d次后，成功解开无招胜有招的奥秘。富源：%d；经验：%d。\n",   
          me->name(1),
          me->query("id"), 
          me->query("quest/hs/dgjj/wuzhao/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
          me->start_busy(1);
		  me->delete_temp("wuzhao");
		  return 1;
      }
        else
        {
         tell_object(me,HIG"\n你沉思许久，不得要领。\n"NOR);
         message_vision(HIC"\n$N摇了摇头，深深地叹了口气。\n"NOR,me); 
		 message_vision(HIY"$N抓耳挠腮，苦思冥想，发现自己还是无法理解这无招胜有招奥意所在，脸上一筹莫展。\n"NOR,me);
         tell_object(me,HBBLU"\n很可惜，你本次尝试无招胜有招绝技秘密失败！\n"NOR);
         tell_object(me,HBBLU"你目前的经验是" + me->query("combat_exp") + "，现在时间是书剑"+ NATURE_D->game_time() + "，请记录。\n"NOR);
         tell_object(me,HBBLU"你将在间隔24小时后获得下一次机会！。\n\n"NOR);
		 log_file("quest/dgjjwuzhao", sprintf("%s(%s) 解密独孤九剑无招胜有招绝技失败%d次。富源：%d；经验：%d。\n",   
          me->name(1),
          me->query("id"), 
          me->query("quest/hs/dgjj/wuzhao/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
          me->add("quest/hs/dgjj/wuzhao/fail",1);
          me->set("quest/hs/dgjj/wuzhao/exp", me->query("combat_exp") );
          me->start_busy(1);
          me->set("quest/hs/dgjj/wuzhao/time",time());
		  me->delete_temp("wuzhao");
		  return 1;
        }
     
	 return 1;
   }
}
/*
int xtj_think(object me)
{
  int i,j,total;
  if(!me) return 0;
	
  if(me->query_temp("wuzhao_xtj")<(10+random(3)))
    { 
	  me->add_temp("wuzhao_xtj",1);
	  switch (random(6))
	  {
		case 0:
			tell_object(me,HIG"\n.「凌厉刚猛，无坚不摧，弱冠前以之与河朔群雄争锋。」。。.\n\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n\n「剑魔独孤求败既无敌於天下，乃埋剑於斯。」。\n"NOR);
			break;
		case 2:
			tell_object(me,HIG"\n\n「重剑无锋，大巧不工。四十岁前恃之横行天下。」\n"NOR);
			break;
		case 3:
			tell_object(me,RED"\n\n「四十岁後，不滞於物，草木竹石均可为剑。自此精修，渐进於无剑胜有剑之境。」。\n"NOR);
			me->add_temp("wuzhao/wujian",1);
			break;
		case 4:
			tell_object(me,HIC"\n\n「紫薇软剑，三十岁前所用，误伤义不祥，乃弃之深谷。」\n"NOR);
			break;
		case 5:
			tell_object(me,HIY"\n\n突然间，灵光乍现，你瞬间领悟到了什么...\n"NOR);
			break;
	  }
 	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  call_out("xtj_think",3+random(3), me);

  } else
   {  
	  me->delete_temp("wuzhao_xtj");
      total = me->query("int")+me->query("str")+me->query("dex")+me->query("con");
      j = 25;
      if(me->query("m-card-vip")) j =  23;
      if(me->query("y-card-vip")) j =  20;
      if(me->query("buyvip"))     j =  15;
      i=random(j-me->query_temp("wuzhao/wujian"));
     
	 if (me->query("kar")<31
		 && i < 2 
		 && random(me->query("kar"))>=27
		 && random(total) >= 130) 		 
     {       
          tell_object(me,HIM"$N按照剑冢所留提示，在实战中一一体验，结合自己多年的实战经验，颇有心得！\n"NOR);
          message_vision(HIG"$N陡然间你忽然明白了这无招胜有招的剑道极境的意境。”\n"NOR,me); 
          tell_object(me,HIR"$N这时体味到了以无招胜有招的道理诀窍，对于无招胜有招的认识大大不同！\n"NOR);
		  tell_object(me,HIW"$N将方才的所得暗暗思索，顿觉脑中对无招胜有招的理解进入了一个前所未有的新境\n"NOR);
		  
		
		  tell_object(me,HBRED+HIW"恭喜"+me->query("name")+HBRED+HIW"经过千辛万苦，终于修成无招胜有招。\n");
          
		  me->set("quest/xtj/wujian/pass", 1);
          //me->set("title",HBWHT+HIC"剑道宗师"NOR);
          log_file("quest/dgjjwuzhao", sprintf("%s(%s) 失败%d次后，成功解开无招胜有招的奥秘。富源：%d；经验：%d。\n",   
          me->name(1),
          me->query("id"), 
          me->query("quest/hs/dgjj/wuzhao/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
          me->start_busy(1);
      }
        else
        {
         tell_object(me,HIG"\n你沉思许久，不得要领。\n"NOR);
         message_vision(HIC"\n$N摇了摇头，深深地叹了口气。\n"NOR,me); 
		 message_vision(HIY"$N抓耳挠腮，苦思冥想，发现自己还是无法理解这无招胜有招奥意所在，脸上一筹莫展。\n"NOR,me);
         tell_object(me,HBBLU"\n很可惜，你本次尝试无招胜有招绝技秘密失败！\n"NOR);
         tell_object(me,HBBLU"你目前的经验是" + me->query("combat_exp") + "，现在时间是书剑"+ NATURE_D->game_time() + "，请记录。\n"NOR);
         tell_object(me,HBBLU"你将在间隔24小时后获得下一次机会！。\n\n"NOR);
		 log_file("quest/dgjjwuzhao", sprintf("%s(%s) 解密独孤九剑无招胜有招绝技失败%d次。富源：%d；经验：%d。\n",   
          me->name(1),
          me->query("id"), 
          me->query("quest/hs/dgjj/wuzhao/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
         me->add("quest/hs/dgjj/wuzhao/fail",1);
         me->set("quest/hs/dgjj/wuzhao/exp", me->query("combat_exp") );
         me->start_busy(1);
         me->set("quest/hs/dgjj/wuzhao/time",time());
		 
        }
     
	 me->delete_temp("wuzhao");
	 return 1;
   }
}

*/