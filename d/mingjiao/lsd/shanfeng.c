///u/qingyun/lsd/shanfeng.c
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", YEL"ɽ��"NOR);
	set("long", @LONG
����ɽ�¶��У��򱱶�����һ��ɽ�壬ɽ�����������ߵ��ı�������ɽ��
֮�������Կ���һ��������é�ݡ�
LONG);
	set("exits", ([
	  	"southdown" : __DIR__"sfjiao",
	]));
	/*
	set("objects",([
                CLASS_D("mingjiao") + "/huiyue" : 1,
                CLASS_D("mingjiao") + "/liuyun" : 1,
                CLASS_D("mingjiao") + "/miaofeng" : 1,
	]));
	*/
	set("outdoors","���ߵ�");
	setup();
}
int init()
{
	object me=this_player();
	
	if (me->query_temp("quest/mj/shlf/zhang") )
	{
		message_vision(HIC"$N������ȥ����Ȼ����ɽ�崦����һƬߺ�ȵ�������\n�������ƺ��������ڴ򶷣�\n"NOR,me);
		call_out("weigong_xie",3+random(3),me);	
		add_action("do_jiejiu","help");
	}
}
//�����ڡ���
int weigong_xie(object me)
{
	object xie,huiyue,liuyun,miaofeng;
	
	if (!objectp(xie=present("xie xun",environment(me))))
	{
		xie=new("kungfu/class/mingjiao/xie2");
		xie->move(this_object());
	}
	if (!present("huiyue shi",environment(me)))
	{
		huiyue=new("kungfu/class/mingjiao/huiyue");
		huiyue->move(this_object());
	}
	if (!present("liuyun shi",environment(me)))
	{
		liuyun=new("kungfu/class/mingjiao/liuyun");
		liuyun->move(this_object());
	}
	if (!present("miaofeng shi",environment(me)))
	{
		miaofeng=new("kungfu/class/mingjiao/miaofeng");
		miaofeng->move(this_object());
	}
	huiyue->kill_ob(xie);
	miaofeng->kill_ob(xie);
	liuyun->kill_ob(xie);
	return 1;

}
int check_fight(object me)
{
	object xie,huiyue,miaofeng,liuyun;
	if (!me) return 0;
	if (present("huiyue shi",environment(me)))
	{
		huiyue=present("huiyue shi",environment(me));
	}

	if (present("liuyun shi",environment(me)))
	{
		liuyun=present("huiyue shi",environment(me));
		
	}
	if (present("miaofeng shi",environment(me)))
	{
		miaofeng=present("huiyue shi",environment(me));
		
	}
	if (present("xie xun",environment(me)))
	{
		xie=present("xie xun",environment(me));
	}
	if (!objectp(xie))
	{
		return notify_fail("���̽�ëʨ��лѷ�Ѿ�����˹��ʹ��ɱ,����ʧ�ܣ�\n");
	}
	if (!me->is_fighting() && objectp(xie)&&!objectp(huiyue)&&!objectp(miaofeng)&&!objectp(liuyun))
	{
		message_vision(HIC"$N�������Ĳ��������ڽ���˹��ʹɱ������лѷ��ȳ�����\n"
							+"���ڿ��Ի�ȥ�����������ˡ�\n"NOR,me);
		me->set("quest/mj/shlf/helpxie",1);
		me->delete_temp("quest/mj/shlf/zhang");
		
		destruct(xie);
		return 1;
	}
	call_out("check_fight",2,me);
	

}

int do_jiejiu(string arg)
{
	object me=this_player();
	object xie,huiyue,liuyun,miaofeng;

	if (!arg||arg !="лѷ")
	{
		return notify_fail("��Ҫ��˭��\n");
	}
	if (!objectp(xie=present("xie xun",environment(me))))
	{
		return notify_fail("���̽�ëʨ��лѷ�Ѿ�����˹��ʹ��ɱ,����ʧ�ܣ�\n");
	}
	message_vision(HIC"$N��лѷ����Ϊ��˹��ʹΧ���������쳣Σ�գ��������֣��ȵ�����л������ţ����������ˡ���\n"NOR,me);
	message_vision(HIY"\n\nлѷ��$N�ȵ���������λ������лѷ��ʤ�м�!����\n"NOR,me);
	message_vision(HIG"\n\n$N�ش����л��������ģ����˴�������Ž�������"+me->query("name")+HIG"��Ҳ!���Ž���֮������Э������!��\n"NOR,me);
	
	
	if (objectp(huiyue=present("huiyue shi",environment(me))))
	{
		huiyue->kill_ob(me);
		me->kill_ob(huiyue);
	}
	if (objectp(liuyun=present("liuyun shi",environment(me))))
	{
		liuyun->kill_ob(me);
		me->kill_ob(liuyun);
	}
	if (objectp(miaofeng=present("miaofeng shi",environment(me))))
	{
		miaofeng->kill_ob(me);
		me->kill_ob(miaofeng);
	}
	
	call_out("check_fight",1,me);
	return 1;

}