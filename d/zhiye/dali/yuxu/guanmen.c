// Modify By River 98/12
inherit ROOM;
#include <ansi.h>

void create()
{
	set("short", "�������");
	set("long", @LONG
�ߵ����������ǻ�ǽԭ�������¹ۣ��Ҷ���д���ƺ��ǡ�����ۡ����֣�
��ǽ���ߣ���ۿ��������Ǽ�ª���ſ�վ������С��ͯ��

LONG
	);
	set("outdoors", "����");
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
		me->delete_temp("yyzhi/first");//��ֹ��������
		
		if (!objectp(yzh=present("yunzhong he",environment(me))))
        {
		      yzh=new("/d/dali/wuliang/npc/yunzhonghe");
		      yzh->move(environment(me));
		}
		message_vision(HIG"\nһ������������˺�Ȼ����Ծ������ɫ���Ե�Ц��������ү��ο���׽������Ư��С椡�\n"NOR,me);
		if (!objectp(fsg=present("fu sigui",this_object())))
        {
			//room=load_object("/d/dali/wangfu/dating");
			
				message_vision(HIY"\nԶ��һ�������ȵ��������粻�������ɣ�����������ţ�ĳ����Ҳ��\n"NOR,me);
				fsg=new("d/dali/wangfu/npc/fusigui");
				fsg->move(environment(me));
			    message_vision(HIY"\n���⴫��һ����Ц�������ﲻ�õ��ģ�ĳ����Ҳ������һλ������ͭ���Ĺٲ�����������\n"NOR,me);
				message_vision(HIG"\n\n��˼�鱧ȭ��$N�������ٸ����£������˵Ȳ�Ҫ���£����Ǿ���Ϊ�������ô��ʰ���Ĵ���ˣ�����\n"NOR,me);

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
			message_vision(HIY"\n��ʱ���ӹ��ڴ���һ���������������Ĵ������Ҫ��������������ǣ�\n"NOR,me);
			yuxu=new("d/dali/yuxu/npc/yuxu");
			yuxu->move("/d/dali/yuxu/guanmen");
		}
		else if (present("yuxu sanren",room))
		{
			message_vision(HIY"\n��ʱ���ӹ��ڴ���һ���������������Ĵ������Ҫ��������������ǣ�\n"NOR,me);
		    yuxu=present("yuxu sanren",room);	
			yuxu->move("/d/dali/yuxu/guanmen");
		}	
		else
			message_vision(HIY"\n����ɢ�˾�����ǰ�ˡ�\n"NOR,me);
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
		message_vision(HIY"\n��ʱ���ӹ��ڴ���һ���������������Ĵ������Ҫ��������������ǣ�\n"NOR,me);
		if (!present("yuxu sanren",room) && !present("yuxu sanren",environment(me)))
		{
			message_vision(HIY"\n��ʱ���ӹ��ڴ���һ���������������Ĵ������Ҫ��������������ǣ�\n"NOR,me);
			yuxu=new("d/dali/yuxu/npc/yuxu");
			yuxu->move("/d/dali/yuxu/guanmen");
		}
		else if (present("yuxu sanren",room))
		{
			message_vision(HIY"\n��ʱ���ӹ��ڴ���һ���������������Ĵ������Ҫ��������������ǣ�\n"NOR,me);
		    yuxu=present("yuxu sanren",room);	
			yuxu->move("/d/dali/yuxu/guanmen");
		}	
		else
			message_vision(HIY"\n����ɢ�˾�����ǰ�ˡ�\n"NOR,me);
       
    }
    add_action("do_help","baohu");	
	message_vision(HIY"\n$Nһ������������߳�һλ�������ˣ����Ǵ�����������ɢ�ˣ�\n"NOR,me);
	message_vision(HIY"\n$N������ү������������������������"HIR"��baohu ��������\n"NOR,me);

	yuxu->kill_ob(yzh);
	yzh->kill_ob(yuxu);
    return 1;

}

int check_yuxu(object me,object yzh,object yuxu)
{
	object fsg;
	if (!living(yuxu))
	{
		message_vision(HIC"����ɢ��Ϊ���к���ɱ������ʧ��,���ͷ����������\n"NOR,me);
		me->add("quest/tls/yyz/start/fail",1);
		me->delete_temp("yyzhi");

		return 1;
	}
    if (yuxu->query("qi",1)<yuxu->query("max_qi",1)/2)
    {
		message_vision(HIG"���к��੹�Цһ�������ֵ�������ɢ�˵�Ѩ�����ᱧ������ת�������Ծ��ȥ��\n"NOR,me);
		tell_object(me,HIW"���������ߣ�����ʧ�ܣ�\n"NOR);
		if (objectp(yuxu)) destruct(yuxu);
		if (objectp(yzh)) destruct(yzh);				
		
		me->add("quest/tls/yyz/start/fail",1);
		me->delete_temp("yyzhi");
		return 1;
    }
    if (!objectp(yzh)&& objectp(yuxu))
    {
   		tell_object(me,HIW"������ȳɹ���\n"NOR);
		tell_object(me,HIG"��������˵�����⣬��̾һ��������Ȼ��ˣ��Ǻðɣ������Ǹ������ˣ���һ��͵���\n"NOR);
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
		return notify_fail("��Ҫ�Ȼ�˭��\n");
	}
	if (arg!="����")
	{
		return notify_fail("�㲻�Ȼ�����������ү��ܲ����ˣ�\n");
	}
	
	message_vision(HIC"$N�����ȵ�����������Ҫ���ţ���Ҫ���£�ĳ���ڴˣ���Ҳ�޷�����\n"NOR,me);
	message_vision(HIY"\n\n���к��ੵ�Ц��������һ������ͷ�ģ���\n"NOR,me);
  if (yzh) yzh->kill_ob(me);
  {
	remove_call_out("check_yuxu");
	call_out("check_yuxu",3,me,yzh,yuxu);
	}

	return 1;
}