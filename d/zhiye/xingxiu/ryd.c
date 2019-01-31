// Room: /d/xingxiu/ryd.c
// Update by caiji@SJ 8/25/2000

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIY"���¶�"NOR);
	set("long", @LONG
�������������ܶ����ڵ����¶������ڵƻ�ͨ��������һ�ѻ�Ƥ���϶���
�������������˶�������߸�վ������ʮλ�����ɵ��ӣ������и�����ʿ��
������(xian)�ϸ��ֱ��һƬ�蹦�̵�֮��������ӯ����˿�����Ҳ���Ŵ�
�ࡣ������ÿ��������֮ʱ������ס�Ӷ����е����ȣ����Ű��룬������˫�ۣ�
޹޹Ȼ��ƮƮȻ�����籥���ơ�������װ���Ż�Ƥ��¹ͷ�����𣬼�һЩ��
�� (zihua)��
LONG
        );
        set("exits", ([
		"north" : __DIR__"yaolu",
		"south" : __DIR__"ryd1",
        ]));
        set("item_desc", ([
                "zihua" : "����Щ�����������ɵ�ʫ�ʺ����Ļ����ƺ�\n�ֻ�����Щ���⣬�е������ڣ�guanwu��ʲô\n						

               ����������������������������������
               ����������������������������������
               �����������š������¡��ǡ���������
               ���������������䡡�ޡ���������
               �����������ޡ�御��졡�ϡ���������
               �����������ȡ���ء��ɡ���������
               ����������������������������������
               ����������������������������������\n"]));

	set("objects", ([
                __DIR__"npc/ding"  : 1,
                __DIR__"npc/zhaixing"  : 1,
                __DIR__"obj/huoyan"  : 1,
        ]));
        setup();
}

void init()
{
        object me = this_player();

        int lvl,lvl1,lvl2;
        lvl = me->query_skill("poison", 1);
        lvl1 = me->query_skill("huagong-dafa", 1);
        
		if (lvl > 500 && !me->query("cut/xingxiu"))
		{
                
			lvl2 = (lvl - 500)/ 4;
		    me->set_skill("poison", 500);
			
			me->set_skill("huagong-dafa", lvl1 + lvl2);
                me->set("cut/xingxiu", lvl2 * 4);
                write(HIG "ϵͳ�ѽ�������ġ�������ת��Ϊ�������󷨡���\n" NOR);
		}
		if ( me->query("xx_points")){
			me->add("job_time/����", me->query("xx_points"));
			me->delete("xx_points");
		}
		if ( me->query("xx_job5")){
			me->add("job_time/������ͽ", me->query("xx_job5"));
			me->delete("xx_job5");
		}
		if ( me->query("xx_job4")){
			me->add("job_time/���ް���", me->query("xx_job4"));
			me->delete("xx_job4");
		}
		if (this_player()->query("family/family_name")=="������")
			add_action("do_guanwu","guanwu");

}
int valid_leave(object me, string dir)
{
	if ( dir == "north" && !userp(me))
		return 0;
	if(dir == "north"
	 && me->query("family/family_name") != "������"
	 && present("ding chunqiu", environment(me))){
		return notify_fail("��������ס������������ɵ�ҩ®�صأ���ô���������ȥ��\n");
	}
	return ::valid_leave(me, dir);
}

int do_guanwu(string arg)
{
	object me=this_player();

	if (!arg||(arg!="zihua"&&arg!="�ֻ�"))
	{
		return notify_fail("��Ҫ��Ħʲô������\n");
	}
	if (me->query("family/family_name")!="������")
	{
		return notify_fail("�㲻�������ɵ��ӣ����˹�Ħʲô��\n");
	}
	if (me->query_skill("tianshan-zhang",1)<250)
	{
		return notify_fail("�����ɽ�ȷ�������250��,�޷���Ħ����ʲô��\n");
	}
	if (me->query_skill("huagong-dafa",1)<250)
	{
		return notify_fail("��Ļ����󷨼�����250��,�޷���Ħ����ʲô��\n");
	}
	if (me->query("quest/xx/tsz/luanpifeng/pass"))
	{
		return notify_fail("���Ѿ��ڻ��ͨ���ֻ��е�������������⡣\n");
	}
	if (me->is_busy())
	{
		return notify_fail("������æµ�У��԰����꣡\n");
	}

	if (time()-me->query("quest/xx/tsz/luanpifeng/time")<86400)
	{
		return notify_fail("���ֻ�ȫƾ�������Ƶ�������к����档\n");
	}
	message_vision(HIY"$Ņ�۴����Ǹ��ֻ�������д�˺ܶ��֣�ÿһ���ֶ�д�ļ�Ϊ���\n"NOR,me);
	message_vision(HIY"״����񣬱���򰾢��������Щ�ֶ�����һ�����������������Ϳ�����ʲô����\n"NOR,me);
	message_vision(HIG"���Ǹ�������������īһ�㣬��һ�ţ���һ�ţ�״�����š�\n"NOR,me);
	message_vision(HIR"��Խ��ԽͶ�룬Խ��Խ���������������\n"NOR,me);
	message_vision(HIW"��Ȼ�����ƺ����з�����Щ�����ƺ��̺�һ�ż����������书��\n"NOR,me);
	me->start_busy(99);
	
	if (me->query_temp("canwu_zihua"))
	{
		return notify_fail("�����ڲ����У��԰����꣡\n");
	}
	remove_call_out("thinking");
	call_out("thinking",1,me);
	return 1;
}

int thinking(object me)
{
	int i,j;
	j = 20;
    if(me->query("m-card-vip")) j =  18;
    if(me->query("y-card-vip")) j =  15;
    if(me->query("buyvip"))     j =  10;
	i=random(j);

	if (me->query("kar")>30) 
	{
	  log_file("quest/bug", sprintf("%s(%s) �������������ʱ��KAR�쳣����ǰ���飺%d�����䣺%d��kar:%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
	}
	if(me->query_temp("canwu_zihua")<(10+random(10)))
	{  
	  me->add_temp("canwu_zihua",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n����ϸ��Ħ����ֻ�������Щ�书�˴�ӡ֤��ֻ���ö�Ŀһ��...\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n��Ȼ�����ƺ�ץס��һЩ����\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n���������״̬������һƬ�������ƺ�Ҫץס�Ǹ������ˣ�..\n"NOR);
			break;
		case 3:
			tell_object(me,HIW"\n������Ķ����������ģ������������ƺ���Щ����.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n�������������ƣ��֮�ʣ��ƺ�����ƿ����..\n"NOR);
			break;
		case 5:
			tell_object(me,MAG"\n��˼άƯ���ڿ��У�����Ӥ����ԡ.������ˬ.\n"NOR);
			break;
		default:tell_object(me,YEL"\n��̾��һ�������������ǲ�����Ч����.\n"NOR);
			break;
	  }
      
	  tell_room(environment(me),HIC"\n"+me->query("name")+"��ɫƽ�ͣ���Ȼ���ң��ƺ���˼����ʲô...\n"NOR, ({}));
	  
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);

   } 
   else if (i<5
			&& random(me->query("kar"))>22
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIY"\n$N����������Ц����������˵������ԭ��������������λǰ����Ȼ����ɽ�ȷ����뵽�ֻ�֮�У������񼼣���\n"NOR,me); 
		 message_vision(HIR"\n$N ���ֻ����������ɽ�ȷ��еġ�������������İ��塣\n"NOR,me); 
        // message_vision(HIY"\n$N`���»����������������������ڵ�����ذ���⡾�������С��İ��أ���\n"NOR,me); 
         log_file("quest/tszluanpifeng", sprintf("%s(%s) ���ܳɹ�����%d�β��򣬻�Ե�ɺ��£��ɹ�������ɽ�ȷ�֮����������İ��أ���ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xx/tsz/luanpifeng/fail"),
		 i,
		 j,
         me->query("combat_exp")));

		 me->set("quest/xx/tsz/luanpifeng/time",time());
		 me->set("quest/xx/tsz/luanpifeng/pass",1);
		 me->delete_temp("canwu_zihua");
		 me->start_busy(1);
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N��̾һ�������������˵����������ֻ��е��״���ʲô���İ��أ��������˹��ˡ���\n"NOR,me); 
		 message_vision(HBYEL+HIR"\n�������¶��ֻ�����ʧ�ܣ�\n"NOR,me); 
         log_file("quest/tszluanpifeng", sprintf("%s(%s) ʧ�ܣ���%d��ʧ�ܲ�����ɽ�ȷ��������������ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xx/tsz/luanpifeng/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/xx/tsz/luanpifeng/fail",1);
		 me->set("quest/xx/tsz/luanpifeng/time",time());// ������дһ��/���¿��Է�������  by renlai		 
		 me->start_busy(2);
		 me->delete_temp("canwu_zihua");
		 return 1;
   }
	

}