// Room: xting.c
// By River 98/12
inherit ROOM;
#include <ansi.h>

int ye_come(object me,object qhm);

void create()
{
        set("short", "����");
	set("long", @LONG
�����ǹ����������Ŀ�����Ϣ֮�ã�һӦ���߱�������һ��ƽ���Ų���
���ʣ�ǽ�Ϲ��ż���ɽˮ������������͸�������������ֱ�������
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
	if (!arg||arg!="ȷ��")
	{
		return notify_fail("����Ե�޹ʵ�Ϲ��Ӧʲô��\n");
	}
	me->set_temp("yyzhi/answeryes",1);
	message_vision(HIC"$Nˬ��Ķ�$n��ͷ����������˷��ģ�����֮ǰ��ү���⽻����Ҫ�ұ���"HIR"(baohu �غ���)"HIC"���㡱\n"NOR,me,qhm);
	call_out("ye_come",2+random(2),me,qhm);
	message_vision(HIB"��ʱ�����⴫��һ�������Ŀ��������ҵĶ�������������������������������������~~~~��\n"NOR,me);
	message_vision(HIB"����~�����Ķ�~~������Ϊ����~��\n"NOR,me);
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
	message_vision(HIY"\n������������Ц�����������ݵõ������£������ڣ��Ĵ����������Σ���\n"NOR,me);

	gao=present("gao shengtai",this_object());
	if (!gao)
	{
		gao=new("d/dali/npc/gaoshengtai");
		gao->move(this_object());
	}
	ye->kill_ob(qhm);
	ye->kill_ob(gao);
	message_vision(HIC"����̩�������������ܵ����������д�����Ӳ������ϰ����Ͻ������÷���"HIR"(baohu �غ���)"HIC"����\n"NOR,me);
	
}

int do_help(string arg)
{
	object me,qhm,ye,gao;
	me=this_player();
	if (!me->query_temp("yyzhi/answeryes"))
	{
		
		return notify_fail("������첲�ƺ���ӵ��ʲô�����˶���Ϊ���ǻ��գ�\n");
	}
	ye=present("ye erniang",this_object());
	gao=present("gao shengtai",this_object());
	qhm=present("qin hongmian",this_object());

    if (!me->query_temp("yyzhi/askqin"))
    {
		return notify_fail("����Ե�޹ʵ���ʲôçײ�������ˣ�\n");
    }
	if (!arg||arg!="�غ���")
	{
		return notify_fail("��ë��ë��Ҫˣ��å����\n");
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
		message_vision(HIC"�غ���ΪҶ������ɱ������ʧ��,���ͷ����������\n"NOR,me);
		me->add("quest/tls/yyz/start/fail",1);
		me->delete_temp("yyzhi");
		if (objectp(ye)) destruct(ye);
		if (objectp(gao=present("gao shengtai",this_object()))) destruct(gao);
		return 1;
	}
    if (qhm->query("qi",1)<qhm->query("max_qi",1)/2)
    {
		message_vision(HIG"Ҷ�����੹�Цһ�������ֵ����غ��޵�Ѩ�����ᱧ������ת�������Ծ��ȥ��\n"NOR,me);
		tell_object(me,HIW"�غ��ޱ����ߣ�����ʧ�ܣ�\n"NOR);
		if (objectp(qhm)) destruct(qhm);		
		if (objectp(ye)) destruct(ye);
		if (objectp(gao=present("gao shengtai",this_object()))) destruct(gao);
		me->add("quest/tls/yyz/start/fail",1);
		me->delete_temp("yyzhi");
		return 1;
    }
    if (!objectp(ye)&& objectp(qhm)&&!me->is_fighting())
    {
   		tell_object(me,HIW"�غ��޽�ȳɹ���\n"NOR);
		tell_object(me,HIG"�غ�������˵�����⣬��̾һ��������Ȼ��ˣ��Ǻðɣ������Ǹ������ˣ���һ��͵���\n"NOR);
		//if (objectp(qhm)) destruct(qhm);
		if (objectp(ye)) destruct(ye);
		if (objectp(gao=present("gao shengtai",this_object()))) destruct(gao);		
		me->set_temp("yyzhi/helpqhmover",1);
		me->set("quest/tls/yyz/start/helpqhmover",1);
		return 1;

    }
	call_out("check_fight",2,me);

}