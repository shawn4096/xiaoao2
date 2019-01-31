// Room: /d/huashan/sheshen.c
// Date: Look 99/03/25
// add 九阳神功 by sohu
#include <ansi.h>
#define QUESTYT1 "quest/倚天屠龙记/华山之巅/"
inherit ROOM;

int fight1(object me,object yinkexi,object xiaoxiang);

void create()
{
        set("short", "舍身崖");
 set("long", @LONG
这是一段极窄极险的山崖，四周云雾飞绕，下面渊深无底。如不小心，一
失足掉下去，只怕连骨头都找不到。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "eastdown" : __DIR__"canglong",
 ]));

 set("no_die", 1);
        set("no_clean_up", 0);
        set("outdoors", "华山" );

        set("coor/x",60);
  set("coor/y",50);
   set("coor/z",70);
   setup();
}
void init()
{
        object yinkexi,xiaoxiang;
		object me;
		me=this_player();
		//me->start_busy(2);
		if ((me->query_temp(QUESTYT1+"start")) && (!me->query(QUESTYT1+"over")))
		{
			if (!present("yin kexi",environment(me)))
			{
				yinkexi=new("d/kunlun/npc/yinkexi");
				yinkexi->move(environment(me));
			}
			if (!present("xiaoxiang zi",environment(me)))
			{
				xiaoxiang=new("d/kunlun/npc/xiaoxiangzi");
				xiaoxiang->move(environment(me));
			}
			call_out("fight1",0,me,yinkexi,xiaoxiang);

		}
		add_action("do_climb","climb");

}

int fight1(object me,object yinkexi,object xiaoxiang)
{
	
	
	
	
	message_vision(HIY"忽然从远处慌慌张张跑来二人，一个是西域大贾尹克西，另外一个是湘西名宿潇湘子！”\n"+
		"令人奇怪的是这二人竟然随身带了个大猴子。尹克西和潇湘子见到你在现场，相当紧张！\n"NOR,me);

		if (!objectp(yinkexi) || !objectp(xiaoxiang))  
{	
      call_out("fail",1,me);
     notify_fail("关键人物死亡，任务失败。\n");
    
}



		
	yinkexi->add_temp("apply/dodge",200);
	yinkexi->add_temp("apply/parry",200);
	yinkexi->add_temp("apply/defense",200);
	xiaoxiang->add_temp("apply/dodge",200);
	xiaoxiang->add_temp("apply/parry",200);
	xiaoxiang->add_temp("apply/defense",200);
	//yinkexi->fight_ob(xiaoxiang);
	//xiaoxiang->fight_ob(yinkexi);
	message_vision(HIC"\n尹克西说道“潇湘兄，这华山林深山密，到处可以藏身。咱们好好的躲上几日， \n算那秃驴神通如何广大，也未必能寻得到。待他到别地寻找，咱们再 往西去。”"NOR,me);
	message_vision(HIG"\n潇湘子阴测测的说道：“尹兄且莫喜欢，这秃驴倘若寻咱们不着，定然守在山下孔道之处。\n咱们若是贸然下去，正好撞在他的手里。””\n"NOR,me);
	message_vision(HIC"\n尹克西道：“潇湘兄深谋远虑，此言不差，却不知有何高见。”\n"NOR,me);
	message_vision(HIG"\n潇湘子道：“我想这山上寺观甚多，咱们便拣一处荒僻的，不管主持是和尚 还是道士，\n都下手宰了，占了寺观，便这么住下去不走啦。那秃驴决计想不到咱们会在山上穷年累月的停留。\n他再不死心，在山中搜寻数遍，在山下守候数月，也该去了。”\n"NOR,me);
	message_vision(HIC"\n尹克西喜道：“潇湘兄此计大妙。”\n潇湘子忙道：“禁声！”\n"NOR,me);
	
	me->set(QUESTYT1+"start",1);
	
	call_out("jueyuan_come",2+random(3),me,yinkexi,xiaoxiang);
	return 1;
}
int jueyuan_come(object me,object yinkexi,object xiaoxiang)
{
	object jueyuan;
	if (!objectp(jueyuan=present("jueyuan dashi",environment(me))))
	{
		jueyuan=new("d/shaolin/npc/jueyuan");
		jueyuan->move(environment(me));
	}
	message_vision(HIY"忽听得山腰里$n喝道：“借书不还的两位朋友，请现身相见！”这两句喝声只震得满山皆响，\n显是内力充沛之极，虽不威猛高昂，但功力之淳，竟是不弱。\n"NOR,me,jueyuan);

	message_vision(HIY"\n$N一惊，心想：“世上竟尚有这样一位高手，我却不知！”$N略略探身，往呼喝声传来处瞧去，\n月光下只见一道灰影迅捷无伦的奔上山来。过了一会，看清楚灰影中共有两人，一个灰袍僧人，携着一个少年。”\n"NOR,me);
	message_vision(HIY"\n尹克西和潇湘子二人缩身在长草丛中，连大气也不敢透一口气。\n"NOR,me);
	message_vision(HIY"\n那$n奔到高岗左近，四下张望，不见潇、尹二人的踪迹，当即向西峰疾奔而去。\n"NOR,me,jueyuan);
	message_vision(HIC"\n眼见那$n竟然要路过而去，你有心喊他一声，"HIR"喊（yell）"HIC"还是不喊？",me,jueyuan);
	add_action("do_yell","yell");
	me->delete_temp(QUESTYT1+"start");
    return 1;

}

int do_yell(string arg)
{
	object me;
	me=this_player();
	if (!arg||!me->query(QUESTYT1+"start")) return notify_fail("在这荒山野岭的，你瞎喊什么？");
	if (arg=="觉远大师")
	{
		message_vision(HIC"$N急忙冲远处的觉远和尚喊道，“喂，觉远和尚，那两人便在此处！”\n"NOR,me);
		message_vision(HIB"话音刚落，忽然远处传来暗器袭来的声音！显然是潇、尹二人想杀人灭口！\n"NOR,me);

		if (random(me->query_skill("dodge",1))<200)
		{
			message_vision(HIR"$N不小心被暗器打中！\n"NOR,me);
			me->receive_wound("qi",-random(3000),"暗器射");
			return 1;
		}else {
			message_vision(HIG"$N轻轻挥手拨落飞来的暗器，然后运起内功冲远处喊道。\n"NOR,me);
			me->set(QUESTYT1+"yelljueyuan",1);
			return 1;
		}

	}
	if (arg=="有缘千里来相会,无缘对面不相逢!" )
	{
		if (!me->query(QUESTYT1+"yelljueyuan")) return notify_fail("你冲远处喊道，“有缘千里来相会,无缘对面不相逢!”\n");
		
		message_vision(HIC"$N运足内力冲远处的觉远和尚逐字喊道，“有缘千里来相会,无缘对面不相逢！”\n"NOR,me);
		message_vision(HIY"\n\n那觉远和尚正走在山腰之间，立时停步，回头说道： “有劳高人指点迷津。”！\n"NOR,me);
		me->set(QUESTYT1+"yellyouyuan",1);
		return 1;
	}
	if (arg=="踏破铁鞋无觅处,得来全不费功夫!" )
	{
		if (!me->query(QUESTYT1+"yellyouyuan")) return notify_fail("你冲远处喊道，“有缘千里来相会,无缘对面不相逢!”\n");

		message_vision(HIC"$N运足内力冲远处的觉远和尚逐字喊道，“踏破铁鞋无觅处,得来全不费功夫!”\n"NOR,me);
		message_vision(HIY"\n\n那觉远和尚大喜，携了那少年飞步奔回！\n"NOR,me);
		me->set(QUESTYT1+"yelltiexie",1);
		message_vision(HIG"\n\n潇湘子和尹克西听了$N的长吟之声，这一惊非同小可，相互使个眼色，从草丛中蹿了出来，向东便奔。\n"NOR,me);
		message_vision(HIC"$N一看不好，这二人想溜走，你是"HIR"阻拦(zulan)"HIC"还是不阻拦？\n"NOR,me);
		add_action("do_zulan","zulan");
		return 1;
	}
}

int do_zulan()
{
	object me,yinkexi,xiaoxiang;
	int zulan;
	me=this_player();
	me->start_busy(1);
	me->set("quest/倚天屠龙记/华山之巅/time",time());
	if (!me->query(QUESTYT1+"yelltiexie")) return notify_fail("你无缘无故，要阻拦什么？");
	//if (me->query(QUESTYT1+"zulan")-zulan>1) return notify_fail("你已经阻拦过一次了,下次再来。\n");
	if (time()-me->query("quest/倚天屠龙记/time")<86400)
		return notify_fail("你来的太勤快了，隔日再来。\n");

	if (!objectp(yinkexi=present("yin kexi",environment(me))))
	{
		yinkexi=new("d/kunlun/npc/yinkexi");
		yinkexi->move(environment(me));
	}
	if (!objectp(xiaoxiang=present("xiaoxiang zi",environment(me))))
	{
		xiaoxiang=new("d/kunlun/npc/xiaoxiangzi");
		xiaoxiang->move(environment(me));
	}
	zulan=me->query(QUESTYT1+"zulan");
	me->add(QUESTYT1+"zulan",1);
	
	yinkexi->kill_ob(me);
	//me->fight_ob(yinkexi);
	xiaoxiang->kill_ob(me);
	//me->fight_ob(xiaoxiang);
	call_out("fight_over",10+random(5),me,yinkexi,xiaoxiang);
	return 1;
}

int fight_over(object me,object yinkexi,object xiaoxiang)
{
	
	
	if (!me) return 1;
	if (!yinkexi)
	{
		tell_object(me,YEL"你失手杀死了尹克西，无法完成后续昆仑山较量环节，任务失败！\n"NOR);
		call_out("fail",1,me);
		return 1;
	}
	if (!xiaoxiang)
	{
		tell_object(me,YEL"你失手杀死了潇湘子，无法完成后续昆仑山较量环节，任务失败！\n"NOR);
		call_out("fail",1,me);
		return 1;
	}
	if (!objectp(present("jueyuan dashi",environment(me))))
	{
		tell_object(me,YEL"觉远大师不再该处，无法完成后续少林环节，任务失败！\n"NOR);
		call_out("fail",1,me);
		return 1;
	}
	if (!me->is_fighting())
	{
		tell_object(me,YEL"你处置不当，使得战斗没有引起觉远大师的指点，任务失败！！\n"NOR);
		call_out("fail",1,me);
		return 1;

	}
	message_vision(CYN"觉远大师喊道，“$N难道不会使用”四通八达“、”鹿死谁手”、”推心置腹“这三招么？\n"NOR,me);
	tell_object(me,WHT"在觉远大师的指点下，你经过苦战，终于打败了这两位武林名宿！\n"NOR);
	
	yinkexi->apply_condition("neishang",10);
	yinkexi->remove_target();
	xiaoxiang->apply_condition("neishang",10);
	xiaoxiang->remove_target();

	tell_object(me,WHT"这二人受伤在地不起，气喘吁吁！\n"NOR);
	tell_object(me,WHT"在觉远大师和众人提示下，你将这二人搜了身，却没有发现任何觉远大师所说的经书！\n"NOR);
	tell_object(me,HIY"只是令人奇怪的是，这二人身边的那只健硕的大猴子却有些低沉的呻吟传来！\n"NOR);

	call_out("leave",3+random(5),me,yinkexi,xiaoxiang);
	return 1;

}

int leave(object me,object yinkexi,object xiaoxiang)
{
	object jueyuan;
	if (objectp(jueyuan=present("jueyuan dashi",environment(me))))
		destruct(jueyuan);
	if (objectp(yinkexi=present("yin kexi",environment(me))))
		destruct(yinkexi);
	if (objectp(xiaoxiang=present("xiaoxiang zi",environment(me))))
		destruct(xiaoxiang);
	message_vision(HIC"眼见觉远和尚所提到经书没有搜到，于是都相继离去。\n"+
		"尹克西和潇湘子二人躺在地上呻吟不已，你有心杀了二人，但却又不甚忍心。\n"NOR,me);
	message_vision(HIG"\n\n\n此时，尹克西和潇湘子相互扶持，向西蹒跚而去。\n"NOR,me);
	
	if (me->query(QUESTYT1+"over")) return 1;
	
	me->set(QUESTYT1+"over",1);
	me->set("quest/倚天屠龙记/time",time());
	me->set("quest/倚天屠龙记/combat_exp",me->query("combat_exp"));
	me->delete_temp(QUESTYT1+"start");
	log_file("quest/YTTLJ", sprintf("%s(%s) 顺利解开<<倚天屠龙记>>中第一章节华山之巅，总共失败%d次。富源：%d；经验：%d。\n",   
          me->name(1),
          me->query("id"), 
          me->query(QUESTYT1+"fail"),
          me->query("kar"),
          me->query("combat_exp")) );

	tell_object(me,HBBLU+HIW"\n\n\倚天屠龙记之第一章节《华山之巅》篇结束。\n"NOR);
	//me->add("combat_exp",);
	return 1;
}
int fail(object me)
{
	if (!me) return 1;
	me->add(QUESTYT1+"fail",1);
	me->set("quest/倚天屠龙记/time",time());
	me->set(QUESTYT1+"combat_exp",me->query("combat_exp"));
	me->delete_temp(QUESTYT1+"start");
	me->delete(QUESTYT1+"start");
	log_file("quest/YTTLJ", sprintf("%s(%s) 解密<<倚天屠龙记>>中第一章节华山之巅环节失败%d次。富源：%d；经验：%d。\n",   
          me->name(1),
          me->query("id"), 
          me->query(QUESTYT1+"fail"),
          me->query("kar"),
          me->query("combat_exp")) );
	return 1;
	
}

int do_climb(string arg)
{
        object me = this_player();
        int time;
	
		if (me->query("oyf/hamagong") == 2)
		{
			time = time() - me->query("quest/hama/nizhuan/time");
		}else if (me->query_temp("wugou/askguo"))
		{
			time = time() - me->query("quest/gb/dgb/wugou/time");
		}
				
        if (arg!="up") 
			return notify_fail(HIG"这个方向没办法爬。\n"NOR);

        if (me->query_skill("dodge",1) < 450)
			return notify_fail(HIG"你基本轻功不足450，爬了半天毫无进展，还是回去练练轻功在来吧。\n"NOR);
        
        
        if (me->query("oyf/hamagong") < 2 && !me->query_temp("wugou/askguo"))
			return notify_fail(HIG"你既不是丐帮弟子，又不是蛤蟆功传人，还是死了这条心吧。\n"NOR);     

        if (me->query("oyf/hamagong") == 3 || me->query("quest/gb/dgb/wugou/pass"))
			return notify_fail(HIG"华山绝顶的秘密你已经解开了，无需再爬了。\n"NOR);     

/*	 if (me->query("quest/jiebai/super") >=3 && me->query("registered") < 3)
        return notify_fail(HIG"你义父都死了多年了，不要来这伤心地了。\n"NOR);  
*/
      
		if ( time < 86400 )
	
        return notify_fail(HIG"你来的太勤了些吧。\n"NOR);  
        if ( me->query("combat_exp") < 6000000 ) 
        return notify_fail(HIG"你经验不足6m,来了也没有用。\n"NOR);  
        
        if (me->query("jingli") < 1500)
        return notify_fail(HIG"你精神不足1500，还是歇歇再爬吧，小心送了小命！\n"NOR);

        me->add("jingli",-500);

        message_vision(HIG"$N手脚并用，使出了吃奶的力气终于爬了上来。\n"NOR,me);
        me->move("/d/huashan/hamasuperquest/jueding1");
        return 1;
}

