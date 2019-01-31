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
        set("short", "�᷿");
        set("long", @LONG
���������᷿�����ܲ���һ����֪��С��Ĺ뷿��ʯ��ʯ�ʣ�����ɽҰ��
Ϣ�������ҹ���Щ�黭��һ����֪������û��ʲô�����ġ�����ʢ����һЩҰ
ɽ�軨����Զ����ɽʯ������������һ��ɽ���
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
		return notify_fail("��Ҫ����˭��\n");
	if (!me->query_temp("yyzhi/askgan"))
		return notify_fail("��Ա���û�¸ɣ������˼���ٹȳ�ʲô��ͷϺ��\n");
	if (arg=="�ʱ���" && me->query_temp("yyzhi/askgan"))
	{
		message_vision(HIM"\n\n\n��˵���������ڣ�˭�������˺��㣡\n"NOR,me);
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
		tell_object(me,HIR"\n\n\n��������һ����������������������С�������Ĳ�����ϧ�޸����Ǹ������\n"NOR);
		tell_object(me,HIY"\n\n\n�ʱ������һ������˭��������\n"NOR);
		if (!objectp(yun))
		{
			yun=new("d/dali/wuliang/npc/yunzhonghe");
			yun->move(environment(me));
			tell_object(me,HIC"\n\n\n���к״�һ����������ԭ���������Ȼ����һ�����ˣ�����Ȼ��һ��С��������\n"NOR);
			tell_object(me,HIG"\n\n\n���к׵�������������˱��˻���������Һ��ˣ���\n"NOR);
			

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
		
		tell_object(me,HIR"\n\n\n����������һ��������������˭��˭�������ŵ����ڣ���ģ�����������\n"NOR);
		tell_object(me,HIC"\n\n\n�ʱ������и��Ǵ󾪵�������˵��������ߣ�����\n"NOR);
		if (!objectp(zhong))
		{
			zhong=new("d/dali/wuliang/npc/zhong_wanchou");
			zhong->move(environment(me));
			tell_object(me,HIR"\n\n\n������һ����������ԭ�������������Ȼ����һ�����ˣ�����Ȼ��һ��С��������\n"NOR);
			tell_object(me,HIR"\n\n\n�����ŭ�����ɣ����㺰��������ȥ���ɣ�������������\n"NOR);

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
		tell_object(me,HIW"\n\n�ʱ����Ѿ������������ʱ�������ʧ�ܣ�\n"NOR);
		return 1;
	}
	if (!objectp(yun)&&!objectp(zhong) && objectp(gan)&&!me->is_fighting())
	{
		tell_object(me,HIW"\n\n����һ����ս�����ڽ���Щ����ɱ����\n"NOR);
		tell_object(me,HIW"\n\n�ʱ������鼫Ϊ��ɥ���ƺ�����ƣ�룬�����Ķ�һ��������\n\n"NOR);
		tell_object(me,HIG"\n\n�ʱ���˵������λ���������Ȼ�ȥ�ɣ���˵�������Ѿ����ӷ����ˣ������ٻ�ȥ�ģ�\n"NOR);
		tell_object(me,HIW"\n\n����ʱ������������Ҳ������ǿ��ֻ���ȷ��������ү��˵��\n"NOR);
		
		me->delete_temp("yyzhi");
		me->set_temp("yyzhi/helpgbbover",1);
		me->set("quest/tls/yyz/start/helpgbbover",1);
		return 1;
		
	}
	//remove_call_out("check_task");
	call_out("check_task",1,me);
	return 0;
}
