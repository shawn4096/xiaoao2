// Room: /d/huashan/hole.c
// Date: Look 99/03/25
#include <ansi.h>
#include <skill.h>
inherit ROOM;
int do_lingwu();
void create()
{
	set("short", "思过崖洞口");
	set("long", @LONG
这里便是犯错误华山派弟子受罚思过的地方。位于玉女峰顶，正好有一小
块平地，一面是深不可测的山谷、一面是陡峭的悬壁(bi)，零零落落的有几块
山石。其中一块特别光滑，想是弟子在面壁是久坐而成。
LONG
	);
	set("exits", ([
		"out" : __DIR__"siguoya",
	]));

	set("item_desc", ([
		"bi" : "你看着看着忽然发现有一处石壁上的青苔比别处少得多。不禁想....\n",
	]) );

	setup();
}

void init()
{
        object me = this_player();
        me->delete_temp("mianbi_count");
        me->delete_temp("break_flag");
        add_action("do_mianbi", "mianbi");
		add_action("do_lingwu", "sikao");
		add_action("do_lingwu", "jingsi");

}
int do_lingwu()
{
   object me = this_player();
   int i;
   if (me->is_busy())
                return notify_fail("你正忙着呢，无法静下心来面壁思过。\n");
   if (me->is_fighting())
                return notify_fail("你正在战斗中，如何静下心来面壁思过？\n");
//   if (me->query_temp("quest/huashan/zixia1",1))
  //              return notify_fail("有标记测试？\n");
   if (me->query_temp("quest/huashan/zixia1",1))
      {
        message_vision("$N对着石壁跌坐领悟，良久，若有所悟。\n", me);
        me->receive_damage("jing", random(100));
        me->add("shen",random(100));
        me->start_busy(random(3));
		i=i+1;
		
		if (random(me->add_temp("lingwu_count", 1)) > 20 && random(me->query("kar"))>= 20 && random(10) <= 5) {
                me->delete_temp("quest/huashan/zixia1", 1);
				me->set_temp("quest/huashan/shandong", 1);
                //add_action("do_break", "break");
                me->command("sigh");
				write(HIR"你忍不住一阵心烦意乱，想起以往的过去，实在按耐不住，“呼”地一声站了起来。\n"
				+"但这和紫霞功要求心气平和宗旨相悖，忍不住一阵气血翻腾,哇地吐出一口鲜血!\n"
				+"看起来你已经深受不轻的内伤。\n"NOR,me);
				
				me->recieve_wound("jing",random(10));
				me->receive_wound("qi",random(10));
				write(HIC"你思前想后，与其这么枯坐还不如到卧室去先睡一觉,说不定还能对疗伤大有效果。\n"NOR,me);
				call_out("thinking",2,me); 
								
				}
		else
			{
		      me->receive_wound("qi",random(10));
			  write(HIC"你按照岳不群给你讲解的紫霞要诀开始领悟,死活不得要领，长叹一声，站起身来，心灰意冷。\n"NOR);
			  //i=i+1;
			  me->start_busy(random(1));
			  me->delete_temp("quest/huashan/zixia1");
			  }
			  return 1;
		}
        write(HIC"你要干什么？\n"NOR);
		return 0;
}
//增加子程序 胡思乱想

int thinking()
{
  object me= this_player();
  if(environment(me)!= find_object(__DIR__"hole")) 
  {
  	//start_condition(ob);
    if(random(2)) message_vision(HIC"\n岳不群伸了伸懒腰，道：没想到"+me->query("name")+"竟然不务正业，没料得竟然是蠢材一个。\n"NOR,me); 
    else message_vision(HIC"\n$N疑惑问道：夷~~~人呢？$n，人呢？\n"NOR,me); 
  	return 1;
  }
  
  if (me->query_temp("quest/huashan/shandong")&& random(10)>= 5)
  {
	  write(HIM"这时，忽然听到洞外岳不群喝道，‘你这小畜生不好好用功，这几天都白白浪费了！真让我失望！’\n"NOR,me);
      write(HIY"不知道岳不群何时来此，想起自己的一言一行，不禁又羞又愧，顿时大汗淋漓！\n"NOR,me);
	  me->delete_temp("quest/huashan/shandong");
	  me->set_temp("quest/huashan/zixia/zixia2",1);
	  return 1;
  }
  message_vision(HIC"\n你思前想后，逐渐陷入到情乱意迷的症状！\n"NOR,me); 
} 
//面壁
int do_mianbi()
{
	int getshen;
        object me = this_player();

        if (me->is_busy())
                return notify_fail("你正忙着呢，无法静下心来面壁思过。\n");
        if (me->is_fighting())
                return notify_fail("你正在战斗中，如何静下心来面壁思过？\n");
        if ((int)me->query("shen") < 0)
        {
        	getshen= random(-1 * (int)me->query("shen")/600);
        }
        else
        {
        	getshen= -1 * random((int)me->query("shen")/300);
        }

        if (!me->query_temp("break_flag"))
        {
        message_vision("$N对着石壁跌坐静思，良久，若有所悟。\n", me);
        me->receive_damage("jing", random(100));
        me->add("shen",getshen);
        me->start_busy(random(3));
        if (random(me->add_temp("mianbi_count", 1)) > 35) {
                me->set_temp("break_flag", 1);
                add_action("do_break", "break");
                write("你忽然产生一种破壁的欲望，不禁站了起来。\n");
        }
        }
        return 1;
}


int do_break(string arg)
{
    int n;
	object me = this_player();
	object weapon;
	object room;
	n = (int)me->query("neili");
   	room = find_object(__DIR__"rukou");
	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("你手中无剑，怎能破壁？\n");
     message_vision("$N走到石壁前，拔出腰间所悬长剑，运劲向石壁刺了过去。\n", me);

 if ( n >= 600 ){
    message_vision("$N只听一声轰响，石壁被捅穿了，原来里面有一个大洞。！\n", me);
    set("exits/enter",__DIR__"rukou");
    set("exits/out",__DIR__"siguoya");
    this_player()->add("neili", -200);
    remove_call_out("close");
    call_out("close", 5, this_object());
    if(!(room = find_object(__DIR__"rukou"))) room = load_object(__DIR__"rukou");
    if( room = find_object(__DIR__"rukou") ) 
	{
		message("vision", "你只听外面一声轰响，石洞被人从外面捅穿了，露出了一个洞口。\n", room);
		room->set("exits/out",__DIR__"hole");
	//  remove_call_out("close1");
		call_out("close1", 5, room);   
	}
  }
  else {
    message_vision("结果只听一声闷哼，$N被石壁的反弹力震得眼前一黑....\n", me);
    this_player()->unconcious();
    }
    return 1;
}

void close(object ob)
{
        message("vision","崖上忽然掉下来一块巨石，将洞口封了个严严实实。\n", ob);
        ob->delete("exits/enter");
}
void close1(object room)
{       
        message("vision","崖上忽然掉下来一块巨石，将洞口封了个严严实实。\n", room);
        room->delete("exits/out");
}

