// Room: xting.c
// By River 98/12
inherit ROOM;
#include <ansi.h>

int ye_come(object me,object qhm);

void create()
{
        set("short", "西厅");
	set("long", @LONG
这里是供来无量剑的客人休息之用，一应茶点具备，窗边一溜平放着不少
锦凳，墙上挂着几幅山水画，几缕阳光透过窗外的绿荫中直射进来。
LONG
	);
	set("exits", ([ 
	    "east" : __DIR__"wlj",	    
        ]));
	set("objects", ([
        	"d/dali/wuliang/npc/qin_hongmian" : 1,
        ]));
	setup();
}
void init()
{
	if (this_player()->query_temp("yyzhi/helpqhm",1))
	{
		add_action("do_help","baohu");
		add_action("do_answer","answer");
	}
}
int do_answer(string arg)
{
	object me,qhm;
	qhm=present("qin hongmian",this_object());
	if (!qhm)
	{
		qhm=new("d/dali/wuliang/npc/qin_hongmian");
		qhm->move(this_object());
	}
	me=this_player();
	if (!arg||arg!="确认")
	{
		return notify_fail("你无缘无故的瞎答应什么？\n");
	}
	me->set_temp("yyzhi/answeryes",1);
	message_vision(HIC"$N爽快的对$n点头道，“请夫人放心，临行之前王爷特意交代，要我保护"HIR"(baohu 秦红棉)"HIC"好你”\n"NOR,me,qhm);
	call_out("ye_come",2+random(2),me,qhm);
	message_vision(HIB"这时，屋外传来一阵阴测测的哭声，“我的儿啊·················~~~~”\n"NOR,me);
	message_vision(HIB"儿啊~你在哪儿~~可想死为娘了~”\n"NOR,me);
	return 1;
}
int ye_come(object me,object qhm)
{
	object ye,gao;
	ye=present("ye erniang",this_object());
	if (!ye)
	{
		ye=new("d/dali/wuliang/npc/erniang");
		ye->move(this_object());
		
	}
	message_vision(HIY"\n屋外有人朗声笑道，“夫人休得担心受怕，有我在，四大恶人又能如何？”\n"NOR,me);

	gao=present("gao shengtai",this_object());
	if (!gao)
	{
		gao=new("d/dali/npc/gaoshengtai");
		gao->move(this_object());
	}
	ye->kill_ob(qhm);
	ye->kill_ob(gao);
	message_vision(HIC"高升泰喊道，“夫人受到攻击，所有大理弟子并肩子上啊，赶紧保护好夫人"HIR"(baohu 秦红棉)"HIC"！”\n"NOR,me);
	
}

int do_help(string arg)
{
	object me,qhm,ye,gao;
	me=this_player();
	if (!me->query_temp("yyzhi/answeryes"))
	{
		
		return notify_fail("你伸出胳膊似乎在拥抱什么，别人都以为你是花痴？\n");
	}
	ye=present("ye erniang",this_object());
	gao=present("gao shengtai",this_object());
	qhm=present("qin hongmian",this_object());

    if (!me->query_temp("yyzhi/askqin"))
    {
		return notify_fail("你无缘无故的做什么莽撞保护事宜？\n");
    }
	if (!arg||arg!="秦红棉")
	{
		return notify_fail("你毛手毛脚要耍流氓？？\n");
	}
  if (ye) ye->kill_ob(me);
	call_out("check_fight",1,me);
	return 1;
}
int check_fight(object me)
{
	object gao,ye,qhm;
	gao=present("gao shengtai",this_object());
	ye=present("ye erniang",this_object());
	qhm=present("qin hongmian",this_object());
	if (!objectp(qhm))
	{
		message_vision(HIC"秦红棉为叶二娘所杀，任务失败,请回头继续再来。\n"NOR,me);
		me->add("quest/tls/yyz/start/fail",1);
		me->delete_temp("yyzhi");
		if (objectp(ye)) destruct(ye);
		if (objectp(gao=present("gao shengtai",this_object()))) destruct(gao);
		return 1;
	}
    if (qhm->query("qi",1)<qhm->query("max_qi",1)/2)
    {
		message_vision(HIG"叶二娘喋喋怪笑一声，伸手点中秦红棉的穴道，横抱起来，转身向外飞跃而去。\n"NOR,me);
		tell_object(me,HIW"秦红棉被劫走，任务失败！\n"NOR);
		if (objectp(qhm)) destruct(qhm);		
		if (objectp(ye)) destruct(ye);
		if (objectp(gao=present("gao shengtai",this_object()))) destruct(gao);
		me->add("quest/tls/yyz/start/fail",1);
		me->delete_temp("yyzhi");
		return 1;
    }
    if (!objectp(ye)&& objectp(qhm)&&!me->is_fighting())
    {
   		tell_object(me,HIW"秦红棉解救成功！\n"NOR);
		tell_object(me,HIG"秦红棉听你说明来意，长叹一声道，既然如此，那好吧，告诉那个负心人，我一会就到。\n"NOR);
		//if (objectp(qhm)) destruct(qhm);
		if (objectp(ye)) destruct(ye);
		if (objectp(gao=present("gao shengtai",this_object()))) destruct(gao);		
		me->set_temp("yyzhi/helpqhmover",1);
		me->set("quest/tls/yyz/start/helpqhmover",1);
		return 1;

    }
	call_out("check_fight",2,me);

}