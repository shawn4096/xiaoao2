// midong.c
// Modified by Java Apr.27 1998
// by sohu
#include <ansi.h>
inherit ROOM;
int do_mo(string arg);
int modao(object me);

void create()
{
        set("short","�ܶ�");
        set("long",@LONG
�˴���Ѫ����ɽ�����������򣬴˴��ڷ��˲��ٵ������̳̳�޹�
�ſ�վ��λѪ�����ӣ�����Ѳ�ߣ��䱸ɭ�ϡ�������һλ��������ָʹ
���µ���æµ�ţ����ڼ����һ�ɹ����ζ����ʱ���������磬ʱ��
�̱ǵ�Ѫ����Ϣ���ط�������һ��ǳ����ĥ��ʯ( shi)��ĥ��ʯ��ɢ
��һ�ص�����Ѫ����
LONG );
        set("exits",([
                "west"   : __DIR__"kengdao4",
        ]));
        set("objects",([				
				"/d/xuedao/obj/liandanlu" : 1,
        ]));
		set("item_desc", ([
			"shi" : CYN"���ĥ��ʯ��Ȼ��������ʹ�õ�Ե�ʣ��ǿ�ʯͷ�Ѿ�ĥ(yanmo)�ɽӽ������Ρ�\n"NOR,
			"ĥ��ʯ" : CYN"���ĥ��ʯ��Ȼ��������ʹ�õ�Ե�ʣ��ǿ�ʯͷ�Ѿ�ĥ(yanmo)�ɽӽ������Ρ�\n"NOR,
		]));
        setup();
        replace_program(ROOM);
}

void init()
{
	add_action("do_mo","yanmo");
	add_action("do_jilian","jilian");
}

int do_mo(string arg)
{
	object me,weapon;
	me=this_player();
	if (!me) return 1;
	
	weapon=me->query_temp("weapon");
	
	if (!arg||arg!="��")
	{
		return notify_fail("��������ĥ��ʯ��������ȥ��һ�����������!\n");
	}
	
	if (!weapon
		||weapon->query("skill_type")!="blade")
	{
		return notify_fail("�㲻װ�������ĥ��!\n");

	}
	if (me->query_skill("xuedao-daofa",1)<300)
	{

		return notify_fail("�㵶������300�����¾ͽ����еĸֵ�ĥ���ˣ�\n");
	}
	if (me->query("family/family_name")!="Ѫ����")
	{
		return notify_fail("�㲻��Ѫ���ŵ��ӣ�������ǲ������ô��\n");
	}

	if (me->query("quest/xd/xddf/huaxue/pass"))
	{
		
		return notify_fail("���Ѿ��⿪��������⣬����Ե�޹���������������\n");
	}

	if (!me->query_temp("quest/xd/xddf/huaxue/asklaozu"))
	{
		return notify_fail("��û�еõ������ָ�㣬��ĥ�˰��첻��Ҫ�죡\n");
	}

	if (time()-me->query("quest/xd/xddf/huaxue/time")<86400)
	{
		//command("say ��");
		return notify_fail( "������̫Ƶ���ˣ��书��ɻ��������ꣿ��\n");
	}
	if (!me->query("quest/xd/dichuan"))
	{
		//command("say ��");
		return notify_fail( "Ѫ����Ҫ����ʼ����һ���ҳϵ��ӣ���ǵմ������ܴ�����߼��书����\n");
	}
	if (me->query_skill("xuedao-jing",1)<300)
	{
		//command("say ��");
		return notify_fail("��ϰѪ������Ҫ��300����ĥ�������Ǻú�����ȥ�ɣ���\n");
	}
	if (me->query_temp("quest/xd/xddf/huaxue/jilian"))
	{
		return notify_fail("�����ڼ�����!\n");

	}
	if (me->query_temp("quest/xd/xddf/huaxue/modao"))
	{
		return notify_fail("������ĥ����!\n");

	}

	message_vision(HIW"$N��ʹ���洫�ڵ��������ţ���ĥʯ��������\n"NOR,me);
	me->set_temp("quest/xd/xddf/huaxue/modao",1);
	me->start_busy(2);
	remove_call_out("modao");
	call_out("modao",1,me);
	return 1;
}

int modao(object me)
{
   int i,j,jobs; 
	if(!me) return 0;
	i=random(me->query("kar"));
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	
	if (!me->query_temp("weapon")) return 0;

	jobs=(int)me->query("job_time/Ѫ������")+(int)me->query("job_time/Ѫ������");
   if(me->query_temp("canwu_modao")<(10+random(10)))
   {  
	  me->add_temp("canwu_modao",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n�㽫���еĵ�ĥ����ĥ����������.\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n����ϸ��ĥĥ���ļ��ɣ�ͣ���������Լ���Ħ�⵶�ĺ�Ⱥͷ����ȡ�\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n��һʱ�������꣬����ĥ����ʮ�£����ÿһ����û���ƺã������ȻԽĨԽ��..\n"NOR);
			 me->add_temp("canwu_modao",-2);
			break;
		case 3:
			tell_object(me,HIW"\n������Ķ��������룬�ƺ������ĵ�.\n"NOR);
			me->add_temp("canwu_modao",1);

			break;
		case 4:
			tell_object(me,CYN"\n�������������ƣ��֮�ʣ��ƺ���������.\n"NOR);
			me->add_temp("canwu_modao",-1);

			break;
		case 5:
			tell_object(me,MAG"\n��ĥ��֮�ʣ���Ȼ����һ�ᣬ���־�Ȼ˿��������û������.\n"NOR);
			me->add_temp("canwu_modao",4);

			break;

		default:tell_object(me,YEL"\n��ĥ��ĥ������������.\n"NOR);
			break;

	  }      

	  tell_room(environment(me),HIC""+me->query("name")+"���øֵ���һ��һ����ĥ�����鼫Ϊרע...\n"NOR, ({}));

	//  remove_call_out("do_mo");
	  call_out("modao",3+random(3), me);

   } 
  else if (i>24
	  && random(j)<4
	  && random(jobs)>1200
	  && me->query("kar")<31)
 	{ 
        
         me->start_busy(3);
		 message_vision(HIG"\n$Nĥ�˰��죬������Ѩ��Ȼһʹ�����еĸֵ���Ȼ��Ȼ�������������������󡣡�\n"NOR,me); 
         message_vision(HIW"\n$N���д�ϲ�����������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HBYEL+HIW"\n$N����������ĥ��ϰ��������������Ѫ�����������ڵĻ�Ѫ���İ��أ���\n"NOR,me); 
         log_file("quest/xdhuaxue", sprintf("%s(%s) ��Ѫ���ܳɹ�����%d�β��򣬻�Ե�ɺ��£��ɹ�����Ѫ�����İ��أ��������ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d,\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xd/xddf/huaxue/fail"),
		 i,
		 j,
         me->query("combat_exp"),
		 ));

		 me->set("quest/xd/xddf/huaxue/time",time());
		 me->set("quest/xd/xddf/huaxue/pass",1);
		 me->delete_temp("canwu_modao");
		// me->set("title",HBRED"Ѫ����������"NOR);
		 me->delete_temp("quest/xd/xddf/huaxue/modao");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N��̾һ�������������˵�����������⻯Ѫ�����ǲ��ýⰡ������Ŭ���ɡ���\n"NOR,me); 
		 message_vision(HIY"\n����Ѫ����������ʧ�ܣ�\n"NOR,me); 
         log_file("quest/xdhuaxue", sprintf("%s(%s) ʧ�ܣ�����Ѫ��%d��ʧ�ܣ��������ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xd/xddf/huaxue/fail",1),
		 i,
		 j,
         me->query("combat_exp"),));        
		 me->add("quest/xd/xddf/huaxue/fail",1);
		 me->set("quest/xd/xddf/huaxue/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_modao");
		 me->delete_temp("quest/xd/xddf/huaxue/modao");
		 me->delete_temp("quest/xd/xddf");
		 return 1;
   }
	
}
