// Add Log By River@SJ 9.21.2001
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", GRN "�Ӱ�" NOR);
        set("long", @LONG
����ˮ��֮�ص����Ӳ��ݺᣬǰ����С����·���޷����С�������һƬ��
���֣��������������������һ��С�ţ������¼�ҶС�ۣ���������������
Ů������������ת���˵Ľ���С����
LONG); 
        set("no_sleep_room", 1);
        set("exits", ([
              "west" : __DIR__"xiaojing1",
        ]));
        set("objects", ([
               __DIR__"npc/xia" : 1,                             
        ]));  
        set("outdoors", "����");
	setup(); 
}

void init()
{   
    	object me = this_player();
    	int luck = me->query_temp("oyf/meet");

	    me->receive_damage("jingli", 10);
//     if(!me->query("oyf/son") && me->query("quest/hama/fail") < 10
    if(!me->query("oyf/son")
        && random(me->query("kar"))>27 //teset
		&& random(10)>6  //�˴��޸ı�� 86400
		&& me->query_temp("lmc/throw") 
	    && (time() - me->query("quest/hama/time")) > 86400)
			{
            if(!luck
				&& me->query_condition("bing_poison") > 20
				&& me->query("combat_exp") > 10000){
              		write("\n��ͻȻ���ú������˸��������ת��ͷ��ȴ����ʲôҲû�С�\n\n");
              		me->set_temp("oyf/meet", 1);
              	}
           	else if (luck >= 10) {
                	write("\n��������һ��˵������С���ޣ�֪�������˰գ�����������ϴ̶����ƴӵص��������һ�㡣\n");
                	message_vision("\n$NͻȻ����һ������ͷ�㷢��񱼡�\n",me); 
                	me->delete_temp("oyf/meet");
                	me->set_temp("oyf/ok", 1); 
                	me->delete_temp("lmc/throw");
		        	call_out("wait", 10, me); 
                }
           	else if (luck >= 1) {
                	write("\n��ͻȻ���ú��������������ת��ͷ��ȴ����ʲôҲû�С�\n\n"); 
                	me->add_temp("oyf/meet", 1); 
                }
        }                             
}

void wait(object me)
{
        int total, try;
         object* ppl;
         int i,j = 0;
         if(!me || environment(me) != this_object() || !living(me)) return;
         ppl = users();
		 total = me->query("kar")+me->query("per")+me->query("con");
         try = me->query("quest/hama/fail");
         i = sizeof(ppl);
         while(i--){
           if( userp(ppl[i])&& !wizardp(ppl[i])&&!ppl[i]->query("no_pk")&& ppl[i]->query("oyf/hamagong"))
			   
        j++;
          }
//��һ���������Ƶ�3����ϴ�ָ�����߾Ͳ��ܿ���
//
//���µ���Ϊ��ģʽ���ø�����˽⿪,
	if(random(total) >= 87  
		  && me->query("kar")<31
		  && me->query("per")<31
		  && me->query("con") <31
		  && j<=300  //3�Ķ���300�����1��������
		  && random(j+1)>=j
		  && random( me->query("kar"))>28 
		  && ( random(10)==1||(me->query("buyvip")&& random(4)==1)) ) 
	     {	      
	    	message_vision(HIR"\n$Nֻ���ֱ���ľ�����Ѳ���ʹ����ֻ���ô����죬��֪����Ǻã��������ܽ����������ӡ�\n\n"NOR,me);  
		   	me->set("quest/hama/move", 1);
	     	log_file("quest/hamagong", sprintf("%8s%-10sʧ��%d�κ󣬳ɹ����������֣�����%d���ݣ�%d������%d��\n", 
			me->name(1),"("+me->query("id")+")", me->query("quest/hama/fail"), me->query("kar"), me->query("per"), me->query("con")), me);
            me->move(__DIR__"river1");
			
        }    

	//�ϴ���
/*	  if(random(total) >= 84  //�Ķ� 87->85->84
		  && me->query("kar")<31
		  && me->query("per")<31
		  && j<=300  //3�Ķ���300�����1��������
		  && ( random(7)==1||(me->query("buyvip")&& random(4)==1)) ) 
	     {
 
	       if(random(total) >=80  //�Ķ���ԭ��85
			 && me->query("kar")<31
			 && me->query("per") <31
			 && me->query("con") <31
			// && j<=300 //3�Ķ���300�����1��������
		     && random( me->query("kar"))>=25 ) //26
	        {
	    	message_vision(HIR"\n$Nֻ���ֱ���ľ�����Ѳ���ʹ����ֻ���ô����죬��֪����Ǻã��������ܽ����������ӡ�\n\n"NOR,me);  
		   	me->set("quest/hama/move", 1);
	     	log_file("quest/hamagong", sprintf("%8s%-10sʧ��%d�κ󣬳ɹ����������֣�����%d���ݣ�%d������%d��\n", 
			me->name(1),"("+me->query("id")+")", me->query("quest/hama/fail"), me->query("kar"), me->query("per"), me->query("con")), me);
            me->move(__DIR__"river1");
			}
        }   */ 
       else {
              	me->add("quest/hama/fail", 1); 
              	me->set("quest/hama/time", time());
	    	    log_file("quest/hamagong", sprintf("%8s%-10s��%d��ʧ��δ���������֣�����%d���ݣ�%d������%d��\n",
			    me->name(1), "("+me->query("id")+")", me->query("quest/hama/fail"), me->query("kar"), me->query("per"), me->query("con")), me);
              	message_vision(HIR"\n$N����ͻȻһ����µµ�ع�������ʮ�ɣ�\n\n"NOR,me);
              	me->delete_temp("oyf/ok");     
              	me->move(__DIR__"shulin1");
              	me->receive_damage("qi", 100);
              	me->receive_wound("qi", 100);
              	tell_room(environment(me), HIR + me->name()+"��µµ�ع��˹��������ڵ��ϰ�������������\n" NOR,({ me }));   
        }  
}

int valid_leave(object me, string dir)
{
        if (me->query_temp("oyf/ok") && dir == "west")
                return notify_fail("��������һ���죬һ����Ӱ����ͷ��Ծ������������ǰ��\n");
        return ::valid_leave(me, dir);
}
