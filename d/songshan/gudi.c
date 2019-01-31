// Room: gudi.c �ȵ�
// Created by Numa 1999-12-04

#include <ansi.h>
inherit ROOM;

string do_zb1();

void create()
{
        set("short", HIW"�ȵ�"NOR);
        set("long", @LONG
���ڹ�ʯ��ᾣ���û��һ���·��Ѱ���˴����Ϻ���Ѱ���ط��ɱȣ�
���������ƺ������ϵ��к��紵���������쳣��ɽ��һ������֮���д���
������֮�����ڣ����ܽ�����������ãã��һƬ�����ݵ���������һ�鿴
����������ֵĹ�ʯ(stone)��
LONG);
        set("item_desc",([
                "��ʯ": (: do_zb1 :),
                "ʯ":   (: do_zb1 :),
                "stone":(: do_zb1 :),
        ]));
        set("outdoors", "��ɽ");
        setup();
}

string do_zb1()
{
        object me = this_player();
        
        if (!me->query_temp("ss/zsb_5"))
                return "������֮�����ǹ�ʯ�����޴���Ķ��ڹ���,���˰��쿴����ɶ����\n";
        //me->delete_temp("ss/zsb_5");
        me->set_temp("ss/zsb_end",1);
        return "������֮�����ǹ�ʯ�����޴���Ķ��ڹ��С�������һ��ʯͷ���ƺ��ж�������˸��\n";
}



void init()
{
        object ob = this_player();
        if (userp(ob))
        {
                if (ob->query_skill("hanbing-zhenqi",1) < 500)
                {
                        message_vision(HIW"$N���¹ȣ����ȫ���飬���ŵ�˳���������˻�ȥ��\n"NOR,ob);
                        ob->move(__DIR__"dtlxia");
                        message_vision(BLU"$N��ɫ���࣬��Ļ���ֱ���¡�\n"NOR,ob);
                        return;
                }
                else if (ob->query_skill("hanbing-zhenqi",1) > 550)
                        message_vision(HIW"$N˳������������������û��ʲô�����ĸо���\n"NOR,ob);
                else
                {
                        ob->set_temp("ss/get_cold",1);
                        message_vision(HIW"$N���¹ȣ�ֻ�о����������²�󣬲��ɵô��˸������\n"NOR,ob);
                }
        }
        add_action("do_back",({"climb","pa"}));
        add_action("do_resist",({"resist","diyu","kangheng"}));
        add_action("do_move",({"fan","move"}));
}

int do_back(string arg)
{
        object me = this_player();
        
        if (!arg)
                return notify_fail("ʲô��\n");
        if (arg != "up" && arg != "back")
                return notify_fail("��Ҫ����������\n");

        if(me->query_encumbrance() * 100 / me->query_max_encumbrance() > 20)
                return notify_fail("�㱳��ô�ණ�������µ�������\n");
        
        message_vision("$N���˴��֣�һ������˳��ɽ��������ȥ��\n",me);
        me->add("jingli",100);
        me->add("neili",200);
        me->delete_temp("ss");
        me->move(__DIR__"dtlxia");
        tell_room(environment(me),me->name(1)+"�ӹȵ������������۵�����������\n",({me}));
        return 1;
}

int do_move(string arg)
{
        object me = this_player();
        object ob, *clone;
        int i, j;
        
        if (!arg)
                return 0;
        if (arg != "stone" && arg != "ʯͷ" && arg != "��ʯ")
                return 0;
        if (!me->query_temp("ss/zsb_end"))
                return notify_fail("û�±��Ұ�ʯͷ���Ա��˳ŵģ�\n");

        if (me->query("neili") < 2000)
        {
                message_vision("$N�þ�ȫ����Ҫ�Ὺʯͷ��û�뵽һ������ʯͷ�������Լ����ϡ�\n",me);
                me->unconcious();
                return 1;
        }
        me->add("neili",-1000);
        message_vision("$N�þ�ȫ�������һ����ʯͷ���˿�����\n",me);

        ob = unew(__DIR__"obj/ice");

        if(!clonep(ob))
                return notify_fail("�㷢������ʲô��û�С�\n");
        i = ob->query("unique");
        clone = filter_array(children(base_name(ob)), (: clonep :));
        j = sizeof(clone);
        while (j--)
                if (!clone[j]->query("clone_by_wizard"))
                        i--; 
        if(clonep(ob) && i < 0)
        {
                destruct(ob);
                return notify_fail("�㷢������ʲô��û�С�\n");
        }

        tell_object(me,"�㷢��ʯͷ�о�Ȼ��һ���������м��ƺ�����ʲô������\n");
        ob->set_temp("find_by",me->query("id"));
        ob->move(this_object());
        me->delete_temp("ss/zsb_end");
        me->set_temp("ss/zsb_get",1);
        return 1;
}
        
int do_resist(string arg)
{
        object me = this_player();
        object ob = this_object();
        
        if (!arg)
                return 0;
		//����
		if (!present("xuan bing",environment(me)))
		{
			message_vision("����������û����������ô�ֿ��ź���ҲûʲôЧ����\n",me);
			return 1;
		}
		//
		if (!me->query_temp("hbzq/askzuo")) 
		{
			me->add_condition("cold_poison",10);

			return notify_fail(HIC"�����Х���㶳��ɪɪ������������֪�������ź����ķ��ţ�������Ϊ�������ˡ�\n"NOR);
		}

        if (arg == "hanfeng" || arg == "cold" || arg == "hanleng" ||arg == "����"||arg == "����"||arg == "����"||arg == "����")
        {
                /*if (!me->query("ss/hb_improve"))
                        return 0;
                if (!me->query_temp("ss/get_cold"))
                        return notify_fail("��Ҫ��ʲô��\n");*/
				if (!me->query_temp("hbzq/askzuo"))
                        return notify_fail("û��ʦ��ָ�㣬������Ϲ׽��ɶ��\n");
        
                if (me->query_skill("hanbing-zhenqi",1) < 450
                ||  me->query("max_neili") < 3000)
                        return notify_fail("��ĺ���������Ϊ���֮��(����450)��ǿ���뺮���࿹����»�������Σ�ա�\n");

                if (me->is_busy() || me->is_fighting())
                        return notify_fail("����æ���أ�\n");
        
                if (me->query("jingli")<50)
                        return notify_fail("������̫���ˣ�������Ϣһ�°ɣ�\n");

                if (me->query("neili")<100)
                        return notify_fail("������̫���ˣ�������Ϣһ�°ɣ�\n");

                if (me->query("jing")<50)
                        return notify_fail("������̫���ˣ�������Ϣһ�°ɣ�\n");
                
//              me->delete_temp("ss/get_cold");
                tell_object(me,BLU"�㾲�����ȶ������������ں������������ĺ����࿹�⡣\n"NOR);
                tell_room(ob,HIW + me->name(1) + "���ȶ���������һ�ɰ��������š�\n"NOR,({me}));
				me->add_temp("ss/kangheng",1);

                me->start_busy(5);
                remove_call_out("hb_improving");
                call_out("hb_improving",4,me);
                return 1;
        }
        else
                return notify_fail("��Ҫ��ʲô�࿹�⣿\n");
}

int hb_improving(object me)
{
        int i,num;
/*      
        if (!me)
        {
                remove_call_out("hb_improving");
                return 1;
        }
*/      
        if (!me->query("songshan_point"))
                i = 100;
        else
                i = me->query("songshan_point")/3;
        if (i<100)
                i = 100;
        if (i>600)
                i = 600;
        
        me->receive_damage("jingli",30);
        me->receive_damage("neili",50);
        if (random(5)>3)
        {
                tell_object(me,"ͻȻһ��ǿ�紵������Ҳ���ɵô��˸������\n");
                me->receive_damage("jing",30);
        }
        i += (400 - me->query_skill("hanbing-zhenqi",1))*2;
        if (i>800)
                i = 800;
		me->improve_skill("hanbing-zhenqi", i*2/3 + random(i));
        tell_object(me,HIC"�����뺮��Ŀ��⵱�к�����������ΪҲ���������\n"NOR);
		//���Ӳ��򴥷�
		
		num=me->query_temp("ss/kangheng",1);
		
		if (random(num)>10 
			&& me->query_temp("hbzq/askzuo")
			&& !me->query_temp("ss/iscold"))
		{
			message_vision(HIR"$N�����뺮�翹��֮�ʣ�������ת���������Ե��ǿ�"HIW"����"HIR"��Ȼ�䷢��һ�ɼ���֮��������$N��������\n",me);
			//me->receive_wound("qi",random(1000),"��������������");
			message_vision(HIR"\n\n$Nһʱ���飬�۵�ͻ��һ����Ѫ����ʱ����ʦ���Ķ�������æ��ת���������ķ�����ʼ�ƶ�(liaodu)������\n",me);

			me->apply_condition("cold_poison",5);
			me->set_temp("ss/iscold",1);
				
			add_action("do_heal","liaodu");
		}
        return 1;
}
//��˼���������Ĳ���֮��
//�����ƶ�
int do_heal(object me)
{
	me=this_player();
	me->delete_temp("hbzq/askzuo");
	//me->start_busy(2);
	if (me->query("family/family_name") != "��ɽ��" )
		return notify_fail("�㲻����ɽ�ɵ��ӣ����򲻳�ʲô��������\n");
	if (me->query_skill("hanbing-zhenqi",1) < 450){
		return notify_fail("�㺮��������������450������������\n");
	}
	if (me->is_busy())
	{
		return notify_fail("������æµ�С�\n");
	}
	if (!me->query("quest/ss/dichuan")){
		return notify_fail("��Ǻ��ĵ��ӣ�����ȥ�úð�Ϊ���������ɴ��ȥ���뼸���������ɣ�\n");
	}
	
	if (me->query_skill_mapped("force")!="hanbing-zhenqi")
	{
		return notify_fail("����ڹ����Ǻ�������,�޷���������\n");
	}
    if (me->query("quest/ss/hbzq/pass")){
		return notify_fail("say ���Ѿ������������,������������������\n");       	
	}
	if (time()-me->query("quest/ss/hbzq/time")<86400){
		return notify_fail("say ��Ҳ̫�ڿ����Ү����\n");    	
					
	}
		    message_vision(HIW"$N��ϥ��������ɫ�԰�һƬ���۵��³�һ����Ѫ����Ȼ�����˲��ᡣ\n"NOR,me);
		    message_vision(HIC"$NΪ��ɺ������֣�֪����ʱ������������֮�ʣ�����Ҵ��⣬����������æȥ�ֿ���ɺ�����\n",me);
	
				me->start_busy(999);
				remove_call_out("thinking");
				call_out("thinking",1,me);
			//	me->delete_temp("chaozong/ask",1);
				return 1;
}

int thinking(object me)
{
  int i,j,s; 
  if(!me) return 0;
  i=random(me->query("kar"));
  s=20;

  if(me->query("m-card-vip")) s =  18;
  if(me->query("y-card-vip")) s =  15;
  if(me->query("buyvip"))     s =  10;
  j=random(s);
  me->set("quest/ss/hbzq/time",time());
  me->delete_temp("ss/iscold");

 // me->set("quest/ss/hbzq/thinking",1);

  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) ���򺮱�����ʱ��KAR�쳣����ǰ���飺%d�����䣺%d��kar:%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_hbzq")<(20+random(10)))
  {  
	  me->add_temp("canwu_hbzq",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n���������������������ɺ������⣬��������һů.\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n��Ȼ����������ת���ݣ�����һů���ƺ�ץס��һЩ����,��\n"NOR);
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

	  tell_room(environment(me),HIC""+me->query("name")+"��ɫ�԰ף�üͷ���壬�ƺ��ڵֿ���ʲô...\n"NOR, ({}));

	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);

   } 
   else if (i>25
			&& j<4
			&& random(me->query("con"))>40
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
		 message_vision(HIY"\n$N��Ȼһ��¶�����ǰ���̲����ĺ��������·���˰�ģ��Է���ת������\n"NOR,me); 
		 message_vision(HIC"\n����β�̣����ڶ��������ٻ����ͨ���£���ʮ����¥��ֱ�ﵤ�ﲿλ��ѭ���������ݡ�\n"NOR,me); 
         message_vision(HIG"\n$N������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HIY"\n$N���������������������˺��������İ��أ������������˳��׻�Ȼ��ͨ�������ɡ���\n"NOR,me); 
         log_file("quest/sshanbing", sprintf("%s(%s) �ɹ�����%d�β��򣬻�Ե�ɺ��£��ɹ����򺮱������İ��أ���ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/ss/hbzq/fail"),
		 i,
		 j,
         me->query("combat_exp")));
		 me->start_busy(1);
		 me->set("quest/ss/hbzq/time",time());
		 me->set("quest/ss/hbzq/pass",1);
		 me->set("title",HBBLU+HIW"���������洫"NOR);		 
		 me->set("mytitle/quest/hanbingtitle",HBBLU+HIW"���������洫"NOR);
		 me->delete_temp("canwu_hbzq");
		 me->delete_temp("ss_iscold");
		 me->delete_temp("hbzq/askzuo");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N��̾һ�������������˵��������������һ�����񰡡���\n"NOR,me); 
		 message_vision(HIY"\n���򺮱�������������ʧ�ܣ�\n"NOR,me); 
         log_file("quest/sshanbing", sprintf("%s(%s) ʧ�ܣ���%d��ʧ�ܲ��򺮱���������ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/ss/hbzq/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/ss/hbzq/fail",1);
		 me->set("quest/ss/hbzq/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_hbzq");
		 me->delete_temp("ss_iscold");
		 me->delete_temp("hbzq/askzuo");
		 return 1;
   }

}