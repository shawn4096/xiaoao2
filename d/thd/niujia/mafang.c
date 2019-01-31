// mafang.c
#include <ansi.h>
inherit ROOM;

string look_daocao();
#define QUESTDIR "quest/射雕英雄传/"

#define QUESTDIR1 "quest/射雕英雄传/风雪惊变/"
int do_fail(object me);

void create()
{
	set("short", "马房");
	set("long", @LONG
这是杨铁心家的后院的马房，马槽前面有个很大的水缸。
马槽左边堆满了很多稻草，平时堆的很整齐，今天不知道怎
么了，稻草(Daocao)堆的乱七八糟的。
LONG
	);

	set("exits", ([
		"south" : __DIR__"houyuan.c",
	]));
            set("objects",([
              // __DIR__"npc/wanyan": 1,
               	
            ]));
            
       set("item_desc",([
		"daocao"		:	(: look_daocao :),
	]));
		set_temp("available",1);
	setup();
}

void init()
{
	
	add_action("do_move", "move");
}
string look_daocao()
{
	this_player()->set_temp("quest/射雕英雄传/风雪惊变/lookdaocao",1);

	return "这是一大堆稻草，堆在墙脚边，不知是派什麽用场。\n";
}
int do_move(string arg)
{
//	string dir;
	object me,ob;
	me=this_player();

	if( !arg || arg=="" || !query_temp("available") ) return 0;
	if (arg!="daocao"||!me->query_temp("quest/射雕英雄传/风雪惊变/lookdaocao")) return notify_fail("你要挪动什么？\n");

	if( arg=="daocao" 
	&& me->query_temp(QUESTDIR1+"weihebao")	
	&& query_temp("available")) 
	{
		write("你试著把稻草慢慢移开，突然发现下面埋着个身受重伤的男人 !\n\n");
	    delete_temp("available");
		ob = new(__DIR__"npc/wanyan");
		
		
		ob->unconscious();
		ob->set("qi",-1);
		
		ob->move(__DIR__"mafang");
		
		remove_call_out("fainting");

		call_out("fainting", 100+random(20), me, ob);

		me->set_temp(QUESTDIR1+"findwanyan",1);

	}else
	{
		write("你试著把稻草慢慢移开，除了稻草下的一滩血迹外什么也没发现!\n\n");
		
	}

	return 1;
}

void fainting(object me, object ob)
{

		message_vision("那个男人缓缓苏醒了过来，对$N说道: 救、、我、、\n",me,ob);
		//me->dest(ob);
		add_action("do_help","baohu");
		add_action("do_help","jiuzhu");

	    return;
}

int do_help(string arg)
{
	object me,wanyan,bao;
	me=this_player();

	if (!me->query_temp(QUESTDIR1+"answerhelp"))
	{
		return notify_fail("完颜洪烈不相信你!\n");
	}

	if (!arg||arg!="完颜洪烈") return notify_fail("你要救谁？\n");
	if (me->query("quest/射雕英雄传/风雪惊变/救王爷"))
	{
		return notify_fail("你已经成功保护完颜洪烈王爷！\n");
	}
	if (time()-me->query("quest/射雕英雄传/time")<86400)
	{
		return notify_fail("今天你已经保护过完颜洪烈王爷一次了！\n");
	}
	wanyan=present("wanyan honglie",this_object());

	if (me->query_temp(QUESTDIR1+"answerhelpwanyan")
		&&me->query(QUESTDIR1+"notongyin"))
	{
		message_vision("完颜洪烈眼神极其无助，口干舌燥，对$N说道: 英雄救我，必不所负！\n",me);
		message_vision("\n$N对完颜洪烈说道，“王爷请放心，我这就开始救你！”\n",me);
		message_vision("\n$N开始替完颜洪烈包扎伤口，并给他喝了点水，此人伤势大为缓和！\n",me);
		wanyan->clear_condition("neishang");
		wanyan->clear_condition("liuxue");
		wanyan->add_temp("apply/armor",150);
		wanyan->add_temp("apply/defense",150);
		wanyan->add_temp("apply/parry",200);

		call_out("qiu_attack",3+random(4),me,wanyan);
	}
	return 1;
}
int qiu_attack(object me,object wanyan)
{
	object yang,guo,qiu;
	me=this_player();
	message_vision(HIR"\n\n屋外忽然传来丘处机的怒吼声，“孽障！知人知面不知心，你果然是间隙，居然在道爷眼皮子底下救助大金国王爷”！\n",me);
	if (!objectp(yang=present("yang tiexin",this_object())))
	{
		yang=new("d/thd/niujia/npc/yang");
		yang->move("d/thd/niujia/mafang");
	}
	if (!objectp(guo=present("guo xiaotian",this_object())))
	{
		guo=new("d/thd/niujia/npc/guo");
		guo->move("d/thd/niujia/mafang");
	}
	if (!objectp(qiu=present("qiu chuji",this_object())))
	{
		qiu=new("d/thd/niujia/npc/qiuchuji");
		qiu->move("d/thd/niujia/mafang");
	}
	if (!wanyan)
	{
		return notify_fail("完颜洪烈不在此地，被人所杀！\n");
	}
	yang->kill_ob(me);
	yang->kill_ob(wanyan);
	guo->kill_ob(me);
	guo->kill_ob(wanyan);
	qiu->kill_ob(me);
	qiu->kill_ob(wanyan);
	me->kill_ob(yang);
	me->kill_ob(guo);
	me->kill_ob(qiu);

	call_out("do_check",20+random(10),me,yang,guo,qiu,wanyan);
	return 1;
}

int do_check(object me,object yang,object guo,object qiu,object wanyan)
{
	if (!me) return 0;
	if (!objectp(wanyan))
	{
		tell_object(me,HBYEL+HIW"射雕sotry重要人物(完颜洪烈)没有得到有效保护，被刺身亡，任务失败，明天再来！\n"NOR);
		do_fail(me);
		return 1;

	}
	if (objectp(yang)||objectp(guo)||objectp(qiu))
	{
		tell_object(me,HBYEL+HIW"在规定时间内，没有保护好完颜洪烈，被刺身亡，任务失败，明天再来！\n"NOR);
		wanyan->die();

		do_fail(me);
		return 1;
	}
//	tell_object(me,HIG""NOR);
	tell_object(me,HBYEL+HIW"《射雕英雄传》故事情节之风雪惊变成功救助完颜洪烈第一次脱险，完颜洪烈对你表示招揽之意！\n"NOR);
	tell_object(me,HIG"完颜洪烈悄声对你说道，“我下一站途径嘉兴回国，壮士若一路护送，定当重谢！”\n"NOR);

	me->set_temp("quest/射雕英雄传/风雪惊变/救王爷",1);
	me->set("quest/射雕英雄传/风雪惊变/救王爷",1);
	destruct(wanyan);

	return 1;
}

int do_fail(object me)
{
	if (!me) return 1;
	
	me->add("quest/射雕英雄传/风雪惊变/fail",1);
	me->set("quest/射雕英雄传/time",time());
	tell_object(me,HBYEL+HIW"\n《射雕英雄传》故事情节之风雪惊篇救护完颜洪烈失败，完颜洪烈被杀！\n"NOR);
	tell_object(me,HBYEL+HIW"请24小时后再来！\n"NOR);

	return 1;
}