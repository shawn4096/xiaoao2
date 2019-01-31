// midong.c
// Modified by Java Apr.27 1998
// by sohu
#include <ansi.h>
inherit ROOM;
int do_mo(string arg);
int modao(object me);

void create()
{
        set("short","密洞");
        set("long",@LONG
此处是血刀门山洞内隐藏区域，此处摆放了不少的器物和坛坛罐罐
门口站两位血刀弟子，往返巡逻，戒备森严。洞内有一位长老正在指使
门下弟子忙碌着，洞内间或传来一股怪异的味道，时而肉香四溢，时而
刺鼻的血腥气息。地方放置了一块非常大的磨刀石( shi)，磨刀石旁散
落一地的阴暗血迹。
LONG );
        set("exits",([
                "west"   : __DIR__"kengdao4",
        ]));
        set("objects",([				
				"/d/xuedao/obj/liandanlu" : 1,
        ]));
		set("item_desc", ([
			"shi" : CYN"这块磨刀石显然经常被人使用的缘故，那块石头已经磨(yanmo)成接近月牙形。\n"NOR,
			"磨刀石" : CYN"这块磨刀石显然经常被人使用的缘故，那块石头已经磨(yanmo)成接近月牙形。\n"NOR,
		]));
        setup();
        replace_program(ROOM);
}

void init()
{
	add_action("do_mo","yanmo");
	add_action("do_jilian","jilian");
}

int do_mo(string arg)
{
	object me,weapon;
	me=this_player();
	if (!me) return 1;
	
	weapon=me->query_temp("weapon");
	
	if (!arg||arg!="刀")
	{
		return notify_fail("你用手在磨刀石上摸来摸去，一副沉醉的样子!\n");
	}
	
	if (!weapon
		||weapon->query("skill_type")!="blade")
	{
		return notify_fail("你不装备刀如何磨？!\n");

	}
	if (me->query_skill("xuedao-daofa",1)<300)
	{

		return notify_fail("你刀法不足300，几下就将手中的钢刀磨坏了！\n");
	}
	if (me->query("family/family_name")!="血刀门")
	{
		return notify_fail("你不是血刀门弟子，来此消遣老祖我么？\n");
	}

	if (me->query("quest/xd/xddf/huaxue/pass"))
	{
		
		return notify_fail("你已经解开了这个谜题，你无缘无故来找我作甚？？\n");
	}

	if (!me->query_temp("quest/xd/xddf/huaxue/asklaozu"))
	{
		return notify_fail("你没有得到老祖的指点，研磨了半天不得要领！\n");
	}

	if (time()-me->query("quest/xd/xddf/huaxue/time")<86400)
	{
		//command("say 你");
		return notify_fail( "你来的太频繁了，武功最忌讳心气浮躁？？\n");
	}
	if (!me->query("quest/xd/dichuan"))
	{
		//command("say 你");
		return notify_fail( "血刀需要的是始终如一的忠诚弟子，你非嫡传，焉能传授你高级武功？？\n");
	}
	if (me->query_skill("xuedao-jing",1)<300)
	{
		//command("say 你");
		return notify_fail("练习血刀经需要到300才能磨刀，还是好好修炼去吧？？\n");
	}
	if (me->query_temp("quest/xd/xddf/huaxue/jilian"))
	{
		return notify_fail("你正在祭炼中!\n");

	}
	if (me->query_temp("quest/xd/xddf/huaxue/modao"))
	{
		return notify_fail("你正在磨刀中!\n");

	}

	message_vision(HIW"$N运使老祖传授的运气法门，在磨石上起刀来！\n"NOR,me);
	me->set_temp("quest/xd/xddf/huaxue/modao",1);
	me->start_busy(2);
	remove_call_out("modao");
	call_out("modao",1,me);
	return 1;
}

int modao(object me)
{
   int i,j,jobs; 
	if(!me) return 0;
	i=random(me->query("kar"));
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	
	if (!me->query_temp("weapon")) return 0;

	jobs=(int)me->query("job_time/血刀打猎")+(int)me->query("job_time/血刀警戒");
   if(me->query_temp("canwu_modao")<(10+random(10)))
   {  
	  me->add_temp("canwu_modao",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n你将手中的刀磨了又磨，声音暗哑.\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n你仔细琢磨磨刀的技巧，停了下来，自己揣摩这刀的厚度和锋利度。\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n你一时心气浮躁，连续磨了数十下，结果每一刀都没控制好，刀锋居然越抹越厚！..\n"NOR);
			 me->add_temp("canwu_modao",-2);
			break;
		case 3:
			tell_object(me,HIW"\n你枯坐哪儿，想了想，似乎有所心得.\n"NOR);
			me->add_temp("canwu_modao",1);

			break;
		case 4:
			tell_object(me,CYN"\n你自言自语，神情疲倦之际，似乎即将崩溃.\n"NOR);
			me->add_temp("canwu_modao",-1);

			break;
		case 5:
			tell_object(me,MAG"\n你磨刀之际，忽然手中一轻，发现竟然丝毫声音都没发出来.\n"NOR);
			me->add_temp("canwu_modao",4);

			break;

		default:tell_object(me,YEL"\n你磨了磨刀，刀声霍霍.\n"NOR);
			break;

	  }      

	  tell_room(environment(me),HIC""+me->query("name")+"手拿钢刀，一下一下研磨，神情极为专注...\n"NOR, ({}));

	//  remove_call_out("do_mo");
	  call_out("modao",3+random(3), me);

   } 
  else if (i>24
	  && random(j)<4
	  && random(jobs)>1200
	  && me->query("kar")<31)
 	{ 
        
         me->start_busy(3);
		 message_vision(HIG"\n$N磨了半天，手腕寸关穴忽然一痛，手中的钢刀竟然忽然间轻了起来，轻若无误。”\n"NOR,me); 
         message_vision(HIW"\n$N心中大喜，「哈哈哈」仰天大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HBYEL+HIW"\n$N经过不断研磨练习领悟，终于领悟了血刀老祖所传授的化血诀的奥秘！”\n"NOR,me); 
         log_file("quest/xdhuaxue", sprintf("%s(%s) 化血解密成功！第%d次参悟，机缘巧合下，成功参悟化血绝技的奥秘，随机幸运值：%d,当前随机值：%d,当前经验：%d,\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xd/xddf/huaxue/fail"),
		 i,
		 j,
         me->query("combat_exp"),
		 ));

		 me->set("quest/xd/xddf/huaxue/time",time());
		 me->set("quest/xd/xddf/huaxue/pass",1);
		 me->delete_temp("canwu_modao");
		// me->set("title",HBRED"血刀刀法传人"NOR);
		 me->delete_temp("quest/xd/xddf/huaxue/modao");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N长叹一生，自言自语地说道：“看来这化血诀真是不好解啊，继续努力吧。”\n"NOR,me); 
		 message_vision(HIY"\n参悟化血诀绝技解密失败！\n"NOR,me); 
         log_file("quest/xdhuaxue", sprintf("%s(%s) 失败！参悟化血第%d次失败，随机幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xd/xddf/huaxue/fail",1),
		 i,
		 j,
         me->query("combat_exp"),));        
		 me->add("quest/xd/xddf/huaxue/fail",1);
		 me->set("quest/xd/xddf/huaxue/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_modao");
		 me->delete_temp("quest/xd/xddf/huaxue/modao");
		 me->delete_temp("quest/xd/xddf");
		 return 1;
   }
	
}
