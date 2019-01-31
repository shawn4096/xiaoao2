// add wd quest 剑诀 by Lane@SJ 2005.7.11
// Room: lwhole.c
// Update By lsxk@hsbbs 增加通宝道具提高解迷成功率 2007/7/18

#include <ansi.h>;

inherit ROOM;

string wall(object me);

void create()
{
	set("short", HIB"石壁岩洞"NOR);
	set("long", @LONG
这是一天然石洞，不是很深，当太阳升起时能直射全洞。象是有人在此住
过，正面有一石床，左边放有一些石碗，右面的石壁(wall)上似乎刻有小字，
你可以尝试研读一下。
LONG
	);

	set("exits", ([
		"out" : __DIR__"wanniansong",
	]));    

	set("item_desc", ([
          "wall" : HIW "彼之力方碍我之皮毛，我之意已入彼骨里。双手支撑，一气贯通。太极者，道也；两仪者，阴阳也。\n"
						+"阴阳一道也，太极无极也。气发则为窍，而气发至本原处，则为生死窍，化无极之真，二五之精，\n"
						+"生生而化，妙合而凝，真气游走全身，生死窍亦随之转移。乃参大衍之数五十，其用四十有九，虚\n"
						+"其一，变化始生之道也。以形气转续为己息，以静穆无穷为内义，阴阳相依，纠缠相转，气淡而神凝，\n"
						+"沉而不浮，敛而不露，凝而不滞，收四海于囊中，含八荒于意下，是以太极真气得以源源不息，浩浩\n"
						+"乎若涌泉之凝聚，渺渺乎若烟湖之深溟，柔而纳万物，浑而吞天下，生死窍圆环游走，清静而微，其来\n"
						+"不可逢，其往不可追，迅即自身体境清明，脱胎换骨而力抵天下。.....左重则左虚，而右已去，右重\n"
						+"则右虚，而左已去......\n"NOR,
             ]));
    set("no_fight", 1);
	setup();
}

void init()
{
	add_action("do_study", "yandu");
}

int do_study(string arg)
{
	object me;
	me = this_player();

	if( !living(me) ) return 0;

	if( (int)me->query_skill("literate", 1) < 10 )
		return notify_fail("你字也不认识几个,如何研读无上心法。\n");
	if (!me->query_temp("tjsg/askzhang"))
		return notify_fail("你和张真人非亲非故，来此瞎逛，无所事事。\n");
	
	if( me->is_busy() || me->is_fighting() )
		return notify_fail("你正忙着呢。\n");
    if (me->query("quest/wd/yyzq/taiji/pass"))
		return notify_fail("你已经解开来太极神功，无需来此研读。\n");   
	if (time()-me->query("quest/wd/yyzq/taiji/time")<86400)
		return notify_fail("你来的太勤快了，对精力损耗太大。\n");   
	
	if( arg == "wall" ) {
		if( me->query_temp("tjsg/askzhang") ) 
		{
			message_vision("$N慢慢的琢磨着石壁上的小字。\n", me);
			
			tell_object(me, HIW"老道年已过百，想我武当能人不多，虽有善心，终不得其用。晚年闭关新创两门绝技\n"+
			"「"RED"太极拳"HIW"」和「"RED"太极剑"HIW"」，\n "+"日后精修，功力日深，恍悟以柔克刚的内功心法,故名"+HIM+"”太极神功“。\n"+
			HIW"望能够留传后世，造福万民，来此昔日故地，留字以待，了却心愿....\n"+
			
			HIY"\t\t冲虚自然，以慢打快，以静制动，後发制人。\n"+
			HIG"\t\t无极而生，阴阳之母。阴阳相济，方为懂劲。\n"+
			RED"\t\t纯以意行，形神合一，圆转贯串，滔滔不绝。\n"+
			HIC"\t\t气之所至，意之所动，内外双修，无我无招。\n"+

			WHT"\t\t\t张三丰\n"NOR);
			write(HIY"你心中大喜，知道这是掌门祖师亲自篆刻秘籍心法。当下静心研习石壁上的文字，大有感触\n对「太极」的领会又更深入了一个层次。\n"NOR);
			me->start_busy(999);
			call_out("yyzq_taiji",1,me);
		
			return 1;
		}
	}
	return notify_fail("这儿荒山野洞，你要读什么？\n");
}

int yyzq_taiji(object me)
{
  int i,j,total;
  if(!me) return 0;
	
  if(me->query_temp("yyzq_taiji")<(10+random(3)))
    { 
	  me->add_temp("yyzq_taiji",1);
	  switch (random(6))
	  {
		case 0:
			tell_object(me,HIG"\n......彼之力方碍我之皮毛，我之意已入彼骨里。双手支撑，一气贯通。\n"+
			"左重则左虚，而右已去，右重则右虚，而左已去......\n\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"冲虚自然，以慢打快，以静制动，後发制人。\n"NOR);
			break;
		case 2:
			tell_object(me,HIG"无极而生，阴阳之母。阴阳相济，方为懂劲。\n"NOR);
		case 3:
			tell_object(me,RED"纯以意行，形神合一，圆转贯串，滔滔不绝。\n"NOR);
		case 4:
			tell_object(me,HIC"气之所至，意之所动，内外双修，无我无招。\n"NOR);
		case 5:
			tell_object(me,HIY"\n突然间，你似乎领悟到了什么...\n"NOR);
	  }
 	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  call_out("yyzq_taiji",3+random(3), me);
  } else
   {  
	  me->delete_temp("yyzq_taiji");
      total = me->query("int")+me->query("str")+me->query("dex")+me->query("con");
      j = 20;
      if(me->query("m-card-vip")) j =  18;
      if(me->query("y-card-vip")) j =  15;
      if(me->query("buyvip"))     j =  10;
      i=random(j);
     
	 if (me->query("kar")<31
		 && i < 2 
		 && random(me->query("kar"))>=27
		 && random(total) >= 120) 		 
     {       
          tell_object(me,HIM"$N按照张三丰的指点，和墙上的文字一一对应，结合自己多年的实战经验，颇有心得！\n"NOR);
          message_vision(HIG"$N陡然间你忽然明白了氤氲紫气运转如意，如长江大河，滔滔不绝的太极意境。”\n"NOR,me); 
          tell_object(me,HIR"$N又忽然懂得了太极剑的以慢打快，后发制人的诀窍，对于太极剑的认识大大不同！\n"NOR);
		  tell_object(me,HIY"$N终于懂得了太极拳终极绝技奥秘，不禁连声大笑，原来如此，原来如此！\n"NOR);
		  tell_object(me,HIW"$N将方才的所得暗暗思索，顿觉脑中对太极的理解进入了一个前所未有的新境\n"NOR);
		  
		  message_vision("\n\n$N忽然感觉‘尾闾穴’酸痛，一股真气起自气海，形成一个小循环后，顺着关元穴直至海底！"
							+"略作停留后，如氤氲状态，环形螺旋上升，直达命门穴。然后势如破竹，上天门，过十二重楼\n"+
							"过膻中，然后一鼓作气，重新到达气海，又成螺旋状缓缓沉入。自此流转不绝，生生不息！"+
							"这任督二脉终于为你打通！至此，氤氲紫气进入一个前所未有的境界！太极神功至此大成！\n\n"NOR,me);
		  tell_object(me,HBRED+HIW"恭喜"+me->query("name")+HBRED+HIW"经过千辛万苦，终于修成武当太极神功。\n");
          
		  me->set("quest/wd/yyzq/taiji/pass", 1);
          me->set("title",HBMAG+HIW"太极宗师"NOR);
		  me->set("mytitle/quest/taijititle",HBMAG+HIW"太极宗师"NOR);
          log_file("quest/yyzqtaiji", sprintf("%s(%s) 失败%d次后，成功解开氤氲紫气太极神功的奥秘。富源：%d；经验：%d。\n",   
          me->name(1),
          me->query("id"), 
          me->query("quest/wd/yyzq/taiji/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
          me->start_busy(1);
      }
        else
        {
         tell_object(me,HIG"\n你沉思许久，不得要领。\n"NOR);
         message_vision(HIC"\n$N摇了摇头，深深地叹了口气。\n"NOR,me); 
		 message_vision(HIY"$N抓耳挠腮，苦思冥想，发现自己还是无法理解氤氲紫气太极神功奥意所在，脸上一筹莫展。\n"NOR,me);
         tell_object(me,HBBLU"\n很可惜，你本次尝试太极神功绝技秘密失败！\n"NOR);
         tell_object(me,HBBLU"你目前的经验是" + me->query("combat_exp") + "，现在时间是书剑"+ NATURE_D->game_time() + "，请记录。\n"NOR);
         tell_object(me,HBBLU"你将在间隔24小时后获得下一次机会！。\n\n"NOR);
		 log_file("quest/yyzqtaiji", sprintf("%s(%s) 解密氤氲紫气太极神功绝技失败%d次。富源：%d；经验：%d。\n",   
          me->name(1),
          me->query("id"), 
          me->query("quest/wd/yyzq/taiji/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
         me->add("quest/wd/yyzq/taiji/fail",1);
         me->set("quest/wd/yyzq/taiji/exp", me->query("combat_exp") );
         me->start_busy(1);
         me->set("quest/wd/yyzq/taiji/time",time());
		 
        }

     
	 me->delete_temp("tjsg");
	 return 1;
   }

}
