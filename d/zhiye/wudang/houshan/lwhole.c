// add wd quest ���� by Lane@SJ 2005.7.11
// Room: lwhole.c
// Update By lsxk@hsbbs ����ͨ��������߽��Գɹ��� 2007/7/18

#include <ansi.h>;

inherit ROOM;

string wall(object me);

void create()
{
	set("short", HIB"ʯ���Ҷ�"NOR);
	set("long", @LONG
����һ��Ȼʯ�������Ǻ����̫������ʱ��ֱ��ȫ�������������ڴ�ס
����������һʯ������߷���һЩʯ�룬�����ʯ��(wall)���ƺ�����С�֣�
����Գ����ж�һ�¡�
LONG
	);

	set("exits", ([
		"out" : __DIR__"wanniansong",
	]));    

	set("item_desc", ([
          "wall" : HIW "��֮��������֮Ƥë����֮������˹��˫��֧�ţ�һ����ͨ��̫���ߣ���Ҳ�������ߣ�����Ҳ��\n"
						+"����һ��Ҳ��̫���޼�Ҳ��������Ϊ�ϣ�����������ԭ������Ϊ�����ϣ����޼�֮�棬����֮����\n"
						+"������������϶�������������ȫ������������֮ת�ơ��˲δ���֮����ʮ��������ʮ�оţ���\n"
						+"��һ���仯ʼ��֮��Ҳ��������ת��Ϊ��Ϣ���Ծ�������Ϊ���壬����������������ת��������������\n"
						+"����������������¶���������ͣ����ĺ������У����˻������£�����̫����������ԴԴ��Ϣ���ƺ�\n"
						+"����ӿȪ֮���ۣ���������̺�֮���飬����������������£�������Բ�����ߣ��徲��΢������\n"
						+"���ɷ꣬��������׷��Ѹ�������徳��������̥���Ƕ��������¡�.....���������飬������ȥ������\n"
						+"�����飬������ȥ......\n"NOR,
             ]));
    set("no_fight", 1);
	setup();
}

void init()
{
	add_action("do_study", "yandu");
}

int do_study(string arg)
{
	object me;
	me = this_player();

	if( !living(me) ) return 0;

	if( (int)me->query_skill("literate", 1) < 10 )
		return notify_fail("����Ҳ����ʶ����,����ж������ķ���\n");
	if (!me->query_temp("tjsg/askzhang"))
		return notify_fail("��������˷��׷ǹʣ�����Ϲ�䣬�������¡�\n");
	
	if( me->is_busy() || me->is_fighting() )
		return notify_fail("����æ���ء�\n");
    if (me->query("quest/wd/yyzq/taiji/pass"))
		return notify_fail("���Ѿ��⿪��̫���񹦣����������ж���\n");   
	if (time()-me->query("quest/wd/yyzq/taiji/time")<86400)
		return notify_fail("������̫�ڿ��ˣ��Ծ������̫��\n");   
	
	if( arg == "wall" ) {
		if( me->query_temp("tjsg/askzhang") ) 
		{
			message_vision("$N��������ĥ��ʯ���ϵ�С�֡�\n", me);
			
			tell_object(me, HIW"�ϵ����ѹ��٣������䵱���˲��࣬�������ģ��ղ������á�����չ��´����ž���\n"+
			"��"RED"̫��ȭ"HIW"���͡�"RED"̫����"HIW"����\n "+"�պ��ޣ����������������˸յ��ڹ��ķ�,����"+HIM+"��̫���񹦡���\n"+
			HIW"���ܹ������������츣�����������չʵأ������Դ�����ȴ��Ը....\n"+
			
			HIY"\t\t������Ȼ��������죬�Ծ��ƶ����ᷢ���ˡ�\n"+
			HIG"\t\t�޼�����������֮ĸ��������ã���Ϊ������\n"+
			RED"\t\t�������У������һ��Բת�ᴮ�����ϲ�����\n"+
			HIC"\t\t��֮��������֮����������˫�ޣ��������С�\n"+

			WHT"\t\t\t������\n"NOR);
			write(HIY"�����д�ϲ��֪������������ʦ����׭���ؼ��ķ������¾�����ϰʯ���ϵ����֣����ид�\n�ԡ�̫����������ָ�������һ����Ρ�\n"NOR);
			me->start_busy(999);
			call_out("yyzq_taiji",1,me);
		
			return 1;
		}
	}
	return notify_fail("�����ɽҰ������Ҫ��ʲô��\n");
}

int yyzq_taiji(object me)
{
  int i,j,total;
  if(!me) return 0;
	
  if(me->query_temp("yyzq_taiji")<(10+random(3)))
    { 
	  me->add_temp("yyzq_taiji",1);
	  switch (random(6))
	  {
		case 0:
			tell_object(me,HIG"\n......��֮��������֮Ƥë����֮������˹��˫��֧�ţ�һ����ͨ��\n"+
			"���������飬������ȥ�����������飬������ȥ......\n\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"������Ȼ��������죬�Ծ��ƶ����ᷢ���ˡ�\n"NOR);
			break;
		case 2:
			tell_object(me,HIG"�޼�����������֮ĸ��������ã���Ϊ������\n"NOR);
		case 3:
			tell_object(me,RED"�������У������һ��Բת�ᴮ�����ϲ�����\n"NOR);
		case 4:
			tell_object(me,HIC"��֮��������֮����������˫�ޣ��������С�\n"NOR);
		case 5:
			tell_object(me,HIY"\nͻȻ�䣬���ƺ�������ʲô...\n"NOR);
	  }
 	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  call_out("yyzq_taiji",3+random(3), me);
  } else
   {  
	  me->delete_temp("yyzq_taiji");
      total = me->query("int")+me->query("str")+me->query("dex")+me->query("con");
      j = 20;
      if(me->query("m-card-vip")) j =  18;
      if(me->query("y-card-vip")) j =  15;
      if(me->query("buyvip"))     j =  10;
      i=random(j);
     
	 if (me->query("kar")<31
		 && i < 2 
		 && random(me->query("kar"))>=27
		 && random(total) >= 120) 		 
     {       
          tell_object(me,HIM"$N�����������ָ�㣬��ǽ�ϵ�����һһ��Ӧ������Լ������ʵս���飬�����ĵã�\n"NOR);
          message_vision(HIG"$N��Ȼ�����Ȼ��������������ת���⣬�糤����ӣ����ϲ�����̫���⾳����\n"NOR,me); 
          tell_object(me,HIR"$N�ֺ�Ȼ������̫������������죬�����˵ľ��ϣ�����̫��������ʶ���ͬ��\n"NOR);
		  tell_object(me,HIY"$N���ڶ�����̫��ȭ�ռ��������أ�����������Ц��ԭ����ˣ�ԭ����ˣ�\n"NOR);
		  tell_object(me,HIW"$N�����ŵ����ð���˼�����پ����ж�̫������������һ��ǰ��δ�е��¾�\n"NOR);
		  
		  message_vision("\n\n$N��Ȼ�о���β��Ѩ����ʹ��һ�����������������γ�һ��Сѭ����˳�Ź�ԪѨֱ�����ף�"
							+"����ͣ��������״̬����������������ֱ������Ѩ��Ȼ���������������ţ���ʮ����¥\n"+
							"�����У�Ȼ��һ�����������µ����������ֳ�����״�������롣�Դ���ת������������Ϣ��"+
							"���ζ���������Ϊ���ͨ�����ˣ�����������һ��ǰ��δ�еľ��磡̫�������˴�ɣ�\n\n"NOR,me);
		  tell_object(me,HBRED+HIW"��ϲ"+me->query("name")+HBRED+HIW"����ǧ����࣬�����޳��䵱̫���񹦡�\n");
          
		  me->set("quest/wd/yyzq/taiji/pass", 1);
          me->set("title",HBMAG+HIW"̫����ʦ"NOR);
		  me->set("mytitle/quest/taijititle",HBMAG+HIW"̫����ʦ"NOR);
          log_file("quest/yyzqtaiji", sprintf("%s(%s) ʧ��%d�κ󣬳ɹ��⿪������̫���񹦵İ��ء���Դ��%d�����飺%d��\n",   
          me->name(1),
          me->query("id"), 
          me->query("quest/wd/yyzq/taiji/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
          me->start_busy(1);
      }
        else
        {
         tell_object(me,HIG"\n���˼��ã�����Ҫ�졣\n"NOR);
         message_vision(HIC"\n$Nҡ��ҡͷ�������̾�˿�����\n"NOR,me); 
		 message_vision(HIY"$Nץ����������˼ڤ�룬�����Լ������޷����������̫���񹦰������ڣ�����һ��Īչ��\n"NOR,me);
         tell_object(me,HBBLU"\n�ܿ�ϧ���㱾�γ���̫���񹦾�������ʧ�ܣ�\n"NOR);
         tell_object(me,HBBLU"��Ŀǰ�ľ�����" + me->query("combat_exp") + "������ʱ�����齣"+ NATURE_D->game_time() + "�����¼��\n"NOR);
         tell_object(me,HBBLU"�㽫�ڼ��24Сʱ������һ�λ��ᣡ��\n\n"NOR);
		 log_file("quest/yyzqtaiji", sprintf("%s(%s) ����������̫���񹦾���ʧ��%d�Ρ���Դ��%d�����飺%d��\n",   
          me->name(1),
          me->query("id"), 
          me->query("quest/wd/yyzq/taiji/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
         me->add("quest/wd/yyzq/taiji/fail",1);
         me->set("quest/wd/yyzq/taiji/exp", me->query("combat_exp") );
         me->start_busy(1);
         me->set("quest/wd/yyzq/taiji/time",time());
		 
        }

     
	 me->delete_temp("tjsg");
	 return 1;
   }

}
