// 全真教 qixing-jian/lianzhen2 quest
//modifield by action@SJ 2008/9/18
#include <ansi.h>;
inherit ROOM;
inherit F_SSERVER;
void create()
{
	set("short", HIB"密洞"NOR);
	set("long", @LONG
这是全真教王重阳自己挖掘的密洞，当太阳升起时能直射全洞。象是有人在此住
过，正面有一石床，左边放有一些石碗，顶上的居然有几个小洞(hole)，阳光透
过小洞直射进来，这有小洞的排列很像北斗七星的排列，你可以演练(yanlian)。
LONG
	);
  set("item_desc", ([
        "hole": CYN"这是一个连接密室与外部的一个小孔，可以看到外面光景，不时有光线通过这个小孔射进这个密室。\n"NOR,
	    "光线":HIC"这光线似乎看起来光怪陆离，如不仔细观察，还真没发现什么异常。\n"NOR,
        ]) );
  set("canwu",1);
  set("exits", ([
		"up" : __DIR__"shandong",
	]));    
	setup();
}

void init()
{
	object me=this_player();
	if (me->query_temp("quest/qixing/asked")) 
	{
		add_action("do_yanlian", "yanlian");
		//me->delete_temp("quest/qixing/asked");
		me->set_temp("quest/qixing/enter",1);
		//load_object("d/quanzhen/obj/bowl1")->move(environment(me));
	}
	if (!me->query_temp("quest/qixing/asked")||me->query("qixing/pass")) 
	   me->move("/d/quanzhen/shandong");
}


int do_yanlian(string arg)
{
	object me;
	me = this_player();

	if( !me||!living(me) ) return 0;
	if( arg == ""|| !arg) return notify_fail("你想演练什么内容！\n");
    if( me->query("family/family_name") !="全真教" )
	{
		me->move("/d/quanzhen/shandong");
		return notify_fail("忽然冥冥中有一个声音大喝一声，你是怎么进来的？滚！\n");
	}
	if( (int)me->query_skill("quanzhen-jianfa", 1) < 450 )
		return notify_fail("你的全真剑法等级不足，怎么练也没有用。\n");
    if( (int)me->query_skill("xiantian-gong", 1) < 450 )
		return notify_fail("你的先天功等级不足，怎么练也没有用。\n");
	if( me->is_busy() || me->is_fighting() )
		return notify_fail("你正忙着呢。\n");
	
  	if( time()-me->query("quest/qz/qzjf/qixing/time")< 86400)
		return notify_fail("唉，盲目瞎练会出差错的，你还是去休息一下吧。\n");
   	
	if(me->query("quest/qz/qzjf/qixing/pass"))
	{
		
		me->set("title",HIG"七"HIC"星"HIR"绝"HIY"命"HIM"剑"HIC"传人"NOR);
		me->set("mytitle/quest/qzqixingtitle",HIG"七"HIC"星"HIR"绝"HIY"命"HIM"剑"HIC"传人"NOR);
		return notify_fail("不要浪费时间了，你已经尽得全真剑法精妙所在。\n");
	}
	
	//if(me->query("qixing/time")< 86400)
		//return notify_fail("唉，别太急啦。\n");	
	
	if( arg == "七星绝技"|| arg == "qixing") {
	
			message_vision("$N慢慢按照小洞中射进来的光线，走起北斗七星剑七星绝命剑的招式来。\n", me);
			me->set("qixing/time",time());
            me->set("qixing/combat_exp",me->query("combat_exp"));
		    //remove_call_out("canwu");
			me->start_busy(999);
            call_out("canwu", 1, me);  
            return 1;
         }  
      return notify_fail("什么？\n");
         
} 							
void canwu(object me)
{
  if(!me) return;  
    remove_call_out("thinking");
    call_out("thinking", 2, me); 

	this_object()->add("canwu",1);

    message_vision(HIR"你跟着从小洞发出来的光线，演练着北斗七星的步法.........\n"NOR,me);
    //me->start_busy(2);
}

int thinking(object me, object ob)
{
	int j,i,total;
	//object bowl;
	if(!me) return 0;
	//bowl=present("posun shuiwan",environment(me));
    if(me->query_temp("lianzhen_thinking")<(6+random(3)))
	{
		me->add_temp("lianzhen_thinking",1);
        if(random(2)) tell_object(me,WHT"\n你按照光线照进来的路线招式,试着练了一遍，你发现你的剑招越来越快...\n"NOR);
        else tell_object(me,HIG"\n\n突然间，你似乎抓到了什么，霎时密洞中金光闪耀，你似乎感觉到了北斗星运行变化...\n"NOR);
	    remove_call_out("thinking");
		call_out("thinking",3+random(3), me, ob);
	}
	else
	{
       me->delete_temp("lianzhen_thinking");      

	//  total = me->query("str") + me->query("con")+ me->query("dex")+ me->query("int");
      
	  j = 22;

      if(me->query("m-card-vip")) j =  20;
      if(me->query("y-card-vip")) j =  18;
      if(me->query("buyvip"))     j =  10;
      i=random(j);

      if (i <3 
		 && random(me->query("int")) > 40 
	     && me->query("kar")<31
		 && random(me->query("kar"))>26)
	  {
   
       tell_object(me,HIG"\n你发现你已经完全看懂了墙壁的招式，招式已如无与伦比之境，整个石室充满了真气。\n"NOR);
       message_vision(HIG"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
       me->set("quest/qz/qzjf/qixing/pass",1);
       me->delete_temp("quest/qixing");
	   me->set("title",HIG"七"HIC"星"HIR"绝"HIY"命"HIM"剑"HIC"传人"NOR);
	   me->set("mytitle/quest/qzqixingtitle",HIG"七"HIC"星"HIR"绝"HIY"命"HIM"剑"HIC"传人"NOR);
       message_vision(HIC"\n你根据照进来的光线，终于领悟了七星绝命剑的精华所在。”\n"NOR,me);   
       me->delete_temp("quest");
	   log_file("quest/qixing", sprintf("%s(%s) 失败%d次成功解开七星绝命剑。富源：%d；经验：%d。\n", me->name(1),me->query("id"), me->query("quest/qz/qzjf/qixing/fail"),me->query("kar"),me->query("combat_exp")) );	   
	  
	 }
    else
    {
       tell_object(me,HIG"\n你脑海里似乎抓住了什么，可是依然不得要领。\n"NOR);
       message_vision(HIC"\n$N摇了摇头，道：“好像还是很困难的。”说罢，深深地叹了口气。\n"NOR,me); 
       me->add("quest/qz/qzjf/qixing/fail",1);
       me->set("quest/qz/qzjf/qixing/time",time());
       me->move("d/quanzhen/shandong");
	   me->delete_temp("quest");
	   me->delete_temp("quest/qixing");
	   
	   log_file("quest/qixing", sprintf("%s(%s) 解七星绝命剑失败：%d次。富源：%d；经验：%d。\n", me->name(1),me->query("id"), me->query("quest/qz/qzjf/qixing/fail"),me->query("kar"),me->query("combat_exp")) );
    }
	me->start_busy(-1);
  }
  return 1;
}

int valid_leave(object me, string dir)
{
        if (me->query_temp("quest/qixing/enter") && dir == "up")
			me->delete_temp("quest");
        return ::valid_leave(me, dir);
}
