// Room: lwhole.c

#include <ansi.h>;

inherit ROOM;

void create()
{
     set("short", "ʯ���Ҷ�");
     set("long", @LONG
����һ��Ȼʯ�������Ǻ����̫������ʱ��ֱ��ȫ��������������
��ס����������һʯ������߷���һЩʯ�룬�����ʯ��(wall)ʮ��ƽ����
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
     
	 add_action("do_study", "yanjiu");
}

int do_study(string arg)
{
     object me;
     me = this_player();

     if ( !living(me) ) return 0;

     if ((int)me->query_skill("literate", 1) < 200)
		return notify_fail("����Ҳ����ʶ����(200),����ж������ķ���\n");
	 if (me->query("family/family_name")!="�䵱��"||me->query("family/master_name")!="������")
	 {
		 return notify_fail("�㲻�������˵ĵ��ӣ����˷Ǽ鼴����\n");
	 }
	 if (!me->query_temp("tjsg/askzhang"))
	 {
		 return notify_fail("�˴����������˾���֮����������������ģ�û�������˵�ָ�㣬���������˴˵صġ�\n");
	 }
	 if (time()-me->query("quest/wd/yyzq/taiji/time")<86400)
	 {
		 return notify_fail("������Ҳ̫�ڿ��ˣ������䵱�õ��ӡ�\n");
	 }
	 if (me->is_busy())
	 {
		 return notify_fail("����æµ�С�\n");

	 }
	  if (me->quest_temp("tjsg/canwu"))
	 {
		 return notify_fail("���ڲ����У����÷��ġ�\n");

	 }
     if ( arg =="wall" )
	 {
		if ( (int)me->query("jing")<30) 
		{ 
			write("��̫���ˣ�����Ъ�����ж��ɣ�\n");
			return 1;
		}
		if (me->query("quest/wd/yyzq/taiji/pass"))
		{
			write("�����ʯ����ϰһ�ᣬֻ���������Ѿ������ء�\n");
			return 1;
		}
		if (me->query("quest/wd/yyzq/taiji/pass"))
		{
			write("�����ʯ����ϰһ�ᣬֻ���������Ѿ������ء�\n");
			return 1;
		}
		message_vision("$N���������˵����ѿ�ʼ��ڣ�����ӡ֤��������ĥ��\n", me);
		write("�㾲����ϰʯ���ϵ��ؼ��������������ڹ��ķ���Щ����\n");
		me->receive_damage("jing", 40);
		me->receive_damage("jingli", 15);
		me->improve_skill("yinyun-ziqi", (int)me->query("int"));
		me->start_busy(999);
		me->set_temp("tjsg/canwu",1);
		call_out("thinking",1,me);
		
		return 1;
   }
}

int thinking(object me)
{
  int i,j,total;
  if(!me) return 0;
	
 if(me->query_temp("wdtaiji_canwu")<(10+random(10)))
    { 
	  me->add_temp("wdtaiji_canwu",1);
      if(random(2)) tell_object(me,HIG"\n����������Ÿղ���������ָ����ڹ��ķ����ز���ǽ�����ֲ���ӡ֤.\n"NOR);
             else tell_object(me,HIY"\n��۾������о�ǽ�ϵ����֣�ͻȻ�䣬���ƺ�ץ����ʲô...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
	}
   else
   {  
	  me->delete_temp("wdtaiji_canwu");
      total = me->query("str") + me->query("con")+ me->query("dex")+ me->query("int");
      j = 25;
      if(me->query("m-card-vip")) j =  23;
      if(me->query("y-card-vip")) j =  20;
      if(me->query("buyvip"))     j =  18;
	  i= random(j);
 
 
    if(i=2 
		&& random(total)>120
		&& random(me->query("kar"))>28)
	 {
		tell_object(me,HIC"\n�㰴���������ָ�㣬����ʯ���ϵľ��ı˴�ӡ֤�ƺ���Щ�ĵá�\n"NOR);
        tell_object(me, HIW"�㰴�����������ԣ���Ϣ���ԡ���ǿѨ������������ᡢ���ء����š�����\n+"+
"��Ѩ��һ·���ż�׵�������ߵĶ��Ǳ��϶��θ���ҪѨ��Ȼ���Ǽ��С����ࡢ������������\n"+
"��̨��������������յ�����׵�����š��縮���Ի���ǿ�䡢�󶥡��������ŵġ��ٻ�Ѩ����\n"NOR);
		tell_object(me,HIY"\n\n������ǧ����࣬���ڵó���Ը����̫�����ڻ��ͨ��\n"NOR);
	
		me->set("quest/wd/yyzq/taiji/pass",1);
		me->set("title",HIC"̫����ʦ"NOR);
		me->set("mytitle/quest/taijititle",HBMAG+HIW"̫����ʦ"NOR);
		me->delete_temp("tjsg");
		me->start_busy(1);
		log_file("quest/yyzqtaiji", sprintf("%8s(%8s) ʧ��%d�κ󣬳�������������̫֮���񹦵İ��ء�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/wd/yyzq/taiji/fail"),i,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/wd/yyzq/taiji/fail",1);
		me->set("quest/wd/yyzq/taiji/time",time());
		
		tell_object(me,HIG"\n\n����̫����ʧ�ܣ���\n"+HIY+"�㾭���Լ��Ĳ��ϲ�����Ȼ��˵�����䵱̫���񹦵İ��أ����Ƕ�����������̫�����а���ȫȻ����Ҫ�졣\n\n"NOR);
		me->delete_temp("tjsg");
		me->start_busy(1);
		log_file("quest/yyzqtaiji", sprintf("%8s(%8s) ������̫֮���񹦽���ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/wd/yyzq/taiji/fail"),i,me->query("combat_exp")) );
	  }
    	return 1;
  }

}

	

