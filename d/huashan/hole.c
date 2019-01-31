// Room: /d/huashan/hole.c
// Date: Look 99/03/25
#include <ansi.h>
#include <skill.h>
inherit ROOM;
int do_lingwu();
void create()
{
	set("short", "˼���¶���");
	set("long", @LONG
������Ƿ�����ɽ�ɵ����ܷ�˼���ĵط���λ����Ů�嶥��������һС
��ƽ�أ�һ������ɲ��ɽ�ȡ�һ���Ƕ��͵�����(bi)������������м���
ɽʯ������һ���ر�⻬�����ǵ���������Ǿ������ɡ�
LONG
	);
	set("exits", ([
		"out" : __DIR__"siguoya",
	]));

	set("item_desc", ([
		"bi" : "�㿴�ſ��ź�Ȼ������һ��ʯ���ϵ���̦�ȱ��ٵöࡣ������....\n",
	]) );

	setup();
}

void init()
{
        object me = this_player();
        me->delete_temp("mianbi_count");
        me->delete_temp("break_flag");
        add_action("do_mianbi", "mianbi");
		add_action("do_lingwu", "sikao");
		add_action("do_lingwu", "jingsi");

}
int do_lingwu()
{
   object me = this_player();
   int i;
   if (me->is_busy())
                return notify_fail("����æ���أ��޷������������˼����\n");
   if (me->is_fighting())
                return notify_fail("������ս���У���ξ����������˼����\n");
//   if (me->query_temp("quest/huashan/zixia1",1))
  //              return notify_fail("�б�ǲ��ԣ�\n");
   if (me->query_temp("quest/huashan/zixia1",1))
      {
        message_vision("$N����ʯ�ڵ����������ã���������\n", me);
        me->receive_damage("jing", random(100));
        me->add("shen",random(100));
        me->start_busy(random(3));
		i=i+1;
		
		if (random(me->add_temp("lingwu_count", 1)) > 20 && random(me->query("kar"))>= 20 && random(10) <= 5) {
                me->delete_temp("quest/huashan/zixia1", 1);
				me->set_temp("quest/huashan/shandong", 1);
                //add_action("do_break", "break");
                me->command("sigh");
				write(HIR"���̲�סһ���ķ����ң����������Ĺ�ȥ��ʵ�ڰ��Ͳ�ס����������һ��վ��������\n"
				+"�������ϼ��Ҫ������ƽ����ּ��㣣��̲�סһ����Ѫ����,�۵��³�һ����Ѫ!\n"
				+"���������Ѿ����ܲ�������ˡ�\n"NOR,me);
				
				me->recieve_wound("jing",random(10));
				me->receive_wound("qi",random(10));
				write(HIC"��˼ǰ���������ô���������絽����ȥ��˯һ��,˵�������ܶ����˴���Ч����\n"NOR,me);
				call_out("thinking",2,me); 
								
				}
		else
			{
		      me->receive_wound("qi",random(10));
			  write(HIC"�㰴������Ⱥ���㽲�����ϼҪ����ʼ����,�����Ҫ�죬��̾һ����վ���������Ļ����䡣\n"NOR);
			  //i=i+1;
			  me->start_busy(random(1));
			  me->delete_temp("quest/huashan/zixia1");
			  }
			  return 1;
		}
        write(HIC"��Ҫ��ʲô��\n"NOR);
		return 0;
}
//�����ӳ��� ��˼����

int thinking()
{
  object me= this_player();
  if(environment(me)!= find_object(__DIR__"hole")) 
  {
  	//start_condition(ob);
    if(random(2)) message_vision(HIC"\n����Ⱥ����������������û�뵽"+me->query("name")+"��Ȼ������ҵ��û�ϵþ�Ȼ�Ǵ���һ����\n"NOR,me); 
    else message_vision(HIC"\n$N�ɻ��ʵ�����~~~���أ�$n�����أ�\n"NOR,me); 
  	return 1;
  }
  
  if (me->query_temp("quest/huashan/shandong")&& random(10)>= 5)
  {
	  write(HIM"��ʱ����Ȼ������������Ⱥ�ȵ���������С�������ú��ù����⼸�춼�װ��˷��ˣ�������ʧ������\n"NOR,me);
      write(HIY"��֪������Ⱥ��ʱ���ˣ������Լ���һ��һ�У�����������������ʱ�����죡\n"NOR,me);
	  me->delete_temp("quest/huashan/shandong");
	  me->set_temp("quest/huashan/zixia/zixia2",1);
	  return 1;
  }
  message_vision(HIC"\n��˼ǰ��������뵽�������Ե�֢״��\n"NOR,me); 
} 
//���
int do_mianbi()
{
	int getshen;
        object me = this_player();

        if (me->is_busy())
                return notify_fail("����æ���أ��޷������������˼����\n");
        if (me->is_fighting())
                return notify_fail("������ս���У���ξ����������˼����\n");
        if ((int)me->query("shen") < 0)
        {
        	getshen= random(-1 * (int)me->query("shen")/600);
        }
        else
        {
        	getshen= -1 * random((int)me->query("shen")/300);
        }

        if (!me->query_temp("break_flag"))
        {
        message_vision("$N����ʯ�ڵ�����˼�����ã���������\n", me);
        me->receive_damage("jing", random(100));
        me->add("shen",getshen);
        me->start_busy(random(3));
        if (random(me->add_temp("mianbi_count", 1)) > 35) {
                me->set_temp("break_flag", 1);
                add_action("do_break", "break");
                write("���Ȼ����һ���Ʊڵ�����������վ��������\n");
        }
        }
        return 1;
}


int do_break(string arg)
{
    int n;
	object me = this_player();
	object weapon;
	object room;
	n = (int)me->query("neili");
   	room = find_object(__DIR__"rukou");
	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("�������޽��������Ʊڣ�\n");
     message_vision("$N�ߵ�ʯ��ǰ���γ����������������˾���ʯ�ڴ��˹�ȥ��\n", me);

 if ( n >= 600 ){
    message_vision("$Nֻ��һ�����죬ʯ�ڱ�ͱ���ˣ�ԭ��������һ���󶴡���\n", me);
    set("exits/enter",__DIR__"rukou");
    set("exits/out",__DIR__"siguoya");
    this_player()->add("neili", -200);
    remove_call_out("close");
    call_out("close", 5, this_object());
    if(!(room = find_object(__DIR__"rukou"))) room = load_object(__DIR__"rukou");
    if( room = find_object(__DIR__"rukou") ) 
	{
		message("vision", "��ֻ������һ�����죬ʯ�����˴�����ͱ���ˣ�¶����һ�����ڡ�\n", room);
		room->set("exits/out",__DIR__"hole");
	//  remove_call_out("close1");
		call_out("close1", 5, room);   
	}
  }
  else {
    message_vision("���ֻ��һ���ƺߣ�$N��ʯ�ڵķ����������ǰһ��....\n", me);
    this_player()->unconcious();
    }
    return 1;
}

void close(object ob)
{
        message("vision","���Ϻ�Ȼ������һ���ʯ�������ڷ��˸�����ʵʵ��\n", ob);
        ob->delete("exits/enter");
}
void close1(object room)
{       
        message("vision","���Ϻ�Ȼ������һ���ʯ�������ڷ��˸�����ʵʵ��\n", room);
        room->delete("exits/out");
}
