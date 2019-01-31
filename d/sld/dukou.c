#include <ansi.h>

inherit ROOM;
#include <wanted.h>
int do_yell(string arg);
int go_zhy(object me);


void create()
{
        set("short", "�ɿ�");
        set("long", @LONG
��ǰ���������ޱߵ�ãã�󺣣���ˮ���������һ�˽���һ�˵س����߻�
����һ����ȥ��ֻ������Ÿ�ں����Ϸ��裬ż��Ҳ�ɼ���Զ���з�Ӱ�ӹ���
������������Ψһ����ͣ�������ĵط�������Ķ������߶���ɳ̲����������
һ�����֡�
LONG
        );

        set("exits", ([
"northeast" : __DIR__"sande",
 "northwest" : __DIR__"sandw",
"north" : __DIR__"trees1",
        ]));
		  set("objects", ([
   __DIR__"npc/chuanfu" :1,
	]));
	set("no_fight",1);
        set("outdoors", "������");
        set("coor/x",490);
  set("coor/y",420);
   set("coor/z",0);
   setup();
        
}
void init()
{

	add_action("do_yell","yell");
}
//���������ͨ��ȥ��ԭ

int do_yell(string arg)
{
	object me;
	me = this_player();
	if (me->query("family/family_name")!="������") return notify_fail("ֻ�����������Ӳ���ר��������ԭ�Ĵ���\n");

	if ( (arg == "�����̶�������" || arg == "������һͳ����") && me->query("family/family_name")=="������" ) {
		if ( is_wanted(me) ) return 0;
		else return go_zhy(me);
	}

}
int go_zhy(object me)
{
	object hc;
	string str ="ʦ��";
		
	if(!objectp(hc=find_object("/d/huanghe/hc1")))
		hc=load_object("/d/huanghe/hc1");
		if(hc->query_temp("curstatus",1)=="run") {
			if(!objectp(hc=find_object("/d/huanghe/hc2")))
				hc=load_object("/d/huanghe/hc2");
				if(hc->query_temp("curstatus",1)=="run") {
					if(!objectp(hc=find_object("/d/huanghe/hc3")))
						hc=load_object("/d/huanghe/hc3");
						if(hc->query_temp("curstatus",1)=="run")
							return notify_fail("�㺰�˼�����ȴʲô��Ҳû�з�����\n");
                        }
                }
	if(me->query("gender")=="Ů��") str="ʦ��";

	message_vision(CYN"һλСͯ�߹�����$N����һ��˵������λ"+str+"Ҫ��������ô��������������ʱ�ˡ�\n" NOR,me);
	message_vision(CYN"ֻ��һ�Ҵ��Ѿ�ʻ�����ڣ�$N�������˽�ȥ��\n" NOR,me);	
	me->move(hc);
	hc->set_temp("curstatus","run");
	me->set_temp("gohuanghe",1);
	return 1;
}
