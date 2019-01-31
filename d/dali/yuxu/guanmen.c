// Modify By River 98/12
inherit ROOM;
#include <ansi.h>

void create()
{
	set("short", "玉虚观门");
	set("long", @LONG
走到近处，见那黄墙原来是所寺观，匾额上写的似乎是‘玉虚观’三字，
黄墙红瓦，这观看起来很是简陋，门口站着两个小道童。

LONG
	);
	set("outdoors", "大理");
	set("exits", ([ /* sizeof() == 1 */
		"enter" : __DIR__"yuxuguan",
		"east" : "/d/group/entry/dlndao5",
        ]));
	set("objects", ([
		__DIR__"npc/daotong" : 2 
	]) );

	setup();
}

void init()
{
    object yzh,fsg,room;
	object me=this_player();	

    if (me->query_temp("yyzhi/first"))
    {
		me->delete_temp("yyzhi/first");//防止反复触发
		
		if (!objectp(yzh=present("yunzhong he",environment(me))))
        {
		      yzh=new("/d/dali/wuliang/npc/yunzhonghe");
		      yzh->move(environment(me));
		}
		message_vision(HIG"\n一个竹竿子样的人忽然从外跃进来，色迷迷地笑道，本大爷这次可以捉到两个漂亮小妞。\n"NOR,me);
		if (!objectp(fsg=present("fu sigui",this_object())))
        {
			//room=load_object("/d/dali/wangfu/dating");
			
				message_vision(HIY"\n远处一个声音喝道，来的早不如来得巧，王妃无需慌张，某家来也！\n"NOR,me);
				fsg=new("d/dali/wangfu/npc/fusigui");
				fsg->move(environment(me));
			    message_vision(HIY"\n屋外传来一阵郎笑，“娘娘不用担心，某家来也！”，一位手拎熟铜棍的官差，随后跨进门来。\n"NOR,me);
				message_vision(HIG"\n\n傅思归抱拳向$N道，“官府办事，闲杂人等不要惹事，还是静观为妙，看我怎么收拾这四大恶人！”。\n"NOR,me);

        }
        yzh->kill_ob(fsg);
		fsg->kill_ob(yzh);
		me->delete_temp("yyz/first");
		
        remove_call_out("check_here");
        call_out("check_here",1,me,yzh,fsg);
    
   }

}
/*
int do_test(string arg)
{
	 object yuxu,room;
	 object me=this_player();
	    room=load_object("/d/dali/yuxu/yuxuguan");
		
		if (!present("yuxu sanren",room) && !present("yuxu sanren",environment(me)))
		{
			message_vision(HIY"\n这时，从观内传出一声清脆的声音道，四大恶人休要猖狂，我来会会你们！\n"NOR,me);
			yuxu=new("d/dali/yuxu/npc/yuxu");
			yuxu->move("/d/dali/yuxu/guanmen");
		}
		else if (present("yuxu sanren",room))
		{
			message_vision(HIY"\n这时，从观内传出一声清脆的声音道，四大恶人休要猖狂，我来会会你们！\n"NOR,me);
		    yuxu=present("yuxu sanren",room);	
			yuxu->move("/d/dali/yuxu/guanmen");
		}	
		else
			message_vision(HIY"\n玉虚散人就在面前了。\n"NOR,me);
}
*/
int check_here(object me,object yzh,object fsg)
{
	object yuxu,room;
	if (!yzh) return 0;
	
	if (yzh->is_fighting(fsg))
	{
		call_out("check_here",3,me,yzh,fsg);
		return 1;
	}
    if (!present("yuxu sanren",this_object()))
    {
		room=load_object("/d/dali/yuxu/yuxuguan");
		message_vision(HIY"\n这时，从观内传出一声清脆的声音道，四大恶人休要猖狂，我来会会你们！\n"NOR,me);
		if (!present("yuxu sanren",room) && !present("yuxu sanren",environment(me)))
		{
			message_vision(HIY"\n这时，从观内传出一声清脆的声音道，四大恶人休要猖狂，我来会会你们！\n"NOR,me);
			yuxu=new("d/dali/yuxu/npc/yuxu");
			yuxu->move("/d/dali/yuxu/guanmen");
		}
		else if (present("yuxu sanren",room))
		{
			message_vision(HIY"\n这时，从观内传出一声清脆的声音道，四大恶人休要猖狂，我来会会你们！\n"NOR,me);
		    yuxu=present("yuxu sanren",room);	
			yuxu->move("/d/dali/yuxu/guanmen");
		}	
		else
			message_vision(HIY"\n玉虚散人就在面前了。\n"NOR,me);
       
    }
    add_action("do_help","baohu");	
	message_vision(HIY"\n$N一见从玉虚观内走出一位绝代佳人，真是大理王妃玉虚散人！\n"NOR,me);
	message_vision(HIY"\n$N想起王爷的嘱咐，决定立即保护王妃"HIR"（baohu 王妃）！\n"NOR,me);

	yuxu->kill_ob(yzh);
	yzh->kill_ob(yuxu);
    return 1;

}

int check_yuxu(object me,object yzh,object yuxu)
{
	object fsg;
	if (!living(yuxu))
	{
		message_vision(HIC"玉虚散人为云中鹤所杀，任务失败,请回头继续再来。\n"NOR,me);
		me->add("quest/tls/yyz/start/fail",1);
		me->delete_temp("yyzhi");

		return 1;
	}
    if (yuxu->query("qi",1)<yuxu->query("max_qi",1)/2)
    {
		message_vision(HIG"云中鹤喋喋怪笑一声，伸手点中玉虚散人的穴道，横抱起来，转身向外飞跃而去。\n"NOR,me);
		tell_object(me,HIW"王妃被劫走，任务失败！\n"NOR);
		if (objectp(yuxu)) destruct(yuxu);
		if (objectp(yzh)) destruct(yzh);				
		
		me->add("quest/tls/yyz/start/fail",1);
		me->delete_temp("yyzhi");
		return 1;
    }
    if (!objectp(yzh)&& objectp(yuxu))
    {
   		tell_object(me,HIW"王妃解救成功！\n"NOR);
		tell_object(me,HIG"王妃听你说明来意，长叹一声道，既然如此，那好吧，告诉那个负心人，我一会就到。\n"NOR);
		if (objectp(yuxu)) destruct(yuxu);
		if (objectp(fsg=present("fusi gui",this_object()))) destruct(fsg);		
		me->set_temp("yyzhi/helpyuxu",1);
		me->set("quest/tls/yyz/start/helpwf",1);
		
		return 1;

    }
	remove_call_out("check_yuxu");
	call_out("check_yuxu",1,me,yzh,yuxu);

}


int do_help(string arg)
{
	object me,yuxu,yzh;
	me=this_player();
	yuxu=present("yuxu sanren",this_object());
	yzh=present("yunzhong he",this_object());
	if (!arg)
	{
		return notify_fail("你要救护谁？\n");
	}
	if (arg!="王妃")
	{
		return notify_fail("你不救护王妃，段王爷会很不高兴？\n");
	}
	
	message_vision(HIC"$N大声喝道，“王妃休要慌张，少要害怕，某家在此，料也无妨！”\n"NOR,me);
	message_vision(HIY"\n\n云中鹤喋喋地笑道，又来一个送人头的！”\n"NOR,me);
  if (yzh) yzh->kill_ob(me);
  {
	remove_call_out("check_yuxu");
	call_out("check_yuxu",3,me,yzh,yuxu);
	}

	return 1;
}