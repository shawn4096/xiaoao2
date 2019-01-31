// pingtai.c
// By River 98/08/28

inherit ROOM;
#include <ansi.h>
void create()
{
    set("short", HIC"ƽ̨"NOR);
    set("long", @LONG
������ƽ̨���棬������ľ�Դ䣬ɽ����ѡ��������ң�ֻ�����ʯ���
��һ����ء���ر���ɽ�ȣ���������������������ڣ����ռ�����ơ���ϸһ
����ʯ�ϡ���ڣ����������֮�ԣ��������������С��ʯ�̣�zi���� 
LONG
        );

    set("item_desc", ([
       "zi": HIY"����ħ������ܼ��޵�����£������˹����\n" +
                "\n���غ���Ⱥ�����֣��������������౯�򣡡�\n"NOR,
    ]));

    set("outdoors", "����");

    setup();
}

void init()
{
        add_action("do_move", "move");
        add_action("do_move", "yi");
		add_action("do_yanlian", "yanlian");
        add_action("do_tiao", ({"tiao", "zong"}));
}

int do_move(string arg)
{
        object me;
        me = this_player();
        if (!arg) return 0;
        if (me->is_busy() || me->is_fighting())
                return notify_fail("����æ���ģ�\n");
        if ( arg == "stone" || arg == "shikuai"){
        if ( me->query("max_neili") < 1500 && me->query_str() < 30 )
          return notify_fail("��Ѿ������ƶ�ʯ�飬������˿������\n");
        if ( me->query_temp("weapon"))
          return notify_fail("�����ű�����ô�ƶ�ʯ�飿\n");
           message_vision(YEL"$N��������˿����������ƶ�ʯ�顣\n\n"NOR,me);
           write(HIG"ֻ��ʯ���������ƶ������ʯ���ƿ��ˣ�¶���˽�ڣ����ڡ�\n"NOR);
           set("exits/enter", __DIR__"jianzhong");
           me->receive_damage("neili", 200);
	   me->receive_damage("jingli", 200); 
           remove_call_out("close");
           call_out("close", 5, this_object());
           return 1;
           }
          return notify_fail("��Ҫ�ƶ�ʲô��\n");
}

void close(object room)
{
        message("vision",HIY"ʯ�������ƻ���ԭλ���ֵ�ס����ڡ�\n"NOR, room);
        room->delete("exits/enter");
}

int do_tiao(string arg)
{ 
        object me;
        me = this_player();
        if ( !arg || arg != "down")
         return notify_fail ("������������");
        if ( arg == "down")
         message_vision(HIG"$N���ζ�ת�����ͻʯ�����������ͱڡ�\n"NOR,me);
         me->move(__DIR__"qiaobi");
         me->receive_damage("qi", 200);
		 me->receive_damage("jingli", 200);
         tell_room(environment(me),HIG + me->name() + "���ζ�ת�����ͻʯ��������ƽ̨������������\n"NOR, ({ me }));
         return 1;
} 

int do_yanlian(string arg)
{
	object me;
	me=this_player();
	if (me->is_busy()) return notify_fail("����æµ��....\n");
	if (me->query_temp("wuzhao/yanlian")) return notify_fail("������������....\n");

	if (!arg||arg!="����ʤ����") return notify_fail("����ʲô��\n");
	
	if (me->query("quest/hs/dgjj/wuzhao/pass")||me->query("quest/xtj/wuzhao/pass"))
	{
		QUEST_D->setmytitle(me,"wuzhaotitle",HBWHT+HIC"���¾Ž�������ʤ����"NOR);
		return notify_fail("���Ѿ�������������ʤ���еľ����������˱Ȼ�������\n");
	}
    
	if (!me->query_temp("wuzhao/askfeng")&&!me->query_temp("wuzhao/askyang")) return notify_fail("�����ɽҰ��ģ���Ϲ�Ȼ�������\n");
	
	//if (!me->query_temp("wuzhao/tigangjian")) return notify_fail("��û��Ħ�������еĸֽ����磡\n");
	//if (!me->query_temp("wuzhao/tizhongjian")) return notify_fail("��û��Ħ�������е��ؽ����磡\n");
	if (!me->query_temp("wuzhao/timujian")) return notify_fail("��û��Ħ�������е�ľ�����磡\n");

	
	if (time()-me->query("quest/hs/dgjj/wuzhao/time")<86400||time()-me->query("quest/xtj/wuzhao/time")<86400)
	{
		return notify_fail("������̫�ڿ��ˡ�\n");
	}
	
	if (me->query_temp("wuzhao/askfeng")&& me->query_temp("wuzhao/timujian"))
	{
		me->start_busy(99);
		me->set_temp("wuzhao/yanlian",1);
		//remove_call_out("jj_think");
		call_out("jj_think",1,me);
		return 1;
	}
	if (me->query_temp("wuzhao/askyang"))
	{
		me->start_busy(99);
		remove_call_out("xtj_think");
		call_out("xtj_think",2,me);
		return 1;
	}
	return notify_fail("����ʲô?\n");

}
int jj_think(object me)
{
  int i,j,total;
  if(!me) return 0;
	
  if(me->query_temp("wuzhao_dgjj")<(10+random(3)))
    { 
	  me->add_temp("wuzhao_dgjj",1);
	  switch (random(6))
	  {
		case 0:
			tell_object(me,HIG"\n.���������ͣ��޼᲻�ݣ�����ǰ��֮���˷Ⱥ�����档������.\n\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n\n����ħ������ܼ��޵�����£������˹������\n"NOR);
			break;
		case 2:
			tell_object(me,HIG"\n\n���ؽ��޷棬���ɲ�������ʮ��ǰ��֮�������¡���\n"NOR);
			break;
		case 3:
			tell_object(me,RED"\n\n����ʮ���ᣬ��������ľ��ʯ����Ϊ�����Դ˾��ޣ�������޽�ʤ�н�֮��������\n"NOR);
			me->add_temp("wuzhao/wujian",1);
			break;
		case 4:
			tell_object(me,HIC"\n\n����ޱ������ʮ��ǰ���ã������岻�飬����֮��ȡ���\n"NOR);
			break;
		case 5:
			tell_object(me,HIY"\n\nͻȻ�䣬���է�֣���˲��������ʲô...\n"NOR);
			break;
	  }
 	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  
	  call_out("jj_think",3+random(3), me);

  } else
   {  
	  me->delete_temp("wuzhao_dgjj");
      total = me->query("int")+me->query("str")+me->query("dex")+me->query("con");
      j = 25;
      if(me->query("m-card-vip")) j =  23;
      if(me->query("y-card-vip")) j =  20;
      if(me->query("buyvip"))     j =  15;
      i=random(j-me->query_temp("wuzhao/wujian"));
     
	 if (me->query("kar")<31
		 && i < 2 
		 && random(me->query("kar"))>28
		 && random(total) >= 130) 		 
     {       
          tell_object(me,HIM"�㰴�ս�ڣ������ʾ����ʵս��һһ���飬����Լ������ʵս���飬�����ĵã�\n"NOR);
          message_vision(HIG"$N��Ȼ���Ȼ������������ʤ���еĽ����������⾳����\n"NOR,me); 
          tell_object(me,HIR"����ʱ��ζ����������ʤ���еĵ�����ϣ���������ʤ���е���ʶ���ͬ��\n"NOR);
		  tell_object(me,HIW"�㽫���ŵ����ð���˼�����پ����ж�����ʤ���е���������һ��ǰ��δ�е��¾�\n"NOR);
		  
		
		  tell_object(me,HBRED+HIW"��ϲ"+me->query("name")+HBRED+HIW"����ǧ����࣬�����޳�����ʤ���С�\n");
          
		  me->set("quest/hs/dgjj/wuzhao/pass", 1);
		  QUEST_D->setmytitle(me,"wuzhaotitle",HBWHT+HIC"���¾Ž�������ʤ����"NOR);
          //me->set("title",HBWHT+HIC"������ʦ"NOR);
          log_file("quest/dgjjwuzhao", sprintf("%s(%s) ʧ��%d�κ󣬳ɹ��⿪����ʤ���еİ��ء���Դ��%d�����飺%d��\n",   
          me->name(1),
          me->query("id"), 
          me->query("quest/hs/dgjj/wuzhao/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
          me->start_busy(1);
		  me->delete_temp("wuzhao");
		  return 1;
      }
        else
        {
         tell_object(me,HIG"\n���˼��ã�����Ҫ�졣\n"NOR);
         message_vision(HIC"\n$Nҡ��ҡͷ�������̾�˿�����\n"NOR,me); 
		 message_vision(HIY"$Nץ����������˼ڤ�룬�����Լ������޷����������ʤ���а������ڣ�����һ��Īչ��\n"NOR,me);
         tell_object(me,HBBLU"\n�ܿ�ϧ���㱾�γ�������ʤ���о�������ʧ�ܣ�\n"NOR);
         tell_object(me,HBBLU"��Ŀǰ�ľ�����" + me->query("combat_exp") + "������ʱ�����齣"+ NATURE_D->game_time() + "�����¼��\n"NOR);
         tell_object(me,HBBLU"�㽫�ڼ��24Сʱ������һ�λ��ᣡ��\n\n"NOR);
		 log_file("quest/dgjjwuzhao", sprintf("%s(%s) ���ܶ��¾Ž�����ʤ���о���ʧ��%d�Ρ���Դ��%d�����飺%d��\n",   
          me->name(1),
          me->query("id"), 
          me->query("quest/hs/dgjj/wuzhao/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
          me->add("quest/hs/dgjj/wuzhao/fail",1);
          me->set("quest/hs/dgjj/wuzhao/exp", me->query("combat_exp") );
          me->start_busy(1);
          me->set("quest/hs/dgjj/wuzhao/time",time());
		  me->delete_temp("wuzhao");
		  return 1;
        }
     
	 return 1;
   }
}
/*
int xtj_think(object me)
{
  int i,j,total;
  if(!me) return 0;
	
  if(me->query_temp("wuzhao_xtj")<(10+random(3)))
    { 
	  me->add_temp("wuzhao_xtj",1);
	  switch (random(6))
	  {
		case 0:
			tell_object(me,HIG"\n.���������ͣ��޼᲻�ݣ�����ǰ��֮���˷Ⱥ�����档������.\n\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n\n����ħ������ܼ��޵�����£������˹������\n"NOR);
			break;
		case 2:
			tell_object(me,HIG"\n\n���ؽ��޷棬���ɲ�������ʮ��ǰ��֮�������¡���\n"NOR);
			break;
		case 3:
			tell_object(me,RED"\n\n����ʮ���ᣬ��������ľ��ʯ����Ϊ�����Դ˾��ޣ�������޽�ʤ�н�֮��������\n"NOR);
			me->add_temp("wuzhao/wujian",1);
			break;
		case 4:
			tell_object(me,HIC"\n\n����ޱ������ʮ��ǰ���ã������岻�飬����֮��ȡ���\n"NOR);
			break;
		case 5:
			tell_object(me,HIY"\n\nͻȻ�䣬���է�֣���˲��������ʲô...\n"NOR);
			break;
	  }
 	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  call_out("xtj_think",3+random(3), me);

  } else
   {  
	  me->delete_temp("wuzhao_xtj");
      total = me->query("int")+me->query("str")+me->query("dex")+me->query("con");
      j = 25;
      if(me->query("m-card-vip")) j =  23;
      if(me->query("y-card-vip")) j =  20;
      if(me->query("buyvip"))     j =  15;
      i=random(j-me->query_temp("wuzhao/wujian"));
     
	 if (me->query("kar")<31
		 && i < 2 
		 && random(me->query("kar"))>=27
		 && random(total) >= 130) 		 
     {       
          tell_object(me,HIM"$N���ս�ڣ������ʾ����ʵս��һһ���飬����Լ������ʵս���飬�����ĵã�\n"NOR);
          message_vision(HIG"$N��Ȼ�����Ȼ������������ʤ���еĽ����������⾳����\n"NOR,me); 
          tell_object(me,HIR"$N��ʱ��ζ����������ʤ���еĵ�����ϣ���������ʤ���е���ʶ���ͬ��\n"NOR);
		  tell_object(me,HIW"$N�����ŵ����ð���˼�����پ����ж�����ʤ���е���������һ��ǰ��δ�е��¾�\n"NOR);
		  
		
		  tell_object(me,HBRED+HIW"��ϲ"+me->query("name")+HBRED+HIW"����ǧ����࣬�����޳�����ʤ���С�\n");
          
		  me->set("quest/xtj/wujian/pass", 1);
          //me->set("title",HBWHT+HIC"������ʦ"NOR);
          log_file("quest/dgjjwuzhao", sprintf("%s(%s) ʧ��%d�κ󣬳ɹ��⿪����ʤ���еİ��ء���Դ��%d�����飺%d��\n",   
          me->name(1),
          me->query("id"), 
          me->query("quest/hs/dgjj/wuzhao/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
          me->start_busy(1);
      }
        else
        {
         tell_object(me,HIG"\n���˼��ã�����Ҫ�졣\n"NOR);
         message_vision(HIC"\n$Nҡ��ҡͷ�������̾�˿�����\n"NOR,me); 
		 message_vision(HIY"$Nץ����������˼ڤ�룬�����Լ������޷����������ʤ���а������ڣ�����һ��Īչ��\n"NOR,me);
         tell_object(me,HBBLU"\n�ܿ�ϧ���㱾�γ�������ʤ���о�������ʧ�ܣ�\n"NOR);
         tell_object(me,HBBLU"��Ŀǰ�ľ�����" + me->query("combat_exp") + "������ʱ�����齣"+ NATURE_D->game_time() + "�����¼��\n"NOR);
         tell_object(me,HBBLU"�㽫�ڼ��24Сʱ������һ�λ��ᣡ��\n\n"NOR);
		 log_file("quest/dgjjwuzhao", sprintf("%s(%s) ���ܶ��¾Ž�����ʤ���о���ʧ��%d�Ρ���Դ��%d�����飺%d��\n",   
          me->name(1),
          me->query("id"), 
          me->query("quest/hs/dgjj/wuzhao/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
         me->add("quest/hs/dgjj/wuzhao/fail",1);
         me->set("quest/hs/dgjj/wuzhao/exp", me->query("combat_exp") );
         me->start_busy(1);
         me->set("quest/hs/dgjj/wuzhao/time",time());
		 
        }
     
	 me->delete_temp("wuzhao");
	 return 1;
   }
}

*/