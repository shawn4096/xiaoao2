// Room: /d/menggu/yading
inherit ROOM;
#include <ansi.h>
int do_canwu(string arg);
int do_climb(string arg);
void create()
{
  set ("short", "ɽ�¶�");
  set ("long", @LONG
�¶��Ǹ��޴��ƽ̨�������˰�����ѩ������޴��ʯͷ������һ��,
��״ǧ��ٹ�,��������ප����С��,�����,��������.�ıߵ�ɽ��ƽƽ
����,���ð�����б�����±�.
LONG);

	set("outdoors", "menggu");
    set("exits", ([ /* sizeof() == 1 */
	//	"down" : __DIR__"xuanya4",
]	));

  setup();
  replace_program(ROOM);
}

void init()
{
	add_action("do_climb", "climb");
	add_action("do_canwu", "canwu");
}


int do_climb(string arg)
{
	object me = this_player();
	int gain,cost;

	if(me->is_busy())
		return notify_fail("�㻹��æ���ء�\n");


	cost = ( 300-me->query_dex()*me->query_skill("dodge")/20 )/10;
	
	if ( cost<10 )cost = 10;
	cost *= 2;

	if( me->query("jing") < 30)
		return notify_fail("���۵�ʵ���������ˡ�\n");
	if (!arg||arg!="down")
	{
		return notify_fail("�˴��Ѿ����¶�����Ҫ���Ķ�ȥ��\n");
	}
	if(arg == "down" )
	{
		message_vision( HIY"\n$N�����������ٸ���С�Ľ���������ȥ��\n"NOR, me);
		me->move(__DIR__"xuanya4");
		message_vision( HIY"\n$N����������\n"NOR, me);
		return 1;
	}
	return 1;
}
//����

int do_canwu(string arg)
{
	object me;
	int i,j;
	me=this_player();
	if (!arg||arg!="������")
	{
		return notify_fail("��Ҫ����ʲô�似��\n");
	}
		if (me->query("family/family_name")!="ȫ���") 
		{
			return notify_fail("�˵ؿտ������ȫ��̵��ӣ�û���ܵ����ڵ�����ָ�㣬Ҫ����ʲô��\n");
		}

		if (!me->query_temp("jyg/start")) 
		{
			return notify_fail("��û�����µ�׼���ã�����û���κ�����\n");
		}

		if(me->is_busy())
			return notify_fail("�㻹��æ���ء�\n");

		message_vision(HIC"$N��ϥ��������ϸ��ζ�������µľ�����������������\n"NOR,me);
		

	   if (!me->query("quest/qz/dichuan"))
	   {
		      return notify_fail("say ���ȫ��մ����ӣ�����������");
             

	   }
	   if (!me->query_dex(1))
	   {
		      return notify_fail("say ��ĺ���������60���������κζ�����");
             

	   }

	   if (me->query_skill("xiantian-gong",1) < 200) {
              return notify_fail("say ��ȫ���һ����ȫ�����칦�������칦����200��������������");
              
       }
	   if (me->query_skill("yuanyang-lianhuantui",1) < 200) {
               return notify_fail("say ��ԧ�������Ȳ���200��������������");
             
       }
	   	if (me->query("quest/qz/jyg/shangtianti/pass"))
		{
			return notify_fail("�������ԧ���ȵ����ž����Ѿ��⿪�ˡ���\n");
		}
		if (time()-me->query("quest/qz/jyg/shangtianti/time")<86400)
		{
			return notify_fail("������̫Ƶ���ˣ�����������\n");
		}
	   if (me->is_busy())
	   {
		  return notify_fail("��������æ������!\n");
	   }
		me->start_busy(10);
		if (me->query("party/gongji")<100)
		{
			return notify_fail("������ɹ���ֵ����100�㣬�����Ŭ��ȥΪ���ɷܶ���\n");
		}
		me->add("party/gongji",-100);


		i = 20;
		  if(me->query("m-card-vip")) i =  18;
		  if(me->query("y-card-vip")) i =  15;
		  if(me->query("buyvip"))     i =  12;
		  i=random(i);
		j=random(me->query("kar"));
		if( i<3
			&& random(me->query_dex())>50
			&& me->query("kar")<31
			&& j > 27 ) 
		{
			tell_object(me,HIC"\n�����˵����ڵ���������ָ�㣬�����������Լ����ý��㹦�������ĵã�����ӡ�ա�\n"NOR);
			tell_object(me,HIR"\n��Ȼ�ŵ�ӿȪѨһ�ɴ������������ʱ�о��������࣬�Ȳ�����������˲���������������ݾ������������š�\n"
						NOR);
			me->set("quest/qz/jyg/shangtianti/pass",1);
			log_file("quest/qzshangtt", sprintf("%8s(%8s) ʧ��%d�κ�ѧ�������ݾ���,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
				me->name(1),me->query("id"), me->query("quest/qz/jyg/shangtianti/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
			command("haha"+me->query("id"));		
			
			tell_object(me, "��ϲ���������ݾ��������ɹ�!\n");/**/
			
		}	
	   else
		{
			log_file("quest/qzshangtt", sprintf("%8s(%8s) ���������ݾ�������ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
				me->name(1),me->query("id"), me->query("quest/qz/jyg/shangtianti/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
			
			tell_object(me,HIY"�������ڵ�����ָ�㣬���Ƕ������ݾ����İ���ȫȻ����Ҫ�졣\n\n"NOR);
	
			me->add("quest/qz/jyg/shangtianti/fail",1);
			me->set("quest/qz/jyg/shangtianti/time",time());
			me->start_busy(1+random(3));
			
			return notify_fail("�ǳ��ź����������㹦֮�����ݾ���ʧ��"+me->query("quest/qz/jyg/shangtianti/fail")+"�Ρ�\n");
		}
		me->add_busy(1);

	
	return 1;
}



