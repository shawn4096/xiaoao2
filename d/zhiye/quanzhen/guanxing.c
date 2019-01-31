// guanxing ����̨
//�����չش����Ʒ�֮��
// by sohu@xojh

#include <ansi.h>

inherit ROOM;


void create()
{
	set("short","����̨");
	set("long",@LONG
����������ɽ��ɽ��һ����ƽ̨��ƽ̨��Բ�Σ����ϰ���ʮ���޵ķ�
λ�Ų���һЩʯͷ���ڳʰ���֮�ƣ��м�Ƕ��һ���޴��̫��ͼ��������
�ڣ��˵�������ˬ���������Ͽ��Կ����������ı������ǡ�
LONG
);
	set("exits",([
		"down" : __DIR__"didao4",
	]));
	set("outdoors","quanzhen");
	set("no_clean_up",0);
	setup();
}

void init()
{

	add_action("do_guanwu",({"guanwu","lingwu","canwu"}) );
	
}

int do_guanwu(string arg)
{
	mixed *local;
	int night,level;

	object me ;
	me= this_player();
	if (!arg||arg!="��������")
	{
		return notify_fail("��Ҫ����ʲô��\n");
	}
	night = 0;
	local = localtime(time() * 60);
	if (local[2] < 5 || local[2] >= 19) night = 1;
	
	if (!night)
	{
		return notify_fail("�����ǰ��죬���޷����򱱶��������Ʊ仯��\n");
	}

	if (!me->query_temp("quest/qz/htz/chongyang/askma"))
	{
		message_vision(YEL"$N��ϥ���������˰��Σ�ֻ���ǿղ����ޱȣ�\n"NOR,me);
		return 1;
	}
	if (me->query_temp("quest/qz/htz/chongyang/start"))
	{
		message_vision(YEL"�����ڹ��򱱶������У�\n"NOR,me);
		return 1;
	}
	if (time()-me->query("quest/qz/htz/chongyang/time")<86400)
	{
		message_vision(YEL"������̫Ƶ���ˣ�\n"NOR,me);
		return 1;
	}
	if (me->is_busy())
	{
		return notify_fail("������æµ�У�\n");
	}
	message_vision(HIG"$N��ϥ�������������죬�������ϱ���������ת�仯�����г����䣬������ȣ�\n"NOR,me);
	me->set_temp("quest/qz/htz/chongyang/start",1);
	remove_call_out("guan_xing");
	call_out("guan_xing",1,me);
	return 1;
}

int guan_xing(object me)
{
	int i,j,total;
    if(!me) return 0;

    if(me->query_temp("guan_xing")<(10+random(3)))
    { 
	  me->add_temp("guan_xing",1);
      if(random(2)) tell_object(me,BLU"\n���������죬���Ϸ��ǵ�㣬���ƺ������Ƕ����ƶ�������ѧ���������Ī�����ϵ..\n"NOR);
      else tell_object(me,HIY"\nͻȻ�䣬����������һЩ��ʵս��������������ļ���..\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  remove_call_out("guan_xing");
	  call_out("guan_xing",3+random(3), me);
    } else
    {  
	  me->delete_temp("guan_xing");
      total = me->query("int");
      j = 20;
      if(me->query("m-card-vip")) j =  18;
      if(me->query("y-card-vip")) j =  15;
      if(me->query("buyvip"))     j =  10;
      i=random(j);

    	if (i < 3 
		&& random(me->query("kar"))>26
		&& random(total) >= 40) 		 
		{
       
			  tell_object(me,HIM"$N�������ڵ�ָ�㣬����Լ������������ϱ������ǣ��ۿ��������ǵİ��أ�\n"NOR);
			  message_vision(HIC"$N�������ɣ���Ȼ�����Ȼ�������������Ƶ��⾳����\n"NOR,me); 
			  tell_object(me,HIR"$N�ֺ�Ȼ�����˱��������Լ�������ʦ�ڴ˹��򱱶�������ת�ĵ�����������Ƶ���ʶ���ͬ��\n"NOR);
			  tell_object(me,HIY"$N���ڶ��������������Ƶľ������أ�����������Ц��ԭ����ˣ�ԭ����ˣ�\n"NOR);
			  tell_object(me,HIW"$N�����ŵ����ð���˼�����پ����ж�����Ƶ���������һ��ǰ��δ�е��¾�\n"NOR);
			  
			  me->set("quest/qz/htz/chongyang/pass", 1);
			  me->set("title",HIG"ȫ��� ����ƴ���"NOR);
			  log_file("quest/qzchongyang", sprintf("%s(%s) ʧ��%d�κ󣬳ɹ��⿪��������������Ƶİ��ء���Դ��%d�����飺%d��\n",   
			  me->name(1),
			  me->query("id"), 
			  me->query("quest/qz/htz/chongyang/fail"),
			  me->query("kar"),
			  me->query("combat_exp")) );
			  me->start_busy(1);
         }
         else
         {
			 tell_object(me,HIG"\n���˼��ã�����Խ��Խ���磬ʼ�ղ���Ҫ�졣\n"NOR);
			 message_vision(HIC"\n$Nҡ��ҡͷ�������̾�˿�����\n"NOR,me); 
			 message_vision(HIY"$Nץ����������˼ڤ�룬�����Լ������޷������������������ư������ڣ�����һ��Īչ��\n"NOR,me);
			 tell_object(me,HBBLU"\n�ܿ�ϧ���㱾�γ�����������ƽ�������ʧ�ܣ�\n"NOR);
			 tell_object(me,HBBLU"��Ŀǰ�ľ�����" + me->query("combat_exp") + "������ʱ�����齣"+ NATURE_D->game_time() + "�����¼��\n"NOR);
			 tell_object(me,HBBLU"�㽫�ڼ��24Сʱ������һ�λ��ᣡ��\n\n"NOR);
			 log_file("quest/qzchongyang", sprintf("%s(%s) ������������������ƾ���ʧ��%d�Ρ���Դ��%d�����飺%d��\n",   
			  me->name(1),
			  me->query("id"), 
			  me->query("quest/qz/htz/chongyang/fail"),
			  me->query("kar"),
			  me->query("combat_exp")) );
			 me->add("quest/qz/htz/chongyang/fail",1);
			 me->set("quest/qz/htz/chongyang/exp", me->query("combat_exp") );
			 me->start_busy(1);
			 me->set("quest/qz/htz/chongyang/time",time());
        }
		 me->delete_temp("quest");
		 me->delete_temp("quest/qz/htz/chongyang/start");
		 return 1;

	}
}
