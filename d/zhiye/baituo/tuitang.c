#include <ansi.h>
inherit ROOM;
int look_zihua();

void create()
{
        set("short", "����");
        set("long", @LONG
������ò���ֻ���������輸�����������ֻ�(zihua)��һ��
�����Ǵ�Į��ѩ����Ⱥ��ͼ��һ����һȺ�����䶯������������˯��
�������Ǹ�СԺ�ӡ�
LONG);
        set("exits", ([
              "south" : __DIR__"tangwu",
              "east" : __DIR__"shuifang",
              "north" : __DIR__"yuanzi",
        ]));
		set("item_desc", ([                    
                "zihua": (:look_zihua:),
				//"guan": "\n������˰���ɽ���еľ綾����,��������������(xidu)��\n",
        ]));
        setup(); 
}
int init()
{
	add_action("do_canwu",({"guanmo","canwu","yandu"}));
}

int look_zihua()
{
	object me=this_player();
	tell_object(me,"������īɽˮ�������һ��Ϊ��Į���ձ��ڵĻ��棬���ư��磬����Ϊ��Į��ѩ���棡\n"
	"�㶨����ȥ�����������д������С�֣���������Ե������ɽ���ˡ���������\n");
	me->set_temp("look/zihua",1);
	return 1;
}
int do_canwu(string arg)
{
	object me;
	me=this_player();
	if (!me->query_temp("look/zihua"))
	{
		return notify_fail("��Ҫ��ʲô��\n");
	}
	if (!arg)
	{
		return notify_fail("��Ҫ����ʲô��\n");
	}
	if (!(arg=="zihua"||arg=="�ֻ�"))
	{
		return notify_fail("��Ҫ����ʲô��\n");
	}
	if (me->query("family/family_name")!="����ɽׯ")
	{
		return notify_fail("��ǰ���ɽׯ�ĵ���!\n");
	}
	if (me->query_skill("hamagong",1)<300)
	{
		return notify_fail("��ĸ�󡹦����300��!\n");
	}
	if (me->query_skill("shentuo-zhang",1)<350)
	{
		return notify_fail("�������ѩɽ����������350��");
	}
	if (me->query_skill("lingshe-quanfa",1)<350)
	{
		return notify_fail("�������ȭ����������350��");
	}
	if (time()-me->query("quest/bt/stxsz/hubei/time")<86400)
	{
		message_vision(YEL"������̫Ƶ���ˣ�\n"NOR,me);
		return 1;
	}
	if (me->is_busy())
	{
		return notify_fail("������æµ�У�\n");
	}
	if (me->query("quest/bt/hubei/start"))
	{
		return notify_fail("�����ڹ����У�\n");
	}

	tell_object(me,"��ۿ�������ͼ����Խ��Խ��������ζ���ƺ����������ݵ����ƣ�\n");
	me->set_temp("quest/bt/hubei/start",1);
	remove_call_out("guan_wu");
	call_out("guan_wu",1,me);
	me->start_busy(99);
	return 1;
}


int guan_wu(object me)
{
	int i,j,total;
    if(!me) return 0;

    if(me->query_temp("guan_wu")<(10+random(3)))
    { 
	  me->add_temp("guan_wu",1);
      if(random(2)) tell_object(me,BLU"\n����ϸ��ȥ���ƺ���������ͼ������ȭ�Լ�����ѩɽ����Ī�����ϵ..\n"NOR);
      else tell_object(me,HIY"\nͻȻ�䣬����������һЩ��ʵս��������ô�����似�ļ���..\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  remove_call_out("guan_wu");
	  call_out("guan_wu",3+random(3), me);
    } else
    {  
	  me->delete_temp("guan_wu");
      total = me->query("int");
      j = 20;
      if(me->query("m-card-vip")) j =  18;
      if(me->query("y-card-vip")) j =  15;
      if(me->query("buyvip"))     j =  10;
      i=random(j);

    	if (i < 5 
		&& random(me->query("kar"))>26) 		 
		{
       
			  message_vision(HIC"$N�������ɣ���Ȼ�����Ȼ������������ȭ���˴���ϵ��⾳����\n"NOR,me); 
			  tell_object(me,HIW"$N�����ŵ����ð���˼�����پ����ж�����ȭ������ѩɽ�Ƶ���������һ��ǰ��δ�е��¾�\n"NOR);
			  
			  me->set("quest/bt/stxsz/hubei/pass", 1);
			  me->set("quest/bt/stxsz/hubei/time",time());
			  log_file("quest/bthubei", sprintf("%s(%s) ʧ��%d�κ󣬳ɹ��⿪����ȭ������ѩɽ���ںϵİ��ء���Դ��%d�����飺%d��\n",   
			  me->name(1),
			  me->query("id"), 
			  me->query("quest/bt/stxsz/hubei/fail"),
			  me->query("kar"),
			  me->query("combat_exp")) );
			  me->start_busy(1);
         }
         else
         {
			 tell_object(me,HIG"\n���˼��ã�����Խ��Խ���磬ʼ�ղ���Ҫ�졣\n"NOR);
			 message_vision(HIC"\n$Nҡ��ҡͷ�������̾�˿�����\n"NOR,me); 
			 message_vision(HIY"$Nץ����������˼ڤ�룬�����Լ������޷���������书�ںϰ������ڣ�����һ��Īչ��\n"NOR,me);
			 tell_object(me,HBBLU"\n�ܿ�ϧ���㱾�γ����ں�����ѩɽ�ƺ�����ȭ����������ʧ�ܣ�\n"NOR);
			 tell_object(me,HBBLU"��Ŀǰ�ľ�����" + me->query("combat_exp") + "������ʱ�����齣"+ NATURE_D->game_time() + "�����¼��\n"NOR);
			 tell_object(me,HBBLU"�㽫�ڼ��24Сʱ������һ�λ��ᣡ��\n\n"NOR);
			 log_file("quest/bthubei", sprintf("%s(%s) ��������ȭ������ѩɽ���ںϾ���ʧ��%d�Ρ���Դ��%d�����飺%d��\n",   
			  me->name(1),
			  me->query("id"), 
			  me->query("quest/bt/stxsz/hubei/fail"),
			  me->query("kar"),
			  me->query("combat_exp")) );
			 me->add("quest/bt/stxsz/hubei/fail",1);
			 me->set("quest/bt/stxsz/hubei/exp", me->query("combat_exp") );
			 me->start_busy(1);
			 me->set("quest/bt/stxsz/hubei/time",time());
        }
		 me->delete_temp("quest");
		 return 1;

	}
}
