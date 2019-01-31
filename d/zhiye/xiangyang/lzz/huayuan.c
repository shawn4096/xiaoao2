//huayuan.c
//Csl 2000.04.26
#include <ansi.h>

inherit ROOM;
string look_gushu();
void create()
{
        set("short", "花园");
        set("long",@LONG
这个花园虽然不大，但整理的井井有条，种植着各式各样的花花草草，看
的出这里的主人下了一番功夫，常有人来这里散步。沿着弯弯曲曲的花径，可
以通向后院。路的两旁栽种了大量的古树，古木森森，甚是高大。枝叶繁茂，
绿荫葱葱。
LONG
        );
		set("outdoors", "襄阳");
        set("exits",([
                "south"  :  __DIR__"houyuan",
		]));
		set("item_desc", ([
                "古树" : (:look_gushu():),
        ]));

	setup();
}

string look_gushu()
{
	this_player()->set_temp("lookgushu",1);
	return "这是一株绿荫葱葱的古树，高耸入云，枝杈繁茂，若人趴在树上看不见踪迹。\n";

}

void init()
{
	object me=this_player();
	object huang,lu;
	add_action("do_jump","jump");
    
	if (me->query_temp("bangjue/cang"))
	{	
		if (!objectp(huang=present("huang rong",load_object("d/xiangyang/lzz/huayuan"))))
		{
			huang=new("d/xiangyang/lzz/npc/huangrong");		
			huang->move("d/xiangyang/lzz/huayuan");	
		}
		if (!objectp(lu=present("lu youjiao",load_object("d/xiangyang/lzz/huayuan"))))
		{
			lu=new("d/xiangyang/lzz/npc/lu");
			lu->move("d/xiangyang/lzz/huayuan");	
		}
		//me->start_busy(999);
		call_out("do_tech1",2+random(3),me,huang,lu);
	}
}

int do_jump(string arg)
{
	object me=this_player();
	if (!me->query_temp("lookgushu"))
		return notify_fail("你要干什么？\n");
	if (!arg || arg!="古树")
	{
		return notify_fail("你像一个猴子一样要往哪里跳？\n");
	}
	message_vision("$N纵身而起，向古树跳去，瞬间隐藏在枝繁叶茂的树顶之间。\n",me);

	me->move("d/xiangyang/lzz/gushu");
	return 1;
}

int do_tech1(object me,object huang,object lu)
{
	
	huang->say_lu1();
	lu->say_huang1();
	call_out("do_tech2",2+random(2),me,huang,lu);
	
}
int do_tech2(object me,object huang,object lu)
{
	
	huang->say_lu2();
	lu->say_huang2();
	call_out("do_tech3",1+random(2),me,huang,lu);
	
}
int do_tech3(object me,object huang,object lu)
{
	message_vision(YEL"\n\n$n将这打狗棒的八字诀一一讲来，$N听的如醉如痴。\n"NOR,me,huang);

	huang->fight_ob(lu);
	lu->fight_ob(huang);
	//message_vision(YEL"黄蓉将这打狗棒的八字诀一一讲来，你听的如醉如痴。\n"NOR);
	add_action("do_guanwu","guanwu");
}


int do_guanwu(string arg)
{
  object me=this_player();
  if(!arg||arg!="打狗棒") return notify_fail("你要观摩什么？");
  
  if (me->query("family/family_name")!="丐帮")
	 return notify_fail("你不是丐帮子弟，来此莫非是蒙古国的奸细么？\n");
  if (me->query("family/master_name")!="洪七公")
	 return notify_fail("你不是洪七公老爷子的亲传弟子，来此作甚？\n");
  
  if (me->query_skill("dagou-bang",1)< 450)
	 return notify_fail("你打狗棒等级太低，不足450，来此作甚？\n");
  if (me->query("quest/gb/dgb/bangjue/pass"))
	 return notify_fail("你已经解开棒诀谜题，来此作甚？\n");
  if (time()-me->query("quest/gb/dgb/bangjue/time")<86400)
	 return notify_fail("你真是太勤快了？\n");
  if (me->is_busy())
	 return notify_fail("你正在忙碌中！\n");
  if(me->query("quest/gb/dgb/bangjue/fail")>=3 && me->query("registered")<3)
  {
		tell_object(me,"shrug 已经多次传授，你怎么都还没有领悟,真够笨的！");
		return 1;
  }
  if (me->query_skill("dagou-bang",1)< 450)
	 return notify_fail("你打狗棒等级太低，不足450，来此作甚？\n");
  me->start_busy(999);
  remove_call_out("thinking");
  call_out("thinking",1,me);
  return 1;

}
int thinking(object me)
{
   int i,j;
	object huang,lu;
  if(me->query_temp("bangjue/guanwu")<(5+random(5)))
  { 
	  me->add_temp("bangjue/guanwu",1);
      if(random(2)) tell_object(me,HIG"\n你认真回想着方才黄蓉和鲁有脚战斗中所展现的一招一式...\n"NOR);
             else tell_object(me,HIY"\n突然间，棒影闪烁，你似乎抓到了什么...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
   }
   else
   {  
	  me->delete_temp("bangjue/guanwu");
      j = 20;
      if(me->query("m-card-vip")) j =  18;
      if(me->query("y-card-vip")) j =  15;
      if(me->query("buyvip"))     j =  10;
	  i= random(j);
 	
	tell_object(me,HIG"\n你听了黄蓉的指点，对打狗棒招式和口诀融合的真正奥妙似乎有些心得。\n"NOR);
    tell_object(me, HIW"\n你按照黄蓉所言，施展出「缠」字诀，手中木棒迟缓之间闪烁不定。\n"NOR);
    tell_object(me, HIC"\n你按照黄蓉所言，施展出「封」字诀，棒影如山，防守严密，水泼不进。\n"NOR);
	tell_object(me, HIR"\n你按照黄蓉所言，施展出「劈」字诀，棒式迅捷无比，招式凶猛凌厉。\n"NOR);
	tell_object(me, HIY"\n你按照黄蓉所言，施展出「绊」字诀，绵绵密密，一波接一波闪动。\n"NOR);
	tell_object(me, HIG"\n你按照黄蓉所言，施展出「转」字诀，宛如形成一个漩涡，将对方圈在棒影之内。\n"NOR);
	tell_object(me, HIB"\n你按照黄蓉所言，施展出「引」字诀，指东打西，指南打北，全无章法可言，但每一招却都灵动异常。\n"NOR);
	tell_object(me, RED"\n你按照黄蓉所言，施展出「戳」字诀，如判官笔、如长枪、如匕首、劲气凝聚成束，端的凶猛。\n"NOR);
	tell_object(me, BLU"\n你按照黄蓉所言，施展出「挑」字诀，手中棒子仿佛具有黏力一般，如跗骨之蛆，随对方招式而走。\n"NOR);
     //悟性30+300为基础
	if(i<3 
		&& me->query("kar")<31
		&& random(me->query_int())>50
		&& random(me->query("kar"))>27)
	 {
		tell_object(me,HIY"\n\n你历尽千辛挖苦，终于得偿所愿，将打狗棒口诀融汇贯通! \n"NOR);
       	me->set_skill("bangjue", 200);
		me->set("quest/gb/dgb/bangjue/pass",1);

		message_vision(HIC"你的打狗棒法口诀提升了！"NOR,me);
		me->start_busy(1);
		log_file("quest/dgbbangjue", sprintf("%8s(%8s) 失败%d次后，彻底领悟打狗棒口诀绝技。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/gb/dgb/bangjue/fail"),i,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/gb/dgb/bangjue/fail",1);
		me->set("quest/gb/dgb/bangjue/time",time());
		
		tell_object(me,HIY"\n\n你听了黄蓉的指点，虽然听见了棒诀的奥秘，可是对棒诀如何和招式融汇贯通的真正奥妙全然不得要领。\n\n"NOR);
		tell_object(me,HBBLU+HIW"\n\n解密棒法口诀失败，再接再厉。\n\n"NOR);
		me->start_busy(1);
		me->delete_temp("bangjue");
		log_file("quest/dgbbangjue", sprintf("%8s(%8s) 打狗棒棒诀解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/gb/dgb/bangjue/fail"),i,me->query("combat_exp")) );
	  }

	  if (objectp(huang=present("huang rong",environment(me))))
	  {
		  destruct(huang);
	  }
	  if (objectp(lu=present("lu youjiao",environment(me))))
	  {
		  destruct(lu);
	  }
      return 1;
  }

}
