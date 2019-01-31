#include <ansi.h>
inherit FBROOM;

int     do_cry();
#include "fuben.h";

void create()
{
                                        
        set("short", HIW"华山绝顶-副本"NOR);
        set("long", @LONG
这是一处人迹罕至的山峰绝顶，足底溜滑，山势险峻，若是一脚踏空，势必
掉在万仞深谷中跌得粉身碎骨,相传华山论剑就在此处。山壁上刻了四个大字，写道
“华山论剑”，字迹遒劲，宛如有人以石做纸，以指而书似得。
LONG
        );
		
        set("outdoors", "副本");
		set("backroom","/d/huashan/sheshen");
        set("quest",1);
		set("no_sleep_room",1);
		set("no_quit", 1);       
		
		setup();
}

void init()
{
		//object me = this_player();		
        add_action("do_chaikai","chaikai");		
        //me->set("startroom", "/d/city/guangchang");
		::init();
}


int do_cry()
{
        command("cry");       
}


void task_over()
{
	
	set("over",1);
	fuben_reset();
}

int do_chaikai()
{
	object feng,hong;
	object me=this_player();
	feng=present("ouyang feng",environment(me));
	hong=present("hong qigong",environment(me));
	if (!feng)
	{
		call_out("task_over",1,me);
		return notify_fail("由于你分拆不及时，使得欧阳锋被洪七公失手杀死，任务失败!\n");		
	}
	if (!hong)
	{
		call_out("task_over",1,me);
		return notify_fail("由于你分拆不及时，使得洪七公被欧阳锋失手杀死，任务失败!\n");		
	}
	feng->remove_all_killer();
    
	tell_object(me,HIC"\n\n你见大事不好，慌忙的四处张望,寻找拆开的机缘所在,当你看到一颗小树后大喜。\n\n"NOR);
	tell_object(me,HIC"你折了一根树干，走到二人之间盘膝坐下，运功护住全身，一咬牙，伸树干往二。\n\n"NOR);
	tell_object(me,HIC"人之间挑去。这一挑居然毫不费力，二人的内力从树干上传来，被你运内力一挡。\n\n"NOR);
	tell_object(me,HIC"立即卸去。原来强弩之末不能穿鲁缟，北丐西毒虽然俱是当世之雄，但互耗多时。\n\n"NOR);
	tell_object(me,HIC"均已精力无多。\n"NOR,me);
	feng->set("neili",0);
	feng->start_busy(999);
	hong->set("neili",0);
	hong->start_busy(999);
	//丐帮弟子接口
	if (me->query_temp("wugou/askguo"))
	{
		hong->hong_say();
		add_action("do_yanlian","yanlian");
	}
	//蛤蟆功接口
	if ( me->query("oyf/hamagong") == 2)
	{
		feng->feng_say();
		add_action("do_yanshi","yanshi");
	}
	return 1;
}
int do_yanlian(string arg)
{
	object me=this_player();
	object hong,feng;
	feng=present("ouyang feng",environment(me));
	hong=present("hong qigong",environment(me));
	if (!arg || arg!="天下无狗")
	{
		return notify_fail("你要演练什么？");
	}
	if (!me->query_temp("wugou/answerok"))
	{
		message_vision(HIC"\n$n对$N喟然一叹，凡事都不能强求，既然你不愿意，那么老叫花子这门绝技就算是失传了！\n"NOR,me,hong);
		return 0;
	}
	if (me->is_busy()||me->is_fighting())
	{
		return notify_fail("你正在忙碌中!\n");
	}
	message_vision(HIC"\n\n$n喝道，老毒物，我还有一门压箱底的武功没有施展出来，你想不想见识下？！\n"NOR,me,hong);
	message_vision(HIG"$n喝道，这门功夫乃是我丐帮不传之秘，叫做天下无狗，意思是此招一出，天下所有的狗都将被打死，包括你！\n"NOR,me,hong);
	message_vision(HIG"$n喝道，当然这里面肯定包括你！说完，$n忍不住一阵狂笑,声音却黯哑无比。\n"NOR,me,hong);
    hong->hong_say2();
	message_vision(HIR"\n\n$n一见此招出现，顿时四面八方皆为棒影，面无人色，良久无策，陷入冥想破解之中。\n"NOR,me,feng);
	hong->hong_say3();
	if (me->query_skill("dagou-bang",1)< 500)
		return notify_fail("你的打狗棒法等级太低了，500级要求，无法领悟这门技能。\n");
	if (me->query("family/family_name")!="丐帮")
		return notify_fail("你不是丐帮子弟，来此莫非是金国的奸细么？\n");
	if (me->query("family/master_name")!="洪七公")
		return notify_fail("你不是洪七公老爷子的亲传弟子，来此作甚？\n");
	if (me->is_busy())
	{
		return notify_fail("你正在手忙脚乱？\n");
	}

	if (me->query("quest/gb/dgb/wugou/pass"))
		return notify_fail("你已经解开天下无狗谜题，来此作甚？\n");
	if (me->query_temp("wugou/yanlian"))
		return notify_fail("你正在演练天下无狗绝技过程中？\n");

	if ((time()-me->query("quest/gb/dgb/wugou/time"))<86400)
		return notify_fail("你真是太勤快了，下次再来？\n");
	if (me->query("int")<40)
		return notify_fail("打狗棒需要绝高的悟性，你这点悟性是领悟不了打狗棒的？\n");
	if(me->query("quest/gb/dgb/wugou/fail")>=3 && me->query("registered")<3)
	{
		tell_object(me,"已经多次传授，你怎么都还没有领悟,真够笨的！");
		return 1;
	}
	me->start_busy(99);
	call_out("thinking",1,me,hong,feng);
	return 1;
}

int thinking(object me,object hong,object feng)
{
   int i,j;

  if(me->query_temp("wugou/yanlian")<(10+random(5)))
  { 
	  me->add_temp("wugou/yanlian",1);
      if(random(2)) tell_object(me,HIY"\n你认真回想着方才洪七公和欧阳锋战斗中所展现的一招一式...\n"NOR);
             else tell_object(me,HIG"\n突然间，你似乎抓到了这天下无狗的关键...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
   }
   else
   {  
	  me->delete_temp("wugou/yanlian");
      j = 25;
      if(me->query("m-card-vip")) j =  20;
      if(me->query("y-card-vip")) j =  18;
      if(me->query("buyvip"))     j =  15;
	  i= random(j);	
     
	if(i< 2
		&& random(me->query("int"))>40
		&& random(me->query("kar"))>28)
	 {
		tell_object(me,HIY"\n\n你演练良久，忽然间豁然开朗，天下无狗的招式尽在你胸中纵横捭阖！\n恭喜你历尽千辛万苦，终于得偿所愿，将这天下无狗的招式融汇贯通! \n"NOR);
       	me->set("quest/gb/dgb/wugou/pass",1);
		me->set("title",HIY"丐帮"HIR"·天下无狗"NOR);
		me->set("quest/gb/dgb/wugou/time",time());
		me->set("mytitle/quest/txwgtitle",HIY"丐帮"HIR"·天下无狗"NOR);
		me->start_busy(1);
		log_file("quest/dgbwugou", sprintf("%8s(%8s) 失败%d次后，彻底天下无狗绝技。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/gb/dgb/wugou/fail"),i,me->query("combat_exp")) );
		set("over",1);
	   fuben_reset();
	 }
	 else
	 {
		me->add("quest/gb/dgb/wugou/fail",1);
		me->set("quest/gb/dgb/wugou/time",time());
		 
		tell_object(me,HIY"\n\n你听了洪七公的指点，虽然看见了天下无狗的奥秘，可是对棒诀如何和招式融汇贯通的真正奥妙全然不得要领。\n\n"NOR);
		tell_object(me,HBBLU+HIW"\n\n解密天下无狗绝技失败，再接再厉。\n\n"NOR);
		me->start_busy(1);
		me->delete_temp("wugou");
		log_file("quest/dgbwugou", sprintf("%8s(%8s) 打狗棒天下无狗解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/gb/dgb/wugou/fail"),i,me->query("combat_exp")) );
	}
	message_vision(HIY"\n\n当你从顿悟中醒来，豁然发现，四周一片寂静。\n"NOR,me);
	tell_object(me,HIR"\n\n欧阳锋和洪七公两人已然同时委顿在地，双目紧闭，面如死灰，一动也不动了。\n\n"NOR);
	tell_object(me,HIR"原来二人已耗尽内力而死。立于两座新坟之前不由感叹。\n\n"NOR);
	tell_object(me,HIR"义父和洪老老前辈居然由自己这无名小卒安葬于如此荒岭，真乃造化弄人。\n\n"NOR);
	tell_object(me,HIR"人死了，天大的功名利禄又有何用呢? \n\n"NOR);
	tell_object(me,HIR"北丐西毒数十年来反覆恶斗，互不相下，岂知竟同时在华山绝顶归天。\n\n"NOR);
	tell_object(me,HIR"\n\n你长叹一声，你只有黯然下山。\n\n"NOR);
	if (objectp(feng)) destruct(feng);
    if (objectp(hong)) destruct(hong);
	me->delete_temp("wugou/yanlian");
	set("over",1);
	fuben_reset();	
    return 1;
  }
}

//蛤蟆功的演示指令

int do_yanshi(string arg)
{
	    object* ppl;
        object me = this_player();
        object hong = this_object();
        object feng;
	      int i, time, total, j, h = 0;

		ppl = users();
		
		i = me->query("combat_exp") - 500000;
		i /= 500000;

		
        feng = present("ouyang feng", environment(me));

         j = sizeof(ppl);      

		while(j--){
			if( userp(ppl[j]) && !wizardp(ppl[j]) && !(ppl[j]->query("no_pk")) && ppl[j]->query("quest/hama/nizhuan/pass") )
			{
			  h++;
			}
          }
		if (h>0)
		{
			return notify_fail("对不起，现在有非洗手玩家在线，没有名额了，\n");
		}
		if (!arg||arg !="灵蛇杖法")
		{
			return notify_fail("你要给洪七公演示什么本事？鬼画符么？。\n");
		}
		if (me->query_skill("lingshe-zhangfa",1)< 500)
			return notify_fail("你的灵蛇杖法等级太低了，500级要求，无法领悟这门技能。\n");
		if (me->query_skill("hamagong",1)< 500)
			return notify_fail("你的蛤蟆功等级太低了，500级要求，无法领悟这门技能。\n");

		if (me->query("family/family_name")=="丐帮")
			return notify_fail("欧阳锋最恨丐帮弟子，来此莫非是想谋害欧阳锋么？\n");
		if (me->query("family/family_name")=="天龙寺")
			return notify_fail("欧阳锋最恨大理弟子，来此莫非是想谋害欧阳锋么？\n");
		
		if (me->is_busy()||me->is_fighting())
		{
			return notify_fail("你正在忙碌中!\n");
		}
		if (me->query("quest/hama/nizhuan/pass"))
			return notify_fail("你已经解开蛤蟆功逆转谜题，来此作甚？\n");
		if ((time()-me->query("quest/hama/nizhuan/time"))<86400)
			return notify_fail("你真是太勤快了，下次再来？\n");
		if (me->query("con")<40)
			return notify_fail("蛤蟆功需要绝高的根骨，你这点根骨是领悟不了蛤蟆功逆转的！\n");
		
		if (me->query_temp("hama/super"))
			return notify_fail("你正在演练灵蛇杖法绝技过程中？\n");
		
		//if(me->query("quest/gb/dgb/wugou/fail")>=3 && me->query("registered")<3)
		//{
		//	tell_object(me,"已经多次传授，你怎么都还没有领悟,真够笨的！");
		//	return 1;
		//}
		//!me->query("oyf_son") || 
		if (me->query("oyf/hamagong") != 2 )
		{
			return notify_fail("对不起，你尚未获得欧阳锋再次传授，来此作甚？\n");
		}
		me->start_busy(99);
		call_out("thinking_hm",1,me,hong,feng);              
        return 1;
}


int thinking_hm(object me,object hong,object feng)
{
   int i,j;

  if(me->query_temp("hama/super")<(10+random(5)))
  { 
	  me->add_temp("hama/super",1);
      if(random(2)) tell_object(me,HIY"\n你认真回想着方才洪七公和欧阳锋战斗中所展现的一招一式...\n"NOR);
             else tell_object(me,HIG"\n突然间，你似乎抓到了这万蛇噬体的关键...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  remove_call_out("thinking_hm");
	  call_out("thinking_hm",3+random(3), me);
   }
   else
   {  
	  me->delete_temp("hama/super");
      j = 25;
      if(me->query("m-card-vip")) j =  20;
      if(me->query("y-card-vip")) j =  18;
      if(me->query("buyvip"))     j =  15;
	  i= random(j);	
     
	if(i<2
		&& random(me->query("con"))>40
		&& random(me->query("kar"))>28)
	 {
		tell_object(me,HIY"\n\n你演练良久，忽然间豁然开朗，万蛇噬体的招式尽在你胸中纵横捭阖！\n恭喜你历尽千辛万苦，终于得偿所愿，将这万蛇噬体的招式融汇贯通! \n"NOR);
       	tell_object(me,HIG"只间你义父和洪老前辈弹出一丈多远，面容煞白,你义父不信洪七公的武功会强过他，直嚷着还要继续比武。\n\n"NOR);
		tell_object(me,HIG"三两句话激得洪七公要教你「打狗棒法」，再由你去演练给义父见识。\n\n"NOR);
		tell_object(me,HIG"欧阳锋看过之后，立即教给你过破解之道，并让他演练给洪七公看。洪七公见棍法遭破解，随即又教了新的招式…。\n\n"NOR);
		tell_object(me,HIG"如此一来一往历经了两个时辰，欧阳锋已接连破了洪七公三十多招，你则从中坐收渔人之利。\n\n"NOR);
		tell_object(me,HIG"洪七公把你叫到身边，讲解他的「天下无狗」，你义父冥思半晌说道:为父把生平绝学最后一试传授与你，方可以破解这「天下无狗」。\n\n"NOR);
		tell_object(me,HIG"洪七公见欧阳锋破解了他的「天下无狗」，激动得强撑着挨到欧阳锋跟前，出人意表的美言他几句。\n\n"NOR);
		tell_object(me,HIG"欧阳锋被这突如其来的举动一激，登时想起自己就是西毒欧阳锋，而眼前则正是老仇家北丐洪七公。\n\n"NOR);
		tell_object(me,HIG"二老会心相拥并狂笑…。\n\n"NOR);
		tell_object(me,HIM"你从洪七公和欧阳峰的战斗中获益菲浅。\n"NOR,me);
		tell_object(me,HIR"\n\n你成功领会义父的蛤蟆功,你的功夫提高了！\n"NOR,me);
		me->add("combat_exp",(30000+random(20000)));
		me->add("oyf/hamagong",1);
		me->set("title",HIW"白驼山庄"BLU"西毒"HIW"·逆九阴"NOR);
		me->set("mytitle/quest/xidutitle",HIW"白驼山庄"BLU"西毒"HIW"·逆九阴"NOR);
		
		me->set("quest/hama/nizhuan/pass",1);
		me->set("quest/hama/nizhuan/time",time());
		me->start_busy(1);
		log_file("quest/hmgsuper", sprintf("%8s(%8s) 失败%d次后，学会逆转九阴绝技。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/hama/nizhuan/fail"),i,me->query("combat_exp")) );		
	 }
	 else
	 {
		me->add("quest/hama/nizhuan/fail",1);
		me->set("quest/hama/nizhuan/time",time());
		me->set("oyf/hamagong",2);//防止bug
		 
		tell_object(me,HIY"\n\n你听了欧阳锋的指点，虽然看见了万蛇噬体和逆转九阴后的奥秘，可是功法融汇贯通的真正奥妙全然不得要领。\n\n"NOR);
		tell_object(me,HBBLU+HIW"\n\n解密万蛇噬体和逆转九阴绝技失败，再接再厉。\n\n"NOR);
		me->start_busy(1);
		me->delete_temp("hama/super");
		log_file("quest/hmgsuper", sprintf("%8s(%8s) 逆转九阴绝技解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/hama/nizhuan/fail"),i,me->query("combat_exp")) );
	}
	message_vision(HIY"\n\n当你从顿悟中醒来，豁然发现，四周一片寂静。\n"NOR,me);


	tell_object(me,HIR"\n\n欧阳锋和洪七公两人已然同时委顿在地，双目紧闭，面如死灰，一动也不动了。\n\n"NOR);
	tell_object(me,HIR"原来二人已耗尽内力而死。立于两座新坟之前不由感叹。\n\n"NOR);
	tell_object(me,HIR"义父和洪老前辈居然由自己这无名小卒安葬于如此荒岭，真乃造化弄人。\n\n"NOR);
	tell_object(me,HIR"人死了，天大的功名利禄又有何用呢? \n\n"NOR);
	tell_object(me,HIR"北丐西毒数十年来反覆恶斗，互不相下，岂知竟同时在华山绝顶归天。\n\n"NOR);
	tell_object(me,HIR"\n\n你长叹一声，你只有黯然下山。\n\n"NOR);
	
	set("over",1);
	me->unconcious();
	me->delete_temp("hama/super");
	fuben_reset();
	
    
	//me->add("quest/hama/super",1);
	//me->set("quest/hama/time", time());
    
    return 1;
  }

}
