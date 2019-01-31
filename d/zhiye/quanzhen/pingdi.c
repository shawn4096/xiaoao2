inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "平地");
        set("long", @LONG
这里是后山上的一块平地。这块平地好像是猎人们为了晾晒各种谷物之所
甚是平整，这块平地的四周打了很多木架，右侧有一排高耸的松树。在一棵大
松树的枝杈间有一栋小木屋。
LONG);
        set("outdoors", "quanzhen");
        set("exits", ([
                "west" : __DIR__"xiaolu3",
               // "enter" : __DIR__"shandong",
        ]));
		set("item_desc", ([
        "小木屋": CYN"这是一栋小木屋，似乎很久没有人来住的样子，屋面上蒙了厚厚的积雪。\n"NOR,
	    //"光线":HIC"这光线似乎看起来光怪陆离，如不仔细观察，还真没发现什么异常。\n"NOR,
        ]) );
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
int init()
{
	object qiu,yang,xiao,duan;
	object me=this_player();
	
	add_action("do_jump","jump");

	if (me->query_temp("tzjj/tingover"))
	{
		if (!objectp(qiu=present("qiu qianzhang",environment(me))))
		{
			qiu=new("kungfu/class/tiezhang/qqren");
			qiu->move("d/quanzhen/pingdi");
			qiu->set("name",HIC"慈恩"NOR);

		}
		if (!objectp(duan=present("yideng dashi",environment(me))))
		{
			duan=new("d/dali/yideng/npc/yideng");
			duan->move("d/quanzhen/pingdi");
		}
		
		//yang=new("kungfu/class/gumu/yang");
		//yang->move("d/quanzhen/pingdi");
		//xiao=new("kungfu/class/gumu/xln");
		//xiao->move("d/quanzhen/pingdi");
		//qiu->kill_ob(duan);
		message_vision(HIR"\n\n$N对$n喝道，“你天天骗我，忽悠我，什么生死无碍，你接我一掌试试。说完一掌拍向$n。\n”"NOR,qiu,duan);
		message_vision(HIY"\n\n$N的铁掌功夫何其犀利，为$N一掌拍中胸口，哇地突出一口鲜血！尽管如此，但$n却没有丝毫还手之意。\n"NOR,qiu,duan);
		message_vision(CYN"$N白眉低垂，只是低声不断吟诵阿弥陀佛，\n"NOR,duan);
		duan->add("qi",-3000);
		call_out("qiu_kill",3+random(2),me,duan,qiu);
		me->delete_temp("tzjj/tingover");

	}
	


}
int do_jump(string arg)
{
	object me=this_player();
	if (!arg || arg!="小木屋")
	{
		return notify_fail("你要往哪儿跳？\n");
	}
	if (me->query_skill("dodge",1)<350)
	{
		return notify_fail("你的轻身基本功不够350，回去好好练习吧。\n");
	}
	message_vision(HIC"你纵身一跃，跳到树杈，一弯腰钻入小木屋之中。\n"NOR,me);
	me->move("d/quanzhen/xiaomuwu");
	return 1;

}
int qiu_kill(object me,object duan,object qiu)
{
	
	message_vision(HIR"裘千仞眼见$N站在一旁，双目顿时变得凶狠，对$N喝道，我见你越来越不顺眼了！"NOR,me);
	qiu->kill_ob(me);
	me->kill_ob(qiu);
	me->set_temp("tzjj/qiukill",time());
	me->delete_temp("tzjj/tingover");
	call_out("check",1,me,duan,qiu);
	return 1;
}
int check(object me,object duan,object qiu)
{
	if (!me) return 1;
	
	if (!present("qiu qianren",environment(me)) && !me->is_fighting())
	{
		message_vision(HIC"$N停下身来，回想方才慈恩的一招一式，端的是精妙异常，不禁呆立当场。\n"NOR,me);
		message_vision(HIY"\n\n\n看来还是很有必要回去跟自己的师傅探讨这铁掌掌法的精妙招式奥妙了。\n"NOR,me);
		//message_vision(YEL"\n\n$N刹那间呆立当场，脑中电闪雷鸣。不禁进入一种奇妙的顿悟(dunwu)状态。"NOR,me);
		//add_condition("do_dunwu","dunwu");
		destruct(duan);
		//destruct(qiu);
		me->set_temp("tzjj/killover",1);
		return 1;
	}
	if (time()-me->query_temp("tzjj/qiukill")>30)
	{
		message_vision(HIY"你太驽钝了，杀一个恶僧都花了这么长时间，解密失败。\n"NOR,me);
		if (objectp(qiu=present("qiu qianren",environment(me))))
			destruct(qiu);
		if (objectp(duan=present("yideng dashi",environment(me))))
			destruct(duan);
		me->set("quest/tz/tzzf/tiezhang/time",time());

		return 1;
	}
	call_out("check",2,me,duan,qiu);

}

//顿悟解密，玄铁剑绝世

/*	    	
int do_dunwu(string arg)
{
	object me=this_player();
	me->start_busy(10);
	if (!arg||arg!="铁掌绝技")
		return notify_fail("你要顿悟什么？\n");
	if (me->query("quest/tz/tzzf/tiezhang/pass"))
		return notify_fail("你已经全部领悟了铁掌绝世武技！\n");
	if (time()-me->query("quest/tz/tzzf/tiezhang/time")<86400)
		return notify_fail("你来的太勤快了！\n");
	
	if (me->query_temp("tzzf/dunwu1")) 
	{
		   message_vision(HIC"你站在那儿，刹那间进入一种顿悟状态，看似纹丝不动，实则大脑中电闪雷鸣。\n"NOR,me);
           me->start_busy(999);
		   remove_call_out("thinking");
		   call_out("thinking",1,me);
		   me->delete_temp("tzzf/dunwu1");
	}
	return 1;
}

int thinking(object me)
{
  int i,j; 
  if(!me) return 0;
  i=random(me->query("kar"));
  j=random(15);

  me->set("quest/tz/tzzf/tiezhang/time",time());

  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) 参悟铁掌绝技时，KAR异常，当前经验：%d。年龄：%d。kar:%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_tiezhang")<(15+random(10)))
   {  
	  me->add_temp("canwu_tiezhang",1);

	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n你将师傅所传授的心法彼此印证，只觉得耳目一新...\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n忽然，你似乎抓住了一些明悟。\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n你陷入馄饨状态，大脑一片空明，似乎要抓住那个线索了！..\n"NOR);
			break;
		case 3:
			tell_object(me,HIW"\n你枯坐哪儿，甚是无聊，神情抑郁，似乎有些累了.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n你自言自语，神情疲倦之际，似乎遇到瓶颈了..\n"NOR);
			break;
		case 5:
			tell_object(me,MAG"\n你思维漂浮在空中，宛如婴儿沐浴.神清气爽.\n"NOR);
			break;
		default:tell_object(me,YEL"\n你叹了一口气，精神总是不能有效集中.\n"NOR);
			break;

	  }
      

	  tell_room(environment(me),HIC""+me->query("name")+"面色平和，浑然忘我，似乎在思索着什么...\n"NOR, ({}));
	
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
	  return 1;

   } 
   else if (i>=28
			&& j==2
			&& random(me->query("str"))>40
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIY"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HIY"\n$N经过不断领悟，终于领悟了教主夫人所传授的金蛇缠丝手的奥秘，缠丝手豁然贯通！”\n"NOR,me); 
         log_file("quest/chansishou", sprintf("%s(%s) 成功！第%d次参悟，机缘巧合下，成功参悟金蛇缠丝手的缠丝奥秘，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/chss/fail"),
		 i,
		 j,
         me->query("combat_exp")));

		 me->set("quest/sld/chss/time",time());
		 me->set("quest/sld/chss/pass",1);
		 me->delete_temp("canwu_chansi");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N长叹一生，自言自语地说道：“看来又是一无所获啊。”\n"NOR,me); 
		 message_vision(HIY"\n参悟金蛇缠丝手解密失败！\n"NOR,me); 
         log_file("quest/chansishou", sprintf("%s(%s) 失败！第%d次失败参悟金蛇缠丝手，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/chss/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/sld/chss/fail",1);
		 me->set("quest/sld/chss/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_chansi");
		 return 1;
   }

}*/