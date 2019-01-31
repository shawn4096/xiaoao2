// Room: xiangfang.c
// By River 98/12
#include <ansi.h>

inherit ROOM;
int do_help(string arg);
int check_task(object me);
int yun_come(object me);
int zhong_come(object me);


void create()
{
        set("short", "厢房");
        set("long", @LONG
这是内室厢房，四周布置一望便知是小姐的闺房。石桌石凳，颇有山野气
息，房里乱挂了些书画，一望可知主人是没有什么修养的。窗外盛开着一些野
山茶花，不远处的山石提醒你这是在一个山谷里。
LONG
        );
        set("exits", ([            
            "west" : __DIR__"keting",
        ]));

        set("objects", ([
              __DIR__"npc/gan_baobao" : 1,
        ]));
        
        setup();
}
void init()
{
     object me=this_player();
	 if (me->query_temp("yyzhi/helpgbb"))
	 {
		 add_action("do_help","baohu");
	 }

}
int do_help(string arg)
{
    object zhong,yun,gan,me;
	me=this_player();
	zhong=present("zhong wanchou",environment(me));
	yun=present("yun zhonghe",environment(me));
	gan=present("gan baobao",environment(me));
	if (!arg)
		return notify_fail("你要保护谁？\n");
	if (!me->query_temp("yyzhi/askgan"))
		return notify_fail("你吃饱了没事干，来到人家万劫谷充什么大头虾？\n");
	if (arg=="甘宝宝" && me->query_temp("yyzhi/askgan"))
	{
		message_vision(HIM"\n\n\n你说道，有我在，谁都不能伤害你！\n"NOR,me);
		call_out("yun_come",1,me);
		//call_out("zhong_come",1,me);
		
		return 1;
	}

}



int yun_come(object me)
{
		object zhong,yun,gan;
		zhong=present("zhong wanchou",environment(me));
		yun=present("yun zhonghe",environment(me));
		gan=present("gan baobao",environment(me));
		tell_object(me,HIR"\n\n\n忽听屋外一个阴测测的声音喊道，”这小娘们真心不错，可惜嫁给了那个丑鬼。“\n"NOR);
		tell_object(me,HIY"\n\n\n甘宝宝大吃一惊道，谁？？。“\n"NOR);
		if (!objectp(yun))
		{
			yun=new("d/dali/wuliang/npc/yunzhonghe");
			yun->move(environment(me));
			tell_object(me,HIC"\n\n\n云中鹤大喊一声，道，”原来你屋里居然藏了一个男人？还居然是一个小白脸？“\n"NOR);
			tell_object(me,HIG"\n\n\n云中鹤道，”与其便宜了别人还不如便宜我好了！“\n"NOR);
			

		}
		//yun->kill_ob(me);
		yun->kill_ob(gan);
		//gan->kill_ob(yun);
		yun->kill_ob(me);
		call_out("zhong_come",2,me,yun);
		return 1;


}

int zhong_come(object me)
{
		object zhong,yun,gan;
		zhong=present("zhong wanchou",environment(me));
		yun=present("yun zhonghe",environment(me));
		gan=present("gan baobao",environment(me));
		
		tell_object(me,HIR"\n\n\n忽听屋外又一个声音喊道，”谁？谁在我老婆的屋内？妈的，找死！。“\n"NOR);
		tell_object(me,HIC"\n\n\n甘宝宝心中更是大惊道，对你说道，你快走！。“\n"NOR);
		if (!objectp(zhong))
		{
			zhong=new("d/dali/wuliang/npc/zhong_wanchou");
			zhong->move(environment(me));
			tell_object(me,HIR"\n\n\n钟万仇大喊一声，道，”原来夫人你屋里居然藏了一个男人？还居然是一个小白脸？“\n"NOR);
			tell_object(me,HIR"\n\n\n钟万仇怒火万丈，对你喊道，给我去死吧，你这淫贼！“\n"NOR);

		}
		
		zhong->kill_ob(gan);
		zhong->kill_ob(me);
		call_out("check_task",1,me);
		return 1;

}
int check_task(object me)
{
	
	object zhong,yun,gan;
	me=this_player();
	zhong=present("zhong wanchou",environment(me));
	yun=present("yun zhonghe",environment(me));
	gan=present("gan baobao",environment(me));
	if (!objectp(gan)|| gan->query("qi") < gan->query("max_qi")/3)
	{
		
		me->delete_temp("yyzhi");
		me->set_temp("yyzhi/fail",1);
		me->delete_temp("yyzhi/askgan");
		tell_object(me,HIW"\n\n甘宝宝已经死亡，保护甘宝宝任务失败！\n"NOR);
		return 1;
	}
	if (!objectp(yun)&&!objectp(zhong) && objectp(gan)&&!me->is_fighting())
	{
		tell_object(me,HIW"\n\n经过一番苦战，终于将这些恶人杀死！\n"NOR);
		tell_object(me,HIW"\n\n甘宝宝神情极为沮丧，似乎甚是疲倦，待在哪儿一动不动！\n\n"NOR);
		tell_object(me,HIG"\n\n甘宝宝说道，这位大侠，你先回去吧，就说我现在已经是钟夫人了，不会再回去的！\n"NOR);
		tell_object(me,HIW"\n\n你见甘宝宝意甚坚决，也不好勉强，只得先返回面见王爷再说！\n"NOR);
		
		me->delete_temp("yyzhi");
		me->set_temp("yyzhi/helpgbbover",1);
		me->set("quest/tls/yyz/start/helpgbbover",1);
		return 1;
		
	}
	//remove_call_out("check_task");
	call_out("check_task",1,me);
	return 0;
}
